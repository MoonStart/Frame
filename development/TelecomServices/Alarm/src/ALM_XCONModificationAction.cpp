// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Signal Alarm
//  AUTHOR   :     Michael Sharkey
//  DESCRIPTION:   Report Defect/Flags to AM based upon XCON info.
// --------------------------------------------------------------------------*/

#include "ALM_XCONModificationAction.h"

#include <T6100_MainAppIf.h>
#include <T6100_SlotIf.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <Alarm/ALM_AppIf.h>
#include <CommonPlatforms/TelecomServices/Alarm/ALM_RsSubApplicationOnCard.h>
#include <CommonPlatforms/TelecomServices/Alarm/ALM_HopSubApplicationOnCard.h>
#include <CommonPlatforms/TelecomServices/Alarm/ALM_OduSubApplicationOnTrn.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_HopDefects.h>
#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_ConfigRegion.h>
#include "../ALM_RegionKeyDefinition.h"
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Odu.h>

#include <AM/AM_DefectCollector.h>

#include <CsPii/CSPII_CardIF.h>
//-----------------------------------------------------------------
ALM_XCONModificationAction::ALM_XCONModificationAction(ALM_AppIf& theAppIf): 

    myAppIf(theAppIf), 
    myCardIf(NULL),
    myRsAppIf(NULL),
    myHopAppIf(NULL),
    myOduAppIf(NULL)

{
    // Save the CardIf
    //----------------
    if ( dynamic_cast<T6100_CardIf*>(myAppIf.GetParent()->GetParent()) )
        myCardIf = dynamic_cast<T6100_CardIf*>(myAppIf.GetParent()->GetParent());

    // Save the RsApp
    //----------------
    ALM_RsSubApplicationOnCard* aRsSubApp = dynamic_cast<ALM_RsSubApplicationOnCard*>(&myAppIf);
    if (aRsSubApp) 
    {
        myRsAppIf = aRsSubApp;
    }

    // Save the HopApp
    //----------------
    ALM_HopSubApplicationOnCard* aHopSubApp = dynamic_cast<ALM_HopSubApplicationOnCard*>(&myAppIf);
    if (aHopSubApp) 
    {
        myHopAppIf = aHopSubApp;
    }

    // Save the OduApp
    //----------------
    ALM_OduSubApplicationOnTrn *aOduSubApp = dynamic_cast<ALM_OduSubApplicationOnTrn*>(&myAppIf);
    if (aOduSubApp)
    {
        myOduAppIf = aOduSubApp;
    }

    // default to 0 and LINE
    //-----------------------------
    myPortNumber = CT_PORT_SIDE_0;
    myDirection  = CT_DIR_WAVE_LINE;

    if (     myAppIf.GetKeySuffix() == ALM_PORT_0_SUFFIX)
       {myPortNumber = CT_PORT_SIDE_0; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_1_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_1; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_2_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_2; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_3_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_3; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_4_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_4; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_5_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_5; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_6_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_6; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_7_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_7; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_8_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_8; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_9_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_9; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_10_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_10; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_11_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_11; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_12_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_12; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_13_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_13; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_14_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_14; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_15_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_15; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_16_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_16; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_17_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_17; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_18_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_18; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_19_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_19; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_20_SUFFIX)
       {myPortNumber = CT_PORT_SIDE_20; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_21_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_21; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_22_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_22; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_23_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_23; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_24_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_24; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_25_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_25; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_26_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_26; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_27_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_27; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_28_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_28; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_29_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_29; myDirection = CT_DIR_WAVE_PORT;}

    else if (myAppIf.GetKeySuffix() == ALM_PORT_30_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_30; myDirection = CT_DIR_WAVE_PORT;}

    // SSM40/OSM20 ODUK Pool
    else if (myAppIf.GetKeySuffix() == ALM_PORT_31_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_31; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_32_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_32; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_33_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_33; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_34_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_34; myDirection = CT_DIR_WAVE_PORT;}

    else if (myAppIf.GetKeySuffix() == ALM_PORT_85_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_85; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_86_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_86; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_87_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_87; myDirection = CT_DIR_WAVE_PORT;}
    else if (myAppIf.GetKeySuffix() == ALM_PORT_88_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_88; myDirection = CT_DIR_WAVE_PORT;}

    else if (myAppIf.GetKeySuffix() == ALM_PORT_O192_OCN_A_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_12; myDirection = CT_DIR_WAVE_PORT;}

    else if (myAppIf.GetKeySuffix() == ALM_LINE_8_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_8; myDirection = CT_DIR_WAVE_LINE;}
    else if (myAppIf.GetKeySuffix() == ALM_LINE_9_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_9; myDirection = CT_DIR_WAVE_LINE;}
    else if (myAppIf.GetKeySuffix() == ALM_LINE_10_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_10; myDirection = CT_DIR_WAVE_LINE;}
    else if (myAppIf.GetKeySuffix() == ALM_LINE_11_SUFFIX) 
       {myPortNumber = CT_PORT_SIDE_11; myDirection = CT_DIR_WAVE_LINE;}
}

