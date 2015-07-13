/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of ODU (Optical Data
                Unit) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_OduFailureBase.h"

//--------------------------------------------------------------------------
//##ModelId=3C506C3801B3
ALM_OduFailureBase::ALM_OduFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus, ALM_SP_NB_OF_DEFECT),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3801BD
ALM_OduFailureBase::~ALM_OduFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_OduFailureBase::GetSignalType() const
{
    return itsSignalType;
}
 
//--------------------------------------------------------------------------
void ALM_OduFailureBase::SetSignalType(int signalType)
{
     itsSignalType = signalType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3801BF
int ALM_OduFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_ODU:  aFailureIndex = UPPER_SA_ODU;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_ODU: aFailureIndex = UPPER_NSA_ODU; break;
        case CT_TelAlarmCondition::ALM_AIS_ODU: aFailureIndex = AIS_ODU;    break;
        case CT_TelAlarmCondition::ALM_GENAIS_ODU: aFailureIndex = GENAIS_ODU;    break;
        case CT_TelAlarmCondition::ALM_TIM_ODU: aFailureIndex = TIM_ODU;    break;
        case CT_TelAlarmCondition::ALM_TIM_NSA_ODU: aFailureIndex = TIM_NSA_ODU;    break;
        case CT_TelAlarmCondition::ALM_PLM_ODU: aFailureIndex = PLM_ODU;    break;
        case CT_TelAlarmCondition::ALM_LCK_ODU: aFailureIndex = LCK_ODU;    break;
        case CT_TelAlarmCondition::ALM_OCI_ODU: aFailureIndex = OCI_ODU;    break;
        case CT_TelAlarmCondition::ALM_BER_ODU: aFailureIndex = BER_ODU;    break;
        case CT_TelAlarmCondition::ALM_BDI_ODU: aFailureIndex = BDI_ODU;    break;
        case CT_TelAlarmCondition::ALM_MSIM_ODU:aFailureIndex = MSIM_ODU;   break;
        case CT_TelAlarmCondition::ALM_LOFLOM_ODU:aFailureIndex = LOFLOM_ODU; break;
        case CT_TelAlarmCondition::ALM_LOOMFI_ODU: aFailureIndex = LOOMFI_ODU; break;
        case CT_TelAlarmCondition::ALM_SSF_ODU: aFailureIndex = SSF_ODU; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid ODU Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3801C8
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OduFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_ODU:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_ODU;  break;
        case UPPER_NSA_ODU: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_ODU; break;
        case AIS_ODU:   aFailureType = CT_TelAlarmCondition::ALM_AIS_ODU;   break;
        case GENAIS_ODU:   aFailureType = CT_TelAlarmCondition::ALM_GENAIS_ODU;   break;
        case TIM_ODU:   aFailureType = CT_TelAlarmCondition::ALM_TIM_ODU;   break;
        case TIM_NSA_ODU:   aFailureType = CT_TelAlarmCondition::ALM_TIM_NSA_ODU;   break;
        case PLM_ODU:   aFailureType = CT_TelAlarmCondition::ALM_PLM_ODU;   break;
        case LCK_ODU:   aFailureType = CT_TelAlarmCondition::ALM_LCK_ODU;   break;
        case OCI_ODU:   aFailureType = CT_TelAlarmCondition::ALM_OCI_ODU;   break;
        case BER_ODU:   aFailureType = CT_TelAlarmCondition::ALM_BER_ODU;   break;
        case BDI_ODU:   aFailureType = CT_TelAlarmCondition::ALM_BDI_ODU;   break;
        case MSIM_ODU:  aFailureType = CT_TelAlarmCondition::ALM_MSIM_ODU;  break;
        case LOFLOM_ODU:aFailureType = CT_TelAlarmCondition::ALM_LOFLOM_ODU; break;
        case LOOMFI_ODU: aFailureType = CT_TelAlarmCondition::ALM_LOOMFI_ODU; break;
        case SSF_ODU: aFailureType = CT_TelAlarmCondition::ALM_SSF_ODU; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid ODU Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
int ALM_OduFailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex = ALM_INVALID_FAILURE;

    // return the index coresponding to the Signal Protect defect type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_SP_NOT_SA:           aFailureIndex = SP_NOT_SERVICE_AFFECTING; break;
        case CT_TelAlarmCondition::ALM_SP_PROTNA_UID:       aFailureIndex = SP_PROTNA; break;
        case CT_TelAlarmCondition::ALM_SP_ODUKP_NOT_SA:     aFailureIndex = SP_ODUKP_NOT_SERVICE_AFFECTING; break;
        case CT_TelAlarmCondition::ALM_SP_ODUKP_PROTNA_UID: aFailureIndex = SP_ODUKP_PROTNA; break;
        case CT_TelAlarmCondition::ALM_SP_FOP_PM_UID:       aFailureIndex = SP_FOP_PM; break;
        case CT_TelAlarmCondition::ALM_SP_FOP_NR_UID:       aFailureIndex = SP_FOP_NR; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OduFailureBase::GetSigProtTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType = CT_TelAlarmCondition::ALM_INVALID_ALARM;
    
    //return the Signal Protect defect type corresponding to the index
    switch(theIndex)
    {
        case SP_NOT_SERVICE_AFFECTING:       aFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA; break;
        case SP_PROTNA:                      aFailureType = CT_TelAlarmCondition::ALM_SP_PROTNA_UID; break;
        case SP_ODUKP_NOT_SERVICE_AFFECTING: aFailureType = CT_TelAlarmCondition::ALM_SP_ODUKP_NOT_SA; break;
        case SP_ODUKP_PROTNA:                aFailureType = CT_TelAlarmCondition::ALM_SP_ODUKP_PROTNA_UID; break;
        case SP_FOP_PM:                      aFailureType = CT_TelAlarmCondition::ALM_SP_FOP_PM_UID; break;
        case SP_FOP_NR:                      aFailureType = CT_TelAlarmCondition::ALM_SP_FOP_NR_UID; break;
        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3801D1
void ALM_OduFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------------------------------------------------------------------------------------------------------------------\n"
         << "    UPPER SA   UPPER NSA  GENAIS:     AIS:     LOFLOM        TIM:         LCK:       OCI:       BER:       BDI:      PLM:         MSIM:\n"
         << "    --------   ---------  ------- ----------  ----------- ---------- ---------- ---------- ----------  --------  ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
FC_Stream& ALM_OduFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
    theStream  << itsSignalType;

	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );
	///*itsOccurTime = *itsDbOccurTime; 

	// Write the Signal Protect defect status table into the stream.
    theStream.write_array( itsSigProtStatus, itsSigProtNumberOfFailure);

    // Write the remaining Signal Protect data.
    theStream  << itsSigProtMatePort;
    theStream  << itsSigProtMatePortType;
    theStream  << itsSigProtMateStartChannel;

    return theStream;
}


