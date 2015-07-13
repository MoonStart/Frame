/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive cross-connection Response Class
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Retrive cross-conection Response class declaration
LAST REVISION:
   Date    Description
   ----    -----------
 10-15-08  t71mr00076507:Add response block for RTRV-CRS-VCG.
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CRSRSPBLK_H_
#define __TL1_CRSRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif
 
#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_XCTYPES_H_
#include <CommonTypes/CT_XcTypes.h>
#endif

#ifndef CT_TESTACCESSTYPES_H
#include <CommonTypes/CT_TestAccessTypes.h>
#endif

#include <CommonTypes/CT_Protection.h>

#include <vector>

using namespace std;


class TL1_CrsRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_CrsRspBlk() {}
    
    TL1_CrsRspBlk(const TL1_CrsRspBlk& );

    TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                  const TL1_SmartParameter<CT_XcType>& theType,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<CT_XcPathData>& thePathData, // includes from_cp_aid and to_cp_aid
                  const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theToAddrs,
                  const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theProtToAddrs,
                  const TL1_SmartParameter<string>& theGrpId,
				  const TL1_SmartParameter<bool>& theAutoCfg,
                  const TL1_SmartParameter<int>&  theNpOwner,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST);

    TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                  const TL1_SmartParameter<CT_XcType>& theType,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<CT_XcPathData>& thePathData, // includes from_cp_aid and to_cp_aid
                  const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theToAddrs,
                  const TL1_SmartParameter<CT_TL1_CrsDropAddrs>& theProtToAddrs,
                  const TL1_SmartParameter<CT_BRTA_ModeType>& theBrtaMode,
                  const TL1_SmartParameter<CT_TL1_CrsAddr>& theBrPair,
                  const TL1_SmartParameter<CT_TapNumber>& theTapNum,
                  const TL1_SmartParameter<bool>& theAutoCfg,
                  const TL1_SmartParameter<CT_SM_SST>&  theSrcProtStatus,
                  const TL1_SmartParameter<CT_SM_SST>&  theDstProtStatus,
                  const TL1_SmartParameter<CT_ProtGpType>&  theSrcProtType,
                  const TL1_SmartParameter<CT_ProtGpType>&  theDstProtType,
                  const TL1_SmartParameter<int>&  theNpOwner,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST);

    TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST);

    TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                  const TL1_SmartParameter<CT_XcType>& theType,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<CT_XcPathData>& thePathData);


    /* Used for: RTRV-CRS-VCG */
    TL1_CrsRspBlk(const TL1_SmartParameter<CT_TL1_CrsAddr>& theAddr,
                  const TL1_SmartParameter<CT_XcType>& theType,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<bool>& theRedLined );
   

    virtual ~TL1_CrsRspBlk();

    TL1_CrsRspBlk& operator=( const TL1_CrsRspBlk& theBlock );
    bool operator==( const TL1_CrsRspBlk& theBlock ) const;
    bool operator<( const TL1_CrsRspBlk& theBlock ) const;

    const TL1_SmartParameter<CT_TL1_CrsAddr>& 
        GetAddr() const
    {
        return itsAddr;
    }

    const TL1_SmartParameter<CT_XcType>& 
        GetType() const
    {
        return itsType;
    }

    const TL1_SmartParameter<string>&
        GetCircuitId() const
    {
        return itsCircuitId;
    }

    const TL1_SmartParameter<CT_XcPathData>&
        GetPathData() const
    {
        return itsPathData;
    }

    const TL1_SmartParameter<CT_TL1_CrsDropAddrs>&
        GetToAddrs() const
    {
        return itsToAddrs;
    }

    const TL1_SmartParameter<CT_TL1_CrsDropAddrs>&
        GetProtToAddrs() const
    {
        return itsProtToAddrs;
    }

    const TL1_SmartParameter<string>&
        GetGrpId() const
    {
        return itsGrpId;
    }

    const TL1_SmartParameter<CT_BRTA_ModeType>& 
        GetBrtaMode() const
    {
        return itsBrtaMode;
    }

    const TL1_SmartParameter<CT_TL1_CrsAddr>& 
        GetBrPair() const
    {
        return itsBrPair;
    }

    const TL1_SmartParameter<CT_TapNumber>& 
        GetTapNum() const
    {
        return itsTapNum;
    }

    const TL1_SmartParameter<bool>& 
        GetAutoCfg() const
    {
        return itsAutoCfg;
    }

    const TL1_SmartParameter<int>& 
        GetNpOwner() const
    {
        return itsNpOwner;
    }

    const TL1_SmartParameter<bool>& 
        GetRedLined() const
    {
        return itsRedLined;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSrcProtStatus() const
    {
        return itsSrcProtStatus;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetDstProtStatus() const
    {
        return itsDstProtStatus;
    }

    const TL1_SmartParameter<CT_ProtGpType>& 
        GetSrcProtType() const
    {
        return itsSrcProtType;
    }

    const TL1_SmartParameter<CT_ProtGpType>& 
        GetDstProtType() const
    {
        return itsDstProtType;
    }

    const TL1_SmartParameter<CT_SM_PST>&
        GetPST() const
    {
        return itsPST;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>&
        GetPSTQ() const
    {
        return itsPSTQ;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSST() const
    {
        return itsSST;
    }

private:

    TL1_SmartParameter<CT_TL1_CrsAddr>      itsAddr;
    TL1_SmartParameter<CT_XcType>           itsType;
    TL1_SmartParameter<string>              itsCircuitId;
    TL1_SmartParameter<CT_XcPathData>       itsPathData;
    TL1_SmartParameter<CT_TL1_CrsDropAddrs> itsToAddrs;
    TL1_SmartParameter<CT_TL1_CrsDropAddrs> itsProtToAddrs;
    TL1_SmartParameter<string>              itsGrpId;
    TL1_SmartParameter<CT_BRTA_ModeType>    itsBrtaMode;
    TL1_SmartParameter<CT_TL1_CrsAddr>      itsBrPair;
    TL1_SmartParameter<CT_TapNumber>        itsTapNum;
    TL1_SmartParameter<bool>                itsAutoCfg;
    TL1_SmartParameter<CT_SM_SST>           itsSrcProtStatus;
    TL1_SmartParameter<CT_SM_SST>           itsDstProtStatus;
    TL1_SmartParameter<CT_ProtGpType>       itsSrcProtType;
    TL1_SmartParameter<CT_ProtGpType>       itsDstProtType;
    TL1_SmartParameter<int>                 itsNpOwner;
    TL1_SmartParameter<bool>                itsRedLined;
    TL1_SmartParameter<CT_SM_PST>           itsPST;
    TL1_SmartParameter<CT_SM_PSTQ>          itsPSTQ;
    TL1_SmartParameter<CT_SM_SST>           itsSST;

};

typedef TL1_Rtv_Response< TL1_CrsRspBlk > TL1_CrsResponse;

#endif


