// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_DEFECTTRANSFERACTION_38E35B0900D0_INCLUDED
#define _INC_SP_DEFECTTRANSFERACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <vector>
#include "SP_Definitions.h"

class FC_BbAction;
class SP_Defects;
class FC_TimedProcess;


//This class handles defect transfer from one card to another.
//##ModelId=38E35B0900D0
class SP_DefectTransferAction 
: public FC_Action
{
public:
	//Constructor. Requires defects region.
    //##ModelId=3BBC9B0F02A0
    SP_DefectTransferAction(TEL_BbRegionBaseImp<SP_Defects>& theDefectsRegion, T6100_CardIf& theCardContext);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_DefectTransferAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles transfer of defects from one card to another
	//based on configuration
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
	FC_TimedProcess* GetTimedProcess() { return myTimedProcess; }

	void AddtoITSConfigRegions(ITS_ConfigRegionOnTrn* theRegion);
	void AddtoITSUpstreamRegions(ITS_UpstreamRegion* theRegion);

	int GetIndexFromPort(CT_IntfId port);

protected:
	
	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

private:
    FC_BbAction* myBbAction;
	FC_TimedProcess* myTimedProcess;

	SP_ITSConfigRegionCollection myITSConfigRegions;
	SP_ITSUpstreamRegionCollection myITSUpstreamRegions;
	TEL_BbRegionBaseImp<SP_Defects>& myDefectsRegion;

	T6100_CardIf& myContext;

	CT_SP_CommandID myPrevDefectId[SP_MAX_NUM_LSP];

};

//##ModelId=39ACEFB00072
inline void SP_DefectTransferAction::Start() { stopped = false; }
//##ModelId=39ACEFB0005E
inline void SP_DefectTransferAction::Stop() { stopped = true; }

#endif /* _INC_SP_DEFECTTRANSFERACTION_38E35B0900D0_INCLUDED */