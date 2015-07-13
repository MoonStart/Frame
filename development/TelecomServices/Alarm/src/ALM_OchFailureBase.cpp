/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OCH (Optical 
                Channel) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_OchFailureBase.h"


//--------------------------------------------------------------------------
//##ModelId=3C506C3802EB
ALM_OchFailureBase::ALM_OchFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3802F6
ALM_OchFailureBase::~ALM_OchFailureBase()
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3802FE
int ALM_OchFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
		case CT_TelAlarmCondition::ALM_DTD_OCH:     aFailureIndex = DTD_OCH;
			 break;
	
		case CT_TelAlarmCondition::ALM_LOS_OCH:     aFailureIndex = LOS_OCH;
			 break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OCH Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C380308
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OchFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case DTD_OCH:   aFailureType = CT_TelAlarmCondition::ALM_DTD_OCH;
			 break;
		
		case LOS_OCH:   aFailureType = CT_TelAlarmCondition::ALM_LOS_OCH;
			 break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OCH Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C380312
void ALM_OchFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "-------------------------\n"
         << "    LOS_OCHL:  DTD_OCH:  \n"
         << "    ---------- ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3C506C380314
ostream& ALM_OchFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
	theStream   << FC_InsertVar(itsStatus[LOS_OCH]);
    theStream   << FC_InsertVar(itsStatus[DTD_OCH]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_OCH]);
    theStream   << FC_InsertVar(itsOccurTime[DTD_OCH]);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C38031D
istream& ALM_OchFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[LOS_OCH]);
	theStream   >> FC_ExtractVar(itsStatus[DTD_OCH]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_OCH]);
    theStream   >> FC_ExtractVar(itsOccurTime[DTD_OCH]);
    return theStream;
}
