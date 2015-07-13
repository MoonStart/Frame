// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_REQUESTPARSER_38F61E9801A3_INCLUDED
#define _INC_SP_REQUESTPARSER_38F61E9801A3_INCLUDED

#include <CommonTypes/CT_SP_CommandType.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <ExecutionSupport/FC_Action.h>
#include "SP_Definitions.h"


class MON_Region;
class SP_ProtectionAction;
class SP_SsmRegion;
class SP_Defects;

//This class is the base class responsible for parsing the 
//different switching request. It provide a common method to 
//read defects.
//##ModelId=38F61E9801A3
class SP_RequestParser 
:  public FC_Action
{
public:

	//This class define a facility defect. It hold a state and 
//count as well as a name (SD/SF).
	//##ModelId=3BBC9AFC00E0
    class Defect
    {
    public:
	//Default constructor.
		//##ModelId=3BBC9AFC00EA
        Defect():
            myStatus(0),
            myCount(0),
            myName(CT_TEL_MS_AIS_DEFECT) // dummy value
        {}
	//Constructor with name (SD/SF).
		//##ModelId=3BBC9AFC00F4
        Defect(CT_TEL_Defect theName):
            myStatus(0),
            myCount(0),
            myName(theName)
        {}
	//Sens the state and counter to s stream (debug).
		//##ModelId=3BBC9AFC00F6
		FC_Stream& SnapshotWrite(FC_Stream& theStream)
		{
			theStream << "      myStatus = " << (myStatus ? "true" : "false") << endl;
			theStream << "      myCount  = " << myCount                       << endl;
		 	theStream << "      myName   = " << (uint32)myName << endl;
			return theStream;
		}
	//Current state of the defect (active or not).
		//##ModelId=3BBC9AFC00FF
        bool myStatus;
	//Current number of rising transition.
		//##ModelId=3BBC9AFC0109
        uint32 myCount;
	//Current type of defect (SD or SF).
		//##ModelId=3BBC9AFC011D
        CT_TEL_Defect myName;
    };

	//Destructor.
	//##ModelId=39058BF4024D
	virtual ~SP_RequestParser();

	//This method sets the switching command on the request 
	//parser. If command cannot be accepted (high priority 
	//request already exists), the command fails. This is an 
	//abstract method.
	//##ModelId=38FF6CA5034F
	virtual CT_SP_CommandResultCode SetSwitchingCommand(CT_SP_CommandType& theCommand) = 0;

	//Not supported.
	//##ModelId=3B8BC9FB0184
    virtual void Run( FC_Object* theObject = NULL );
	//Does nothing.
	//##ModelId=3B8BC9FB013E
	virtual FC_Stream& SnapshotWrite(FC_Stream& theStream);

	//checks the aSSM versus bSSM for quality
	//returns true if A has a lower level (better quality)
	//than B
	bool GetHighestSSMPriority(CT_FAC_RxSsm aSSM, CT_FAC_RxSsm bSSM);

	//This method reads the received SSM value for a given port
	//from the monitoring interface
	//NOTE: This is only applicable for timing protection schemes
	virtual CT_FAC_RxSsm UpdateRxSSM(MON_Region* theStatusRegion, int theIndex, CT_SP_1plus1SubType theSubType, CT_SP_Protection theSide, CT_TEL_FacilityStandard theFacStandard);
    //This is an alternate method to read received SSM value
    //NOTE: This is only applicable for timing protection schemes
    virtual CT_FAC_RxSsm UpdateRxSSM(CT_ShelfId theShelf, CT_TEL_FacilityStandard theFacStandard);
	//This method returns the active sync ref id (for shelf based timing).
	virtual CT_IntfId GetActiveSyncRefId(CT_ShelfId theShelf, CT_SlotId theSlot);
	//This is an alternate method to return the active sync ref id (for system based timing)
	virtual CT_IntfId GetActiveSyncRefId(CT_ShelfId theShelf, CT_SlotId theSlot, CT_SP_1plus1SubType theSubType, CT_SP_Protection theSide);
	//NOTE: This is only applicable for timing protection schemes
	virtual void GetSelectedSsmShelfSlot(CT_SP_1plus1SubType theSubType, CT_SP_Protection theSide, CT_TEL_FacilityStandard theFacStandard, CT_ShelfId* theSelShelf, CT_SlotId* theSelSlot);
    //NOTE: This is only applicable for timing protection schemes
    virtual void GetSelectedSsmShelfSlot(CT_ShelfId theShelf, CT_TEL_FacilityStandard theFacStandard, CT_ShelfId* theSelShelf, CT_SlotId* theSelSlot);

protected:
	//This method reads SD and SF defects (line or path 
	//depending on mode) from defect monitoring interface for 
	//the given port. It also looks for glitches using 
	//previous run state and counters. It also report signal 
	//failure if card status or inventory is wrong.
	//##ModelId=39ACEFCA016A
    virtual CT_SP_AutoSwitchDefect UpdateFailureStatus(
                                               MON_Region& theDefectRegion,
											   MON_Region* theStatusRegion,
                                               Defect& thePreviousSF,
											   Defect& thePreviousSFLow,
                                               Defect& thePreviousSD,
                                               CT_SP_1plus1Type theType,
                                               CT_SP_1plus1SubType theSubType,
                                               bool& theGlitchIndication,
											   int theIndex,
											   CT_IntfId thePortId,
											   SP_ProtectionLayer theLayer,
											   SP_ProtectionAction* theProtectionAction,
											   CT_SP_Protection theProtSide,
                                               unsigned int theTspiiIntf,
                                               SP_Defects* theSPDefects);

	

	//Returns false.
	//##ModelId=3B8BC9FB003A
    inline virtual bool HasChangedSinceLastCheck() { return false; }

	//Does nothing.
	//##ModelId=3B8BC9FA03DC
    inline virtual ostream& WriteObject( ostream& theStream ) { return theStream; }
	//Does nothing.
	//##ModelId=3B8BC9FA0396
    inline virtual istream& ReadObject( istream& theStream ) { return theStream; }
	//Does nothing.
	//##ModelId=3B8BC9FA035A
	inline virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream ) { return theStream; }
	//Does nothing.
	//##ModelId=3B8BC9FA0314
    inline virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream ) { return theStream; }

};

#endif /* _INC_SP_REQUESTPARSER_38F61E9801A3_INCLUDED */