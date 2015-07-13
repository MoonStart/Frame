/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     SSM
 DESCRIPTION:   This class defines the failure type of MAC layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_MacFailureBase.h"

//--------------------------------------------------------------------------
ALM_MacFailureBase::ALM_MacFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus, ALM_SP_NB_OF_DEFECT),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{
}

//--------------------------------------------------------------------------
ALM_MacFailureBase::~ALM_MacFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_MacFailureBase::GetSignalType() const
{
    return itsSignalType;
}
 
//--------------------------------------------------------------------------
void ALM_MacFailureBase::SetSignalType(int signalType)
{
     itsSignalType = signalType;
}

//--------------------------------------------------------------------------
int ALM_MacFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_MAC:  aFailureIndex = UPPER_SA_MAC;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_MAC: aFailureIndex = UPPER_NSA_MAC; break;
        case CT_TelAlarmCondition::ALM_LACPFAIL_MAC:  aFailureIndex = LACPFAIL_MAC;  break;
        case CT_TelAlarmCondition::ALM_RFLINKFAIL_MAC:aFailureIndex = RFLINKFAIL_MAC;break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid MAC Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_MacFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_MAC:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_MAC;  break;
        case UPPER_NSA_MAC: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_MAC; break;
        case LACPFAIL_MAC:  aFailureType = CT_TelAlarmCondition::ALM_LACPFAIL_MAC;  break;
        case RFLINKFAIL_MAC:aFailureType = CT_TelAlarmCondition::ALM_RFLINKFAIL_MAC;break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid MAC Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
int ALM_MacFailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex = ALM_INVALID_FAILURE;

    // return the index coresponding to the Signal Protect defect type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_SP_NOT_SA: aFailureIndex = SP_NOT_SERVICE_AFFECTING; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_MacFailureBase::GetSigProtTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType = CT_TelAlarmCondition::ALM_INVALID_ALARM;
    
    //return the Signal Protect defect type corresponding to the index
    switch(theIndex)
    {
        case SP_NOT_SERVICE_AFFECTING: aFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_MacFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------------------------------------\n"
         << "    UPPER SA   UPPER NSA   LACPF:    RFLINK  \n"
         << "    --------   ---------  -------- ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
FC_Stream& ALM_MacFailureBase::WriteObjectBinary (FC_Stream& theStream)
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

FC_Stream& ALM_MacFailureBase::ReadObjectBinary (FC_Stream& theStream) 
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

//--------------------------------------------------------------------------
ostream& ALM_MacFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_MAC]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_MAC]);
    theStream   << FC_InsertVar(itsStatus[LACPFAIL_MAC]);
    theStream   << FC_InsertVar(itsStatus[RFLINKFAIL_MAC]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_MAC]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_MAC]);
    theStream   << FC_InsertVar(itsOccurTime[LACPFAIL_MAC]);
    theStream   << FC_InsertVar(itsOccurTime[RFLINKFAIL_MAC]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtMatePort);
    theStream   << FC_InsertVar(itsSigProtMatePortType);
    theStream   << FC_InsertVar(itsSigProtMateStartChannel);
    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_MacFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsSignalType);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_MAC]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_MAC]);
    theStream   >> FC_ExtractVar(itsStatus[LACPFAIL_MAC]);
    theStream   >> FC_ExtractVar(itsStatus[RFLINKFAIL_MAC]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_MAC]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_MAC]);
    theStream   >> FC_ExtractVar(itsOccurTime[LACPFAIL_MAC]);
    theStream   >> FC_ExtractVar(itsOccurTime[RFLINKFAIL_MAC]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtMatePort);
    theStream   >> FC_ExtractVar(itsSigProtMatePortType);
    theStream   >> FC_ExtractVar(itsSigProtMateStartChannel);
    return theStream;
}
