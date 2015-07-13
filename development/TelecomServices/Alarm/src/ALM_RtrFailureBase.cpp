/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     Controller (SPM)
 AUTHOR   :     Michael Sharkey
 DESCRIPTION:   This class defines the failure type of Router layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_RtrFailureBase.h"

//--------------------------------------------------------------------------
ALM_RtrFailureBase::ALM_RtrFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
ALM_RtrFailureBase::~ALM_RtrFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_RtrFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_RTR_DOWN:      aFailureIndex = RTR_DOWN;      break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid RTR Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_RtrFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case RTR_DOWN:  aFailureType = CT_TelAlarmCondition::ALM_RTR_DOWN;  break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid RTR Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_RtrFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------\n"
         << "    RTR DOWN : \n"
         << "    ---------- \n";
}

//--------------------------------------------------------------------------
FC_Stream& ALM_RtrFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );
	//*itsOccurTime = *itsDbOccurTime; 

    return theStream;
}

//--------------------------------------------------------------------------
FC_Stream& ALM_RtrFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = *itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    return theStream;
}

//--------------------------------------------------------------------------
ostream& ALM_RtrFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[RTR_DOWN]);
    theStream   << FC_InsertVar(itsOccurTime[RTR_DOWN]);
    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_RtrFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[RTR_DOWN]);
    theStream   >> FC_ExtractVar(itsOccurTime[RTR_DOWN]);
    return theStream;
}
