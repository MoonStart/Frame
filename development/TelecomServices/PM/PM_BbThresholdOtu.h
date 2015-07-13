/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Configuration parameters class for Physical, RS and MS.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLDOTU_H
#define PM_BBTHRESHOLDOTU_H

#include <PM/PM_TypeOtu.h>
#include <PM/PM_BbCounterThreshold.h>
#include <PM/PM_BbGaugeThreshold.h>


//Keeps the Optical Transport Unit threshold values 
//configuration of PM.
//##ModelId=3C1F6F5C011C
class PM_BbThresholdOtu : public PM_BbCounterThreshold, public PM_TypeOtu
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5C034D
    PM_BbThresholdOtu(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    //##ModelId=3C1F6F5C0360
    virtual ~PM_BbThresholdOtu();

    //Resets all PM threshold value to the default value
    //##ModelId=3C1F6F5C0362
    virtual void Reset();

    CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter) const;

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F5C036B
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F5C037E
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    //##ModelId=3C1F6F5C0393
    CT_PM_Value myThresholdArray[PM_PARAM_NUM];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    //##ModelId=3E6E4CCE0064
    bool myThresholdChangedArray[PM_PARAM_NUM];

};

//Keeps the Optical Transport Unit threshold values 
//configuration of PM. This class inherits of 
//PM_BbThresholdOtu, but redefined the method Reset to reset 
//threshold default value for a 1-day period instead of 
//15-minutes period.
//##ModelId=3C1F6F5C03BB
class PM_BbThresholdOtu1Day : public PM_BbThresholdOtu
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F5D01F9
    PM_BbThresholdOtu1Day(uint32 dummy = 0, uint32 dummy2 = 0 );
    
    //Class default destructor.
    //##ModelId=3C1F6F5D020D
    virtual ~PM_BbThresholdOtu1Day();

    //Resets all PM threshold value to the default value.
    //##ModelId=3C1F6F5D020F
    virtual void Reset();

};

class PM_BbThresholdOtuGauge : public PM_BbGaugeThreshold,
                                public PM_TypeOtuGauge
{

public:

    //Class default constructor.
    PM_BbThresholdOtuGauge(uint32 dummy = 0, uint32 dummy2 = 0);
    
    //Class default destructor.
    virtual ~PM_BbThresholdOtuGauge();

    //Resets all PM threshold value to the default value
    virtual void Reset();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Array that holds the value of all thresholds (of all 
    //supported parameters).
    CT_PM_Value myThresholdArray[PM_PARAM_NUM * 2];

    //Array that holds a flag for all thresholds (of all 
    //supported parameters) indicating if the threshold
    //has changed after blackboard transfer.
    bool myThresholdChangedArray[PM_PARAM_NUM * 2];

};

class PM_BbThresholdOtuGauge1Day : public PM_BbThresholdOtuGauge
{

public:

    //Class default constructor.
    PM_BbThresholdOtuGauge1Day(uint32 dummy = 0, uint32 dummy2 = 0 ); 
    
    //Class default destructor.
    virtual ~PM_BbThresholdOtuGauge1Day();

    //Resets all PM threshold value to the default value.
    virtual void Reset();

};


#endif //PM_BBTHRESHOLDOTU_H
