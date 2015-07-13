/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeOms.h>


//##ModelId=3FA164BE039B
CT_PM_Value PM_TypeOms::myMaxValueTableOms15M[PM_PARAM_NUM];
//##ModelId=3FA164BE03AA
CT_PM_Value PM_TypeOms::myMaxValueTableOmsDay[PM_PARAM_NUM];

string PM_TypeOms::PM_ParamNameTable[] =
{
    "opr",
    "opt"
};

string PM_TypeOms::PM_ParamUnitTable[] =
{
    "x100 dBm",
    "x100 dBm"
};

//-------------------------------------------------------------
//##ModelId=3C9255B401F6
PM_TypeOms::PM_TypeOms()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOms15M[PM_OPR].SignedValue       = 6000;
    myMaxValueTableOms15M[PM_OPT].SignedValue       = 6000;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableOmsDay[PM_OPR].SignedValue       = 6000;
    myMaxValueTableOmsDay[PM_OPT].SignedValue       = 6000;

    done = true;
}

//-------------------------------------------------------------
//##ModelId=3C9255B4020A
PM_TypeOms::~PM_TypeOms()
{
    // Nothing to do for now.

}

string& PM_TypeOms::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOms::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

