// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_T1E1If.h>
#include "../CFG_HwRefreshT1E1.h"
#include "../CFG_T1E1.h"
#include "../CFG_T1E1Automatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>


CFG_HwRefreshT1E1::CFG_HwRefreshT1E1(CFG_AppIf& theCfgIf,
                                     CFG_T1E1AutomaticCfgRegion* theAutomaticCfgRegion,
									 CFG_T1E1CfgRegion& theAltConfigRegion,
									 CFG_T1E1AutomaticCfgRegion* theAutoShutdownCfgRegion,
                                     TSPII_T1E1Region& theT1E1PiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
	myAltConfigRegion(theAltConfigRegion),
	myAutoShutdownCfgRegion(theAutoShutdownCfgRegion),
    myT1E1PiiRegion(theT1E1PiiRegion),
    myFirstRefreshAction(true)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion(), false);
	GetBbAction()->AddInputRegion(&myAltConfigRegion, false);
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
	if (myAutoShutdownCfgRegion) GetBbAction()->AddInputRegion(myAutoShutdownCfgRegion);
        GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshT1E1::~CFG_HwRefreshT1E1()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->RemoveInputRegion(&myAltConfigRegion);
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
	if (myAutoShutdownCfgRegion) GetBbAction()->RemoveInputRegion(myAutoShutdownCfgRegion);
        GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshT1E1::Process(unsigned theRunReason,
                                      FC_Object* theInvokerObj,
                                      FC_Object* theParam)
{

	CFG_T1E1& aCfgObject = static_cast<CFG_T1E1&>((*GetCfgIf().GetCfgRegion())[0]);
	CFG_T1E1& aAltCfgObject = static_cast<CFG_T1E1&>(myAltConfigRegion[0]);
   
    TSPII_T1E1If& aT1E1PiiObject = myT1E1PiiRegion[0];

    bool useAlternate = false;

	if (myAltConfigRegion.IsValid())
	{
		if (aAltCfgObject.GetT1E1Enable())
		{
			useAlternate = true;
		}
	}

	if (useAlternate)
	{
		bool aAutomaticDisqualifyRef = false;
		if (myAutoShutdownCfgRegion)
		{
            CFG_T1E1Automatic& aAutoShutCfgObject = (*myAutoShutdownCfgRegion)[0];
			// Get Disqualify Reference
            aAutomaticDisqualifyRef = aAutoShutCfgObject.GetDisqualifyRef();
		}
		// Turn off reference disqualification
        aT1E1PiiObject.SetClkDisqualifyRef(aAutomaticDisqualifyRef);
		// Set the timing source
		aT1E1PiiObject.SetTimingSource(aAltCfgObject.GetTimingSourceShelf(), aAltCfgObject.GetTimingSourceSlot());
	}
	else
	{
		if (GetCfgIf().GetCfgRegion()->IsValid())
		{
	
            bool aAutomaticDisqualifyRef = false;


            if (myAutomaticCfgRegion)
			{
                CFG_T1E1Automatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[0];

                // Get Disqualify Reference
                aAutomaticDisqualifyRef = aAutomaticCfgObject.GetDisqualifyRef();
			}

		    if (myAutoShutdownCfgRegion)
			{
                CFG_T1E1Automatic& aAutoShutCfgObject = (*myAutoShutdownCfgRegion)[0];
			    // Get Disqualify Reference
                aAutomaticDisqualifyRef |= aAutoShutCfgObject.GetDisqualifyRef();
			}

            // For now, use disqualify reference from automatic action
            aT1E1PiiObject.SetClkDisqualifyRef(aAutomaticDisqualifyRef);

            // Set line coding
            aT1E1PiiObject.SetLineCoding(aCfgObject.GetT1E1LineCoding());

            // Set framing type
            aT1E1PiiObject.SetFramingType(aCfgObject.GetT1E1FramingType());

            // Set the timing source
            aT1E1PiiObject.SetTimingSource(aCfgObject.GetTimingSourceShelf(), aCfgObject.GetTimingSourceSlot());

            // Set the SSM SaBit
            aT1E1PiiObject.SetSSMSaBit(aCfgObject.GetSABIT());
		}
	}


    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
	

