/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for LABELSET TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LABELSETPARAMETERS_H__
#define __TL1_LABELSETPARAMETERS_H__

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

class TL1_LabelSetParameters  
{
public:
    
    TL1_LabelSetParameters();

    virtual ~TL1_LabelSetParameters();

    TL1_LabelSetParameters(const TL1_LabelSetParameters& theInst );

    TL1_LabelSetParameters& operator=( const TL1_LabelSetParameters& theInst );

    bool operator==( const TL1_LabelSetParameters& theInst ) const;

    inline LT_Handle*                   GetHandle( ) const;
    inline void                         SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                      GetCtag( ) const;
    inline void                         SetCtag( LT_Ctag theCtag );

    inline CT_ControlPlane_LabelSet*    GetIngress( ) const;
    inline void                         SetIngress( CT_ControlPlane_LabelSet* theLabelSet );

    inline CT_ControlPlane_LabelSet*    GetEgress( ) const;
    inline void                         SetEgress( CT_ControlPlane_LabelSet* theLabelSet );

    inline CT_OperationType*            GetOperType() const;
    inline void                         SetOperType(CT_OperationType* theOperType);

    inline CT_TL1_LabelSetAddr*         GetSeedLabelSet( ) const;
    inline void                         SetSeedLabelSet( CT_TL1_LabelSetAddr* theAddr );

    inline CT_TL1_LabelSetIdxRangeList* GetIdxRangeList( ) const;
    inline void                         SetIdxRangeList( CT_TL1_LabelSetIdxRangeList* theList );

private:

    LT_Handle*                   myHandle;
    LT_Ctag                      myCtag;
    CT_ControlPlane_LabelSet*    myIngress;
    CT_ControlPlane_LabelSet*    myEgress;
    CT_OperationType*            myOperationType;
    CT_TL1_LabelSetAddr*         mySeedLabelSet;
    CT_TL1_LabelSetIdxRangeList* myIdxRangeList;
};


inline LT_Handle*                   
TL1_LabelSetParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_LabelSetParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_LabelSetParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_LabelSetParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*                     
TL1_LabelSetParameters::GetIngress( ) const
{
    return myIngress;
}

inline void                         
TL1_LabelSetParameters::SetIngress( CT_ControlPlane_LabelSet* theLabelSet )
{
    myIngress = theLabelSet;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*                     
TL1_LabelSetParameters::GetEgress( ) const
{
    return myEgress;
}

inline void                         
TL1_LabelSetParameters::SetEgress( CT_ControlPlane_LabelSet* theLabelSet )
{
    myEgress = theLabelSet;
}

inline CT_OperationType*                     
TL1_LabelSetParameters::GetOperType( ) const
{
    return myOperationType;
}

inline void                         
TL1_LabelSetParameters::SetOperType( CT_OperationType* theOperationType )
{
    myOperationType = theOperationType;
}


//--------------------------------------------------------------------------------
inline CT_TL1_LabelSetAddr*                      
TL1_LabelSetParameters::GetSeedLabelSet( ) const
{
    return mySeedLabelSet;
}

inline void                         
TL1_LabelSetParameters::SetSeedLabelSet( CT_TL1_LabelSetAddr* theAddr )
{
    mySeedLabelSet = theAddr;
}


//--------------------------------------------------------------------------------
inline CT_TL1_LabelSetIdxRangeList*                      
TL1_LabelSetParameters::GetIdxRangeList( ) const
{
    return myIdxRangeList;
}

inline void                         
TL1_LabelSetParameters::SetIdxRangeList( CT_TL1_LabelSetIdxRangeList* theList )
{
    myIdxRangeList = theList;
}
#endif
