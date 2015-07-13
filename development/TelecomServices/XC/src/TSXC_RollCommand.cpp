/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     July, 2007  Kumar Solai
 DESCRIPTION:   TSXC_RollCommand  Implementation
--------------------------------------------------------------------------*/
#include <BaseClass/FC_TextStream.h>
#include <XC/TSXC_RollCommand.h>

//--------------------------------------------------------------------------------------------------
// Constructor
TSXC_RollCommand::TSXC_RollCommand():
myRollCommand(0),
myRollCommandID(0)
{
    myRollConnectKeyOne.aCKey = 0;
    myRollConnectKeyTwo.aCKey = 0;
    memset(&myRollInfo, 0, sizeof(TSXC_Roll_Info));
}

//Destructor
TSXC_RollCommand::~TSXC_RollCommand()
{
}

//--------------------------------------------------------------------------------------------------
//Methods to set object attributes
//--------------------------------------------------------------------------------------------------
void    TSXC_RollCommand::SetRollCommand(INT32 theCommand)
{
    myRollCommand = theCommand;    
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollCommand::SetRollCommandID(INT32 theCommandID)
{
    myRollCommandID = theCommandID;
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollCommand::SetRollConnectKeyOne(TSXC_Connection theCKey)
{
    myRollConnectKeyOne = theCKey;
}

//--------------------------------------------------------------------------------------------------
void    TSXC_RollCommand::SetRollConnectKeyTwo(TSXC_Connection theCKey)
{
    myRollConnectKeyTwo = theCKey;
}
//--------------------------------------------------------------------------------------------------
void    TSXC_RollCommand::SetRollInfo(TSXC_Roll_Info theRollInfo)
{
    myRollInfo = theRollInfo;
}

//--------------------------------------------------------------------------------------------------
//Methods to get object attributes
//--------------------------------------------------------------------------------------------------
TSXC_Connection TSXC_RollCommand::GetRollConnectKeyOne()
{
    return myRollConnectKeyOne;
}

TSXC_Connection TSXC_RollCommand::GetRollConnectKeyTwo()
{
    return myRollConnectKeyTwo;
}
//--------------------------------------------------------------------------------------------------
INT32   TSXC_RollCommand::GetRollCommand()
{ 
    return  myRollCommand; 
}

//--------------------------------------------------------------------------------------------------
INT32   TSXC_RollCommand::GetRollCommandID()
{
    return  myRollCommandID; 
}

//--------------------------------------------------------------------------------------------------
TSXC_Roll_Info  TSXC_RollCommand::GetRollInfo()
{
    return  myRollInfo;
}

//--------------------------------------------------------------------------------------------------
ostream& TSXC_RollCommand::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myRollCommand);
    theStream << FC_InsertVar(myRollCommandID);
    theStream << FC_InsertVar(myRollConnectKeyOne.aCKey);
    theStream << FC_InsertVar(myRollConnectKeyTwo.aCKey);
    theStream << FC_InsertVar(myRollInfo.OldSrcShelf);
    theStream << FC_InsertVar(myRollInfo.OldSrcSlot);
    theStream << FC_InsertVar(myRollInfo.NewSrcShelf);    
    theStream << FC_InsertVar(myRollInfo.NewSrcSlot);
    theStream << FC_InsertVar(myRollInfo.IsProtected);
    theStream << FC_InsertVar(myRollInfo.IsResponseExpected);
    theStream << FC_InsertVar(myRollInfo.RemoteSrcChan);                
    theStream << FC_InsertVar(myRollInfo.RemoteSrcSlot);                
    theStream << FC_InsertVar(myRollInfo.DestChanIndex);                    
    theStream << FC_InsertVar(myRollInfo.MulticastId);      
    return theStream;
}

//--------------------------------------------------------------------------------------------------
istream& TSXC_RollCommand::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myRollCommand);
    theStream >> FC_ExtractVar(myRollCommandID);
    theStream >> FC_ExtractVar(myRollConnectKeyOne.aCKey);
    theStream >> FC_ExtractVar(myRollConnectKeyTwo.aCKey);
    theStream >> FC_ExtractVar(myRollInfo.OldSrcShelf);    
    theStream >> FC_ExtractVar(myRollInfo.OldSrcSlot);
    theStream >> FC_ExtractVar(myRollInfo.NewSrcShelf);    
    theStream >> FC_ExtractVar(myRollInfo.NewSrcSlot);
    theStream >> FC_ExtractVar(myRollInfo.IsProtected);
    theStream >> FC_ExtractVar(myRollInfo.IsResponseExpected);
    theStream >> FC_ExtractVar(myRollInfo.RemoteSrcChan);                
    theStream >> FC_ExtractVar(myRollInfo.RemoteSrcSlot);                
    theStream >> FC_ExtractVar(myRollInfo.DestChanIndex);                    
    theStream >> FC_ExtractVar(myRollInfo.MulticastId);           
    return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollCommand::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << (myRollCommand);
    theStream << (myRollCommandID);
    theStream << (myRollConnectKeyOne.aCKey);
    theStream << (myRollConnectKeyTwo.aCKey);
    theStream << (myRollInfo.OldSrcShelf);
    theStream << (myRollInfo.OldSrcSlot);    
    theStream << (myRollInfo.NewSrcShelf);
    theStream << (myRollInfo.NewSrcSlot);    
    theStream << (myRollInfo.IsProtected);
    theStream << (myRollInfo.IsResponseExpected);
    theStream << (myRollInfo.RemoteSrcChan);                
    theStream << (myRollInfo.RemoteSrcSlot);                
    theStream << (myRollInfo.DestChanIndex);                    
    theStream << (myRollInfo.MulticastId);          
	return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollCommand::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> (myRollCommand);
    theStream >> (myRollCommandID);
    theStream >> (myRollConnectKeyOne.aCKey);
    theStream >> (myRollConnectKeyTwo.aCKey);
    theStream >> (myRollInfo.OldSrcShelf);    
    theStream >> (myRollInfo.OldSrcSlot);
    theStream >> (myRollInfo.NewSrcShelf);
    theStream >> (myRollInfo.NewSrcSlot);    
    theStream >> (myRollInfo.IsProtected);
    theStream >> (myRollInfo.IsResponseExpected);
    theStream >> (myRollInfo.RemoteSrcChan);                
    theStream >> (myRollInfo.RemoteSrcSlot);                
    theStream >> (myRollInfo.DestChanIndex);                    
    theStream >> (myRollInfo.MulticastId);    
    return theStream;
}
//--------------------------------------------------------------------------------------------------
