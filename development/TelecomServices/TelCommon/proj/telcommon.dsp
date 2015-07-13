# Microsoft Developer Studio Project File - Name="telcommon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=telcommon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "telcommon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "telcommon.mak" CFG="telcommon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "telcommon - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "telcommon - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "telcommon"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "telcommon - Win32 Release"

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

!ELSEIF  "$(CFG)" == "telcommon - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\SoftwareServices\Fcpii" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /I "..\..\..\TelecomServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\\" /I "..\..\.." /I "..\..\..\CardServices" /I "..\..\..\SoftwareServices\T6100" /I "..\..\..\CommonPlatforms\CardServices" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__SIMULATION__" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\TelCommon.lib"

!ENDIF 

# Begin Target

# Name "telcommon - Win32 Release"
# Name "telcommon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\src\TEL_AppIf.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TEL_BbObjectBase.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TEL_BbRegionBase.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TEL_CallbackTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\src\TEL_ContextAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\src\TEL_ShellTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TEL_TraceUtilities.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\TEL_AppIf.h
# End Source File
# Begin Source File

SOURCE=..\TEL_BbObjectBase.h
# End Source File
# Begin Source File

SOURCE=..\TEL_BbRegionBase.h
# End Source File
# Begin Source File

SOURCE=..\TEL_BbRegionBaseImp.h
# End Source File
# Begin Source File

SOURCE=..\TEL_BbRegionBaseImpWithIndex.h
# End Source File
# Begin Source File

SOURCE=..\TEL_CallbackTimer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\TEL_ContextAction.h
# End Source File
# Begin Source File

SOURCE=..\TEL_RegionBaseImpWithIndex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\TelCommon\TEL_ShellTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\TEL_TraceUtilities.h
# End Source File
# End Group
# End Target
# End Project
