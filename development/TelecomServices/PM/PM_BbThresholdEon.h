/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   PM Configuration parameters class for Data.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDEON_H
#define PM_BBTHRESHOLDEON_H

#include <PM/PM_TypeEon.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the EON threshold values configuration of PM.
//##ModelId=3C9255B90026
class PM_BbThresholdEon : public PM_BbCounterThreshold, public PM_TypeEon
{

public:

    //Class default constructor.
	//##ModelId=3FA1610A0249
    PM_BbThresholdEon(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
	//##ModelId=3FA1610A025A
    virtual ~PM_BbThresholdEon();

    //Resets all PM threshold value to the default value
	//##ModelId=3C9255B9029D
    virtual void Reset();

protected:

    //Stores the values to the stream.
	//##ModelId=3C9255B902A7
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
	//##ModelId=3C9255B902B2
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
	//##ModelId=3C926090021C
    CT_PM_Value myThresholdArray[PM_PARAM_NUM];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
	//##ModelId=3E6E4CDF0330
    bool myThresholdChangedArray[PM_PARAM_NUM];

};

//Keeps the EON threshold values configuration of PM. 
//This class inherits of PM_BbThresholdEon, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
//##ModelId=3FA1610A0278
class PM_BbThresholdEon1Day : public PM_BbThresholdEon
{

public:

    //Class default constructor.
	//##ModelId=3FA1610A03D1
    PM_BbThresholdEon1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
	//##ModelId=3FA1610A03E1
    virtual ~PM_BbThresholdEon1Day();

    //Resets all PM threshold value to the default value
	//##ModelId=3FA1610A03E3
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDEON_H
