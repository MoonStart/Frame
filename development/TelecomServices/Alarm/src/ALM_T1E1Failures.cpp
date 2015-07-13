/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class manages the failures of the T1E1 (bits clock).
--------------------------------------------------------------------------*/
#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_T1E1Defects.h>

#include "../ALM_AppIf.h"
#include <Alarm/ALM_SubApplicationOnCard.h>
#include "../ALM_T1E1FailureBase.h"

#include "ALM_T1E1Failures.h"

#include "AM/AM_Definitions.h"
#include "AM/AM_6100Registry.h"
#include <T6100_CardIf.h>
#include <AM/AM_DefectCollector.h>

// As stated in SRS 7100000250, section 5.5.2 and 5.5.3, page 40
const FC_Milliseconds ALM_T1E1_SOAKING_TIME (1000  - ALM_ADJUSTMENT_FACTOR);
const FC_Milliseconds ALM_T1E1_RECOVERY_TIME (20000  - ALM_ADJUSTMENT_FACTOR);

/* T1E1 filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For T1E1, there are 4
failures, so the table contained all possible combinations give by these 
failures. That means the table will have 2^4 (16) combinations. 

bit#:    3        2      1          0
defect: LOS     AIS    LOF      FREQ_OFF
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    0x00, 0x01, 
    0x02, 0x02,
    0x04, 0x04, 0x04, 0x04,
    0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08
};

// One bit set for each possible T1E1 defect.
static const ALM_BitField ourFailureProtectionMask = 0x000F;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures & defect of lower layer if one of the following 
// failure or defect is declared: NONE
static const ALM_BitField ourFilterAllMask = 0x0000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: NONE
static const ALM_BitField ourNoFilterMask = 0x0000;

//-----------------------------------------------------------------
ALM_T1E1Failures::ALM_T1E1Failures (ALM_IndexNb theIndex,
                                    ALM_AppIf& theApplication,
                                    MON_T1E1Defects& theMonitor,
                                    ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_T1E1FailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor),
    myLos(ALM_T1E1_SOAKING_TIME, ALM_T1E1_RECOVERY_TIME),
    myAis(ALM_T1E1_SOAKING_TIME, ALM_T1E1_RECOVERY_TIME),
    myLof(ALM_T1E1_SOAKING_TIME, ALM_T1E1_RECOVERY_TIME),
    myFreqOff(ALM_T1E1_SOAKING_TIME, ALM_T1E1_RECOVERY_TIME)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_T1E1FailureBase::LOS_T1E1, &myLos);
    AddAt (ALM_T1E1FailureBase::AIS_T1E1, &myAis);
    AddAt (ALM_T1E1FailureBase::LOF_T1E1, &myLof);
    AddAt (ALM_T1E1FailureBase::FREQOFF_T1E1, &myFreqOff);

    myLOSLedStatus = false;
    myAISLedStatus = false;
    myLOFLedStatus = false;

    myCardIf = NULL;
}

//-----------------------------------------------------------------
ALM_T1E1Failures::~ALM_T1E1Failures ()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_T1E1Failures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the LOS_T1E1 defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_T1E1_LOS_DEFECT, ALM_T1E1FailureBase::LOS_T1E1)

    // Read the AIS_T1E1 defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_T1E1_AIS_DEFECT, ALM_T1E1FailureBase::AIS_T1E1)

    // Read the LOF_T1E1 defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_T1E1_LOF_DEFECT, ALM_T1E1FailureBase::LOF_T1E1)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_T1E1_OFF_FREQ_DEFECT, ALM_T1E1FailureBase::FREQOFF_T1E1)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
ALM_BitField ALM_T1E1Failures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
ALM_BitField ALM_T1E1Failures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_T1E1Failures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//##ModelId=3DBFFADB03D0
void ALM_T1E1Failures::ProcessAfterSoaking()
{
    bool aLedStatus;

    //Use the AIS defect to drive LED
    aLedStatus = myAISLed.DefectUpdated(itsDefect[ALM_T1E1FailureBase::AIS_T1E1].GetStatus(),
                                     itsDefect[ALM_T1E1FailureBase::AIS_T1E1].GetTCount());
    if (myAISLedStatus != aLedStatus)
    {
        myAISLedStatus = aLedStatus;
        if (myCardIf)
        {
            if (myAISLedStatus)
            {
                AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_DS1_AIS_NSA_UID, myCardIf, 0);
            }
            else 
            {
                AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LED_DS1_AIS_NSA_UID, myCardIf);
            }
        }
        else
        {
            //FC_THROW_ERROR(FC_SWError, "Cannot drive DS1 AIS LED on TRN");
        }
    }

    //Use the LOS defect to drive LED
    aLedStatus = myLOSLed.DefectUpdated(itsDefect[ALM_T1E1FailureBase::LOS_T1E1].GetStatus(),
                                     itsDefect[ALM_T1E1FailureBase::LOS_T1E1].GetTCount());
    if (myLOSLedStatus != aLedStatus)
    {
        myLOSLedStatus = aLedStatus;
        if (myCardIf)
        {
            if (myLOSLedStatus)
            {
                AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_DS1_LOS_UID, myCardIf, 0);
            }
            else 
            {
                AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LED_DS1_LOS_UID, myCardIf);
            }
        }
        else
        {
            //FC_THROW_ERROR(FC_SWError, "Cannot drive DS1 LOS LED on TRN");
        }
    }

   //Use the LOF defect to drive LED
    aLedStatus = myLOFLed.DefectUpdated(itsDefect[ALM_T1E1FailureBase::LOF_T1E1].GetStatus(),
                                     itsDefect[ALM_T1E1FailureBase::LOF_T1E1].GetTCount());
    if (myLOFLedStatus != aLedStatus)
    {
        myLOFLedStatus = aLedStatus;
        if (myCardIf)
        {
            if (myLOFLedStatus)
            {
                AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_DS1_LOF_UID, myCardIf, 0);
            }
            else 
            {
                AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LED_DS1_LOF_UID, myCardIf);
            }
        }
        else
        {
            //FC_THROW_ERROR(FC_SWError, "Cannot drive DS1 LOF LED on TRN");
        }
    }
}
