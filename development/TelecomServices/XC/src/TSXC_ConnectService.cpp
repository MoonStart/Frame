/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     December, 2007  Kumar C Solai
    DESCRIPTION:   TSXC_ConnectService  Implementation
--------------------------------------------------------------------------*/
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_ConnectService.h>
#include <XC/TSXC_ShelfBaseApp.h>
#include <T6100_CssIf.h>
#include <XC/TSXC_CssBasedApp.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <Configuration/CFG_MiscBaseApplication.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Misc.h>
#include <CommonTypes/CT_PortMap.h>



//----------------------------------------------------------------------------------------------------------------------------------
//--- Initialize the singleton pointer to NULL at the start
TSXC_ConnectService* TSXC_ConnectService::ItsInstance = NULL;

//--- Initialize the Roll action pointer
TSXC_RollAction*    TSXC_ConnectService::myRollActionPtr = NULL;

//--- Initialize the debug level 
INT32   TSXC_ConnectService::myDebugLevel = 0;
TSXC_RollType TSXC_ConnectService::myRollType = ROLL_TYPE_NONE;

//----------------------------------------------------------------------------------------------------------------------------------
//--- Returns the pointer to the singleton class TSXC_ConnectService
TSXC_ConnectService* TSXC_ConnectService::GetInstance()
{
    if (ItsInstance == NULL)
    {
        ItsInstance = new  TSXC_ConnectService();
        myRollActionPtr = new TSXC_RollAction();
    }
    return ItsInstance;
}

