/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 28, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Base implementation
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_Notification.h>

#include <TL1Core/TL1_NotifCenter.h>
#include <ErrorService/FC_Error.h>

TL1_Notification::TL1_Notification( TL1_NotifType theType,
                                    const TL1_Response& theResponse) :
    itsType( theType ),
    itsAtag( TL1_NotifCenter::Instance().GetNextAtag() ),
    itsResponse( theResponse )
{
}

TL1_Notification::~TL1_Notification()
{
}

const TL1_Response& TL1_Notification::GetResponse() const
{
    return itsResponse;
}
