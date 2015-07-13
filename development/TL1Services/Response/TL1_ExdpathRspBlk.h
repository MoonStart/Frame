/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive EXDPATH Response Class
TARGET:
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Header file for TL1 Retrive EXDPATH Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_EXDPATH_RESPONSE_BLOCK_H__
#define __TL1_EXDPATH_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

//---------------------------------------------------------------------------------------
class TL1_ExdpathRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_ExdpathRspBlk( );

    virtual ~TL1_ExdpathRspBlk( );

    TL1_ExdpathRspBlk& operator=( const TL1_ExdpathRspBlk& t1Blk );

    bool operator==( const TL1_ExdpathRspBlk& t1Blk ) const;

    bool GetExdpath( CT_ControlPlane_Hops& theExdpath ) const;
    void SetExdpath( const CT_ControlPlane_Hops& theExdpath );

    bool GetExdpathName( string& theExdpathName ) const;
    void SetExdpathName( const string& theExdpathName );

    bool GetExdpathAddr( CT_TL1_ExdpathAddr& theExdpathAddr ) const;
    void SetExdpathAddr( const CT_TL1_ExdpathAddr& theExdpathAddr );

private:
    enum 
    {   
        INDEX_ExdpathAddr  = 0,
        INDEX_ExdpathName,
        INDEX_Exdpath,
        INDEX_END
    };

    vector<bool>            myBitSet;

    CT_TL1_ExdpathAddr      myExdpathAddr;
    string                  myExdpathName;
    CT_ControlPlane_Hops    myExdpath;
};
typedef TL1_Rtv_Response< TL1_ExdpathRspBlk > TL1_ExdpathResponse;

#endif  // #ifndef __TL1_EXDPATH_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus

