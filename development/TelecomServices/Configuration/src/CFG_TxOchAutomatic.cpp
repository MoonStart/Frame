//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_TxOchAutomatic.h"
#include <BaseClass/FC_TextStream.h>
#include <math.h>

CFG_TxOchAutomatic::CFG_TxOchAutomatic(uint32 theIndex):
    myTraceId(0),
    CFG_Object(theIndex),
    myToneAmplitude(0),
    myToneAmpliRatio(0),
    myModulationRatio(1.0),
    myTargetPowerBoost(0),
    myControlFailure(false)
{
    myTotalReads = 0;
    mySuspectReads = 0;
    myConsecutiveGoodReads = 0;
    myAveStableFlag = false;
    myTotSizeAmpQueue = DEFAULT_AMPL_QUEUE_SIZE;
    myActReadsAmpQueue = 0;
    myAveAmplQueue = 0.0;
    mySumAmplQueue = 0;
    for(int i = 0; i < myTotSizeAmpQueue; i++)
    {
        myAmplSamples[i] = 0;
    }
    myIndexPos = 0;
}


CFG_TxOchAutomatic::~CFG_TxOchAutomatic()
{
}


bool CFG_TxOchAutomatic::SetTraceId(CT_TEL_PilotToneID theTraceId)
{
    bool hasChanged = false;
    if (theTraceId != myTraceId)
    {
        myTraceId = theTraceId;
        hasChanged = true;
    }
    return hasChanged;
}


CT_TEL_PilotToneID CFG_TxOchAutomatic::GetTraceId() const
{
    return myTraceId;
}

bool CFG_TxOchAutomatic::SetToneAmplitude(float theToneAmplitude)
{
    bool hasChanged = false;
    if (theToneAmplitude != myToneAmplitude)
    {
        myToneAmplitude = theToneAmplitude;
        hasChanged = true;
    }
    return hasChanged;
}


float CFG_TxOchAutomatic::GetToneAmplitude() const
{
    return myToneAmplitude;
}


bool CFG_TxOchAutomatic::SetToneAmpliRatio(float theToneAmpliRatio)
{
    // Make this value be in increments of .05
    // First, make it a integer with the precision to the hundredths 
    // This is so we can use the modulus operator to get the value
    // at the hundredths, which is needed to step by .05
    uint32 tmpInt = uint32((theToneAmpliRatio + float(.005)) * float(100.0));
    uint32 tmpRem = tmpInt % 10;

    // Now divide by 10 to get the tenths place and figure out the 
    // hundreths based on the remainder of the modulus
    tmpInt /= 10;
    float  addTenths = float(0.0);
    if ((tmpRem >= 3) || (tmpRem <= 7))
    {
        addTenths = float(0.05);
    }
    else if (tmpRem > 7) 
    {
        addTenths = float(0.1);
    }

    // To get the new Ampli Ratio, we must divide by 100.  tmpInt was already
    // divided by 10 above, so multiply by .1 and then add the hundredths
    // portion (either 0, 0.05, or .1). 
    theToneAmpliRatio = (float(tmpInt) * float(0.1)) + addTenths;

    bool hasChanged = false;
    if (theToneAmpliRatio != myToneAmpliRatio)
    {
        myToneAmpliRatio = theToneAmpliRatio;
        hasChanged = true;
    }
    return hasChanged;
}


float CFG_TxOchAutomatic::GetToneAmpliRatio() const
{
    return myToneAmpliRatio;
}


bool CFG_TxOchAutomatic::SetDcPower(const MON_OchPower& theDcPower)
{
    bool hasChanged = false;
    if (!(theDcPower == myDcPower))
    {
        myDcPower = theDcPower;
        hasChanged = true;
    }
    return hasChanged;
}


const MON_OchPower& CFG_TxOchAutomatic::GetDcPower() const
{
    return myDcPower;
}

bool CFG_TxOchAutomatic::SetAcPower(const MON_OchPower& theAcPower)
{
    bool hasChanged = false;
    if (!(theAcPower == myAcPower))
    {
        myAcPower = theAcPower;
        hasChanged = true;
    }
    return hasChanged;
}


const MON_OchPower& CFG_TxOchAutomatic::GetAcPower() const
{
    return myAcPower;
}

