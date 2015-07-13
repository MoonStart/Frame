/*-------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage One Route Action Implementaion.
-------------------------------------------------------------*/
#include <XC/TSXC_S1RtAction.h>
#include <XC/TSXC_BaseApplication.h>
#include <CommonTypes/CT_FabMulticast.h>
#include <TsPii/TSPII_SsmIf.h>
#include <TsPii/TSPII_FabIf.h>
#include <TsPii/TSPII_SubApplication.h>

//---------------------------------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------------------------------
TSXC_S1RtAction::TSXC_S1RtAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myS1RtCfg_Region(NULL),
    myXCMCastFilter_Region(NULL),        
    myMiscConfig_Region(NULL),
    mySPReady_Regions(NULL) 
{
}

//---------------------------------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------------------------------
TSXC_S1RtAction::~TSXC_S1RtAction()
{
}

//---------------------------------------------------------------------------------------------------------
// Get Methods
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
// Set Methods
//---------------------------------------------------------------------------------------------------------
void TSXC_S1RtAction::SetS1RtCfgRegion(TSXC_S1RtRegion<TSXC_S1Route>* theS1RtCfgRegion)
{
    myS1RtCfg_Region = theS1RtCfgRegion;
}

void TSXC_S1RtAction::SetMCFilterRegion(TSXC_MCastFilterRegion<TSXC_MCastFilter>* theMCFilterRegion)
{
    myXCMCastFilter_Region = theMCFilterRegion;
}

void TSXC_S1RtAction::SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion)
{
    myMiscConfig_Region = theMiscCfgRegion;
}

void TSXC_S1RtAction::SetSPReady_Regions(vector<TEL_BbRegionBaseImp<SP_ApplicationStatus>*> * theSPReady_Regions)
{
    mySPReady_Regions = theSPReady_Regions;
}

//---------------------------------------------------------------------------------------------------------
// Do the work
//---------------------------------------------------------------------------------------------------------
FC_Object* TSXC_S1RtAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    bool                        ValidCardProvisioned;
    bool                        aCardInSwitchMode = false;
    CT_CardType                 aCardType;

    aCardType            = myS1RtCfg_Region->GetMyCardType();
    ValidCardProvisioned =  ( aCardType == CARD_TYPE_SSMX  || 
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
        aCardInSwitchMode = ((*myMiscConfig_Region)[0].GetSwitchMode() != CT_TEL_SwitchMode_None);
    }

    // No MiscConfig Region for OSM2C/S
    if ( aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C || aCardType == CARD_TYPE_OSM1S )
    {
        aCardInSwitchMode = true;
    }
        
    //
    // Check if Signal Protect is ready.  If not, XC MCast Action
    // cannot run since source activation information and signal protect
    // configuration information is not yet available.
    //
    bool SPReady = true;
    if (mySPReady_Regions != NULL)
    {
        for (int i = 0; i < int((*mySPReady_Regions).size()); i++)
        {
            if (!((*(*mySPReady_Regions)[i])[0].IsReady()))
                SPReady = false;
        }
    }

    if (aCardInSwitchMode && ValidCardProvisioned && SPReady) 
    {
        TSXC_S1Route*     RT_CfgObjectPtr = NULL;
        TSXC_MCastFilter* MC_FilterObjectPtr = NULL;
        TSPII_FabIf&      tspiiFabIf = (*(TSPII_SubApplication::GetInstance()->GetFab()))[0];

        int         maxRouteRegionIdx = myS1RtCfg_Region->Size();
        uint16      aMCastId;    
        uint8       aDstShelf;  
        uint8       aDstSlot;   
        uint8       aDstSlice;  
        CT_CardType aDstCardType;
        uint16      aConnId;
           
        // set start time if debug level was set.
        START_TIME(TSXC_DEBUG_LEVEL01);

        tspiiFabIf.DeleteAllEdgeIngressXconns();
        for (uint16 aSrcSts = 0; aSrcSts < maxRouteRegionIdx; aSrcSts++)
        {
            RT_CfgObjectPtr = &((*myS1RtCfg_Region)[aSrcSts]);

            if (RT_CfgObjectPtr->IsDstSet())
            {
                aConnId = RT_CfgObjectPtr->GetConnId();
                aMCastId = RT_CfgObjectPtr->GetMCastId(CT_XC_MAPPING_FIXED);
                if(myXCMCastFilter_Region != NULL)
                {
                    MC_FilterObjectPtr = &((*myXCMCastFilter_Region)[aSrcSts]);
                    aMCastId           = RT_CfgObjectPtr->GetMCastId(MC_FilterObjectPtr->GetMCastTypeToUse());
                }

                // If this is a multicast connection, set multicast info
                if (aMCastId != XC_MCASTID_UNKNOWN)
                {
                    tspiiFabIf.AddEdgeIngressXconn(aSrcSts,
                                                   true,               // True for Mcast
                                                   aMCastId, 
                                                   0,                  // DstInfo (n/a for mcast)
                                                   0,                  // DstInfo (n/a for mcast)
                                                   0,                  // DstInfo (n/a for mcast)
                                                   aConnId,
                                                   false,              // No bypass
                                                   CARD_TYPE_UNKNOWN); // DstInfo (n/a for mcast)
                }

                // Else this is a unicast connection, so set unicast info
                else    
                {
                    aDstShelf = 0;
                    if (myMiscConfig_Region)
                    {
                        aDstShelf = PhysToLogicalShelf(
                                      RT_CfgObjectPtr->GetDstShelf(),                   // PhysicalShelf (1-based)
                                      (*myMiscConfig_Region)[0].GetSwitchMode(),        // switchMode
                                      (*myMiscConfig_Region)[0].GetSwitchDomainMode()); //Switch Domain Mode
                    }
                    aDstSlot     = RT_CfgObjectPtr->GetDstSlot() - 1;
                    aDstSlice    = RT_CfgObjectPtr->GetDstSlice();
                    aDstCardType = (CT_CardType) RT_CfgObjectPtr->GetDstCardType();
                    tspiiFabIf.AddEdgeIngressXconn(aSrcSts, 
                                                   false,          // False for unicast
                                                   0,              // McastId (n/a for unicast)
                                                   aDstShelf, 
                                                   aDstSlot, 
                                                   aDstSlice,
                                                   aConnId,
                                                   false,          // No bypass
                                                   aDstCardType);
                }
            }
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage one route provision time : ");

        START_TIME(TSXC_DEBUG_LEVEL01);

        tspiiFabIf.CommitEdgeIngressXconns();

        Respond(myS1RtCfg_Region->GetCQMRequest());

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage one route commit time : ");
    } 

    return NULL;
}

