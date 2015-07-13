/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Xinlun Fang
 DESCRIPTION:   This class manages the failures of ODU-TCM
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_TcmDefects.h>
#include <Monitoring/MON_AppIf.h>
#include <Configuration/CFG_AppIf.h>

#include "../ALM_AppIf.h"
#include "../ALM_TcmFailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include <T6100/T6100_CardIf.h>
#include <T6100/T6100_TelecomIf.h>
#include <Alarm/ALM_SubApplicationOnRpt.h>
#include <Alarm/ALM_SubApplicationOnCard.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Tcm.h>
#include <Configuration/CFG_Odu.h>
#include <Monitoring/MON_TcmStatus.h>
#include <AM/AM_DefectCollector.h>

#include <Alarm/ALM_RegionKeyDefinition.h>

#include "ALM_TcmFailures.h"

//======================  =============================  ================================
// bit#:     10      9            8       7             6       5       4       3       2      1       0
// defect: UP_SA UP_NSA  LTC   LTCNSA   AIS     LCK     OCI     TIM   TIMNSA   BER     BDI 
//======================  =============================  ================================

static const ALM_BitField UP_SA_FilterMask  = 0x0400; // 0100 0000 0000
static const ALM_BitField UP_NSA_FilterMask = 0x07FF; // 0111 1111 1111
static const ALM_BitField LTC_FilterMask    = 0x0700; // 0111 0000 0000
static const ALM_BitField LTC_NSA_FilterMask    = 0x0780; // 0111 1000 0000
static const ALM_BitField AIS_FilterMask    = 0x07C0; // 0111 1100 0000
static const ALM_BitField LCK_FilterMask    = 0x07E0; // 0111 1110 0000
static const ALM_BitField OCI_FilterMask    = 0x07F0; // 0111 1111 0000
static const ALM_BitField TIM_FilterMask    = 0x07F8; // 0111 1111 1000
static const ALM_BitField TIM_NSA_FilterMask= 0x07FF; // 0111 1111 1111
static const ALM_BitField BER_FilterMask    = 0x07FF; // 0111 1111 1111
static const ALM_BitField BDI_FilterMask    = 0x07FF; // 0111 1111 1111

static const ALM_BitField ourFailureProtectionMask = 0x07FF;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared: (rely on SGEO in AMA_ProcessAlarmAction)
static const ALM_BitField ourFilterAllMask = 0x0000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x0600;

//-----------------------------------------------------------------
//##ModelId=3C506C3102D7
ALM_TcmFailures::ALM_TcmFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_TcmDefects& theMonitor,
                                  //CT_TCM_LEVEL theTcmLevel,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_TcmFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr,
        ALM_LayerFailures::ALM_SP_NB_OF_SOAK_DEFECT
    ),
    //Set the monitor
    myMonitor(theMonitor),

    //myTcmLevel(theTcmLevel),

    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_TCM_SOAKING_TIME),

    //-------------------------------------------
    // Signal Protection Not Service Affecting
    // must report NSA flag after 10 second soak
    // and clear   NSA flag after 2  second soak.
    // NOTE: this is the opposite of reporting/clearing
    //       defects, because SP-NSA is REPORTED
    //       when defects are CLEARED!
    //-------------------------------------------
    mySigProtNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_TcmFailureBase::UPPER_SA_Tcm,  &myUpperSa);
    AddAt (ALM_TcmFailureBase::UPPER_NSA_Tcm, &myUpperNsa);
    AddAt (ALM_TcmFailureBase::AIS_Tcm, &myAis);
    AddAt (ALM_TcmFailureBase::TIM_Tcm, &myTim);
    AddAt (ALM_TcmFailureBase::TIM_NSA_Tcm, &myTimNsa);
    AddAt (ALM_TcmFailureBase::LTC_Tcm, &myLtc);
    AddAt (ALM_TcmFailureBase::LCK_Tcm, &myLck);
    AddAt (ALM_TcmFailureBase::OCI_Tcm, &myOci);
    AddAt (ALM_TcmFailureBase::BER_Tcm, &myBer);
    AddAt (ALM_TcmFailureBase::BDI_Tcm, &myBdi);
    AddAt (ALM_TcmFailureBase::LTC_NSA_Tcm, &myLtcNsa);

    // Add all SP Soak failures to LayerFailures object
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_NOT_SA, &mySigProtNSA);

    myCardIf = NULL;
    if (theApplication.GetContext().GetParent())
    {
        T6100_CardIf* theCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
        if (theCardIf)
        {
            myCardIf = theCardIf;
        }
    }

    //--------------------------------------------------------
    // SSM40 ODU1 and ODU2 mapping information.
    //--------------------------------------------------------
    myIntfId = CT_INTF_ID_UNKNOWN;
    if ( myApplication.GetKeySuffix() == ALM_PORT_40_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_40;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_41_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_41;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_50_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_50;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_51_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_51;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_60_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_60;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_61_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_61;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_70_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_70;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_71_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_71;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_80_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_80;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_81_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_81;
    }

    myServerId = CT_ODU_ServerID::SERVER_DEFAULT;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3102E4
