// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OduStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>

MON_OduStatus::MON_OduStatus(uint32 theIndex):
    MON_Status(theIndex),
    myTraceInUse(false),
    myTraceMessagePtr(NULL),
    myRxPayloadType(0),
    myActTribSize(CT_TEL_TS_UNKNOWN),
    myAutoFallbackStatus(false),
    myServerSignalFail(false),
    myServerSignalDegrade(false),
    myPathDelay(0),
    myPrbsRxMostSignifCount(0),
    myPrbsRxLeastSignifCount(0),
    myPrbsRxTimeInterval(0),
    myPrbsRxLosync(CT_TEL_PRBS_OUTSYNC),
    myPrbsRxFirstSyncLosyncCount(0),
    myPrbsRxFirstSync(false)
{
}

MON_OduStatus::~MON_OduStatus()
{
}

void MON_OduStatus::GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const
{
    switch (theStatus)
    {
    case 0:
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuStatus: unsupported status");
    }
}

bool MON_OduStatus::SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel)
{
    //Return true if changed
    bool hasChanged = false;
    switch (theStatus)
    {
    case 0:
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuStatus: unsupported status");
    }

    return hasChanged;
}

void MON_OduStatus::Reset()
{
    MON_Object::Reset();
    // Note: DeleteTraceMessage() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //myTraceMessagePtr   = NULL;
    DeleteTraceMessage();
    myRxPayloadType = 0;
    myActTribSize = CT_TEL_TS_UNKNOWN;
    myServerSignalFail = false;
    myPathDelay = 0;

    myPrbsRxMostSignifCount  = 0;
    myPrbsRxLeastSignifCount = 0;
    myPrbsRxTimeInterval     = 0;
    myPrbsRxLosync           = CT_TEL_PRBS_OUTSYNC;
    myPrbsRxFirstSyncLosyncCount = 0;
    myPrbsRxFirstSync        = false;
}


bool MON_OduStatus::SetTraceMessage(const CT_G709Trace theTrace)
{
    // Create as new trace if the pointer is NULL
    if (myTraceMessagePtr == NULL) 
    {
        myTraceMessagePtr = new CT_G709Trace(); 
    }
    myTraceInUse = true;

    // keep track of any changes
    if (*myTraceMessagePtr == theTrace)
        return false; // trace has not changed
    else
    {
        *myTraceMessagePtr = theTrace;
        return true; // trace has changed
    }
}

void MON_OduStatus::DeleteTraceMessage()
{
    if (myTraceMessagePtr != NULL) 
    {
        delete myTraceMessagePtr;
        myTraceMessagePtr = NULL;
    }

    myTraceInUse = false;
}

CT_G709Trace & MON_OduStatus::GetTraceMessage() const
{
    if (myTraceMessagePtr != NULL) 
    {
        return(*myTraceMessagePtr);
    }
    else
    {
        return(CT_G709DefaultTrace::GetInstance());
    }
}


const uint8 MON_OduStatus::GetRxPayloadType() const
{
    return myRxPayloadType;
}

bool MON_OduStatus::SetRxPayloadType(const uint8 theRxPayloadType)
{
    // keep track of any changes
    if (myRxPayloadType == theRxPayloadType)
        return false; // trace has not changed
    else
    {
        myRxPayloadType = theRxPayloadType;
        return true;// trace has changed
    }   
}

const CT_TEL_TS_SIZE MON_OduStatus::GetActTribSize() const
{
    return (CT_TEL_TS_SIZE)myActTribSize;
}

bool MON_OduStatus::SetActTribSize(const CT_TEL_TS_SIZE theActTribSize)
{
    // keep track of any changes
    if (myActTribSize == theActTribSize)
        return false; // trib size has not changed
    else
    {
        myActTribSize = theActTribSize;
        return true; // trib size has changed
    }   
}

const bool MON_OduStatus::GetAutoFallbackStatus() const
{
    return myAutoFallbackStatus;
}

bool MON_OduStatus::SetAutoFallbackStatus(const bool theAutoFallbackStatus)
{
    // keep track of any changes
    if (myAutoFallbackStatus == theAutoFallbackStatus)
        return false; // fallabck status has not changed
    else
    {
        myAutoFallbackStatus = theAutoFallbackStatus;
        return true;// fallabck status has changed
    }
}

const bool MON_OduStatus::GetServerSignalFail() const
{
    return myServerSignalFail;
}

bool MON_OduStatus::SetServerSignalFail(const bool theServerSignalFail)
{
    // keep track of any changes
    if (myServerSignalFail == theServerSignalFail)
        return false; // trace has not changed
    else
    {
        myServerSignalFail = theServerSignalFail;
        return true;// trace has changed
    }
}

const bool MON_OduStatus::GetServerSignalDegrade() const
{
    return myServerSignalDegrade;
}

bool MON_OduStatus::SetServerSignalDegrade(const bool theServerSignalDegrade)
{
    // keep track of any changes
    if (myServerSignalDegrade == theServerSignalDegrade)
        return false; // trace has not changed
    else
    {
        myServerSignalDegrade = theServerSignalDegrade;
        return true;// trace has changed
    }
}

