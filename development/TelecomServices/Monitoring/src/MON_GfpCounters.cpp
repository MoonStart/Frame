//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_GfpCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_GfpCounters::MON_GfpCounters(uint32 theIndex):
    MON_Counters(theIndex),
    my10BErrorCount(0)
{
}

MON_GfpCounters::~MON_GfpCounters()
{
}


void MON_GfpCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_GFP_10BERROR:
        *theCount = my10BErrorCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_GfpCounters: Unsupported register");
        break;
    }
}

void MON_GfpCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_GFP_10BERROR:
        my10BErrorCount = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_GfpCounters: Unsupported register");
        break;
    }
}


void MON_GfpCounters::Reset(void)
{
    MON_Counters::Reset();
    my10BErrorCount = 0;
}

ostream& MON_GfpCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(my10BErrorCount);
    return theStream;
}

istream& MON_GfpCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(my10BErrorCount);
    return theStream;
}

FC_Stream& MON_GfpCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << my10BErrorCount;
    return theStream;
}

FC_Stream& MON_GfpCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> my10BErrorCount;
    return theStream;

}

void MON_GfpCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "GFP     - 10B Error Count                   = " << my10BErrorCount << endl;
}
