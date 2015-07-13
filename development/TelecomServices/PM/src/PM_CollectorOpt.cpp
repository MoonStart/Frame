/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor 
                Optical.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OptStatus.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Monitoring/MON_AppIf.h>

#include <PM/PM_Def.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbStatusOpt.h>
#include <PM/PM_CollectorOpt.h>


//-----------------------------------------------------------------
//##ModelId=3C1F8D630291
PM_CollectorOpt::PM_CollectorOpt (PM_GenericApplication&    theGenericApplication,
                                  FC_OneShotProcess         &theProcessorProcess, 
                                  uint32                    theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_OPT_STRING, theNumberOfPort),
    myStatusOpt(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F8D63029C
PM_CollectorOpt::~PM_CollectorOpt ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F8D6302A5
void PM_CollectorOpt::Init()
{
    // Initialize pointers to optical status and defect regions.
    myStatusOpt = &(*myGenericApplication.GetRegionStatusOpt());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
//##ModelId=3C1F8D6302C4
void PM_CollectorOpt::ProcessData() 
{
	MON_AppIf* monTxApplicationPtr;
    MON_OptStatus &statusObject = (MON_OptStatus &)(*(myGenericApplication.GetMonApplication().GetStatusRegion()))[0];

	// Check to see if a MON Transmit Application exists
    if( (monTxApplicationPtr = myGenericApplication.GetMonTxApplicationPtr()) != NULL )
	{
		// Get the MON Transmit status region
		MON_TxOptStatus &txStatusObject = (MON_TxOptStatus &)(*(monTxApplicationPtr->GetStatusRegion()))[0];

		 // Update Optical gauges statuses for both TDTN and TDTC directions.
		 (*myStatusOpt)[0].Update(statusObject, txStatusObject);
	}
	else
	{
		// Update TDTC Optical gauge status.
		(*myStatusOpt)[0].Update(statusObject);
	}

    // Call base class method.
    PM_Collector::ProcessData();

}
