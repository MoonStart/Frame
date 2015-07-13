// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_OTSOCHOHUPDATESTATUSACTION_
#define _MON_OTSOCHOHUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include <TsPii/TSPII_Region.h>

class TSPII_OchOHIf;

//This action handle the refresh of its OTS defect and status object.
class MON_OtsOchOHUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_OtsOchOHUpdateStatusAction(MON_AppIf& theMonIf,
                                   MON_AppIf& theUpstreamLayerIf,
                                   TSPII_OchOHRegion& theOchOHPiiRegion,
                                   MON_OtsOchOHDefectsRegion& theDefectsRegion);

    //Virtual destructor of the class.
	virtual ~MON_OtsOchOHUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason, uint8 theIndex);

private:

    TSPII_OchOHRegion& myOchOHPiiRegion;

    MON_OtsOchOHDefectsRegion& myDefectsRegion;

    //Local counts of defects read on PII
    uint32 myPiiOchFDIPCount[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    uint32 myPiiOchFDIOCount[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    uint32 myPiiOchOCICount[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
};

#endif /* _MON_OTSOCHOHUPDATESTATUSACTION_ */
