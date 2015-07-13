/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of OPT (Optical)
                layer.
--------------------------------------------------------------------------*/

//#include "BaseClass/FC_TextStream.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_OptFailureBase.h"


//--------------------------------------------------------------------------
//##ModelId=3C506C38007D
ALM_OptFailureBase::ALM_OptFailureBase (int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus, ALM_SP_NB_OF_DEFECT),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{
}

//--------------------------------------------------------------------------
//##ModelId=3C506C380088
ALM_OptFailureBase::~ALM_OptFailureBase()
{
}

/**
 * Method used to get the signal type currently associated to the port
 */
inline int ALM_OptFailureBase::GetSignalType() const
{
    return itsSignalType;
}

/**
 * Method used to set the signal type currently associated to the port
 */
inline void ALM_OptFailureBase::SetSignalType(int signalType)
{
     itsSignalType = signalType;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C38008A
int ALM_OptFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_OPT:  aFailureIndex = UPPER_SA_OPT;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_OPT: aFailureIndex = UPPER_NSA_OPT; break;
        case CT_TelAlarmCondition::ALM_LOS_OPT:       aFailureIndex = LOS_OPT;       break;
        case CT_TelAlarmCondition::ALM_SWTH_OPT:      aFailureIndex = SWTH_OPT;      break;
        case CT_TelAlarmCondition::ALM_LOC_OPT:       aFailureIndex = LOC_OPT;       break;
        case CT_TelAlarmCondition::ALM_MFA_OPT:       aFailureIndex = MFA_OPT;       break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OPT Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C380093
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OptFailureBase::GetTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_OPT:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_OPT;  break;
        case UPPER_NSA_OPT: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_OPT; break;
        case LOS_OPT:       aFailureType = CT_TelAlarmCondition::ALM_LOS_OPT;       break;
        case SWTH_OPT:      aFailureType = CT_TelAlarmCondition::ALM_SWTH_OPT;      break;
        case LOC_OPT:       aFailureType = CT_TelAlarmCondition::ALM_LOC_OPT;       break;
        case MFA_OPT:       aFailureType = CT_TelAlarmCondition::ALM_MFA_OPT;       break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid OPT Index.");
            break;
    }

    return aFailureType;
}

//--------------------------------------------------------------------------
int ALM_OptFailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the Signal Protect defect type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_SP_NOT_SA:       aFailureIndex = SP_NOT_SERVICE_AFFECTING; break;
        case CT_TelAlarmCondition::ALM_SP_PROTNA_UID:   aFailureIndex = SP_PROTNA; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_OptFailureBase::GetSigProtTypeFromIndex( int theIndex) const
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
//##ModelId=3C506C3800A5
void ALM_OptFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "---------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:    LOS:       SW THRESH: LOC:       MFA:  \n"
         << "    ---------- ---------- ---------- ---------- ---------- ----------\n";
}

//--------------------------------------------------------------------------
FC_Stream& ALM_OptFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
    // Write the signal type
    theStream  << itsSignalType;

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


FC_Stream& ALM_OptFailureBase::ReadObjectBinary (FC_Stream& theStream)
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

    theStream  >> itsSigProtMatePort;
    theStream  >> itsSigProtMatePortType;
    theStream  >> itsSigProtMateStartChannel;

    return theStream;
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3C506C3800A7
ostream& ALM_OptFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_OPT]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_OPT]);
    theStream   << FC_InsertVar(itsStatus[LOS_OPT]);
    theStream   << FC_InsertVar(itsStatus[SWTH_OPT]);
    theStream   << FC_InsertVar(itsStatus[LOC_OPT]);
    theStream   << FC_InsertVar(itsStatus[MFA_OPT]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_OPT]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_OPT]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_OPT]);
    theStream   << FC_InsertVar(itsOccurTime[SWTH_OPT]);
    theStream   << FC_InsertVar(itsOccurTime[LOC_OPT]);
    theStream   << FC_InsertVar(itsOccurTime[MFA_OPT]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_PROTNA]);
    theStream   << FC_InsertVar(itsSigProtMatePort);
    theStream   << FC_InsertVar(itsSigProtMatePortType);
    theStream   << FC_InsertVar(itsSigProtMateStartChannel);
    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3C506C3800B1
istream& ALM_OptFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsSignalType);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_OPT]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_OPT]);
    theStream   >> FC_ExtractVar(itsStatus[LOS_OPT]);
    theStream   >> FC_ExtractVar(itsStatus[SWTH_OPT]);
    theStream   >> FC_ExtractVar(itsStatus[LOC_OPT]);
    theStream   >> FC_ExtractVar(itsStatus[MFA_OPT]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_OPT]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_OPT]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_OPT]);
    theStream   >> FC_ExtractVar(itsOccurTime[SWTH_OPT]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOC_OPT]);
    theStream   >> FC_ExtractVar(itsOccurTime[MFA_OPT]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_PROTNA]);
    theStream   >> FC_ExtractVar(itsSigProtMatePort);
    theStream   >> FC_ExtractVar(itsSigProtMatePortType);
    theStream   >> FC_ExtractVar(itsSigProtMateStartChannel);
    return theStream;
}
