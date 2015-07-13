//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_MSCOUNTERS_H
#define MON_MSCOUNTERS_H

#include "MON_Object.h"
#include "MON_Counters.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the counters for the 
//Regenerator Section (MS) layer (or SONET Section).
//##ModelId=3C0FE66E0263
class MON_MsCounters :public MON_Counters
{
public:

    //Constructor.
    MON_MsCounters(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_MsCounters(void);

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

    // The current number of coding violation read from SONET/SDH B2 byte.
    uint32 myB2Count;

    // The current Remote Error Indication Line (REI-L) Count
    uint32 myREI_LCount;

};

#endif /* MON_MSCOUNTERS_H */
