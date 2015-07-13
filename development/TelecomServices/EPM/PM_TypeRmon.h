/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Teresa L. Chen, Nov 22, 2005
 DESCRIPTION:   Base for PM parameters definition for RMON Ethernet Stats.
--------------------------------------------------------------------------*/

#ifndef PM_TYPERMON_H
#define PM_TYPERMON_H

#include <gdef.h>
#include <PM/PM_Def.h>
#include <CommonTypes/CT_PMA_General.h>

//Base class for PM parameters of the RMON Ethernet Stats. This class 
//contains a PM_Param enum definition. Each enum element is a 
//PM parameter of the RMON Ethernet Stats. The last element, 
//PM_PARAM_NUM, defines the number of parameters for this 
//layer.

//--------------------------
// Class PM_TypeRmonCounter
//--------------------------

class PM_TypeRmonCounter
{

public:

    //Default constructor.
    PM_TypeRmonCounter();

    //Default destructor.
    virtual ~PM_TypeRmonCounter();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        // PM Parameter Number of Dropped Packets
        PM_DROP,
        // PM Parameter Number of Packets
        PM_PKT,
        // PM Parameter Number of Broadcast Packets
        PM_BCPKT,
        // PM Parameter Number of Multicast Packets
        PM_MCPKT,
        // PM Parameter CRC Alignment Error
        PM_CRCAE,
        // PM Parameter Number of Undersize Packets
        PM_USPKT,
        // PM Parameter Number of Oversize Packets
        PM_OSPKT,
        // PM Parameter Number of Packets (< 64 octets) with FCS
        PM_FRAG,
        // PM Parameter Number of Packets (> 1518 octets) with FCS
        PM_JABR,

        //======================================================
        // WARNING!!! High Order Bit param(s) must be at end!
        // Insert any -new- param(s) above High Order Bit(s)!
        //======================================================
 
        PM_DROP_HIGH,
        PM_PKT_HIGH,
        PM_BCPKT_HIGH,
        PM_MCPKT_HIGH,
        PM_CRCAE_HIGH,
        PM_USPKT_HIGH,
        PM_OSPKT_HIGH,
        PM_FRAG_HIGH,
        PM_JABR_HIGH,
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
    inline static CT_PM_64BitValue* GetMaxValueTableRmon15M()
    {
        return myMaxValueTableRmon15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_64BitValue* GetMaxValueTableRmonDay()
    {
        return myMaxValueTableRmonDay;
    }

    inline static uint16 GetMaxNbParamsNoHighOrder64Bits()
    {
        // do NOT need HIGH order param!
        return (PM_TypeRmonCounter::PM_PARAM_NUM - 9);
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    static CT_PM_64BitValue myMaxValueTableRmon15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_64BitValue myMaxValueTableRmonDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];
};


//------------------------
// Class PM_TypeRmonGauge
//------------------------

class PM_TypeRmonGauge
{

public:

    //Default constructor.
    PM_TypeRmonGauge();

    //Default destructor.
    virtual ~PM_TypeRmonGauge();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

    enum PM_Param
    {
        // PM Parameter Utilization
        PM_UTIL,

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
    inline static CT_PM_Value* GetMaxValueTableRmon15M()
    {
        return myMaxValueTableRmon15M;
    }

    //This method returns a pointer to a table that contained 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
    inline static CT_PM_Value* GetMaxValueTableRmonDay()
    {
        return myMaxValueTableRmonDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 minutes period.
    static CT_PM_Value myMaxValueTableRmon15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
    static CT_PM_Value myMaxValueTableRmonDay[PM_PARAM_NUM];

private:

    // Table containing names of parameters for test menu.
    static string PM_ParamNameTable[];

    // Table containing units of parameters for test menu.
    static string PM_ParamUnitTable[];

};

#endif //PM_TYPERMON_H

