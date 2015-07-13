// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OTSAUTOMATICTXPWRSHUTACTION_
#define _CFG_OTSAUTOMATICTXPWRSHUTACTION_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"


// Forward declaration of class.
class ALM_AppIf;
class CFG_AtpsFsm;
class FC_Stream;

//This class is an action that automatically performs
//automatic TX power shutdown on the OTS layer (ATPS).
class CFG_OtsAutomaticTxPwrShutAction 
: public CFG_HwRefreshAction
{
    friend class CFG_AtpsFsm;
public:
    //Constructor.
    CFG_OtsAutomaticTxPwrShutAction(CFG_AppIf& theCfgIf,
                                    CFG_OtsAutomaticTxPwrShutRegion& theAutomaticTxPwrShutRegion,
                                    ALM_AppIf& theOtsOHAlmIf,
                                    ALM_AppIf& theOtsAlmIf);

    //Virtual destructor of the class.
    virtual ~CFG_OtsAutomaticTxPwrShutAction();


    //Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    virtual void Display(FC_Stream& theStream);

private:
    
    // ATPS finite state machine
    CFG_AtpsFsm* myAtpsFsm;

    // Output Region
    CFG_OtsAutomaticTxPwrShutRegion& myAutomaticTxPwrShutRegion;

    //Reference to alarm applications
    ALM_AppIf& myOtsOHAlmIf;
    ALM_AppIf& myOtsAlmIf;
};



#endif /* _CFG_OTSAUTOMATICTXPWRSHUTACTION_ */
