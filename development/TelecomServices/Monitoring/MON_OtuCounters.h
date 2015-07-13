//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTUCOUNTERS_H
#define MON_OTUCOUNTERS_H

#include "MON_Counters.h"

#include "MON_Object.h"


//This class contains the error counters related to the OTU 
//layer.
class MON_OtuCounters :public MON_Counters
{
public:
    
    //Constructor.
    MON_OtuCounters(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OtuCounters(void);

    void GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const;
    void SetErrorCount(CT_TEL_Register theRegister, uint32 theCount);

    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    
    //The number of bytes that were corrected.
    uint32 myByteCorrectionCount;
    uint32 myHighByteCorrectionCount;

    uint32 myBitErrorCountOnOnes;
    uint32 myHighBitErrorCountOnOnes;

    uint32 myBitErrorCountOnZeros;
    uint32 myHighBitErrorCountOnZeros;

    //The number of Reed Solomon frames that could not be corrected.
    uint32 myNonCorrectableRSFrameCount;
    uint32 myHighNonCorrectableRSFrameCount;

    //The current value of the OTU overhead 8-bit interleave parity counter.
    uint32 myBIP8Count;
    uint32 myHighBIP8Count;

    //The current value of the OTU overhead backward error indicator counter.
    uint32 myBEICount;
    uint32 myHighBEICount;

};

#endif /* MON_OTUCOUNTERS_H */
