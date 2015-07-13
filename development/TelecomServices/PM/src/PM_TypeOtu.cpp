/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeOtu.h>
#include <CommonTypes/CT_Float32.h>
#include <CsPii/CSPII_CardIF.h>

CT_PM_64BitValue PM_TypeOtu::myMaxValueTableOtu15M[PM_PARAM_NUM];
CT_PM_64BitValue PM_TypeOtu::myMaxValueTableOtuDay[PM_PARAM_NUM];

string PM_TypeOtu::PM_ParamNameTable[] =
{
    "be",
    "ube",
    "cv",
    "es",
    "ses",
    "uas",
    "psc",
    "psd",
    "cvh",
    "beh"
};

string PM_TypeOtu::PM_ParamUnitTable[] =
{
    "error",
    "error",
    "error",
    "s",
    "s",
    "s",
    "prot sw cnt",
    "s",
    "s",
    "s"
};

//-------------------------------------------------------------
//##ModelId=3C9255A8002C
PM_TypeOtu::PM_TypeOtu()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOtu15M[PM_BE].UnsignedValue      = 0xffffffff;
    myMaxValueTableOtu15M[PM_BE_HIGH].UnsignedValue = 9223372036854775808ULL;
    myMaxValueTableOtu15M[PM_UBE].UnsignedValue     = 2147483647;
    myMaxValueTableOtu15M[PM_CV].UnsignedValue      = 57600000;
    myMaxValueTableOtu15M[PM_CV_HIGH].UnsignedValue = 9223372036854775808ULL;
    myMaxValueTableOtu15M[PM_PSC].UnsignedValue     = 18000;
    myMaxValueTableOtu15M[PM_PSD].UnsignedValue     = 900;
    myMaxValueTableOtu15M[PM_ES].UnsignedValue      = 900;
    myMaxValueTableOtu15M[PM_SES].UnsignedValue     = 900;
    myMaxValueTableOtu15M[PM_UAS].UnsignedValue     = 900;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableOtuDay[PM_BE].UnsignedValue      = 0xffffffff;
    myMaxValueTableOtuDay[PM_BE_HIGH].UnsignedValue = 9223372036854775808ULL;
    myMaxValueTableOtuDay[PM_UBE].UnsignedValue     = 2147483647;
    myMaxValueTableOtuDay[PM_CV].UnsignedValue      = 0xffffffff;
    myMaxValueTableOtuDay[PM_CV_HIGH].UnsignedValue = 9223372036854775808ULL;
    myMaxValueTableOtuDay[PM_PSC].UnsignedValue     = 1728000;
    myMaxValueTableOtuDay[PM_PSD].UnsignedValue     = 86400;
    myMaxValueTableOtuDay[PM_ES].UnsignedValue      = 86400;
    myMaxValueTableOtuDay[PM_SES].UnsignedValue     = 86400;
    myMaxValueTableOtuDay[PM_UAS].UnsignedValue     = 86400;

    done = true;

}

//-------------------------------------------------------------
//##ModelId=3C9255A80036
PM_TypeOtu::~PM_TypeOtu()
{
    // Nothing to do for now.

}

CT_PMA_ParamId
PM_TypeOtu::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_BE:
		paramId = PMA_BE_PARAMETER;
		break;

	case PM_UBE:
		paramId = PMA_UBE_PARAMETER;
		break;

	case PM_CV:
		paramId = PMA_CV_OTU_PARAMETER;
		break;

	case PM_ES:
		paramId = PMA_ES_OTU_PARAMETER;
		break;

	case PM_SES:
		paramId = PMA_SES_OTU_PARAMETER;
		break;

	case PM_UAS:
		paramId = PMA_UAS_OTU_PARAMETER;
		break;

	case PM_PSC:
		paramId = PMA_PSC_O_PARAMETER;
		break;

	case PM_PSD:
		paramId = PMA_PSD_O_PARAMETER;
		break;

	case PM_CV_HIGH:
		paramId = PMA_CV_OTU_HIGH_PARAMETER;
		break;

	case PM_BE_HIGH:
		paramId = PMA_BE_HIGH_PARAMETER;
		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeOtu::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOtu::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}


//--------------------------
// Class PM_TypeOtuGauge
//--------------------------

CT_PM_Value PM_TypeOtuGauge::myMaxValueTableOtu15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeOtuGauge::myMaxValueTableOtuDay[PM_PARAM_NUM];

string PM_TypeOtuGauge::PM_ParamNameTable[] =
{
    "ber"
};

string PM_TypeOtuGauge::PM_ParamUnitTable[] =
{
    "ratio"
};

//-------------------------------------------------------------
PM_TypeOtuGauge::PM_TypeOtuGauge()
{
    static bool done = false;
    CT_Float32  maxValue(2.0E-3);
    CT_Float32  maxValueHGTM(1.9E-2);
    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
    bool a100GCard = (aCardType == HGTM || aCardType == HGTMS || aCardType == HGTMM || aCardType == HGTMMS || aCardType == OSM2C || aCardType == OSM2S) ? true : false; // Coriant HGTMMS // Coriant HGTMS

    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOtu15M[PM_BER].UnsignedValue       = (a100GCard) ? maxValueHGTM.GetValue() : maxValue.GetValue();

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableOtuDay[PM_BER].UnsignedValue       = (a100GCard) ? maxValueHGTM.GetValue() : maxValue.GetValue();

    done = true;
}

//-------------------------------------------------------------
PM_TypeOtuGauge::~PM_TypeOtuGauge()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeOtuGauge::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_BER:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_BER_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_BER_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_BER_C_PARAMETER;
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

string& PM_TypeOtuGauge::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOtuGauge::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

