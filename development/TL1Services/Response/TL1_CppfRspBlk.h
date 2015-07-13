/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Cppf Response Class
TARGET:
AUTHOR:         November 07, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Retrive CP Profile Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_CPPF_RESPONSE_BLOCK_H__
#define __TL1_CPPF_RESPONSE_BLOCK_H__

#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <Response/TL1_Response.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>

class TL1_CppfRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_CppfRspBlk( );
	
    TL1_CppfRspBlk( const string*                  theEntityName,
                    const CT_TL1_LogicalAddr*      theAddr,
                    const string*                  theProfName,
                    const CT_GMPLS_MODE*           theGMPLSMode,
                    const uint32*                  theRefreshSecs,
                    const CT_Advertisement*        theAdvertisement );
 	
    TL1_CppfRspBlk(const TL1_CppfRspBlk& );
    
    virtual ~TL1_CppfRspBlk();

    TL1_CppfRspBlk& operator=( const TL1_CppfRspBlk& t1Blk );

    bool operator==( const TL1_CppfRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetCppfAddr( CT_TL1_LogicalAddr& theAddr ) const;
    bool GetProfileName( string& theProfName ) const;
    bool GetGMPLSMode( CT_GMPLS_MODE& theGMPLSMode ) const;
    bool GetRefreshSeconds( uint32& theRefreshSecs ) const;
    bool GetAdvertisement( CT_Advertisement& theAdvertisement ) const;

    void SetEntityName( string& theEntityName );
    void SetCppfAddr( const CT_TL1_LogicalAddr& theAddr );
    void SetProfileName( const string& theProfName );
    void SetGMPLSMode( const CT_GMPLS_MODE& theGMPLSMode );
    void SetRefreshSeconds( const uint32& theRefreshSecs );
    void SetAdvertisement( const CT_Advertisement& theAdvertisement );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_CppfAddr,	
        INDEX_ProfileName,
        INDEX_GMPLSMode,
        INDEX_RefreshSecs,
        INDEX_Advertisement,
        INDEX_END
    };

    vector<bool>            myBitSet;

    string                  myEntityName;
    CT_TL1_LogicalAddr      myAddr;
    string                  myProfileName;
    CT_GMPLS_MODE           myGMPLSMode;
    uint32                  myRefreshSecs;
    CT_Advertisement        myAdvertisement;
};

typedef TL1_Rtv_Response< TL1_CppfRspBlk > TL1_CppfResponse;

#endif  // #ifndef __TL1_CPPF_RESPONSE_BLOCK_H__
#endif  // #ifdef  __cplusplus
