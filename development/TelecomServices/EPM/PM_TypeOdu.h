/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Base for PM parameters definition for ODU layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEODU_H
#define PM_TYPEODU_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>


//Base class for PM parameters of the ODU type 
//This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of the ODU layer. The last 
//element, PM_PARAM_NUM, defines the number of parameters for 
//this layer.
class PM_TypeOdu
{

public:

    //Default constructor.
    PM_TypeOdu();

    //Default destructor.
    virtual ~PM_TypeOdu();  

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        //PM Parameter Code Violation .
        PM_CV,

        //PM Parameter Errored Second.
        PM_ES,

        //PM Parameter Severely Errored Second.
        PM_SES,

        //PM Parameter Unavailable Seconds.
        PM_UAS,

        //PM Parameter Unavailable Seconds.
        PM_PSC,

        //PM Parameter Unavailable Seconds.
        PM_PSD,

        //======================================================
        // WARNING!!! High Order Bit param(s) must be at end!
        // Insert any -new- param(s) above High Order Bit(s)!
        //======================================================

        //PM Parameter Code Violation - High Order Bit (64bit).
        PM_CV_HIGH,

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
    inline static CT_PM_64BitValue* GetMaxValueTableOdu15M()
    {
        return myMaxValueTableOdu15M;
    }

    //This method returns a pointer to a table that contains 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_64BitValue* GetMaxValueTableOduDay()
    {
        return myMaxValueTableOduDay;
    }

    inline static uint16 GetMaxNbParams(CT_EntityType theEntityType)
    {
        if ( theEntityType == CT_ODU4 ) // HIGH order param needed!
        {
            return (PM_TypeOdu::PM_PARAM_NUM);
        }
        else // do NOT need HIGH order param!
        {
            return (PM_TypeOdu::PM_PARAM_NUM - 1);
        }
    }
 
    inline static uint16 GetMaxNbParamsNoHighOrder64Bits()
    {
        // do NOT need HIGH order param!
        return (PM_TypeOdu::PM_PARAM_NUM - 1);
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    static CT_PM_64BitValue myMaxValueTableOdu15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_64BitValue myMaxValueTableOduDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};


//------------------------
// Class PM_TypeOduGauge
//------------------------

class PM_TypeOduGauge
{

public:

    //Default constructor.
    PM_TypeOduGauge();

    //Default destructor.
    virtual ~PM_TypeOduGauge();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        // PM Parameter Utilization
        PM_DELAY,

        //Number of PM Parameters
        PM_PARAM_NUM
    };

	// Converts subapp/layer param ID to PMA param ID.
	static CT_PMA_ParamId ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType = CT_PM_PARAM_CURRENT );

    // Method to return the name string of the indicated parameter.
    static string& GetParamName( CT_PM_Parameter theParameter );

    // Method to return the unit string of the indicated parameter.
    static string& GetParamUnit( CT_PM_Parameter theParameter );

    //This method returns a pointer to a table that contained 
    //the maximum value parameters can have for an 
    //accumulation period of 15 minutes.
    inline static CT_PM_Value* GetMaxValueTableOdu15M()
    {
        return myMaxValueTableOdu15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableOduDay()
    {
        return myMaxValueTableOduDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    static CT_PM_Value myMaxValueTableOdu15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableOduDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPEODU_H

