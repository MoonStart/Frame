/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive TOD Response Class
TARGET:
AUTHOR:         June 11, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Retrive TOD Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TIMERSPBLK_H_
#define __TL1_TIMERSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_TIME_H_
#include <CommonTypes/CT_Time.h>
#endif


#include <vector>

using namespace std;

class TL1_TodRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_TodRspBlk() {}
    
    TL1_TodRspBlk(const TL1_TodRspBlk& );

    TL1_TodRspBlk( const TL1_SmartParameter<CT_TimeTm>&   theUTCDateAndTime,
                   const TL1_SmartParameter<int>&         theTimeSubSeconds,
                   const TL1_SmartParameter<string>&      theTimeSource,
                   const TL1_SmartParameter<string>&      theAlternalteTimeSource,
                   const TL1_SmartParameter<CT_SM_State>& theState );
                 
    
    virtual ~TL1_TodRspBlk();

    TL1_TodRspBlk& operator=( const TL1_TodRspBlk& theBlock );

    const TL1_SmartParameter<CT_TimeTm>& 
        GetUTCDateAndTime() const
    {
        return itsUTCDateAndTime;
    }

    const TL1_SmartParameter<int>& 
        GetTimeSubSeconds() const
    {
        return itsTimeSubSeconds;
    }


    const TL1_SmartParameter<string>& 
        GetTimeSource() const
    {
        return itsTimeSource;
    }

    const TL1_SmartParameter<string>& 
        GetAlternalteTimeSource() const
    {
        return itsAlternalteTimeSource;
    }

    const TL1_SmartParameter<CT_SM_State>&
        GetState() const
    {
        return itsState;
    }


private:

    TL1_SmartParameter<CT_TimeTm>   itsUTCDateAndTime;
    TL1_SmartParameter<int>         itsTimeSubSeconds;
    TL1_SmartParameter<string>      itsTimeSource;    
    TL1_SmartParameter<string>      itsAlternalteTimeSource;
    TL1_SmartParameter<CT_SM_State> itsState;
};

typedef TL1_Rtv_Response< TL1_TodRspBlk > TL1_TodResponse;

#endif


