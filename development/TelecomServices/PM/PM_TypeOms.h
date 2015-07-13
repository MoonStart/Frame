/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Base for PM parameters definition for Oms Layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEOMS_H
#define PM_TYPEOMS_H

#include <gdef.h>
#include <PM/PM_Def.h>


//Base class for PM parameters of the Oms. This class 
//contains a PM_Param enum definition. Each enum element is a 
//PM parameter of the Oms. The last element, 
//PM_PARAM_NUM, defines the number of parameters for this 
//layer.
//##ModelId=3C9255B30385
class PM_TypeOms
{

public:

    //Default constructor.
    //##ModelId=3C9255B401F6
    PM_TypeOms();

    //Default destructor.
    //##ModelId=3C9255B4020A
    virtual ~PM_TypeOms();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    //##ModelId=3C9255B4028C
    enum PM_Param
    {
        // PM Parameter Oms Power Received.
        //##ModelId=3C9255B403E1
        PM_OPR,
        // PM Parameter Oms Power Transmitted
        //##ModelId=3C9255B50003
        PM_OPT,

        //Number of PM Parameters
        //##ModelId=3C9255B50017
        PM_PARAM_NUM
    };

    // Method to return the name string of the indicated parameter.
    static string& GetParamName( CT_PM_Parameter theParameter );

    // Method to return the unit string of the indicated parameter.
    static string& GetParamUnit( CT_PM_Parameter theParameter );

    //This method returns a pointer to a table that contained 
    //the maximum value parameters can have for an 
    //accumulation period of 15 minutes.
    //##ModelId=3E6E4C9303BD
    inline static CT_PM_Value* GetMaxValueTableOms15M()
    {
        return myMaxValueTableOms15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    //##ModelId=3E6E4C9303DB
    inline static CT_PM_Value* GetMaxValueTableOmsDay()
    {
        return myMaxValueTableOmsDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    //##ModelId=3FA164BE039B
    static CT_PM_Value myMaxValueTableOms15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    //##ModelId=3FA164BE03AA
    static CT_PM_Value myMaxValueTableOmsDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPEOMS_H

