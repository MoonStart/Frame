// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_OCHRESULT_3C4828A200F6_INCLUDED
#define _INC_MON_OCHRESULT_3C4828A200F6_INCLUDED

#include "MON_Definitions.h"
#include "MON_OchStatus.h"
#include "MON_PilotToneProcessorRequest.h"

//This class defines a pilot tone power and a request ID 
//number. It is used for on-demand pilot tone power results.
//##ModelId=3C4828A200F6
class MON_OchResult 
: public MON_OchStatus
{
private:
    MON_PilotToneProcessorRequest myRequestInformation;
    uint32 myErrorCode;

public:

	//Constructor.
	//##ModelId=3C7170F003D9
    MON_OchResult(uint32 theIndex);

	//Virtual destructor.
	//##ModelId=3C7170F10005
    virtual ~MON_OchResult(void);

	//##ModelId=3C7170F10019
    void Reset();
	//##ModelId=3C7170F1001A
    virtual void Display(FC_Stream& theStream);

    bool operator==(const MON_OchResult& theOchResult) const;
    void operator=(const MON_OchResult& theOchResult);

    void SetRequestInformation(MON_PilotToneProcessorRequest& theRequest);
    const MON_PilotToneProcessorRequest& GetRequestInformation() const;

    void SetErrorCode(uint32 theErrorCode);
    uint32 GetErrorCode() const;

protected:
	//##ModelId=3C7170F10037
    virtual ostream& WriteObject( ostream& theStream );
	//##ModelId=3C7170F1004B
    virtual istream& ReadObject( istream& theStream );
	//##ModelId=3C7170F1005F
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//##ModelId=3C7170F10073
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

};

#endif /* _INC_MON_OCHRESULT_3C4828A200F6_INCLUDED */
