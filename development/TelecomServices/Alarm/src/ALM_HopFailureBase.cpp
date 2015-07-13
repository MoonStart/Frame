/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the failure type of HOP (High Order
                Path) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_HopFailureBase.h"


//--------------------------------------------------------------------------

ALM_HopFailureBase::ALM_HopFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus, ALM_SP_NB_OF_DEFECT)
{
}

//--------------------------------------------------------------------------

ALM_HopFailureBase::~ALM_HopFailureBase()
{
}


//--------------------------------------------------------------------------

int ALM_HopFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_HOP:  aFailureIndex = UPPER_SA_HOP;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_HOP: aFailureIndex = UPPER_NSA_HOP; break;
        case CT_TelAlarmCondition::ALM_AIS_HOP:       aFailureIndex = AIS_HOP;       break;
        case CT_TelAlarmCondition::ALM_LOP_HOP:       aFailureIndex = LOP_HOP;       break;
        case CT_TelAlarmCondition::ALM_UNEQ_HOP:      aFailureIndex = UNEQ_HOP;      break;
        case CT_TelAlarmCondition::ALM_PLM_HOP:       aFailureIndex = PLM_HOP;       break;
        case CT_TelAlarmCondition::ALM_RDI_HOP:       aFailureIndex = RDI_HOP;       break;
        case CT_TelAlarmCondition::ALM_SFBER_HOP:     aFailureIndex = SFBER_HOP;     break;
        case CT_TelAlarmCondition::ALM_SDBER_HOP:     aFailureIndex = SDBER_HOP;     break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid HOP Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C3601FA
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_HopFailureBase::GetTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_HOP:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_HOP;  break;
        case UPPER_NSA_HOP: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_HOP; break;
        case AIS_HOP:       aFailureType = CT_TelAlarmCondition::ALM_AIS_HOP;       break;
        case LOP_HOP:       aFailureType = CT_TelAlarmCondition::ALM_LOP_HOP;       break;
        case UNEQ_HOP:      aFailureType = CT_TelAlarmCondition::ALM_UNEQ_HOP;      break;
        case PLM_HOP:       aFailureType = CT_TelAlarmCondition::ALM_PLM_HOP;       break;
        case RDI_HOP:       aFailureType = CT_TelAlarmCondition::ALM_RDI_HOP;       break;
        case SFBER_HOP:     aFailureType = CT_TelAlarmCondition::ALM_SFBER_HOP;     break;
        case SDBER_HOP:     aFailureType = CT_TelAlarmCondition::ALM_SDBER_HOP;     break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid HOP index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
int ALM_HopFailureBase::GetSigProtIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the Signal Protect defect type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_SP_NOT_SA:       aFailureIndex = SP_NOT_SERVICE_AFFECTING; break;
        case CT_TelAlarmCondition::ALM_SP_STRM_A_NR:    aFailureIndex = SP_STREAM_ALM_NR;         break;
        case CT_TelAlarmCondition::ALM_SP_ALM_MATE_ID:  aFailureIndex = SP_ALM_W_MATE_ID;         break;
        case CT_TelAlarmCondition::ALM_SP_PROTNA_UID:   aFailureIndex = SP_PROTNA;                break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_HopFailureBase::GetSigProtTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the Signal Protect defect type corresponding to the index
    switch(theIndex)
    {
        case SP_NOT_SERVICE_AFFECTING:  aFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA;      break;
        case SP_STREAM_ALM_NR:          aFailureType = CT_TelAlarmCondition::ALM_SP_STRM_A_NR;   break;
        case SP_ALM_W_MATE_ID:          aFailureType = CT_TelAlarmCondition::ALM_SP_ALM_MATE_ID; break;
        case SP_PROTNA:                 aFailureType = CT_TelAlarmCondition::ALM_SP_PROTNA_UID;  break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C360203
void ALM_HopFailureBase::PrintHeader() const
{
    /*
    fc_cout << endl
         << "----------------------------------------------------------------------\n"
         << "UP_SA_HOP:  UP_NSA_HOP: AIS_HOP:    RDI_HOP:    SFBER_HOP:  SDBER_HOP: \n"
         << "---------- ---------- ---------- ---------- ---------- ----------\n"
         << "# f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC): f ft(UTC):\n";
     */

         //  0000000001111111111222222222233333333334444444444555555555566666666667777777777888888888899999999990
         //  1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
    fc_cout << endl
         << "------------------------------------------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:    AIS:       LOP:       UNEQ       PLM        RDI:       SFBER:     SDBER:\n"
         << "    ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n";

}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
FC_Stream& ALM_HopFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
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


FC_Stream& ALM_HopFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = *itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    // Read its Signal Protect defect status table from the stream.
    theStream.read_array( itsSigProtStatus, itsSigProtNumberOfFailure);

    // Read the remaining Signal Protect data.
    theStream  >> itsSigProtMatePort;
    theStream  >> itsSigProtMatePortType;
    theStream  >> itsSigProtMateStartChannel;

    return theStream;
}

//##ModelId=3C506C36020C
ostream& ALM_HopFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_HOP]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_HOP]);
    theStream   << FC_InsertVar(itsStatus[AIS_HOP]);
    theStream   << FC_InsertVar(itsStatus[LOP_HOP]);
    theStream   << FC_InsertVar(itsStatus[UNEQ_HOP]);
    theStream   << FC_InsertVar(itsStatus[PLM_HOP]);
    theStream   << FC_InsertVar(itsStatus[RDI_HOP]);
    theStream   << FC_InsertVar(itsStatus[SFBER_HOP]);
    theStream   << FC_InsertVar(itsStatus[SDBER_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[LOP_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[UNEQ_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[PLM_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[RDI_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[SFBER_HOP]);
    theStream   << FC_InsertVar(itsOccurTime[SDBER_HOP]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_STREAM_ALM_NR]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_ALM_W_MATE_ID]);
    theStream   << FC_InsertVar(itsSigProtStatus[SP_PROTNA]);
    theStream   << FC_InsertVar(itsSigProtMatePort);
    theStream   << FC_InsertVar(itsSigProtMatePortType);
    theStream   << FC_InsertVar(itsSigProtMateStartChannel);

    return theStream;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C360216
istream& ALM_HopFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[LOP_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[UNEQ_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[PLM_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[RDI_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[SFBER_HOP]);
    theStream   >> FC_ExtractVar(itsStatus[SDBER_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOP_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[UNEQ_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[PLM_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[RDI_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[SFBER_HOP]);
    theStream   >> FC_ExtractVar(itsOccurTime[SDBER_HOP]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_NOT_SERVICE_AFFECTING]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_STREAM_ALM_NR]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_ALM_W_MATE_ID]);
    theStream   >> FC_ExtractVar(itsSigProtStatus[SP_PROTNA]);
    theStream   >> FC_ExtractVar(itsSigProtMatePort);
    theStream   >> FC_ExtractVar(itsSigProtMatePortType);
    theStream   >> FC_ExtractVar(itsSigProtMateStartChannel);

    return theStream;
}
