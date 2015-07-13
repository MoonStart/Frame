//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_MsCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_MsCounters::MON_MsCounters(uint32 theIndex):
    MON_Counters(theIndex),
    myB2Count(0),
    myREI_LCount(0)
{
}

MON_MsCounters::~MON_MsCounters()
{
}


void MON_MsCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_MS_B2:
        *theCount = myB2Count;
        break;
    case CT_TEL_MS_REI:
        *theCount = myREI_LCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_MsCounters: Unsupported register");
        break;
    }
}

void MON_MsCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_MS_B2:
        myB2Count = theCount;
        break;
    case CT_TEL_MS_REI:
        myREI_LCount = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_MsCounters: Unsupported register");
        break;
    }
}


void MON_MsCounters::Reset(void)
{
    MON_Counters::Reset();
    myB2Count = 0;
    myREI_LCount = 0;
}

ostream& MON_MsCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myB2Count);
    theStream   << FC_InsertVar(myREI_LCount);
    return theStream;
}

istream& MON_MsCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myB2Count);
    theStream   >> FC_ExtractVar(myREI_LCount);
    return theStream;
}

FC_Stream& MON_MsCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myB2Count;
    theStream   << myREI_LCount;
    return theStream;
}

FC_Stream& MON_MsCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myB2Count;
    theStream   >> myREI_LCount;
    return theStream;

}

void MON_MsCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "MS      - CV Count                          = " << myB2Count << endl;
    theStream   << "MS      - REI-L Count                       = " << myREI_LCount << endl;

}
