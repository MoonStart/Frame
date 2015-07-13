/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 1st, 2003- Jean-Francois Emond
DESCRIPTION:    Implementation file for 7100 Specific TL1 Db Change Wake up
                action declaration.
-----------------------------------------------------------------------------*/ 

#include <TL1Core/TL1_WakeUpAction.h>
#include <TL1Core/TL1_AgentRegionObserver.h>
#include <Blackboard/FC_BbRegion.h>

//--------------------------------------------------------------------------
TL1_WakeUpAction::TL1_WakeUpAction( FC_OneShotProcess& theProcess, 
								    TL1_AgentRegionObserver& theImmediateObserver ) :
    FC_WakeUpProcessAction( theProcess ),
    itsProcess( theProcess ),
    itsImmediateObserver(theImmediateObserver)
{
}

//--------------------------------------------------------------------------
TL1_WakeUpAction::~TL1_WakeUpAction()
{
}

//--------------------------------------------------------------------------
void TL1_WakeUpAction::RegionModify( FC_BbRegion* theRegion )
{
    FC_WakeUpProcessAction::Run(theRegion);
}

//--------------------------------------------------------------------------
void TL1_WakeUpAction::Run( FC_Object* theObject )
{
}