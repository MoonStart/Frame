/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     Controller (SPM)
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class manages the failures of Router layer.
--------------------------------------------------------------------------*/
#ifndef ALM_RTRFAILURES_H
#define ALM_RTRFAILURES_H

#include <CommonTypes/CT_FacilityIds.h>

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

// Foward declaration of classes
class ALM_AppIf;

//This class is responsible for processing all failures
class ALM_RtrFailures: public ALM_LayerFailures
{
public:

    //Constructor for this class.
    //
    //PARAM ALM_IndexNb theIndex: index of the object within the region.
    //
    //PARAM ALM_AppIf& theApplication: a reference to the application instantiating this class.
    //
    //PARAM MON_OptDefects& theMonitor: reference to the monitor used to retrieve all defects.
    //
    //PARAM ALM_LayerFailures* theHigherLayerPtr = NULL: pointer to the higher layer use for the filtering.
    ALM_RtrFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    //MON_OptDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

    //Destructor for this class.
    virtual ~ALM_RtrFailures();

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
    //MON_OptDefects& myMonitor;

    ALM_SoakingFailure myRtrDown;

};

#endif //ALM_RTRFAILURES_H
