// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtuStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>


MON_OtuStatus::MON_OtuStatus(uint32 theIndex):
    MON_Status(theIndex),
    myTraceInUse(false),
    myTraceMessagePtr(NULL),
    myBER()
{
}

MON_OtuStatus::~MON_OtuStatus(void )
{
}

void MON_OtuStatus::GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const
{
    switch (theStatus)
    {
    case 0:
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OtuStatus: unsupported status");
    }
}

bool MON_OtuStatus::SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel)
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

void MON_OtuStatus::Reset()
{
    MON_Object::Reset();
    // Note: DeleteTraceMessage() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //myTraceMessagePtr   = NULL;
    DeleteTraceMessage();
    myBER=CT_Float32();
}


bool MON_OtuStatus::SetTraceMessage(const CT_G709Trace& theTrace)
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

void MON_OtuStatus::DeleteTraceMessage()
{
    if (myTraceMessagePtr != NULL) 
    {
        delete myTraceMessagePtr;
        myTraceMessagePtr = NULL;
    }

    myTraceInUse = false;
}

CT_G709Trace & MON_OtuStatus::GetTraceMessage() const
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


const CT_Float32 MON_OtuStatus::GetBER() const
{
    return myBER;
}

bool MON_OtuStatus::SetBER(const CT_Float32& theBER)
{
    // keep track of any changes
    if (myBER == theBER)
        return false; // trace has not changed
    else
    {
        myBER = theBER;
        return true;// trace has changed
    }
}


CT_TEL_DispCompState MON_OtuStatus::GetDispCompState() const 
{
    return myDispCompState;
}

bool MON_OtuStatus::SetDispCompState(CT_TEL_DispCompState theDispCompState) 
{
    bool hasChanged = false;
    if (!(myDispCompState == theDispCompState))
    {
        myDispCompState = theDispCompState;
        hasChanged = true;
    }

    return hasChanged;
}


// For persitance and region transfer
FC_Stream& MON_OtuStatus::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);

    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        theStream    << aTrace;
    }

    //Agent does not need BER because PM is the only reader
    //theStream << myBER;

    //Agent does not need the Dispersion Compensation State (turned into defect for LED)
    //uint8 aDispCompState = (uint8) myDispCompState;
    //theStream   << aDispCompState;

    return theStream;
}


// For persitance and region transfer
FC_Stream& MON_OtuStatus::ReadObjectBinary(FC_Stream& theStream)
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

    //Agent does not need BER because PM is the only reader
    //theStream >> myBER;

    //Agent does not need the Dispersion Compensation State (turned into defect for LED)
    //uint8 aDispCompState;
    //theStream   >> aDispCompState;
    //myDispCompState = (CT_TEL_DispCompState) aDispCompState;

    return theStream;
}


// For Display
ostream& MON_OtuStatus::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetTraceMessage();
        theStream    << FC_InsertVar(aTrace);
    }

    theStream << FC_InsertVar(myBER);

    uint8 aDispCompState = (uint8) myDispCompState;
    theStream   << FC_InsertVar(aDispCompState);

    return theStream;
}

istream& MON_OtuStatus::ReadObject(istream& theStream)
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

    theStream >> FC_ExtractVar(myBER);

    uint8 aDispCompState;
    theStream   >> FC_ExtractVar(aDispCompState);
    myDispCompState = (CT_TEL_DispCompState) aDispCompState;

    return theStream;
}


void MON_OtuStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "OTU     - BER                               = " << myBER.DisplayFloat() << endl;
    theStream   << "OTU     - Dispersion Compensation State     = " << DISPLAY_DISP_COMP_STATE(myDispCompState) << endl;
    theStream   << "OTU     - Trace In Use                      = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "OTU     - Received Trace                    = " ;
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
