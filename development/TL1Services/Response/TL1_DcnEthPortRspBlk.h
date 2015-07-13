/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive DcnEth Response Class
TARGET:
AUTHOR:         2014.12.29 - Gang zhu
DESCRIPTION:    Header file for TL1 Retrive mtera DcnEth class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DCNETHPORTRSPBLK_H_
#define __TL1_DCNETHPORTRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif

#include <vector>

using namespace std;


class TL1_DcnEthPortRspBlk : public TL1_GeneralRspBlk
{
public: 
    TL1_DcnEthPortRspBlk() {};
    
    TL1_DcnEthPortRspBlk(const TL1_DcnEthPortRspBlk& );

    TL1_DcnEthPortRspBlk(const TL1_SmartParameter<CT_DCNETHPORTType>& theIfname,
                   const TL1_SmartParameter<bool>& theIfstate,const TL1_SmartParameter<bool>& theZtcstate);
    
    virtual ~TL1_DcnEthPortRspBlk();

    TL1_DcnEthPortRspBlk& operator=( const TL1_DcnEthPortRspBlk& theBlock );

    const TL1_SmartParameter<CT_DCNETHPORTType>& 
        GetIfname() const
    {
        return itsIfname;
    }

    const TL1_SmartParameter<bool>& 
        GetIfstate() const
    {
        return itsIfstate;
    }

    const TL1_SmartParameter<bool>& 
        GetZtcstate() const
    {
        return itsZtcstate;
    }
private:

    
    TL1_SmartParameter<CT_DCNETHPORTType>     itsIfname;
    TL1_SmartParameter<bool>     itsIfstate;
    TL1_SmartParameter<bool>     itsZtcstate;
    
};

typedef TL1_Rtv_Response< TL1_DcnEthPortRspBlk > TL1_DcnEthPortResponse;

#endif


