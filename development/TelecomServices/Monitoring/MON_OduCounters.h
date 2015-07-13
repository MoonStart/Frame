//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_ODUCOUNTERS_H
#define MON_ODUCOUNTERS_H

#include "MON_Counters.h"

#include "MON_Object.h"


//This class contains the error counters related to the ODU 
//layer.
class MON_OduCounters :public MON_Counters
{
public:
    
    //Constructor.
    MON_OduCounters(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OduCounters(void);

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
	
    //The current value of the ODU overhead 8-bit interleave parity counter.
	uint32 myBIP8Count;
	uint32 myHighBIP8Count;

	//The current value of the ODU overhead backward error indicator counter.
    //(NOT IMPLEMENTED YET)
	uint32 myBEICount;
	uint32 myHighBEICount;

};

#endif /* MON_ODUCOUNTERS_H */