//-----------------------------------------------------------------
ALM_XCONModificationAction::~ALM_XCONModificationAction()
{
}

//-----------------------------------------------------------------
void ALM_XCONModificationAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR( FC_NotSupportedError, "Run not supported" );
}

//-----------------------------------------------------------------
FC_Object* ALM_XCONModificationAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam)
{
    if ( myRsAppIf )
    {
        HandleRsLayer();
    }
    else if ( myHopAppIf ) 
    {
        HandleHopLayer();
    }
    else if ( myOduAppIf ) 
    {
        HandleOduLayer();
    }

    return NULL;
}

//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleRsLayer()
{
    CT_CardFamily theCardFam = myCardIf->GetCardFamily();
    if ( theCardFam == HDTG_FAM )
    {
        HandleRsHDTGLayer();
    }
    else if ( theCardFam == SSM40_FAM || theCardFam == OMM_FAM || theCardFam == OSM_FAM )
    {
        HandleRsSSM40Layer();
    }
    else if ( theCardFam == ENH_PACKET_FAM ) 
    {
        HandleRsESMLayer();
    }
    else if ( theCardFam == FGSM_FAM )
    {
        HandleRsFGSMLayer();
    }
    else if (theCardFam == HGTMM_FAM)
    {
        HandleRSHGTMMLayer();
    }
    else if (theCardFam == HDTG2_FAM)
    {
        HandleRSHDTG2Layer();
    }
    else if ( theCardFam == ENH_TRN_FAM )
    {
        HandleRsEnhTrnLayer();
    }
    else if ( theCardFam == TRN_FAM )
    {
        HandleRsTrnLayer();
    }
    else 
    {
        HandleRsNormalLayer();
    }
}

//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleOduLayer()
{
    if ( myCardIf->GetCardFamily() == FGTMM_FAM )
    {
        HandleOduFGTMMLayer();
    }
    else if ( myCardIf->GetCardFamily() == SSM40_FAM ||
                 myCardIf->GetCardFamily() == OMM_FAM ||
                 myCardIf->GetCardFamily() == HGTMM_FAM ||
                 myCardIf->GetCardFamily() == OSM_FAM )
    {
        HandleOduSSM40Layer();
    }
    else if ( myCardIf->GetCardFamily() == FGSM_FAM )
    {
        HandleOduFGSMLayer();
    }
}

//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleRsNormalLayer()
{
    uint32 theSrcCount = 0,     theDstCount = 0;
    bool   theSrcState = false, theDstState = false;

    //=============================================================
    //                       Handle RS XCONs
    // 
    // NOTE: the RS layer handles the summation of -ALL- STS level
    //       crossconnects on the facility. If all the XCONs are
    //       in ONLY one direction (LtoP or PtoL), then we will
    //       want to suppress either maintenance signals or failures.
    // 
    // NOTE: this is the PORT side of an SMTMU!
    // 
    //=============================================================

    MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
    MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);

    (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
    (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);

    if ( theSrcState && !theDstState )
    {
        //------------------------------------------------------------------
        // This is a one way add (from STS level perspective). 
        // Therefore, the LINE side must ignore any FAILURES.
        //------------------------------------------------------------------
        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINE_FAIL_INT_XC, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORT_FAIL_INT_XC, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
    }
    else if ( theDstState && !theSrcState )
    {
        //------------------------------------------------------------------
        // This is a one way drop (from STS level perspective). 
        // Therefore, the PORT side must ignore any FAILURES.
        //------------------------------------------------------------------
        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORT_FAIL_INT_XC, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINE_FAIL_INT_XC, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
    }
    else // Either a two way -or- no XCON...// Clear BLOCK MAINTSIG and FAILURES!
    {
        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINE_FAIL_INT_XC, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORT_FAIL_INT_XC, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
    }
}

