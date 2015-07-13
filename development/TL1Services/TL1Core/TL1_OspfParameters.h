/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for OSPF TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSPFPARAMETERS_H__
#define __TL1_OSPFPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#include <CommonTypes/CT_EON.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>


class TL1_OspfParameters  
{
public:
    
    TL1_OspfParameters();

    virtual ~TL1_OspfParameters();

    TL1_OspfParameters(const TL1_OspfParameters& theInst );

    TL1_OspfParameters& operator=( const TL1_OspfParameters& theInst );

    bool operator==( const TL1_OspfParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline CT_TL1_AdjacencyAddr* GetAdjacencyAddr( ) const;
    inline void                 SetAdjacencyAddr( CT_TL1_AdjacencyAddr* theAdacencyAddr );

    inline CT_TL1_LinkAddr* GetInterfaceAddr( ) const;
    inline void                 SetInterfaceAddr( CT_TL1_LinkAddr* theInterfaceAddr );

    inline CT_TL1_AreaAddr* GetAreaAddr( ) const;
    inline void                 SetAreaAddr( CT_TL1_AreaAddr* theAreaAddr );

    inline CT_InterfaceType* GetInterfaceType( ) const;
    inline void                 SetInterfaceType( CT_InterfaceType* theInterfaceType );

    inline uint32*              GetIPAddr( ) const;
    inline void                 SetIPAddr( uint32* theIPAddr );

    inline bool*                GetCommandMode( ) const;
    inline void                 SetCommandMode( bool* theCommandMode );

private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_SM_PST*          myPrimaryState;

    CT_InterfaceType*   myInterfaceType; 
    CT_TL1_AdjacencyAddr* myAdjacencyAddr; 
    CT_TL1_LinkAddr*    myInterfaceAddr; 
    CT_TL1_AreaAddr*    myAreaAddr; 
    uint32*             myIPAddr; 
    bool*               myCommandMode; 
};

class TL1_OspfrpEntParameters  
{
public:
    
    TL1_OspfrpEntParameters();

    virtual ~TL1_OspfrpEntParameters();

    TL1_OspfrpEntParameters(const TL1_OspfrpEntParameters& theInst );

    TL1_OspfrpEntParameters& operator=( const TL1_OspfrpEntParameters& theInst );

    bool operator==( const TL1_OspfrpEntParameters& theInst ) const;

    inline LT_Handle*            GetHandle( ) const;
    inline void                  SetHandle( LT_Handle* theHandle );

    inline LT_Ctag               GetCtag( ) const;
    inline void                  SetCtag( LT_Ctag theCtag );

    inline uint32*               GetChildRoutingAreaId( ) const;
    inline void                  SetChildRoutingAreaId( uint32* theChildRoutingAreaId );

    inline uint32*               GetParentRoutingAreaId( ) const;
    inline void                  SetParentRoutingAreaId( uint32* theParentRoutingAreaId );

    inline CT_Ospfrp_Entry_Type* GetEntryType( ) const;
    inline void                  SetEntryType( CT_Ospfrp_Entry_Type* theEntryType );

    inline uint32*               GetParentNodeId( ) const;
    inline void                  SetParentNodeId( uint32* theParentNodeId );

    inline uint32*               GetParentTgtAddr( ) const;
    inline void                  SetParentTgtAddr( uint32* theParentTgtAddr );

    inline uint32*               GetParentTgtAddrMask( ) const;
    inline void                  SetParentTgtAddrMask( uint32* theParentTgtAddrMask );

    inline uint32*               GetChildTgtAddr( ) const;
    inline void                  SetChildTgtAddr( uint32* theChildTgtAddr );

    inline uint32*               GetChildTgtAddrMask( ) const;
    inline void                  SetChildTgtAddrMask( uint32* theChildTgtAddrMask );
    
    inline uint32*               GetParentLinkAddr( ) const;
    inline void                  SetParentLinkAddr( uint32* theParentLinkAddr );
    
    inline uint32*               GetParentLinkIfIdx( ) const;
    inline void                  SetParentLinkIfIdx( uint32* theParentLinkIfIdx );
    
    inline uint32*               GetChildLinkAddr( ) const;
    inline void                  SetChildLinkAddr( uint32* theChildLinkAddr );
    
    inline uint32*               GetChildLinkIfIdx( ) const;
    inline void                  SetChildLinkIfIdx( uint32* theChildLinkIdx );
    