FC_Stream& ALM_OduFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    theStream  >> itsSignalType;

    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = *itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    // Read its Signal Protect defect status table from the stream.
    theStream.read_array( itsSigProtStatus, itsSigProtNumberOfFailure);

    // Read the remaining Signal Protect data.
    theStream  >> itsSigProtMatePort;
    theStream  >> itsSigProtMatePortType;
    theStream  >> itsSigProtMateStartChannel;

    return theStream;
}

//##ModelId=3C506C3801DB
ostream& ALM_OduFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_ODU]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_ODU]);
    theStream   << FC_InsertVar(itsStatus[GENAIS_ODU]);
    theStream   << FC_InsertVar(itsStatus[AIS_ODU]);
    theStream   << FC_InsertVar(itsStatus[LOFLOM_ODU]);
    theStream   << FC_InsertVar(itsStatus[TIM_ODU]);
    theStream   << FC_InsertVar(itsStatus[TIM_NSA_ODU]);
    theStream   << FC_InsertVar(itsStatus[PLM_ODU]);
    theStream   << FC_InsertVar(itsStatus[LCK_ODU]);
    theStream   << FC_InsertVar(itsStatus[OCI_ODU]);
    theStream   << FC_InsertVar(itsStatus[BER_ODU]);
    theStream   << FC_InsertVar(itsStatus[BDI_ODU]);
    theStream   << FC_InsertVar(itsStatus[MSIM_ODU]);
    theStream   << FC_InsertVar(itsStatus[LOOMFI_ODU]);
    theStream   << FC_InsertVar(itsStatus[SSF_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[GENAIS_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[LOFLOM_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_NSA_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[PLM_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[LCK_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[OCI_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[BER_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[BDI_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[MSIM_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[LOOMFI_ODU]);
    theStream   << FC_InsertVar(itsOccurTime[SSF_ODU]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_PROTNA]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_FOP_PM]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_FOP_NR]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_ODUKP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_ODUKP_PROTNA]);
    theStream   << FC_InsertVar(itsSigProtMatePort);
    theStream   << FC_InsertVar(itsSigProtMatePortType);
    theStream   << FC_InsertVar(itsSigProtMateStartChannel);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3801E5
istream& ALM_OduFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsSignalType);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[GENAIS_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[LOFLOM_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_NSA_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[PLM_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[LCK_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[OCI_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[BER_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[BDI_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[MSIM_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[LOOMFI_ODU]);
    theStream   >> FC_ExtractVar(itsStatus[SSF_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[GENAIS_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOFLOM_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_NSA_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[PLM_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[LCK_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[OCI_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[BER_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[BDI_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[MSIM_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOOMFI_ODU]);
    theStream   >> FC_ExtractVar(itsOccurTime[SSF_ODU]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_PROTNA]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_FOP_PM]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_FOP_NR]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_ODUKP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_ODUKP_PROTNA]);
    theStream   >> FC_ExtractVar(itsSigProtMatePort);
    theStream   >> FC_ExtractVar(itsSigProtMatePortType);
    theStream   >> FC_ExtractVar(itsSigProtMateStartChannel);
    return theStream;
}
