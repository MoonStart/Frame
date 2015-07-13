/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Feb 17, 2011 - Tom Novak
DESCRIPTION:    Header Source for Control Plane Fal Structure
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONTROLPLANEFAL_H__
#include <TL1Core/TL1_ControlPlaneFal.h>
#endif

TL1_ControlPlaneFal::TL1_ControlPlaneFal()
{
    myFalData= (void*)0;
}

TL1_ControlPlaneFal::~TL1_ControlPlaneFal()
{
}

TL1_ControlPlaneFal& 
TL1_ControlPlaneFal::operator=( const TL1_ControlPlaneFal& theInst )
{
    myFalData= theInst.myFalData;    

    return *this;
}

bool 
TL1_ControlPlaneFal::operator==( const TL1_ControlPlaneFal& theInst ) const
{
    if ( myFalData != theInst.myFalData )
        return false;
    
    return true;
}

