/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     
 DESCRIPTION:   This class defines the failure type of OMS (Optical
                Multiplex Section) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_OmsFailureBase.h"


//--------------------------------------------------------------------------

//##ModelId=3E7765010307
ALM_OmsFailureBase::ALM_OmsFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------

//##ModelId=3E7765010312
ALM_OmsFailureBase::~ALM_OmsFailureBase()
{
}

//--------------------------------------------------------------------------

//##ModelId=3E7765010314
int ALM_OmsFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_AOPE_OMS: aFailureIndex = AOPE_OMS;
            break;
        case CT_TelAlarmCondition::ALM_OPOVLD_OMS: aFailureIndex = OPOVLD_OMS;
            break;
        case CT_TelAlarmCondition::ALM_LOS_OMS: aFailureIndex = LOS_OMS;
            break;
        case CT_TelAlarmCondition::ALM_LOSINT_OMS: aFailureIndex = LOSINT_OMS;
            break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OMS Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------

//##ModelId=3E7765010325
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OmsFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case AOPE_OMS:   aFailureType = CT_TelAlarmCondition::ALM_AOPE_OMS;
            break;
        case OPOVLD_OMS:   aFailureType = CT_TelAlarmCondition::ALM_OPOVLD_OMS;
            break;
        case LOS_OMS:   aFailureType = CT_TelAlarmCondition::ALM_LOS_OMS;
            break;
        case LOSINT_OMS:   aFailureType = CT_TelAlarmCondition::ALM_LOSINT_OMS;
            break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OMS Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3E776501032F
void ALM_OmsFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "------------------------------------------------\n"
         << "    AOPE:       OPOVLD:    LOS:       LOSINT:\n"
         << "    ----------  ---------- ---------- ----------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3E7765010331
ostream& ALM_OmsFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[AOPE_OMS]);
    theStream   << FC_InsertVar(itsStatus[OPOVLD_OMS]);
    theStream   << FC_InsertVar(itsStatus[LOS_OMS]);
    theStream   << FC_InsertVar(itsStatus[LOSINT_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[AOPE_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[OPOVLD_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[LOSINT_OMS]);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3E7765010343
istream& ALM_OmsFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[AOPE_OMS]);
    theStream   >> FC_ExtractVar(itsStatus[OPOVLD_OMS]);
    theStream   >> FC_ExtractVar(itsStatus[LOS_OMS]);
    theStream   >> FC_ExtractVar(itsStatus[LOSINT_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[AOPE_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[OPOVLD_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOSINT_OMS]);
    return theStream;
}
