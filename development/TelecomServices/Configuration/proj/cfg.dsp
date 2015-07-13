# Microsoft Developer Studio Project File - Name="cfg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cfg - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cfg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cfg.mak" CFG="cfg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cfg - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cfg - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "cfg"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cfg - Win32 Release"

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

!ELSEIF  "$(CFG)" == "cfg - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\SoftwareServices\Fcpii" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100\common" /I "..\..\..\TelecomServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\\" /I "..\..\.." /I "..\..\..\CardServices" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /I "..\..\..\CommonPlatforms\CardServices" /I "..\..\..\CommonPlatforms\SoftwareServices\IpcToFacade" /I "..\..\..\shared\include" /I "..\..\..\CommonPlatforms\SoftwareServices" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__SIMULATION__" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CFGGeneric.lib"

!ENDIF 

# Begin Target

# Name "cfg - Win32 Release"
# Name "cfg - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\CFG_AppIf.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_AtpsFsm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_BbKeys.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Gfp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_GfpAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_GfpAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Hop.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshGfp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshHop.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshMs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshOch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshOdu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshOms.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshOts.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshRs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshSync.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_HwRefreshVcg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Ms.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_MsProt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_MsProtAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Object.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Och.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OchAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OchBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OchSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Odu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OduAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OduAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OduBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OduSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Oms.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OmsAutomaticPwrAdj.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OmsAutomaticShutdown.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OmsAutomaticShutdownAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OmsBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OmsSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Opt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OptAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OptAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OptAutoRateLock.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OptAutoRateLockAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OptBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OptSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Ots.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsAutomaticTxPwrShut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsAutomaticTxPwrShutAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OtsBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsOchOHAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsOchOHAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtsOH.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OtsSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Otu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtuAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_OtuAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OtuBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_OtuSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Region.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Rs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_RsAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_RsAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_RsBaseApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_RsSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_ShellTestMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Sync.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_SyncProt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_SyncProtAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_TxOchAutomatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_TxOchAutomaticAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\src\CFG_TxOchSubApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CFG_Vcg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\CFG_AppIf.h
# End Source File
# Begin Source File

SOURCE=..\CFG_AtpsFsm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_BbKeys.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Definitions.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Gfp.h
# End Source File
# Begin Source File

SOURCE=..\CFG_GfpAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_GfpAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Hop.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshGfp.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshHop.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshMs.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshOch.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshOdu.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshOms.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshOpt.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshOts.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshOtu.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshRs.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshSync.h
# End Source File
# Begin Source File

SOURCE=..\CFG_HwRefreshVcg.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Ms.h
# End Source File
# Begin Source File

SOURCE=..\CFG_MsProt.h
# End Source File
# Begin Source File

SOURCE=..\CFG_MsProtAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Object.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Och.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OchAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OchBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OchSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Odu.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OduAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OduAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OduBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OduSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Oms.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OmsAutomaticPwrAdj.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OmsAutomaticShutdown.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OmsAutomaticShutdownAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OmsBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OmsSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Opt.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OptAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OptAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OptAutoRateLock.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OptAutoRateLockAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OptBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OptSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Ots.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsAutomaticTxPwrShut.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsAutomaticTxPwrShutAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OtsBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsOchOHAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsOchOHAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtsOH.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OtsSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Otu.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtuAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_OtuAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OtuBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_OtuSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Region.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Rs.h
# End Source File
# Begin Source File

SOURCE=..\CFG_RsAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_RsAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_RsBaseApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_RsSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_ShellTestMenu.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Sync.h
# End Source File
# Begin Source File

SOURCE=..\CFG_SyncProt.h
# End Source File
# Begin Source File

SOURCE=..\CFG_SyncProtAction.h
# End Source File
# Begin Source File

SOURCE=..\CFG_TxOchAutomatic.h
# End Source File
# Begin Source File

SOURCE=..\CFG_TxOchAutomaticAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonPlatforms\TelecomServices\Configuration\CFG_TxOchSubApplication.h
# End Source File
# Begin Source File

SOURCE=..\CFG_Vcg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\incl\STL\map.h
# End Source File
# End Group
# End Target
# End Project
