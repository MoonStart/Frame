/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#include <SNMP/SNMP_RmonEtherHistData.h>
#include <BaseClass/FC_TextStream.h>

// --------------------------------------------------------------------------
//  SNMP_RmonEtherHistSample member function implementation
// --------------------------------------------------------------------------
SNMP_RmonEtherHistSample::SNMP_RmonEtherHistSample()
{
    ResetAll();
}

SNMP_RmonEtherHistSample::SNMP_RmonEtherHistSample(SNMP_RmonEtherHistSample& theCopy)
{
    mySampleIndex = theCopy.mySampleIndex;
    myIntervalStart = theCopy.myIntervalStart;
    myEtherData.myDropEvents = theCopy.myEtherData.myDropEvents;
    myEtherData.myOctets = theCopy.myEtherData.myOctets;
    myEtherData.myPkts = theCopy.myEtherData.myPkts;
    myEtherData.myBroadcastPkts = theCopy.myEtherData.myBroadcastPkts;
    myEtherData.myMulticastPkts = theCopy.myEtherData.myMulticastPkts;
    myEtherData.myCRCAlignErrors = theCopy.myEtherData.myCRCAlignErrors;
    myEtherData.myUndersizePkts = theCopy.myEtherData.myUndersizePkts;
    myEtherData.myOversizePkts = theCopy.myEtherData.myOversizePkts;
    myEtherData.myFragments = theCopy.myEtherData.myFragments;
    myEtherData.myJabbers = theCopy.myEtherData.myJabbers;
    myEtherData.myCollisions = theCopy.myEtherData.myCollisions;
    myUtilization = theCopy.myUtilization;
}

SNMP_RmonEtherHistSample::~SNMP_RmonEtherHistSample()
{
}

SNMP_RmonEtherHistSample& SNMP_RmonEtherHistSample::operator=(SNMP_RmonEtherHistSample& theRhs)
{
    mySampleIndex = theRhs.mySampleIndex;
    myIntervalStart = theRhs.myIntervalStart;
    myEtherData.myDropEvents = theRhs.myEtherData.myDropEvents;
    myEtherData.myOctets = theRhs.myEtherData.myOctets;
    myEtherData.myPkts = theRhs.myEtherData.myPkts;
    myEtherData.myBroadcastPkts = theRhs.myEtherData.myBroadcastPkts;
    myEtherData.myMulticastPkts = theRhs.myEtherData.myMulticastPkts;
    myEtherData.myCRCAlignErrors = theRhs.myEtherData.myCRCAlignErrors;
    myEtherData.myUndersizePkts = theRhs.myEtherData.myUndersizePkts;
    myEtherData.myOversizePkts = theRhs.myEtherData.myOversizePkts;
    myEtherData.myFragments = theRhs.myEtherData.myFragments;
    myEtherData.myJabbers = theRhs.myEtherData.myJabbers;
    myEtherData.myCollisions = theRhs.myEtherData.myCollisions;
    myUtilization = theRhs.myUtilization;
    return *this;
}

