/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   Base for PM parameters definition for Laser.
--------------------------------------------------------------------------*/

#ifndef PM_TYPELASER_H
#define PM_TYPELASER_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>


//Base class for PM parameters of the Laser.
//This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of the Laser. The 
//last element, PM_PARAM_NUM, defines the number of 
//parameters for this layer.
//##ModelId=3E6E4CCF0016
class PM_TypeLaser
{

public:

    //Default constructor.
    //##ModelId=3E6E4CD00216
    PM_TypeLaser();

    //Default destructor.
    //##ModelId=3E6E4CD00217
    virtual ~PM_TypeLaser();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    //##ModelId=3E6E4CD002FC
    enum PM_Param
    {
        // PM Parameter Laser Temperature.
        //##ModelId=3E6E4CD101EF
        PM_LT = 0,
        // PM Parameter Laser Bias Current.
        //##ModelId=3E6E4CD10203
        PM_LBC,

        //Number of PM Parameters
        //##ModelId=3E6E4CD10217
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
    //##ModelId=3E6E4CD00221
    inline static CT_PM_Value* GetMaxValueTableLaser15M()
    {
        return myMaxValueTableLaser15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    //##ModelId=3E6E4CD00234
    inline static CT_PM_Value* GetMaxValueTableLaserDay()
    {
        return myMaxValueTableLaserDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
    //##ModelId=3FA164BF03C9
    static CT_PM_Value myMaxValueTableLaser15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    //##ModelId=3FA164BF03D9
    static CT_PM_Value myMaxValueTableLaserDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPELASER_H

