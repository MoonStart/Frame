/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004   Hemant Thakkar.
 DESCRIPTION:   Base for PM parameters definition for Near-End
                SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEMSNEAREND_H
#define PM_TYPEMSNEAREND_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>


//Base class for PM parameters of the Near-End SONET/SDH MS type 
//This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of the Near-End MS layer. The last 
//element, PM_PARAM_NUM, defines the number of parameters for 
//this layer.
class PM_TypeMsNearEnd
{

public:

    //Default constructor.
    PM_TypeMsNearEnd();

    //Default destructor.
    virtual ~PM_TypeMsNearEnd();  

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
        PM_AISS,
        //PM Parameter Failure Counts.
        PM_FC,
        //PM Parameter Protection Switch Count.
        PM_PSC,
        //PM Parameter Protection Switch Duration.
        PM_PSD,
        //Number of PM Parameters
        PM_PARAM_NUM
    };

	// Converts subapp/layer param ID to PMA param ID.
	static CT_PMA_ParamId ConvertPmIdToPmaId( uint32 theParamId );

    // Method to return the name string of the indicated parameter.
    static string& GetParamName( CT_PM_Parameter theParameter );

    // Method to return the unit string of the indicated parameter.
    static string& GetParamUnit( CT_PM_Parameter theParameter );

     //This method returns a pointer to a table that contains 
     //the maximum value parameters can have for an 
     //accumulation period of 15 minutes.
    inline static CT_PM_Value* GetMaxValueTableMsNearEnd15M()
    {
        return myMaxValueTableMsNearEnd15M;
    }

    //This method returns a pointer to a table that contains 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableMsNearEndDay()
    {
        return myMaxValueTableMsNearEndDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    static CT_PM_Value myMaxValueTableMsNearEnd15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableMsNearEndDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPEMSNEAREND_H

