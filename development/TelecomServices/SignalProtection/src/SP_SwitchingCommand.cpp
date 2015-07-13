// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SwitchingCommand.h"
#include <BaseClass/FC_TextStream.h>


//##ModelId=38DFC0FF0232
CT_SP_CommandID SP_SwitchingCommand::SetCommand(CT_SP_Request theCommand, bool incCommandId)
{
	if (incCommandId &&
		myCommand != theCommand)
        myCommandID++;

    myCommand = theCommand;
    return myCommandID;
}

//##ModelId=38DFCFDC03D8
SP_SwitchingCommand::SP_SwitchingCommand() : myCommand(CT_SP_NO_REQUEST), myCommandID(NULL)
{
}

//##ModelId=38E0AF7D0284
CT_SP_Request& SP_SwitchingCommand::GetCommand()
{
    return myCommand;
}

//##ModelId=3911AE76001D
CT_SP_CommandID& SP_SwitchingCommand::GetCommandID()
{
    return myCommandID;
}

    //##ModelId=38E201EC018A
SP_SwitchingCommand::~SP_SwitchingCommand()
{
}


//##ModelId=3932D1D40150
ostream& SP_SwitchingCommand::WriteObject( ostream& theStream )
{
	theStream<<FC_InsertVar(myCommand);
	theStream<<FC_InsertVar(myCommandID);

    return theStream;
}

//##ModelId=3932D1D400EC
istream& SP_SwitchingCommand::ReadObject( istream& theStream )
{
	theStream>>FC_ExtractVar(myCommand);
	theStream>>FC_ExtractVar(myCommandID);

    return theStream;
}

//##ModelId=39ACEFAA0087
FC_Stream& SP_SwitchingCommand::WriteObjectBinary( FC_Stream& theStream )
{
	theStream<<myCommand;
	theStream<<myCommandID;

    return theStream;
}

//##ModelId=39ACEFAA0055
FC_Stream& SP_SwitchingCommand::ReadObjectBinary( FC_Stream& theStream )
{
	theStream>>myCommand;
	theStream>>myCommandID;

    return theStream;
}
