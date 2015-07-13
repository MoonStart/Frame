/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     December  2005, Teresa Chen
 DESCRIPTION:   PM Configuration parameters class for RMON
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDRMON_H
#define PM_BBTHRESHOLDRMON_H

#include <EPM/PM_TypeRmon.h>
#include <PM/PM_BbCounterThreshold.h>
#include <PM/PM_BbGaugeThreshold.h>

using namespace std;

//Keeps the RMON layer threshold values configuration of PM.

class PM_BbThresholdRmonCounter : public PM_BbCounterThreshold,
                                  public PM_TypeRmonCounter
{
public:

    //Class default constructor.
    PM_BbThresholdRmonCounter(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdRmonCounter();

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
    CT_PM_Value myThresholdArray[PM_PARAM_NUM];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    bool myThresholdChangedArray[PM_PARAM_NUM];

};


class PM_BbThresholdRmonCounter1Day : public PM_BbThresholdRmonCounter
{

public:

    //Class default constructor.
    PM_BbThresholdRmonCounter1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdRmonCounter1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};


class PM_BbThresholdRmonGauge : public PM_BbGaugeThreshold,
                                public PM_TypeRmonGauge
{

public:

    //Class default constructor.
    PM_BbThresholdRmonGauge(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdRmonGauge();

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

class PM_BbThresholdRmonGauge1Day : public PM_BbThresholdRmonGauge
{

public:

    //Class default constructor.
    PM_BbThresholdRmonGauge1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdRmonGauge1Day();

    //Resets all PM threshold value to the default value.
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDRMON_H
