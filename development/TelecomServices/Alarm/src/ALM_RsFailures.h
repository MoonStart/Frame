/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of RS (Regenerator
                Section) layer
--------------------------------------------------------------------------*/
#ifndef ALM_RSFAILURES_H
#define ALM_RSFAILURES_H

//To drive LED on LOF
#include <AM/AM_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"


const FC_Milliseconds  ALM_UPPER_NSA_RS_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

/* Foward declaration of classes */
class ALM_AppIf;
class MON_RsDefects;
class T6100_CardIf;


/**
 * This class (with its peer class ALM_RsFailureBase) is responsible for processing all
 * failures within the RS (Regenerator Section) layer. It uses the appropriate monitor
 * to get all defects condition related to this layer. It also creates objects for each
 * failure to soak defects when necessary.
 */
//##ModelId=3C506C3000F4
class ALM_RsFailures:   public ALM_LayerFailures
{

public:

    /**
     * Constructor for this class.
     * 
     * PARAM ALM_IndexNb theIndex: index of the object within the region.
     * 
     * PARAM ALM_AppIf& theApplication: a reference to my application.
     * 
     * PARAM MON_RsDefects& theMonitor: reference to the monitor used to retrieve all defects.
     * 
     * PARAM CFG_Rs& theConfiguration: reference to the config used to retrieve config info.
     * 
     * PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
     */
    //##ModelId=3C506C300158
    ALM_RsFailures(ALM_IndexNb theIndex,
                   ALM_AppIf& theApplication,
                   MON_RsDefects& theMonitor,
                   ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    //##ModelId=3C506C300164
    virtual ~ALM_RsFailures();
    
    //This method read all defects of RS layer.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
    //##ModelId=3C506C30016C
    virtual ALM_BitField ReadDefects() const;

    //Get the bit field mask that will use filter all failure of the lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.
    //##ModelId=3C506C30016E
    virtual ALM_BitField GetFilterAllMask() const;

    //Get the bit field mask that will be used to filter failures of the 
    //current layer when upper layer is in failure.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handled by this 
    //class), concatenated in a bit field, that filters will not be filtered
    //when its upper layer is in failure.
	//##ModelId=3F954C2A012B
    virtual ALM_BitField GetNoFilterMask() const;

    //This method filters failures associated to RS layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    //##ModelId=3C506C300177
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    //Drive the LEDs when an LOF occurred.
    //##ModelId=3DBFFADB03D0
    void ProcessAfterSoaking();

private:

    //The monitor that gives defects to Signal Alarm.
    //##ModelId=3C515E2702DE
    MON_RsDefects& myMonitor;

    //The following instances process the failures according to its type. It
    //can be either normal or soaking.
    //
    //Optical Upper Layer Service Affection is a soaking failure.
	//##ModelId=3F954C2A014C
    ALM_SoakingFailure myUpperSa;
    ALM_SoakingFailure myUpperIntSa;

    //Optical Upper Layer None Service Affection is a soaking failure.
	//##ModelId=3F954C2A015B
    ALM_SoakingFailure myUpperNsa;

    //LOS is a soaking failure.
    //##ModelId=3C506FB80159
    ALM_SoakingFailure myLos;

    ALM_SoakingFailure myTais;

    //LOF is a soaking failure.
    //##ModelId=3C506FB8016D
    ALM_SoakingFailure myLof;
    ALM_SoakingFailure myLofInt;

    //TIM is a soaking failure.
    //##ModelId=3C506FB80181
    ALM_SoakingFailure myTim;
    ALM_SoakingFailure myTimNsa;

    //LF is a soaking failure.
    ALM_SoakingFailure myLf;

    //RF is a soaking failure.
    ALM_SoakingFailure myRf;

    //AIS_TX is a internal soaking failure.
    ALM_SoakingFailure myAisTx;

    ALM_SoakingFailure myCsfOpu;

    //LOF failure to drive a LED is a soaking failure of one second for soaking/recovery time.
    //##ModelId=3DBFFADC006B
    ALM_SoakingFailure myLed;

    ALM_SoakingFailure myGenAis;
    ALM_SoakingFailure myGenAisInt;

    // The signal type currently associated with the RS port.
    int mySignalType;

    //the status of the LED.
    //##ModelId=3DBFFADC00D8
    bool myLedStatus;

    uint8 myLedStatusAuditCnt;

    //The PortType to report the LED .
    //##ModelId=3E7764F400F7
    AM_PortType     theDirn;

	//##ModelId=3F954C2A016A
    unsigned char   myPortOffset;

    //A pointer to the card IF that support this RS layer, use to drive the LED.
    //##ModelId=3DBFFADC02EC
    T6100_CardIf* myCardIf;
};

#endif //ALM_RSFAILURES_H
