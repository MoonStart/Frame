/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         Aug 11, 2003- Christian Halle 
DESCRIPTION:    Header file for TL1 Retrieve Software response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWRSPBLK_H__
#define __TL1_SWRSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif


class TL1_RtrvSwRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtrvSwRspBlk(){}

    TL1_RtrvSwRspBlk( const TL1_RtrvSwRspBlk& theBlock );

    TL1_RtrvSwRspBlk( const TL1_SmartParameter< string >&       theVendor,
                      const TL1_SmartParameter< string >&       theSwType,
                      const TL1_SmartParameter< string >&       theSwVersion,
                      const TL1_SmartParameter< string >&       thePatchLevel,
                      const TL1_SmartParameter< string >&       theSwContext,
                      const TL1_SmartParameter< int >&          theSize,
                      const TL1_SmartParameter< string >&       theLacation,
                      const TL1_SmartParameter< string >&       theLastUpdate,
                      const TL1_SmartParameter< string >&       thePath,
                      const TL1_SmartParameter< CT_SM_PST >&    thePst,
                      const TL1_SmartParameter< CT_SM_PSTQ >&   thePstq,
                      const TL1_SmartParameter< CT_SM_SST >&    theSst);

    virtual ~TL1_RtrvSwRspBlk();

    TL1_RtrvSwRspBlk& operator=( const TL1_RtrvSwRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetVendor() const
    {
        return itsVendor;
    }

    const TL1_SmartParameter< string >&
        GetSwType() const
    {
        return itsSwType;
    }

    const TL1_SmartParameter< string >&
        GetSwVersion() const
    {
        return itsSwVersion;
    }

    const TL1_SmartParameter< string >&
        GetPatchLevel() const
    {
        return itsPatchLevel;
    }

    const TL1_SmartParameter< string >&
        GetSwContext() const
    {
        return itsSwContext;
    }

    const TL1_SmartParameter< int >&
        GetSize() const
    {
        return itsSize;
    }

    const TL1_SmartParameter< string >&
        GetLocation() const
    {
        return itsLocation;
    }

    const TL1_SmartParameter< string >&
        GetLastUpdate() const
    {
        return itsLastUpdate;
    }

    const TL1_SmartParameter< string >&
        GetPath() const
    {
        return itsPath;
    }

    const TL1_SmartParameter<CT_SM_PST>& 
        GetPst() const
    {
        return itsPst;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>& 
        GetPstq() const
    {
        return itsPstq;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSst() const
    {
        return itsSst;
    }

private:
    TL1_SmartParameter< string >        itsVendor;
    TL1_SmartParameter< string >        itsSwType;
    TL1_SmartParameter< string >        itsSwVersion;
    TL1_SmartParameter< string >        itsPatchLevel;
    TL1_SmartParameter< string >        itsSwContext;
    TL1_SmartParameter< int >           itsSize;
    TL1_SmartParameter< string >        itsLocation;
    TL1_SmartParameter< string >        itsLastUpdate;
    TL1_SmartParameter< string >        itsPath;
    TL1_SmartParameter< CT_SM_PST >     itsPst;
    TL1_SmartParameter< CT_SM_PSTQ >    itsPstq;
    TL1_SmartParameter< CT_SM_SST >     itsSst;
};

typedef TL1_Rtv_Response< TL1_RtrvSwRspBlk > TL1_RtrvSwResponse;


#endif //__TL1_SWRSPBLK_H__
