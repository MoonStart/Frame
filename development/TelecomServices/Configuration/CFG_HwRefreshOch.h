// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHOCH_
#define _CFG_HWREFRESHOCH_

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
class CFG_HwRefreshOch
: public CFG_HwRefreshAction
{
public:
    //Constructor
    CFG_HwRefreshOch(CFG_AppIf& theCfgIf,
                     TSPII_PipeRegion& thePipePiiRegion,
                     unsigned int thePipePiiUnit,
                     CT_Side theSide);

    //Virtual destructor
    virtual ~CFG_HwRefreshOch();

    //This method refreshes all hardware related to optical
    //channel layer.  It reads the current value of each Och layer
    //parameter an invokes the corresponding PII interface.
    //This action is normally invoked upon a change of the
    //region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    bool UpdateObject(unsigned theRunReason,uint32 theIndex);

private:
    uint32 GetWavelengthFromEvoa(uint32 theEvoa) const;

    TSPII_PipeRegion& myPipePiiRegion;
    ITS_ConfigRegion* myItsConfigRegion;

    unsigned int myPipePiiUnit;
    CT_Side mySide;

    T6100_CardIf* myCardContext;
    CFG_OchHistoryCfgRegion* myHistoryCfgRegion;
    CT_TEL_mBm myOchMaxAtten;
    CT_TEL_mBm myPrevGain[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool       myPrevActivePath[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    uint8      myPrevPortNumber[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    FC_BaseTimer myRefreshTimer;

    uint32 myHistorySize;

    // New booleans to handle the complexity of the HwRefresh action.
    // For example, the case when the Automatic Power Region is not ready
    // or any case in the future when the data should not be written to hardware.
    // These are defined to help TSPII determine what should be written to HW.
    bool myIsAutoPowerAdjReady;
    bool myIsAllDataValid;

    bool myEvoaWrittenFlag;
    bool myXcInfoWrittenFlag;

    bool myHasAnyEvoaChanged;
    bool myHasAnyXcInfoChanged;
};

#endif /* _CFG_HWREFRESHOCH_ */
