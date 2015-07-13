/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan/Sharkey
 DESCRIPTION:   This class is used to determine the filtered failures of the
                GFP (Generic Framing Procedure) layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_GfpDefects.h>
#include <T6100_CardIf.h>

#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_OtuDefects.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_OptProtConfig.h>
#include <AM/AM_DefectCollector.h>
#include <Alarm/ALM_RegionKeyDefinition.h>
#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_AppIf.h"
#include "../ALM_GfpFailureBase.h"

#include "ALM_GfpFailures.h"

//============================  =====================================  ===========================  ======================
// bit#:    15        14         13               12       11      10           9                    8                   7               6       5       4      3       2         1     0         
// defect: UP_SA  UP_NSA UP_INT_SA  LOFD   PLM   CSF-LOS  CSF-LOSYNC  CSF-FEFI    CSF-FDI  CSF_RDI  LOA  SQM  CHEC  PLI  RMTLF  ANF 
//============================  =====================================  ===========================  ======================
//
// NOTES: CSF-FEFI maps to CSF-RDI-GFP condition type in Alarm Management for the SMTMU.
//        RMTLF and ANF are actually TDTN conditions and should never be inhibited here.
//
//===========================================================================================

static const ALM_BitField UP_SA_FilterMask        = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField UP_NSA_FilterMask       = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField UP_INT_SA_FilterMask = 0xE13F;//1110 0001 0011 1111
static const ALM_BitField LOFD_FilterMask         = 0xF03F; // 1111 0000 0011 1111
static const ALM_BitField PLM_FilterMask          = 0xF83F; // 1111 1000 0011 1111
static const ALM_BitField LOS_FilterMask          = 0xFC3F; // 1111 1100 0011 1111
static const ALM_BitField LOSSYNC_FilterMask      = 0xFE3F; // 1111 1110 0011 1111
static const ALM_BitField FEFI_FilterMask         = 0xFF3F; // 1111 1111 0011 1111
static const ALM_BitField FDI_FilterMask          = 0xFFBF; // 1111 1111 1011 1111
static const ALM_BitField RDI_FilterMask          = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField LOA_FilterMask          = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField SQM_FilterMask          = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField CHEC_FilterMask         = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField PLI_FilterMask          = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField RMTLF_FilterMask        = 0xFFFF; // 1111 1111 1111 1111
static const ALM_BitField AUTONEGFAIL_FilterMask  = 0xFFFF; // 1111 1111 1111 1111

// One bit set for each possible GFP defect.
static const ALM_BitField ourFailureProtectionMask = 0xFFFF;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of the lower layer if one of the following
// failures or defects are declared: Not Applicable (lowest layer)
// See SRS 7100000715 Table 6-11 Facility Defect Correlation Hierarchy.
static const ALM_BitField ourFilterAllMask = 0x0000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
// See SRS 7100000715 Table 6-11 Facility Defect Correlation Hierarchy.
static const ALM_BitField ourNoFilterMask = 0xE000;

