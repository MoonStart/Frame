// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchStatus.h"
#include "../MON_SubNodeParameters.h"
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>

const uint32 MON_INTERFERENCE_ISOLATION_VALUE_MBM = 1000;

//##ModelId=3C1A4D7C000D
MON_OchStatus::MON_OchStatus(uint32 theIndex):
    MON_Object(theIndex),
    mySampleTime(0),
    myPreviousSampleTime(0),
    myChannelId(UNKNOWN_WAVELENGHT),
    myPreAmpPower(TRAFFIC_DEFAULT_POWER),
    myOutputPower(TRAFFIC_DEFAULT_POWER)
{
    int i;
    for (i=0; i<MON_NUMBER_OF_ID_PER_LAMBDA; i++)
        myIdPowers.push_back(new MON_OchPower((MON_RelativeTraceId)i));
}

MON_OchStatus::MON_OchStatus(const MON_OchStatus& theOchStatus):
    MON_Object(theOchStatus),
    mySampleTime(theOchStatus.mySampleTime),
    myPreviousSampleTime(theOchStatus.myPreviousSampleTime),
    myChannelId(theOchStatus.myChannelId),
    myPreAmpPower(theOchStatus.myPreAmpPower),
    myOutputPower(theOchStatus.myOutputPower)
{
    int i;
    for (i=0; i<MON_NUMBER_OF_ID_PER_LAMBDA; i++)
        myIdPowers.push_back(new MON_OchPower(theOchStatus.GetTraceIdPower((MON_RelativeTraceId)i)));
}

void MON_OchStatus::operator=(const MON_OchStatus& theOchStatus)
{
    MON_Object::operator=(theOchStatus);

    uint32 i;
    for (i=0; i<myIdPowers.size(); i++)
        *myIdPowers[i] = *theOchStatus.myIdPowers[i];
    myChannelId = theOchStatus.myChannelId;
    mySampleTime = theOchStatus.mySampleTime;
    myPreviousSampleTime = theOchStatus.myPreviousSampleTime;
}

bool MON_OchStatus::operator==(const MON_OchStatus& theOchStatus) const
{
    if (!MON_Object::operator ==(theOchStatus))
        return false;

    bool equal=true;
    uint32 i;
    for (i=0; i<myIdPowers.size(); i++)
        equal &= (*myIdPowers[i]==*theOchStatus.myIdPowers[i]);

    equal &= (myChannelId == theOchStatus.myChannelId);

    return equal;
}

//##ModelId=3C1A4D7C0016
MON_OchStatus::~MON_OchStatus(void )
{
    int i;
    for (i=0; i<MON_NUMBER_OF_ID_PER_LAMBDA; i++)
        delete myIdPowers[i];
}

//##ModelId=3C1A4D7C0020
void MON_OchStatus::Reset()
{
    MON_Object::Reset();
    mySampleTime = 0;
    myPreviousSampleTime = 0;
    ClearPowersLevels();
    myChannelId = UNKNOWN_WAVELENGHT;
    myPreAmpPower = TRAFFIC_DEFAULT_POWER;
    myOutputPower = TRAFFIC_DEFAULT_POWER;
}

void MON_OchStatus::ClearPowersLevels()
{
    int i;
    for (i=0; i<MON_NUMBER_OF_ID_PER_LAMBDA; i++)
    {
        MON_OchPower aPower((MON_RelativeTraceId)i);
        *myIdPowers[i]=aPower;
    }
}

