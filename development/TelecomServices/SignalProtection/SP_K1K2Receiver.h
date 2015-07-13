// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_K1K2RECEIVER_38FDCCBC01F0_INCLUDED
#define _INC_SP_K1K2RECEIVER_38FDCCBC01F0_INCLUDED

#include "SP_K1K2.h"
#include "ExecutionSupport/FC_Action.h"

class TEL_BbObjectBase;

//This class is the base class for the K1K2 receiver. It hold 
//the K1K2 bytes value and provide few interface to compare 
//status and request.
//##ModelId=38FDCCBC01F0
class SP_K1K2Receiver 
: public FC_Action
{
public:
	//Constructor.
	//##ModelId=390583FB03C5
	SP_K1K2Receiver();

	//Destructor.
	//##ModelId=390583FC0023
	virtual ~SP_K1K2Receiver();

	//Returns the K1K2 bytes received.
	//##ModelId=39ACEFBC0246
    inline SP_K1K2 GetReceivedKbytes() const{return myK1K2bytes;};

	//Returns true if request is identical to given one.
	//##ModelId=39ACEFBC0214
    inline bool RequestIsEqualTo(SP_K1Request theComparedRequest) const { return myK1K2bytes.request == theComparedRequest;};
	//Returns true if request is different from given one.
	//##ModelId=39ACEFBC01EC
    inline bool RequestIsDifferentThan(SP_K1Request theComparedRequest) const {return myK1K2bytes.request != theComparedRequest;};

	//Returns true if status is identical to given one.
	//##ModelId=39ACEFBC01C4
    inline bool StatusIsEqualTo(SP_Status theComparedStatus) const { return myK1K2bytes.status == theComparedStatus;};
	//Returns true if status is different from given one.
	//##ModelId=39ACEFBC0187
    inline bool StatusIsDifferentThan(SP_Status theComparedStatus) const {return myK1K2bytes.status != theComparedStatus;};

	//Not supported.
	//##ModelId=3B8BC9E60026
    virtual void Run( FC_Object* theObject = NULL );
	//Sends the K1K2 to a stream (debug).
	//##ModelId=3B8BC9E503DC
	virtual FC_Stream& SnapshotWrite(FC_Stream& theStream);

protected:
	//Last value of K1K2 read on the facility.
	//##ModelId=3917FB890304
	SP_K1K2 myK1K2bytes;

};


#endif /* _INC_SP_K1K2RECEIVER_38FDCCBC01F0_INCLUDED */

