/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 February 2004  Hemant Thakkar.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeMsNearEnd.h>


CT_PM_Value PM_TypeMsNearEnd::myMaxValueTableMsNearEnd15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeMsNearEnd::myMaxValueTableMsNearEndDay[PM_PARAM_NUM];

string PM_TypeMsNearEnd::PM_ParamNameTable[] =
{
    "cv",
    "ses",
    "es",
    "uas",
    "aiss",
    "fc",
    "psc",
    "psd"
};

string PM_TypeMsNearEnd::PM_ParamUnitTable[] =
{
    "error",
    "s",
    "s",
    "s",
    "s",
    "failure cnt",
    "prot sw cnt",
    "s"
};

//-------------------------------------------------------------
PM_TypeMsNearEnd::PM_TypeMsNearEnd()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableMsNearEnd15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableMsNearEnd15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableMsNearEnd15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableMsNearEnd15M[PM_UAS].UnsignedValue        = 900;
    myMaxValueTableMsNearEnd15M[PM_AISS].UnsignedValue       = 900;
    myMaxValueTableMsNearEnd15M[PM_FC].UnsignedValue         = 72;
    myMaxValueTableMsNearEnd15M[PM_PSC].UnsignedValue        = 900;
    myMaxValueTableMsNearEnd15M[PM_PSD].UnsignedValue        = 900;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableMsNearEndDay[PM_CV].UnsignedValue         = 0xffffffff;
    myMaxValueTableMsNearEndDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableMsNearEndDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableMsNearEndDay[PM_UAS].UnsignedValue        = 86400;
    myMaxValueTableMsNearEndDay[PM_AISS].UnsignedValue       = 86400;
    myMaxValueTableMsNearEndDay[PM_FC].UnsignedValue         = 6912;
    myMaxValueTableMsNearEndDay[PM_PSC].UnsignedValue        = 86400;
    myMaxValueTableMsNearEndDay[PM_PSD].UnsignedValue        = 86400;

    done = true;

}

//-------------------------------------------------------------
PM_TypeMsNearEnd::~PM_TypeMsNearEnd()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeMsNearEnd::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_CV:
		paramId = PMA_CV_L_PARAMETER;
		break;

	case PM_SES:
		paramId = PMA_SES_L_PARAMETER;
		break;

	case PM_ES:
		paramId = PMA_ES_L_PARAMETER;
		break;

	case PM_UAS:
		paramId = PMA_UAS_L_PARAMETER;
		break;

	case PM_AISS:
		paramId = PMA_AISS_L_PARAMETER;
		break;

	case PM_FC:
		paramId = PMA_FC_L_PARAMETER;
		break;

	case PM_PSC:
		paramId = PMA_PSC_L_PARAMETER;
		break;

	case PM_PSD:
		paramId = PMA_PSD_L_PARAMETER;
		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeMsNearEnd::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeMsNearEnd::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}
