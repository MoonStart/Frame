// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_1plus1Selector.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_SwitchingStatistic.h"
#include "../SP_1plus1RequestParser.h"
#include <BaseClass/FC_TextStream.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <Configuration/CFG_OptProt.h>
#include <TimeService/FC_TimePrecise.h>
#include <CsPii/CSPII_CardIF.h>

extern int gSP_DebugTraceYcable;

void SP_1plus1Selector::ClearConnections()
{
    // reset to working
    mySelection = CT_SP_WORKING_SIDE;
    // Set it the same as mySelection in order not to increment switching stats
    myPreviousSelection = mySelection;

    // refresh HW accordingly
    RunWithReason(0,NULL,NULL);
}

SP_1plus1Selector::SP_1plus1Selector(SP_1plus1ProtectionAction& theProtectionAction):
    myProtectionAction(theProtectionAction),
    mySelection(CT_SP_WORKING_SIDE),
    myPreviousSelection(CT_SP_WORKING_SIDE),
    mySelectionHistory(CT_SP_WORKING_SIDE)
{
}

SP_1plus1Selector::~SP_1plus1Selector()
{
}

void SP_1plus1Selector::Reset()
{
    ClearConnections();
}

FC_Object*  SP_1plus1Selector::DoRunWithReason(unsigned theRunReason,
                                                       FC_Object* theInvokerObj,
                                                       FC_Object* theParam)
{
    // Activate the H/W
    Switch();

	//Commit the switch for all operations other than upsr defects on SMTM
	//This command has no effect on the OPSM or RAM
	//The commit is used on the SMTM for performance reasons
	if (theRunReason != SP_DEFECT_REASON_NO_COMMIT)
		Commit();

    // Statistiques if applicable
	CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();
    if (protectionType == CT_SP_LINEAR ||
		protectionType == CT_SP_DPRING ||
		protectionType == CT_SP_OAPS ||
		protectionType == CT_SP_YCABLE ||
		protectionType == CT_SP_SNCN ||
		protectionType == CT_SP_SNCI ||
		protectionType == CT_SP_SNCS)
    {
        // Set statistic objects
        CT_SP_ProtectionPair<bool> changed(false,false);

        // update status of activity
        if (mySelection == CT_SP_WORKING_SIDE)
        {
            // Connected working ingress direction
            changed.working    |= myProtectionAction.mySwitchingStat.working->SetCurrentlyActive(true);
            changed.protection |= myProtectionAction.mySwitchingStat.protection->SetCurrentlyActive(false);
        }
        else // SP_PROTECTION
        {
            // Connected working ingress direction
            changed.working    |= myProtectionAction.mySwitchingStat.working->SetCurrentlyActive(false);
            changed.protection |= myProtectionAction.mySwitchingStat.protection->SetCurrentlyActive(true);
        }

        // Update statistics if applicable
		
        if ( myPreviousSelection != mySelection )
		{
            myProtectionAction.mySwitchingStat.working->IncrementPSCwork();
            myProtectionAction.mySwitchingStat.protection->IncrementPSCspan();
            changed.working = true;
            changed.protection = true;
		}

		//update revertive status
		changed.working    |= myProtectionAction.mySwitchingStat.working->SetRevertiveMode(myProtectionAction.Get1plus1Config().GetRevertiveMode());
		changed.protection |= myProtectionAction.mySwitchingStat.protection->SetRevertiveMode(myProtectionAction.Get1plus1Config().GetRevertiveMode());

        // Notify that statistic regions have changed
        if (changed.working)
            myProtectionAction.mySwitchingStat.working->MarkAsChanged();
        if (changed.protection)
            myProtectionAction.mySwitchingStat.protection->MarkAsChanged();
	

    }

    //store previous value
	myPreviousSelection = mySelection;
    return NULL;
}


void SP_1plus1Selector::SelectWorking()
{
    mySelection = CT_SP_WORKING_SIDE;
}

void SP_1plus1Selector::SelectProtection()
{
    mySelection = CT_SP_PROTECTION_SIDE;
}

//NO DEFAULT IMPLEMENTATION
//Specific implementation will override when needed
void SP_1plus1Selector::Commit()
{
    
}


//  /////////////////////////////////////////////////////////////////
//  From FC_Object
//  /////////////////////////////////////////////////////////////////
ostream& SP_1plus1Selector::WriteObject( ostream& theStream )
{
    SP_Selector::WriteObject(theStream);

    theStream<<FC_InsertVar(mySelection);
    return theStream;
}