bool MON_OduStatus::SetPathDelay(const int32 thePathDelay)
{
    // keep track of any changes
    if (myPathDelay == thePathDelay)
        return false; // trace has not changed
    else
    {
        myPathDelay = thePathDelay;
        return true;// trace has changed
    }
}

int32 MON_OduStatus::GetPathDelay() const
{
    return myPathDelay;
}


uint32 MON_OduStatus::GetPrbsRxMostSignifCount() const 
{
    return myPrbsRxMostSignifCount;
}

bool MON_OduStatus::SetPrbsRxMostSignifCount(uint32 thePrbsRxMostSignifCount) 
{
    bool hasChanged = false;
    if (myPrbsRxMostSignifCount != thePrbsRxMostSignifCount)
    {
        myPrbsRxMostSignifCount = thePrbsRxMostSignifCount;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_OduStatus::GetPrbsRxLeastSignifCount() const 
{
    return myPrbsRxLeastSignifCount;
}

bool MON_OduStatus::SetPrbsRxLeastSignifCount(uint32 thePrbsRxLeastSignifCount) 
{
    bool hasChanged = false;
    if (myPrbsRxLeastSignifCount != thePrbsRxLeastSignifCount)
    {
        myPrbsRxLeastSignifCount = thePrbsRxLeastSignifCount;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_OduStatus::GetPrbsRxTimeInterval() const 
{
    return myPrbsRxTimeInterval;
}

bool MON_OduStatus::SetPrbsRxTimeInterval(uint32 thePrbsRxTimeInterval) 
{
    bool hasChanged = false;
    if (myPrbsRxTimeInterval != thePrbsRxTimeInterval)
    {
        myPrbsRxTimeInterval = thePrbsRxTimeInterval;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_PrbsSyncStatus MON_OduStatus::GetPrbsRxLosync() const 
{
    return myPrbsRxLosync;
}

bool MON_OduStatus::SetPrbsRxLosync(CT_TEL_PrbsSyncStatus thePrbsRxLosync) 
{
    bool hasChanged = false;
    if (myPrbsRxLosync != thePrbsRxLosync)
    {
        myPrbsRxLosync = thePrbsRxLosync;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_OduStatus::GetPrbsRxFirstSyncLosyncCount() const 
{
    return myPrbsRxFirstSyncLosyncCount;
}

bool MON_OduStatus::SetPrbsRxFirstSyncLosyncCount(uint32 thePrbsRxFirstSyncLosyncCount) 
{
    bool hasChanged = false;
    if (myPrbsRxFirstSyncLosyncCount != thePrbsRxFirstSyncLosyncCount)
    {
        myPrbsRxFirstSyncLosyncCount = thePrbsRxFirstSyncLosyncCount;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_OduStatus::GetPrbsRxFirstSync() const 
{
    return myPrbsRxFirstSync;
}

bool MON_OduStatus::SetPrbsRxFirstSync(bool thePrbsRxFirstSync) 
{
    bool hasChanged = false;
    if (myPrbsRxFirstSync != thePrbsRxFirstSync)
    {
        myPrbsRxFirstSync = thePrbsRxFirstSync;
        hasChanged = true;
    }

    return hasChanged;
}

// For persitance and region transfer
FC_Stream& MON_OduStatus::WriteObjectBinary( FC_Stream& theStream )
{
    uint8 tmpPrbsRxLosync = myPrbsRxLosync;

    MON_Object::WriteObjectBinary(theStream);

    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        theStream    << aTrace;
    }

    theStream << myServerSignalFail;
    theStream << myServerSignalDegrade;
    theStream << myRxPayloadType;

    uint8 aActTribSize = (uint8) myActTribSize;
    theStream   << aActTribSize;
    theStream << myAutoFallbackStatus;
    // -- Used only locally -- theStream << myPathDelay;

    theStream << myPrbsRxMostSignifCount;
    theStream << myPrbsRxLeastSignifCount;
    theStream << myPrbsRxTimeInterval;
    theStream << tmpPrbsRxLosync;
    // -- Used only locally -- theStream << myPrbsRxLosyncCount;
    // -- Used only locally -- theStream << myPrbsRxFirstSync;
    return theStream;
}

// For persitance and region transfer
FC_Stream& MON_OduStatus::ReadObjectBinary( FC_Stream& theStream )
{
    uint8 tmpPrbsRxLosync;

    MON_Object::ReadObjectBinary(theStream);

    theStream   >> myTraceInUse;
    if (myTraceInUse) 
    {
        // CT_G709Trace aTrace();
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream    >> aTrace;
        SetTraceMessage(aTrace);
    }
    else
    {
        DeleteTraceMessage();
    }

    theStream >> myServerSignalFail;
    theStream >> myServerSignalDegrade;
    theStream >> myRxPayloadType;

    uint8 aActTribSize;
    theStream   >> aActTribSize;
    myActTribSize = (CT_TEL_TS_SIZE) aActTribSize;
    theStream >> myAutoFallbackStatus;
    // -- Used only locally -- theStream >> myPathDelay;

    theStream >> myPrbsRxMostSignifCount;
    theStream >> myPrbsRxLeastSignifCount;
    theStream >> myPrbsRxTimeInterval;
    theStream >> tmpPrbsRxLosync;
    // -- Used only locally -- theStream >> myPrbsRxLosyncCount;
    // -- Used only locally -- theStream >> myPrbsRxFirstSync;

    myPrbsRxLosync = (CT_TEL_PrbsSyncStatus)(tmpPrbsRxLosync);

    return theStream;
}


// For Display
ostream& MON_OduStatus::WriteObject( ostream& theStream )
{
    uint8 tmpPrbsRxLosync = myPrbsRxLosync;

    MON_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        theStream    << FC_InsertVar(aTrace);
    }

    theStream   << FC_InsertVar(myServerSignalFail);
    theStream   << FC_InsertVar(myServerSignalDegrade);
    theStream   << FC_InsertVar(myRxPayloadType);

    uint8 aActTribSize = (uint8)myActTribSize;
    theStream   << FC_InsertVar(aActTribSize);
    theStream   << FC_InsertVar(myAutoFallbackStatus);
    theStream   << FC_InsertVar(myPathDelay);

    theStream << FC_InsertVar(myPrbsRxMostSignifCount);
    theStream << FC_InsertVar(myPrbsRxLeastSignifCount);
    theStream << FC_InsertVar(myPrbsRxTimeInterval);
    theStream << FC_InsertVar(tmpPrbsRxLosync);
    theStream << FC_InsertVar(myPrbsRxFirstSyncLosyncCount);
    theStream << FC_InsertVar(myPrbsRxFirstSync);

    return theStream;
}

// For Display
istream& MON_OduStatus::ReadObject( istream& theStream )
{
    uint8 tmpPrbsRxLosync;

    MON_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream   >> FC_ExtractVar(aTrace);
        SetTraceMessage(aTrace);
    }
    else
    {
        DeleteTraceMessage();
    }

    theStream   >> FC_ExtractVar(myServerSignalFail);
    theStream   >> FC_ExtractVar(myServerSignalDegrade);
    theStream   >> FC_ExtractVar(myRxPayloadType);

    uint8 aActTribSize;
    theStream   >> FC_ExtractVar(aActTribSize);
    myActTribSize = (CT_TEL_TS_SIZE)aActTribSize;
    theStream   >> FC_ExtractVar(myAutoFallbackStatus);
    theStream   >> FC_ExtractVar(myPathDelay); 
    
    theStream >> FC_ExtractVar(myPrbsRxMostSignifCount);
    theStream >> FC_ExtractVar(myPrbsRxLeastSignifCount);
    theStream >> FC_ExtractVar(myPrbsRxTimeInterval);
    theStream >> FC_ExtractVar(tmpPrbsRxLosync);
    theStream >> FC_ExtractVar(myPrbsRxFirstSyncLosyncCount);
    theStream >> FC_ExtractVar(myPrbsRxFirstSync);

    myPrbsRxLosync = (CT_TEL_PrbsSyncStatus)(tmpPrbsRxLosync);

    return theStream;
}

void MON_OduStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "ODU     - Server Signal Fail                = " << DISPLAY_BOOL(myServerSignalFail) << endl;
    theStream   << "ODU     - Server Signal Degrade             = " << DISPLAY_BOOL(myServerSignalDegrade) << endl;
    theStream   << "ODU     - Received Payload Type             = 0x" << hex << (uint32)myRxPayloadType << endl;
    theStream   << "ODU     - Actual Trib Slot Size             = " << DISPLAY_TS_SIZE(myActTribSize) << endl;
    theStream   << "ODU     - AutoFallback Status               = " << DISPLAY_BOOL(myAutoFallbackStatus) << endl;
    theStream   << "ODU     - Path Delay                        = " << dec << myPathDelay << endl;
    theStream   << "ODU     - PRBS Rx Errors Most Signif Count  = " << myPrbsRxMostSignifCount << endl;
    theStream   << "ODU     - PRBS Rx Errors Least Signif Count = " << myPrbsRxLeastSignifCount << endl;
    theStream   << "ODU     - PRBS Rx Errors Time Interval (ms) = " << myPrbsRxTimeInterval << endl;
    theStream   << "ODU     - PRBS Rx Losync                    = " << DISPLAY_PRBS_SYNC_STATUS(myPrbsRxLosync) << endl;
    theStream   << "ODU     - PRBS Rx FirstSyncLosyncCount      = " << myPrbsRxFirstSyncLosyncCount << endl;
    theStream   << "ODU     - PRBS Rx First Sync                = " << DISPLAY_BOOL(myPrbsRxFirstSync) << endl;
    theStream   << "ODU     - Trace In Use                      = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "ODU     - Received Trace                    = " ;
    if (myTraceMessagePtr != NULL) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        aTrace.Display(theStream);
    }
    else
    {
        theStream   << endl;
    }
    
}
