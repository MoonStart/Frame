/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Mtera Response Class
TARGET:
AUTHOR:         2013.11.8 - Gang zhu
DESCRIPTION:    Header file for TL1 Retrive mtera Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MTERARSPBLK_H_
#define __TL1_MTERARSPBLK_H_

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


class TL1_MTERARspBlk : public TL1_GeneralRspBlk
{
public: 
    TL1_MTERARspBlk() {};
    
    TL1_MTERARspBlk(const TL1_MTERARspBlk& );

    TL1_MTERARspBlk(const TL1_SmartParameter<uint32>& theLocalIf,
                   const TL1_SmartParameter<uint32>& theLocalIfMask,
                   const TL1_SmartParameter<uint32>& theLocalIfGtw
                   );
    
    virtual ~TL1_MTERARspBlk();

    TL1_MTERARspBlk& operator=( const TL1_MTERARspBlk& theBlock );

    const TL1_SmartParameter<uint32>& 
        GetLocalIf() const
    {
        return itsLocalIf;
    }

    const TL1_SmartParameter<uint32>& 
        GetLocalIfMask() const
    {
        return itsLocalIfMask;
    }
    const TL1_SmartParameter<uint32>& 
        GetLocalIfGtw() const
    {
        return itsLocalIfGtw;
    }

private:

    
    TL1_SmartParameter<uint32>     itsLocalIf;
    TL1_SmartParameter<uint32>     itsLocalIfMask;
    TL1_SmartParameter<uint32>     itsLocalIfGtw;
    
};

typedef TL1_Rtv_Response< TL1_MTERARspBlk > TL1_MTERAResponse;

#endif


