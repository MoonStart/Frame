# Microsoft Developer Studio Project File - Name="pmLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=pmLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pmLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pmLib.mak" CFG="pmLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pmLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "pmLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "pmLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pmLib - Win32 Release"

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

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /I "..\\" /I "..\..\\" /I "..\..\..\\" /I "..\..\..\incl\stl" /I "..\..\..\incl" /I "..\..\..\CardServices" /I "..\..\..\SoftwareServices\incl" /I "..\..\..\SoftwareServices\Fc" /I "..\..\..\CardServices\T6100_Services" /I "..\..\..\CardServices\T6100_Services\common" /I "..\..\..\SoftwareServices\T6100\common" /I "..\..\..\SoftwareServices\FcPii" /I "..\..\TelecomServices" /I "..\..\..\CommonPlatforms\TelecomServices" /I "..\..\..\CommonPlatforms\CardServices" /I "..\..\..\CommonPlatforms\SoftwareServices\T6100" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__SIMULATION__" /FR /FD /c
# SUBTRACT CPP /WX /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\obj\pm.lib"

!ENDIF 

# Begin Target

# Name "pmLib - Win32 Release"
# Name "pmLib - Win32 Debug"
# Begin Group "Collector"

# PROP Default_Filter ""
# Begin Group "Collector Data (RS, FICON, ESCON, GbE, GOPT)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbCountData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCountData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbDefectData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbDefectData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorData.h
# End Source File
# End Group
# Begin Group "Collector Otu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbCountOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCountOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbDefectOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbDefectOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorOTU.h
# End Source File
# End Group
# Begin Group "Collector Opt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbStatusOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbStatusOpt.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorOpt.h
# End Source File
# End Group
# Begin Group "Collector Laser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbStatusLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbStatusLaser.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorLaser.h
# End Source File
# End Group
# Begin Group "Collector Cop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbDefectCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbDefectCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbStatusCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbStatusCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorCop.h
# End Source File
# End Group
# Begin Group "Collector Oms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbStatusOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbStatusOms.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorOms.h
# End Source File
# End Group
# Begin Group "Collector Eon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbCountEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCountEon.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CollectorEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_CollectorEon.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\PM_BbStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbStatus.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_Collector.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_Collector.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_Counter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_Counter.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_Defect.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_Defect.h
# End Source File
# End Group
# Begin Group "Processor"

# PROP Default_Filter ""
# Begin Group "Processor Data (RS, FICON, ESCON, GbE, GOPT)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriodData.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriodData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbInhibitData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesData.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesData.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeData.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeData.h
# End Source File
# End Group
# Begin Group "Processor Cop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbInhibitCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesCop.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesCop.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeCop.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeCop.h
# End Source File
# End Group
# Begin Group "Processor Laser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbInhibitLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitLaser.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdLaser.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueLaser.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorLaser.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesLaser.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeLaser.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeLaser.h
# End Source File
# End Group
# Begin Group "Processor Otu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbInhibitOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesOtu.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeOtu.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeOtu.h
# End Source File
# End Group
# Begin Group "Processor Opt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbInhibitOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitOpt.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdOpt.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueOpt.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorOpt.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesOpt.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeOpt.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeOpt.h
# End Source File
# End Group
# Begin Group "Processor Oms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbInhibitOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitOms.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdOms.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueOms.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorOms.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesOms.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesOms.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeOms.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeOms.h
# End Source File
# End Group
# Begin Group "Processor Eon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_BbInhibitEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibitEon.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThresholdEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThresholdEon.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValueEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValueEon.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ProcessorEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_ProcessorEon.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesEon.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RulesEon.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_TypeEon.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_TypeEon.h
# End Source File
# End Group
# Begin Group "Counter Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriodCounter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriodCounter.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbCounterReset.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCounterReset.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbCounterThreshold.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCounterThreshold.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbCounterValue.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCounterValue.h
# End Source File
# End Group
# Begin Group "Gauge Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriodGauge.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriodGauge.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbGaugeReset.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbGaugeReset.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbGaugeThreshold.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbGaugeThreshold.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbGaugeValue.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbGaugeValue.h
# End Source File
# End Group
# Begin Group "Base Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriod.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_AccumulationPeriod.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbCfg.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCfg.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbIdf.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbIdf.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbInhibit.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbInhibit.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbObject.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbObject.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbReset.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbReset.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbTca.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbTca.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbThreshold.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbThreshold.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbValue.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbValue.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_Processor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_Processor.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_Rules.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_Rules.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\PM_BbRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbRequest.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_CommandUpdateAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_CommandUpdateAction.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ControlPeriod.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_ControlPeriod.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_LayerElem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_LayerElem.h
# End Source File
# Begin Source File

SOURCE=..\PM_RegionImp.h
# End Source File
# Begin Source File

SOURCE=..\PM_RegionImpVirtual.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RequestAction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_RequestAction.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_ResetRequestPeriod.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PM_ResetRequestPeriod.h
# End Source File
# End Group
# Begin Group "Generic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\OngTelecomServices\Pm\src\PM_BbEndOfPeriod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\OngTelecomServices\Pm\PM_BbEndOfPeriod.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_BbGeneralCfg.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbGeneralCfg.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_Def.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_Def.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\OngTelecomServices\Pm\src\PM_EndOfPeriodAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\OngTelecomServices\Pm\PM_EndOfPeriodAction.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_GenericApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_GenericApplication.h
# End Source File
# Begin Source File

SOURCE=..\src\PM_RegionKeyDefinition.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_RegionKeyDefinition.h
# End Source File
# End Group
# Begin Group "Applications"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\APM8250\Application\src\APM8250_Application.cpp

!IF  "$(CFG)" == "pmLib - Win32 Release"

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\OSC8250\Application\src\OSC8250_Application.cpp

!IF  "$(CFG)" == "pmLib - Win32 Release"

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\osc\Application\src\OSC_Application.cpp

!IF  "$(CFG)" == "pmLib - Win32 Release"

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\RAM\Application\src\RAM_Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\transponder10G\Application\src\TRN10G_Application.cpp

!IF  "$(CFG)" == "pmLib - Win32 Release"

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\transponder\Application\src\TRN_Application.cpp

!IF  "$(CFG)" == "pmLib - Win32 Release"

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\transponderMRTM\Application\src\TRNMRTM_Application.cpp

!IF  "$(CFG)" == "pmLib - Win32 Release"

!ELSEIF  "$(CFG)" == "pmLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\src\PM_BbCfgLayer.cpp
# End Source File
# Begin Source File

SOURCE=..\PM_BbCfgLayer.h
# End Source File
# End Target
# End Project
