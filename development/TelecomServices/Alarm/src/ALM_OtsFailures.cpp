/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OTS (Optical Transport
                Section) layer.
--------------------------------------------------------------------------*/

#include <AppFramework/FC_Context.h>
#include <T6100_CardIf.h>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_ITS_Definitions.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_OtsDefects.h>
#include <ITS/ITS_AppIfFailure.h>

#include "../ALM_AppIf.h"
#include <Alarm/ALM_SubApplicationOnCard.h>
#include "../ALM_FailureRegionImp.h"
#include "../ALM_OtsFailureBase.h"
#include "../ALM_OscFailureBase.h"
#include "../ALM_FailureBase.h"

#include "ALM_OtsFailures.h"


/* OTS filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For OTS, there is 1
failure, so the table contains all possible combinatons give by these 
failures. That means the table will have 2^1 (2) combinations. 

bit#:     0       
defect: LOS-OTS 
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // LOS-OTS nothing else to filters at this level.
    0x00, 0x01
};


static const ALM_BitField ourFailureProtectionMask = 0x0001;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared: LOS_OTS, LOS_OMS and LOSINT_OMS
static const ALM_BitField ourFilterAllMask = 0x0001;


//-----------------------------------------------------------------
//##ModelId=3F954C2B0225
ALM_OtsFailures::ALM_OtsFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OtsDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OtsFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor)   
{
    // Add all failures to LayerFailures object
    AddAt (ALM_OtsFailureBase::LOS_OTS, &myLosOts);
}


//-----------------------------------------------------------------
//##ModelId=3C506C300375
ALM_OtsFailures::~ALM_OtsFailures()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C300377
ALM_BitField ALM_OtsFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the LOS OTS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTS_LOS_DEFECT, ALM_OtsFailureBase::LOS_OTS)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
//##ModelId=3C506C300381
ALM_BitField ALM_OtsFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
//##ModelId=3C506C30037F
ALM_BitField ALM_OtsFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}