void ALM_XCONModificationAction::HandleRsHDTGLayer()
{
    //=============================================================
    //                       Handle RS XCONs
    // 
    // NOTE: HDTG Module will generate AM_BLOCK_PORTSIDE_FAILURES, 
    //       AM_BLOCK_LINESIDE_MAINTSIG and AM_BLOCK_LINESIDE_FAILURES
    //       similar to ITS_ValidateWaveFailures. This is done here
    //       because -only- the OCHPs can be handled by ITS and there
    //       is no single mapping to the port side (unlike the SMTMU).
    // 
    // NOTE: Also, ODU2s must account for Add vs. Drop here too!
    //       Additionally, remember ODU2 detection points are limited
    //       to the Client or DWDM(OCHP) which it is associated with.
    //       
    // OTU2 <--> (det)ODU2(no-det) <--> (no-det)ODU2(det) <--> OCHP/DWMD
    //  
    //=============================================================

    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();

    //-------------------------------------------------------------
    // ODUK Defects are POOLED and use the StartChannel to differ.
    // HDTG StChan (1..10)
    //-------------------------------------------------------------
    uint32 OduKStartChan = myPortNumber + 1; // HDTG Ports (0..9)
    CT_IntfId anIntfId = CT_PORT_SIDE_32;
  
	if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();
        // Coriant jchen: if HGTMS client/line mode is OTU4, alarm should not be suppressed. 
        // if client mode is HGE, there is no ODU4 entity. 
        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN || (aCardType == CARD_TYPE_HGTMS && aSignalType == CT_TEL_SIGNAL_OTU4))
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

            // ODU2s...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Drop XCON (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else // non-OCHP is a Add (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                }
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Add XCON (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else // non-OCHP is a Drop (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                }
            }
            else // Either a two way -or- no XCON...
            {
                if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                {
                    // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                    // non-OCHPs...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

                    // ODU2s...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                {
                    if ( aSignalType == CT_TEL_SIGNAL_OCH_P )
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                    else
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                }
            }
        }
    }
}


//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleRsESMLayer()
{
    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    //-------------------------------------------------------------
    // ODUK Defects are POOLED and use the StartChannel to differ.
    // ENH_PACKET_FAM StChan (1..4).
    //-------------------------------------------------------------
    uint32 OduKStartChan     = 1;     // CT_PORT_SIDE_88
    
    if ( myPortNumber == CT_PORT_SIDE_87 )  // CT_PORT_SIDE_87
        OduKStartChan = 2;
    if ( myPortNumber == CT_PORT_SIDE_86 )  // CT_PORT_SIDE_86
        OduKStartChan = 3;
    if ( myPortNumber == CT_PORT_SIDE_85 )  // CT_PORT_SIDE_85
        OduKStartChan = 4;

    if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();

        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN )
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on ESM module!
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

            // ODU2s...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Drop XCON (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                }
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Add XCON (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                }
            }
            else // Either a two way -or- no XCON...
            {
                if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                {
                    // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on ESM module!
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                    // non-OCHPs...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

                    // ODU2s...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                {
                    if ( aSignalType == CT_TEL_SIGNAL_OCH_P )
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                }
            }
        }
    }
}


//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleRsSSM40Layer()
{
    //=============================================================
    //                       Handle RS XCONs
    // 
    // NOTE: Module will generate AM_BLOCK_PORTSIDE_FAILURES, 
    //       AM_BLOCK_LINESIDE_MAINTSIG and AM_BLOCK_LINESIDE_FAILURES
    //       similar to ITS_ValidateWaveFailures. This is done here
    //       because -only- the OCHPs can be handled by ITS and there
    //       is no single mapping to the port side (unlike the SMTMU).
    // 
    // NOTE: Also, ODU1s and ODU2s must account for Add vs. Drop here too!
    //       And for SSM40 there is no static mapping!
    //  
    //=============================================================

    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();

        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN )
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE)!
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Drop XCON (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                }
                else // non-OCHP is a Add (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                }
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Add XCON (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                }
                else // non-OCHP is a Drop (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                }
            }
            else // Either a two way -or- no XCON...
            {
                if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                {
                    // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                    // non-OCHPs...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                }
                else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                {
                    if ( aSignalType == CT_TEL_SIGNAL_OCH_P )
                    {
                        
                        CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
                        /*if (myPortNumber == CT_PORT_SIDE_12 && aCardType == HGTMM)
                        {
                            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);*/
                            /*AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, */
                            /*============== ODU4 ===========*///(bbindex_t)CT_PORT_SIDE_34, CT_DIR_WAVE_PORT, 1);
//                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
    //                        /*============== ODU4 ===========*/(bbindex_t)CT_PORT_SIDE_34, CT_DIR_WAVE_PORT, 1);
                       // }
                        //else
                        //{
                        //    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        //    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                        //}
                         
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                        
                    }
                    else
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    }
                }
            }
        }
    }
}

