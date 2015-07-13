/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   Base for PM parameters definition for EON layer.
--------------------------------------------------------------------------*/

#include <PM_TypeEon.h>


//##ModelId=3FA164BE0262
CT_PM_Value PM_TypeEon::myMaxValueTableEon15M[PM_PARAM_NUM];
//##ModelId=3FA164BE0272
CT_PM_Value PM_TypeEon::myMaxValueTableEonDay[PM_PARAM_NUM];

//-------------------------------------------------------------
//##ModelId=3FA161090027
PM_TypeEon::PM_TypeEon()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableEon15M[PM_ICMPDUR].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_ICMPDUT].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_ICMPER].UnsignedValue      = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_ICMPTTLER].UnsignedValue   = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_IPADDER].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_IPDISCR].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_IPDISCT].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_IPHDRR].UnsignedValue      = 0xFFFFFFFF;
    myMaxValueTableEon15M[PM_IPNOROUTEST].UnsignedValue = 0xFFFFFFFF;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableEonDay[PM_ICMPDUR].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_ICMPDUT].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_ICMPER].UnsignedValue      = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_ICMPTTLER].UnsignedValue   = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_IPADDER].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_IPDISCR].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_IPDISCT].UnsignedValue     = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_IPHDRR].UnsignedValue      = 0xFFFFFFFF;
    myMaxValueTableEonDay[PM_IPNOROUTEST].UnsignedValue = 0xFFFFFFFF;

    done = true;

}

//-------------------------------------------------------------
//##ModelId=3FA161090028
PM_TypeEon::~PM_TypeEon()
{
    // Nothing to do for now.

}
