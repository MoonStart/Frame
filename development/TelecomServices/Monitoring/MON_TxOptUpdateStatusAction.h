// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_TXOPTUPDATESTATUSACTION_
#define _MON_TXOPTUPDATESTATUSACTION_

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class TSPII_OpticalIf;

//This action handle the refresh of its Optical defect and 
//status object.
class MON_TxOptUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_TxOptUpdateStatusAction(MON_AppIf& theMonIf, 
                                TSPII_OpticalRegion& theOptPiiRegion);

    //Virtual destructor of the class.
	virtual ~MON_TxOptUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);


    void UpdateObject(unsigned theRunReason,
                      TSPII_OpticalIf& theOptPii);

private:

    TSPII_OpticalRegion& myOptPiiRegion;

    uint32 myCount;
    uint32 myPassesPerFiveSecs;
};



#endif /* _MON_TXOPTUPDATESTATUSACTION_ */
