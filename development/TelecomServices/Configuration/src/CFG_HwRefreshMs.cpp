// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_MsIf.h>
#include "../CFG_HwRefreshMs.h"
#include "../CFG_Ms.h"
#include "../CFG_MsAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_FacilityIds.h>


CFG_HwRefreshMs::CFG_HwRefreshMs(CFG_AppIf& theCfgIf,
                                 CFG_MsAutomaticCfgRegion* theAutomaticCfgRegion,
                                 TSPII_MsRegion& theMsPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myMsPiiRegion(theMsPiiRegion)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}


CFG_HwRefreshMs::~CFG_HwRefreshMs()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshMs::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Ms& aCfgObject = static_cast<CFG_Ms&>((*GetCfgIf().GetCfgRegion())[0]);
    TSPII_MsIf& aMsPiiObject = myMsPiiRegion[0];
	
    // Note:  the transmitted K1 and K2 byte values are sent down to 
    //        TSPII in the MsProtAction.



    bool         anActiveRef              = false;
    CT_FAC_RxSsm aAutomaticSelectedRefSSM = CT_TEL_SUPPORTED_DEFAULT_SSM;

    if (myAutomaticCfgRegion)
    {
       CFG_MsAutomatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[0];

       // Get whether this reference is Active Reference (true if it is)
       anActiveRef = aAutomaticCfgObject.GetIsActiveRef();

       // Get Selected Reference SSM
       aAutomaticSelectedRefSSM = aAutomaticCfgObject.GetSelectedRefSSM();
    }

    // Set Timing Reference, if allowed to do so
    // If auto timing redundancy is provisioned, then user
    // provisioned ref type does not apply.
    if (aCfgObject.GetIsAutoTimingRedProv() == false)
    {
        aMsPiiObject.SetAsTimingRef(aCfgObject.GetRefType());
    }


    // Set First Timeslot
    aMsPiiObject.SetFirstTimeslot(aCfgObject.GetFirstTimeslot());

	//Set Derived Source Mode
    aMsPiiObject.SetDerivedTimingSourceMode(aCfgObject.GetDerivedTimingSourceMode());


    // Set Transmit SSM to not supported value 
    // Note: this is also sent out when the selected refected is the refernece transmitting the SSM
    //       (see code below)
    CT_FAC_RxSsm aTxSsm = CT_TEL_NOT_SUPPORTED_SSM;

    // Set Tx SSM Value
    if (aCfgObject.GetTxSsmForce())
    {
        aTxSsm = aCfgObject.GetTxSsm();
    }
    else if ((aCfgObject.GetSsmSupported()) && (!(anActiveRef)))
    {
        aTxSsm = aAutomaticSelectedRefSSM;
    }
    aMsPiiObject.SetTxSsm(aTxSsm);


    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
	

