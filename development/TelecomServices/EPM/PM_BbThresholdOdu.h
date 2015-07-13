/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   PM Configuration parameters class for ODU.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDODU_H
#define PM_BBTHRESHOLDODU_H

#include <EPM/PM_TypeOdu.h>
#include <PM/PM_BbCounterThreshold.h>
#include <PM/PM_BbGaugeThreshold.h>

//Keeps the ODU layer threshold values configuration of PM.
class PM_BbThresholdOdu : public PM_BbCounterThreshold, public PM_TypeOdu
{
public:

    //Class default constructor.
    PM_BbThresholdOdu(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdOdu();

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

//Keeps the ODU threshold values configuration of PM. 
//This class inherits of PM_BbThresholdOdu, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdOdu1Day : public PM_BbThresholdOdu
{

public:

    //Class default constructor.
    PM_BbThresholdOdu1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdOdu1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

class PM_BbThresholdOduGauge : public PM_BbGaugeThreshold,
                               public PM_TypeOduGauge
{
 
public:
 
    //Class default constructor.
    PM_BbThresholdOduGauge(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdOduGauge();
 
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
 
class PM_BbThresholdOduGauge1Day : public PM_BbThresholdOduGauge
{
 
public:
 
    //Class default constructor.
    PM_BbThresholdOduGauge1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdOduGauge1Day();
 
    //Resets all PM threshold value to the default value.
    virtual void Reset();
 
};

#endif //PM_BBTHRESHOLDODU_H
