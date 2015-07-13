/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Patrick Meehan
 DESCRIPTION:   This class defines the failure type of GFP (Generic
                Framing Procedure) layer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_GfpFailureBase.h"


//--------------------------------------------------------------------------

ALM_GfpFailureBase::ALM_GfpFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------

ALM_GfpFailureBase::~ALM_GfpFailureBase()
{
}

//--------------------------------------------------------------------------

int ALM_GfpFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_UPPER_SA_GFP:   aFailureIndex = UPPER_SA_GFP;   break;
        case CT_TelAlarmCondition::ALM_UPPER_NSA_GFP:  aFailureIndex = UPPER_NSA_GFP;  break;
        case CT_TelAlarmCondition::ALM_UPPER_INT_SA_GFP:  aFailureIndex = UPPER_INT_SA_GFP;  break;
        case CT_TelAlarmCondition::ALM_LOFD_GFP:       aFailureIndex = LOFD_GFP;       break;
        case CT_TelAlarmCondition::ALM_PLM_GFP:        aFailureIndex = PLM_GFP;        break;
        case CT_TelAlarmCondition::ALM_CSF_LOS_GFP:    aFailureIndex = CSF_LOS_GFP;    break;
        case CT_TelAlarmCondition::ALM_CSF_LOSYNC_GFP: aFailureIndex = CSF_LOSYNC_GFP; break;
        case CT_TelAlarmCondition::ALM_CSF_FEFI_GFP:   aFailureIndex = CSF_FEFI_GFP;   break;
        case CT_TelAlarmCondition::ALM_CSF_FDI_GFP:    aFailureIndex = CSF_FDI_GFP;    break;
        case CT_TelAlarmCondition::ALM_CSF_RDI_GFP:    aFailureIndex = CSF_RDI_GFP;    break;
        case CT_TelAlarmCondition::ALM_LOA_GFP:        aFailureIndex = LOA_GFP;        break;
        case CT_TelAlarmCondition::ALM_SQM_GFP:        aFailureIndex = SQM_GFP;        break;
        case CT_TelAlarmCondition::ALM_CHEC_GFP:       aFailureIndex = CHEC_GFP;       break;
        case CT_TelAlarmCondition::ALM_PLI_GFP:        aFailureIndex = PLI_GFP;        break;
        case CT_TelAlarmCondition::ALM_RMTLF_GFP:      aFailureIndex = RMTLF_GFP;      break;
        case CT_TelAlarmCondition::ALM_AUTONEGFAIL_GFP:aFailureIndex = AUTONEGFAIL_GFP;break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid GFP Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------

CT_TelAlarmCondition::CT_FacilityAlarmType ALM_GfpFailureBase::GetTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case UPPER_SA_GFP:   aFailureType = CT_TelAlarmCondition::ALM_UPPER_SA_GFP;   break;
        case UPPER_NSA_GFP:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_NSA_GFP;  break;
        case UPPER_INT_SA_GFP:  aFailureType = CT_TelAlarmCondition::ALM_UPPER_INT_SA_GFP;  break;
        case LOFD_GFP:       aFailureType = CT_TelAlarmCondition::ALM_LOFD_GFP;       break;
        case PLM_GFP:        aFailureType = CT_TelAlarmCondition::ALM_PLM_GFP;        break;
        case CSF_LOS_GFP:    aFailureType = CT_TelAlarmCondition::ALM_CSF_LOS_GFP;    break;
        case CSF_LOSYNC_GFP: aFailureType = CT_TelAlarmCondition::ALM_CSF_LOSYNC_GFP; break;
        case CSF_FEFI_GFP:   aFailureType = CT_TelAlarmCondition::ALM_CSF_FEFI_GFP;   break;
        case CSF_FDI_GFP:    aFailureType = CT_TelAlarmCondition::ALM_CSF_FDI_GFP;    break;
        case CSF_RDI_GFP:    aFailureType = CT_TelAlarmCondition::ALM_CSF_RDI_GFP;    break;
        case LOA_GFP:        aFailureType = CT_TelAlarmCondition::ALM_LOA_GFP;        break;
        case SQM_GFP:        aFailureType = CT_TelAlarmCondition::ALM_SQM_GFP;        break;
        case CHEC_GFP:       aFailureType = CT_TelAlarmCondition::ALM_CHEC_GFP;       break;
        case PLI_GFP:        aFailureType = CT_TelAlarmCondition::ALM_PLI_GFP;        break;
        case RMTLF_GFP:      aFailureType = CT_TelAlarmCondition::ALM_RMTLF_GFP;      break;
        case AUTONEGFAIL_GFP: aFailureType = CT_TelAlarmCondition::ALM_AUTONEGFAIL_GFP; break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid GFP index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------

