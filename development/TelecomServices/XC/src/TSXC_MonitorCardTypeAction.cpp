//  Copyright(c) Tellabs Transport Group. All rights reserved

#include <XC/TSXC_MonitorCardTypeAction.h>
#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_ShelfIf.h>
#include <T6100_TelecomIf.h>
#include <CSM/CSM_AppIf.h>
#include <CsPii/CSPII_CardIF.h>
#include <CsPii/CSPII_SysCfgParamIF.h>

#pragma warning "TSXC_MonitorCardTypeAction needs updates for STPM/FPCA"

//---------------------------------------------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------------------------------------------
TSXC_MonitorCardTypeAction::TSXC_MonitorCardTypeAction(T6100_CardIf& theCardContext) :
    myBbAction(NULL),
    myXCAgentConfig_Region(NULL),
    myFrmCfg_Region(NULL),
    myMuxCfg_Region(NULL),
    myS1MCastCfg_Region(NULL),
    myS1RouteCfg_Region(NULL),
    myS3MCastCfg_Region(NULL),
    myS3RouteCfg_Region(NULL),
	myCardConfigStatusRegion(NULL),
    myCardContext(theCardContext)
{
    myBbAction = new FC_BbAction(this);

    // CSM Application does not exist on STPM/FPCA
    if (CSPII_CardIF::GetInstance()->GetCardType() != CARD_TYPE_STPM || CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsHwPicoVer() )
    {
	    //add CSM card config status region as an input region to this Bb action
	    T6100_SlotIf * theSlotIf = dynamic_cast<T6100_SlotIf*> (theCardContext.GetParent());
        if (theSlotIf)
        {
	        myCardConfigStatusRegion = &(theSlotIf->GetCsmApp().GetCardConfigStatusRegion());
            myBbAction->AddInputRegion(myCardConfigStatusRegion);
        }
        else
        {
            FC_REPORT_ERROR(FC_LogicError, "Unexpected null pointer");
        }
    }

    // For STPM/FPCA, determine CardType without CSM
    else
    {
    }
}

//---------------------------------------------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------------------------------------------
TSXC_MonitorCardTypeAction::~TSXC_MonitorCardTypeAction()
{
	//remove the CSM card config status region as an input region
	myBbAction->RemoveInputRegion(myCardConfigStatusRegion);
    delete myBbAction;
}

//---------------------------------------------------------------------------------------------------------------------
// Get Methods
//---------------------------------------------------------------------------------------------------------------------
TSXC_ConfigRegion<TSXC_Connect>*    TSXC_MonitorCardTypeAction::GetAgCfgRegion()
{
    return myXCAgentConfig_Region;
}

TSXC_FrmCfgRegion<TSXC_Connect>*    TSXC_MonitorCardTypeAction::GetFrmCfgRegion()
{
    return myFrmCfg_Region;
}

TSXC_MuxCfgRegion<TSXC_MuxCfg>*    TSXC_MonitorCardTypeAction::GetMuxCfgRegion()
{
    return myMuxCfg_Region;
}

TSXC_S3RtRegion<TSXC_S3Route>*      TSXC_MonitorCardTypeAction::GetS3RtCfgRegion()    
{
    return myS3RouteCfg_Region;
}

TSXC_S1McRegion<TSXC_S1MCast>*      TSXC_MonitorCardTypeAction::GetS1McCfgRegion()    
{
    return myS1MCastCfg_Region;
}

//---------------------------------------------------------------------------------------------------------------------
// Set Methods
//---------------------------------------------------------------------------------------------------------------------
void TSXC_MonitorCardTypeAction::SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion)
{
    myXCAgentConfig_Region = theAGCfgRegion;
}

void TSXC_MonitorCardTypeAction::SetFrmCfgRegion(TSXC_FrmCfgRegion<TSXC_Connect>* theFrmCfgRegion)
{
    myFrmCfg_Region = theFrmCfgRegion;
}

void TSXC_MonitorCardTypeAction::SetMuxCfgRegion(TSXC_MuxCfgRegion<TSXC_MuxCfg>* theMuxCfgRegion)
{
    myMuxCfg_Region = theMuxCfgRegion;
}

void TSXC_MonitorCardTypeAction::SetS1McCfgRegion(TSXC_S1McRegion<TSXC_S1MCast>*    theS1McCfgRegion)
{
    myS1MCastCfg_Region = theS1McCfgRegion;
}

