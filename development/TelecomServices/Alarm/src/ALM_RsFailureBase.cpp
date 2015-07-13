/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class defines the failure type of RS (Regenerator
                Section) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

#include "../ALM_RsFailureBase.h"


//--------------------------------------------------------------------------
//##ModelId=3F954C31035F
ALM_RsFailureBase::ALM_RsFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus),
    itsSignalType (CT_TEL_SIGNAL_UNKNOWN)
{

}

//--------------------------------------------------------------------------
//##ModelId=3F954C310362
ALM_RsFailureBase::~ALM_RsFailureBase()
{
}

/**
 * Method used to get the signal type currently associated to the port
 */
inline int ALM_RsFailureBase::GetSignalType() const
{
    return itsSignalType;
}

/**
 * Method used to set the signal type currently associated to the port
 */
inline void ALM_RsFailureBase::SetSignalType(int signalType)
{
     itsSignalType = signalType;
}

//--------------------------------------------------------------------------
//##ModelId=3F954C31036E
int ALM_RsFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_RS:  aFailureIndex = UPPER_SA_RS;  break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_RS: aFailureIndex = UPPER_NSA_RS; break;      
        case CT_TelAlarmCondition::ALM_UPPER_INT_SA_RS: aFailureIndex = UPPER_INT_SA_RS; break;
        case CT_TelAlarmCondition::ALM_AIS_TX_RS:    aFailureIndex = AIS_TX_RS;    break;
        case CT_TelAlarmCondition::ALM_LOS_RS:       aFailureIndex = LOS_RS;       break;
        case CT_TelAlarmCondition::ALM_TAIS_RS:      aFailureIndex = TAIS_RS;      break;
        case CT_TelAlarmCondition::ALM_LOF_RS:       aFailureIndex = LOF_RS;       break;
        case CT_TelAlarmCondition::ALM_LOF_INT_RS:   aFailureIndex = LOF_INT_RS;   break;
        case CT_TelAlarmCondition::ALM_TIM_RS:       aFailureIndex = TIM_RS;       break;
        case CT_TelAlarmCondition::ALM_TIM_NSA_RS:   aFailureIndex = TIM_NSA_RS;   break;
        case CT_TelAlarmCondition::ALM_LF_RS:        aFailureIndex = LF_RS;        break;
        case CT_TelAlarmCondition::ALM_RF_RS:        aFailureIndex = RF_RS;        break;
        case CT_TelAlarmCondition::ALM_CSF_OPU_RS:   aFailureIndex = CSF_OPU_RS;   break;
        case CT_TelAlarmCondition::ALM_GENAIS_RS: aFailureIndex = GEN_AIS_RS; break;
        case CT_TelAlarmCondition::ALM_GENAIS_INT_RS: aFailureIndex = GEN_AIS_INT_RS; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid RS Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------
//##ModelId=3F954C310371
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_RsFailureBase::GetTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_RS:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_RS;  break;
        case UPPER_NSA_RS: aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_RS; break;
        case UPPER_INT_SA_RS: aFailureType = CT_TelAlarmCondition::ALM_UPPER_INT_SA_RS; break;
        case AIS_TX_RS:    aFailureType = CT_TelAlarmCondition::ALM_AIS_TX_RS;    break;
        case LOS_RS:       aFailureType = CT_TelAlarmCondition::ALM_LOS_RS;       break;
        case TAIS_RS:      aFailureType = CT_TelAlarmCondition::ALM_TAIS_RS;      break;
        case LOF_RS:       aFailureType = CT_TelAlarmCondition::ALM_LOF_RS;       break;
        case LOF_INT_RS:   aFailureType = CT_TelAlarmCondition::ALM_LOF_INT_RS;   break;
        case TIM_RS:       aFailureType = CT_TelAlarmCondition::ALM_TIM_RS;       break;
        case TIM_NSA_RS:   aFailureType = CT_TelAlarmCondition::ALM_TIM_NSA_RS;   break;
        case LF_RS:        aFailureType = CT_TelAlarmCondition::ALM_LF_RS;        break;
        case RF_RS:        aFailureType = CT_TelAlarmCondition::ALM_RF_RS;        break;
        case CSF_OPU_RS:   aFailureType = CT_TelAlarmCondition::ALM_CSF_OPU_RS;   break;
        case GEN_AIS_RS: aFailureType = CT_TelAlarmCondition::ALM_GENAIS_RS; break;
        case GEN_AIS_INT_RS: aFailureType = CT_TelAlarmCondition::ALM_GENAIS_INT_RS; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid RS index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------
//##ModelId=3F954C310374
void ALM_RsFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "----------------------------------------------------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:    AIS_TX     LOS:       TAIS:      LOF:        RF:        LF:        TIM:     CSF-OPU   \n"
         << "    ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ------- ------------\n";
}