bool CFG_TxOchAutomatic::SetControlFailure(bool theControlFailure)
{
    bool hasChanged = false;
    if (theControlFailure != myControlFailure)
    {
        myControlFailure = theControlFailure;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_TxOchAutomatic::GetControlFailure() const
{
    return myControlFailure;
}


float CFG_TxOchAutomatic::GetModulationRatio()
{
    // check for divide by zero
    myModulationRatio = pow(10.0, (double)(myAcPower.GetAmplitude() - myDcPower.GetAmplitude())/CT_TEL_POWER_FACTOR/10);
    return myModulationRatio;
}


bool CFG_TxOchAutomatic::SetNewModulationRatio()
{
    bool hasChanged = false;
    // For now, we won't use the average
    // NOTE: Before this is turned on, need to decide when to use average, etc.
    // CT_TEL_mBm anAveAcPowerAmpl = GetAverageAcPowerAmpl();

    CT_TEL_mBm aNormTargetPowerBoost = CT_TEL_mBm(myTargetPowerBoost * CT_TEL_POWER_FACTOR);
    float aModulationRatio = pow(10.0, (double)(myLatestAcPowerAmpl - aNormTargetPowerBoost - myLatestDcPowerAmpl)/CT_TEL_POWER_FACTOR/10);

    if (aModulationRatio != myModulationRatio)
    {
        myModulationRatio = aModulationRatio;
        hasChanged = true;
    }
    return hasChanged;
}


float CFG_TxOchAutomatic::GetNewModulationRatio() const
{
    return myModulationRatio;
}


bool CFG_TxOchAutomatic::IsAcPowerInRange()
{
    CT_TEL_mBm aNormTargetPowerBoost = CT_TEL_mBm(myTargetPowerBoost * CT_TEL_POWER_FACTOR);
    CT_TEL_mBm aPowerTolerance       = CT_TEL_mBm(myPowerTolerance * CT_TEL_POWER_FACTOR);

    myTotalReads++;
    myConsecutiveGoodReads++;
    myLatestAcPowerAmpl = myAcPower.GetAmplitude();
    myLatestDcPowerAmpl = myDcPower.GetAmplitude();

    // Make sure the fc_cout is commented out if submitted.
    bool aValidReading = true;
    if ((myLatestAcPowerAmpl < (myLatestDcPowerAmpl + aNormTargetPowerBoost - aPowerTolerance)) ||
        (myLatestAcPowerAmpl > (myLatestDcPowerAmpl + aNormTargetPowerBoost + aPowerTolerance)) )
    {
        aValidReading = false;
        mySuspectReads++;
        myConsecutiveGoodReads = 0;
        // For now, print out first ten
        if (mySuspectReads <= 10)
        {
            fc_cout << "**** CFG_TxOchAutomatic: Suspect AcPower Number / Amplitude:  " << mySuspectReads << " / " << myLatestAcPowerAmpl << endl;
        }
    }
    return aValidReading;
}


CT_TEL_mBm CFG_TxOchAutomatic::GetAverageAcPowerAmpl()
{
    // Make sure reads are within 10 times the tolerance before putting the 
    // new value on the queue and getting new average.  Otherwise, use ave (if available)
    // or use latest read
    if (myAcPowerInRange)
    {  
        // If within range, put it in the queue
        // Subract the oldest read and replace it with the newest
        uint32 anOldestRead = myAmplSamples[myIndexPos];
        myAmplSamples[myIndexPos++] = uint32(myLatestAcPowerAmpl);
        mySumAmplQueue += (uint32(myLatestAcPowerAmpl) - anOldestRead);

        // Wrap around
        if (myIndexPos >= myTotSizeAmpQueue) 
        {
            myIndexPos = 0;
        }

        if (myActReadsAmpQueue < myTotSizeAmpQueue) 
        {
            myActReadsAmpQueue++;
        }
        else
        {   
            myActReadsAmpQueue = myTotSizeAmpQueue;
        }

        // Only take average after queue is full 
        if (myActReadsAmpQueue == myTotSizeAmpQueue)
        {
            myAveAmplQueue = float(mySumAmplQueue) / float(myActReadsAmpQueue);
        }

        // Make sure we take enough good reads at the beginning
        // and we have all good reads in the queue before we start using the average
        // becuase there is no going back.
        if ((myTotalReads > MIN_READS_BEFORE_AVE_USED) && 
            (myConsecutiveGoodReads > myTotSizeAmpQueue))
        {
            myAveStableFlag = true;
        }
    }

    // Wait until the average is actually used; until then, use the latest read.
    if (myAveStableFlag) 
    {
        return CT_TEL_mBm(myAveAmplQueue + 0.5);
    }
    else
    { 
        return myLatestAcPowerAmpl;
    }    
}


bool CFG_TxOchAutomatic::SetTargetPowerBoost(float theBoost)
{
    bool hasChanged = false;
    if (theBoost != myTargetPowerBoost)
    {
        myTargetPowerBoost = theBoost;
        hasChanged = true;
    }
    return hasChanged;
}


float CFG_TxOchAutomatic::GetTargetPowerBoost() const
{
    return myTargetPowerBoost;
}


bool CFG_TxOchAutomatic::SetPowerTolerance(float theTolerance)
{
    bool hasChanged = false;
    if (theTolerance != myPowerTolerance)
    {
        myPowerTolerance = theTolerance;
        hasChanged = true;
    }
    return hasChanged;
}


float CFG_TxOchAutomatic::GetPowerTolerance() const
{
    return myPowerTolerance;
}


void CFG_TxOchAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myTraceId = 0;
    myToneAmplitude=0;
    myToneAmpliRatio=0;
    myModulationRatio = 1.0;
    myTargetPowerBoost = 0;
    myPowerTolerance = 0;
    MON_OchPower aPower;
    myAcPower=aPower;
    myDcPower=aPower;
    myControlFailure=false;
    myTotalReads=0;
    mySuspectReads=0;
    myConsecutiveGoodReads = 0;
    myAveStableFlag = false;
    myTotSizeAmpQueue = DEFAULT_AMPL_QUEUE_SIZE;
    myActReadsAmpQueue = 0;
    myAveAmplQueue = 0.0;
    mySumAmplQueue = 0;
    for(int i = 0; i < myTotSizeAmpQueue; i++)
    {
        myAmplSamples[i] = 0;
    }
    myIndexPos = 0;
}

// For Display
ostream& CFG_TxOchAutomatic::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myTraceId);
    theStream   << FC_InsertVar(myToneAmplitude);
    theStream   << FC_InsertVar(myToneAmpliRatio);
    theStream   << FC_InsertVar(myModulationRatio);
    theStream   << FC_InsertVar(myTargetPowerBoost);
    theStream   << FC_InsertVar(myPowerTolerance);
    theStream   << FC_InsertVar(myAcPower);
    theStream   << FC_InsertVar(myDcPower);
    theStream   << FC_InsertVar(myControlFailure);
    theStream   << FC_InsertVar(myTotalReads);
    theStream   << FC_InsertVar(mySuspectReads);
    theStream   << FC_InsertVar(myConsecutiveGoodReads);
    theStream   << FC_InsertVar(myAveStableFlag);
    theStream   << FC_InsertVar(myAveAmplQueue);
    return theStream;

}

