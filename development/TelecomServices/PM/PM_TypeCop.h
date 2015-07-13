/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   Base for PM parameters definition for Optical Channel.
--------------------------------------------------------------------------*/

#ifndef PM_TYPECOP_H
#define PM_TYPECOP_H

#include <gdef.h>
#include <PM/PM_Def.h>


//Base class for PM parameters of the Optical Channel. This 
//class contains a PM_Param enum definition. Each enum 
//element is a PM parameter related to Optical Channel. The last 
//element, PM_PARAM_NUM, defines the number of parameters for 
//this layer.
//##ModelId=3C9255B10151
class PM_TypeCop
{

public:

    //Class default constructor.
    //##ModelId=3C9255B103B4
    PM_TypeCop();

    //Class default destructor.
    //##ModelId=3C9255B103B5
    virtual ~PM_TypeCop();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    //##ModelId=3C9255B20058
    enum PM_Param
    {
        // PM Parameter Channel Optical Power.
        //##ModelId=3C9255B20185
        PM_COP = 0,

        //Number of PM Parameters
        //##ModelId=3C9255B2018F
        PM_PARAM_NUM
    };

    // Method to return the name string of the indicated parameter.
    static string& GetParamName( CT_PM_Parameter theParameter );

    // Method to return the unit string of the indicated parameter.
    static string& GetParamUnit( CT_PM_Parameter theParameter );

     //This method returns a pointer to a table that contained 
     //the maximum value parameters can have for an 
     //accumulation period of 15 minutes.
    //##ModelId=3C9255B103BE
    inline static CT_PM_Value* GetMaxValueTableCop15M()
    {
        return myMaxValueTableCop15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    //##ModelId=3C9255B103D3
    inline static CT_PM_Value* GetMaxValueTableCopDay()
    {
        return myMaxValueTableCopDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    //##ModelId=3FA164C0010A
    static CT_PM_Value myMaxValueTableCop15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    //##ModelId=3FA164C0011A
    static CT_PM_Value myMaxValueTableCopDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPECOP_H

