//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_HOPCOUNTERS_H
#define MON_HOPCOUNTERS_H

#include "MON_Object.h"
#include "MON_Counters.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the counters for the 
//Regenerator Section (HOP) layer (or SONET Section).
//##ModelId=3C0FE66E0263
class MON_HopCounters :public MON_Counters
{
public:

    //Constructor.
    MON_HopCounters(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_HopCounters(void);

    void Reset();

    virtual void Display(FC_Stream& theStream);

    void GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const;

    void SetErrorCount(CT_TEL_Register theRegister, uint32 theCount);

protected:

    virtual ostream& WriteObject( ostream& theStream );

    virtual istream& ReadObject( istream& theStream );

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // The current number of coding violation read from SONET/SDH B3 byte.
    uint32 myB3Count;

    // The current Remote Error Indication Line (REI-P) Count
    uint32 myREI_PCount;

    // The current Positive Pointer Justification Generated Count
    uint32 myPPJ_GENCount;

    // The current Negative Pointer Justification Generated Count
    uint32 myNPJ_GENCount;

    // The current Positive Pointer Justification Detected Count
    uint32 myPPJ_DETCount;

    // The current Negative Pointer Justification Detected Count
    uint32 myNPJ_DETCount;
};

#endif /* MON_HOPCOUNTERS_H */