//---------------------------------------------------------------------------------------------------------
//--- Signal protection uses the following method to quickly change one entry in the hardware
//---------------------------------------------------------------------------------------------------------
void TSXC_S1RtAction::ApplyCesIngress(UINT16 theIndex)
{
    TSXC_MCastFilter*   MC_FilterObjectPtr = NULL;
    TSXC_S1Route*       RT_CfgObjectPtr    = NULL;    
    if (theIndex < myS1RtCfg_Region->Size())
    {
        MC_FilterObjectPtr  = &((*myXCMCastFilter_Region)[theIndex]);
        RT_CfgObjectPtr     = &((*myS1RtCfg_Region)[theIndex]);
        if (MC_FilterObjectPtr && RT_CfgObjectPtr && RT_CfgObjectPtr->IsDstSet())
        {
            UINT16 aMCId   = RT_CfgObjectPtr->GetMCastId(MC_FilterObjectPtr->GetMCastTypeToUse());
            UINT16 aConnId = RT_CfgObjectPtr->GetConnId();

            //
            //--- There are cases (2-card protected d&c, 2-card DRI) where signalProtect
            //--- operates on mcastIds to perform switching when mcastIds are not actually
            //--- used.  To handle these cases when signalProtect invokes ApplyCesIngress(),
            //--- check for a valid mcastId before invoking TSPII.
            //
            if (aMCId != XC_MCASTID_UNKNOWN)
            {
                bool    byPass = true;
                (*(TSPII_SubApplication::GetInstance()->GetFab()))[0].AddEdgeIngressXconn(
                                                                   theIndex, 
                                                                   true,         // True for mcast
                                                                   aMCId, 
                                                                   0,            // DstInfo (n/a for mcast)
                                                                   0,            // DstInfo (n/a for mcast)
                                                                   0,            // DstInfo (n/a for mcast)
                                                                   aConnId, 
                                                                   byPass);
            }
        }
    }
}

