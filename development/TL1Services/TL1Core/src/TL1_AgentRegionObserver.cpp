/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 10, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 State Notification Observer implementation
-----------------------------------------------------------------------------*/
 
#include <TL1Core/TL1_AgentRegionObserver.h>

#include <Blackboard/FC_BbRegion.h>
#include <ErrorService/FC_Error.h>
#include <DatabaseService/FC_DbModeRegion.h>

//-----------------------------------------------------------------------------
FC_DbModeRegion* TL1_AgentRegionObserver::theirDbModeRegionPtr = 0;

//-----------------------------------------------------------------------------
TL1_AgentRegionObserver::TL1_AgentRegionObserver(FC_BbRegion& theObservedRegion, 
                                                 TL1_AgentRegionObserverImp& theRegionObserverImp) : 
    itsObservedRegion(theObservedRegion),
    itsAgentRegionObserverImp(theRegionObserverImp),
    itsIsDbRestored(false)
{
    // If the database region has been set, we register this observer on that
    // region to be notified when the 
    if( GetDbModeRegionPtr() )
    {
        GetDbModeRegionPtr()->AddRegionObserver( this );
    }
}

//-----------------------------------------------------------------------------
TL1_AgentRegionObserver::~TL1_AgentRegionObserver()
{
    if( GetDbModeRegionPtr() )
    {
        GetDbModeRegionPtr()->RemoveRegionObserver( this );
    }
}

//-----------------------------------------------------------------------------
void TL1_AgentRegionObserver::SetDbModeRegion(FC_DbModeRegion& theDbModeRegion) 
{ 
    theirDbModeRegionPtr = &theDbModeRegion; 
}

//-----------------------------------------------------------------------------
FC_DbModeRegion* TL1_AgentRegionObserver::GetDbModeRegionPtr() 
{ 
    return theirDbModeRegionPtr; 
}

//-----------------------------------------------------------------------------
void TL1_AgentRegionObserver::RegionModify( FC_BbRegion* theRegion )
{
    // Check if were notified because the DB has just been restored
    if( !itsIsDbRestored &&
        theRegion == GetDbModeRegionPtr() && 
        GetDbModeRegionPtr() && 
        GetDbModeRegionPtr()->GetMode() == FC_DbModeRegion::IDLE )
    {
        itsIsDbRestored = true;
        OnDatabaseRestore();    
    }
    else if ( itsIsDbRestored && theRegion )
    {
        DoRegionModify(*theRegion);
    }
}

//-----------------------------------------------------------------------------
void TL1_AgentRegionObserver::Run( FC_Object* theObject )
{
    FC_THROW_ERROR_IF( !theObject, FC_LogicError,
                       "Null pointer passed to AgentRegionObserver" );

    FC_BbRegion* isRegion = dynamic_cast<FC_BbRegion*>( theObject );

    // Check if the object is a region or a BB object.  Also, only run
    // in the case where the database is restored.
    if( isRegion )
    {
        RegionModify( &itsObservedRegion );
    }
    else if( theObject && itsIsDbRestored )
    {
        DoRun( *theObject );
    }
}

//-----------------------------------------------------------------------------
void TL1_AgentRegionObserver::DoRegionModify( FC_BbRegion& theRegion )
{
}

//-----------------------------------------------------------------------------
void TL1_AgentRegionObserver::DoRun( FC_Object& theObject )
{
}

//-----------------------------------------------------------------------------
void TL1_AgentRegionObserver::OnDatabaseRestore()
{
}