/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     
 AUTHOR   :     xinlun fang
 DESCRIPTION:   This class manages the failures of Gcc Link layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>

#include <Monitoring/MON_GccDefects.h>

#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>

#include <Alarm/ALM_RegionKeyDefinition.h>
#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_GccFailureBase.h"
#include "../ALM_FailureRegionImp.h"

#include "ALM_GccFailures.h"
#include "ALM_LayerFailures.h"

/*
bit#:     3        2         1              0
defect: UP_SA   UP_NSA  LINK_INCOMPLETE LINK_DOWN 
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // Bit 0.
    0x00, 0x01,
    // Bit 1.
    0x02, 0x02,
    // Bit 2.
    0x04, 0x05, 0x06, 0x06,
    // Bit 3.
    0x08, 0x09, 0x0a, 0x0a, 0x0c, 0x0d, 0x0e, 0x0e
};

static const ALM_BitField ourFailureProtectionMask = 0x00f;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures & defect of lower layer if one of the following 
// failure or defect is declared: NONE
static const ALM_BitField ourFilterAllMask = 0x0000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x00c;

//-----------------------------------------------------------------
ALM_GCCFailures::ALM_GCCFailures (ALM_IndexNb theIndex,
                                    ALM_AppIf& theApplication,
                                    MON_GccDefects& theMonitor,
                                    ALM_LayerFailures* theHigherLayerPtr):

    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_GCCFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),

    //Set the monitor
    myMonitor(theMonitor)
    
{
    // Add all failures to LayerFailures object
    AddAt (ALM_GCCFailureBase::UPPER_SA_GCC,     &myUpperSa);
    AddAt (ALM_GCCFailureBase::UPPER_NSA_GCC,    &myUpperNsa);
    AddAt (ALM_GCCFailureBase::GCC_LINK_INCMPLT, &myGCCLinkIncmplt);
    AddAt (ALM_GCCFailureBase::GCC_LINK_DOWN,    &myGCCLinkDown);

    // default the signal type to unknown
    mySignalType = (int)CT_TEL_SIGNAL_UNKNOWN;

    myCardIf = NULL;
    if (theApplication.GetContext().GetParent())
    {
        myCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
    }
}

//-----------------------------------------------------------------
ALM_GCCFailures::~ALM_GCCFailures ()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_GCCFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;
/*
    // Read the UPPER_SA_OPT defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GCC_UPPER_LAYER_FAIL_TA_DEFECT, ALM_GCCFailureBase::UPPER_SA_GCC)

    // Read the UPPER_NSA_OPT defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GCC_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_GCCFailureBase::UPPER_NSA_GCC)
*/

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GCC_LINK_INCOMPLETE_DEFECT, ALM_GCCFailureBase::GCC_LINK_INCMPLT)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GCC_LINK_DOWN_DEFECT,       ALM_GCCFailureBase::GCC_LINK_DOWN)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
ALM_BitField ALM_GCCFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
ALM_BitField ALM_GCCFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_GCCFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

void ALM_GCCFailures::ProcessAfterSoaking()
{
    if ( (myCardIf) && (myCardIf->GetCardFamily() == SSM40_FAM)
       )
    {
        // set the GCCID, get it from MON
        //(static_cast<ALM_GCCFailureBase*>(&itsFilteredFailureBase))->SetValue(aCfgObject.GetGccIdentifier().GetIdValue());
    }
}


