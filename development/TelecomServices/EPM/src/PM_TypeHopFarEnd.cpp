/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     27 February 2006  Larry Wolfrum.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <EPM/PM_TypeHopFarEnd.h>


CT_PM_Value PM_TypeHopFarEnd::myMaxValueTableHopFarEnd15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeHopFarEnd::myMaxValueTableHopFarEndDay[PM_PARAM_NUM];

//-------------------------------------------------------------
PM_TypeHopFarEnd::PM_TypeHopFarEnd()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableHopFarEnd15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableHopFarEnd15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableHopFarEnd15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableHopFarEnd15M[PM_UAS].UnsignedValue        = 900;
    myMaxValueTableHopFarEnd15M[PM_FC].UnsignedValue         = 72;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableHopFarEndDay[PM_CV].UnsignedValue         = 2147483647;
    myMaxValueTableHopFarEndDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableHopFarEndDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableHopFarEndDay[PM_UAS].UnsignedValue        = 86400;
    myMaxValueTableHopFarEndDay[PM_FC].UnsignedValue         = 6912;

    done = true;

}

//-------------------------------------------------------------
PM_TypeHopFarEnd::~PM_TypeHopFarEnd()
{
    // Nothing to do for now.
}
