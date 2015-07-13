/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   PM Configuration parameters class for Oms layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDOMS_H
#define PM_BBTHRESHOLDOMS_H

#include <PM/PM_TypeOms.h>
#include <PM/PM_BbGaugeThreshold.h>


//Keeps the Oms threshold values configuration of PM.
//##ModelId=3E6E4C9903B1
class PM_BbThresholdOms : public PM_BbGaugeThreshold, public PM_TypeOms
{

public:

    //Class default constructor.
    //##ModelId=3E6E4C9B015B
    PM_BbThresholdOms(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    //##ModelId=3E6E4C9B0170
    virtual ~PM_BbThresholdOms();

    //Resets all PM threshold value to the default value
    //##ModelId=3E6E4C9B0184
    virtual void Reset();

protected:

    //Stores the values to the stream.
    //##ModelId=3E6E4C9B018F
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4C9B01AD
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    //##ModelId=3E6FC01C032C
    CT_PM_Value myThresholdArray[PM_PARAM_NUM * 2];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //##ModelId=3E6E4C9B0224
    bool myThresholdChangedArray[PM_PARAM_NUM * 2];

};

//Keeps the Oms threshold values configuration of PM. 
//This class contains a structure that defines all. This 
//class inherits of PM_BbThresholdOms, but redefined the 
//method Reset to reset threshold default value for a 1-day 
//period instead of 15-minutes period.
//##ModelId=3E6E4C9B0260
class PM_BbThresholdOms1Day : public PM_BbThresholdOms
{

public:

    //Class default constructor.
    //##ModelId=3E6E4C9C03DE
    PM_BbThresholdOms1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    //##ModelId=3E6E4C9D000A
    virtual ~PM_BbThresholdOms1Day();

    //Resets all PM threshold value to the default value
    //##ModelId=3E6E4C9D0014
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDOMS_H
