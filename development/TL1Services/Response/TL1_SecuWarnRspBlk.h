/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         Feb. 7, 2005- Maggie Zhang 
DESCRIPTION:    Header for Retreive Warning Message Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SECUWARNRSPBLK_H_
#define __TL1_SECUWARNRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#include <vector>

using namespace std;

class TL1_SecuWarnRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SecuWarnRspBlk() {}
    
    TL1_SecuWarnRspBlk(const TL1_SecuWarnRspBlk& );

    TL1_SecuWarnRspBlk(const TL1_SmartParameter<string>& theWarningMesg);
                 
    virtual ~TL1_SecuWarnRspBlk();

    TL1_SecuWarnRspBlk& operator=( const TL1_SecuWarnRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetWarningMesg() const
    {
        return itsWarningMesg;
    }

private:

    TL1_SmartParameter<string> itsWarningMesg;
};

typedef TL1_Rtv_Response< TL1_SecuWarnRspBlk > TL1_SecuWarnResponse;

#endif