void ALM_GfpFailureBase::PrintHeader() const
{
    fc_cout << endl
         << "-----------------------------------------------------------------------------------------\n"
         << "    UP_SA:     UP_NSA:   UP_INT_SA:  LOFD:      PLM:      CSFLOS:    CSFLOSYNC:    CSFFDI:    CSFRDI\n"
         << "    ---------- ---------- ---------- ---------- ----------    -------    ----------------\n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------

//##ModelId=3C506C36020C
ostream& ALM_GfpFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[UPPER_SA_GFP]);
    theStream   << FC_InsertVar(itsStatus[UPPER_NSA_GFP]);
    theStream   << FC_InsertVar(itsStatus[UPPER_INT_SA_GFP]);
    theStream   << FC_InsertVar(itsStatus[LOFD_GFP]);
    theStream   << FC_InsertVar(itsStatus[PLM_GFP]);
    theStream   << FC_InsertVar(itsStatus[CSF_LOS_GFP]);
    theStream   << FC_InsertVar(itsStatus[CSF_LOSYNC_GFP]);
    theStream   << FC_InsertVar(itsStatus[CSF_FEFI_GFP]);
    theStream   << FC_InsertVar(itsStatus[CSF_FDI_GFP]);
    theStream   << FC_InsertVar(itsStatus[CSF_RDI_GFP]);
    theStream   << FC_InsertVar(itsStatus[LOA_GFP]);
    theStream   << FC_InsertVar(itsStatus[SQM_GFP]);
    theStream   << FC_InsertVar(itsStatus[CHEC_GFP]);
    theStream   << FC_InsertVar(itsStatus[PLI_GFP]);
    theStream   << FC_InsertVar(itsStatus[RMTLF_GFP]);
    theStream   << FC_InsertVar(itsStatus[AUTONEGFAIL_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_SA_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_NSA_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[UPPER_INT_SA_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[LOFD_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[PLM_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[CSF_LOS_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[CSF_LOSYNC_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[CSF_FEFI_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[CSF_FDI_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[CSF_RDI_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[LOA_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[SQM_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[CHEC_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[PLI_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[RMTLF_GFP]);
    theStream   << FC_InsertVar(itsOccurTime[AUTONEGFAIL_GFP]);

    return theStream;
}

//--------------------------------------------------------------------------

//##ModelId=3C506C360216
istream& ALM_GfpFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_SA_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_NSA_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[UPPER_INT_SA_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[LOFD_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[PLM_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[CSF_LOS_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[CSF_LOSYNC_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[CSF_FEFI_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[CSF_FDI_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[CSF_RDI_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[LOA_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[SQM_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[CHEC_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[PLI_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[RMTLF_GFP]);
    theStream   >> FC_ExtractVar(itsStatus[AUTONEGFAIL_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_SA_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_NSA_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[UPPER_INT_SA_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOFD_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[PLM_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[CSF_LOS_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[CSF_LOSYNC_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[CSF_FEFI_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[CSF_FDI_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[CSF_RDI_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[LOA_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[SQM_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[CHEC_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[PLI_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[RMTLF_GFP]);
    theStream   >> FC_ExtractVar(itsOccurTime[AUTONEGFAIL_GFP]);

    return theStream;
}
