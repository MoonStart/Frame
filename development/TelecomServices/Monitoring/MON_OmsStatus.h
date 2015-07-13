// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _INC_MON_OMSSTATUS
#define _INC_MON_OMSSTATUS

#include "MON_Object.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SystemIds.h>

//This class hold the status value (equipment levels) for the OMS layer (amplifiers).
class MON_OmsStatus 
: public MON_Object
{
public:
    //Constructor.
    MON_OmsStatus(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OmsStatus(void );

    CT_TEL_mBm GetOmsInputPower() const;
    bool SetOmsInputPower(CT_TEL_mBm thePower);

    CT_TEL_mBm GetOmsOutputPower() const;
    bool SetOmsOutputPower(CT_TEL_mBm thePower);

    CT_TEL_mBm GetOmsAlternatePower() const;
    bool SetOmsAlternatePower(CT_TEL_mBm thePower);

    CT_TEL_mBm GetDcmInputPower() const;
    bool SetDcmInputPower(CT_TEL_mBm thePower);

    CT_TEL_mBm GetDcmOutputPower() const;
    bool SetDcmOutputPower(CT_TEL_mBm thePower);

    CT_TEL_mBm GetActualGain() const;
    bool SetActualGain(CT_TEL_mBm theGain);

    CT_TEL_mBm GetConfiguredGain() const;
    bool SetConfiguredGain(CT_TEL_mBm theGain);  

    CT_TEL_mBm GetGainTilt() const;
    bool SetGainTilt(CT_TEL_mBm theGain);

    CT_TEL_mBm GetMinGain() const;
    bool SetMinGain(CT_TEL_mBm thePower);

    CT_TEL_mBm GetMaxGain() const;
    bool SetMaxGain(CT_TEL_mBm thePower);

    CT_TEL_mBm GetActualGroupEvoa() const;
    bool SetActualGroupEvoa(CT_TEL_mBm theEvoa);

    CT_TEL_mBm GetConfiguredGroupEvoa() const;
    bool SetConfiguredGroupEvoa(CT_TEL_mBm theEvoa);  

    CT_TEL_mBm GetOpovldThreshold() const;
    bool SetOpovldThreshold(CT_TEL_mBm theThreshold);

    CT_TEL_mBm GetAopeThreshold() const;
    bool SetAopeThreshold(CT_TEL_mBm theThreshold);

    // special validate method for PM
    bool ForPmIsValidated() const;
    bool ForPmValidate();
    bool ForPmInvalidate();

    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject(ostream& theStream);
    virtual istream& ReadObject(istream& theStream);
    virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);
    virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);

private:

    //The total aggregate optical input power in milliBels (0.01 dBm).
    CT_TEL_mBm myOmsInputPower;

    //The transmitted optical power (in mBm).
    CT_TEL_mBm myOmsOutputPower;

    CT_TEL_mBm myOmsAlternatePower;

    // The input and output DCM power (DSR/DST)
    CT_TEL_mBm myDcmInputPower;
    CT_TEL_mBm myDcmOutputPower;

    CT_TEL_mBm myActualGain;
    CT_TEL_mBm myConfiguredGain;
    CT_TEL_mBm myMinGain;
    CT_TEL_mBm myMaxGain;

    CT_TEL_mBm myGainTilt;

    CT_TEL_mBm myActualGroupEvoa;
    CT_TEL_mBm myConfiguredGroupEvoa;

    CT_TEL_mBm myLastNotifiedOmsInputPower;
    CT_TEL_mBm myLastNotifiedOmsOutputPower;
    CT_TEL_mBm myLastNotifiedOmsAlternatePower;
    CT_TEL_mBm myLastNotifiedDcmInputPower;
    CT_TEL_mBm myLastNotifiedDcmOutputPower;
    CT_TEL_mBm myLastNotifiedActualGain;
    CT_TEL_mBm myLastNotifiedActualGroupEvoa;

    CT_TEL_mBm myOpovldThreshold;
    CT_TEL_mBm myAopeThreshold;

    bool forPMisValidated;
};

#endif /* _INC_MON_OMSSTATUS */
