//
// //Copyright(c) Tellabs Transport Group. All rights reserved.
//
#include "../MON_OptProtConfig.h"
#include <BaseClass/FC_TextStream.h>

MON_OptProtConfig::MON_OptProtConfig(uint32 theIndex):
    MON_Config(theIndex),
    myProtectionEnable(false),
    myOppositeSideBitMask(0)
{
}

MON_OptProtConfig::~MON_OptProtConfig(void )
{
}


bool MON_OptProtConfig::SetProtectionEnable(bool theState)
{
        bool hasChanged = false;
        if (myProtectionEnable != theState)
        {
                myProtectionEnable = theState;
                hasChanged = true;
        }
        return hasChanged;
}

bool MON_OptProtConfig::GetProtectionEnable() const
{
        return myProtectionEnable;
}



void MON_OptProtConfig::ClearOppositeSideBitMask()
{
        myOppositeSideBitMask = 0;
    return;
}

void MON_OptProtConfig::SetOppositeSidePosition(uint16 thePosition)
{
    uint16 aSetMask = 1;
    aSetMask = aSetMask << thePosition;
        myOppositeSideBitMask |= aSetMask;
    return;
}

uint16 MON_OptProtConfig::GetOppositeSideBitMask() const
{
    return(myOppositeSideBitMask);
}

CT_IntfId MON_OptProtConfig::GetOppositeSideIntfId() const
{
    if ( myOppositeSideBitMask & 0x0001 )
        return CT_PORT_SIDE_0;
    if ( myOppositeSideBitMask & 0x0002 )
        return CT_PORT_SIDE_1;
    if ( myOppositeSideBitMask & 0x0004 )
        return CT_PORT_SIDE_2;
    if ( myOppositeSideBitMask & 0x0008 )
        return CT_PORT_SIDE_3;
    if ( myOppositeSideBitMask & 0x0010 )
        return CT_PORT_SIDE_4;
    if ( myOppositeSideBitMask & 0x0020 )
        return CT_PORT_SIDE_5;
    if ( myOppositeSideBitMask & 0x0040 )
        return CT_PORT_SIDE_6;
    if ( myOppositeSideBitMask & 0x0080 )
        return CT_PORT_SIDE_7;
    if ( myOppositeSideBitMask & 0x0100 )
        return CT_PORT_SIDE_8;
    if ( myOppositeSideBitMask & 0x0200 )
        return CT_PORT_SIDE_9;
    if ( myOppositeSideBitMask & 0x0400 )
        return CT_PORT_SIDE_10;
    if ( myOppositeSideBitMask & 0x0800 )
        return CT_PORT_SIDE_11;
    if ( myOppositeSideBitMask & 0x1000 )
        return CT_PORT_SIDE_12;
    if ( myOppositeSideBitMask & 0x2000 )
        return CT_PORT_SIDE_13;
    if ( myOppositeSideBitMask & 0x4000 )
        return CT_PORT_SIDE_14;
    if ( myOppositeSideBitMask & 0x8000 )
        return CT_PORT_SIDE_15;

    return CT_INTF_ID_UNKNOWN;
}

void MON_OptProtConfig::ResetOppositeSidePosition(uint16 thePosition)
{
    uint16 aSetMask = 1;
    aSetMask = aSetMask << thePosition;
        myOppositeSideBitMask &= ~aSetMask;
    return;
}



void MON_OptProtConfig::Reset()
{
    myProtectionEnable = false;
    myOppositeSideBitMask = 0;
    MON_Config::Reset();
}

ostream& MON_OptProtConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myProtectionEnable);
    theStream << FC_InsertVar(myOppositeSideBitMask);
    return theStream;
}

istream& MON_OptProtConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myProtectionEnable);
    theStream   >> FC_ExtractVar(myOppositeSideBitMask);
    return theStream;
}

FC_Stream& MON_OptProtConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream   << myProtectionEnable;
    theStream   << myOppositeSideBitMask;
    return theStream;
}

FC_Stream& MON_OptProtConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream   >> myProtectionEnable;
    theStream   >> myOppositeSideBitMask;
    return theStream;
}

void MON_OptProtConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "PROT    - Protection Enabled        [prot]      = "   << DISPLAY_BOOL(myProtectionEnable) << endl;
    theStream   << "PROT    - Opposite Side Bit Mask    [setPos]    = 0x" << hex << myOppositeSideBitMask << endl;
}

FC_CmdProcessor::STATUS MON_OptProtConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto OPTPROTERROR;

    if (!strcmp(argv[0],"prot"))
    {
        SetProtectionEnable(argv[1][0]=='e');
    }
    else if (!strncmp(argv[0],"set",3))
        {
        SetOppositeSidePosition(atoi(argv[1]));
    }
    else if (!strncmp(argv[0],"res",3))
        {
        ResetOppositeSidePosition(atoi(argv[1]));
    }
    else if (!strncmp(argv[0],"bit",3))
        {
        ClearOppositeSideBitMask();
    }
    else
        goto OPTPROTERROR;

    return FC_CmdProcessor::E_SUCCESS;

OPTPROTERROR:
    {
        fc_cout << "prot <e-nable|d-isable> " << endl;
        fc_cout << "<setPos | resetPos> <Numeric value for bit position, range 0 .. 15 inclusive> " << endl;
        fc_cout << "<setPos | resetPos> <Numeric value for bit position, range 0 .. 15 inclusive> " << endl;
        fc_cout << "bitsclear <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

