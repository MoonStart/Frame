/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SMTM card
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class manages the failures of Dcc Link layer.
--------------------------------------------------------------------------*/

#ifndef ALM_DCCLFAILURES_H
#define ALM_DCCLFAILURES_H

#include <CommonTypes/CT_FacilityIds.h>

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

// Foward declaration of classes
class ALM_AppIf;
class MON_DcclDefects;

//This class is responsible for processing all failures
class ALM_DcclFailures: public ALM_LayerFailures
{
public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
    //
    //PARAM MON_DcclDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    ALM_DcclFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_DcclDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    virtual ~ALM_DcclFailures();

    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
    virtual ALM_BitField ReadDefects() const;

    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
    virtual ALM_BitField GetFilterAllMask() const;

    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
    virtual ALM_BitField GetNoFilterMask() const;

    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

private:

    //The monitor that gives defects to Signal Alarm.
    MON_DcclDefects& myMonitor;

    //Optical Upper Layer Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperSa;

    //Optical Upper Layer None Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperNsa;

    ALM_SoakingFailure myDccLinkIncmplt;

    ALM_SoakingFailure myDccLinkDown;

    // The signal type currently associated with the RS port.
    int mySignalType;

    //A pointer to the card IF that support this RS layer, use to drive the LED.
    T6100_CardIf* myCardIf;
};

#endif //ALM_DCCLFAILURES_H
