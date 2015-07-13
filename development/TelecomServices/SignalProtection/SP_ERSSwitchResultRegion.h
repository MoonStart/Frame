#ifndef SP_ERSSWITCHRESULTREGION_H
#define SP_ERSSWITCHRESULTREGION_H
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:   Equipment Redundancy
TARGET:          
AUTHOR:      Feb, 2005 - Anoop Mathew
DESCRIPTION: equipment redundancy switch result region.
-----------------------------------------------------------------------------*/ 
#include <Blackboard/FC_BbKey.h>
#include <Blackboard/FC_BbObject.h>
#include <Blackboard/FC_BbRegionVectImp.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_SystemIds.h>

class SP_ERSSwitchResult : public FC_BbObject
{
public:
    /** Default constructor.*/
    SP_ERSSwitchResult(); 

	virtual ~SP_ERSSwitchResult();
//-----------------------------------------------------------------------------

    
    //Add Set and Get methods here
	void SetLastProcessedCommandID(CT_SP_CommandID theCommandID);
	void SetActiveSlot(CT_SlotId slot);
	void SetStandbySlot(CT_SlotId slot);
	void Reset();

	CT_SlotId GetActiveSlot()
	{
		return myActiveSlot;
	}

	CT_SlotId GetStandbySlot()
	{
		return myStandbySlot;
	}

    CT_SP_CommandID GetLastProcessedCommandID()
	{
		return myLastProcessedCommandID;
	}
//-----------------------------------------------------------------------------

protected:
    virtual ostream& WriteObject( ostream& theStream );
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------
    virtual istream& ReadObject( istream& theStream );
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
//-----------------------------------------------------------------------------

private:
    //Add class data members here
    //The active and standby controller slots
	//##ModelId=38DFC85C00F2
	CT_SlotId myActiveSlot;
	CT_SlotId myStandbySlot;
	//The last processed command id
	CT_SP_CommandID myLastProcessedCommandID;


};


/** Region used to contain controller redundancy switch command execution results */
class SP_ERSSwitchResultRegion : public FC_BbRegionVectImp<SP_ERSSwitchResult>
{
public:
    /** Constructor.
    @param theKey: The region key. */
    SP_ERSSwitchResultRegion(FC_BbKey theKey);
	virtual ~SP_ERSSwitchResultRegion();
//-----------------------------------------------------------------------------
	CT_SlotId GetActiveSlot();

	CT_SlotId GetStandbySlot();

    CT_SP_CommandID GetLastProcessedCommandID();

//-----------------------------------------------------------------------------
};
#endif //SP_ERSSWITCHRESULTREGION_H
