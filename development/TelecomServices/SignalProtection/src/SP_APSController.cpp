// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_APSController.h"
#include "../SP_RequestParser.h"
#include "../SP_Selector.h"
#include "../SP_ProtectionAction.h"
#include <BaseClass/FC_TextStream.h>
#include <Blackboard/FC_BbAction.h>

//##ModelId=38FB09630339
SP_APSController::SP_APSController(SP_ProtectionAction& theAction):
    myWTRTimer(*theAction.GetBbAction()),
    myStateMachineIsStable(true)
{
}

//##ModelId=38FB0963034D
SP_APSController::~SP_APSController()
{
}

//##ModelId=3B8BC9C700E9
ostream& SP_APSController::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myWTRTimer);
}

//##ModelId=3B8BC9C70099
istream& SP_APSController::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myWTRTimer);
}

//##ModelId=3B8BC9C7003F
FC_Stream& SP_APSController::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream << myWTRTimer;
}

//##ModelId=3B8BC9C603D7
FC_Stream& SP_APSController::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream >> myWTRTimer;
}

//##ModelId=3B8BC9C70144
bool SP_APSController::HasChangedSinceLastCheck()
{
    return myWTRTimer.HasChangedSinceLastCheck();
}

//##ModelId=3B8BC9C70176
FC_Stream& SP_APSController::SnapshotWrite(FC_Stream& theStream)
{
	return theStream;
}
