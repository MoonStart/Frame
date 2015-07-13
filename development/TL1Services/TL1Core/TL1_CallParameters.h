/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 07, 2007 - Tong Wu
DESCRIPTION:    Header file for CALL TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CALLPARAMETERS_H__
#define __TL1_CALLPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_CALLRSPBLK_H__
#include <Response/TL1_CallRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

#ifndef __TL1_CONTROLPLANEFAL_H__
#include <TL1Core/TL1_ControlPlaneFal.h>
#endif


//-----------------------------------------------------------------------------
class TL1_CallEntParameters : public TL1_ControlPlaneFal
{
public:
    
    TL1_CallEntParameters();

    virtual ~TL1_CallEntParameters();

    TL1_CallEntParameters(const TL1_CallEntParameters& theInst );

    TL1_CallEntParameters& operator=( const TL1_CallEntParameters& theInst );

    bool operator==( const TL1_CallEntParameters& theInst ) const;

    inline LT_Handle*                   GetHandle( ) const;
    inline void                         SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                      GetCtag( ) const;
    inline void                         SetCtag( LT_Ctag theCtag );

    inline CT_ControlPlane_TNA*         GetAEnd( ) const;
    inline void                         SetAEnd( CT_ControlPlane_TNA* theAEnd ); 

    inline CT_ControlPlane_TNA*         GetZEnd( ) const;
    inline void                         SetZEnd( CT_ControlPlane_TNA* theZEnd );

    inline CT_TL1_NodeAddr*             GetNodeAddr( ) const;
    inline void                         SetNodeAddr( CT_TL1_NodeAddr* theNodeAddr );

    inline CT_ControlPlane_TNA*         GetAEnd2( ) const;
    inline void                         SetAEnd2( CT_ControlPlane_TNA* theAEnd2 ); 

    inline CT_ControlPlane_TNA*         GetZEnd2( ) const;
    inline void                         SetZEnd2( CT_ControlPlane_TNA* theZEnd2 );

    inline uint32*                      GetNodeId2( ) const;
    inline void                         SetNodeId2( uint32* theNodeId2 );
    
    inline CT_Call_SignalType*          GetSignalType( ) const;
    inline void                         SetSignalType( CT_Call_SignalType* theSignalType );

    inline uint8*                       GetMultiplierValue( ) const;
    inline void                         SetMultiplierValue( uint8* theMultiplierValue );

    inline CT_ControlPlane_LabelSet*    GetIngrss( ) const;
    inline void                         SetIngrss( CT_ControlPlane_LabelSet* theIngrss );

    inline CT_ControlPlane_LabelSet*    GetEgrss( ) const;
    inline void                         SetEgrss( CT_ControlPlane_LabelSet* theEgrss );

    inline CT_ControlPlane_LabelSet*    GetIngrss2( ) const;
    inline void                         SetIngrss2( CT_ControlPlane_LabelSet* theIngrss2 );

    inline CT_ControlPlane_LabelSet*    GetEgrss2( ) const;
    inline void                         SetEgrss2( CT_ControlPlane_LabelSet* theEgrss2 );
    
    inline CT_Call_Directionality*      GetDirection( ) const;
    inline void                         SetDirection( CT_Call_Directionality* theDirection );

    inline CT_ControlPlane_Srlg*        GetSrlg( ) const;
    inline void                         SetSrlg( CT_ControlPlane_Srlg* theSrlg );

    inline uint16*                      GetTimeout( ) const;
    inline void                         SetTimeout( uint16* theTimeout );

    inline CT_ControlPlane_CallId*      GetCallId( ) const;
    inline void                         SetCallId( CT_ControlPlane_CallId* theCallId );

    inline string*                      GetCallName() const;
    inline void                         SetCallName(string* theCallName);

    inline CT_Call_Oper_State*          GetCallOperState( ) const;
    inline void                         SetCallOperState( CT_Call_Oper_State* theCallOperState );

    inline CT_Call_Status*              GetCallStatus( ) const;
    inline void                         SetCallStatus( CT_Call_Status* theCallStatus );

    inline CT_TL1_LogicalAddr*          GetSlpf( ) const;
    inline void                         SetSlpf( CT_TL1_LogicalAddr* theSlpf );

    inline CT_SLPF_ProtLvl*             GetProtLvl( ) const;
    inline void                         SetProtLvl( CT_SLPF_ProtLvl* theProtLvl );

    inline CT_TL1_ExppathAddr*          GetWorkingPath( ) const;
    inline void                         SetWorkingPath( CT_TL1_ExppathAddr* thePath );          