//-----------------------------------------------------------------
// Class used to store the Generic Framing Procedure (GFP) failure statuses.
//
ALM_GfpFailures::ALM_GfpFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_GfpDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls the base class constructor
    ALM_LayerFailures 
    ( 
        ALM_GfpFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    // Set the monitor
    myMonitor(theMonitor),
    
    // Upper Non-Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_GFP_SOAKING_TIME),

    myPortOffset(0),
    theDirn(CT_DIR_WAVE_PORT),
    myCardIf(NULL)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_GfpFailureBase::UPPER_SA_GFP,   &myUpperSa);
    AddAt (ALM_GfpFailureBase::UPPER_NSA_GFP,  &myUpperNsa);
    AddAt(ALM_GfpFailureBase::UPPER_INT_SA_GFP, &myUpperIntSA);
    AddAt (ALM_GfpFailureBase::LOFD_GFP,       &myLofd);
    AddAt (ALM_GfpFailureBase::PLM_GFP,        &myPlm);
    AddAt (ALM_GfpFailureBase::CSF_LOS_GFP,    &myCsfLos);
    AddAt (ALM_GfpFailureBase::CSF_LOSYNC_GFP, &myCsfLoSync);
    AddAt (ALM_GfpFailureBase::CSF_FEFI_GFP,   &myCsfFefi);
    AddAt (ALM_GfpFailureBase::CSF_FDI_GFP,    &myCsfFdi);
    AddAt (ALM_GfpFailureBase::CSF_RDI_GFP,    &myCsfRdi);
    AddAt (ALM_GfpFailureBase::LOA_GFP,        &myLoa);
    AddAt (ALM_GfpFailureBase::SQM_GFP,        &mySqm);
    AddAt (ALM_GfpFailureBase::CHEC_GFP,       &myChec);
    AddAt (ALM_GfpFailureBase::PLI_GFP,        &myPli);
    AddAt (ALM_GfpFailureBase::RMTLF_GFP,      &myRmtlf);
    AddAt (ALM_GfpFailureBase::AUTONEGFAIL_GFP,&myAutoNeg);

    if ( theApplication.GetContext().GetParent() )
    {
        T6100_CardIf* theCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
        if ( theCardIf )
        {
            myCardIf = theCardIf;
        }

        const string sKey = myApplication.GetKeySuffix();
        if ( myCardIf && myCardIf->GetCardFamily() == HDTG_FAM )
        {
            if      (sKey == ALM_PORT_0_SUFFIX)   {  myPortOffset = 0;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_1_SUFFIX)   {  myPortOffset = 1;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_2_SUFFIX)   {  myPortOffset = 2;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_3_SUFFIX)   {  myPortOffset = 3;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_4_SUFFIX)   {  myPortOffset = 4;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_5_SUFFIX)   {  myPortOffset = 5;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_6_SUFFIX)   {  myPortOffset = 6;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_7_SUFFIX)   {  myPortOffset = 7;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_8_SUFFIX)   {  myPortOffset = 8;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_9_SUFFIX)   {  myPortOffset = 9;  theDirn = CT_DIR_WAVE_PORT; }
        }
        else if ( myCardIf && myCardIf->GetCardFamily() == ENH_PACKET_FAM )
        {
            if      (sKey == ALM_PORT_85_SUFFIX)   {  myPortOffset = 85;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_86_SUFFIX)   {  myPortOffset = 86;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_87_SUFFIX)   {  myPortOffset = 87;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_88_SUFFIX)   {  myPortOffset = 88;  theDirn = CT_DIR_WAVE_PORT; }
        }
        else if (myCardIf && myCardIf->GetCardFamily() == FGTMM_FAM)
        {
            if      (sKey == ALM_PORT_0_SUFFIX)   {  myPortOffset = 0;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_1_SUFFIX)   {  myPortOffset = 1;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_2_SUFFIX)   {  myPortOffset = 2;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_3_SUFFIX)   {  myPortOffset = 3;  theDirn = CT_DIR_WAVE_PORT; }
        } 
        else if ( myCardIf && myCardIf->GetCardFamily() == SMTM_FAM )
        {
            if      (sKey == ALM_PORT_0_SUFFIX)   {  myPortOffset = 0;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_1_SUFFIX)   {  myPortOffset = 1;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_2_SUFFIX)   {  myPortOffset = 2;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_3_SUFFIX)   {  myPortOffset = 3;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_4_SUFFIX)   {  myPortOffset = 4;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_5_SUFFIX)   {  myPortOffset = 5;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_6_SUFFIX)   {  myPortOffset = 6;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_7_SUFFIX)   {  myPortOffset = 7;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_8_SUFFIX)   {  myPortOffset = 8;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_9_SUFFIX)   {  myPortOffset = 9;  theDirn = CT_DIR_WAVE_PORT; }
        }
    }
}

//-----------------------------------------------------------------

ALM_GfpFailures::~ALM_GfpFailures ()
{
}

