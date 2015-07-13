/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002, Sebastien Cossette
 DESCRIPTION:   Base for PM parameters definition for OTU.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEOTU_H
#define PM_TYPEOTU_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>


//Base class for PM parameters of the Optical Transport Unit. 
//This class contains a PM_Param enum definition. Each enum 
//element is a PM parameter of the OTU. The last element, 
//PM_PARAM_NUM, defines the number of parameters for this 
//layer.
//##ModelId=3C9255A701B1
class PM_TypeOtu
{

public:

    //Default constructor.
    //##ModelId=3C9255A8002C
    PM_TypeOtu();

    //Default destructor.
    //##ModelId=3C9255A80036
    virtual ~PM_TypeOtu();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////
    //##ModelId=3C9255A800C2
    enum PM_Param
    {
        //PM Parameter Block error corrected.
        //##ModelId=3C9255A801EF
        PM_BE = 0,
        //PM Parameter Block error uncorrectable.
        //##ModelId=3E6E4CCC00D0
        PM_UBE,
        //PM Parameter for OTU layer Coding Violations
        PM_CV,
        //PM Parameter Errored Second
        PM_ES,
        //PM Parameter Severely Errored Second
        PM_SES,
        //PM Parameter Unavailable Second
        PM_UAS,
        //PM Parameter Protection Switch Count
        PM_PSC,
        //PM Parameter Protection Switch Duration
        PM_PSD,

        //======================================================
        // WARNING!!! High Order Bit param(s) must be at end!
        // Insert any -new- param(s) above High Order Bit(s)!
        //======================================================

        //PM Parameter Code Violation - High Order Bit (64bit).
        PM_CV_HIGH,

        //PM Parameter BE FEC - High Order Bit (64bit).
        PM_BE_HIGH,

		//Number of PM Parameters.
        //##ModelId=3C9255A801F9
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
    //##ModelId=3C9255A80038
    inline static CT_PM_64BitValue* GetMaxValueTableOtu15M()
    {
        return myMaxValueTableOtu15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    //##ModelId=3C9255A80041
    inline static CT_PM_64BitValue* GetMaxValueTableOtuDay()
    {
        return myMaxValueTableOtuDay;
    }

    inline static uint16 GetMaxNbParamsNoHighOrder64Bits()
    {
        // do NOT need HIGH order param!
        return (PM_TypeOtu::PM_PARAM_NUM - 2);
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    //##ModelId=3FA164BF0223
    static CT_PM_64BitValue myMaxValueTableOtu15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    //##ModelId=3FA164BF0233
    static CT_PM_64BitValue myMaxValueTableOtuDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};


//------------------------
// Class PM_TypeOtuGauge
//------------------------

class PM_TypeOtuGauge
{

public:

    //Default constructor.
    PM_TypeOtuGauge();

    //Default destructor.
    virtual ~PM_TypeOtuGauge();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        // PM Parameter Utilization
        PM_BER,

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
    inline static CT_PM_Value* GetMaxValueTableOtu15M()
    {
        return myMaxValueTableOtu15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableOtuDay()
    {
        return myMaxValueTableOtuDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    static CT_PM_Value myMaxValueTableOtu15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableOtuDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPEOTU_H

