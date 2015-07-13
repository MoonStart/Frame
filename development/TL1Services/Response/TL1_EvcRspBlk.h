/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive cross-connection Response Class
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Retrive cross-conection Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EVCRSPBLK_H_
#define __TL1_EVCRSPBLK_H_

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

#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_TL1_EvcAddr.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AM_Definitions.h>

#include <vector>

using namespace std;

typedef list<CT_TEL_VlanTag> VlanTag_List;


class TL1_EvcRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_EvcRspBlk() {}
    
    TL1_EvcRspBlk(const TL1_EvcRspBlk& );
//For RTRV-EVC 
    TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                  const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<bool>& theRedlined,
                  const TL1_SmartParameter<bool>& isAllFrame,
                  const TL1_SmartParameter<VlanTag_List>& theCVidList,
                  const TL1_SmartParameter<VlanTag_List>& theSVidList,
                  const TL1_SmartParameter<CT_TEL_VlanTag>& theSVid,
                  const TL1_SmartParameter<int>& theBwpfCOS0,
                  const TL1_SmartParameter<bool>& theDiscPause,
                  const TL1_SmartParameter<CT_TEL_PbitRegen>& thePbitRegen,
                  const TL1_SmartParameter<bool> theAisState,
                  const TL1_SmartParameter<int>  theAisInterval,
                  const TL1_SmartParameter<int>  theAisMegLevel,
                  const TL1_SmartParameter<CT_TEL_MacMode> theDestMacModeLevel,
                  const TL1_SmartParameter<bool>& theLoopbackState,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST,
                  const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile);
