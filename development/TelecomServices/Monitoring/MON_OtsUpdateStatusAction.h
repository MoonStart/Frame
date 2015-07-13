// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_OTSUPDATESTATUSACTION_
#define _MON_OTSUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include <TsPii/TSPII_Region.h>

class TSPII_OtsOHIf;
class TSPII_OmsOHIf;

//This action handle the refresh of its OTS defect and status object.
class MON_OtsUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_OtsUpdateStatusAction(MON_AppIf& theMonIf,
                              MON_AppIf& theUpstreamLayerIf,
                              MON_OmsDefectsRegion& theOmsDefectsRegion,
                              TSPII_OtsOHRegion& theOtsPiiRegion,
                              TSPII_OmsOHRegion* theOmsPiiRegion,
                              MON_OtsOHDefectsRegion& theOtsOHDefectsRegion);

    //Virtual destructor of the class.
	virtual ~MON_OtsUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason);

private:

    MON_AppIf& myUpstreamLayerIf;

    TSPII_OtsOHRegion& myOtsPiiRegion;
    TSPII_OmsOHRegion* myOmsPiiRegion;
    MON_OmsDefectsRegion& myOmsDefectsRegion;
    MON_OtsOHDefectsRegion& myOtsOHDefectsRegion;
    
    //Counters used to debounce Trace modification
    uint32 myGoodTraceMessageCounter;
    uint32 myBadTraceMessageCounter;

	//Local counts of defects read on PII
    uint32 myPiiOtsBDIPCount;
    uint32 myPiiOtsBDIOCount;
    uint32 myPiiOtsPMICount;
    uint32 myPiiOmsFDIPCount;
    uint32 myPiiOmsFDIOCount;
    uint32 myPiiOmsPMICount;

};



#endif /* _INC_MON_OTSUPDATESTATUSACTION */
