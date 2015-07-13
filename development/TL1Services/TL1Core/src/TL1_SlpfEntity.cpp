/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:
AUTHOR:         June 12, 2005 - Tong Wu
DESCRIPTION:    Implementation file for TL1 SLPF Entity Base class
-----------------------------------------------------------------------------*/

#include "TL1Core/TL1_SlpfEntity.h"
#include <TL1Core/T7100_TL1RegionValidate.h>
#include <Response/TL1_SlpfRspBlk.h>
#include <AG7100/AG7100_AgentIf.h>
#include <AG7100/AG7100_ControlPlaneIf.h>
#include <AG7100/AG7100_SlaProfileIf.h>
#include <AG7100/AG7100_SlaPolicyIf.h>
#include <ControlPlane/SLA_ProfileSubApplication.h>
#include <ControlPlane/SLA_PolicySubApplication.h>
#include <ControlPlane/SLA_ProfileRegion.h>
#include <ControlPlane/SLA_PolicyRegion.h>
#include <ControlPlane/SLA_ProfileConfig.h>
#include <ControlPlane/SLA_PolicyConfig.h>
#include <TL1Core/TL1_SlpfParameters.h>
#include <StateManagement/SM_SubApplication.h>

//--------------------------------------------------------------------------
TL1_SlpfEntity::TL1_SlpfEntity()
{
}

//--------------------------------------------------------------------------
TL1_SlpfEntity::~TL1_SlpfEntity()
{
}

//--------------------------------------------------------------------------
AG7100_SlaProfileIf&
TL1_SlpfEntity::GetControlPlaneSlpfIf( )
{
    return AG7100_AgentIf::GetInstance().GetControlPlaneIf( ).GetSlaProfileIf( );
}

//--------------------------------------------------------------------------
SLA_ProfileSubApplication&
TL1_SlpfEntity::GetControlPlaneSlpfSubApp( )
{
    return GetControlPlaneSlpfIf( ).GetProfileSubApp( );
}

//--------------------------------------------------------------------------
SLA_ProfileRegion&
TL1_SlpfEntity::GetControlPlaneSlpfRegion( )
{
    return T7100_TL1RegionValidate( GetControlPlaneSlpfSubApp( ).GetConfigRegion( ) );
}

//--------------------------------------------------------------------------
SLA_ProfileConfig
TL1_SlpfEntity::GetControlPlaneSlpfConfig(const CT_TL1_LogicalAddr& theSlpfAddr)
{
    return GetControlPlaneSlpfSubApp().GetCopy(theSlpfAddr.GetLogical());
}

//--------------------------------------------------------------------------
SLA_ProfileConfig
TL1_SlpfEntity::GetControlPlaneSlpfConfig(uint16 theProfileId)
{
    return GetControlPlaneSlpfSubApp().GetCopy(theProfileId);
}

//--------------------------------------------------------------------------
void
TL1_SlpfEntity::PopulateRspBlk(SLA_ProfileConfig& theConfig, TL1_SlpfRspBlk&  rspBlk)
{
    string SlpfName( "SLPF" );
    rspBlk.SetEntityName( SlpfName );

    CT_TL1_LogicalAddr SlpfAddr ( (uint8)theConfig.GetProfileId() );
    rspBlk.SetSlpfAddr( SlpfAddr );

    rspBlk.SetProfileName ( theConfig.GetProfileName( ) );
    rspBlk.SetProtectionLevel( theConfig.GetProtectionLevel( ) );
    rspBlk.SetDiversity( theConfig.GetDiversity( ) );
    rspBlk.SetReversion( theConfig.GetReversion( ) );
    rspBlk.SetCoRouting( theConfig.GetCoRouting( ) );
    rspBlk.SetTransLineMSDCC ( theConfig.GetTransLineMsDcc( ) );
    rspBlk.SetTransSectionRSDCC( theConfig.GetTransSectionRsDcc( ) );
    rspBlk.SetTransOTUGCC0( theConfig.GetTransOtuGcc0( ) );
    rspBlk.SetTransODUGCC12( theConfig.GetTransOduGcc1_2( ) );
    rspBlk.SetWtr( theConfig.GetWtr( ) );
    rspBlk.SetCallSetupReroute( theConfig.GetCallSetupReroute( ) );
    rspBlk.SetMaxRerouteAttempts( theConfig.GetMaxRerouteAttempts( ) );
    rspBlk.SetBackoffInterval( theConfig.GetBackoffInterval( ) );
    rspBlk.SetBoundReroute( theConfig.GetBoundReroute( ) );
    rspBlk.SetEndToEndReroute( theConfig.GetEndToEndReroute( ) );
    rspBlk.SetLatency( theConfig.GetLatency( ) );
    rspBlk.SetResourceClass( theConfig.GetResourceClass( ) );
    rspBlk.SetPriority( theConfig.GetPriority() );
    rspBlk.SetReservationStyle( theConfig.GetResvStyle() );
    rspBlk.SetResConnA( theConfig.GetResConnA( ) );
    rspBlk.SetResConnB( theConfig.GetResConnB( ) );
    rspBlk.SetDiversityCheck( theConfig.GetDiversityCheck( ) );
    rspBlk.SetCpReversion( theConfig.GetCpReversion( ) );
    rspBlk.SetCpWtr( theConfig.GetCpWtr( ) );
}


