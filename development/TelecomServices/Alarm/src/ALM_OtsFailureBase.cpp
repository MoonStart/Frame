/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OTS (Optical
                Transport Section) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_OtsFailureBase.h"


//--------------------------------------------------------------------------
//##ModelId=3C506C3701DB
ALM_OtsFailureBase::ALM_OtsFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3701E5
ALM_OtsFailureBase::~ALM_OtsFailureBase()
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3701E7
int ALM_OtsFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex = ALM_INVALID_FAILURE;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_LOS_OTS: aFailureIndex = LOS_OTS;   break;
        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OTS Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3701F0
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OtsFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType = CT_TelAlarmCondition::ALM_INVALID_ALARM;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case LOS_OTS:   aFailureType = CT_TelAlarmCondition::ALM_LOS_OTS;       break;
        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OTS Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3701FA
void ALM_OtsFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "--------------\n"
         << "    LOS-OTS:   \n"
         << "    ---------- \n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3C506C370202
ostream& ALM_OtsFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[LOS_OTS]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_OTS]);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C37020C
istream& ALM_OtsFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[LOS_OTS]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_OTS]);
    return theStream;
}
