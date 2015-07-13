/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class defines the failure type of MS (Regenerator
                Section) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_MsFailureBase.h"


//--------------------------------------------------------------------------

//##ModelId=3C506C3601E4
ALM_MsFailureBase::ALM_MsFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus, ALM_SP_NB_OF_DEFECT),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{
}

//--------------------------------------------------------------------------

//##ModelId=3C506C3601EF
ALM_MsFailureBase::~ALM_MsFailureBase()
{
}

/**
 * Method used to get the signal type currently associated to the port
 */
int ALM_MsFailureBase::GetSignalType() const
{
    return itsSignalType;
}

/**
 * Method used to set the signal type currently associated to the port
 */
void ALM_MsFailureBase::SetSignalType(int signalType)
{
     itsSignalType = signalType;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C3601F7
int ALM_MsFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_MS:  aFailureIndex = UPPER_SA_MS;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_MS: aFailureIndex = UPPER_NSA_MS; break;
        case CT_TelAlarmCondition::ALM_UPPER_INT_SA_RS: aFailureIndex = UPPER_INT_SA_MS; break;
        case CT_TelAlarmCondition::ALM_AIS_INT_MS:   aFailureIndex = AIS_INT_MS;   break;
        case CT_TelAlarmCondition::ALM_AIS_MS:       aFailureIndex = AIS_MS;       break;
        case CT_TelAlarmCondition::ALM_RDI_MS:       aFailureIndex = RDI_MS;       break;
        case CT_TelAlarmCondition::ALM_SFBER_MS:     aFailureIndex = SFBER_MS;     break;
        case CT_TelAlarmCondition::ALM_SDBER_MS:     aFailureIndex = SDBER_MS;     break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid MS Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C3601FA
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_MsFailureBase::GetTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_MS:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_MS;  break;
        case UPPER_NSA_MS: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_MS; break;
        case UPPER_INT_SA_MS: aFailureType = CT_TelAlarmCondition::ALM_UPPER_INT_SA_RS; break;
        case AIS_INT_MS:   aFailureType = CT_TelAlarmCondition::ALM_AIS_INT_MS;   break;
        case AIS_MS:       aFailureType = CT_TelAlarmCondition::ALM_AIS_MS;       break;
        case RDI_MS:       aFailureType = CT_TelAlarmCondition::ALM_RDI_MS;       break;
        case SFBER_MS:     aFailureType = CT_TelAlarmCondition::ALM_SFBER_MS;     break;
        case SDBER_MS:     aFailureType = CT_TelAlarmCondition::ALM_SDBER_MS;     break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid MS index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
int ALM_MsFailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the Signal Protect defect type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_SP_NOT_SA:       aFailureIndex = SP_NOT_SERVICE_AFFECTING; break;
        case CT_TelAlarmCondition::ALM_SP_PROTNA_UID:   aFailureIndex = SP_PROTNA;                break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_MsFailureBase::GetSigProtTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the Signal Protect defect type corresponding to the index
    switch(theIndex)
    {
        case SP_NOT_SERVICE_AFFECTING:  aFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA;      break;
        case SP_PROTNA:                 aFailureType = CT_TelAlarmCondition::ALM_SP_PROTNA_UID;  break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}


//--------------------------------------------------------------------------

//##ModelId=3C506C360203
void ALM_MsFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:    AIS:       RDI:       SFBER:     SDBER: \n"
         << "    ---------- ---------- ---------- ---------- ---------- ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
FC_Stream& ALM_MsFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
    // Write the signal type
    theStream  <<  itsSignalType;

	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );
	//*itsOccurTime = *itsDbOccurTime; 

	// Write the Signal Protect defect status table into the stream.
    theStream.write_array( itsSigProtStatus, itsSigProtNumberOfFailure);

    // Write the remaining Signal Protect data.
    theStream  << itsSigProtMatePort;
    theStream  << itsSigProtMatePortType;
    theStream  << itsSigProtMateStartChannel;

    return theStream;
}


FC_Stream& ALM_MsFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read the signal type
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


//##ModelId=3C506C36020C
ostream& ALM_MsFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_MS]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_MS]);
    theStream   << FC_InsertVar(itsStatus[AIS_INT_MS]);
    theStream   << FC_InsertVar(itsStatus[AIS_MS]);
    theStream   << FC_InsertVar(itsStatus[RDI_MS]);
    theStream   << FC_InsertVar(itsStatus[SFBER_MS]);
    theStream   << FC_InsertVar(itsStatus[SDBER_MS]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_MS]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_MS]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_INT_MS]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_MS]);
    theStream   << FC_InsertVar(itsOccurTime[RDI_MS]);
    theStream   << FC_InsertVar(itsOccurTime[SFBER_MS]);
    theStream   << FC_InsertVar(itsOccurTime[SDBER_MS]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_PROTNA]);
    theStream   << FC_InsertVar(itsSigProtMatePort);
    theStream   << FC_InsertVar(itsSigProtMatePortType);
    theStream   << FC_InsertVar(itsSigProtMateStartChannel);

    return theStream;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C360216
istream& ALM_MsFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);    
    theStream   >> FC_ExtractVar(itsSignalType);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_MS]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_MS]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_INT_MS]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_MS]);
    theStream   >> FC_ExtractVar(itsStatus[RDI_MS]);
    theStream   >> FC_ExtractVar(itsStatus[SFBER_MS]);
    theStream   >> FC_ExtractVar(itsStatus[SDBER_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_INT_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[RDI_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[SFBER_MS]);
    theStream   >> FC_ExtractVar(itsOccurTime[SDBER_MS]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_PROTNA]);
    theStream   >> FC_ExtractVar(itsSigProtMatePort);
    theStream   >> FC_ExtractVar(itsSigProtMatePortType);
    theStream   >> FC_ExtractVar(itsSigProtMateStartChannel);

    return theStream;
}
