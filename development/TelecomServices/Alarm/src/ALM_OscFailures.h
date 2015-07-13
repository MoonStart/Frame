/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OSC (Optical Supervisory
                Channel) layer.
--------------------------------------------------------------------------*/
#ifndef ALM_OSCFAILURES_H
#define ALM_OSCFAILURES_H


#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

/* Foward declaration of classes */
class ALM_AppIf;
class MON_OtsOHDefects;

//This class (with its peer class ALM_OscFailureBase) is responsible for processing all failures within the OSC (Optical Supervisory Channel) layer. It uses the appropriate monitor to get all defects condition related to this layer. It also creates objects for each failure to soak defects when necessary.
//##ModelId=3C506C310005
class ALM_OscFailures:   public ALM_LayerFailures
{

public:

	//Constructor for this class.
	//
	//PARAM ALM_IndexNb theIndex: index of the object within the region.
	//
	//PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
	//
	//PARAM MON_OscDefects& theMonitor: reference to the monitor used to retrieve all defects.
	//
	//PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
	//##ModelId=3C506C310060
    ALM_OscFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_OtsOHDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

	//Destructor for this class.
	//##ModelId=3C506C310073
    virtual ~ALM_OscFailures();
    
	//This method read all OSC defects.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field.
	//##ModelId=3C506C310075
    virtual ALM_BitField ReadDefects() const;

	//Get the bit field mask that will use filter all failure of the lower layer.
	//
	//RETURN ALM_BitField: a mask that represents all failures (handle by this 
	//class), concatenated in a bit field, that filters all failures of an 
	//hierarchically lower layer.
	//##ModelId=3C506C31007D
    virtual ALM_BitField GetFilterAllMask() const;

	//This method filters failures associated to OSC layer using the filtering table.
    //
    //PARAM ALM_BitField theFailure: the status of all failures (handle by this class) concatenated in a bit field.
    //
    //RETURN ALM_BitField: the status of all failures (handle by this class) concatenated in a bit field once they are filtered.
	//##ModelId=3C506C31007F
    virtual ALM_BitField Filter(ALM_BitField theFailure) const;


private:

	//The monitor that gives defects to Signal Alarm.
	//##ModelId=3C515E2803BD
    MON_Defects& myMonitor;

	//The following instances process the failures according to its type. It  can be either normal or soaking.
	//
	 
    //PMI is a soaking failure.
	//##ModelId=3C506FB803D0
    ALM_SoakingFailure myPmiOts;

    //BDI is a soaking failure.
	//##ModelId=3CC4D1CF01B3
    ALM_SoakingFailure myBdiOts;

    //BDIO is a soaking failure.
	//##ModelId=3C506FB803E4
    ALM_SoakingFailure myBdioOts;

    //BDIP is a soaking failure.
	//##ModelId=3C506FB9001A
    ALM_SoakingFailure myBdipOts;

    //TIM is a soaking failure.
	//##ModelId=3C506FB803BC
    ALM_SoakingFailure myTimOts;

	//FDIO is a soaking failure.
	//##ModelId=3C506FB9004C
    ALM_SoakingFailure myFdioOms;

    //FDIP is a soaking failure.
	//##ModelId=3C506FB90060
    ALM_SoakingFailure myFdipOms;

    //PMI is a soadking failure.
	//##ModelId=3E7764F80201
     ALM_SoakingFailure myPmiOms;
    
     //BDIO is a soaking failure.
	//##ModelId=3C506FB90074
    ALM_SoakingFailure myBdioOms;

    //BDIP is a soaking failure.
	//##ModelId=3C506FB90092
    ALM_SoakingFailure myBdipOms;
};


#endif //ALM_OSCFAILURES_H
