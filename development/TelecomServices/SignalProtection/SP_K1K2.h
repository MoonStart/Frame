// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_K1K2_38FF57EC03B5_INCLUDED
#define _INC_SP_K1K2_38FF57EC03B5_INCLUDED

#include "SP_Definitions.h"
#include <CommonTypes/CT_SignalProtection.h>
#include <BaseClass/FC_Object.h>

//This is a structure defining the field of the K1 and K2 
//bytes.
//##ModelId=38FF57EC03B5
class SP_K1K2 : public FC_Object
{
public:

	//Returns K1 bytes.
	//##ModelId=3BBC9B080368
    uint8 GetK1() const;
	//Returns K2 bytes.
	//##ModelId=3BBC9B080386
    uint8 GetK2() const;

	//Comparison operator.
    //##ModelId=39ACEFB201DD
    bool operator==(const SP_K1K2 &rhs) const;

	//Unequal operator.
	//##ModelId=3B8BC9D80256
    bool operator!=(const SP_K1K2 &rhs) const;

	//Assignment operator.
	//##ModelId=3B8BC9D8022E
    SP_K1K2& operator=(const SP_K1K2 &rhs);

	//b1-b4 of K1.
	//##ModelId=38FF5803021E
	SP_K1Request request;

	//b5-b8 of K1
	//##ModelId=38FF582F02AD
	CT_SP_NodeID destination;

	//b1-b4 of K2
	//##ModelId=38FF58350252
	CT_SP_NodeID source;

	//b5 of K2
	//##ModelId=38FF583900E5
	bool path;

	//b6-b8 of K2
	//##ModelId=38FF583C00FD
	SP_Status status;

	//Constructor.
	//##ModelId=390583F901AF
	SP_K1K2();

	//Copy constructor.
	//##ModelId=3B8BC9D80206
	SP_K1K2(const SP_K1K2& theK1K2);

	//Destructor.
	//##ModelId=390583F901B0
	virtual ~SP_K1K2();
	//Sends the K1K2 to a stream (debug).
	//##ModelId=3B8BC9D801D4
	virtual FC_Stream& SnapshotWrite(FC_Stream& theStream);

protected:
    
	//Sends the K1K2 to a stream.
	//##ModelId=3B8BC9D80198
    virtual ostream& WriteObject( ostream& theStream );
	//Extracts the K1K2 from a stream.
	//##ModelId=3B8BC9D80166
    virtual istream& ReadObject( istream& theStream );
	//Sends the K1K2 to a binary stream.
	//##ModelId=3B8BC9D8012A
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extracts the K1K2 from a binary stream.
	//##ModelId=3B8BC9D800F8
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

};

#endif /* _INC_SP_K1K2_38FF57EC03B5_INCLUDED */

