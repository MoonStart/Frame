/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Base for PM parameters definition for ODU layer.
--------------------------------------------------------------------------*/

#include <EPM/PM_TypeOdu.h>


CT_PM_64BitValue PM_TypeOdu::myMaxValueTableOdu15M[PM_PARAM_NUM];
CT_PM_64BitValue PM_TypeOdu::myMaxValueTableOduDay[PM_PARAM_NUM];

string PM_TypeOdu::PM_ParamNameTable[] =
{
    "cv",
    "es",
    "ses",
    "uas",
    "psc",
    "psd",
    "cvh"
};

string PM_TypeOdu::PM_ParamUnitTable[] =
{
    "error",
    "s",
    "s",
    "s",
    "prot sw cnt",
    "s",
    "s"
};

//-------------------------------------------------------------
PM_TypeOdu::PM_TypeOdu()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOdu15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableOdu15M[PM_CV_HIGH].UnsignedValue    = 9223372036854775808;
    myMaxValueTableOdu15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableOdu15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableOdu15M[PM_UAS].UnsignedValue        = 900;
    myMaxValueTableOdu15M[PM_PSC].UnsignedValue        = 18000;
    myMaxValueTableOdu15M[PM_PSD].UnsignedValue        = 900;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableOduDay[PM_CV].UnsignedValue         = 2147483647;
    myMaxValueTableOduDay[PM_CV_HIGH].UnsignedValue    = 9223372036854775808;
    myMaxValueTableOduDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableOduDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableOduDay[PM_UAS].UnsignedValue        = 86400;
    myMaxValueTableOduDay[PM_PSC].UnsignedValue        = 17280000;
    myMaxValueTableOduDay[PM_PSD].UnsignedValue        = 86400;

    done = true;
}

//-------------------------------------------------------------
PM_TypeOdu::~PM_TypeOdu()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeOdu::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_CV:
		paramId = PMA_CV_ODU_PARAMETER;
		break;

	case PM_ES:
		paramId = PMA_ES_ODU_PARAMETER;
		break;

	case PM_SES:
		paramId = PMA_SES_ODU_PARAMETER;
		break;

	case PM_UAS:
		paramId = PMA_UAS_ODU_PARAMETER;
		break;

	case PM_PSC:
		paramId = PMA_PSC_ODU_PARAMETER;
		break;

	case PM_PSD:
		paramId = PMA_PSD_ODU_PARAMETER;
		break;

	case PM_CV_HIGH:
		paramId = PMA_CV_ODU_HIGH_PARAMETER;
		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeOdu::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOdu::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CT_PM_Value PM_TypeOduGauge::myMaxValueTableOdu15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeOduGauge::myMaxValueTableOduDay[PM_PARAM_NUM];

string PM_TypeOduGauge::PM_ParamNameTable[] =
{
    "delay"
};

string PM_TypeOduGauge::PM_ParamUnitTable[] =
{
    "s"
};

//-------------------------------------------------------------
PM_TypeOduGauge::PM_TypeOduGauge()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOdu15M[PM_DELAY].SignedValue       = 2147483647;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableOduDay[PM_DELAY].SignedValue       = 2147483647;

    done = true;
}

//-------------------------------------------------------------
PM_TypeOduGauge::~PM_TypeOduGauge()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeOduGauge::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_DELAY:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_DELAY_ODU_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_DELAY_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_DELAY_C_PARAMETER;
			break;

		default:
			paramId = PMA_INVALID_PARAMETER;
			break;
		}

		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeOduGauge::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOduGauge::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