//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleRsFGSMLayer()
{
    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();

        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN )
        {
            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            }
            else if ( theDstState && !theSrcState )
            {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
            }
            else // Either a two way -or- no XCON...
            {
                if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                {
                    // non-OCHPs...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                }
                else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                }
            }
        }
    }
}

void ALM_XCONModificationAction::HandleRSHGTMMLayer()
{
    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;
    
    CT_IntfId anIntfId;
    if (myPortNumber > CT_PORT_SIDE_1 && myPortNumber < CT_PORT_SIDE_12)
    {
         anIntfId = CT_PORT_SIDE_32;
    }
    else if (myPortNumber == CT_PORT_SIDE_12)
    {
        anIntfId = CT_PORT_SIDE_34;
    }
    else
    {
        anIntfId = CT_INTF_ID_UNKNOWN;
    }
 
    if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();

        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN )
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Drop XCON (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                }
                else // non-OCHP is a Add (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                }
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Add XCON (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                }
                else // non-OCHP is a Drop (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                }
            }
            else // Either a two way -or- no XCON...
            {
                if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                {
                    // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                    // non-OCHPs...
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                }
                else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                {
                    if ( aSignalType == CT_TEL_SIGNAL_OCH_P )
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    }
                    else
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    }
                }
            }
        }
    }
}
//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleHopLayer()
{
    uint32 theSrcCount = 0,     theDstCount = 0;
    bool   theSrcState = false, theDstState = false;

    MON_Region* aMonRegion = myHopAppIf->GetMonDefectRegionPtr();
    MON_HopDefectsRegion* aMonHopDefectsRegion = static_cast<MON_HopDefectsRegion*>(aMonRegion);

    for (uint8 i=0; i < aMonHopDefectsRegion->Size(); i++) 
    {
        (*aMonHopDefectsRegion)[i].GetDefectStatus(CT_TEL_HOP_IS_SRC, &theSrcCount, &theSrcState);
        (*aMonHopDefectsRegion)[i].GetDefectStatus(CT_TEL_HOP_IS_DST, &theDstCount, &theDstState);

        if (      theSrcState && !theDstState )
        {
            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_STS_MAINT_INT_XC, myCardIf, 0, myPortNumber, myDirection, i+1);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_STS_FAIL_INT_XC,  myCardIf,    myPortNumber, myDirection, i+1);
        }
        else if ( theDstState && !theSrcState )
        {
            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_STS_FAIL_INT_XC,  myCardIf, 0, myPortNumber, myDirection, i+1);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_STS_MAINT_INT_XC, myCardIf,    myPortNumber, myDirection, i+1);
        }
        else // Either a two way -or- no XCON...// Clear BLOCK MAINTSIG and FAILURES!
        {
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_STS_MAINT_INT_XC, myCardIf,    myPortNumber, myDirection, i+1);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_STS_FAIL_INT_XC,  myCardIf,    myPortNumber, myDirection, i+1);
        }
    }
}

//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleOduFGTMMLayer()
{
    TSXC_ConfigRegion<TSXC_Connect>* aXcConfigRegion = myCardIf->GetXCAppIf().GetXCApp().GetAgCfgRegion();

    uint8 mapIndex = 0;
    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_8_SUFFIX  )
        mapIndex = 1;
    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_9_SUFFIX  )
        mapIndex = 2;
    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_10_SUFFIX )
        mapIndex = 3;
    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_11_SUFFIX )
        mapIndex = 4;

    if (mapIndex)
    {
        if (!aXcConfigRegion || !aXcConfigRegion->IsConnectActive(XC_FGTMM_DWDM_FACILITY_ID, mapIndex, CT_XC_TYPE_ODU2))
        {
            AM_DefectCollector::GetInstance()->ReportDefect(AM_ODU2_NOT_XCON, myCardIf, 0, myPortNumber, CT_DIR_RCV, mapIndex);
        }
        else
        {
            AM_DefectCollector::GetInstance()->ClearDefect(AM_ODU2_NOT_XCON, myCardIf,     myPortNumber, CT_DIR_RCV, mapIndex);
        }
    }
}

