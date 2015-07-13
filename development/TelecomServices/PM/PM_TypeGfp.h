/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     22 Apr 2004  Hemant Thakkar.
 DESCRIPTION:   Base for PM parameters definition for GFP layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEGFP_H
#define PM_TYPEGFP_H

#include <gdef.h>
#include <PM/PM_Def.h>


//Base class for PM parameters of the GFP type 
//This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of the GFP layer. The last 
//element, PM_PARAM_NUM, defines the number of parameters for 
//this layer.
class PM_TypeGfp
{

public:

    //Default constructor.
    PM_TypeGfp();

    //Default destructor.
    virtual ~PM_TypeGfp();  

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        //PM Parameter 10B_ERR .
        PM_10B_ERR,
        //Number of PM Parameters
        PM_PARAM_NUM
    };

     //This method returns a pointer to a table that contains 
     //the maximum value parameters can have for an 
     //accumulation period of 15 minutes.
    inline static CT_PM_Value* GetMaxValueTableGfp15M()
    {
        return myMaxValueTableGfp15M;
    }

    //This method returns a pointer to a table that contains 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableGfpDay()
    {
        return myMaxValueTableGfpDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    static CT_PM_Value myMaxValueTableGfp15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableGfpDay[PM_PARAM_NUM];

};

#endif //PM_TYPEGFP_H

