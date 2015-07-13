// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#include "../SP_RequestParser.h"
#include "../SP_ProtectionAction.h"
#include "../SP_SsmRegion.h"
#include "../SP_Utilities.h"
#include "../SP_ProtectionGroupConfig.h"
#include "../SP_Defects.h"
#include "../SP_Application.h"
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_MsStatus.h>
#include <Monitoring/MON_T1E1Status.h>
#include <SignalProtection/SP_SystemTimingBaseApplication.h>
#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <CommonTypes/CT_SP_SwitchingPriority.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <TsPii/TSPII_RsIf.h>
#include <TsPii/TSPII_MsIf.h>
#include <TsPii/TSPII_GfpIf.h>
#include <TsPii/TSPII_FecIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_AppIf.h>
#include <CsPii/CSPII_CardIF.h>

//##ModelId=39058BF4024D
SP_RequestParser::~SP_RequestParser()
{
}

//##ModelId=3B8BC9FB0184
void SP_RequestParser::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}


//##ModelId=39ACEFCA016A
CT_SP_AutoSwitchDefect SP_RequestParser::UpdateFailureStatus(
                                               MON_Region& theDefectRegion,
                                               MON_Region* theStatusRegion,
                                               SP_RequestParser::Defect& thePreviousSF,
                                               SP_RequestParser::Defect& thePreviousSFLow,
                                               SP_RequestParser::Defect& thePreviousSD,
                                               CT_SP_1plus1Type theType,
                                               CT_SP_1plus1SubType theSubType,
                                               bool& theGlitchIndication,
                                               int theIndex,
                                               CT_IntfId thePortId,
                                               SP_ProtectionLayer theLayer,
                                               SP_ProtectionAction* theProtectionAction,
                                               CT_SP_Protection theProtSide,
                                               unsigned int theTspiiIntf,
                                               SP_Defects* theSPDefects)
{
    // -------------------------------------------------
    // Read SD and SF failures from monitoring
    // This must be done at each execution in order to
    // refresh previous count and status.
    // -------------------------------------------------
    bool aSFStatus(false), aSFLowStatus(false), aSDStatus(false);
    uint32 aSFCount(0), aSFLowCount(0), aSDCount(0);
    MON_Defects* aMonitoringObject = NULL;
    uint32 aCount=0;
    bool aState=false;
    bool rc(true), ignoreGlitch(false);

    //if the index is not valid
    //return SF
    if (theIndex == -1)
        return CT_SP_AUTO_SF;

    // check if SF and/or SD defect status on facility(path)
    if (theType == CT_SP_LINEAR)
    {
        aMonitoringObject = static_cast<MON_Defects*>(&(theDefectRegion[theIndex]));
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_MS_SFBER_DEFECT, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_MS_AIS_DEFECT, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_MS_LOCK, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        //Get any specific defects (this is done for perfomance reasons)
        theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);

        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_MS_SDBER_DEFECT, &aCount, &aState);
        aSDStatus |= aState;
        aSDCount  += aCount;
        aCount=0,aState=false;
        //Get any specific defects (this is done for perfomance reasons)
        theProtectionAction->GetSpecificSDDefects(theProtSide, thePortId, &aSDCount, &aSDStatus);
    }
    else if (theType == CT_SP_UPSR)
    {
        //SF
        aMonitoringObject = static_cast<MON_Defects*>(&(theDefectRegion[theIndex]));
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_HOP_AIS_DEFECT, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_HOP_LOP_DEFECT, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_HOP_UNEQ_DEFECT, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_HOP_LOCK, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;
        aCount=0,aState=false;
        //Get any specific defects (this is done for perfomance reasons)
        theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);

        //SF LOW
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_HOP_SFBER_DEFECT, &aCount, &aState);
        aSFLowStatus |= aState;
        aSFLowCount  += aCount;
        aCount=0,aState=false;
        theProtectionAction->GetSpecificSFLowDefects(theProtSide, thePortId, &aSFLowCount, &aSFLowStatus);

        //SD
        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_HOP_SDBER_DEFECT, &aCount, &aState);
        aSDStatus |= aState;
        aSDCount  += aCount;
        aCount=0,aState=false;
        //Get any specific defects (this is done for perfomance reasons)
        theProtectionAction->GetSpecificSDDefects(theProtSide, thePortId, &aSDCount, &aSDStatus);

    }
    else if (theType == CT_SP_TIMING)
    {

        aMonitoringObject = static_cast<MON_Defects*>(&(theDefectRegion[theIndex]));

        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_MS_LOCK, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;

        aCount=0,aState=false;
        aMonitoringObject->GetDefectStatus(CT_TEL_MS_REF_DEFECT, &aCount, &aState);
        aSFStatus |= aState;
        aSFCount  += aCount;


        aCount=0,aState=false;
        //Get any specific defects (this is done for perfomance reasons)
        theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);

        if (theProtectionAction->IsSsmSwitchingAllowed())
        {
            //if the Rx SSM value < internal clock but not DUS/DNU
            //consider the reference failed
            CT_FAC_RxSsm rxSSM = UpdateRxSSM(theStatusRegion, theIndex, theSubType, theProtSide, theProtectionAction->GetConfig().GetFacilityStandard());
            if (GetHighestSSMPriority(GetFreeRunSsm(theProtectionAction->GetConfig().GetFacilityStandard()), rxSSM) && (rxSSM != CT_RxSsm_DUS && rxSSM != CT_RxSsm_DNU) )
                aSFStatus = true;
        }

        //SF LOW
        aCount=0,aState=false;
        //Get any specific defects (this is done for perfomance reasons)
        theProtectionAction->GetSpecificSFLowDefects(theProtSide, thePortId, &aSFLowCount, &aSFLowStatus);

    }
    else if (theType == CT_SP_DPRING ||
             theType == CT_SP_OAPS)
    {
        //layer to monitor is dependent on the card
        if (theLayer == SP_ODU)
        {
            aMonitoringObject = static_cast<MON_Defects*>(&(theDefectRegion[theIndex]));
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_ODU_AIS_DEFECT, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_ODU_LCK_DEFECT, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_ODU_OCI_DEFECT, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_ODU_LOCK, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
            aCount=0,aState=false;
            //Get any specific defects (this is done for perfomance reasons)
            theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);

            //SD
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aCount, &aState);
            aSDStatus |= aState;
            aSDCount  += aCount;
            aCount=0,aState=false;
            //Get any specific defects (this is done for perfomance reasons)
            theProtectionAction->GetSpecificSDDefects(theProtSide, thePortId, &aSDCount, &aSDStatus);

        }
        else if (theLayer == SP_OPT)
        {
            aMonitoringObject = static_cast<MON_Defects*>(&(theDefectRegion[theIndex]));
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_OPT_LOCK, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
            //Get any specific SF defects
            theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);

            //SF LOW
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_OPT_SDPWR_DEFECT, &aCount, &aState);
            aSFLowStatus |= aState;
            aSFLowCount  += aCount;
            //Get any specific SF_Low defects
            theProtectionAction->GetSpecificSFLowDefects(theProtSide, thePortId, &aSFLowCount, &aSFLowStatus);

            //SD
            aCount=0,aState=false;
            theProtectionAction->GetSpecificSDDefects(theProtSide, thePortId, &aSDCount, &aSDStatus);
        }
        else
        {
            FC_REPORT_ERROR(FC_NotSupportedError, "Unexpected 1+1 monitoring layer for OAPS or DPRing");
            return CT_SP_AUTO_SF;
        }
    }
    else if (theType == CT_SP_YCABLE)
    {
        if (theLayer == SP_OPT)
        {
			uint32 PII_count= 0;

			//SF-HIGH
            //Common SF HIGH Defects
            aMonitoringObject = static_cast<MON_Defects*>(&(theDefectRegion[theIndex]));
            aCount=0,aState=false;
            aMonitoringObject->GetDefectStatus(CT_TEL_OPT_LOCK, &aCount, &aState);
            aSFStatus |= aState;
            aSFCount  += aCount;
			
            if (theTspiiIntf != TSPII_DONT_CARE)
            {
                TSPII_RsRegion*            aRsRegion = NULL;
                TSPII_MsRegion*            aMsRegion = NULL;
                TSPII_GfpRegion*           aGfpRegion = NULL;
                
                CFG_Region* aCfgOptRegion = NULL;
                CFG_Opt* aCfgOptObject = NULL;

                aCfgOptRegion = theProtectionAction->GetAppIf().GetCardContext().GetOptIf().GetCfgPortSideApp(thePortId).GetCfgRegion();
                aCfgOptObject = static_cast<CFG_Opt*>(&((*aCfgOptRegion)[0]));
                if (aCfgOptObject->GetLaserEnable() == false)
                {
                    aSFStatus |= true;
                    aSFCount += 1;
                }

                //GFP
                aGfpRegion = TSPII_SubApplication::GetInstance()->GetGfp(theTspiiIntf);
                if (aGfpRegion)
                {
                    PII_count = (*aGfpRegion)[0].GetCsfLos();
                    if(PII_count%2 != 0)
                    {
                        aSFStatus |= true;
                        aSFCount += 1;
                    }
                    PII_count = (*aGfpRegion)[0].GetCsfLosync();
                    if(PII_count%2 != 0)
                    {
                        aSFStatus |= true;
                        aSFCount += 1;
                    }
                    PII_count = (*aGfpRegion)[0].GetLofd();
                    if(PII_count%2 != 0)
                    {
                        aSFStatus |= true;
                        aSFCount += 1;
                    }
                }

                //RS
                aRsRegion = TSPII_SubApplication::GetInstance()->GetRs(theTspiiIntf);
                if (aRsRegion)
                {
                    PII_count = (*aRsRegion)[0].GetInternalCSFOPU(); //CSF-OPU
                    if(PII_count%2 != 0)
                    {
                        aSFStatus |= true;
                        aSFCount += 1;
                    }
                    PII_count = (*aRsRegion)[0].GetInternalLOF(); //Internal LOF
                    if(PII_count%2 != 0)
                    {
                        aSFStatus |= true;
                        aSFCount += 1;
                    }
                }

                //MS
                aMsRegion = TSPII_SubApplication::GetInstance()->GetMs(theTspiiIntf);
                if (aMsRegion)
                {
                    PII_count = (*aMsRegion)[0].GetInternalAis();
                    if(PII_count%2 != 0)
                    {
                        aSFStatus |= true;
                        aSFCount += 1;
                    }
                }
            }

            //Card failures
            if (theSPDefects != NULL)
            {
                //Check for equipment failures
                theSPDefects->GetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT, &aCount, &aState);
                if (aState == true)
                {
                    aSFStatus |= true;
                    aSFCount += 1;
                }

            }
            //Get any other module specific SF defects
            theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);




			aCount=0,aState=false;
			//SF LOW
			if (theTspiiIntf != TSPII_DONT_CARE)
            {
				TSPII_OpticalRegion*       aOpticalRegion = NULL;
				TSPII_FecRegion*           aFecRegion = NULL;
				TSPII_RsRegion*            aRsRegion = NULL;
				MON_Region* aDefectRegion = NULL;
				//Port rx los should only be considered for y-cable switching if traffic is being
                //added on the port. Otherwise this defect should be ignored (for example in a 
                //unidirectional drop scenario)
                aDefectRegion = theProtectionAction->GetAppIf().GetCardContext().GetRsIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
                aMonitoringObject = static_cast<MON_Defects*>(&((*aDefectRegion)[0]));
                aMonitoringObject->GetDefectStatus(CT_TEL_RS_IS_SRC, &aCount, &aState);
                //Connected as a src, check los indication
                if (aState == true)
                {
			        aOpticalRegion = TSPII_SubApplication::GetInstance()->GetOptical(theTspiiIntf);
			        PII_count = (*aOpticalRegion)[0].GetOptLOS();
		            if(PII_count%2 != 0)
		            {
		                aSFLowStatus |= true;
                        aSFLowCount += 1;
		            }
                }

				aRsRegion = TSPII_SubApplication::GetInstance()->GetRs(theTspiiIntf);
				if (aState == true)
                {
	                PII_count = (*aRsRegion)[0].GetTlabAISRx();
	                if(PII_count%2 != 0)
	                {
		                aSFLowStatus |= true;
                        aSFLowCount += 1;
	                }
                    PII_count = (*aRsRegion)[0].GetLOF();
	                if(PII_count%2 != 0)
	                {
		                aSFLowStatus |= true;
                        aSFLowCount += 1;
	                }
                }

				aFecRegion = TSPII_SubApplication::GetInstance()->GetFec(theTspiiIntf);
                if (aFecRegion)
                {
                    if (aState == true)
                    {
                        PII_count = (*aFecRegion)[0].GetLOF();
                        if(PII_count%2 != 0)
                        {
                            aSFLowStatus |= true;
                            aSFLowCount += 1;
                        }

                        PII_count = (*aFecRegion)[0].GetLOMF();
                        if(PII_count%2 != 0)
                        {
                            aSFLowStatus |= true;
                            aSFLowCount += 1;
                        }
                    }
                }
			}

			aCount=0,aState=false;
			//sfp failures
            if (theSPDefects != NULL)
            {
                //Check for sfp failures
                theSPDefects->GetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT, &aCount, &aState);
                if (aState == true)
                {
                    aSFLowStatus |= true;
                    aSFLowCount += 1;
                }

            }
			theProtectionAction->GetSpecificSFLowDefects(theProtSide, thePortId, &aSFLowCount, &aSFLowStatus);

            
			//SD
            //Get any other module specific SD defects
            theProtectionAction->GetSpecificSDDefects(theProtSide, thePortId, &aSDCount, &aSDStatus);
            
        }
        else
        {
            FC_REPORT_ERROR(FC_NotSupportedError, "Unexpected 1+1 monitoring layer for Y-CABLE");
            return CT_SP_AUTO_SF;
        }
    }
	else if (theType == CT_SP_SNCN ||
		     theType == CT_SP_SNCI ||
		     theType == CT_SP_SNCS)
	{
		//Get any specific defects (this is done for perfomance reasons)
		//SF
        theProtectionAction->GetSpecificSFDefects(theProtSide, thePortId, &aSFCount, &aSFStatus);
		//SD
		theProtectionAction->GetSpecificSDDefects(theProtSide, thePortId, &aSDCount, &aSDStatus);
	}
    else
    {
        FC_REPORT_ERROR(FC_NotSupportedError, "Unexpected 1+1 type");
        return CT_SP_AUTO_SF;
    }

    //ignore all glitches
    ignoreGlitch = true;

    //-------------
    // check if SF
    //-------------
    // Check if we were called because of a glitch:
    // status should be the same, but count has changed
    // This means we should run the protection action again
    // to make sure we are stable.
    /*Commenting out since we are always ignoring glitches. Uncomment if we 
      ever want to look at glitches
    if ((thePreviousSF.myStatus == aSFStatus) &&
        (thePreviousSF.myCount != aSFCount) &&
        (!ignoreGlitch))
    {
        theGlitchIndication = true;
        aSFStatus = true;
    }
    */

    // remember last count & status
    thePreviousSF.myCount = aSFCount;
    thePreviousSF.myStatus = aSFStatus;

    // Return SF is status is true
    if (aSFStatus)
        return CT_SP_AUTO_SF;

    //-------------
    // check if SF Low
    //-------------
    // Check if we were called because of a glitch:
    // status should be the same, but count has changed
    // This means we should run the protection action again
    // to make sure we are stable.
    /*Commenting out since we are always ignoring glitches. Uncomment if we 
      ever want to look at glitches
    if ((thePreviousSFLow.myStatus == aSFLowStatus) &&
        (thePreviousSFLow.myCount != aSFLowCount) &&
        (!ignoreGlitch))
    {
        theGlitchIndication = true;
        aSFLowStatus = true;
    }
    */

    // remember last count & status
    thePreviousSFLow.myCount = aSFLowCount;
    thePreviousSFLow.myStatus = aSFLowStatus;

    // Return SF Low if status is true
    if (aSFLowStatus)
        return CT_SP_AUTO_SF_LOW;


    //-------------
    // check if SD
    //-------------
    // Check if we were called because of a glitch:
    // status should be the same, but count has changed
    // This means we should run the protection action again
    // to make sure we are stable.
    /*Commenting out since we are always ignoring glitches. Uncomment if we 
      ever want to look at glitches
    if ((thePreviousSD.myStatus == aSDStatus) &&
        (thePreviousSD.myCount != aSDCount) &&
        (!ignoreGlitch))
    {
        theGlitchIndication = true;
        aSDStatus = true;
    }
    */

    // remember last count & status
    thePreviousSD.myCount = aSDCount;
    thePreviousSD.myStatus = aSDStatus;

    // return SD if status is true
    if (aSDStatus)
        return CT_SP_AUTO_SD;

    // otherwise return no defect
    return CT_SP_AUTO_NONE;

}

CT_FAC_RxSsm SP_RequestParser::UpdateRxSSM(MON_Region* theStatusRegion, int theIndex, CT_SP_1plus1SubType theSubType, CT_SP_Protection theSide, CT_TEL_FacilityStandard theFacStandard)
{
    MON_MsStatus* aMsMonitoringStatusObject = NULL;
    CT_FAC_RxSsm rxSSM = CT_RxSsm_DUS;
    if (theSubType == CT_SP_LINE ||
        theSubType == CT_SP_EXT_OPSM)
    {
        aMsMonitoringStatusObject = static_cast<MON_MsStatus*>(&((*theStatusRegion)[theIndex]));
        rxSSM = aMsMonitoringStatusObject->GetRxSsm();
    }
    else if (theSubType == CT_SP_EXT_SYS)
    {
        SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion();
        if (theSpStatusRegion->IsValid())
        {
            if ((*theSpStatusRegion)[0].IsSsmValid(theSide))
            {
                //aT1E1MonitoringStatusObject = static_cast<MON_T1E1Status*>(&(theStatusRegion[theIndex]));
                rxSSM = (*theSpStatusRegion)[0].GetSsmValue(theSide);
            }
            else
            {
                //Assume a default SSM value
                rxSSM = GetFreeRunSsm(theFacStandard);
            }
        }
        else
        {
            //Assume a default SSM value
            rxSSM = GetFreeRunSsm(theFacStandard);
        }
    }
    else if (theSubType == CT_SP_EXT_SLAVE)
    {
        SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion();
        if (theSpStatusRegion->IsValid())
        {
            CT_SP_Protection theSelectedSide = (*theSpStatusRegion)[0].GetSelectedSide();
            if ((*theSpStatusRegion)[0].IsSsmValid(theSelectedSide))
            {
                //aT1E1MonitoringStatusObject = static_cast<MON_T1E1Status*>(&(theStatusRegion[theIndex]));
                rxSSM = (*theSpStatusRegion)[0].GetSsmValue(theSelectedSide);
            }
            else
            {
                //Assume a default SSM value
                rxSSM = GetFreeRunSsm(theFacStandard);
            }
        }
        else
        {
            //Assume a default SSM value
            rxSSM = GetFreeRunSsm(theFacStandard);
        }
    }

    return rxSSM;

}

