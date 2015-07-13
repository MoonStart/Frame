/*----------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage One Tx activation Action Implementaion.
----------------------------------------------------*/
#include <XC/TSXC_BaseApplication.h>
#include <TsPii/TSPII_HopIf.h>
#include <TsPii/TSPII_DwIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <PII_TickTimer.h>
extern int gSP_DebugTraceSnc;                            
//------------------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------------------
TSXC_S1EnAction::TSXC_S1EnAction(T6100_CardIf& theCardContext):
    TSXC_BaseAction(theCardContext),
    myXCAgentConfig_Region(NULL),   
    myMiscConfig_Region(NULL),
    myRollStatus_Region(NULL)
{

}

//------------------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------------------
TSXC_S1EnAction::~TSXC_S1EnAction()
{

}

//------------------------------------------------------------------------------------------------
// Get Methods
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// Set Methods
//------------------------------------------------------------------------------------------------
void TSXC_S1EnAction::SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion)
{
    myXCAgentConfig_Region = theAGCfgRegion;
}

//------------------------------------------------------------------------------------------------
void TSXC_S1EnAction::SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion)
{
    myMiscConfig_Region = theMiscCfgRegion;
}

//------------------------------------------------------------------------------------------------
//--- Do the work
//------------------------------------------------------------------------------------------------
FC_Object* TSXC_S1EnAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    TSXC_Connect*               aXcAgCfgObjectPtr;
    CT_XC_ConnectState          aXcAgConnectState;
    bool                        ValidCardProvisioned;
    CT_CardType                 aCardType;
    bool                        aCardInSwitchMode = false;
    TSXC_SourceTxStatus*        aSrcTxStatus = NULL;
    const int*                  aConfigMapPtr;
    size_t                      aStartIndex;
    bool                        RegionSizeOK;
    TSPII_DwRegion*             aDwRegion = NULL;
                    
    START_TIME(TSXC_DEBUG_LEVEL01);

    // Get and store card type
    aCardType = myXCAgentConfig_Region->GetMyCardType();
    aSrcTxStatus  = myCardContext.GetXCAppIf().GetXCApp().GetSrcTxStatus();
    
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

    if ( (aCardType == CARD_TYPE_SSMX) || (aCardType == CARD_TYPE_SSMD) )
    {
        aConfigMapPtr = SSMConfigMap;
        aStartIndex   = *(aConfigMapPtr + XC_SSM_IM_LINE_FACILITY_ID);
        RegionSizeOK  = (aStartIndex + XC_MAX_XC_SSM_IM_ALL) <= myXCAgentConfig_Region->Size();
    
        if (ValidCardProvisioned && aCardInSwitchMode && RegionSizeOK)
        {
            aSrcTxStatus->ClearCurrent(); //--- Clear the current status prior to new update.
            for(int channel = 0; channel < XC_MAX_XC_SSM_IM_ALL; channel++)
            {
                aXcAgCfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)aStartIndex+channel]);
                bool isConnected = (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED);
                bool manageSrcEnable = (aXcAgCfgObjectPtr->GetMapping() == CT_XC_MAPPING_FIXED);

                UINT8 dstFac = (channel < XC_MAX_XC_SSM_IM_LINE) ? XC_SSM_IM_LINE_FACILITY_ID : XC_SSM_IM_PORT_FACILITY_ID;
                UINT8 dstFacEndpt = channel % XC_MAX_XC_SSM_IM_LINE;
                
                if (NULL != myRollStatus_Region)
                {
                    //--- Note: Need changes at the method ApplyRollFilterForActivation().
                    (*myRollStatus_Region)[0].ApplyRollFilterForActivation(0,0, dstFac, dstFacEndpt+1, &isConnected);
                }
                            
                //--- Only set src traffic enabled if TSXC manages this src
                if (manageSrcEnable)
                {
                    //--- If Src is connected, then Enable traffic
                    if (isConnected)
                    {
                        int aTspii_port = ConvertSsmPortToTspii(dstFac);
                        (*(TSPII_SubApplication::GetInstance()->GetHop(aTspii_port)))[dstFacEndpt].SetSrcTrafficEnabled(true);
                        aSrcTxStatus->SetCurrentStatus(channel);
                    }
                    //--- Deactivation for removed connection since the last time.
                    else if (aSrcTxStatus->IsDeactivationNeeded(channel)) 
                    {
                        int aTspii_port = ConvertSsmPortToTspii(dstFac);
                        (*(TSPII_SubApplication::GetInstance()->GetHop(aTspii_port)))[dstFacEndpt].SetSrcTrafficEnabled(false);
                    }
                }
            }
        }
    }

    else if ( (aCardType == CARD_TYPE_OSM40) || (aCardType == CARD_TYPE_SSM40) )
    {
        aConfigMapPtr = SSM40ConfigMap;
        aStartIndex   = *(aConfigMapPtr + XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID);  // Second imux
        RegionSizeOK  = (aStartIndex + XC_MAX_XC_SSM40_ODUXC_IMUX) <= myXCAgentConfig_Region->Size();
    
        if (ValidCardProvisioned && aCardInSwitchMode && RegionSizeOK)
        {
            int    channel;
            int    imuxChannel;
            uint8  imux;
            uint8  dstFac;
            uint8  dstFacEndpt;
            uint32 logicalOduId;
            uint16 tspiiOduIndex;

            aSrcTxStatus->ClearCurrent(); //--- Clear the current status prior to new update.

            for(channel = 0; channel < XC_MAX_XC_SSM40_ODUXC_IMUX; channel++)
            {
                for(imux=0; imux < 2; imux++)
                {
                    switch (imux)
                    {
                        case 0:   // IMUXL
                            imuxChannel = *(aConfigMapPtr + XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID) + channel;
                            dstFac = XC_SSM_IM_LINE_FACILITY_ID;
                            break;
                        case 1:   // IMUXP
                            imuxChannel = *(aConfigMapPtr + XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID) + channel;
                            dstFac = XC_SSM_IM_PORT_FACILITY_ID;
                            break;
                    }

                    aXcAgCfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)imuxChannel]);
                    bool isConnected = (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED);
                    bool manageSrcEnable = (aXcAgCfgObjectPtr->GetMapping() == CT_XC_MAPPING_FIXED);

                    if (myRollStatus_Region != NULL)
                    {
                        dstFacEndpt = imuxChannel % XC_MAX_XC_SSM40_ODUXC_IMUX;
                    
                        //--- Note: Need changes at the method ApplyRollFilterForActivation().
                        (*myRollStatus_Region)[0].ApplyRollFilterForActivation(0,0, dstFac, dstFacEndpt+1, &isConnected);
                    }

                    // --- OSM40/SSM40, only activation is possible since activation/deactivation
                    // --- point is not available when imux channel is disconnected.  Deactivation
                    // --- occurs at lower layer when imux channel is disconnected.
                    //
                    // --- If TSXC manages this Src, and Src is connected, then Enable traffic
                    if ( (manageSrcEnable) && (isConnected) )
                    {
                        logicalOduId = CreateOduId(aXcAgCfgObjectPtr->GetInputFacility(), 
                                                   aXcAgCfgObjectPtr->GetInputFacilityEndpoint(),
                                                   aXcAgCfgObjectPtr->GetType());

                        switch (aXcAgCfgObjectPtr->GetType())
                        {
                            case CT_XC_TYPE_ODU0:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu0PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_13);
                                break;
                            case CT_XC_TYPE_ODU1:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu1PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_14);
                                break;
                            case CT_XC_TYPE_ODU2:
                            case CT_XC_TYPE_ODU2E:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu2PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_15);
                                break;
                        }
                        if (NULL != aDwRegion)
                            (*aDwRegion)[tspiiOduIndex].SetSrcTrafficEnabled(true);
                        aSrcTxStatus->SetCurrentStatus(imuxChannel);
                        if ( gSP_DebugTraceSnc == 1 )
                        {
                            fc_cout << "S1En " << uint32(tspiiOduIndex) << " 1" << endl;
                        }
                    }
                }
            }
        }
    }

    else if (aCardType == CARD_TYPE_FGSM)
    {
        aConfigMapPtr = FGSMConfigMap;
        aStartIndex   = *(aConfigMapPtr + XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID);
        RegionSizeOK  = (aStartIndex + XC_MAX_XC_FGSM_ODUXC_IMUX) <= myXCAgentConfig_Region->Size();
    
        if (ValidCardProvisioned && aCardInSwitchMode && RegionSizeOK)
        {
            int    channel;
            int    imuxChannel;
            uint8  dstFac;
            uint8  dstFacEndpt;
            uint32 logicalOduId;
            uint16 tspiiOduIndex;

            aSrcTxStatus->ClearCurrent(); //--- Clear the current status prior to new update.

            for(channel = 0; channel < XC_MAX_XC_FGSM_ODUXC_IMUX; channel++)
            {
                imuxChannel = *(aConfigMapPtr + XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID) + channel;
                dstFac = XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID;

                aXcAgCfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)imuxChannel]);
                bool isConnected = (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED);
                bool manageSrcEnable = (aXcAgCfgObjectPtr->GetMapping() == CT_XC_MAPPING_FIXED);

                if (myRollStatus_Region != NULL)
                {
                    dstFacEndpt = imuxChannel % XC_MAX_XC_FGSM_ODUXC_IMUX;
                
                    //--- Note: Need changes at the method ApplyRollFilterForActivation().
                    (*myRollStatus_Region)[0].ApplyRollFilterForActivation(0,0, dstFac, dstFacEndpt+1, &isConnected);
                }

                // --- FGSM, only activation is possible since activation/deactivation
                // --- point is not available when imux channel is disconnected.  Deactivation
                // --- occurs at lower layer when imux channel is disconnected.
                //
                // --- If TSXC manages this Src, and Src is connected, then Enable traffic
                if ( (manageSrcEnable) && (isConnected) )
                {
                    logicalOduId = CreateOduId(aXcAgCfgObjectPtr->GetInputFacility(), 
                                               aXcAgCfgObjectPtr->GetInputFacilityEndpoint(),
                                               aXcAgCfgObjectPtr->GetType());
    
                    switch (aXcAgCfgObjectPtr->GetType())
                    {
                        case CT_XC_TYPE_ODU0:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu0PoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_12);
                            break;
                        case CT_XC_TYPE_ODU1:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu1PoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_13);
                            break;
                        case CT_XC_TYPE_ODU2:
                        case CT_XC_TYPE_ODU2E:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu2PoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_14);
                            break;
                    }
                    if (NULL != aDwRegion)
                        (*aDwRegion)[tspiiOduIndex].SetSrcTrafficEnabled(true);
                    aSrcTxStatus->SetCurrentStatus(imuxChannel);
                }
            }
        }
    }

    else if (aCardType == CARD_TYPE_OSM20)
    {
        aConfigMapPtr = OSM20ConfigMap;
        aStartIndex   = *(aConfigMapPtr + XC_OSM20_ODUXC_IMUX_FACILITY_ID);
        RegionSizeOK  = (aStartIndex + XC_MAX_XC_OSM20_ODUXC_IMUX) <= myXCAgentConfig_Region->Size();
    
        if (ValidCardProvisioned && aCardInSwitchMode && RegionSizeOK)
        {
            int    channel;
            int    imuxChannel;
            uint8  dstFac;
            uint8  dstFacEndpt;
            uint32 logicalOduId;
            uint16 tspiiOduIndex;

            aSrcTxStatus->ClearCurrent(); //--- Clear the current status prior to new update.

            for(channel = 0; channel < XC_MAX_XC_OSM20_ODUXC_IMUX; channel++)
            {
                imuxChannel = *(aConfigMapPtr + XC_OSM20_ODUXC_IMUX_FACILITY_ID) + channel;
                dstFac = XC_OSM20_ODUXC_IMUX_FACILITY_ID;

                aXcAgCfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)imuxChannel]);
                bool isConnected = (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED);
                bool manageSrcEnable = (aXcAgCfgObjectPtr->GetMapping() == CT_XC_MAPPING_FIXED);

                if (myRollStatus_Region != NULL)
                {
                    dstFacEndpt = imuxChannel % XC_MAX_XC_OSM20_ODUXC_IMUX;
                
                    //--- Note: Need changes at the method ApplyRollFilterForActivation().
                    (*myRollStatus_Region)[0].ApplyRollFilterForActivation(0,0, dstFac, dstFacEndpt+1, &isConnected);
                }

                // --- OSM20, only activation is possible since activation/deactivation
                // --- point is not available when imux channel is disconnected.  Deactivation
                // --- occurs at lower layer when imux channel is disconnected.
                //
                // --- If TSXC manages this Src, and Src is connected, then Enable traffic
                if ( (manageSrcEnable) && (isConnected) )
                {
                    logicalOduId = CreateOduId(aXcAgCfgObjectPtr->GetInputFacility(), 
                                               aXcAgCfgObjectPtr->GetInputFacilityEndpoint(),
                                               aXcAgCfgObjectPtr->GetType());
    
                    switch (aXcAgCfgObjectPtr->GetType())
                    {
                        case CT_XC_TYPE_ODU0:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu0PoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_13);
                            break;
                        case CT_XC_TYPE_ODU1:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu1PoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_14);
                            break;
                        case CT_XC_TYPE_ODU2:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu2PoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_15);
                            break;
                        case CT_XC_TYPE_ODUF:
                            tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOduFPoolIndex(logicalOduId);
                            aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_12);
                            break;
                    }
                    if (NULL != aDwRegion)
                        (*aDwRegion)[tspiiOduIndex].SetSrcTrafficEnabled(true);
                    aSrcTxStatus->SetCurrentStatus(imuxChannel);
                }
            }
        }
    }

    else if (aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C)
    {
        aConfigMapPtr = OSMOduXcConfigMap;
        aStartIndex   = *(aConfigMapPtr + XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID);  // Second imux
        RegionSizeOK  = (aStartIndex + XC_MAX_XC_OSM_ODUXC_IMUX) <= myXCAgentConfig_Region->Size();
    
        if (ValidCardProvisioned && RegionSizeOK)
        {
            int    channel;
            int    imuxChannel;
            uint8  imux;
            uint32 logicalOduId;
            uint16 tspiiOduIndex;

            for(channel = 0; channel < XC_MAX_XC_OSM_ODUXC_IMUX; channel++)
            {
                for(imux=0; imux < 2; imux++)
                {
                    switch (imux)
                    {
                        case 0:   // IMUX0
                            imuxChannel = *(aConfigMapPtr + XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID) + channel;
                            break;
                        case 1:   // IMUX1
                            imuxChannel = *(aConfigMapPtr + XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID) + channel;
                            break;
                    }

                    aXcAgCfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)imuxChannel]);
                    bool isConnected = (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED);
                    bool manageSrcEnable = (aXcAgCfgObjectPtr->GetMapping() == CT_XC_MAPPING_FIXED);

                    // --- OSM2S/OSM2C, only activation is possible since activation/deactivation
                    // --- point is not available when imux channel is disconnected.  Deactivation
                    // --- occurs at lower layer when imux channel is disconnected.
                    //
                    // --- If TSXC manages this Src, and Src is connected, then Enable traffic
                    if(manageSrcEnable && isConnected)
                    {
                        logicalOduId = CreateOduId(aXcAgCfgObjectPtr->GetInputFacility(), 
                                                   aXcAgCfgObjectPtr->GetInputFacilityEndpoint(),
                                                   aXcAgCfgObjectPtr->GetType());

                        switch(aXcAgCfgObjectPtr->GetType())
                        {
                            case CT_XC_TYPE_ODUF:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOduFPoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_11);
                                break;
                            case CT_XC_TYPE_ODU0:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu0PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_11);
                                break;
                            case CT_XC_TYPE_ODU1:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu1PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_12);
                                break;
                            case CT_XC_TYPE_ODU2:
                            case CT_XC_TYPE_ODU2E:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu2PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_13);
                                break;
                            case CT_XC_TYPE_ODU3:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu3PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_14);
                                break;
                            case CT_XC_TYPE_ODU4:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu4PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_15);
                                break;
                        }

                        if (NULL != aDwRegion)
                            (*aDwRegion)[tspiiOduIndex].SetSrcTrafficEnabled(true);

                        if ( gSP_DebugTraceSnc == 1 )
                        {
                            fc_cout << "S1En " << uint32(tspiiOduIndex) << " 1" << endl;
                        }
                    }
                }
            }
        }
    }

    else if (aCardType == CARD_TYPE_OSM1S)
    {
        aConfigMapPtr = OSM1SOduXcConfigMap;
        aStartIndex   = *(aConfigMapPtr + XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID);  // Second imux
        RegionSizeOK  = (aStartIndex + XC_MAX_OSM1S_ODUXC_IMUX) <= myXCAgentConfig_Region->Size();
    
        if (ValidCardProvisioned && RegionSizeOK)
        {
            int    channel;
            int    imuxChannel;
            uint8  imux;
            uint32 logicalOduId;
            uint16 tspiiOduIndex;

            for(channel = 0; channel < XC_MAX_OSM1S_ODUXC_IMUX; channel++)
            {
                for(imux=0; imux < 2; imux++)
                {
                    switch (imux)
                    {
                        case 0:   // HyPHYflex 0
                            imuxChannel = *(aConfigMapPtr + XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID) + channel;
                            break;
                        case 1:   // HyPHYflex 1
                            imuxChannel = *(aConfigMapPtr + XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID) + channel;
                            break;
                    }

                    aXcAgCfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)imuxChannel]);
                    bool isConnected = (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED);
                    bool manageSrcEnable = (aXcAgCfgObjectPtr->GetMapping() == CT_XC_MAPPING_FIXED);

                    // --- OSM1S, only activation is possible since activation/deactivation
                    // --- point is not available when imux channel is disconnected.  Deactivation
                    // --- occurs at lower layer when imux channel is disconnected.
                    //
                    // --- If TSXC manages this Src, and Src is connected, then Enable traffic
                    if(manageSrcEnable && isConnected)
                    {
                        logicalOduId = CreateOduId(aXcAgCfgObjectPtr->GetInputFacility(), 
                                                   aXcAgCfgObjectPtr->GetInputFacilityEndpoint(),
                                                   aXcAgCfgObjectPtr->GetType());

                        switch(aXcAgCfgObjectPtr->GetType())
                        {
                            case CT_XC_TYPE_ODU0:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu0PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_11);
                                break;
                            case CT_XC_TYPE_ODU1:
                                tspiiOduIndex = TSPII_SubApplication::GetInstance()->GetOdu1PoolIndex(logicalOduId);
                                aDwRegion     = TSPII_SubApplication::GetInstance()->GetDw(TSPII_LINE_SIDE_12);
                                break;
                        }

                        if (NULL != aDwRegion)
                            (*aDwRegion)[tspiiOduIndex].SetSrcTrafficEnabled(true);

                        if ( gSP_DebugTraceSnc == 1 )
                        {
                            fc_cout << "S1En " << uint32(tspiiOduIndex) << " 1" << endl;
                        }
                    }
                }
            }
        }
    }

    END_TIME(TSXC_DEBUG_LEVEL01);
    PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage one enable update :");           

    return NULL;
}

