// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SwitchingCommandResult.h"
#include <BaseClass/FC_TextStream.h>


//##ModelId=38DFCBD90074
CT_SP_CommandID SP_SwitchingCommandResult::GetCommandStatus(CT_SP_CommandResultCode& theResult)
{
    theResult = myResult;
    return myCommandID;
}

//##ModelId=38DFD00F011F
SP_SwitchingCommandResult::SP_SwitchingCommandResult():
    myResult(CT_SP_COMMAND_FAILED),
    myCommandID(CT_SP_INVALID_COMMAND)
{
}

//##ModelId=39ACEFBA0365
    SP_SwitchingCommandResult::SP_SwitchingCommandResult(const SP_SwitchingCommandResult& theComandResult):
    myResult(theComandResult.myResult),
    myCommandID(theComandResult.myCommandID)
{
}

//##ModelId=39ACEFBA0301
bool SP_SwitchingCommandResult::operator==(const SP_SwitchingCommandResult& theComandResult) const
{
    return ((myResult==theComandResult.myResult) && (myCommandID==theComandResult.myCommandID));
}

//##ModelId=39ACEFBA02CF
SP_SwitchingCommandResult& SP_SwitchingCommandResult::operator=(const SP_SwitchingCommandResult& theComandResult)
{
    myResult = theComandResult.myResult;
    myCommandID = theComandResult.myCommandID;

    return *this;
}


//##ModelId=38E201F20066
SP_SwitchingCommandResult::~SP_SwitchingCommandResult()
{
}

//##ModelId=38EDEA6D0329
void SP_SwitchingCommandResult::SetCommandStatus(CT_SP_CommandResultCode theResult, CT_SP_CommandID theCommandID)
{
    myResult= theResult;
    myCommandID = theCommandID;
}


//##ModelId=3932D1E10394
ostream& SP_SwitchingCommandResult::WriteObject( ostream& theStream )
{
	theStream<<FC_InsertVar(myCommandID);
	theStream<<FC_InsertVar(myResult);
    return theStream;
}

//##ModelId=3932D1E10325
istream& SP_SwitchingCommandResult::ReadObject( istream& theStream )
{
	theStream>>FC_ExtractVar(myCommandID);
	theStream>>FC_ExtractVar(myResult);

    return theStream;
}

//##ModelId=39ACEFBA026B
FC_Stream& SP_SwitchingCommandResult::WriteObjectBinary( FC_Stream& theStream )
{
	theStream<<myCommandID;
	theStream<<myResult;
    return theStream;
}

//##ModelId=39ACEFBA021B
FC_Stream& SP_SwitchingCommandResult::ReadObjectBinary( FC_Stream& theStream )
{
	theStream>>myCommandID;
	theStream>>myResult;

    return theStream;
}
