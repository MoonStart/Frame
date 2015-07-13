// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_K1K2Transmitter.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>

//##ModelId=38FB0964015A
SP_K1K2Transmitter::SP_K1K2Transmitter()
{
}

//##ModelId=38FB09640164
SP_K1K2Transmitter::~SP_K1K2Transmitter()
{
}


//##ModelId=3B8BC9CB009F
ostream& SP_K1K2Transmitter::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myK1K2bytes);

    return theStream;
}

//##ModelId=3B8BC9CB0059
istream& SP_K1K2Transmitter::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myK1K2bytes);

    myLastK1K2bytes = myK1K2bytes;

    return theStream;
}

//##ModelId=3B8BC9CB0013
FC_Stream& SP_K1K2Transmitter::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myK1K2bytes;

    return theStream;
}

//##ModelId=3B8BC9CA03B5
FC_Stream& SP_K1K2Transmitter::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myK1K2bytes;

    myLastK1K2bytes = myK1K2bytes;

    return theStream;
}

//##ModelId=3B8BC9CB017B
bool SP_K1K2Transmitter::HasChangedSinceLastCheck()
{
    if (myLastK1K2bytes != myK1K2bytes)
    {
        myLastK1K2bytes = myK1K2bytes;
        return true;
    }
    else
    {
        return false;
    }
}

//##ModelId=3B8BC9CB012B
void SP_K1K2Transmitter::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3B8BC9CB00E5
FC_Stream& SP_K1K2Transmitter::SnapshotWrite(FC_Stream& theStream)
{
	theStream << "    myK1K2bytes" << endl;
	myK1K2bytes.SnapshotWrite(theStream);
	theStream << "    myLastK1K2bytes" << endl;
	myLastK1K2bytes.SnapshotWrite(theStream);
	return theStream;
}