CT_FAC_RxSsm SP_RequestParser::UpdateRxSSM(CT_ShelfId theShelf, CT_TEL_FacilityStandard theFacStandard)
{
    CT_FAC_RxSsm rxSSM = CT_RxSsm_DUS;
    SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion(theShelf);
    if (theSpStatusRegion->IsValid())
    {
        CT_SP_Protection theSelectedSide = (*theSpStatusRegion)[0].GetSelectedSide();
        if ((*theSpStatusRegion)[0].IsSsmValid(theSelectedSide))
        {
                
            rxSSM = (*theSpStatusRegion)[0].GetSsmValue(theSelectedSide);
        }
        else
        {
            //Assume a default SSM value
            rxSSM = GetFreeRunSsm(theFacStandard);
        }
    }
    else
    {
        //Assume a default SSM value
        rxSSM = GetFreeRunSsm(theFacStandard);
    }
    return rxSSM;
}

bool SP_RequestParser::GetHighestSSMPriority(CT_FAC_RxSsm aSSM, CT_FAC_RxSsm bSSM)
{
    int aPriority = CT_SP_SwitchingPriority::GetSSMPriority(aSSM);
    int bPriority = CT_SP_SwitchingPriority::GetSSMPriority(bSSM);

    if (aPriority > bPriority) //means that aSSM is better in quality than bSSM
        return true;
    else
        return false;
}

