/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     RCMM
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class manages failures of OCH (Optcal Channel) layer on
                the RCMM module.
--------------------------------------------------------------------------*/
#ifndef ALM_OCHRCMMFAILURES_H
#define ALM_OCHRCMMFAILURES_H


#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds  ALM_LOS_OCHL_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

/* Foward declaration of classes */
class ALM_AppIf;
class MON_OptDefects;

// This class (with its peer class ALM_OchRcmmFailureBase) is responsible for
// processing all failures within the OCH (Optical Channel) layer on the RCMM.
// The RCMM implementation specifically uses the OPT monitor (all 32 of them)
// to get all defects condition related to this layer. It also creates objects
// for each failure to soak defects when necessary.
class ALM_OchRcmmFailures:   public ALM_LayerFailures
{

public:

	// Constructor for this class.
	//
	// PARAM ALM_IndexNb theIndex: index of the object within the region.
	//
	// PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
	//
	// PARAM MON_Defects& theMonitor: reference to the monitor used to retrieve all defects.
	//
	// PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    //
    ALM_OchRcmmFailures(ALM_IndexNb theIndex,
                        ALM_AppIf& theApplication,
                        MON_OptDefects& theMonitor,
                        ALM_LayerFailures* theHigherLayerPtr = NULL);

	// Destructor for this class.
    virtual ~ALM_OchRcmmFailures();
    
	// This method read all OCH defects.
    //
    // RETURN ALM_BitField: the status of all failures (handle by this class)
    // concatenated in a bit field.
    //
    virtual ALM_BitField ReadDefects() const;

	// Get the bit field mask that will use filter all failure of the lower layer.
	//
	// RETURN ALM_BitField: a mask that represents all failures (handle by this 
	// class), concatenated in a bit field, that filters all failures of an 
	// hierarchically lower layer.
    //
    virtual ALM_BitField GetFilterAllMask() const;

	// This method filters failures associated to OCH layer using the filtering table.
    //
    // PARAM ALM_BitField theFailure: the status of all failures (handle by this class)
    // concatenated in a bit field.
    //
    // RETURN ALM_BitField: the status of all failures (handle by this class)
    // concatenated in a bit field once they are filtered.
    //
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;


private:

	// The monitor that gives defects to Signal Alarm. Note that for the OCH
    // layer on the RCMM, it comes from the MON OPT layer.
    MON_OptDefects& myMonitor;

	// The following instances process the failures according to its type. It can
    // be either normal or soaking.
	//
	// LOS is a soaking failure.
    ALM_SoakingFailure  myLos;
};


#endif //ALM_OCHRCMMFAILURES_H
