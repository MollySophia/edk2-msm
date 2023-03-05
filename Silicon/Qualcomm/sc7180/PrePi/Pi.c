// Pi.c: Entry point for SEC(Security).

#include <PiPei.h>
#include <Pi/PiBootMode.h>

#include <Library/ArmLib.h>
#include <Library/ArmMmuLib.h>
#include <Library/PrePiLib.h>
#include <Library/PrintLib.h>
#include <Library/PrePiHobListPointerLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/PlatformPrePiLib.h>
#include <Library/BlParseLib.h>

#include <Ppi/GuidedSectionExtraction.h>
#include <Coreboot.h>

#include "Pi.h"

#define IS_XIP()  (((UINT64)FixedPcdGet64 (PcdFdBaseAddress) > mSystemMemoryEnd) ||\
                  ((FixedPcdGet64 (PcdFdBaseAddress) + FixedPcdGet32 (PcdFdSize)) <= FixedPcdGet64 (PcdSystemMemoryBase)))

UINT64  mSystemMemoryEnd = FixedPcdGet64 (PcdSystemMemoryBase) +
                           FixedPcdGet64 (PcdSystemMemorySize) - 1;

VOID EFIAPI ProcessLibraryConstructorList(VOID);

ARM_MEMORY_REGION_DESCRIPTOR
        MemoryDescriptor[128];
static int MemoryDescriptorIndex = 0;

/**
   Callback function to find TOLUD (Top of Lower Usable DRAM)

   Estimate where TOLUD (Top of Lower Usable DRAM) resides. The exact position
   would require platform specific code.

   @param MemoryMapEntry         Memory map entry info got from bootloader.
   @param Params                 Not used for now.

  @retval EFI_SUCCESS            Successfully updated mTopOfLowerUsableDram.
**/
// EFI_STATUS
// FindToludCallback (
//   IN MEMORY_MAP_ENTRY  *MemoryMapEntry,
//   IN VOID              *Params
//   )
// {
//   //
//   // This code assumes that the memory map on this x86 machine below 4GiB is continous
//   // until TOLUD. In addition it assumes that the bootloader provided memory tables have
//   // no "holes" and thus the first memory range not covered by e820 marks the end of
//   // usable DRAM. In addition it's assumed that every reserved memory region touching
//   // usable RAM is also covering DRAM, everything else that is marked reserved thus must be
//   // MMIO not detectable by bootloader/OS
//   //

//   //
//   // Skip memory types not RAM or reserved
//   //
//   if ((MemoryMapEntry->Type == E820_UNUSABLE) || (MemoryMapEntry->Type == E820_DISABLED) ||
//       (MemoryMapEntry->Type == E820_PMEM))
//   {
//     return EFI_SUCCESS;
//   }

//   //
//   // Skip resources above 4GiB
//   //
//   if ((MemoryMapEntry->Base + MemoryMapEntry->Size) > 0x100000000ULL) {
//     return EFI_SUCCESS;
//   }

//   if ((MemoryMapEntry->Type == E820_RAM) || (MemoryMapEntry->Type == E820_ACPI) ||
//       (MemoryMapEntry->Type == E820_NVS))
//   {
//     //
//     // It's usable DRAM. Update TOLUD.
//     //
//     if (mTopOfLowerUsableDram < (MemoryMapEntry->Base + MemoryMapEntry->Size)) {
//       mTopOfLowerUsableDram = (UINT32)(MemoryMapEntry->Base + MemoryMapEntry->Size);
//     }
//   } else {
//     //
//     // It might be 'reserved DRAM' or 'MMIO'.
//     //
//     // If it touches usable DRAM at Base assume it's DRAM as well,
//     // as it could be bootloader installed tables, TSEG, GTT, ...
//     //
//     if (mTopOfLowerUsableDram == MemoryMapEntry->Base) {
//       mTopOfLowerUsableDram = (UINT32)(MemoryMapEntry->Base + MemoryMapEntry->Size);
//     }
//   }

//   return EFI_SUCCESS;
// }

