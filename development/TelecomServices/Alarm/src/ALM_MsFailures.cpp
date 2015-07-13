/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class manages the failures of MS (Regenerator
                Section) layer
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_MsDefects.h>
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_OtuDefects.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_OptProtConfig.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Ms.h>
#include <Configuration/CFG_Rs.h>
#include <ErrorService/FC_Error.h>
#include <T6100_CardIf.h>
#include <AM/AM_DefectCollector.h>

#include <Alarm/ALM_RegionKeyDefinition.h>
#include <Alarm/ALM_SubApplicationOnCard.h>
#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include "../ALM_MsFailureBase.h"

#include "ALM_MsFailures.h"

/* Regenerator Section filtering table. This table contained the 
failure conditions once they are filtered. The table entry (index)
is a combination of bits that represent the failure conditions.
For Regenerator Section, there are 6 failures, so the table contains
all possible combinatons give by these failures. That means the
table has 2^6 (64) combinations.

bit#:    7       6          5        4     3    2    1     0
defect: UP_SA   UP_NSA  UP_INT_SA AIS-INT AIS  RDI SFBER  SDBER
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // SFBER filters nothing.
    0x00, 0x01, 0x02, 0x03,
    // RDI filter nothing.
    0x04, 0x05, 0x06, 0x07,
    // AIS filter RDI, SFBER and SDBER.
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    // AIS-INT filters nothing
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,

    // UP_INT_SA filters AIS-INT.
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,

    // UPPER_NSA filters nothing.
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58,

    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68,


    // UPPER_SA filters nothing.
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98,

    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8,

    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8,

    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
    0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xE8,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
    0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xE8,
};

// One bit set for each possible MS defect.
static const ALM_BitField ourFailureProtectionMask = 0x00ff;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of lower layer if one of the folowing failure
// or defect is declared: AIS, SFBER.
static const ALM_BitField ourFilterAllMask = 0x000A;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA and AIS-INT.
static const ALM_BitField ourNoFilterMask = 0x00F0;

//-----------------------------------------------------------------

//##ModelId=3F954C2F009F
ALM_MsFailures::ALM_MsFailures (ALM_IndexNb theIndex,
                                ALM_AppIf& theApplication,
                                MON_MsDefects& theMonitor,
                                ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_MsFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr,
        ALM_LayerFailures::ALM_SP_NB_OF_SOAK_DEFECT
    ),
    //Set the monitor
    myMonitor(theMonitor),
    
    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_MS_SOAKING_TIME),

    //-------------------------------------------
    // Signal Protection Not Service Affecting
    // must report NSA flag after 10 second soak
    // and clear   NSA flag after 2  second soak.
    // NOTE: this is the opposite of reporting/clearing
    //       defects, because SP-NSA is REPORTED
    //       when defects are CLEARED!
    //-------------------------------------------
    mySigProtNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME),

    myPortOffset(0),
    theDirn(CT_DIR_WAVE_PORT),
    myCardIf(NULL)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_MsFailureBase::UPPER_SA_MS,  &myUpperSa);
    AddAt (ALM_MsFailureBase::UPPER_NSA_MS, &myUpperNsa);
    AddAt (ALM_MsFailureBase::UPPER_INT_SA_MS, &myUpperIntSa);
    AddAt (ALM_MsFailureBase::AIS_INT_MS,   &myAisInt);
    AddAt (ALM_MsFailureBase::AIS_MS,       &myAis);
    AddAt (ALM_MsFailureBase::SFBER_MS,     &mySfBer);
    AddAt (ALM_MsFailureBase::SDBER_MS,     &mySdBer);
    AddAt (ALM_MsFailureBase::RDI_MS,       &myRdi);

    // Add all SP Soak failures to LayerFailures object
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_NOT_SA,     &mySigProtNSA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_PROTNA_UID, &mySigProtProtna);

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
        else if (myCardIf && myCardIf->GetCardFamily() == FGTMM_FAM)
        {
            if      (sKey == ALM_PORT_0_SUFFIX)   {  myPortOffset = 0;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_1_SUFFIX)   {  myPortOffset = 1;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_2_SUFFIX)   {  myPortOffset = 2;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_3_SUFFIX)   {  myPortOffset = 3;  theDirn = CT_DIR_WAVE_PORT; }
        }
        else if (myCardIf && myCardIf->GetCardFamily() == HDTG2_FAM)
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
            else if (sKey == ALM_PORT_10_SUFFIX)   {  myPortOffset = 10;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_11_SUFFIX)   {  myPortOffset = 11;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_12_SUFFIX)   {  myPortOffset = 12;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_13_SUFFIX)   {  myPortOffset = 13;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_14_SUFFIX)   {  myPortOffset = 14;  theDirn = CT_DIR_WAVE_PORT; }
            else if (sKey == ALM_PORT_15_SUFFIX)   {  myPortOffset = 15;  theDirn = CT_DIR_WAVE_PORT; }
        }
    }
}

//-----------------------------------------------------------------

//##ModelId=3F954C2F00A4
ALM_MsFailures::~ALM_MsFailures ()
{
}

//-----------------------------------------------------------------

//##ModelId=3F954C2F00A6
ALM_BitField ALM_MsFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_MS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_UPPER_LAYER_FAIL_TA_DEFECT,   ALM_MsFailureBase::UPPER_SA_MS)
    
    // Read the UPPER_NSA_MS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_UPPER_LAYER_FAIL_NTA_DEFECT,   ALM_MsFailureBase::UPPER_NSA_MS)

    // Read the UPPER_INT_SA_MS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT,   ALM_MsFailureBase::UPPER_INT_SA_MS)

    // Read the AIS-L INTERNAL defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_INTERNAL_AISL_DEFECT, ALM_MsFailureBase::AIS_INT_MS)

    // Read the AIS-L defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_AIS_DEFECT,   ALM_MsFailureBase::AIS_MS)

    // Read the SF Bit error rate defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_SFBER_DEFECT, ALM_MsFailureBase::SFBER_MS)

    // Read the SD bit error rate defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_SDBER_DEFECT, ALM_MsFailureBase::SDBER_MS)

    // Read the RDI defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_MS_RDI_DEFECT,   ALM_MsFailureBase::RDI_MS)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------

//##ModelId=3F954C2F00B2
ALM_BitField ALM_MsFailures::Filter(ALM_BitField theFailure) const
{
    //Filter raw failure according to the table
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------

//##ModelId=3F954C2F00AE
ALM_BitField ALM_MsFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer.
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
//##ModelId=3F954C2F00B0
ALM_BitField ALM_MsFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//---------------------------------------------------------------------------------
void ALM_MsFailures::ProcessAfterSoaking()
{
    if (myCardIf && ((myCardIf->GetCardFamily() == HDTG_FAM) || (myCardIf->GetCardFamily() == FGTMM_FAM) || (myCardIf->GetCardFamily() == HDTG2_FAM)))
    {
        bool inhibitAISLInternal = false;

        CT_IntfId aActiveClientIntfId = CT_INTF_ID_UNKNOWN;
        CT_IntfId aOduIndex = CT_INTF_ID_UNKNOWN;
        CT_IntfId aOduLineIntfId = CT_INTF_ID_UNKNOWN;

        MON_AppIf* aMonActiveOptAppPtr = NULL;
        MON_AppIf* aMonActiveOtuAppPtr = NULL;
        MON_AppIf* aMonActiveOduAppPtr = NULL;
        MON_AppIf* aMonActiveRsAppPtr = NULL;

        if ( myCardIf->GetCardFamily() == HDTG_FAM )
        {
            // OPT-MON-PROT will determine if DPRING exists and ACTIVE source for OC192(AIS-L-INT).
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
        else if ( myCardIf->GetCardFamily() == FGTMM_FAM )    //FGTMM
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
        else // HDTG2
        {
            // OPT-MON-PROT will determine if DPRING exists and ACTIVE source for OC192(AIS-L-INT).
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
            aMonActiveRsAppPtr = myCardIf->GetRsIf().GetMonPortSideAppPtr((CT_IntfId) myPortOffset );

        }

        ALM_TCount aBlkAISLCount = 0;
        bool       aBlkAISLDefect = false;

        if ( aMonActiveOptAppPtr ) 
        {
            MON_Region* aMonActiveOptBcReg = aMonActiveOptAppPtr->GetDefectsRegion();
            if ( aMonActiveOptBcReg )
            {
                MON_OptDefects* aMonActiveOptObj = dynamic_cast<MON_OptDefects*>(&((*aMonActiveOptBcReg)[0]));
                if ( aMonActiveOptObj )
                {
                    aMonActiveOptObj->GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                    if ( aBlkAISLDefect )
                        inhibitAISLInternal = true;
                }
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
                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_LOMF_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_TIM_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOtuObj->GetDefectStatus(CT_TEL_OTU_FECM_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }
                }
            }
        }
        
        if ( aMonActiveRsAppPtr ) 
        {
            MON_Region* aMonActiveRsBcReg = aMonActiveRsAppPtr->GetDefectsRegion();
            if ( aMonActiveRsBcReg )
            {
                MON_RsDefects* aMonActiveRsObj = dynamic_cast<MON_RsDefects*>(&((*aMonActiveRsBcReg)[0]));
                if ( aMonActiveRsObj )
                {
                    aMonActiveRsObj->GetDefectStatus(CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                    if ( aBlkAISLDefect )
                        inhibitAISLInternal = true;
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
                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_AIS_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_LCK_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_OCI_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_PLM_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }

                    if ( !inhibitAISLInternal )
                    {
                        aMonActiveOduObj->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                        if ( aBlkAISLDefect )
                            inhibitAISLInternal = true;
                    }
                }
            }
        }

        if ( inhibitAISLInternal ) // Report or Clear the INHIBITING defect now!
        {
            AM_DefectCollector::GetInstance()->ReportDefect(AM_INH_TDTC_FAILURE_UID, myCardIf, 0, myPortOffset, CT_DIR_WAVE_LINE);
        }
        else
            AM_DefectCollector::GetInstance()->ClearDefect (AM_INH_TDTC_FAILURE_UID, myCardIf,    myPortOffset, CT_DIR_WAVE_LINE);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    CFG_AppIf* ConfigAppIf = myApplication.GetCfgApp(); // RS CFG Application (see *_Applicaton.cpp)

    if (ConfigAppIf != NULL )
    {
        CFG_Region* ConfigRegion = ConfigAppIf->GetCfgRegion();
        if (ConfigRegion->IsValid())
        {
            CFG_Rs* aRsCfgObject = NULL;
            CT_TEL_SignalType aSignalType = CT_TEL_SIGNAL_UNKNOWN;

            //----------------------------------------------------------------
            // We use the RS layer CFG application to get the Signal Type, as
            // Signal Type is no longer in the MS layer CFG.
            //----------------------------------------------------------------
            aRsCfgObject = dynamic_cast<CFG_Rs*>(&((*ConfigRegion)[0]));
            if ( aRsCfgObject )
            {
                    aSignalType = aRsCfgObject->GetSignalType();
            }
            
            //----------------------------------------------------------------------------
            // If the signal type retrieved from CFG is different from what is currently
            // stored in the signal alarms RS filtered region, then update the region.
            //----------------------------------------------------------------------------
            if ( (aRsCfgObject) && (itsFilteredFailureBase.GetSignalType() != aSignalType) )
            {
                // Set the signal type into the BB
                itsFilteredFailureBase.SetSignalType(aSignalType);
                // Increment assiciated region modification counter
                itsFilteredFailureRegionPtr->IncModificationCounter();
            }
        }
    }
}

