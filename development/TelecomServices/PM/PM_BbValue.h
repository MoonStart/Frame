/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     1 June, 1998 Jean-Francois Birtz.
 DESCRIPTION:   PM Parameter values class. Keeps and set PM parameter values.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUE_H
#define PM_BBVALUE_H

#include <PM/PM_Def.h>
#include <PM/PM_BbTca.h>
#include <PM/PM_BbIdf.h>
#include <PM/PM_BbObject.h>


class PM_StorageAction;

//Keeps the Parameter Values. This contains an array of
//uint32 that keeps parameter values.
//##ModelId=3C1F6F6F019B
class PM_BbValue : public PM_BbObject
{

public:

#ifdef LINUX
    friend class PM_StorageAction;
#else
    friend PM_StorageAction;
#endif

    //This class constructor allocates the necessary memory
    //to put an array of parameter value.
    //##ModelId=3C1F6F6F03D6
    PM_BbValue (uint32 theNumberOfParam, uint32 dummy = 0);

    //Class default destructor.
    //##ModelId=3C1F6F700003
    virtual ~PM_BbValue();

    //Resets all Values to default.
    //##ModelId=3C1F6F70000C
    virtual void Reset();

    //Resets all PM values to zero.
    //##ModelId=3CBC723E00F5
    virtual void ResetAll(void);

    //##ModelId=3C1F6F700036
    //Resets all PM values to zero but current value.
    virtual void ResetAll(const PM_BbValue &thePreviousValue);

    //Specific overloaded version of ResetAll() needed in the root
    // base class to allow PM_BbValueRmonGauge::ResetAll() to be correctly
    // accessed.
    virtual void ResetAll(const uint32 theUtilization);

    //Resets current value for one parameter.
    //##ModelId=3C9255C00062
    virtual void ResetCurParam(CT_PM_Parameter theParameter);

    //Resets minimum value for one parameter.
    //##ModelId=3E6E4CA400A0
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    //##ModelId=3E6E4CA40168
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

    //Sets the period start time.
    //##ModelId=3E6E4CA40227
    void SetStartTime(FC_Time theStartTime);

    //Gets the period start time.
    //
    //RETURN: The period start time.
    //##ModelId=3E6E4CA402EF
    FC_Time GetStartTime() const;

    //Sets the period end time.
    //##ModelId=3E6E4CA40349
    void SetEndTime(FC_Time theEndTime);

    //Gets the period end time.
    //##ModelId=3E6E4CA50029
    FC_Time GetEndTime() const;

    //Gets the Value of a parameter.
    //##ModelId=3C1F6F700017
    virtual void GetValues(CT_PM_Parameter  theParameter,
                           CT_PM_64BitValue&     theValue,
                           CT_PM_64BitValue&     theMinValue,
                           CT_PM_64BitValue&     theMaxValue) const;

    //Sets the parameter with the value.
    //##ModelId=3C1F6F70002A
    virtual void SetValues(CT_PM_Parameter  theParameter,
                           CT_PM_64BitValue      theValue,
                           CT_PM_64BitValue      theMinValue,
                           CT_PM_64BitValue      theMaxValue);

    //Returns the current value for the specified parameters.
    //##ModelId=3C9255BF0332
    virtual void GetValue(CT_PM_Parameter theParameter, CT_PM_64BitValue& theValue, bool useLowHigh64Bit = true);

    //Sets the value of the specified parameter.
    //##ModelId=3C9255BF03C8
    virtual void SetValue(CT_PM_Parameter theParameter, CT_PM_64BitValue theValue);

    //Operator that copies the register values.
    //##ModelId=3C1F6F70005C
    virtual PM_BbValue& operator=(PM_BbValue &theOtherValue);

    //Operator that returns true if values of this object are
    //##ModelId=3C1F6F700048
    virtual bool operator==(PM_BbValue &theOtherValue);

    //Gets the Request Id.
    //##ModelId=3C1F6F700066
    CT_PM_RequestId GetRequestId() const;