//-----------------------------------------------------------------
// Since the SSM40 ODUk entities are dynamically connected to the 
// provisioned client facilities, we can -not- follow a static 
// mapping like we did for the HDTG RS layer. MON is providing XCON
// information directly on the ODUk Layer (MON_DEFECTS_PORT_31/32)!
//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleOduSSM40Layer()
{
    CFG_AppIf* aOduCfgAppIf = NULL;
    if ( (myPortNumber != CT_PORT_SIDE_30) && 
         (myPortNumber != CT_PORT_SIDE_31) &&
         (myPortNumber != CT_PORT_SIDE_32) &&
         (myPortNumber != CT_PORT_SIDE_33) &&
         (myPortNumber != CT_PORT_SIDE_34)) 
        return;

    aOduCfgAppIf = myCardIf->GetOduIfPtr()->GetCfgPortSideAppPtr((CT_IntfId)myPortNumber);

    CFG_Region* aCfgRegion = aOduCfgAppIf->GetCfgRegion();

    if (aCfgRegion && aCfgRegion->IsValid())
    {
        CFG_OduCfgRegion* aOduCfgRegion = static_cast<CFG_OduCfgRegion *>(aCfgRegion);
        CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();

        //OMM-X doesn't support ODU2 XC
        if ( aCardType == CARD_TYPE_OMMX && myPortNumber == CT_PORT_SIDE_32 ) 
            return;

        //===============================================================================
        // The number of ODU2s, ODU1s, ODU0s will be different in SSM40/OSM20.
        //===============================================================================
        bbindex_t aMaxOduSize = 0;
        if ( aCardType == CARD_TYPE_OSM20 )
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0FS_ON_OSM20 
                                 : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_OSM20
                                 : ((myPortNumber == CT_PORT_SIDE_32) ? NUMBER_OF_POOLED_ODU2S_ON_OSM20 : 0));
        }
        else if ( aCardType == CARD_TYPE_OMMX ) 
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0FS_ON_OMMX 
                                 : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_OMMX : 0);
        }
        else if ( aCardType == CARD_TYPE_OSM2S )
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0FS_ON_OSM2 
                                 : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_OSM2
                                 : ((myPortNumber == CT_PORT_SIDE_32) ? NUMBER_OF_POOLED_ODU2S_ON_OSM2 : 0));
        }
        else if ( aCardType == CARD_TYPE_OSM2C )
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0FS_ON_OSM2 
                                 : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_OSM2
                                 : ((myPortNumber == CT_PORT_SIDE_32) ? NUMBER_OF_POOLED_ODU2S_ON_OSM2
                                 : ((myPortNumber == CT_PORT_SIDE_33) ? NUMBER_OF_POOLED_ODU3S_ON_OSM2
                                 : ((myPortNumber == CT_PORT_SIDE_34) ? NUMBER_OF_POOLED_ODU4S_ON_OSM2 : 0))));
        }
        else if ( aCardType == CARD_TYPE_OSM1S )
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0FS_ON_OSM1S
                                 : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_OSM1S : 0);
        }
        else if (aCardType == CARD_TYPE_OSM40)
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0S_ON_OSM40 
                                 : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_OSM40
                                 : ((myPortNumber == CT_PORT_SIDE_32) ? NUMBER_OF_POOLED_ODU2S_ON_OSM40 : 0));
        }
        else
        {
            aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0FS_ON_HGTMM 
                                 : ((myPortNumber == CT_PORT_SIDE_32) ? NUMBER_OF_POOLED_ODU2S_ON_HGTMM
                                 : ((myPortNumber == CT_PORT_SIDE_34) ? NUMBER_OF_POOLED_ODU4S_ON_HGTMM : 0));
        }

        for ( bbindex_t i=0; i < aMaxOduSize; i++ )
        {
            if (i >= aOduCfgRegion->Size())
            {
                break;
            }
            if ( !(*aOduCfgRegion)[i].GetProvisionningActive() ) // If not provisioned, clear all alarms!
            {
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
            }
            //================================================================================
            else // Provisioned! Now check the status of the XCON from MON_DEFECTS_PORT_31/32!
            //================================================================================
            {
                //----------------------------------------------------------------------------
                // In addition to the XCON status, we must also factor in the type of ODU:
                //    Non-Terminated: OTN mapped client with possible MUXed ODUkj; and
                //    Terminated ODU: Client within ODUk facility (GBEP->ODU1, OC192->ODU2).
                //----------------------------------------------------------------------------
                bool IsNonTermOdu = false;
                bool IsTerminated = false;

                if ( ((*aOduCfgRegion)[i].GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT) ||
                     ((*aOduCfgRegion)[i].GetOduObjectType() == CT_ODU_POOL_MUX) )
                {
                    IsNonTermOdu = true;
                }
                else if ( ((*aOduCfgRegion)[i].GetOduObjectType() == CT_ODU_POOL_CLIENT_INSIDE_ODU) )
                {
                    IsTerminated = true;
                }

                uint32 theSrcCount = 0,     theDstCount = 0;
                bool   theSrcState = false, theDstState = false;

                MON_Region* aMonRegion = myOduAppIf->GetMonDefectRegionPtr();
                MON_OduDefectsRegion* aMonDefectsRegion = static_cast<MON_OduDefectsRegion*>(aMonRegion);
                (*aMonDefectsRegion)[i].GetDefectStatus(CT_TEL_ODU_IS_SRC, &theSrcCount, &theSrcState);
                (*aMonDefectsRegion)[i].GetDefectStatus(CT_TEL_ODU_IS_DST, &theDstCount, &theDstState);

                if ( theSrcState && !theDstState )      // client -----> (SrcXcon DetectionPt)ODUk
                {
                    if ( IsNonTermOdu )
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                    else if ( IsTerminated )
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                }
                else if ( theDstState && !theSrcState ) // client <----- (DstXcon DetectionPt)ODUk
                {
                    if ( IsNonTermOdu )
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                    else if ( IsTerminated )
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                }
                else // Either a two way -or- no XCON...
                {
                    if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                    else if ( !theSrcState && !theDstState ) // No XCON!
                    {
                        if ( IsNonTermOdu )      // Monitoring from Client (allow)!
                        {
                            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                            /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                            /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        }
                        else if ( IsTerminated ) // Monitoring from Switch (Ignore)!
                        {
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                            /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                            /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        }
                    }
                }
            }
        }
    }
}