CT_IntfId SP_RequestParser::GetActiveSyncRefId(CT_ShelfId theShelf, CT_SlotId theSlot, CT_SP_1plus1SubType theSubType, CT_SP_Protection theSide)
{
	CT_IntfId aActiveRefId = CT_INTF_ID_UNKNOWN;
	SP_SsmRegion* theSpStatusRegion = NULL;
	CT_SP_Protection theSelectedSide = theSide;

	if (theSubType == CT_SP_EXT_SYS)
	{
		theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion();
	}
	else if (theSubType == CT_SP_EXT_SLAVE)
	{
		theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion();
		theSelectedSide = (*theSpStatusRegion)[0].GetSelectedSide();
	}
	else
	{
		return aActiveRefId;
	}

	if (theSpStatusRegion->IsValid())
	{
		if ((*theSpStatusRegion)[0].IsSsmValid(theSelectedSide))
		{
			if (theSelectedSide == CT_SP_WORKING_SIDE)
			{
				if ((*theSpStatusRegion)[0].GetInterfaces().working.GetShelfId() == theShelf &&
					(*theSpStatusRegion)[0].GetInterfaces().working.GetSlotId() == theSlot)
				{
					aActiveRefId = (*theSpStatusRegion)[0].GetInterfaces().working.GetPortId();
				}
			}
			else if (theSelectedSide == CT_SP_PROTECTION_SIDE)
			{
				if ((*theSpStatusRegion)[0].GetInterfaces().protection.GetShelfId() == theShelf &&
					(*theSpStatusRegion)[0].GetInterfaces().protection.GetSlotId() == theSlot)
				{
					aActiveRefId = (*theSpStatusRegion)[0].GetInterfaces().protection.GetPortId();
				}
			}
		}
	}

	return aActiveRefId;
}


