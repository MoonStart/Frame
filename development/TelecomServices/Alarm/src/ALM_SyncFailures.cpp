/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHORS  :     Luc Charbonneau, Patrick Meehan
 DESCRIPTION:   This class manages the failures of Sync
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_SyncDefects.h>

#include <ErrorService/FC_Error.h>
#include <AM/AM_DefectCollector.h>
#include <Alarm/ALM_RegionKeyDefinition.h>
#include <T6100_CardIf.h>
#include <CsPii/CSPII_CardIF.h>
#include "../ALM_AppIf.h"
#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_SyncFailureBase.h"

#include "ALM_SyncFailures.h"


/* SYNC layer filtering table. This table contains the 
failure conditions once they are filtered. The table entry (index)
is a combination of bits that represent the failure conditions.
For the SYNC layer, there are 2 failures, so the table contains
all possible combinatons give by these failures. That means the
table have 2^2 (4) combinations.

bit#:    1          0
defect: FREERUN   HOLDOVER
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // FREERUN filters HOLDOVER.
    0x00, 0x01, 0x02, 0x02    
};

static const ALM_BitField ourFailureProtectionMask = 0x0003;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of lower layer if one of the folowing failure
// or defect is declared: None
static const ALM_BitField ourFilterAllMask = 0x0000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x0000;

//-----------------------------------------------------------------

ALM_SyncFailures::ALM_SyncFailures (ALM_IndexNb theIndex,
                                ALM_AppIf& theApplication,
                                MON_SyncDefects& theMonitor,
                                ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_SyncFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor) 
{
    //-------------------------------------------------------------
    // SMTMU should SOAK alarms for 30 seconds when setting!
    //-------------------------------------------------------------
    if ( CSPII_CardIF::GetInstance()->GetCardFamily() == SMTM_FAM ) 
    {
        myFreeRun.SetSoakingRecoveryTime (ALM_SYNC_SOAKING_TIME, ALM_DEFAULT_RECOVERY_TIME);
        myHoldover.SetSoakingRecoveryTime(ALM_SYNC_SOAKING_TIME, ALM_DEFAULT_RECOVERY_TIME);
    }

    // Add all failures to LayerFailures object
    AddAt (ALM_SyncFailureBase::FREERUN_SYNC,    &myFreeRun);
    AddAt (ALM_SyncFailureBase::HOLDOVER_SYNC,   &myHoldover);
}

//-----------------------------------------------------------------

ALM_SyncFailures::~ALM_SyncFailures ()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_SyncFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Get the current free run state from the monitor, save in
	// the objects itsStatus[] array.
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_SYNC_FREERUN_DEFECT, ALM_SyncFailureBase::FREERUN_SYNC)

    // Get the current holdover state from the monitor, save in
	// the objects itsStatus[] array.
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_SYNC_HOLDOVER_DEFECT, ALM_SyncFailureBase::HOLDOVER_SYNC)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------

ALM_BitField ALM_SyncFailures::Filter(ALM_BitField theFailure) const
{
    //Filter raw failure according to the table
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------

ALM_BitField ALM_SyncFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer.
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_SyncFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}


