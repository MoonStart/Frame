// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_Selector.h"


//##ModelId=38FB096B0363
SP_Selector::SP_Selector()
{
}

//##ModelId=38FB096B0377
SP_Selector::~SP_Selector()
{
}

//##ModelId=3B8BCA020167
void SP_Selector::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3B8BCA020116
FC_Stream& SP_Selector::SnapshotWrite(FC_Stream& theStream)
{
	return theStream;
}

