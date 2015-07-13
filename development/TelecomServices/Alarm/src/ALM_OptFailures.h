/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OPT (Optical) layer.
--------------------------------------------------------------------------*/
#ifndef ALM_OPTFAILURES_H
#define ALM_OPTFAILURES_H

#include <AM/AM_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"


const FC_Milliseconds  ALM_UPPER_NSA_OPT_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

// Foward declaration of classes
class ALM_AppIf;
class MON_OptDefects;
class T6100_CardIf;


//This class (with its peer class ALM_OptFailureBase) is responsible for processing all failures within the OPT (Optical) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
//##ModelId=3C506C310195
class ALM_OptFailures:    public ALM_LayerFailures
{

public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
    //
    //PARAM MON_OptDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    //##ModelId=3C506C3101F9
    ALM_OptFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_OptDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    //##ModelId=3C506C310206
    virtual ~ALM_OptFailures();

    //This method read all OPT defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
    //##ModelId=3C506C31020D
    virtual ALM_BitField ReadDefects() const;

    //Get the bit field mask that will use filter all failure of the lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
    //##ModelId=3C506C31020F
    virtual ALM_BitField GetFilterAllMask() const;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
	//##ModelId=3F954C2D0080
    virtual ALM_BitField GetNoFilterMask() const;

    //This method filters failures associated to OPT layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    //##ModelId=3C506C310218
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    //Drive the LEDs when an LOS occurred.
    void ProcessAfterSoaking();

private:

    //The monitor that gives defects to Signal Alarm.
    //##ModelId=3C515E2900D9
    MON_OptDefects& myMonitor;

    //The following instances process failures according to its type. The type can be either Normal or Soaking.
    //
    //Optical Upper Layer Service Affection is a soaking failure.
	//##ModelId=3F954C2D0090
    ALM_SoakingFailure myUpperSa;

    //Optical Upper Layer None Service Affection is a soaking failure.
	//##ModelId=3F954C2D00A2
    ALM_SoakingFailure myUpperNsa;

    //Optical LOS is a soaking failure.
    //##ModelId=3C506FB90128
    ALM_SoakingFailure myLos;

    //LOSS of clock is a soaking failure.
    //##ModelId=3C506FB90146
    ALM_SoakingFailure myLoc;

    //Facility Switch Threshold Crossed is a soaking failure
    ALM_SoakingFailure mySwThresh;

    //Facility mismatch is a soaking failure
    //##ModelId=3E7764F9009A
    ALM_SoakingFailure myMfa;

    //---------------------------------------------
    //Declare the Signal Protect soaking failures.
    //---------------------------------------------
    ALM_SoakingFailure mySigProtNSA;
    ALM_SoakingFailure mySigProtProtna;

    // The signal type currently associated with the RS port.
    int mySignalType;

    //A pointer to the card IF that support this RS layer, use to drive the LED.
    T6100_CardIf* myCardIf;

    //the status of the LED.
    //used by OSC card.
    bool myLedStatus;

    uint8 myLedStatusAuditCnt;
};

#endif //ALM_OPTFAILURES_H