void TSXC_MonitorCardTypeAction::SetS1RtCfgRegion(TSXC_S1RtRegion<TSXC_S1Route>*    theS1RtCfgRegion)
{
    myS1RouteCfg_Region = theS1RtCfgRegion;
}

void TSXC_MonitorCardTypeAction::SetS3McCfgRegion(TSXC_S3McRegion<TSXC_S3MCast>*    theS3McCfgRegion)
{
    myS3MCastCfg_Region = theS3McCfgRegion;
}

void TSXC_MonitorCardTypeAction::SetS3RtCfgRegion(TSXC_S3RtRegion<TSXC_S3Route>*    theS3RtCfgRegion)
{
    myS3RouteCfg_Region = theS3RtCfgRegion;
}

//---------------------------------------------------------------------------------------------------------------------
// Do the work
//---------------------------------------------------------------------------------------------------------------------
FC_Object* TSXC_MonitorCardTypeAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    CT_CardType   CardType;
    CT_CardType   aPreviousCardType;
    TSXC_ConfigRegion<TSXC_Connect>* aTsXcConfigRegionPtr;

    //
    // Set CardType based on card which is provisioned in our slot.
    // If no card is provisioned, the card type is set to unknown.
    //
    CardType = CARD_TYPE_UNKNOWN;

    if (myCardConfigStatusRegion != NULL)
    {
        if ((*myCardConfigStatusRegion)[0].IsCardProvisionned() == TRUE)
        {
            list<CT_PartNumber>* aList =  (*myCardConfigStatusRegion)[0].GetProvisionConfigList();
            CardType = (*(aList->begin())).GetCardType();
        }
    }

    // TODO : Add code for STPM/FPCA since CSM app is unavailable.

    //
    // Set CardType in Config Region
    //
    aPreviousCardType = myXCAgentConfig_Region->GetMyCardType();
    myXCAgentConfig_Region->SetMyCardType(CardType);

    if(myFrmCfg_Region != NULL)
        myFrmCfg_Region->SetMyCardType(CardType);

    if(myMuxCfg_Region != NULL)
        myMuxCfg_Region->SetMyCardType(CardType);

    if (myS1RouteCfg_Region != NULL)
        myS1RouteCfg_Region->SetMyCardType(CardType);

    if (myS1MCastCfg_Region != NULL)
        myS1MCastCfg_Region->SetMyCardType(CardType);
    
    if (myS3MCastCfg_Region != NULL)
        myS3MCastCfg_Region->SetMyCardType(CardType);
    
    if (myS3RouteCfg_Region != NULL)
        myS3RouteCfg_Region->SetMyCardType(CardType);

    //
    // if the card type is SPFAB and the prvious card type was not the same then new SPFAB has been added 
    // therefore we need to copy the connection information form the mate SPFAB (if exist) to the new card. 
    //
    if ((CardType == CARD_TYPE_SPFAB) && (CardType != aPreviousCardType))
    {
        TSXC_ConfigRegion<TSXC_Connect>*  aSrcTsXcConfigRegionPtr = NULL;
        T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(myCardContext.GetShelfId());
        T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr((myCardContext.GetCardId() == SPFAB_PRI_SLOT)? SPFAB_SEC_SLOT:SPFAB_PRI_SLOT);
        T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
        
        if (NULL != aCardPtr)
        {
            aSrcTsXcConfigRegionPtr  = aCardPtr->GetXCAppIf().GetXCApp().GetAgCfgRegion();
            aTsXcConfigRegionPtr = myCardContext.GetXCAppIf().GetXCApp().GetAgCfgRegion();
            if ((NULL != aTsXcConfigRegionPtr) && (NULL != aSrcTsXcConfigRegionPtr) && 
                    (aSrcTsXcConfigRegionPtr->GetMyCardType() == CARD_TYPE_SPFAB))
            {
                *aTsXcConfigRegionPtr = *aSrcTsXcConfigRegionPtr;
				aTsXcConfigRegionPtr->IncModificationCounter();
				aTsXcConfigRegionPtr->UpdateNotify();
            } 
        }      
    }

    return NULL;
}
//---------------------------------------------------------------------------------------------------------------------
void TSXC_MonitorCardTypeAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
//---------------------------------------------------------------------------------------------------------------------
