/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OTU (Optical
                Transport Unit) layer.
--------------------------------------------------------------------------*/

#include "BaseClass/FC_TextStream.h"

#include "../ALM_OtuFailureBase.h"

//--------------------------------------------------------------------------
//##ModelId=3C506C3700A4
ALM_OtuFailureBase::ALM_OtuFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3700AE
ALM_OtuFailureBase::~ALM_OtuFailureBase()
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3700B0
int ALM_OtuFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_OTU:  aFailureIndex = UPPER_SA_OTU;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_OTU: aFailureIndex = UPPER_NSA_OTU; break;
        case CT_TelAlarmCondition::ALM_LOF_OTU:       aFailureIndex = LOF_OTU;       break;
        case CT_TelAlarmCondition::ALM_LOM_OTU:       aFailureIndex = LOM_OTU;       break;
        case CT_TelAlarmCondition::ALM_AIS_OTU:       aFailureIndex = AIS_OTU;       break;
        case CT_TelAlarmCondition::ALM_TIM_OTU:       aFailureIndex = TIM_OTU;       break;
        case CT_TelAlarmCondition::ALM_TIM_NSA_OTU:   aFailureIndex = TIM_NSA_OTU;   break;
        case CT_TelAlarmCondition::ALM_FECM_OTU:      aFailureIndex = FECM_OTU;      break;
        case CT_TelAlarmCondition::ALM_BDI_OTU:       aFailureIndex = BDI_OTU;       break;
        case CT_TelAlarmCondition::ALM_BERSD_OTU:     aFailureIndex = BERSD_OTU;     break;
        case CT_TelAlarmCondition::ALM_FEC_SD_OTU:    aFailureIndex = FEC_SD_OTU;    break;
        case CT_TelAlarmCondition::ALM_DISP_OTU:      aFailureIndex = DISP_OTU;      break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OTU Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3700B9
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OtuFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_OTU:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_OTU;  break;
        case UPPER_NSA_OTU: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_OTU; break;
        case LOF_OTU:       aFailureType = CT_TelAlarmCondition::ALM_LOF_OTU;       break;
        case LOM_OTU:       aFailureType = CT_TelAlarmCondition::ALM_LOM_OTU;       break;
        case AIS_OTU:       aFailureType = CT_TelAlarmCondition::ALM_AIS_OTU;       break;
        case TIM_OTU:       aFailureType = CT_TelAlarmCondition::ALM_TIM_OTU;       break;
        case TIM_NSA_OTU:   aFailureType = CT_TelAlarmCondition::ALM_TIM_NSA_OTU;   break;
        case FECM_OTU:      aFailureType = CT_TelAlarmCondition::ALM_FECM_OTU;      break;
        case BDI_OTU:       aFailureType = CT_TelAlarmCondition::ALM_BDI_OTU;       break;
        case BERSD_OTU:     aFailureType = CT_TelAlarmCondition::ALM_BERSD_OTU;     break;
        case FEC_SD_OTU:    aFailureType = CT_TelAlarmCondition::ALM_FEC_SD_OTU;    break;
        case DISP_OTU:      aFailureType = CT_TelAlarmCondition::ALM_DISP_OTU;      break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OTU Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3700C3
void ALM_OtuFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "------------------------------------------------------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:    LOF:       LOM:       AIS:       TIM:       TIM_NSA:    FECM:     BDI:      BERSD:   FECSD:   DISP:\n"
         << "    ---------- ---------- ---------- ---------- ---------- --------- -------- ---------- --------   ------  ------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3C506C3700C5
ostream& ALM_OtuFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_OTU]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_OTU]);
    theStream   << FC_InsertVar(itsStatus[LOF_OTU]);
    theStream   << FC_InsertVar(itsStatus[LOM_OTU]);
    theStream   << FC_InsertVar(itsStatus[AIS_OTU]);
    theStream   << FC_InsertVar(itsStatus[TIM_OTU]);
    theStream   << FC_InsertVar(itsStatus[TIM_NSA_OTU]);
    theStream   << FC_InsertVar(itsStatus[FECM_OTU]);
    theStream   << FC_InsertVar(itsStatus[BDI_OTU]);
    theStream   << FC_InsertVar(itsStatus[BERSD_OTU]);
    theStream   << FC_InsertVar(itsStatus[FEC_SD_OTU]);
    theStream   << FC_InsertVar(itsStatus[DISP_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[LOF_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[LOM_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_NSA_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[FECM_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[BDI_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[BERSD_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[FEC_SD_OTU]);
    theStream   << FC_InsertVar(itsOccurTime[DISP_OTU]);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3700CE
istream& ALM_OtuFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[LOF_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[LOM_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_NSA_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[FECM_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[BDI_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[BERSD_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[FEC_SD_OTU]);
    theStream   >> FC_ExtractVar(itsStatus[DISP_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOF_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOM_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_NSA_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[FECM_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[BDI_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[BERSD_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[FEC_SD_OTU]);
    theStream   >> FC_ExtractVar(itsOccurTime[DISP_OTU]);
    return theStream;
}
