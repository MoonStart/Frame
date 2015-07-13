/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:   T6100 Software Service
TARGET:          

-----------------------------------------------------------------------------*/ 
#include <BaseClass/FC_TextStream.h>

#include "../SP_ERSSwitchRegion.h"

using namespace std;


SP_ERSSwitchCommand::SP_ERSSwitchCommand(void): 
	myCommand(CT_SP_NO_REQUEST),
	myCommandID(CT_SP_INVALID_COMMAND)
{
}

SP_ERSSwitchCommand::~SP_ERSSwitchCommand()
{
}

CT_SP_CommandID SP_ERSSwitchCommand::SetCommand(CT_SP_Request theCommand, bool incCommandId)
{
    if (incCommandId &&
	    myCommand != theCommand)
	{
        myCommandID++;
	}

    myCommand = theCommand;
    return myCommandID;
}

CT_SP_Request SP_ERSSwitchCommand::GetCommand()
{
	return myCommand;
}

CT_SP_CommandID SP_ERSSwitchCommand::GetCommandID()
{
	return myCommandID;
}

//-----------------------------------------------------------------------------
ostream& SP_ERSSwitchCommand::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myCommand);
	theStream << FC_InsertVar(myCommandID);
    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& SP_ERSSwitchCommand::WriteObjectBinary( FC_Stream& theStream )
{
    theStream <<myCommand;
	theStream <<myCommandID;
    return theStream;
}

//-----------------------------------------------------------------------------
istream& SP_ERSSwitchCommand::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myCommand);
	theStream >> FC_ExtractVar(myCommandID);
    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& SP_ERSSwitchCommand::ReadObjectBinary( FC_Stream& theStream )
{
	
    theStream >> myCommand;
	theStream >> myCommandID;
    return theStream;
}

//-----------------------------------------------------------------------------
SP_ERSSwitchRegion::SP_ERSSwitchRegion(FC_BbKey theKey):
    FC_BbRegionVectImp<SP_ERSSwitchCommand>(theKey, 1)
{
    
}

SP_ERSSwitchRegion::~SP_ERSSwitchRegion()
{
}

//Add other methods here
CT_SP_CommandID SP_ERSSwitchRegion::SetCommand(CT_SP_Request theCommand)
{
	return ((*this)[0].SetCommand(theCommand));
}
CT_SP_Request SP_ERSSwitchRegion::GetCommand()
{
	return (*this)[0].GetCommand();
}
CT_SP_CommandID SP_ERSSwitchRegion::GetCommandID()
{
	return (*this)[0].GetCommandID();
}
