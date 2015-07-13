/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class manages failures action of OCH layer within 
                the OSC channel.
--------------------------------------------------------------------------*/
#ifndef ALM_OCHOSCFAILURES_H
#define ALM_OCHOSCFAILURES_H


#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

/* Foward declaration of classes */
class ALM_AppIf;
class MON_OtsOchOHDefects;

//This class (with its peer class ALM_OchFailureBase) is responsible for processing all failures within the OCH (Optical Channel) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.

//##ModelId=3E7764FA03B1
class ALM_OchOscFailures:   public ALM_LayerFailures
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

	//##ModelId=3E7764FB016E
    ALM_OchOscFailures(ALM_IndexNb theIndex,
                       ALM_AppIf& theApplication,
                       MON_OtsOchOHDefects& theMonitor,
                       ALM_LayerFailures* theHigherLayerPtr = NULL);

	//Destructor for this class.

	//##ModelId=3E7764FB0182
    virtual ~ALM_OchOscFailures();
    
	//This method read all OCH defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.

	//##ModelId=3E7764FB0184
    virtual ALM_BitField ReadDefects() const;

	//Get the bit field mask that will use filter all failure of the lower layer.
	//
	//RETURN ALM_BitField: a mask that represents all failures (handle by this 
	//class), concatenated in a bit field, that filters all failures of an 
	//hierarchically lower layer.

	//##ModelId=3E7764FB018D
    virtual ALM_BitField GetFilterAllMask() const;

	//This method filters failures associated to OCH layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.

	//##ModelId=3E7764FB0196
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;


private:

	//The monitor that gives defects to Signal Alarm.

	//##ModelId=3E7768200307
    MON_OtsOchOHDefects& myMonitor;

	//The following instances process the failures according to its type. It  can be either normal or soaking.
	//

	//FDIP-OCH is a soaking failure.
	//##ModelId=3E776820031B
	ALM_SoakingFailure myFdiP;
	
	//FDIO-OCH is a soaking failure.
	//##ModelId=3E7768200339
	ALM_SoakingFailure myFdiO;

    //OCI is a soaking failure.
	//##ModelId=3E776820034D
    ALM_SoakingFailure myOci;
};


#endif //ALM_OCHOSCFAILURES_H
