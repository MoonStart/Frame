/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 2004 Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for Near-End SONET/SDH MS layer
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_HopCounters.h>
#include <Monitoring/MON_HopDefects.h>
#include <Alarm/ALM_HopFailureBase.h>
#include <Monitoring/MON_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Hop.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM/PM_BbDefectHopNearEnd.h>
#include <PM/PM_BbCountHopNearEnd.h>
#include <PM/PM_BbFailureHopNearEnd.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_HopNearEndSubApplication.h>
#include <PM/PM_Def.h>
#include <PM/PM_CollectorHopNearEnd.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbCfg.h>


//-----------------------------------------------------------------
PM_CollectorHopNearEnd::PM_CollectorHopNearEnd (PM_GenericApplication&  theGenericApplication,
                                                FC_OneShotProcess&      theProcessorProcess,
                                                uint32                  theNumberOfPort,
                                                CT_PM_Sts_Offset                theSts1Offset) :
PM_Collector(theGenericApplication, theProcessorProcess, PM_HOP_NE_STRING, theNumberOfPort),
myDefectHopNearEnd(NULL),
myCountHopNearEnd(NULL),
myFailureHopNearEnd(NULL),
myConfigUpdateAction(),
mySts1Offset(theSts1Offset)
{
    // Note: This registration is done for each STS-1 in the region. So
    // there will be more than one action on the same region.
    myGenericApplication.GetDayRegionConfig()->AddObserver(&myConfigUpdateAction);
}

//-----------------------------------------------------------------
PM_CollectorHopNearEnd::~PM_CollectorHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorHopNearEnd::Init()
{
    // Initialize pointers to HopNearEnd status and defect regions.
    myDefectHopNearEnd = &(*myGenericApplication.GetRegionDefectHopNearEnd());
    myFailureHopNearEnd = &(*myGenericApplication.GetRegionFailureHopNearEnd());
    myCountHopNearEnd = &(*myGenericApplication.GetRegionCountHopNearEnd());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorHopNearEnd::ProcessData()
{
    uint8 anIndex;

    // Update the selected STS-1 for pointer justification data collection.
    UpdateSelectedSts1();

    for (anIndex = 0; anIndex < myNumberOfPort; anIndex++)
    {
        MON_HopCounters &countersObject = (MON_HopCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[mySts1Offset + anIndex];
        MON_HopDefects &defectsObject = (MON_HopDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[mySts1Offset + anIndex];
        ALM_FailureBase &failureObject = (ALM_FailureBase &)(*(myGenericApplication.GetAlmHopApplication().GetFilteredRegionPtr()))[anIndex];

        // Update Regenerator error counters,
        // defect-second counters and failure-second counters.
        (*myDefectHopNearEnd)[anIndex].Update(defectsObject);
        (*myCountHopNearEnd)[anIndex].Update(countersObject);
        (*myFailureHopNearEnd)[anIndex].Update(failureObject);
    }

    // Call base class method.
    PM_Collector::ProcessData();
}

void PM_CollectorHopNearEnd::UpdateSelectedSts1()
{
    uint8 index;
    PM_HopNearEndSubApplication &hopApp = dynamic_cast<PM_HopNearEndSubApplication&>(myGenericApplication);

    // Check to see if this is a line side facility
    if ( hopApp.GetSide() == CT_PM_LINE_SIDE_0 )
    {
        // This is a line side facility.

        // Check for changes in the facility PM configuration.
        if ( GetConfigVerifyRequest() )
        {
            // The 1 day configuration is used to drive the selection.
            PM_RegionImp<PM_BbCfg> *cfgRegion = myGenericApplication.GetDayRegionConfig();

            // Now determine the lowest numbered STS-1 that is enabled.
            for ( index = 0; index < myNumberOfPort; index++ )
            {
                if ( !(*cfgRegion)[index].GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) )
                {
                    // Found the lowest numbered STS-1 that is enabled.
                    break;
                }
            }

            // Check to see if this STS-1 number has changed.
            // If no STS-1s are enabled for PM data collection,
            // the index will be set to 1 past the valid range
            // of STS-1 offsets.
            if ( index != hopApp.GetSelectedSts1() )
            {
                // The STS-1 has changed.
                hopApp.SetSts1ConfigChanged( true );
                hopApp.SetSelectedSts1( index );

                // Now refresh the STS-1 Pointer Justification data collection
                // selection based in the selected STS-1.
                for ( index = 0; index < myNumberOfPort; index++ )
                {
                    if ( index == hopApp.GetSelectedSts1() )
                    {
                        CFG_Hop& cfgHopObj = (CFG_Hop&)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[mySts1Offset + index];
                        cfgHopObj.SetPointerJustEnabled( true );
                    }
                    else
                    {
                        CFG_Hop& cfgHopObj = (CFG_Hop&)(*(myGenericApplication.GetCfgApplication().GetCfgRegion()))[mySts1Offset + index];
                        cfgHopObj.SetPointerJustEnabled( false );
                    }
                }
            }

            SetConfigVerifyRequest( false );
        }
    }
}

