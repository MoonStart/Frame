# Microsoft Developer Studio Project File - Name="TsPii" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=TsPii - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TsPii.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TsPii.mak" CFG="TsPii - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TsPii - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TsPii - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "TsPii"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TsPii - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj"
# PROP Intermediate_Dir "..\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "..\..\.." /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\SoftwareServices\FcPii" /I "..\..\..\CardServices" /I "..\..\..\TelecomServices" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /I "..\..\..\CommonPlatforms\CardServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\..\..\transponder" /I "..\..\..\transponder10G" /I "..\..\..\OSC" /I "..\..\..\OSI" /I "..\..\..\transponder\TelecomServices" /I "..\..\..\transponder10G\TelecomServices" /I "..\..\..\transponder10G\CardServices" /I "..\..\..\OSI\TelecomServices" /I "..\..\..\OSC\TelecomServices" /I "..\..\..\shared\include" /I "..\..\..\shared\fw\include" /I "..\..\..\transponder10G\CardServices\Devices" /I "..\..\..\transponderMRTM\TelecomServices" /I "..\..\..\transponderMRTM\CardServices" /I "..\..\..\transponderMRTM\CardServices\Devices" /I "..\..\..\CommonPlatforms\SoftwareServices\IpcToFacade" /I "..\..\..\transponder\CardServices" /I "..\..\..\osc\CardServices" /I "..\..\..\OSC8250\CardServices\Devices" /I "..\..\..\OSC8250\TelecomServices" /I "..\..\..\OSC8250\CardServices" /I "..\..\..\APM8250\TelecomServices" /I "..\..\..\APM8250\CardServices" /I "..\..\..\transponder\fw\hw_control\include" /I "..\..\..\RAM\CardServices" /I "..\..\..\RAM\TelecomServices" /D "DEBUG" /D "MSWINNT" /D "_WINDOWS" /D "_DEBUG" /D "WIN32" /D "__SIMULATION__" /FR /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "TsPii - Win32 Release"
# Name "TsPii - Win32 Debug"
# Begin Group "OSC files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\Application\src\OSC_Application.cpp

!IF  "$(CFG)" == "TsPii - Win32 Release"

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_AmpSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_AmpSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscFwAccess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscFwAccess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscIAMPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscIAMPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscNullAMPPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscNullAMPPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscOAMPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscOAMPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscOpticalIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscOpticalIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscOtsOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscOtsOHIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscPilotToneCtrlAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscPilotToneCtrlAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscPumpOpticalIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscPumpOpticalIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscRsIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscRsIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_OscTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_OscTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_UpdatePdcStateAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_UpdatePdcStateAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\src\TSPII_UpdatePmDataAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\osc\TelecomServices\TsPii_Imp\TSPII_UpdatePmDataAction.h
# End Source File
# End Group
# Begin Group "Generic files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\makefile
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_BaseIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_BaseIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_ClkSelIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_ClkSelIf.h
# End Source File
# Begin Source File

SOURCE=..\TSPII_Common.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_ControlLoop.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_ControlLoop.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_DwIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_DwIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_FecIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_FecIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_GfpIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_GfpIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_HopIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_HopIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_IPCountersIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_IPCountersIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_MsIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_MsIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_OchOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_OchOHIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_OmsOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_OmsOHIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_OpticalIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_OpticalIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_OtsOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_OtsOHIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_PilotToneAction.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_PilotToneAction.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_PilotToneActionFFT.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_PilotToneIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_PilotToneIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_PipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_PipeIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_Region.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_Region.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_RsIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_RsIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_SubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_SubApplication.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_UpdateAction.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_UpdateAction.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_VcgIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_VcgIf.h
# End Source File
# Begin Source File

SOURCE=..\src\TSPII_XcIf.cpp
# End Source File
# Begin Source File

SOURCE=..\TSPII_XcIf.h
# End Source File
# End Group
# Begin Group "Transponder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\Application\src\TRN_Application.cpp

