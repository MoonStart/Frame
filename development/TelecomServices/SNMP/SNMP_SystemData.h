/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_BBSYSTEMDATA_H
#define SNMP_BBSYSTEMDATA_H


#include <gdef.h>
#include <iostream>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>

class SNMP_BbSystemInfo : public FC_BbObject
{
public:
    SNMP_BbSystemInfo();
    virtual ~SNMP_BbSystemInfo();
    virtual void Init(restart_type theRestart);
    void   SetSnmpEnableTimestamp(uint32 theTimeTick)   { mySnmpEnableTimestamp = theTimeTick; }
    uint32 GetSnmpEnableTimestamp()                     { return mySnmpEnableTimestamp; }
protected:
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );  
private:
    uint32 mySnmpEnableTimestamp;
    bool   mySnmpEnabledFlag;
};

class SNMP_BbSystemUpTime : public FC_BbObject
{
public:
    SNMP_BbSystemUpTime();
    virtual ~SNMP_BbSystemUpTime();
    virtual void Init(restart_type theRestart);
    void SetSysUpTime(CT_SNMP_TimeTicks theUpTime) { mySysUpTime = theUpTime; }
    CT_SNMP_TimeTicks GetSysUpTime() { return mySysUpTime; }

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );  

private:
    CT_SNMP_TimeTicks mySysUpTime;
};


#endif //SNMP_BBSYSTEMDATA_H
