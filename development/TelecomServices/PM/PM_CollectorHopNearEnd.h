/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 2004  Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for Near-End SONET/SDH HOP layer..
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORHOPNEAREND_H
#define PM_COLLECTORHOPNEAREND_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/src/PM_CommandUpdateAction.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for Near-End SONET/SDH HOP layer. These data
//are needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
class PM_CollectorHopNearEnd: public PM_Collector
{

public:

    //The constructor of collector HopNearEnd.
    PM_CollectorHopNearEnd(PM_GenericApplication& theGenericApplication,
                          FC_OneShotProcess&     theProcessorProcess,
                          uint32                 theNumberOfPort,
						  CT_PM_Sts_Offset		 theSts1Offset);
    
    //The default destructor of collector HopNearEnd.
    virtual ~PM_CollectorHopNearEnd();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM defects and PM BIP counters contain in the 
    //blackboard. The data is derived from the Facility 
    //Monitoring for BIP counters. The Collector blackboard 
    //regions will be used by the Processor.
    virtual void ProcessData();

	//Gets the inhibition verify request flag.
    bool GetConfigVerifyRequest();

    //Sets the inhibition verify request flag.
    void SetConfigVerifyRequest(bool theState);

protected:

    //Pointer to the region that contains HOP defects status for the current second.
    TEL_BbRegionBaseImp<PM_BbDefectHopNearEnd>* myDefectHopNearEnd;

    //Pointer to the region that contains HOP counters for the current second.
    TEL_BbRegionBaseImp<PM_BbCountHopNearEnd>* myCountHopNearEnd;

    //Pointer to the region that contains HOP failures for the current second.
    TEL_BbRegionBaseImp<PM_BbFailureHopNearEnd>* myFailureHopNearEnd;

private:

	// Method to update the STS-1 selected for pointer justification data collection.
	void UpdateSelectedSts1();

    //Action to run when configuration region has changed.
    PM_CommandUpdateAction myConfigUpdateAction;

	// Offset of the starting STS-1 into the set of STS-1s contained
	// in the OC-48 or OC-192.
	CT_PM_Sts_Offset mySts1Offset;

};

//-----------------------------------------------------------------
inline bool PM_CollectorHopNearEnd::GetConfigVerifyRequest() 
{ 
    return myConfigUpdateAction.GetState();

}

//-----------------------------------------------------------------
inline void PM_CollectorHopNearEnd::SetConfigVerifyRequest(bool theState) 
{ 
    myConfigUpdateAction.SetState(theState);

}

#endif //PM_COLLECTORHOPNEAREND_H
