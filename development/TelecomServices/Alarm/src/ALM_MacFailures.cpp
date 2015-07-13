/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM
 DESCRIPTION:   This class manages the failures of MAC layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_MacDefects.h>

#include "../ALM_AppIf.h"
#include "../ALM_MacFailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include <T6100/T6100_CardIf.h>
#include <T6100/T6100_TelecomIf.h>
#include <Alarm/ALM_SubApplicationOnRpt.h>
#include <Alarm/ALM_SubApplicationOnCard.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_Rs.h>

#include "ALM_MacFailures.h"

/* MAC filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For MAC, there are 3
failures, so the table contained all possible combinatons give by these 
failures. That means the table will have 2^3 (8) combinations. 

bit#:     3       2     1       0
defect: UP_SA UP_NSA LACPFAIL RFLINK
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,

    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

static const ALM_BitField ourFailureProtectionMask = 0x000F;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared: LACPFAIL
static const ALM_BitField ourFilterAllMask = 0x0002;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA, UP_NSA, RFLINK
static const ALM_BitField ourNoFilterMask = 0x000D;

//-----------------------------------------------------------------
ALM_MacFailures::ALM_MacFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_MacDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_MacFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr,
        ALM_LayerFailures::ALM_SP_NB_OF_SOAK_DEFECT
    ),
    //Set the monitor
    myMonitor(theMonitor),

    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_MAC_SOAKING_TIME),

    //-------------------------------------------
    // Signal Protection Not Service Affecting
    // must report NSA flag after 10 second soak
    // and clear   NSA flag after 2  second soak.
    // NOTE: this is the opposite of reporting/clearing
    //       defects, because SP-NSA is REPORTED
    //       when defects are CLEARED!
    //-------------------------------------------
    mySigProtNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_MacFailureBase::UPPER_SA_MAC,  &myUpperSa);
    AddAt (ALM_MacFailureBase::UPPER_NSA_MAC, &myUpperNsa);
    AddAt (ALM_MacFailureBase::LACPFAIL_MAC,  &myLacpFail);
    AddAt (ALM_MacFailureBase::RFLINKFAIL_MAC,&myRflinkFail);

    // Add all SP Soak failures to LayerFailures object
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_NOT_SA, &mySigProtNSA);

    myCardIf = NULL;
    if (theApplication.GetContext().GetParent())
    {
        T6100_CardIf* theCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
        if (theCardIf)
        {
            myCardIf = theCardIf;
        }
    }
}

//-----------------------------------------------------------------
ALM_MacFailures::~ALM_MacFailures ()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_MacFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_ defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MAC_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, ALM_MacFailureBase::UPPER_SA_MAC)

    // Read the UPPER_NSA defect from the monitor
    // ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MAC_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_MacFailureBase::UPPER_NSA_MAC)

    // Read the LACPFAIL defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_LACPFAIL_DEFECT, ALM_MacFailureBase::LACPFAIL_MAC)

    //====================================================================
    // Read the RFLINKFAIL_MAC defect from the monitor.
    // NOTE: MON_DEFECTS has extra attr FEFI state and 
    //       equates to RFLINKFAIL_MAC failure in Signal Alarm!
    //====================================================================
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MAC_RFLINKFAIL_DEFECT, ALM_MacFailureBase::RFLINKFAIL_MAC)
    if ( !(aBitFieldDefect & (1 << ALM_MacFailureBase::RFLINKFAIL_MAC)) )
    {
        ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MAC_FEFI_DEFECT, ALM_MacFailureBase::RFLINKFAIL_MAC)
    }

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
ALM_BitField ALM_MacFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
ALM_BitField ALM_MacFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_MacFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//-----------------------------------------------------------------
void ALM_MacFailures::ProcessAfterSoaking()
{
}

