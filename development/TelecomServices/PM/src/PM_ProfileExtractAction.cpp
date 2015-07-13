/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTMU, SSM, HDTG.
 AUTHOR   :     Michael Sharkey
--------------------------------------------------------------------------*/

#include <PM/PM_ProfileExtractAction.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_HopNearEndSubApplication.h>
#include <PM/PM_OduSubApplication.h>
#include <PM/PM_OduGaugeSubApplication.h>
#include <PM/PM_TcmSubApplication.h>
#include <PM/PM_TcmGaugeSubApplication.h>
#include <PM/PM_ProfileTableRegion.h>
#include <PM/PM_TypeHopNearEnd.h>
#include <EPM/PM_TypeOdu.h>
#include <EPM/PM_TypeTcm.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbCfgLayer.h>
#include <PM/PM_BbCfg.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Hop.h>
#include <Configuration/CFG_Odu.h>
#include <Configuration/CFG_Tcm.h>
#include <T6100/T6100_MainAppIf.h>
#include <TelCommon/TEL_BbObjectBase.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_PortMap.h>

#include <Configuration/CFG_Rs.h>
#include <T6100/T6100_CardIf.h>

using namespace std;

#define SECONDS_15MIN 900
#define SECONDS_1DAY  86400
#define BLOCK_SIZE  122386

//-----------------------------------------------------------------
PM_ProfileExtractAction::PM_ProfileExtractAction(PM_GenericApplication* thePMSubApp):

    myPMSubApp(thePMSubApp)
{
}

