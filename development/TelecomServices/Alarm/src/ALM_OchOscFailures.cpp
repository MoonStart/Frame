/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class manages failures of OCH layer within the OSC.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OtsOchOHDefects.h>

#include "../ALM_AppIf.h"
#include "../ALM_OchOscFailureBase.h"

#include "ALM_OchOscFailures.h"


/* OCH filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For OCH in the OSC, there is 3
failures, so the table contained all possible combinatons give by these 
failures. That means the table will have 2^3 (8) combinations. 

bit#:        2         1          0
defect:  FDIO-OCH   FDIP-OCH    OCI-OCH
*/
static const ALM_BitField ourFilteredFailureTable[] =  // TGBLC verify filtering table
{
    // FDIP filter OCI
    0x00, 0x01, 0x02, 0x02,
    
    // FDIO filter OCI
	0x04, 0x04, 0x06, 0x06
};


static const ALM_BitField ourFailureProtectionMask = 0x0007;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
static const ALM_BitField ourFilterAllMask = 0x0000;


//-----------------------------------------------------------------

//##ModelId=3E7764FB016E
ALM_OchOscFailures::ALM_OchOscFailures (ALM_IndexNb theIndex,
                                        ALM_AppIf& theApplication,
                                        MON_OtsOchOHDefects& theMonitor,
                                        ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OchOscFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor)
{
    // Add all failures to LayerFailures object
	AddAt (ALM_OchOscFailureBase::FDIP_OCH, &myFdiP);
	AddAt (ALM_OchOscFailureBase::FDIO_OCH, &myFdiO);
    AddAt (ALM_OchOscFailureBase::OCI_OCH,  &myOci);
}


//-----------------------------------------------------------------

//##ModelId=3E7764FB0182
ALM_OchOscFailures::~ALM_OchOscFailures()
{
}

//-----------------------------------------------------------------

//##ModelId=3E7764FB0184
ALM_BitField ALM_OchOscFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

	// Read the FDI-P defect from the monitor
	ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OCH_FDIP_DEFECT, ALM_OchOscFailureBase::FDIP_OCH)
	
	// Read the FDI-P defect from the monitor
	ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OCH_FDIO_DEFECT, ALM_OchOscFailureBase::FDIO_OCH)

    // Read the LOS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OCH_OCI_DEFECT, ALM_OchOscFailureBase::OCI_OCH)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------

//##ModelId=3E7764FB0196
ALM_BitField ALM_OchOscFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------

//##ModelId=3E7764FB018D
ALM_BitField ALM_OchOscFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}
