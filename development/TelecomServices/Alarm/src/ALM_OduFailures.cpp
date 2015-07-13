/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of ODU (Optical Data Unit)
                layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OduDefects.h>

#include "../ALM_AppIf.h"
#include "../ALM_OduFailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include <T6100/T6100_CardIf.h>
#include <T6100/T6100_TelecomIf.h>
#include <Alarm/ALM_SubApplicationOnRpt.h>
#include <Alarm/ALM_SubApplicationOnCard.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Odu.h>
#include <Alarm/ALM_RegionKeyDefinition.h>
#include <AM/AM_DefectCollector.h>

#include "ALM_OduFailures.h"

//==============  =============================  ==============================  ===============================
// bit#:     14     13       12          11          10      9            8     7      6      5      4          3            2      1       0
// defect:  SSF  UP_SA  UP_NSA  GENAIS  MSIM  LOFLOM  AIS  LCK  OCI  TIM  TIMNSA  LOOMFI  BER  BDI   PLM
//==============  =============================  ==============================  ===============================

static const ALM_BitField UP_SA_FilterMask  = 0x5800; //101 1000 0000 0000 
static const ALM_BitField UP_NSA_FilterMask = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField SSF_FilterMask = 0x7000; // 111 0000 0000 0000
static const ALM_BitField GENAIS_FilterMask = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField MSIM_FilterMask   = 0x7C00; // 111 1100 0000 0000
static const ALM_BitField LOFLOM_FilterMask = 0x7E00; // 111 1110 0000 0000
static const ALM_BitField AIS_FilterMask    = 0x7FC0; // 111 1111 1100 0000
static const ALM_BitField LCK_FilterMask    = 0x7FC0; // 111 1111 1100 0000
static const ALM_BitField OCI_FilterMask    = 0x7FC0; // 111 1111 1100 0000
static const ALM_BitField TIM_FilterMask    = 0x7FE0; // 111 1111 1110 0000
static const ALM_BitField TIM_NSA_FilterMask= 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField LOOMFI_FilterMask = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField BER_FilterMask    = 0x7FFF; // 1111 1111 1111 1111
static const ALM_BitField BDI_FilterMask    = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField PLM_FilterMask    = 0x7FFF; // 111 1111 1111 1111
 
static const ALM_BitField ourFailureProtectionMask = 0x7FFF;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures of lower layer if one of the folowing failure
// is declared:   MSIM, LOFLOM, AIS, LCK, OCI, TIM, PLM
static const ALM_BitField ourFilterAllMask = 0x07E1;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x7000;

//-----------------------------------------------------------------
//##ModelId=3C506C3102D7
ALM_OduFailures::ALM_OduFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OduDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OduFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr,
        ALM_LayerFailures::ALM_SP_NB_OF_SOAK_DEFECT
    ),
    //Set the monitor
    myMonitor(theMonitor),

    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_ODU_SOAKING_TIME),

    //-------------------------------------------
    // Signal Protection Not Service Affecting
    // must report NSA flag after 10 second soak
    // and clear   NSA flag after 2  second soak.
    // NOTE: this is the opposite of reporting/clearing
    //       defects, because SP-NSA is REPORTED
    //       when defects are CLEARED!
    //-------------------------------------------
    mySigProtNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME),
    mySigProtODUKPNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_OduFailureBase::UPPER_SA_ODU,  &myUpperSa);
    AddAt (ALM_OduFailureBase::UPPER_NSA_ODU, &myUpperNsa);
    AddAt (ALM_OduFailureBase::AIS_ODU, &myAis);
    AddAt (ALM_OduFailureBase::GENAIS_ODU, &myGenAis);
    AddAt (ALM_OduFailureBase::TIM_ODU, &myTim);
    AddAt (ALM_OduFailureBase::TIM_NSA_ODU, &myTimNsa);
    AddAt (ALM_OduFailureBase::PLM_ODU, &myPlm);
    AddAt (ALM_OduFailureBase::LCK_ODU, &myLck);
    AddAt (ALM_OduFailureBase::OCI_ODU, &myOci);
    AddAt (ALM_OduFailureBase::BER_ODU, &myBer);
    AddAt (ALM_OduFailureBase::BDI_ODU, &myBdi);
    AddAt (ALM_OduFailureBase::MSIM_ODU,&myMsim);
    AddAt (ALM_OduFailureBase::LOFLOM_ODU,&myLofLom);
    AddAt (ALM_OduFailureBase::LOOMFI_ODU,&myLoomfi);
    AddAt (ALM_OduFailureBase::SSF_ODU,&mySSF);

    // Add all SP Soak failures to LayerFailures object
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_NOT_SA,           &mySigProtNSA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_PROTNA_UID,       &mySigProtPROTNA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_ODUKP_NOT_SA,     &mySigProtODUKPNSA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_ODUKP_PROTNA_UID, &mySigProtODUKPPROTNA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_FOP_PM_UID,       &mySigProtFOPPM);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_FOP_NR_UID,       &mySigProtFOPNR);

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

    if ( myApplication.GetKeySuffix()      == ALM_PORT_30_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_30;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_31_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_31;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_32_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_32;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_33_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_33;
    }
    else if ( myApplication.GetKeySuffix() == ALM_PORT_34_SUFFIX )
    {
        myIntfId = CT_PORT_SIDE_34;
    }

    myOduObjectType = CT_ODU_POOL_NOT_ASSIGNED;
    myServerId = CT_ODU_ServerID::SERVER_DEFAULT;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3102E4
