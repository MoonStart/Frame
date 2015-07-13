/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 4, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Application interface class declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_APPIF_H__
#define __TL1_APPIF_H__


#ifndef FC_BB_APP_H
#include <AppFramework/FC_Context.h>
#endif

class TL1_AppIf : public FC_Context
{
public:
    TL1_AppIf( FC_Context& theRootContext );
    virtual ~TL1_AppIf();

    virtual void DoCreateRegions( FC_Object* theObject = 0 );

    virtual void DoDeleteRegions( FC_Object* theObject = 0 );

    virtual void DoCreateActions( FC_Object* theObject = 0 );

    virtual void DoDeleteActions( FC_Object* theObject = 0 );

    virtual void DoActivateActions( FC_Object* theObject = 0 );

    virtual void DoDeactivateActions( FC_Object* theObject = 0 );


    virtual FC_Blackboard& GetEntityBb();
    FC_Blackboard& GetRootBb();

private:
    FC_Context& itsRootContext;
    FC_Blackboard* itsEntityBb;
};



#endif

