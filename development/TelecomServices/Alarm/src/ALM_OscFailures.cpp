/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OSC (Optical Supervisory
                Channel) layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OtsOHDefects.h>

#include "../ALM_AppIf.h"
#include "../ALM_OscFailureBase.h"

#include "ALM_OscFailures.h"


/* OSC filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For OSC, there is 10
failures, so the table contained all possible combinatons give by these 
failures. That means the table will have 2^10 (1024) combinations. 

bit#:      7       6        5        4        3        2        1        0        x       x
defect: TIM-OTS PMI-OTS  BDI-OTS  BDIO-OTS BDIP-OTS FDIO-OMS FDIP-OMS PMI-OMS BDIO-OMS BDIP-OMS 
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
	// PMI-OMS filter nothing here
    0x00, 0x01, 
        
    // FDIP-OMS  filter PMI-OMS
    0x02, 0x02, 
        
    // FDIO-OMS  filter nothing here (FDIP-OMS filter PMI-OMS)
    0x04, 0x05, 0x06, 0x06, 
        
    // BDIP-OTS filter nothing (FDIP-OMS filter PMI-OMS)
    0x08, 0x09, 0x0a, 0x0a, 0x0c, 0x0d, 0x0e, 0x0e,
	
    // BDIO-OTS filter nothing (FDIP-OMS filter PMI-OMS)  
    0x10, 0x11, 0x12, 0x12, 0x14, 0x15, 0x16, 0x16, 0x18, 0x19, 0x1a, 0x1a, 0x1c, 0x1d, 0x1e, 0x1e,
	
    // BDI-OTS filter BDIO-OTS and BDIP-OTS (FDIP-OMS filter PMI-OMS) 
    0x20, 0x21, 0x22, 0x22, 0x24, 0x25, 0x26, 0x26, 0x20, 0x21, 0x22, 0x22, 0x24, 0x25, 0x26, 0x26,
    0x20, 0x21, 0x22, 0x22, 0x24, 0x25, 0x26, 0x26, 0x20, 0x21, 0x22, 0x22, 0x24, 0x25, 0x26, 0x26,
    
    // PMI-OTS filter PMI-OMS (BDI filter BDIP and BDIO)
    0x40, 0x40, 0x42, 0x42, 0x44, 0x44, 0x46, 0x46, 0x48, 0x48, 0x4a, 0x4a, 0x4c, 0x4c, 0x4e, 0x4e,
    0x50, 0x50, 0x52, 0x52, 0x54, 0x54, 0x56, 0x56, 0x58, 0x58, 0x5a, 0x5a, 0x5c, 0x5c, 0x5e, 0x5e,
    0x60, 0x60, 0x62, 0x62, 0x64, 0x64, 0x66, 0x66, 0x60, 0x60, 0x62, 0x62, 0x64, 0x64, 0x66, 0x66,
    0x60, 0x60, 0x62, 0x62, 0x64, 0x64, 0x66, 0x66, 0x60, 0x60, 0x62, 0x62, 0x64, 0x64, 0x66, 0x66,

	// TIM-OTS filter PMI-OTS,BDI-OTS,BDIO-OTS,BDIP-OTS,FDIO-OMS,FDIP-OMS,PMI-OMS
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
};


static const ALM_BitField ourFailureProtectionMask = 0x00ff;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer (OCH OSC) if one of the folowing failure
// is declared: TIM-OTS, PMI-OTS, FDIP-OMS
static const ALM_BitField ourFilterAllMask = 0x00C2; 


//-----------------------------------------------------------------
//##ModelId=3C506C310060
ALM_OscFailures::ALM_OscFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OtsOHDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OscFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_OscFailureBase::TIM_OTS,  &myTimOts);
    AddAt (ALM_OscFailureBase::PMI_OTS,  &myPmiOts);
    AddAt (ALM_OscFailureBase::BDI_OTS,  &myBdiOts);
    AddAt (ALM_OscFailureBase::BDIO_OTS, &myBdioOts);
    AddAt (ALM_OscFailureBase::BDIP_OTS, &myBdipOts);
  //AddAt (ALM_OscFailureBase::BDIO_OMS, &myBdioOms);
  //AddAt (ALM_OscFailureBase::BDIP_OMS, &myBdipOms);
    AddAt (ALM_OscFailureBase::FDIO_OMS, &myFdioOms);
    AddAt (ALM_OscFailureBase::FDIP_OMS, &myFdipOms);
    AddAt (ALM_OscFailureBase::PMI_OMS,  &myPmiOms);
}


//-----------------------------------------------------------------
//##ModelId=3C506C310073
ALM_OscFailures::~ALM_OscFailures()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C310075
ALM_BitField ALM_OscFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the TIM-OTS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTS_TIM_DEFECT, ALM_OscFailureBase::TIM_OTS)

    // Read the PMI-OTS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTS_PMI_DEFECT, ALM_OscFailureBase::PMI_OTS)

    // Read the BDI-OTS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTS_BDI_DEFECT, ALM_OscFailureBase::BDI_OTS)

    // Read the BDIO-OTS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTS_BDIO_DEFECT, ALM_OscFailureBase::BDIO_OTS)

    // Read the BDIP-OTS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTS_BDIP_DEFECT, ALM_OscFailureBase::BDIP_OTS)

    // Read the FDIO-OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_FDIO_DEFECT, ALM_OscFailureBase::FDIO_OMS)

    // Read the FDIP-OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_FDIP_DEFECT, ALM_OscFailureBase::FDIP_OMS)

    // Read the PMI-OMS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_PMI_DEFECT, ALM_OscFailureBase::PMI_OMS)

    // Read the BDIO-OMS defect from the monitor
    //ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_BDIO_DEFECT, ALM_OscFailureBase::BDIO_OMS)

    // Read the BDIP-OMS defect from the monitor
    //ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OMS_BDIP_DEFECT, ALM_OscFailureBase::BDIP_OMS)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
//##ModelId=3C506C31007F
ALM_BitField ALM_OscFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
//##ModelId=3C506C31007D
ALM_BitField ALM_OscFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}