ALM_OduFailures::~ALM_OduFailures ()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C3102EB
ALM_BitField ALM_OduFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    //====================================================================
    // Read the UPPER_SA_ defect from the monitor.
    //====================================================================
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT, ALM_OduFailureBase::UPPER_SA_ODU)
    if ( !(aBitFieldDefect & (1 << ALM_OduFailureBase::UPPER_SA_ODU)) )
    {
        ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, ALM_OduFailureBase::UPPER_SA_ODU)
    }

    // Read the UPPER_NSA defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_OduFailureBase::UPPER_NSA_ODU)

    // Read the AIS_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_AIS_DEFECT, ALM_OduFailureBase::AIS_ODU)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_GENAIS_DEFECT, ALM_OduFailureBase::GENAIS_ODU)

    //=====================================================================================
    // TIM_ODU is a special case scenario where it is ServiceAffecting(SA) or NSA
    // based on the provisioned MONTRCODU attribute (AIS, NOAIS). Must process special!
    //=====================================================================================
    myMonitor.GetDefectStatusSpecial(CT_TEL_ODU_TIM_DEFECT, &aTCount, &aStatus, true); // TIM_ODU
    itsDefect[ALM_OduFailureBase::TIM_ODU].SetTCount(aTCount);
    itsDefect[ALM_OduFailureBase::TIM_ODU].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_OduFailureBase::TIM_ODU); }
 
    myMonitor.GetDefectStatusSpecial(CT_TEL_ODU_TIM_DEFECT, &aTCount, &aStatus, false); // TIM_NSA_ODU
    itsDefect[ALM_OduFailureBase::TIM_NSA_ODU].SetTCount(aTCount);
    itsDefect[ALM_OduFailureBase::TIM_NSA_ODU].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_OduFailureBase::TIM_NSA_ODU); }

    // Read the PLM_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_PLM_DEFECT, ALM_OduFailureBase::PLM_ODU)

    // Read the LCK_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_LCK_DEFECT, ALM_OduFailureBase::LCK_ODU)

    // Read the OCI_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_OCI_DEFECT, ALM_OduFailureBase::OCI_ODU)

    // Read the BER_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_SDBER_DEFECT, ALM_OduFailureBase::BER_ODU)

    // Read the DBI_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_BDI_DEFECT, ALM_OduFailureBase::BDI_ODU)

    // Read the MSIM_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_MSIM_DEFECT, ALM_OduFailureBase::MSIM_ODU)

    // Read the MSIM_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_LOFLOM_DEFECT, ALM_OduFailureBase::LOFLOM_ODU)

    // Read the LOOMFI_ODU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_LOOMFI_DEFECT, ALM_OduFailureBase::LOOMFI_ODU)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_ODU_SSF_DEFECT, ALM_OduFailureBase::SSF_ODU)

    return aBitFieldDefect;
}

