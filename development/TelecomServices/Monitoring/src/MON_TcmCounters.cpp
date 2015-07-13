// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TcmCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_TcmCounters::MON_TcmCounters(uint32 theIndex):
    MON_Counters(theIndex),
    myBIP8Count(0),
    myHighBIP8Count(0),
    myBEICount(0),
    myHighBEICount(0)
{
}

MON_TcmCounters::~MON_TcmCounters()
{
}

void MON_TcmCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_TCM_BEI:
        *theCount = myBEICount;
        break;
    case CT_TEL_TCM_HIGH_BEI:
        *theCount = myHighBEICount;
        break;
    case CT_TEL_TCM_BIP8:
        *theCount = myBIP8Count;
        break;
    case CT_TEL_TCM_HIGH_BIP8:
        *theCount = myHighBIP8Count;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmCounters::Unsupported register");
        break;
    }
}

void MON_TcmCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_TCM_BEI:
        myBEICount = theCount;
        break;
    case CT_TEL_TCM_HIGH_BEI:
        myHighBEICount = theCount;
        break;
    case CT_TEL_TCM_BIP8:
        myBIP8Count = theCount;
        break;
    case CT_TEL_TCM_HIGH_BIP8:
        myHighBIP8Count = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmCounters::Unsupported register");
        break;
    }
}

void MON_TcmCounters::Reset(void)
{
    // Initialize all attributes to zero
    MON_Counters::Reset();
    myBIP8Count = 0;
    myHighBIP8Count = 0;
    myBEICount = 0;
    myHighBEICount = 0;
}

ostream& MON_TcmCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myBIP8Count);
    theStream   << FC_InsertVar(myBEICount);
    theStream   << FC_InsertVar(myHighBIP8Count);
    theStream   << FC_InsertVar(myHighBEICount);

    return theStream;
}

istream& MON_TcmCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myBIP8Count);
    theStream   >> FC_ExtractVar(myBEICount);
    theStream   >> FC_ExtractVar(myHighBIP8Count);
    theStream   >> FC_ExtractVar(myHighBEICount);

    return theStream;
}

FC_Stream& MON_TcmCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myBIP8Count;
    theStream   << myBEICount;
    theStream   << myHighBIP8Count;
    theStream   << myHighBEICount;

    return theStream;

}

FC_Stream& MON_TcmCounters::ReadObjectBinary( FC_Stream& theStream ) 
{

    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myBIP8Count;
    theStream   >> myBEICount;
    theStream   >> myHighBIP8Count;
    theStream   >> myHighBEICount;

    return theStream;

}

void MON_TcmCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "TCM     - BIP-8                             = " << myBIP8Count << endl;
    theStream   << "TCM     - High BIP-8                        = " << myHighBIP8Count << endl;
    theStream   << "TCM     - BEI                               = " << myBEICount << endl;
    theStream   << "TCM     - High BEI                          = " << myHighBEICount << endl;
}

