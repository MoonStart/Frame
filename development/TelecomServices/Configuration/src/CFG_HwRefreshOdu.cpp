//Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_DwIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <ErrorService/FC_Error.h>
#include "Monitoring/MON_AppIf.h"
#include "Monitoring/MON_OduConfig.h"
#include "Configuration/CFG_OduSubApplication.h"
#include "../CFG_HwRefreshOdu.h"
#include "../CFG_Tcm.h"
#include "../CFG_Odu.h"
#include "../CFG_OduAutomatic.h"
#include "../CFG_OduCritical.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <T6100_TelecomIf.h>
#include <T6100_CardIf.h>


CFG_HwRefreshOdu::CFG_HwRefreshOdu(CFG_AppIf& theCfgIf, 
                                   TSPII_DwRegion& theDwPiiRegion,
                                   CT_NumberOfOdus theOdusOnCard,
                                   CFG_OduCfgCriticalRegion* theOduCfgCriticalRegion):

    CFG_HwRefreshAction(theCfgIf),
    myDwPiiRegion(theDwPiiRegion),
    myOdusOnCard(theOdusOnCard),
    myOduCfgCriticalRegion(theOduCfgCriticalRegion),
    myNumTspiiInstancesInPool(0),
    myFirstPass(true),
    myOduMonConfigRegion(NULL)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
	GetBbAction()->AddInputRegion(theCfgIf.GetAutomaticCfgRegion());
	GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    if (myOduCfgCriticalRegion)
    {
        GetBbAction()->AddInputRegion(myOduCfgCriticalRegion);
    }

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        if(aCardContext->GetCardFamily() == OSM_FAM)
        {
            CFG_OduSubApplication & aOduCfgApp = (static_cast<CFG_OduSubApplication&>(theCfgIf));
            myOduMonConfigRegion = static_cast<MON_OduConfigRegion*>(aOduCfgApp.GetIncomingMonApp()->GetConfigRegion());
            GetBbAction()->AddInputRegion(myOduMonConfigRegion);
        }
    }

    for (uint32 anIndex = 0; anIndex < myOdusOnCard; anIndex++)
    {
        myLocalPrbsRxSessionCounter.push_back((uint32) 0);
    }
}

CFG_HwRefreshOdu::~CFG_HwRefreshOdu()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    if (myOduCfgCriticalRegion)
    {
        GetBbAction()->RemoveInputRegion(myOduCfgCriticalRegion);
    }
    if (myOduMonConfigRegion)
    {
        GetBbAction()->RemoveInputRegion(myOduMonConfigRegion);
    }
}