bool SNMP_RmonEtherHistSample::operator==(SNMP_RmonEtherHistSample& theRhs) 
{
    if (
        (mySampleIndex == theRhs.mySampleIndex) &&
        (myIntervalStart == theRhs.myIntervalStart) &&
        (myEtherData.myDropEvents == theRhs.myEtherData.myDropEvents) &&
        (myEtherData.myOctets == theRhs.myEtherData.myOctets) &&
        (myEtherData.myPkts == theRhs.myEtherData.myPkts) &&
        (myEtherData.myBroadcastPkts == theRhs.myEtherData.myBroadcastPkts) &&
        (myEtherData.myMulticastPkts == theRhs.myEtherData.myMulticastPkts) &&
        (myEtherData.myCRCAlignErrors == theRhs.myEtherData.myCRCAlignErrors) &&
        (myEtherData.myUndersizePkts == theRhs.myEtherData.myUndersizePkts) &&
        (myEtherData.myOversizePkts == theRhs.myEtherData.myOversizePkts) &&
        (myEtherData.myFragments == theRhs.myEtherData.myFragments) &&
        (myEtherData.myJabbers == theRhs.myEtherData.myJabbers) &&
        (myEtherData.myCollisions == theRhs.myEtherData.myCollisions) &&
        (myUtilization == theRhs.myUtilization)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

FC_Stream& SNMP_RmonEtherHistSample::ReadObjectBinary (FC_Stream& theStream)
{
    theStream >> mySampleIndex;
    theStream >> myIntervalStart;
    theStream >> myUtilization;
    theStream >> myEtherData.myDropEvents;
    theStream >> myEtherData.myOctets;
    theStream >> myEtherData.myPkts;
    theStream >> myEtherData.myBroadcastPkts;
    theStream >> myEtherData.myMulticastPkts;
    theStream >> myEtherData.myCRCAlignErrors;
    theStream >> myEtherData.myUndersizePkts;
    theStream >> myEtherData.myOversizePkts;
    theStream >> myEtherData.myFragments;
    theStream >> myEtherData.myJabbers;
    theStream >> myEtherData.myCollisions;

    return theStream;
}

FC_Stream& SNMP_RmonEtherHistSample::WriteObjectBinary (FC_Stream& theStream)
{
    theStream << mySampleIndex;
    theStream << myIntervalStart;
    theStream << myUtilization;
    theStream << myEtherData.myDropEvents;
    theStream << myEtherData.myOctets;
    theStream << myEtherData.myPkts;
    theStream << myEtherData.myBroadcastPkts;
    theStream << myEtherData.myMulticastPkts;
    theStream << myEtherData.myCRCAlignErrors;
    theStream << myEtherData.myUndersizePkts;
    theStream << myEtherData.myOversizePkts;
    theStream << myEtherData.myFragments;
    theStream << myEtherData.myJabbers;
    theStream << myEtherData.myCollisions;

    return theStream;
}

istream& SNMP_RmonEtherHistSample::ReadObject (istream& theStream)
{
    theStream >> FC_ExtractVar(mySampleIndex);
    theStream >> FC_ExtractVar(myIntervalStart);
    theStream >> FC_ExtractVar(myUtilization);
    theStream >> FC_ExtractVar(myEtherData.myDropEvents);
    theStream >> FC_ExtractVar(myEtherData.myOctets);
    theStream >> FC_ExtractVar(myEtherData.myPkts);
    theStream >> FC_ExtractVar(myEtherData.myBroadcastPkts);
    theStream >> FC_ExtractVar(myEtherData.myMulticastPkts);
    theStream >> FC_ExtractVar(myEtherData.myCRCAlignErrors);
    theStream >> FC_ExtractVar(myEtherData.myUndersizePkts);
    theStream >> FC_ExtractVar(myEtherData.myOversizePkts);
    theStream >> FC_ExtractVar(myEtherData.myFragments);
    theStream >> FC_ExtractVar(myEtherData.myJabbers);
    theStream >> FC_ExtractVar(myEtherData.myCollisions);

    return theStream;
}

ostream& SNMP_RmonEtherHistSample::WriteObject (ostream& theStream)
{
    theStream << FC_InsertVar(mySampleIndex);
    theStream << FC_InsertVar(myIntervalStart);
    theStream << FC_InsertVar(myUtilization);
    theStream << FC_InsertVar(myEtherData.myDropEvents);
    theStream << FC_InsertVar(myEtherData.myOctets);
    theStream << FC_InsertVar(myEtherData.myPkts);
    theStream << FC_InsertVar(myEtherData.myBroadcastPkts);
    theStream << FC_InsertVar(myEtherData.myMulticastPkts);
    theStream << FC_InsertVar(myEtherData.myCRCAlignErrors);
    theStream << FC_InsertVar(myEtherData.myUndersizePkts);
    theStream << FC_InsertVar(myEtherData.myOversizePkts);
    theStream << FC_InsertVar(myEtherData.myFragments);
    theStream << FC_InsertVar(myEtherData.myJabbers);
    theStream << FC_InsertVar(myEtherData.myCollisions);

    return theStream;
}

void SNMP_RmonEtherHistSample::ResetAll()
{
    ResetSampleIndex();
    ResetIntervalStart();
    ResetDropEvents();
    ResetOctets();
    ResetPkts();
    ResetBroadcastPkts();
    ResetMulticastPkts();
    ResetCRCAlignErrors();
    ResetUndersizePkts();
    ResetOversizePkts();
    ResetFragments();
    ResetJabbers();
    ResetCollisions();
    ResetUtilization();
}

// --------------------------------------------------------------------------
//  SNMP_BbRmonEtherHistData member function implementation
// --------------------------------------------------------------------------

SNMP_BbRmonEtherHistData::SNMP_BbRmonEtherHistData() :
SNMP_BbRmonData()
{
    ResetAll();
}

SNMP_BbRmonEtherHistData::~SNMP_BbRmonEtherHistData()
{
}

void SNMP_BbRmonEtherHistData::ResetAll()
{
    SNMP_BbRmonData::ResetAll();
    ResetBucketsGranted();
    mySample.ResetAll();
}

FC_Stream& SNMP_BbRmonEtherHistData::ReadObjectBinary (FC_Stream& theStream)
{
    SNMP_BbRmonData::ReadObjectBinary(theStream);
    theStream >> myBucketsGranted;
    mySample.ReadObjectBinary(theStream);

    return theStream;
}

FC_Stream& SNMP_BbRmonEtherHistData::WriteObjectBinary (FC_Stream& theStream)
{
    SNMP_BbRmonData::WriteObjectBinary(theStream);
    theStream << myBucketsGranted;
    mySample.WriteObjectBinary(theStream);

    return theStream;
}

istream& SNMP_BbRmonEtherHistData::ReadObject (istream& theStream)
{
    SNMP_BbRmonData::ReadObject(theStream);
    theStream >> FC_ExtractVar(myBucketsGranted);
    mySample.ReadObject(theStream);

    return theStream;
}

ostream& SNMP_BbRmonEtherHistData::WriteObject (ostream& theStream)
{
    SNMP_BbRmonData::WriteObject(theStream);
    theStream << FC_InsertVar(myBucketsGranted);
    mySample.WriteObject(theStream);

    return theStream;
}

// --------------------------------------------------------------------------
//  SNMP_BbbmonEtherHistStorage member function implementation
// --------------------------------------------------------------------------

SNMP_BbRmonEtherHistStorage::SNMP_BbRmonEtherHistStorage() :
SNMP_BbRmonData(),
myCurrSample(0),
myCurrSampleIndex(1),
myBucketsGranted(0),
myInterval(CT_SNMP_DEFAULT_HIST_INTERVAL)
{
    ResetAll();
}

SNMP_BbRmonEtherHistStorage::~SNMP_BbRmonEtherHistStorage()
{

}

void SNMP_BbRmonEtherHistStorage::ResetAll()
{
    int index;

    SNMP_BbRmonData::ResetAll();
    ResetBucketsGranted();
    ResetInterval();
    for (index = 0; index < MAX_SAMPLES; index++) 
    {
        mySamples[index].ResetAll();
    }
    myCurrSample = 0;
    myCurrSampleIndex = 1;
}


SNMP_RmonEtherHistSample& SNMP_BbRmonEtherHistStorage::GetSample(CT_SNMP_Integer32 theSampleIndex) 
throw (FC_RuntimeError)
{
    int index;
    SNMP_RmonEtherHistSample* samplePtr = 0;
    for (index = 0; index < myBucketsGranted; index++) 
    {
        if (mySamples[index].GetSampleIndex() == theSampleIndex) 
        {
            break;
        }
    }

    if (index == myBucketsGranted) 
    {
        //FC_THROW_ERROR(FC_RuntimeError, "RMON Ethernet history sample not found");
        FC_RuntimeError theError("RMON Ethernet history sample not found");
        throw theError;        
    }
    else
    {
        samplePtr = &(mySamples[index]);
    }
    return *samplePtr;
}


SNMP_RmonEtherHistSample& SNMP_BbRmonEtherHistStorage::GetSampleBuffer(CT_SNMP_Integer32 theIndex) 
{
    SNMP_RmonEtherHistSample* samplePtr = 0;
    if (theIndex < MAX_SAMPLES)
    {
        samplePtr = &(mySamples[theIndex]);
    }
    return *samplePtr;
}


SNMP_RmonEtherHistSample& SNMP_BbRmonEtherHistStorage::GetFirstSampleToFill()
{
    myCurrSample = 0;
    myCurrSampleIndex = 1;
    mySamples[myCurrSample].ResetAll();
    mySamples[myCurrSample].SetSampleIndex(myCurrSampleIndex);
    return mySamples[myCurrSample];
}

SNMP_RmonEtherHistSample& SNMP_BbRmonEtherHistStorage::GetNextSampleToFill()
{
    if (++myCurrSample == myBucketsGranted) 
    {
        myCurrSample = 0;
    }
    if (++myCurrSampleIndex > CT_SNMP_MAX_INTEGER32_VALUE) 
    {
        myCurrSampleIndex = 1;
    }
    mySamples[myCurrSample].ResetAll();
    mySamples[myCurrSample].SetSampleIndex(myCurrSampleIndex);
    return mySamples[myCurrSample];
}

SNMP_RmonEtherHistSample& SNMP_BbRmonEtherHistStorage::GetCurrentSample()
{
    return mySamples[myCurrSample];
}

SNMP_RmonEtherHistSample& SNMP_BbRmonEtherHistStorage::GetLeastRecentSample()
{
    int leastRecent = myCurrSample + 1;
    while (leastRecent != myCurrSample) 
    {
        if (leastRecent == myBucketsGranted) 
        {
            leastRecent = 0;
        }
        if (mySamples[leastRecent].GetSampleIndex() != CT_SNMP_DEFAULT_HIST_SAMPLE_INDEX) 
        {
            break;
        }
        else
        {
            ++leastRecent;
        }
    }
    return mySamples[leastRecent];
}

void SNMP_BbRmonEtherHistStorage::SetBucketsRequested(CT_SNMP_Integer32 theData)
{
    if (theData >= MAX_SAMPLES) 
    {
        SetBucketsGranted(static_cast<CT_SNMP_Integer32>(MAX_SAMPLES));
    }
    else
    {
        SetBucketsGranted(theData);
    }
}

FC_Stream& SNMP_BbRmonEtherHistStorage::ReadObjectBinary (FC_Stream& theStream)
{
    int index;

    SNMP_BbRmonData::ReadObjectBinary(theStream);
    theStream >> myBucketsGranted;

    for (index = 0; index < MAX_SAMPLES; index++) 
    {
        mySamples[index].ReadObjectBinary(theStream);
    }
    return theStream;
}

FC_Stream& SNMP_BbRmonEtherHistStorage::WriteObjectBinary (FC_Stream& theStream)
{
    int index;

    SNMP_BbRmonData::WriteObjectBinary(theStream);
    theStream << myBucketsGranted;

    for (index = 0; index < MAX_SAMPLES; index++) 
    {
        mySamples[index].WriteObjectBinary(theStream);
    }

    return theStream;
}

istream& SNMP_BbRmonEtherHistStorage::ReadObject (istream& theStream)
{
    int index;

    SNMP_BbRmonData::ReadObject(theStream);
    theStream >> FC_ExtractVar(myBucketsGranted);

    for (index = 0; index < MAX_SAMPLES; index++) 
    {
        mySamples[index].ReadObject(theStream);
    }

    return theStream;
}

ostream& SNMP_BbRmonEtherHistStorage::WriteObject (ostream& theStream)
{
    int index;
    SNMP_BbRmonData::WriteObject(theStream);

    theStream << FC_InsertVar(myBucketsGranted);
    for (index = 0; index < MAX_SAMPLES; index++) 
    {
        mySamples[index].WriteObject(theStream);
    }

    return theStream;
}

