// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_APSCONTROLLER_38F5D26801BE_INCLUDED
#define _INC_SP_APSCONTROLLER_38F5D26801BE_INCLUDED

#include "SignalProtection/SP_CallbackTimer.h"

class SP_RequestParser;
class SP_Selector;
class SP_ProtectionAction;

//This is the base class for the APS controller. It defines a 
//WTR timer and a stability indication.
//##ModelId=38F5D26801BE
class SP_APSController
{
public:

	//Constructor. Requires the protection action.
	//##ModelId=38FB09630339
	SP_APSController(SP_ProtectionAction& theAction);

	//Destructor.
	//##ModelId=38FB0963034D
	virtual ~SP_APSController();
	//Write the attributes to a stream (debug).
	//##ModelId=3B8BC9C70176
	virtual FC_Stream& SnapshotWrite(FC_Stream& theStream);

	//True state machine was marked as stable (no oscillation 
	//between states).
	//##ModelId=3B8BC9C7016C
    bool IsStable() const { return myStateMachineIsStable; }
	//Marks the APS controller as stable after run.
	//##ModelId=3B8BC9C70162
    void MarkAsStable() { myStateMachineIsStable = true; }
	//Marks the APS controller as UN-stable after run.
	//##ModelId=3B8BC9C70158
    void MarkAsUnstable() { myStateMachineIsStable = false; }
	//True is WTR timer is started.
	//##ModelId=3BBC9B2A01D6
    bool IsWtrTimerRunning() { return myWTRTimer.IsStarted(); }
protected:

	//True state machine was marked as stable (no oscillation 
	//between states).
	//##ModelId=3B8BC9C603CD
    bool myStateMachineIsStable;

	//Returns true is WTR timer state (not remaining time) 
	//has changes since last call.
	//##ModelId=3B8BC9C70144
    virtual bool HasChangedSinceLastCheck();
	//Sends the WTR timer to the stream.
	//##ModelId=3B8BC9C700E9
    virtual ostream& WriteObject( ostream& theStream );
	//Extracts the WTR timer from the stream.
	//##ModelId=3B8BC9C70099
    virtual istream& ReadObject( istream& theStream );
	//Sends the WTR timer to the binary stream.
	//##ModelId=3B8BC9C7003F
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Extracts the WTR timer from the binary stream.
	//##ModelId=3B8BC9C603D7
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

	//Wait to restore callback timer.
	//##ModelId=39ACEFA90036
    SP_CallbackTimer myWTRTimer;
};


#endif /* _INC_SP_APSCONTROLLER_38F5D26801BE_INCLUDED */

