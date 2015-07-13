// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_FecIf.h>
#include <ErrorService/FC_Error.h>
#include "Monitoring/MON_AppIf.h"
#include "Monitoring/MON_OtuConfig.h"
#include "Configuration/CFG_OtuSubApplication.h"
#include "../CFG_HwRefreshOtu.h"
#include "../CFG_Otu.h"
#include "../CFG_OtuAutomatic.h"
#include "../CFG_TxOchAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <CsPii/CSPII_CardIF.h>

CFG_HwRefreshOtu::CFG_HwRefreshOtu(CFG_AppIf& theCfgIf,
                                   TSPII_FecRegion& theFecPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myFecPiiRegion(theFecPiiRegion),
    myTxOchAutomaticConfigRegion(NULL),
    myOtuMonConfigRegion(NULL)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddInputRegion(theCfgIf.GetAutomaticCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());

    // also register to ochStatus region if TsPii is not supporting rx power
    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        T6100_TelecomIf* aOchContext = aCardContext->GetOchIfPtr();
        if (aOchContext)
        {
            if(aCardContext->GetCardFamily() == SMTM_FAM ||
               aCardContext->GetCardFamily() == TRN_FAM  ||
               aCardContext->GetCardFamily() == PACKET_FAM ||
               aCardContext->GetCardFamily() == OTNM_FAM ||
               aCardContext->GetCardFamily() == FGTMM_FAM ||
               aCardContext->GetCardFamily() == SSM_FAM)
            {
                CT_CardType cardType = (CSPII_CardIF::GetInstance())->GetCardType();
                if (cardType == HGTM || cardType == HGTMS) // Coriant HGTMS
                {
                    myTxOchAutomaticConfigRegion = NULL;
                }
                else
                {
                    CFG_AppIf& aCfgIf = aOchContext->GetCfgLineSideApp(CT_LINE_SIDE_1);
                    CFG_Region* aRegion = aCfgIf.GetAutomaticCfgRegion();
                    myTxOchAutomaticConfigRegion = static_cast<CFG_TxOchAutomaticCfgRegion*>(aRegion);
                }
            }
            else
            {
                CFG_AppIf& aCfgIf = aOchContext->GetCfgLineApp();
                CFG_Region* aRegion = aCfgIf.GetAutomaticCfgRegion();
                myTxOchAutomaticConfigRegion = static_cast<CFG_TxOchAutomaticCfgRegion*>(aRegion);
            }
        }
        
        if(aCardContext->GetCardFamily() == OSM_FAM)
        {
            CFG_OtuSubApplication & aOtuCfgApp = (static_cast<CFG_OtuSubApplication&>(theCfgIf));
            myOtuMonConfigRegion = static_cast<MON_OtuConfigRegion*>(aOtuCfgApp.GetIncomingMonApp()->GetConfigRegion());
            GetBbAction()->AddInputRegion(myOtuMonConfigRegion);
        }
    }

    if (myTxOchAutomaticConfigRegion)
        GetBbAction()->AddInputRegion(myTxOchAutomaticConfigRegion);

}

CFG_HwRefreshOtu::~CFG_HwRefreshOtu()
{
    if (myTxOchAutomaticConfigRegion)
        GetBbAction()->RemoveInputRegion(myTxOchAutomaticConfigRegion);

    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    if (myOtuMonConfigRegion)
    {
        GetBbAction()->RemoveInputRegion(myOtuMonConfigRegion);
    }
}

FC_Object* CFG_HwRefreshOtu::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Otu& aCfgObject   = static_cast<CFG_Otu&>((*GetCfgIf().GetCfgRegion())[0]);
    CFG_OtuAutomatic& aAutoCfgObject = static_cast<CFG_OtuAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    TSPII_FecIf& aFecPiiObject = myFecPiiRegion[0];

    aFecPiiObject.ForceAIS(aCfgObject.GetForceAIS());
    aFecPiiObject.SetCorrectionEnable(aCfgObject.GetEnableFECCorrection());
    aFecPiiObject.SetErrorGeneration(aCfgObject.GetForceErrorInsertion());
    aFecPiiObject.SetSuperFecEnable(aCfgObject.GetEnableSuperFEC());
    aFecPiiObject.SetFECType(aCfgObject.GetFECType());
    aFecPiiObject.SetBurstyBerSdThreshold(uint(aCfgObject.GetBurstyBerSdIntervals()),aCfgObject.GetBurstyBerSdThreshold() );

    // set trace ID according to value found in tx och automatic region
    if (myTxOchAutomaticConfigRegion)
    {
        CFG_TxOchAutomatic& aTxOchAutomatic = static_cast<CFG_TxOchAutomatic&>((*myTxOchAutomaticConfigRegion)[0]);
        CT_G709Trace aTrace(aCfgObject.GetSentTrace().GetSapi(),
                            aCfgObject.GetSentTrace().GetDapi(),
                            aCfgObject.GetSentTrace().GetOperatorSpecific(),
                            (uint16)aTxOchAutomatic.GetTraceId());
        aFecPiiObject.SetTxTrace(aTrace);
    }
    else
        aFecPiiObject.SetTxTrace(aCfgObject.GetSentTrace());

    if (myOtuMonConfigRegion)
    {
        aFecPiiObject.SetTIMMonitoringEnable((*myOtuMonConfigRegion)[0].GetTIMMonitoringEnable());
        aFecPiiObject.SetTimCriteria((*myOtuMonConfigRegion)[0].GetTimCriteria());
        aFecPiiObject.SetExpectedTrace((*myOtuMonConfigRegion)[0].GetExpectedTrace());
        aFecPiiObject.SetLayerFailOnTIM((*myOtuMonConfigRegion)[0].GetLayerFailOnTIM());
    }

    aFecPiiObject.SetBDIAndBEIAllowed(!aAutoCfgObject.GetSuppressBackwardInd());
    // Suppression of software forced BDI is handled in the automatic action
    // and the suppress flag is only used for the SetBDIAndBEIAllowed call above.
    aFecPiiObject.ForceBDI(aAutoCfgObject.GetForceBDI());
    aFecPiiObject.SetSendDefectToMate(aAutoCfgObject.GetSendDefectToMate());

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}

