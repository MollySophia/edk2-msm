[Defines]
  PLATFORM_NAME                  = trogdor
  PLATFORM_GUID                  = 28f1a3bf-193a-47e3-a7b9-5a435eaab2ee
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010019
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = Platform/Qualcomm/sc7180/sc7180.fdf
  DEVICE_DXE_FV_COMPONENTS       = Platform/Google/sc7180/trogdor.fdf.inc

!include Platform/Qualcomm/sc7180/sc7180.dsc

[BuildOptions.common]
  GCC:*_*_AARCH64_CC_FLAGS =

[PcdsFixedAtBuild.common]
  gQcomTokenSpaceGuid.PcdMipiFrameBufferWidth|1200
  gQcomTokenSpaceGuid.PcdMipiFrameBufferHeight|1920

  # Simple Init
  # gSimpleInitTokenSpaceGuid.PcdGuiDefaultDPI|350

  gRenegadePkgTokenSpaceGuid.PcdDeviceVendor|"Google"
  gRenegadePkgTokenSpaceGuid.PcdDeviceProduct|"Trogdor"
  gRenegadePkgTokenSpaceGuid.PcdDeviceCodeName|"trogdor"