FC_Object* CFG_HwRefreshOdu::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    if (myFirstPass)
    {
        myNumTspiiInstancesInPool = myDwPiiRegion.Size();

        for (uint32 anIndex = 0; anIndex < myNumTspiiInstancesInPool; anIndex++)
        {
            myCurrentPassInstanceUsed.push_back(false);
            myPreviousPassInstanceUsed.push_back(false);
        }
        myFirstPass = false;
    }


    for (uint32 anIndex = 0; anIndex < myNumTspiiInstancesInPool; anIndex++)
    {        
        myPreviousPassInstanceUsed[anIndex] = myCurrentPassInstanceUsed[anIndex];
        myCurrentPassInstanceUsed[anIndex] = false;
    }

    uint16 aTspiiDwInstance = 0;
    CFG_OduCfgRegion* aOduCfgRegion = static_cast<CFG_OduCfgRegion*>(GetCfgIf().GetCfgRegion());
    FC_THROW_ERROR_IF(aOduCfgRegion==NULL, FC_RuntimeError, "Unable to retrieve CFG region");

    for (uint32 anIndex = 0; anIndex < myOdusOnCard; anIndex++)
    {
        if (anIndex >= aOduCfgRegion->Size())
        {
            break;
        }
        CFG_Odu& aCfgObject = (*aOduCfgRegion)[bbindex_t(anIndex)];
        CFG_OduAutomatic& aAutoCfgObject = static_cast<CFG_OduAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[bbindex_t(anIndex)]);

        // In 9.0, we can now have configuration data from two sources 
        // a. the normal data from Agent Facility (contained in the CfgRegion)
        // b. the new critical data from FPCA (contained in CriticalCfgRegion)
        //
        // The critical region is a subset of the data in the CFG region and when 
        // the critical region is present, the Agent Facility will not populate the
        // fields that are common.
        //
        // This part first places the data from the normal CFG region into local 
        // variables.  If the Critical CFG exists, then these variables will be 
        // over written with the correct data; otherwise, the normal CFG values 
        // will be used.

        CT_ODU_Identifier  aOduIdentifier     = aCfgObject.GetOduIdentifier();
        CT_ODU_Object_Type aOduObjectType     = aCfgObject.GetOduObjectType();
        bool aOduTerm                         = aCfgObject.GetIsOduTerm();
        CT_TEL_PayloadSignalId aTxPayloadType = aCfgObject.GetTxPayloadType();
        //bool aProvisionningActive             = aCfgObject.GetProvisionningActive();
        CT_TEL_ClkType aClockType             = aCfgObject.GetClockType();
        CT_TEL_TS_SIZE aTribSize              = aCfgObject.GetTribSize();
        uint8 aTribPort                       = aCfgObject.GetTribPort();
        uint8 aGfpTs                          = aCfgObject.GetGfpTs();
        uint32 aExpectedSignalRate            = aCfgObject.GetExpectedSignalRate();

        // Check for critical region and re-populate local variables if necessary 
        if (myOduCfgCriticalRegion)
        {
            CFG_OduCritical& aCritCfgObject = static_cast<CFG_OduCritical&>((*myOduCfgCriticalRegion)[bbindex_t(anIndex)]); 

            aOduIdentifier       = aCritCfgObject.GetOduIdentifier();
            aOduObjectType       = aCritCfgObject.GetOduObjectType();
            aOduTerm             = aCritCfgObject.GetIsOduTerm();  
            aTxPayloadType       = aCritCfgObject.GetTxPayloadType();
            //aProvisionningActive = aCritCfgObject.GetProvisionningActive();
            aClockType           = aCritCfgObject.GetClockType();
            aTribSize            = aCritCfgObject.GetTribSize();
            aTribPort            = aCritCfgObject.GetTribPort();
            aGfpTs               = aCritCfgObject.GetGfpTs();
            aExpectedSignalRate  = aCritCfgObject.GetExpectedSignalRate();
        }

        // Determine the TSPII Instance number depending on the type of ODU Client
        // If number of Odus is one, then use the instance zero (0).
        aTspiiDwInstance = uint16(CT_DEFAULT_ODU_POSITION);
        if (myOdusOnCard == 1) 
        {
            aTspiiDwInstance = 0;
        }
        else
        {
            if ((aOduObjectType == CT_ODU_POOL_ODU_WITHIN_CLIENT) || 
                (aOduObjectType == CT_ODU_POOL_CLIENT_INSIDE_ODU) || 
                (aOduObjectType == CT_ODU_POOL_MUX))
            {
                aTspiiDwInstance = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(aOduIdentifier.GetIdValue());
            }
        }

        // If the is no Tspii instance (unassigned) or the instance is out of range, 
        // then skip to the next instance (nothing to look up) 
        if ((aTspiiDwInstance == uint16(CT_DEFAULT_ODU_POSITION)) ||
            (aTspiiDwInstance >= myNumTspiiInstancesInPool))
        {
            continue;
        }

        // Mark the current Tspii as used.
        myCurrentPassInstanceUsed[aTspiiDwInstance] = true;

        TSPII_DwIf& aDwPiiObject = myDwPiiRegion[aTspiiDwInstance];

        // Set 1 Way XC Add and Drop flags.
        // bool aDrop = aAutoCfgObject.GetDrop();
        // bool aAdd  = aAutoCfgObject.GetAdd();
        bool aAutomaticSuppressBI = aAutoCfgObject.GetSuppressBackwardInd();


        // Check if external signaling is disabled
        if (!aCfgObject.GetExternalSignalingDisabled()) 
        {
            //AIS, LCK and OCI are mutually exclusive signaling.
            if(aAutoCfgObject.GetForceLCK() || aCfgObject.GetForceLCK())
            {
                aDwPiiObject.ForceODUIndication(CT_ODU_INDICATION_LCK);
            }
            else if(aAutoCfgObject.GetForceOCI() || aCfgObject.GetForceOCI())
            {
                aDwPiiObject.ForceODUIndication(CT_ODU_INDICATION_OCI);
            }
            else if(aAutoCfgObject.GetForceAIS() || aCfgObject.GetForceAIS())
            {
                aDwPiiObject.ForceODUIndication(CT_ODU_INDICATION_AIS);
            }
            else
            {
                aDwPiiObject.ForceODUIndication(CT_ODU_INDICATION_NONE);
            }

            aDwPiiObject.ForceBDI(aAutoCfgObject.GetForceBDI() && !aAutomaticSuppressBI);
        }
        else
        {
            aDwPiiObject.ForceODUIndication(CT_ODU_INDICATION_NONE);
            aDwPiiObject.ForceBDI(false);
        }

        // And now for something completely different (see Monty Python)
        // Not really, just send down the internal indication as we just did 
        // the regular indication.
        // Note: Internal AIS also has it's own call and is all right.
        // TSPII will use the one that is need for a specific card.
        // 
        // Check if internal signaling is disabled
        if (!aCfgObject.GetInternalSignalingDisabled()) 
        {
            if(aAutoCfgObject.GetForceInternalLCK() || aCfgObject.GetForceInternalLCK())
            {
                aDwPiiObject.ForceInternalODUIndication(CT_ODU_INDICATION_LCK);
            }
            else if(aAutoCfgObject.GetForceInternalOCI() || aCfgObject.GetForceInternalOCI())
            {
                aDwPiiObject.ForceInternalODUIndication(CT_ODU_INDICATION_OCI);
            }
            else if(aAutoCfgObject.GetForceInternalAIS() || aCfgObject.GetForceInternalAIS())
            {
                aDwPiiObject.ForceInternalODUIndication(CT_ODU_INDICATION_AIS);
            }
            else
            {
                aDwPiiObject.ForceInternalODUIndication(CT_ODU_INDICATION_NONE);
            }

            aDwPiiObject.ForceInternalAIS(aAutoCfgObject.GetForceInternalAIS());
        }
        else
        {
            aDwPiiObject.ForceInternalODUIndication(CT_ODU_INDICATION_NONE);
            aDwPiiObject.ForceInternalAIS(false);
        }

        // *****************************************************************************
        // NOTE: For Pool Instances, we are now clearing  TSPII when the instance is 
        // no longet used.  Therefore, any additional methods to Tspii for either 
        // maintenance signaling (above) or configuration (below) should be updated 
        // in the section (below) that clears the Tspii instances.
        // *****************************************************************************
        aDwPiiObject.SetBurstyBerSdThreshold(uint(aCfgObject.GetBurstyBerSdIntervals()),aCfgObject.GetBurstyBerSdThreshold() );
        aDwPiiObject.SetBerSfThreshold(aCfgObject.GetBerSfThreshold());
        aDwPiiObject.SetBerSdThreshold(aCfgObject.GetBerSdThreshold());
        aDwPiiObject.SetTxTrace(aCfgObject.GetSentTrace());
        aDwPiiObject.SetIsOduTerm(aOduTerm);
        aDwPiiObject.SetPathDelayEnabled(aCfgObject.GetPathDelayEnabled());      
        aDwPiiObject.SetServer(aCfgObject.GetServerID());
        
        aDwPiiObject.SetClockType(aClockType);
        aDwPiiObject.SetGfpTsNum(aGfpTs);
        aDwPiiObject.SetExpRate(aExpectedSignalRate);
        aDwPiiObject.SetTribPort(aTribPort);

        aDwPiiObject.SetIsProvisioned(true);
        
        if (myOduMonConfigRegion)
        {
            aDwPiiObject.SetTIMMonitoringEnable((*myOduMonConfigRegion)[bbindex_t(anIndex)].GetTIMMonitoringEnable());
            aDwPiiObject.SetTimCriteria((*myOduMonConfigRegion)[bbindex_t(anIndex)].GetTimCriteria());
            aDwPiiObject.SetExpectedTrace((*myOduMonConfigRegion)[bbindex_t(anIndex)].GetExpectedTrace());
            aDwPiiObject.SetLayerFailOnTIM((*myOduMonConfigRegion)[bbindex_t(anIndex)].GetLayerFailOnTIM());
        }

        if (aCfgObject.GetPrbsTxEnable())
            aDwPiiObject.SetDiagSigTxEnable(CT_TEL_DiagSig_ODUPRBS, true);
        else if (aCfgObject.GetNULLSignalEnable())
            aDwPiiObject.SetDiagSigTxEnable(CT_TEL_DiagSig_ODUNULL, true);
        else
            aDwPiiObject.SetDiagSigTxEnable(CT_TEL_DiagSig_ODUNONE, true);

        if ((aCfgObject.GetPrbsRxEnable()) &&
            (aCfgObject.GetPrbsRxSessionCounter() != myLocalPrbsRxSessionCounter[anIndex]))
        {
            myLocalPrbsRxSessionCounter[anIndex] = aCfgObject.GetPrbsRxSessionCounter();
            aDwPiiObject.SetPRBSRXEnable(false);
        }
        aDwPiiObject.SetPRBSRXEnable(aCfgObject.GetPrbsRxEnable());
        aDwPiiObject.SetPRBSRXSessionCounter(aCfgObject.GetPrbsRxSessionCounter());

        if ( aCfgObject.GetTribAutoFallBack() && 
             (aAutoCfgObject.GetTribSize() != CT_TEL_TS_UNKNOWN) && 
             (aAutoCfgObject.GetTxPayloadType() != CT_TEL_PSI_UNAVAILABLE) )
        {
            aDwPiiObject.SetTxPayloadType(aAutoCfgObject.GetTxPayloadType());
            aDwPiiObject.SetODUTsSize(aAutoCfgObject.GetTribSize(), true);
        }
        else
        {
            aDwPiiObject.SetTxPayloadType(aTxPayloadType);
            aDwPiiObject.SetODUTsSize(aTribSize);
        }

        aDwPiiObject.SetXcOtherSideIndex(aCfgObject.GetCrossConnectedOduIdx());


    } // for (uint32 anIndex = 0; anIndex < myOdusOnCard; anIndex++)

    // CLEAR ANY TSPII INSTANCES THAT ARE NO LONGER USED.
    for (uint32 anIndex = 0; anIndex < myNumTspiiInstancesInPool; anIndex++)
    {        
        if (myPreviousPassInstanceUsed[anIndex] && (!myCurrentPassInstanceUsed[anIndex]))
        {
            // If previous pass used the Tspii instance, but this pass did not use the instance,
            // then clear the Tspii instance.
            TSPII_DwIf& aDwPiiObject = myDwPiiRegion[bbindex_t(anIndex)];

            aDwPiiObject.ForceODUIndication(CT_ODU_INDICATION_UNKNOWN);
            aDwPiiObject.ForceBDI(false);

            aDwPiiObject.ForceInternalODUIndication(CT_ODU_INDICATION_UNKNOWN);
            aDwPiiObject.ForceInternalAIS(false);
            aDwPiiObject.SetBurstyBerSdThreshold(0,0);
            aDwPiiObject.SetBerSfThreshold(CT_TEL_INFINITE_BER);
            aDwPiiObject.SetBerSdThreshold(CT_TEL_INFINITE_BER);
            aDwPiiObject.SetTxTrace(CT_G709Trace());
            aDwPiiObject.SetIsOduTerm(false);
            aDwPiiObject.SetPathDelayEnabled(false);

            aDwPiiObject.SetServer(CT_DEFAULT_ODU_SERVER_ID.GetIdValue());

            aDwPiiObject.SetGfpTsNum(0);
            aDwPiiObject.SetExpRate(0);
            aDwPiiObject.SetPRBSRXEnable(false);
            aDwPiiObject.SetNULLSignalEnable(false);
            aDwPiiObject.SetPRBSTXEnable(false);

            aDwPiiObject.SetTribPort(0);

            aDwPiiObject.SetTxPayloadType(CT_TEL_PSI_UNAVAILABLE);
            aDwPiiObject.SetODUTsSize(CT_TEL_TS_UNKNOWN);
            aDwPiiObject.SetClockType(CT_TEL_CLK_UNKNOWN);

            aDwPiiObject.SetIsProvisioned(false);
        }
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;
}

