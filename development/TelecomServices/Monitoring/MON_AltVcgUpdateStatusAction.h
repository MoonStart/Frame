// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_ALTVCGUPDATESTATUSACTION
#define _INC_MON_ALTVCGUPDATESTATUSACTION

#include "MON_UpdateStatusAction.h"

#include <TsPii/TSPII_Region.h>


// Forward declaration of class.
class TSPII_VcgIf;

// This class is an action that reads the current state of the 
// Alt (SSM) VCG layer in the hardware and updates the VCG regions 
// accordingly.
class MON_AltVcgUpdateStatusAction : public MON_UpdateStatusAction
{
public:

	// Constructor.
	MON_AltVcgUpdateStatusAction(MON_AppIf& theMonIf, 
                                 uint16 theMaxVcgs,
                                 uint16 theNbrVcgs2Check,
                                 TSPII_VcgRegion& theVcgPiiRegion);

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	// Virtual destructor of the class.
	virtual ~MON_AltVcgUpdateStatusAction();

private:
 
    TSPII_VcgRegion& myVcgPiiRegion;

    uint16 myMaxVcgs;
    uint16 myNextVcg;
    uint16 myNbrVcgs2Check;

    bool myFirstPassFlag;

    //Local counts of defects read on PII
#ifndef PSOSP
    vector<uint32> myPiiTX_TLCCount;
    vector<uint32> myPiiTX_PLCCount;
    vector<uint32> myPiiRX_TLCCount;
    vector<uint32> myPiiRX_PLCCount;
    vector<uint32> myPiiLOS_AlignCount;
    vector<uint32> myPiiTX_FOPCount;
    vector<uint32> myPiiRX_FOPCount;
#else
    uint32 myPiiTX_TLCCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiTX_PLCCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiRX_TLCCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiRX_PLCCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiLOS_AlignCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiTX_FOPCount[CT_TEL_NBR_OF_VCGS];
    uint32 myPiiRX_FOPCount[CT_TEL_NBR_OF_VCGS];
#endif

};



#endif /* _INC_MON_ALTVCGUPDATESTATUSACTION */
