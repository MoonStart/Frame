//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_GCCSTATUS_H
#define MON_GCCSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include "MON_Object.h"


//This class hold the status values for the GCC layer.
class MON_GccStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_GccStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_GccStatus();

    // These methods are modifiers and accessors for 
    // the current state of the GCC Protocol Link
    CT_DCC_LinkState GetProtocolLinkState() const;
    bool SetProtocolLinkState(CT_DCC_LinkState theLinkState);

    // These methods are modifiers and accessors for 
    // the current state of the GCC Tunnel Session
    bool GetTunnelSessionState() const;
    bool SetTunnelSessionState(bool theTunnelState);

    // These methods are modifiers and accessors for 
    // the current Magic Number
    uint32 GetMagicNumber() const; 
    bool SetMagicNumber(uint32 theMagicNumber);

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

    //The current state of the GCC Protocol Link.
    CT_DCC_LinkState myLinkState;

    //The current state of the GCC Tunnel Session.
    bool myTunnelState;

    //The current Magic Number.
    uint32 myMagicNumber;

};

#endif /* MON_GCCSTATUS_H */

