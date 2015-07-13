/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive SWV VERSION Response Class
TARGET:
AUTHOR:         Ed Bandyk
DESCRIPTION:    Header file for TL1 Retrive SWV VERSION Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_SWVERRESPONSE_BLOCK_H_
#define __TL1_SWVERRESPONSE_BLOCK_H_


#include <Response/TL1_Response.h>

#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_LED_Definitions.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_Telecom.h>

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_ACCEPTABLECPLIST_H_
#include <CommonTypes/CT_AcceptableCPList.h>
#endif

#include <vector>

using namespace std;

class TL1_SWVERRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_SWVERRspBlk();

    TL1_SWVERRspBlk(const string* entityName,
                      const CT_TL1_SlotAddr*    slotAddr,
                      const string              theVersion,
                      const uint8               thePatchLevel,
                      const CT_SoftwareStatus   theStatus
                      );

    TL1_SWVERRspBlk(const TL1_SWVERRspBlk& theBlk);

    virtual ~TL1_SWVERRspBlk();

    TL1_SWVERRspBlk& operator=( const TL1_SWVERRspBlk& theBlock );

    bool operator==( const TL1_SWVERRspBlk& theBlock ) const;

    bool GetEntityName( string& ) const ;

    bool GetSlotAddr( CT_TL1_SlotAddr& ) const ;

    bool GetVersion( string& ) const ;

    bool GetPatchLevel( uint8& ) const ;

    bool GetStatus( CT_SoftwareStatus& theStatus ) const ;

private:

        enum {
        INDEX_EntityName = 0,
        INDEX_SlotAddr,
        INDEX_Version,
        INDEX_PatchLevel,
        INDEX_Status,
        INDEX_END
        };

        vector<bool>        myBitSet;
        string              myEntityName;
        CT_TL1_SlotAddr     mySlotAddr;
        string              myVersion;
        uint8               myPatchLevel;
        CT_SoftwareStatus   myStatus;
};

typedef TL1_Rtv_Response< TL1_SWVERRspBlk > TL1_SwVerResponse;

#endif  // #ifndef __TL1_FPPAVERRESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