//==============  =============================  ==============================  ===============================
// bit#:     12     11      10      9     8         7       6       5       4       3      2      1       0
// defect: UP_SA  UP_NSA  GENAIS  MSIM  LOFLOM     AIS     LCK     OCI     TIM    TIMNSA  BER     BDI     PLM
//==============  =============================  ==============================  ===============================
ALM_BitField ALM_OduFailures::Filter(ALM_BitField theFailure) const
{
    ALM_BitField tempFailureFilterResults = (theFailure & ourFailureProtectionMask);
    
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::UPPER_SA_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::UPPER_NSA_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::SSF_ODU) )
    {
    	tempFailureFilterResults = (tempFailureFilterResults & SSF_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::GENAIS_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & GENAIS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::MSIM_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & MSIM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::LOFLOM_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOFLOM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::AIS_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & AIS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::LCK_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LCK_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::OCI_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & OCI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::TIM_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::TIM_NSA_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::LOOMFI_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOOMFI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::BER_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & BER_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::BDI_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & BDI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OduFailureBase::PLM_ODU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & PLM_FilterMask);
    }

    return tempFailureFilterResults;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3102ED
ALM_BitField ALM_OduFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_OduFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//-----------------------------------------------------------------
void ALM_OduFailures::ProcessAfterSoaking()
{
    //-----------------------------------------------------------------
    // For a HDTG module, the ODU2 layer is -ALWAYS- mapped to OTU layer
    // irregardless if the client is provisioned as a OCHP or OTU2.
    // Map HDTG ODU2s to corresponding OCHP/OTU2 facility.
    //-----------------------------------------------------------------
    if (  myCardIf &&
         (myCardIf->GetCardFamily() == HDTG_FAM ||
          myCardIf->GetCardFamily() == ENH_TRN_FAM ||
          myCardIf->GetCardFamily() == ENH_PACKET_FAM ) )
    {
        CT_IntfId aMappedIntfId = (CT_IntfId)itsIndex;
        if ( myCardIf->GetCardFamily() == ENH_PACKET_FAM )
        {
            aMappedIntfId = CT_PORT_SIDE_88;
            if ( itsIndex == 1 ) aMappedIntfId = CT_PORT_SIDE_87;
            if ( itsIndex == 2 ) aMappedIntfId = CT_PORT_SIDE_86;
            if ( itsIndex == 3 ) aMappedIntfId = CT_PORT_SIDE_85;
        }

        // Get the CFG_RS region to determine the mapped signalType (OCHP/OTU2)
        CFG_AppIf*   aConfigAppIf = myCardIf->GetRsIf().GetCfgPortSideAppPtr(aMappedIntfId);
        CFG_Region* aConfigRegion = aConfigAppIf->GetCfgRegion();

        if ( aConfigRegion->IsValid() )
        {
            CFG_Rs& aCfgObject = static_cast<CFG_Rs&>((*aConfigRegion)[0]);
            CT_TEL_SignalType aSignalType = aCfgObject.GetSignalType();

            if (itsFilteredFailureBase.GetSignalType() != aSignalType)
            {
                itsFilteredFailureBase.SetSignalType(aSignalType);
                itsFilteredFailureRegionPtr->IncModificationCounter();

                //----------------------------------------------------------
                // Update the ODU2's HigherLayerPtr when signalType changes!
                //----------------------------------------------------------
                itsHigherLayerPtr = NULL;

                if ( aSignalType != CT_TEL_SIGNAL_UNKNOWN )
                {
                    ALM_AppIf* aOtuAlmAppIf = myCardIf->GetOtuIf().GetAlmPortSideAppPtr(aMappedIntfId);
                    ALM_SubApplicationOnRpt* aOtuAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aOtuAlmAppIf);
                    if ( aOtuAlmRptAppIf )
                        SetHigherLayerPtr( aOtuAlmRptAppIf->GetLayerFailurePtr(0) );
                }
            }
        }
    }

    //---------------------------------------------------------------------
    // Below, the ODU0, ODU1, ODU2 and ODU3 layers are dynamically set.
    // We can rely solely on the ServerId to determine HigherLayerPtr.
    //---------------------------------------------------------------------
    if ( myCardIf && 
        (myCardIf->GetCardFamily() == SSM40_FAM || 
         myCardIf->GetCardFamily() == ENH_TRN_FAM || 
         myCardIf->GetCardFamily() == FGSM_FAM ||
         myCardIf->GetCardFamily() == OMM_FAM ||
         myCardIf->GetCardFamily() == HGTMM_FAM ||
         myCardIf->GetCardFamily() == OSM_FAM ||
         myCardIf->GetCardFamily() == HDTG2_FAM))
    {
        bool resetToDefault = true;

        CFG_AppIf* aConfigAppIf = myCardIf->GetOduIf().GetCfgPortSideAppPtr( myIntfId );
        CFG_Region* aConfigRegion = aConfigAppIf->GetCfgRegion();

        if ( aConfigRegion->IsValid() && itsIndex < aConfigRegion->Size() )
        {
            CFG_Odu& aCfgObject = static_cast<CFG_Odu&>((*aConfigRegion)[ itsIndex ]); // itsIndex(0-15 ODU1, 0-3 ODU2)

            if ( aCfgObject.GetProvisionningActive() )
            {
                resetToDefault = false;

                if ( myServerId != aCfgObject.GetServerID() )
                {
                    itsHigherLayerPtr = NULL;
                    myServerId = aCfgObject.GetServerID();

                    if ( myServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu ) // MUXED ODUk.
                    {
                        CT_IntfId aHigherLayerIntId = CT_PORT_SIDE_31; // Default ODU1 (can NOT be ODU0!).
                        if ( myServerId.GetOduKvalueEnum() == CT_ODU_Layer2 )
                        {
                            aHigherLayerIntId = CT_PORT_SIDE_32;
                        }
                        else if ( myServerId.GetOduKvalueEnum() == CT_ODU_Layer3 )
                        {
                            aHigherLayerIntId = CT_PORT_SIDE_33;
                        }
                        else if ( myServerId.GetOduKvalueEnum() == CT_ODU_Layer4 )
                        {
                            aHigherLayerIntId = CT_PORT_SIDE_34;
                        }
                        ALM_AppIf* aOduAlmAppIf = myCardIf->GetOduIf().GetAlmPortSideAppPtr(aHigherLayerIntId);
                        ALM_SubApplicationOnRpt* aOduAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aOduAlmAppIf);
                        if ( aOduAlmRptAppIf )
                            SetHigherLayerPtr( aOduAlmRptAppIf->GetLayerFailurePtr(myServerId.GetPoolInstance()) );
                    }
                    else if ( myServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu )
                    {
                        int aFac = myServerId.GetPoolInstance(); // Facility PortId (88, 87, 86,..).
                        ALM_AppIf* aOtuAlmAppIf = myCardIf->GetOtuIf().GetAlmPortSideAppPtr((CT_IntfId)aFac);
                        ALM_SubApplicationOnRpt* aOtuAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aOtuAlmAppIf);
                        if ( aOtuAlmRptAppIf )
                            SetHigherLayerPtr( aOtuAlmRptAppIf->GetLayerFailurePtr(0) );
                    }
                    else if ( myServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm )
                    {
                        CT_ODU_Layer higherLayer = myServerId.GetOduKvalueEnum(); 
                        CT_IntfId aHigherLayerIntId = CT_PORT_SIDE_40; // it's always CT_PORT_SIDE_40 for any TCM type
                        ALM_AppIf* aTcmAlmAppIf = myCardIf->GetTcmIf().GetAlmPortSideAppPtr(aHigherLayerIntId);
                        ALM_SubApplicationOnRpt* aTcmAlmRptAppIf = dynamic_cast<ALM_SubApplicationOnRpt*>(aTcmAlmAppIf);
                        if ( aTcmAlmRptAppIf )
                            SetHigherLayerPtr( aTcmAlmRptAppIf->GetLayerFailurePtr(myServerId.GetPoolInstance()) );
                    }
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////
        if ( resetToDefault )
        {
            itsHigherLayerPtr = NULL;
            myServerId = CT_ODU_ServerID::SERVER_DEFAULT;
        }

        // ------- add this for trace the MRt71mr00148899---------
        int counter = 0;
        if ( itsHigherLayerPtr != NULL )
        {
            ALM_LayerFailures* temp = itsHigherLayerPtr;
            for( ;temp != NULL; counter++ )
            {
                temp = temp->GetHigherLayerPtr();
                if ( counter == 20 )
                    FC_THROW_ERROR( FC_NotSupportedError, "!!!!!!!! ALM_OduFailures, HigherLayer == 20!!!!!" );
            }
        }
    }
}


