// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OmsStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <stdlib.h>

const CT_TEL_mBm MON_OMS_STATUS_NOTIF_DIFFERENCE = 40; // 0.4

MON_OmsStatus::MON_OmsStatus(uint32 theIndex):
    MON_Object(theIndex),
    myOmsInputPower(TRAFFIC_DEFAULT_POWER),
    myOmsOutputPower(TRAFFIC_DEFAULT_POWER),
    myOmsAlternatePower(TRAFFIC_DEFAULT_POWER),
    myDcmInputPower(TRAFFIC_DEFAULT_POWER),
    myDcmOutputPower(TRAFFIC_DEFAULT_POWER),
    myMinGain(TRAFFIC_DEFAULT_POWER),
    myMaxGain(TRAFFIC_DEFAULT_POWER),
    myActualGain(0),
    myGainTilt(0),
    myActualGroupEvoa(0),
    myConfiguredGroupEvoa(0),
    myLastNotifiedOmsInputPower(TRAFFIC_DEFAULT_POWER),
    myLastNotifiedOmsOutputPower(TRAFFIC_DEFAULT_POWER),
    myLastNotifiedOmsAlternatePower(TRAFFIC_DEFAULT_POWER),
    myLastNotifiedDcmInputPower(TRAFFIC_DEFAULT_POWER),
    myLastNotifiedDcmOutputPower(TRAFFIC_DEFAULT_POWER),
    myLastNotifiedActualGain(0),
    myLastNotifiedActualGroupEvoa(0),
    myConfiguredGain(0),
    forPMisValidated(false),
    myOpovldThreshold(0),
    myAopeThreshold(CT_TEL_DEFAULT_AOPE_THRESHOLD)
{
}

MON_OmsStatus::~MON_OmsStatus(void )
{
}

void MON_OmsStatus::Reset()
{
    myOmsInputPower  = TRAFFIC_DEFAULT_POWER;
    myOmsOutputPower = TRAFFIC_DEFAULT_POWER;
    myOmsAlternatePower = TRAFFIC_DEFAULT_POWER;
    myDcmInputPower  = TRAFFIC_DEFAULT_POWER;
    myDcmOutputPower = TRAFFIC_DEFAULT_POWER;
    myMinGain  = TRAFFIC_DEFAULT_POWER;
    myMaxGain = TRAFFIC_DEFAULT_POWER;
    myActualGain = 0;
    myConfiguredGain = 0;
    myGainTilt = 0;
    myActualGroupEvoa = 0;
    myConfiguredGroupEvoa = 0;
    myLastNotifiedOmsInputPower  = TRAFFIC_DEFAULT_POWER;
    myLastNotifiedOmsOutputPower = TRAFFIC_DEFAULT_POWER;
    myLastNotifiedOmsAlternatePower = TRAFFIC_DEFAULT_POWER;
    myLastNotifiedDcmInputPower  = TRAFFIC_DEFAULT_POWER;
    myLastNotifiedDcmOutputPower = TRAFFIC_DEFAULT_POWER;
    myLastNotifiedActualGain = 0;
    myLastNotifiedActualGroupEvoa = 0;
    myOpovldThreshold = 0;
    myAopeThreshold = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    forPMisValidated = false;
}

CT_TEL_mBm MON_OmsStatus::GetOmsInputPower() const
{
    return myOmsInputPower;
}

bool MON_OmsStatus::SetOmsInputPower(CT_TEL_mBm thePower)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myOmsInputPower != thePower)
    {
        myOmsInputPower = thePower;
        if (abs(myOmsInputPower - myLastNotifiedOmsInputPower) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedOmsInputPower = myOmsInputPower;
        }
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetOmsOutputPower() const
{
    return myOmsOutputPower; 
}

bool MON_OmsStatus::SetOmsOutputPower(CT_TEL_mBm thePower)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myOmsOutputPower != thePower)
    {
        myOmsOutputPower = thePower;
        if (abs(myOmsOutputPower - myLastNotifiedOmsOutputPower) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedOmsOutputPower = myOmsOutputPower;
        }
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetOmsAlternatePower() const
{
    return myOmsAlternatePower; 
}

bool MON_OmsStatus::SetOmsAlternatePower(CT_TEL_mBm thePower)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myOmsAlternatePower != thePower)
    {
        myOmsAlternatePower = thePower;
        if (abs(myOmsAlternatePower - myLastNotifiedOmsAlternatePower) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedOmsAlternatePower = myOmsAlternatePower;
        }
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetDcmInputPower() const
{
    return myDcmInputPower; 
}

bool MON_OmsStatus::SetDcmInputPower(CT_TEL_mBm thePower)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myDcmInputPower != thePower)
    {
        myDcmInputPower = thePower;
        if (abs(myDcmInputPower - myLastNotifiedDcmInputPower) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedDcmInputPower = myDcmInputPower;
        }
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetDcmOutputPower() const
{
    return myDcmOutputPower; 
}

bool MON_OmsStatus::SetDcmOutputPower(CT_TEL_mBm thePower)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myDcmOutputPower != thePower)
    {
        myDcmOutputPower = thePower;
        if (abs(myDcmOutputPower - myLastNotifiedDcmOutputPower) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedDcmOutputPower = myDcmOutputPower;
        }
    }
    return hasChanged;
}


