/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Xinlun Fang
 DESCRIPTION:   This class defines the failure type of ODU-TCM
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_TcmFailureBase.h"

//--------------------------------------------------------------------------
//##ModelId=3C506C3801B3
ALM_TcmFailureBase::ALM_TcmFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus, ALM_SP_NB_OF_DEFECT),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3801BD
ALM_TcmFailureBase::~ALM_TcmFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_TcmFailureBase::GetSignalType() const
{
    return itsSignalType;
}
 
//--------------------------------------------------------------------------
void ALM_TcmFailureBase::SetSignalType(int signalType)
{
     itsSignalType = signalType;
}

//--------------------------------------------------------------------------
int ALM_TcmFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_TCM:  aFailureIndex = UPPER_SA_Tcm;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_TCM: aFailureIndex = UPPER_NSA_Tcm; break;
        case CT_TelAlarmCondition::ALM_AIS_TCM: aFailureIndex = AIS_Tcm;    break;
        case CT_TelAlarmCondition::ALM_TIM_TCM: aFailureIndex = TIM_Tcm;    break;
        case CT_TelAlarmCondition::ALM_TIM_NSA_TCM: aFailureIndex = TIM_NSA_Tcm;    break;
        case CT_TelAlarmCondition::ALM_LTC_TCM: aFailureIndex = LTC_Tcm;    break;
        case CT_TelAlarmCondition::ALM_LCK_TCM: aFailureIndex = LCK_Tcm;    break;
        case CT_TelAlarmCondition::ALM_OCI_TCM: aFailureIndex = OCI_Tcm;    break;
        case CT_TelAlarmCondition::ALM_BER_TCM: aFailureIndex = BER_Tcm;    break;
        case CT_TelAlarmCondition::ALM_BDI_TCM: aFailureIndex = BDI_Tcm;    break;
        case CT_TelAlarmCondition::ALM_LTC_NSA_TCM: aFailureIndex = LTC_NSA_Tcm; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid TCM Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_TcmFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_Tcm:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_TCM;  break;
        case UPPER_NSA_Tcm: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_TCM; break;
        case AIS_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_AIS_TCM;   break;
        case TIM_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_TIM_TCM;   break;
        case TIM_NSA_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_TIM_NSA_TCM;   break;
        case LTC_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_LTC_TCM;   break;
        case LCK_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_LCK_TCM;   break;
        case OCI_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_OCI_TCM;   break;
        case BER_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_BER_TCM;   break;
        case BDI_Tcm:   aFailureType = CT_TelAlarmCondition::ALM_BDI_TCM;   break;
        case LTC_NSA_Tcm: aFailureType = CT_TelAlarmCondition::ALM_LTC_NSA_TCM; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid TCM Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
int ALM_TcmFailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex = ALM_INVALID_FAILURE;

    // return the index coresponding to the Signal Protect defect type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_SP_NOT_SA:       aFailureIndex = SP_NOT_SERVICE_AFFECTING; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_TcmFailureBase::GetSigProtTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType = CT_TelAlarmCondition::ALM_INVALID_ALARM;
    
    //return the Signal Protect defect type corresponding to the index
    switch(theIndex)
    {
        case SP_NOT_SERVICE_AFFECTING:  aFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA;      break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_TcmFailureBase::PrintHeader() const
{
    fc_cout << endl   
         << "------------------------------------------------------------------------------------------------------\n"
         << "    UPPER SA   UPPER NSA  LTC:       AIS:       LCK:       OCI:       TIM:       BER:       BDI:      \n"
         << "    --------   ---------  ------- ----------  ----------- ---------- ---------- ----------  ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
FC_Stream& ALM_TcmFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
    theStream  << itsSignalType;
    //theStream  << myTcmLevel;

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


FC_Stream& ALM_TcmFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    theStream  >> itsSignalType;
    //theStream  >> myTcmLevel;

    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
    uint32 itsDbOccurTime = (uint32)*itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    // Read its Signal Protect defect status table from the stream.
    theStream.read_array( itsSigProtStatus, itsSigProtNumberOfFailure);

    // Read the remaining Signal Protect data.
    theStream  >> itsSigProtMatePort;
    theStream  >> itsSigProtMatePortType;
    theStream  >> itsSigProtMateStartChannel;

    return theStream;
}

//--------------------------------------------------------------------------
ostream& ALM_TcmFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    //theStream   << FC_InsertVar(myTcmLevel);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_Tcm]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_Tcm]);
    theStream   << FC_InsertVar(itsStatus[AIS_Tcm]);
    theStream   << FC_InsertVar(itsStatus[TIM_Tcm]);
    theStream   << FC_InsertVar(itsStatus[TIM_NSA_Tcm]);
    theStream   << FC_InsertVar(itsStatus[LTC_Tcm]);
    theStream   << FC_InsertVar(itsStatus[LTC_NSA_Tcm]);
    theStream   << FC_InsertVar(itsStatus[LCK_Tcm]);
    theStream   << FC_InsertVar(itsStatus[OCI_Tcm]);
    theStream   << FC_InsertVar(itsStatus[BER_Tcm]);
    theStream   << FC_InsertVar(itsStatus[BDI_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_NSA_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[LTC_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[LTC_NSA_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[LCK_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[OCI_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[BER_Tcm]);
    theStream   << FC_InsertVar(itsOccurTime[BDI_Tcm]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtMatePort);
    theStream   << FC_InsertVar(itsSigProtMatePortType);
    theStream   << FC_InsertVar(itsSigProtMateStartChannel);
    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_TcmFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsSignalType);
    //theStream   >> FC_ExtractVar(myTcmLevel);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_NSA_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[LTC_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[LTC_NSA_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[LCK_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[OCI_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[BER_Tcm]);
    theStream   >> FC_ExtractVar(itsStatus[BDI_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_NSA_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[LTC_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[LTC_NSA_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[LCK_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[OCI_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[BER_Tcm]);
    theStream   >> FC_ExtractVar(itsOccurTime[BDI_Tcm]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtMatePort);
    theStream   >> FC_ExtractVar(itsSigProtMatePortType);
    theStream   >> FC_ExtractVar(itsSigProtMateStartChannel);
    return theStream;
}
