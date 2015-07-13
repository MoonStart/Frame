// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_TXOPTONDEMANDACTION_
#define _MON_TXOPTONDEMANDACTION_

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class TSPII_OpticalIf;

//This action handle ondemand request of TX OPT layer.
class MON_TxOptOnDemandAction 
: public MON_UpdateStatusAction
{
public:
    //Constructor for .
    MON_TxOptOnDemandAction(MON_AppIf& theMonIf, 
                            TSPII_OpticalRegion& theOptPiiRegion);

    //Virtual destructor of the class.
    virtual ~MON_TxOptOnDemandAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:

    TSPII_OpticalRegion& myOptPiiRegion;

    MON_RequestID myRequestID;
};



#endif /* _MON_TXOPTONDEMANDACTION_ */
