/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     RCMM
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the failure type of OCH (Optical 
                Channel) layer specific to the RCMM.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_OchRcmmFailureBase.h"


//--------------------------------------------------------------------------
ALM_OchRcmmFailureBase::ALM_OchRcmmFailureBase(int theIndex, bool theDefaultStatus):
           ALM_FailureBase(theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
ALM_OchRcmmFailureBase::~ALM_OchRcmmFailureBase()
{
}

//--------------------------------------------------------------------------
int ALM_OchRcmmFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex = ALM_INVALID_FAILURE;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
		case CT_TelAlarmCondition::ALM_LOS_OCH:     aFailureIndex = LOS_OCH;
			 break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OCH Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OchRcmmFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType = CT_TelAlarmCondition::ALM_INVALID_ALARM;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
		case LOS_OCH:   aFailureType = CT_TelAlarmCondition::ALM_LOS_OCH;
			 break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OCH Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
void ALM_OchRcmmFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------\n"
         << "    LOS_OCHL:  \n"
         << "    ---------- \n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
ostream& ALM_OchRcmmFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
	theStream   << FC_InsertVar(itsStatus[LOS_OCH]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_OCH]);
    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_OchRcmmFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[LOS_OCH]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_OCH]);
    return theStream;
}