    inline CT_TL1_ExppathAddr*          GetProtectPath( ) const;
    inline void                         SetProtectPath( CT_TL1_ExppathAddr* thePath );          

    inline CT_TL1_LabelSetAddr*         GetLabelSet( ) const;
    inline void                         SetLabelSet( CT_TL1_LabelSetAddr* theAddr );

    inline CT_SLPF_PRIORITY*            GetPriority( ) const;
    inline void                         SetPriority( CT_SLPF_PRIORITY *thePriority );

    inline CT_Call_Location*            GetLocation( ) const;
    inline void                         SetLocation( CT_Call_Location* theLoc );

    CT_TL1_ExppathAddr*          GetWkgPrp1( ) const;
    void                         SetWkgPrp1(CT_TL1_ExppathAddr* theWkgPrp1);

    CT_TL1_ExppathAddr*          GetWkgPrp2( ) const;
    void                         SetWkgPrp2(CT_TL1_ExppathAddr* theWkgPrp2);
    
    CT_TL1_ExppathAddr*          GetProtPrp1( ) const;
    void                         SetProtPrp1(CT_TL1_ExppathAddr* theProtPrp1);

    CT_TL1_ExppathAddr*          GetProtPrp2( ) const;
    void                         SetProtPrp2(CT_TL1_ExppathAddr* theProtPrp2);
    
    bool*                        GetCompWkgPrp1( ) const;
    void                         SetCompWkgPrp1(bool* theCompWkgPrp1);
    
    bool*                        GetCompProtPrp1( ) const;
    void                         SetCompProtPrp1(bool* theCompProtPrp1);

    CT_TL1_CallNumber*           GetCallNumber( ) const;
    void                         SetCallNumber(CT_TL1_CallNumber * theCallNumber);

    CT_TEL_daHz*                 GetExpRate( ) const;
    void                         SetExpRate(CT_TEL_daHz* theExpRate);

    uint8*                       GetGfpTs( ) const;
    void                         SetGfpTs(uint8* theGfpTs);

    CT_TL1_ExdpathAddr*          GetWkgXPath( ) const;
    void                         SetWkgXPath(CT_TL1_ExdpathAddr* theWkgXPath);

    CT_TL1_ExdpathAddr*          GetProtXPath( ) const;
    void                         SetProtXPath(CT_TL1_ExdpathAddr* theProtXPath);

    CT_CallRetainPath*           GetCallRetainPath( ) const;
    void                         SetCallRetainPath(CT_CallRetainPath* theCallRetainPath);

private:

    LT_Handle*                  myHandle;
    LT_Ctag                     myCtag;
    CT_ControlPlane_TNA*        myAEnd;
    CT_ControlPlane_TNA*        myZEnd;
    CT_TL1_NodeAddr*            myNodeAddr;
    CT_ControlPlane_TNA*        myAEnd2;
    CT_ControlPlane_TNA*        myZEnd2;
    uint32*                     myNodeId2;
    CT_Call_SignalType*         mySignalType;
    uint8*                      myMultiplier;
    CT_ControlPlane_LabelSet*   myIngrss;
    CT_ControlPlane_LabelSet*   myEgrss;
    CT_ControlPlane_LabelSet*   myIngrss2;
    CT_ControlPlane_LabelSet*   myEgrss2;
    CT_Call_Directionality*     myDirection;
    CT_ControlPlane_Srlg*       mySrlg;
    uint16*                     myTimeout;
    CT_ControlPlane_CallId*     myCallId;
    string*                     myCallName;
    CT_Call_Oper_State*         myCallOperState;
    CT_Call_Status*             myCallStatus;
    CT_TL1_LogicalAddr*         mySlpf;
    CT_SLPF_ProtLvl*            myProtLvl;
    CT_TL1_ExppathAddr*         myWorkingPath;
    CT_TL1_ExppathAddr*         myProtectPath;
    CT_TL1_LabelSetAddr*        myLabelSet;
    CT_SLPF_PRIORITY*           myPriority;
    CT_Call_Location*           myLocation;
    CT_TL1_ExppathAddr*         myWkgPrp1;
    CT_TL1_ExppathAddr*         myWkgPrp2;
    CT_TL1_ExppathAddr*         myProtPrp1;
    CT_TL1_ExppathAddr*         myProtPrp2;
    bool*                       myCompWkgPrp1;
    bool*                       myCompProtPrp1;
    CT_TL1_CallNumber*          myCallNumber;
    CT_TEL_daHz*                myExpRate;
    uint8*                      myGfpTs;
    CT_TL1_ExdpathAddr*         myWkgXPath;
    CT_TL1_ExdpathAddr*         myProtXPath;
    CT_CallRetainPath*          myCallRetainPath;
};

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_CallEntParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_CallEntParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_CallEntParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_CallEntParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallEntParameters::GetAEnd( ) const
{
    return myAEnd;
}