CT_TEL_mBm MON_OmsStatus::GetActualGain() const
{
    return myActualGain;
}

bool MON_OmsStatus::SetActualGain(CT_TEL_mBm theGain)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myActualGain != theGain)
    {
        myActualGain = theGain;
        if (abs(myActualGain - myLastNotifiedActualGain) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedActualGain = myActualGain;
        }
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetConfiguredGain() const
{
    return myConfiguredGain;
}

bool MON_OmsStatus::SetConfiguredGain(CT_TEL_mBm theGain)
{
    // return true if changed
    if (myConfiguredGain != theGain)
    {
        myConfiguredGain = theGain;
        return true;
    }
    else
        return false;
}

CT_TEL_mBm MON_OmsStatus::GetGainTilt() const
{
    return myGainTilt;
}

bool MON_OmsStatus::SetGainTilt(CT_TEL_mBm theGain)
{
    // return true if changed
    if (myGainTilt != theGain)
    {
        myGainTilt = theGain;
        return true;
    }
    else
        return false;
}

bool MON_OmsStatus::SetMinGain(CT_TEL_mBm theGain)
{
    bool hasChanged = false;
    // return true if changed
    if (myMinGain != theGain)
    {
        myMinGain = theGain;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetMinGain() const
{
    return myMinGain; 
}

bool MON_OmsStatus::SetMaxGain(CT_TEL_mBm theGain)
{
    bool hasChanged = false;
    // return true if changed
    if (myMaxGain != theGain)
    {
        myMaxGain = theGain;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetMaxGain() const
{
    return myMaxGain; 
}


CT_TEL_mBm MON_OmsStatus::GetActualGroupEvoa() const
{
    return myActualGroupEvoa;
}

bool MON_OmsStatus::SetActualGroupEvoa(CT_TEL_mBm theEvoa)
{
    // return true if changed for more than minimum difference
    bool hasChanged = false;
    if (myActualGroupEvoa != theEvoa)
    {
        myActualGroupEvoa = theEvoa;
        if (abs(myActualGroupEvoa - myLastNotifiedActualGroupEvoa) >= MON_OMS_STATUS_NOTIF_DIFFERENCE) 
        {
            hasChanged = true;
            myLastNotifiedActualGroupEvoa = myActualGroupEvoa;
        }
    }
    return hasChanged;
}

CT_TEL_mBm MON_OmsStatus::GetConfiguredGroupEvoa() const
{
    return myConfiguredGroupEvoa;
}

bool MON_OmsStatus::SetConfiguredGroupEvoa(CT_TEL_mBm theEvoa)
{
    // return true if changed
    if (myConfiguredGroupEvoa != theEvoa)
    {
        myConfiguredGroupEvoa = theEvoa;
        return true;
    }
    else
        return false;
}


CT_TEL_mBm MON_OmsStatus::GetOpovldThreshold() const
{
    return myOpovldThreshold;
}

bool MON_OmsStatus::SetOpovldThreshold(CT_TEL_mBm theThreshold)
{
    // return true if changed
    if (myOpovldThreshold != theThreshold)
    {
        myOpovldThreshold = theThreshold;
        return true;
    }
    else
        return false;
}

CT_TEL_mBm MON_OmsStatus::GetAopeThreshold() const
{
    return myAopeThreshold;
}

bool MON_OmsStatus::SetAopeThreshold(CT_TEL_mBm theThreshold)
{
    // return true if changed
    if (myAopeThreshold != theThreshold)
    {
        myAopeThreshold = theThreshold;
        return true;
    }
    else
        return false;
}

bool MON_OmsStatus::ForPmIsValidated() const
{
    return forPMisValidated;
}

bool MON_OmsStatus::ForPmValidate()
{
    if (forPMisValidated)
        return false;
    else
    {
        forPMisValidated = true;
        return true;
    }
}

bool MON_OmsStatus::ForPmInvalidate()
{
    if (!forPMisValidated)
        return false;
    else
    {
        forPMisValidated = false;
        return true;
    }
}

ostream& MON_OmsStatus::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myOmsInputPower);
    theStream << FC_InsertVar(myOmsOutputPower);
    theStream << FC_InsertVar(myActualGain);
    theStream << FC_InsertVar(myConfiguredGain);
    theStream << FC_InsertVar(myGainTilt);
    theStream << FC_InsertVar(myActualGroupEvoa);
    theStream << FC_InsertVar(myConfiguredGroupEvoa);
    theStream << FC_InsertVar(myOpovldThreshold);
    theStream << FC_InsertVar(myAopeThreshold);
    theStream << FC_InsertVar(myOmsAlternatePower);
    theStream << FC_InsertVar(forPMisValidated);
    theStream << FC_InsertVar(myDcmInputPower);
    theStream << FC_InsertVar(myDcmOutputPower);
    theStream << FC_InsertVar(myMinGain);
    theStream << FC_InsertVar(myMaxGain);
    return theStream;
}

istream& MON_OmsStatus::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myOmsInputPower);
    theStream >> FC_ExtractVar(myOmsOutputPower);
    theStream >> FC_ExtractVar(myActualGain);
    theStream >> FC_ExtractVar(myConfiguredGain);
    theStream >> FC_ExtractVar(myGainTilt);
    theStream >> FC_ExtractVar(myActualGroupEvoa);
    theStream >> FC_ExtractVar(myConfiguredGroupEvoa);
    theStream >> FC_ExtractVar(myOpovldThreshold);
    theStream >> FC_ExtractVar(myAopeThreshold);
    theStream >> FC_ExtractVar(myOmsAlternatePower);
    theStream >> FC_ExtractVar(forPMisValidated);
    theStream >> FC_ExtractVar(myDcmInputPower);
    theStream >> FC_ExtractVar(myDcmOutputPower);
    theStream >> FC_ExtractVar(myMinGain);
    theStream >> FC_ExtractVar(myMaxGain);
    return theStream;
}

FC_Stream& MON_OmsStatus::WriteObjectBinary(FC_Stream& theStream)
{
    //NOTE: Serialize only the attributes needed
    MON_Object::WriteObjectBinary(theStream);
    theStream << myOmsInputPower;
    theStream << myOmsOutputPower;
    theStream << myActualGain;
    theStream << myConfiguredGain;
    theStream << myGainTilt;
    theStream << myActualGroupEvoa;
    theStream << myConfiguredGroupEvoa;
    theStream << myOmsAlternatePower;
    theStream << forPMisValidated;
    theStream << myDcmInputPower;
    theStream << myDcmOutputPower;
    theStream << myMinGain;
    theStream << myMaxGain;
    return theStream;
}

FC_Stream& MON_OmsStatus::ReadObjectBinary(FC_Stream& theStream)
{
    //NOTE: Serialize only the attributes needed
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myOmsInputPower;
    theStream >> myOmsOutputPower;
    theStream >> myActualGain;
    theStream >> myConfiguredGain;
    theStream >> myGainTilt;
    theStream >> myActualGroupEvoa;
    theStream >> myConfiguredGroupEvoa;
    theStream >> myOmsAlternatePower;
    theStream >> forPMisValidated;
    theStream >> myDcmInputPower;
    theStream >> myDcmOutputPower;
    theStream >> myMinGain;
    theStream >> myMaxGain;
    return theStream;
}

void MON_OmsStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    if(!ForPmIsValidated())
    {
        theStream << "              **** DATA INVALID FOR PM ****"  << endl;  
    }
    theStream   << "OMS     - Input Power  (dBm)                = " << DISPLAY_MBM(myOmsInputPower) << endl;
    theStream   << "OMS     - Output Power (dBm)                = " << DISPLAY_MBM(myOmsOutputPower) << endl;
    theStream   << "OMS     - Alternate Power (dBm)             = " << DISPLAY_MBM(myOmsAlternatePower) << endl;
    theStream   << "OMS     - DCM Input Power  - DSR (dBm)      = " << DISPLAY_MBM(myDcmInputPower) << endl;
    theStream   << "OMS     - DCM Output Power - DST (dBm)      = " << DISPLAY_MBM(myDcmOutputPower) << endl;
    theStream   << "OMS     - Actual Gain  (dB )                = " << DISPLAY_MBM(myActualGain) << endl;
    theStream   << "OMS     - Configured Gain  (dB )            = " << DISPLAY_MBM(myConfiguredGain) << endl;
    theStream   << "OMS     - Gain Tilt  (dB )                  = " << DISPLAY_MBM(myGainTilt) << endl;
    theStream   << "OMS     - Actual Group Evoa  (dB )          = " << DISPLAY_MBM(myActualGroupEvoa) << endl;
    theStream   << "OMS     - Configured Group Evoa  (dB )      = " << DISPLAY_MBM(myConfiguredGroupEvoa) << endl;
    theStream   << "OMS     - Optical Overload Threshold (dB )  = " << DISPLAY_MBM(myOpovldThreshold) << endl;
    theStream   << "OMS     - AOPE Threshold (dB )              = " << DISPLAY_MBM(myAopeThreshold) << endl;
    theStream   << "OMS     - Gain Range                        = " << DISPLAY_MBM(myMinGain)
                                                                    << "," << DISPLAY_MBM(myMaxGain) << endl;
}

