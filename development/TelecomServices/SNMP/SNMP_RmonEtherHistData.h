/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_RMONETHERHISTDATA_H
#define SNMP_RMONETHERHISTDATA_H

#include <SNMP/SNMP_RmonData.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ErrorService/FC_Error.h>

using namespace std;

class SNMP_RmonEtherHistSample 
{
public:
    SNMP_RmonEtherHistSample();
    SNMP_RmonEtherHistSample(SNMP_RmonEtherHistSample& theCopy);
    virtual ~SNMP_RmonEtherHistSample();

    CT_SNMP_Integer32 GetSampleIndex()    {return mySampleIndex; }
    CT_SNMP_TimeTicks GetIntervalStart()  {return myIntervalStart; }
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
    CT_SNMP_Integer32 GetUtilization()    {return myUtilization; }

    void SetSampleIndex(CT_SNMP_Integer32 theData)    { mySampleIndex = theData; }
    void SetIntervalStart(CT_SNMP_TimeTicks theData)  { myIntervalStart = theData; }
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
    void SetUtilization(CT_SNMP_Integer32 theUtil)    { myUtilization = theUtil; }

    SNMP_RmonEtherHistSample& operator=(SNMP_RmonEtherHistSample& theRhs);
    bool operator==(SNMP_RmonEtherHistSample& theRhs);
    FC_Stream& ReadObjectBinary(FC_Stream& theStream);
    FC_Stream& WriteObjectBinary(FC_Stream& theStream);
    istream& ReadObject (istream& theStream);
    ostream& WriteObject (ostream& theStream);

    void ResetSampleIndex()       { mySampleIndex = CT_SNMP_DEFAULT_HIST_SAMPLE_INDEX; }
    void ResetIntervalStart()     { myIntervalStart = CT_SNMP_DEFAULT_HIST_IVAL_START; }
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
    void ResetUtilization()       { myUtilization = 0; }
    virtual void ResetAll();

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
private:
    CT_SNMP_Integer32        mySampleIndex;
    CT_SNMP_TimeTicks        myIntervalStart;
    CT_SNMP_Integer32        myUtilization;
    CT_SNMP_RmonEtherData    myEtherData;
};


class SNMP_BbRmonEtherHistStorage : public SNMP_BbRmonData
{
public:
    enum 
    {
        MAX_SAMPLES = 100
    };

    SNMP_BbRmonEtherHistStorage();
    virtual ~SNMP_BbRmonEtherHistStorage();

    CT_SNMP_Integer32 GetBucketsGranted() {return myBucketsGranted; }
    CT_SNMP_Integer32 GetInterval()       { return myInterval; }
    SNMP_RmonEtherHistSample& GetSample(CT_SNMP_Integer32 theSampleIndex) throw (FC_RuntimeError);
    SNMP_RmonEtherHistSample& GetFirstSampleToFill();
    SNMP_RmonEtherHistSample& GetNextSampleToFill();
    SNMP_RmonEtherHistSample& GetCurrentSample();
    SNMP_RmonEtherHistSample& GetLeastRecentSample();

    SNMP_RmonEtherHistSample& GetSampleBuffer(CT_SNMP_Integer32 theIndex); 

    void SetInterval(CT_SNMP_Integer32 theInterval)       { myInterval = theInterval; }
    void SetBucketsRequested(CT_SNMP_Integer32 theData);

    void ResetInterval()          { myInterval = CT_SNMP_DEFAULT_HIST_INTERVAL; }
    void ResetBucketsGranted()    { myBucketsGranted = 0; }
    virtual void ResetAll();

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);
    void SetBucketsGranted(CT_SNMP_Integer32 theData) { myBucketsGranted = theData; }
private:
    CT_SNMP_Integer32        myBucketsGranted;
    CT_SNMP_Integer32        myInterval;
    SNMP_RmonEtherHistSample mySamples[MAX_SAMPLES];
    int                      myCurrSample;
    int                      myCurrSampleIndex;
};


class SNMP_BbRmonEtherHistData : public SNMP_BbRmonData
{
public:
    SNMP_BbRmonEtherHistData();
    virtual ~SNMP_BbRmonEtherHistData();

