/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   PM Configuration parameters class for Near-End SONET/SDH
                HOP.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDHOPNEAREND_H
#define PM_BBTHRESHOLDHOPNEAREND_H

#include <PM/PM_TypeHopNearEnd.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the Near-End SONET/SDH HOP layer threshold values configuration of PM.
class PM_BbThresholdHopNearEnd : public PM_BbCounterThreshold, public PM_TypeHopNearEnd
{
public:

    //Class default constructor.
    PM_BbThresholdHopNearEnd(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdHopNearEnd();

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

//Keeps the HopNearEnd threshold values configuration of PM. 
//This class inherits of PM_BbThresholdHopNearEnd, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdHopNearEnd1Day : public PM_BbThresholdHopNearEnd
{

public:

    //Class default constructor.
    PM_BbThresholdHopNearEnd1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdHopNearEnd1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDHOPNEAREND_H
