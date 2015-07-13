/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     22 April 2004   Hemant Thakkar
 DESCRIPTION:   PM Configuration parameters class for GFP
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDGFP_H
#define PM_BBTHRESHOLDGFP_H

#include <PM/PM_TypeGfp.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the GFP layer threshold values configuration of PM.
class PM_BbThresholdGfp : public PM_BbCounterThreshold, public PM_TypeGfp
{
public:

    //Class default constructor.
    PM_BbThresholdGfp(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdGfp();

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

//Keeps the Gfp threshold values configuration of PM. 
//This class inherits of PM_BbThresholdGfp, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
class PM_BbThresholdGfp1Day : public PM_BbThresholdGfp
{

public:

    //Class default constructor.
    PM_BbThresholdGfp1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdGfp1Day();

    //Resets all PM threshold value to the default value
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDGFP_H