// For Display
istream& CFG_TxOchAutomatic::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myTraceId);
    theStream   >> FC_ExtractVar(myToneAmplitude);
    theStream   >> FC_ExtractVar(myToneAmpliRatio);
    theStream   >> FC_ExtractVar(myModulationRatio);
    theStream   >> FC_ExtractVar(myTargetPowerBoost);
    theStream   >> FC_ExtractVar(myPowerTolerance);
    theStream   >> FC_ExtractVar(myAcPower);
    theStream   >> FC_ExtractVar(myDcPower);
    theStream   >> FC_ExtractVar(myControlFailure);
    theStream   >> FC_ExtractVar(myTotalReads);
    theStream   >> FC_ExtractVar(mySuspectReads);
    theStream   >> FC_ExtractVar(myConsecutiveGoodReads);
    theStream   >> FC_ExtractVar(myAveStableFlag);
    theStream   >> FC_ExtractVar(myAveAmplQueue);
    return theStream;

}

// For persitance and region transfer
FC_Stream& CFG_TxOchAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myTraceId;
    theStream   << myToneAmplitude;
    theStream   << myToneAmpliRatio;
    theStream   << myModulationRatio;
    theStream   << myTargetPowerBoost;
    theStream   << myPowerTolerance;
    theStream   << myAcPower;
    theStream   << myDcPower;
    theStream   << myControlFailure;
    return theStream;

}

// For persitance and region transfer
FC_Stream& CFG_TxOchAutomatic::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myTraceId;
    theStream   >> myToneAmplitude;
    theStream   >> myToneAmpliRatio;
    theStream   >> myModulationRatio;
    theStream   >> myTargetPowerBoost;
    theStream   >> myPowerTolerance;
    theStream   >> myAcPower;
    theStream   >> myDcPower;
    theStream   >> myControlFailure;
    return theStream;

}

void CFG_TxOchAutomatic::Display( FC_Stream& theStream )
{
    theStream.GetOutputStream()   << "OCH TX AUTO Trace ID         = "  << (uint32)myTraceId << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Tone Amplitude   = "  << myToneAmplitude << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Tone Ampli Ratio = "  << myToneAmpliRatio << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Target Pow Boost = "  << myTargetPowerBoost << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Ratio Tolerance  = "  << myPowerTolerance << endl;
    //theStream.GetOutputStream()   << "OCH TX AUTO Queue Power Ave  = "  << myAveAmplQueue << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Total AC Reads   = "  << myTotalReads << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Suspect AC Reads = "  << mySuspectReads << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Consec Good Reads= "  << myConsecutiveGoodReads << endl;
    //theStream.GetOutputStream()   << "OCH TX AUTO Using Pow Average= "  << DISPLAY_BOOL(myAveStableFlag) << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Control Failure  = "  << myControlFailure << endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Current Mod ratio = " << myModulationRatio*100 <<"%"<< endl;
    theStream.GetOutputStream()   << "OCH TX AUTO Target  Mod ratio = " << "100%" << endl;
    theStream.GetOutputStream()   << "AC Power " << endl;
    myAcPower.Display(theStream);
    theStream.GetOutputStream()   << "DC Power " << endl;
    myDcPower.Display(theStream);
}
