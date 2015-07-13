/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages failures of OCH (Optcal Channel) layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OchDefects.h>

#include "../ALM_AppIf.h"
#include "../ALM_OchFailureBase.h"

#include "ALM_OchFailures.h"


/* OCH filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For OCH, there are 2
failures, so the table contains all possible combinatons give by these 
failures. That means the table will have 2^2 (4) combinations. 

bit#:     1           0
defect: LOS-OCH     DTD-OCH
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // LOS-OCH filter DTD-OCH
    0x00, 0x01, 0x02, 0x02
};

// One bit set for each possible OCH defect.
static const ALM_BitField ourFailureProtectionMask = 0x0003;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared: LOS.
static const ALM_BitField ourFilterAllMask = 0x0002;


//-----------------------------------------------------------------
//##ModelId=3C506C320006
ALM_OchFailures::ALM_OchFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OchDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OchFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor),
    myLos(ALM_LOS_OCHL_SOAKING_TIME), // 90 seconds
    myDtd(0)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_OchFailureBase::LOS_OCH, &myLos);
	AddAt (ALM_OchFailureBase::DTD_OCH, &myDtd);
}


//-----------------------------------------------------------------
//##ModelId=3C506C320011
ALM_OchFailures::~ALM_OchFailures()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C320013
ALM_BitField ALM_OchFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the LOS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OCH_LOSS_PTONE_DEFECT, ALM_OchFailureBase::LOS_OCH)

	// Read the DTD defect from the monitor
	ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OCH_DEBUG_TRACE_DETECTED_DEFECT, ALM_OchFailureBase::DTD_OCH)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
//##ModelId=3C506C320024
ALM_BitField ALM_OchFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
//##ModelId=3C506C32001B
ALM_BitField ALM_OchFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}
