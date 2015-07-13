/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   PM Configuration parameters class for Laser.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDLASER_H
#define PM_BBTHRESHOLDLASER_H

#include <PM/PM_TypeLaser.h>
#include <PM/PM_BbGaugeThreshold.h>


//Keeps the Optical Transport Section threshold values 
//configuration of PM.
//##ModelId=3C1F6F5601B3
class PM_BbThresholdLaser : public PM_BbGaugeThreshold, public PM_TypeLaser
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5603DA
    PM_BbThresholdLaser(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    //##ModelId=3C1F6F5603E5
    virtual ~PM_BbThresholdLaser();

    //Resets all PM threshold value to the default value
    //##ModelId=3C1F6F570006
    virtual void Reset();

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F57004D
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F570060
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    //##ModelId=3C1F6F570075
    CT_PM_Value myThresholdArray[PM_PARAM_NUM * 2];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    //##ModelId=3E6E4CD40316
    bool myThresholdChangedArray[PM_PARAM_NUM * 2];

};

//Keeps the Optical Transport Section threshold values 
//configuration of PM. This class inherits of 
//PM_BbThresholdLaser, but redefined the method Reset to reset 
//threshold default value for a 1-day period instead of 
//15-minutes period.
//##ModelId=3C1F6F57009C
class PM_BbThresholdLaser1Day : public PM_BbThresholdLaser
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5702B9
    PM_BbThresholdLaser1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    //##ModelId=3C1F6F5702C5
    virtual ~PM_BbThresholdLaser1Day();

    //Resets all PM threshold value to the default value.
    //##ModelId=3C1F6F5702CE
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDLASER_H
