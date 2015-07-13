#ifndef __TL1_TACC_RESPONSE_BLOCK_H__
#define __TL1_TACC_RESPONSE_BLOCK_H__
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TACC Response Class
TARGET:
AUTHOR:         December 7, 2006 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Retrive Tacc Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus


#include <Response/TL1_Response.h>
#include <CommonTypes/CT_TL1_Base.h>

#ifndef CT_TESTACCESSTYPES_H
#include <CommonTypes/CT_TestAccessTypes.h>
#endif

class TL1_TaccRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_TaccRspBlk( ) {}
	
	TL1_TaccRspBlk(const TL1_TaccRspBlk&);
    
	TL1_TaccRspBlk( const string* theTapAid,
                   const CT_XcFacData* theTapTermAid1,
                   const CT_XcFacData* theTapTermAid2,
                   const CT_XcFacData* theEquipAid,
                   const CT_XcFacData* theFacAid,
                   const CT_BRTA_ModeType* theTapMode,
                   const string* theTapStatus);


    virtual ~TL1_TaccRspBlk();

    TL1_TaccRspBlk& operator=( const TL1_TaccRspBlk& theBlock );

    bool GetTapAid(string&) const;
    bool GetTapTermAid1(CT_XcFacData&) const;
    bool GetTapTermAid2(CT_XcFacData&) const;
    bool GetEquipAid(CT_XcFacData&) const;
    bool GetFacAid(CT_XcFacData&) const;
    bool GetTapMode(CT_BRTA_ModeType&) const;
    bool GetTapStatus(string&) const;

private:

    enum {
        INDEX_TapAid = 0,
        INDEX_TapTermAid1,
        INDEX_TapTermAid2,
        INDEX_EquipAid,
        INDEX_FacAid,
        INDEX_TapMode,
        INDEX_TapStatus,
        INDEX_END
	};

    vector<bool>     myBitSet;
    string				myTapAid;
    CT_XcFacData           myTapTermAid1;
    CT_XcFacData           myTapTermAid2;
    CT_XcFacData           myEquipAid;
    CT_XcFacData           myFacAid;
    CT_BRTA_ModeType  myTapMode;
    string           myTapStatus;

};

typedef TL1_Rtv_Response< TL1_TaccRspBlk > TL1_TaccResponse;

#endif  // #ifdef  __cplusplus
#endif  // #ifndef __TL1_TACC_RESPONSE_BLOCK_H__

