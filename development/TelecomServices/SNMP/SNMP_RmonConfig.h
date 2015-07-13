/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_RMONETHERCFG_H
#define SNMP_RMONETHERCFG_H

#include <SNMP/SNMP_Config.h>

class SNMP_BbRmonEtherCfg : public SNMP_BbCfg
{
public:
    SNMP_BbRmonEtherCfg();
    virtual ~SNMP_BbRmonEtherCfg();
    virtual void Init(restart_type theRestart);

    CT_SNMP_Integer32   GetIndex()  {return myIndex; }
    bool IsValidIndex()             { return (myIndex != CT_SNMP_DEFAULT_RMON_INDEX); }
    //CT_SNMP_EntryStatus GetStatus()           {return myStatus; }

    void SetIndex(CT_SNMP_Integer32 theCfg)            { myIndex = theCfg; }
    //void SetStatus(CT_SNMP_EntryStatus theCfg)         { myStatus = theCfg; }

    void ResetIndex()             { myIndex = 0; }
   // void ResetStatus()            { myStatus = CT_SNMP_EntryStatus_invalid; }
    virtual void ResetAll();

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);

    CT_SNMP_Integer32        myIndex;
    //CT_SNMP_EntryStatus      myStatus;
};


class SNMP_BbRmonEtherStatsCfg : public SNMP_BbRmonEtherCfg
{
public:
    SNMP_BbRmonEtherStatsCfg();
    virtual ~SNMP_BbRmonEtherStatsCfg();
};


class SNMP_BbRmonEtherHistCfg : public SNMP_BbRmonEtherCfg
{
public:
    SNMP_BbRmonEtherHistCfg();
    virtual ~SNMP_BbRmonEtherHistCfg();
    CT_SNMP_Integer32 GetBucketsRequested() {return myBucketsRequested; }
    CT_SNMP_Integer32 GetInterval()         {return myInterval; }

    void SetBucketsRequested(CT_SNMP_Integer32 theCfg) { myBucketsRequested = theCfg; }
    void SetInterval(CT_SNMP_TimeTicks theCfg)         { myInterval = theCfg; }

    void ResetBucketsRequested()  { myBucketsRequested = 0; }
    void ResetInterval()          { myInterval = 0; }
    virtual void ResetAll();

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);

private:
    CT_SNMP_Integer32        myBucketsRequested;
    CT_SNMP_Integer32        myInterval;
};

#endif //SNMP_RMONETHERCFG_H

