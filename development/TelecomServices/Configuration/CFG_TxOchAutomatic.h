/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_TXOCHAUTOMATICOBJECT_H
#define CFG_TXOCHAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"
#include <Monitoring/MON_OchPower.h>
#include <deque>


const int DEFAULT_AMPL_QUEUE_SIZE   = 10;
const int MIN_READS_BEFORE_AVE_USED = 20;

class CFG_TxOchAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_TxOchAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_TxOchAutomatic(void);

    bool SetTraceId(CT_TEL_PilotToneID theTraceId);
    CT_TEL_PilotToneID GetTraceId() const;

    bool SetToneAmplitude(float theToneAmplitude);
    float GetToneAmplitude() const;

    bool SetToneAmpliRatio(float theToneAmpliRatio);
    float GetToneAmpliRatio() const;

    bool SetAcPower(const MON_OchPower& thePower);
    const MON_OchPower& GetAcPower() const;

    bool SetDcPower(const MON_OchPower& thePower);
    const MON_OchPower& GetDcPower() const;

    bool SetControlFailure(bool thePower);
    bool GetControlFailure() const;

    float GetModulationRatio();

    bool SetNewModulationRatio();
    float GetNewModulationRatio() const;
    bool IsAcPowerInRange();
    CT_TEL_mBm GetAverageAcPowerAmpl();

    bool SetTargetPowerBoost(float theBoost);
    float GetTargetPowerBoost() const;

    bool SetPowerTolerance(float theTolerance);
    float GetPowerTolerance() const;

    //This method resets all attributes to their default 
    //value.
    virtual void Reset(void);

    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization text mode: This function allows writing 
    //object content to the output stream for debugging with 
    //the console.
    //##ModelId=3C0FE62F02E5
    virtual ostream& WriteObject( ostream& theStream );

    //Serialization text mode: This function allows reading 
    //object content from the input stream for debugging with 
    //the console.
    //##ModelId=3C0FE62F02EF
    virtual istream& ReadObject( istream& theStream );

    //Serialization binary mode: This function allows writing 
    //object content to the output stream for blackboard 
    //transfer.
    //##ModelId=3C0FE62F02F9
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Serialization binary mode: This function allows reading 
    //object content from the input stream for blackboard 
    //transfer.
    //##ModelId=3C0FE62F0304
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    CT_TEL_PilotToneID myTraceId;
    float myToneAmplitude;
    float myToneAmpliRatio;
    float myModulationRatio;
    MON_OchPower myAcPower;
    MON_OchPower myDcPower;
    bool myControlFailure;

    float  myTargetPowerBoost;
    float  myPowerTolerance;
    bool   myAcPowerInRange;
    CT_TEL_mBm myLatestAcPowerAmpl;
    CT_TEL_mBm myLatestDcPowerAmpl;

    uint32 myTotalReads;
    uint32 mySuspectReads;
    uint32 myConsecutiveGoodReads;
    bool   myAveStableFlag;
    uint16 myTotSizeAmpQueue;
    uint16 myActReadsAmpQueue;
    float  myAveAmplQueue;
    uint32 mySumAmplQueue;

    uint32 myAmplSamples[DEFAULT_AMPL_QUEUE_SIZE];
    uint16 myIndexPos;
};

#endif /* CFG_TXOCHAUTOMATICOBJECT_H */

