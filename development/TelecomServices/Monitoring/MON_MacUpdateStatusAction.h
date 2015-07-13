// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _MON_MACUPDATESTATUSACTION_
#define _MON_MACUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_MacIf;

//This class is an action that reads the current state of the 
//Mac layer in the hardware and updates the Mac regions 
//accordingly.
class MON_MacUpdateStatusAction : public MON_UpdateStatusAction
{
public:
    //Constructor.
    MON_MacUpdateStatusAction(MON_AppIf& theMonIf,
                              TSPII_MacRegion& theMacPiiRegion);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    //Virtual destructor of the class.
    virtual ~MON_MacUpdateStatusAction();

private:

    TSPII_MacRegion& myMacPiiRegion;
    uint8            myMacThrottle;
    //Local counts of defects read on PII
    uint32 myPiiRFLinkFailCount;
    uint32 myPiiFefiCount;
    //uint32 myPiiLacpFailCount;
    bool   myLastLacpFail;
};



#endif /* _MON_MACRUPDATESTATUSACTION_ */
