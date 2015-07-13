/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     December 13, 2001 Sebastien Cossette
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeCop.h>


//##ModelId=3FA164C0010A
CT_PM_Value PM_TypeCop::myMaxValueTableCop15M[PM_PARAM_NUM];
//##ModelId=3FA164C0011A
CT_PM_Value PM_TypeCop::myMaxValueTableCopDay[PM_PARAM_NUM];

string PM_TypeCop::PM_ParamNameTable[] =
{
    "cop"
};

string PM_TypeCop::PM_ParamUnitTable[] =
{
    "x100 dBm"
};


//-------------------------------------------------------------
//##ModelId=3C9255B103B4
PM_TypeCop::PM_TypeCop()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableCop15M[PM_COP].SignedValue       = 6000;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableCopDay[PM_COP].SignedValue       = 6000;

    done = true;

}

//-------------------------------------------------------------
//##ModelId=3C9255B103B5
PM_TypeCop::~PM_TypeCop()
{
    // Nothing to do for now.

}

string& PM_TypeCop::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeCop::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}