//-----------------------------------------------------------------
PM_ProfileExtractAction::~PM_ProfileExtractAction()
{
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::Run (FC_Object* theObject)
{
    PM_HopNearEndSubApplication* theHopPmSubApp      = dynamic_cast<PM_HopNearEndSubApplication*>(myPMSubApp);
    PM_OduSubApplication*        theOduPmSubApp      = dynamic_cast<PM_OduSubApplication*>(myPMSubApp);
    PM_OduGaugeSubApplication*   theOduGaugePmSubApp = dynamic_cast<PM_OduGaugeSubApplication*>(myPMSubApp);
    PM_TcmSubApplication*        theTcmPmSubApp      = dynamic_cast<PM_TcmSubApplication*>(myPMSubApp);
    PM_TcmGaugeSubApplication*   theTcmGaugePmSubApp = dynamic_cast<PM_TcmGaugeSubApplication*>(myPMSubApp);

    if( theHopPmSubApp )
    {
        ProcessProfileHopAction(theHopPmSubApp); // PM Profile Table (Threshold)
        ProcessPMCfgHopAction(theHopPmSubApp); // PM Cfg Info from Controller
    }
    else if ( theOduPmSubApp )
    {
        ProcessProfileOduAction(theOduPmSubApp); // PM Profile Table (Threshold)
        ProcessPMCfgOduAction(theOduPmSubApp); // PM Cfg Info from Controller
    }
    else if ( theOduGaugePmSubApp )
    {
        ProcessProfileOduGaugeAction(theOduGaugePmSubApp); // PM Profile Table (Threshold)
        ProcessPMCfgOduGaugeAction(theOduGaugePmSubApp); // PM Cfg Info from Controller
    }
    else if( theTcmPmSubApp )
    {
        ProcessProfileTcmAction(theTcmPmSubApp); // PM Profile Table (Threshold)
        ProcessPMCfgTcmAction(theTcmPmSubApp); // PM Cfg Info from Controller
    }
    else if ( theTcmGaugePmSubApp )
    {
        ProcessProfileTcmGaugeAction(theTcmGaugePmSubApp); // PM Profile Table (Threshold)
        ProcessPMCfgTcmGaugeAction(theTcmGaugePmSubApp); // PM Cfg Info from Controller
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessProfileHopAction(PM_HopNearEndSubApplication* theHopPmSubApp)
{
    bbindex_t              iStart = 0;
    bbindex_t              iEnd   = 0;
    CT_DirectionFlag       aDirection = CT_PORT_SIDE;
    PM_ProfileTableRegion* aPMPFTableRegion = NULL;
    bool                   isRegionModified1 = false;
    bool                   isRegionModified2 = false;

    if ( theHopPmSubApp->GetKeySuffix() == "_LINE_0_A" || theHopPmSubApp->GetKeySuffix() == "_LINE_0_B" ||
         theHopPmSubApp->GetKeySuffix() == "_LINE_0_C" || theHopPmSubApp->GetKeySuffix() == "_LINE_0_D" )
    {
        aDirection = CT_LINE_SIDE; // Otherwise PORT_0 - PORT_12_A/B/C/D (SSM)

        if ( theHopPmSubApp->GetKeySuffix() == "_LINE_0_B" )
            iStart = CT_TEL_NB_STS1_AU3_IN_OC48_STM16 * 1;
        if ( theHopPmSubApp->GetKeySuffix() == "_LINE_0_C" )
            iStart = CT_TEL_NB_STS1_AU3_IN_OC48_STM16 * 2;
        if ( theHopPmSubApp->GetKeySuffix() == "_LINE_0_D" )
            iStart = CT_TEL_NB_STS1_AU3_IN_OC48_STM16 * 3;
    }

    if ( theHopPmSubApp->GetKeySuffix() == "_PORT_12_A" || theHopPmSubApp->GetKeySuffix() == "_PORT_12_B" ||
         theHopPmSubApp->GetKeySuffix() == "_PORT_12_C" || theHopPmSubApp->GetKeySuffix() == "_PORT_12_D" )
    {
        if ( theHopPmSubApp->GetKeySuffix() == "_PORT_12_B" )
            iStart = CT_TEL_NB_STS1_AU3_IN_OC48_STM16 * 1;
        if ( theHopPmSubApp->GetKeySuffix() == "_PORT_12_C" )
            iStart = CT_TEL_NB_STS1_AU3_IN_OC48_STM16 * 2;
        if ( theHopPmSubApp->GetKeySuffix() == "_PORT_12_D" )
            iStart = CT_TEL_NB_STS1_AU3_IN_OC48_STM16 * 3;

    }

    iEnd = iStart + CT_TEL_NB_STS1_AU3_IN_OC48_STM16;

    //---------------------------------------------------------------------------------------
    // Loop thru the PMHopSubApp's corresponding CFG_LINE/PORT_x region to determine STS Type.
    // This will be used to obtain the proper -global- PM PROFILE TABLE Region and Object.
    //---------------------------------------------------------------------------------------
    for (bbindex_t i = iStart; i < iEnd; i++)
    {
        CFG_Object& aCFGObj = (*theHopPmSubApp->GetCfgApplication().GetCfgRegion())[i];
        CFG_Hop*    aCFGHop = dynamic_cast<CFG_Hop*>(&aCFGObj);
        if ( !aCFGHop ) continue;

        if ( aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_STS1 ||
             aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_VC3 )
        {
            aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>(T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(CT_STS1));
        }
        else if ( aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_STS3C ||
                  aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_VC4 )
        {
            aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>(T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(CT_STS3C));
        }
        else if ( aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_STS12C ||
                  aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_VC4_4 )
        {
            aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>(T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(CT_STS12C));
        }
        else if ( aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_STS48C ||
                  aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_VC4_16 )
        {
            aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>(T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(CT_STS48C));
        }
        else if ( aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_STS192C ||
                  aCFGHop->GetSpeMapping() == CT_TEL_HOP_MAPPING_VC4_64 )
        {
            aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>(T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(CT_STS192C));
        }
        else
        {
            continue;
        }

        //-------------------------------------------------------------------------------------------
        // Use the CFG_PORT/LINE_x HOP's PMProfileId to obtain the correct -global- PROFILE TABLE.
        // Then, update the PM_HOP_NE_CONFIG regions for 15min and 1day with -global- PM PROFILEs.
        // NOTE: mod(%)CT_TEL_NB_STS1_AU3_IN_OC48_STM16 needed because PM_BbCfg MAX value is 48!
        //-------------------------------------------------------------------------------------------
        PM_ProfileTable& aPMPFTableObj = (*aPMPFTableRegion)[(bbindex_t) aCFGHop->GetPMProfileId() ];

        PM_ProfileTableElem* aPMPFTableElem1 = aPMPFTableObj.GetPMProfileTableElem(aDirection, CT_PM_PERIOD_15_MINUTES);
        PM_BbCfg* aPM_HOP_NE_CONFIG_OBJ1 = &((*(theHopPmSubApp->Get15MRegionConfig()))[ i % CT_TEL_NB_STS1_AU3_IN_OC48_STM16 ]);

        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_CV,      aPMPFTableElem1->GetCVPThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_ES,      aPMPFTableElem1->GetESPThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_SES,     aPMPFTableElem1->GetSESPThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_FC,      aPMPFTableElem1->GetFCPThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_UAS,     aPMPFTableElem1->GetUASPThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_PJCSDET, aPMPFTableElem1->GetPJCSPDetThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_PJCSGEN, aPMPFTableElem1->GetPJCSPGenThreshold());
        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ1->SetThreshold(PM_TypeHopNearEnd::PM_PJCDIFF, aPMPFTableElem1->GetPJCDiffPThreshold());

        PM_ProfileTableElem* aPMPFTableElem2 = aPMPFTableObj.GetPMProfileTableElem(aDirection, CT_PM_PERIOD_1_DAY);
        PM_BbCfg* aPM_HOP_NE_CONFIG_OBJ2 = &((*(theHopPmSubApp->GetDayRegionConfig()))[ i % CT_TEL_NB_STS1_AU3_IN_OC48_STM16 ]);

        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_CV,      aPMPFTableElem2->GetCVPThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_ES,      aPMPFTableElem2->GetESPThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_SES,     aPMPFTableElem2->GetSESPThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_FC,      aPMPFTableElem2->GetFCPThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_UAS,     aPMPFTableElem2->GetUASPThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_PJCSDET, aPMPFTableElem2->GetPJCSPDetThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_PJCSGEN, aPMPFTableElem2->GetPJCSPGenThreshold());
        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ2->SetThreshold(PM_TypeHopNearEnd::PM_PJCDIFF, aPMPFTableElem2->GetPJCDiffPThreshold());
    }

    if ( isRegionModified1 )
    {
        theHopPmSubApp->Get15MRegionConfig()->IncModificationCounter();
        theHopPmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        theHopPmSubApp->GetDayRegionConfig()->IncModificationCounter();
        theHopPmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessProfileOduAction(PM_OduSubApplication* thePmSubApp)
{
    bbindex_t              i      = 0;
    bbindex_t              iStart = 0;
    bbindex_t              iEnd   = (bbindex_t)thePmSubApp->GetCfgApplication().GetCfgRegion()->Size();
    PM_ProfileTableRegion* aPMPFTableRegion = NULL;
    bool                   isRegionModified1 = false;
    bool                   isRegionModified2 = false;

    for (bbindex_t i = iStart; i < iEnd; i++)
    {
        CFG_Object& aCFGObj = (*thePmSubApp->GetCfgApplication().GetCfgRegion())[i];
        CFG_Odu*    aCFGOdu = dynamic_cast<CFG_Odu*>(&aCFGObj);
        if ( !aCFGOdu ) continue;

        if ( !aCFGOdu->GetProvisionningActive() )
        {
            continue; ///////////////////////////
        }

        uint32 expRate  = aCFGOdu->GetExpectedSignalRate();
        uint8 theKvalue = aCFGOdu->GetOduIdentifier().GetOduKvalue();
        CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();

        CT_EntityType theOduType = CT_ODU0;
        if ( theKvalue == 0  )
            theOduType = CT_ODU0;
        else if ( theKvalue == 1  )
            theOduType = CT_ODU1;
        else if ( theKvalue == 2  )
        {
            theOduType = CT_ODU2;
            if( (aCFGOdu->GetClockType() == CT_TEL_CLK_OVRCLKFS) && (aCardType == OSM2C ||  aCardType == OSM2S))
                theOduType = CT_ODU2E;
        }
        else if ( theKvalue == 3  )
            theOduType = CT_ODU3;
        else if ( theKvalue == 4  )
            theOduType = CT_ODU4;
        else if ( theKvalue == 5  )
            theOduType = CT_ODUF;

        CT_DirectionFlag  aCurrDirection = CT_DIR_RCV;

                
        if( (aCardType == OSM20) || 
			(aCardType == OMMX)  || 
			(aCardType == OSM40) || 
			(aCardType == HGTMM) ||
			(aCardType == OSM2S) || 
			(aCardType == OSM2C) || 
			(aCardType == OSM1S) || 
			(aCardType == HGTMMS)||
			(aCardType == HDTG2))
        {
            aCurrDirection = PM_GetOduDirectionByOduType(CSPII_CardIF::GetInstance()->GetCardType(), aCFGOdu->GetOduObjectType());
        }
        else // HDTG,ESM20 and HGTM
        {
            vector<CT_ODU_ServerID> aPositionList = aCFGOdu->GetOduPositionList();
            if (aPositionList.size() > 0)
            {
                CT_IntfId anIns                  = (CT_IntfId)(aPositionList[0].GetPoolInstance());
                CFG_RsCfgRegion* aCfgRegion      = static_cast<CFG_RsCfgRegion*> 
                                                   (thePmSubApp->GetCardContext().GetRsIf().GetCfgPortSideApp(anIns).GetCfgRegion());
                CT_TEL_SignalType aSignalType    = (*aCfgRegion)[0].GetSignalType();
                aCurrDirection = PM_GetOduDirectionBySigType(aCardType, aSignalType);
            }
        }

        aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>
                           (T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(theOduType));
		if( aPMPFTableRegion == NULL)
			  continue;

        //-------------------------------------------------------------------------------------------
        // Use the CFG_PORT_32 PMProfileId to obtain the correct -global- PROFILE TABLE.
        // Then, update the PM_NE_CONFIG regions for 15min and 1day with -global- PM PROFILEs.
        //-------------------------------------------------------------------------------------------
        PM_ProfileTable& aPMPFTableObj = (*aPMPFTableRegion)[(bbindex_t) aCFGOdu->GetPMProfileId() ];

        PM_ProfileTableElem* aPMPFTableElem1 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_15_MINUTES);
        PM_BbCfg* aPM_NE_CONFIG_OBJ1 = &((*(thePmSubApp->Get15MRegionConfig()))[ i ]);

        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_CV,  aPMPFTableElem1->GetCVODUThreshold());
        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_ES,  aPMPFTableElem1->GetESODUThreshold());
        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_SES, aPMPFTableElem1->GetSESODUThreshold());
        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_UAS, aPMPFTableElem1->GetUASODUThreshold());

        if ( theOduType == CT_ODU4 ) // need HIGH order param!
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_CV_HIGH, aPMPFTableElem1->GetThreshold(PM_TypeOdu::PM_CV_HIGH));
        }
        else if ( theOduType == CT_ODUF ) //  calculate count for ODUF Rate*%
        {
            if(CSPII_CardIF::GetInstance()->GetCardFamily() == OSM_FAM)
            {
                isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_CV, aPMPFTableElem1->GetThreshold(PM_TypeOdu::PM_CV)*9*0.01*(expRate/122368.0));// For mTera, expected rate is of kbps
            }
            else
            {
                isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOdu::PM_CV, aPMPFTableElem1->GetThreshold(PM_TypeOdu::PM_CV)*9*0.0001*(expRate/(122368.0))); //(1000*expRate/100)*thePMPFThreshold*900*1E-7/122368)
            }
        }

        PM_ProfileTableElem* aPMPFTableElem2 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_1_DAY);
        PM_BbCfg* aPM_NE_CONFIG_OBJ2 = &((*(thePmSubApp->GetDayRegionConfig()))[ i ]);

        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_CV,  aPMPFTableElem2->GetCVODUThreshold());
        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_ES,  aPMPFTableElem2->GetESODUThreshold());
        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_SES, aPMPFTableElem2->GetSESODUThreshold());
        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_UAS, aPMPFTableElem2->GetUASODUThreshold());
        if ( theOduType == CT_ODU4 ) // need HIGH order param!
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_CV_HIGH, aPMPFTableElem2->GetThreshold(PM_TypeOdu::PM_CV_HIGH));
        }
        else if ( theOduType == CT_ODUF ) //  calculate count for ODUF
        {           
            if(CSPII_CardIF::GetInstance()->GetCardFamily() == OSM_FAM)
            {
                isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_CV, aPMPFTableElem2->GetThreshold(PM_TypeOdu::PM_CV)*864*0.01*(expRate/122368.0));// For mTera, expected rate is of kbps
            }
            else
            {
                isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOdu::PM_CV, aPMPFTableElem2->GetThreshold(PM_TypeOdu::PM_CV)*864*0.0001*(expRate/122368));//(1000*expRate/100)*thePMPFThreshold*86400*1E-7/122368)
            }
        }
    }

    if ( isRegionModified1 )
    {
        thePmSubApp->Get15MRegionConfig()->IncModificationCounter();
        thePmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        thePmSubApp->GetDayRegionConfig()->IncModificationCounter();
        thePmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessProfileOduGaugeAction(PM_OduGaugeSubApplication* thePmSubApp)
{
    bbindex_t              i      = 0;
    bbindex_t              iStart = 0;
    bbindex_t              iEnd   = (bbindex_t)thePmSubApp->GetCfgApplication().GetCfgRegion()->Size();
    PM_ProfileTableRegion* aPMPFTableRegion = NULL;

    for (bbindex_t i = iStart; i < iEnd; i++)
    {
        CFG_Object& aCFGObj = (*thePmSubApp->GetCfgApplication().GetCfgRegion())[i];
        CFG_Odu*    aCFGOdu = dynamic_cast<CFG_Odu*>(&aCFGObj);
        if ( !aCFGOdu ) continue;

        if ( !aCFGOdu->GetProvisionningActive() )
        {
            continue; ///////////////////////////
        }

        uint32 expRate  =  aCFGOdu->GetExpectedSignalRate();
        uint8 theKvalue = aCFGOdu->GetOduIdentifier().GetOduKvalue();

        CT_EntityType theOduType = CT_ODU0;
        if ( theKvalue == 0  )
            theOduType = CT_ODU0;
        else if ( theKvalue == 1  )
            theOduType = CT_ODU1;
        else if ( theKvalue == 2  )
        {
            theOduType = CT_ODU2;
            if(aCFGOdu->GetClockType() == CT_TEL_CLK_OVRCLKFS)
            {
                if((CSPII_CardIF::GetInstance()->GetCardType() == HGTMM) ||
                   (CSPII_CardIF::GetInstance()->GetCardType() == HGTMMS) ||
				   (CSPII_CardIF::GetInstance()->GetCardType() == HDTG2))
                {
                    theOduType = CT_ODU2;
                }
                else
                    theOduType = CT_ODU2E;
            }
                
        }
        else if ( theKvalue == 3  )
            theOduType = CT_ODU3;
        else if ( theKvalue == 4  )
            theOduType = CT_ODU4;
        else if ( theKvalue == 5  )
            theOduType = CT_ODUF;

        CT_DirectionFlag  aCurrDirection = CT_DIR_INVALID;

        if( CSPII_CardIF::GetInstance()->GetCardType() == OSM20 ||
            CSPII_CardIF::GetInstance()->GetCardType() == OMMX  ||
            CSPII_CardIF::GetInstance()->GetCardType() == OSM40 ||
            CSPII_CardIF::GetInstance()->GetCardType() == OSM2C ||
            CSPII_CardIF::GetInstance()->GetCardType() == OSM2S ||
            CSPII_CardIF::GetInstance()->GetCardType() == OSM1S)
        {
           aCurrDirection = PM_GetOduDirectionByOduType(CSPII_CardIF::GetInstance()->GetCardType(), aCFGOdu->GetOduObjectType());
        }
        else // HDTG,ESM20 and HGTM
        {
            vector<CT_ODU_ServerID> aPositionList = aCFGOdu->GetOduPositionList();
            if (aPositionList.size() > 0)
            {
                CT_IntfId anIns                  = (CT_IntfId)(aPositionList[0].GetPoolInstance());
                CFG_RsCfgRegion* aCfgRegion      = static_cast<CFG_RsCfgRegion*> 
                                                   (thePmSubApp->GetCardContext().GetRsIf().GetCfgPortSideApp(anIns).GetCfgRegion());
                CT_TEL_SignalType aSignalType    = (*aCfgRegion)[0].GetSignalType();
                aCurrDirection = PM_GetOduDirectionBySigType(CSPII_CardIF::GetInstance()->GetCardType(), aSignalType );
            }
        }

        aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>
                           (T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(theOduType));
		if( aPMPFTableRegion == NULL)
			  continue;

        //-------------------------------------------------------------------------------------------
        // Use the CFG_PORT_x PMProfileId to obtain the correct -global- PROFILE TABLE.
        // Then, update the PM_NE_CONFIG regions for 15min and 1day with -global- PM PROFILEs.
        //-------------------------------------------------------------------------------------------
        PM_ProfileTable& aPMPFTableObj = (*aPMPFTableRegion)[(bbindex_t) aCFGOdu->GetPMProfileId() ];
        uint32 gaugeStart = PM_TypeOdu::GetMaxNbParams( theOduType );

        PM_ProfileTableElem* aPMPFTableElem1 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_15_MINUTES);
        PM_BbCfg* aPM_NE_CONFIG_OBJ1 = &((*(thePmSubApp->Get15MRegionConfig()))[ i ]);

        aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeOduGauge::PM_DELAY, 
                /* floor */  aPMPFTableElem1->GetThreshold(gaugeStart + PM_TypeOduGauge::PM_DELAY),
                /* ceil  */  aPMPFTableElem1->GetThreshold(gaugeStart + PM_TypeOduGauge::PM_DELAY + 1));

        PM_ProfileTableElem* aPMPFTableElem2 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_1_DAY);
        PM_BbCfg* aPM_NE_CONFIG_OBJ2 = &((*(thePmSubApp->GetDayRegionConfig()))[ i ]);

        aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeOduGauge::PM_DELAY, 
                /* floor */  aPMPFTableElem2->GetThreshold(gaugeStart + PM_TypeOduGauge::PM_DELAY),
                /* ceil  */  aPMPFTableElem2->GetThreshold(gaugeStart + PM_TypeOduGauge::PM_DELAY + 1));
    }

    thePmSubApp->Get15MRegionConfig()->IncModificationCounter();
    thePmSubApp->Get15MRegionConfig()->UpdateNotify();
    thePmSubApp->GetDayRegionConfig()->IncModificationCounter();
    thePmSubApp->GetDayRegionConfig()->UpdateNotify();
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessProfileTcmAction(PM_TcmSubApplication* thePmSubApp)
{
    bbindex_t              i      = 0;
    bbindex_t              iStart = 0;
    bbindex_t              iEnd   = (bbindex_t)(thePmSubApp->GetMaxEntities());
    PM_ProfileTableRegion* aPMPFTableRegion = NULL;
    bool                   isRegionModified1 = false;
    bool                   isRegionModified2 = false;
    CT_ODU_Layer           aOduLayer = CT_ODU_LayerEnd;
    CT_ODU_Direction       aOduDirection = CT_ODU_Direction_A;
    CT_EntityType          aTcmEntityType = CT_ODU0TA;

    iEnd = (iEnd <= (bbindex_t)thePmSubApp->GetCfgApplication().GetCfgRegion()->Size()) ? iEnd : (bbindex_t)thePmSubApp->GetCfgApplication().GetCfgRegion()->Size();
    for (bbindex_t i = iStart; i < iEnd; i++)
    {
        CFG_Object& aCFGObj = (*thePmSubApp->GetCfgApplication().GetCfgRegion())[i];
        CFG_Tcm*    aCFGTcm = dynamic_cast<CFG_Tcm*>(&aCFGObj);
        if ( !aCFGTcm ) continue;

        if ( !aCFGTcm->GetProvisionningActive() )
        {
            continue; ///////////////////////////
        }

        // get TcmEntitytype based on OduLayer and OduDirection
        // of configurated object
        aOduLayer = aCFGTcm->GetTcmIdentifier().GetOduKvalueEnum();
        aOduDirection = aCFGTcm->GetTcmIdentifier().GetOduDirection();

        // Get ODUF_Rate for ODUFT case to calculate real digital number
        // according to configurated threshold-percentage
        uint32 expRate = 0;

        // PM_ProfileExtractAction only observer direction-A profile region
        switch (aOduLayer)
        {
            case CT_ODU_Layer0:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU0TA : CT_ODU0TB);
                break;
            case CT_ODU_Layer1:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU1TA : CT_ODU1TB);
                break;
            case CT_ODU_Layer2:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU2TA : CT_ODU2TB);
                break;
            case CT_ODU_Layer3:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU3TA : CT_ODU3TB);
                break;
            case CT_ODU_Layer4:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU4TA : CT_ODU4TB);
                break;
            case CT_ODU_LayerF:
            {
                T6100_TelecomIf& theOduApp = thePmSubApp->GetCardContext().GetOduIf();

                // ODUF share with ODU0, so CT_PORT_SIDE_30 is used for ODUF also.
                CFG_AppIf& aCfgApp = theOduApp.GetCfgPortSideApp((CT_IntfId)CT_PORT_SIDE_30);
                CFG_Odu& aCfgOdu   = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[aCFGTcm->GetOduBbIndex()]);
                expRate            = aCfgOdu.GetExpectedSignalRate();
                
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODUFTA : CT_ODUFTB);
            }
                break;
            default:
                break;
        }
        
        aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>
                           (T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(aTcmEntityType));

        CT_DirectionFlag aCurrDirection = (aOduDirection == CT_ODU_Direction_A ? CT_DIR_RCV : CT_DIR_TRMT);


        //-------------------------------------------------------------------------------------------
        // Use the CFG_PORT_32 PMProfileId to obtain the correct -global- PROFILE TABLE.
        // Then, update the PM_NE_CONFIG regions for 15min and 1day with -global- PM PROFILEs.
        //-------------------------------------------------------------------------------------------
        PM_ProfileTable& aPMPFTableObj = (*aPMPFTableRegion)[(bbindex_t) aCFGTcm->GetPMProfileId() ];

        PM_ProfileTableElem* aPMPFTableElem1 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_15_MINUTES);
        PM_BbCfg* aPM_NE_CONFIG_OBJ1 = &((*(thePmSubApp->Get15MRegionConfig()))[ i ]);

        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcm::PM_CV,  aPMPFTableElem1->GetCVTcmThreshold());
        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcm::PM_ES,  aPMPFTableElem1->GetESTcmThreshold());
        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcm::PM_SES, aPMPFTableElem1->GetSESTcmThreshold());
        isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcm::PM_UAS, aPMPFTableElem1->GetUASTcmThreshold());
        if ( aTcmEntityType == CT_ODU4TA || aTcmEntityType == CT_ODU4TB ) // need HIGH order param!
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcm::PM_CV_HIGH, aPMPFTableElem1->GetThreshold(PM_TypeTcm::PM_CV_HIGH));
        }

        // ODUFT, need to convert threshold-percentage to real digital number for CV TCA,
        // this is similar to ODUF case
        if ( aTcmEntityType == CT_ODUFTA || aTcmEntityType == CT_ODUFTB )
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcm::PM_CV, aPMPFTableElem1->GetThreshold(PM_TypeTcm::PM_CV)*9*0.0001*(expRate/(122368.0)));
        }
        
        PM_ProfileTableElem* aPMPFTableElem2 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_1_DAY);
        PM_BbCfg* aPM_NE_CONFIG_OBJ2 = &((*(thePmSubApp->GetDayRegionConfig()))[ i ]);

        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcm::PM_CV,  aPMPFTableElem2->GetCVTcmThreshold());
        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcm::PM_ES,  aPMPFTableElem2->GetESTcmThreshold());
        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcm::PM_SES, aPMPFTableElem2->GetSESTcmThreshold());
        isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcm::PM_UAS, aPMPFTableElem2->GetUASTcmThreshold());
        if ( aTcmEntityType == CT_ODU4TA || aTcmEntityType == CT_ODU4TB ) // need HIGH order param!
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcm::PM_CV_HIGH, aPMPFTableElem2->GetThreshold(PM_TypeTcm::PM_CV_HIGH));
        }

        // ODUFT, need to convert threshold-percentage to real digital number for CV TCA,
        // this is similar to ODUF case
        if ( aTcmEntityType == CT_ODUFTA || aTcmEntityType == CT_ODUFTB )
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcm::PM_CV, aPMPFTableElem2->GetThreshold(PM_TypeTcm::PM_CV)*864*0.0001*(expRate/(122368.0)));
        }
    }

    if ( isRegionModified1 )
    {
        thePmSubApp->Get15MRegionConfig()->IncModificationCounter();
        thePmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        thePmSubApp->GetDayRegionConfig()->IncModificationCounter();
        thePmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessProfileTcmGaugeAction(PM_TcmGaugeSubApplication* thePmSubApp)
{
    bbindex_t              i      = 0;
    bbindex_t              iStart = 0;
    bbindex_t              iEnd   = (bbindex_t)(thePmSubApp->GetMaxEntities());
    PM_ProfileTableRegion* aPMPFTableRegion = NULL;
    CT_ODU_Layer           aOduLayer = CT_ODU_LayerEnd;
    CT_ODU_Direction       aOduDirection = CT_ODU_Direction_A;
    CT_EntityType          aTcmEntityType = CT_ODU0TA;

    iEnd = (iEnd <= (bbindex_t)thePmSubApp->GetCfgApplication().GetCfgRegion()->Size()) ? iEnd : (bbindex_t)thePmSubApp->GetCfgApplication().GetCfgRegion()->Size();
    for (bbindex_t i = iStart; i < iEnd; i++)
    {
        CFG_Object& aCFGObj = (*thePmSubApp->GetCfgApplication().GetCfgRegion())[i];
        CFG_Tcm*    aCFGTcm = dynamic_cast<CFG_Tcm*>(&aCFGObj);
        if ( !aCFGTcm ) continue;
        
        if ( !aCFGTcm->GetProvisionningActive() )
        {
            continue; ///////////////////////////
        }


        // get TcmEntitytype based on OduLayer and OduDirection
        // of configurated object
        aOduLayer = aCFGTcm->GetTcmIdentifier().GetOduKvalueEnum();
        aOduDirection = aCFGTcm->GetTcmIdentifier().GetOduDirection();

        // PM_ProfileExtractAction only observer direction-A profile region
        switch (aOduLayer)
        {
            case CT_ODU_Layer0:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU0TA : CT_ODU0TB);
                break;
            case CT_ODU_Layer1:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU1TA : CT_ODU1TB);
                break;
            case CT_ODU_Layer2:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU2TA : CT_ODU2TB);
                break;
            case CT_ODU_Layer3:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU3TA : CT_ODU3TB);
                break;
            case CT_ODU_Layer4:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODU4TA : CT_ODU4TB);
                break;
            case CT_ODU_LayerF:
                aTcmEntityType = (aOduDirection == CT_ODU_Direction_A ? CT_ODUFTA : CT_ODUFTB);
                break;
            default:
                break;
                
        }
        

        aPMPFTableRegion = dynamic_cast<PM_ProfileTableRegion*>
                           (T6100_MainAppIf::Instance().GetPmMainApp().GetPMProfileTableRegion(aTcmEntityType));

        CT_TL1_Port portId = CT_TL1_PORT_UNKNOWN;
        CT_ChannelId channelId = UNKNOWN_CHANNEL_ID;
        CT_Map_PortId::GetOduTl1PortChan( CARD_FAM_ENH_TRN, *aCFGTcm, portId, channelId );
        
	    CT_DirectionFlag aCurrDirection = (aOduDirection == CT_ODU_Direction_A ? CT_DIR_RCV : CT_DIR_TRMT);


        //-------------------------------------------------------------------------------------------
        // Use the CFG_PORT_x PMProfileId to obtain the correct -global- PROFILE TABLE.
        // Then, update the PM_NE_CONFIG regions for 15min and 1day with -global- PM PROFILEs.
        //-------------------------------------------------------------------------------------------
        PM_ProfileTable& aPMPFTableObj = (*aPMPFTableRegion)[(bbindex_t) aCFGTcm->GetPMProfileId() ];
        uint32 gaugeStart = PM_TypeTcm::GetMaxNbParams( aTcmEntityType );
 
        PM_ProfileTableElem* aPMPFTableElem1 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_15_MINUTES);
        PM_BbCfg* aPM_NE_CONFIG_OBJ1 = &((*(thePmSubApp->Get15MRegionConfig()))[ i ]);
 
        aPM_NE_CONFIG_OBJ1->SetThreshold(PM_TypeTcmGauge::PM_DELAY,
                /* floor */  aPMPFTableElem1->GetThreshold(gaugeStart + PM_TypeTcmGauge::PM_DELAY),
                /* ceil  */  aPMPFTableElem1->GetThreshold(gaugeStart + PM_TypeTcmGauge::PM_DELAY + 1));
 
        PM_ProfileTableElem* aPMPFTableElem2 = aPMPFTableObj.GetPMProfileTableElem(aCurrDirection, CT_PM_PERIOD_1_DAY);
        PM_BbCfg* aPM_NE_CONFIG_OBJ2 = &((*(thePmSubApp->GetDayRegionConfig()))[ i ]);
 
        aPM_NE_CONFIG_OBJ2->SetThreshold(PM_TypeTcmGauge::PM_DELAY,
                /* floor */  aPMPFTableElem2->GetThreshold(gaugeStart + PM_TypeTcmGauge::PM_DELAY),
                /* ceil  */  aPMPFTableElem2->GetThreshold(gaugeStart + PM_TypeTcmGauge::PM_DELAY + 1));
    }
 
    thePmSubApp->Get15MRegionConfig()->IncModificationCounter();
    thePmSubApp->Get15MRegionConfig()->UpdateNotify();
    thePmSubApp->GetDayRegionConfig()->IncModificationCounter();
    thePmSubApp->GetDayRegionConfig()->UpdateNotify();
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessPMCfgHopAction(PM_HopNearEndSubApplication* theHopPmSubApp)
{
    bbindex_t i;
    bool isRegionModified1 = false;
    bool isRegionModified2 = false;

    for (i=0; i < (bbindex_t)theHopPmSubApp->Get15MRegionConfig()->Size(); i++)
    {
        PM_BbCfg* aPM_HOP_NE_CONFIG_SPM = &((*(theHopPmSubApp->Get15MPFRegionConfig()))[i]);
        PM_BbCfg* aPM_HOP_NE_CONFIG_OBJ = &((*(theHopPmSubApp->Get15MRegionConfig()))[i]);

        isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_HOP_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_HOP_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified1 |= aPM_HOP_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount
                                     (j, aPM_HOP_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    for (i=0; i < (bbindex_t)theHopPmSubApp->GetDayRegionConfig()->Size(); i++)
    {
        PM_BbCfg* aPM_HOP_NE_CONFIG_SPM = &((*(theHopPmSubApp->GetDayPFRegionConfig()))[i]);
        PM_BbCfg* aPM_HOP_NE_CONFIG_OBJ = &((*(theHopPmSubApp->GetDayRegionConfig()))[i]);

        isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_HOP_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_HOP_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified2 |= aPM_HOP_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount
                                     (j, aPM_HOP_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    if ( isRegionModified1 )
    {
        theHopPmSubApp->Get15MRegionConfig()->IncModificationCounter();
        theHopPmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        theHopPmSubApp->GetDayRegionConfig()->IncModificationCounter();
        theHopPmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessPMCfgOduAction(PM_OduSubApplication* theOduPmSubApp)
{
    bbindex_t i;
    bool isRegionModified1 = false;
    bool isRegionModified2 = false;

    for (i=0; i < (bbindex_t)theOduPmSubApp->Get15MRegionConfig()->Size(); i++)
    {
        if (i >= (bbindex_t)theOduPmSubApp->Get15MPFRegionConfig()->Size())
        {
            break;
        }
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theOduPmSubApp->Get15MPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theOduPmSubApp->Get15MRegionConfig()))[i]);

        isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    for (i=0; i < (bbindex_t)theOduPmSubApp->GetDayRegionConfig()->Size(); i++)
    {
        if (i >= (bbindex_t)theOduPmSubApp->GetDayPFRegionConfig()->Size())
        {
            break;
        }
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theOduPmSubApp->GetDayPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theOduPmSubApp->GetDayRegionConfig()))[i]);

        isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    if ( isRegionModified1 )
    {
        theOduPmSubApp->Get15MRegionConfig()->IncModificationCounter();
        theOduPmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        theOduPmSubApp->GetDayRegionConfig()->IncModificationCounter();
        theOduPmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessPMCfgOduGaugeAction(PM_OduGaugeSubApplication* theOduPmSubApp)
{
    bbindex_t i;
    bool isRegionModified1 = false;
    bool isRegionModified2 = false;

    for (i=0; i < (bbindex_t)theOduPmSubApp->Get15MRegionConfig()->Size(); i++)
    {
        if (i >= (bbindex_t)theOduPmSubApp->Get15MPFRegionConfig()->Size())
        {
            break;
        }
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theOduPmSubApp->Get15MPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theOduPmSubApp->Get15MRegionConfig()))[i]);

        isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    for (i=0; i < (bbindex_t)theOduPmSubApp->GetDayRegionConfig()->Size(); i++)
    {
        if (i >= (bbindex_t)theOduPmSubApp->GetDayPFRegionConfig()->Size())
        {
            break;
        }
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theOduPmSubApp->GetDayPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theOduPmSubApp->GetDayRegionConfig()))[i]);

        isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    if ( isRegionModified1 )
    {
        theOduPmSubApp->Get15MRegionConfig()->IncModificationCounter();
        theOduPmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        theOduPmSubApp->GetDayRegionConfig()->IncModificationCounter();
        theOduPmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessPMCfgTcmAction(PM_TcmSubApplication* theTcmPmSubApp)
{
    bbindex_t i;
    bool isRegionModified1 = false;
    bool isRegionModified2 = false;
    uint32 size = (theTcmPmSubApp->Get15MRegionConfig()->Size() <= theTcmPmSubApp->Get15MPFRegionConfig()->Size()) ? 
        theTcmPmSubApp->Get15MRegionConfig()->Size() : theTcmPmSubApp->Get15MPFRegionConfig()->Size();

    for (i=0; i < (bbindex_t)size; i++)
    {
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theTcmPmSubApp->Get15MPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theTcmPmSubApp->Get15MRegionConfig()))[i]);

        isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    size = (theTcmPmSubApp->GetDayRegionConfig()->Size() <= theTcmPmSubApp->GetDayPFRegionConfig()->Size()) ? 
        theTcmPmSubApp->GetDayRegionConfig()->Size() : theTcmPmSubApp->GetDayPFRegionConfig()->Size();
    for (i=0; i < (bbindex_t)size; i++)
    {
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theTcmPmSubApp->GetDayPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theTcmPmSubApp->GetDayRegionConfig()))[i]);

        isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());

        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j));
        }
    }

    if ( isRegionModified1 )
    {
        theTcmPmSubApp->Get15MRegionConfig()->IncModificationCounter();
        theTcmPmSubApp->Get15MRegionConfig()->UpdateNotify();
    }

    if ( isRegionModified2 )
    {
        theTcmPmSubApp->GetDayRegionConfig()->IncModificationCounter();
        theTcmPmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}

