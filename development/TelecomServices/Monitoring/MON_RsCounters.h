//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RSCOUNTERS_H
#define MON_RSCOUNTERS_H

#include "MON_Object.h"
#include "MON_Counters.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the counters for the 
//Regenerator Section (RS) layer (or SONET Section).
//##ModelId=3C0FE66E0263
class MON_RsCounters :public MON_Counters
{
public:

	//Constructor.
	//##ModelId=3C0FE66E026E
    MON_RsCounters(uint32 theIndex);

	//Virtual destructor.
	//##ModelId=3C0FE66E0277
    virtual ~MON_RsCounters(void);

	//##ModelId=3C0FE66E0282
    void Reset();
	//##ModelId=3C7170D80225
    virtual void Display(FC_Stream& theStream);

	//##ModelId=3C0FE66E028B
    void GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const;
	//##ModelId=3C18E9320167
	void SetErrorCount(CT_TEL_Register theRegister, uint32 theCount);

protected:
	//##ModelId=3C0FE66E0295
    virtual ostream& WriteObject( ostream& theStream );
	//##ModelId=3C0FE66E029F
    virtual istream& ReadObject( istream& theStream );
	//##ModelId=3C0FE66E02AA
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//##ModelId=3C0FE66E02B4
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	//The current number of coding violation read from 
	//SONET/SDH B1 byte.
	//##ModelId=3C0FE7900133
    uint32 myB1Count;
	uint32 myHighB1Count;

    //Symbol Errors was removed in 7.1 (combined with B1 count
};

#endif /* MON_RSCOUNTERS_H */
