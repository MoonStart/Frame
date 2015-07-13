/*-------------------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     September, 2008  Teresa Chen
    DESCRIPTION:   TSXC Stage Three Multicast Action Implementaion.
-------------------------------------------------------------------------------------*/
#include <XC/TSXC_S3McAction.h>
#include <XC/TSXC_BaseApplication.h>
#include <CommonTypes/CT_FabMulticast.h>
#include <TsPii/TSPII_SsmIf.h>
#include <TsPii/TSPII_FabIf.h>
#include <TsPii/TSPII_SubApplication.h>

//-------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------
TSXC_S3McAction::TSXC_S3McAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myS3McCfg_Region(NULL),
    myMiscConfig_Region(NULL)
{

}

//-------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------
TSXC_S3McAction::~TSXC_S3McAction()
{

}

//-------------------------------------------------------------------------------------
// Get Methods
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// Set Methods
//-------------------------------------------------------------------------------------
void TSXC_S3McAction::SetS3McCfgRegion(TSXC_S3McRegion<TSXC_S3MCast>*   theS3McCfgRegion)
{
    myS3McCfg_Region = theS3McCfgRegion;
}

void TSXC_S3McAction::SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion)
{
    myMiscConfig_Region = theMiscCfgRegion;
}

//-------------------------------------------------------------------------------------
// Do the work
//-------------------------------------------------------------------------------------
FC_Object* TSXC_S3McAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    bool                        ValidCardProvisioned;
    bool                        aCardInSwitchMode = false;
    CT_CardType                 aCardType;

    aCardType               = myS3McCfg_Region->GetMyCardType();
    ValidCardProvisioned    =  ( aCardType == CARD_TYPE_SSMX  || 
                                 aCardType == CARD_TYPE_SSMD  ||
                                 aCardType == CARD_TYPE_OSM40 || 
                                 aCardType == CARD_TYPE_SSM40 ||
                                 aCardType == CARD_TYPE_FGSM  ||
                                 aCardType == CARD_TYPE_OSM20 ||
                                 aCardType == CARD_TYPE_OSM2S ||
                                 aCardType == CARD_TYPE_OSM2C ||
                                 aCardType == CARD_TYPE_OSM1S );
    

    if (myMiscConfig_Region != NULL)
    {
        aCardInSwitchMode = (*myMiscConfig_Region)[0].IsSwitchMode();
    }

    // No MiscConfig Region for OSM2C/S
    if (aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C || aCardType == CARD_TYPE_OSM1S)
    {
        aCardInSwitchMode = true;
    }
    
    if (aCardInSwitchMode && ValidCardProvisioned)
    {
        TSXC_S3MCast*     MC_CfgObjectPtr;
        CT_FabMcMember    aFabMember;
        int               idx;
        uint16            mcastId;
        int               maxMcastRegionIdx = (*myS3McCfg_Region).Size();
        uint8             dst;
        CT_FAC_StsMap     dstMap;
        TSPII_FabIf&      tspiiFabIf = (*(TSPII_SubApplication::GetInstance()->GetFab()))[0];

        // Set start time 
        START_TIME(TSXC_DEBUG_LEVEL01);

        // Delete all Mc Groups.  Will add necessary ones below.
        tspiiFabIf.DeleteAllMcGroups();

        for (idx = 0; idx < maxMcastRegionIdx; idx++)
        {
            MC_CfgObjectPtr = &((*myS3McCfg_Region)[idx]);

            if (MC_CfgObjectPtr && MC_CfgObjectPtr->IsMcastIdSet())
            {
                vector<CT_FabMcMember> aFabMemberList;

                mcastId             = MC_CfgObjectPtr->GetMCastId();
                dst                 = MC_CfgObjectPtr->GetDestination();

                aFabMember.RemShelf = 0;        // Unused for S3Mcast
                aFabMember.RemSlot  = 0;        // Unused for S3Mcast

                //
                // Following cards have two S3 Mcast destinations:
                //   IMUXL - 0
                //   IMUXP - 1
                //
                if ( (aCardType == CARD_TYPE_SSMX) ||
                     (aCardType == CARD_TYPE_SSMD) )
                {
                    if (dst & CT_XC_S3MC_IMUXL_BIT)
                    {
                        aFabMember.RemImux = 0;
                        aFabMemberList.push_back(aFabMember);
                    }

                    if (dst & CT_XC_S3MC_IMUXP_BIT)
                    {
                        aFabMember.RemImux = 1;
                        aFabMemberList.push_back(aFabMember);
                    }
                }

                //
                // Following cards have four S3 Mcast destinations:
                //   IMUXL  - 0
                //   IMUXL1 - 1
                //   IMUXP  - 2
                //   IMUXP1 - 3
                //
                else if ( (aCardType == CARD_TYPE_OSM40) ||
                          (aCardType == CARD_TYPE_SSM40) )
                {
                    if (dst & CT_XC_S3MC_IMUXL_BIT)
                    {
                        aFabMember.RemImux = 0;
                        aFabMemberList.push_back(aFabMember);
                    }

                    if (dst & CT_XC_S3MC_IMUXL1_BIT)
                    {
                        aFabMember.RemImux = 1;
                        aFabMemberList.push_back(aFabMember);
                    }

                    if (dst & CT_XC_S3MC_IMUXP_BIT)
                    {
                        aFabMember.RemImux = 2;
                        aFabMemberList.push_back(aFabMember);
                    }

                    if (dst & CT_XC_S3MC_IMUXP1_BIT)
                    {
                        aFabMember.RemImux = 3;
                        aFabMemberList.push_back(aFabMember);
                    }
                }

                else if (aCardType == CARD_TYPE_FGSM  || 
                         aCardType == CARD_TYPE_OSM20)
                {
                    if (dst & CT_XC_S3MC_IMUXL_BIT)
                    {
                        aFabMember.RemImux = 0;
                        aFabMemberList.push_back(aFabMember);
                    }
                }

                else if(aCardType == CARD_TYPE_OSM2S ||
                        aCardType == CARD_TYPE_OSM2C ||
                        aCardType == CARD_TYPE_OSM1S)
                {
                    MC_CfgObjectPtr->GetDestinationMap(dstMap);

                    int maxChan = 0;
                    if(aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C)
                    {
                        maxChan = XC_MAX_XC_OSM_ODUXC_IMUX * XC_MAX_OSM_ODUXC_IMUX_INTF;
                    }
                    else if(aCardType == CARD_TYPE_OSM1S)
                    {
                        maxChan = XC_MAX_OSM1S_ODUXC_IMUX * XC_MAX_OSM1S_ODUXC_IMUX_INTF;
                    }

                    for(int aChan = 0; aChan < maxChan; aChan++)
                    {
                        if (dstMap.IsInUse(aChan))
                        {
                            aFabMember.RemImux = aChan;
                            aFabMemberList.push_back(aFabMember);
                        }
                    }
                }

                tspiiFabIf.SetMcGroup( mcastId, aFabMemberList );
            }
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage three MCAST provision time : ");

        START_TIME(TSXC_DEBUG_LEVEL01);

        tspiiFabIf.CommitMcGroups();

        Respond(myS3McCfg_Region->GetCQMRequest());

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage three MCAST commit time : ");        
    }
 
    return NULL;
}