//-----------------------------------------------------------------
void PM_ProfileExtractAction::ProcessPMCfgTcmGaugeAction(PM_TcmGaugeSubApplication* theTcmPmSubApp)
{
    bbindex_t i;
    bool isRegionModified1 = false;
    bool isRegionModified2 = false;
    uint32 size = (theTcmPmSubApp->Get15MRegionConfig()->Size() <= theTcmPmSubApp->Get15MPFRegionConfig()->Size()) ? 
        theTcmPmSubApp->Get15MRegionConfig()->Size() : theTcmPmSubApp->Get15MPFRegionConfig()->Size();
 
    for (i=0; i < (bbindex_t)size; i++)
    {
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theTcmPmSubApp->Get15MPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theTcmPmSubApp->Get15MRegionConfig()))[i]);
 
        isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());
 
        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified1 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j))
;
        }
    }

    size = (theTcmPmSubApp->GetDayRegionConfig()->Size() <= theTcmPmSubApp->GetDayPFRegionConfig()->Size()) ? 
        theTcmPmSubApp->GetDayRegionConfig()->Size() : theTcmPmSubApp->GetDayPFRegionConfig()->Size();
    for (i=0; i < (bbindex_t)size; i++)
    {
        PM_BbCfg* aPM_NE_CONFIG_SPM = &((*(theTcmPmSubApp->GetDayPFRegionConfig()))[i]);
        PM_BbCfg* aPM_NE_CONFIG_OBJ = &((*(theTcmPmSubApp->GetDayRegionConfig()))[i]);
 
        isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetInhibitPtr()->SetControlWord(aPM_NE_CONFIG_SPM->GetInhibitPtr()->GetControlWord());
 
        for (uint32 j=0; j < aPM_NE_CONFIG_OBJ->GetResetPtr()->GetNumberOfParam(); j++)
        {
            isRegionModified2 |= aPM_NE_CONFIG_OBJ->GetResetPtr()->SetPMResetCount(j, aPM_NE_CONFIG_SPM->GetResetPtr()->GetPMResetCount(j))
;
        }
    }
 
    if ( isRegionModified1 )
    {
        theTcmPmSubApp->Get15MRegionConfig()->IncModificationCounter();
        theTcmPmSubApp->Get15MRegionConfig()->UpdateNotify();
    }
 
    if ( isRegionModified2 )
    {
        theTcmPmSubApp->GetDayRegionConfig()->IncModificationCounter();
        theTcmPmSubApp->GetDayRegionConfig()->UpdateNotify();
    }
}
 
