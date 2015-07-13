/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   Base for PM parameters definition for EON layer.
--------------------------------------------------------------------------*/

#ifndef PM_TYPEEON_H
#define PM_TYPEEON_H

#include <gdef.h>
#include <PM/PM_Def.h>


//Base class for PM parameters of the Eon type.
//This class contains a PM_Param enum definition. 
//Each enum element is a PM parameter of Eon. The last 
//element, PM_PARAM_NUM, defines the number of parameters 
//for this layer.
//##ModelId=3FA1610802AA
class PM_TypeEon
{

public:

    //Default constructor.
	//##ModelId=3FA161090027
    PM_TypeEon();

    //Default destructor.
	//##ModelId=3FA161090028
    virtual ~PM_TypeEon();

    ////////////////////////////////////////////////////////////
    // WARNING!!! Changing the order or adding new parameters,
    //            affects the behavior of the inhhibition checking
    //            code, as well as the test command display.
    ////////////////////////////////////////////////////////////

	//##ModelId=3FA161090056
    enum PM_Param
    {
        //PM Parameter ICMP Destination Unreachable Received.
		//##ModelId=3FA161090102
        PM_ICMPDUR = 0,
        //PM Parameter ICMP Destination Unreachable Transmitted.
		//##ModelId=3FA161090112
        PM_ICMPDUT,
        //PM Parameter ICMP Errors Received.
		//##ModelId=3FA161090113
        PM_ICMPER,
        //PM Parameter ICMP Time To Live Exceeded Received.
		//##ModelId=3FA161090114
        PM_ICMPTTLER,
        //PM Parameter IP Address Error Received.
		//##ModelId=3FA161090121
        PM_IPADDER,
        //PM Parameter IP Discards Received.
		//##ModelId=3FA161090122
        PM_IPDISCR,
        //PM Parameter IP Discrard Transmitted.
		//##ModelId=3FA161090123
        PM_IPDISCT,
        //PM Parameter IP Header Errors Received.
		//##ModelId=3FA161090124
        PM_IPHDRR,
        //PM Parameter IP No Routes Transmitted.
		//##ModelId=3FA161090131
        PM_IPNOROUTEST,

        //Number of PM Parameters
		//##ModelId=3FA161090132
        PM_PARAM_NUM
    };

     //This method returns a pointer to a table that contains 
     //the maximum value parameters can have for an 
     //accumulation period of 15 minutes.
	//##ModelId=3FA16109002A
    inline static CT_PM_Value* GetMaxValueTableEon15M()
    {
        return myMaxValueTableEon15M;
    }

    //This method returns a pointer to a table that contains 
    //the maximum value that parameters can have for an 
    //accumulation period of 1-day.
	//##ModelId=3FA16109002C
    inline static CT_PM_Value* GetMaxValueTableEonDay()
    {
        return myMaxValueTableEonDay;
    }

protected:

    // **************15 MINUTE STUFF*************

    //Table that contains the max value for 15 Minute period.
	//##ModelId=3FA164BE0262
    static CT_PM_Value myMaxValueTableEon15M[PM_PARAM_NUM];

    // **************1 DAY MINUTE STUFF*************

    //Table that contains the max value for 1 Day period.
	//##ModelId=3FA164BE0272
    static CT_PM_Value myMaxValueTableEonDay[PM_PARAM_NUM];

};

#endif //PM_TYPEEON_H

