//Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_HopCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

MON_HopCounters::MON_HopCounters(uint32 theIndex):
    MON_Counters(theIndex),
    myB3Count(0),
    myREI_PCount(0),
    myPPJ_GENCount(0),
    myNPJ_GENCount(0),
    myPPJ_DETCount(0),
    myNPJ_DETCount(0)
{
}

MON_HopCounters::~MON_HopCounters()
{
}


void MON_HopCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_HOP_B3:
        *theCount = myB3Count;
        break;
    case CT_TEL_HOP_REI:
        *theCount = myREI_PCount;
        break;
    case CT_TEL_HOP_PPJ_GEN:
        *theCount = myPPJ_GENCount;
        break;
    case CT_TEL_HOP_NPJ_GEN:
        *theCount = myNPJ_GENCount;
        break;
    case CT_TEL_HOP_PPJ_DET:
        *theCount = myPPJ_DETCount;
        break;
    case CT_TEL_HOP_NPJ_DET:
        *theCount = myNPJ_DETCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_HopCounters: Unsupported register");
        break;
    }
}

void MON_HopCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_HOP_B3:
        myB3Count = theCount;
        break;
    case CT_TEL_HOP_REI:
        myREI_PCount = theCount;
        break;
    case CT_TEL_HOP_PPJ_GEN:
        myPPJ_GENCount = theCount;
        break;
    case CT_TEL_HOP_NPJ_GEN:
        myNPJ_GENCount = theCount;
        break;
    case CT_TEL_HOP_PPJ_DET:
        myPPJ_DETCount = theCount;
        break;
    case CT_TEL_HOP_NPJ_DET:
        myNPJ_DETCount = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_HopCounters: Unsupported register");
        break;
    }
}


void MON_HopCounters::Reset(void)
{
    MON_Counters::Reset();
    myB3Count = 0;
    myREI_PCount = 0;
    myPPJ_GENCount = 0;
    myNPJ_GENCount = 0;
    myPPJ_DETCount = 0;
    myNPJ_DETCount = 0;
}

ostream& MON_HopCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myB3Count);
    theStream   << FC_InsertVar(myREI_PCount);
    theStream   << FC_InsertVar(myPPJ_GENCount);
    theStream   << FC_InsertVar(myNPJ_GENCount);
    theStream   << FC_InsertVar(myPPJ_DETCount);
    theStream   << FC_InsertVar(myNPJ_DETCount);
    return theStream;
}

istream& MON_HopCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myB3Count);
    theStream   >> FC_ExtractVar(myREI_PCount);
    theStream   >> FC_ExtractVar(myPPJ_GENCount);
    theStream   >> FC_ExtractVar(myNPJ_GENCount);
    theStream   >> FC_ExtractVar(myPPJ_DETCount);
    theStream   >> FC_ExtractVar(myNPJ_DETCount);
    return theStream;
}

FC_Stream& MON_HopCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myB3Count;
    theStream   << myREI_PCount;
    theStream   << myPPJ_GENCount;
    theStream   << myNPJ_GENCount;
    theStream   << myPPJ_DETCount;
    theStream   << myNPJ_DETCount;
    return theStream;
}

FC_Stream& MON_HopCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myB3Count;
    theStream   >> myREI_PCount;
    theStream   >> myPPJ_GENCount;
    theStream   >> myNPJ_GENCount;
    theStream   >> myPPJ_DETCount;
    theStream   >> myNPJ_DETCount;
    return theStream;

}

void MON_HopCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "HOP     - CV Count                          = " << myB3Count << endl;
    theStream   << "HOP     - REI_P Count                       = " << myREI_PCount << endl;
    theStream   << "HOP     - PPJ_GEN Count                     = " << myPPJ_GENCount << endl;
    theStream   << "HOP     - NPJ_GEN Count                     = " << myNPJ_GENCount << endl;
    theStream   << "HOP     - PPJ_DET Count                     = " << myPPJ_DETCount << endl;
    theStream   << "HOP     - NPJ_DET Count                     = " << myNPJ_DETCount << endl;

}
