// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TxOptResult.h"
#include <BaseClass/FC_TextStream.h>

MON_TxOptResult::MON_TxOptResult(uint32 theIndex):
    MON_Object(theIndex),
    myRequestID(0),
    myTransmitPower(0)
{
}

MON_TxOptResult::~MON_TxOptResult(void)
{
}

void MON_TxOptResult::Reset()
{
    MON_Object::Reset();
    myRequestID = 0;
    myTransmitPower = 0;
}

void MON_TxOptResult::SetRequestID(MON_RequestID theRequestID)
{
    myRequestID = theRequestID;
}

MON_RequestID MON_TxOptResult::GetRequestID() const
{
    return myRequestID;
}

void MON_TxOptResult::SetTransmitPower(CT_TEL_mBm thePower)
{
    myTransmitPower = thePower;
}

CT_TEL_mBm MON_TxOptResult::GetTransmitPower() const
{
    return myTransmitPower;
}

ostream& MON_TxOptResult::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myRequestID);
    theStream << FC_InsertVar(myTransmitPower);
    return theStream;
}

istream& MON_TxOptResult::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRequestID);
    theStream >> FC_ExtractVar(myTransmitPower);
    return theStream;
}

FC_Stream& MON_TxOptResult::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myRequestID;
    theStream << myTransmitPower;
    return theStream;
}

FC_Stream& MON_TxOptResult::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myRequestID;
    theStream >> myTransmitPower;
    return theStream;
}

void MON_TxOptResult::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "TX OPT  - Request ID                        = " << myRequestID << endl;
    theStream   << "TX OPT  - Transmit Power (dBm)              = " << DISPLAY_MBM(myTransmitPower) << endl;
}
