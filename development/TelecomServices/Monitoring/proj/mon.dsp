# Microsoft Developer Studio Project File - Name="mon" - Package Owner=<4>

# Microsoft Developer Studio Generated Build File, Format Version 6.00

# ** DO NOT EDIT **



# TARGTYPE "Win32 (x86) Static Library" 0x0104



CFG=mon - Win32 Debug

!MESSAGE This is not a valid makefile. To build this project using NMAKE,

!MESSAGE use the Export Makefile command and run

!MESSAGE 

!MESSAGE NMAKE /f "mon.mak".

!MESSAGE 

!MESSAGE You can specify a configuration when running NMAKE

!MESSAGE by defining the macro CFG on the command line. For example:

!MESSAGE 

!MESSAGE NMAKE /f "mon.mak" CFG="mon - Win32 Debug"

!MESSAGE 

!MESSAGE Possible choices for configuration are:

!MESSAGE 

!MESSAGE "mon - Win32 Release" (based on "Win32 (x86) Static Library")

!MESSAGE "mon - Win32 Debug" (based on "Win32 (x86) Static Library")

!MESSAGE 



# Begin Project

# PROP AllowPerConfigDependencies 0

# PROP Scc_ProjName "mon"

# PROP Scc_LocalPath "."

CPP=cl.exe

RSC=rc.exe



!IF  "$(CFG)" == "mon - Win32 Release"



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



!ELSEIF  "$(CFG)" == "mon - Win32 Debug"



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

# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\SoftwareServices\Fcpii" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100\common" /I "..\..\..\TelecomServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\..\..\osc\TelecomServices" /I "..\..\..\osi\TelecomServices" /I "..\..\..\transponder\TelecomServices" /I "..\\" /I "..\..\.." /I "..\..\..\CardServices" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /I "..\..\..\CommonPlatforms\CardServices" /I "..\..\..\transponder10G\TelecomServices" /I "..\..\..\CommonPlatforms\SoftwareServices" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__SIMULATION__" /FR /YX /FD /GZ /c

# ADD BASE RSC /l 0x409 /d "_DEBUG"

# ADD RSC /l 0x409 /d "_DEBUG"

BSC32=bscmake.exe

# ADD BASE BSC32 /nologo

# ADD BSC32 /nologo

LIB32=link.exe -lib

# ADD BASE LIB32 /nologo

# ADD LIB32 /nologo /out:"..\lib\MONGeneric.lib"



!ENDIF 



# Begin Target



# Name "mon - Win32 Release"

# Name "mon - Win32 Debug"

# Begin Group "Source Files"



# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Source File



SOURCE=..\src\MON_AppIf.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_BbKeys.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_Config.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_Counters.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_Defects.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_MsBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_MsConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_MsCounters.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_MsDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_MsStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_MsSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_MsUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_Object.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchAltStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchMainBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchMainDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchMainSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchMainUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchPower.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchRequest.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchResult.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchSubApplicationG709.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchSubApplicationOlim.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OchUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OchUpdateStatusActionG709.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OduBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OduConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OduCounters.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OduDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OduStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OduSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OduUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OmsBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OmsDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OmsStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OmsSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OmsUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OnDemandPilotToneAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OnDemandPilotToneActionG709.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OptBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OptConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OptDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OptStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OptSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OptUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OtsBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\MON_OtsConfig.h

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsOchOHDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsOchOHUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsOHDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OtsSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtsUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OtuBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtuConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtuCounters.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtuDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtuStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_OtuSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_OtuUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_PilotToneAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_PilotToneControllerRequest.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_PilotToneDirectProcessor.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_PilotToneProcessingController.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_PilotToneProcessor.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_PilotToneProcessorRequest.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_PilotToneTaskProcessor.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_Region.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_RsBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_RsConfig.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_RsCounters.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_RsDefects.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_RsStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_RsSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_RsUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_ShellTestMenu.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_Status.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_TxOptBaseApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_TxOptOnDemandAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_TxOptRequest.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_TxOptResult.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_TxOptStatus.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\src\MON_TxOptSubApplication.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_TxOptUpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\src\MON_UpdateStatusAction.cpp

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\src\TEL_ShellTestMenu.cpp

# End Source File

# End Group

# Begin Group "Header Files"



# PROP Default_Filter "h;hpp;hxx;hm;inl"

# Begin Source File



SOURCE=..\MON_AppIf.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_BbKeys.h

# End Source File

# Begin Source File



SOURCE=..\MON_Config.h

# End Source File

# Begin Source File



SOURCE=..\MON_Counters.h

# End Source File

# Begin Source File



SOURCE=..\MON_Defects.h

# End Source File

# Begin Source File



SOURCE=..\MON_Definitions.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_MsBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_MsCounters.h

# End Source File

# Begin Source File



SOURCE=..\MON_MsDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_MsStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_MsSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_MsUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_Object.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchAltStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchConfig.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchDefects.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchMainBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchMainDefects.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchMainSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchMainUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchPower.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchRequest.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchResult.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchSubApplicationG709.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchSubApplicationOlim.h

# End Source File

# Begin Source File



SOURCE=..\MON_OchUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OchUpdateStatusActionG709.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OduBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OduConfig.h

# End Source File

# Begin Source File



SOURCE=..\MON_OduCounters.h

# End Source File

# Begin Source File



SOURCE=..\MON_OduDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OduStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OduSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OduUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OmsBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OmsDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OmsStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OmsSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OmsUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_OnDemandPilotToneAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OnDemandPilotToneActionG709.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OptBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OptConfig.h

# End Source File

# Begin Source File



SOURCE=..\MON_OptDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OptStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OptSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OptUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OtsBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtsDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtsOchOHDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtsOchOHUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtsOHDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtsStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OtsSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtsUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OtuBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtuConfig.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtuCounters.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtuDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtuStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_OtuSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_OtuUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_PilotToneAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_PilotToneControllerRequest.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_PilotToneDirectProcessor.h

# End Source File

# Begin Source File



SOURCE=..\MON_PilotToneProcessingController.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_PilotToneProcessor.h

# End Source File

# Begin Source File



SOURCE=..\MON_PilotToneProcessorRequest.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_PilotToneTaskProcessor.h

# End Source File

# Begin Source File



SOURCE=..\MON_Region.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_RsBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_RsConfig.h

# End Source File

# Begin Source File



SOURCE=..\MON_RsCounters.h

# End Source File

# Begin Source File



SOURCE=..\MON_RsDefects.h

# End Source File

# Begin Source File



SOURCE=..\MON_RsStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_RsSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_RsUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_ShellTestMenu.h

# End Source File

# Begin Source File



SOURCE=..\MON_Status.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_TxOptBaseApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_TxOptOnDemandAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_TxOptRequest.h

# End Source File

# Begin Source File



SOURCE=..\MON_TxOptResult.h

# End Source File

# Begin Source File



SOURCE=..\MON_TxOptStatus.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\Monitoring\MON_TxOptSubApplication.h

# End Source File

# Begin Source File



SOURCE=..\MON_TxOptUpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\MON_UpdateStatusAction.h

# End Source File

# Begin Source File



SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\TEL_ShellTestMenu.h

# End Source File

# End Group

# Begin Group "test"



# PROP Default_Filter ""

# End Group

# End Target

# End Project

SOURCE=..\MON_MsConfig.h
