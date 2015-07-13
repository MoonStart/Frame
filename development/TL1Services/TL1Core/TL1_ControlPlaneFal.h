/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Feb 17, 2011 - Tom Novak
DESCRIPTION:    Header file for Control Plane Fal Structure
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONTROLPLANEFAL_H__
#define __TL1_CONTROLPLANEFAL_H__

#include <CommonTypes/CT_ControlPlane_Requests.h>

class TL1_ControlPlaneFal  
{
public:
    
    TL1_ControlPlaneFal( );

    virtual ~TL1_ControlPlaneFal();

    TL1_ControlPlaneFal& operator=( const TL1_ControlPlaneFal& theInst );

    bool operator==( const TL1_ControlPlaneFal& theBlock ) const;

    inline void*    GetFal( ) const;
    inline void     SetFal( const void* theFalData );

private:

    void* myFalData;
};

//--------------------------------------------------------------------------------
inline void*    
TL1_ControlPlaneFal::GetFal( ) const
{
    return myFalData;
}

inline void             
TL1_ControlPlaneFal::SetFal( const void* theFalData )
{
    myFalData = const_cast<void*>(theFalData);
}

#endif /* __TL1_CONTROLPLANEFAL_H__ */

