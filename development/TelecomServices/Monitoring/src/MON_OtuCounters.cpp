// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtuCounters.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>


MON_OtuCounters::MON_OtuCounters(uint32 theIndex):
    MON_Counters(theIndex),
    myBIP8Count(0),
    myHighBIP8Count(0),
    myBEICount(0),
    myHighBEICount(0),
    myByteCorrectionCount(0),
    myBitErrorCountOnOnes(0),
    myBitErrorCountOnZeros(0),
    myHighByteCorrectionCount(0),
    myHighBitErrorCountOnOnes(0),
    myHighBitErrorCountOnZeros(0),
    myNonCorrectableRSFrameCount(0),
    myHighNonCorrectableRSFrameCount(0)
{
}

MON_OtuCounters::~MON_OtuCounters()
{
}

void MON_OtuCounters::GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const
{
    switch (theRegister)
    {
    case CT_TEL_OTU_BYTE_CORRECTIONS:
        *theCount = myByteCorrectionCount;
        break;
    case CT_TEL_OTU_BIT_ERROR_ON_ONES:
        *theCount = myBitErrorCountOnOnes;
        break;
    case CT_TEL_OTU_BIT_ERROR_ON_ZEROS:
        *theCount = myBitErrorCountOnZeros;
        break;
    case CT_TEL_OTU_UNCORRECTABLE_RSFRAMES:
        *theCount = myNonCorrectableRSFrameCount;
        break;
    case CT_TEL_OTU_BEI:
        *theCount = myBEICount;
        break;
    case CT_TEL_OTU_BIP8:
        *theCount = myBIP8Count;
        break;
    case CT_TEL_OTU_HIGH_BYTE_CORRECTIONS:
        *theCount = myHighByteCorrectionCount;
        break;
    case CT_TEL_OTU_HIGH_BIT_ERROR_ON_ONES:
        *theCount = myHighBitErrorCountOnOnes;
        break;
    case CT_TEL_OTU_HIGH_BIT_ERROR_ON_ZEROS:
        *theCount = myHighBitErrorCountOnZeros;
        break;
    case CT_TEL_OTU_HIGH_UNCORRECTABLE_RSFRAMES:
        *theCount = myHighNonCorrectableRSFrameCount;
        break;
    case CT_TEL_OTU_HIGH_BEI:
        *theCount = myHighBEICount;
        break;
    case CT_TEL_OTU_HIGH_BIP8:
        *theCount = myHighBIP8Count;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "Unsupported register");
        break;
    }
}

void MON_OtuCounters::SetErrorCount(CT_TEL_Register theRegister, uint32 theCount)
{
    switch (theRegister)
    {
    case CT_TEL_OTU_BYTE_CORRECTIONS:
        myByteCorrectionCount = theCount;
        break;
    case CT_TEL_OTU_BIT_ERROR_ON_ONES:
        myBitErrorCountOnOnes = theCount;
        break;
    case CT_TEL_OTU_BIT_ERROR_ON_ZEROS:
        myBitErrorCountOnZeros = theCount;
        break;
    case CT_TEL_OTU_UNCORRECTABLE_RSFRAMES:
        myNonCorrectableRSFrameCount = theCount;
        break;
    case CT_TEL_OTU_BEI:
        myBEICount = theCount;
        break;
    case CT_TEL_OTU_BIP8:
        myBIP8Count = theCount;
        break;
    case CT_TEL_OTU_HIGH_BYTE_CORRECTIONS:
        myHighByteCorrectionCount = theCount;
        break;
    case CT_TEL_OTU_HIGH_BIT_ERROR_ON_ONES:
        myHighBitErrorCountOnOnes = theCount;
        break;
    case CT_TEL_OTU_HIGH_BIT_ERROR_ON_ZEROS:
        myHighBitErrorCountOnZeros = theCount;
        break;
    case CT_TEL_OTU_HIGH_UNCORRECTABLE_RSFRAMES:
        myHighNonCorrectableRSFrameCount = theCount;
        break;
    case CT_TEL_OTU_HIGH_BEI:
        myHighBEICount = theCount;
        break;
    case CT_TEL_OTU_HIGH_BIP8:
        myHighBIP8Count = theCount;
        break;
    default: 
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuCounters: Unsupported register");
        break;
    }
}

void MON_OtuCounters::Reset(void)
{
    MON_Counters::Reset();
	myBIP8Count = 0;
    myBEICount = 0;
    myByteCorrectionCount = 0;
    myBitErrorCountOnOnes = 0;
    myBitErrorCountOnZeros = 0;
    myNonCorrectableRSFrameCount = 0;
    myHighBIP8Count = 0;
    myHighBEICount = 0;
    myHighByteCorrectionCount = 0;
    myHighBitErrorCountOnOnes = 0;
    myHighBitErrorCountOnZeros = 0;
    myHighNonCorrectableRSFrameCount = 0;
}