!IF  "$(CFG)" == "TsPii - Win32 Release"

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_FwCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_FwCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_Trn2_5GbETestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_Trn2_5GbETestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_TrnLine2_5GbE_2ROpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_TrnLine2_5GbE_2ROpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_TrnLine2_5GbERsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_TrnLine2_5GbERsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_TrnPilotToneCtrlAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_TrnPilotToneCtrlAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_TrnPort2_5GbE_2ROpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_TrnPort2_5GbE_2ROpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_TrnPort2_5GbERsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_TrnPort2_5GbERsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\src\TSPII_TrnSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\TelecomServices\TsPii_Imp\TSPII_TrnSubApplication.h
# End Source File
# End Group
# Begin Group "CommonPlatforms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\CsPii_Imp\src\CSPII_ComPlatCtrlCPLDDrv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\CsPii_Imp\CSPII_ComPlatCtrlCPLDDrv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\CsPii_Imp\src\CSPII_Mpc860PortDrv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\CsPii_Imp\CSPII_Mpc860PortDrv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\src\DEV_BackIfFpgaBufDescGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\DEV_BackIfFpgaBufDescGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\src\DEV_BackplaneIfFpgaDrv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\DEV_BackplaneIfFpgaDrv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\src\DEV_TdmCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\DEV_TdmDefinition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_CommonPilotToneCtrlAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_CommonPilotToneCtrlAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_CommonPilotToneIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_CommonPilotToneIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_OscCommonTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_OscCommonTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_PilotToneCallback.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_PilotToneCallback.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_PilotToneDebugAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_PilotToneDebugAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_PilotToneSchedulerAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_PilotToneSchedulerAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_ShelfTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_ShelfTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_TestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_TestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\src\TSPII_TrnTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\TSPII_TrnTestMenu.h
# End Source File
# End Group
# Begin Group "Transponder10G"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_FpgaSpiCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_FpgaSpiCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_FpgaSpiCtrlRevA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_FpgaSpiCtrlRevA.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_IXF30005Ctrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_IXF30005Ctrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_IXF30005Drv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_IXF30005Drv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_MemMapHwTrafficCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_MemMapHwTrafficCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_PicProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_PicProgram.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\src\DEV_SpiTransaction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\DEV_SpiTransaction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\CardServices\Devices\PicC\FpgaMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\Application\src\TRN10G_Application.cpp

!IF  "$(CFG)" == "TsPii - Win32 Release"

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_ControlLoopManager10G.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_ControlLoopManager10G.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_ControlLoopPTModulation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_ControlLoopPTModulation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_ControlLoopWaveLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_ControlLoopWaveLocker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_HwRefreshAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_HwRefreshAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_LaserOffOnLOFAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_LaserOffOnLOFAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_Trn10GSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_Trn10GSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_Trn10GTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_Trn10GTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_TrnLine10GDwHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_TrnLine10GDwHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_TrnLine10GFecHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_TrnLine10GFecHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_TrnLine10GOpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_TrnLine10GOpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_TrnLine10GRsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_TrnLine10GRsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_TrnPort10GOpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_TrnPort10GOpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\src\TSPII_TrnPort10GRsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\TelecomServices\TsPii_Imp\TSPII_TrnPort10GRsHwDrvIf.h
# End Source File
# End Group
# Begin Group "TransponderMRTM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\CsPii_Imp\CSPII_TrnMRTMEeprom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_HudsonCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_HudsonCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_HudsonDrv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_HudsonDrv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CAdc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CAdc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CDac.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CDac.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CDeserializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CDeserializer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CDigPot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CDigPot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CTransaction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CTransaction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_I2CXceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_I2CXceiver.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_MrtmParallelIOCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_MrtmParallelIOCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_MrtmSpiTransaction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_MrtmSpiTransaction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_MrtmSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_MrtmSynchronization.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_MrtmUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_MrtmUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_SpiCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_SpiCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_SpiDigPot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_SpiNumCtrlOsc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_TrafficFpgaCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_TrafficFpgaCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\src\DEV_TrafficFpgaDrv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\CardServices\Devices\DEV_TrafficFpgaDrv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\Application\src\TRNMRTM_Application.cpp

