// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SELECTOR_38F4D8A10028_INCLUDED
#define _INC_SP_SELECTOR_38F4D8A10028_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include "SP_ProtectionAction.h"

#include <ErrorService/FC_Error.h>


//This is the base class for the signal protection switch 
//selector.
//##ModelId=38F4D8A10028
class SP_Selector 
: public FC_Action
{
public:
	//This method removes any previous connections. This 
	//method is abstract.
	//##ModelId=38F75C0E01E0
	virtual void ClearConnections() = 0;

	//Default constructor.
	//##ModelId=38FB096B0363
	SP_Selector();

	//Destructor.
	//##ModelId=38FB096B0377
	virtual ~SP_Selector();

	//Not supported.
	//##ModelId=3B8BCA020167
    virtual void Run( FC_Object* theObject = NULL );
	//Does nothing.
	//##ModelId=3B8BCA020116
	virtual FC_Stream& SnapshotWrite(FC_Stream& theStream);

protected:
	//Returns false.
	//##ModelId=3B8BCA020102
    inline virtual bool HasChangedSinceLastCheck() { return false; }

	//Does nothing.
	//##ModelId=3B8BCA0200B2
    inline virtual ostream& WriteObject( ostream& theStream ) { return theStream; }
	//Does nothing.
	//##ModelId=3B8BCA020062
    inline virtual istream& ReadObject( istream& theStream ) { return theStream; }
	//Does nothing.
	//##ModelId=3B8BCA02001C
	inline virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream ) { return theStream; }
	//Does nothing.
	//##ModelId=3B8BCA0103BE
    inline virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream ) { return theStream; }


private:
	//Returns a reference to the protection action.
	//##ModelId=3B8BCA01027D
    virtual SP_ProtectionAction& GetProtectionAction() = 0;
};

#endif /* _INC_SP_SELECTOR_38F4D8A10028_INCLUDED */

