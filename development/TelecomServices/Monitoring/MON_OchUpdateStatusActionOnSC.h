// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef MON_OCHUPDATESTATUSACTIONONSC
#define MON_OCHUPDATESTATUSACTIONONSC

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include "MON_OchPower.h"

//This action handle the refresh of its Optical defect and status object.
class MON_OchUpdateStatusActionOnSC
: public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_OchUpdateStatusActionOnSC(MON_AppIf& theMonIf,
                              TSPII_PipeRegion* theTspiiPipeRegion, 
                              MON_OchAltStatusRegion* theAltOchRegion);

    //Virtual destructor of the class.
	virtual ~MON_OchUpdateStatusActionOnSC();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason, uint32 theIndex);//, const MON_OchPower& theMostPowerFullOfRegion);

private:

    static MON_OchPower GetMostPowerFullOfRegion(const MON_OchStatusRegion* theOchStatusRegion);
    TSPII_PipeRegion* myTspiiPipeRegion;
    MON_OchAltStatusRegion* myAltOchRegion;
};

#endif /* MON_OCHUPDATESTATUSACTIONONSC */
