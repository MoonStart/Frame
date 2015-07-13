# Microsoft Developer Studio Project File - Name="sp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sp.mak" CFG="sp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "sp"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sp - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "sp - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\SoftwareServices\Fcpii" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /I "..\..\..\TelecomServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\\" /I "..\..\.." /I "..\..\..\CardServices" /I "..\..\..\CommonPlatforms\CardServices" /I "..\..\..\CommonPlatforms\SoftwareServices\IpcToFacade" /I "..\..\..\shared\include" /I "..\..\..\CommonPlatforms\SoftwareServices" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__SIMULATION__" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\sp.lib"

!ENDIF 

# Begin Target

# Name "sp - Win32 Release"
# Name "sp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\SP_1plus1APSController.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\src\SP_1plus1BaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1CommandProcessorAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1FsmLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1K1K2Receiver.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1K1K2Transmitter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1ProtectionAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1ProtectionGroupConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1ProtectionGroupStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1RequestParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_1plus1Selector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\src\SP_1plus1SubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\src\SP_AdminApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\src\SP_AdminTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_Application.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_APSController.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_CallbackTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_CommandProcessorAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_Fsm1plus1TestParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_FsmGlbTestParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\src\SP_FsmTestParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_FsmTestScenario.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_K1K2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_K1K2Receiver.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_K1K2Transmitter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_ProtectionAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_ProtectionGroupConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_ProtectionGroupConfigRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_ProtectionGroupStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_ProtectionGroupStatusRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\SignalProtection\src\SP_RAM1plus1ProtectionAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\SignalProtection\src\SP_RAM1plus1Selector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\SignalProtection\src\SP_RAM1plus1SubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\SignalProtection\src\SP_RAM1plus1SubApplicationOnAPM.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\src\SP_RammTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_RequestParser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_Selector.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_StatusCollectionAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_SwitchingCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_SwitchingCommandResult.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_SwitchingStatistic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_TestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SP_UnitStatus.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\SP_1plus1APSController.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\SP_1plus1BaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1CommandProcessorAction.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1FsmLogger.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1K1K2Receiver.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1K1K2Transmitter.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1ProtectionAction.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1ProtectionGroupConfig.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1ProtectionGroupStatus.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1RequestParser.h
# End Source File
# Begin Source File

SOURCE=..\SP_1plus1Selector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\SP_1plus1SubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\SP_AdminApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\SP_AdminTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\SP_Application.h
# End Source File
# Begin Source File

SOURCE=..\SP_APSController.h
# End Source File
# Begin Source File

SOURCE=..\SP_CallbackTimer.h
# End Source File
# Begin Source File

SOURCE=..\SP_CommandProcessorAction.h
# End Source File
# Begin Source File

SOURCE=..\SP_Definitions.h
# End Source File
# Begin Source File

SOURCE=..\SP_Fsm1plus1TestParser.h
# End Source File
# Begin Source File

SOURCE=..\SP_FsmGlbTestParser.h
# End Source File
# Begin Source File

SOURCE=..\SP_FsmTestCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\SP_FsmTestParser.h
# End Source File
# Begin Source File

SOURCE=..\SP_FsmTestScenario.h
# End Source File
# Begin Source File

SOURCE=..\SP_K1K2.h
# End Source File
# Begin Source File

SOURCE=..\SP_K1K2Receiver.h
# End Source File
# Begin Source File

SOURCE=..\SP_K1K2Transmitter.h
# End Source File
# Begin Source File

SOURCE=..\SP_LocationPair.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionAction.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionGroupConfig.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionGroupConfigRegion.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionGroupConfigRegionImp.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionGroupStatus.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionGroupStatusRegion.h
# End Source File
# Begin Source File

SOURCE=..\SP_ProtectionGroupStatusRegionImp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\SignalProtection\SP_RAM1plus1ProtectionAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\SignalProtection\SP_RAM1plus1Selector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\TelecomServices\SignalProtection\SP_RAM1plus1SubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\APM8250\TelecomServices\SignalProtection\SP_RAM1plus1SubApplicationOnAPM.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\SignalProtection\SP_RammTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\SP_RequestParser.h
# End Source File
# Begin Source File

SOURCE=..\SP_Selector.h
# End Source File
# Begin Source File

SOURCE=..\SP_StatusCollectionAction.h
# End Source File
# Begin Source File

SOURCE=..\SP_SwitchingCommand.h
# End Source File
# Begin Source File

SOURCE=..\SP_SwitchingCommandResult.h
# End Source File
# Begin Source File

SOURCE=..\SP_SwitchingStatistic.h
# End Source File
# Begin Source File

SOURCE=..\SP_TestMenu.h
# End Source File
# Begin Source File

SOURCE=..\SP_UnitStatus.h
# End Source File
# End Group
# End Target
# End Project