//-----------------------------------------------------------------
// This function is copied from ALM_XCONModificationAction::HandleOduSSM40Layer() 
// in addition to add CT_PORT_SIDE_30/CT_PORT_SIDE_33 support.
//-----------------------------------------------------------------
void ALM_XCONModificationAction::HandleOduFGSMLayer()
{
    CFG_AppIf* aOduCfgAppIf = NULL;

    if ( (myPortNumber < CT_PORT_SIDE_30) || 
         (myPortNumber > CT_PORT_SIDE_33) ) 
        return;

    aOduCfgAppIf = myCardIf->GetOduIfPtr()->GetCfgPortSideAppPtr((CT_IntfId)myPortNumber);   
    CFG_Region* aCfgRegion = aOduCfgAppIf->GetCfgRegion();

    if (aCfgRegion && aCfgRegion->IsValid())
    {
        CFG_OduCfgRegion* aOduCfgRegion = static_cast<CFG_OduCfgRegion *>(aCfgRegion);

        //===============================================================================
        // For the FGSM, there are NUMBER_OF_POOLED_ODU3S_ON_FGSM ODU3s,
        //                         NUMBER_OF_POOLED_ODU2S_ON_FGSM ODU2s,
        //                         NUMBER_OF_POOLED_ODU1S_ON_FGSM ODU1s and
        //                         NUMBER_OF_POOLED_ODU0S_ON_FGSM ODU0s that must be accounted for here.
        //===============================================================================
        bbindex_t aMaxOduSize = (myPortNumber == CT_PORT_SIDE_30) ? NUMBER_OF_POOLED_ODU0S_ON_FGSM 
                             : ((myPortNumber == CT_PORT_SIDE_31) ? NUMBER_OF_POOLED_ODU1S_ON_FGSM
                             : ((myPortNumber == CT_PORT_SIDE_32) ? NUMBER_OF_POOLED_ODU2S_ON_FGSM 
                             : ((myPortNumber == CT_PORT_SIDE_33) ? NUMBER_OF_POOLED_ODU3S_ON_FGSM : 0)));

        for ( bbindex_t i=0; i < aMaxOduSize; i++ )
        {
            if ( !(*aOduCfgRegion)[i].GetProvisionningActive() ) // If not provisioned, clear all alarms!
            {
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
            }
            //================================================================================
            else // Provisioned! Now check the status of the XCON from MON_DEFECTS_PORT_31/32!
            //================================================================================
            {
                uint32 theSrcCount = 0,     theDstCount = 0;
                bool   theSrcState = false, theDstState = false;

                MON_Region* aMonRegion = myOduAppIf->GetMonDefectRegionPtr();
                MON_OduDefectsRegion* aMonDefectsRegion = static_cast<MON_OduDefectsRegion*>(aMonRegion);
                (*aMonDefectsRegion)[i].GetDefectStatus(CT_TEL_ODU_IS_SRC, &theSrcCount, &theSrcState);
                (*aMonDefectsRegion)[i].GetDefectStatus(CT_TEL_ODU_IS_DST, &theDstCount, &theDstState);

                if ( theSrcState && !theDstState )      // OTU -----> (SrcXcon DetectionPt)ODUk
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0,
                    /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                }
                else if ( theDstState && !theSrcState ) // OTU <----- (DstXcon DetectionPt)ODUk
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0,
                    /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                }
                else // Either a two way -or- no XCON...
                {
                    if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                    else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODUk ===========*/(bbindex_t)myPortNumber, CT_DIR_WAVE_PORT, i+1);
                    }
                }
            }
        }
    }
}