CT_IntfId SP_RequestParser::GetActiveSyncRefId(CT_ShelfId theShelf, CT_SlotId theSlot)
{
	CT_IntfId aActiveRefId = CT_INTF_ID_UNKNOWN;
	SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion(theShelf);
	if (theSpStatusRegion->IsValid())
	{
		CT_SP_Protection theSelectedSide = (*theSpStatusRegion)[0].GetSelectedSide();
		if ((*theSpStatusRegion)[0].IsSsmValid(theSelectedSide))
		{
            if (theSelectedSide == CT_SP_WORKING_SIDE)
			{
				if ((*theSpStatusRegion)[0].GetInterfaces().working.GetShelfId() == theShelf &&
                    (*theSpStatusRegion)[0].GetInterfaces().working.GetSlotId() == theSlot)
				{
                    aActiveRefId = (*theSpStatusRegion)[0].GetInterfaces().working.GetPortId();
				}
			}
			else if (theSelectedSide == CT_SP_PROTECTION_SIDE)
			{
				if ((*theSpStatusRegion)[0].GetInterfaces().protection.GetShelfId() == theShelf &&
                    (*theSpStatusRegion)[0].GetInterfaces().protection.GetSlotId() == theSlot)
				{
                    aActiveRefId = (*theSpStatusRegion)[0].GetInterfaces().protection.GetPortId();
				}
			}
		}
	}

	return aActiveRefId;
}

