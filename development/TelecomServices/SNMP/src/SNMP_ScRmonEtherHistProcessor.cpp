/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:
 TARGET   :
 AUTHOR   :
 DESCRIPTION:
--------------------------------------------------------------------------*/

#include <TimeService/FC_TimeService.h>
#include <PII_TickTimer.h>
#include <CsPii/CSPII_CardIF.h>
#include <SNMP/SNMP_ScRmonEtherHistProcessor.h>
#include <CommonTypes/CT_SNMP_Utilization.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_PMA_General.h>
#include <SNMP/SNMP_RmonEtherHistController.h>
#include <SNMP/SNMP_RmonConfigController.h>
#include <SNMP/SNMP_RmonEtherHistData.h>
#include <SNMP/SNMP_RmonEtherCount.h>
#include <SNMP/SNMP_RmonConfig.h>
#include <Configuration/CFG_Region.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_MacStatus.h>


//-----------------------------------------------------------------
SNMP_ScRmonEtherHistProcessor::SNMP_ScRmonEtherHistProcessor (SNMP_RmonEtherHistStorageRegion* theStorageRegion,
                                                              SNMP_RmonEtherHistDataRegion* theDataRegion,
                                                              SNMP_RmonEtherHistCfgRegion* theCfgRegion,
                                                              SNMP_RmonEtherCountRegion* theCountRegion,
                                                              SNMP_SysUpTimeRegion* theSysUpTimeRegion,
                                                              CFG_Region* theOptCfgRegion,
                                                              MON_AppIf& theMonApp,
                                                              CFG_AppIf& theCfgRsApp,
                                                              MON_AppIf* theMacMonApp) :
myStorageRegion(theStorageRegion),
myCfgRegion(theCfgRegion),
myCountRegion(theCountRegion),
myDataRegion(theDataRegion),
myMacMonApp(theMacMonApp),
myUtilzationMonitors(NULL)
{
    size_t loopIndex;
    myHistCtrl = new SNMP_RmonEtherHistIvalController(myStorageRegion,theSysUpTimeRegion);
    myCfgCtrl  = new SNMP_RmonEtherHistCfgCtrl(myCfgRegion, myStorageRegion, myDataRegion, theSysUpTimeRegion,
                                               theOptCfgRegion, theMonApp, theCfgRsApp, theMacMonApp);

    //Create a temporary utilization object and set the precision scale to 10000 to
    // give an accuracy to two decimal places.
    CT_SNMP_Utilization utilMonitor;
    utilMonitor.SetPrecisionScale( 10000 );

    for (loopIndex = 0; loopIndex < myStorageRegion->Size(); loopIndex++)
    {
        // Default the bit rate to GBEP. On each new etherHist entry,
        // the current facility's bit rate is set on the corresponding utilization monitor.
        myUtilzationMonitors.push_back(utilMonitor);
    }
}

//-----------------------------------------------------------------
SNMP_ScRmonEtherHistProcessor::~SNMP_ScRmonEtherHistProcessor ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScRmonEtherHistProcessor::Run (FC_Object* theObject)
{
    size_t loopIndex;
    SNMP_BbRmonEtherCount& etherCount = (*myCountRegion)[0];
    myCfgCtrl->UpdateEtherHistConfig(myUtilzationMonitors);
    myHistCtrl->UpdateSampleStart(myUtilzationMonitors);
    for (loopIndex = 0; loopIndex < myStorageRegion->Size(); loopIndex++)
    {
        SNMP_BbRmonEtherHistStorage& histStorage = (*myStorageRegion)[loopIndex];
        if (histStorage.IsCollectionEnabled())
        {
            SNMP_RmonEtherHistSample& currSample = histStorage.GetCurrentSample();
            currSample.IncDropEvents(etherCount.GetDropEvents());
            currSample.IncOctets(etherCount.GetOctets());
            currSample.IncPkts(etherCount.GetPkts());
            currSample.IncBroadcastPkts(etherCount.GetBroadcastPkts());
            currSample.IncMulticastPkts(etherCount.GetMulticastPkts());
            currSample.IncCRCAlignErrors(etherCount.GetCRCAlignErrors());
            currSample.IncUndersizePkts(etherCount.GetUndersizePkts());
            currSample.IncOversizePkts(etherCount.GetOversizePkts());
            currSample.IncFragments(etherCount.GetFragments());
            currSample.IncJabbers(etherCount.GetJabbers());
            currSample.IncCollisions(etherCount.GetCollisions());
            CT_SNMP_Integer32 util = 0;
            CT_PM_64bit_ull packets64bit = 0;
            CT_PM_64bit_ull octets64bit = 0;
            packets64bit = ( etherCount.GetHighPkts() * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + etherCount.GetPkts();
            octets64bit  = ( etherCount.GetHighOctets()  * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + etherCount.GetOctets();

            bool aRateChange = false;
            // If we have a Mac Layer Bit Rate could change. i.e. AutoNeg Enabled, Link Goes Down and comes back
            // at a different rate.
            if (myMacMonApp)
            {

                MON_MacStatus&  aMonMacStatus = static_cast<MON_MacStatus&> ((*myMacMonApp->GetStatusRegion())[0]);
                CT_TEL_daHz bitrate = aMonMacStatus.GetOperRate();
                // Rate has changed.
                if (myCfgCtrl->GetUtilBitRate() != bitrate)
                {
                    myUtilzationMonitors[loopIndex].SetBitRate(bitrate);
                    myCfgCtrl->SetUtilBitRate(bitrate);
                    aRateChange = true;
                }

            }
            if (!aRateChange)
                util = static_cast<CT_SNMP_Integer32> (myUtilzationMonitors[loopIndex].UpdateWithDeltaCounts(packets64bit, octets64bit));
                currSample.SetUtilization(util);
        }
    }
}