//-----------------------------------------------------------------
// Method reads each GFP error status located in the MON region and
// returns the results in a bit map.
//
ALM_BitField ALM_GfpFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_GFP defect from the monitor
    // ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_UPPER_LAYER_FAIL_TA_DEFECT,   ALM_GfpFailureBase::UPPER_SA_GFP)
    
    // Read the UPPER_NSA_GFP defect from the monitor
    // ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_UPPER_LAYER_FAIL_NTA_DEFECT,   ALM_GfpFailureBase::UPPER_NSA_GFP)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT,  ALM_GfpFailureBase::UPPER_INT_SA_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_LOFD_DEFECT,       ALM_GfpFailureBase::LOFD_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_PLM_DEFECT,        ALM_GfpFailureBase::PLM_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_CSF_LOS_DEFECT,    ALM_GfpFailureBase::CSF_LOS_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_CSF_LOSYNC_DEFECT, ALM_GfpFailureBase::CSF_LOSYNC_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_CSF_FEFI_DEFECT,   ALM_GfpFailureBase::CSF_FEFI_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_CSF_FDI_DEFECT,    ALM_GfpFailureBase::CSF_FDI_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_CSF_RDI_DEFECT,    ALM_GfpFailureBase::CSF_RDI_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_LOS_ALIGN,         ALM_GfpFailureBase::LOA_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_SEQMISMATCH,       ALM_GfpFailureBase::SQM_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_CORE_HEC_DEFECT,   ALM_GfpFailureBase::CHEC_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_PLI_DEFECT,        ALM_GfpFailureBase::PLI_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_LINKFAILRX_DEFECT, ALM_GfpFailureBase::RMTLF_GFP)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_GFP_ANF_DEFECT,        ALM_GfpFailureBase::AUTONEGFAIL_GFP)

    return aBitFieldDefect;
}

//============================  =====================================  ===========================  ======================
// bit#:    14     13      12    11      10         9           8          7        6      5    4    3     2     1     0
// defect: UP_SA  UP_NSA  LOFD   PLM   CSF-LOS  CSF-LOSYNC  CSF-FEFI    CSF-FDI  CSF_RDI  LOA  SQM  CHEC  PLI  RMTLF  ANF 
//============================  =====================================  ===========================  ======================
ALM_BitField ALM_GfpFailures::Filter(ALM_BitField theFailure) const
{
    ALM_BitField tempFailureFilterResults = (theFailure & ourFailureProtectionMask);

    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::UPPER_SA_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::UPPER_NSA_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::UPPER_INT_SA_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_INT_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::LOFD_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOFD_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::PLM_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & PLM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::CSF_LOS_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::CSF_LOSYNC_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOSSYNC_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::CSF_FEFI_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & FEFI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::CSF_FDI_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & FDI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::CSF_RDI_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & RDI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::LOA_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::SQM_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & SQM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::CHEC_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & CHEC_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::PLI_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & PLI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::RMTLF_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & RMTLF_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_GfpFailureBase::AUTONEGFAIL_GFP) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & AUTONEGFAIL_FilterMask);
    }

    return tempFailureFilterResults;
}

//-----------------------------------------------------------------

