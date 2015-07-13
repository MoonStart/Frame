/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive EXPPATH Response Class
TARGET:
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for TL1 Retrive EXPPATH Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_EXPPATH_RESPONSE_BLOCK_H__
#define __TL1_EXPPATH_RESPONSE_BLOCK_H__

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
class TL1_ExppathRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_ExppathRspBlk( );

    virtual ~TL1_ExppathRspBlk( );

    TL1_ExppathRspBlk& operator=( const TL1_ExppathRspBlk& t1Blk );

    bool operator==( const TL1_ExppathRspBlk& t1Blk ) const;

    bool GetExppath( CT_ControlPlane_Hops& theExppath ) const;
    void SetExppath( const CT_ControlPlane_Hops& theExppath );

    bool GetExppathName( string& theExppathName ) const;
    void SetExppathName( const string& theExppathName );

    bool GetExppathAddr( CT_TL1_ExppathAddr& theExppathAddr ) const;
    void SetExppathAddr( const CT_TL1_ExppathAddr& theExppathAddr );

private:
    enum 
    {   
        INDEX_ExppathAddr  = 0,
        INDEX_ExppathName,
        INDEX_Exppath,
        INDEX_END
    };

    vector<bool>            myBitSet;

    CT_TL1_ExppathAddr      myExppathAddr;
    string                  myExppathName;
    CT_ControlPlane_Hops    myExppath;
};
typedef TL1_Rtv_Response< TL1_ExppathRspBlk > TL1_ExppathResponse;

#endif  // #ifndef __TL1_EXPPATH_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
