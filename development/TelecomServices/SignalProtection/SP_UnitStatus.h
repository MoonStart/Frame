// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_UNITSTATUS_38E11D1D00E3_INCLUDED
#define _INC_SP_UNITSTATUS_38E11D1D00E3_INCLUDED

#include <CommonTypes/CT_SignalProtection.h>
#include <Blackboard/FC_BbObject.h>
#include "SP_Definitions.h"

//This class defines a set of status information common to 
//both type of protection group. It is a base class for unit 
//status. It is a blackboard object.
//##ModelId=38E11D1D00E3
class SP_UnitStatus : public FC_BbObject
{
public:
	//Class constructor.
	//##ModelId=38E201F10368
	SP_UnitStatus();

	//Constructor.
	//##ModelId=3932D1E000FD
	SP_UnitStatus(const SP_UnitStatus& theUnit);

	//Assignment operator.
	//##ModelId=39ACEFB7027B
    SP_UnitStatus& operator=(const SP_UnitStatus& theUnit);
	//Comparison operator.
	//##ModelId=39ACEFB701DA
    bool operator==(const SP_UnitStatus& theUnit) const;

	//Class destructor.
	//##ModelId=38E201F103A4
	virtual ~SP_UnitStatus();

	//Resets the content of the unit status to default. 
	//Should be specialized by derived classes.
	//##ModelId=3B8BC9DE0327
    virtual void Init(restart_type theRestartType);

protected:
	//Method to send the object into a stream.
	//##ModelId=3932D1DF034B
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the unit status from a stream.
	//##ModelId=3932D1DF01E2
    virtual istream& ReadObject( istream& theStream );
	//Method to send the object into a binary stream.
	//##ModelId=39ACEFB700CC
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Method to extract the object from a binary stream.
	//##ModelId=39ACEFB70018
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:


};

#endif /* _INC_SP_UNITSTATUS_38E11D1D00E3_INCLUDED */

