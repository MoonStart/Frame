/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 System Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SYSDOMAIN_H__
#define __TL1_SYSDOMAIN_H__

#ifndef __CT_TL1_SYSTEM_H__
#include <CommonTypes/CT_TL1_System.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

class CT_TimeTm;


/**
   CLASS TL1_SysDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of system related TL1 commands, that a TL1 Entities
   for a system is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_SystemDomain
{
public:

    virtual void AbtCmd( )= 0;              //Not supported by Lumos

    virtual void AlwCondRept( )= 0;         //AP200

    virtual void AlwMsgAll( )= 0;           //AP200

    virtual void InhMsgAll( )= 0;           //AP200

    virtual void InitSys( CT_TL1_InitPhase* theInitPhase,
                          TL1_Response& theResponse ) = 0;       

    virtual void RtrvTod( TL1_Response& theResponse )const = 0;

    virtual void RtrvHdr( TL1_Response& theResponse )const = 0;

    virtual void RtrvLog( )const= 0;        //AP200

    virtual void RtrvCondSched( )const = 0; //AP200

    virtual void SchedCondRept( ) = 0;      //AP200

    virtual void SetDat( const CT_TimeTm& theDateAndTime,
                         bool  isDateSet,
                         bool  isTimeSet,
                         TL1_Response& theResponse) = 0;
};

#endif
