// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1PROTECTIONGROUPSTATUS_38E0B15303D4_INCLUDED
#define _INC_SP_1PLUS1PROTECTIONGROUPSTATUS_38E0B15303D4_INCLUDED

#include "SP_ProtectionGroupStatus.h"
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include <CommonTypes/CT_SP_1plus1UnitStatus.h>

//The class defines the status of a 1+1 protection group. It 
//is a blackboard object that hold one unit status. There is 
//one object per protection group. These object are contains 
//in blackboard region and are accessed by facade operations 
//on admin, and by direct context access on PCSM for updates.
class SP_1plus1ProtectionGroupStatus 
: public SP_ProtectionGroupStatus
{
public:
	//Default constructor.
	SP_1plus1ProtectionGroupStatus();

	//Copy constructor.
	SP_1plus1ProtectionGroupStatus(const SP_1plus1ProtectionGroupStatus& theStatus);
	//Comparision operator.
    bool operator==(const SP_1plus1ProtectionGroupStatus& theStatus) const;
	//Assignment operator.
    SP_1plus1ProtectionGroupStatus& operator=(const SP_1plus1ProtectionGroupStatus& theStatus);

	//Destructor.
	virtual ~SP_1plus1ProtectionGroupStatus();

	//This method returns a reference to the status of the 
	//unit of the 1+1 protection group.
	CT_SP_1plus1UnitStatus& GetProtectionUnits();

	//Return current source of request (remote or local).
	//##ModelId=3B98C8030163
	CT_SP_Location GetRemoteOrLocal() const;

    // ActualApsBidir methods
        CT_SP_ApsBidirType GetActualApsBidir() const;
        void SetActualApsBidir(CT_SP_ApsBidirType theActualApsBidir);

	//Return current automatic switch reason.
	//##ModelId=3B98C803013B
	const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect> GetAutoSwitchReason() const;
	//Return the current switch request.
	//##ModelId=3B98C803014F
	CT_SP_Request GetRequest() const;

    // Returns the current selection
    CT_SP_Protection        GetSelectedSide();
    void                    SetSelectedSide(const CT_SP_Protection theSelection);

	//Return the last processed command id
	CT_SP_CommandID         GetLastProcessedCommandID();
	void                    SetLastProcessedCommandID(CT_SP_CommandID theCommandID);

    //Return the selected side usable
	bool                    GetSelectedSideUsable();
	bool                    SetSelectedSideUsable(bool theUsable);

	//Writes the attributes of the status to a stream.
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the status from a stream.
    virtual istream& ReadObject( istream& theStream );
	//Writes the attributes of the status to a binary stream.
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the attributes of the status from a binary stream.
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//The unit status holds the information about the 1+1 
	//protection group.
	CT_SP_1plus1UnitStatus myUnitStatus;
    CT_SP_Protection       mySelectedSide;
	CT_SP_CommandID        myLastProcessedCommandID;
    bool                   mySelectedSideUsable;

};

#endif /* _INC_SP_1PLUS1PROTECTIONGROUPSTATUS_38E0B15303D4_INCLUDED */