//For EVC DBCHG
    TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                  const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<bool>& theRedlined,
                  const TL1_SmartParameter<bool>& isAllFrame,
                  const TL1_SmartParameter<VlanTag_List>& theCVidList,
                  const TL1_SmartParameter<VlanTag_List>& theSVidList,
                  const TL1_SmartParameter<VlanTag_List>& theAddCVidList,
                  const TL1_SmartParameter<VlanTag_List>& theAddSVidList,
                  const TL1_SmartParameter<VlanTag_List>& theRmvCVidList,
                  const TL1_SmartParameter<VlanTag_List>& theRmvSVidList,
                  const TL1_SmartParameter<CT_TEL_VlanTag>& theSVid,
                  const TL1_SmartParameter<int>& theBwpfCOS0,
                  const TL1_SmartParameter<bool>& theDiscPause,
                  const TL1_SmartParameter<CT_TEL_PbitRegen>& thePbitRegen,
                  const TL1_SmartParameter<bool> theAisState,
                  const TL1_SmartParameter<int>  theAisInterval,
                  const TL1_SmartParameter<int>  theAisMegLevel,
                  const TL1_SmartParameter<CT_TEL_MacMode> theDestMacModeLevel,
                  const TL1_SmartParameter<bool>& theLoopbackState,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST,
                  const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile);

    TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                  const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                  const TL1_SmartParameter<string>& theCircuitId,
                  const TL1_SmartParameter<int>&  theNpOwner,
                  const TL1_SmartParameter<bool>&  theQua,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST);

    TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST);

    TL1_EvcRspBlk(const TL1_SmartParameter<CT_EvcData>& theEvcId,
                  const TL1_SmartParameter<CT_TL1_EvcAddr>& theAddr,
                  const TL1_SmartParameter<string>& theCircuitId);
   
    virtual ~TL1_EvcRspBlk();

    TL1_EvcRspBlk& operator=( const TL1_EvcRspBlk& theBlock );
    bool operator==( const TL1_EvcRspBlk& theBlock ) const;

    const TL1_SmartParameter<CT_EvcData>&
        GetEvcId() const
    {
        return itsEvcId;
    }

    const TL1_SmartParameter<CT_TL1_EvcAddr>& 
        GetAddr() const
    {
        return itsAddr;
    }

    const TL1_SmartParameter<string>&
        GetCircuitId() const
    {
        return itsCircuitId;
    }

    const TL1_SmartParameter<bool>&
        GetAllFrames() const
    {
        return itsAllFrame;
    }

    const TL1_SmartParameter<bool>&
        GetRedline() const
    {
        return itsRedline;
    }

    const TL1_SmartParameter<int>& 
        GetNpOwner() const
    {
        return itsNpOwner;
    }

    const TL1_SmartParameter<bool>& 
        GetQuarantine() const
    {
        return itsQua;
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

    const TL1_SmartParameter<CT_TEL_VlanTag>& 
        GetSVid() const
    {
        return itsSVid;
    }

    const TL1_SmartParameter<VlanTag_List>& 
        GetCVidList() const
    {
        return itsCVidList;
    }

    const TL1_SmartParameter<VlanTag_List>& 
        GetSVidList() const
    {
        return itsSVidList;
    }

    const TL1_SmartParameter<VlanTag_List>& 
        GetAddCVidList() const
    {
        return itsAddCVidList;
    }

    const TL1_SmartParameter<VlanTag_List>& 
        GetAddSVidList() const
    {
        return itsAddSVidList;
    }

    const TL1_SmartParameter<VlanTag_List>& 
        GetRmvCVidList() const
    {
        return itsRmvCVidList;
    }

    const TL1_SmartParameter<VlanTag_List>& 
        GetRmvSVidList() const
    {
        return itsRmvSVidList;
    }

    const TL1_SmartParameter<int>& 
        GetBwpfCOS0() const
    {
        return itsBwpfCOS0;
    }

    const TL1_SmartParameter<bool>&
        GetDiscardPause() const
    {
        return itsDiscPause;
    }

    const TL1_SmartParameter<CT_TEL_PbitRegen>& GetPbitRegen() const
    {
        return itsPbitRegen;
    }

    const TL1_SmartParameter<bool>& GetAisState() const
    {
        return itsAisState;
    }

    const TL1_SmartParameter<int>& GetAisInterval() const
    {
        return itsAisInterval;
    }

    const TL1_SmartParameter<int>& GetAisMegLevel() const
    {
        return itsAisMegLevel;
    }

    const TL1_SmartParameter<CT_TEL_MacMode>& GetDestMacMode() const
    {
        return itsDestMacMode;
    }

    const TL1_SmartParameter<bool>&
        GetLoopbackState() const
    {
        return itsLoopbackState;
    }

    const TL1_SmartParameter<CT_ProfileTableId>&
        GetAlarmProfile() const
    {
        return itsAlarmProfile;
    }

private:

    TL1_SmartParameter<CT_EvcData>          itsEvcId;
    TL1_SmartParameter<CT_TL1_EvcAddr>      itsAddr;
    TL1_SmartParameter<bool>                itsAllFrame;
    TL1_SmartParameter<bool>                itsRedline;
    TL1_SmartParameter<string>              itsCircuitId;
    TL1_SmartParameter<int>                 itsNpOwner;
    TL1_SmartParameter<bool>                itsQua;
    TL1_SmartParameter<CT_SM_PST>           itsPST;
    TL1_SmartParameter<CT_SM_PSTQ>          itsPSTQ;
    TL1_SmartParameter<CT_SM_SST>           itsSST;
    TL1_SmartParameter<CT_TEL_VlanTag>      itsSVid;
    TL1_SmartParameter<VlanTag_List>        itsCVidList;
    TL1_SmartParameter<VlanTag_List>        itsSVidList;
    TL1_SmartParameter<VlanTag_List>        itsAddCVidList;
    TL1_SmartParameter<VlanTag_List>        itsAddSVidList;
    TL1_SmartParameter<VlanTag_List>        itsRmvCVidList;
    TL1_SmartParameter<VlanTag_List>        itsRmvSVidList;
    TL1_SmartParameter<int>                 itsBwpfCOS0;
    TL1_SmartParameter<bool>                itsDiscPause;
    TL1_SmartParameter<CT_TEL_PbitRegen>    itsPbitRegen;
    TL1_SmartParameter<bool>                itsAisState;
    TL1_SmartParameter<int>                 itsAisInterval;
    TL1_SmartParameter<int>                 itsAisMegLevel;
    TL1_SmartParameter<CT_TEL_MacMode>      itsDestMacMode;
    TL1_SmartParameter<bool>                itsLoopbackState;
    TL1_SmartParameter<CT_ProfileTableId>   itsAlarmProfile;
};

typedef TL1_Rtv_Response< TL1_EvcRspBlk > TL1_EvcResponse;

#endif

