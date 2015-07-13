// Copyright(c) Tellabs Transport Group. All rights reserved.
#ifndef _INC_TSXC_SRCSTATUSACTION_INCLUDED
#define _INC_TSXC_SRCSTATUSACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>

class FC_BoolRegion;

//------------------------------------------------------------------------------
// This class is responsible for updating source connection status
//------------------------------------------------------------------------------
class TSXC_SrcStatusAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_SrcStatusAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_SrcStatusAction();

    //-------------------------------------------------------------------------- 
    // This method causes this object to execute its main function.
    //-------------------------------------------------------------------------- 
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    //-------------------------------------------------------------------------- 
    // Set Methods
    //-------------------------------------------------------------------------- 
    void SetSrcStatusRegion(FC_BoolRegion* theSrcStatusRegion);

private:
    FC_BoolRegion*           mySrcStatusRegion;
};

#endif /* _INC_TSXC_SRCSTATUSACTION_INCLUDED */
