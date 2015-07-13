/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     November, 2008  Kumar Solai
 DESCRIPTION:   TSXC_RollStatus  Implementation
--------------------------------------------------------------------------*/
#include <BaseClass/FC_TextStream.h>
#include <XC/TSXC_RollStatus.h>

//--------------------------------------------------------------------------------------------------
// Constructor
TSXC_RollStatus::TSXC_RollStatus()
{
    Reset();
    memset(&myRollInfo, 0, sizeof(TSXC_Roll_Info));   
}

//Destructor
TSXC_RollStatus::~TSXC_RollStatus()
{
}

//--------------------------------------------------------------------------------------------------
//Methods to set object attributes
//--------------------------------------------------------------------------------------------------
void TSXC_RollStatus::Reset()
{
    myRollCommand = ROLL_CMD_NOREQ;
    myRollConnectAddKey.aCKey = 0;
    myRollConnectRmvKey.aCKey = 0;
    myRollCmdState = ROLL_CMD_IDLE;  
}

void TSXC_RollStatus::SetRollCommand(INT32 theCommand)
{
    myRollCommand = theCommand;    
}

void TSXC_RollStatus::SetRollCmdState(TSXC_RollCmdFsmState theRollCmdState)
{
    myRollCmdState = theRollCmdState;    
}

void TSXC_RollStatus::SetRollConnectAddKey(TSXC_Connection theConnKey)
{
    myRollConnectAddKey = theConnKey;
}

void TSXC_RollStatus::SetRollConnectRmvKey(TSXC_Connection theConnKey)
{
    myRollConnectRmvKey = theConnKey;
}

void TSXC_RollStatus::SetRollInfo(TSXC_Roll_Info theRollInfo)
{
    myRollInfo = theRollInfo;
}

//--------------------------------------------------------------------------------------------------
//--- The TSXC cfg action should use this method to apply this filter for the activation flag.
//--- If no Roll command is active then theActiveflag will not be modified
//--- if that connection is protected then theActiveflag will not be modified.
//--- if Roll command is active for the unprotected connection then theActiveflag is modified  
//--- based on the Roll command and the state. 
//--------------------------------------------------------------------------------------------------
void TSXC_RollStatus::ApplyRollFilterForActivation(uint8 theSrc, uint8 theSrcEndPt, uint8 theDst, uint8 theDstEndPt, bool* theActiveFlag)
{
    TSXC_Connection aConnKey;
    aConnKey.aCE.srcFacPort = theSrc;
    aConnKey.aCE.srcFacChan = theSrcEndPt;
    aConnKey.aCE.dstFacPort = theDst;
    aConnKey.aCE.dstFacChan = theDstEndPt;
    
    if ((myRollCmdState == ROLL_CMD_INPROGRESS) && *theActiveFlag)
    {
        //--- The Rmv key is matched then mute the TX 
        if (aConnKey.aCKey == myRollConnectRmvKey.aCKey)
        {
            *theActiveFlag = false;
            //fc_cout << "Filter Deactivates RMV" << endl;
        }
        else if (aConnKey.aCKey == myRollConnectAddKey.aCKey && ROLL_CMD_REQ_ADD == myRollCommand)
        {
            //fc_cout << "Filter Deactivates ADD" << endl;
            *theActiveFlag = false;
        }
    }       
}

//--------------------------------------------------------------------------------------------------
//Methods to get object attributes
//--------------------------------------------------------------------------------------------------

INT32 TSXC_RollStatus::GetRollCommand()
{ 
    return  myRollCommand; 
}

TSXC_Connection TSXC_RollStatus::GetRollConnectAddKey()
{
    return  myRollConnectAddKey;     
}

TSXC_Connection TSXC_RollStatus::GetRollConnectRmvKey()
{
    return  myRollConnectRmvKey; 
}

TSXC_Roll_Info  TSXC_RollStatus::GetRollInfo()
{
    return  myRollInfo; 
}

TSXC_RollCmdFsmState TSXC_RollStatus::GetRollCmdState()
{
    return  myRollCmdState; 
}
    
//--------------------------------------------------------------------------------------------------
ostream& TSXC_RollStatus::WriteObject( ostream& theStream )
{
    uint8 tmpCmdState = (uint8) myRollCmdState;
    theStream << FC_InsertVar(myRollCommand);    
    theStream << FC_InsertVar(myRollConnectAddKey.aCKey);
    theStream << FC_InsertVar(myRollConnectRmvKey.aCKey);
    theStream << FC_InsertVar(myRollInfo.OldSrcShelf);
    theStream << FC_InsertVar(myRollInfo.OldSrcSlot);
    theStream << FC_InsertVar(myRollInfo.NewSrcShelf);    
    theStream << FC_InsertVar(myRollInfo.NewSrcSlot);
    theStream << FC_InsertVar(myRollInfo.IsProtected);
    theStream << FC_InsertVar(myRollInfo.IsResponseExpected);
    theStream << FC_InsertVar(tmpCmdState);   
    return theStream;
}

//--------------------------------------------------------------------------------------------------
istream& TSXC_RollStatus::ReadObject( istream& theStream )
{
    uint8 tmpCmdState;
    theStream >> FC_ExtractVar(myRollCommand);
    theStream >> FC_ExtractVar(myRollConnectAddKey.aCKey);
    theStream >> FC_ExtractVar(myRollConnectRmvKey.aCKey);
    theStream >> FC_ExtractVar(myRollInfo.OldSrcShelf);    
    theStream >> FC_ExtractVar(myRollInfo.OldSrcSlot);
    theStream >> FC_ExtractVar(myRollInfo.NewSrcShelf);    
    theStream >> FC_ExtractVar(myRollInfo.NewSrcSlot);
    theStream >> FC_ExtractVar(myRollInfo.IsProtected);
    theStream >> FC_ExtractVar(myRollInfo.IsResponseExpected);
    theStream >> FC_ExtractVar(tmpCmdState);
    myRollCmdState = (TSXC_RollCmdFsmState) tmpCmdState;
    return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollStatus::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << (myRollCommand);
    theStream << (myRollConnectAddKey.aCKey);
    theStream << (myRollConnectRmvKey.aCKey);
    theStream << (myRollInfo.OldSrcShelf);
    theStream << (myRollInfo.OldSrcSlot);    
    theStream << (myRollInfo.NewSrcShelf);
    theStream << (myRollInfo.NewSrcSlot);    
    theStream << (myRollInfo.IsProtected);
    theStream << (myRollInfo.IsResponseExpected);
    theStream << (myRollCmdState);          
	return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_RollStatus::ReadObjectBinary( FC_Stream& theStream )
{
    uint8 tmpCmdState;
    theStream >> (myRollCommand);
    theStream >> (myRollConnectAddKey.aCKey);
    theStream >> (myRollConnectRmvKey.aCKey);
    theStream >> (myRollInfo.OldSrcShelf);    
    theStream >> (myRollInfo.OldSrcSlot);
    theStream >> (myRollInfo.NewSrcShelf);
    theStream >> (myRollInfo.NewSrcSlot);    
    theStream >> (myRollInfo.IsProtected);
    theStream >> (myRollInfo.IsResponseExpected);
    theStream >> (tmpCmdState);
    myRollCmdState = (TSXC_RollCmdFsmState) tmpCmdState;              
    return theStream;
}
//--------------------------------------------------------------------------------------------------
