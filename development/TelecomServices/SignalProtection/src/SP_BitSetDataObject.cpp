// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_BitSetDataObject.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <../SP_Utilities.h>


SP_BitSetDataObject::SP_BitSetDataObject()
{
    myBitSet =0;
}

SP_BitSetDataObject::~SP_BitSetDataObject()
{
}


bool SP_BitSetDataObject::Set(uint32 theMask)
{
    if (IsSet(theMask))
        return false;
    
    myBitSet |= theMask;
    return true;
}
bool SP_BitSetDataObject::IsSet(uint32 theMask)
{
    if ( (myBitSet & theMask) == theMask)
        return true;

    return false;
}
bool SP_BitSetDataObject::Clear(uint32 theMask)
{
    if (IsSet(theMask))
    {
        myBitSet &= ~(theMask);
        return true;
    }

    return false;
}

ostream& SP_BitSetDataObject::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myBitSet);
    return theStream;
}

istream& SP_BitSetDataObject::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myBitSet);
    return theStream;
}

FC_Stream& SP_BitSetDataObject::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myBitSet;
    return theStream;
}

FC_Stream& SP_BitSetDataObject::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream >> myBitSet;
    return theStream;
}
