// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_STATUS_
#define _MON_STATUS_

#include "MON_Object.h"

//This is the base class for status monitoring. It is a MON_Object.
class MON_Status 
: public MON_Object
{
public:
	//Constructor.
	MON_Status(uint32 theIndex);

	//Virtual destructor.
	virtual ~MON_Status();

   	//Returns the level of the status provide as argument.
	virtual void GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const = 0;

    //Returns true if level has changed.
    virtual bool SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel) = 0;

protected:

	virtual ostream& WriteObject(ostream& theStream);

	virtual istream& ReadObject(istream& theStream);

	virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);

	virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);

};


#endif /* _MON_STATUS_*/
