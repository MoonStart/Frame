/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 30, 2011 - TLD
DESCRIPTION:    Header file for TL1 OPR-FINDRTE parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FINDRTEPARAMETERS_H__
#define __TL1_FINDRTEPARAMETERS_H__

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>


#if 0
#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_CALLRSPBLK_H__
#include <Response/TL1_CallRspBlk.h>
#endif
#endif


class TL1_OprFindRteParameters  
{
public:
    
    TL1_OprFindRteParameters();

    virtual ~TL1_OprFindRteParameters();

    TL1_OprFindRteParameters( const TL1_OprFindRteParameters& theInst );

    TL1_OprFindRteParameters& operator=( const TL1_OprFindRteParameters& theInst );

    bool operator==( const TL1_OprFindRteParameters& theInst ) const;

    inline LT_Handle*             GetHandle( ) const;
    inline void                   SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                GetCtag( ) const;
    inline void                   SetCtag( LT_Ctag theCtag );

    inline CT_ControlPlane_TNA*   GetAEnd( ) const;
    inline void                   SetAEnd( CT_ControlPlane_TNA* theAEnd ); 

    inline CT_ControlPlane_TNA*   GetZEnd( ) const;
    inline void                   SetZEnd( CT_ControlPlane_TNA* theZEnd );

    inline CT_TL1_NodeAddr*       GetNodeAddr( ) const;
    inline void                   SetNodeAddr( CT_TL1_NodeAddr* theNodeAddr );

    inline CT_ControlPlane_TNA*   GetAEnd2( ) const;
    inline void                   SetAEnd2( CT_ControlPlane_TNA* theAEnd2 ); 

    inline CT_ControlPlane_TNA*   GetZEnd2( ) const;
    inline void                   SetZEnd2( CT_ControlPlane_TNA* theZEnd2 );

    inline uint32*                GetNodeId2( ) const;
    inline void                   SetNodeId2( uint32* theNodeId2 ); 
    
    inline CT_Call_SignalType*    GetSignalType( ) const;
    inline void                   SetSignalType( CT_Call_SignalType* theSignalType );

    inline uint8*                 GetMultiplierValue( ) const;
    inline void                   SetMultiplierValue( uint8* theMultiplierValue );

    inline uint32*                GetWorkingToNode( ) const;
    inline void                   SetWorkingToNode( uint32* theWorkingToNode ); 

    inline uint32*                GetProtectToNode( ) const;
    inline void                   SetProtectToNode( uint32* theProtectToNode ); 

    inline CT_TL1_ExppathAddr*    GetWorkingPath( ) const;
    inline void                   SetWorkingPath( CT_TL1_ExppathAddr* theWorkingPath ); 

    inline CT_TL1_ExppathAddr*    GetProtectPath( ) const;
    inline void                   SetProtectPath( CT_TL1_ExppathAddr* theProtectPath );

    inline CT_ControlPlane_Srlg*  GetSrlg( ) const;
    inline void                   SetSrlg( CT_ControlPlane_Srlg* theSrlg );

    inline CT_TL1_LogicalAddr*    GetSlpf( ) const;
    inline void                   SetSlpf( CT_TL1_LogicalAddr* theSlpf );

    CT_TEL_daHz*                  GetExpRate( ) const;
    void                          SetExpRate(CT_TEL_daHz* theExpRate);

    uint8*                        GetGfpTs( ) const;
    void                          SetGfpTs(uint8* theGfpTs);

    CT_TL1_ExdpathAddr*           GetWkgXPath( ) const;
    void                          SetWkgXPath(CT_TL1_ExdpathAddr* theWkgXPath);

    CT_TL1_ExdpathAddr*           GetProtXPath( ) const;
    void                          SetProtXPath(CT_TL1_ExdpathAddr* theProtXPath);


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
    uint8*                      myMultiplierValue;
    uint32*                     myWorkingToNode;
    uint32*                     myProtectToNode;
    CT_TL1_ExppathAddr*         myWorkingPath;
    CT_TL1_ExppathAddr*         myProtectPath;
    CT_ControlPlane_Srlg*       mySrlg;
    CT_TL1_LogicalAddr*         mySlpf;
    CT_TEL_daHz*                myExpRate;
    uint8*                      myGfpTs;
    CT_TL1_ExdpathAddr*         myWkgXPath;
    CT_TL1_ExdpathAddr*         myProtXPath;
};


//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_OprFindRteParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_OprFindRteParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}


//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_OprFindRteParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_OprFindRteParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}


//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_OprFindRteParameters::GetAEnd( ) const
{
    return myAEnd;
}

inline void                         
TL1_OprFindRteParameters::SetAEnd( CT_ControlPlane_TNA* theAEnd ) 
{
    myAEnd = theAEnd;
}


//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_OprFindRteParameters::GetZEnd( ) const
{
    return myZEnd;
}

inline void                         
TL1_OprFindRteParameters::SetZEnd( CT_ControlPlane_TNA* theZEnd ) 
{
    myZEnd = theZEnd;
}


//--------------------------------------------------------------------------------
inline CT_TL1_NodeAddr*    
TL1_OprFindRteParameters::GetNodeAddr( ) const
{
    return myNodeAddr;
}

