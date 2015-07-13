/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OMS (Optical Multiplex
                Section) layer.
--------------------------------------------------------------------------*/

#include <AppFramework/FC_Context.h>
#include <T6100_CardIf.h>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_ITS_Definitions.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_OmsDefects.h>
#include <ITS/ITS_AppIfBase.h>

#include "../ALM_AppIf.h"
#include <Alarm/ALM_SubApplicationOnCard.h>
#include "../ALM_FailureRegionImp.h"
#include "../ALM_OmsFailureBase.h"
#include "../ALM_OscFailureBase.h"
#include "../ALM_FailureBase.h"

#include "ALM_OmsFailures.h"


/* OMS filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For OMS, there are 4
failures, so the table contains all possible combinatons give by these 
failures. That means the table will have 2^4 (16) combinations. 

bit#:     3       2      1       0
defect: AOPE   OPOVLD LOS-OMS LOSINT-OMS
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // LOSINT-OMS filters nothing at this level. It filters all downstream alarm at AM level.
    0x00, 0x01, 0x02, 0x03,

    // OPOVLD filter nothing
    0x04, 0x05, 0x06, 0x07,

    // AOPE filter nothing
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};


static const ALM_BitField ourFailureProtectionMask = 0x000f;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared: LOS_OMS 
static const ALM_BitField ourFilterAllMask = 0x0002;


//-----------------------------------------------------------------
//##ModelId=3E7764F90270
ALM_OmsFailures::ALM_OmsFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OmsDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OmsFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor),
    
    //Use 30 second as soaking time / 30 second recovery
    myAopeOms(ALM_AOPE_OMS_SOAKING_TIME,     ALM_AOPE_OMS_RECOVERY_TIME),  // (30s, 30s)

    //Use 30 second as soaking time / 30 second recovery
    myOpovldOms(ALM_OPOVLD_OMS_SOAKING_TIME, ALM_OPOVLD_OMS_RECOVERY_TIME),// (30s, 30s)

    //Use 0 second as soaking time
    myLosIntOms(0)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_OmsFailureBase::AOPE_OMS, &myAopeOms);
    AddAt (ALM_OmsFailureBase::OPOVLD_OMS, &myOpovldOms);
    AddAt (ALM_OmsFailureBase::LOS_OMS, &myLosOms);
    AddAt (ALM_OmsFailureBase::LOSINT_OMS, &myLosIntOms);
}


//-----------------------------------------------------------------
//##ModelId=3E7764F90284
ALM_OmsFailures::~ALM_OmsFailures()
{
}

//-----------------------------------------------------------------
//##ModelId=3E7764F9028D
ALM_BitField ALM_OmsFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the AOPE OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_AOPE_DEFECT, ALM_OmsFailureBase::AOPE_OMS)

    // Read the LOS OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_OPOVLD_DEFECT, ALM_OmsFailureBase::OPOVLD_OMS)

    // Read the LOS OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_LOS_DEFECT, ALM_OmsFailureBase::LOS_OMS)

    // Read the LOS Internal OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_LOS_AFTER_AMPLI_DEFECT, ALM_OmsFailureBase::LOSINT_OMS)
    

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
//##ModelId=3E7764F90298
ALM_BitField ALM_OmsFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
//##ModelId=3E7764F9028F
ALM_BitField ALM_OmsFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}