//-----------------------------------------------------------------------------
int
TL1_SlpfEntity::GetSlpfNum(const CT_TL1_LogicalAddr& theAddr) const
{
    if ( 99 == (int)theAddr.GetLogical() )
        return 20;
    else
        return (int)theAddr.GetLogical() - 1;
}
//--------------------------------------------------------------------------
TL1_SlpolicyEntity::TL1_SlpolicyEntity()
{
}

//--------------------------------------------------------------------------
TL1_SlpolicyEntity::~TL1_SlpolicyEntity()
{
}

//--------------------------------------------------------------------------
AG7100_SlaPolicyIf&
TL1_SlpolicyEntity::GetControlPlaneSlpolicyIf( ) const
{
    return AG7100_AgentIf::GetInstance().GetControlPlaneIf( ).GetSlaPolicyIf( );
}

//--------------------------------------------------------------------------
SLA_PolicySubApplication&
TL1_SlpolicyEntity::GetControlPlaneSlpolicySubApp( ) const
{
    return GetControlPlaneSlpolicyIf( ).GetPolicySubApp( );
}

//--------------------------------------------------------------------------
SLA_PolicyRegion&
TL1_SlpolicyEntity::GetControlPlaneSlpolicyRegion( ) const
{
    return T7100_TL1RegionValidate( GetControlPlaneSlpolicySubApp( ).GetConfigRegion( ) );
}

//--------------------------------------------------------------------------
SLA_PolicyConfig
TL1_SlpolicyEntity::GetControlPlaneSlpolicyConfig(const CT_TL1_LogicalAddr& theSlpolicyAddr)
{
    return GetControlPlaneSlpolicySubApp().GetCopy(theSlpolicyAddr.GetLogical());
}

//--------------------------------------------------------------------------
void
TL1_SlpolicyEntity::PopulateRspBlk( SLA_PolicyConfig&    theConfig,
                                  TL1_SlpolicyRspBlk&  rspBlk )
{
    SLA_ProfileConfig aProfileConfig;

    string SlpolicyName ( "SLPOLICY" );
    rspBlk.SetEntityName( SlpolicyName );

    CT_TL1_LogicalAddr SlpolicyAddr ( (CT_TL1_LogicalId)theConfig.GetPolicyId() );
    rspBlk.SetSlpolicyAddr( SlpolicyAddr );

    rspBlk.SetPolicyName ( theConfig.GetPolicyName( ) );

    rspBlk.SetSvcLvlCodePt1( theConfig.GetCodePoint(1) );
    rspBlk.SetSvcLvlPfAid1( (CT_TL1_LogicalId)theConfig.GetProfileId(1) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(1) );
    rspBlk.SetSvcLvlPfName1( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt2( theConfig.GetCodePoint(2) );
    rspBlk.SetSvcLvlPfAid2( (CT_TL1_LogicalId)theConfig.GetProfileId(2) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(2) );
    rspBlk.SetSvcLvlPfName2( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt3( theConfig.GetCodePoint(3) );
    rspBlk.SetSvcLvlPfAid3( (CT_TL1_LogicalId)theConfig.GetProfileId(3) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(3) );
    rspBlk.SetSvcLvlPfName3( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt4( theConfig.GetCodePoint(4) );
    rspBlk.SetSvcLvlPfAid4( (CT_TL1_LogicalId)theConfig.GetProfileId(4) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(4) );
    rspBlk.SetSvcLvlPfName4( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt5( theConfig.GetCodePoint(5) );
    rspBlk.SetSvcLvlPfAid5( (CT_TL1_LogicalId)theConfig.GetProfileId(5) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(5) );
    rspBlk.SetSvcLvlPfName5( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt6( theConfig.GetCodePoint(6) );
    rspBlk.SetSvcLvlPfAid6( (CT_TL1_LogicalId)theConfig.GetProfileId(6) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(6) );
    rspBlk.SetSvcLvlPfName6( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt7( theConfig.GetCodePoint(7) );
    rspBlk.SetSvcLvlPfAid7( (CT_TL1_LogicalId)theConfig.GetProfileId(7) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(7) );
    rspBlk.SetSvcLvlPfName7( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt8( theConfig.GetCodePoint(8) );
    rspBlk.SetSvcLvlPfAid8( (CT_TL1_LogicalId)theConfig.GetProfileId(8) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(8) );
    rspBlk.SetSvcLvlPfName8( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt9( theConfig.GetCodePoint(9) );
    rspBlk.SetSvcLvlPfAid9( (CT_TL1_LogicalId)theConfig.GetProfileId(9) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(9) );
    rspBlk.SetSvcLvlPfName9( aProfileConfig.GetProfileName( ) );

    rspBlk.SetSvcLvlCodePt10( theConfig.GetCodePoint(10) );
    rspBlk.SetSvcLvlPfAid10( (CT_TL1_LogicalId)theConfig.GetProfileId(10) );
    aProfileConfig = TL1_SlpfEntity::GetControlPlaneSlpfConfig( theConfig.GetProfileId(10) );
    rspBlk.SetSvcLvlPfName10( aProfileConfig.GetProfileName( ) );

    // **** ToDo:
    //  Need to support resv_style
    //
}
