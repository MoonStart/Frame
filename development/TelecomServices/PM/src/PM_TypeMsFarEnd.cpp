/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 February 2004  Hemant Thakkar.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeMsFarEnd.h>


//##ModelId=3FA164C00233
CT_PM_Value PM_TypeMsFarEnd::myMaxValueTableMsFarEnd15M[PM_PARAM_NUM];
//##ModelId=3FA164C00243
CT_PM_Value PM_TypeMsFarEnd::myMaxValueTableMsFarEndDay[PM_PARAM_NUM];

//-------------------------------------------------------------
PM_TypeMsFarEnd::PM_TypeMsFarEnd()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableMsFarEnd15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableMsFarEnd15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableMsFarEnd15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableMsFarEnd15M[PM_UAS].UnsignedValue        = 900;
    myMaxValueTableMsFarEnd15M[PM_AISS].UnsignedValue       = 900;
    myMaxValueTableMsFarEnd15M[PM_FC].UnsignedValue         = 72;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableMsFarEndDay[PM_CV].UnsignedValue         = 0xffffffff;
    myMaxValueTableMsFarEndDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableMsFarEndDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableMsFarEndDay[PM_UAS].UnsignedValue        = 86400;
    myMaxValueTableMsFarEndDay[PM_AISS].UnsignedValue       = 86400;
    myMaxValueTableMsFarEndDay[PM_FC].UnsignedValue         = 6912;

    done = true;

}

//-------------------------------------------------------------
PM_TypeMsFarEnd::~PM_TypeMsFarEnd()
{
    // Nothing to do for now.
}