ALM_BitField ALM_GfpFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer.
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_GfpFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//---------------------------------------------------------------------------------
void ALM_GfpFailures::ProcessAfterSoaking()
{
    if ( myCardIf && 
         ((myCardIf->GetCardFamily() == HDTG_FAM) || 
          (myCardIf->GetCardFamily() == ENH_PACKET_FAM) || 
          (myCardIf->GetCardFamily() == FGTMM_FAM)))
    {
        bool inhibitCSFDefects = false;

        CT_IntfId aActiveClientIntfId = CT_INTF_ID_UNKNOWN;
        CT_IntfId aOduIndex = CT_INTF_ID_UNKNOWN;
        CT_IntfId aOduLineIntfId = CT_INTF_ID_UNKNOWN;

        MON_AppIf* aMonActiveOptAppPtr = NULL;
        MON_AppIf* aMonActiveOtuAppPtr = NULL;
        MON_AppIf* aMonActiveOduAppPtr = NULL;
        
        if ( myCardIf->GetCardFamily() == HDTG_FAM )
        {
            // OPT-MON-PROT will determine if DPRING exists and ACTIVE source
            MON_AppIf&  aMonOptApp = myCardIf->GetOptIf().GetMonPortSideApp((CT_IntfId)myPortOffset);
            MON_Region* aMonReg = aMonOptApp.GetProtConfigRegion();
            MON_OptProtConfig* aMonProtObj = dynamic_cast<MON_OptProtConfig*>(&((*aMonReg)[0]));

            if ( aMonProtObj && aMonProtObj->GetProtectionEnable() )
            {
                aActiveClientIntfId = aMonProtObj->GetOppositeSideIntfId();
            }
            else // use matching port ( ..1,2.. ..3,4.. etc).
            {
                switch ( myPortOffset )
                {
                    case 0: aActiveClientIntfId = CT_PORT_SIDE_1; break;
                    case 1: aActiveClientIntfId = CT_PORT_SIDE_0; break;
                    case 2: aActiveClientIntfId = CT_PORT_SIDE_3; break;
                    case 3: aActiveClientIntfId = CT_PORT_SIDE_2; break;
                    case 4: aActiveClientIntfId = CT_PORT_SIDE_5; break;
                    case 5: aActiveClientIntfId = CT_PORT_SIDE_4; break;
                    case 6: aActiveClientIntfId = CT_PORT_SIDE_7; break;
                    case 7: aActiveClientIntfId = CT_PORT_SIDE_6; break;
                    case 8: aActiveClientIntfId = CT_PORT_SIDE_9; break;
                    case 9: aActiveClientIntfId = CT_PORT_SIDE_8; break;
                }
            }
            aOduLineIntfId = CT_PORT_SIDE_32;
            aOduIndex = aActiveClientIntfId;

            aMonActiveOptAppPtr = myCardIf->GetOptIf().GetMonPortSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOtuAppPtr = myCardIf->GetOtuIf().GetMonPortSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOduAppPtr = myCardIf->GetOduIf().GetMonPortSideAppPtr((CT_IntfId) aOduLineIntfId );

        }
        else if (myCardIf->GetCardFamily() == FGTMM_FAM) 
        {
            aActiveClientIntfId = CT_LINE_SIDE_1;

            switch ( myPortOffset ) 
            {
                case 0: aOduLineIntfId = CT_LINE_SIDE_8; break;
                case 1: aOduLineIntfId = CT_LINE_SIDE_9; break;
                case 2: aOduLineIntfId = CT_LINE_SIDE_10; break;
                case 3: aOduLineIntfId = CT_LINE_SIDE_11; break;
            }
            
            aOduIndex = (CT_IntfId)0;
            aMonActiveOptAppPtr = myCardIf->GetOptIf().GetMonLineSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOtuAppPtr = myCardIf->GetOtuIf().GetMonLineSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOduAppPtr = myCardIf->GetOduIf().GetMonLineSideAppPtr((CT_IntfId) aOduLineIntfId );
        }
        else if (myCardIf->GetCardFamily() == HDTG2_FAM)
        {
            // OPT-MON-PROT will determine if DPRING exists and ACTIVE source
            MON_AppIf&  aMonOptApp = myCardIf->GetOptIf().GetMonPortSideApp((CT_IntfId)myPortOffset);
            MON_Region* aMonReg = aMonOptApp.GetProtConfigRegion();
            MON_OptProtConfig* aMonProtObj = dynamic_cast<MON_OptProtConfig*>(&((*aMonReg)[0]));

            if ( aMonProtObj && aMonProtObj->GetProtectionEnable() )
            {
                aActiveClientIntfId = aMonProtObj->GetOppositeSideIntfId();
            }
            else // use matching port ( ..1,2.. ..3,4.. etc).
            {
                switch ( myPortOffset )
                {
                    case 0: aActiveClientIntfId = CT_PORT_SIDE_1; break;
                    case 1: aActiveClientIntfId = CT_PORT_SIDE_0; break;
                    case 2: aActiveClientIntfId = CT_PORT_SIDE_3; break;
                    case 3: aActiveClientIntfId = CT_PORT_SIDE_2; break;
                    case 4: aActiveClientIntfId = CT_PORT_SIDE_5; break;
                    case 5: aActiveClientIntfId = CT_PORT_SIDE_4; break;
                    case 6: aActiveClientIntfId = CT_PORT_SIDE_7; break;
                    case 7: aActiveClientIntfId = CT_PORT_SIDE_6; break;
                    case 8: aActiveClientIntfId = CT_PORT_SIDE_9; break;
                    case 9: aActiveClientIntfId = CT_PORT_SIDE_8; break;
                    case 10: aActiveClientIntfId = CT_PORT_SIDE_11; break;
                    case 11: aActiveClientIntfId = CT_PORT_SIDE_10; break;
                    case 12: aActiveClientIntfId = CT_PORT_SIDE_13; break;
                    case 13: aActiveClientIntfId = CT_PORT_SIDE_12; break;
                    case 14: aActiveClientIntfId = CT_PORT_SIDE_15; break;
                    case 15: aActiveClientIntfId = CT_PORT_SIDE_14; break;
                }
            }
            aOduLineIntfId = CT_PORT_SIDE_32;
            aOduIndex = aActiveClientIntfId;

            aMonActiveOptAppPtr = myCardIf->GetOptIf().GetMonPortSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOtuAppPtr = myCardIf->GetOtuIf().GetMonPortSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOduAppPtr = myCardIf->GetOduIf().GetMonPortSideAppPtr((CT_IntfId) aOduLineIntfId );
        }
        else
        {
            //ESM40/20
            switch ( myPortOffset )
            {
                case 85: 
                    aActiveClientIntfId = CT_PORT_SIDE_85; 
                    aOduIndex = CT_PORT_SIDE_3;
                    break;
                case 86: 
                    aActiveClientIntfId = CT_PORT_SIDE_86; 
                    aOduIndex = CT_PORT_SIDE_2;
                    break;
                case 87: 
                    aActiveClientIntfId = CT_PORT_SIDE_87; 
                    aOduIndex = CT_PORT_SIDE_1;
                    break;
                case 88: 
                    aActiveClientIntfId = CT_PORT_SIDE_88; 
                    aOduIndex = CT_PORT_SIDE_0;
                    break;
            }

            aOduLineIntfId = CT_PORT_SIDE_32;
            aMonActiveOptAppPtr = myCardIf->GetOptIf().GetMonPortSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOtuAppPtr = myCardIf->GetOtuIf().GetMonPortSideAppPtr((CT_IntfId) aActiveClientIntfId );
            aMonActiveOduAppPtr = myCardIf->GetOduIf().GetMonPortSideAppPtr((CT_IntfId) aOduLineIntfId );
        }

        ALM_TCount aBlkCSFDefectCount = 0;
        bool       aBlkCSFDefect = false;

        if ( aMonActiveOptAppPtr )
        {
            MON_Region* aMonActiveOptBcReg = aMonActiveOptAppPtr->GetDefectsRegion();
            if ( aMonActiveOptBcReg )
            {
            MON_OptDefects* aMonActiveOptObj = dynamic_cast<MON_OptDefects*>(&((*aMonActiveOptBcReg)[0]));
                if ( aMonActiveOptObj )
            aMonActiveOptObj->GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
            if ( aBlkCSFDefect )
                inhibitCSFDefects = true;
            }
        }
        if ( aMonActiveOtuAppPtr ) 
        {
            MON_Region* aMonActiveOtuBcReg = aMonActiveOtuAppPtr->GetDefectsRegion();
            if ( aMonActiveOtuBcReg )
            {
            MON_OtuDefects* aMonActiveOtuObj = dynamic_cast<MON_OtuDefects*>(&((*aMonActiveOtuBcReg)[0]));
                if ( aMonActiveOtuObj )
                {
            if ( !inhibitCSFDefects )
            {
                aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_LOMF_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_TIM_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_FECM_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }
        }
            }
        }
        if ( aMonActiveOduAppPtr )
        {
            MON_Region* aMonActiveOduBcReg = aMonActiveOduAppPtr->GetDefectsRegion();
            if ( aMonActiveOduBcReg )
            {
            MON_OduDefects* aMonActiveOduObj = dynamic_cast<MON_OduDefects*>(&((*aMonActiveOduBcReg)[(bbindex_t) aOduIndex]));
                if ( aMonActiveOduObj )
                {
            if ( !inhibitCSFDefects )
            {
                aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_AIS_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_LCK_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_OCI_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_PLM_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
            }

            if ( !inhibitCSFDefects )
            {
                aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aBlkCSFDefectCount, &aBlkCSFDefect);
                if ( aBlkCSFDefect )
                    inhibitCSFDefects = true;
                    }
                }
            }
        }

        if ( inhibitCSFDefects ) // Report or Clear the INHIBITING defect now!
        {
            AM_DefectCollector::GetInstance()->ReportDefect(AM_INH_TDTC_GFP_FAILURE_UID, myCardIf, 0, myPortOffset, CT_DIR_WAVE_LINE);
        }
        else
            AM_DefectCollector::GetInstance()->ClearDefect (AM_INH_TDTC_GFP_FAILURE_UID, myCardIf,    myPortOffset, CT_DIR_WAVE_LINE);
    }
}