//--------------------------------------------------------------------------
FC_Stream& ALM_RsFailureBase::WriteObjectBinary (FC_Stream& theStream)
{
    // Write the signal type
    theStream  <<  itsSignalType;

	// Write the failure status table into the stream.
    theStream.write_array( itsStatus, itsNumberOfFailure);

	// Write the failure occurring time table into the stream.
	uint32* itsDbOccurTime = (uint32*)itsOccurTime;
    theStream.write_array( itsDbOccurTime, itsNumberOfFailure );
	//*itsOccurTime = *itsDbOccurTime; 

    return theStream;
}


FC_Stream& ALM_RsFailureBase::ReadObjectBinary (FC_Stream& theStream) 
{
    // Read the signal type
    theStream  >> itsSignalType;

    // Read its failure status table from the stream.
    theStream.read_array( itsStatus, itsNumberOfFailure );

    // Read its failure occurring time table from the stream.
	uint32 itsDbOccurTime = *itsOccurTime;
    theStream.read_array( &itsDbOccurTime, itsNumberOfFailure );

    return theStream;
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------
//##ModelId=3F954C31037D
ostream& ALM_RsFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsSignalType);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_RS]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_RS]);
    theStream   << FC_InsertVar(itsStatus[UPPER_INT_SA_RS]);
    theStream   << FC_InsertVar(itsStatus[AIS_TX_RS]);
    theStream   << FC_InsertVar(itsStatus[LOS_RS]);
    theStream   << FC_InsertVar(itsStatus[TAIS_RS]);
    theStream   << FC_InsertVar(itsStatus[LOF_RS]);
    theStream   << FC_InsertVar(itsStatus[LOF_INT_RS]);
    theStream   << FC_InsertVar(itsStatus[RF_RS]);
    theStream   << FC_InsertVar(itsStatus[LF_RS]);
    theStream   << FC_InsertVar(itsStatus[TIM_RS]);
    theStream   << FC_InsertVar(itsStatus[TIM_NSA_RS]);
    theStream   << FC_InsertVar(itsStatus[CSF_OPU_RS]);
    theStream   << FC_InsertVar(itsStatus[GEN_AIS_RS]);
    theStream   << FC_InsertVar(itsStatus[GEN_AIS_INT_RS]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_RS]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_RS]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_INT_SA_RS]);
    theStream   << FC_InsertVar(itsOccurTime[AIS_TX_RS]);
    theStream   << FC_InsertVar(itsOccurTime[LOS_RS]);
    theStream   << FC_InsertVar(itsOccurTime[TAIS_RS]);
    theStream   << FC_InsertVar(itsOccurTime[LOF_RS]);
    theStream   << FC_InsertVar(itsOccurTime[LOF_INT_RS]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_RS]);
    theStream   << FC_InsertVar(itsOccurTime[TIM_NSA_RS]);
    theStream   << FC_InsertVar(itsOccurTime[CSF_OPU_RS]);
    theStream   << FC_InsertVar(itsOccurTime[GEN_AIS_RS]);
    theStream   << FC_InsertVar(itsOccurTime[GEN_AIS_INT_RS]);

    return theStream;
}

//--------------------------------------------------------------------------
//##ModelId=3F954C310380
istream& ALM_RsFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsSignalType);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_RS]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_RS]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_INT_SA_RS]);
    theStream   >> FC_ExtractVar(itsStatus[AIS_TX_RS]);
    theStream   >> FC_ExtractVar(itsStatus[LOS_RS]);
    theStream   >> FC_ExtractVar(itsStatus[TAIS_RS]);
    theStream   >> FC_ExtractVar(itsStatus[LOF_RS]);
    theStream   >> FC_ExtractVar(itsStatus[LOF_INT_RS]);
    theStream   >> FC_ExtractVar(itsStatus[RF_RS]);
    theStream   >> FC_ExtractVar(itsStatus[LF_RS]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_RS]);
    theStream   >> FC_ExtractVar(itsStatus[TIM_NSA_RS]);
    theStream   >> FC_ExtractVar(itsStatus[CSF_OPU_RS]);
    theStream   >> FC_ExtractVar(itsStatus[GEN_AIS_RS]);
    theStream   >> FC_ExtractVar(itsStatus[GEN_AIS_INT_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_INT_SA_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[AIS_TX_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOS_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[TAIS_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOF_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOF_INT_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[TIM_NSA_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[CSF_OPU_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[GEN_AIS_RS]);
    theStream   >> FC_ExtractVar(itsOccurTime[GEN_AIS_INT_RS]);

    return theStream;
}

