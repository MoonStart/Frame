// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _INC_MON_OSCUTUPDATESTATUSACTION
#define _INC_MON_OSCUTUPDATESTATUSACTION

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include "MON_OchPower.h"

class MON_PilotToneControllerRequest;
class CSM_CardStatusRegion;

//This action handle the refresh of its Optical defect and status object.
class MON_OchUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_OchUpdateStatusAction(MON_AppIf& theMonIf,
                              TSPII_PilotToneRegion* theTspiiRegion,
                              TSPII_PipeRegion* theTspiiPipeRegion, 
                              MON_OchAltStatusRegion* theAltOchRegion,
                              MON_OchStatusRegion* theRawOchStatusRegion,
                              MON_OchStatusRegion* theAmpOchStatusRegion=NULL,
                              MON_OmsStatusRegion* theAmpOmsStatusRegion=NULL,
                              MON_OchStatusRegion* theInterferingStatusRegion=NULL,
                              MON_AppIf* theOmsLayerIf=NULL);  

    //Virtual destructor of the class.
	virtual ~MON_OchUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason, uint32 theIndex, const MON_OchPower& theMostPowerFullOfRegion);

private:

    static MON_OchPower GetMostPowerFullOfRegion(const MON_OchStatusRegion* theOchStatusRegion);
	static uint32 theirRequestId;
    bool myRegistrationDone;
    MON_PilotToneControllerRequest* myRequest;
    CSM_CardStatusRegion* myCSMRegion;
    TSPII_PipeRegion* myTspiiPipeRegion;

    MON_OchStatusRegion* myAmpOchStatusRegion;
    MON_OchAltStatusRegion* myAltOchRegion;
    MON_OmsStatusRegion* myAmpOmsStatusRegion;
    MON_OmsStatusRegion* myOlimOmsStatusRegion;
    MON_OchStatusRegion* myInterferingStatusRegion;
    MON_OchStatusRegion* myRawOchStatusRegion;

    MON_AppIf* myOmsLayerIf;
};

#endif /* _INC_MON_OSCUTUPDATESTATUSACTION */
