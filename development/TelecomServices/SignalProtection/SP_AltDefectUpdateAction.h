// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_ALTDEFECTUPDATEACTION_38E35B0900D0_INCLUDED
#define _INC_SP_ALTDEFECTUPDATEACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include "SP_Definitions.h"
#include <CommonTypes/CT_SignalProtection.h>


class FC_BbAction;
class SP_Defects;
class SP_1plus1BaseApplication;


//This class handles defect writes to the alt defects region.
//##ModelId=38E35B0900D0
class SP_AltDefectUpdateAction 
: public FC_Action
{
public:
	//Constructor. Requires defects region.
    //##ModelId=3BBC9B0F02A0
    SP_AltDefectUpdateAction(SP_1plus1BaseApplication& theLineProtApp);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_AltDefectUpdateAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles switching request coming from the 
	//admin. It also updates the command results once the 
	//command is completed.
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	//Forces the defect processing to start if it was 
	//stopped(debug).
    //##ModelId=39ACEFB00072
    inline void Start();
	//Forces the defect processing to stop (debug).
    //##ModelId=39ACEFB0005E
    inline void Stop();

    FC_BbAction* GetBbAction() { return myBbAction; }

	void UpdateDefects(SP_Defects* theDefects, int index, CT_IntfId theIntfId, CT_SP_1plus1Type theType, bool theForceInc);

protected:
	
	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

private:
    FC_BbAction* myBbAction;

	SP_1plus1BaseApplication& myLineApp;

};

//##ModelId=39ACEFB00072
inline void SP_AltDefectUpdateAction::Start() { stopped = false; }
//##ModelId=39ACEFB0005E
inline void SP_AltDefectUpdateAction::Stop() { stopped = true; }

#endif /* _INC_SP_DEFECTTRANSFERACTION_38E35B0900D0_INCLUDED */