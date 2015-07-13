/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM Configuration parameters class for Data.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDDATA_H
#define PM_BBTHRESHOLDDATA_H

#include <PM/PM_TypeData.h>
#include <PM/PM_BbCounterThreshold.h>


//Keeps the Data threshold values configuration of PM.
//##ModelId=3FA1610E01CB
class PM_BbThresholdData : public PM_BbCounterThreshold, public PM_TypeData
{

public:

    //Class default constructor.
    //##ModelId=3FA1610E0343
    PM_BbThresholdData(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    //##ModelId=3FA1610E0346
    virtual ~PM_BbThresholdData();

    //Resets all PM threshold value to the default value
    //##ModelId=3FA1610E0348
    virtual void Reset();

    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter) const;

protected:

    //Stores the values to the stream.
    //##ModelId=3FA1610E0352
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3FA1610E0355
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    //##ModelId=3FA164C003B8
    CT_PM_Value myThresholdArray[PM_PARAM_NUM];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    //##ModelId=3FA1610E0366
    bool myThresholdChangedArray[PM_PARAM_NUM];

};

//Keeps the Data threshold values configuration of PM. 
//This class inherits of PM_BbThresholdData, but redefined 
//the method Reset to reset threshold default value for 
//a 1-day period instead of 15-minutes period.
//##ModelId=3FA16B800297
class PM_BbThresholdData1Day : public PM_BbThresholdData
{

public:

    //Class default constructor.
    //##ModelId=3FA16B810007
    PM_BbThresholdData1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    //##ModelId=3FA16B81000A
    virtual ~PM_BbThresholdData1Day();

    //Resets all PM threshold value to the default value
    //##ModelId=3FA16B81000C
    virtual void Reset();

};

#endif //PM_BBTHRESHOLDDATA_H
