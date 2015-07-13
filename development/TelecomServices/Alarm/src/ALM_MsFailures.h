/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All card
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class manages the failures of MS (Regenerator
                Section) layer
--------------------------------------------------------------------------*/
#ifndef ALM_MSFAILURES_H
#define ALM_MSFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"


const FC_Milliseconds  ALM_UPPER_NSA_MS_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

/* Foward declaration of classes */
class ALM_AppIf;
class MON_MsDefects;
class T6100_CardIf;


//This class (with its peer class ALM_MsFailureBase) is responsible for processing all failures within the MS (Regenerator Section) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
//##ModelId=3F954C2E0352
class ALM_MsFailures:   public ALM_LayerFailures
{

public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to my application.
    //
    //PARAM MON_MsDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
	//##ModelId=3F954C2F009F
    ALM_MsFailures(ALM_IndexNb theIndex,
                   ALM_AppIf& theApplication,
                   MON_MsDefects& theMonitor,
                   ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
	//##ModelId=3F954C2F00A4
    virtual ~ALM_MsFailures();
    
    //This method read all defects of MS layer.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
	//##ModelId=3F954C2F00A6
    virtual ALM_BitField ReadDefects() const;

    //Get the bit field mask that will use filter all failure of the lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
	//##ModelId=3F954C2F00AE
    virtual ALM_BitField GetFilterAllMask() const;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
	//##ModelId=3F954C2F00B0
    virtual ALM_BitField GetNoFilterMask() const;

    //This method filters failures associated to MS layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
	//##ModelId=3F954C2F00B2
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    /**
     * This method is used by the MS layer to obtain the signal rate of the
     * port which is reporting the AIS-L failure (actually detected on the line).
     */
    void ProcessAfterSoaking();
    
private:

    //The monitor that gives defects to Signal Alarm.
	//##ModelId=3F954C2F00B6
    MON_MsDefects& myMonitor;

    //The following instances process the failures according to its type. It  can be either normal or soaking.
    //
    //Optical Upper Layer Service Affection is a soaking failure.
	//##ModelId=3F954C2F00C2
    ALM_SoakingFailure myUpperSa;

    //Optical Upper Layer None Service Affection is a soaking failure.
	//##ModelId=3F954C2F00CF
    ALM_SoakingFailure myUpperNsa;

    ALM_SoakingFailure myUpperIntSa;

    ALM_SoakingFailure myAisInt;
    //AIS is a soaking failure.
	//##ModelId=3F954C2F00DE
    ALM_SoakingFailure myAis;

    //RDI is a soaking failure.
	//##ModelId=3F954C2F00EE
    ALM_SoakingFailure myRdi;

    //SFBER is a soaking failure.
	//##ModelId=3F954C2F011D
    ALM_SoakingFailure mySfBer;

    //SDBER is a soaking failure.
	//##ModelId=3F954C2F012C
    ALM_SoakingFailure mySdBer;

    //----------------------------------------
    //Declare Signal Protect soaking failures.
    //----------------------------------------
    ALM_SoakingFailure mySigProtNSA;
    ALM_SoakingFailure mySigProtProtna;

    T6100_CardIf* myCardIf;
    uint16        myPortOffset;
    AM_PortType   theDirn;
};

#endif //ALM_MSFAILURES_H
