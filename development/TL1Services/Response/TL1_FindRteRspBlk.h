/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OPR-FINDRTE Response Class
TARGET:
AUTHOR:         July 07, 2011 - TLD
DESCRIPTION:    TL1 OPR-FINDRTE response, class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_FINDRTERSPBLK_H__
#define __TL1_FINDRTERSPBLK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>



//---------------------------------------------------------------------------------------
class TL1_FindRteRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_FindRteRspBlk( );
	
	TL1_FindRteRspBlk( const CT_CallPathType theCallPathType,
                       const CT_FindRte_Status theFindRteStatus,
                       const CT_ControlPlane_Hops& theRouteElements );
	
	TL1_FindRteRspBlk( const TL1_FindRteRspBlk& );
    
    virtual ~TL1_FindRteRspBlk();

    /* Overloaded operators */
    TL1_FindRteRspBlk& operator=( const TL1_FindRteRspBlk& theObject );
    bool operator==( const TL1_FindRteRspBlk& theObject ) const;
    bool operator!=( const TL1_FindRteRspBlk& theObject ) const;

    /* Member Get methods */
    bool GetCallPathType( CT_CallPathType& theCallPathType ) const;
    bool GetFindRteStatus( CT_FindRte_Status& theFindRteStatus ) const;
    bool GetRouteElements( CT_ControlPlane_Hops& theRouteElements ) const;

    /* Member Set methods */
    void SetCallPathType( const CT_CallPathType& theCallPathType );
    void SetFindRteStatus( const CT_FindRte_Status& theFindRteStatus );
    void SetRouteElements( const CT_ControlPlane_Hops& theRouteElements );


private:

    enum 
    {
        INDEX_CallPathType = 0,
        INDEX_FindRteStatus,
        INDEX_RouteElements,
        INDEX_END
    };

    vector<bool>                 myBitSet;

    CT_CallPathType              myCallPathType;
    CT_FindRte_Status            myFindRteStatus;
    CT_ControlPlane_Hops         myRouteElements;
};

typedef TL1_Rtv_Response< TL1_FindRteRspBlk > TL1_FindRteResponse;

#endif  // #ifndef __TL1_FINDRTERSPBLK_H__

#endif  // #ifdef  __cplusplus