istream& SP_1plus1Selector::ReadObject( istream& theStream )
{
    SP_Selector::ReadObject(theStream);

    theStream>>FC_ExtractVar(mySelection);

    mySelectionHistory = mySelection;

    return theStream;
}

FC_Stream& SP_1plus1Selector::WriteObjectBinary( FC_Stream& theStream )
{
    SP_Selector::WriteObjectBinary(theStream);

    theStream<<mySelection;
    return theStream;
}

FC_Stream& SP_1plus1Selector::ReadObjectBinary( FC_Stream& theStream )
{
    SP_Selector::ReadObjectBinary(theStream);

    theStream>>mySelection;

    mySelectionHistory = mySelection;

    return theStream;
}

//  /////////////////////////////////////////////////////////////////
//  From RS_Redundant
//  /////////////////////////////////////////////////////////////////
bool SP_1plus1Selector::HasChangedSinceLastCheck()
{
    bool hasChanged = SP_Selector::HasChangedSinceLastCheck();

    if ((mySelectionHistory == mySelection) &&
        !hasChanged)
    {
        return false;
    }
    else
    {
        mySelectionHistory = mySelection;
        return true;
    }
}

//  /////////////////////////////////////////////////////////////////
//  Dual module Y-Cable common switch implementation
//  /////////////////////////////////////////////////////////////////
void SP_1plus1Selector::YCableSelectorSwitch(TSPII_OpticalRegion* theTxOpticalRegion, TSPII_OpticalRegion* theRxOpticalRegion, CFG_OptProtCfgRegion* theProtRegion, bool portIsWorking)
{
    uint8 rxMsg = (*theRxOpticalRegion)[0].GetRxYCableMessage();
    uint8 txMsg = 0;
	bool mateLaserEnable = ( ((rxMsg & SP_LASER_STATE) == 0x0) ? false : true);

	//@TO DO: Prevent both lasers from turning on at the same time
	//@TO DO: Add manual switch
	//If a manual switch, then only allow the laser control if we have received ms indication
	//from far side
	uint8 usrCmdMsg = 0x0;
	bool usrCommand = true;
	const CT_SP_CommandType& theCommand = myProtectionAction.myRequestParserPtr->GetCommand();
	switch (theCommand.myRequest)
	{
		case CT_SP_1PLUS1_MS_P:
			usrCmdMsg = 0x1;
			break;
        case CT_SP_1PLUS1_FS_P:
			usrCmdMsg = 0x2;
			break;
        case CT_SP_1PLUS1_LK_P:
			usrCmdMsg = 0x3;
			break;
        case CT_SP_1PLUS1_FS_W:
			usrCmdMsg = 0x4;
			break;
        case CT_SP_1PLUS1_MS_W:
			usrCmdMsg = 0x5;
			break;
        default:
			usrCommand = false;
			break;
	}

	//Now shift to correct position
	usrCmdMsg = usrCmdMsg << SP_USER_CMD_SHIFT;
	uint8 mateusrCmdMsg = (rxMsg & SP_USR_CMD);
    
    uint8 mateAutoCmdMsg = (rxMsg & SP_AUTO_CMD);
	const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>& theLocalDefect = myProtectionAction.myRequestParserPtr->GetDefectStatus();
	uint8 localDefectMsg = ((portIsWorking == true) ? theLocalDefect.working : theLocalDefect.protection);
	//Shift to correct position
	localDefectMsg = localDefectMsg << SP_AUTO_CMD_SHIFT;

	
   //Both ends have synchronized on the user command, so 
   //if we are switching away then turn off laser regardless of mate
   //laser state. If we are switching to, then turn laser on only when
   //other side is turned off

	bool laserEnable = false;
	bool switchAllowed = true;
    bool sendMessage = true;
	if (mySelection == CT_SP_WORKING_SIDE)
	{
		//Other card is selected, turn off laser
		if (portIsWorking == false)
		{
			if (usrCommand == true)
			{
               	if (usrCmdMsg == mateusrCmdMsg)
	            {
					laserEnable = false;
				}
				else
				{
					switchAllowed = false;
                    laserEnable = (*theTxOpticalRegion)[0].GetLaserState();
                    //Don't send a message to the far end if we haven't heard from the module
                    //that will be going active. This is to prevent duplicate messages
                    sendMessage = false;
				}
			}
			else
			{
                if ( mateusrCmdMsg  != 0 && // mate command not cleared
                     mateAutoCmdMsg == 0 && // mate has no defect
                     localDefectMsg == 0 )  // local has no defect
                {
                    //wait until mate switch command is clear
                    switchAllowed = false;
                    laserEnable = (*theTxOpticalRegion)[0].GetLaserState();
                    //Don't send a message to the far end if we haven't heard from the module
                    //that will be going active. This is to prevent duplicate messages
                    sendMessage = false;
                }
                else
                {
                    laserEnable = false;
                }
			}
		}
		else
		{
			if (mateLaserEnable == false)
			{
			    laserEnable = true;
			}
			else
			{
				switchAllowed = false;
                laserEnable = (*theTxOpticalRegion)[0].GetLaserState();
			}
		}
	}
	else if (mySelection == CT_SP_PROTECTION_SIDE)
	{
		//Other card is selected, turn off laser
		if (portIsWorking == true)
		{
			if (usrCommand == true)
			{
               	if (usrCmdMsg == mateusrCmdMsg)
	            {
					laserEnable = false;
				}
				else
				{
					switchAllowed = false;
                    laserEnable = (*theTxOpticalRegion)[0].GetLaserState();
                    //Don't send a message to the far end if we haven't heard from the module
                    //that will be going active. This is to prevent duplicate messages
                    sendMessage = false;
				}
			}
			else
			{
                if ( mateusrCmdMsg  != 0 && // mate command not cleared
                     mateAutoCmdMsg == 0 && // mate has no defect
                     localDefectMsg == 0 )  // local has no defect
                {
                    //wait until mate switch command is clear
                    switchAllowed = false;
                    laserEnable = (*theTxOpticalRegion)[0].GetLaserState();
                    //Don't send a message to the far end if we haven't heard from the module
                    //that will be going active. This is to prevent duplicate messages
                    sendMessage = false;
                }
                else
                {
                    laserEnable = false;
                }
			}
		}
		else
		{
			if (mateLaserEnable == false)
			{
			    laserEnable = true;
			}
			else
			{
				switchAllowed = false;
                laserEnable = (*theTxOpticalRegion)[0].GetLaserState();
			}
		}
	}

	CFG_OptProt& aProtObject = (*theProtRegion)[0];
	//Control the laser. Check to make sure we do not have dual on/off scenario
	if (switchAllowed == true)
	{
#if defined(__TARGET__)
    	bool oriLaserEnable = (*theTxOpticalRegion)[0].GetLaserEnable();
#endif
	    if (laserEnable)
	    {
#if defined(WRLINUX)
            CT_CardType cardtype;
            cardtype = CSPII_CardIF::GetInstance()->GetCardType();
            /*When the card is pull out, the mate channel interrupt will trigger the YCABLE switch. 
            In this case, because no defect is found in this pulling card except the MateLofEnter, 
            so the pulling card will also be selected as work card, and the laser will be enabled until 
            the card is pulled out. we have to wait for 500ms to make laser on*/
            if(CARD_TYPE_HGTMMS == cardtype)
            {
                TSPII_OpticalRegion*       OpticalRegion = NULL;
                uint32 PII_count(0);

                OpticalRegion = TSPII_SubApplication::GetInstance()->GetOptical(TSPII_LINE_SIDE_3);
                PII_count = (*OpticalRegion)[0].GetOptLOS();
                if(PII_count%2 != 0)
                {
                    usleep(500*1000);
                }
            }
#endif
            (*theTxOpticalRegion)[0].SetLaserEnable(laserEnable);	
		    aProtObject.SetForceLaserShutdown(false);
	    }
	    else
	    {
            (*theTxOpticalRegion)[0].SetLaserEnable(laserEnable);
		    aProtObject.SetForceLaserShutdown(true);
	    }

#if defined(__TARGET__)
        if ((gSP_DebugTraceYcable) && (oriLaserEnable != laserEnable))
        {
            FC_TimePrecise time;
            time.GetCurrentTime();
  fc_cout << "[SP_1plus1Selector]YCable dual module switch: laser is " << laserEnable << " at " << uint32(time.GetUTCTime()) << " sec, " << uint32(time.GetFractionalTime()) << " ms" << endl;
        }
#endif

	}
	else
	{
		//fc_cout << "Waiting for usr command response or correct laser state from mate module" << endl;
	}

    if (sendMessage == true)
    {
	    const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>& theDefect = myProtectionAction.myRequestParserPtr->GetDefectStatus();
	    uint8 defectMsg = ((portIsWorking == true) ? theDefect.working : theDefect.protection);
	    //Shift to correct position
	    defectMsg = defectMsg << SP_AUTO_CMD_SHIFT;
    	
	    //Send defect and manual switch indicator
        uint8 theTxMsg = 0;
	    theTxMsg = (theTxMsg | defectMsg);
	    theTxMsg = (theTxMsg | usrCmdMsg);
        //Add the laser state
        theTxMsg = (theTxMsg | ( (laserEnable == true) ? 0x1 : 0x0));
	    (*theTxOpticalRegion)[0].SetTxYCableMessage(theTxMsg);
	    //DEBUG
	    //fc_cout << "Tx Msg: " << (uint32) theTxMsg <<endl;
	    //END DEBUG
    }

 if(gSP_DebugTraceYcable)
    {
        fc_cout << "[1p1 Y-Selector]Switch allowed " <<(int)switchAllowed << " to " << DISPLAY_CT_SP_Protection(mySelection) << endl;
        fc_cout << "[1p1 Y-Selector]RxMsg = " <<(int)rxMsg << " SndMsg is " << (int)sendMessage << " TxMsg=" << (int)txMsg << endl; 
    }
    

	//At the end, inc the counter the CFG PROT region
    //Update notify is done during the commit or by specific selector implementations
	if (switchAllowed == true)
	{
	    theProtRegion->IncModificationCounter();
	    //theProtRegion->UpdateNotify();
	}
	else
	{
		//If th CFG OPT prot region is invalid, validate it based on the current
		//configuration in hardware. This is so that CFG is not held up from running
		if (theProtRegion->IsValid() == false)
		{
 fc_cout << "[1p1 Y-Selector] Error!!!, valid PROT region, so reverse laser ON_OFF" << endl;
		    
			aProtObject.SetForceLaserShutdown( ( (*theTxOpticalRegion)[0].GetLaserState() == true ) ? false : true );
			theProtRegion->IncModificationCounter();
		}
	}
}

