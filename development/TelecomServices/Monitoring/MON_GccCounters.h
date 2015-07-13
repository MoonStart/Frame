//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_GCCCOUNTERS_H
#define MON_GCCCOUNTERS_H

#include "MON_Object.h"
#include "MON_Counters.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the counters for the 
//GCC (GCC Link).
//##ModelId=3C0FE66E0263
class MON_GccCounters :public MON_Counters
{
public:

    //Constructor.
    MON_GccCounters(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_GccCounters(void);

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

    // The current number of Dropped Packets from the GCC Link.
    uint32 myDroppedPacketsCount;

};

#endif /* MON_GCCCOUNTERS_H */
