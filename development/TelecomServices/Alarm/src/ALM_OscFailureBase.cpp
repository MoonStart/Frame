/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OSC (Optical
                Supervisory Channel) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_OscFailureBase.h"


//--------------------------------------------------------------------------
//##ModelId=3C506C370306
ALM_OscFailureBase::ALM_OscFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C370311
ALM_OscFailureBase::~ALM_OscFailureBase()
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C370313
int ALM_OscFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_TIM_OTS:   aFailureIndex = TIM_OTS;   break;
        case CT_TelAlarmCondition::ALM_PMI_OTS:   aFailureIndex = PMI_OTS;   break;
        case CT_TelAlarmCondition::ALM_BDI_OTS:   aFailureIndex = BDI_OTS;   break;
        case CT_TelAlarmCondition::ALM_BDIO_OTS:  aFailureIndex = BDIO_OTS;  break;
        case CT_TelAlarmCondition::ALM_BDIP_OTS:  aFailureIndex = BDIP_OTS;  break;
        case CT_TelAlarmCondition::ALM_FDIO_OMS:  aFailureIndex = FDIO_OMS;  break;
        case CT_TelAlarmCondition::ALM_FDIP_OMS:  aFailureIndex = FDIP_OMS;  break;
        case CT_TelAlarmCondition::ALM_PMI_OMS:   aFailureIndex = PMI_OMS;   break;
      //case CT_TelAlarmCondition::ALM_BDIO_OMS:  aFailureIndex = BDIO_OMS;  break;
      //case CT_TelAlarmCondition::ALM_BDIP_OMS:  aFailureIndex = BDIP_OMS;  break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OSC Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C37031C
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OscFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case TIM_OTS:   aFailureType = CT_TelAlarmCondition::ALM_TIM_OTS;   break;
        case PMI_OTS:   aFailureType = CT_TelAlarmCondition::ALM_PMI_OTS;   break;     
        case BDI_OTS:   aFailureType = CT_TelAlarmCondition::ALM_BDI_OTS;   break;
        case BDIO_OTS:  aFailureType = CT_TelAlarmCondition::ALM_BDIO_OTS;  break;
        case BDIP_OTS:  aFailureType = CT_TelAlarmCondition::ALM_BDIP_OTS;  break;
        case FDIO_OMS:  aFailureType = CT_TelAlarmCondition::ALM_FDIO_OMS;  break;
        case FDIP_OMS:  aFailureType = CT_TelAlarmCondition::ALM_FDIP_OMS;  break;
        case PMI_OMS:   aFailureType = CT_TelAlarmCondition::ALM_PMI_OMS;   break;
      //case BDIO_OMS:  aFailureType = CT_TelAlarmCondition::ALM_BDIO_OMS;  break;
      //case BDIP_OMS:  aFailureType = CT_TelAlarmCondition::ALM_BDIP_OMS;  break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OSC Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C370327
void ALM_OscFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "--------------------------------------------------------------------------------------------\n" //-----------------------\n"
         << "     TIM-OTS:   PMI-OTS:   BDI-OTS:   BDIO-OTS:  BDIP-OTS:  FDIO-OMS:  FDIP-OMS:  PMI-OMS:  \n" //  BDIO-OMS:  BDIP-OMS: \n"
         << "     ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n" //  ---------- ----------\n"
         << "  #  f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC):\n";//                       \n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3C506C37032F
ostream& ALM_OscFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[TIM_OTS]);
    theStream   << FC_InsertVar(itsStatus[PMI_OTS]);
    theStream   << FC_InsertVar(itsStatus[BDI_OTS]);
    theStream   << FC_InsertVar(itsStatus[BDIO_OTS]);
    theStream   << FC_InsertVar(itsStatus[BDIP_OTS]);
    theStream   << FC_InsertVar(itsStatus[FDIO_OMS]);
    theStream   << FC_InsertVar(itsStatus[FDIP_OMS]);
    theStream   << FC_InsertVar(itsStatus[PMI_OMS]);
  //theStream   << FC_InsertVar(itsStatus[BDIO_OMS]);
  //theStream   << FC_InsertVar(itsStatus[BDIP_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_OTS]);
    theStream   << FC_InsertVar(itsOccurTime[PMI_OTS]);
    theStream   << FC_InsertVar(itsOccurTime[BDI_OTS]);
    theStream   << FC_InsertVar(itsOccurTime[BDIO_OTS]);
    theStream   << FC_InsertVar(itsOccurTime[BDIP_OTS]);
    theStream   << FC_InsertVar(itsOccurTime[FDIO_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[FDIP_OMS]);
    theStream   << FC_InsertVar(itsOccurTime[PMI_OMS]);
  //theStream   << FC_InsertVar(itsOccurTime[BDIO_OMS]);
  //theStream   << FC_InsertVar(itsOccurTime[BDIP_OMS]);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C37033A
istream& ALM_OscFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[TIM_OTS]);
    theStream   >> FC_ExtractVar(itsStatus[PMI_OTS]);
    theStream   >> FC_ExtractVar(itsStatus[BDI_OTS]);
    theStream   >> FC_ExtractVar(itsStatus[BDIO_OTS]);
    theStream   >> FC_ExtractVar(itsStatus[BDIP_OTS]);
    theStream   >> FC_ExtractVar(itsStatus[FDIO_OMS]);
    theStream   >> FC_ExtractVar(itsStatus[FDIP_OMS]);
    theStream   >> FC_ExtractVar(itsStatus[PMI_OMS]);
  //theStream   >> FC_ExtractVar(itsStatus[BDIO_OMS]);
  //theStream   >> FC_ExtractVar(itsStatus[BDIP_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_OTS]);
    theStream   >> FC_ExtractVar(itsOccurTime[PMI_OTS]);
    theStream   >> FC_ExtractVar(itsOccurTime[BDI_OTS]);
    theStream   >> FC_ExtractVar(itsOccurTime[BDIO_OTS]);
    theStream   >> FC_ExtractVar(itsOccurTime[BDIP_OTS]);
    theStream   >> FC_ExtractVar(itsOccurTime[FDIO_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[FDIP_OMS]);
    theStream   >> FC_ExtractVar(itsOccurTime[PMI_OMS]);
  //theStream   >> FC_ExtractVar(itsOccurTime[BDIO_OMS]);
  //theStream   >> FC_ExtractVar(itsOccurTime[BDIP_OMS]);
    return theStream;
}
