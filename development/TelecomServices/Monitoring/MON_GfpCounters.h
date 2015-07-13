//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_GFPCOUNTERS_H
#define MON_GFPCOUNTERS_H

#include "MON_Object.h"
#include "MON_Counters.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the counters for the 
//Generic Framing Protocol (GFP) layer.
//##ModelId=3C0FE66E0263
class MON_GfpCounters :public MON_Counters
{
public:

    //Constructor.
    MON_GfpCounters(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_GfpCounters(void);

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
    uint32 my10BErrorCount;
};

#endif /* MON_GFPCOUNTERS_H */
