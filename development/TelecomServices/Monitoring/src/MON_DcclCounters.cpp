//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_DcclCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_DcclCounters::MON_DcclCounters(uint32 theIndex):
    MON_Counters(theIndex)
{
    Reset();
}

MON_DcclCounters::~MON_DcclCounters()
{
}


void MON_DcclCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_DCCL_DROPPED_PACKETS:
        *theCount = myDroppedPacketsCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_DcclCounters: Unsupported register");
        break;
    }
}

void MON_DcclCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_DCCL_DROPPED_PACKETS:
        myDroppedPacketsCount = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_DcclCounters: Unsupported register");
        break;
    }
}


void MON_DcclCounters::Reset(void)
{
    MON_Counters::Reset();
    myDroppedPacketsCount = 0;
}

ostream& MON_DcclCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myDroppedPacketsCount);
    return theStream;
}

istream& MON_DcclCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myDroppedPacketsCount);
    return theStream;
}

FC_Stream& MON_DcclCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myDroppedPacketsCount;
    return theStream;
}

FC_Stream& MON_DcclCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myDroppedPacketsCount;
    return theStream;

}

void MON_DcclCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "DCCL    - Dropped Packets Count             = " << myDroppedPacketsCount << endl;
}
