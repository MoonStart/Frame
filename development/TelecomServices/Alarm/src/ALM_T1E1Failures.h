/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class manages the failures of the T1E1 (bits clock).
--------------------------------------------------------------------------*/
#ifndef ALM_T1E1FAILURES_H
#define ALM_T1E1FAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"


// Foward declaration of classes
class ALM_AppIf;
class MON_T1E1Defects;
class T6100_CardIf;


// This class is responsible for processing all failures within the T1E1 (bits
// clock). It uses the appropriate monitor to get all defects condition related
// to this layer. It also creates objects for each failure to soak defects when
// necessary.
class ALM_T1E1Failures:    public ALM_LayerFailures
{

public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
    //
    //PARAM MON_T1E1Defects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    ALM_T1E1Failures(ALM_IndexNb theIndex,
                     ALM_AppIf& theApplication,
                     MON_T1E1Defects& theMonitor,
                     ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    virtual ~ALM_T1E1Failures();

    //This method reads all of the T1E1 defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
    virtual ALM_BitField ReadDefects() const;

    //Get the bit field mask that will use filter all failure of the lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
    virtual ALM_BitField GetFilterAllMask() const;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
    virtual ALM_BitField GetNoFilterMask() const;

    //This method filters failures associated to T1E1 layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    //Drive the LEDs on an error.
    void ProcessAfterSoaking();


private:

    //The monitor that gives defects to Signal Alarm.
    MON_T1E1Defects& myMonitor;

    // Loss of Signal is a soaking failure.
    ALM_SoakingFailure myLos;

    // Loss of Frame is a soaking failure.
    ALM_SoakingFailure myLof;

    // Alarm Indication Signal is a soaking failure
    ALM_SoakingFailure myAis;

    ALM_SoakingFailure myFreqOff;

    // LED AIS on OPSM 
    ALM_SoakingFailure myAISLed;

    // LED LOS on OPSM
    ALM_SoakingFailure myLOSLed;

    // LED LOF on OPSM
    ALM_SoakingFailure myLOFLed;

    //the AIS status of the LED.
    bool myAISLedStatus;

    //the LOS status of the LED.
    bool myLOSLedStatus;

    //the LOF status of the LED.
    bool myLOFLedStatus;

    //A pointer to the card IF that support this T1E1 layer, use to drive the LED.
    T6100_CardIf* myCardIf;

};

#endif //ALM_T1E1FAILURES_H