inline void                         
TL1_OprFindRteParameters::SetNodeAddr( CT_TL1_NodeAddr* theNodeAddr )
{
    myNodeAddr = theNodeAddr;
}


//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_OprFindRteParameters::GetAEnd2( ) const
{
    return myAEnd2;
}

inline void                         
TL1_OprFindRteParameters::SetAEnd2( CT_ControlPlane_TNA* theAEnd2 ) 
{
    myAEnd2 = theAEnd2;
}


//--------------------------------------------------------------------------------
inline CT_ControlPlane_TNA*         
TL1_OprFindRteParameters::GetZEnd2( ) const
{
    return myZEnd2;
}

inline void                         
TL1_OprFindRteParameters::SetZEnd2( CT_ControlPlane_TNA* theZEnd2 ) 
{
    myZEnd2 = theZEnd2;
}

//--------------------------------------------------------------------------------
inline uint32*    
TL1_OprFindRteParameters::GetNodeId2( ) const
{
    return myNodeId2;
}

inline void              
TL1_OprFindRteParameters::SetNodeId2( uint32* theNodeId2 )
{
    myNodeId2 = theNodeId2;
}

//--------------------------------------------------------------------------------
inline CT_Call_SignalType*    
TL1_OprFindRteParameters::GetSignalType( ) const
{
    return mySignalType;
}

inline void              
TL1_OprFindRteParameters::SetSignalType( CT_Call_SignalType* theSignalType )
{
    mySignalType = theSignalType;
}


//--------------------------------------------------------------------------------
inline uint8*                  
TL1_OprFindRteParameters::GetMultiplierValue( ) const
{
    return myMultiplierValue;
}

inline void                         
TL1_OprFindRteParameters::SetMultiplierValue( uint8* theMultiplierValue )
{
    myMultiplierValue = theMultiplierValue;
}


//--------------------------------------------------------------------------------
inline uint32*    
TL1_OprFindRteParameters::GetWorkingToNode( ) const
{
    return myWorkingToNode;
}

inline void              
TL1_OprFindRteParameters::SetWorkingToNode( uint32* theWorkingToNode )
{
    myWorkingToNode = theWorkingToNode;
}


//--------------------------------------------------------------------------------
inline uint32*    
TL1_OprFindRteParameters::GetProtectToNode( ) const
{
    return myProtectToNode;
}

inline void              
TL1_OprFindRteParameters::SetProtectToNode( uint32* theProtectToNode )
{
    myProtectToNode = theProtectToNode;
}


//--------------------------------------------------------------------------------
inline CT_TL1_ExppathAddr*                      
TL1_OprFindRteParameters::GetWorkingPath( ) const
{
    return myWorkingPath;
}

inline void                         
TL1_OprFindRteParameters::SetWorkingPath( CT_TL1_ExppathAddr* theWorkingPath )
{
    myWorkingPath = theWorkingPath;
}


//--------------------------------------------------------------------------------
inline CT_TL1_ExppathAddr*                      
TL1_OprFindRteParameters::GetProtectPath( ) const
{
    return myProtectPath;
}

inline void                         
TL1_OprFindRteParameters::SetProtectPath( CT_TL1_ExppathAddr* theProtectPath )
{
    myProtectPath = theProtectPath;
}


//--------------------------------------------------------------------------------
inline CT_ControlPlane_Srlg*    
TL1_OprFindRteParameters::GetSrlg( ) const
{
    return mySrlg;
}

inline void              
TL1_OprFindRteParameters::SetSrlg( CT_ControlPlane_Srlg* theSrlg )
{
    mySrlg = theSrlg;
}


//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*          
TL1_OprFindRteParameters::GetSlpf( ) const
{ 
    return mySlpf;
}

inline void                         
TL1_OprFindRteParameters::SetSlpf( CT_TL1_LogicalAddr* theSlpf )
{
    mySlpf = theSlpf;
}

//--------------------------------------------------------------------------------
inline CT_TEL_daHz*
TL1_OprFindRteParameters::GetExpRate( ) const
{
    return myExpRate;
}

inline void
TL1_OprFindRteParameters::SetExpRate( CT_TEL_daHz* theExpRate )
{
   myExpRate = theExpRate;
}

//--------------------------------------------------------------------------------
inline uint8*
TL1_OprFindRteParameters::GetGfpTs( ) const
{
    return myGfpTs;
}

inline void
TL1_OprFindRteParameters::SetGfpTs( uint8* theGfpTs )
{
   myGfpTs = theGfpTs;
}

//--------------------------------------------------------------------------------
inline CT_TL1_ExdpathAddr*                      
TL1_OprFindRteParameters::GetWkgXPath( ) const
{
    return myWkgXPath;
}

inline void                         
TL1_OprFindRteParameters::SetWkgXPath( CT_TL1_ExdpathAddr* theWkgXPath )
{
    myWkgXPath = theWkgXPath;
}

//--------------------------------------------------------------------------------
inline CT_TL1_ExdpathAddr*                      
TL1_OprFindRteParameters::GetProtXPath( ) const
{
    return myProtXPath;
}

inline void                         
TL1_OprFindRteParameters::SetProtXPath( CT_TL1_ExdpathAddr* theProtXPath )
{
    myProtXPath = theProtXPath;
}

#endif // __TL1_FINDRTEPARAMETERS_H__