void ALM_XCONModificationAction::HandleRSHDTG2Layer()
{
    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();

    //-------------------------------------------------------------
    // ODUK Defects are POOLED and use the StartChannel to differ.
    // HDTG StChan (1..10), while ENH_TRN_FAM StChan (1..2).
    //-------------------------------------------------------------
    uint32 OduKStartChan = myPortNumber + 1; // HDTG2 Ports (0..15)
    
	if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();
        //CT_IntfId anIntfId = (aSignalType != CT_TEL_SIGNAL_FC8G) ? CT_PORT_SIDE_32 : CT_PORT_SIDE_30;
        bool isOduf = (aSignalType == CT_TEL_SIGNAL_FC8G) ? true : false;
        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN)
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG2 module!
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

            // ODUks...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
            /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
            /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Drop XCON (LtoP)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                    /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else if (aSignalType == CT_TEL_SIGNAL_OTU2 || aSignalType == CT_TEL_SIGNAL_OTU_TGLAN_WFS) // OTU is a Add (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else // non-OTN signal
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    if (isOduf)
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                }
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                if ( aSignalType == CT_TEL_SIGNAL_OCH_P ) // OCHP is a Add XCON (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else if (aSignalType == CT_TEL_SIGNAL_OTU2 || aSignalType == CT_TEL_SIGNAL_OTU_TGLAN_WFS) // OTU is a Add (PtoL)!
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                    /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                }
                else // non-OTN signal
                {
                    AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    if (isOduf)
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                }
            }
            else // Either a two way -or- no XCON...
            {
                if ( theSrcState && theDstState ) // Clear -ALL- inhibitors!
                {
                    if (aSignalType == CT_TEL_SIGNAL_OCH_P || 
                        aSignalType == CT_TEL_SIGNAL_OTU2 || 
                        aSignalType == CT_TEL_SIGNAL_OTU_TGLAN_WFS)
                    {
                        // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                        // non-OCHPs...
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

                        // ODU2s...
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                    else
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        if (isOduf)
                        {
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                            /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                            /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                        }
                    }
                }
                else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
                {
                    if ( aSignalType == CT_TEL_SIGNAL_OCH_P )
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODUf ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                    }
                    else  // Non-och is a Add (PtoL)!
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                        /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_32, CT_DIR_WAVE_PORT, OduKStartChan);
                        if (isOduf)
                        {
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                            /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                            /*============== ODU2 ===========*/(bbindex_t)CT_PORT_SIDE_30, CT_DIR_WAVE_PORT, OduKStartChan);
                        }
                    }
                }
            }
        }
    }
}

