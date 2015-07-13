// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OTSAUTOMATICACTION_
#define _CFG_OTSAUTOMATICACTION_

#include "CFG_HwRefreshAction.h"
#include "Monitoring/MON_Definitions.h"
#include "CSM/CSM_CardStatusRegion.h"
#include "ITS/ITS_Definitions.h"



class T6100_CardIf;
class MON_AppIf;

//This action handle the refresh of transmitted indication over the OTS
class CFG_OtsAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor for .
	CFG_OtsAutomaticAction(CFG_AppIf& aCfgApp,
                           MON_RsDefectsRegion& theMonRsDefectsRegion,
                           MON_OtsOHDefectsRegion& theMonOtsOHDefectsRegion,
                           MON_OmsDefectsRegion& theMonOmsSourceDefectsRegion,
                           MON_OmsDefectsRegion& theMonOmsDestDefectsRegion,
                           MON_OchDefectsRegion& theMonOchOutputDefectsRegion,
						   ITS_ConfigRegion& theItsConfigRegion,
                           MON_RsDefectsRegion* theOtherSideMonRsDefectsRegion = NULL,
                           MON_OmsDefectsRegion* theOtherSideMonOmsDefectsRegion = NULL,
                           MON_OtsOHDefectsRegion* theOtherSideMonOtsOHDefectsRegion = NULL);

    //Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~CFG_OtsAutomaticAction();
    void UpdateObject(unsigned theRunReason);

private:
    MON_RsDefectsRegion& myMonRsDefectsRegion;
    MON_OtsOHDefectsRegion& myMonOtsOHDefectsRegion;
    MON_OmsDefectsRegion& myMonOmsSourceDefectsRegion;
    MON_OmsDefectsRegion& myMonOmsDestDefectsRegion;
    MON_OchDefectsRegion& myMonOchOutputDefectsRegion;
    MON_RsDefectsRegion* myOtherSideMonRsDefectsRegion;
    MON_OmsDefectsRegion* myOtherSideMonOmsDefectsRegion;
    MON_OtsOHDefectsRegion* myOtherSideMonOtsOHDefectsRegion;
	ITS_ConfigRegion&          myItsConfigRegion;
};



#endif /* _CFG_OTSAUTOMATICACTION_ */
