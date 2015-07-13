/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_INTFREQUEST_H
#define SNMP_INTFREQUEST_H

#include <SNMP/SNMP_Request.h>
#include <CommonTypes/CT_SNMP_Definition.h>

class SNMP_BbIntfStatsRequest : public SNMP_BbRequest
{
public:

    SNMP_BbIntfStatsRequest () : 
        SNMP_BbRequest() {}
    virtual ~SNMP_BbIntfStatsRequest() {}

};


#endif //SNMP_INTFREQUEST_H
