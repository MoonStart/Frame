// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_DdltIf.h>
#include "../CFG_HwRefreshDdlt.h"
#include "../CFG_Dccl.h"
#include "../CFG_Ddlt.h"
#include "../CFG_Lprf.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

#include <T6100_MainAppIf.h>
#include <T6100_TelecomIf.h>


CFG_HwRefreshDdlt::CFG_HwRefreshDdlt(CFG_AppIf& theCfgIf,
                                     TSPII_DdltRegion& theDdltPiiRegion,
                                     CFG_AppIf* theLprfCfgApp,
                                     CFG_AppIf* theCfgDcclSectionApp,
                                     CFG_AppIf* theCfgDcclLineApp):

    CFG_HwRefreshAction(theCfgIf),
    myDdltPiiRegion(theDdltPiiRegion),
    myCfgDcclSectionApp(theCfgDcclSectionApp),
    myCfgDcclLineApp(theCfgDcclLineApp),
    myLprfCfgApp(theLprfCfgApp),
    myFirstRefreshAction(true)
{
    // Since there are up to 16 instances (one per slot) per application,
    // we won't have these input and output regions for now.
    // GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    // GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());

    if (myCfgDcclSectionApp)
    {
        GetBbAction()->AddInputRegion(myCfgDcclSectionApp->GetCfgRegion(),false);
    }

    if (myCfgDcclLineApp)
    {
        GetBbAction()->AddInputRegion(myCfgDcclLineApp->GetCfgRegion(),false);
    }

    if (myLprfCfgApp)
    {
        GetBbAction()->AddInputRegion(myLprfCfgApp->GetCfgRegion());
    }
}

CFG_HwRefreshDdlt::~CFG_HwRefreshDdlt()
{
    if (myCfgDcclSectionApp)
    {
        GetBbAction()->RemoveInputRegion(myCfgDcclSectionApp->GetCfgRegion());
    }

    if (myCfgDcclLineApp)
    {
        GetBbAction()->RemoveInputRegion(myCfgDcclLineApp->GetCfgRegion());
    }

    if (myLprfCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myLprfCfgApp->GetCfgRegion());
    }

    // Since there are up to 16 instances (one per slot) per application,
    // we won't have these input and output regions for now.
    // GetBbAction()->RemoveInputRegion(theCfgIf.GetCfgRegion());
    // GetBbAction()->RemoveOutputRegion(theCfgIf.GetOutputCfgRegion());

}

FC_Object* CFG_HwRefreshDdlt::Process(unsigned theRunReason,
                                      FC_Object* theInvokerObj,
                                      FC_Object* theParam)
{

    TSPII_DdltIf& aDdltPiiObject = myDdltPiiRegion[0];


    //Loop through twice for each instance of DCC Link on the card (first section, then line)
    int i;
    uint32 j;
    for( i = 0; i<=1; i++)  // index 0 is Section Dcc and index 1 is Line Dcc
    {
        CFG_Region* aDcclCfgRegion = NULL;
        //
        if (i == 0)
        {
            // Find Section Dcc Link Cfg Region
            if (myCfgDcclSectionApp)
            {
                aDcclCfgRegion = myCfgDcclSectionApp->GetCfgRegion();
            }
        }
        else
        {
            // Find Line Dcc Link Cfg Region
            if (myCfgDcclLineApp)
            {
                aDcclCfgRegion = myCfgDcclLineApp->GetCfgRegion();
            }
        }

        if (aDcclCfgRegion)
        {
            if (aDcclCfgRegion->IsValid())
            {
                //Iterate through region and configure
                for (j=0; j<aDcclCfgRegion->Size(); j++)
                {
                    CFG_Dccl& aCfgObject = static_cast<CFG_Dccl&>((*aDcclCfgRegion)[(bbindex_t)j]);

                    aDdltPiiObject.SetCommandSequence(CT_DCC_LINK_BEGIN);

                    aDdltPiiObject.SetIntfID(aCfgObject.GetIntfID());
                    aDdltPiiObject.SetIsProvisioned(aCfgObject.GetIsProvisioned());
                    aDdltPiiObject.SetLinkRouterID(aCfgObject.GetLinkRouterID());
                    aDdltPiiObject.SetRouterShelfID(aCfgObject.GetRouterShelfID());
                    aDdltPiiObject.SetProtocolLinkEnabled(aCfgObject.GetProtocolLinkEnabled());

                    if (myLprfCfgApp)
                    {
                        CT_Link_ProfileId aProfileId = aCfgObject.GetLinkProfileID();

                        // Make sure Profile ID is in range before accessing the region.
                        if (aProfileId < CT_DCC_MAX_LAPD_PROFILES)
                        {
                            CFG_Region* aLprfCfgRegion = myLprfCfgApp->GetCfgRegion();
                            CFG_Lprf&   aLprfCfgObject = static_cast<CFG_Lprf&>((*aLprfCfgRegion)[aProfileId]);;

                            aDdltPiiObject.SetTransferMode(aLprfCfgObject.GetTransferMode());
                            aDdltPiiObject.SetMaxFrameSize(aLprfCfgObject.GetMaxFrameSize());
                        }
                    }

                    aDdltPiiObject.SetFollowProtection(aCfgObject.GetFollowProtection());
                    aDdltPiiObject.SetChecksumEnabled(aCfgObject.GetChecksumEnabled());
                    aDdltPiiObject.SetHoldingTimerMultiplier(aCfgObject.GetHoldingTimerMultiplier());
                    aDdltPiiObject.SetConfigurationTimer(aCfgObject.GetConfigurationTimer());
                    aDdltPiiObject.SetHelloTimer(aCfgObject.GetHelloTimer());
                    aDdltPiiObject.SetDefaultMetric(aCfgObject.GetDefaultMetric());
                    aDdltPiiObject.SetReDirectHoldingTimer(aCfgObject.GetReDirectHoldingTimer());
                    aDdltPiiObject.SetLinkRoutingLevel(aCfgObject.GetLinkRoutingLevel());
                    aDdltPiiObject.SetESConfigurationTimer(aCfgObject.GetESConfigurationTimer());

                    aDdltPiiObject.SetCommandSequence(CT_DCC_LINK_COMMIT);
                }
            }
        }

    }  //  for( i = 0; i<=1; i++)  // index 0 is Section Dcc and index 1 is Line Dcc

    // Right now, no output region
    // GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}


