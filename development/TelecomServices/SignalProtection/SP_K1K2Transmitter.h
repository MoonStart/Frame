// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_K1K2TRANSMITTER_38F5D2890220_INCLUDED
#define _INC_SP_K1K2TRANSMITTER_38F5D2890220_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include "SP_K1K2.h"

//This is the base class for the K1K2 bytes transmitter. It 
//holds the K1K2 byte to transmit and provides interface to 
//compared status and request.
//##ModelId=38F5D2890220
class SP_K1K2Transmitter 
: public FC_Action
{
public:
	//Default constructor.
	//##ModelId=38FB0964015A
	SP_K1K2Transmitter();

	//Destructor.
	//##ModelId=38FB09640164
	virtual ~SP_K1K2Transmitter();

	//Returns the K1K2 bytes transmitted.
	//##ModelId=39ACEFAC01C1
    inline SP_K1K2 GetTransmittedKbytes() const{return myK1K2bytes;};

	//Returns true if request is identical to given one.
	//##ModelId=39ACEFAC0198
    inline bool RequestIsEqualTo(SP_K1Request theComparedRequest) const { return myK1K2bytes.request == theComparedRequest;};
	//Returns true if request is different from given one.
	//##ModelId=39ACEFAC015C
    inline bool RequestIsDifferentThan(SP_K1Request theComparedRequest) const {return myK1K2bytes.request != theComparedRequest;};

	//Returns true if status is identical to given one.
	//##ModelId=39ACEFAC012A
    inline bool StatusIsEqualTo(SP_Status theComparedStatus) const { return myK1K2bytes.status == theComparedStatus;};
	//Returns true if status is different from given one.
	//##ModelId=39ACEFAC00E4
    inline bool StatusIsDifferentThan(SP_Status theComparedStatus) const {return myK1K2bytes.status != theComparedStatus;};
    
	//Returns true if K1K2 value as changes since last call.
	//##ModelId=3B8BC9CB017B
    virtual bool HasChangedSinceLastCheck();

	//Not supported.
	//##ModelId=3B8BC9CB012B
    virtual void Run( FC_Object* theObject = NULL );
	//Sends the K1K2 to a stream (debug).
	//##ModelId=3B8BC9CB00E5
	virtual FC_Stream& SnapshotWrite(FC_Stream& theStream);

protected:
	//The current K1 and K2 value being transmitted on the 
	//protection facility.
	//##ModelId=39170C350233
	SP_K1K2 myK1K2bytes;

	//The value of K1K2 when the transmitter was checked for 
	//changes.
	//##ModelId=3B8BC9CA03AB
  	SP_K1K2 myLastK1K2bytes;

	//Sends the K1K2 to a stream.
	//##ModelId=3B8BC9CB009F
    virtual ostream& WriteObject( ostream& theStream );
	//Extracts the K1K2 from a stream.
	//##ModelId=3B8BC9CB0059
    virtual istream& ReadObject( istream& theStream );
	//Sends the K1K2 to a binary stream.
	//##ModelId=3B8BC9CB0013
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extracts the K1K2 from a binary stream.
	//##ModelId=3B8BC9CA03B5
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

};

#endif /* _INC_SP_K1K2TRANSMITTER_38F5D2890220_INCLUDED */