//  /////////////////////////////////////////////////////////////////
//  Single module Y-Cable common laser control implementation
//  /////////////////////////////////////////////////////////////////
void SP_1plus1Selector::YCableLaserTxControl(TSPII_OpticalRegion* theWorkingTxOpticalRegion, TSPII_OpticalRegion* theProtectTxOpticalRegion,CFG_OptProtCfgRegion* theWorkingOptProtRegion,CFG_OptProtCfgRegion* theProtectOptProtRegion)
{
if (gSP_DebugTraceYcable)
    {
        FC_TimePrecise time;
        time.GetCurrentTime();
        fc_cout <<"[SP_1plus1Selector]Ycable same slot switch to " << DISPLAY_CT_SP_Protection(mySelection) << " at " << uint32(time.GetUTCTime()) << " sec, " << uint32(time.GetFractionalTime()) << " ms" << endl;
    } 
    
    if (mySelection == CT_SP_WORKING_SIDE)
	{
        //Turn off protect laser
        (*theProtectTxOpticalRegion)[0].SetLaserEnable(false);	
        CFG_OptProt& aPOptObject = (*theProtectOptProtRegion)[0];
		aPOptObject.SetForceLaserShutdown(true);

        //Turn on working laser
        (*theWorkingTxOpticalRegion)[0].SetLaserEnable(true);	
        CFG_OptProt& aWOptObject = (*theWorkingOptProtRegion)[0];
		aWOptObject.SetForceLaserShutdown(false);
    }
    else
    {
        //Turn off working laser
        (*theWorkingTxOpticalRegion)[0].SetLaserEnable(false);	
        CFG_OptProt& aWOptObject = (*theWorkingOptProtRegion)[0];
		aWOptObject.SetForceLaserShutdown(true);

        //Turn on protect laser
        (*theProtectTxOpticalRegion)[0].SetLaserEnable(true);	
        CFG_OptProt& aPOptObject = (*theProtectOptProtRegion)[0];
		aPOptObject.SetForceLaserShutdown(false);
    }

    theProtectOptProtRegion->IncModificationCounter();
    theWorkingOptProtRegion->IncModificationCounter();
}
