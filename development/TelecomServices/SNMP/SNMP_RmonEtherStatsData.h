/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_RMONETHERSTATSDATA_H
#define SNMP_RMONETHERSTATSDATA_H

#include <SNMP/SNMP_RmonData.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ErrorService/FC_Error.h>


class SNMP_BbRmonEtherStatsData : public SNMP_BbRmonData
{
public:
    SNMP_BbRmonEtherStatsData();
    virtual ~SNMP_BbRmonEtherStatsData();
    CT_SNMP_Counter32 GetDropEvents()     {return myEtherData.myDropEvents;}
    CT_SNMP_Counter32 GetOctets()         {return myEtherData.myOctets;}
    CT_SNMP_Counter32 GetPkts()           {return myEtherData.myPkts;}
    CT_SNMP_Counter32 GetBroadcastPkts()  {return myEtherData.myBroadcastPkts;}
    CT_SNMP_Counter32 GetMulticastPkts()  {return myEtherData.myMulticastPkts;}
    CT_SNMP_Counter32 GetCRCAlignErrors() {return myEtherData.myCRCAlignErrors;}
    CT_SNMP_Counter32 GetUndersizePkts()  {return myEtherData.myUndersizePkts;}
    CT_SNMP_Counter32 GetOversizePkts()   {return myEtherData.myOversizePkts;}
    CT_SNMP_Counter32 GetFragments()      {return myEtherData.myFragments;}
    CT_SNMP_Counter32 GetJabbers()        {return myEtherData.myJabbers;}
    CT_SNMP_Counter32 GetCollisions()     {return myEtherData.myCollisions;}
    CT_SNMP_Counter32 GetPkts64()         {return myPkts64Octets;}
    CT_SNMP_Counter32 GetPkts65to127()    {return myPkts65to127Octets;}
    CT_SNMP_Counter32 GetPkts128to255()   {return myPkts128to255Octets;}
    CT_SNMP_Counter32 GetPkts256to511()   {return myPkts256to511Octets;}
    CT_SNMP_Counter32 GetPkts512to1023()  {return myPkts512to1023Octets;}
    CT_SNMP_Counter32 GetPkts1024to1518() {return myPkts1024to1518Octets;}
    CT_SNMP_Counter32 GetDroppedFrames()  {return myDroppedFrames; }
    CT_SNMP_TimeTicks GetCreateTime()     {return myCreateTime; }

    void SetDropEvents(CT_SNMP_Counter32 theData)     { myEtherData.myDropEvents = theData;}
    void SetOctets(CT_SNMP_Counter32 theData)         { myEtherData.myOctets = theData;}
    void SetPkts(CT_SNMP_Counter32 theData)           { myEtherData.myPkts = theData;}
    void SetBroadcastPkts(CT_SNMP_Counter32 theData)  { myEtherData.myBroadcastPkts = theData;}
    void SetMulticastPkts(CT_SNMP_Counter32 theData)  { myEtherData.myMulticastPkts = theData;}
    void SetCRCAlignErrors(CT_SNMP_Counter32 theData) { myEtherData.myCRCAlignErrors = theData;}
    void SetUndersizePkts(CT_SNMP_Counter32 theData)  { myEtherData.myUndersizePkts = theData;}
    void SetOversizePkts(CT_SNMP_Counter32 theData)   { myEtherData.myOversizePkts = theData;}
    void SetFragments(CT_SNMP_Counter32 theData)      { myEtherData.myFragments = theData;}
    void SetJabbers(CT_SNMP_Counter32 theData)        { myEtherData.myJabbers = theData;}
    void SetCollisions(CT_SNMP_Counter32 theData)     { myEtherData.myCollisions = theData;}
    void SetPkts64(CT_SNMP_Counter32 theData)         { myPkts64Octets = theData;}
    void SetPkts65to127(CT_SNMP_Counter32 theData)    { myPkts65to127Octets = theData;}
    void SetPkts128to255(CT_SNMP_Counter32 theData)   { myPkts128to255Octets = theData;}
    void SetPkts256to511(CT_SNMP_Counter32 theData)   { myPkts256to511Octets = theData;}
    void SetPkts512to1023(CT_SNMP_Counter32 theData)  { myPkts512to1023Octets = theData;}
    void SetPkts1024to1518(CT_SNMP_Counter32 theData) { myPkts1024to1518Octets = theData;}
    void SetDroppedFrames(CT_SNMP_Counter32 theData)  { myDroppedFrames = theData; }
    void SetCreateTime(CT_SNMP_TimeTicks theData)     { myCreateTime = theData; }
 