ALM_TcmFailures::~ALM_TcmFailures ()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C3102EB
ALM_BitField ALM_TcmFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_ defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT, ALM_TcmFailureBase::UPPER_SA_Tcm)
    if ( !(aBitFieldDefect & (1 << ALM_TcmFailureBase::UPPER_SA_Tcm)) )
    {
        ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, ALM_TcmFailureBase::UPPER_SA_Tcm)
    }

    // Read the UPPER_NSA defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_TcmFailureBase::UPPER_NSA_Tcm)

    // Read the AIS_TCM defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_AIS_DEFECT, ALM_TcmFailureBase::AIS_Tcm)

    //=====================================================================================
    // TIM_TCM is a special case scenario where it is ServiceAffecting(SA) or NSA
    // based on the provisioned MONTRCTCM attribute (AIS, NOAIS). Must process special!
    //=====================================================================================
    myMonitor.GetDefectStatusSpecial(CT_TEL_TCM_TIM_DEFECT, &aTCount, &aStatus, true); // TIM_TCM
    itsDefect[ALM_TcmFailureBase::TIM_Tcm].SetTCount(aTCount);
    itsDefect[ALM_TcmFailureBase::TIM_Tcm].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_TcmFailureBase::TIM_Tcm); }
 
    myMonitor.GetDefectStatusSpecial(CT_TEL_TCM_TIM_DEFECT, &aTCount, &aStatus, false); // TIM_NSA_TCM
    itsDefect[ALM_TcmFailureBase::TIM_NSA_Tcm].SetTCount(aTCount);
    itsDefect[ALM_TcmFailureBase::TIM_NSA_Tcm].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_TcmFailureBase::TIM_NSA_Tcm); }
    
    myMonitor.GetDefectStatusSpecial(CT_TEL_TCM_LTC_DEFECT, &aTCount, &aStatus, true); // TIM_TCM
    itsDefect[ALM_TcmFailureBase::LTC_Tcm].SetTCount(aTCount);
    itsDefect[ALM_TcmFailureBase::LTC_Tcm].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_TcmFailureBase::LTC_Tcm); }
 
    myMonitor.GetDefectStatusSpecial(CT_TEL_TCM_LTC_DEFECT, &aTCount, &aStatus, false); // TIM_NSA_TCM
    itsDefect[ALM_TcmFailureBase::LTC_NSA_Tcm].SetTCount(aTCount);
    itsDefect[ALM_TcmFailureBase::LTC_NSA_Tcm].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_TcmFailureBase::LTC_NSA_Tcm); }

    // Read the LCK_TCM defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_LCK_DEFECT, ALM_TcmFailureBase::LCK_Tcm)

    // Read the OCI_TCM defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_OCI_DEFECT, ALM_TcmFailureBase::OCI_Tcm)

    // Read the BER_TCM defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_SDBER_DEFECT, ALM_TcmFailureBase::BER_Tcm)

    // Read the DBI_TCM defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_TCM_BDI_DEFECT, ALM_TcmFailureBase::BDI_Tcm)

    return aBitFieldDefect;
}

//======================  =============================  ================================
// bit#:     9     8        7       6       5       4       3       2      1       0
// defect: UP_SA UP_NSA    LTC     AIS     LCK     OCI     TIM   TIMNSA   BER     BDI
//======================  =============================  ================================
ALM_BitField ALM_TcmFailures::Filter(ALM_BitField theFailure) const
{
    ALM_BitField tempFailureFilterResults = (theFailure & ourFailureProtectionMask);
 
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::UPPER_SA_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::UPPER_NSA_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::LTC_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LTC_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::LTC_NSA_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LTC_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::AIS_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & AIS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::LCK_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LCK_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::OCI_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & OCI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::TIM_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::TIM_NSA_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::BER_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & BER_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_TcmFailureBase::BDI_Tcm) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & BDI_FilterMask);
    }
 
    return tempFailureFilterResults;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3102ED
