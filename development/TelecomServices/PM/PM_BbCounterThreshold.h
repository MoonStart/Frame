/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Counter threshold class.
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTERTHRESHOLD_H
#define PM_BBCOUNTERTHRESHOLD_H

#include <PM/PM_BbThreshold.h>
#include <CommonTypes/CT_Telecom.h>

//Keeps the Configuration parameters of PM.
//##ModelId=3E6E4CBE01B6
class PM_BbCounterThreshold : public PM_BbThreshold
{
public:

    //This class constructor allocates the necessary memory 
    //to put an array of threshold value.
    //##ModelId=3E6E4CBF02DA
    PM_BbCounterThreshold(uint32 theNumberOfParam, uint32 dummy);

    //This class constructor uses theThresholdPtr instead of 
    //allocates memory dynamically.
    //##ModelId=3E6E4CBF02EE
    PM_BbCounterThreshold(uint32        theNumberOfParam, 
                          CT_PM_Value*  theThresholdPtr, 
                          bool*         theThresholdChangedPtr);

    //Class default destructor.
    //##ModelId=3E6E4CBF0302
    virtual ~PM_BbCounterThreshold();

    //Sets threshold parameter value.
    //##ModelId=3E6E4CBF030C
    virtual bool SetThreshold(CT_PM_Parameter theParameter, uint32 theValue );

    //##ModelId=3E6E4CBF0334
    virtual void SetThreshold(CT_PM_Parameter   theParameter, 
                              int32             theMinValue, 
                              int32             theMaxValue);

    //Gets the threshold value according to the parameters type.
    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter) const;

    //Not supported by the base class.
    //##ModelId=3E6E4CBF0366
    virtual void GetThreshold(CT_PM_Parameter   theParameter, 
                              int32&            theMinValue, 
                              int32&            theMaxValue) const;

    //Gets the threshold flag according to the parameters 
    //type. This flag indicates if the threshold configuration
    //has changed since last blackboard refresh.
    //##ModelId=3E6E4CBF037B
    virtual bool HasThresholdChanged(CT_PM_Parameter theParameter) const;

    //Not supported by the base class.
    //##ModelId=3E6E4CBF03A2
    virtual void HasThresholdChanged(CT_PM_Parameter    theParameter, 
                                     bool&              theMinFlag, 
                                     bool&              theMaxFlag) const;

    //Reads the states from a binary stream.
	//##ModelId=3FA1610801ED
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

};

#endif //PM_BBCOUNTERTHRESHOLD_H