    inline uint8*                GetPrecedence( ) const;
    inline void                  SetPrecedence( uint8*  thePrecedence );

private:

    LT_Handle*             myHandle;
    LT_Ctag                myCtag;
    uint32*                myChildRoutingAreaId;
    uint32*                myParentRoutingAreaId;
    CT_Ospfrp_Entry_Type*  myEntryType;
    uint32*                myParentNodeId;
    uint32*                myParentTgtAddr;
    uint32*                myParentTgtAddrMask;
    uint32*                myChildTgtAddr;
    uint32*                myChildTgtAddrMask;
    uint32*                myParentLinkAddr;
    uint32*                myParentLinkIfIdx;
    uint32*                myChildLinkAddr;
    uint32*                myChildLinkIfIdx;
    uint8*                 myPrecedence;
};


class TL1_OspfrpEdParameters  
{
public:
    
    TL1_OspfrpEdParameters();

    virtual ~TL1_OspfrpEdParameters();

    TL1_OspfrpEdParameters(const TL1_OspfrpEdParameters& theInst );

    TL1_OspfrpEdParameters& operator=( const TL1_OspfrpEdParameters& theInst );

    bool operator==( const TL1_OspfrpEdParameters& theInst ) const;

    inline LT_Handle*            GetHandle( ) const;
    inline void                  SetHandle( LT_Handle* theHandle );

    inline LT_Ctag               GetCtag( ) const;
    inline void                  SetCtag( LT_Ctag theCtag );

    inline uint32*               GetChildRoutingAreaId( ) const;
    inline void                  SetChildRoutingAreaId( uint32* theChildRoutingAreaId );

    inline uint32*               GetParentRoutingAreaId( ) const;
    inline void                  SetParentRoutingAreaId( uint32* theParentRoutingAreaId );

    inline uint32*               GetParentNodeId( ) const;
    inline void                  SetParentNodeId( uint32* theParentNodeId );

    inline uint32*               GetParentTgtAddr( ) const;
    inline void                  SetParentTgtAddr( uint32* theParentTgtAddr );

    inline uint32*               GetParentTgtAddrMask( ) const;
    inline void                  SetParentTgtAddrMask( uint32* theParentTgtAddrMask );

    inline uint32*               GetChildTgtAddr( ) const;
    inline void                  SetChildTgtAddr( uint32* theChildTgtAddr );

    inline uint32*               GetChildTgtAddrMask( ) const;
    inline void                  SetChildTgtAddrMask( uint32* theChildTgtAddrMask );
    
    inline uint32*               GetParentLinkAddr( ) const;
    inline void                  SetParentLinkAddr( uint32* theParentLinkAddr );
    
    inline uint32*               GetParentLinkIfIdx( ) const;
    inline void                  SetParentLinkIfIdx( uint32* theParentLinkIfIdx );
    
    inline uint32*               GetChildLinkAddr( ) const;
    inline void                  SetChildLinkAddr( uint32* theChildLinkAddr );
    
    inline uint32*               GetChildLinkIfIdx( ) const;
    inline void                  SetChildLinkIfIdx( uint32* theChildLinkIdx );
    
    inline uint8*                GetPrecedence( ) const;
    inline void                  SetPrecedence( uint8*  thePrecedence );

private:

    LT_Handle*             myHandle;
    LT_Ctag                myCtag;
    uint32*                myChildRoutingAreaId;
    uint32*                myParentRoutingAreaId;
    uint32*                myParentNodeId;
    uint32*                myParentTgtAddr;
    uint32*                myParentTgtAddrMask;
    uint32*                myChildTgtAddr;
    uint32*                myChildTgtAddrMask;
    uint32*                myParentLinkAddr;
    uint32*                myParentLinkIfIdx;
    uint32*                myChildLinkAddr;
    uint32*                myChildLinkIfIdx;
    uint8*                 myPrecedence;
};

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_OspfParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_OspfParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_OspfParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_OspfParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_OspfParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_OspfParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_TL1_AdjacencyAddr*              
TL1_OspfParameters::GetAdjacencyAddr( ) const
{
    return myAdjacencyAddr;
}

inline void
TL1_OspfParameters::SetAdjacencyAddr( CT_TL1_AdjacencyAddr* theAdjanceyAddr )
{
    myAdjacencyAddr = theAdjanceyAddr;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LinkAddr*              
TL1_OspfParameters::GetInterfaceAddr( ) const
{
    return myInterfaceAddr;
}

inline void
TL1_OspfParameters::SetInterfaceAddr( CT_TL1_LinkAddr* theInterfaceAddr )
{
    myInterfaceAddr = theInterfaceAddr;
}

//--------------------------------------------------------------------------------
inline CT_TL1_AreaAddr*              
TL1_OspfParameters::GetAreaAddr( ) const
{
    return myAreaAddr;
}

inline void
TL1_OspfParameters::SetAreaAddr( CT_TL1_AreaAddr* theAreaAddr )
{
    myAreaAddr = theAreaAddr;
}

//--------------------------------------------------------------------------------
inline CT_InterfaceType*              
TL1_OspfParameters::GetInterfaceType( ) const
{
    return myInterfaceType;
}

inline void                
TL1_OspfParameters::SetInterfaceType( CT_InterfaceType* theInterfaceType )
{
    myInterfaceType = theInterfaceType;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfParameters::GetIPAddr( ) const
{
    return myIPAddr;
}

inline void                 
TL1_OspfParameters::SetIPAddr( uint32* theIPAddr )
{
    myIPAddr = theIPAddr;
}

//--------------------------------------------------------------------------------
inline bool*              
TL1_OspfParameters::GetCommandMode( ) const
{
    return myCommandMode;
}

inline void                 
TL1_OspfParameters::SetCommandMode( bool* theCommandMode )
{
    myCommandMode = theCommandMode;
}

//--------------------------------------------------------------------------------
inline uint32*                   
TL1_OspfrpEntParameters::GetChildRoutingAreaId( ) const
{
    return myChildRoutingAreaId;
}

inline void                         
TL1_OspfrpEntParameters::SetChildRoutingAreaId( uint32* theChildRoutingAreaId )
{
    myChildRoutingAreaId = theChildRoutingAreaId;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_OspfrpEntParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_OspfrpEntParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_OspfrpEntParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_OspfrpEntParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetParentRoutingAreaId( ) const
{
    return myParentRoutingAreaId;
}

inline void
TL1_OspfrpEntParameters::SetParentRoutingAreaId( uint32* theParentRoutingAreaId )
{
    myParentRoutingAreaId = theParentRoutingAreaId;
}

//--------------------------------------------------------------------------------
inline CT_Ospfrp_Entry_Type*              
TL1_OspfrpEntParameters::GetEntryType( ) const
{
    return myEntryType;
}

inline void
TL1_OspfrpEntParameters::SetEntryType( CT_Ospfrp_Entry_Type* theEntryType )
{
    myEntryType = theEntryType;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetParentNodeId( ) const
{
    return myParentNodeId;
}

inline void
TL1_OspfrpEntParameters::SetParentNodeId( uint32* theParentNodeId )
{
    myParentNodeId = theParentNodeId;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetParentTgtAddr( ) const
{
    return myParentTgtAddr;
}

inline void                
TL1_OspfrpEntParameters::SetParentTgtAddr( uint32* theParentTgtAddr )
{
    myParentTgtAddr = theParentTgtAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetParentTgtAddrMask( ) const
{
    return myParentTgtAddrMask;
}

inline void                 
TL1_OspfrpEntParameters::SetParentTgtAddrMask( uint32* theParentTgtAddrMask )
{
    myParentTgtAddrMask = theParentTgtAddrMask;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetChildTgtAddr( ) const
{
    return myChildTgtAddr;
}

inline void                 
TL1_OspfrpEntParameters::SetChildTgtAddr( uint32* theChildTgtAddr )
{
    myChildTgtAddr = theChildTgtAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetChildTgtAddrMask( ) const
{
    return myChildTgtAddrMask;
}

inline void                 
TL1_OspfrpEntParameters::SetChildTgtAddrMask( uint32* theChildTgtAddrMask )
{
    myChildTgtAddrMask = theChildTgtAddrMask;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetParentLinkAddr( ) const
{
    return myParentLinkAddr;
}

inline void
TL1_OspfrpEntParameters::SetParentLinkAddr( uint32* theParentLinkAddr )
{
    myParentLinkAddr = theParentLinkAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetParentLinkIfIdx( ) const
{
    return myParentLinkIfIdx;
}

inline void                
TL1_OspfrpEntParameters::SetParentLinkIfIdx( uint32* theParentLinkIfIdx )
{
    myParentLinkIfIdx = theParentLinkIfIdx;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetChildLinkAddr( ) const
{
    return myChildLinkAddr;
}

inline void                 
TL1_OspfrpEntParameters::SetChildLinkAddr( uint32* theChildLinkAddr )
{
    myChildLinkAddr = theChildLinkAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEntParameters::GetChildLinkIfIdx( ) const
{
    return myChildLinkIfIdx;
}

inline void                 
TL1_OspfrpEntParameters::SetChildLinkIfIdx( uint32* theChildLinkIfIdx )
{
    myChildLinkIfIdx = theChildLinkIfIdx;
}

//--------------------------------------------------------------------------------
inline uint8*              
TL1_OspfrpEntParameters::GetPrecedence( ) const
{
    return myPrecedence;
}

inline void                 
TL1_OspfrpEntParameters::SetPrecedence( uint8* thePrecedence )
{
    myPrecedence = thePrecedence;
}

//--------------------------------------------------------------------------------
inline uint32*                   
TL1_OspfrpEdParameters::GetChildRoutingAreaId( ) const
{
    return myChildRoutingAreaId;
}

inline void                         
TL1_OspfrpEdParameters::SetChildRoutingAreaId( uint32* theChildRoutingAreaId )
{
    myChildRoutingAreaId = theChildRoutingAreaId;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_OspfrpEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_OspfrpEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_OspfrpEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_OspfrpEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetParentRoutingAreaId( ) const
{
    return myParentRoutingAreaId;
}

inline void
TL1_OspfrpEdParameters::SetParentRoutingAreaId( uint32* theParentRoutingAreaId )
{
    myParentRoutingAreaId = theParentRoutingAreaId;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetParentNodeId( ) const
{
    return myParentNodeId;
}

inline void
TL1_OspfrpEdParameters::SetParentNodeId( uint32* theParentNodeId )
{
    myParentNodeId = theParentNodeId;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetParentTgtAddr( ) const
{
    return myParentTgtAddr;
}

inline void                
TL1_OspfrpEdParameters::SetParentTgtAddr( uint32* theParentTgtAddr )
{
    myParentTgtAddr = theParentTgtAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetParentTgtAddrMask( ) const
{
    return myParentTgtAddrMask;
}

inline void                 
TL1_OspfrpEdParameters::SetParentTgtAddrMask( uint32* theParentTgtAddrMask )
{
    myParentTgtAddrMask = theParentTgtAddrMask;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetChildTgtAddr( ) const
{
    return myChildTgtAddr;
}

inline void                 
TL1_OspfrpEdParameters::SetChildTgtAddr( uint32* theChildTgtAddr )
{
    myChildTgtAddr = theChildTgtAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetChildTgtAddrMask( ) const
{
    return myChildTgtAddrMask;
}

inline void                 
TL1_OspfrpEdParameters::SetChildTgtAddrMask( uint32* theChildTgtAddrMask )
{
    myChildTgtAddrMask = theChildTgtAddrMask;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetParentLinkAddr( ) const
{
    return myParentLinkAddr;
}

inline void
TL1_OspfrpEdParameters::SetParentLinkAddr( uint32* theParentLinkAddr )
{
    myParentLinkAddr = theParentLinkAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetParentLinkIfIdx( ) const
{
    return myParentLinkIfIdx;
}

inline void                
TL1_OspfrpEdParameters::SetParentLinkIfIdx( uint32* theParentLinkIfIdx )
{
    myParentLinkIfIdx = theParentLinkIfIdx;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetChildLinkAddr( ) const
{
    return myChildLinkAddr;
}

inline void                 
TL1_OspfrpEdParameters::SetChildLinkAddr( uint32* theChildLinkAddr )
{
    myChildLinkAddr = theChildLinkAddr;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_OspfrpEdParameters::GetChildLinkIfIdx( ) const
{
    return myChildLinkIfIdx;
}

inline void                 
TL1_OspfrpEdParameters::SetChildLinkIfIdx( uint32* theChildLinkIfIdx )
{
    myChildLinkIfIdx = theChildLinkIfIdx;
}

//--------------------------------------------------------------------------------
inline uint8*              
TL1_OspfrpEdParameters::GetPrecedence( ) const
{
    return myPrecedence;
}

inline void                 
TL1_OspfrpEdParameters::SetPrecedence( uint8* thePrecedence )
{
    myPrecedence = thePrecedence;
}

#endif
