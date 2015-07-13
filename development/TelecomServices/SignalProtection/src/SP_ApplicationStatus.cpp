/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Protect
 TARGET   :     All
--------------------------------------------------------------------------*/



//#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>
#include <../SP_ApplicationStatus.h>


// *************
// Constructor
// *************
SP_ApplicationStatus::SP_ApplicationStatus():
    myReadyState(false)
{
}

// *************
// Destructor
// *************
SP_ApplicationStatus::~SP_ApplicationStatus()
{
}

// *************
// Set Methods
// *************
void SP_ApplicationStatus::SetApplicationStatus(bool status)
{
	myReadyState = status;
}
    
// *************
// Get Methods
// *************
bool SP_ApplicationStatus::IsReady()
{
    return myReadyState;
}

bool SP_ApplicationStatus::IsStatusDifferent(bool newStatus)
{
	if (myReadyState != newStatus)
		return true;
	else
		return false;
}

// *********************
// Serialization Methods
// *********************

ostream& SP_ApplicationStatus::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myReadyState);

    return theStream;
}

istream& SP_ApplicationStatus::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myReadyState);

    return theStream;
}

FC_Stream& SP_ApplicationStatus::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myReadyState;

    return theStream;
}

FC_Stream& SP_ApplicationStatus::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myReadyState;
    
    return theStream;
}


