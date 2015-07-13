/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM & ESIM
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class manages the failures of VCG layer
--------------------------------------------------------------------------*/
#ifndef ALM_VCGFAILURES_H
#define ALM_VCGFAILURES_H

#include <AM/AM_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>
#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds  ALM_UPPER_NSA_VCG_SOAKING_TIME (90000 - ALM_ADJUSTMENT_FACTOR);

/* Foward declaration of classes */
class ALM_AppIf;
class MON_AltVcgDefects;

/**
 * This class (with its peer class ALM_VcgFailureBase) is responsible for processing all
 * failures within the VCG layer. It uses the appropriate monitor
 * to get all defects condition related to this layer. It also creates objects for each
 * failure to soak defects when necessary.
 */
class ALM_VcgFailures:   public ALM_LayerFailures
{
public:

    /**
     * Constructor for this class.
     * 
     * PARAM ALM_IndexNb theIndex: index of the object within the region.
     * 
     * PARAM ALM_AppIf& theApplication: a reference to my application.
     * 
     * PARAM MON_AltVcgDefects& theMonitor: reference to the monitor used to retrieve all defects.
     * 
     * PARAM CFG_Vcg& theConfiguration: reference to the config used to retrieve config info.
     * 
     * PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
     */
    ALM_VcgFailures(ALM_IndexNb theIndex,
                   ALM_AppIf& theApplication,
                   MON_AltVcgDefects& theMonitor,
                   CT_CardFamily theCardFamily = SSM_FAM,
                   ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    virtual ~ALM_VcgFailures();
    
    //This method read all defects of RS layer.
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

    //This method filters failures associated to RS layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    void ProcessAfterSoaking();

private:

    //The monitor that gives defects to Signal Alarm.
    MON_AltVcgDefects& myMonitor;

    //The following instances process the failures according to its type. It
    //can be either normal or soaking.
    //
    //Optical Upper Layer Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperSa;

    //Optical Upper Layer None Service Affection is a soaking failure.
    ALM_SoakingFailure myUpperNsa;

    ALM_SoakingFailure myTLCRX;
    ALM_SoakingFailure myPLCRX;
    ALM_SoakingFailure myFOPRX;
    ALM_SoakingFailure myFOPTX;

    ALM_SoakingFailure myLOM;
    ALM_SoakingFailure mySQM;
    ALM_SoakingFailure myMND;

    bool IsVCGBlockAlarmFlagSet;

    //The VCG class is used for both SSM and ESIM. 
    //ESIM uses TelecomIf to report/clear alarms while SSM uses CardIf. Need distinguish them using myCardFamily.
    //In order not to change legacy code, the default value is SSM_FAM if not input.
    CT_CardFamily myCardFamily;

    T6100_CardIf* myCardIf;
    //myRptIf is used for ESIM card. ESIM uses this interface to report/clear defects instead of myCardIf.
    T6100_TelecomIf* myRptIf;   
};

#endif //ALM_VCGFAILURES_H
