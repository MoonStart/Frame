/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, December 5, 2001.
 DESCRIPTION:   Base for PM parameters definition for Optical Layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEOPT_H
#define PM_TYPEOPT_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>


//Base class for PM parameters of the Optical. This class 
//contains a PM_Param enum definition. Each enum element is a 
//PM parameter of the Optical. The last element, 
//PM_PARAM_NUM, defines the number of parameters for this 
//layer.
//##ModelId=3E6E4CC300CD
class PM_TypeOpt
{

public:

    //Default constructor.
    //##ModelId=3E6E4CC40241
    PM_TypeOpt();

    //Default destructor.
    //##ModelId=3E6E4CC40242
    virtual ~PM_TypeOpt();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    //##ModelId=3E6E4CC40331
    enum PM_Param
    {
        // PM Parameter Optical Power Received.
        //##ModelId=3E6E4CC501E8
        PM_OPR,
        // PM Parameter Optical Power Transmitted
        //##ModelId=3E6E4CC501FC
        PM_OPT,
        // PM Parameter Differential Group Delay
        PM_DGD,
        // PM Parameter Chromatic Dispersion
        PM_CD,
        // PM Parameter Optical Signal Noise Ratio
        PM_OSNR,

        //Number of PM Parameters
        //##ModelId=3E6E4CC50210
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
    //##ModelId=3E6E4CC40255
    inline static CT_PM_Value* GetMaxValueTableOpt15M()
    {
        return myMaxValueTableOpt15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    //##ModelId=3E6E4CC4026A
    inline static CT_PM_Value* GetMaxValueTableOptDay()
    {
        return myMaxValueTableOptDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    //##ModelId=3FA164BF00AC
    static CT_PM_Value myMaxValueTableOpt15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    //##ModelId=3FA164BF00BE
    static CT_PM_Value myMaxValueTableOptDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

class PM_TypeOptCounter
{

public:

    //Default constructor.
    PM_TypeOptCounter();

    //Default destructor.
    virtual ~PM_TypeOptCounter();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        PM_PSC,
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

    //This method returns a pointer to a table that contained 
    //the maximum value parameters can have for an 
    //accumulation period of 15 minutes.
    inline static CT_PM_Value* GetMaxValueTableOpt15M()
    {
        return myMaxValueTableOpt15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableOptDay()
    {
        return myMaxValueTableOptDay;
    }

    inline static uint16 GetMaxNbParamsNoHighOrder64Bits()
    {
        return (PM_TypeOptCounter::PM_PARAM_NUM);
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    static CT_PM_Value myMaxValueTableOpt15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableOptDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];
};

#endif //PM_TYPEOPT_H

