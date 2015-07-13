//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_SyncProt.h"
#include "../CFG_Definitions.h"
#include "ErrorService/FC_Error.h"
#include "CommonTypes/CT_SystemIds.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Telecom.h>

using namespace std;


CFG_SyncProt::CFG_SyncProt(uint32 theIndex):
    CFG_Object(theIndex)
{
    // Reset.
    Reset();
}

CFG_SyncProt::~CFG_SyncProt(void)
{
    // Nothing to do for now.

}


void CFG_SyncProt::SetTimingReference(CT_TEL_ClkSelRef theTimingReference)
{
    myTimingReference = theTimingReference;
    itsReady          = true;
}

CT_TEL_ClkSelRef CFG_SyncProt::GetTimingReference() const
{
    return myTimingReference;
}


void CFG_SyncProt::SetActiveRefId(CT_IntfId theActiveRefId)
{
    myActiveRefId     = theActiveRefId;
    itsReady          = true;
}

CT_IntfId CFG_SyncProt::GetActiveRefId() const
{
    return myActiveRefId;
}


void CFG_SyncProt::SetSelectedRefSSM(CT_FAC_RxSsm theSelectedRefSSM)
{
    mySelectedRefSSM  = theSelectedRefSSM;
    itsReady          = true;
}

CT_FAC_RxSsm CFG_SyncProt::GetSelectedRefSSM() const
{
    return mySelectedRefSSM;
}


/*
void CFG_SyncProt::HwRefresh(void)
{
    // Skip this if not ready.
    // After a warm restart, signal protection is not ready yet.
    // Keep the value already present.
    if (!itsReady) return;

    CT_SlotId slotId;


    // Determine slot identifier.
    slotId = itsContext->GetCardId();


    // Refresh the hardware related to facility config object according
    // to current configuration within this object.


    // Update the egress K1 and K2 values.
    gPortConfigHwInd->SetEgressTransportOverheadByte(UNUSED_SHELF_NUMBER, slotId,
                                                     itsPortNumber,
                                                     CT_TEL_TOH_REGISTER,
                                                     CT_TEL_K1K2_BYTES,
                                                     myEgressK1Value,
                                                     myEgressK2Value);

    // Update the egress E2 value.
    gPortConfigHwInd->SetEgressTransportOverheadByte(UNUSED_SHELF_NUMBER, slotId,
                                                     itsPortNumber,
                                                     CT_TEL_TOH_REGISTER,
                                                     CT_TEL_E2_BYTE,
                                                     myEgressE2Value);

}
*/

void CFG_SyncProt::Reset(void)
{
    // Initialize all attributes to default values.
    myTimingReference   = CT_TEL_CLKSEL_REF_INTERNAL;
    itsReady            = false;
    myActiveRefId       = CT_INTF_ID_UNKNOWN;
    mySelectedRefSSM    = CT_TEL_SUPPORTED_INTERNAL_SSM;

}

ostream& CFG_SyncProt::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    uint32 aTimingReference = (uint32) myTimingReference;
    theStream   << FC_InsertVar(aTimingReference);

    uint32 aActiveRefId = (uint32) myActiveRefId;
    theStream   << FC_InsertVar(aActiveRefId);

    uint32 aSelectedRefSSM = (uint32) mySelectedRefSSM;
    theStream   << FC_InsertVar(aSelectedRefSSM);

    theStream   << FC_InsertVar(itsReady);
//    theStream   << FC_InsertVar(itsPortNumber);

    return theStream;

}

istream& CFG_SyncProt::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint32 aTimingReference = 0;
    theStream   >> FC_ExtractVar(aTimingReference);
    myTimingReference = (CT_TEL_ClkSelRef) aTimingReference;

    uint32 aActiveRefId = 0;
    theStream   >> FC_ExtractVar(aActiveRefId);
    myActiveRefId = (CT_IntfId) aActiveRefId;

    uint32 aSelectedRefSSM = 0;
    theStream   >> FC_ExtractVar(aSelectedRefSSM);
    mySelectedRefSSM = (CT_FAC_RxSsm) aSelectedRefSSM;

    theStream   >> FC_ExtractVar(itsReady);
//    theStream   >> FC_ExtractVar(itsPortNumber);

    return theStream;

}

FC_Stream& CFG_SyncProt::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    uint32 aTimingReference = (uint32) myTimingReference;
    theStream   << aTimingReference;

    uint32 aActiveRefId = (uint32) myActiveRefId;
    theStream   << aActiveRefId;

    uint32 aSelectedRefSSM = (uint32) mySelectedRefSSM;
    theStream   << aSelectedRefSSM;

    theStream   << itsReady;

    return theStream;

}

FC_Stream& CFG_SyncProt::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint32 aTimingReference = 0;
    theStream   >> aTimingReference;
    myTimingReference = (CT_TEL_ClkSelRef)aTimingReference;

    uint32 aActiveRefId = 0;
    theStream   >> aActiveRefId;
    myActiveRefId = (CT_IntfId)aActiveRefId;

    uint32 aSelectedRefSSM = 0;
    theStream   >> aSelectedRefSSM;
    mySelectedRefSSM = (CT_FAC_RxSsm)aSelectedRefSSM;

    uint8  ready = 0;
    theStream   >> ready;
    // Conversion to custom type.
    itsReady = (ready == 1) ? true : false;

    return theStream;

}

FC_CmdProcessor::STATUS CFG_SyncProt::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto SYNCPROTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"tmgref"))
    {
        SetTimingReference(CFG_STRING_TO_TIMING_REF(argv[1]));
    }
    else
    {
        goto SYNCPROTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

SYNCPROTERROR:
    {
        fc_cout << "sync <tmgref> <p-rimary|s-econdary|i-nternal>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_SyncProt::Display( FC_Stream& theStream )
{
    theStream   << "SYNC PROT  - Timing Reference    [tmgref]     = " << DISPLAY_CLKSEL_REF(myTimingReference) << endl;
}

