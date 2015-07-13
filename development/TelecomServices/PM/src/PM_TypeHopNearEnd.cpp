/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 February 2004  Hemant Thakkar.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeHopNearEnd.h>


CT_PM_Value PM_TypeHopNearEnd::myMaxValueTableHopNearEnd15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeHopNearEnd::myMaxValueTableHopNearEndDay[PM_PARAM_NUM];

string PM_TypeHopNearEnd::PM_ParamNameTable[] =
{
    "cv",
    "es",
    "ses",
    "fc",
    "uas",
    "pjcsdet",
    "pjcsgen",
    "pjcdiff"
};

string PM_TypeHopNearEnd::PM_ParamUnitTable[] =
{
    "error",
    "s",
    "s",
    "failure cnt",
    "s",
    "s",
    "s",
    "count"
};

//-------------------------------------------------------------
PM_TypeHopNearEnd::PM_TypeHopNearEnd()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableHopNearEnd15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableHopNearEnd15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableHopNearEnd15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableHopNearEnd15M[PM_UAS].UnsignedValue        = 900;
    myMaxValueTableHopNearEnd15M[PM_FC].UnsignedValue         = 72;
    myMaxValueTableHopNearEnd15M[PM_PJCSGEN].UnsignedValue	  = 900;
    myMaxValueTableHopNearEnd15M[PM_PJCSDET].UnsignedValue	  = 900;
    myMaxValueTableHopNearEnd15M[PM_PJCDIFF].UnsignedValue	  = 1048575;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableHopNearEndDay[PM_CV].UnsignedValue         = 2147483647;
    myMaxValueTableHopNearEndDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableHopNearEndDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableHopNearEndDay[PM_UAS].UnsignedValue        = 86400;
    myMaxValueTableHopNearEndDay[PM_FC].UnsignedValue         = 6912;
    myMaxValueTableHopNearEndDay[PM_PJCSGEN].UnsignedValue	  = 86400;
    myMaxValueTableHopNearEndDay[PM_PJCSDET].UnsignedValue	  = 86400;
    myMaxValueTableHopNearEndDay[PM_PJCDIFF].UnsignedValue	  = 16777215;

    done = true;

}

//-------------------------------------------------------------
PM_TypeHopNearEnd::~PM_TypeHopNearEnd()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeHopNearEnd::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_CV:
		paramId = PMA_CV_P_PARAMETER;
		break;

	case PM_ES:
		paramId = PMA_ES_P_PARAMETER;
		break;

	case PM_SES:
		paramId = PMA_SES_P_PARAMETER;
		break;

	case PM_FC:
		paramId = PMA_FC_P_PARAMETER;
		break;

	case PM_UAS:
		paramId = PMA_UAS_P_PARAMETER;
		break;

	case PM_PJCSDET:
		paramId = PMA_PJCS_PDET_PARAMETER;
		break;

	case PM_PJCSGEN:
		paramId = PMA_PJCS_PGEN_PARAMETER;
		break;

	case PM_PJCDIFF:
		paramId = PMA_PJCDIFF_P_PARAMETER;
		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeHopNearEnd::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeHopNearEnd::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