// EnhTrn (Eg: FGTME's line side ochp is created automatically)
void ALM_XCONModificationAction::HandleRsEnhTrnLayer()
{
    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();

    //-------------------------------------------------------------
    // ODUK Defects are POOLED and use the StartChannel to differ.
    // ENH_TRN_FAM StChan (1..2).
    //-------------------------------------------------------------
    uint32 OduKStartChan = myPortNumber + 1; // ENH_TRN (0,1)
    CT_IntfId anIntfId = CT_PORT_SIDE_34; // ENH_TRN_FAM
    if( aCardType == CARD_TYPE_FGTME )
    {
        anIntfId = CT_PORT_SIDE_33; //FGTME support ODU3 Alarm   
    }
  
	if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();
        // Coriant jchen: if HGTMS client/line mode is OTU4, alarm should not be suppressed. 
        // if client mode is HGE, there is no ODU4 entity. 
        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN || (aCardType == CARD_TYPE_HGTMS && aSignalType == CT_TEL_SIGNAL_OTU4))
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

            // ODU2s...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
            /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
            }
            else if ( theSrcState && theDstState ) // two way, Clear -ALL- inhibitors!
            {
                // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                // non-OCHPs...
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);

                // ODU2s...
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
            }
            else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
            {
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);

                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, 
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, myCardIf, 0, 
                /*============== ODU2 ===========*/(bbindex_t)anIntfId, CT_DIR_WAVE_PORT, OduKStartChan);
            }
        }
    }
}

// Trn (Eg: TGTMT/E's line side ochp is created automatically)
void ALM_XCONModificationAction::HandleRsTrnLayer()
{
    ALM_SubApplicationOnCard* aALMSubApp = dynamic_cast<ALM_SubApplicationOnCard*>(&myAppIf);
    if ( !aALMSubApp ) return;

    CFG_AppIf* rsConfigAppIf = aALMSubApp->GetCfgApp();
    if ( !rsConfigAppIf ) return;

    CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();
    if ( !rsConfigRegion ) return;

    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
    if(aCardType != CARD_TYPE_TRN_10GT && aCardType != CARD_TYPE_TRN_10GTE)
    {
        return;
    }

    //-------------------------------------------------------------
    // ODUK Defects are POOLED and use the StartChannel to differ.
    //-------------------------------------------------------------
    uint32 OduKStartChan = myPortNumber + 1;
  
	if (rsConfigRegion->IsValid())
    {
        CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
        CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();
        if ( aSignalType == CT_TEL_SIGNAL_UNKNOWN )
        {
            // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE)
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

            // non-OCHPs...
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
        }
        else
        {
            uint32 theSrcCount = 0,     theDstCount = 0;
            bool   theSrcState = false, theDstState = false;
    
            MON_Region* aMonRegion = myRsAppIf->GetMonDefectRegionPtr();
            MON_RsDefectsRegion* aMonRsDefectsRegion = static_cast<MON_RsDefectsRegion*>(aMonRegion);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_SRC, &theSrcCount, &theSrcState);
            (*aMonRsDefectsRegion)[0].GetDefectStatus(CT_TEL_RS_IS_DST, &theDstCount, &theDstState);
    
            if ( theSrcState && !theDstState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
            }
            else if ( theDstState && !theSrcState )
            {
                //------------------------------------------------------------------
                // OCHPs must be handled differently than clientSide interfaces!
                //------------------------------------------------------------------
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_FAILURES, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
            }
            else if ( theSrcState && theDstState ) // two way, Clear -ALL- inhibitors!
            {
                // OCHPs which are treated as "portSide" interface but still conntected to DWDM (LINESIDE) on HDTG module!
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);

                // non-OCHPs...
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_MAINTSIG, myCardIf,    myPortNumber, CT_DIR_WAVE_LINE);
            }
            else if ( !theSrcState && !theDstState ) // No XCON (see MR t71mr00115859)!
            {
                AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_LINESIDE_FAILURES, myCardIf,    myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_PORT);
                AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_LINESIDE_MAINTSIG, myCardIf, 0, myPortNumber, CT_DIR_WAVE_LINE);
            }
        }
    }
}

