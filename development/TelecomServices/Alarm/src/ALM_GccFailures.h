/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     
 AUTHOR   :     xinlun fang
 DESCRIPTION:   This class manages the failures of Gcc Link layer.
--------------------------------------------------------------------------*/

#ifndef ALM_GCCFAILURES_H
#define ALM_GCCFAILURES_H

#include <CommonTypes/CT_FacilityIds.h>

#include "../ALM_FPCommon.h"
#include "ALM_LayerFailures.h"
#include "ALM_NormalFailure.h"
#include "../ALM_SoakingFailure.h"

// Foward declaration of classes
class ALM_AppIf;
class MON_GccDefects;

class ALM_GCCFailures: public ALM_LayerFailures
{
public:

    ALM_GCCFailures(ALM_IndexNb theIndex,
                    ALM_AppIf& theApplication,
                    MON_GccDefects& theMonitor,
                    ALM_LayerFailures* theHigherLayerPtr = NULL);

    virtual ~ALM_GCCFailures();

    virtual ALM_BitField ReadDefects() const;

    virtual ALM_BitField GetFilterAllMask() const;

    virtual ALM_BitField GetNoFilterMask() const;

    virtual ALM_BitField Filter(ALM_BitField theFailure) const;

    void ProcessAfterSoaking();

private:

    MON_GccDefects& myMonitor;

    ALM_SoakingFailure myUpperSa;

    ALM_SoakingFailure myUpperNsa;

    ALM_SoakingFailure myGCCLinkIncmplt;

    ALM_SoakingFailure myGCCLinkDown;

    int mySignalType;

    T6100_CardIf* myCardIf;
};

#endif //ALM_GCCFAILURES_H
