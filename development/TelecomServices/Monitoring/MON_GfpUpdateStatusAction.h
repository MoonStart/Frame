// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_GFPUPDATESTATUSACTION_3C164A850173_INCLUDED
#define _INC_MON_GFPUPDATESTATUSACTION_3C164A850173_INCLUDED

#include "MON_UpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_GfpIf;

//This class is an action that reads the current state of the 
//GFP layer in the hardware and updates the GFP regions 
//accordingly.
class MON_GfpUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_GfpUpdateStatusAction(MON_AppIf& theMonIf, 
                              TSPII_GfpRegion& theGfpPiiRegion,
                              MON_AppIf* theUpstreamLayerIf,
                              uint8 theNumGfps);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Virtual destructor of the class.
	virtual ~MON_GfpUpdateStatusAction();

    virtual bool GetInternalRealTimeDefects(uint16 index, uint8 facNumber, CT_TEL_Defect theDefect);
    virtual bool GetExternalRealTimeDefects(uint16 index, uint8 facNumber, CT_TEL_Defect theDefect);

private:

    TSPII_GfpRegion& myGfpPiiRegion;

    uint16 myNumGfps;
    uint16 myNextGfp;
    uint16 myNbrGfp2Check;

    bool myFirstPassFlag;

	//Local counts of defects read on PII
#ifndef PSOSP
    vector<uint32> myPiiLOFDCount;
    vector<uint32> myPiiCsfLosCount;
    vector<uint32> myPiiCsfLosyncCount;
    vector<uint32> myPiiVirtualLOFDCount;
    vector<uint32> myPiiCsfFdiCount;
    vector<uint32> myPiiCsfRdiCount;
    vector<uint32> myPiiCsfRFLinkFailCount;
    vector<uint32> myPiiCsfRFOfflineCount;
    vector<uint32> myPiiCsfRFAutoNegFailCount;
    vector<uint32> myPiiLocalAutoNegFailCount;
    vector<uint32> myPiiCsfLinkFailRxCount;
    vector<uint32> myPiiRFLinkFailCount;
    vector<uint32> myPiiRFOfflineCount;
    vector<uint32> myPiiRFAutoNegFailCount;
    vector<uint32> myPiiLinkFailRxCount;
    vector<uint32> myPiiFefiCount;
    vector<uint32> myPiiCsfFefiCount;
    vector<uint32> myPiiPLMCount;
    vector<uint32> myPiiLosAlignCount;
    vector<uint32> myPiiSeqMisMatchCount;
    vector<uint32> myPiiCoreHecCount;
    vector<uint32> myPiiPliCount;
#else
    uint32 myPiiLOFDCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfLosCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfLosyncCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiVirtualLOFDCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfFdiCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfRdiCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfRFLinkFailCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfRFOfflineCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfRFAutoNegFailCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiLocalAutoNegFailCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfLinkFailRxCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiRFLinkFailCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiRFOfflineCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiRFAutoNegFailCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiLinkFailRxCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiFefiCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCsfFefiCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiPLMCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiLosAlignCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiSeqMisMatchCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiCoreHecCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiPliCount[CT_TEL_NBR_OF_VCGS];
#endif
};



#endif /* _INC_MON_GFPUPDATESTATUSACTION_3C164A850173_INCLUDED */
