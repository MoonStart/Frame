/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_BBREQUEST_H
#define SNMP_BBREQUEST_H

#include <gdef.h>
#include <TimeService/FC_Time.h>
#include <TimeService/FC_TimeService.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>


class SNMP_BbRequest : public FC_BbObject
{
public:

    SNMP_BbRequest ();
    virtual ~SNMP_BbRequest();
    inline uint32 SendRequest();
    inline void SendRequest(uint32 theReqId);
    inline uint32 GetRequestId() const;
    inline FC_Time GetRequestTime() const;
    virtual void Reset();
    virtual void Init(restart_type theRestart);

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );

    uint32 ChangeRequestId();
    uint32 myRequestId;
    FC_Time myRequestTime;

private:

};

//-----------------------------------------------------------------
inline uint32 SNMP_BbRequest::GetRequestId() const
{
    return myRequestId;
}

//-----------------------------------------------------------------
inline FC_Time SNMP_BbRequest::GetRequestTime() const
{
    return myRequestTime;
}

//-----------------------------------------------------------------
inline uint32 SNMP_BbRequest::SendRequest()
{
    myRequestTime.GetCurrentTime();
    return ChangeRequestId();
}

//-----------------------------------------------------------------
inline void SNMP_BbRequest::SendRequest(uint32 theReqId)
{
    myRequestTime.GetCurrentTime();
    myRequestId = theReqId;
}

#endif //SNMP_BBREQUEST_H
