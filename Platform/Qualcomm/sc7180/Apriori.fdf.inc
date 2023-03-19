APRIORI DXE {

  #
  # PI DXE Drivers producing Architectural Protocols (EFI Services)
  #
  INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf
  INF MdeModulePkg/Core/Dxe/DxeMain.inf
  INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
  INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/StatusCodeHandlerRuntimeDxe.inf
  INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
  INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
  INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf

  INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf

  FILE DRIVER = f541d663-4a48-40aa-aabf-ff158ccae34c {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/SmemDxe/SmemDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/SmemDxe/SmemDxe.efi
    SECTION UI = "SmemDxe"
  }

  FILE DRIVER = 8E9BD160-B184-11DF-94E2-0800200C9A66 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/DALSYSDxe/DALSYSDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/DALSYSDxe/DALSYSDxe.efi
    SECTION UI = "DALSys"
  }

  FILE DRIVER = af9763a2-033b-4109-8e17-56a98d380c92 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/HWIODxe/HWIODxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/HWIODxe/HWIODxe.efi
    SECTION UI = "HWIODxe"
  }

  FILE DRIVER = 10e193df-9966-44e7-b17c-59dd831e20fc {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/ChipInfoDxe/ChipInfoDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/ChipInfoDxe/ChipInfoDxe.efi
    SECTION UI = "ChipInfo"
  }

  FILE DRIVER = B105211B-BBBD-4ADD-A3B0-D1CF4A52154C {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/PlatformInfoDxe/PlatformInfoDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/PlatformInfoDxe/PlatformInfoDxe.efi
    SECTION UI = "PlatformInfoDxeDriver"
  }

  INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf

  FILE DRIVER = E43128A8-8692-42B6-8AFA-676158578D18 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/ULogDxe/ULogDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/ULogDxe/ULogDxe.efi
    SECTION UI = "ULogDxe"
  }

  FILE DRIVER = ABA01FF8-2CCB-4E12-8B2E-CD3F4A742993 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/CmdDbDxe/CmdDbDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/CmdDbDxe/CmdDbDxe.efi
    SECTION UI = "CmdDbDxe"
  }

  FILE DRIVER = CB29F4D1-7F37-4692-A416-93E82E219711 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/NpaDxe/NpaDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/NpaDxe/NpaDxe.efi
    SECTION UI = "NpaDxe"
  }

  FILE DRIVER = CB29F4D1-7F37-4692-A416-93E82E219766 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/RpmhDxe/RpmhDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/RpmhDxe/RpmhDxe.efi
    SECTION UI = "RpmhDxe"
  }

  FILE DRIVER = B43C22DB-6333-490C-872D-0A73439059FD {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/PdcDxe/PdcDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/PdcDxe/PdcDxe.efi
    SECTION UI = "PdcDxe"
  }

  FILE DRIVER = 4DB5DEA6-5302-4D1A-8A82-677A683B0D29 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/ClockDxe/ClockDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/ClockDxe/ClockDxe.efi
    SECTION UI = "ClockDxe"
  }

  FILE DRIVER = 9c1eb71f-dd6c-4ed5-9f6a-5cc0ca789f16 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/ShmBridgeDxe/ShmBridgeDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/ShmBridgeDxe/ShmBridgeDxe.efi
    SECTION UI = "ShmBridgeDxe"
  }

  FILE DRIVER = 2d7a83e3-e343-4ffb-9109-631f2ee11694 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/TzDxe/ScmDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/TzDxe/ScmDxe.efi
    SECTION UI = "ScmDxe"
  }

  INF MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
  INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf

  # FILE DRIVER = 0d35cd8e-97ea-4f9a-96af-0f0d89f76567 {
  #   SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/UFSDxe/UFSDxe.depex
  #   SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/UFSDxe/UFSDxe.efi
  #   SECTION UI = "UFSDxe"
  # }

  FILE DRIVER = f10f76db-42c1-533f-34a8-69be24653110 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/SdccDxe/SdccDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/SdccDxe/SdccDxe.efi
    SECTION UI = "SdccDxe"
  }

  FILE DRIVER = 6925fad3-e243-4b69-ad61-3f978c8abc60 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/TzDxe/TzDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/TzDxe/TzDxe.efi
    SECTION UI = "TzDxe"
  }

  INF FatPkg/EnhancedFatDxe/Fat.inf

  INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf

  INF EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
  INF MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
  INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
  INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf

!if $(SECURE_BOOT_ENABLE) == TRUE
  INF SecurityPkg/VariableAuthenticated/SecureBootConfigDxe/SecureBootConfigDxe.inf
  INF SecurityPkg/VariableAuthenticated/SecureBootDefaultKeysDxe/SecureBootDefaultKeysDxe.inf
!endif

  INF MdeModulePkg/Universal/BdsDxe/BdsDxe.inf

  INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf

  FILE DRIVER = 8681cc5a-0df6-441e-b4b8-e915c538f067 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/TLMMDxe/TLMMDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/TLMMDxe/TLMMDxe.efi
    SECTION UI = "DALTLMM"
  }

  FILE DRIVER = 2a7b4bef-80cd-49e1-b473-374ba4d673fc {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/SPMIDxe/SPMIDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/SPMIDxe/SPMIDxe.efi
    SECTION UI = "SPMI"
  }

  FILE DRIVER = 7DB0793A-4402-4BE1-906E-D0FABAD2707E {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/DDRInfoDxe/DDRInfoDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/DDRInfoDxe/DDRInfoDxe.efi
    SECTION UI = "DDRInfoDxe"
  }

  FILE DRIVER = 5776232e-082d-4b75-9a0e-fe1d13f7a5d9 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/PmicDxe/PmicDxeWp.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/PmicDxe/PmicDxeWp.efi
    SECTION UI = "PmicDxe"
  }

    FILE DRIVER = 04de8591-d2b3-4077-bbbe-b12070094eb6 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/I2CDxe/I2CDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/I2CDxe/I2CDxe.efi
    SECTION UI = "I2C"
  }

  FILE DRIVER = 7A32BD23-F735-4F57-AA1A-447D2FE3BE0D {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/SPIDxe/SPIDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/SPIDxe/SPIDxe.efi
    SECTION UI = "SPIDxe"
  }

  FILE DRIVER = 569ea0de-b557-4043-84cf-01103fe516e5 {
    SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/GpiDxe/GpiDxe.depex
    SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/GpiDxe/GpiDxe.efi
    SECTION UI = "GpiDxe"
  }

  INF EmbeddedPkg/SimpleTextInOutSerial/SimpleTextInOutSerial.inf
  INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf

  # FILE DRIVER = 5bd181db-0487-4f1a-ae73-820e165611b3 {
  #   SECTION DXE_DEPEX = Platform/EFI_Binaries/Drivers/sc7180/ButtonsDxe/ButtonsDxe.depex
  #   SECTION PE32 = Platform/EFI_Binaries/Drivers/sc7180/ButtonsDxe/ButtonsDxe.efi
  #   SECTION UI = "ButtonsDxe"
  # }

  INF MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
  INF MdeModulePkg/Bus/Usb/UsbMouseDxe/UsbMouseDxe.inf
  INF MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf
}
