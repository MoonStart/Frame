/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Slpf Response Class
TARGET:
AUTHOR:         June 08, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive Service Level Profile Response 
                class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_SLPF_RESPONSE_BLOCK_H__
#define __TL1_SLPF_RESPONSE_BLOCK_H__

#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_SM_Types.h>
#include <Response/TL1_Response.h>

class TL1_SlpfRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_SlpfRspBlk( );
    
    TL1_SlpfRspBlk( const string*                  theEntityName,
                    const CT_TL1_LogicalAddr*      theAddr,
                    const string*                  theProfName,
                    const CT_SLPF_ProtLvl*         theProtectionLevel,
                    const CT_SLPF_Diversity*       theDiversity,
                    const CT_SLPF_Params*          theReversion,
                    const CT_SLPF_Params*          theCoRouting,
                    const CT_SLPF_Params*          theTransparentLineMSDCC,
                    const CT_SLPF_Params*          theTransparentSectionRSDCC,
                    const CT_SLPF_Params*          theTransparentOTUGCC0,
                    const CT_SLPF_Params*          theTrabsparentODUGCC12,
                    const int*                     theWaitTime,
                    const CT_SLPF_Params*          theCallSetupReroute,
                    const int*                     theMaxRerouteAttempts,
                    const int*                     theBackoffInterval,
                    const CT_SLPF_Params*          theBoundReroute,
                    const CT_SLPF_Params*          theEndToEndReroute,
                    const int*                     theLatency,
                    const uint32*                  theResourceClass,
                    const CT_SLPF_PRIORITY*        thePriority,
                    const CT_Resv_Style*           theReservationStyle,
                    const CT_Advertisement*        theResConnA,
                    const CT_Advertisement*        theResConnB,
                    const CT_Slpf_DiversityCheck*  theDiversityCheck,
                    const CT_Slpf_CpReversion*     theCpReversion,
                    const int*                     theCpWaitTime );
     
    TL1_SlpfRspBlk(const TL1_SlpfRspBlk& );
    
    virtual ~TL1_SlpfRspBlk();

    TL1_SlpfRspBlk& operator=( const TL1_SlpfRspBlk& t1Blk );

    bool operator==( const TL1_SlpfRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetSlpfAddr( CT_TL1_LogicalAddr& theAddr ) const;
    bool GetProfileName( string& theProfName ) const;
    bool GetProtectionLevel( CT_SLPF_ProtLvl& theProtLevel ) const;
    bool GetDiversity( CT_SLPF_Diversity& theDiversity ) const;
    bool GetReversion( CT_SLPF_Params& theReversion ) const;
    bool GetCoRouting( CT_SLPF_Params& theCoRouting ) const;
    bool GetTransLineMSDCC( CT_SLPF_Params& theTransLineMSDCC ) const;
    bool GetTransSectionRSDCC( CT_SLPF_Params& theTransSectionRSDCC ) const;
    bool GetTransOTUGCC0( CT_SLPF_Params& theTransOTUGCC0 ) const;
    bool GetTransODUGCC12( CT_SLPF_Params& theTransODUGCC12 ) const;
    bool GetWtr( int& theWaitTime ) const;
    bool GetCallSetupReroute( CT_SLPF_Params& theCallSetupReroute ) const;
    bool GetMaxRerouteAttempts( int& theMaxRerouteAttempts ) const;
    bool GetBackoffInterval( int& theBackoffInterval ) const;
    bool GetBoundReroute( CT_SLPF_Params& theBoundReroute ) const;
    bool GetEndToEndReroute( CT_SLPF_Params& theEndToEndReroute ) const;
    bool GetLatency( int& theLatency ) const;
    bool GetResourceClass( CT_ControlPlane_Addr& CT_ControlPlane_Addr ) const;
    bool GetPriority( CT_SLPF_PRIORITY& thePriority ) const;
    bool GetReservationStyle( CT_Resv_Style& theReservationStyle ) const;
    bool GetResConnA( CT_Advertisement& theResConnA ) const;
    bool GetResConnB( CT_Advertisement& theResConnB ) const;
    bool GetDiversityCheck( CT_Slpf_DiversityCheck& theDiversityCheck ) const;
    bool GetCpReversion( CT_Slpf_CpReversion& theCpReversion ) const;
    bool GetCpWtr( int& theCpWaitTime ) const;

    void SetEntityName( string& theEntityName );
    void SetSlpfAddr( const CT_TL1_LogicalAddr& theAddr );
    void SetProfileName( const string& theProfName );
    void SetProtectionLevel( const CT_SLPF_ProtLvl& theProtLevel );
    void SetDiversity( const CT_SLPF_Diversity& theDiversity );
    void SetReversion( const CT_SLPF_Params& theReversion );
    void SetCoRouting( const CT_SLPF_Params& theCoRouting );
    void SetTransLineMSDCC( const CT_SLPF_Params& theTransLineMSDCC );
    void SetTransSectionRSDCC( const CT_SLPF_Params& theTransSectionRSDCC );
    void SetTransOTUGCC0( const CT_SLPF_Params& theTransOTUGCC0 );
    void SetTransODUGCC12( const CT_SLPF_Params& theTransODUGCC12 );
    void SetWtr( const int& theWaitTime );
    void SetCallSetupReroute( const CT_SLPF_Params& theCallSetupReroute );
    void SetMaxRerouteAttempts( const int& theMaxRerouteAttempts );
    void SetBackoffInterval( const int& theBackoffInterval );
    void SetBoundReroute( const CT_SLPF_Params& theBoundReroute );
    void SetEndToEndReroute( const CT_SLPF_Params& theEndToEndReroute );
    void SetLatency( const int& theLatency );
    void SetResourceClass( const CT_ControlPlane_Addr& theResourceClass );
    void SetPriority( const CT_SLPF_PRIORITY& thePriority );
    void SetReservationStyle( const CT_Resv_Style& theReservationStyle );
    void SetResConnA( const CT_Advertisement& theResConnA );
    void SetResConnB( const CT_Advertisement& theResConnB );
    void SetDiversityCheck( const CT_Slpf_DiversityCheck& theDiversityCheck );
    void SetCpReversion( const CT_Slpf_CpReversion& theCpReversion );
    void SetCpWtr( const int& theCpWaitTime );

private:

    enum 
    {
        INDEX_EntityName = 0,
        INDEX_SlpfAddr,    
        INDEX_ProfileName,
        INDEX_ProtectionLevel,
        INDEX_Diversity,    
        INDEX_Reversion,    
        INDEX_CoRouting,
        INDEX_TransparentLineMSDCC,
        INDEX_TransparentSectionRSDCC,    
        INDEX_TransparentOTUGCC0,
        INDEX_TransparentODUGCC12,
        INDEX_WaitTime,
        INDEX_CallSetupReroute,
        INDEX_MaxRerouteAttempts,
        INDEX_BackoffInterval,
        INDEX_BoundReroute,
        INDEX_EndToEndReroute,
        INDEX_Latency,
        INDEX_ResourceClass,
        INDEX_Priority,
        INDEX_ReservationStyle,
        INDEX_ResConnA,
        INDEX_ResConnB,
        INDEX_CpReversion,
        INDEX_DiversityCheck,
        INDEX_CpWaitTime,
        INDEX_END
    };

    vector<bool>            myBitSet;

    string                  myEntityName;
    CT_TL1_LogicalAddr      myAddr;
    string                  myProfileName;
    CT_SLPF_ProtLvl         myProtectionLevel;
    CT_SLPF_Diversity       myDiversity;
    CT_SLPF_Params          myReversion; 
    CT_SLPF_Params          myCoRouting;
    CT_SLPF_Params          myTransparentLineMSDCC;
    CT_SLPF_Params          myTransparentSectionRSDCC; 
    CT_SLPF_Params          myTransparentOTUGCC0;
    CT_SLPF_Params          myTransparentODUGCC12; 
    int                     myWaitTime;
    CT_SLPF_Params          myCallSetupReroute;
    int                     myMaxRerouteAttempts;
    int                     myBackoffInterval;
    CT_SLPF_Params          myBoundReroute;
    CT_SLPF_Params          myEndToEndReroute;
    int                     myLatency;
    CT_ControlPlane_Addr    myResourceClass;
    CT_SLPF_PRIORITY        myPriority;
    CT_Resv_Style           myReservationStyle;
    CT_Advertisement        myResConnA;
    CT_Advertisement        myResConnB;
    CT_Slpf_DiversityCheck  myDiversityCheck;
    CT_Slpf_CpReversion     myCpReversion;
    int	                    myCpWaitTime;
};

