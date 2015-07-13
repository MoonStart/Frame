/*------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage Three Route Action Implementaion.
------------------------------------------------------*/
#include <XC/TSXC_S3RtAction.h>
#include <XC/TSXC_BaseApplication.h>
#include <CommonTypes/CT_FabMulticast.h>
#include <TsPii/TSPII_SsmIf.h>
#include <TsPii/TSPII_FabIf.h>
#include <TsPii/TSPII_SubApplication.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_S3RtAction::TSXC_S3RtAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myS3RtCfg_Region(NULL),
    myMiscConfig_Region(NULL)
{
    
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_S3RtAction::~TSXC_S3RtAction()
{

}

//--------------------------------------------------------------------------------------------------
// Get Methods
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------
void TSXC_S3RtAction::SetS3RtCfgRegion(TSXC_S3RtRegion<TSXC_S3Route>*    theS3RtCfgRegion)
{
    myS3RtCfg_Region = theS3RtCfgRegion;
}

void TSXC_S3RtAction::SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion)
{
    myMiscConfig_Region = theMiscCfgRegion;
}

//--------------------------------------------------------------------------------------------------
// Do the work
//--------------------------------------------------------------------------------------------------
FC_Object* TSXC_S3RtAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    bool                        ValidCardProvisioned;
    bool                        aSsmInMeshOrHCSSMode = false;
    CT_CardType                 aCardType;
 
    aCardType = myS3RtCfg_Region->GetMyCardType();
    ValidCardProvisioned =  ( (aCardType == CARD_TYPE_SSMX)  || 
                              (aCardType == CARD_TYPE_SSMD)  ||
                              (aCardType == CARD_TYPE_OSM40) || 
                              (aCardType == CARD_TYPE_SSM40) ||
                              (aCardType == CARD_TYPE_FGSM)  ||
                              aCardType == CARD_TYPE_OSM20);
    
    
    if (myMiscConfig_Region != NULL)
    {
        aSsmInMeshOrHCSSMode = ((*myMiscConfig_Region)[0].GetSwitchMode() != CT_TEL_SwitchMode_None);
    }
    
    if (aSsmInMeshOrHCSSMode && ValidCardProvisioned)
    {
        TSXC_S3Route*   aS3Rt_CfgObjectPtr = NULL;
        int             maxRouteRegionIdx  = myS3RtCfg_Region->Size();
        TSPII_FabIf&    tspiiFabIf         = (*(TSPII_SubApplication::GetInstance()->GetFab()))[0];

        uint16  aSrcFacEndPt;
        uint8   aSrcSlot;
        uint8   aSrcShelf;
        uint16  aConnId;

        START_TIME(TSXC_DEBUG_LEVEL01);

        tspiiFabIf.DeleteAllEdgeEgressXconns();

        for (int aDstSts = 0; aDstSts < maxRouteRegionIdx; aDstSts++)
        {
            aS3Rt_CfgObjectPtr = &((*myS3RtCfg_Region)[aDstSts]);

            for (int aSrcIdx = 0; aSrcIdx < XC_MAX_SRC_ENDPT; aSrcIdx++)
            {
                if (aS3Rt_CfgObjectPtr->IsSrcSet(aSrcIdx))
                {
                    aSrcFacEndPt = aS3Rt_CfgObjectPtr->GetSrcFacilityEndpoint(aSrcIdx) - 1;
                    aSrcSlot     = aS3Rt_CfgObjectPtr->GetSrcSlot(aSrcIdx) - 1;
                    aSrcShelf    = PhysToLogicalShelf(aS3Rt_CfgObjectPtr->GetSrcShelf(aSrcIdx),         // PhysicalShelf (1-based)
                                                      (*myMiscConfig_Region)[0].GetSwitchMode(),        // switchMode
                                                      (*myMiscConfig_Region)[0].GetSwitchDomainMode()); // SwitchDomain Mode
                    aConnId      = aS3Rt_CfgObjectPtr->GetSrcConnId(aSrcIdx);
                    
                    // At the Egress SSM, aDstSts is the IMUX channel (0-383)
                    // for incoming traffic of the destination module
                    tspiiFabIf.AddEdgeEgressXconn(aSrcShelf, aSrcSlot, aSrcFacEndPt, aConnId, aDstSts);
                }
            }
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage three route provision time : ");

        START_TIME(TSXC_DEBUG_LEVEL01);

        tspiiFabIf.CommitEdgeEgressXconns( );

        Respond(myS3RtCfg_Region->GetCQMRequest());

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage three route commit time : ");

    } 

    return NULL;
}
//--------------------------------------------------------------------------------------------------

