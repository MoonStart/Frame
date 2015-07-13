// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _INC_MON_OCHMAINUTUPDATESTATUSACTION
#define _INC_MON_OCHMAINUTUPDATESTATUSACTION

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include "Alarm/ALM_SoakingFailure.h"

class T6100_CardIf;
class FC_TimedProcess;

//This action handle the refresh of its Optical defect and status object.
class MON_OchMainUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor
	MON_OchMainUpdateStatusAction(MON_AppIf& theMonIf,
                                  MON_OtsOHDefectsRegion*    theOtsOHDefectsRegion=NULL,
                                  MON_OtsOchOHDefectsRegion* theOtsOchOHDefectsRegion=NULL);  

    //Virtual destructor of the class.
	virtual ~MON_OchMainUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason, uint32 theIndex);

private:

    MON_OtsOHDefectsRegion*    myOtsOHDefectsRegion;
    MON_OtsOchOHDefectsRegion* myOtsOchOHDefectsRegion; 
};

#endif /* _INC_MON_OCHMAINUTUPDATESTATUSACTION */
