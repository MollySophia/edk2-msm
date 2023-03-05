#include <Library/PcdLib.h>
#include <Library/ArmLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Library/SerialPortLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryMapHelperLib.h>
#include <Library/PlatformPrePiLib.h>

#include "PlatformUtils.h"

VOID InitializeSharedUartBuffers(VOID)
{
  INTN* pFbConPosition = (INTN*)(FixedPcdGet32(PcdMipiFrameBufferAddress) + (FixedPcdGet32(PcdMipiFrameBufferWidth) * 
                                                                              FixedPcdGet32(PcdMipiFrameBufferHeight) * 
                                                                              FixedPcdGet32(PcdMipiFrameBufferPixelBpp) / 8));

  *(pFbConPosition + 0) = 0;
  *(pFbConPosition + 1) = 0;
}

VOID UartInit(VOID)
{
  SerialPortInitialize();

  InitializeSharedUartBuffers();

  // Avoid notch area
  DEBUG((EFI_D_INFO, "\n\n\n\nRenegade Project edk2-msm (AArch64)\n"));
  DEBUG(
      (EFI_D_INFO, "Firmware version %s built %a %a\n\n",
       (CHAR16 *)PcdGetPtr(PcdFirmwareVersionString), __TIME__, __DATE__));
}

VOID SetWatchdogState(BOOLEAN Enable)
{
  // MmioWrite32(APSS_WDT_BASE + APSS_WDT_ENABLE_OFFSET, Enable);
}

#define TLMM_NORTH_TILE_BASE		0x03900000
#define TLMM_SOUTH_TILE_BASE		0x03D00000
#define TLMM_WEST_TILE_BASE		0x03500000
#define TLMM_GPIO_OFF_DELTA	0x1000

VOID PlatformInitialize()
{
  // Enable backlight
  MmioWrite32(TLMM_SOUTH_TILE_BASE + 12*TLMM_GPIO_OFF_DELTA + 4, 1 << 1);

  ZeroMem((VOID*)FixedPcdGet32(PcdMipiFrameBufferAddress), (FixedPcdGet32(PcdMipiFrameBufferWidth) * 
      FixedPcdGet32(PcdMipiFrameBufferHeight) * 
      FixedPcdGet32(PcdMipiFrameBufferPixelBpp) / 8));
  // Program fb addr
  MmioWrite32(0x0AE05014, FixedPcdGet32(PcdMipiFrameBufferAddress));
  // Start TE
  MmioWrite32(0x0AE6B800, 0x1);

  UartInit();

  // Disable WatchDog Timer
  SetWatchdogState(FALSE);
}
