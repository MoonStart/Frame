/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   PM Configuration parameters class for Optical Channel layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDCOP_H
#define PM_BBTHRESHOLDCOP_H

#include <PM/PM_TypeCop.h>
#include <PM/PM_BbGaugeThreshold.h>


//Keeps the Optical Channel threshold values configuration of 
//PM.
//##ModelId=3C1F6F5102BA
class PM_BbThresholdCop : public PM_BbGaugeThreshold, public PM_TypeCop
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F520082
    PM_BbThresholdCop(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    //##ModelId=3C1F6F52008D
    virtual ~PM_BbThresholdCop();

    //Resets all PM threshold value to the default value
    //##ModelId=3C1F6F520096
    virtual void Reset();

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F5200E5
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F5200F0
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    //##ModelId=3C1FAF820076
    CT_PM_Value myThresholdArray[PM_PARAM_NUM * 2];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    //##ModelId=3E6E4CD9022D
    bool myThresholdChangedArray[PM_PARAM_NUM * 2];

};

//Keeps the Optical Channel threshold values configuration of 
//PM. This class inherits of PM_BbThresholdCop, but redefined 
//the method Reset to reset threshold default value for a 
//1-day period instead of 15-minutes period.
//##ModelId=3C1F6F520121
class PM_BbThresholdCop1Day : public PM_BbThresholdCop
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5202C6
    PM_BbThresholdCop1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    //##ModelId=3C1F6F5202D1
    virtual ~PM_BbThresholdCop1Day();

    //Resets all PM threshold value to the default value
    //##ModelId=3C1F6F5202DB
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDCOP_H
