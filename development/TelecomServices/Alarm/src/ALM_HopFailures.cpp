/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class is used to determine the filtered failures of the
                HOP (High Order Path) layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_HopDefects.h>

//To drive LED on LOF
#include <ErrorService/FC_Error.h>
#include <AM/AM_DefectCollector.h>
#include <Alarm/ALM_RegionKeyDefinition.h>
#include <T6100_CardIf.h>

#include "../ALM_AppIf.h"
#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_HopFailureBase.h"

#include "ALM_HopFailures.h"


/* High Order Path filtering table. This table contains the 
 * failure conditions once they are filtered. The table entry (index)
 * is a combination of bits that represent the aggregate HOP failure conditions.
 * For the High Order Path, there are 9 failures, thus the table contains
 * all possible combinatons give by these failures, 2^9 (512) entries.
 *
 * bit#:     8       7     6    5     4    3    2    1      0
 * defect: UP_SA  UP_NSA  AIS  LOP  UNEQ  PLM  RDI SFBER  SDBER
 */
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // Bit 0 - SDBER filters nothing.
    0x00, 0x01,
    // Bit 1 - SFBER filters nothing.
	0x02, 0x03,
    // Bit 2 - RDI filters nothing.
    0x04, 0x05, 0x06, 0x07,
    // Bit 3 - PLM filters nothing.
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    // Bit 4 - UNEQ filters PLM,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    // Bit 5 - LOP filters UNEQ, PLM, RDI, SFBER, and SDBER.
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    // Bit 6 - AIS filters LOP, UNEQ, PLM, RDI, SFBER, and SDBER
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    // Bit 7 - UP_NSA filters nothing.
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
    0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
    0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
    0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    // Bit 8 - UP_SA filters nothing.
    0x100, 0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107,
    0x108, 0x109, 0x10a, 0x10b, 0x10c, 0x10d, 0x10e, 0x10f,
    0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117,
    0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117,
    0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120,
    0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120,
    0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120,
    0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120, 0x120,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140, 0x140,
    0x180, 0x181, 0x182, 0x183, 0x184, 0x185, 0x186, 0x187,
    0x188, 0x189, 0x18a, 0x18b, 0x18c, 0x18d, 0x18e, 0x18f,
    0x190, 0x191, 0x192, 0x193, 0x194, 0x195, 0x196, 0x197,
    0x190, 0x191, 0x192, 0x193, 0x194, 0x195, 0x196, 0x197,
    0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0,
    0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0,
    0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0,
    0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0, 0x1a0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
    0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0
};

// One bit set for each possible HOP defect.
static const ALM_BitField ourFailureProtectionMask = 0x01ff;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of the lower layer if one of the following
// failures or defects are declared: AIS, LOP, UNEQ, and PLM.
// See SRS 7100000715 Table 6-11 Facility Defect Correlation Heirarchy.
static const ALM_BitField ourFilterAllMask = 0x0078;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
// See SRS 7100000715 Table 6-11 Facility Defect Correlation Heirarchy.
static const ALM_BitField ourNoFilterMask = 0x0180;

//-----------------------------------------------------------------
// Class used to store the High Order Path (HOP) failure statuses.
//
ALM_HopFailures::ALM_HopFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_HopDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls the base class constructor
    ALM_LayerFailures 
    ( 
        ALM_HopFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr,
        ALM_LayerFailures::ALM_SP_NB_OF_SOAK_DEFECT
    ),
    // Set the monitor
    myMonitor(theMonitor),
    
    // Upper Non-Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_HOP_SOAKING_TIME),

    //-------------------------------------------
    // Signal Protection Not Service Affecting
    // must report NSA flag after 10 second soak
    // and clear   NSA flag after 2  second soak.
    // NOTE: this is the opposite of reporting/clearing
    //       defects, because SP-NSA is REPORTED
    //       when defects are CLEARED!
    //-------------------------------------------
    mySigProtNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME),

    myCardIf(NULL)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_HopFailureBase::UPPER_SA_HOP,  &myUpperSa);
    AddAt (ALM_HopFailureBase::UPPER_NSA_HOP, &myUpperNsa);
    AddAt (ALM_HopFailureBase::AIS_HOP,       &myAis);
    AddAt (ALM_HopFailureBase::LOP_HOP,       &myLop);
    AddAt (ALM_HopFailureBase::UNEQ_HOP,      &myUneq);
    AddAt (ALM_HopFailureBase::PLM_HOP,       &myPlm);
    AddAt (ALM_HopFailureBase::RDI_HOP,       &myRdi);
    AddAt (ALM_HopFailureBase::SFBER_HOP,     &mySfBer);
    AddAt (ALM_HopFailureBase::SDBER_HOP,     &mySdBer);

    // Add all SP Soak failures to LayerFailures object
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_NOT_SA,      &mySigProtNSA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_STRM_A_NR,   &mySigProtALMNR);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_ALM_MATE_ID, &mySigProtMATE);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_PROTNA_UID,  &mySigProtProtna);
}

//-----------------------------------------------------------------

//##ModelId=3F954C2F00A4
ALM_HopFailures::~ALM_HopFailures ()
{
}

//-----------------------------------------------------------------
// Method reads each HOP error status located in the MON region and
// returns the results in a bit map.
//
ALM_BitField ALM_HopFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_HOP defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_UPPER_LAYER_FAIL_TA_DEFECT,   ALM_HopFailureBase::UPPER_SA_HOP)
    
    // Read the UPPER_NSA_HOP defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_UPPER_LAYER_FAIL_NTA_DEFECT,   ALM_HopFailureBase::UPPER_NSA_HOP)

    // Read the AIS-P defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_AIS_DEFECT,   ALM_HopFailureBase::AIS_HOP)

    // Read the LOP-P defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_LOP_DEFECT,   ALM_HopFailureBase::LOP_HOP)

    // Read the UNEQ-P defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_UNEQ_DEFECT,   ALM_HopFailureBase::UNEQ_HOP)

    // Read the PLM-P defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_PLM_DEFECT,   ALM_HopFailureBase::PLM_HOP)

    // Read the RDI defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_RDI_DEFECT,   ALM_HopFailureBase::RDI_HOP)

    // Read the SF Bit error rate defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_SFBER_DEFECT, ALM_HopFailureBase::SFBER_HOP)

    // Read the SD bit error rate defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_HOP_SDBER_DEFECT, ALM_HopFailureBase::SDBER_HOP)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
// Method returns a predefined HOP filter (a bitmap) based on the current
// HOP defect status obtained from MON.
//
ALM_BitField ALM_HopFailures::Filter(ALM_BitField theFailure) const
{
    //Filter raw failure according to the table
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------

ALM_BitField ALM_HopFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer.
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
ALM_BitField ALM_HopFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}