/**
   Callback function to build resource descriptor HOB

   This function build a HOB based on the memory map entry info.
   Only add EFI_RESOURCE_SYSTEM_MEMORY.

   @param MemoryMapEntry         Memory map entry info got from bootloader.
   @param Params                 Not used for now.

  @retval RETURN_SUCCESS        Successfully build a HOB.
**/
EFI_STATUS
MemInfoCallback (
  IN MEMORY_MAP_ENTRY  *MemoryMapEntry,
  IN VOID              *Params
  )
{
  EFI_PHYSICAL_ADDRESS         Base;
  EFI_RESOURCE_TYPE            Type;
  EFI_MEMORY_TYPE              MemType;
  UINT64                       Size;
  EFI_RESOURCE_ATTRIBUTE_TYPE  Attribue;
  ARM_MEMORY_REGION_ATTRIBUTES ArmAttribute;

  //
  // Skip everything not known to be usable DRAM.
  // It will be added later.
  //
  switch(MemoryMapEntry->Type) {
    case CB_MEM_RAM:
      Type = EFI_RESOURCE_SYSTEM_MEMORY;
      MemType = EfiConventionalMemory;
      break;
    case CB_MEM_RESERVED:
      Type = EFI_RESOURCE_MEMORY_RESERVED;
      MemType = EfiReservedMemoryType;
      break;

    default:
      return EFI_SUCCESS;
  }

  Base = MemoryMapEntry->Base;
  Size = MemoryMapEntry->Size;

  Attribue = EFI_RESOURCE_ATTRIBUTE_PRESENT |
             EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
             EFI_RESOURCE_ATTRIBUTE_TESTED |
             EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
             EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
             EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
             EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE;
  
  ArmAttribute = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;

  BuildResourceDescriptorHob (Type, Attribue, (EFI_PHYSICAL_ADDRESS)Base, Size);
  if(MemoryMapEntry->Type == CB_MEM_RAM)
    BuildMemoryAllocationHob((EFI_PHYSICAL_ADDRESS)Base, Size, MemType);
  DEBUG ((DEBUG_INFO, "buildhob: base = 0x%lx, size = 0x%lx, type = 0x%x\n", Base, Size, Type));

  ASSERT(MemoryDescriptorIndex < 128);
  MemoryDescriptor[MemoryDescriptorIndex].PhysicalBase = Base;
  MemoryDescriptor[MemoryDescriptorIndex].VirtualBase = Base;
  MemoryDescriptor[MemoryDescriptorIndex].Length = Size;
  MemoryDescriptor[MemoryDescriptorIndex].Attributes = ArmAttribute;
  MemoryDescriptorIndex++;

  return RETURN_SUCCESS;
}

EFI_STATUS
NullMemCallback (
  IN MEMORY_MAP_ENTRY  *MemoryMapEntry,
  IN VOID              *Params
  )
{
  return EFI_SUCCESS; 
}