    //Sets the Request Id.
    //##ModelId=3C1F6F700070
    void SetRequestId(CT_PM_RequestId theRequestId);

    //Returns the number of supported parameters.
    //##ModelId=3C9255C000A9
    int GetNumberOfParam()const;

    //Gets the IDF pointer.
    //##ModelId=3E6E4CA5012E
    PM_BbIdf* GetIdf();

    //Get the Min TCA pointer.
    //##ModelId=3E6E4CA50174
    virtual PM_BbTca* GetMinTca();

    //Get the Max TCA pointer.
    //##ModelId=3E6E4CA501BA
    PM_BbTca* GetMaxTca();

    //Is the specified parameter an Unavailable Seconds parameter?
    bool IsUasParameter(CT_PM_Parameter theParameter) const;

    //Is the specified parameter an adjusted parameter based on
    //the state of unavailability
    bool IsUasAdjustedParameter(CT_PM_Parameter theParameter) const;

    //Triggers member TCA objects to allocate space for TCA event data.
    virtual void AllocateTca();

    // Method to set the value of the first parameter to the start time.
    void SetTestValue();

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F7000B6
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F7000D4
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    //##ModelId=3C1F6F7000E8
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the states from a binary stream.
    //##ModelId=3C1F6F7000F3
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Creates all members of this object.
    //##ModelId=3E6E4CA50391
    virtual void CreateMembersDeep();

    //Deletes all members of this object.
    //##ModelId=3E6E4CA60017
    virtual void DeleteMembersDeep();

    //The number of parameter values contained in *myCurValues.
    //##ModelId=3C1F6F700106
    uint32 myNumberOfParam;

    //Array that contains all current values for the period
    //for each parameter.
    //##ModelId=3C1F6F700143
    CT_PM_Value* myCurValues;

    //8-bit flags to mark UAS parameter
    uint8*   myUasParameterFlags;

    //Period start time.
    //##ModelId=3E6E4CA502BF
    FC_Time myStartTime;

    //Period end time.
    //##ModelId=3E6E4CA5032D
    FC_Time myEndTime;

    //The IDF of all registers in that object.
    //##ModelId=3C1F6F700085
    PM_BbIdf* myIdf;

    //The maximum TCA of all registers in that object.
    //##ModelId=3E6E4CA6011B
    PM_BbTca* myMaxTca;

    //Handle 64Bit values (e.g. ODU4 CV-ODU)
    virtual bool IsParam64BitValue( const CT_PM_Parameter theParameter );
    virtual CT_PM_64BitValue Get64BitValue( const CT_PM_Parameter theParameter );
    virtual void             Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue );

private:

    //Creates all members of this object.
    void CreateMembers();

    //Deletes all members of this object.
    void DeleteMembers();

    //The last request id.
    //##ModelId=3C1F6F700125
    CT_PM_RequestId myRequestId;

};

//-----------------------------------------------------------------
//##ModelId=3C1F6F700066
inline CT_PM_RequestId PM_BbValue::GetRequestId() const
{
    return myRequestId;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F700070
inline void PM_BbValue::SetRequestId(CT_PM_RequestId theRequestId)
{
    myRequestId = theRequestId;

}

//-----------------------------------------------------------------
//##ModelId=3C9255C000A9
inline int PM_BbValue::GetNumberOfParam() const
{
    return myNumberOfParam;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA402EF
inline FC_Time PM_BbValue::GetStartTime() const
{
    return myStartTime;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA40227
inline void PM_BbValue::SetStartTime(FC_Time theStartTime)
{
    myStartTime = theStartTime;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA50029
inline FC_Time PM_BbValue::GetEndTime() const
{
    return myEndTime;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA40349
inline void PM_BbValue::SetEndTime(FC_Time theEndTime)
{
    myEndTime = theEndTime;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA5012E
inline PM_BbIdf* PM_BbValue::GetIdf()
{
    return myIdf;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA501BA
inline PM_BbTca* PM_BbValue::GetMaxTca()
{
    return myMaxTca;

}

#endif //PM_BBVALUE_H

