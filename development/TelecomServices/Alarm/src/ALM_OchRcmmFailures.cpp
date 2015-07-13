/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     RCMM
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class manages failures of the OCH (Optcal Channel)
                layer on the RCMM.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OptDefects.h>

#include "../ALM_AppIf.h"
#include "../ALM_OchRcmmFailureBase.h"

#include "ALM_OchRcmmFailures.h"


/* OCH filtering table. This table contains the failure conditions
 * once they are filtered. The table entry (index) is a combination of
 * bits that represent the failure conditions. For OCH-RCMM, there is 1
 * failure, so the table contains all possible combinatons give by these 
 * failures. That means the table will have 2^1 (2) combinations. 

 * bit#:     0
 * defect: LOS-OCH
 */
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // LOS-OCH
    0x00, 0x01
};

// One bit set for each possible OCH-RCMM defect.
static const ALM_BitField ourFailureProtectionMask = 0x0001;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared: LOS.
static const ALM_BitField ourFilterAllMask = 0x0001;


//-----------------------------------------------------------------
ALM_OchRcmmFailures::ALM_OchRcmmFailures (ALM_IndexNb theIndex,
                                          ALM_AppIf& theApplication,
                                          MON_OptDefects& theMonitor,
                                          ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OchRcmmFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor),
    myLos(ALM_LOS_OCHL_SOAKING_TIME) // 90 seconds - WHAT ARE THE RCMM REQUIREMENTS?
{
    // Add all failures to LayerFailures object
    AddAt (ALM_OchRcmmFailureBase::LOS_OCH, &myLos);
}


//-----------------------------------------------------------------
ALM_OchRcmmFailures::~ALM_OchRcmmFailures()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_OchRcmmFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // For the RCMM, PM needs to know when the OCH-LOS occurs, however MON has
    // not implemented an OCH layer. Instead, they have implemented 32 different
    // OPT regions. Thus each OCH-LOS defect object shall map directly to the
    // specific OPT-LOS defect port object.
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OPT_LOSS_LIGHT_DEFECT, ALM_OchRcmmFailureBase::LOS_OCH);

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
ALM_BitField ALM_OchRcmmFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
ALM_BitField ALM_OchRcmmFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}