bool MON_OchStatus::SetTraceIdPowers(const MON_OchPower& thePower)
{
    FC_THROW_ERROR_IF(thePower.GetTraceId() >=MON_ID_UNKNOWN, FC_InvalidArgumentError, "Invalid trace ID");

    //return true if changed
    bool hasChanged = false;
    if (!(*myIdPowers[thePower.GetTraceId()] == thePower))
    {
        *myIdPowers[thePower.GetTraceId()] = thePower;
        hasChanged |= true;
    }

//    time_t myPreviousSampleTime = mySampleTime;
    mySampleTime = CSPII_CardIF::GetInstance()->GetUTCTime();

    // warn if previous valid sample is more than 15min old
    if ((abs(long(mySampleTime-myPreviousSampleTime)) > 15*60)  && IsValidated())
    {
        char aErrorString[256];
        char tstamp[20];
        char *pBuf = &tstamp[0];
        char tempstamp[20];
        char *pTempBuf = &tempstamp[0];

        GetDateTimeStampStr(mySampleTime, &pBuf, sizeof(tstamp));
        GetDateTimeStampStr(myPreviousSampleTime, &pTempBuf, sizeof(tempstamp));

        //FC_REPORT_ERROR(FC_RuntimeError, "Och power measurement was more than 15 minutes old.");
        sprintf(aErrorString, "Och power measurement was more than 15 minutes old: Sample = %s Prev = %s Diff = %d", tstamp, tempstamp, abs(long(mySampleTime-myPreviousSampleTime)) );
        FC_REPORT_ERROR(FC_RuntimeError, aErrorString);
    }

    myPreviousSampleTime = mySampleTime;

    return hasChanged;
}

const MON_OchPower& MON_OchStatus::GetTraceIdPower(MON_RelativeTraceId theTraceId) const
{
    FC_THROW_ERROR_IF(theTraceId >=MON_ID_UNKNOWN, FC_InvalidArgumentError,"Invalid trace ID");
    return *myIdPowers[theTraceId];
}

#ifdef WIN32
#define max _cpp_max
#endif

const MON_OchPower& MON_OchStatus::GetMostPowerfullId() const
{
    return max(max(*myIdPowers[0], *myIdPowers[1]), *myIdPowers[2]);
}

CT_TEL_mBm MON_OchStatus::GetPower() const
{
    CT_TEL_mBm subNodeSNR = MON_SubNodeParameters::GetInstance().GetMinimumSNRatio();

    // if SNR is bad, return -99 instead
    const MON_OchPower& aPower = GetMostPowerfullId();
    if (aPower.GetSnr() < subNodeSNR)
        return TRAFFIC_DEFAULT_POWER;
    else
        return aPower.GetAmplitude();
}


