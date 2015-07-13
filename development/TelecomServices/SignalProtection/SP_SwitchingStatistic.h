// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SWITCHINGSTATISTIC_38F47B4103A1_INCLUDED
#define _INC_SP_SWITCHINGSTATISTIC_38F47B4103A1_INCLUDED

#include "TelCommon/TEL_BbObjectBase.h"
#include "SP_Definitions.h"

//This object contains the switching statics of a port for 
//performance monitoring and alarm purposes. It provide acces 
//to the number of switching of a facility as well as the 
//current APS trouble defect status.
//##ModelId=38F47B4103A1
class SP_SwitchingStatistic 
: public TEL_BbObjectBase
{
public:

	//True if the corresponding facility is current selecting 
	//traffic.
	//##ModelId=39ACEFB40280
	bool IsCurrentlyActive()
    {
        return isCurrentlyActive;
    }

    //Returns the state of my ProtectionState.
	//##ModelId=38F484310275
	bool IsInvolvedInProtection();

	//Returns the state of myProtectingRole.
	//##ModelId=38F484A0001B
	bool IsProtecting();

	//Returns the revertive state
	//true if revertive/false otherwise
	bool IsRevertive();

	//Returns the content of myPSCwork.
	//##ModelId=38F485A9033E
	inline uint32 GetPSCwork() const
    {
        return myPSCwork;
    }

	//Returns the content of myPSCspan.
	//##ModelId=38F485E103A2
	inline uint32 GetPSCspan() const
    {
        return myPSCspan;
    }

	//This method increments the PSC span counter of one.
	//##ModelId=38F4917A02ED
	void IncrementPSCspan();

	//This method increments the PSC work counter of one.
	//##ModelId=38F491C300AD
	void IncrementPSCwork();

	//Indicates that the facility is being selected.
	//##ModelId=39ACEFB40226
    bool SetCurrentlyActive(bool theState);

	//This method allows specifying if the port is involved 
	//in protection.
	//##ModelId=38F4B47E00A8
	bool SetInvolvedInProtection(bool theProtectionInvolvement);

	//This method allows specifying if a facility plays a 
	//protecting role in the protection group.
	//##ModelId=38F4B4E9030F
	bool SetProtecting(bool theProtecting);

	//This method allows specifying if the protection group
	//is in revertive mode or not
	bool SetRevertiveMode( bool theMode);

	//Destructor.
	//##ModelId=38FB09660199
	virtual ~SP_SwitchingStatistic();

	//Default constructor.
	//##ModelId=3911AE7F00F2
	SP_SwitchingStatistic();

	//Writes the attributes of the statistics to a stream.
	//##ModelId=3932D1DD02DA
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the statistics from a stream.
	//##ModelId=3932D1DD021B
    virtual istream& ReadObject( istream& theStream );
	//Writes the attributes of the statistics to a stream.
	//##ModelId=39ACEFB401C2
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the attributes of the statistics from a binary 
	//stream.
	//##ModelId=39ACEFB4015E
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

	//Assignment operator.
	//##ModelId=3B8BC9DB00B6
    SP_SwitchingStatistic& operator=(const SP_SwitchingStatistic &rhs);


	//Sets the hasChanged flag to true.
	//##ModelId=3B8BC9DB0098
    void MarkAsChanged() {myHasChanged = true;}
	//True if hasChange is true. Clears that hasChanges flag.
	//##ModelId=3B8BC9DB007A
    bool HasChangedSinceLastCheck();

private:
	//True if the corresponding facility is current selecting 
	//traffic.
	//##ModelId=39ACEFB40046
    bool isCurrentlyActive;

	//True if the port is involved in protection.
	//##ModelId=38F481720314
	bool myProtectionState;

	//True if the port is acting as a protecting unit (not a 
	//protected).
	//##ModelId=38F482290263
	bool myProtectingRole;

	//This counter increments of one when a port acting as a 
	//protected unit is switched to or from a back-up 
	//protection unit.
	//##ModelId=38F4828B0322
	uint32 myPSCwork;

	//This counter increments of one when a port acting as a 
	//protecting unit is span switched to or from a back-up 
	//protected unit (1+1 or CLSR).
	//##ModelId=38F482BA0207
	uint32 myPSCspan;


	//Indication that some of the attribute have changed.
	//##ModelId=3B8BC9DB0020
    bool myHasChanged;

	//indicates whether the protection group is revertive
	bool revertiveMode;



};

#endif /* _INC_SP_SWITCHINGSTATISTIC_38F47B4103A1_INCLUDED */

