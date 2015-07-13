// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SlotClockUsageApplyAction.h"
#include "../SP_Definitions.h"
#include "../SP_Utilities.h"
#include <Blackboard/FC_BbAction.h>
#include <SignalProtection/SP_TimingModeRegion.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_MsIf.h>
#include <CsPii/CSPII_CardIF.h>



///////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_SlotClockUsageApplyAction::SP_SlotClockUsageApplyAction(SP_TimingModeRegion& theTimingModeRegion):
	myTimingModeRegion(theTimingModeRegion)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(&myTimingModeRegion);
}

//##ModelId=38EDF51800A6
SP_SlotClockUsageApplyAction::~SP_SlotClockUsageApplyAction()
{
	myBbAction->RemoveInputRegion(&myTimingModeRegion);
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_SlotClockUsageApplyAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_SlotClockUsageApplyAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{

	CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
	TSPII_MsRegion*   thePiiMsRegion = NULL;
	unsigned int tspiiIntf;
    for (uint16 i=0; i<myTimingModeRegion.Size();i++)
    {
        CT_TEL_ClkMode theTimingMode = myTimingModeRegion[i].GetTimingMode();

		tspiiIntf = GetTspiiIntfFromSlotId(aCardType, (CT_SlotId)i+1);
		if (tspiiIntf != 0xFF)
		{
            thePiiMsRegion = TSPII_SubApplication::GetInstance()->GetMs(tspiiIntf);
			if (theTimingMode == CT_TEL_CLKMODE_MASTER)
            {
				(*thePiiMsRegion)[0].SetInputReferenceMapping(INPUT_UNFILTERED);
			}
			else if (theTimingMode == CT_TEL_CLKMODE_SLAVE)
			{
				(*thePiiMsRegion)[0].SetInputReferenceMapping(INPUT_SETS_CLK);
			}
            else if (theTimingMode == CT_TEL_CLKMODE_HOLDOVER)
            {
                (*thePiiMsRegion)[0].SetInputReferenceMapping(INPUT_MATE);
            }
		}
    }
		
	return NULL;
}