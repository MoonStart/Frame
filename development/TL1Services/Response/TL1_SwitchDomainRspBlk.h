/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 SwitchDomain Response Class
TARGET:
AUTHOR:         February 24, 2009 - Ed Badnyk
DESCRIPTION:    Header file for TL1 SwitchDomain Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_SWITCHDOMAIN_RESPONSE_BLOCK_H_
#define __TL1_SWITCHDOMAIN_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_SwitchDomainMap.h>


class TL1_SwitchDomainRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SwitchDomainRspBlk();

    // Ctor for SwitchDomain
    TL1_SwitchDomainRspBlk(const CT_SwitchDomain* SwitchDomain,
                            const CT_SwitchDomainMembers* CntrSwitch,
                            const CT_SwitchDomainMembers* RepeaterSwitch,
                            const CT_SwitchDomainMembers* EndSwitch,
                            const CT_ProtLevel* ProtLevel, 
                            const CT_SwitchDomainMode* SwitchDomainMode,
                            const CT_ProfileTableId* AlmPf,                                                       
                            const CT_SM_PST* PST,
                            const CT_SM_PSTQ* PSTQ,
                            const CT_SM_SST* SST);

    TL1_SwitchDomainRspBlk(const TL1_SwitchDomainRspBlk& );

    virtual ~TL1_SwitchDomainRspBlk();

    TL1_SwitchDomainRspBlk& operator=( const TL1_SwitchDomainRspBlk& theBlock );
    bool operator==( const TL1_SwitchDomainRspBlk& theBlock ) const;

    bool GetSwitchDomain(CT_SwitchDomain&) const ;
    bool GetCntrSwitch(CT_SwitchDomainMembers&) const ;
    bool GetRepeaterSwitch(CT_SwitchDomainMembers&) const ;
    bool GetEndSwitch(CT_SwitchDomainMembers&) const ;
    bool GetAlmPf( CT_ProfileTableId& almPf) const ;
    bool GetSwitchDomainMode( CT_SwitchDomainMode& switchDomainMode) const;
    bool GetProtLevel( CT_ProtLevel& protLevel) const ;

    bool GetPST(CT_SM_PST&) const ;
    bool GetPSTQ(CT_SM_PSTQ&) const ;
    bool GetSST(CT_SM_SST&) const ;

    CT_SM_PST  GetPST() const ;
    CT_SM_PSTQ GetPSTQ() const ;
    CT_SM_SST  GetSST() const ;

private:
    enum {
        INDEX_SwitchDomain = 0,
        INDEX_CntrSwitch,
        INDEX_RepeaterSwitch,
        INDEX_EndSwitch,
        INDEX_ProtLevel,
        INDEX_SwitchDomainMode,
        INDEX_AlmPf,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>            myBitSet;

    CT_SwitchDomain         mySwitchDomain;
    CT_SwitchDomainMembers  myCntrSwitch;
    CT_SwitchDomainMembers  myRepeaterSwitch;
    CT_SwitchDomainMembers  myEndSwitch;
    CT_ProtLevel            myProtLevel;  
    CT_SwitchDomainMode     mySwitchDomainMode;  
    CT_ProfileTableId       myAlmPf;

    CT_SM_PST               myPST;
    CT_SM_PSTQ              myPSTQ;
    CT_SM_SST               mySST;
};

typedef TL1_Rtv_Response< TL1_SwitchDomainRspBlk > TL1_SwitchDomainResponse;
#endif  // #ifndef __TL1_SWITCHDOMAIN_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
