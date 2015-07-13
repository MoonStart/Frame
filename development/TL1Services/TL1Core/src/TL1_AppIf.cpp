/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 4, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Application interface class declaration
-----------------------------------------------------------------------------*/ 


#include <TL1Core/TL1_AppIf.h>
#include <TL1Core/TL1_NotifCenter.h>

#include <AppFramework/FC_Context.h>
#include <Blackboard/FC_Blackboard.h>


TL1_AppIf::TL1_AppIf( FC_Context& theRootContext ) :
    FC_Context( "TL1", false ),
    itsRootContext( theRootContext ),
    itsEntityBb( 0 )
{
}

TL1_AppIf::~TL1_AppIf()
{
}

void TL1_AppIf::DoCreateRegions( FC_Object* theObject )
{
    FC_Context::DoCreateRegions( theObject );
	itsRootContext.GetBb().Register( GetBb() );

    // Do local initialization
    itsEntityBb = new FC_Blackboard( "Entity" );
    GetBb().Register( *itsEntityBb );
}

void TL1_AppIf::DoDeleteRegions( FC_Object* theObject )
{
    // Do location uninitialization
    if ( itsEntityBb )
    {
        GetBb().Unregister( *itsEntityBb );
        delete itsEntityBb;
        itsEntityBb = 0;
    }

    FC_Context::DoDeleteRegions( theObject );
}

void TL1_AppIf::DoCreateActions( FC_Object* theObject )
{
    FC_Context::DoCreateActions( theObject );

    // Create local actions
    // Create Notificaiton actions
    TL1_NotifCenter::Instance();
}

void TL1_AppIf::DoDeleteActions( FC_Object* theObject )
{
    // Delete local actions

    FC_Context::DoDeleteActions( theObject );
}

void TL1_AppIf::DoActivateActions( FC_Object* theObject )
{
    FC_Context::DoActivateActions( theObject );

    // Activate local actions
}

void TL1_AppIf::DoDeactivateActions( FC_Object* theObject )
{
    // Deactivate local actions

    FC_Context::DoDeactivateActions( theObject );
}

FC_Blackboard& TL1_AppIf::GetEntityBb()
{
    FC_THROW_ERROR_IF( !itsEntityBb,
                       FC_RuntimeError,
                       "TL1 Entity Blackboard does not exists" );
    return (*itsEntityBb);
}

FC_Blackboard& TL1_AppIf::GetRootBb()
{
    return GetBb();
}
