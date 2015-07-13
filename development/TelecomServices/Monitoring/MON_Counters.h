// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_COUNTERS_3C1785F30086_INCLUDED
#define _INC_MON_COUNTERS_3C1785F30086_INCLUDED

#include "MON_Object.h"

//This is the base class for counters monitoring. It is a 
//MON_Object.
//##ModelId=3C1785F30086
class MON_Counters 
: public MON_Object
{
public:
	//Constructor.
	//##ModelId=3C17861300BE
	MON_Counters(uint32 theIndex);

	//Virtual destructor.
	//##ModelId=3C17861300C8
	virtual ~MON_Counters(void );

	//##ModelId=3C17861300E8
	virtual void GetErrorCount(CT_TEL_Register theRegister, uint32* theCount) const = 0;
	//##ModelId=3C18E936004C
	virtual void SetErrorCount(CT_TEL_Register theRegister, uint32 theCount) = 0;

protected:
	//##ModelId=3C17861300D2
	virtual ostream& WriteObject(ostream& theStream);

	//##ModelId=3C17861300D4
	virtual istream& ReadObject(istream& theStream);

	//##ModelId=3C17861300DC
	virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);

	//##ModelId=3C17861300E6
	virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);

};

#endif /* _INC_MON_COUNTERS_3C1785F30086_INCLUDED */