//------------------------------------------------------------------------------------------------
int TSXC_S1EnAction::ConvertSsmPortToTspii(uint8 srcFac)
{
    int aTspii_port = -1;
    switch (srcFac)
    {
        case XC_SSM_DWDM_FACILITY_ID:
            aTspii_port = TSPII_LINE_SIDE_0;
            break;
        case XC_SSM_IM_LINE_FACILITY_ID:
            aTspii_port = TSPII_LINE_SIDE_3;
            break;
        case XC_SSM_IM_PORT_FACILITY_ID:
            aTspii_port = TSPII_LINE_SIDE_4;
            break;
        case XC_SSM_TTP_FACILITY_ID:
            aTspii_port = TSPII_PORT_SIDE_26;
            break;
        case XC_SSM_PORT0_FACILITY_ID:
        case XC_SSM_PORT1_FACILITY_ID:
        case XC_SSM_PORT2_FACILITY_ID:
        case XC_SSM_PORT3_FACILITY_ID:
        case XC_SSM_PORT4_FACILITY_ID:
        case XC_SSM_PORT5_FACILITY_ID:
        case XC_SSM_PORT6_FACILITY_ID:
        case XC_SSM_PORT7_FACILITY_ID:
        case XC_SSM_PORT8_FACILITY_ID:
        case XC_SSM_PORT9_FACILITY_ID:
        case XC_SSM_PORT10_FACILITY_ID:
        case XC_SSM_PORT11_FACILITY_ID:
        case XC_SSM_PORT12_FACILITY_ID:
            aTspii_port = (srcFac - XC_SSM_PORT0_FACILITY_ID) + TSPII_PORT_SIDE_0;
            break;
        default:
            char ErrorMsg[50];
            sprintf(ErrorMsg, "TSXC_S1EnAction: unsupported source facility id (%d)\n", srcFac);
            FC_REPORT_ERROR(FC_NotSupportedError, ErrorMsg);
            break;
    }
    return aTspii_port;
}

