/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     August 15, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Parameter Counter values class. Keeps and sets PM 
                parameter counter values.
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTERVALUE_H
#define PM_BBCOUNTERVALUE_H

#include <PM/PM_BbValue.h>


//##ModelId=3E6E4CBD0042
class PM_BbCounterValue : public PM_BbValue
{
public :

    //##ModelId=3E6E4CBE00C7
    PM_BbCounterValue(uint32 numberOfParam, uint32 dummy1 = 0);

    //##ModelId=3E6E4CBE00DB
    virtual ~PM_BbCounterValue();

    //Resets all Values to default.
    //##ModelId=3E6E4CBE00E5
    virtual void Reset();

    //Resets all parameters value.
    //##ModelId=3E6E4CBE00EE
    virtual void ResetAll(void);

    //Same as ResetAll with no argument.
    //##ModelId=3E6E4CBE010C
    virtual void ResetAll(const PM_BbValue &thePreviousValue);

    //Resets current value for one parameter.
    //##ModelId=3E6E4CBE0117
    virtual void ResetCurParam(CT_PM_Parameter theParam);

    //Gets the Value of a parameter.
    //##ModelId=3E6E4CBE0166
    virtual void GetValues(CT_PM_Parameter  theParam, 
                           CT_PM_Value&     theValue, 
                           CT_PM_Value&     theMinValue, 
                           CT_PM_Value&     theMaxValue) const;

};

#endif //PM_BBCOUNTERVALUE_H
