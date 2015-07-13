/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class defines the failure type of OCH layer within
                the OSC Channel) .
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_OchOscFailureBase.h"


//--------------------------------------------------------------------------

//##ModelId=3E77650202B8
ALM_OchOscFailureBase::ALM_OchOscFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------

//##ModelId=3E77650202C3
ALM_OchOscFailureBase::~ALM_OchOscFailureBase()
{
}

//--------------------------------------------------------------------------

//##ModelId=3E77650202CC
int ALM_OchOscFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
		case CT_TelAlarmCondition::ALM_OCI_OCH:     aFailureIndex = OCI_OCH;
			 break;
	
		case CT_TelAlarmCondition::ALM_FDIP_OCH:     aFailureIndex = FDIP_OCH;
			 break;
		
		case CT_TelAlarmCondition::ALM_FDIO_OCH:     aFailureIndex = FDIO_OCH;
			 break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OCH Failure type in the OSC.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------

//##ModelId=3E77650202D6
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OchOscFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case OCI_OCH:   aFailureType = CT_TelAlarmCondition::ALM_OCI_OCH;
			 break;
		
		case FDIP_OCH:   aFailureType = CT_TelAlarmCondition::ALM_FDIP_OCH;
			 break;

		case FDIO_OCH:   aFailureType = CT_TelAlarmCondition::ALM_FDIO_OCH;
			 break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OCH Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------

//##ModelId=3E77650202E0
void ALM_OchOscFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "------------------------------------ \n"
         << "    FDIO_OCH:  FDIP_OCH:   OCI_OCH:  \n"
         << "    ---------- ----------  ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------

//##ModelId=3E77650202E2
ostream& ALM_OchOscFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
	theStream   << FC_InsertVar(itsStatus[FDIO_OCH]);
	theStream   << FC_InsertVar(itsStatus[FDIP_OCH]);
    theStream   << FC_InsertVar(itsStatus[OCI_OCH]);
    theStream   << FC_InsertVar(itsOccurTime[FDIO_OCH]);
	theStream   << FC_InsertVar(itsOccurTime[FDIP_OCH]);
    theStream   << FC_InsertVar(itsOccurTime[OCI_OCH]);

    return theStream;
}

//--------------------------------------------------------------------------

//##ModelId=3E77650202F4
istream& ALM_OchOscFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[FDIO_OCH]);
	theStream   >> FC_ExtractVar(itsStatus[FDIP_OCH]);
    theStream   >> FC_ExtractVar(itsStatus[OCI_OCH]);
    theStream   >> FC_ExtractVar(itsOccurTime[FDIO_OCH]);
	theStream   >> FC_ExtractVar(itsOccurTime[FDIP_OCH]);
    theStream   >> FC_ExtractVar(itsOccurTime[OCI_OCH]);
    return theStream;
}
