//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_DRTRCOUNTERS_H
#define MON_DRTRCOUNTERS_H

#include "MON_Counters.h"

#include "MON_Object.h"


//This class contains the error counters related to the DRTR 
//layer.
class MON_DrtrCounters :public MON_Counters
{
public:
	
    //Constructor.
    MON_DrtrCounters(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_DrtrCounters(void);

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

    // The current number of Resolution Failures from the DCC Router.
    uint32 myResolutionFailureCount;

};

#endif /* MON_DRTRCOUNTERS_H */
