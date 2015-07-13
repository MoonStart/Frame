/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 08, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Control Plane SLPF Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLPFENTITY_H__
#define __TL1_SLPFENTITY_H__

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_SLPFDOMAIN_H__
#include "TL1Core/TL1_SlpfDomain.h"
#endif

#ifndef _CT_SM_TYPES_H_
#include "CommonTypes/CT_SM_Types.h"
#endif

class AG7100_SlaProfileIf;
class AG7100_SlaPolicyIf;
class SLA_ProfileSubApplication;
class SLA_PolicySubApplication;
class SLA_ProfileRegion;
class SLA_PolicyRegion;
class SLA_ProfileConfig;
class SLA_PolicyConfig;
class CT_TL1_LogicalAddr;
class TL1_SlpfRspBlk;
class TL1_SlpolicyRspBlk;
class SM_AdminRegion;

class TL1_SlpfEntity : public TL1_Entity,        // Base Class
                       public TL1_SlpfDomain    // Protocol Class
{
public:
    
    TL1_SlpfEntity( );

    virtual ~TL1_SlpfEntity( );

    void PopulateRspBlk(SLA_ProfileConfig& theConfig, TL1_SlpfRspBlk& rspBlk);
    virtual void RtrvSlpf(const CT_TL1_LogicalAddr& theSlpfAddr, 
                          const LT_ProfName         theProfileName,
                          TL1_Response&             theResponse ) {}

    static AG7100_SlaProfileIf&       GetControlPlaneSlpfIf( );
    static SLA_ProfileSubApplication& GetControlPlaneSlpfSubApp( );
    static SLA_ProfileRegion&         GetControlPlaneSlpfRegion( );
    static SLA_ProfileConfig          GetControlPlaneSlpfConfig(const CT_TL1_LogicalAddr& theSlpfAddr);
    static SLA_ProfileConfig          GetControlPlaneSlpfConfig(uint16 theProfileId);

    int                               GetSlpfNum(const CT_TL1_LogicalAddr& theAddr) const; 
};

class TL1_SlpolicyEntity : public TL1_Entity,        // Base Class
                           public TL1_SlpolicyDomain    // Protocol Class
{
public:
    
    TL1_SlpolicyEntity( );

    virtual ~TL1_SlpolicyEntity( );

    void PopulateRspBlk(SLA_PolicyConfig& theConfig, TL1_SlpolicyRspBlk& rspBlk);
    virtual void RtrvSlpolicy(const CT_TL1_LogicalAddr& theSlpolicyAddr, TL1_Response& theResponse ) {}

    AG7100_SlaPolicyIf&       GetControlPlaneSlpolicyIf( ) const;
    SLA_PolicySubApplication& GetControlPlaneSlpolicySubApp( ) const;
    SLA_PolicyRegion&         GetControlPlaneSlpolicyRegion( ) const;
    SLA_PolicyConfig          GetControlPlaneSlpolicyConfig(const CT_TL1_LogicalAddr& theSlpfAddr);

};

#endif
