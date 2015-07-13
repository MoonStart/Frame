/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for ODU layer
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_OduCounters.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Odu.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <EPM/PM_BbDefectOdu.h>
#include <EPM/PM_BbCountOdu.h>
#include <EPM/PM_BbStatusOdu.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_OduSubApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorOdu.h>
#include <PM/PM_RegionImp.h>
#include <SignalProtection/SP_SwitchingStatistic.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>
#include <CommonTypes/CT_OduDefinitions.h>
//#include <PM/PM_BbCfg.h>


//-----------------------------------------------------------------
PM_CollectorOdu::PM_CollectorOdu (PM_GenericApplication&  theGenericApplication,
                                  FC_OneShotProcess&      theProcessorProcess,
                                  uint32                  theNumberOfPort,
                                  CT_PM_Side              theSide) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_ODU_STRING, theNumberOfPort),
    myDefectOdu(NULL),
    myCountOdu(NULL),
    myStatusOdu(NULL),
    myOduSide(theSide)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_CollectorOdu::~PM_CollectorOdu ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_CollectorOdu::Init()
{
    // Initialize pointers to ODU status and defect regions.
    myDefectOdu = &(*myGenericApplication.GetRegionDefectOdu());
    myCountOdu = &(*myGenericApplication.GetRegionCountOdu());
    myStatusOdu = &(*myGenericApplication.GetRegionStatusOdu());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorOdu::ProcessData()
{
    uint8 anIndex;
    CT_ODU_Identifier theODUKPort;

    // Configuration reference.
    CFG_AppIf* configApp = (CFG_AppIf *)(myGenericApplication.GetCfgApplicationPtr());

    SP_1plus1BaseApplication* spApp = myGenericApplication.Get1plus1SpApplication();;
    SP_SwitchingStatistic* spStatObject = (SP_SwitchingStatistic * ) 0;
    for (anIndex = 0; anIndex < myNumberOfPort; anIndex++)
    {
        if (anIndex >= configApp->GetCfgRegion()->Size())
        {
            break;
        }
        MON_OduCounters &countersObject = (MON_OduCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[anIndex];
        MON_OduDefects &defectsObject = (MON_OduDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[anIndex];
		CFG_Odu& configRef = dynamic_cast<CFG_Odu&>((*(configApp->GetCfgRegion()))[anIndex]);
        theODUKPort = configRef.GetOduIdentifier();

        // If the module supports ODU protection, acquire the signal protection
        // switching statistics object.
        if (spApp != NULL) 
        {
            spStatObject = spApp->GetSwitchingStat(theODUKPort);
        }

        // Update error counters and defect-second counters.
        (*myDefectOdu)[anIndex].Update(defectsObject);
        (*myCountOdu)[anIndex].Update(countersObject);
        (*myStatusOdu)[anIndex].Update(spStatObject);
    }

    // Call base class method.
    PM_Collector::ProcessData();
}


