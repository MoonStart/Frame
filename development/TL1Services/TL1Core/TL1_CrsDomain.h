/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 15, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 cross-connection Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CRSDOMAIN_H__
#define __TL1_CRSDOMAIN_H__

#ifndef __CT_XCTYPES_H__
#include <CommonTypes/CT_XcTypes.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef CT_TESTACCESSTYPES_H
#include <CommonTypes/CT_TestAccessTypes.h>
#endif

#include <CommonTypes/CT_Protection.h>

#include <LumosTypes/LT_System.h>

class CT_TL1_CrsAddr;
class TL1_Response;

/**
   CLASS TL1_CrsDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of CRS related TL1 commands, that a TL1 Entities
   for a CRS is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_CrsDomain
{
public:

    virtual void RtrvCrs(const LT_Handle&       theHandle,
                         const CT_TL1_CrsAddr&  theAddr,
                         string*                theGrpId,
                         CT_BRTA_ModeType*      theBrtaMode,
                         TL1_Response&          theResponse) = 0;

    virtual void RtrvCrs(const CT_TL1_CrsAddr& theFirstAddr,
                         const CT_TL1_CrsAddr& theLastAddr,
                         string* theGrpId,
                         CT_BRTA_ModeType* theBrtaMode,
                         TL1_Response& theResponse){}

    virtual void EntCrs( const CT_TL1_CrsAddr& theAddr,
                         CT_XcType* theType,
                         string* theCircuitId,
                         bool* theRdld,
                         // CRM attributes cc_path, from_cp_aid, and to_cp_aid
                         // will be part of the CT_XcPathData.
                         CT_XcPathData* thePathData,
                         string* theGrpId,
                         CT_ProtGpType* theSrcProtType,
                         CT_ProtGpType* theDstProtType,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag,
                         bool* theCommandMode)= 0;

    virtual void ValidateCrs( const CT_TL1_CrsAddr& theAddr,
                              CT_XcType* theType,
                              string* theCircuitId,
                              // CRM attributes cc_path, from_cp_aid, and to_cp_aid
                              // will be part of the CT_XcPathData.
                              CT_XcPathData* thePathData,
                              TL1_Response& theResponse)= 0;
    
    virtual void EdCrs(  const CT_TL1_CrsAddr& theAddr,
                            string* theCircuitId,
                            bool* theRdld,
                            bool* theIncl,
                            CT_ProtGpType* theSrcProtType,
                            CT_ProtGpType* theDstProtType,
                            CT_XcPathData* thePathData,
                            CT_TL1_FacAddr* theAddTo, 
                            CT_XcFacType* theAddToFacType,
                            CT_TL1_FacAddr* theRemoveTo,
                            CT_XcFacType* theRemoveToFacType, 
                            CT_TL1_FacAddr* theAddProtTo, 
                            CT_XcFacType* theAddProtToFacType,
                            CT_TL1_FacAddr* theRemoveProtTo,
                            CT_XcFacType* theRemoveProtToFacType, 
                            string* theGrpId,
                            CT_TL1_FacAddr* theOldTP, 
                            CT_XcFacType* theOldTPFacType,
                            CT_TL1_FacAddr* theNewTP,
                            CT_XcFacType* theNewTPFacType,
                            bool* theCommandMode,
                            CT_TL1_FacAddr* theAddSrcProt, 
                            CT_XcFacType* theAddSrcProtFacType,
                            CT_TL1_FacAddr* theAddDstProt,
                            CT_XcFacType*   theAddDstFacType, 
                            CT_TL1_FacAddr* theRmvProt, 
                            CT_XcFacType*   theRmvProtFacType,
                            TL1_Response& theResponse,
                            LT_Handle theHandle,
                            LT_Ctag   theCtag)= 0;
    
    virtual void DltCrs( const CT_TL1_CrsAddr& theAddr,
                         bool* theIncl,
                         bool* theCommandMode,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;

    virtual void EntRoll( CT_XcFacData& fromFac,
                          CT_XcFacData& toFac,
                          CT_XcFacData& rollFromFac,
                          CT_XcFacData& rollToFac,
                          bool* ctAutoManual,
                          bool* ctIncl,
                          TL1_Response& theResponse,
                          LT_Handle theHandle,
                          LT_Ctag   theCtag)= 0;

    virtual void DltRoll( CT_XcFacData& fromFac,
                          CT_XcFacData& toFac,
                          bool* ctIncl,
                          TL1_Response& theResponse,
                          LT_Handle theHandle,
                          LT_Ctag   theCtag)= 0;

};

#endif
