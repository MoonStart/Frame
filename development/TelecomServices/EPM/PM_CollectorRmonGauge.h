/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 19, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Rmon.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORRMONGAUGE_H
#define PM_COLLECTORRMONGAUGE_H

#include <vector>
#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_BbStatusRmon.h>
#include <Configuration/CFG_Rs.h>


// Forward class declaration
class FC_OneShotProcess;

using namespace std;

//The Class is responsible to collect data used by the 
//Processor Rmon Gauge. These data are needed once 
//every second.
class PM_CollectorRmonGauge: public PM_Collector
{

public:

    //The default constructor.
    PM_CollectorRmonGauge(PM_GenericApplication&  theGenericApplication,
						  FC_OneShotProcess&     theProcessorProcess,
						  uint32 theNumberOfPort);
    
    //The default destructor.
    virtual ~PM_CollectorRmonGauge();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    virtual void ProcessData();

	// Returns a pointer to the CFG_Rs region.
	CFG_Rs* GetCfgRsRegion( T6100_CardIf& theCardContext, CT_PM_Side theSide );

	// Maps a Signal Type to payload bit rate.
	CT_TEL_daHz SignalTypeToBitRate( CT_TEL_SignalType theSignalType );

	// Method to map line bit rate to payload bit rate.
	void MapToPayloadBitRate( CT_TEL_daHz& theBitRate );

	// Returns the bit rate of the facility.
	CT_TEL_daHz GetBitRate();

protected:

    //Pointer to the region that contained Rmon gauge 
    //values for the current second.
    TEL_BbRegionBaseImp<PM_BbStatusRmon>* myStatusRmon;

};

#endif //PM_COLLECTORRMON_H