inline void                         
TL1_CallEntParameters::SetAEnd( CT_ControlPlane_TNA* theAEnd ) 
{
    myAEnd = theAEnd;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallEntParameters::GetZEnd( ) const
{
    return myZEnd;
}

inline void                         
TL1_CallEntParameters::SetZEnd( CT_ControlPlane_TNA* theZEnd ) 
{
    myZEnd = theZEnd;
}

//--------------------------------------------------------------------------------
inline CT_TL1_NodeAddr*    
TL1_CallEntParameters::GetNodeAddr( ) const
{
    return myNodeAddr;
}

inline void                         
TL1_CallEntParameters::SetNodeAddr( CT_TL1_NodeAddr* theNodeAddr )
{
    myNodeAddr = theNodeAddr;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallEntParameters::GetAEnd2( ) const
{
    return myAEnd2;
}

inline void                         
TL1_CallEntParameters::SetAEnd2( CT_ControlPlane_TNA* theAEnd2 ) 
{
    myAEnd2 = theAEnd2;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallEntParameters::GetZEnd2( ) const
{
    return myZEnd2;
}

inline void                         
TL1_CallEntParameters::SetZEnd2( CT_ControlPlane_TNA* theZEnd2 ) 
{
    myZEnd2 = theZEnd2;
}

//--------------------------------------------------------------------------------
inline uint32*    
TL1_CallEntParameters::GetNodeId2( ) const
{
    return myNodeId2;
}

inline void                         
TL1_CallEntParameters::SetNodeId2( uint32* theNodeId2 )
{
    myNodeId2 = theNodeId2;
}

//--------------------------------------------------------------------------------
inline CT_Call_SignalType*    
TL1_CallEntParameters::GetSignalType( ) const
{
    return mySignalType;
}


inline void              
TL1_CallEntParameters::SetSignalType( CT_Call_SignalType* theSignalType )
{
    mySignalType = theSignalType;
}
//--------------------------------------------------------------------------------
inline uint8*                  
TL1_CallEntParameters::GetMultiplierValue( ) const
{
    return myMultiplier;
}

inline void                         
TL1_CallEntParameters::SetMultiplierValue( uint8* theMultiplierValue )
{
    myMultiplier = theMultiplierValue;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*                     
TL1_CallEntParameters::GetIngrss( ) const
{
    return myIngrss;
}

inline void                         
TL1_CallEntParameters::SetIngrss( CT_ControlPlane_LabelSet* theIngrss )
{
    myIngrss = theIngrss;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*    
TL1_CallEntParameters::GetEgrss( ) const
{
    return myEgrss;
}


inline void              
TL1_CallEntParameters::SetEgrss( CT_ControlPlane_LabelSet* theEgrss )
{
    myEgrss = theEgrss;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*                     
TL1_CallEntParameters::GetIngrss2( ) const
{
    return myIngrss2;
}

inline void                         
TL1_CallEntParameters::SetIngrss2( CT_ControlPlane_LabelSet* theIngrss2 )
{
    myIngrss2 = theIngrss2;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*    
TL1_CallEntParameters::GetEgrss2( ) const
{
    return myEgrss2;
}


inline void              
TL1_CallEntParameters::SetEgrss2( CT_ControlPlane_LabelSet* theEgrss2 )
{
    myEgrss2 = theEgrss2;
}

//--------------------------------------------------------------------------------
inline CT_Call_Directionality*                     
TL1_CallEntParameters::GetDirection( ) const
{
    return myDirection;
}

inline void                         
TL1_CallEntParameters::SetDirection( CT_Call_Directionality* theDirection )
{
    myDirection = theDirection;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Srlg*    
TL1_CallEntParameters::GetSrlg( ) const
{
    return mySrlg;
}


inline void              
TL1_CallEntParameters::SetSrlg( CT_ControlPlane_Srlg* theSrlg )
{
    mySrlg = theSrlg;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_CallEntParameters::GetTimeout( ) const
{
    return myTimeout;
}

inline void                         
TL1_CallEntParameters::SetTimeout( uint16* theTimeout )
{
    myTimeout = theTimeout;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_CallId*    
TL1_CallEntParameters::GetCallId( ) const
{
    return myCallId;
}

inline void              
TL1_CallEntParameters::SetCallId( CT_ControlPlane_CallId* theCallId )
{
    myCallId = theCallId;
}

//--------------------------------------------------------------------------------
inline string*    
TL1_CallEntParameters::GetCallName( ) const
{
    return myCallName;
}

inline void              
TL1_CallEntParameters::SetCallName( string* theCallName )
{
    myCallName = theCallName;
}


//--------------------------------------------------------------------------------
inline CT_Call_Oper_State*               
TL1_CallEntParameters::GetCallOperState( ) const
{
    return myCallOperState;
}

inline void                         
TL1_CallEntParameters::SetCallOperState( CT_Call_Oper_State* theCallOperState )
{
    myCallOperState = theCallOperState;
}


//--------------------------------------------------------------------------------
inline CT_Call_Status*               
TL1_CallEntParameters::GetCallStatus( ) const
{
    return myCallStatus;
}

inline void                         
TL1_CallEntParameters::SetCallStatus( CT_Call_Status* theCallStatus )
{
    myCallStatus = theCallStatus;
}


//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*          
TL1_CallEntParameters::GetSlpf( ) const
{ 
    return mySlpf;
}

inline void                         
TL1_CallEntParameters::SetSlpf( CT_TL1_LogicalAddr* theSlpf )
{
    mySlpf = theSlpf;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_ProtLvl*             
TL1_CallEntParameters::GetProtLvl( ) const
{
    return myProtLvl;
}

inline void                         
TL1_CallEntParameters::SetProtLvl( CT_SLPF_ProtLvl* theProtLvl )
{
    myProtLvl = theProtLvl;
}

//--------------------------------------------------------------------------------
inline CT_TL1_ExppathAddr*                      
TL1_CallEntParameters::GetWorkingPath( ) const
{
    return myWorkingPath;
}

inline void                         
TL1_CallEntParameters::SetWorkingPath( CT_TL1_ExppathAddr* thePath )
{
    myWorkingPath = thePath;
}

//--------------------------------------------------------------------------------
inline CT_TL1_ExppathAddr*                      
TL1_CallEntParameters::GetProtectPath( ) const
{
    return myProtectPath;
}

inline void                         
TL1_CallEntParameters::SetProtectPath( CT_TL1_ExppathAddr* thePath )
{
    myProtectPath = thePath;
}

//--------------------------------------------------------------------------------
inline CT_Call_Location*             
TL1_CallEntParameters::GetLocation( ) const
{
    return myLocation;
}

inline void                         
TL1_CallEntParameters::SetLocation( CT_Call_Location* theLoc )
{
    myLocation = theLoc;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LabelSetAddr*                      
TL1_CallEntParameters::GetLabelSet( ) const
{
    return myLabelSet;
}

inline void                         
TL1_CallEntParameters::SetLabelSet( CT_TL1_LabelSetAddr* theAddr )
{
    myLabelSet = theAddr;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_PRIORITY*
TL1_CallEntParameters::GetPriority( ) const
{
    return myPriority;
}

inline void
TL1_CallEntParameters::SetPriority( CT_SLPF_PRIORITY* thePriority )
{
   myPriority = thePriority;
}

//--------------------------------------------------------------------------------
inline CT_TEL_daHz*
TL1_CallEntParameters::GetExpRate( ) const
{
    return myExpRate;
}

inline void
TL1_CallEntParameters::SetExpRate( CT_TEL_daHz* theExpRate )
{
   myExpRate = theExpRate;
}

//--------------------------------------------------------------------------------
inline uint8*
TL1_CallEntParameters::GetGfpTs( ) const
{
    return myGfpTs;
}

inline void
TL1_CallEntParameters::SetGfpTs( uint8* theGfpTs )
{
   myGfpTs = theGfpTs;
}

//--------------------------------------------------------------------------------
inline CT_TL1_ExdpathAddr*                      
TL1_CallEntParameters::GetWkgXPath( ) const
{
    return myWkgXPath;
}

inline void                         
TL1_CallEntParameters::SetWkgXPath( CT_TL1_ExdpathAddr* theWkgXPath )
{
    myWkgXPath = theWkgXPath;
}

//--------------------------------------------------------------------------------
inline CT_TL1_ExdpathAddr*                      
TL1_CallEntParameters::GetProtXPath( ) const
{
    return myProtXPath;
}

inline void                         
TL1_CallEntParameters::SetProtXPath( CT_TL1_ExdpathAddr* theProtXPath )
{
    myProtXPath = theProtXPath;
}

//--------------------------------------------------------------------------------
inline CT_CallRetainPath*                      
TL1_CallEntParameters::GetCallRetainPath( ) const
{
    return myCallRetainPath;
}

inline void                         
TL1_CallEntParameters::SetCallRetainPath( CT_CallRetainPath* theCallRetainPath )
{
    myCallRetainPath = theCallRetainPath;
}

//-----------------------------------------------------------------------------
// RTRV-CALL Parameters
class TL1_CallRtrvParameters
{
public:
    
    TL1_CallRtrvParameters();

    virtual ~TL1_CallRtrvParameters();

    TL1_CallRtrvParameters( const TL1_CallRtrvParameters& theInst );

    TL1_CallRtrvParameters& operator=( const TL1_CallRtrvParameters& theInst );

    bool operator==( const TL1_CallRtrvParameters& theInst ) const;

    inline LT_Handle*                   GetHandle( ) const;
    inline void                         SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                      GetCtag( ) const;
    inline void                         SetCtag( LT_Ctag theCtag );

    inline CT_TL1_CallAddr*             GetCallAddr( ) const;
    inline void                         SetCallAddr( CT_TL1_CallAddr* theCallAddr );

    inline CT_ControlPlane_CallId*      GetCallId( ) const;
    inline void                         SetCallId( CT_ControlPlane_CallId* theCallId );

    inline CT_TL1_LogicalAddr*          GetSlpf( ) const;
    inline void                         SetSlpf( CT_TL1_LogicalAddr* theSlpf );

    inline CT_ControlPlane_TNA*         GetAEnd( ) const;
    inline void                         SetAEnd( CT_ControlPlane_TNA* theAEnd ); 

    inline CT_ControlPlane_TNA*         GetZEnd( ) const;
    inline void                         SetZEnd( CT_ControlPlane_TNA* theZEnd );

    inline CT_ControlPlane_LabelSet*    GetIngrss( ) const;
    inline void                         SetIngrss( CT_ControlPlane_LabelSet* theIngrss );

    inline CT_ControlPlane_LabelSet*    GetEgrss( ) const;
    inline void                         SetEgrss( CT_ControlPlane_LabelSet* theEgrss );

    inline CT_ControlPlane_TNA*         GetAEnd2( ) const;
    inline void                         SetAEnd2( CT_ControlPlane_TNA* theAEnd2 ); 

    inline CT_ControlPlane_TNA*         GetZEnd2( ) const;
    inline void                         SetZEnd2( CT_ControlPlane_TNA* theZEnd2 );

    inline CT_ControlPlane_LabelSet*    GetIngrss2( ) const;
    inline void                         SetIngrss2( CT_ControlPlane_LabelSet* theIngrss2 );

    inline CT_ControlPlane_LabelSet*    GetEgrss2( ) const;
    inline void                         SetEgrss2( CT_ControlPlane_LabelSet* theEgrss2 );

    inline CT_TL1_ExppathAddr*          GetPrpUse( ) const;
    inline void                         SetPrpUse( CT_TL1_ExppathAddr* thePrpUse );

    inline CT_SM_PST*                   GetEditablePrimaryState( ) const;
    inline void                         SetEditablePrimaryState( CT_SM_PST* theEditablePrimaryState );

    inline CT_SM_SST*                   GetSecondaryState( ) const;
    inline void                         SetSecondaryState( CT_SM_PST* theSecondaryState );


private:

    LT_Handle*                  myHandle;
    LT_Ctag                     myCtag;
    CT_TL1_CallAddr*            myCallAddr;
    CT_ControlPlane_CallId*     myCallId;
    CT_TL1_LogicalAddr*         mySlpf;
    CT_ControlPlane_TNA*        myAEnd;
    CT_ControlPlane_TNA*        myZEnd;
    CT_ControlPlane_LabelSet*   myIngrss;
    CT_ControlPlane_LabelSet*   myEgrss;
    CT_ControlPlane_TNA*        myAEnd2;
    CT_ControlPlane_TNA*        myZEnd2;
    CT_ControlPlane_LabelSet*   myIngrss2;
    CT_ControlPlane_LabelSet*   myEgrss2;
    CT_TL1_ExppathAddr*         myPrpUse;
    CT_SM_PST*                  myEditablePrimaryState;
    CT_SM_SST*                  mySecondaryState;
};


//-----------------------------------------------------------------------------
inline LT_Handle*                   
TL1_CallRtrvParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_CallRtrvParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//-----------------------------------------------------------------------------
inline LT_Ctag                     
TL1_CallRtrvParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_CallRtrvParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//-----------------------------------------------------------------------------
inline CT_TL1_CallAddr*                     
TL1_CallRtrvParameters::GetCallAddr( ) const
{
    return myCallAddr;
}

inline void                         
TL1_CallRtrvParameters::SetCallAddr( CT_TL1_CallAddr* theCallAddr )
{
    myCallAddr = theCallAddr;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_CallId*    
TL1_CallRtrvParameters::GetCallId( ) const
{
    return myCallId;
}

inline void              
TL1_CallRtrvParameters::SetCallId( CT_ControlPlane_CallId* theCallId )
{
    myCallId = theCallId;
}

//-----------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*          
TL1_CallRtrvParameters::GetSlpf( ) const
{ 
    return mySlpf;
}

inline void                         
TL1_CallRtrvParameters::SetSlpf( CT_TL1_LogicalAddr* theSlpf )
{
    mySlpf = theSlpf;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallRtrvParameters::GetAEnd( ) const
{
    return myAEnd;
}

inline void                         
TL1_CallRtrvParameters::SetAEnd( CT_ControlPlane_TNA* theAEnd ) 
{
    myAEnd = theAEnd;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallRtrvParameters::GetZEnd( ) const
{
    return myZEnd;
}

inline void                         
TL1_CallRtrvParameters::SetZEnd( CT_ControlPlane_TNA* theZEnd ) 
{
    myZEnd = theZEnd;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*                     
TL1_CallRtrvParameters::GetIngrss( ) const
{
    return myIngrss;
}

inline void                         
TL1_CallRtrvParameters::SetIngrss( CT_ControlPlane_LabelSet* theIngrss )
{
    myIngrss = theIngrss;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*    
TL1_CallRtrvParameters::GetEgrss( ) const
{
    return myEgrss;
}


inline void              
TL1_CallRtrvParameters::SetEgrss( CT_ControlPlane_LabelSet* theEgrss )
{
    myEgrss = theEgrss;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallRtrvParameters::GetAEnd2( ) const
{
    return myAEnd2;
}

inline void                         
TL1_CallRtrvParameters::SetAEnd2( CT_ControlPlane_TNA* theAEnd2 ) 
{
    myAEnd2 = theAEnd2;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_CallRtrvParameters::GetZEnd2( ) const
{
    return myZEnd2;
}

inline void                         
TL1_CallRtrvParameters::SetZEnd2( CT_ControlPlane_TNA* theZEnd2 ) 
{
    myZEnd2 = theZEnd2;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*                     
TL1_CallRtrvParameters::GetIngrss2( ) const
{
    return myIngrss2;
}

inline void                         
TL1_CallRtrvParameters::SetIngrss2( CT_ControlPlane_LabelSet* theIngrss2 )
{
    myIngrss2 = theIngrss2;
}

//-----------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*    
TL1_CallRtrvParameters::GetEgrss2( ) const
{
    return myEgrss2;
}


inline void              
TL1_CallRtrvParameters::SetEgrss2( CT_ControlPlane_LabelSet* theEgrss2 )
{
    myEgrss2 = theEgrss2;
}
//-----------------------------------------------------------------------------
inline CT_TL1_ExppathAddr*    
TL1_CallRtrvParameters::GetPrpUse( ) const
{
    return myPrpUse;
}


inline void              
TL1_CallRtrvParameters::SetPrpUse( CT_TL1_ExppathAddr* thePrpUse )
{
    myPrpUse = thePrpUse;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_CallRtrvParameters::GetEditablePrimaryState( ) const
{
    return myEditablePrimaryState;
}

inline void                         
TL1_CallRtrvParameters::SetEditablePrimaryState( CT_SM_PST* theEditablePrimaryState )
{
    myEditablePrimaryState = theEditablePrimaryState;
}

//--------------------------------------------------------------------------------
inline CT_SM_SST*                   
TL1_CallRtrvParameters::GetSecondaryState( ) const
{
    return mySecondaryState;
}

inline void                         
TL1_CallRtrvParameters::SetSecondaryState( CT_SM_PST* theSecondaryState )
{
    mySecondaryState = theSecondaryState;
}

#endif