typedef TL1_Rtv_Response< TL1_SlpfRspBlk > TL1_SlpfResponse;

class TL1_SlpolicyRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_SlpolicyRspBlk( );
    
    TL1_SlpolicyRspBlk( const string*                  theEntityName,
                        const CT_TL1_LogicalAddr*      theAddr,
                        const string*                  thePolicyName,
                        const int16*                    theSvcLvlCodePt1,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid1,
                        const string*                  theSvcLvlPfName1,
                        const int16*                    theSvcLvlCodePt2,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid2,
                        const string*                  theSvcLvlPfName2,
                        const int16*                    theSvcLvlCodePt3,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid3,
                        const string*                  theSvcLvlPfName3,
                        const int16*                    theSvcLvlCodePt4,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid4,
                        const string*                  theSvcLvlPfName4,
                        const int16*                    theSvcLvlCodePt5,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid5,
                        const string*                  theSvcLvlPfName5,
                        const int16*                    theSvcLvlCodePt6,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid6,
                        const string*                  theSvcLvlPfName6,
                        const int16*                    theSvcLvlCodePt7,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid7,
                        const string*                  theSvcLvlPfName7,
                        const int16*                    theSvcLvlCodePt8,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid8,
                        const string*                  theSvcLvlPfName8,
                        const int16*                    theSvcLvlCodePt9,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid9,
                        const string*                  theSvcLvlPfName9,
                        const int16*                    theSvcLvlCodePt10,
                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid10,
                        const string*                  theSvcLvlPfName10);
     
    TL1_SlpolicyRspBlk(const TL1_SlpolicyRspBlk& );
    
    virtual ~TL1_SlpolicyRspBlk();

    TL1_SlpolicyRspBlk& operator=( const TL1_SlpolicyRspBlk& t1Blk );

    bool operator==( const TL1_SlpolicyRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetSlpolicyAddr( CT_TL1_LogicalAddr& theAddr ) const;
    bool GetPolicyName( string& thePolicyName ) const;
    bool GetSvcLvlCodePt1( int16& theSvcLvlCodePt1 ) const;
    bool GetSvcLvlPfAid1( CT_TL1_LogicalAddr& theSvcLvlPfAid1 ) const;
    bool GetSvcLvlPfName1( string& theSvcLvlPfName1 ) const;
    bool GetSvcLvlCodePt2( int16& theSvcLvlCodePt2 ) const;
    bool GetSvcLvlPfAid2( CT_TL1_LogicalAddr& theSvcLvlPfAid2 ) const;
    bool GetSvcLvlPfName2( string& theSvcLvlPfName2 ) const;
    bool GetSvcLvlCodePt3( int16& theSvcLvlCodePt3 ) const;
    bool GetSvcLvlPfAid3( CT_TL1_LogicalAddr& theSvcLvlPfAid3 ) const;
    bool GetSvcLvlPfName3( string& theSvcLvlPfName3 ) const;
    bool GetSvcLvlCodePt4( int16& theSvcLvlCodePt4 ) const;
    bool GetSvcLvlPfAid4( CT_TL1_LogicalAddr& theSvcLvlPfAid4 ) const;
    bool GetSvcLvlPfName4( string& theSvcLvlPfName4 ) const;
    bool GetSvcLvlCodePt5( int16& theSvcLvlCodePt5 ) const;
    bool GetSvcLvlPfAid5( CT_TL1_LogicalAddr& theSvcLvlPfAid5 ) const;
    bool GetSvcLvlPfName5( string& theSvcLvlPfName5 ) const;
    bool GetSvcLvlCodePt6( int16& theSvcLvlCodePt6 ) const;
    bool GetSvcLvlPfAid6( CT_TL1_LogicalAddr& theSvcLvlPfAid6 ) const;
    bool GetSvcLvlPfName6( string& theSvcLvlPfName6 ) const;
    bool GetSvcLvlCodePt7( int16& theSvcLvlCodePt7 ) const;
    bool GetSvcLvlPfAid7( CT_TL1_LogicalAddr& theSvcLvlPfAid7 ) const;
    bool GetSvcLvlPfName7( string& theSvcLvlPfName7 ) const;
    bool GetSvcLvlCodePt8( int16& theSvcLvlCodePt8 ) const;
    bool GetSvcLvlPfAid8( CT_TL1_LogicalAddr& theSvcLvlPfAid8 ) const;
    bool GetSvcLvlPfName8( string& theSvcLvlPfName8 ) const;
    bool GetSvcLvlCodePt9( int16& theSvcLvlCodePt9 ) const;
    bool GetSvcLvlPfAid9( CT_TL1_LogicalAddr& theSvcLvlPfAid9 ) const;
    bool GetSvcLvlPfName9( string& theSvcLvlPfName9 ) const;
    bool GetSvcLvlCodePt10( int16& theSvcLvlCodePt10 ) const;
    bool GetSvcLvlPfAid10( CT_TL1_LogicalAddr& theSvcLvlPfAid10 ) const;
    bool GetSvcLvlPfName10( string& theSvcLvlPfName10 ) const;


    void SetEntityName( string& theEntityName );
    void SetSlpolicyAddr( const CT_TL1_LogicalAddr& theAddr );
    void SetPolicyName( const string& thePolicyName );
    void SetSvcLvlCodePt1( const int16& theSvcLvlCodePt1 );
    void SetSvcLvlPfAid1( const CT_TL1_LogicalAddr& theSvcLvlPfAid1 );
    void SetSvcLvlPfName1( const string& theSvcLvlPfName1 );
    void SetSvcLvlCodePt2( const int16& theSvcLvlCodePt2 );
    void SetSvcLvlPfAid2( const CT_TL1_LogicalAddr& theSvcLvlPfAid2 );
    void SetSvcLvlPfName2( const string& theSvcLvlPfName2 );
    void SetSvcLvlCodePt3( const int16& theSvcLvlCodePt3 );
    void SetSvcLvlPfAid3( const CT_TL1_LogicalAddr& theSvcLvlPfAid3 );
    void SetSvcLvlPfName3( const string& theSvcLvlPfName3 );
    void SetSvcLvlCodePt4( const int16& theSvcLvlCodePt4 );
    void SetSvcLvlPfAid4( const CT_TL1_LogicalAddr& theSvcLvlPfAid4 );
    void SetSvcLvlPfName4( const string& theSvcLvlPfName4 );
    void SetSvcLvlCodePt5( const int16& theSvcLvlCodePt5 );
    void SetSvcLvlPfAid5( const CT_TL1_LogicalAddr& theSvcLvlPfAid5 );
    void SetSvcLvlPfName5( const string& theSvcLvlPfName5 );
    void SetSvcLvlCodePt6( const int16& theSvcLvlCodePt6 );
    void SetSvcLvlPfAid6( const CT_TL1_LogicalAddr& theSvcLvlPfAid6 );
    void SetSvcLvlPfName6( const string& theSvcLvlPfName6 );
    void SetSvcLvlCodePt7( const int16& theSvcLvlCodePt7 );
    void SetSvcLvlPfAid7( const CT_TL1_LogicalAddr& theSvcLvlPfAid7 );
    void SetSvcLvlPfName7( const string& theSvcLvlPfName2 );
    void SetSvcLvlCodePt8( const int16& theSvcLvlCodePt8 );
    void SetSvcLvlPfAid8( const CT_TL1_LogicalAddr& theSvcLvlPfAid8);
    void SetSvcLvlPfName8 ( const string& theSvcLvlPfName8);
    void SetSvcLvlCodePt9( const int16& theSvcLvlCodePt9 );
    void SetSvcLvlPfAid9( const CT_TL1_LogicalAddr& theSvcLvlPfAid9 );
    void SetSvcLvlPfName9( const string& theSvcLvlPfName9 );
    void SetSvcLvlCodePt10( const int16& theSvcLvlCodePt10 );
    void SetSvcLvlPfAid10( const CT_TL1_LogicalAddr& theSvcLvlPfAid10 );
    void SetSvcLvlPfName10( const string& theSvcLvlPfName10 );


private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_SlpolicyAddr,    
        INDEX_PolicyName,
        INDEX_SvcLvlCodePt1,
        INDEX_SvcLvlPfAid1,    
        INDEX_SvcLvlPfName1,    
        INDEX_SvcLvlCodePt2,
        INDEX_SvcLvlPfAid2,    
        INDEX_SvcLvlPfName2,    
        INDEX_SvcLvlCodePt3,
        INDEX_SvcLvlPfAid3,    
        INDEX_SvcLvlPfName3,    
        INDEX_SvcLvlCodePt4,
        INDEX_SvcLvlPfAid4,    
        INDEX_SvcLvlPfName4,    
        INDEX_SvcLvlCodePt5,
        INDEX_SvcLvlPfAid5,    
        INDEX_SvcLvlPfName5,    
        INDEX_SvcLvlCodePt6,
        INDEX_SvcLvlPfAid6,    
        INDEX_SvcLvlPfName6,    
        INDEX_SvcLvlCodePt7,
        INDEX_SvcLvlPfAid7,    
        INDEX_SvcLvlPfName7,    
        INDEX_SvcLvlCodePt8,
        INDEX_SvcLvlPfAid8,    
        INDEX_SvcLvlPfName8,    
        INDEX_SvcLvlCodePt9,
        INDEX_SvcLvlPfAid9,    
        INDEX_SvcLvlPfName9,    
        INDEX_SvcLvlCodePt10,
        INDEX_SvcLvlPfAid10,    
        INDEX_SvcLvlPfName10,    
        INDEX_END
    };

    vector<bool>                 myBitSet;

    string                       myEntityName;
    CT_TL1_LogicalAddr           myAddr;
    string                       myPolicyName;
    int16                        mySvcLvlCodePt1;
    CT_TL1_LogicalAddr           mySvcLvlPfAid1;
    string                       mySvcLvlPfName1; 
    int16                        mySvcLvlCodePt2;
    CT_TL1_LogicalAddr           mySvcLvlPfAid2;
    string                       mySvcLvlPfName2; 
    int16                        mySvcLvlCodePt3;
    CT_TL1_LogicalAddr           mySvcLvlPfAid3;
    string                       mySvcLvlPfName3; 
    int16                        mySvcLvlCodePt4;
    CT_TL1_LogicalAddr           mySvcLvlPfAid4;
    string                       mySvcLvlPfName4; 
    int16                        mySvcLvlCodePt5;
    CT_TL1_LogicalAddr           mySvcLvlPfAid5;
    string                       mySvcLvlPfName5;
    int16                        mySvcLvlCodePt6;
    CT_TL1_LogicalAddr           mySvcLvlPfAid6;
    string                       mySvcLvlPfName6; 
    int16                        mySvcLvlCodePt7;
    CT_TL1_LogicalAddr           mySvcLvlPfAid7;
    string                       mySvcLvlPfName7; 
    int16                        mySvcLvlCodePt8;
    CT_TL1_LogicalAddr           mySvcLvlPfAid8;
    string                       mySvcLvlPfName8; 
    int16                        mySvcLvlCodePt9;
    CT_TL1_LogicalAddr           mySvcLvlPfAid9;
    string                       mySvcLvlPfName9; 
    int16                        mySvcLvlCodePt10;
    CT_TL1_LogicalAddr           mySvcLvlPfAid10;
    string                       mySvcLvlPfName10; 

};

typedef TL1_Rtv_Response< TL1_SlpolicyRspBlk > TL1_SlpolicyResponse;

#endif  // #ifndef __TL1_SLPF_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
