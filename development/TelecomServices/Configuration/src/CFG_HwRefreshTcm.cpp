// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_TcmIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <ErrorService/FC_Error.h>
#include "../CFG_HwRefreshTcm.h"
#include "../CFG_Tcm.h"
#include "../CFG_TcmAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_OduDefinitions.h>


CFG_HwRefreshTcm::CFG_HwRefreshTcm(CFG_AppIf& theCfgIf, TSPII_TcmRegion&  theTcmPiiRegion, CT_NumberOfOdus  theTcmsOnCard, CT_NumberOfOdus  theInstancesPerRound):
    CFG_HwRefreshAction(theCfgIf),
    myTcmPiiRegion(theTcmPiiRegion),
    myTcmsOnCard(theTcmsOnCard),
    myInstancesPerRound(theInstancesPerRound),
    myRoundCount(0)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddInputRegion(theCfgIf.GetAutomaticCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());

    for (uint16 anIndex = 0; anIndex < myTcmsOnCard; anIndex++)
    {
        myPiiTspiiTcmInstance.push_back(0xffff);
        myNewPiiTspiiTcmInstance.push_back(0xffff);
    }

    if (myTcmsOnCard >= myTcmPiiRegion.Size()) 
    {
        myTcmsOnCard = myTcmPiiRegion.Size();
    }
}

