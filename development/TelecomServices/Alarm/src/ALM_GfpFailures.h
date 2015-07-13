/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class manages the failures of the GFP (Generic
                Framing Procedure) layer
--------------------------------------------------------------------------*/
#ifndef ALM_GFPFAILURES_H
#define ALM_GFPFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"


const FC_Milliseconds  ALM_UPPER_NSA_GFP_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

/* Foward declaration of classes */
class ALM_AppIf;
class MON_GfpDefects;
class T6100_CardIf;


// This class (with its peer class ALM_GfpFailureBase) is responsible for
// processing all failures within the GFP (Generic Framing Procedure) layer. It
// uses the appropriate monitor to get all defects condition related to this
// layer. It also creates objects for each failure to soak defects when necessary.
class ALM_GfpFailures:   public ALM_LayerFailures
{

public:

    // Constructor for this class.
    //
    // PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    // PARAM ALM_AppIf& theApplication: a reference to my application.
    //
    // PARAM MON_GfpDefects& theMonitor: reference to the monitor used to retrieve
	//      all of the GFP defects.
    //
    // PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher
	//      layer use for the filtering.
    ALM_GfpFailures(ALM_IndexNb theIndex,
                   ALM_AppIf& theApplication,
                   MON_GfpDefects& theMonitor,
                   ALM_LayerFailures* theHigherLayerPtr = NULL);

    // Destructor for this class.
    virtual ~ALM_GfpFailures();
    
    // This method reads all the defects of the GFP layer.
    //
    // RETURN ALM_BitField: the status of all failures (handle by this class)
	// concatenated in a bit field.
    virtual ALM_BitField ReadDefects() const;

    // Get the bit field mask that will use filter all failure of the lower layer.
    //
    // RETURN ALM_BitField: a mask that represents all failures (handle by this 
    // class), concatenated in a bit field, that filters all failures of an 
    // hierarchically lower layer.
    virtual ALM_BitField GetFilterAllMask() const;

    // Get the bit field mask that will be used to filter failures of the 
    // current layer when upper layer is in failure.
    //
    // RETURN ALM_BitField: a mask that represents all failures (handled by this 
    // class), concatenated in a bit field, that filters will not be filtered
    // when its upper layer is in failure.
    virtual ALM_BitField GetNoFilterMask() const;

    // This method filters failures associated to GFP layer using the filtering
	// table.
    //
    // PARAM ALM_BitField theFailure: the status of all failures (handle by this
	// class) concatenated in a bit field.
    //
    // RETURN ALM_BitField: the status of all failures (handle by this class)
	// concatenated in a bit field once they are filtered.
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    void ProcessAfterSoaking();

private:

    // The monitor that gives defects to Signal Alarm.
    MON_GfpDefects& myMonitor;

    // The following instances process the failures according to its type. It
	// can be either normal or soaking.
    //
    // Optical Upper Layer Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperSa;

    // Optical Upper Layer None Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperNsa;

    ALM_SoakingFailure myUpperIntSA;

    ALM_SoakingFailure myLofd;
    ALM_SoakingFailure myPlm;
    ALM_SoakingFailure myCsfLos;
    ALM_SoakingFailure myCsfLoSync;
    ALM_SoakingFailure myCsfFefi;
    ALM_SoakingFailure myCsfFdi;
    ALM_SoakingFailure myCsfRdi;
    ALM_SoakingFailure myLoa;
    ALM_SoakingFailure mySqm;
    ALM_SoakingFailure myChec;
    ALM_SoakingFailure myPli;
    ALM_SoakingFailure myRmtlf;
    ALM_SoakingFailure myAutoNeg;

    T6100_CardIf* myCardIf;
    uint16        myPortOffset;
    AM_PortType   theDirn;
};

#endif //ALM_GFPFAILURES_H
