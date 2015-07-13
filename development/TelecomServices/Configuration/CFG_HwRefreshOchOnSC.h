// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHOCHONSC_
#define _CFG_HWREFRESHOCHONSC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <ITS/ITS_Definitions.h>
#include <T6100_CardIf.h>
#include <CommonTypes/CT_Telecom.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <ExecutionSupport/FC_BaseTimer.h>

//This action is invoked periodically in order to update
//'optical channel layer' hardware registers with current 'optical channel
//layer' configuration.
class CFG_HwRefreshOchOnSC
: public CFG_HwRefreshAction
{
public:
    //Constructor
    CFG_HwRefreshOchOnSC(CFG_AppIf& theCfgIf,
                     TSPII_PipeRegion& thePipePiiRegion,
                     unsigned int thePipePiiUnit,
                     CT_Side theSide);

    //Virtual destructor
    virtual ~CFG_HwRefreshOchOnSC();

    //This method refreshes all hardware related to optical
    //channel layer.  It reads the current value of each Och layer
    //parameter an invokes the corresponding PII interface.
    //This action is normally invoked upon a change of the
    //region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    bool UpdateObject(unsigned theRunReason,uint32 theIndex);

    void Commit();

private:
    uint32 GetWavelengthFromEvoa(uint32 theEvoa) const;

    TSPII_PipeRegion& myPipePiiRegion;

    unsigned int myPipePiiUnit;
    CT_Side mySide;

    T6100_CardIf* myCardContext;
    CFG_OchHistoryCfgRegion* myHistoryCfgRegion;
    CT_TEL_mBm myPrevGain[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    FC_BaseTimer myRefreshTimer;

    uint32 myHistorySize;
};

#endif /* _CFG_HWREFRESHOCHONSC_ */
