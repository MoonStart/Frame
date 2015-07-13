/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         March 31, 2003- Jean-Francois Emond
DESCRIPTION:    Source file for the Generic TL1 Notification Tag implementation
-----------------------------------------------------------------------------*/

#include <TL1Core/TL1_MultipleObserverTag.h>
#include <TL1Core/TL1_DeferredObserverFactoryIf.h>
#include <TL1Core/TL1_WakeUpAction.h>
#include <Blackboard/FC_BbRegion.h>
#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_OneShotProcess.h>

//-----------------------------------------------------------------------------
TL1_MultipleObserverTag::TL1_MultipleObserverTag( FC_BbTagId theId, TL1_DeferredObserverFactoryIf *theObsFactory ) :
    FC_BbTag( theId ),
    itsObserverFactory( theObsFactory )
{
}

//--------------------------------------------------------------------------
TL1_MultipleObserverTag::~TL1_MultipleObserverTag()
{
    if( itsObserverFactory )
    {
        delete itsObserverFactory;
        itsObserverFactory = 0;
    }
}

//--------------------------------------------------------------------------
void TL1_MultipleObserverTag::Install( FC_BbRegion& theRegion )
{
    // First make sure the observer has been correctly set
    FC_THROW_ERROR_IF( !itsObserverFactory,
                       FC_RuntimeError,
                       "Attempted to use undefined observer factory" );

    // Check first if region is already member
    RegionObserverMap::iterator it = itsMemberRegions.find( &theRegion );

    if ( it == itsMemberRegions.end() )
    {
        // Only add observer if it hasn't been added yet
        itsMemberRegions[&theRegion] =
            itsObserverFactory->CreateObserver( theRegion );
        DoInstall( theRegion );
        theRegion.AddRegionObserver( itsMemberRegions[&theRegion] );
    }

    it = itsMemberRegions.find( &theRegion );
    FC_THROW_ERROR_IF( (it == itsMemberRegions.end()), FC_LogicError, 
        "Failed to register the region in the multiple observer map!" );
}

//--------------------------------------------------------------------------
void TL1_MultipleObserverTag::Uninstall( FC_BbRegion& theRegion )
{
    // First make sure the observer has been correctly set
    FC_THROW_ERROR_IF( !itsObserverFactory,
                       FC_RuntimeError,
                       "Attempted to use undefined observer factory" );


    RegionObserverMap::iterator it = itsMemberRegions.find(&theRegion);
    if ( it != itsMemberRegions.end() )
    {
        theRegion.RemoveRegionObserver( (*it).second );

        if((*it).second)
        {
            FC_OneShotProcess* aProc = &((*it).second->GetOneShotProcess());
            TL1_AgentRegionObserver* anObs = &((*it).second->GetImmediateObserver());
            // Suspend the one shot process
            aProc->SuspendImmediate();
            // Delete the one shot process
            delete aProc;
            // Delete the observer
            delete anObs;
            // Delete the wake up action
            delete (*it).second;
        }
        itsMemberRegions.erase( it );
    }

    it = itsMemberRegions.find( &theRegion );
    FC_THROW_ERROR_IF( (it != itsMemberRegions.end()), FC_LogicError, 
        "Failed to unregister the region in the multiple observer map!" );
}

//--------------------------------------------------------------------------
void TL1_MultipleObserverTag::DoInstall( FC_BbRegion& theRegion )
{
}

//--------------------------------------------------------------------------
bool TL1_MultipleObserverTag::IsInstalledOn( FC_BbRegion& theRegion )
{
    RegionObserverMap::iterator it = itsMemberRegions.find( &theRegion );

    return (it != itsMemberRegions.end() )?true:false;
}

//--------------------------------------------------------------------------
FC_BbRegionObserver* TL1_MultipleObserverTag::GetObserver( FC_BbRegion* theRegion )
{
    RegionObserverMap::iterator it = itsMemberRegions.find(theRegion);
    if ( it != itsMemberRegions.end() )
    {
        return (*it).second;
    }
    else
    {
        return 0;
    }
}