/**
  It will build HOBs based on information from bootloaders.

  @retval EFI_SUCCESS        If it completed successfully.
  @retval Others             If it failed to build required HOBs.
**/
EFI_STATUS
BuildHobFromBl (
  VOID
  )
{
  EFI_STATUS                        Status;
  EFI_PEI_GRAPHICS_INFO_HOB         GfxInfo;
  EFI_PEI_GRAPHICS_INFO_HOB         *NewGfxInfo;
  EFI_PEI_GRAPHICS_DEVICE_INFO_HOB  GfxDeviceInfo;
  EFI_PEI_GRAPHICS_DEVICE_INFO_HOB  *NewGfxDeviceInfo;

  //
  // Parse memory info and build memory HOBs for Usable RAM
  //
  DEBUG ((DEBUG_INFO, "Dumping RAM Table:\n"));
  Status = ParseMemoryInfo (MemInfoCallback, NULL);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // DEBUG ((DEBUG_INFO, "Assuming TOLUD = 0x%x\n", mTopOfLowerUsableDram));

  // //
  // // Parse memory info and build memory HOBs for Usable RAM
  // //
  // DEBUG ((DEBUG_INFO, "Building ResourceDescriptorHobs for usable memory:\n"));
  // Status = ParseMemoryInfo (MemInfoCallback, NULL);
  // if (EFI_ERROR (Status)) {
  //   return Status;
  // }

  //
  // Create guid hob for frame buffer information
  //
  DEBUG ((DEBUG_INFO, "Dumping GFX info:\n"));
  Status = ParseGfxInfo (&GfxInfo);
  if (!EFI_ERROR (Status)) {
    NewGfxInfo = BuildGuidHob (&gEfiGraphicsInfoHobGuid, sizeof (GfxInfo));
    ASSERT (NewGfxInfo != NULL);
    CopyMem (NewGfxInfo, &GfxInfo, sizeof (GfxInfo));
    DEBUG ((DEBUG_INFO, "Created graphics info hob\n"));
  }

  DEBUG ((DEBUG_INFO, "Dumping GFX info done\n"));

  //
  // Creat SmBios table Hob
  //
  // SmBiosTableHob = BuildGuidHob (&gUniversalPayloadSmbiosTableGuid, sizeof (UNIVERSAL_PAYLOAD_SMBIOS_TABLE));
  // ASSERT (SmBiosTableHob != NULL);
  // SmBiosTableHob->Header.Revision = UNIVERSAL_PAYLOAD_SMBIOS_TABLE_REVISION;
  // SmBiosTableHob->Header.Length   = sizeof (UNIVERSAL_PAYLOAD_SMBIOS_TABLE);
  // DEBUG ((DEBUG_INFO, "Create smbios table gUniversalPayloadSmbiosTableGuid guid hob\n"));
  // Status = ParseSmbiosTable (SmBiosTableHob);
  // if (!EFI_ERROR (Status)) {
  //   DEBUG ((DEBUG_INFO, "Detected Smbios Table at 0x%lx\n", SmBiosTableHob->SmBiosEntryPoint));
  // }

  //
  // Creat ACPI table Hob
  //
  // AcpiTableHob = BuildGuidHob (&gUniversalPayloadAcpiTableGuid, sizeof (UNIVERSAL_PAYLOAD_ACPI_TABLE));
  // ASSERT (AcpiTableHob != NULL);
  // AcpiTableHob->Header.Revision = UNIVERSAL_PAYLOAD_ACPI_TABLE_REVISION;
  // AcpiTableHob->Header.Length   = sizeof (UNIVERSAL_PAYLOAD_ACPI_TABLE);
  // DEBUG ((DEBUG_INFO, "Create ACPI table gUniversalPayloadAcpiTableGuid guid hob\n"));
  // Status = ParseAcpiTableInfo (AcpiTableHob);
  // if (!EFI_ERROR (Status)) {
  //   DEBUG ((DEBUG_INFO, "Detected ACPI Table at 0x%lx\n", AcpiTableHob->Rsdp));
  // }

  //
  // Create guid hob for acpi board information
  //
  // AcpiBoardInfo = BuildHobFromAcpi (AcpiTableHob->Rsdp);
  // ASSERT (AcpiBoardInfo != NULL);

  return EFI_SUCCESS;
}

