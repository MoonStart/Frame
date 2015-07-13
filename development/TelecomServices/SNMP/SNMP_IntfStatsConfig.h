/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_INTFCFG_H
#define SNMP_INTFCFG_H

#include <SNMP/SNMP_Config.h>

class SNMP_BbIntfStatsCfg : public SNMP_BbCfg
{
public:
    SNMP_BbIntfStatsCfg();
    virtual ~SNMP_BbIntfStatsCfg();
    virtual void Init(restart_type theRestart);

    void ResetAdminStatus()                             { myAdminStatus = CT_SNMP_AdminStatusUnk; }
    virtual void ResetAll();

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);

    CT_SNMP_AdminStatus        myAdminStatus;
};

#endif //SNMP_INTFCFG_H

