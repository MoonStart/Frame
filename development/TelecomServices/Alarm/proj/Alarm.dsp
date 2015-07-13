# Microsoft Developer Studio Project File - Name="Alarm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Alarm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Alarm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Alarm.mak" CFG="Alarm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Alarm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Alarm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Alarm"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Alarm - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Alarm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Alarm___"
# PROP BASE Intermediate_Dir "Alarm___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj"
# PROP Intermediate_Dir "..\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "..\\" /I "..\..\\" /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\SoftwareServices\FcPii" /I "..\..\TelecomServices" /I "..\..\.." /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /I "..\..\..\CardServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\..\..\CommonPlatforms\CardServices" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__SIMULATION__" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\AlarmGeneric.lib"

!ENDIF 

# Begin Target

# Name "Alarm - Win32 Release"
# Name "Alarm - Win32 Debug"
# Begin Group "BB stuff"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\ALM_FailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_FailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_FailureRegion.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_FailureRegion.h
# End Source File
# Begin Source File

SOURCE=..\ALM_FailureRegionImp.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OchFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OchFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OchOscFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OchOscFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OduFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OduFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OmsFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OmsFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OptFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OptFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OscFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OscFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OtsFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OtsFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OtuFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_OtuFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\ALM_RegionImpVirtual.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_RsFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_RsFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_SyncFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_SyncFailureBase.h
# End Source File
# End Group
# Begin Group "Failure and Filter Actions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\ALM_LayerFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_LayerFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_MsFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_MsFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_MsFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_MsFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OchFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OchFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OchOscFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OchOscFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OduFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OduFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OmsFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OmsFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OptFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OptFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OscFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OscFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OtsFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OtsFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OtuFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_OtuFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_RsFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_RsFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_SyncFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_SyncFailures.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\ALM_AppDecorator.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_AppDecorator.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_AppIf.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_AppIf.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_DefectStatusDefinition.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_FailureModificationAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_FailureModificationAction.h
# End Source File
# Begin Source File

SOURCE=..\ALM_FPCommon.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_ListOfAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_ListOfAction.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_NormalFailure.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_NormalFailure.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_RegionKeyDefinition.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_RegionKeyDefinition.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_SoakingFailure.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_SoakingFailure.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_TransferEnableAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_TransferEnableAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\SoftwareServices\FC\AppFramework\FC_BbApp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\SoftwareServices\FC\AppFramework\FC_BbAppDecoratorImp.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\ALM_GfpFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_GfpFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_GfpFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_GfpFailures.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_HopFailureBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ALM_HopFailureBase.h
# End Source File
# Begin Source File

SOURCE=..\src\ALM_HopFailures.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ALM_HopFailures.h
# End Source File
# Begin Source File

SOURCE=..\ALM_T1E1FailureBase.h
# End Source File
# End Target
# End Project
