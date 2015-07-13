/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     Sebastien Cossette, January 25, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Optical Transport Unit or FEC.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Monitoring/MON_OtuCounters.h>
#include <Monitoring/MON_OtuDefects.h>
#include <Monitoring/MON_AppIf.h>

#include <PM/PM_Def.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbCountOtu.h>
#include <PM/PM_BbDefectOtu.h>
#include <PM/PM_BbStatusOtu.h>
#include <PM/PM_CollectorOtu.h>
#include <SignalProtection/SP_SwitchingStatistic.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>


//-----------------------------------------------------------------
//##ModelId=3C1F6F7D0319
PM_CollectorOtu::PM_CollectorOtu (PM_GenericApplication& theGenericApplication,
                                  FC_OneShotProcess &theProcessorProcess,
                                  uint32 theNumberOfPort,
                                  CT_PM_Side theSide) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_OTU_STRING, theNumberOfPort),
    myCountOtu(NULL),
    myDefectOtu(NULL),
    myStatusOtu(NULL),
    myOtuSide(theSide)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7D032C
PM_CollectorOtu::~PM_CollectorOtu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7D032E
void PM_CollectorOtu::Init()
{
    // Initialize pointers to OTU status and defect regions.
    myCountOtu = &(*myGenericApplication.GetRegionCountOtu());
    myDefectOtu = &(*myGenericApplication.GetRegionDefectOtu());
    myStatusOtu = &(*myGenericApplication.GetRegionStatusOtu());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7D0336
void PM_CollectorOtu::ProcessData()
{
    SP_1plus1BaseApplication* spApp = myGenericApplication.Get1plus1SpApplication();
    SP_SwitchingStatistic* spStatObject = (SP_SwitchingStatistic * ) 0;
    CT_IntfId portId;

    // If the module supports OCH protection, acquire the signal protection
    // switching statistics object.
    if (spApp != NULL) 
    {
        switch (myOtuSide) 
        {
            case CT_PM_PORT_SIDE_0: portId = CT_PORT_SIDE_0; break;
            case CT_PM_PORT_SIDE_1: portId = CT_PORT_SIDE_1; break;
            case CT_PM_PORT_SIDE_2: portId = CT_PORT_SIDE_2; break;
            case CT_PM_PORT_SIDE_3: portId = CT_PORT_SIDE_3; break;
            case CT_PM_PORT_SIDE_4: portId = CT_PORT_SIDE_4; break;
            case CT_PM_PORT_SIDE_5: portId = CT_PORT_SIDE_5; break;
            case CT_PM_PORT_SIDE_6: portId = CT_PORT_SIDE_6; break;
            case CT_PM_PORT_SIDE_7: portId = CT_PORT_SIDE_7; break;
            case CT_PM_PORT_SIDE_8: portId = CT_PORT_SIDE_8; break;
            case CT_PM_PORT_SIDE_9: portId = CT_PORT_SIDE_9; break;
            case CT_PM_PORT_SIDE_10: portId = CT_PORT_SIDE_10; break;
            case CT_PM_PORT_SIDE_11: portId = CT_PORT_SIDE_11; break;
            case CT_PM_PORT_SIDE_12: portId = CT_PORT_SIDE_12; break;
            case CT_PM_PORT_SIDE_13: portId = CT_PORT_SIDE_13; break;
            case CT_PM_PORT_SIDE_14: portId = CT_PORT_SIDE_14; break;
            case CT_PM_PORT_SIDE_15: portId = CT_PORT_SIDE_15; break;
            case CT_PM_PORT_SIDE_16: portId = CT_PORT_SIDE_16; break;
            case CT_PM_PORT_SIDE_17: portId = CT_PORT_SIDE_17; break;
            case CT_PM_PORT_SIDE_18: portId = CT_PORT_SIDE_18; break;
            case CT_PM_PORT_SIDE_19: portId = CT_PORT_SIDE_19; break;
            case CT_PM_PORT_SIDE_20: portId = CT_PORT_SIDE_20; break;
            case CT_PM_PORT_SIDE_21: portId = CT_PORT_SIDE_21; break;
            case CT_PM_PORT_SIDE_22: portId = CT_PORT_SIDE_22; break;
            case CT_PM_PORT_SIDE_23: portId = CT_PORT_SIDE_23; break;
            case CT_PM_PORT_SIDE_24: portId = CT_PORT_SIDE_24; break;
            case CT_PM_PORT_SIDE_25: portId = CT_PORT_SIDE_25; break;
            case CT_PM_PORT_SIDE_26: portId = CT_PORT_SIDE_26; break;
            case CT_PM_PORT_SIDE_27: portId = CT_PORT_SIDE_27; break;
            case CT_PM_PORT_SIDE_28: portId = CT_PORT_SIDE_28; break;
            case CT_PM_PORT_SIDE_29: portId = CT_PORT_SIDE_29; break;
            case CT_PM_PORT_SIDE_30: portId = CT_PORT_SIDE_30; break;
            case CT_PM_PORT_SIDE_31: portId = CT_PORT_SIDE_31; break;
            case CT_PM_PORT_SIDE_85: portId = CT_PORT_SIDE_85; break;
            case CT_PM_PORT_SIDE_86: portId = CT_PORT_SIDE_86; break;
            case CT_PM_PORT_SIDE_87: portId = CT_PORT_SIDE_87; break;
            case CT_PM_PORT_SIDE_88: portId = CT_PORT_SIDE_88; break;
            case CT_PM_LINE_SIDE_0: portId = CT_LINE_SIDE_0; break;
            case CT_PM_LINE_SIDE_1: portId = CT_LINE_SIDE_1; break;
            case CT_PM_LINE_SIDE_2: portId = CT_LINE_SIDE_2; break;
            case CT_PM_LINE_SIDE_3: portId = CT_LINE_SIDE_3; break;
            case CT_PM_LINE_SIDE_4: portId = CT_LINE_SIDE_4; break;
            case CT_PM_LINE_SIDE_5: portId = CT_LINE_SIDE_5; break;
            case CT_PM_LINE_SIDE_6: portId = CT_LINE_SIDE_6; break;
            case CT_PM_LINE_SIDE_7: portId = CT_LINE_SIDE_7; break;
            default: portId = CT_INTF_ID_UNKNOWN;
        }
        spStatObject = spApp->GetSwitchingStat(portId);
    }

    // If MON OTU application is available on the module, 
    // update OTU defect-second counters and failure-second counters
    // and update OTU gauges.
    MON_AppIf*	monOtuApp = myGenericApplication.GetMonApplicationPtr(CT_PM_OTU_MON_APPLICATION);
    MON_AppIf*	monOptApp = myGenericApplication.GetMonApplicationPtr(CT_PM_OPT_MON_APPLICATION);

    if (monOtuApp) 
    {
        MON_OtuDefects &otuDefectsObject = (MON_OtuDefects &)(*(monOtuApp->GetDefectsRegion()))[0];
        (*myDefectOtu)[0].Update( otuDefectsObject );

        MON_OtuCounters &statusObject = (MON_OtuCounters &)(*(monOtuApp->GetCountersRegion()))[0];
        (*myCountOtu)[0].Update(statusObject);
    }

    if (monOptApp) 
    {
        MON_OptDefects &optDefectsObject = (MON_OptDefects &)(*(monOptApp->GetDefectsRegion()))[0];
        (*myDefectOtu)[0].Update( optDefectsObject );
    }

    // Update protection switching stats
    (*myStatusOtu)[0].Update(spStatObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
