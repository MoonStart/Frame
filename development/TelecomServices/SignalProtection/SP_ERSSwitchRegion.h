#ifndef SP_ERSSWITCHREGION_H
#define SP_ERSSWITCHREGION_H
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:   Equipment Redundancy Support
TARGET:          
AUTHOR:      Feb, 2005 - Anoop Mathew
DESCRIPTION: equipment redundancy switch region.
-----------------------------------------------------------------------------*/ 
#include <Blackboard/FC_BbKey.h>
#include <Blackboard/FC_BbObject.h>
#include <Blackboard/FC_BbRegionVectImp.h>
#include <CommonTypes/CT_SignalProtection.h>


using namespace std;

class SP_ERSSwitchCommand : public FC_BbObject
{
public:
    /** Default constructor.*/
    SP_ERSSwitchCommand(void);
	virtual ~SP_ERSSwitchCommand();
//-----------------------------------------------------------------------------

    
    //Add Set and Get methods here
	CT_SP_CommandID SetCommand(CT_SP_Request theCommand, bool incCommandId = true);

	CT_SP_Request GetCommand();
    CT_SP_CommandID GetCommandID();
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
	//The current command to apply on the equipment. The command 
	//is a typedef of type CT_SP_Request.
	//##ModelId=38DFC85C00F2
	CT_SP_Request myCommand;
	//The current command id associated with the command
	CT_SP_CommandID myCommandID;
};

/** Region used to contain equipment redundancy switch commands */
class SP_ERSSwitchRegion : public FC_BbRegionVectImp<SP_ERSSwitchCommand>
{
public:
    /** Constructor.
    @param theKey: The region key. */
    SP_ERSSwitchRegion(FC_BbKey theKey);
	virtual ~SP_ERSSwitchRegion();
//-----------------------------------------------------------------------------

   //Add set and get methods here
	CT_SP_CommandID SetCommand(CT_SP_Request theCommand);
	CT_SP_Request GetCommand();
	CT_SP_CommandID GetCommandID();
	
//-----------------------------------------------------------------------------
};
#endif //SP_ERSSWITCHREGION_H
