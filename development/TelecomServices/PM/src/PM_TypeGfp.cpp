/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004  Hemant Thakkar.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeGfp.h>


CT_PM_Value PM_TypeGfp::myMaxValueTableGfp15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeGfp::myMaxValueTableGfpDay[PM_PARAM_NUM];

//-------------------------------------------------------------
PM_TypeGfp::PM_TypeGfp()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableGfp15M[PM_10B_ERR].UnsignedValue    = 57600000;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableGfpDay[PM_10B_ERR].UnsignedValue    = 2147483647;

    done = true;

}

//-------------------------------------------------------------
PM_TypeGfp::~PM_TypeGfp()
{
    // Nothing to do for now.
}
