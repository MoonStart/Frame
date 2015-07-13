//Copyright(c) Tellabs Transport Group. All rights reserved

#include "CFG_MsProt.h"
#include "ErrorService/FC_Error.h"
#include "CommonTypes/CT_SystemIds.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>

using namespace std;


CFG_MsProt::CFG_MsProt(uint32 theIndex):
    CFG_Object(theIndex),
    //itsContext(NULL),
    myEgressK1Value(0),
    myEgressK2Value(0),
    myEgressCsi(0),
    itsReady(false),
    myMateIntfId(CT_INTF_ID_UNKNOWN)
    //itsPortNumber(theIndex)
{
    // Nothing to do for now.

}

CFG_MsProt::~CFG_MsProt(void)
{
    // Nothing to do for now.

}

//void CFG_MsProt::SetContext(T6700_OpmIf& theContext)
//{
//    itsContext = &theContext;
//
//}

void CFG_MsProt::SetEgressK1Value(uint8 theK1Value)
{
    myEgressK1Value  = theK1Value;
    itsReady         = true;

}

void CFG_MsProt::SetEgressK2Value(uint8 theK2Value)
{
    myEgressK2Value  = theK2Value;
    itsReady         = true;

}

void CFG_MsProt::SetEgressCsi(uint8 theCsi)
{
    myEgressCsi      = theCsi;
    itsReady         = true;

}

void CFG_MsProt::SetMateIntfId(CT_IntfId theIntfId)
{
    myMateIntfId = theIntfId;
}

uint8 CFG_MsProt::GetEgressK1Value(void)
{
    return myEgressK1Value;

}

uint8 CFG_MsProt::GetEgressK2Value(void)
{
    return myEgressK2Value;

}

uint8 CFG_MsProt::GetEgressCsi(void)
{
    return myEgressCsi;

}

CT_IntfId CFG_MsProt::GetMateIntfId(void)
{
    return myMateIntfId;
}

/*
void CFG_MsProt::HwRefresh(void)
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
                                                     ???myEgressCsi???

    // Update the egress E2 value.
    gPortConfigHwInd->SetEgressTransportOverheadByte(UNUSED_SHELF_NUMBER, slotId,
                                                     itsPortNumber,
                                                     CT_TEL_TOH_REGISTER,
                                                     CT_TEL_E2_BYTE,
                                                     myEgressE2Value);

}
*/

void CFG_MsProt::Reset(void)
{
    // Initialize all attributes to default values.
    myEgressK1Value = 0;
    myEgressK2Value = 0;
    myEgressCsi     = 0;
    itsReady        = false;
    myMateIntfId    = CT_INTF_ID_UNKNOWN;

}

ostream& CFG_MsProt::WriteObject( ostream& theStream )
{

    theStream   << FC_InsertVar(myEgressK1Value)
                << FC_InsertVar(myEgressK2Value)
                << FC_InsertVar(myEgressCsi)
                << FC_InsertVar(itsReady);
//                << FC_InsertVar(itsPortNumber);

    uint32 aMateIntfId = (uint32) myMateIntfId;
    theStream<<FC_InsertVar(aMateIntfId);

    return theStream;

}

istream& CFG_MsProt::ReadObject( istream& theStream )
{

    theStream   >> FC_ExtractVar(myEgressK1Value)
                >> FC_ExtractVar(myEgressK2Value)
                >> FC_ExtractVar(myEgressCsi)
                >> FC_ExtractVar(itsReady);
//                >> FC_ExtractVar(itsPortNumber);

    uint32 aMateIntfId = 0;
    theStream>>FC_ExtractVar(aMateIntfId);
    myMateIntfId = (CT_IntfId) aMateIntfId;

    return theStream;

}

FC_Stream& CFG_MsProt::WriteObjectBinary( FC_Stream& theStream )
{

    theStream   << myEgressK1Value
                << myEgressK2Value
                << myEgressCsi
                << itsReady;

    uint32 aMateIntfId = (uint32) myMateIntfId;
    theStream<<aMateIntfId;

    return theStream;

}

FC_Stream& CFG_MsProt::ReadObjectBinary( FC_Stream& theStream )
{
    uint8   ready;

    theStream   >> myEgressK1Value
                >> myEgressK2Value
                >> myEgressCsi
                >> ready;

    // Conversion to custom type.
    itsReady = (ready == 1) ? true : false;

    //conversion to custom type
    uint32 aMateIntfId = 0;
    theStream>>aMateIntfId;
    myMateIntfId = (CT_IntfId) aMateIntfId;

    return theStream;

}

FC_CmdProcessor::STATUS CFG_MsProt::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSPROTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"txk1"))
    {
        SetEgressK1Value((uint8)(atoi(argv[1])));
    }
    else if (!strcmp(aParam,"txk2"))
    {
        SetEgressK2Value((uint8)(atoi(argv[1])));
    }
    else if (!strcmp(aParam,"txcsi"))
    {
        SetEgressCsi((uint8)(atoi(argv[1])));
    }
    else
    {
        goto MSPROTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSPROTERROR:
    {
        fc_cout << "ms <txk1>  <1-byte integer value>" << endl;
        fc_cout << "ms <txk2>  <1-byte integer value>" << endl;
        fc_cout << "ms <txcsi> <1-byte integer value>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_MsProt::Display( FC_Stream& theStream )
{
    FC_FmtFlags previousFlags = fc_cout.Flags();

    fc_cout.Setf(ios::hex, ios::basefield);
    theStream   << "MS PROT  - Tx K1 Byte         [txk1]            = 0x" << (int)myEgressK1Value << endl;
    theStream   << "MS PROT  - Tx K2 Byte         [txk2]            = 0x" << (int)myEgressK2Value << endl;
    theStream   << "MS PROT  - Tx Csi Code        [txcsi]           = 0x" << (int)myEgressCsi << endl;
    fc_cout.Flags(previousFlags);
    theStream   << "MS PROT  - Mate Intf Id       [mateIntfId]      =" << DISPLAY_CT_IntfId(myMateIntfId) << endl;
}

