// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TcmStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>

MON_TcmStatus::MON_TcmStatus(uint32 theIndex):
    MON_Status(theIndex),
    myTraceInUse(false),
    myTraceMessagePtr(NULL),
    myServerSignalFail(false),
    myServerSignalDegrade(false),
    myTcmDelay(0)
{
}

MON_TcmStatus::~MON_TcmStatus()
{
}

void MON_TcmStatus::Reset()
{
    MON_Object::Reset();   

    // Note: DeleteTraceMessage() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //myTraceMessagePtr   = NULL;
    DeleteTraceMessage();
    myServerSignalFail = false;
    myServerSignalDegrade = false;
    myTcmDelay = 0;
}


void MON_TcmStatus::GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const
{
    switch (theStatus)
    {
    case 0:
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmStatus: unsupported status");
    }
}

bool MON_TcmStatus::SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel)
{
    //Return true if changed
    bool hasChanged = false;
    switch (theStatus)
    {
    case 0:
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_TcmStatus: unsupported status");
    }

    return hasChanged;
}

bool MON_TcmStatus::SetTraceMessage(const CT_G709Trace theTrace)
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

void MON_TcmStatus::DeleteTraceMessage()
{
    if (myTraceMessagePtr != NULL) 
    {
        delete myTraceMessagePtr;
        myTraceMessagePtr = NULL;
    }

    myTraceInUse = false;
}

CT_G709Trace & MON_TcmStatus::GetTraceMessage() const
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


bool MON_TcmStatus::SetServerSignalFail(const bool theServerSignalFail)
{
    // keep track of any changes
    if (myServerSignalFail == theServerSignalFail)
        return false; // has not changed
    else
    {
        myServerSignalFail = theServerSignalFail;
        return true; //  has changed
    }
}

bool MON_TcmStatus::SetServerSignalDegrade(const bool theServerSignalDegrade)
{
    // keep track of any changes
    if (myServerSignalDegrade == theServerSignalDegrade)
        return false; // has not changed
    else
    {
        myServerSignalDegrade = theServerSignalDegrade;
        return true;  // has changed
    }
}

bool MON_TcmStatus::SetTcmDelay(const int32 theTcmDelay)
{
    // keep track of any changes
    if (myTcmDelay == theTcmDelay)
        return false; // trace has not changed
    else
    {
        myTcmDelay = theTcmDelay;
        return true;// trace has changed
    }
}

int32 MON_TcmStatus::GetTcmDelay() const
{
    return myTcmDelay;
}

// For persitance and region transfer
FC_Stream& MON_TcmStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);

    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        theStream    << aTrace;
    }

    theStream << myServerSignalFail;
    theStream << myServerSignalDegrade;
    // -- Used only locally -- theStream << myTcmDelay;

    return theStream;
}

// For persitance and region transfer
FC_Stream& MON_TcmStatus::ReadObjectBinary( FC_Stream& theStream )
{
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
    // -- Used only locally -- theStream >> myTcmDelay;

    return theStream;
}

// For Display
ostream& MON_TcmStatus::WriteObject( ostream& theStream )
{
    MON_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        theStream    << FC_InsertVar(aTrace);
    }

    theStream   << FC_InsertVar(myServerSignalFail);
    theStream   << FC_InsertVar(myServerSignalDegrade);
    theStream   << FC_InsertVar(myTcmDelay);

    return theStream;
}

// For Display
istream& MON_TcmStatus::ReadObject( istream& theStream )
{
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
    theStream   >> FC_ExtractVar(myTcmDelay);    

    return theStream;
}

void MON_TcmStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "TCM     - Server Signal Fail                = " << DISPLAY_BOOL(myServerSignalFail) << endl;
    theStream   << "TCM     - Server Signal Degrade             = " << DISPLAY_BOOL(myServerSignalDegrade) << endl;
    theStream   << "TCM     - TCM Delay                         = " << dec << myTcmDelay << endl;
    theStream   << "TCM     - Trace In Use                      = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "TCM     - Received Trace                    = " ;
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
