/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM
 DESCRIPTION:   This class manages the failures of MAC layer.
--------------------------------------------------------------------------*/
#ifndef ALM_MACFAILURES_H
#define ALM_MACFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds  ALM_UPPER_NSA_MAC_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

// Foward declaration of classes
class ALM_AppIf;
class MON_MacDefects;
class T6100_CardIf;

class ALM_MacFailures: public ALM_LayerFailures
{
public:

	//Constructor for this class.
	//
	//PARAM ALM_IndexNb theIndex: index of the object within the region.
	//
	//PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
	//
	//PARAM MON_OduDefects& theMonitor: a reference to the monitor used to retrieve all defects.
	//
	//PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
	//##ModelId=3C506C3102D7
    ALM_MacFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_MacDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

	//Destructor for this class.
	//##ModelId=3C506C3102E4
    virtual ~ALM_MacFailures();

	//This method read all ODU defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
	//##ModelId=3C506C3102EB
    virtual ALM_BitField ReadDefects() const;

	//Get the bit field mask that will use filter all failure of the lower layer.
	//
	//RETURN ALM_BitField: a mask that represents all failures (handle by this 
	//class), concatenated in a bit field, that filters all failures of an 
	//hierarchically lower layer.
	//##ModelId=3C506C3102ED
    virtual ALM_BitField GetFilterAllMask() const;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
    virtual ALM_BitField GetNoFilterMask() const;

	//This method filters failures associated to ODU layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
	//##ModelId=3C506C3102FF
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    void ProcessAfterSoaking();

private:

	//The monitor that gives defects to Signal Alarm.
	//##ModelId=3C515E29029C
    MON_MacDefects& myMonitor;

	//The following instances process failures according to its type. The type can be either Normal or Soaking.

    //Upper Layer Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperSa;

    //Upper Layer None Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperNsa;

	//AIS is a soaking failure.
	//##ModelId=3C506FB901DC
    ALM_SoakingFailure myLacpFail;

    ALM_SoakingFailure myRflinkFail;

    T6100_CardIf* myCardIf;

    //--------------------------------------------
    //Declare all Signal Protect soaking failures.
    //--------------------------------------------
    ALM_SoakingFailure mySigProtNSA;
};

#endif //ALM_MACFAILURES_H
