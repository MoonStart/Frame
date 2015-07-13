#ifndef __TSPII_VCGRESEQUENCEACTION_H
#define __TSPII_VCGRESEQUENCEACTION_H

/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM  : TSPII
 TARGET     :
 AUTHOR     : James Jackson
 DESCRIPTION: Hardware low-level configuration refresh action.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_Action.h>

//#include "TsPii/TSPII_VcgMemberMap.h"

class FC_TimedProcess;

class TSPII_VcgResequenceAction : public FC_Action
{
public:

    /* CONSTRUCTOR */        TSPII_VcgResequenceAction();
    virtual                  ~TSPII_VcgResequenceAction();
    virtual void             Run(FC_Object* theObject = NULL);
    virtual bool                     IsWakeUp() const;
    virtual void                     WakeUp();
    virtual void                     Suspend();

private:
    FC_TimedProcess *        myProcess;
//    TspiiVcgGroupMemberMap &    theVcgGroupMemberMapRef;  possibly restructure VCG class to separte member class object
};

#endif // __TSPII_VCGRESEQUENCEACTION_H
