// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_OMSUPDATESTATUSACTION_
#define _MON_OMSUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>

class T6100_CardIf;

//This action handle the refresh of its OMS defect and status object.
class MON_OmsUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_OmsUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_PipeRegion& thePipePiiRegion,
                              TSPII_OpticalRegion* thePump1Region,
                              TSPII_OpticalRegion* thePump2Region,
                              bool theHasAmplifierFlag = true);
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~MON_OmsUpdateStatusAction();

private:
    
    TSPII_PipeRegion& myPipePiiRegion;
    TSPII_OpticalRegion* myPump1Region;
    TSPII_OpticalRegion* myPump2Region;

    uint32 myPiiOmsLosCount;
    uint32 myPiiOmsAltLosCount;
    uint32 myPiiOmsAltTwoLosCount;
    uint32 myPiiOmsAltThreeLosCount;
    uint32 myPiiOmsOutputPowerLimitedCount;

    bool myHasAmplifierFlag;
};



#endif /* _MON_OMSUPDATESTATUSACTION_ */