    CT_SNMP_Integer32 GetBucketsGranted() {return myBucketsGranted; }
    CT_SNMP_Integer32 GetSampleIndex()    {return mySample.GetSampleIndex(); }
    CT_SNMP_Integer32 GetIntervalStart()  {return mySample.GetIntervalStart(); }
    CT_SNMP_Counter32 GetDropEvents()     {return mySample.GetDropEvents();}
    CT_SNMP_Counter32 GetOctets()         {return mySample.GetOctets();}
    CT_SNMP_Counter32 GetPkts()           {return mySample.GetPkts();}
    CT_SNMP_Counter32 GetBroadcastPkts()  {return mySample.GetBroadcastPkts();}
    CT_SNMP_Counter32 GetMulticastPkts()  {return mySample.GetMulticastPkts();}
    CT_SNMP_Counter32 GetCRCAlignErrors() {return mySample.GetCRCAlignErrors();}
    CT_SNMP_Counter32 GetUndersizePkts()  {return mySample.GetUndersizePkts();}
    CT_SNMP_Counter32 GetOversizePkts()   {return mySample.GetOversizePkts();}
    CT_SNMP_Counter32 GetFragments()      {return mySample.GetFragments();}
    CT_SNMP_Counter32 GetJabbers()        {return mySample.GetJabbers();}
    CT_SNMP_Counter32 GetCollisions()     {return mySample.GetCollisions();}
    CT_SNMP_Integer32 GetUtilization()    {return mySample.GetUtilization(); }
    SNMP_RmonEtherHistSample& GetData()   {return mySample; }

    void SetBucketsGranted(CT_SNMP_Integer32 theData) { myBucketsGranted = theData; }
    void SetSampleIndex(CT_SNMP_Integer32 theData)    { mySample.SetSampleIndex(theData); }
    void SetIntervalStart(CT_SNMP_Integer32 theData)  { mySample.SetIntervalStart(theData); }
    void SetDropEvents(CT_SNMP_Counter32 theData)     { mySample.SetDropEvents(theData);}
    void SetOctets(CT_SNMP_Counter32 theData)         { mySample.SetOctets(theData);}
    void SetPkts(CT_SNMP_Counter32 theData)           { mySample.SetPkts(theData);}
    void SetBroadcastPkts(CT_SNMP_Counter32 theData)  { mySample.SetBroadcastPkts(theData);}
    void SetMulticastPkts(CT_SNMP_Counter32 theData)  { mySample.SetMulticastPkts(theData);}
    void SetCRCAlignErrors(CT_SNMP_Counter32 theData) { mySample.SetCRCAlignErrors(theData);}
    void SetUndersizePkts(CT_SNMP_Counter32 theData)  { mySample.SetUndersizePkts(theData);}
    void SetOversizePkts(CT_SNMP_Counter32 theData)   { mySample.SetOversizePkts(theData);}
    void SetFragments(CT_SNMP_Counter32 theData)      { mySample.SetFragments(theData);}
    void SetJabbers(CT_SNMP_Counter32 theData)        { mySample.SetJabbers(theData);}
    void SetCollisions(CT_SNMP_Counter32 theData)     { mySample.SetCollisions(theData);}
    void SetUtilization(CT_SNMP_Integer32 theUtil)    { mySample.SetUtilization(theUtil); }
    void SetData(SNMP_RmonEtherHistSample& theSample) { mySample = theSample; }

    void ResetBucketsGranted()    { myBucketsGranted = 0; }
    void ResetSampleIndex()       { mySample.ResetSampleIndex(); }
    void ResetIntervalStart()     { mySample.ResetIntervalStart(); }
    void ResetDropEvents()        { mySample.ResetDropEvents();}
    void ResetOctets()            { mySample.ResetOctets();}
    void ResetPkts()              { mySample.ResetPkts();}
    void ResetBroadcastPkts()     { mySample.ResetBroadcastPkts();}
    void ResetMulticastPkts()     { mySample.ResetMulticastPkts();}
    void ResetCRCAlignErrors()    { mySample.ResetCRCAlignErrors();}
    void ResetUndersizePkts()     { mySample.ResetUndersizePkts();}
    void ResetOversizePkts()      { mySample.ResetOversizePkts();}
    void ResetFragments()         { mySample.ResetFragments();}
    void ResetJabbers()           { mySample.ResetJabbers();}
    void ResetCollisions()        { mySample.ResetCollisions();}
    void ResetUtilization()       { mySample.ResetUtilization(); }
    virtual void ResetAll();

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);
private:
    CT_SNMP_Integer32        myBucketsGranted;
    SNMP_RmonEtherHistSample mySample;
};

#endif //SNMP_RMONETHERHISTDATA_H