bool MON_OchStatus::SetPreAmpPower(CT_TEL_mBm thePreAmpPower)
{
    bool hasChanged = false;
    if (!(myPreAmpPower == thePreAmpPower))
    {
        myPreAmpPower = thePreAmpPower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OchStatus::GetPreAmpPower() const
{
    // Determined in Update Status Action
    return myPreAmpPower;
}

bool MON_OchStatus::SetOutputPower(CT_TEL_mBm theOutputPower)
{
    bool hasChanged = false;
    if (!(myOutputPower == theOutputPower))
    {
        myOutputPower = theOutputPower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OchStatus::GetOutputPower() const
{
    // Determined in Update Status Action
    return myOutputPower;
}


bool MON_OchStatus::SetChannelId(const CT_Wavelength& theChannelId)
{
    bool hasChanged = false;
    if (!(myChannelId == theChannelId))
    {
        myChannelId = theChannelId;
        hasChanged = true;
    }
    return hasChanged;
}

const CT_Wavelength& MON_OchStatus::GetChannelId() const
{
    return myChannelId;
}

const MON_OchPower& MON_OchStatus::GetMostPowerfullId(const MON_OchStatus* theInterferenceStatus) const
{
    //Check if interference source was provided
    if (theInterferenceStatus==NULL)
        return GetMostPowerfullId();

    //--------------------------------
    // exclude source of interference
    //--------------------------------
    // find max of all 6
    const MON_OchPower& aLocalMaxPower       = GetMostPowerfullId();
    const MON_OchPower& aInterferingMaxPower = theInterferenceStatus->GetMostPowerfullId();

    CT_TEL_mBm aPowerDifference = aInterferingMaxPower.GetAmplitude() - aLocalMaxPower.GetAmplitude();

    // there is interference only if same ID is seen from both side
    // and if interfering power is higher than local.
    if ((aInterferingMaxPower.GetTraceId() != aLocalMaxPower.GetTraceId()) ||
        (aInterferingMaxPower <  aLocalMaxPower) ||
        (aPowerDifference < MON_INTERFERENCE_ISOLATION_VALUE_MBM))
            return aLocalMaxPower;

    // there is interference, exclude local max found
    MON_RelativeTraceId aInterferedId = aLocalMaxPower.GetTraceId();
    switch (aInterferedId)
    {
    case MON_ID_FIRST:
        return max(GetTraceIdPower(MON_ID_SECOND),GetTraceIdPower(MON_ID_DEBUG));;
    case MON_ID_SECOND:
        return max(GetTraceIdPower(MON_ID_FIRST),GetTraceIdPower(MON_ID_DEBUG));;
    case MON_ID_DEBUG:
        return max(GetTraceIdPower(MON_ID_FIRST),GetTraceIdPower(MON_ID_SECOND));;
    default:
        FC_THROW_ERROR(FC_RuntimeError, "Invalid relative trace ID");
        return GetMostPowerfullId(); //for compiler
    }
}

void MON_OchStatus::GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len)
{
    if(*pBuf == NULL)
        return;

    memset(*pBuf, 0x00, len);

    struct tm *stamp = NULL;

    if( (stamp = localtime(&theTime)) != NULL)
    {
        sprintf(*pBuf, "%2.2d/%2.2d/%4.4d-%2.2d:%2.2d:%2.2d",
                stamp->tm_mon+1, stamp->tm_mday, stamp->tm_year+1900,
                stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
    }
}

ostream& MON_OchStatus::WriteObject(ostream& theStream)
{
    uint8 aChannelId = myChannelId.WavelengthIndex();
    MON_Object::WriteObject(theStream);
    uint32 i;
    for (i=0; i<myIdPowers.size(); i++)
    {
        MON_OchPower& aPower = *myIdPowers[i];
        theStream << FC_InsertVar(aPower);
    }
    theStream <<  FC_InsertLabelAndVar("myChannelId", aChannelId);
    theStream << FC_InsertVar(myPreAmpPower);
    theStream << FC_InsertVar(myOutputPower);
    return theStream;
}

istream& MON_OchStatus::ReadObject(istream& theStream)
{
    uint8 aChannelId;  // for conversion
    MON_Object::ReadObject(theStream);
    uint32 i;
    for (i=0; i<myIdPowers.size(); i++)
    {
        MON_OchPower& aPower = *myIdPowers[i];
        theStream >> FC_ExtractVar(aPower);
    }
    theStream >>  FC_ExtractVar(aChannelId);
    // Convert and store the expected channel
    CT_Wavelength bChannelId(aChannelId);
    myChannelId = bChannelId;
    theStream   >> FC_ExtractVar(myPreAmpPower);
    theStream   >> FC_ExtractVar(myOutputPower);
    return theStream;
}

FC_Stream& MON_OchStatus::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myIdPowers;
    theStream << myChannelId;
    theStream << myPreAmpPower;
    theStream << myOutputPower;
    return theStream;
}

FC_Stream& MON_OchStatus::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myIdPowers;
    theStream >> myChannelId;
    theStream >> myPreAmpPower;
    theStream >> myOutputPower;
    return theStream;
}

void MON_OchStatus::Display(FC_Stream& theStream)
{
    tm  aTmData;
    tm* aTmPtr = &aTmData;
    char aTimeBuf[CSPII_TIME_BUFF_LENGTH];

    MON_Object::Display(theStream);
    theStream   << "OCH     - Channel Id (0-based)              = " << (uint32)myChannelId.WavelengthIndex() << endl;
    theStream   << "OCH     - PreAmp Power (mBm) [if available] = " << myPreAmpPower << endl;
    theStream   << "OCH     - Output Power (mBm) [if available] = " << myOutputPower << endl;
    theStream   << "OCH     - Input power sample time (UTC)     = " << CSPII_CardIF::GetInstance()->GetAsctime(CSPII_CardIF::GetInstance()->GetGmtime( &mySampleTime, aTmPtr ), aTimeBuf );

    for (uint32 i=0; i<myIdPowers.size(); i++)
        (*myIdPowers[i]).Display(theStream);
}

void MON_OchStatus::Boost(CT_TEL_mBm theBoost)
{
    uint32 i;
    for (i=0; i<myIdPowers.size(); i++)
        myIdPowers[i]->Boost(theBoost);
}
