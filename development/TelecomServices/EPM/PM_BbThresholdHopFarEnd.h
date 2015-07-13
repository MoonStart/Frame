/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     27 February 2006   Larry Wolfrum
 DESCRIPTION:   PM Configuration parameters class for Far-End SONET/SDH
                HOP.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDHOPFAREND_H
#define PM_BBTHRESHOLDHOPFAREND_H

#include <EPM/PM_TypeHopFarEnd.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the Far-End SONET/SDH HOP layer threshold values configuration of PM.
class PM_BbThresholdHopFarEnd : public PM_BbCounterThreshold, public PM_TypeHopFarEnd
{
public:

    //Class default constructor.
    PM_BbThresholdHopFarEnd(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdHopFarEnd();

    //Resets all PM threshold value to the default value
    virtual void Reset();

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

//Keeps the HopFarEnd threshold values configuration of PM. 
//This class inherits of PM_BbThresholdHopFarEnd, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdHopFarEnd1Day : public PM_BbThresholdHopFarEnd
{

public:

    //Class default constructor.
    PM_BbThresholdHopFarEnd1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdHopFarEnd1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDHOPFAREND_H
