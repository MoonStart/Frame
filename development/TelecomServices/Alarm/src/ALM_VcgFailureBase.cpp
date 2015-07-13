/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class defines the failure type of VCG layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_VcgFailureBase.h"

//--------------------------------------------------------------------------
ALM_VcgFailureBase::ALM_VcgFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
ALM_VcgFailureBase::~ALM_VcgFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_VcgFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_VCG:     aFailureIndex = UPPER_SA_VCG;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_VCG:    aFailureIndex = UPPER_NSA_VCG; break;      
        case CT_TelAlarmCondition::ALM_PLC_RX_VCG:       aFailureIndex = PLC_RX;        break;
        case CT_TelAlarmCondition::ALM_TLC_RX_VCG:       aFailureIndex = TLC_RX;        break;
        case CT_TelAlarmCondition::ALM_FOP_RX_VCG:       aFailureIndex = FOP_RX;        break;
        case CT_TelAlarmCondition::ALM_FOP_TX_VCG:       aFailureIndex = FOP_TX;        break;
        case CT_TelAlarmCondition::ALM_LOS_MF_ALIGN_VCG: aFailureIndex = LOM;           break;
        case CT_TelAlarmCondition::ALM_SQM_VCG:          aFailureIndex = SQM;           break;
        case CT_TelAlarmCondition::ALM_MND_VCG:          aFailureIndex = MND;           break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid VCG Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_VcgFailureBase::GetTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_VCG:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_VCG;     break;
        case UPPER_NSA_VCG: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_VCG;    break;
        case PLC_RX:        aFailureType = CT_TelAlarmCondition::ALM_PLC_RX_VCG;       break;
        case TLC_RX:        aFailureType = CT_TelAlarmCondition::ALM_TLC_RX_VCG;       break;
        case FOP_RX:        aFailureType = CT_TelAlarmCondition::ALM_FOP_RX_VCG;       break;
        case FOP_TX:        aFailureType = CT_TelAlarmCondition::ALM_FOP_TX_VCG;       break;
        case LOM:           aFailureType = CT_TelAlarmCondition::ALM_LOS_MF_ALIGN_VCG; break;
        case SQM:           aFailureType = CT_TelAlarmCondition::ALM_SQM_VCG;          break;
        case MND:           aFailureType = CT_TelAlarmCondition::ALM_MND_VCG;          break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid VCG index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_VcgFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------------------------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:    FOPTX:     FOPRX:     TLC_RX:    PLC_RX:     LOM:    SQM:    MND:  \n"
         << "    ---------- ---------- ---------- ---------- ---------- ----------  ----    ----    ----  \n";
}

//--------------------------------------------------------------------------
FC_Stream& ALM_VcgFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );

    return theStream;
}

//--------------------------------------------------------------------------
FC_Stream& ALM_VcgFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = *itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    return theStream;
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
ostream& ALM_VcgFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_VCG]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_VCG]);
    theStream   << FC_InsertVar(itsStatus[TLC_RX]);
    theStream   << FC_InsertVar(itsStatus[PLC_RX]);
    theStream   << FC_InsertVar(itsStatus[FOP_RX]);
    theStream   << FC_InsertVar(itsStatus[FOP_TX]);
    theStream   << FC_InsertVar(itsStatus[LOM]);
    theStream   << FC_InsertVar(itsStatus[SQM]);
    theStream   << FC_InsertVar(itsStatus[MND]);

    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_VcgFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_VCG]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_VCG]);
    theStream   >> FC_ExtractVar(itsStatus[TLC_RX]);
    theStream   >> FC_ExtractVar(itsStatus[PLC_RX]);
    theStream   >> FC_ExtractVar(itsStatus[FOP_RX]);
    theStream   >> FC_ExtractVar(itsStatus[FOP_TX]);
    theStream   >> FC_ExtractVar(itsStatus[LOM]);
    theStream   >> FC_ExtractVar(itsStatus[SQM]);
    theStream   >> FC_ExtractVar(itsStatus[MND]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_VCG]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_VCG]);
    theStream   >> FC_ExtractVar(itsOccurTime[TLC_RX]);
    theStream   >> FC_ExtractVar(itsOccurTime[PLC_RX]);
    theStream   >> FC_ExtractVar(itsOccurTime[FOP_RX]);
    theStream   >> FC_ExtractVar(itsOccurTime[FOP_TX]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOM]);
    theStream   >> FC_ExtractVar(itsOccurTime[SQM]);
    theStream   >> FC_ExtractVar(itsOccurTime[MND]);

    return theStream;
}

