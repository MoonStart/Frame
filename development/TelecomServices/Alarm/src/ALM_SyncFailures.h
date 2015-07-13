/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class manages the failures of Sync
--------------------------------------------------------------------------*/
#ifndef ALM_SYNCFAILURES_H
#define ALM_SYNCFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds ALM_SYNC_SOAKING_TIME(30000 - ALM_ADJUSTMENT_FACTOR); // 30 seconds

/* Foward declaration of classes */
class ALM_AppIf;
class MON_SyncDefects;
class T6100_CardIf;


//This class (with its peer class ALM_SyncFailureBase) is responsible for processing all failures within the Sync (Regenerator Section) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
class ALM_SyncFailures:   public ALM_LayerFailures
{

public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to my application.
    //
    //PARAM MON_SyncDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    ALM_SyncFailures(ALM_IndexNb theIndex,
                   ALM_AppIf& theApplication,
                   MON_SyncDefects& theMonitor,
                   ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    virtual ~ALM_SyncFailures();
    
    //This method read all defects of Sync layer.
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

    //This method filters failures associated to Sync layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;
    
private:

    //The monitor that gives defects to Signal Alarm.
    MON_SyncDefects& myMonitor;

    //The following instances process the failures according to its type. It  can be either normal or soaking.
    //
    //SFBER is a soaking failure.
    ALM_SoakingFailure myFreeRun;

    //SDBER is a soaking failure.
    ALM_SoakingFailure myHoldover;
};


#endif //ALM_SYNCFAILURES_H
