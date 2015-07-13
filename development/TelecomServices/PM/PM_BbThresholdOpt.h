/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     12 December, 2001 Sebastien Cossette.
 DESCRIPTION:   PM Configuration parameters class for Optical layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDOPT_H
#define PM_BBTHRESHOLDOPT_H

#include <PM/PM_TypeOpt.h>
#include <PM/PM_BbGaugeThreshold.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the Optical threshold values configuration of PM.
//##ModelId=3C50162600CC
class PM_BbThresholdOpt : public PM_BbGaugeThreshold, public PM_TypeOpt
{

public:

    //Class default constructor.
    //##ModelId=3C501626027C
    PM_BbThresholdOpt(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    //##ModelId=3C501626028E
    virtual ~PM_BbThresholdOpt();

    //Resets all PM threshold value to the default value
    //##ModelId=3C5016260290
    virtual void Reset();

protected:

    //Stores the values to the stream.
    //##ModelId=3C50162602D5
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C50162602DF
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    //##ModelId=3C50162602F4
    CT_PM_Value myThresholdArray[PM_PARAM_NUM * 2];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    //##ModelId=3E6E4CCA0249
    bool myThresholdChangedArray[PM_PARAM_NUM * 2];

};

//Keeps the Optical threshold values configuration of PM. 
//This class contains a structure that defines all. This 
//class inherits of PM_BbThresholdOpt, but redefined the 
//method Reset to reset threshold default value for a 1-day 
//period instead of 15-minutes period.
//##ModelId=3C5016260311
class PM_BbThresholdOpt1Day : public PM_BbThresholdOpt
{

public:

    //Class default constructor.
    //##ModelId=3C50162700D8
    PM_BbThresholdOpt1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    //##ModelId=3C50162700EB
    virtual ~PM_BbThresholdOpt1Day();

    //Resets all PM threshold value to the default value
    //##ModelId=3C50162700ED
    virtual void Reset();

};

class PM_BbThresholdOptCounter : public PM_BbCounterThreshold,
                                  public PM_TypeOptCounter
{
public:

    //Class default constructor.
    PM_BbThresholdOptCounter(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdOptCounter();

    //Resets all PM threshold value to the default value
    virtual void Reset();

    //virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter) const;

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


class PM_BbThresholdOptCounter1Day : public PM_BbThresholdOptCounter
{

public:

    //Class default constructor.
    PM_BbThresholdOptCounter1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdOptCounter1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDOPT_H