void SP_RequestParser::GetSelectedSsmShelfSlot(CT_SP_1plus1SubType theSubType, CT_SP_Protection theSide, CT_TEL_FacilityStandard theFacStandard, CT_ShelfId* theSelShelf, CT_SlotId* theSelSlot)
{
    bool invalid = true;
    if (theSubType == CT_SP_LINE ||
        theSubType == CT_SP_EXT_OPSM)
    {
        (*theSelShelf) = CSPII_CardIF::GetInstance()->GetShelfId();
        (*theSelSlot) = CSPII_CardIF::GetInstance()->GetSlotId();
        invalid = false;
    }
    else if (theSubType == CT_SP_EXT_SYS)
    {
        SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion();
        if (theSpStatusRegion->IsValid())
        {
            if ((*theSpStatusRegion)[0].IsSsmValid(theSide))
            {
                (*theSelShelf) = (*theSpStatusRegion)[0].GetSsmShelf(theSide);    
                (*theSelSlot) = (*theSpStatusRegion)[0].GetSsmSlot(theSide);   
                invalid = false;
            }
        }
    }
    else if (theSubType == CT_SP_EXT_SLAVE)
    {
        SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion();
        if (theSpStatusRegion->IsValid())
        {
            CT_SP_Protection theSelectedSide = (*theSpStatusRegion)[0].GetSelectedSide();
            if ((*theSpStatusRegion)[0].IsSsmValid(theSelectedSide))
            {
                (*theSelShelf) = (*theSpStatusRegion)[0].GetSsmShelf(theSelectedSide);    
                (*theSelSlot) = (*theSpStatusRegion)[0].GetSsmSlot(theSelectedSide);  
                invalid = false;
            }
        }
    }

    if (invalid)
    {
        (*theSelShelf) = 0;    
        (*theSelSlot) = 0;    
    }

}
    
void SP_RequestParser::GetSelectedSsmShelfSlot(CT_ShelfId theShelf, CT_TEL_FacilityStandard theFacStandard, CT_ShelfId* theSelShelf, CT_SlotId* theSelSlot)
{
    bool invalid = true;
    SP_SsmRegion* theSpStatusRegion = T6100_MainAppIf::Instance().GetSpSystemTimingApp().GetSsmRegion(theShelf);
    if (theSpStatusRegion->IsValid())
    {
        CT_SP_Protection theSelectedSide = (*theSpStatusRegion)[0].GetSelectedSide();
        if ((*theSpStatusRegion)[0].IsSsmValid(theSelectedSide))
        {
            (*theSelShelf) = (*theSpStatusRegion)[0].GetSsmShelf(theSelectedSide);    
            (*theSelSlot) = (*theSpStatusRegion)[0].GetSsmSlot(theSelectedSide);    
            invalid = false;
        }
    }

    if (invalid)
    {
        (*theSelShelf) = 0;    
        (*theSelSlot) = 0;    
    }
}


//##ModelId=3B8BC9FB013E
FC_Stream& SP_RequestParser::SnapshotWrite(FC_Stream& theStream)
{
    return theStream;
}
