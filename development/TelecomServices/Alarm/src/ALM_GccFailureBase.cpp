/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     
 AUTHOR   :     xinlun fang
 DESCRIPTION:   This class defines the failure type of GCC link layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_GccFailureBase.h"

//--------------------------------------------------------------------------
ALM_GCCFailureBase::ALM_GCCFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{
}

//--------------------------------------------------------------------------
ALM_GCCFailureBase::~ALM_GCCFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_GCCFailureBase::GetSignalType() const
{
    return itsSignalType;
}

//--------------------------------------------------------------------------
void ALM_GCCFailureBase::SetSignalType(int signalType)
{
    itsSignalType = signalType;
}

//--------------------------------------------------------------------------
int ALM_GCCFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_GCC:     aFailureIndex = UPPER_SA_GCC;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_GCC:    aFailureIndex = UPPER_NSA_GCC; break;
        case CT_TelAlarmCondition::ALM_GCC_LINK_INCMPLT: aFailureIndex = GCC_LINK_INCMPLT; break;
        case CT_TelAlarmCondition::ALM_GCC_LINK_DOWN:    aFailureIndex = GCC_LINK_DOWN; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid GCC Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_GCCFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_GCC:     aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_GCC;  break;
        case UPPER_NSA_GCC:    aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_GCC; break;
        case GCC_LINK_INCMPLT: aFailureType = CT_TelAlarmCondition::ALM_GCC_LINK_INCMPLT; break;
        case GCC_LINK_DOWN:    aFailureType = CT_TelAlarmCondition::ALM_GCC_LINK_DOWN; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid GCC Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_GCCFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "------------------------------------\n"
         << "    UP_SA:     UP_NSA:    LINK DOWN:\n"
         << "    ---------- ---------- ----------\n";
}

//--------------------------------------------------------------------------
FC_Stream& ALM_GCCFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
    // Write the signal type
    theStream  << itsSignalType;

	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );
	//*itsOccurTime = *itsDbOccurTime; 

    return theStream;
}

//--------------------------------------------------------------------------
FC_Stream& ALM_GCCFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read the signal type
    theStream  >> itsSignalType;

    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = (uint32)(*itsOccurTime);
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    return theStream;
}

//--------------------------------------------------------------------------
ostream& ALM_GCCFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_GCC]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_GCC]);
    theStream   << FC_InsertVar(itsStatus[GCC_LINK_INCMPLT]);
    theStream   << FC_InsertVar(itsStatus[GCC_LINK_DOWN]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_GCC]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_GCC]);
    theStream   << FC_InsertVar(itsOccurTime[GCC_LINK_INCMPLT]);
    theStream   << FC_InsertVar(itsOccurTime[GCC_LINK_DOWN]);
    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_GCCFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsSignalType);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_GCC]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_GCC]);
    theStream   >> FC_ExtractVar(itsStatus[GCC_LINK_INCMPLT]);
    theStream   >> FC_ExtractVar(itsStatus[GCC_LINK_DOWN]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_GCC]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_GCC]);
    theStream   >> FC_ExtractVar(itsOccurTime[GCC_LINK_INCMPLT]);
    theStream   >> FC_ExtractVar(itsOccurTime[GCC_LINK_DOWN]);
    return theStream;
}
