/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class manages the failures of OMS (Optical Multiplex
                Section) layer.
--------------------------------------------------------------------------*/
#ifndef ALM_OMSFAILURES_H
#define ALM_OMSFAILURES_H

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

const FC_Milliseconds ALM_AOPE_OMS_SOAKING_TIME(30000 - ALM_ADJUSTMENT_FACTOR);    // 30 seconds
const FC_Milliseconds ALM_AOPE_OMS_RECOVERY_TIME(30000 - ALM_ADJUSTMENT_FACTOR);   // 30 seconds
const FC_Milliseconds ALM_OPOVLD_OMS_SOAKING_TIME(30000 - ALM_ADJUSTMENT_FACTOR);  // 30 seconds
const FC_Milliseconds ALM_OPOVLD_OMS_RECOVERY_TIME(30000 - ALM_ADJUSTMENT_FACTOR); // 30 seconds


/* Foward declaration of classes */
class ALM_AppIf;
class MON_OmsDefects;
class T6100_CardIf;

//This class (with its peer class ALM_OmsFailureBase) is responsible for processing all failures within the OMS (Optical Multiplex Section) layer. It links itself with the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.

//##ModelId=3E7764F900D6
class ALM_OmsFailures:   public ALM_LayerFailures
{

public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
    //
    //PARAM MON_OmsDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.

    //##ModelId=3E7764F90270
    ALM_OmsFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_OmsDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    
    //##ModelId=3E7764F90284
    virtual ~ALM_OmsFailures();
    
    //This method read all OMS defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.

    //##ModelId=3E7764F9028D
    virtual ALM_BitField ReadDefects() const;

    //Get the bit field mask that will use filter all failure of the lower layer.
    //
    //RETURN ALM_BitField: a mask that represents all failures (handle by this 
    //class), concatenated in a bit field, that filters all failures of an 
    //hierarchically lower layer.

    //##ModelId=3E7764F9028F
    virtual ALM_BitField GetFilterAllMask() const;

    //This method filters failures associated to OMS layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.

    //##ModelId=3E7764F90298
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;


private:

    //The monitor that gives defects to Signal Alarm.
    //##ModelId=3E77681F0201
    MON_OmsDefects& myMonitor;

    //The following instances process the failures according to its type. It  can be either normal or soaking.

    //LOS OMS is a soaking failure.
    //##ModelId=3E77681F0214
    ALM_SoakingFailure myLosOms;

    //LOS Internal OMS is a soaking failure.
    //##ModelId=3E77681F0229
    ALM_SoakingFailure myLosIntOms;

    //OPOVLD OMS is a soaking failure.
	//##ModelId=3F954C2D0236
    ALM_SoakingFailure myOpovldOms;

    //AOPE OMS is a soaking failure.
	//##ModelId=3F954C2D0246
    ALM_SoakingFailure myAopeOms;

};


#endif //ALM_OMSFAILURES_H
