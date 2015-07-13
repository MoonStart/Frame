//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_RsCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#define CT_TEL_RS_HIGH_B1 1

//##ModelId=3C0FE66E026E
MON_RsCounters::MON_RsCounters(uint32 theIndex):
    MON_Counters(theIndex),
    myB1Count(0),
    myHighB1Count(0)
{
}

//##ModelId=3C0FE66E0277
MON_RsCounters::~MON_RsCounters()
{
}


//##ModelId=3C0FE66E028B
void MON_RsCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_RS_B1:
        *theCount = myB1Count;
        break;
    case CT_TEL_RS_HIGH_B1:
        *theCount = myHighB1Count;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_RsCounters: Unsupported register");
        break;
    }
}

//##ModelId=3C18E9320167
void MON_RsCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_RS_B1:
        myB1Count = theCount;
        break;
    case CT_TEL_RS_HIGH_B1:
        myHighB1Count = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_RsCounters: Unsupported register");
        break;
    }
}


//##ModelId=3C0FE66E0282
void MON_RsCounters::Reset(void)
{
    MON_Counters::Reset();
    myB1Count = 0;
    myHighB1Count = 0;
}

//##ModelId=3C0FE66E0295
ostream& MON_RsCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myB1Count);
    theStream   << FC_InsertVar(myHighB1Count);
    return theStream;
}

//##ModelId=3C0FE66E029F
istream& MON_RsCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myB1Count);
    theStream   >> FC_ExtractVar(myHighB1Count);
    return theStream;
}

//##ModelId=3C0FE66E02AA
FC_Stream& MON_RsCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myB1Count;
    theStream   << myHighB1Count;
    return theStream;
}

//##ModelId=3C0FE66E02B4
FC_Stream& MON_RsCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myB1Count;
    theStream   >> myHighB1Count;
    return theStream;

}

//##ModelId=3C7170D80225
void MON_RsCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "RS      - CV Count                          = " << myB1Count << endl;
    theStream   << "RS      - High CV Count                     = " << myHighB1Count << endl;
}