    void ResetDropEvents()        { myEtherData.myDropEvents = 0;}
    void ResetOctets()            { myEtherData.myOctets = 0;}
    void ResetPkts()              { myEtherData.myPkts = 0;}
    void ResetBroadcastPkts()     { myEtherData.myBroadcastPkts = 0;}
    void ResetMulticastPkts()     { myEtherData.myMulticastPkts = 0;}
    void ResetCRCAlignErrors()    { myEtherData.myCRCAlignErrors = 0;}
    void ResetUndersizePkts()     { myEtherData.myUndersizePkts = 0;}
    void ResetOversizePkts()      { myEtherData.myOversizePkts = 0;}
    void ResetFragments()         { myEtherData.myFragments = 0;}
    void ResetJabbers()           { myEtherData.myJabbers = 0;}
    void ResetCollisions()        { myEtherData.myCollisions = 0;}
    void ResetPkts64()            { myPkts64Octets = 0;}
    void ResetPkts65to127()       { myPkts65to127Octets = 0;}
    void ResetPkts128to255()      { myPkts128to255Octets = 0;}
    void ResetPkts256to511()      { myPkts256to511Octets = 0;}
    void ResetPkts512to1023()     { myPkts512to1023Octets = 0;}
    void ResetPkts1024to1518()    { myPkts1024to1518Octets = 0;}
    void ResetDroppedFrames()     { myDroppedFrames = 0; }
    void ResetCreateTime()        { myCreateTime = 0; }
    void ResetAll();

    void IncDropEvents(CT_SNMP_Counter32 theInc)     { myEtherData.myDropEvents += theInc; }
    void IncOctets(CT_SNMP_Counter32 theInc)         { myEtherData.myOctets += theInc; }
    void IncPkts(CT_SNMP_Counter32 theInc)           { myEtherData.myPkts += theInc; }
    void IncBroadcastPkts(CT_SNMP_Counter32 theInc)  { myEtherData.myBroadcastPkts += theInc; }
    void IncMulticastPkts(CT_SNMP_Counter32 theInc)  { myEtherData.myMulticastPkts += theInc; }
    void IncCRCAlignErrors(CT_SNMP_Counter32 theInc) { myEtherData.myCRCAlignErrors += theInc; }
    void IncUndersizePkts(CT_SNMP_Counter32 theInc)  { myEtherData.myUndersizePkts += theInc; }
    void IncOversizePkts(CT_SNMP_Counter32 theInc)   { myEtherData.myOversizePkts += theInc; }
    void IncFragments(CT_SNMP_Counter32 theInc)      { myEtherData.myFragments += theInc; }
    void IncJabbers(CT_SNMP_Counter32 theInc)        { myEtherData.myJabbers += theInc; }
    void IncCollisions(CT_SNMP_Counter32 theInc)     { myEtherData.myCollisions += theInc; }
    void IncPkts64(CT_SNMP_Counter32 theData)        { myPkts64Octets += theData;}
    void IncPkts65to127(CT_SNMP_Counter32 theData)   { myPkts65to127Octets += theData;}
    void IncPkts128to255(CT_SNMP_Counter32 theData)  { myPkts128to255Octets += theData;}
    void IncPkts256to511(CT_SNMP_Counter32 theData)  { myPkts256to511Octets += theData;}
    void IncPkts512to1023(CT_SNMP_Counter32 theData) { myPkts512to1023Octets += theData;}
    void IncPkts1024to1518(CT_SNMP_Counter32 theData){ myPkts1024to1518Octets += theData;}
    void IncDroppedFrames(CT_SNMP_Counter32 theData) { myDroppedFrames += theData; }
    void IncCreateTime(CT_SNMP_Counter32 theData) { myCreateTime += theData; }

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);

private:
    CT_SNMP_RmonEtherData    myEtherData;
    CT_SNMP_Counter32        myPkts64Octets;
    CT_SNMP_Counter32        myPkts65to127Octets;
    CT_SNMP_Counter32        myPkts128to255Octets;
    CT_SNMP_Counter32        myPkts256to511Octets;
    CT_SNMP_Counter32        myPkts512to1023Octets;
    CT_SNMP_Counter32        myPkts1024to1518Octets;
    CT_SNMP_Counter32        myDroppedFrames;
    CT_SNMP_TimeStamp        myCreateTime;
};

#endif //SNMP_RMONETHERSTATSDATA_H

