// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_K1K2Receiver.h"
#include <ErrorService/FC_Error.h>


//##ModelId=390583FB03C5
SP_K1K2Receiver::SP_K1K2Receiver()
{
}

//##ModelId=390583FC0023
SP_K1K2Receiver::~SP_K1K2Receiver()
{
}


//##ModelId=3B8BC9E60026
void SP_K1K2Receiver::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3B8BC9E503DC
FC_Stream& SP_K1K2Receiver::SnapshotWrite(FC_Stream& theStream)
{
	theStream << "    myK1K2bytes" << endl;
	myK1K2bytes.SnapshotWrite(theStream);
	return theStream;
}
