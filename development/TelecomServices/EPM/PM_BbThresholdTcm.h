/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   PM Configuration parameters class for TCM.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDTCM_H
#define PM_BBTHRESHOLDTCM_H

#include <EPM/PM_TypeTcm.h>
#include <PM/PM_BbCounterThreshold.h>
#include <PM/PM_BbGaugeThreshold.h>

//Keeps the TCM layer threshold values configuration of PM.
class PM_BbThresholdTcm : public PM_BbCounterThreshold, public PM_TypeTcm
{
public:

    //Class default constructor.
    PM_BbThresholdTcm(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdTcm();

    //Resets all PM threshold value to the default value
    virtual void Reset();

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter) const;

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    CT_PM_Value myThresholdArray[PM_TypeTcm::PM_PARAM_NUM];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    bool myThresholdChangedArray[PM_TypeTcm::PM_PARAM_NUM];

};

//Keeps the TCM threshold values configuration of PM. 
//This class inherits of PM_BbThresholdTcm, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdTcm1Day : public PM_BbThresholdTcm
{

public:

    //Class default constructor.
    PM_BbThresholdTcm1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdTcm1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

class PM_BbThresholdTcmGauge : public PM_BbGaugeThreshold,
                               public PM_TypeTcmGauge
{

public:

    //Class default constructor.
    PM_BbThresholdTcmGauge(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdTcmGauge();

    //Resets all PM threshold value to the default value
    virtual void Reset();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    CT_PM_Value myThresholdArray[PM_PARAM_NUM * 2];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    bool myThresholdChangedArray[PM_PARAM_NUM * 2];

};

class PM_BbThresholdTcmGauge1Day : public PM_BbThresholdTcmGauge
{

public:

    //Class default constructor.
    PM_BbThresholdTcmGauge1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdTcmGauge1Day();

    //Resets all PM threshold value to the default value.
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDTCM_H
