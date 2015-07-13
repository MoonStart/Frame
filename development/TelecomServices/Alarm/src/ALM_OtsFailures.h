/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OTS (Optical Transport
                Section) layer.
--------------------------------------------------------------------------*/
#ifndef ALM_OTSFAILURES_H
#define ALM_OTSFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

/* Foward declaration of classes */
class ALM_AppIf;
class MON_OtsDefects;
class T6100_CardIf;

//This class (with its peer class ALM_OtsFailureBase) is responsible for processing all failures within the OTS (Optical Transport Section) layer. It links itself with the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
//##ModelId=3C506C300306
class ALM_OtsFailures:   public ALM_LayerFailures
{

public:

	//Constructor for this class.
	//
	//PARAM ALM_IndexNb theIndex: index of the object within the region.
	//
	//PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
	//
	//PARAM MON_OtsDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM T6100_CardIf& theOscContext: reference to the OSC context to retrieve the PMI.
	//
	//PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
	//##ModelId=3F954C2B0225
    ALM_OtsFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_OtsDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

	//Destructor for this class.
	//##ModelId=3C506C300375
    virtual ~ALM_OtsFailures();
    
	//This method read all OTS defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
	//##ModelId=3C506C300377
    virtual ALM_BitField ReadDefects() const;

	//Get the bit field mask that will use filter all failure of the lower layer.
	//
	//RETURN ALM_BitField: a mask that represents all failures (handle by this 
	//class), concatenated in a bit field, that filters all failures of an 
	//hierarchically lower layer.
	//##ModelId=3C506C30037F
    virtual ALM_BitField GetFilterAllMask() const;

	//This method filters failures associated to OTS layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
	//##ModelId=3C506C300381
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;


private:

	//The monitor that gives defects to Signal Alarm.
	//##ModelId=3C515E2800F6
    MON_OtsDefects& myMonitor;

	//The following instances process the failures according to its type. It  can be either normal or soaking.
	//
	//LOS OTS is a soaking failure.
	//##ModelId=3C506FB802FD
    ALM_SoakingFailure myLosOts;

};


#endif //ALM_OTSFAILURES_H
