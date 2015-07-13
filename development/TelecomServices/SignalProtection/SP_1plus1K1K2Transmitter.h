// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1K1K2TRANSMITTER_38FDC7E30105_INCLUDED
#define _INC_SP_1PLUS1K1K2TRANSMITTER_38FDC7E30105_INCLUDED

#include "SP_K1K2Transmitter.h"
#include "SP_Definitions.h"

class SP_1plus1ProtectionAction;

//This class is responsible for setting the K1K2 bytes to 
//transmit for the Linear 1+1 protocol.
//##ModelId=38FDC7E30105
class SP_1plus1K1K2Transmitter 
: public SP_K1K2Transmitter
{
public:
	//Sets the request to transmit of the protection facility 
	//K1K2 bytes.
	//##ModelId=39059FDE01F5
	void SetRequest(SP_K1Request theRequest);

	//Constructor. Takes a protection action.
	//##ModelId=390584020003
	SP_1plus1K1K2Transmitter(SP_1plus1ProtectionAction& theProtectionAction);

	//Destructor.
	//##ModelId=39058402002B
	virtual ~SP_1plus1K1K2Transmitter();

	//Sets the APS channel number to transmit on the 
	//protection facility K1K2 bytes.
	//##ModelId=3905A66900F9
	void SetAPSChannel(CT_SP_Protection theChannel);


	//This method is updates the value K1K2 bytes to transmit 
	//in the CFG_ProtObject of the right facility (according 
	//to configuration).
	//##ModelId=39170C490169
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Calls base class method.
	//##ModelId=3B8BCA030191
    virtual bool HasChangedSinceLastCheck();

	//Does nothing.
	//##ModelId=3B8BCA030190
    void Reset();

protected:
	//Sends the K1K2 byte to a stream.
	//##ModelId=3B8BCA03017C
    virtual ostream& WriteObject( ostream& theStream );
	//Extract the K1K2 byte from a stream.
	//##ModelId=3B8BCA03015E
    virtual istream& ReadObject( istream& theStream );
	//Sends the K1K2 byte to a binary stream.
	//##ModelId=3B8BCA03014A
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extract the K1K2 byte from a binary stream.
	//##ModelId=3B8BCA03012C
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	//Reference to its protection action.
	//##ModelId=39170C49014B
    SP_1plus1ProtectionAction& myProtectionAction;
};

#endif /* _INC_SP_1PLUS1K1K2TRANSMITTER_38FDC7E30105_INCLUDED */

