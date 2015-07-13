// //Copyright(c) Tellabs Transport Group. All rights reserved.


#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_RMONUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_RMONUPDATESTATUSACTION_3C164A850173_INCLUDED


#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_RmonIf;

//This class is an action that reads the current state of the 
//RMON layer in the hardware and updates the RMON regions 
//accordingly.
//##ModelId=3C164A850173
class MON_RmonUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	//##ModelId=3C164B12000E
	MON_RmonUpdateStatusAction(MON_AppIf& theMonIf, 
                               TSPII_RmonRegion& theRmonPiiRegion,
                               MON_AppIf* theUpstreamLayerIf);

	//##ModelId=3C3B52F6018B
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	//##ModelId=3C164B12002C
	virtual ~MON_RmonUpdateStatusAction();

private:

    TSPII_RmonRegion& myRmonPiiRegion;

};



#endif /* _INC_MON_RMONUPDATESTATUSACTION_3C164A850173_INCLUDED */