VOID
PrePiMain(
  IN VOID *StackBase,
  IN UINTN StackSize
  )
{

  EFI_HOB_HANDOFF_INFO_TABLE *HobList;
  EFI_STATUS                  Status;

  UINTN MemoryBase     = 0;
  UINTN MemorySize     = 0;
  UINTN UefiMemoryBase = 0;
  UINTN UefiMemorySize = 0;

  UINTN HcrReg;

  // Architecture-specific initialization
  // Enable Floating Point
  ArmEnableVFP();

  if (ArmReadCurrentEL() == AARCH64_EL2) {
    HcrReg = ArmReadHcr ();

    // Trap General Exceptions. All exceptions that would be routed to EL1 are routed to EL2
    HcrReg |= ARM_HCR_TGE;

    ArmWriteHcr (HcrReg);

    /* Enable Timer access for non-secure EL1 and EL0
       The cnthctl_el2 register bits are architecturally
       UNKNOWN on reset.
       Disable event stream as it is not in use at this stage
    */
    ArmWriteCntHctl(CNTHCTL_EL2_EL1PCTEN | CNTHCTL_EL2_EL1PCEN);
  }

  /* Enable program flow prediction, if supported */
  ArmEnableBranchPrediction();

  // Declare UEFI region
  MemoryBase     = FixedPcdGet32(PcdSystemMemoryBase);
  MemorySize     = FixedPcdGet32(PcdSystemMemorySize);
  UefiMemoryBase = FixedPcdGet32(PcdUefiMemPoolBase);
  UefiMemorySize = FixedPcdGet32(PcdUefiMemPoolSize);
  StackBase      = (VOID *)(UefiMemoryBase + UefiMemorySize - StackSize);

  DEBUG((EFI_D_INFO,
         "Overriding CorebootTable addr from 0x%llx to 0x%llx\n",
         GET_BOOTLOADER_PARAMETER(),
         0xffec4000));
  Status = PcdSet64S (PcdBootloaderParameter, 0xffec4000);
  ASSERT_EFI_ERROR (Status);

  UINTN SPSel = 0;
  asm volatile(
    "mrs %0, SPSel" : "+r"(SPSel)
  );

  DEBUG(
      (EFI_D_INFO | EFI_D_LOAD,
       "UEFI Memory Base = 0x%llx, Size = 0x%llx \n"
       "Stack Base = 0x%llx, Stack Size = 0x%llx \n"
       "CorebootTable = 0x%llx, Current EL = 0x%x, SPSel = 0x%x\n",
       UefiMemoryBase, UefiMemorySize, StackBase, StackSize,
       GET_BOOTLOADER_PARAMETER(), ArmReadCurrentEL(), SPSel));

  // Set up HOB
  HobList = HobConstructor(
      (VOID *)UefiMemoryBase, UefiMemorySize, (VOID *)UefiMemoryBase,
      StackBase);

  PrePeiSetHobList (HobList);

  // Invalidate cache
  InvalidateDataCacheRange(
      (VOID *)(UINTN)PcdGet64(PcdFdBaseAddress), PcdGet32(PcdFdSize));

  // BuildHobFromBl();

  // MemoryDescriptor[MemoryDescriptorIndex].PhysicalBase = PcdGet64(PcdFdBaseAddress);
  // MemoryDescriptor[MemoryDescriptorIndex].VirtualBase  = PcdGet64(PcdFdBaseAddress);
  // MemoryDescriptor[MemoryDescriptorIndex].Length       = PcdGet32(PcdFdSize);
  // MemoryDescriptor[MemoryDescriptorIndex].Attributes   = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;

  // MemoryDescriptorIndex++;

  // MemoryDescriptor[MemoryDescriptorIndex].PhysicalBase = 0;
  // MemoryDescriptor[MemoryDescriptorIndex].VirtualBase  = 0;
  // MemoryDescriptor[MemoryDescriptorIndex].Length       = 0;
  // MemoryDescriptor[MemoryDescriptorIndex].Attributes   = 0;

  // DEBUG((EFI_D_INFO, "enable MMU:\n"));
  // Status = ArmConfigureMmu(
  //     MemoryDescriptor, &TranslationTableBase, &TranslationTableSize);

  // if (EFI_ERROR(Status)) {
  //   DEBUG((EFI_D_ERROR, "Error: Failed to enable MMU: %r\n", Status));
  // }

  // Initialize MMU
  Status = MemoryPeim(UefiMemoryBase, UefiMemorySize);
  ASSERT_EFI_ERROR (Status);
  
  DEBUG((EFI_D_INFO, "build stack hob:\n"));
  // Add HOBs
  BuildStackHob ((UINTN)StackBase, StackSize);

  DEBUG((EFI_D_INFO, "build cpu hob\n"));

  // TODO: Call CpuPei as a library
  BuildCpuHob (ArmGetPhysicalAddressBits (), PcdGet8 (PcdPrePiCpuIoSize));

  DEBUG((EFI_D_INFO, "set boot mode\n"));

  // Set the Boot Mode
  SetBootMode (BOOT_WITH_DEFAULT_SETTINGS);

  // Initialize Platform HOBs (CpuHob and FvHob)
  DEBUG((EFI_D_INFO, "PlatformPeim In \n"));
  Status = PlatformPeim();
  ASSERT_EFI_ERROR (Status);

  // Now, the HOB List has been initialized, we can register performance information
  // PERF_START (NULL, "PEI", NULL, StartTimeStamp);

  // SEC phase needs to run library constructors by hand.
  ProcessLibraryConstructorList();

  // Assume the FV that contains the SEC (our code) also contains a compressed FV.
  DEBUG((EFI_D_INFO, "DecompressFirstFv In \n"));
  Status = DecompressFirstFv();
  ASSERT_EFI_ERROR (Status);

  // Load the DXE Core and transfer control to it
  DEBUG((EFI_D_INFO, "LoadDxeCoreFromFv In \n"));
  Status = LoadDxeCoreFromFv(NULL, 0);
  ASSERT_EFI_ERROR (Status);
}

VOID
CEntryPoint(
  IN VOID *StackBase,
  IN UINTN StackSize,
  IN UINTN BootloaderParameters
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  // Save coreboot parameters
  Status = PcdSet64S (PcdBootloaderParameter, BootloaderParameters);
  ASSERT_EFI_ERROR (Status);

  // Do platform specific initialization here
  PlatformInitialize();

  // Goto primary Main.
  PrePiMain(StackBase, StackSize);

  // DXE Core should always load and never return
  ASSERT(FALSE);
}

VOID
SecondaryCEntryPoint(
  IN  UINTN  MpId
  )
{
  // We must never get into this function on UniCore system
  ASSERT(FALSE);
}