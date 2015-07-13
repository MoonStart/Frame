/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     27 February 2006   Larry Wolfrum.
 DESCRIPTION:   Base for PM parameters definition for Far-End
                SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEHOPFAREND_H
#define PM_TYPEHOPFAREND_H

#include <gdef.h>
#include <PM/PM_Def.h>


//Base class for PM parameters of the Far-End SONET/SDH HOP type 
//This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of the Far-End HOP layer. The last 
//element, PM_PARAM_NUM, defines the number of parameters for 
//this layer.
class PM_TypeHopFarEnd
{

public:

    //Default constructor.
    PM_TypeHopFarEnd();

    //Default destructor.
    virtual ~PM_TypeHopFarEnd();  

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        //PM Parameter Code Violation .
        PM_CV,
        //PM Parameter Severely Errored Second.
        PM_SES,
        //PM Parameter Errored Second.
        PM_ES,
        //PM Parameter Unavailable Seconds.
        PM_UAS,
        //PM Parameter AIS Seconds.
        PM_FC,
        //Number of PM Parameters
        PM_PARAM_NUM
    };

     //This method returns a pointer to a table that contains 
     //the maximum value parameters can have for an 
     //accumulation period of 15 minutes.
    inline static CT_PM_Value* GetMaxValueTableHopFarEnd15M()
    {
        return myMaxValueTableHopFarEnd15M;
    }

    //This method returns a pointer to a table that contains 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableHopFarEndDay()
    {
        return myMaxValueTableHopFarEndDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    static CT_PM_Value myMaxValueTableHopFarEnd15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableHopFarEndDay[PM_PARAM_NUM];

};

#endif //PM_TYPEHOPFAREND_H

