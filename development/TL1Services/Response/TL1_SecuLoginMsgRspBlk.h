/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         April 11, 2006 - Michael Kreger 
DESCRIPTION:    Header for retrieve login message class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SECULOGINMSGRSPBLK_H_
#define __TL1_SECULOGINMSGRSPBLK_H_

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

class TL1_SecuLoginMsgRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SecuLoginMsgRspBlk() {}
    
    TL1_SecuLoginMsgRspBlk(const TL1_SecuLoginMsgRspBlk& );

    TL1_SecuLoginMsgRspBlk(const TL1_SmartParameter<string>& theLoginMesg);
                 
    virtual ~TL1_SecuLoginMsgRspBlk();

    TL1_SecuLoginMsgRspBlk& operator=( const TL1_SecuLoginMsgRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetLoginMesg() const
    {
        return itsLoginMesg;
    }

private:

    TL1_SmartParameter<string> itsLoginMesg;
};

typedef TL1_Rtv_Response< TL1_SecuLoginMsgRspBlk > TL1_SecuLoginMsgResponse;

#endif



