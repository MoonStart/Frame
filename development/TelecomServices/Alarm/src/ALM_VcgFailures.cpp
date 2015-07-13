/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM & ESIM
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class manages the failures of VCG layer
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_AltVcgDefects.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Vcg.h>
#include <T6100_MainAppIf.h>
#include <ErrorService/FC_Error.h>
#include <Alarm/ALM_RegionKeyDefinition.h>
#include <Alarm/ALM_SubApplicationOnCard.h>
#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_VcgFailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include "ALM_VcgFailures.h"
#include "ALM_LayerFailures.h"
#include <AM/AM_DefectCollector.h>
#include <AM/AM_DefectProcessor.h>

/* VCG filtering table. This table contains the 
failure conditions once they are filtered. The table entry (index)
is a combination of bits that represent the failure conditions.
For VCG, there are 8 failures, so the table contains
all possible combinatons given by these failures. That means the
table has 2^8 (256) combinations.

bit#:     8       7        6         5        4        3     2    1    0
defect: UP_SA   UP_NSA  FOP_TX    TLC_RX   FOP_RX   PLC_RX  LOM  SQM  MND

*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    0x00, 0x01, 0x02, 0x03, 

    0x04, 0x05, 0x06, 0x07,

    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,

    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, //
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, // FOP_RX suppress PLC_RX

    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, // TLC_RX suppress PLC_RX
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, // TLC_RX suppress FOP_RX

    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 

    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, // 0xff suppress table complete...NSA

    0x100, 0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0x108, 0x109, 0x10a, 0x10b, 0x10c, 0x10d, 0x10e, 0x10f,
    0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 
    0x120, 0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 0x120, 0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 
    0x120, 0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 0x120, 0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 
    0x140, 0x141, 0x142, 0x143, 0x144, 0x145, 0x146, 0x147, 0x148, 0x149, 0x14a, 0x14b, 0x14c, 0x14d, 0x14e, 0x14f, 
    0x150, 0x151, 0x152, 0x153, 0x154, 0x155, 0x156, 0x157, 0x150, 0x151, 0x152, 0x153, 0x154, 0x155, 0x156, 0x157,
    0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167, 0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167,
    0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167, 0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167,
    0x180, 0x181, 0x182, 0x183, 0x184, 0x185, 0x186, 0x187, 0x188, 0x189, 0x18a, 0x18b, 0x18c, 0x18d, 0x18e, 0x18f, 
    0x190, 0x191, 0x192, 0x193, 0x194, 0x195, 0x196, 0x197, 0x190, 0x191, 0x192, 0x193, 0x194, 0x195, 0x196, 0x197,
    0x1a0, 0x1a1, 0x1a2, 0x1a3, 0x1a4, 0x1a5, 0x1a6, 0x1a7, 0x1a0, 0x1a1, 0x1a2, 0x1a3, 0x1a4, 0x1a5, 0x1a6, 0x1a7,
    0x1a0, 0x1a1, 0x1a2, 0x1a3, 0x1a4, 0x1a5, 0x1a6, 0x1a7, 0x1a0, 0x1a1, 0x1a2, 0x1a3, 0x1a4, 0x1a5, 0x1a6, 0x1a7,
    0x1c0, 0x1c1, 0x1c2, 0x1c3, 0x1c4, 0x1c5, 0x1c6, 0x1c7, 0x1c8, 0x1c9, 0x1ca, 0x1cb, 0x1cc, 0x1cd, 0x1ce, 0x1cf, 
    0x1d0, 0x1d1, 0x1d2, 0x1d3, 0x1d4, 0x1d5, 0x1d6, 0x1d7, 0x1d0, 0x1d1, 0x1d2, 0x1d3, 0x1d4, 0x1d5, 0x1d6, 0x1d7,
    0x1e0, 0x1e1, 0x1e2, 0x1e3, 0x1e4, 0x1e5, 0x1e6, 0x1e7, 0x1e0, 0x1e1, 0x1e2, 0x1e3, 0x1e4, 0x1e5, 0x1e6, 0x1e7,
    0x1e0, 0x1e1, 0x1e2, 0x1e3, 0x1e4, 0x1e5, 0x1e6, 0x1e7, 0x1e0, 0x1e1, 0x1e2, 0x1e3, 0x1e4, 0x1e5, 0x1e6, 0x1e7,
};

static const ALM_BitField ourFailureProtectionMask = 0x01ff;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of lower layer if one of the folowing failure
// or defect is declared: 
static const ALM_BitField ourFilterAllMask = 0x0000;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x0180;

//-----------------------------------------------------------------
ALM_VcgFailures::ALM_VcgFailures (ALM_IndexNb theIndex,
                                ALM_AppIf& theApplication,
                                MON_AltVcgDefects& theMonitor,
                                CT_CardFamily theCardFamily,
                                ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_VcgFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor),
    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_VCG_SOAKING_TIME),
    myCardFamily(theCardFamily)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_VcgFailureBase::UPPER_SA_VCG,  &myUpperSa);
    AddAt (ALM_VcgFailureBase::UPPER_NSA_VCG, &myUpperNsa);
    AddAt (ALM_VcgFailureBase::TLC_RX,        &myTLCRX);
    AddAt (ALM_VcgFailureBase::PLC_RX,        &myPLCRX);
    AddAt (ALM_VcgFailureBase::FOP_RX,        &myFOPRX);
    AddAt (ALM_VcgFailureBase::FOP_TX,        &myFOPTX);
    AddAt (ALM_VcgFailureBase::LOM,           &myLOM);
    AddAt (ALM_VcgFailureBase::SQM,           &mySQM);
    AddAt (ALM_VcgFailureBase::MND,           &myMND);

    IsVCGBlockAlarmFlagSet = false;

    myCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
    myRptIf = NULL;
    
}

//-----------------------------------------------------------------
ALM_VcgFailures::~ALM_VcgFailures ()
{
}

//-----------------------------------------------------------------
ALM_BitField ALM_VcgFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_VCG defect from the monitor
    //ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_UPPER_LAYER_FAIL_TA_DEFECT, ALM_VcgFailureBase::UPPER_SA_VCG)

    // Read the UPPER_NSA_VCG defect from the monitor
    //ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_RsFailureBase::UPPER_NSA_VCG)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_RX_TLC, ALM_VcgFailureBase::TLC_RX)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_RX_PLC, ALM_VcgFailureBase::PLC_RX)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_RX_FOP, ALM_VcgFailureBase::FOP_RX)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_TX_FOP, ALM_VcgFailureBase::FOP_TX)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_LOS_MF_ALIGN,       ALM_VcgFailureBase::LOM)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_SEQMISMATCH,        ALM_VcgFailureBase::SQM)
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_VCG_MBR_NOT_DESKEWABLE, ALM_VcgFailureBase::MND)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
ALM_BitField ALM_VcgFailures::Filter(ALM_BitField theFailure) const
{
    //Filter raw failure according to the table
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
ALM_BitField ALM_VcgFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer.
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_VcgFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//=================================================================================
// ProcessAfterSoaking() method is called every .5 seconds (ALM_LayerFailures).
//=================================================================================
void ALM_VcgFailures::ProcessAfterSoaking()
{
    bool aDropStatus = false;
    ALM_TCount aTCount = 0;

    //-----------------------------------------------------------------------------
    // If the VCG's CCPATH is DROP (maps to CT_TEL_VCG_IS_SRC), then we are o.k.
    // Otherwise, we must create INHIBITING VCG defect to block VCG RX conditions.
    //-----------------------------------------------------------------------------
    myMonitor.GetDefectStatus(CT_TEL_VCG_IS_SRC, &aTCount, &aDropStatus);

    if ( aDropStatus ) 
    {
        if ( IsVCGBlockAlarmFlagSet ) 
        {
            IsVCGBlockAlarmFlagSet = false;
            AM_DefectCollector::GetInstance()->ClearDefect(
                AM_VCG_BLOCK_RX_COND_UID, myCardIf,            0/*port0*/, CT_DIR_WAVE_LINE, itsIndex+1);
        }
    }
    else
    {
        if ( IsVCGBlockAlarmFlagSet == false) 
        {
            IsVCGBlockAlarmFlagSet = true;
            AM_DefectCollector::GetInstance()->ReportDefect(
                AM_VCG_BLOCK_RX_COND_UID, myCardIf, 0/*time*/, 0/*port0*/, CT_DIR_WAVE_LINE, itsIndex+1);
        }
    }
}