ostream& MON_OtuCounters::WriteObject( ostream& theStream )
{
    MON_Counters::WriteObject(theStream);
    theStream   << FC_InsertVar(myBIP8Count);
    theStream   << FC_InsertVar(myBEICount);
    theStream   << FC_InsertVar(myByteCorrectionCount);
    theStream   << FC_InsertVar(myBitErrorCountOnOnes);
    theStream   << FC_InsertVar(myBitErrorCountOnZeros);
    theStream   << FC_InsertVar(myNonCorrectableRSFrameCount);
    theStream   << FC_InsertVar(myHighBIP8Count);
    theStream   << FC_InsertVar(myHighBEICount);
    theStream   << FC_InsertVar(myHighByteCorrectionCount);
    theStream   << FC_InsertVar(myHighBitErrorCountOnOnes);
    theStream   << FC_InsertVar(myHighBitErrorCountOnZeros);
    theStream   << FC_InsertVar(myHighNonCorrectableRSFrameCount);
    return theStream;
}

istream& MON_OtuCounters::ReadObject( istream& theStream )
{
    MON_Counters::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myBIP8Count);
    theStream   >> FC_ExtractVar(myBEICount);
    theStream   >> FC_ExtractVar(myByteCorrectionCount);
    theStream   >> FC_ExtractVar(myBitErrorCountOnOnes);
    theStream   >> FC_ExtractVar(myBitErrorCountOnZeros);
    theStream   >> FC_ExtractVar(myNonCorrectableRSFrameCount);
    theStream   >> FC_ExtractVar(myHighBIP8Count);
    theStream   >> FC_ExtractVar(myHighBEICount);
    theStream   >> FC_ExtractVar(myHighByteCorrectionCount);
    theStream   >> FC_ExtractVar(myHighBitErrorCountOnOnes);
    theStream   >> FC_ExtractVar(myHighBitErrorCountOnZeros);
    theStream   >> FC_ExtractVar(myHighNonCorrectableRSFrameCount);
    return theStream;
}

FC_Stream& MON_OtuCounters::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Counters::WriteObjectBinary(theStream);
    theStream   << myBIP8Count;
    theStream   << myBEICount;
    theStream   << myByteCorrectionCount;
    theStream   << myBitErrorCountOnOnes;
    theStream   << myBitErrorCountOnZeros;
    theStream   << myNonCorrectableRSFrameCount;
    theStream   << myHighBIP8Count;
    theStream   << myHighBEICount;
    theStream   << myHighByteCorrectionCount;
    theStream   << myHighBitErrorCountOnOnes;
    theStream   << myHighBitErrorCountOnZeros;
    theStream   << myHighNonCorrectableRSFrameCount;
    return theStream;
}

FC_Stream& MON_OtuCounters::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Counters::ReadObjectBinary(theStream);
    theStream   >> myBIP8Count;
    theStream   >> myBEICount;
    theStream   >> myByteCorrectionCount;
    theStream   >> myBitErrorCountOnOnes;
    theStream   >> myBitErrorCountOnZeros;
    theStream   >> myNonCorrectableRSFrameCount;
    theStream   >> myHighBIP8Count;
    theStream   >> myHighBEICount;
    theStream   >> myHighByteCorrectionCount;
    theStream   >> myHighBitErrorCountOnOnes;
    theStream   >> myHighBitErrorCountOnZeros;
    theStream   >> myHighNonCorrectableRSFrameCount;
    return theStream;
}

void MON_OtuCounters::Display(FC_Stream& theStream)
{
    MON_Counters::Display(theStream);
    theStream   << "OTU     - BIP-8 (Low 32 bits)               = " << myBIP8Count << endl;
    theStream   << "OTU     - BIP-8 (High 32 bits)              = " << myHighBIP8Count << endl;
    theStream   << "OTU     - BEI (Low 32 bits)                 = " << myBEICount << endl;
    theStream   << "OTU     - BEI (High 32 bits)                = " << myHighBEICount << endl;
    theStream   << "OTU     - Byte Correction Count (Low)       = " << myByteCorrectionCount << endl;
    theStream   << "OTU     - Bit Error Count On Ones (Low)     = " << myBitErrorCountOnOnes << endl;
    theStream   << "OTU     - Bit Error Count On Zeros (Low)    = " << myBitErrorCountOnZeros << endl;
    theStream   << "OTU     - Byte Correction Count (High)      = " << myHighByteCorrectionCount << endl;
    theStream   << "OTU     - Bit Error Count On Ones (High)    = " << myHighBitErrorCountOnOnes << endl;
    theStream   << "OTU     - Bit Error Count On Zeros (High)   = " << myHighBitErrorCountOnZeros << endl;
    theStream   << "OTU     - Uncorrectable Frame Count (Low)   = " << myNonCorrectableRSFrameCount << endl;
    theStream   << "OTU     - Uncorrectable Frame Count (High)  = " << myHighNonCorrectableRSFrameCount << endl;
}
