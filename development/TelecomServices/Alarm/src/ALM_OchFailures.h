/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages failures of OCH (Optcal Channel) layer.
--------------------------------------------------------------------------*/
#ifndef ALM_OCHFAILURES_H
#define ALM_OCHFAILURES_H


#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds  ALM_LOS_OCHL_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

/* Foward declaration of classes */
class ALM_AppIf;
class MON_OchDefects;

//This class (with its peer class ALM_OchFailureBase) is responsible for processing all failures within the OCH (Optical Channel) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
//##ModelId=3C506C31038A
class ALM_OchFailures:   public ALM_LayerFailures
{

public:

	//Constructor for this class.
	//
	//PARAM ALM_IndexNb theIndex: index of the object within the region.
	//
	//PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
	//
	//PARAM MON_Defects& theMonitor: reference to the monitor used to retrieve all defects.
	//
	//PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
	//##ModelId=3C506C320006
    ALM_OchFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_OchDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

	//Destructor for this class.
	//##ModelId=3C506C320011
    virtual ~ALM_OchFailures();
    
	//This method read all OCH defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
	//##ModelId=3C506C320013
    virtual ALM_BitField ReadDefects() const;

	//Get the bit field mask that will use filter all failure of the lower layer.
	//
	//RETURN ALM_BitField: a mask that represents all failures (handle by this 
	//class), concatenated in a bit field, that filters all failures of an 
	//hierarchically lower layer.
	//##ModelId=3C506C32001B
    virtual ALM_BitField GetFilterAllMask() const;

	//This method filters failures associated to OCH layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
	//##ModelId=3C506C320024
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;


private:

	//The monitor that gives defects to Signal Alarm.
	//##ModelId=3C515E29036D
    MON_OchDefects& myMonitor;

	//The following instances process the failures according to its type. It  can be either normal or soaking.
	//
	//LOS is a soaking failure.
	//##ModelId=3C506FB902E1
    ALM_SoakingFailure  myLos;

	//##ModelId=3E7764FB03AA
	ALM_SoakingFailure  myDtd;

};


#endif //ALM_OCHFAILURES_H