//------------------------------------------------------------------------------------------------
uint32 TSXC_S1EnAction::CreateOduId(uint8 theInputFacility, uint8 theInputFacilityEndpoint, CT_XC_ConnectType theConnType)
{
    uint16           aCbrbPort;
    uint16           aCbrbSlot;
    CT_ODU_Layer     aKValue;

    TSPII_XcRegion*  tspiiXcRegion = TSPII_SubApplication::GetInstance()->GetXc();

    aCbrbPort = (*tspiiXcRegion)[0].TsPortToTspiiPort(theInputFacility);
    aCbrbSlot = theInputFacilityEndpoint - 1;

    if (theConnType == CT_XC_TYPE_ODU1)
    {
        aKValue = CT_ODU_Layer1;
    }
    else if ( (theConnType == CT_XC_TYPE_ODU2) || (theConnType == CT_XC_TYPE_ODU2E) )
    {
        aKValue = CT_ODU_Layer2;
    }
    else if (theConnType == CT_XC_TYPE_ODU0)
    {
        aKValue = CT_ODU_Layer0;
    }
    else if (theConnType == CT_XC_TYPE_ODU3)
    {
        aKValue = CT_ODU_Layer3;
    }
    else if (theConnType == CT_XC_TYPE_ODU4)
    {
        aKValue = CT_ODU_Layer4;
    }
    else if (theConnType == CT_XC_TYPE_ODUF)
    {
        aKValue = CT_ODU_LayerF;
    }
    else
    {
        aKValue = CT_ODU_LayerEnd;
        fc_cout << "TSXC_S1EnAction::CreateOduId Invalid k value" << endl;
    }

    CT_ODU_Identifier aOduIdentifier ((uint8)aKValue, (uint8) aCbrbPort, (uint8) aCbrbSlot);

    return aOduIdentifier.GetIdValue();
}
