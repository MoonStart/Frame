//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OCHSTATUS_H
#define MON_OCHSTATUS_H

#include "MON_Object.h"
#include "MON_OchPower.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <ctime>
#include <BaseClass/FC_ObjVectorImp.h>
#include <PII_TickTimer.h>


//This class hold the status value (levels) for the OCH layer.
class MON_OchStatus
: public MON_Object
{

public:

    
	//Constructor.
    MON_OchStatus(uint32 theIndex);
    MON_OchStatus(const MON_OchStatus& theOchStatus);

	//Virtual destructor.
    virtual ~MON_OchStatus(void);

    bool operator==(const MON_OchStatus& theOchStatus) const;
    void operator=(const MON_OchStatus& theOchStatus);

    virtual bool SetTraceIdPowers(const MON_OchPower& thePower);
    const MON_OchPower& GetTraceIdPower(MON_RelativeTraceId theTraceId) const; 

    void Boost(CT_TEL_mBm theBoost);

    time_t GetSampleTime() const { return mySampleTime;}

    const MON_OchPower& GetMostPowerfullId() const;
    CT_TEL_mBm GetPower() const;

    bool SetPreAmpPower(const CT_TEL_mBm thePreAmpPower);
    CT_TEL_mBm GetPreAmpPower() const;

    bool SetOutputPower(const CT_TEL_mBm theOutputPower);
    CT_TEL_mBm GetOutputPower() const;

    bool SetChannelId(const CT_Wavelength& theChannelId);
    const CT_Wavelength& GetChannelId() const;

    const MON_OchPower& GetMostPowerfullId(const MON_OchStatus* theInterferenceStatus) const;
	
    void GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len);
    
    // Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    void ClearPowersLevels();

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:

    FC_ObjVectorImp<MON_OchPower*> myIdPowers;

    time_t          mySampleTime;
    time_t          myPreviousSampleTime;
    CT_Wavelength   myChannelId;

    CT_TEL_mBm      myPreAmpPower;
    CT_TEL_mBm      myOutputPower;
};

#endif /* MON_OCHSTATUS_H */
