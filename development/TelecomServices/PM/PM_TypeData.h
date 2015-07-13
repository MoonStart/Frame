/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     9 April, 1999 Dominic Levesque.
 DESCRIPTION:   Base for PM parameters definition for Data layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEDATA_H
#define PM_TYPEDATA_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>


//Base class for PM parameters of the Data type (RS, ESCON, FICON,
//GbE and GOPT). This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of the Data. The last 
//element, PM_PARAM_NUM, defines the number of parameters for 
//this layer.
//##ModelId=3C9255B601A9
class PM_TypeData
{

public:

    //Default constructor.
    //##ModelId=3C9255B70019
    PM_TypeData();

    //Default destructor.
    //##ModelId=3C9255B7001A
    virtual ~PM_TypeData();  

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    //##ModelId=3C9255B70074
    enum PM_Param
    {
        //PM Parameter Loss Of Signal Second.
        //##ModelId=3C9255B701A0
        PM_LOSS = 0,
        //PM Parameter Code Violation (RS only).
        //##ModelId=3C9255B701AA
        PM_CV,
        //PM Parameter Symbol Error (FICON, ESCON and GbE only).
        //##ModelId=3E6E4CDB02B2
        PM_SE,
        //PM Parameter Severely Errored Frame Second (RS only).
        //##ModelId=3C9255B701BE
        PM_SEFS,
        //PM Parameter Severely Errored Second (RS only).
        //##ModelId=3C9255B701C8
        PM_SES,
        //PM Parameter Errored Second (RS only).
        //##ModelId=3C9255B701D2
        PM_ES,
 
        //======================================================
        // WARNING!!! High Order Bit param(s) must be at end!
        // Insert any -new- param(s) above High Order Bit(s)!
        //======================================================
 
        PM_SE_HIGH,

        //Number of PM Parameters
        //##ModelId=3C9255B701FA
        PM_PARAM_NUM
    };

	// Converts subapp/layer param ID to PMA param ID.
	static CT_PMA_ParamId ConvertPmIdToPmaId( uint32 theParamId );

     //This method returns a pointer to a table that contains 
     //the maximum value parameters can have for an 
     //accumulation period of 15 minutes.
    //##ModelId=3C9255B70023
    inline static CT_PM_64BitValue* GetMaxValueTableData15M()
    {
        return myMaxValueTableData15M;
    }

    //This method returns a pointer to a table that contains 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    //##ModelId=3C9255B7002D
    inline static CT_PM_64BitValue* GetMaxValueTableDataDay()
    {
        return myMaxValueTableDataDay;
    }

    // Method to return the name string of the indicated parameter.
    static string& GetParamName( CT_PM_Parameter theParameter );

    // Method to return the unit string of the indicated parameter.
    static string& GetParamUnit( CT_PM_Parameter theParameter );

    inline static uint16 GetMaxNbParamsNoHighOrder64Bits()
    {
        // do NOT need HIGH order param!
        return (PM_TypeData::PM_PARAM_NUM - 1);
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    //##ModelId=3FA164C00233
    static CT_PM_64BitValue myMaxValueTableData15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    //##ModelId=3FA164C00243
    static CT_PM_64BitValue myMaxValueTableDataDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPEDATA_H

