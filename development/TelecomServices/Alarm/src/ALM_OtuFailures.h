/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OTU (Optical Transport
                Unit) layer.
--------------------------------------------------------------------------*/
#ifndef ALM_OTUFAILURES_H
#define ALM_OTUFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds  ALM_UPPER_NSA_OTU_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

// Foward declaration of classes
class ALM_AppIf;
class MON_OtuDefects;
class T6100_CardIf;

//This class (with its peer class ALM_OtuFailureBase) is responsible for processing all failures within the OTU (Optical Transport Unit) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
//##ModelId=3C506C3001F8
class ALM_OtuFailures:    public ALM_LayerFailures
{
public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
    //
    //PARAM MON_OtuDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    //##ModelId=3C506C30025D
    ALM_OtuFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_OtuDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    //##ModelId=3C506C300269
    virtual ~ALM_OtuFailures();

    //This method read all OTU defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
    //##ModelId=3C506C300271
    virtual ALM_BitField ReadDefects() const;

    //Get the bit field mask that will use filter all failure of the lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
    //##ModelId=3C506C300273
    virtual ALM_BitField GetFilterAllMask() const;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
	//##ModelId=3F954C2A03AC
    virtual ALM_BitField GetNoFilterMask() const;

    //This method filters failures associated to OTU layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    //##ModelId=3C506C30027B
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    // needed to drive LED behavior
    void ProcessAfterSoaking();

private:

    //The monitor that gives defects to Signal Alarm.
    //##ModelId=3C515E28002D
    MON_OtuDefects& myMonitor;

    //The following instances process failures according to its type. The type can be either Normal or Soaking.
    //
    //Optical Upper Layer Service Affection is a soaking failure.
	//##ModelId=3F954C2A03CC
    ALM_SoakingFailure myUpperSa;

    //Optical Upper Layer None Service Affection is a soaking failure.
	//##ModelId=3F954C2A03DC
    ALM_SoakingFailure myUpperNsa;

    //LOF is a soaking failure.
    //##ModelId=3C506FB80217
    ALM_SoakingFailure myLof;
    ALM_SoakingFailure myLom;

    //AIS is a soaking failure.
    //##ModelId=3C506FB8022B
    ALM_SoakingFailure myAis;

    //TIM is a soaking failure.
    //##ModelId=3C506FB80249
    ALM_SoakingFailure myTim;

    ALM_SoakingFailure myTimNsa;

    ALM_SoakingFailure myFecm;

    //BDI is a soaking failure.
    //##ModelId=3E7764F500EE
    ALM_SoakingFailure myBdi;

    ALM_SoakingFailure myBersd;

    //FEC-SD is a soaking failure.
    //##ModelId=3C506FB8025D
    ALM_SoakingFailure myFecsd;

    ALM_SoakingFailure myDisp;

    // LOF-OTU will drive FGTMM LINE LED
    ALM_SoakingFailure myLed4LOFOTU;
    ALM_SoakingFailure myLed4LOMOTU;
    bool               myLedStatus;
    T6100_CardIf*      myCardIf;
    unsigned char      myPortOffset;
};

#endif //ALM_OTUFAILURES_H
