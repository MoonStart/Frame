// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_OMSUPDATESTATUSACTIONONSC_
#define _MON_OMSUPDATESTATUSACTIONONSC_

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>

class T6100_CardIf;

//This action handle the refresh of its OMS defect and status object.
class MON_OmsUpdateStatusActionOnSC
: public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_OmsUpdateStatusActionOnSC(MON_AppIf& theMonIf, 
                              TSPII_PipeRegion& thePipePiiRegion);
                              
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~MON_OmsUpdateStatusActionOnSC();

private:
    
    TSPII_PipeRegion& myPipePiiRegion;

    uint32 myPiiOmsLosCount;
    uint32 myPiiOmsAltLosCount;
    uint32 myPiiOmsOutputPowerLimitedCount;
};



#endif /* _MON_OMSUPDATESTATUSACTIONONSC_ */
