/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   PM Configuration parameters class for Far-End SONET/SDH
                Multiplex Section.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDMSFAREND_H
#define PM_BBTHRESHOLDMSFAREND_H

#include <PM/PM_TypeMsFarEnd.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the Far-End SONET/SDH MS layer threshold values configuration of PM.
class PM_BbThresholdMsFarEnd : public PM_BbCounterThreshold, public PM_TypeMsFarEnd
{
public:

    //Class default constructor.
    PM_BbThresholdMsFarEnd(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdMsFarEnd();

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

//Keeps the MsFarEnd threshold values configuration of PM. 
//This class inherits of PM_BbThresholdMsFarEnd, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdMsFarEnd1Day : public PM_BbThresholdMsFarEnd
{

public:

    //Class default constructor.
    PM_BbThresholdMsFarEnd1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdMsFarEnd1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDMSFAREND_H
