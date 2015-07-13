/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 10, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 State Notification Observer implementation
-----------------------------------------------------------------------------*/ 

#include <TL1Core/TL1_DeferredObserverFactory.h>
#include <TL1Core/TL1_AgentRegionObserver.h>
#include <TL1Core/TL1_WakeUpAction.h>
#include <Blackboard/FC_BbRegionObserver.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <T6100_Dispatcher.h>
#include <ErrorService/FC_Error.h>

//-----------------------------------------------------------------------------
TL1_WakeUpAction* TL1_DeferredObserverBuilderHelper::operator()( TL1_AgentRegionObserver* theImmediateObserver )
{
    FC_THROW_ERROR_IF( !( theImmediateObserver ), FC_LogicError, 
        "Error creating the immediate observer in TL1WakeUpObserverBuilder" );

    FC_OneShotProcess* aOneShotProcess = 
        new FC_OneShotProcess( *theImmediateObserver, gLowDispatcher );
    FC_THROW_ERROR_IF( !( aOneShotProcess ), FC_LogicError, 
        "Error creating the one shot process in TL1WakeUpObserverBuilder" );

    TL1_WakeUpAction* aDeferredObserver = 
        new TL1_WakeUpAction( *aOneShotProcess, *theImmediateObserver );
    FC_THROW_ERROR_IF( !( aDeferredObserver ), FC_LogicError, 
        "Error creating the deferred observer in TL1WakeUpObserverBuilder" );
    
    return aDeferredObserver;
}
