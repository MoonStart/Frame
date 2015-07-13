/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     November, 2008  Kumar Solai
 DESCRIPTION:   TSXC_RollRxStatus  Implementation
--------------------------------------------------------------------------*/
#include <BaseClass/FC_TextStream.h>
#include <XC/TSXC_RollRxStatus.h>

//--------------------------------------------------------------------------------------------------
// Constructor
TSXC_RollRxStatus::TSXC_RollRxStatus()
{
    Reset();
}

//Destructor
TSXC_RollRxStatus::~TSXC_RollRxStatus()
{
}

//--------------------------------------------------------------------------------------------------
//Methods to set object attributes
//--------------------------------------------------------------------------------------------------
void    TSXC_RollRxStatus::SetRollCommand(INT32 theCommand)
{
    myRollCommand = theCommand;    
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollRxStatus::SetRollCommandID(INT32 theCommandID)
{
    myRollCommandID = theCommandID;    
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollRxStatus::SetRollMsgSent(INT32 theMsgSent)
{
    myRollMsgSent = theMsgSent;
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollRxStatus::SetRollMsgRcvd(INT32 theMsgRcvd)
{
    myRollMsgRcvd = theMsgRcvd; 
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollRxStatus::Reset()
{
    myRollCommand = 0;
    myRollCommandID = 0;
    myRollMsgSent = 0;
    myRollMsgRcvd = 0; 
}    
//--------------------------------------------------------------------------------------------------
//Methods to get object attributes
//--------------------------------------------------------------------------------------------------

INT32   TSXC_RollRxStatus::GetRollCommand()
{ 
    return  myRollCommand; 
}
//--------------------------------------------------------------------------------------------------
INT32   TSXC_RollRxStatus::GetRollCommandID()
{ 
    return  myRollCommandID; 
}
//--------------------------------------------------------------------------------------------------

INT32   TSXC_RollRxStatus::GetRollMsgSent()
{ 
    return  myRollMsgSent; 
}
//--------------------------------------------------------------------------------------------------
INT32   TSXC_RollRxStatus::GetRollMsgRcvd()
{ 
    return  myRollMsgRcvd; 
}
//--------------------------------------------------------------------------------------------------
ostream& TSXC_RollRxStatus::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myRollCommand);    
    theStream << FC_InsertVar(myRollCommandID);
    theStream << FC_InsertVar(myRollMsgSent);
    theStream << FC_InsertVar(myRollMsgRcvd);
    return theStream;
}

//--------------------------------------------------------------------------------------------------
istream& TSXC_RollRxStatus::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myRollCommand);
    theStream >> FC_ExtractVar(myRollCommandID);
    theStream >> FC_ExtractVar(myRollMsgSent);
    theStream >> FC_ExtractVar(myRollMsgRcvd);
    return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollRxStatus::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << (myRollCommand);
    theStream << (myRollCommandID);
    theStream << (myRollMsgSent);
    theStream << (myRollMsgRcvd);
	return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollRxStatus::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> (myRollCommand);
    theStream >> (myRollCommandID);
    theStream >> (myRollMsgSent);
    theStream >> (myRollMsgRcvd);            
    return theStream;
}
//--------------------------------------------------------------------------------------------------
