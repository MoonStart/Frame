/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 2004 Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for Near-End SONET/SDH MS layer
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_AppIf.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <PM/PM_BbStatusOptCounter.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_Def.h>
#include <PM/PM_CollectorOptCounter.h>
#include <SignalProtection/SP_SwitchingStatistic.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>


//-----------------------------------------------------------------
PM_CollectorOptCounter::PM_CollectorOptCounter (PM_GenericApplication&  theGenericApplication,
                                              FC_OneShotProcess&      theProcessorProcess,
                                              uint32                  theNumberOfPort,
                                              CT_PM_Side              theSide) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_OPT_STRING, theNumberOfPort),
    myStatusOpt(NULL),
    myOptSide(theSide)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorOptCounter::~PM_CollectorOptCounter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorOptCounter::Init()
{
    myStatusOpt = &(*myGenericApplication.GetRegionStatusOptCounter());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorOptCounter::ProcessData() 
{
    SP_1plus1BaseApplication* spApp = myGenericApplication.Get1plus1SpApplication();;
    SP_SwitchingStatistic* spStatObject = (SP_SwitchingStatistic * ) 0;
    CT_IntfId portId;

    // If the module supports OPT protection, acquire the signal protection
    // switching statistics object.
    if (spApp != NULL) 
    {
        switch (myOptSide) 
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
            case CT_PM_LINE_SIDE_0:  portId = CT_LINE_SIDE_0; break;

            default: portId = CT_INTF_ID_UNKNOWN;
        }
        spStatObject = spApp->GetSwitchingStat(portId);
    }


    (*myStatusOpt)[0].Update(spStatObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
