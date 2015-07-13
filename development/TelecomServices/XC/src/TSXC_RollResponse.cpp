// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../TSXC_RollResponse.h"
#include <BaseClass/FC_TextStream.h>

// -----------------------------------------------------------------------------------------------------
//  Constructor
TSXC_RollResponse::TSXC_RollResponse():
myRollResponse(0),
myRollCommandID(0)
{
}

// Destructor
TSXC_RollResponse::~TSXC_RollResponse()
{
}

// -----------------------------------------------------------------------------------------------------
// Methods to set object attributes
// -----------------------------------------------------------------------------------------------------
void TSXC_RollResponse::SetRollResponse(INT32 theResponse)
{
	myRollResponse = theResponse;
}

void TSXC_RollResponse::SetRollCommandID(INT32 theCommand)
{
	myRollCommandID = theCommand;
}

// -----------------------------------------------------------------------------------------------------
// Methods to get object attributes
// -----------------------------------------------------------------------------------------------------
INT32 TSXC_RollResponse::GetRollResponse()
{
	return myRollResponse;
}

INT32 TSXC_RollResponse::GetRollCommandID()
{
	return myRollCommandID;
}

// -----------------------------------------------------------------------------------------------------
ostream& TSXC_RollResponse::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myRollResponse);
    theStream<<FC_InsertVar(myRollCommandID);
	return theStream;
}

istream& TSXC_RollResponse::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myRollResponse);
    theStream>>FC_ExtractVar(myRollCommandID);
    return theStream;
}

// -----------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollResponse::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myRollResponse;
    theStream<<myRollCommandID;
	return theStream;
}

FC_Stream& TSXC_RollResponse::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myRollResponse;
    theStream>>myRollCommandID;
    return theStream;
}