!IF  "$(CFG)" == "TsPii - Win32 Release"

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_AD6620Drv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_AD6620Drv.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmControlLoopManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmControlLoopManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmControlLoopWaveLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmControlLoopWaveLocker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmHwRefreshAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmHwRefreshAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmLineDwHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmLineDwHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmLineFecHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmLineFecHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmLineOpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmLineOpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmLineRsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmLineRsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmPilotToneCtrlAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmPilotToneCtrlAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmPortOpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmPortOpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmPortRsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmPortRsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\src\TSPII_MrtmTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\TelecomServices\TsPii_Imp\TSPII_MrtmTestMenu.h
# End Source File
# End Group
# Begin Group "OSC8250"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\Application\src\OSC8250_Application.cpp

!IF  "$(CFG)" == "TsPii - Win32 Release"

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OSC8250HwRefreshAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OSC8250HwRefreshAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OSC8250OchOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OSC8250OchOHIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OSC8250OmsOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OSC8250OmsOHIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OSC8250OpticalIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OSC8250OpticalIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OSC8250OtsOHIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OSC8250OtsOHIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OSC8250RsIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OSC8250RsIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_Osc8250SubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_Osc8250SubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_Osc8250TestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_Osc8250TestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OscMapperFpgaCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OscMapperFpgaCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\src\TSPII_OscMapperFpgaDrv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\TelecomServices\TsPii_Imp\TSPII_OscMapperFpgaDrv.h
# End Source File
# End Group
# Begin Group "APM8250"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APM8250\Application\src\APM8250_Application.cpp

!IF  "$(CFG)" == "TsPii - Win32 Release"

!ELSEIF  "$(CFG)" == "TsPii - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\CardServices\Devices\DEV_TdmCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\proj\makefile
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250AmpPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250AmpPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250EcmmP2LPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250EcmmP2LPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250FcmmEcmmL2PPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250FcmmEcmmL2PPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250FcmmP2LPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250FcmmP2LPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250HwRefreshAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250HwRefreshAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250LegacyPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250LegacyPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250OlimL2PPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250OlimL2PPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250OlimP2LPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250OlimP2LPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250PilotToneCtrlAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250PilotToneCtrlAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250PumpOpticalIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250PumpOpticalIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250ScadQuadP2LPipeIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250ScadQuadP2LPipeIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250SlaveSlot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250SlaveSlot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250SubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250SubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_APM8250TestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_APM8250TestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_CardAmpCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_CardAmpCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_CardCOPMCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_CardCOPMCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\src\TSPII_TdmSlaveCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\TsPii_Imp\TSPII_TdmSlaveCtrl.h
# End Source File
# End Group
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Group "Cards"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\test10g.sh
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\testapm8250.sh
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\testmrtm.sh
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\testosc.sh
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\testosc8250.sh
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\testtrn.sh
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiOmsOchTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiOptPtPipeAmpTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiOptTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiOtsOptRsTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiPipeTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiPtTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiTrnFecDwTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiTrnOptTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiTrnPtTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\test\TspiiTrnRsTest.txt
# End Source File
# End Group
# Begin Group "RAM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\RAM\CardServices\Devices\src\DEV_I2CCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\CardServices\Devices\DEV_I2CCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\CardServices\Devices\src\DEV_SpiCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\CardServices\Devices\DEV_SpiCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamClkSelHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamClkSelHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamClkSelIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamGfpHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamGfpHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamHwRefreshAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamHwRefreshAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamLineHopHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamLineHopHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamLineMsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamLineMsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamLineOpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamLineOpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamLineRsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamLineRsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamPortOpticalHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamPortOpticalHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamPortRsHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamPortRsHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RAMSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamVcgHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamVcgHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\src\TSPII_RamXcHwDrvIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamXcHwDrvIf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\TsPii_Imp\TSPII_RamXcIf.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TsPii_Imp\proj\TSPII_IFAvailability.xls
# End Source File
# End Target
# End Project
