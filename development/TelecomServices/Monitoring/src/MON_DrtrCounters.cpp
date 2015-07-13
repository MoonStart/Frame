//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_DrtrCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_DrtrCounters::MON_DrtrCounters(uint32 theIndex):
    MON_Counters(theIndex)
{
    Reset();
}

MON_DrtrCounters::~MON_DrtrCounters()
{
}


void MON_DrtrCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_DRTR_RESOLUTION_FAILURE:
        *theCount = myResolutionFailureCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_DrtrCounters: Unsupported register");
        break;
    }
}

void MON_DrtrCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_DRTR_RESOLUTION_FAILURE:
        myResolutionFailureCount = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_DrtrCounters: Unsupported register");
        break;
    }
}


void MON_DrtrCounters::Reset(void)
{
    MON_Counters::Reset();
    myResolutionFailureCount = 0;
}

ostream& MON_DrtrCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myResolutionFailureCount);
    return theStream;
}

istream& MON_DrtrCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myResolutionFailureCount);
    return theStream;
}

FC_Stream& MON_DrtrCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myResolutionFailureCount;
    return theStream;
}

FC_Stream& MON_DrtrCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myResolutionFailureCount;
    return theStream;

}

void MON_DrtrCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "DRTR    - Resolution Failure Count          = " << myResolutionFailureCount << endl;
}
