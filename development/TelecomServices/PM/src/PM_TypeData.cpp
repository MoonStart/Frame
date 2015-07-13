/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     9 April, 1999 Dominic Levesque.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeData.h>

//##ModelId=3FA164C00233
CT_PM_64BitValue PM_TypeData::myMaxValueTableData15M[PM_PARAM_NUM];
//##ModelId=3FA164C00243
CT_PM_64BitValue PM_TypeData::myMaxValueTableDataDay[PM_PARAM_NUM];

string PM_TypeData::PM_ParamNameTable[] =
{
    "loss",
    "cv",
    "se",
    "sefs",
    "ses",
    "es",
    "seh"
};

string PM_TypeData::PM_ParamUnitTable[] =
{
    "s",
    "error",
    "symbol error",
    "s",
    "s",
    "s",
    "symbol error"
};

//-------------------------------------------------------------
//##ModelId=3C9255B70019
PM_TypeData::PM_TypeData()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableData15M[PM_LOSS].UnsignedValue       = 900;
    myMaxValueTableData15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableData15M[PM_SE].UnsignedValue         = 2147483647;
    myMaxValueTableData15M[PM_SEFS].UnsignedValue       = 900;
    myMaxValueTableData15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableData15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableData15M[PM_SE_HIGH].UnsignedValue    = 0xffffffffffffffffULL;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableDataDay[PM_LOSS].UnsignedValue       = 86400;
    myMaxValueTableDataDay[PM_CV].UnsignedValue         = 0xffffffff;
    myMaxValueTableDataDay[PM_SE].UnsignedValue         = 2147483647;
    myMaxValueTableDataDay[PM_SEFS].UnsignedValue       = 86400;
    myMaxValueTableDataDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableDataDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableDataDay[PM_SE_HIGH].UnsignedValue    = 0xffffffffffffffffULL;

    done = true;

}

//-------------------------------------------------------------
//##ModelId=3C9255B7001A
PM_TypeData::~PM_TypeData()
{
    // Nothing to do for now.

}

CT_PMA_ParamId
PM_TypeData::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_LOSS:
		paramId = PMA_LOSS_PARAMETER;
		break;

	case PM_CV:
		paramId = PMA_CV_S_PARAMETER;
		break;

	case PM_SE:
		paramId = PMA_SE_PARAMETER;
		break;

	case PM_SEFS:
		paramId = PMA_SEFS_S_PARAMETER;
		break;

	case PM_SES:
		paramId = PMA_SES_S_PARAMETER;
		break;

	case PM_ES:
		paramId = PMA_ES_S_PARAMETER;
		break;

	case PM_SE_HIGH:
		paramId = PMA_SE_HIGH_PARAMETER;
		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeData::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeData::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

