// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_MsStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_MsStatus::MON_MsStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_MsStatus::~MON_MsStatus(void)
{
    // Nothing to do for now.

}

uint8 MON_MsStatus::GetK1RxByte() const 
{
    return myRxK1Byte;
}

bool MON_MsStatus::SetK1RxByte(uint8 theK1Byte) 
{
    bool hasChanged = false;
    if (!(myRxK1Byte == theK1Byte))
    {
        myRxK1Byte = theK1Byte;
        hasChanged = true;
    }

    return hasChanged;
}

uint8 MON_MsStatus::GetK2RxByte() const 
{
    return myRxK2Byte;
}

bool MON_MsStatus::SetK2RxByte(uint8 theK2Byte) 
{
    bool hasChanged = false;
    if (!(myRxK2Byte == theK2Byte))
    {
        myRxK2Byte = theK2Byte;
        hasChanged = true;
    }

    return hasChanged;
}


uint8 MON_MsStatus::GetRxCsi() const 
{
    return myRxCsi;
}

bool MON_MsStatus::SetRxCsi(uint8 theCsi) 
{
    bool hasChanged = false;
    if (!(myRxCsi == theCsi))
    {
        myRxCsi = theCsi;
        hasChanged = true;
    }

    return hasChanged;
}


CT_FAC_RxSsm MON_MsStatus::GetRxSsm() const 
{
    return myRxSsm;
}

bool MON_MsStatus::SetRxSsm(CT_FAC_RxSsm theRxSsm) 
{
    bool hasChanged = false;
    if (!(myRxSsm == theRxSsm))
    {
        myRxSsm    = theRxSsm;
        hasChanged = true;
    }

    return hasChanged;
}


void MON_MsStatus::Reset(void)
{
    MON_Object::Reset();
    myRxK1Byte = 0;
    myRxK2Byte = 0;
    myRxCsi    = 255; //Special code that means default
    myRxSsm    = CT_RxSsm_DUS;
}

ostream& MON_MsStatus::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myRxK1Byte);
    theStream << FC_InsertVar(myRxK2Byte);
    theStream << FC_InsertVar(myRxCsi);
    uint32 aSsm = (uint32) myRxSsm;
    theStream << FC_InsertVar(aSsm);
    return theStream;

}

istream& MON_MsStatus::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRxK1Byte);
    theStream >> FC_ExtractVar(myRxK2Byte);
    theStream >> FC_ExtractVar(myRxCsi);
    uint32 aSsm;
    theStream >> FC_ExtractVar(aSsm);
    myRxSsm = (CT_FAC_RxSsm) aSsm;
    return theStream;

}

FC_Stream& MON_MsStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myRxK1Byte;
    theStream << myRxK2Byte;
    theStream << myRxCsi;
    uint32 aSsm = (uint32) myRxSsm;
    theStream << aSsm;
    return theStream;

}

FC_Stream& MON_MsStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myRxK1Byte;
    theStream >> myRxK2Byte;
    theStream >> myRxCsi;
    uint32 aSsm;
    theStream >> aSsm;
    myRxSsm = (CT_FAC_RxSsm) aSsm;
    return theStream;

}

void MON_MsStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);

    FC_FmtFlags previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::hex, ios::basefield);    
    theStream   << "MS      - Received K1 Byte                  = 0x" << (int)myRxK1Byte << endl;
    theStream   << "MS      - Received K2 Byte                  = 0x" << (int)myRxK2Byte << endl;
    theStream   << "MS      - Received CSI Code                 = 0x" << (int)myRxCsi << endl;
    theStream   << "MS      - Received SSM Value                = " << display_RXSSM(myRxSsm) << endl;
    fc_cout.Flags(previousFlags);
}
