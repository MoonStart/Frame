/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   PM Configuration parameters class for Near-End SONET/SDH
                Multiplex Section.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDMSNEAREND_H
#define PM_BBTHRESHOLDMSNEAREND_H

#include <PM/PM_TypeMsNearEnd.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the Near-End SONET/SDH MS layer threshold values configuration of PM.
class PM_BbThresholdMsNearEnd : public PM_BbCounterThreshold, public PM_TypeMsNearEnd
{
public:

    //Class default constructor.
    PM_BbThresholdMsNearEnd(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdMsNearEnd();

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

//Keeps the MsNearEnd threshold values configuration of PM. 
//This class inherits of PM_BbThresholdMsNearEnd, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdMsNearEnd1Day : public PM_BbThresholdMsNearEnd
{

public:

    //Class default constructor.
    PM_BbThresholdMsNearEnd1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdMsNearEnd1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDMSNEAREND_H