CFG_HwRefreshTcm::~CFG_HwRefreshTcm()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshTcm::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    uint16 aSdInterval  = 0;
    uint32 aSdThreshold = 0;

    uint16 aStartIndex = 0;
    uint16 anEndIndex = 0;

    aStartIndex = myInstancesPerRound * myRoundCount;
    anEndIndex  = aStartIndex + myInstancesPerRound;

    myTcmsOnCard = (myTcmsOnCard <= GetCfgIf().GetCfgRegion()->Size()) ? myTcmsOnCard : GetCfgIf().GetCfgRegion()->Size();
    if(anEndIndex>=myTcmsOnCard)
    {
        anEndIndex = myTcmsOnCard;
    }

    /*to be studied, use the line below leads to BDI maintenance signal insertion quite slow*/
    for (uint16 anIndex = 0; anIndex < myTcmsOnCard; anIndex++)  
    //for (uint16 anIndex = aStartIndex; anIndex < anEndIndex; anIndex++)
    {
        CFG_Tcm& aCfgObject = static_cast<CFG_Tcm&>((*GetCfgIf().GetCfgRegion())[bbindex_t(anIndex)]);
        CFG_TcmAutomatic& aAutoCfgObject = static_cast<CFG_TcmAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[bbindex_t(anIndex)]);

        CT_ODU_Identifier aTcmIdentifier = aCfgObject.GetTcmIdentifier();
        bool aIsProvisioned  = aCfgObject.GetProvisionningActive();

        TSPII_TcmIf& aTcmPiiObject = myTcmPiiRegion[(bbindex_t)anIndex];

        //if tcm id is is valid then doesn't call tspii.
        if (((aTcmIdentifier.GetDevicePort() == 0xff) || (aTcmIdentifier.GetDeviceChannel() == 0xff)) && (!aIsProvisioned)) 
        {
            //Don't use Reset to delete, because the sequence is not correct.
            //aTcmPiiObject.Reset();
            //aTcmPiiObject.RefreshSet();
            aTcmPiiObject.SetBurstyBerSdThreshold(0, 0);
            aTcmPiiObject.SetTxTrace(CT_G709Trace());        
            aTcmPiiObject.SetTcmDelayEnabled(false);      
            aTcmPiiObject.ForceBDI(false);  
            aTcmPiiObject.ForceTCMIndication(CT_TCM_INDICATION_NONE);              
            aTcmPiiObject.SetAutoTCMIndication(CT_TCM_INDICATION_BIAE, false);
            aTcmPiiObject.SetTcmLTCActEnabled(false);

            TSPII_TcmMapRecord *aTspiiTcmMap = aTcmPiiObject.GetTcmMap();

           
            aTcmPiiObject.SetTcmOrder(CT_TCM_Order_END);

            //For deleting TCM, FW needs below API to be called after all other APIs.
            aTcmPiiObject.SetTCMMode(CT_TCM_MODE_NONE);

            //aTspiiTcmMap->TcmChannel   = anIndex;
            //aTspiiTcmMap.OduIndex     = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(aTcmIdentifier.GetIdValue());
            aTspiiTcmMap->TcmLevel     = CT_TCM_Level_UNKNOWN;
            aTspiiTcmMap->TcmDirection = CT_ODU_Direction_A;        
            //aTspiiTcmMap.OduKLevel    = aTcmIdentifier.GetOduKvalueEnum();
            aTcmPiiObject.SetTcmMap(*aTspiiTcmMap);

            continue;
        }        

        //set the map
        TSPII_TcmMapRecord aTspiiTcmMap;

        aTspiiTcmMap.TcmChannel   = anIndex;
        aTspiiTcmMap.OduIndex     = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(aTcmIdentifier.GetIdValue());
        aTspiiTcmMap.TcmLevel     = aTcmIdentifier.GetTcmLevelEnum();
        aTspiiTcmMap.TcmDirection = aTcmIdentifier.GetOduDirection();        
        aTspiiTcmMap.OduKLevel    = aTcmIdentifier.GetOduKvalueEnum();
        
        aTcmPiiObject.SetTcmMap(aTspiiTcmMap);
        aTcmPiiObject.SetTCMMode(aCfgObject.GetTcmMode());        

        bool aAutomaticSuppressBI = aAutoCfgObject.GetSuppressBackwardInd();        

        aSdInterval  = aCfgObject.GetBerSdInterval();
        aSdThreshold = aCfgObject.GetBerSdThreshold();        
        aTcmPiiObject.SetBurstyBerSdThreshold(aSdInterval, aSdThreshold);
        aTcmPiiObject.SetServer(aCfgObject.GetServerID());
        aTcmPiiObject.SetTcmOrder(aCfgObject.GetTcmOrder());
        aTcmPiiObject.SetTcmLTCActEnabled(aCfgObject.GetTcmLTCActEnabled());

        //Below interfaces should be called after SetTCMMode.
        aTcmPiiObject.SetTxTrace(aCfgObject.GetSentTrace());        
        aTcmPiiObject.SetTcmDelayEnabled(aCfgObject.GetTcmDelayEnabled());    

        //in src mode, the ForceBDI should always be false
        bool aForceBDI = false;
        if( aCfgObject.GetTcmMode() == CT_TCM_MODE_SOURCE)
        {
            aTcmPiiObject.ForceBDI(aForceBDI);
        }
        else
        {
            aForceBDI = aAutoCfgObject.GetForceBDI() && !aAutomaticSuppressBI;
            aTcmPiiObject.ForceBDI(aForceBDI);
        }

        //An operational ODUkT Source shall insert the appropriate value into the BIAE bits in the TCM overhead 
        //associated with the ODUkT when a near end IAE is detected. To do so, 
        if( aCfgObject.GetTcmMode() == CT_TCM_MODE_SRC_SNK || aCfgObject.GetTcmMode() == CT_TCM_MODE_SRC_SNK_NIM)
        {
            aTcmPiiObject.SetAutoTCMIndication(CT_TCM_INDICATION_BIAE, true);
        }
        else
        {
            aTcmPiiObject.SetAutoTCMIndication(CT_TCM_INDICATION_BIAE, false);
        }

        //when TCM mode changed, fw needs this be called. Otherwise, there will be dLTC always.
        aTcmPiiObject.ForceTCMIndication(CT_TCM_INDICATION_NONE);  

    } // for (uint32 anIndex = 0; anIndex < myTcmsOnCard; anIndex++)

    if (anEndIndex>=myTcmsOnCard)
    {
        myRoundCount = 0;
    }
    else
    {
        myRoundCount++;
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    if (anEndIndex < myTcmsOnCard) 
    {
        //wake up the second run.
        GetCfgIf().WakeUpNextRun();
    }
    
    return NULL;
}



