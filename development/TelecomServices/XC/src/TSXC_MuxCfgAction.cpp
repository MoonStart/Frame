/*-------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved
-------------------------------------------------------------*/

#include <XC/TSXC_MuxCfgAction.h>

#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_SubApplication.h>

//---------------------------------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------------------------------
TSXC_MuxCfgAction::TSXC_MuxCfgAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myMuxCfg_Region(NULL)
{
}

//---------------------------------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------------------------------
TSXC_MuxCfgAction::~TSXC_MuxCfgAction()
{
}

//---------------------------------------------------------------------------------------------------------
void TSXC_MuxCfgAction::SetMuxCfgRegion(TSXC_MuxCfgRegion<TSXC_MuxCfg>* theMuxCfgRegion)
{
    myMuxCfg_Region = theMuxCfgRegion;
}

//---------------------------------------------------------------------------------------------------------
FC_Object* TSXC_MuxCfgAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    TSPII_XcRegion* tspiiXcRegion = NULL;
    CT_CardType aCardType = CARD_TYPE_UNKNOWN;

    aCardType = myMuxCfg_Region->GetMyCardType();
    
    if(aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C || aCardType == CARD_TYPE_OSM1S)
    {
        // 0(default) means cfg, 2 means frm, 3 means mux
        tspiiXcRegion = TSPII_SubApplication::GetInstance()->GetXc(3);
    }

    if(tspiiXcRegion != NULL)
    {
        START_TIME(TSXC_DEBUG_LEVEL01);

        UINT32 maxRegionIndex = (*myMuxCfg_Region).Size();
        for(UINT32 regionIndex = 0; regionIndex < maxRegionIndex; regionIndex++)
        {
            uint16 theTribSlot[TSXC_MUX_BITMAP_LENGTH];

            TSXC_MuxCfg* theMuxCfgObjPtr = &((*myMuxCfg_Region)[(bbindex_t)regionIndex]);
            uint16 theHighOdu = theMuxCfgObjPtr->GetHighOdu();
            uint16 theLowOdu = theMuxCfgObjPtr->GetLowOdu();
            theMuxCfgObjPtr->GetTribSlot(theTribSlot);

            if(theHighOdu != 0 && theLowOdu != 0)
            {
                (*tspiiXcRegion)[0].AddMux(theHighOdu, theLowOdu, theTribSlot);
            }
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: TSXC MUX provision time : ");
        
        START_TIME(TSXC_DEBUG_LEVEL01);
        (*tspiiXcRegion)[0].CommitXconns();
        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: TSXC MUX commit time : ");
    }

    Respond(myMuxCfg_Region->GetCQMRequest());

    return NULL;
}

