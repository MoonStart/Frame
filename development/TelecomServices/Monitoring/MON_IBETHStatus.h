//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_IBETHSTATUS_H
#define MON_IBETHSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_IBETH_Definitions.h>
#include "MON_Object.h"



class MON_IBETHStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_IBETHStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_IBETHStatus();

    // These methods are modifiers and accessors for 
    // the current state of the GCC Protocol Link
    CT_IBETH_LinkState GetProtocolLinkState() const;
    bool SetProtocolLinkState(CT_IBETH_LinkState theLinkState);

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
    CT_IBETH_LinkState myLinkState;


};

#endif 