ALM_BitField ALM_TcmFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_TcmFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//-----------------------------------------------------------------
void ALM_TcmFailures::ProcessAfterSoaking()
{
    if ( (myCardIf) && (myCardIf->GetCardFamily() == SSM40_FAM || 
                        myCardIf->GetCardFamily() == ENH_TRN_FAM ||
                        myCardIf->GetCardFamily() == HGTMM_FAM ||
                        myCardIf->GetCardFamily() == OSM_FAM))
    {
        bool resetToDefault = false;
        CFG_TcmCfgRegion* aConfigRegion = static_cast<CFG_TcmCfgRegion*>(myCardIf->GetTcmIf().GetCfgPortSideApp(myIntfId).GetCfgRegion());

        if ((uint)itsIndex >= aConfigRegion->Size())
            return;
        //FC_THROW_ERROR_IF ((uint)itsIndex >= aConfigRegion->Size(), FC_RuntimeError, "ALM: ALM region is not consistent with MON/CFG !!");

        CFG_Tcm& aCfgObject = static_cast<CFG_Tcm&>((*aConfigRegion)[ itsIndex ]); 

        if ( aConfigRegion->IsValid() )
        {

            if ( aCfgObject.GetProvisionningActive() )
            { 
                if ( myServerId != aCfgObject.GetServerID() )
                {
                    myServerId = aCfgObject.GetServerID();

                    itsHigherLayerPtr = NULL;
                    CT_IntfId aIntId = CT_INTF_ID_UNKNOWN;
                    CT_ODU_ServerID aServerId = aCfgObject.GetServerID();
    
                    if ( aServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu )
                    {
                        CT_ODU_Layer higherLayer = aServerId.GetOduKvalueEnum();
                        aIntId = (CT_IntfId)((higherLayer == CT_ODU_Layer0)  ? CT_PORT_SIDE_30  //higher layer should never be CT_ODU_Layer0!
                                          : ((higherLayer == CT_ODU_Layer1 ) ? CT_PORT_SIDE_31
                                          : ((higherLayer == CT_ODU_Layer2 ) ? CT_PORT_SIDE_32
                                          : ((higherLayer == CT_ODU_Layer3 ) ? CT_PORT_SIDE_33
                                          : ((higherLayer == CT_ODU_Layer4 ) ? CT_PORT_SIDE_34
                                          : CT_INTF_ID_UNKNOWN)))));
                        if (aIntId != CT_INTF_ID_UNKNOWN)
                        {
                            ALM_AppIf* aOduAlmAppIf = myCardIf->GetOduIf().GetAlmPortSideAppPtr(aIntId);
                            ALM_SubApplicationOnRpt* aOduAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aOduAlmAppIf);
                            if ( aOduAlmRptAppIf )
                                SetHigherLayerPtr( aOduAlmRptAppIf->GetLayerFailurePtr(aServerId.GetPoolInstance()) );
                        }
                    }
                    else if ( aServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu )
                    {
                        int aFac = aServerId.GetPoolInstance();
                        ALM_AppIf* aOtuAlmAppIf = myCardIf->GetOtuIf().GetAlmPortSideAppPtr((CT_IntfId)aFac);
                        ALM_SubApplicationOnRpt* aOtuAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aOtuAlmAppIf);
                        if ( aOtuAlmRptAppIf )
                            SetHigherLayerPtr( aOtuAlmRptAppIf->GetLayerFailurePtr(0) );
                    }
                    else if ( aServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm )
                    {
                        CT_ODU_Layer higherLayer = aServerId.GetOduKvalueEnum();
                        //TCM restructure
                        aIntId = (CT_IntfId)((higherLayer == CT_ODU_Layer0 || 
                                                        higherLayer == CT_ODU_Layer1 || 
                                                        higherLayer == CT_ODU_Layer2 || 
                                                        higherLayer == CT_ODU_Layer3 || 
                                                        higherLayer == CT_ODU_Layer4)  ? CT_PORT_SIDE_40  //higher layer should never be CT_ODU_Layer0!
                                                                                                           : CT_INTF_ID_UNKNOWN);
                        if (aIntId != CT_INTF_ID_UNKNOWN)
                        {
                            aIntId = (CT_IntfId)(aIntId);// + aServerId.GetOduDirection());
        
                            ALM_AppIf* aTcmAlmAppIf = myCardIf->GetTcmIf().GetAlmPortSideAppPtr(aIntId);
                            ALM_SubApplicationOnRpt* aTcmAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aTcmAlmAppIf);
                            if ( aTcmAlmRptAppIf )
                                SetHigherLayerPtr( aTcmAlmRptAppIf->GetLayerFailurePtr(aServerId.GetPoolInstance()) );
                        }
                    }
                    else
                    {
                        resetToDefault = true;
                    }
                }
            }
            else
            {
                resetToDefault = true;
            }
        }
        else
        {
            resetToDefault = true;
        }

        ///////////////////////////////////////////////////////////////////////////////////////
        if ( resetToDefault )
        {
            itsHigherLayerPtr = NULL;
            myServerId = CT_ODU_ServerID::SERVER_DEFAULT;
        }

        // set the TCMID, get it from MON
        (static_cast<ALM_TcmFailureBase*>(&itsFilteredFailureBase))->SetValue(aCfgObject.GetTcmIdentifier().GetIdValue());


        // ------- add this for trace the MRt71mr00148899---------
        int counter = 0;
        if ( itsHigherLayerPtr != NULL )
        {
            ALM_LayerFailures* temp = itsHigherLayerPtr;
            for( ;temp != NULL; counter++ )
            {
                temp = temp->GetHigherLayerPtr();
                if ( counter == 20 )
                    FC_THROW_ERROR( FC_NotSupportedError, "!!!!!!!! ALM_TcmFailures, HigherLayer == 20!!!!!" );
            }
        }
    }
}

