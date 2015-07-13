//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_GccCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_GccCounters::MON_GccCounters(uint32 theIndex):
    MON_Counters(theIndex)
{
    Reset();
}

MON_GccCounters::~MON_GccCounters()
{
}


void MON_GccCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_GCC_DROPPED_PACKETS:
        *theCount = myDroppedPacketsCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_GccCounters: Unsupported register");
        break;
    }
}

void MON_GccCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_GCC_DROPPED_PACKETS:
        myDroppedPacketsCount = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_GccCounters: Unsupported register");
        break;
    }
}


void MON_GccCounters::Reset(void)
{
    MON_Counters::Reset();
    myDroppedPacketsCount = 0;
}

ostream& MON_GccCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myDroppedPacketsCount);
    return theStream;
}

istream& MON_GccCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myDroppedPacketsCount);
    return theStream;
}

FC_Stream& MON_GccCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myDroppedPacketsCount;
    return theStream;
}

FC_Stream& MON_GccCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myDroppedPacketsCount;
    return theStream;

}

void MON_GccCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "GCC    - Dropped Packets Count             = " << myDroppedPacketsCount << endl;
}
