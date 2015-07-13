/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     Controller (SPM)
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class manages the failures of RTR layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>

#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>

#include <Alarm/ALM_RegionKeyDefinition.h>
#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_RtrFailureBase.h"
#include "../ALM_FailureRegionImp.h"

#include "ALM_RtrFailures.h"
#include "ALM_LayerFailures.h"

/*
bit#:      0
defect: RTR_DOWN
*/
static const ALM_BitField ourFilteredFailureTable[] =
{
    // Bit 0
    0x00, 0x01
};

static const ALM_BitField ourFailureProtectionMask = 0x001;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures & defect of lower layer if one of the following
// failure or defect is declared: NONE
static const ALM_BitField ourFilterAllMask = 0x000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in
// failure or defect: NONE
static const ALM_BitField ourNoFilterMask = 0x000;

//-----------------------------------------------------------------
ALM_RtrFailures::ALM_RtrFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  //MON_OptDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):

    // Calls base class constructor
    ALM_LayerFailures
    (
        ALM_RtrFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    )

    //Set the monitor
    //myMonitor(theMonitor)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_RtrFailureBase::RTR_DOWN, &myRtrDown);
}

//-----------------------------------------------------------------
ALM_RtrFailures::~ALM_RtrFailures ()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_RtrFailures::ReadDefects() const
{

    ALM_BitField aBitFieldDefect = 0;
/*
    // Read the defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RTR_xxx_DEFECT, ALM_RtrFailureBase::RTR_DOWN)
*/
    return aBitFieldDefect;
}

//-----------------------------------------------------------------
ALM_BitField ALM_RtrFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
ALM_BitField ALM_RtrFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_RtrFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}
