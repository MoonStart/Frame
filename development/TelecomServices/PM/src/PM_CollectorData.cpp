/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     February 10, 1999 Marc-Andre Ledoux.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Data SONET/SDH.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_RsCounters.h>
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_AppIf.h>

#include <PM/PM_BbDefectData.h>
#include <PM/PM_BbCountData.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_Def.h>
#include <PM/PM_CollectorData.h>
#include <SignalProtection/SP_SwitchingStatistic.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>

//-----------------------------------------------------------------
//##ModelId=3C1F8A5402FA
PM_CollectorData::PM_CollectorData (PM_GenericApplication&  theGenericApplication,
                                FC_OneShotProcess           &theProcessorProcess,
                                uint32                      theNumberOfPort,
                                bool                        theObtainDataFromOpticalLayer,
                                CT_PM_Side                  theSide) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_DATA_STRING, theNumberOfPort),
    myDefectData(NULL),
    myCountData(NULL),
    myObtainDataFromOpticalLayer(theObtainDataFromOpticalLayer),
    myPmSide(theSide)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F8A54030E
PM_CollectorData::~PM_CollectorData ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F8A540310
void PM_CollectorData::Init()
{
    // Initialize pointers to data status and defect regions.
    myDefectData = &(*myGenericApplication.GetRegionDefectData());
    myCountData = &(*myGenericApplication.GetRegionCountData());

    PM_Collector::Init();

}

void PM_CollectorData::ProcessData()
{   
    if (myObtainDataFromOpticalLayer) 
    {
        // For modules supporting optical protection switching,
        // selected line LOSS PM is collected. For these modules,
        // Data subapplication collects the LOSS based on selected
        // interface's LOS defect from OPT layer.

        SP_1plus1BaseApplication* spApp = myGenericApplication.Get1plus1SpApplication();;
        SP_SwitchingStatistic* spStatObject = (SP_SwitchingStatistic * ) 0;
        CT_IntfId portId;

        if (spApp != NULL) 
        {
            // Get the approriate switching stat object.
            switch (myPmSide) 
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
            
        if (spStatObject != (SP_SwitchingStatistic *) 0) 
        {
            // If the facility is part of FFP ...
            if (spStatObject->IsInvolvedInProtection()) 
            { 
                bool aProtectSelected = false;


                MON_OptDefects* defectsObjectWorking = (MON_OptDefects *) &((*(myGenericApplication.GetMonApplication(CT_PM_WORKING_FACILITY).GetDefectsRegion()))[0]);
                MON_OptDefects* defectsObjectProtect = (MON_OptDefects *) &((*(myGenericApplication.GetMonApplication(CT_PM_PROTECT_FACILITY).GetDefectsRegion()))[0]);

                if (!(spStatObject->IsCurrentlyActive()))
                {
                    // the protect facility is the selected facility
                    aProtectSelected = true;
                }
                (*myDefectData)[0].Update(defectsObjectWorking, defectsObjectProtect, aProtectSelected);
            }
        }
        else
        {
            // The facility on which LOSS being collected based on OPT loss
            // of light is not part of a signal protection scheme. 
            MON_OptDefects* defectsObject = (MON_OptDefects *) &((*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[0]);
            (*myDefectData)[0].Update(defectsObject);
        }
    }
    else
    {
        MON_RsCounters &countersObject = (MON_RsCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[0];
        MON_RsDefects &defectsObject = (MON_RsDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[0];
        // If the cards are not OPSM/OBM, the first layer is for RS and the second layer is for OPT. 
        // Just use the value of constant CT_PM_PROTECT_FACILITY here, not for protection usage.
        MON_AppIf* optMonAppPtr = NULL;
        MON_OptDefects *optDefectsObjectPtr = NULL;

        optMonAppPtr = myGenericApplication.GetMonApplicationPtr(CT_PM_PROTECT_FACILITY);
        if (optMonAppPtr) 
        {
            MON_OptDefects &optDefectsObject = (MON_OptDefects &)(*(optMonAppPtr->GetDefectsRegion()))[0];
            optDefectsObjectPtr = &optDefectsObject;
        }

        // Update Regenerator error counters, 
        // defect-second counters and failure-second counters.
        (*myDefectData)[0].Update(defectsObject, optDefectsObjectPtr);
        (*myCountData)[0].Update(countersObject);

        // Call base class method.
        PM_Collector::ProcessData();
    }

    // Call base class method.
    PM_Collector::ProcessData();
}