//---------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::ConnectPair(
            CT_XcTerm& SrcOne,                   //--- Clsss contains pointers to source information one 
            CT_XcTerm& DstOne,                   //--- Clsss contains pointers to destination information one 
            CT_XcTerm& SrcTwo,                   //--- Clsss contains pointers to source information Two 
            CT_XcTerm& DstTwo,                   //--- Clsss contains pointers to destination information Two 
            const CT_ProtGpType SrcProtScheme,  //--- Source Protection type such as DPRING, UPSR, UNPROTECTED and etc.
            const CT_ProtGpType DstProtScheme,  //--- Destination Protection type such as UPSR, 1PLUS1, UNPROTECTED and etc.
            const CT_XC_ConnectionScheme&   ConnScheme,  //--- Connect Scheme such as 1WAY, 1WAYFIX, 2WAY and etc.
            const CT_XC_ConnectType&        ConnType,    //--- Connect type such as 3c, 12c and etc.
            CT_InterconMode InterConnectMode,            //--- SPFAB, NONSPFAB and UNKNOWN  
            XC_ConnAction             Action)            //--- action as connect or Disconnect
{
    switch(ConnScheme)
    {
        case CT_XC_2WAY_DRI:
            ConnectRequest(DstOne,SrcOne,DstTwo,SrcTwo,DstProtScheme,SrcProtScheme,CT_XC_1WAY_DRI,ConnType,InterConnectMode,Action);
            // fall through 
        case CT_XC_1WAY_DRI:
            ConnectRequest(SrcOne,DstOne,SrcTwo,DstTwo,SrcProtScheme,DstProtScheme,CT_XC_1WAY_DRI,ConnType,InterConnectMode,Action);
            break;
        case CT_XC_2WAY:
            ConnectRequest(DstOne,SrcOne,DstTwo,SrcTwo,DstProtScheme,SrcProtScheme,CT_XC_1WAY,ConnType,InterConnectMode,Action);
            //--- Continue with other direction as well
        case CT_XC_1WAY:
            ConnectRequest(SrcOne,DstOne,SrcTwo,DstTwo,SrcProtScheme,DstProtScheme,CT_XC_1WAY,ConnType,InterConnectMode,Action);
            break;
        case CT_XC_1WAY_FIXED:
            ConnectRequest(SrcOne,DstOne,SrcTwo,DstTwo,SrcProtScheme,DstProtScheme,ConnScheme,ConnType,InterConnectMode,Action);
            break;
        default:
            FC_REPORT_ERROR(FC_LogicError, "TSXC_ConnectService::ConnectPair(), Invaild ConnectScheme");
            break;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::ConnectRequest(
            CT_XcTerm& SrcOne,                   //--- Clsss contains pointers to source information one 
            CT_XcTerm& DstOne,                   //--- Clsss contains pointers to destination information one 
            CT_XcTerm& SrcTwo,                   //--- Clsss contains pointers to source information Two 
            CT_XcTerm& DstTwo,                   //--- Clsss contains pointers to destination information Two 
            const CT_ProtGpType SrcProtScheme,  //--- Source Protection type such as DPRING, UPSR, UNPROTECTED and etc.
            const CT_ProtGpType DstProtScheme,  //--- Destination Protection type such as UPSR, 1PLUS1, UNPROTECTED and etc.
            const CT_XC_ConnectionScheme&   ConnScheme,  //--- Connect Scheme such as 1WAY, 1WAYFIX, 2WAY and etc.
            const CT_XC_ConnectType&        ConnType,    //--- Connect type such as 3c, 12c and etc.
            CT_InterconMode InterConnectMode,            //--- SPFAB, NONSPFAB and UNKNOWN  
            XC_ConnAction             Action,            //--- action as connect or Disconnect 
            bool    Roll,
            bool    IsQrsTransitionReq)
{
    TSXC_ConfigRegion<TSXC_Connect>* SrcOneCfgPtr = NULL;
    TSXC_ConfigRegion<TSXC_Connect>* DstOneCfgPtr = NULL;
    TSXC_ConfigRegion<TSXC_Connect>* SrcTwoCfgPtr = NULL;
    TSXC_ConfigRegion<TSXC_Connect>* DstTwoCfgPtr = NULL;
    
    INT32   stsCount;
    UINT32  group = 0;
    bool    XcAllowed = true;
    bool    IsHybrid = false;
    bool    IsMixed  = false;
    UINT8   LastPort = XC_SMTMU_PORT9_FACILITY_ID;      //--- start with SMTMU last port
    UINT8   SrcOneFac, DstOneFac, SrcTwoFac, DstTwoFac;
    UINT8   SrcOneMuxFac, DstOneMuxFac, SrcTwoMuxFac, DstTwoMuxFac;
    UINT8   PortBaseSlot;
    CT_FAC_StsMap * SrcOneMuxMapPtr = NULL;
    CT_FAC_StsMap * DstOneMuxMapPtr = NULL;
    CT_FAC_StsMap * SrcTwoMuxMapPtr = NULL;
    CT_FAC_StsMap * DstTwoMuxMapPtr = NULL;
    
    UINT8   SPFABSrcOneMuxFac, SPFABDstOneMuxFac, SPFABSrcTwoMuxFac, SPFABDstTwoMuxFac;
    bool    InputParamsAreValid = TRUE;
    bool    IsSrcOneConnectDisconnectAllowed = TRUE;
    bool    IsDstOneConnectDisconnectAllowed = TRUE;
    bool    IsSrcTwoConnectDisconnectAllowed = TRUE;
    bool    IsDstTwoConnectDisconnectAllowed = TRUE;
    
    //--- Get the Shelf type and the card family information
    CT_CardType     aCardType = CARD_TYPE_UNKNOWN;
    if ((NULL == SrcOne.FacData) || (NULL == DstOne.FacData))
    {
        // Normally this should never happen. If it did then it can not proceed any more. 
        FC_REPORT_ERROR(FC_LogicError, "unexpected Null pointer for FacData on SrcOne/DstOne");
        return;
    }

    T6100_ShelfIf*  aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(SrcOne.FacData->GetShelf());
    T6100_SlotIf*   aSlotPtr    = aShelfPtr->GetSlotPtr(SrcOne.FacData->GetSlot());
    T6100_CardIf*   aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL == aCardPtr)
    {
        // Card may not be provision correctly  Then it should not continue.
        FC_REPORT_ERROR(FC_LogicError, "unexpected Null pointer for aCardPtr");
        return;
    }

    CT_CardFamily   aCardFamily = aCardPtr->GetCardFamily();
    CT_ShelfType    aShelfType  = GetShelfType(SrcOne.FacData->GetShelf());

    bool    IsNanoSwitch = false;
    bool    IsCesSwitch  = false;
    bool    IsTdmSwitch  = false;
    
    //--- Determine switch type
    if (InterConnectMode == CT_INTERCON_MODE_SPFAB)
    {
        switch (aShelfType)
        {
            case OPTICAL_SHELF_NANO_TYPE:
            case PORT_SHELF_NANO_TYPE:
                IsNanoSwitch = true;
                break;
            case MTERA_SHELF_TYPE:
                IsCesSwitch = true;
                aCardFamily = OSM_FAM;  // Logic above doesn't set card family correctly for MTERA
                break;
            default:
                switch (aCardFamily.GetCardFamily())
                {
                    case CARD_FAM_SMTM:
                        IsTdmSwitch = true;
                        break;
                    case CARD_FAM_SSM:
                    case CARD_FAM_SSM40:
                    case CARD_FAM_FGSM:
                        // SSM only supports CES traffic in switched mode
                        IsCesSwitch = true;
                        break;
                    default:
                        FC_REPORT_ERROR(FC_LogicError,"unsupported card family");
                        return; // Something is wrong, With out a proper card family can't continue 
                }
                break;
        }
    }

    CT_XC_ConnectMapping Spfab_XcMapping = CT_XC_MAPPING_FIXED;  
    char    aDebugMsg[DEBUG_MSG_LEN];
    char    *aGroupMsg[GROUP_END] = {"None","G1","G2","G3","G4","G5","G6","G7","G8",
                                           "G2P","G3P","G4P","G5P","G8P","G3H","G4H","G5H","G8H", "G5M", "G6P"};

    //--- Get the config pointers for all four module if available and update facility Id 
    if ( SrcOne.FacData->IsDefault() == false )
    {
        SrcOneCfgPtr = FindTSXCConfigRegion(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot());
        if (NULL != SrcOneCfgPtr)
        {        
            SrcOneCfgPtr->GetFacilityIdFromAGPortId(&SrcOneFac, SrcOne.FacData->GetPortId());

            //--- If SrcOne is mapped to IMUXL, set SrcOneMux info based on IMUXL
            if (SrcOne.TermMappedToImuxl == true)
            {
                SrcOneMuxMapPtr = &SrcOne.ImuxLineMapIngress;
                SrcOneCfgPtr->GetFacilityIdFromIntfId(&SrcOneMuxFac,CT_LINE_SIDE_3);
            }
            //--- If SrcOne is mapped to IMUXP, set SrcOneMux info based on IMUXP
            else if (SrcOne.TermMappedToImuxp == true)
            {
                SrcOneMuxMapPtr = &SrcOne.ImuxPortMapIngress;
                SrcOneCfgPtr->GetFacilityIdFromIntfId(&SrcOneMuxFac,CT_LINE_SIDE_4);
            }

            //--- If neither path is to be established, set allowed flag to false
            if ( (SrcOne.TermToImuxlPath == false) && (SrcOne.TermToImuxpPath == false) )
            {
                IsSrcOneConnectDisconnectAllowed = FALSE;
            }

            //--- Set the LastPort that will be used later for hybrid or pair_module on a protected connections.
            aCardType = SrcOneCfgPtr->GetMyCardType();
            if (aCardType  == CARD_TYPE_SSMX || aCardType == CARD_TYPE_SSMD)
                LastPort = XC_SSM_PORT12_FACILITY_ID;
        }
    }
    
    if (DstOne.FacData->IsDefault() == false)
    {
        DstOneCfgPtr = FindTSXCConfigRegion(DstOne.FacData->GetShelf(), DstOne.FacData->GetSlot());
        if (NULL != DstOneCfgPtr)
        {
            DstOneCfgPtr->GetFacilityIdFromAGPortId(&DstOneFac, DstOne.FacData->GetPortId());
			
            //--- If DstOne is mapped to IMUXL, set DstOneMux info based on IMUXL
            if (DstOne.TermMappedToImuxl == true)
            {
                DstOneMuxMapPtr = &DstOne.ImuxLineMapEgress;
                DstOneCfgPtr->GetFacilityIdFromIntfId(&DstOneMuxFac,CT_LINE_SIDE_3);
            }
            //--- If DstOne is mapped to IMUXP, set DstOneMux info based on IMUXP
            else if (DstOne.TermMappedToImuxp == true)
            {
                DstOneMuxMapPtr = &DstOne.ImuxPortMapEgress;
                DstOneCfgPtr->GetFacilityIdFromIntfId(&DstOneMuxFac,CT_LINE_SIDE_4);
            }

            //--- If neither path is to be established, set allowed flag to false
            if ( (DstOne.ImuxlToTermPath == false) && (DstOne.ImuxpToTermPath == false) )
            {
                IsDstOneConnectDisconnectAllowed = FALSE;
            }
        }  
    }

    if ((NULL != SrcTwo.FacData) && (SrcTwo.FacData->IsDefault() == false))
    {
        SrcTwoCfgPtr = FindTSXCConfigRegion(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot());
        if (NULL != SrcTwoCfgPtr)
        {
            SrcTwoCfgPtr->GetFacilityIdFromAGPortId(&SrcTwoFac, SrcTwo.FacData->GetPortId());

            //--- If SrcTwo is mapped to IMUXL, set SrcTwoMux info based on IMUXL
            if (SrcTwo.TermMappedToImuxl == true)
            {
                SrcTwoMuxMapPtr = &SrcTwo.ImuxLineMapIngress;
                SrcTwoCfgPtr->GetFacilityIdFromIntfId(&SrcTwoMuxFac,CT_LINE_SIDE_3);
            }
            //--- If SrcTwo is mapped to IMUXP, set SrcTwoMux info based on IMUXP
            else if (SrcTwo.TermMappedToImuxp == true)
            {
                SrcTwoMuxMapPtr = &SrcTwo.ImuxPortMapIngress;
                SrcTwoCfgPtr->GetFacilityIdFromIntfId(&SrcTwoMuxFac,CT_LINE_SIDE_4);
            }

            //--- If neither path is to be established, set allowed flag to false
            if ( (SrcTwo.TermToImuxlPath == false) && (SrcTwo.TermToImuxpPath == false) )
            {
                IsSrcTwoConnectDisconnectAllowed = FALSE;
            }
        }
    }
    
    if ((NULL != DstTwo.FacData) && (DstTwo.FacData->IsDefault() == false))
    {
        DstTwoCfgPtr = FindTSXCConfigRegion(DstTwo.FacData->GetShelf(), DstTwo.FacData->GetSlot());
        if (NULL != DstTwoCfgPtr)
        {
            DstTwoCfgPtr->GetFacilityIdFromAGPortId(&DstTwoFac, DstTwo.FacData->GetPortId());

            //--- If DstTwo is mapped to IMUXL, set DstTwoMux info based on IMUXL
            if (DstTwo.TermMappedToImuxl == true)
            {
                DstTwoMuxMapPtr = &DstTwo.ImuxLineMapEgress;
                DstTwoCfgPtr->GetFacilityIdFromIntfId(&DstTwoMuxFac,CT_LINE_SIDE_3);
            }
            //--- If DstTwo is mapped to IMUXP, set DstTwoMux info based on IMUXP
            else if (DstTwo.TermMappedToImuxp == true)
            {
                DstTwoMuxMapPtr = &DstTwo.ImuxPortMapEgress;
                DstTwoCfgPtr->GetFacilityIdFromIntfId(&DstTwoMuxFac,CT_LINE_SIDE_4);
            }

            //--- If neither path is to be established, set allowed flag to false
            if ( (DstTwo.ImuxlToTermPath == false) && (DstTwo.ImuxpToTermPath == false) )
            {
                IsDstTwoConnectDisconnectAllowed = FALSE;
            }
        }  
    }

    //----------------------------
    //--- Figuring out the group
    //----------------------------
    
    //--- Determintaion of the hyprid mode.
    if (IsNanoSwitch || IsCesSwitch)
    {
        map< unsigned char, unsigned char, less<unsigned char> >    aSlotInfo;
        UINT8 aSrc1Slot = SrcOne.FacData->GetSlot();
        UINT8 aDst1Slot = DstOne.FacData->GetSlot();
        UINT8 aSrc2Slot = ((NULL != SrcTwo.FacData) && (SrcTwo.FacData->IsDefault() == false)) ?
                            SrcTwo.FacData->GetSlot() : SrcOne.FacData->GetSlot();
        UINT8 aDst2Slot = ((NULL != DstTwo.FacData) && (DstTwo.FacData->IsDefault() == false)) ?
                            DstTwo.FacData->GetSlot() : DstOne.FacData->GetSlot();

        CT_ShelfId aSrc1Shelf = SrcOne.FacData->GetShelf();
        CT_ShelfId aDst1Shelf = DstOne.FacData->GetShelf();
        CT_ShelfId aSrc2Shelf = ((NULL != SrcTwo.FacData) && (SrcTwo.FacData->IsDefault() == false)) ?
                                  SrcTwo.FacData->GetShelf() : SrcOne.FacData->GetShelf();
        CT_ShelfId aDst2Shelf  = ((NULL != DstTwo.FacData) && (DstTwo.FacData->IsDefault() == false)) ?
                                  DstTwo.FacData->GetShelf() : DstOne.FacData->GetShelf();

        aSlotInfo[aSrc1Slot] = aSrc1Slot;
        aSlotInfo[aDst1Slot] = aDst1Slot;
        aSlotInfo[aSrc2Slot] = aSrc2Slot;
        aSlotInfo[aDst2Slot] = aDst2Slot;

        //--- If there are four module ivolved, then it can not be Hybrid or Mixed mode.
        //--- If this is an OSM40/SSM40/OSM20/FGSM/OSM2S/OSM2C/OSM1S, then it can not be Hybrid or Mixed mode since all traffic must use switchCore.
        if ( (aSlotInfo.size() == 4) || (aCardFamily == SSM40_FAM) || (aCardFamily == FGSM_FAM) || aCardFamily == OSM_FAM)
        {
            IsHybrid = false;
            IsMixed  = false;
        }
        else
        {
            // If src1 and dst1 are on same module, then this is a Hybrid connection.
            IsHybrid = ( (aSrc1Shelf == aDst1Shelf) && (aSrc1Slot == aDst1Slot) );

            // If src1 and dst1 are on same module, and
            //    src2 and dst2 are not on same module, then this is a Mixed connection.
            IsMixed  = (  (aSrc1Shelf == aDst1Shelf) && (aSrc1Slot == aDst1Slot) && 
                        !((aSrc2Shelf == aDst2Shelf) && (aSrc2Slot == aDst2Slot)) );
        }
    }
    
    if ((PROT_GP_UNKNOWN == SrcProtScheme) && (PROT_GP_UNKNOWN == DstProtScheme))
    {
        if ( (SrcOne.FacData->GetSlot()  == DstOne.FacData->GetSlot()) &&
             (SrcOne.FacData->GetShelf() == DstOne.FacData->GetShelf()) )
        {
            group = GROUP_1;  //--- same module without Imux or SPFAB

            // For OSM40/SSM40/OSM20/FGSM/OSM2S/OSM2C/OSM1S, all traffic uses switchCore so fake it as GROUP_2
            if (aCardFamily == SSM40_FAM || aCardFamily == FGSM_FAM || aCardFamily == OSM_FAM)
                group = GROUP_2;
        }
        else 
            group = (CT_INTERCON_MODE_SPFAB == InterConnectMode) ? GROUP_2 : GROUP_2P; //--- Diverted using SPFAB/PairMode.
    }
        
    else if ((PROT_GP_UNKNOWN == SrcProtScheme) && (PROT_GP_UNKNOWN != DstProtScheme))
        //--- Note: Here we make the addition connection on spfab plus the diverted traffic from the group two
        group = (CT_INTERCON_MODE_SPFAB == InterConnectMode) ? (IsHybrid ? GROUP_3H : GROUP_3) : GROUP_3P;
    
    else if ((PROT_GP_UNKNOWN != SrcProtScheme) && (PROT_GP_UNKNOWN == DstProtScheme) && (CT_XC_1WAY == ConnScheme))
    {
        if (aCardFamily == HDTG_FAM || aCardFamily == HDTG2_FAM)
            group = GROUP_6P;
        else 
            //--- Note: Here if the SrcProtection is DPRING/1P1 then skip the shaed area
            group = (CT_INTERCON_MODE_SPFAB == InterConnectMode) ? (IsHybrid ? GROUP_4H : GROUP_4) : GROUP_4P;
    }
    
    else if ((PROT_GP_UNKNOWN != SrcProtScheme) && (PROT_GP_UNKNOWN != DstProtScheme) && (CT_XC_1WAY == ConnScheme))
        //--- Same as Group four plus the additional connection to DST two
        group = (CT_INTERCON_MODE_SPFAB == InterConnectMode) ? (IsMixed ? GROUP_5M : (IsHybrid ? GROUP_5H : GROUP_5)) : GROUP_5P;
    
    else if ((PROT_GP_UNKNOWN != SrcProtScheme) && (PROT_GP_UNKNOWN == DstProtScheme) && (CT_XC_1WAY_FIXED == ConnScheme))
        //--- Here is the test access connection on a protected line.
        group = GROUP_6;
     
    else if ((PROT_GP_UNKNOWN != SrcProtScheme) && (PROT_GP_UNKNOWN != DstProtScheme) && (CT_XC_1WAY_FIXED == ConnScheme))
        //--- same as group six plus additional connection for the DST two.
        group = GROUP_7;
     
    else if (ConnScheme == CT_XC_1WAY_DRI)
    {
        if ( (SrcProtScheme == PROT_GP_SMTM_UPSR) ||
             (SrcProtScheme == PROT_GP_SNCN)      ||
             (SrcProtScheme == PROT_GP_SNCI)      ||
             (SrcProtScheme == PROT_GP_SNCS) )
        {
            if ( (DstProtScheme == PROT_GP_SMTM_UPSR) ||
                 (DstProtScheme == PROT_GP_SNCN)      ||
                 (DstProtScheme == PROT_GP_SNCI)      ||
                 (DstProtScheme == PROT_GP_SNCS) )  
            {
                //--- This is a special connection for path-level protection, It makes a oneway connection only.
                group = (CT_INTERCON_MODE_SPFAB == InterConnectMode) ? (IsHybrid? GROUP_8H : GROUP_8) : GROUP_8P;
            }
        }
    }
    
// Debug code
#if 0
fc_cout << "Group : " << (uint32) group << endl;
DisplayTerm("SrcOne: ", SrcOne);
DisplayTerm("DstOne: ", DstOne);
DisplayTerm("SrcTwo: ", SrcTwo);
DisplayTerm("DstTwo: ", DstTwo);
#endif

    //--- Based on the group validate the input parameters and  assign value for facility IDs
    switch(group)
    {
        case GROUP_8H:
        case GROUP_8P:
        case GROUP_8:
        case GROUP_7:
        case GROUP_6:
        case GROUP_5M:
        case GROUP_5H:
        case GROUP_5P:
        case GROUP_5:
        case GROUP_4H:
        case GROUP_4P:
        case GROUP_4:
            //--- Validate the SRC two information
            if ((NULL == SrcTwoCfgPtr) || (NULL == SrcTwo.FacStsMap) ||
                (SrcOne.FacStsMap->CountSts() != SrcTwo.FacStsMap->CountSts()))
            {
                if ((NULL == SrcTwoCfgPtr) || (NULL == SrcTwo.FacStsMap))
                    sprintf(aDebugMsg,"Src two cfgPtr or Src two STS map pointer is not valid");
                else 
                    sprintf(aDebugMsg,"Src One STS count (%d) not equal to Src two STS count (%d)",
                            SrcOne.FacStsMap->CountSts(), SrcTwo.FacStsMap->CountSts());
                InputParamsAreValid = false;
            }
            if (SrcTwo.FacData)
                GetFacilityOnSPFAB( &SPFABSrcTwoMuxFac, &SrcTwo);
            else
            {
                FC_REPORT_ERROR(FC_LogicError, "unexpected Null pointer for SrcTwo.FacData");
                InputParamsAreValid = false;
            }
            // fall through 
        case GROUP_3H:
        case GROUP_3P:
        case GROUP_3:
            //--- Validate the DST two information for group 3, 5, 7 and 8
            if (group != GROUP_4 && group != GROUP_4H && group != GROUP_4P && group != GROUP_6)
            {
                if ((NULL == DstTwoCfgPtr) || (NULL == DstTwo.FacStsMap) ||
                    (SrcOne.FacStsMap->CountSts() != DstTwo.FacStsMap->CountSts()))
                {
                    if ((NULL == DstTwoCfgPtr) || (NULL == DstTwo.FacStsMap))
                        sprintf(aDebugMsg,"Dst two cfgPtr or Dst two STS map pointer is not valid");
                    else 
                        sprintf(aDebugMsg,"Src One STS count (%d) not equal to Dst two STS count (%d)",
                                SrcOne.FacStsMap->CountSts(), DstTwo.FacStsMap->CountSts());
                    InputParamsAreValid = false;
                }
                if (DstTwo.FacData)
                    GetFacilityOnSPFAB( &SPFABDstTwoMuxFac, &DstTwo);
                else
                {
                    FC_REPORT_ERROR(FC_LogicError, "unexpected Null pointer for DstTwo.FacData");
                    InputParamsAreValid = false;
                }
            }
            if(aCardFamily == OMM_FAM)
            {
                // OMMX doesn't need mux pointer is valid
            }
            else
            {
                //--- In the following group the mux pointer must be valid if not force an error.
                if ((group == GROUP_3P || group == GROUP_3H) && (SrcOneMuxMapPtr == NULL))
                {
                    sprintf(aDebugMsg,"In group 3P/3H the Src one mux map pointer is not valid");
                    InputParamsAreValid = false;
                }
            }
            // fall through 
        case GROUP_2P:   
        case GROUP_2:
            //--- Here we need to check the STS counts on one of IMUX params.
            stsCount = SrcOne.ImuxLineMapIngress.CountSts();
            stsCount += SrcOne.ImuxPortMapIngress.CountSts();
            if (stsCount == 0)
            {
                stsCount = SrcOne.ImuxLineMapEgress.CountSts();
                stsCount += SrcOne.ImuxPortMapEgress.CountSts();
            }
            //--- Only perform the check for SPFAB mode, and if SrcOne
            //--- is going to be connected/disconnected.
            if ( (InterConnectMode == CT_INTERCON_MODE_SPFAB) && 
                 (IsSrcOneConnectDisconnectAllowed == TRUE) )
            {
                if (SrcOne.FacStsMap->CountSts() != stsCount)
                {
                    sprintf(aDebugMsg,"SPFAB mode the Src one STS map count (%d) is not equal to mux map count (%d)",
                            SrcOne.FacStsMap->CountSts(), stsCount);  
                    InputParamsAreValid = false;
                }
            }

            GetFacilityOnSPFAB( &SPFABSrcOneMuxFac, &SrcOne);
            GetFacilityOnSPFAB( &SPFABDstOneMuxFac, &DstOne);
            // fall through 
        case GROUP_1:
        case GROUP_6P:
            if ((NULL == SrcOneCfgPtr) || (NULL == DstOneCfgPtr) || (NULL == SrcOne.FacStsMap) ||
                (NULL == DstOne.FacStsMap) || (SrcOne.FacStsMap->CountSts() != DstOne.FacStsMap->CountSts()))
            {
                if ((NULL == SrcOneCfgPtr) || (NULL == SrcOne.FacStsMap) ||
                   (NULL == DstOneCfgPtr) || (NULL == DstOne.FacStsMap))
                    sprintf(aDebugMsg,"(SRCOne/DSTOne) cfg or map pointer are not valid");
                else
                    sprintf(aDebugMsg,"Src one STS count(%d) is not equal to DST one STS map count(%d)",
                                SrcOne.FacStsMap->CountSts(), DstOne.FacStsMap->CountSts()); 
                    InputParamsAreValid = FALSE;
            }
            break;
        default:
            sprintf(aDebugMsg,"The group number can not be established");
            InputParamsAreValid = FALSE;

    }

    //-------------------------------- Now do the Connect or Disconnect process ------------------------------
    if (InputParamsAreValid == TRUE)
    {
        sprintf(aDebugMsg, "TSXC_CS->Connect Group based on %s first pass.", aGroupMsg[group]);
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL05, aDebugMsg);
                            
        switch (group)  //--- first pass
        {
            case GROUP_1:
                //--- if Roll and a delete request then we set for post deletion else connection right away.
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, 
                                    DstOneFac, DstOne.FacStsMap, 
                                    ConnType, CT_XC_MAPPING_FIXED, 
                                    Action, XcAllowed, ((Roll && Action == XC_DISCONNECT) || (Roll && IsNanoSwitch)));
                break;

            case GROUP_6P:
                //--- HDTG/HDTG2 DPRING connection.
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, 
                                    DstOneFac, DstOne.FacStsMap, 
                                    ConnType, CT_XC_MAPPING_FLEXIBLE, 
                                    Action, XcAllowed, false);
            // fall through 
            case GROUP_8:               
                if (IsNanoSwitch || IsCesSwitch)
                {
                    SetDestinationSrcInfo(SrcTwo, SrcOne, SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, 
                            SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwoMuxFac, SrcTwoMuxMapPtr, PROT_GP_UNKNOWN, 
                            ConnType, Action, Roll, IsQrsTransitionReq);
                }
            // fall through 
            case GROUP_7:
            case GROUP_6:
            case GROUP_5:
            case GROUP_4:
            case GROUP_3:
            case GROUP_2P:
            case GROUP_2:
                //--- Connecting the SRC One module Line/Port to IMUXL/IMUXP.
                //--- When the Src protection is set to DPRING or 1+1 then do not make this connection.
                //--- becuase the signal protect will make the connection as expected.
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, 
                                    SrcOneMuxFac, SrcOneMuxMapPtr, 
                                    ConnType, CT_XC_MAPPING_FIXED, 
                                    Action, IsSrcOneConnectDisconnectAllowed, Roll, false, 
                                    (IsNanoSwitch && PROT_GP_UNKNOWN == SrcProtScheme), 
                                    (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                    SrcProtScheme);
                
                //--- Regardless of the above connect/disconnect is called or not 
                //--- we still need to update the destination slots. Because there could be broadcast.
                if (IsNanoSwitch || IsCesSwitch)
                {
                    SetSourceMCInfo(SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, DstOne, ConnType, 
                                    Action, Roll, IsQrsTransitionReq, DstOneMuxFac, DstOneMuxMapPtr);
                }
                
                //--- Connecting the DST one module IMUXL/IMUXP to Line/Port. 
                //--- Incase of roll operation then do not remove the connections
                //--- but the roll connection request should be a post operation.
                if ((IsDstOneConnectDisconnectAllowed) && ((false == Roll) || (Action == XC_CONNECT)))
                {
                    ConnectOrDisconnect(DstOne.FacData->GetShelf(), DstOne.FacData->GetSlot(),
                                        DstOneMuxFac, DstOneMuxMapPtr, 
                                        DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, IsDstOneConnectDisconnectAllowed, Roll, true, 
                                        (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme));
                }
                if (IsNanoSwitch || IsCesSwitch)
                {
                    SetDestinationSrcInfo(DstOne, SrcOne, SrcTwo, DstOneMuxFac, DstOneMuxMapPtr, 
                            SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcProtScheme, 
                            ConnType, Action, Roll, IsQrsTransitionReq); 
                }                
                break;
                
            case GROUP_5M:
                 //--- Connect SRC one to DST one on the Same modoule on the Dst module.
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, 
                                    DstOneFac, DstOne.FacStsMap,
                                    ConnType, CT_XC_MAPPING_FLEXIBLE, 
                                    Action, XcAllowed, Roll);

                //--- Connecting the SRC One module Line/Port to IMUXL/IMUXP.
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, 
                                    SrcOneMuxFac, SrcOneMuxMapPtr,
                                    ConnType, CT_XC_MAPPING_FIXED, 
                                    Action, IsSrcOneConnectDisconnectAllowed, Roll, false, 
                                    (IsNanoSwitch && PROT_GP_UNKNOWN == SrcProtScheme), 
                                    (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                    SrcProtScheme);
                SetSourceMCInfo(SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, DstTwo, ConnType, 
                                Action, Roll, IsQrsTransitionReq);
                SetDestinationSrcInfo(DstTwo, SrcOne, SrcTwo, DstTwoMuxFac, DstTwoMuxMapPtr,
                        SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwoMuxFac, SrcTwoMuxMapPtr, PROT_GP_UNKNOWN, 
                        ConnType, Action, Roll, IsQrsTransitionReq);
                break;
                
            case GROUP_5H:
                    //--- Connect SRC one to DST one on the Same modoule
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE, Action, XcAllowed,
                                        Roll, false, (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme));

                    if (IsQrsTransitionReq == false)
                    {
                    //--- Connect SRC two to DST two on the Same modoule the second pair
                    ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                        SrcTwoFac, SrcTwo.FacStsMap, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE, Action, XcAllowed, 
                                        Roll, false, (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme));
                }
                break;

            case GROUP_5P:
                if(aCardFamily == OMM_FAM)
                {
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE_DIST_SEL, Action, true);

                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE_DIST_SEL, Action, true);
                }
                else
                {
                    PortBaseSlot = (SrcOneFac <= LastPort)? SrcOne.FacData->GetSlot() : DstOne.FacData->GetSlot();
                    //--- Connect SRC one to DST one on the Same modoule
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), PortBaseSlot,
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE, Action, XcAllowed);
                    PortBaseSlot = CT_ProtScPairCompMatrix::Instance().GetMateOnPair( PortBaseSlot, aShelfType ); //--- Use the mate Slot
                    if (IsQrsTransitionReq == false)
                    {
                        //--- Connect SRC two to DST two on the Same modoule the second pair
                        ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), PortBaseSlot,
                                            SrcTwoFac, SrcTwo.FacStsMap, DstTwoFac, DstTwo.FacStsMap, 
                                            ConnType, CT_XC_MAPPING_FLEXIBLE, Action, XcAllowed);
                    }
                }

                break;
                
            case GROUP_3H:
                //--- Connect SrcOne --> IMUX
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, 
                                    SrcOneMuxFac, SrcOneMuxMapPtr, 
                                    ConnType, CT_XC_MAPPING_FIXED, 
                                    Action, XcAllowed, Roll, false, 
                                    IsNanoSwitch, (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                    SrcProtScheme);

                //--- Mcast SrcOne --> DstTwo  (Don't worry about DstOne since it's on same card as SrcOne)
                SetSourceMCInfo(SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, DstTwo, ConnType, 
                                Action, Roll, IsQrsTransitionReq);

                //--- DstSrc DstTwo <-- SrcOne
                    SetDestinationSrcInfo(DstTwo, SrcOne, SrcOne, DstTwoMuxFac, DstTwoMuxMapPtr, 
                            SrcOneMuxFac, SrcOneMuxMapPtr, SrcOneMuxFac, SrcOneMuxMapPtr, PROT_GP_UNKNOWN, 
                            ConnType, Action, Roll, IsQrsTransitionReq);

                //--- Connect IMUX --> DstTwo
                    ConnectOrDisconnect(DstTwo.FacData->GetShelf(), DstTwo.FacData->GetSlot(),
                                        DstTwoMuxFac, DstTwoMuxMapPtr, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, XcAllowed, Roll);

                //--- Connect SrcOne --> DstOne  (SrcOne and DstOne on same card)
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                    ConnType, CT_XC_MAPPING_FIXED, Action, XcAllowed, Roll);
                break;

            case GROUP_8H:
            case GROUP_4H:
                //--- Connect SrcOne --> DstOne  (SrcOne and DstOne on same card)
                ConnectOrDisconnect(DstOne.FacData->GetShelf(), DstOne.FacData->GetSlot(),
                                    SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                    ConnType, CT_XC_MAPPING_FLEXIBLE, Action, XcAllowed, Roll);
                break;

            case GROUP_3P:
                if(aCardFamily == OMM_FAM)
                {
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, true);

                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, true);
                }
                else
                {
                    //--- Connect the SRC one to IMUX connection. could be IMUXL or IMUXP based DPRING or UPSR.
                    PortBaseSlot = (SrcOneFac <= LastPort)? SrcOne.FacData->GetSlot() : DstOne.FacData->GetSlot();
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), PortBaseSlot,
                                        SrcOneFac, SrcOne.FacStsMap, 
                                        SrcOneMuxFac, SrcOneMuxMapPtr, 
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, XcAllowed, false, false,
                                        false, (IsCesSwitch || IsNanoSwitch) , SrcOne.TermToImuxConnMapping,
                                        SrcProtScheme);

                    //--- Connnect the DST two IMUX to DST two facility termination.
                    PortBaseSlot = CT_ProtScPairCompMatrix::Instance().GetMateOnPair( PortBaseSlot, aShelfType ); //--- Use the mate Slot
                    ConnectOrDisconnect(DstTwo.FacData->GetShelf(), PortBaseSlot,
                                        DstTwoMuxFac, DstTwoMuxMapPtr, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, XcAllowed);

                    //--- Connect SRC one to DST one on the Same modoule
                    PortBaseSlot = (SrcOneFac <= LastPort)? SrcOne.FacData->GetSlot() : DstOne.FacData->GetSlot();
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), PortBaseSlot,
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, XcAllowed);
                }
                break;

            case GROUP_8P:
            case GROUP_4P:
                if(aCardFamily == OMM_FAM)
                {
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE_DIST_SEL, Action, true);
                }
                else
                {
                    PortBaseSlot = (SrcOneFac <= LastPort)? SrcOne.FacData->GetSlot() : DstOne.FacData->GetSlot();
                    //--- Connect SRC one to DST one on the Same modoule
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), PortBaseSlot,
                                        SrcOneFac, SrcOne.FacStsMap, DstOneFac, DstOne.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FLEXIBLE, Action, XcAllowed);
                }
                break;
        } //--- end of the first pass

        //------------------    Now go head and do the Second pass  ------------------------------------------------------
        sprintf(aDebugMsg, "TSXC_CS->Connect Group based on %s second pass.", aGroupMsg[group]);
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL05, aDebugMsg);
   
        switch(group)   
        {
            case GROUP_5M:
                //--- Connect the SRC-Two module Line/Port to IMUXL/IMUXP.
                if (IsQrsTransitionReq == false)
                {
                    ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                        SrcTwoFac, SrcTwo.FacStsMap, 
                                        SrcTwoMuxFac, SrcTwoMuxMapPtr,
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, IsSrcTwoConnectDisconnectAllowed, Roll, false, 
                                        (IsNanoSwitch && PROT_GP_UNKNOWN == SrcProtScheme), 
                                        (IsCesSwitch || IsNanoSwitch), SrcTwo.TermToImuxConnMapping,
                                        SrcProtScheme);
                    SetSourceMCInfo(SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, DstTwo, ConnType, 
                                    Action, Roll, IsQrsTransitionReq);
                }

                SetDestinationSrcInfo(SrcOne, SrcTwo, SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr,
                        SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcOneMuxFac, SrcOneMuxMapPtr, PROT_GP_UNKNOWN, 
                        ConnType, Action, Roll, IsQrsTransitionReq);

                SetDestinationSrcInfo(DstTwo, SrcTwo, SrcOne, DstTwoMuxFac, DstTwoMuxMapPtr,
                        SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcOneMuxFac, SrcOneMuxMapPtr, PROT_GP_UNKNOWN, 
                        ConnType, Action, Roll, IsQrsTransitionReq);

                if ((IsDstTwoConnectDisconnectAllowed) && ((false == Roll) || (Action == XC_CONNECT)))
                {
                    ConnectOrDisconnect(DstTwo.FacData->GetShelf(), DstTwo.FacData->GetSlot(),
                                        DstTwoMuxFac, DstTwoMuxMapPtr, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, IsDstTwoConnectDisconnectAllowed, 
                                        Roll, true, (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme));
                }
                break;
                
          case GROUP_5H:
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                        SrcOneFac, SrcOne.FacStsMap, 
                                        SrcOneMuxFac, SrcOneMuxMapPtr,
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, IsSrcOneConnectDisconnectAllowed, Roll, false, 
                                        (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme), 
                                        (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                        SrcProtScheme);
                    SetSourceMCInfo(SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwo, ConnType, 
                                    Action, Roll, IsQrsTransitionReq);
                    SetDestinationSrcInfo(SrcTwo, SrcOne, SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, 
                            SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwoMuxFac, SrcTwoMuxMapPtr, PROT_GP_UNKNOWN, 
                            ConnType, Action, Roll, IsQrsTransitionReq);
                //--- fall through and do SRC two connection as well.
            case GROUP_4H:
                    if (IsQrsTransitionReq == false)
                    {
                        ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                            SrcTwoFac, SrcTwo.FacStsMap, 
                                            SrcTwoMuxFac, SrcTwoMuxMapPtr,
                                            ConnType, CT_XC_MAPPING_FIXED, 
                                            Action, IsSrcTwoConnectDisconnectAllowed, Roll, false, 
                                            (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme), 
                                            (IsCesSwitch || IsNanoSwitch), SrcTwo.TermToImuxConnMapping,
                                            SrcProtScheme);
                        SetSourceMCInfo(SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcOne, ConnType, 
                                        Action, Roll, IsQrsTransitionReq);
                    }

                    SetDestinationSrcInfo(SrcOne, SrcTwo, SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, 
                            SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcOneMuxFac, SrcOneMuxMapPtr, PROT_GP_UNKNOWN, 
                            ConnType, Action, Roll, IsQrsTransitionReq);
                break;
                              
            case GROUP_5P:
                    if(aCardFamily == OMM_FAM)
                    {
                        ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                            SrcTwoFac, SrcTwo.FacStsMap, DstTwoFac+1, DstTwo.FacStsMap, 
                                            ConnType, CT_XC_MAPPING_FLEXIBLE_DIST_SEL, Action, true);
                    }
                    else
                    {
                        ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(),
                                            SrcOneFac, SrcOne.FacStsMap, 
                                            SrcOneMuxFac, SrcOneMuxMapPtr,
                                            ConnType, CT_XC_MAPPING_FIXED, 
                                            Action, IsSrcOneConnectDisconnectAllowed, false, false,
                                            false, (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                            SrcProtScheme);
                    }
                //--- fall through and do SRC two connection as well.                    
            case GROUP_4P:
                    if(aCardFamily == OMM_FAM)
                    {
                        ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                            SrcTwoFac, SrcTwo.FacStsMap, DstOneFac+1, DstOne.FacStsMap, 
                                            ConnType, CT_XC_MAPPING_FLEXIBLE_DIST_SEL, Action, true);
                    }
                    else
                    {
                        if (IsQrsTransitionReq == false)
                        {
                            ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                                SrcTwoFac, SrcTwo.FacStsMap, 
                                                SrcTwoMuxFac, SrcTwoMuxMapPtr,
                                                ConnType, CT_XC_MAPPING_FIXED, 
                                                Action, IsSrcTwoConnectDisconnectAllowed, false, false,
                                                false, (IsCesSwitch || IsNanoSwitch), SrcTwo.TermToImuxConnMapping,
                                                SrcProtScheme);
                        }
                    }
                break;

            case GROUP_5:
            case GROUP_4:
                Spfab_XcMapping = CT_XC_MAPPING_FLEXIBLE;

                if (IsQrsTransitionReq == false)
                {
                    //--- Connect the SRC Two module Line/Port to IMUXL/IMUXP.
                    ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                        SrcTwoFac, SrcTwo.FacStsMap, 
                                        SrcTwoMuxFac, SrcTwoMuxMapPtr,
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, IsSrcTwoConnectDisconnectAllowed, Roll, false, 
                                        (IsNanoSwitch && PROT_GP_UNKNOWN == SrcProtScheme), 
                                        (IsCesSwitch || IsNanoSwitch), SrcTwo.TermToImuxConnMapping,
                                        SrcProtScheme);
                
                    //--- Regardless of the above connect/disconnect is called or not 
                    //--- we still need to update the destination slots. Because there could be broadcast.
                    if (IsNanoSwitch || IsCesSwitch)
                    {
                        if (DstTwo.FacData->IsDefault() == false)
                        { 
                            SetSourceMCInfo(SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, DstTwo, ConnType, 
                                            Action, Roll, IsQrsTransitionReq, DstTwoMuxFac, DstTwoMuxMapPtr);
                        }
                        else    //--- Since the destination 2 does not exist then destination one may be uses a unicast 
                        {
                            SetSourceMCInfo(SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, DstOne, ConnType, 
                                            Action, Roll, IsQrsTransitionReq, DstOneMuxFac, DstOneMuxMapPtr);
                        }
                    }
                }
            // fall through 
            case GROUP_7:
            case GROUP_6: 
            case GROUP_3:
            case GROUP_2:
                               
                //--- Connect SRC One to DST One on SPFAB for SPFAB mode only, do nothing for pairmode.
                if (IsTdmSwitch)
                    ConnectOrDisconnectOnSPFAB(SrcOne.FacData->GetShelf(), SPFABSrcOneMuxFac, SrcOneMuxMapPtr,
                                        SPFABDstOneMuxFac, DstOneMuxMapPtr, ConnType, Spfab_XcMapping, Action, Roll);

                if (group == GROUP_2 || group == GROUP_4 || group == GROUP_4H || group == GROUP_6)
                    break;  
                  
                //--- continue for group 3,5, and 7
                //--- Connect DST two module muxline to the facility port/Line
                if ((IsDstTwoConnectDisconnectAllowed) && ((false == Roll) || (Action == XC_CONNECT)))
                {
                    ConnectOrDisconnect(DstTwo.FacData->GetShelf(), DstTwo.FacData->GetSlot(),
                                        DstTwoMuxFac, DstTwoMuxMapPtr, DstTwoFac, DstTwo.FacStsMap, 
                                        ConnType, CT_XC_MAPPING_FIXED, Action, IsDstTwoConnectDisconnectAllowed, 
                                        Roll, true, (IsNanoSwitch && PROT_GP_UNKNOWN == DstProtScheme));
                }
                
                if (IsNanoSwitch || IsCesSwitch)
                {
                    SetDestinationSrcInfo(DstTwo, SrcOne, SrcTwo, DstTwoMuxFac, DstTwoMuxMapPtr, 
                            SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcProtScheme, 
                            ConnType, Action, Roll, IsQrsTransitionReq);
                }
                                
                //--- Connect SRC one to DST two on SPFAB
                if (IsTdmSwitch)
                    ConnectOrDisconnectOnSPFAB( SrcOne.FacData->GetShelf(), SPFABSrcOneMuxFac, SrcOneMuxMapPtr, 
                                                SPFABDstTwoMuxFac, DstTwoMuxMapPtr,ConnType, Spfab_XcMapping, Action, Roll);
                break;
                
            case GROUP_8H:
            case GROUP_8P:
            case GROUP_8:

                if (IsQrsTransitionReq == false)
                {
                    //--- Connect SRC two mux to SRC two facility side
                    ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                        SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcTwoFac, SrcTwo.FacStsMap,
                                        ConnType, CT_XC_MAPPING_FIXED, Action, IsSrcTwoConnectDisconnectAllowed);
                
                    //--- Connect SRC two facility to mux 
                    ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(),
                                        SrcTwoFac, SrcTwo.FacStsMap, 
                                        SrcTwoMuxFac, SrcTwoMuxMapPtr, 
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, IsSrcTwoConnectDisconnectAllowed, false, false,
                                        false, (IsCesSwitch || IsNanoSwitch), SrcTwo.TermToImuxConnMapping,
                                        SrcProtScheme);
                }

                if (IsNanoSwitch || IsCesSwitch)
                {
                    if (IsQrsTransitionReq == false)
                    {
                        // For multiple card case, send traffic to destination since
                        // selector is distributed among cards.
                        if ( group == GROUP_8 )
                        {
                            SetSourceMCInfo(SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr,        // Src
                                            DstOne,                                       // Dst
                                            ConnType, Action, Roll, IsQrsTransitionReq,
                                            DstOneMuxFac, DstOneMuxMapPtr);
                        }

                        // For paired and hybrid case, send traffic to other source since
                        // selector is local to a card.
                        else
                        {
                            SetSourceMCInfo(SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr,        // Src
                                            SrcOne,                                       // Dst
                                            ConnType, Action, Roll, IsQrsTransitionReq);
                        }
                    }

                    if ( group == GROUP_8H ) // GROUP_8 2WDRI does NOT need to listen to SrcTwo
                    {
                        SetDestinationSrcInfo(SrcOne, SrcTwo, SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, 
                                              SrcTwoMuxFac, SrcTwoMuxMapPtr, SrcOneMuxFac, SrcOneMuxMapPtr, PROT_GP_UNKNOWN, 
                                              ConnType, Action, Roll, IsQrsTransitionReq);
                    }
                }

                if (IsTdmSwitch)
                {
                    //--- SRC one to SRC two on SPFAB
                    ConnectOrDisconnectOnSPFAB( SrcOne.FacData->GetShelf(), SPFABSrcOneMuxFac, SrcOneMuxMapPtr, 
                                                SPFABSrcTwoMuxFac, SrcTwoMuxMapPtr, ConnType, CT_XC_MAPPING_FIXED, Action, Roll);
                    //--- Connect SRC One to DST one on SPFAB
                    ConnectOrDisconnectOnSPFAB( SrcOne.FacData->GetShelf(), SPFABSrcOneMuxFac, SrcOneMuxMapPtr,
                                                SPFABDstOneMuxFac, DstOneMuxMapPtr, ConnType, CT_XC_MAPPING_FLEXIBLE, Action, Roll);
                }
                
                if (group == GROUP_8P || group == GROUP_8H)
                {   
                    //--- Connect the SRC one facility to SRC one mux 
                    ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(), // Target card
                                        SrcOneFac, SrcOne.FacStsMap,                           // Src (userPort)
                                        SrcOneMuxFac, SrcOneMuxMapPtr,                         // Dst (imux)
                                        ConnType, CT_XC_MAPPING_FIXED, 
                                        Action, XcAllowed, false, false,
                                        false, (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                        SrcProtScheme);
                    if (IsNanoSwitch || IsCesSwitch)
                    {
                        SetSourceMCInfo(SrcOne, SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwo, ConnType, 
                                        Action, Roll, IsQrsTransitionReq);
                        SetDestinationSrcInfo(SrcTwo, SrcOne, SrcTwo, SrcTwoMuxFac, SrcTwoMuxMapPtr, 
                                SrcOneMuxFac, SrcOneMuxMapPtr, SrcTwoMuxFac, SrcTwoMuxMapPtr, PROT_GP_UNKNOWN, 
                                ConnType, Action, Roll, IsQrsTransitionReq);
                    }
                }
                break;
        }

        //
        // After a disconnect, a connection from Src to Imux may still exist.  This connection's
        // ConnMapping may have changed due to the disconnect.  So, re-apply the connection
        // from Src to Imux with its current ConnMapping.
        //
        if ( (Action == XC_DISCONNECT) &&
             ((aCardType  == CARD_TYPE_SSMX) || (aCardType == CARD_TYPE_SSMD) ||
              (aCardType  == CARD_TYPE_OSM40) || (aCardType == CARD_TYPE_SSM40) || 
              (aCardType == CARD_TYPE_FGSM) || aCardType == CARD_TYPE_OSM20 ||
              aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C ||
              aCardType == CARD_TYPE_OSM1S) &&
             ((IsNanoSwitch == true) || (IsCesSwitch == true)) )
        {
            if (SrcOne.TermToImuxConnMapping != CT_XC_MAPPING_UNSPECIFIED)
            {
                ConnectOrDisconnect(SrcOne.FacData->GetShelf(), SrcOne.FacData->GetSlot(), // Target card
                                    SrcOneFac, SrcOne.FacStsMap,                           // Src (userPort)
                                    SrcOneMuxFac, SrcOneMuxMapPtr,                         // Dst (imux)
                                    ConnType, CT_XC_MAPPING_UNSPECIFIED, 
                                    XC_CONNECT, true, false, false,
                                    IsNanoSwitch, (IsCesSwitch || IsNanoSwitch), SrcOne.TermToImuxConnMapping,
                                    SrcProtScheme);
            }

            if (SrcTwo.TermToImuxConnMapping != CT_XC_MAPPING_UNSPECIFIED)
            {
                ConnectOrDisconnect(SrcTwo.FacData->GetShelf(), SrcTwo.FacData->GetSlot(), // Target card
                                    SrcTwoFac, SrcTwo.FacStsMap,                           // Src (userPort)
                                    SrcTwoMuxFac, SrcTwoMuxMapPtr,                         // Dst (imux)
                                    ConnType, CT_XC_MAPPING_UNSPECIFIED, 
                                    XC_CONNECT, true, false, false,
                                    IsNanoSwitch, (IsCesSwitch || IsNanoSwitch), SrcTwo.TermToImuxConnMapping,
                                    SrcProtScheme);
            }
        }
    }
    else
    {
        char errorMsg[DEBUG_MSG_LEN];
        sprintf(errorMsg,"\nInvalid parameters specified, Connect/Disconnect has failed.\n More info:");
        strcat(errorMsg, aDebugMsg);   
        FC_REPORT_ERROR(FC_LogicError, errorMsg);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::SetDebugLevel(int theValue)
{
    myDebugLevel = theValue;
    myRollActionPtr->SetDebugLevel(theValue);
}

//----------------------------------------------------------------------------------------------------------------------------------               
void TSXC_ConnectService::ConnectOrDisconnect(
            CT_ShelfId   ShelfID, UINT8   SlotID,
            UINT8 SrcFac, const CT_FAC_StsMap* SrcFacStsMap, 
            UINT8 DstFac, const CT_FAC_StsMap* DstFacStsMap, 
            CT_XC_ConnectType ConnType, CT_XC_ConnectMapping Xc_Mapping, 
            XC_ConnAction Action, bool XcAllowed, bool theRoll, bool thePostReq, 
            bool IsNanoSwitch, bool IsCesSwitch, CT_XC_ConnectMapping imuxXcMapping,
            CT_ProtGpType SrcProtScheme)
{
    if ((NULL ==  SrcFacStsMap) || (NULL == DstFacStsMap))
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL06,"Bad input parameter in TSXC_CS->ConnectOrDisconnect()\n");
        return;
    }  
    if (theRoll)
    {
        TSXC_RollConnInfo aCInfo;
        memset(&aCInfo, 0, sizeof(TSXC_RollConnInfo));
        aCInfo.ShelfID      = (UINT8) ShelfID;
        aCInfo.SlotID       = SlotID;
        aCInfo.SrcFac       = SrcFac;
        aCInfo.SrcFacStsMap = *SrcFacStsMap; 
        aCInfo.DstFac       = DstFac;
        aCInfo.DstFacStsMap = *DstFacStsMap; 
        aCInfo.ConnType     = ConnType;
        aCInfo.Xc_Mapping   = Xc_Mapping;
        aCInfo.IsNanoMesh   = IsNanoSwitch;
        aCInfo.XcAllowed    = XcAllowed;
        aCInfo.RollType     = myRollType;
                
        if (XC_DISCONNECT == Action)
             myRollActionPtr->AddRemoveConnection(aCInfo);  
        else
          thePostReq ?  myRollActionPtr->AddPostConnection(aCInfo):
                        myRollActionPtr->AddNewSrcConnection(aCInfo);
    }
    else
    {
        TSXC_ConfigRegion<TSXC_Connect>* aConfigPtr = NULL;
        aConfigPtr = FindTSXCConfigRegion(ShelfID, SlotID);
        if (NULL != aConfigPtr && XcAllowed)
        {
            if (XC_CONNECT == Action)
            {
                // For connections destined to the IMUX on modules that are in Fabric mode,
                // the imux connection mapping indicates if traffic is destined to a distributed
                // selector or not.
                if ( (IsNanoSwitch) || (IsCesSwitch) )
                {
                    switch (aConfigPtr->GetMyCardType())
                    {
                        case CARD_TYPE_SSMX:
                        case CARD_TYPE_SSMD:
                            switch (DstFac)
                            {
                                case XC_SSM_IM_LINE_FACILITY_ID:
                                case XC_SSM_IM_PORT_FACILITY_ID:
                                    Xc_Mapping = imuxXcMapping;

                                    // For SSMs in switched mode with line-level protection,
                                    // XC Mapping must be set to flexible distributed to
                                    // allow hitless AlwaysOn operation.
                                    if ( (SrcProtScheme == PROT_GP_SMTM_LINEAR) ||
                                         (SrcProtScheme == PROT_GP_SMTM_DPRING) ||
                                         (SrcProtScheme == PROT_GP_SMTM_OAPS) )
                                    {
                                        Xc_Mapping = CT_XC_MAPPING_FLEXIBLE_DIST_SEL;
                                    }
                                    break;
                            }
                            break;
                        case CARD_TYPE_OSM40:
                        case CARD_TYPE_SSM40:
                            switch (DstFac)
                            {
                                case XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID:
                                case XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID:
                                    Xc_Mapping = imuxXcMapping;
                                    break;
                            }
                            break;
                        case CARD_TYPE_FGSM:
                            switch (DstFac)
                            {
                                case XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID:
                                    Xc_Mapping = imuxXcMapping;
                                    break;
                            }
                            break;
                        case CARD_TYPE_OSM20:
                            switch (DstFac)
                            {
                                case XC_OSM20_ODUXC_IMUX_FACILITY_ID:
                                    Xc_Mapping = imuxXcMapping;
                                    break;
                            }
                            break;
                        case CARD_TYPE_OSM2S:
                        case CARD_TYPE_OSM2C:
                            switch (DstFac)
                            {
                                case XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID:
                                case XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID:
                                    Xc_Mapping = imuxXcMapping;
                                    break;
                            }
                            break;
                        case CARD_TYPE_OSM1S:
                            switch (DstFac)
                            {
                                case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID:
                                case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID:
                                    Xc_Mapping = imuxXcMapping;
                                    break;
                            }
                            break;
                    }
                }

                aConfigPtr->Connect(SrcFac, *SrcFacStsMap, DstFac, *DstFacStsMap, ConnType, Xc_Mapping);
            }
            else
            {
                aConfigPtr->Disconnect(DstFac, *DstFacStsMap, ConnType);
            }
        }
    }
       
    if (0 != myDebugLevel)
    {
        char aDebugMsg[DEBUG_MSG_LEN];
        sprintf(aDebugMsg,"TSXC_CS->ConnectOrDisconnect(): %sing (%d-%d) %d-%d -> %d-%d(%d) %s %s",
                (XC_CONNECT == Action) ? "Connect":"Disconnect", ShelfID, SlotID,
                SrcFac,SrcFacStsMap->FindLowestInUseSts()+1, 
                DstFac, DstFacStsMap->FindLowestInUseSts()+1,SrcFacStsMap->CountSts(), 
                XcAllowed ? "":" but !allowed", theRoll ? "Roll" : "Normal"); 
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL06+TSXC_DEBUG_LEVEL16,aDebugMsg);
    }        
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::ConnectOrDisconnectOnSPFAB(
            CT_ShelfId ShelfNum,
            UINT8 SrcFac, const CT_FAC_StsMap* SrcFacStsMap, 
            UINT8 DstFac, const CT_FAC_StsMap* DstFacStsMap, 
            CT_XC_ConnectType ConnType, CT_XC_ConnectMapping Xc_Mapping, 
            XC_ConnAction Action, bool theRoll)
{
    if (theRoll)
    {
        for(int spfab = SPFAB_PRI_SLOT; spfab <= SPFAB_SEC_SLOT; spfab++)
        {
            TSXC_ConfigRegion<TSXC_Connect>* SPFABCfgPtr = NULL;
            SPFABCfgPtr = FindTSXCConfigRegion(ShelfNum, spfab);
            if ((NULL != SPFABCfgPtr) && (SPFABCfgPtr->GetMyCardType() == CARD_TYPE_SPFAB))
            {
                TSXC_RollConnInfo   aCInfo;
                memset(&aCInfo, 0, sizeof(TSXC_RollConnInfo));
                aCInfo.ShelfID      = (UINT8) ShelfNum;
                aCInfo.SlotID       = spfab;
                aCInfo.SrcFac       = SrcFac;
                aCInfo.SrcFacStsMap = *SrcFacStsMap; 
                aCInfo.DstFac       = DstFac;
                aCInfo.DstFacStsMap = *DstFacStsMap; 
                aCInfo.ConnType     = ConnType;
                aCInfo.Xc_Mapping   = Xc_Mapping;
                aCInfo.IsNanoMesh   = false;
                
                if (XC_CONNECT == Action)
                    myRollActionPtr->AddSpfabConnection(aCInfo);
                //--- Since, there may be a bridge connections, do not want to remove any 
                //--- connections in the SPFAB module. The agent will remove the connections 
                //--- during the delete roll command is entered.
                /* 
                else
                    myRollActionPtr->AddSpfabRemoveConnection(aCInfo);
                */
                break; //--- exit the for loop as soon as first module is done.
            }
        }    
    }
    else    //--- do the normal connect process with out roll operation
    {
        for(int spfab = SPFAB_PRI_SLOT; spfab <= SPFAB_SEC_SLOT; spfab++)
        {
            TSXC_ConfigRegion<TSXC_Connect>* SPFABCfgPtr = NULL;
            SPFABCfgPtr = FindTSXCConfigRegion(ShelfNum, spfab);
            if ((NULL != SPFABCfgPtr) && (SPFABCfgPtr->GetMyCardType() == CARD_TYPE_SPFAB))
            {
                if (XC_CONNECT == Action)
                    SPFABCfgPtr->Connect(SrcFac, *SrcFacStsMap, DstFac, *DstFacStsMap, ConnType, Xc_Mapping);
                else
                    SPFABCfgPtr->Disconnect(DstFac, *DstFacStsMap, ConnType);
        
                if (0 != myDebugLevel)
                {
                    char aDebugMsg[DEBUG_MSG_LEN];
                    sprintf(aDebugMsg,
                        "TSXC_CS->ConnectOrDisconnectOnSPFAB(): %sing (%d-%d) %d-%d -> %d-%d(%d)",
                        (XC_CONNECT == Action) ? "Connect":"Disconnect", ShelfNum, spfab,  
                        SrcFac,SrcFacStsMap->FindLowestInUseSts()+1, 
                        DstFac, DstFacStsMap->FindLowestInUseSts()+1,SrcFacStsMap->CountSts());
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL06+TSXC_DEBUG_LEVEL16,aDebugMsg);
                }
            }
        }         
    }    
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::GetFacilityOnSPFAB( UINT8 *theFacility, const CT_XcTerm *theTerm)
{
    int aSlot  = theTerm->FacData->GetSlot();
    int offset = 0; // set to invalid
    
    *theFacility = 0; // pre set to invalid facility.
    
    if ((aSlot >= PS_FIRST_SLOT) && (aSlot <SPFAB_PRI_SLOT))
        offset = aSlot;
    else if ((aSlot > SPFAB_SEC_SLOT) && (aSlot <= PS_LAST_SLOT))
        offset = aSlot-2; // this is to skip the two slots 8 and 9.
    
    if (theTerm->FacData->GetPortId() >= CT_AG_LINE_0)
    {
        //--- treat as line mux
        *theFacility = XC_SPFAB_LINE14_FACILITY_ID+offset-1;
    }
    else
    {
        //--- treat as port mux
        *theFacility = XC_SPFAB_LINE0_FACILITY_ID+offset-1;
    } 
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::ReplaceConnection( CT_XcInfo& NewConn, CT_XcInfo& OldConn)
{                  
    CT_XC_ConnectionScheme aConnScheme = CT_XC_1WAY;
    bool IsNanoShelf = ( (GetShelfType(NewConn.SrcOne.FacData->GetShelf()) == OPTICAL_SHELF_NANO_TYPE) ||
                         (GetShelfType(NewConn.SrcOne.FacData->GetShelf()) == PORT_SHELF_NANO_TYPE   )   );
       
    if ((NewConn.ConnScheme == CT_XC_1WAY_DRI) || (NewConn.ConnScheme == CT_XC_2WAY_DRI))
            aConnScheme = CT_XC_1WAY_DRI;

    myRollType = ROLL_TYPE_NONE;
    // For any unprotected connection if the new source and the destination is on the same slot then roll is simplefied.
    if ( (PROT_GP_UNKNOWN == NewConn.SrcProtScheme) && (PROT_GP_UNKNOWN == NewConn.DstProtScheme) &&
         (NewConn.SrcOne.FacData->GetSlot() ==  NewConn.DstOne.FacData->GetSlot()))
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL16,"TSXC_CS->ReplaceConnection() Roll simplified\n");
       
        ConnectRequest(OldConn.SrcOne, OldConn.DstOne,OldConn.SrcTwo, OldConn.DstTwo,
                       OldConn.SrcProtScheme, OldConn.DstProtScheme, aConnScheme, OldConn.ConnType,
                       CT_INTERCON_MODE_SPFAB, XC_DISCONNECT, false);

        ConnectRequest(NewConn.SrcOne, NewConn.DstOne,NewConn.SrcTwo, NewConn.DstTwo,
                       NewConn.SrcProtScheme, NewConn.DstProtScheme, aConnScheme, NewConn.ConnType,
                       CT_INTERCON_MODE_SPFAB, XC_CONNECT, false);
    }
    else
    {
        if (IsNanoShelf)
        {
            bool sameChan = false;
            if (OldConn.DstOne.TermMappedToImuxl == true)
            {
                sameChan = (OldConn.DstOne.ImuxLineMapEgress.CountSts() !=0 && 
                            OldConn.DstOne.ImuxLineMapEgress.FindLowestInUseSts() == 
                            NewConn.DstOne.ImuxLineMapEgress.FindLowestInUseSts());
            }
            else if (OldConn.DstOne.TermMappedToImuxp == true)
            {
                sameChan = (OldConn.DstOne.ImuxPortMapEgress.CountSts() !=0 && 
                            OldConn.DstOne.ImuxPortMapEgress.FindLowestInUseSts() == 
                            NewConn.DstOne.ImuxPortMapEgress.FindLowestInUseSts());                
            }
            if (sameChan)
            {
                myRollType = ROLL_TYPE_COMPLEX;
                XCDEBUG_INFO(TSXC_DEBUG_LEVEL16, "TSXC_CS->Roll() New/Old channels match");
            }
            else
            {
                myRollType = ROLL_TYPE_SIMPLE;
                XCDEBUG_INFO(TSXC_DEBUG_LEVEL16, "TSXC_CS->Roll() New/Old channels mismatch");
            }
        }
        //--- allocate the  necessary vectors for connection information to be stored during
        //--- the next two calls to the function ConnectRequest()
        myRollActionPtr->SetupNextQueueElements();

        ConnectRequest(OldConn.SrcOne, OldConn.DstOne,OldConn.SrcTwo, OldConn.DstTwo,
                       OldConn.SrcProtScheme, OldConn.DstProtScheme, aConnScheme, OldConn.ConnType,
                       CT_INTERCON_MODE_SPFAB, XC_DISCONNECT, true);

        ConnectRequest(NewConn.SrcOne, NewConn.DstOne,NewConn.SrcTwo, NewConn.DstTwo,
                       NewConn.SrcProtScheme, NewConn.DstProtScheme, aConnScheme, NewConn.ConnType,
                       CT_INTERCON_MODE_SPFAB, XC_CONNECT, true);

        if (ROLL_IDLE == myRollActionPtr->GetRollState())
                myRollActionPtr->StartRoll();
    }
}       
//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::CommitPairConns(uint8 FirstShelf, uint8 FirstSlot, uint8 SecondShelf, uint8 SecondSlot)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Invoke this method once all connections for a pair of SMTMs have been processed.
    // This will ensure that half-populated regions are not used to program hardwared since
    // that may cause a traffic loss. 
    // This method is to support the test menu only and not for the agent software.
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    TSXC_ConfigRegion<TSXC_Connect>*    cfgRegPtr    = NULL;
    TSXC_S1McRegion<TSXC_S1MCast>*      aS1McRegionPtr = NULL;
    TSXC_S3RtRegion<TSXC_S3Route>*      aS3RtRegionPtr = NULL;
    uint8   aShelf = FirstShelf;
    uint8   aSlot  = FirstSlot;
    
    for (int i=0; i < 2; i++)
    {    
        if ( (aShelf != 0) && (aSlot != 0) )
        {
            cfgRegPtr      = FindTSXCConfigRegion(aShelf, aSlot);
            aS1McRegionPtr = FindS1McCfgRegion(aShelf, aSlot);
            aS3RtRegionPtr = FindS3RtCfgRegion(aShelf, aSlot);

            if (NULL != cfgRegPtr)
            {
                // cfgRegPtr->IncSeqNum();
                cfgRegPtr->IncModificationCounter();
                cfgRegPtr->UpdateNotify();
                if (NULL != aS1McRegionPtr)
                {
                    // aMCRegionPtr->IncSeqNum();
                    // aMCRegionPtr->IncModificationCounter();
                    aS1McRegionPtr->UpdateNotify(); 
                }            
                if (NULL != aS3RtRegionPtr)
                {
                    // aRTRegionPtr->IncSeqNum();
                    // aRTRegionPtr->IncModificationCounter();
                    aS3RtRegionPtr->UpdateNotify(); 
                }            
            }
        }
        aShelf = SecondShelf;
        aSlot  = SecondSlot;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_FrmCfgRegion<TSXC_Connect>* TSXC_ConnectService::FindXcFrmRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_FrmCfgRegion<TSXC_Connect>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetFrmCfgRegion();
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_MuxCfgRegion<TSXC_MuxCfg>* TSXC_ConnectService::FindXcMuxRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_MuxCfgRegion<TSXC_MuxCfg>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetMuxCfgRegion();
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_ConfigRegion<TSXC_Connect>* TSXC_ConnectService::FindTSXCConfigRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_ConfigRegion<TSXC_Connect>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetAgCfgRegion();
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_S1McRegion<TSXC_S1MCast>* TSXC_ConnectService::FindS1McCfgRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_S1McRegion<TSXC_S1MCast>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetS1McCfgRegion();
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_S1RtRegion<TSXC_S1Route>* TSXC_ConnectService::FindS1RtCfgRegion( CT_ShelfId ShelfNum, uint8 SlotNum)
{
    TSXC_S1RtRegion<TSXC_S1Route>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetS1RtCfgRegion();
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_S3RtRegion<TSXC_S3Route>* TSXC_ConnectService::FindS3RtCfgRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_S3RtRegion<TSXC_S3Route>*   retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetS3RtCfgRegion();
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_S3McRegion<TSXC_S3MCast>* TSXC_ConnectService::FindS3McCfgRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_S3McRegion<TSXC_S3MCast>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetS3McCfgRegion();
    }        

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_S2McRegion<TSXC_S2MCast>* TSXC_ConnectService::FindS2McCfgRegion( CT_ShelfId ShelfNum, UINT16 theMCastId )
{
    TSXC_S2McRegion<TSXC_S2MCast>*  retVal = NULL;
    int anIndex;
    int aMaxNumRegions;

    anIndex = (theMCastId - TSXC_UFAB_MCASTID_START)/TSXC_S2MC_REGION_SIZE;
    aMaxNumRegions = TSXC_NUM_S2MC_REGIONS;
    if (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == DC_CH88_MTERA_INDEX)
    {
        anIndex = (theMCastId)/TSXC_S2MC_REGION_SIZE;
        aMaxNumRegions = TSXC_NUM_S2MC_REGIONS_MTERA;
    }
    
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    if ( (aShelfPtr != NULL) && ( (anIndex >= 0) && (anIndex < aMaxNumRegions)) )
    {
        TSXC_ShelfBaseApp&  xcShelfApp = aShelfPtr->GetXCShelfAppIf().GetXCShelfBaseApp();
        retVal = xcShelfApp.GetS2McCfgRegion(anIndex);
    }   

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_S2McRegion<TSXC_S2MCast>* TSXC_ConnectService::FindS2CMcCfgRegion( UINT16 theMCastId ) // KW should return S2CMC pointer
{

    TSXC_S2McRegion<TSXC_S2MCast>*  retVal = NULL;

    int anIndex = (theMCastId - TSXC_UFAB_MCASTID_START)/TSXC_S2MC_REGION_SIZE;

    if (anIndex >= 0 && anIndex < TSXC_NUM_S2MC_REGIONS)
    {
        TSXC_CssBasedApp&  aCssApp = T6100_MainAppIf::Instance().GetT6100_CssIf().GetT6100_CssXcIf().GetCssBasedApp();
        retVal = aCssApp.GetS2CMcCfgRegion(anIndex);
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
TSXC_PortDataAllocRegion<TSXC_PortDataAlloc>* TSXC_ConnectService::FindPortDataAllocRegion( CT_ShelfId ShelfNum, uint8 SlotNum )
{
    TSXC_PortDataAllocRegion<TSXC_PortDataAlloc>*  retVal = NULL;
    T6100_ShelfIf*        aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(ShelfNum);
    T6100_SlotIf*         aSlotPtr    = aShelfPtr->GetSlotPtr(SlotNum);
    T6100_CardIf*         aCardPtr    = aSlotPtr->GetProvCardPtr();
    if (NULL != aCardPtr)
    {    
        T6100_TelecomIf&      cardXcAppIf = aCardPtr->GetXCAppIf();
        TSXC_BaseApplication& xcApp       = cardXcAppIf.GetXCApp();
        retVal                            = xcApp.GetPortDataAllocRegion();
    }        

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::SetSourceMCInfo(CT_XcTerm& theSrc, UINT8 SrcMuxFac, const CT_FAC_StsMap* SrcMuxFacStsMap, 
                                CT_XcTerm& theDst, CT_XC_ConnectType ConnType, XC_ConnAction Action, bool theRoll,
                                bool theIsQrsTransitionReq, UINT8 DstMuxFac, const CT_FAC_StsMap* DstMuxFacStsMap)
{
    char    aDebugMsg[DEBUG_MSG_LEN];
    int     aChannelOffset;
    int     index;
    UINT8   aShelfId[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN];
    UINT16  aMembers[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN];

    bool IsNanoShelf = ( (GetShelfType(theSrc.FacData->GetShelf()) == OPTICAL_SHELF_NANO_TYPE) ||
                         (GetShelfType(theSrc.FacData->GetShelf()) == PORT_SHELF_NANO_TYPE   )   );
    
    TSXC_S1McRegion<TSXC_S1MCast>* aS1McRegionPtr = NULL;
    TSXC_S1RtRegion<TSXC_S1Route>* aS1RtRegionPtr = NULL;

    aS1McRegionPtr = FindS1McCfgRegion(theSrc.FacData->GetShelf(), theSrc.FacData->GetSlot());
    aS1RtRegionPtr = FindS1RtCfgRegion(theSrc.FacData->GetShelf(), theSrc.FacData->GetSlot());

    if (NULL == aS1McRegionPtr || NULL == aS1RtRegionPtr)
    {
       FC_REPORT_ERROR(FC_LogicError, "TSXC_CS->SetSourceMCInfo(), Invalid pointer of Multicast/Route region");
       return;
    }

    if ( (aChannelOffset = GetChanOffset(SrcMuxFac, theSrc)) == 0xFFFF)
    {
        return;
    }
    int aChan = SrcMuxFacStsMap->FindLowestInUseSts();
    int aChanCount = SrcMuxFacStsMap->CountSts();
    int anIndex = 0;

    if (0 != myDebugLevel)
    {        
        sprintf(aDebugMsg, "TSXC_CS->SetSourceMCInfo()-%s at Slot: %d, CHAN: %d, MCID: %d, MCLM: %Xh  MCPM: %Xh %s", 
                ((XC_CONNECT == Action) ? "   Connect" : "Disconnect"), theSrc.FacData->GetSlot(),
                aChannelOffset+aChan, theSrc.MulticastId, 
                theSrc.MulticastIMUXLMap[0], theSrc.MulticastIMUXPMap[0],theRoll ? "Roll":"Normal");
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL09, aDebugMsg);
    }
    
    //--- During the Roll operation do not update the MC/RT regions instead passed to roll service for later use.
    if (theRoll)
    {
        TSXC_RollConnInfo aCInfo;
        memset(&aCInfo, 0, sizeof(TSXC_RollConnInfo));
        aCInfo.MulticastId = theSrc.MulticastId;
        aCInfo.MulticastIMUXLMap = theSrc.MulticastIMUXLMap[0];
        aCInfo.MulticastIMUXPMap = theSrc.MulticastIMUXPMap[0];
        aCInfo.MulticastIdFlex   = theSrc.MulticastIdFlex;
        aCInfo.MulticastIMUXLMapFlex = theSrc.MulticastIMUXLMapFlex;
        aCInfo.MulticastIMUXPMapFlex = theSrc.MulticastIMUXPMapFlex;
        aCInfo.ChannelIndex = aChannelOffset + aChan;
        aCInfo.ChannelCount = aChanCount;
        myRollActionPtr->SetSourceMC(aCInfo, Action);  
    }
    else
    {
        anIndex = aChannelOffset + aChan;
        if (IsNanoShelf)
        {
            TSXC_ConfigRegion<TSXC_Connect>*  aCfgPtr = NULL;
            aCfgPtr = FindTSXCConfigRegion(theSrc.FacData->GetShelf(), theSrc.FacData->GetSlot());
            if (aCfgPtr == NULL)
            {
               FC_REPORT_ERROR(FC_LogicError, "TSXC_CS->SetSourceMCInfo(), aCfgPtr = NULL");
               return;
            }
            if(aCfgPtr->GetMyCardType() == CARD_TYPE_OSM20)
            {
                int idx = aChannelOffset + aChan;
                //--- Fixed MCastId setup
                (*aS1McRegionPtr)[idx].SetMCastId(theSrc.MulticastId);
                (*aS1McRegionPtr)[idx].SetMCastImuxLMap(theSrc.MulticastIMUXLMap[0]);
                (*aS1McRegionPtr)[idx].SetMCastImuxPMap(theSrc.MulticastIMUXPMap[0]);

                //--- Flexible MCastId setup
                (*aS1McRegionPtr)[idx+XC_MAX_OSM20_FIXED_MCASTID].SetMCastId(theSrc.MulticastIdFlex);
                (*aS1McRegionPtr)[idx+XC_MAX_OSM20_FIXED_MCASTID].SetMCastImuxLMap(theSrc.MulticastIMUXLMapFlex);
                (*aS1McRegionPtr)[idx+XC_MAX_OSM20_FIXED_MCASTID].SetMCastImuxPMap(theSrc.MulticastIMUXPMapFlex);
            }
            else
            {
                for (int count =0; count < aChanCount; count++)
                {
                    int idx = aChannelOffset + aChan + count;
                    //--- Fixed MCastId setup
                    (*aS1McRegionPtr)[idx].SetMCastId(theSrc.MulticastId);
                    (*aS1McRegionPtr)[idx].SetMCastImuxLMap(theSrc.MulticastIMUXLMap[0]);
                    (*aS1McRegionPtr)[idx].SetMCastImuxPMap(theSrc.MulticastIMUXPMap[0]);

                    //--- Flexible MCastId setup
                    (*aS1McRegionPtr)[idx+XC_MAX_FIXED_MCASTID].SetMCastId(theSrc.MulticastIdFlex);
                    (*aS1McRegionPtr)[idx+XC_MAX_FIXED_MCASTID].SetMCastImuxLMap(theSrc.MulticastIMUXLMapFlex);
                    (*aS1McRegionPtr)[idx+XC_MAX_FIXED_MCASTID].SetMCastImuxPMap(theSrc.MulticastIMUXPMapFlex);
                }
            }
        }
        else  // not Nano Shelf
        {
            CT_ShelfType aShelfType  = GetShelfType(theSrc.FacData->GetShelf());

            if (XC_CONNECT == Action)
            {
                if (aShelfType == MTERA_SHELF_TYPE)
                {
                    //
                    // Update Stage2 Mcast for the Fixed McastId
                    //
                    if (theSrc.MulticastId != XC_MCASTID_UNKNOWN)
                    {
                        UpdateS2McGroup(XC_CONNECT, theSrc.MulticastId, theSrc.MulticastIMUXMapMtera);
                    }

                    // Update Stage2 Mcast for the Flex McastId
                    //    Note: Only do this is Fix and Flex McastIds are different.
                    if ( (theSrc.MulticastIdFlex != XC_MCASTID_UNKNOWN) && (theSrc.MulticastIdFlex != theSrc.MulticastId) )
                    {
                        UpdateS2McGroup(XC_CONNECT, theSrc.MulticastIdFlex, theSrc.MulticastIMUXMapMteraFlex);
                    }
                }
                else
                {
                    //
                    // Update Stage2 Mcast for the Fixed McastId
                    //
                    if (theSrc.MulticastId != XC_MCASTID_UNKNOWN)
                    {
                        // Ensure McastId is valid
                        if (theSrc.MulticastId >= TSXC_UFAB_MCASTID_START)
                        {
                            // Calculate contents of mcast
                            for (index =0; index < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; index++)
                            {
                                aShelfId[index]= (UINT8) theSrc.MulticastShelfId[index];
                                aMembers[index]= theSrc.MulticastIMUXLMap[index] | theSrc.MulticastIMUXPMap[index] |
                                                 theSrc.MulticastIMUXL1Map[index] | theSrc.MulticastIMUXP1Map[index] ;
                            }

                            UpdateS2McGroup(XC_CONNECT, theSrc, theSrc.MulticastId, aShelfId, aMembers);
                        }
                        else
                        {
                            FC_REPORT_ERROR(FC_LogicError, "TSXC_CS->SetSourceMCInfo(), Invaild range on S2MCast ID");
                        }
                    }

                    //    Update Stage2 Mcast for the Flex McastId
                    //    Note: Only do this is Fix and Flex McastIds are different.  If they are the same,
                    //          the full info is not provided for Flex McastId and executing code below
                    //          will wipe out what has been done above.
                    if ( (theSrc.MulticastIdFlex != XC_MCASTID_UNKNOWN) && (theSrc.MulticastIdFlex != theSrc.MulticastId) )
                    {
                        // Ensure McastId is valid
                        if (theSrc.MulticastIdFlex >= TSXC_UFAB_MCASTID_START)
                        {
                            // Clear out ALL indices since only index 0 is populated below
                            for (index =0; index < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; index++)
                            {
                                aShelfId[index]=0;
                                aMembers[index]=0;
                            }
                            
                            // Calculate contents of mcast
                            aShelfId[0]= (UINT8) theSrc.MulticastShelfIdFlex;
                            aMembers[0]= theSrc.MulticastIMUXLMapFlex | theSrc.MulticastIMUXPMapFlex |
                                         theSrc.MulticastIMUXL1MapFlex | theSrc.MulticastIMUXP1MapFlex;
                           
                            UpdateS2McGroup(XC_CONNECT, theSrc, theSrc.MulticastIdFlex, aShelfId, aMembers);
                        }
                        else
                        {
                            FC_REPORT_ERROR(FC_LogicError, "TSXC_CS->SetSourceMCInfo(), Invaild range on S2MCast ID Flex");
                        }
                    }
                }
            }
            else  // DISCONNECT
            {
                if (aShelfType == MTERA_SHELF_TYPE)
                {
                    // Update Stage 2 Mcast for OldMcastId
                    if ( (theSrc.OldMulticastId != XC_MCASTID_UNKNOWN) && 
                         (theSrc.OldMCIDInUseFlag == false) )
                    {
                        UpdateS2McGroup(XC_DISCONNECT, theSrc.OldMulticastId, theSrc.MulticastIMUXMapMtera);
                    }

                    // Update Stage 2 Mcast for OldFlexMcastId
                    if ( (theSrc.OldMulticastIdFlex != XC_MCASTID_UNKNOWN) && 
                         (theSrc.OldMCIDInUseFlagFlex == false) &&
                         (theSrc.OldMulticastIdFlex != theSrc.OldMulticastId) )
                    {
                        UpdateS2McGroup(XC_DISCONNECT, theSrc.OldMulticastIdFlex, theSrc.MulticastIMUXMapMteraFlex);
                    }
                }
                else
                {
                    // Update Stage 2 Mcast for OldMcastId
                    if ( (theSrc.OldMulticastId != XC_MCASTID_UNKNOWN) && 
                         (theSrc.OldMCIDInUseFlag == false) )
                    {
                        // Note: aShelfId, aMembers is not used for DISCONNECT
                        UpdateS2McGroup(XC_DISCONNECT, theSrc, theSrc.OldMulticastId, aShelfId, aMembers);
                    }

                    // Update Stage 2 Mcast for OldFlexMcastId
                    if ( (theSrc.OldMulticastIdFlex != XC_MCASTID_UNKNOWN) && 
                         (theSrc.OldMCIDInUseFlagFlex == false) &&
                         (theSrc.OldMulticastIdFlex != theSrc.OldMulticastId) )
                    {
                        // Note: aShelfId, aMembers is not used for DISCONNECT
                        UpdateS2McGroup(XC_DISCONNECT, theSrc, theSrc.OldMulticastIdFlex, aShelfId, aMembers);
                    }
                }
            }
        }
        
        //--- Update the S1 Route for all configuration, Process the connection of multicast and uicast
        if (XC_CONNECT == Action)
        {
            if (theSrc.MulticastId != XC_MCASTID_UNKNOWN) //--- set up the normal multicast connections
            {    
                aS1RtRegionPtr->Connect(anIndex, true, theSrc.MulticastId, ConnType, theSrc.ConnIds, false, 0, 0, 0, NULL, false );
                aS1RtRegionPtr->Connect(anIndex, true, theSrc.MulticastIdFlex, ConnType, theSrc.ConnIds, true, 0, 0, 0, NULL, false);
            }
            else    // Set up the unicast connection
            {
                UINT8 aDstShelf = (UINT8) theDst.FacData->GetShelf();
                UINT8 aDstSlot  = theDst.FacData->GetSlot();
                UINT8 aDstSlice;
                CT_CardType theSrcCardType = aS1RtRegionPtr->GetMyCardType();
                if(theSrcCardType == CARD_TYPE_OSM2S || theSrcCardType == CARD_TYPE_OSM2C || theSrcCardType == CARD_TYPE_OSM1S)
                {
                    aDstSlice = GetDstSlice(theDst, false, DstMuxFac, DstMuxFacStsMap);
                }
                else
                {
                    aDstSlice = GetDstSlice(theDst, false);
                }
                if (aDstSlice != 0xff)
                    aS1RtRegionPtr->Connect(anIndex, false, 0, ConnType, theSrc.ConnIds, false, aDstShelf, aDstSlot, aDstSlice, NULL,  false);
            }
        }
        //--- Update the S1 Route for all configuration, Process the disconnection of multicast and uicast
        else // XC_DISCONNECT
        {
            bool    IsDeletingOkay = false;
            if (theSrc.OldMulticastId != XC_MCASTID_UNKNOWN)
            {
                for (int index =0; index < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; index++)
                {
                    IsDeletingOkay |= (0 == theSrc.MulticastIMUXLMap[index]+theSrc.MulticastIMUXPMap[index]+
                                            theSrc.MulticastIMUXL1Map[index]+theSrc.MulticastIMUXP1Map[index]);
                }
            }
            //--- If the src is involved in broadcast then we do not remove S1 route info for the unicast connection.
            else 
            {
                IsDeletingOkay = !(theSrc.TermToImuxlPath == false && theSrc.TermToImuxpPath == false);
            }

            // Disconnect S1Rt if it is okay to do so
            if (IsDeletingOkay == true)
            {
                aS1RtRegionPtr->Disconnect(anIndex, ConnType, NULL, false);
            }
            // If it is not okay to disconnect S1Rt, reprogram S1Rt to handle cases in which
            // multicastIds have changed (ie Flex now equal to Fix)
            else if ( (theSrc.MulticastId != XC_MCASTID_UNKNOWN) && (theSrc.MulticastId != 0) )
            {    
                aS1RtRegionPtr->Connect(anIndex, true, theSrc.MulticastId,     ConnType, theSrc.ConnIds, false, 0, 0, 0, NULL, false);
                aS1RtRegionPtr->Connect(anIndex, true, theSrc.MulticastIdFlex, ConnType, theSrc.ConnIds, true,  0, 0, 0, NULL, false);
            }
        }
        
        if (IsNanoShelf)
            aS1McRegionPtr->IncModificationCounter();
        aS1RtRegionPtr->IncModificationCounter();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::SetDestinationSrcInfo(
                CT_XcTerm& Dest, CT_XcTerm& SrcOne, CT_XcTerm& SrcTwo,
                UINT8 DstMuxFac,    const CT_FAC_StsMap* DstMuxFacStsMap,
                UINT8 SrcOneMuxFac, const CT_FAC_StsMap* SrcOneMuxFacStsMap,
                UINT8 SrcTwoMuxFac, const CT_FAC_StsMap* SrcTwoMuxFacStsMap,
                const CT_ProtGpType SrcProtScheme, CT_XC_ConnectType   ConnType, 
                XC_ConnAction Action, bool theRoll, bool theIsQrsTransitionReq)
{
    char  aDebugMsg[DEBUG_MSG_LEN];

    if ( (NULL == DstMuxFacStsMap || NULL == SrcOneMuxFacStsMap) ) 
    {
       FC_REPORT_ERROR(FC_LogicError, "TSXC_CS->SetDestinationSrcInfo(), Invaild MUX fac sts map");
       return; 
    }

    CT_ShelfId aDestFacShelfId = Dest.FacData->GetShelf();
    CT_SlotId  aDestFacSlotId  = Dest.FacData->GetSlot();

    bool IsNanoShelf = ( (GetShelfType(aDestFacShelfId) == OPTICAL_SHELF_NANO_TYPE) ||
                         (GetShelfType(aDestFacShelfId) == PORT_SHELF_NANO_TYPE   )   );
    
    TSXC_S3RtRegion<TSXC_S3Route>* aS3RtRegionPtr = NULL;
    TSXC_S3McRegion<TSXC_S3MCast>* aS3McRegionPtr = NULL;
    TSXC_ConfigRegion<TSXC_Connect>*   aConfigPtr = NULL;
    aS3RtRegionPtr = FindS3RtCfgRegion(aDestFacShelfId, aDestFacSlotId);
    aS3McRegionPtr = FindS3McCfgRegion(aDestFacShelfId, aDestFacSlotId);
    aConfigPtr     = FindTSXCConfigRegion(aDestFacShelfId, aDestFacSlotId);
    CT_CardType aDestCardType = CARD_TYPE_UNKNOWN;
    if(aConfigPtr != NULL)
    {
        aDestCardType = aConfigPtr->GetMyCardType();
    }

    if(aDestCardType == CARD_TYPE_OSM2S || aDestCardType == CARD_TYPE_OSM2C || aDestCardType == CARD_TYPE_OSM1S)
    {
        int aSrcloop;
        CT_XcTerm* aSrc;
        CT_FAC_StsMap aSlotDestMembers;
        uint8 aDevNum;
        CT_ChannelId aChanId;

        if (XC_CONNECT == Action)
        {
            if (NULL != aS3McRegionPtr)
            {
                // Setting the S3MC for SRC1 and SRC2
                for (aSrcloop = 0; aSrcloop < 2; aSrcloop++)
                {
                    aSrc = (aSrcloop == 0)? &SrcOne : &SrcTwo;
                    if (aSrcloop == 1 && SrcProtScheme == PROT_GP_UNKNOWN)
                        break; // do not process the unprotected connections

                    // --
                    // -- Program FIX Mcast Id --
                    // --

                    // Clear destination members
                    aSlotDestMembers.Reset();

                    CT_SwitchMulticastMapSet::iterator aSetIter;
            
                    for ( aSetIter = aSrc->MulticastIMUXMapMtera.begin();
                          aSetIter!= aSrc->MulticastIMUXMapMtera.end();
                          aSetIter++ )
                    {
                        if ( (*aSetIter).GetSlotId() == aDestFacSlotId )
                        {
                            aChanId = (*aSetIter).GetIChannelId();
                            aDevNum = (*aSetIter).GetIDeviceNum();

                            // Each device handles 80 channels.  If this is second
                            // device, it is using second set of 80 channels.
                            if (aDevNum == 2)  // TODO - Replace hard-coded value
                            {
                                aChanId += XC_MAX_XC_OSM_ODUXC_IMUX;
                            }
    
                            aSlotDestMembers.AddSts(aChanId);
                        }
                    }

                    if (!aSlotDestMembers.IsEmpty())
                    {
                        aS3McRegionPtr->AddMcGroup(aSrc->MulticastId, aSlotDestMembers, NULL, false);
                        aS3McRegionPtr->IncModificationCounter();
                    }

                    // --
                    // -- Program FLEX Mcast Id --
                    // --
                    if (aSrc->MulticastId != aSrc->MulticastIdFlex)
                    {
                        // Clear destination members
                        aSlotDestMembers.Reset();

                        CT_SwitchMulticastMapSet::iterator aSetIter;
            
                        for ( aSetIter = aSrc->MulticastIMUXMapMteraFlex.begin();
                              aSetIter!= aSrc->MulticastIMUXMapMteraFlex.end();
                              aSetIter++ )
                        {
                            if ( (*aSetIter).GetSlotId() == aDestFacSlotId )
                            {
                                aChanId = (*aSetIter).GetIChannelId();
                                aDevNum = (*aSetIter).GetIDeviceNum();

                                // Each device handles 80 channels.  If this is second
                                // device, it is using second set of 80 channels.
                                if (aDevNum == 2)  // TODO - Replace hard-coded value
                                {
                                    aChanId += 80;  // TODO - Replace hard-coded value
                                }
    
                                aSlotDestMembers.AddSts(aChanId);
                            }
                        }

                        if (!aSlotDestMembers.IsEmpty())
                        {
                            aS3McRegionPtr->AddMcGroup(aSrc->MulticastIdFlex, aSlotDestMembers, NULL, false);
                            aS3McRegionPtr->IncModificationCounter();
                        }
                    }
                }
            }
        }
        else  // Disconnect for OSM2C/S
        {
            if (NULL != aS3McRegionPtr)
            {
                // Don't delete Mcast groups if this is a Qrs Transition Request
                if (theIsQrsTransitionReq == false)
                {
                    // Removing the S3MC for SRC1 and SRC2
                    for (aSrcloop = 0; aSrcloop < 2; aSrcloop++)
                    {
                        aSrc = (aSrcloop == 0)? &SrcOne : &SrcTwo;
                        if (aSrcloop == 1 && SrcProtScheme == PROT_GP_UNKNOWN)
                            break; // do not process the unprotected connections

                        if (!aSrc->OldMCIDInUseFlag) 
                            aS3McRegionPtr->DeleteMcGroup(aSrc->OldMulticastId, NULL, false);
                        if (!aSrc->OldMCIDInUseFlagFlex)
                            aS3McRegionPtr->DeleteMcGroup(aSrc->OldMulticastIdFlex, NULL, false);
                    }
                }
                aS3McRegionPtr->IncModificationCounter();
            }
        }
    }
    else if (aS3RtRegionPtr != NULL)
    {
        int aChannelOffset;
        int aSrcOneChanOffset;
        int aSrcTwoChanOffset;

        aChannelOffset    = GetChanOffset(DstMuxFac, Dest);
        aSrcOneChanOffset = GetChanOffset(SrcOneMuxFac, SrcOne);
        if ( (aChannelOffset    == 0xFFFF) ||
             (aSrcOneChanOffset == 0xFFFF) )
        {
            return;
        }

        aSrcTwoChanOffset = (SrcProtScheme != PROT_GP_UNKNOWN) ? GetChanOffset(SrcTwoMuxFac, SrcTwo) : 0;
        if (aSrcTwoChanOffset == 0xFFFF)
        {
            return;
        }

        int aChan = DstMuxFacStsMap->FindLowestInUseSts();
        int aChanCount = DstMuxFacStsMap->CountSts();
        uint8 aSrcOneSlot = SrcOne.FacData->GetSlot();
        uint8 aSrcTwoSlot = (SrcProtScheme != PROT_GP_UNKNOWN) ? SrcTwo.FacData->GetSlot():0;
        uint8 aSrcOneShelf = (uint8) SrcOne.FacData->GetShelf();
        uint8 aSrcTwoShelf = (SrcProtScheme != PROT_GP_UNKNOWN) ? (uint8) SrcTwo.FacData->GetShelf():0;
                
        int aSrcOneChan  =  SrcOneMuxFacStsMap->FindLowestInUseSts() + 1 + aSrcOneChanOffset;
        int aSrcTwoChan  =  (SrcProtScheme != PROT_GP_UNKNOWN) ? 
                (SrcTwoMuxFacStsMap->FindLowestInUseSts() + 1 + aSrcTwoChanOffset) : 0;
        
        
        //--- Determine whether to remove the egress info or not.
        bool aDeleteOneAllowed = false;
        bool aDeleteTwoAllowed = false;
        if (IsNanoShelf)
        {
            //--- In the Nano when the IMUX channels are shared for the TAP or on other ports then 
            //--- the delete will not remove S3Rt Information.
            if (Action == XC_DISCONNECT)
            {
                UINT16  aMUXMap;
                aMUXMap = (DstMuxFac == XC_SSM_IM_LINE_FACILITY_ID) ? 
                         (SrcOne.MulticastIMUXLMap[0] | SrcOne.MulticastIMUXLMapFlex) : 
                         (SrcOne.MulticastIMUXPMap[0] | SrcOne.MulticastIMUXPMapFlex) ;
                aMUXMap &= (1 << (Dest.FacData->GetSlot()-1));
                aDeleteOneAllowed = aMUXMap == 0;
                if (SrcProtScheme != PROT_GP_UNKNOWN)
                {
                    aMUXMap = (DstMuxFac == XC_SSM_IM_LINE_FACILITY_ID) ? 
                             (SrcTwo.MulticastIMUXLMap[0] | SrcTwo.MulticastIMUXLMapFlex) :
                             (SrcTwo.MulticastIMUXPMap[0] | SrcTwo.MulticastIMUXPMapFlex) ;
                    aMUXMap &= (1 << (Dest.FacData->GetSlot()-1));
                    aDeleteTwoAllowed = aMUXMap == 0;
                }
            }
        }
        else
        {
            aDeleteOneAllowed = !(SrcOne.TermToImuxlPath == false && SrcOne.TermToImuxpPath == false);
            aDeleteTwoAllowed = (SrcProtScheme != PROT_GP_UNKNOWN && aDeleteOneAllowed);
        }

        if (0 != myDebugLevel)
        {
            char    aMark1 = (XC_DISCONNECT == Action && !aDeleteOneAllowed) ? '*' : '-';
            char    aMark2 = (XC_DISCONNECT == Action && !aDeleteTwoAllowed && SrcProtScheme != PROT_GP_UNKNOWN) ? '*' : '-';
            sprintf(aDebugMsg, "TSXC_CS->SetDestinationSrcInfo()-%s for Slot: %d, CHAN: %d (%d), SrcOne: (%d)-%d%c, SrcTwo: (%d)-%d%c", 
                    ((XC_CONNECT == Action) ? "Connecting" : "Disconnect"), (int) Dest.FacData->GetSlot(),
                    aChannelOffset+aChan, aChanCount, aSrcOneSlot, aSrcOneChan, aMark1, aSrcTwoSlot, aSrcTwoChan, aMark2);
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL10, aDebugMsg);
        }
        
        //--- If roll connect request then update 
        if (theRoll && XC_CONNECT == Action)
        {
            myRollActionPtr->SetRouteInfo(Dest.FacData->GetShelf(), Dest.FacData->GetSlot(), 
                                            (aChannelOffset + aChan), aSrcOneChan, aSrcOneSlot);
        }

        int anIndex = aChannelOffset + aChan;
        int aSrcloop;
        CT_XcTerm*  aSrc = NULL;

        if (XC_CONNECT == Action)
        {
            aS3RtRegionPtr->Connect(aSrcOneShelf, aSrcOneSlot, aSrcOneChan, anIndex, ConnType, SrcOne.ConnIds, NULL, false);
            if ( (SrcProtScheme != PROT_GP_UNKNOWN) && (theIsQrsTransitionReq == false) )
                aS3RtRegionPtr->Connect(aSrcTwoShelf, aSrcTwoSlot, aSrcTwoChan, anIndex, ConnType, SrcTwo.ConnIds, NULL, false);

            if (!IsNanoShelf && NULL != aS3McRegionPtr)
            {
                // Setting the S3MC for SRC1 and SRC2
                for (aSrcloop = 0; aSrcloop < 2; aSrcloop++)
                {
                    aSrc = (aSrcloop == 0)? &SrcOne : &SrcTwo;
                    if (aSrcloop == 1 && SrcProtScheme == PROT_GP_UNKNOWN)
                        break; // do not process the unprotected connections
                    //--- now setup the S3Mc for appropriate source
                    UINT16 aMuxLMap =0;
                    UINT16 aMuxL1Map =0;
                    UINT16 aMuxPMap =0;
                    UINT16 aMuxP1Map =0;
                    UINT16 aDstSlotMap =0;
                    aDstSlotMap = GetSlotMap(Dest);
                    for (int index =0; index < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; index++)
                    {
                        UINT8 aShelfId = (UINT8) aSrc->MulticastShelfId[index];
                        if (aShelfId == Dest.FacData->GetShelf())
                        {
                            aMuxLMap  =  aSrc->MulticastIMUXLMap[index];
                            aMuxL1Map =  aSrc->MulticastIMUXL1Map[index];
                            aMuxPMap  =  aSrc->MulticastIMUXPMap[index];
                            aMuxP1Map =  aSrc->MulticastIMUXP1Map[index];
                            break;
                        }
                    }

                    aS3McRegionPtr->AddMcGroup(aSrc->MulticastId, aDstSlotMap,
                                               aMuxLMap, aMuxL1Map, 
                                               aMuxPMap, aMuxP1Map,
                                               NULL, false);

                    aS3McRegionPtr->AddMcGroup(aSrc->MulticastIdFlex, aDstSlotMap,
                                               aSrc->MulticastIMUXLMapFlex, aSrc->MulticastIMUXL1MapFlex, 
                                               aSrc->MulticastIMUXPMapFlex, aSrc->MulticastIMUXP1MapFlex,
                                               NULL, false);
                }
                aS3McRegionPtr->IncModificationCounter();
            }
        }
        else if (!theRoll)
        {
            if (aDeleteOneAllowed)
                aS3RtRegionPtr->Disconnect(aSrcOneShelf, aSrcOneSlot, aSrcOneChan, anIndex, ConnType, SrcOne.OldConnIds, NULL, false);
            if ( (aDeleteTwoAllowed) && (theIsQrsTransitionReq == false) )
                aS3RtRegionPtr->Disconnect(aSrcTwoShelf, aSrcTwoSlot, aSrcTwoChan, anIndex, ConnType, SrcTwo.OldConnIds, NULL, false);
            if (!IsNanoShelf && NULL != aS3McRegionPtr)
            {
                // Don't delete Mcast groups if this is a Qrs Transition Request
                if (theIsQrsTransitionReq == false)
                {
                    // Removing the S3MC for SRC1 and SRC2
                    for (aSrcloop = 0; aSrcloop < 2; aSrcloop++)
                    {
                        aSrc = (aSrcloop == 0)? &SrcOne : &SrcTwo;
                        if (aSrcloop == 1 && SrcProtScheme == PROT_GP_UNKNOWN)
                            break; // do not process the unprotected connections
                        if (!aSrc->OldMCIDInUseFlag) 
                            aS3McRegionPtr->DeleteMcGroup(aSrc->OldMulticastId, NULL, false);
                        if (!aSrc->OldMCIDInUseFlagFlex)
                            aS3McRegionPtr->DeleteMcGroup(aSrc->OldMulticastIdFlex, NULL, false);
                    }
                }
                aS3McRegionPtr->IncModificationCounter();
            }
        }

        aS3RtRegionPtr->IncModificationCounter();
        if (theRoll && XC_CONNECT == Action)
        {
            aS3RtRegionPtr->UpdateNotify();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::UpdateS2McGroup(
  XC_ConnAction     theAction,
  CT_XcTerm&        theSrc,
  uint16            theMcastId,
  uint8             theMcastShelfId[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN],
  uint16            theMcastMembers[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN])
{
    TSXC_S2McRegion<TSXC_S2MCast>* aS2MCRegionPtr;
    uint32                         aShelfIndex;
    CT_ShelfId                     aShelfId;

    //
    // Update Stage 2 Mcast Region for all shelves in switching domain.
    //
    for(aShelfIndex = 0; aShelfIndex < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; aShelfIndex++)
    {
        if ( (aShelfId = theSrc.SwitchDomainShelfId[aShelfIndex]) != UNKNOWN_SHELF_ID)
        {
            aS2MCRegionPtr = FindS2McCfgRegion(aShelfId, theMcastId);
            if (NULL == aS2MCRegionPtr)
            {
                FC_REPORT_ERROR(FC_LogicError, "TSXC_CS->SetSourceMCInfo(), Invaild S2MCast ID");
                return; // do not continue with null pointer.
            }

            if (theAction == XC_CONNECT)
            {
                aS2MCRegionPtr->AddMcGroup(theMcastId, theMcastShelfId, theMcastMembers, NULL, false);
            }
            else
            {
               aS2MCRegionPtr->DeleteMcGroup(theMcastId, NULL, false);
            }

            aS2MCRegionPtr->IncModificationCounter();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------
void TSXC_ConnectService::UpdateS2McGroup(
  XC_ConnAction theAction,
  uint16 theMcastId,
  CT_SwitchMulticastMapSet& theMcastImuxMap)
{
    TSXC_S2McRegion<TSXC_S2MCast>* s2McRegPtr;
    uint8 aShelfId[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN];
    uint16 aMembers[MAX_SHELVES_PER_CSS_SWITCH_DOMAIN];
    uint8 aMteraShelfId = MTERA_SHELF_1;
    uint16 aDstSlots;
    uint8 aSlotId;
    uint8 aBitPos;
    CT_SwitchMulticastMapSet::iterator aSetIter;

    // Init shelf and member arrays
    for(int aShelf = 0; aShelf < MAX_SHELVES_PER_CSS_SWITCH_DOMAIN; aShelf++)
    {
        aShelfId[aShelf] = 0;
        aMembers[aShelf] = 0;
    }

    s2McRegPtr = FindS2McCfgRegion(aMteraShelfId , theMcastId);
    if (theAction == XC_CONNECT)
    {
        // For Mtera, only one shelf exists
        aShelfId[0] = aMteraShelfId;

        // Init destination slot bit-field
        aDstSlots = 0;

        // Add slots from IMUXL Map
        for ( aSetIter = theMcastImuxMap.begin();
              aSetIter!= theMcastImuxMap.end();
              aSetIter++ )
        {
            aSlotId = (*aSetIter).GetSlotId();
            aBitPos = S2MCSlotToBitMtera(aSlotId);
            aDstSlots |= (1 << aBitPos);
        }

        // Set members
        aMembers[0] = aDstSlots;

        s2McRegPtr->AddMcGroup(theMcastId, aShelfId, aMembers, NULL, false);
    }
    else
    {
        s2McRegPtr->DeleteMcGroup(theMcastId, NULL, false);
    }

    s2McRegPtr->IncModificationCounter();
}

//---------------------------------------------------------------------------------------
uint8 TSXC_ConnectService::S2MCSlotToBitMtera(
  uint8 theSlotId)
{
    uint8 aBitPos;

    if (theSlotId <= 7)
    {
        aBitPos = theSlotId - 1;
    }
    else
    {
        aBitPos = theSlotId - 3;
    }

    return aBitPos;
}

//----------------------------------------------------------------------------------------------------------------------------------
uint16 TSXC_ConnectService::GetSlotMap(CT_XcTerm& Dest)
{
    //--- Note the HCSS shelf the slots 2..8 as bits 0..6 and slots 12..18 as bits 7..13
    //--- but all other shelf the slots 1..16 as bits 0..15  
    
    uint16          aSlotMap;
    CT_ShelfType    aShelfType  = GetShelfType(Dest.FacData->GetShelf());

    aSlotMap =  1 << (Dest.FacData->GetSlot()-1); // Make it for the Non HCSS shelf    
    if (aShelfType == PORT_SHELF_HCSS_TYPE)
    {
        if (Dest.FacData->GetSlot() <= 8)
            aSlotMap =  1 << (Dest.FacData->GetSlot()-2);
        else
            aSlotMap =  1 << (Dest.FacData->GetSlot()-(3+2));  
    }

    return aSlotMap;
}

//----------------------------------------------------------------------------------------------------------------------------------
CT_ShelfType TSXC_ConnectService::GetShelfType(CT_ShelfId theShelfId)
{
    T6100_ShelfIf*  aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theShelfId);
    CT_ShelfType    aShelfType = UNKNOWN_SHELF;

    // Avoid pulling in CFG_Misc for MTERA/FPCA by checking subnode config
    if (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == DC_CH88_MTERA_INDEX)
    {
        aShelfType = MTERA_SHELF_TYPE;
    }
    else
    {
#if PSOSP
        CFG_MiscBaseApplication* aMiscApp = 
          static_cast<CFG_MiscBaseApplication*>(aShelfPtr->GetMiscIf().GetCfgShelfAppPtr());
        CFG_MiscCfgRegion* aMiscCfgRegion = 
          static_cast<CFG_MiscCfgRegion*>(aMiscApp->GetCfgRegion());
        aShelfType = (*aMiscCfgRegion)[0].GetShelfType();
#else
        CFG_MiscBaseApplication* aMiscApp = 
          dynamic_cast<CFG_MiscBaseApplication*>(aShelfPtr->GetMiscIf().GetCfgShelfAppPtr());
        if (aMiscApp)
        {
            CFG_MiscCfgRegion* aMiscCfgRegion = 
              dynamic_cast<CFG_MiscCfgRegion*>(aMiscApp->GetCfgRegion());
            if (aMiscCfgRegion)
                aShelfType = (*aMiscCfgRegion)[0].GetShelfType();
        }
#endif
    }

    return aShelfType;
}

//----------------------------------------------------------------------------------------------------
uint16 TSXC_ConnectService::GetChanOffset(UINT8 theMuxFac, CT_XcTerm& theTerm)
{
    uint16   aChannelOffset = 0xFFFF;
    char     errMsg[80];
    TSXC_ConfigRegion<TSXC_Connect>*  aSrcOneCfgPtr;

    aSrcOneCfgPtr = FindTSXCConfigRegion(theTerm.FacData->GetShelf(), theTerm.FacData->GetSlot());
    if (NULL == aSrcOneCfgPtr)
    {
        FC_REPORT_ERROR(FC_LogicError, "unexpected null pointer for aSrcOneCfgPtr");
        return aChannelOffset; // do not continue with null pointer.
    }

    switch (aSrcOneCfgPtr->GetMyCardType())
    {
        case CARD_TYPE_SSMX: 
        case CARD_TYPE_SSMD:
    switch (theMuxFac)
    {
        case XC_SSM_IM_LINE_FACILITY_ID:             aChannelOffset = 0;   break;
        case XC_SSM_IM_PORT_FACILITY_ID:             aChannelOffset = 192; break;
            }
            break;

        case CARD_TYPE_OSM40:
        case CARD_TYPE_SSM40:
            switch (theMuxFac)
            {
        case XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID:  aChannelOffset = 0;   break;
                case XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID:  aChannelOffset = 16;  break;
            }
            break;

        case CARD_TYPE_FGSM:
            aChannelOffset = 0;
            break;

        case CARD_TYPE_OSM20:
            aChannelOffset = 0;
            break;

        case CARD_TYPE_OSM2S:
        case CARD_TYPE_OSM2C:
            switch (theMuxFac)
            {
                case XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID:  aChannelOffset = 0;   break;
                case XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID:  aChannelOffset = 80;  break;
            }
            break;
        case CARD_TYPE_OSM1S:
            switch (theMuxFac)
            {
                case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID:  aChannelOffset = 0;   break;
                case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID:  aChannelOffset = 16;  break;
            }
            break;
    }

    if (aChannelOffset == 0xFFFF)
    {
        sprintf(errMsg, "TSXC_CS->GetChanOffset(), Invalid cardType = %d, and/or Invalid muxFac = %d", 
                        aSrcOneCfgPtr->GetMyCardType(), theMuxFac);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return aChannelOffset;
}

//----------------------------------------------------------------------------------------------------
uint8 TSXC_ConnectService::GetDstSlice(CT_XcTerm& theDstTerm, bool useDstLookup, UINT8 DstMuxFac, const CT_FAC_StsMap* DstMuxFacStsMap)
{
    CT_CardType                       aCardType = CARD_TYPE_UNKNOWN;
    uint8                             aSlice;
    char                              errMsg[80];
    uint16                            aChannelOffset = 0xFFFF;
    int                               aChan = 0;
    TSXC_ConfigRegion<TSXC_Connect>*  anXcCfgPtr;

    anXcCfgPtr = FindTSXCConfigRegion(theDstTerm.FacData->GetShelf(), theDstTerm.FacData->GetSlot());
    if (anXcCfgPtr)
        aCardType  = anXcCfgPtr->GetMyCardType();
    aSlice     = 0xFF;

    switch (aCardType)
    {
        //
        // On SSM, either 
        //
        //   1 - Find IMUX based on what is connected to destination
        //       (for arrow selector cases)
        //   2 - Find IMUX based on whether destination is port or dwdm.
        //
        case CARD_TYPE_SSMX:
        case CARD_TYPE_SSMD:
            if (useDstLookup == true)
            {
                switch(anXcCfgPtr->GetInputFacilityFromDst(theDstTerm))
                {
                    // InputFac is IMUXL so set slice to IMUXL
                    case XC_SSM_IM_LINE_FACILITY_ID:
                        aSlice = 0;       /* IMUXL */
                        break;

                    // InputFac is IMUXP so set slice to IMUXP
                    case XC_SSM_IM_PORT_FACILITY_ID:
                        aSlice = 1;       /* IMUXP */
                        break;

                    // InputFac is on the port-side.  Arrow Selector
                    // chooses between port-side and IMUXP so
                    // set slice to IMUXP
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
                        aSlice = 1;       /* IMUXP */
                        break;

                    // InputFac is on the dwdm-side.  Arrow Selector
                    // chooses between dwdm-side and IMUXL so
                    // set slice to IMUXL
                    case XC_SSM_DWDM_FACILITY_ID:
                        aSlice = 0;       /* IMUXL */
                        break;

                    default:
                        sprintf(errMsg, "TSXC_ConnectService::GetDstSlice(), GetInputFacilityFromDst returns %d",
                                anXcCfgPtr->GetInputFacilityFromDst(theDstTerm));
                        FC_REPORT_ERROR(FC_LogicError, errMsg);
                }
            }
            else
            {
                aSlice = 1;       /* IMUXP */
                if (theDstTerm.FacData->GetPortId() >= CT_AG_LINE_0)
                {
                    aSlice = 0;   /* IMUXL */
                }
            }

            break;

        //
        // On OSM40/SSM40, the links to the FPGA associated with the first
        // HyPhy are Slices 0 & 1, and the links to the FPGA associated with the
        // second HyPhy are Slices 2 & 3.
        // 
        // The slice to use is specified by the UniSpauiId field.
        //
        case CARD_TYPE_OSM40:
        case CARD_TYPE_SSM40:
            switch (theDstTerm.UniSpauiId)
            {
                case CT_XC_SpauiId_IMUXL:    aSlice = 0;  break;
                case CT_XC_SpauiId_IMUXL1:   aSlice = 1;  break;
                case CT_XC_SpauiId_IMUXP:    aSlice = 2;  break;
                case CT_XC_SpauiId_IMUXP1:   aSlice = 3;  break;
            }
            break;

        case CARD_TYPE_FGSM:
        case CARD_TYPE_OSM20:
            aSlice = 0;
            break;
        case CARD_TYPE_OSM2S:
        case CARD_TYPE_OSM2C:
        case CARD_TYPE_OSM1S:
            aChannelOffset = GetChanOffset(DstMuxFac, theDstTerm);
            if(aChannelOffset == 0xFFFF || DstMuxFacStsMap == NULL)
            {
                break;
            }
            aChan = DstMuxFacStsMap->FindLowestInUseSts();
            aSlice = (uint8)(aChannelOffset + aChan);
            break;

        default:
            FC_REPORT_ERROR(FC_LogicError,"unknown card type");
    }

    if (aSlice == 0xFF)
    {
        sprintf(errMsg, "TSXC_ConnectService::GetSlice(), aCardType = %d, PortId = %d",
                aCardType, theDstTerm.FacData->GetPortId());
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return aSlice;
}

//----------------------------------------------------------------------------------------------------
uint8 TSXC_ConnectService::GetDstSlice(CT_Port& theDstTerm)
{
    CT_XcTerm       aDstKeepTerm;
    CT_AG_PortId    anAgPortId;
    char            errMsg[80];
    CT_CardFamily   aCardFamily = CARD_FAM_UNKNOWN;
    T6100_ShelfIf*  aShelfPtr   = T6100_MainAppIf::Instance().GetShelfPtr(theDstTerm.GetShelfId());
    T6100_SlotIf*   aSlotPtr    = aShelfPtr->GetSlotPtr(theDstTerm.GetSlotId());
    T6100_CardIf*   aCardPtr    = aSlotPtr->GetProvCardPtr();

    if (aCardPtr)
    {
        // Retrieving card family based on GetProvCardPtr() does not work for MTERA.
        // So, explicitly set cardFamily for MTERA.
        CT_ShelfType aShelfType  = GetShelfType(theDstTerm.GetShelfId());
        if (aShelfType == MTERA_SHELF_TYPE)
        {
            aCardFamily = OSM_FAM;
        }
        else
        {
            aCardFamily = aCardPtr->GetCardFamily();
        }
    }
    else
    {
        FC_REPORT_ERROR(FC_LogicError,"unknown card family");
        return 0xff; // No need to continue 
    }


    if ( aCardFamily == SSM_FAM )
    {
        anAgPortId =  CT_Map_PortId::GetSsmAGPortId(FAC_SUBTYPE_UNKNOWN, theDstTerm.GetPortId());
    }    
    else if ( aCardFamily == SSM40_FAM )
    {
        anAgPortId =  CT_Map_PortId::GetSsm40AGPortId(FAC_SUBTYPE_UNKNOWN, theDstTerm.GetPortId());
    }
    else if ( aCardFamily == OSM_FAM )
    {
        anAgPortId =  CT_Map_PortId::GetOsmAGPortId(FAC_SUBTYPE_UNKNOWN, theDstTerm.GetPortId());
    }
    else
    {
        sprintf(errMsg, "No slices for aCardFamily = %d", aCardFamily.GetCardFamily());
        FC_REPORT_ERROR(FC_LogicError, errMsg);
        return 0xff; // No need to continue 
    }

    CT_StsXcFacData  aDstKeepFac(XC_STS1,                        // Unused
                                 theDstTerm.GetShelfId(),
                                 theDstTerm.GetSlotId(),
                                 FAC_TYPE_UNKNOWN,               // Unused
                                 anAgPortId,
                                 theDstTerm.GetChannelId());

    aDstKeepTerm.FacData    = &aDstKeepFac;

    return GetDstSlice(aDstKeepTerm, true);
}

//----------------------------------------------------------------------------------------------------------------------------------
bool TSXC_ConnectService::IsLineLevelProtScheme(const CT_ProtGpType theProtScheme)
{
    bool retVal;

    switch (theProtScheme)
    {
        case PROT_GP_SMTM_LINEAR:
        case PROT_GP_SMTM_DPRING:
        case PROT_GP_SMTM_OAPS:
            retVal = true;
            break;

        default:
            retVal = false;
            break;
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------------------

void TSXC_ConnectService::DisplayTerm(char termId[30], CT_XcTerm& Term)
{
    fc_cout << termId << " :" << endl;
    if ((NULL != Term.FacData) && (Term.FacData->IsDefault() == false))
    {
        fc_cout << "Shelf : " << (uint32) Term.FacData->GetShelf()  << endl;
        fc_cout << "Slot  : " << (uint32) Term.FacData->GetSlot()   << endl;
        fc_cout << "Port  : " << (uint32) Term.FacData->GetPortId() << endl;
    }
    else
    {
        fc_cout << "Default" << endl;
    }

    fc_cout << endl;

    return;
}

//-------------------------------------------------- End of this file --------------------------------------------------------------
