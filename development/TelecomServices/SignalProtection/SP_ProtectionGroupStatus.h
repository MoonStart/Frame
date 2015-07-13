// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_PROTECTIONGROUPSTATUS_38E0B0ED03C3_INCLUDED
#define _INC_SP_PROTECTIONGROUPSTATUS_38E0B0ED03C3_INCLUDED

#include <TelCommon/TEL_BbObjectBase.h>

//This is the base class of the protection group status. It 
//contains the status common to both types of protection. It 
//inherits for TEL_BbObject, which is a FC_BbObject.
//##ModelId=38E0B0ED03C3
class SP_ProtectionGroupStatus 
: public TEL_BbObjectBase
{
public:
	//Class destructor.
	//##ModelId=38E201EB01A7
	virtual ~SP_ProtectionGroupStatus();

	//Default constructor.
	//##ModelId=39ACEFA403DC
    SP_ProtectionGroupStatus();
	//Copy constructor.
	//##ModelId=39ACEFA50008
	SP_ProtectionGroupStatus(const SP_ProtectionGroupStatus& theStatus);
	//Comparison operator.
	//##ModelId=39ACEFA40382
    bool operator==(const SP_ProtectionGroupStatus& theStatus) const;
	//Assignment operator.
	//##ModelId=39ACEFA40332
    SP_ProtectionGroupStatus& operator=(const SP_ProtectionGroupStatus& theStatus);

	//Writes the attributes of the status to a stream.
	//##ModelId=3932D1CD00F6
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the status from a stream.
	//##ModelId=3932D1CD0056
    virtual istream& ReadObject( istream& theStream );
	//Writes the attributes of the status to a binary stream.
	//##ModelId=39ACEFA402CD
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the attributes of the status from a binary stream.
	//##ModelId=39ACEFA40223
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

};

#endif /* _INC_SP_PROTECTIONGROUPSTATUS_38E0B0ED03C3_INCLUDED */

