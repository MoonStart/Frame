//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Mac.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Mac::CFG_Mac(uint32 theIndex):
    CFG_Object(theIndex),
    myAutoNeg(false),
    myEthernetRate(0),
    myDuplexMode(CT_TEL_MAC_DUPLEX_UNKNOWN),
    myAdvrtFlowCtrl(CT_TEL_MAC_ADFLW_UNKNOWN),
    myFlowControl(CT_TEL_MAC_FLW_UNKNOWN)
{
}

CFG_Mac::~CFG_Mac(void)
{
}


bool CFG_Mac::SetAutoNeg(bool theAutoNeg)
{
    bool hasChanged = (myAutoNeg != theAutoNeg);
    myAutoNeg = theAutoNeg;
    return hasChanged;
}

bool CFG_Mac::GetAutoNeg() const
{
    return myAutoNeg;
}

bool CFG_Mac::SetEthernetRate(CT_TEL_daHz theEthernetRate)
{
    bool hasChanged = (myEthernetRate != theEthernetRate);
    myEthernetRate = theEthernetRate;
    return hasChanged;
}

CT_TEL_daHz CFG_Mac::GetEthernetRate() const
{
    return myEthernetRate;
}

bool CFG_Mac::SetDuplexMode(CT_TEL_MAC_DUPLEX_MODE theDuplexMode)
{
    bool hasChanged = (myDuplexMode != theDuplexMode);
    myDuplexMode = theDuplexMode;
    return hasChanged;
}

CT_TEL_MAC_DUPLEX_MODE CFG_Mac::GetDuplexMode() const
{
    return myDuplexMode;
}

bool CFG_Mac::SetAdvrtFlowCtrl(CT_TEL_MAC_ADFLW_CTRL theAdvrtFlowCtrl)
{
    bool hasChanged = (myAdvrtFlowCtrl != theAdvrtFlowCtrl);
    myAdvrtFlowCtrl = theAdvrtFlowCtrl;
    return hasChanged;
}

CT_TEL_MAC_ADFLW_CTRL CFG_Mac::GetAdvrtFlowCtrl() const
{
    return myAdvrtFlowCtrl;
}

bool CFG_Mac::SetFlowControl(CT_TEL_MAC_FLOWCTRL theFlowControl)
{
    bool hasChanged = (myFlowControl != theFlowControl);
    myFlowControl = theFlowControl;
    return hasChanged;
}

CT_TEL_MAC_FLOWCTRL CFG_Mac::GetFlowControl() const
{
    return myFlowControl;
}

void CFG_Mac::Reset(void)
{
    // Initialize all attributes to default values.
    myAutoNeg = false;
    myEthernetRate = 0;
    myDuplexMode = CT_TEL_MAC_DUPLEX_UNKNOWN;
    myAdvrtFlowCtrl = CT_TEL_MAC_ADFLW_UNKNOWN;
    myFlowControl = CT_TEL_MAC_FLW_UNKNOWN;
}

ostream& CFG_Mac::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myAutoNeg);
    theStream   << FC_InsertVar(myEthernetRate);

    uint8  aTmp = (uint8) myDuplexMode;
    theStream   << FC_InsertVar(aTmp);
    aTmp = (uint8) myAdvrtFlowCtrl;
    theStream   << FC_InsertVar(aTmp);
    aTmp = (uint8) myFlowControl;
    theStream   << FC_InsertVar(aTmp);

    return theStream;
}

istream& CFG_Mac::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myAutoNeg);
    theStream   >> FC_ExtractVar(myEthernetRate);

    uint8  aTmp = 0;
    theStream   >> FC_ExtractVar(aTmp);
    myDuplexMode = (CT_TEL_MAC_DUPLEX_MODE) aTmp;
    theStream   >> FC_ExtractVar(aTmp);
    myAdvrtFlowCtrl = (CT_TEL_MAC_ADFLW_CTRL) aTmp;
    theStream   >> FC_ExtractVar(aTmp);
    myFlowControl = (CT_TEL_MAC_FLOWCTRL) aTmp;

    return theStream;
}

FC_Stream& CFG_Mac::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   <<  myAutoNeg;
    theStream   <<  myEthernetRate;
    theStream   <<  (uint8)myDuplexMode;
    theStream   <<  (uint8)myAdvrtFlowCtrl;
    theStream   <<  (uint8)myFlowControl;

    return theStream;
}

FC_Stream& CFG_Mac::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >>  myAutoNeg;
    theStream   >>  myEthernetRate;

    uint8  aTmp = 0;
    theStream   >>  aTmp;
    myDuplexMode = (CT_TEL_MAC_DUPLEX_MODE) aTmp;
    theStream   >>  aTmp;
    myAdvrtFlowCtrl = (CT_TEL_MAC_ADFLW_CTRL) aTmp;
    theStream   >>  aTmp;
    myFlowControl = (CT_TEL_MAC_FLOWCTRL) aTmp;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Mac::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"autoneg",7))
    {
        SetAutoNeg(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"ethrate",7))
    {
        SetEthernetRate(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"duplex",6))
    {
        SetDuplexMode(CFG_STRING_TO_DUPLEX_MD(argv[1]));
    }
    else if (!strncmp(aParam,"adflw",5))
    {
        SetAdvrtFlowCtrl(CFG_STRING_TO_ADVT_FLWCTRL(argv[1]));
    }
    else if (!strncmp(aParam,"flwctl",6))
    {
        SetFlowControl(CFG_STRING_TO_FLOWCTRL(argv[1]));
    }   
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "MAC <autoneg>    <e-nable|d-isable> " << endl;
        fc_cout << "MAC <ethrate>    <rate (daHz)>" << endl;
        fc_cout << "MAC <duplex>     <full|half> " << endl;
        fc_cout << "MAC <adflw>      <nopause|spause|apause|bpause> " << endl;
        fc_cout << "MAC <flwctl>     <txrx|tx|rx> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Mac::Display( FC_Stream& theStream )
{
    theStream   << "MAC       - Auto-Negotiation        [autoneg] = " << DISPLAY_BOOL(myAutoNeg) << endl;
    theStream   << "MAC       - Ethernet Rate           [ethrate] = " << myEthernetRate << endl;
    theStream   << "MAC       - Duplex Mode             [duplex]  = " << DISPLAY_MAC_DUPLEX_MODE(myDuplexMode) << endl;
    theStream   << "MAC       - Advertised Flow Control [adflw]   = " << DISPLAY_MAC_ADFLOWCTRL(myAdvrtFlowCtrl) << endl;
    theStream   << "MAC       - Manual Flow Control     [flwctl]  = " << DISPLAY_MAC_FLOWCTRL(myFlowControl) << endl;
}

