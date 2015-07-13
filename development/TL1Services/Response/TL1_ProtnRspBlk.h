/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Protection Response Class
TARGET:
AUTHOR:        April 12, 2004 Maggie Zhang 
DESCRIPTION:    Header file for TL1 Retrive Protection Group Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PROTNRSPBLK_H_
#define __TL1_PROTNRSPBLK_H_

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
 
#ifndef __CT_PROTECTION_H__
#include <CommonTypes/CT_Protection.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef CT_PMA_GENERAL_H
#include <CommonTypes/CT_PMA_General.h>
#endif

#ifndef __CT_TL1_PM_H__
#include <CommonTypes/CT_TL1_Pm.h>
#endif

#include <vector>

using namespace std;


class TL1_ProtnRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_ProtnRspBlk() {}
    
    TL1_ProtnRspBlk(const TL1_ProtnRspBlk& );

    TL1_ProtnRspBlk( const CT_TL1_ProtnAddr*    theAddr,
                     const CT_ProtGpType*       theType,
                     const bool*                theRtrtv,
                     const int*                 theWtr,
                     const int*                 theProtHoldOffTime,
                     const CT_ProtGpType*       theProtectType,
                     const bool*                theCPFlag,
                     const int*                 theNpOwner,
                     const CT_SM_PST*           thePST,
                     const CT_SM_PSTQ*          thePSTQ,
                     const CT_SM_SST*           theSST );
   
    virtual ~TL1_ProtnRspBlk();

    TL1_ProtnRspBlk& operator=( const TL1_ProtnRspBlk& theBlock );

	bool operator==(const TL1_ProtnRspBlk& theBlock) const;

    void SetBiSwitching(bool isBiSwitching);
    void SetProtnRequset(CT_ProtnRequest theProtnRequest);
    
	bool GetAddr(CT_TL1_ProtnAddr&) const;

    bool GetType(CT_ProtGpType&) const;
    bool GetBiSwitching(bool&) const;
    bool GetProtnRequest(CT_ProtnRequest&) const;

    bool GetRtrtv(bool&) const;

    bool GetWtr(int&) const;

    bool GetProtHoldOffTime(int&) const;
    
    bool GetProtectType(CT_ProtGpType&) const;

    bool GetCPFlag(bool&) const;

    bool GetNpOwner(int&) const;

    bool GetPST(CT_SM_PST&) const;

    bool GetPSTQ(CT_SM_PSTQ&) const;

    bool GetSST(CT_SM_SST&) const;


    void Reset();


private:

    enum {
           INDEX_Addr = 0,
           INDEX_Type,
           INDEX_BiSwitching,
           INDEX_ProtnRequest,
           INDEX_Rtrtv,
           INDEX_Wtr,
           INDEX_ProtHoldTime,
           INDEX_ProtectType,
           INDEX_CPFlag,
           INDEX_NpOwner,
           INDEX_PST,
           INDEX_PSTQ,
           INDEX_SST,
           INDEX_END
         };

    vector<bool>      itsBitSet;
    CT_TL1_ProtnAddr  itsAddr;
    CT_ProtGpType     itsType;
    bool              itsBiSwitching;
    CT_ProtnRequest   itsProtnRequest;
    bool              itsRtrtv;
    int               itsWtr;
    int               itsProtHoldOffTime;
    CT_ProtGpType     itsProtectType;
    bool              itsCPFlag;
    int               itsNpOwner;
    CT_SM_PST         itsPST;
    CT_SM_PSTQ        itsPSTQ;
    CT_SM_SST         itsSST;

};

typedef TL1_Rtv_Response< TL1_ProtnRspBlk > TL1_ProtnResponse;

class TL1_ProtnEvtSSTChgRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_ProtnEvtSSTChgRspBlk() {};
    
    // TL1_ProtnEvtSSTChgRspBlk(const TL1_ProtnRspBlk& );

    TL1_ProtnEvtSSTChgRspBlk(const TL1_SmartParameter< const CT_TL1_ProtnAddr* > &theAddr,
                  const TL1_SmartParameter< string > &theEntityName,
                  const TL1_SmartParameter< CT_ConditionType > &theSST,
                  const TL1_SmartParameter< CT_TL1_ConditionEffect > &theConditionEffect,
                  const TL1_SmartParameter< CT_NEFlag > &theLocation,
                  const TL1_SmartParameter< string > &theDescription); 
                  /*
	          const TL1_SmartParameter< CT_PMA_ParamId > &theParamId,
                  const TL1_SmartParameter< CT_TimeTm > &theOcrDateOcrTime,
                  */

    const TL1_SmartParameter< CT_TL1_ProtnAddr >& GetFacAddr() const
    {
        return itsProtnAddr;
    }
    const TL1_SmartParameter< string >& GetEntityName() const
    {
        return itsEntityName;
    }
    const TL1_SmartParameter< CT_ConditionType >& GetSST() const
    {
        return itsSST;
    }
    const TL1_SmartParameter< CT_TL1_ConditionEffect >& GetConditionEffect() const
    {
        return itsConditionEffect;
    }
    const TL1_SmartParameter< string >& GetDescription() const
    {
        return itsDescription;
    }
    const TL1_SmartParameter< CT_FacilitySubType >& GetFacType() const
    {
        return itsFacType;
    }
    const TL1_SmartParameter< CT_NEFlag >& GetLocation() const
    {
        return itsLocation;
    }
    virtual ~TL1_ProtnEvtSSTChgRspBlk();
private:
    TL1_SmartParameter< string >                       itsEntityName;
    TL1_SmartParameter< CT_PMA_ParamId >               itsParamId;
    TL1_SmartParameter< CT_ConditionType >             itsSST;
    TL1_SmartParameter< CT_TL1_ConditionEffect >       itsConditionEffect;
    TL1_SmartParameter< CT_TimeTm >                    itsOcrDateOcrTime;
    TL1_SmartParameter< CT_NEFlag >                    itsLocation;
    TL1_SmartParameter< string >                       itsDescription;
    TL1_SmartParameter< CT_TL1_ProtnAddr >             itsProtnAddr;
    TL1_SmartParameter< CT_FacilitySubType >           itsFacType;
};

#endif


