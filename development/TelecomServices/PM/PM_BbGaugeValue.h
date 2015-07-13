/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 15, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Parameter Gauge values class. Keeps and sets PM 
                parameter gauge values.
--------------------------------------------------------------------------*/

#ifndef PM_BBGAUGEVALUE_H
#define PM_BBGAUGEVALUE_H

#include <PM/PM_BbValue.h>
#include <PM/PM_BbTca.h>

//Keeps the Parameter Values. This contains an array of 
//uint32 that keeps parameter values.
//##ModelId=3E6E4CB701AC
class PM_BbGaugeValue : public PM_BbValue
{

public:

    //This class constructor allocates the necessary memory 
    //to put an array of parameter value.
    //##ModelId=3E6E4CB801FE
    PM_BbGaugeValue (uint32 theNumberOfParam, uint32 dummy = 0);

    //Class default destructor.
    //##ModelId=3E6E4CB8021B
    virtual ~PM_BbGaugeValue();

    //Resets all Values to default.
    //##ModelId=3E6E4CB80225
    virtual void Reset();

    //Resets all PM values to zero.
    //##ModelId=3E6E4CB80239
    virtual void ResetAll(void);

    //Resets all PM values to zero but current value.
    //##ModelId=3E6E4CB80243
    virtual void ResetAll(const PM_BbValue &thePreviousValue);

    //Resets current value for one parameter.
    //##ModelId=3E6E4CB80258
    virtual void ResetCurParam(CT_PM_Parameter theParameter);

    //Resets minimum value for one parameter.
    //##ModelId=3E6E4CB8026C
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

	//Gets the Value of a parameter.
    virtual void GetValues(CT_PM_Parameter  theParameter, 
                           CT_PM_64BitValue&     theValue, 
                           CT_PM_64BitValue&     theMinValue, 
                           CT_PM_64BitValue&     theMaxValue) const;

    //Sets the parameter with the value.
    virtual void SetValues(CT_PM_Parameter  theParameter, 
                           CT_PM_64BitValue      theValue, 
                           CT_PM_64BitValue      theMinValue, 
                           CT_PM_64BitValue      theMaxValue);

    //Operator that copies the register values.
    virtual PM_BbValue& operator=(PM_BbValue &theOtherValue);

    //Operator that returns true if values of this object are 
    virtual bool operator==(PM_BbValue &theOtherValue);

	//Get the Min TCA pointer.
    virtual PM_BbTca* GetMinTca();

	//Triggers member TCA objects to allocate space for TCA event data.
	virtual void AllocateTca();

protected:

    //Stores the values to the stream.
    //##ModelId=3E6E4CB80295
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4CB802B2
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    //##ModelId=3E6E4CB802C6
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    //##ModelId=3E6E4CB802E4
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Creates all members of this object, including base classes.
    virtual void CreateMembersDeep();

    //Deletes all members of this object, including base classes.
    virtual void DeleteMembersDeep();

    //Array that contains all minimum values for the period 
    //for each parameter.
    CT_PM_Value* myMinValues;

    //Array that contains all maximum values for the period 
    //for each parameter.
    CT_PM_Value* myMaxValues;

private:

    //Creates all members of this object.
    void CreateMembers();

    //Deletes all members of this object.
    void DeleteMembers();

    //The minimum TCA of all registers in that object.
    PM_BbTca* myMinTca;

};

#endif //PM_BBVALUE_H

