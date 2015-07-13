/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM threshold class. Keeps the threshold of PM.
--------------------------------------------------------------------------*/

#ifndef PM_BBTHRESHOLD_H
#define PM_BBTHRESHOLD_H

#include "PM_BbObject.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_PM_Definition.h>

//Keeps the Configuration parameters of PM.
//##ModelId=3C1F6F7100EA
class PM_BbThreshold : public PM_BbObject
{

public:

    //This class constructor allocates the necessary memory 
    //to put an array of threshold value.
    //##ModelId=3C1F6F710311
    PM_BbThreshold(uint32 theNumberOfParam, uint32 dummy);

    //This class constructor uses theThresholdPtr instead of 
    //allocates memory dynamically.
    //##ModelId=3C1F6F710325
    PM_BbThreshold(uint32       theNumberOfParam, 
                   CT_PM_Value* theThresholdPtr, 
                   bool*        theThresholdChangedPtr);

    //Class default destructor.
    //##ModelId=3C1F6F710331
    virtual ~PM_BbThreshold();

    //Resets all PM values to zero.
    //##ModelId=3C1F6F71033A
    virtual void Reset();

    //Sets threshold parameter value.
    //##ModelId=3C1F6F710344
    virtual bool SetThreshold(CT_PM_Parameter theParameter, uint32 theValue ) = 0;

    //Not supported by the base class.
    //##ModelId=3C1F6F710357
    virtual void SetThreshold(CT_PM_Parameter   theParameter, 
                              int32             theMinValue, 
                              int32             theMaxValue) = 0;

    //Gets the threshold value according to the parameters type.
    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter) const = 0;

    //Not supported by the base class.
    //##ModelId=3C1F6F710377
    virtual void GetThreshold(CT_PM_Parameter   theParameter, 
                              int32&            theMinValue, 
                              int32&            theMaxValue) const = 0;

    //Gets the threshold flag according to the parameters 
    //type. This flag indicates if the threshold configuration
    //has changed since last blackboard refresh.
    //##ModelId=3E6E4CA70006
    virtual bool HasThresholdChanged(CT_PM_Parameter theParameter) const = 0;

    //Not supported by the base class.
    //##ModelId=3E6E4CA7005E
    virtual void HasThresholdChanged(CT_PM_Parameter    theParameter, 
                                     bool&              theMinFlag, 
                                     bool&              theMaxFlag) const = 0;

    //Writes the states to the binary stream.
    //##ModelId=3C1F6F71038B
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    //##ModelId=3C1F6F71039D
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3C1F6F7103B1
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F7103C5
    virtual istream& ReadObject( istream& theStream );

    uint32 GetNumberOfParam() { return myNumberOfParam; }

protected:

    //The number of parameter values contained in myThreshold. 
    //##ModelId=3C1F6F7103D0
    uint32 myNumberOfParam;

    //Array that contains all the threshold values of the 
    //layer.
    //##ModelId=3C1F6F720006
    CT_PM_Value* myThreshold;

    //Array of flag indicating if the threshold has changed.
    //##ModelId=3E6E4CA70159
    bool* myThresholdChanged;

    //Flag indicating if memory was allocated.
    //##ModelId=3C1F6F72000F
    bool myMemoryAllocated;

};

#endif //PM_BBTHRESHOLD_H
