/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         2013.9.16 - Gang Zhu
DESCRIPTION:    Header file for  TL1 MGTETH Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MGTETHPARAMETERS_H__
#define __TL1_MGTETHPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_FACDOMAIN_H__
#include <TL1Core/TL1_FacDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_FACRSPBLK_H__
#include <Response/TL1_FACRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>


class TL1_MgtETHParameters  
{
public:
    
    TL1_MgtETHParameters();

    virtual ~TL1_MgtETHParameters();

    TL1_MgtETHParameters(const TL1_MgtETHParameters& theBlock );

    TL1_MgtETHParameters& operator=( const TL1_MgtETHParameters& theBlock );

    bool operator==( const TL1_MgtETHParameters& theBlock ) const;

	inline LT_Handle*               GetHandle( ) const;
    inline void                     SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                  GetCtag( ) const;
    inline void                     SetCtag( LT_Ctag theCtag );
	
	inline CT_ProfileTableId*	    GetAlarmProfile( ) const;
	inline void						SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile );

	inline void                     SetAutoNegotiationEnabled(bool* theIsAutoNegotiationEnabled);
    bool*                           GetAutoNegotiationEnabled() const;

    inline CT_TEL_daHz*             GetEthRate( ) const;
    inline void                     SetEthRate( CT_TEL_daHz* theEthRate );

	inline CT_TEL_MAC_DUPLEX_MODE*  GetDuplexMode( ) const;
    inline void                     SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode );   

    inline CT_TEL_MAC_FLOWCTRL*     GetFlowCtrl() const;
	inline void                     SetFlowCtrl(CT_TEL_MAC_FLOWCTRL* theFlowCtrl);
	
	inline CT_SM_PST*               GetPrimaryState( ) const;
    inline void                     SetPrimaryState( CT_SM_PST* thePrimaryState );

private:
	
    CT_ProfileTableId*            myAlarmProfile;
	bool*                         myAutoNegotiation;
	CT_TEL_daHz*				  myEthRate;
    CT_TEL_MAC_DUPLEX_MODE* 	  myDuplexMode;
    CT_TEL_MAC_FLOWCTRL*          myFlowCtrl;
    LT_Handle*			          myHandle;
    LT_Ctag				          myCtag;
	CT_SM_PST*                    myPst;
};


inline CT_ProfileTableId*           
TL1_MgtETHParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_MgtETHParameters::SetAlarmProfile(  CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}

inline bool*     
TL1_MgtETHParameters::GetAutoNegotiationEnabled( ) const
{
    return myAutoNegotiation;
}

inline void     
TL1_MgtETHParameters::SetAutoNegotiationEnabled(bool* theIsAutoNegotiationEnabled)
{
    myAutoNegotiation = theIsAutoNegotiationEnabled;
}


inline CT_TEL_daHz*     
TL1_MgtETHParameters::GetEthRate( ) const
{
    return myEthRate;
}

inline void     
TL1_MgtETHParameters::SetEthRate( CT_TEL_daHz* theEthRate )
{
    myEthRate = theEthRate;
}

inline CT_TEL_MAC_DUPLEX_MODE*     
TL1_MgtETHParameters::GetDuplexMode( ) const
{   
    return myDuplexMode;
}

inline void    
TL1_MgtETHParameters::SetDuplexMode( CT_TEL_MAC_DUPLEX_MODE* theDuplexMode )
{
    myDuplexMode = theDuplexMode;
}

inline CT_TEL_MAC_FLOWCTRL* 
TL1_MgtETHParameters::GetFlowCtrl() const
{
   return myFlowCtrl;
}

inline void 
TL1_MgtETHParameters::SetFlowCtrl(CT_TEL_MAC_FLOWCTRL * theFlowCtrl)
{
   myFlowCtrl = theFlowCtrl;
}

inline LT_Handle*                   
TL1_MgtETHParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_MgtETHParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

inline LT_Ctag                     
TL1_MgtETHParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_MgtETHParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

inline CT_SM_PST*               
TL1_MgtETHParameters::GetPrimaryState( ) const
{
    return myPst;
}

inline void
TL1_MgtETHParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPst = thePrimaryState;
}

#endif

