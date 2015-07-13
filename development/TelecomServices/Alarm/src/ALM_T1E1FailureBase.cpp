/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the failure type T1E1 (bits clock)
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_T1E1FailureBase.h"


//--------------------------------------------------------------------------
ALM_T1E1FailureBase::ALM_T1E1FailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
ALM_T1E1FailureBase::~ALM_T1E1FailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_T1E1FailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_LOS_T1E1:       aFailureIndex = LOS_T1E1;       break;
        case CT_TelAlarmCondition::ALM_AIS_T1E1:       aFailureIndex = AIS_T1E1;       break;
        case CT_TelAlarmCondition::ALM_LOF_T1E1:       aFailureIndex = LOF_T1E1;       break;
        case CT_TelAlarmCondition::ALM_FREQOFF_T1E1:   aFailureIndex = FREQOFF_T1E1;   break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid T1E1 Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_T1E1FailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case LOS_T1E1:       aFailureType = CT_TelAlarmCondition::ALM_LOS_T1E1;       break;
        case AIS_T1E1:       aFailureType = CT_TelAlarmCondition::ALM_AIS_T1E1;       break;
        case LOF_T1E1:       aFailureType = CT_TelAlarmCondition::ALM_LOF_T1E1;       break;
        case FREQOFF_T1E1:   aFailureType = CT_TelAlarmCondition::ALM_FREQOFF_T1E1;   break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid T1E1 Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_T1E1FailureBase::PrintHeader() const
{
    fc_cout << endl
         << "-------------------------------------\n"
         << "    LOS:       AIS:        LOF:\n"
         << "    ---------- ----------  ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
ostream& ALM_T1E1FailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[LOS_T1E1]);
    theStream   << FC_InsertVar(itsStatus[AIS_T1E1]);
    theStream   << FC_InsertVar(itsStatus[LOF_T1E1]);
    theStream   << FC_InsertVar(itsStatus[FREQOFF_T1E1]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_T1E1]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_T1E1]);
    theStream   << FC_InsertVar(itsOccurTime[LOF_T1E1]);
    theStream   << FC_InsertVar(itsOccurTime[FREQOFF_T1E1]);
    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_T1E1FailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[LOS_T1E1]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_T1E1]);
    theStream   >> FC_ExtractVar(itsStatus[LOF_T1E1]);
    theStream   >> FC_ExtractVar(itsStatus[FREQOFF_T1E1]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_T1E1]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_T1E1]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOF_T1E1]);
    theStream   >> FC_ExtractVar(itsOccurTime[FREQOFF_T1E1]);
    return theStream;
}
