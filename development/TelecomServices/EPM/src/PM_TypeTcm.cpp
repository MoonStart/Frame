
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Base for PM parameters definition for TCM layer.
--------------------------------------------------------------------------*/

#include <EPM/PM_TypeTcm.h>


CT_PM_64BitValue PM_TypeTcm::myMaxValueTableTcm15M[PM_PARAM_NUM];
CT_PM_64BitValue PM_TypeTcm::myMaxValueTableTcmDay[PM_PARAM_NUM];

string PM_TypeTcm::PM_ParamNameTable[] =
{
    "cv",
    "es",
    "ses",
    "uas",
    "cvh"
};

string PM_TypeTcm::PM_ParamUnitTable[] =
{
    "error",
    "s",
    "s",
    "s",
    "s"
};

//-------------------------------------------------------------
PM_TypeTcm::PM_TypeTcm()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableTcm15M[PM_CV].UnsignedValue         = 57600000;
    myMaxValueTableTcm15M[PM_CV_HIGH].UnsignedValue    = 9223372036854775808;
    myMaxValueTableTcm15M[PM_SES].UnsignedValue        = 900;
    myMaxValueTableTcm15M[PM_ES].UnsignedValue         = 900;
    myMaxValueTableTcm15M[PM_UAS].UnsignedValue        = 900;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableTcmDay[PM_CV].UnsignedValue         = 2147483647;
    myMaxValueTableTcmDay[PM_CV_HIGH].UnsignedValue    = 9223372036854775808;
    myMaxValueTableTcmDay[PM_SES].UnsignedValue        = 86400;
    myMaxValueTableTcmDay[PM_ES].UnsignedValue         = 86400;
    myMaxValueTableTcmDay[PM_UAS].UnsignedValue        = 86400;

    done = true;
}

//-------------------------------------------------------------
PM_TypeTcm::~PM_TypeTcm()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeTcm::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_CV:
		paramId = PMA_CV_ODUKT_PARAMETER;
		break;

	case PM_ES:
		paramId = PMA_ES_ODUKT_PARAMETER;
		break;

	case PM_SES:
		paramId = PMA_SES_ODUKT_PARAMETER;
		break;

	case PM_UAS:
		paramId = PMA_UAS_ODUKT_PARAMETER;
		break;

	case PM_CV_HIGH:
		paramId = PMA_CV_ODUKT_HIGH_PARAMETER;
		break;

	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeTcm::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeTcm::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
 
CT_PM_Value PM_TypeTcmGauge::myMaxValueTableTcm15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeTcmGauge::myMaxValueTableTcmDay[PM_PARAM_NUM];
 
string PM_TypeTcmGauge::PM_ParamNameTable[] =
{
    "delay"
};
 
string PM_TypeTcmGauge::PM_ParamUnitTable[] =
{
    "s"
};
 
//-------------------------------------------------------------
PM_TypeTcmGauge::PM_TypeTcmGauge()
{
    static bool done = false;
    if (done) return;
 
    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableTcm15M[PM_DELAY].SignedValue       = 2147483647;
 
    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableTcmDay[PM_DELAY].SignedValue       = 2147483647;
 
    done = true;
}
 
//-------------------------------------------------------------
PM_TypeTcmGauge::~PM_TypeTcmGauge()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeTcmGauge::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
    CT_PMA_ParamId paramId;
 
    switch( theParamId )
    {
    case PM_DELAY:
 
        switch( theParamType )
        {
        case CT_PM_PARAM_CURRENT:
            paramId = PMA_DELAY_ODUKT_PARAMETER;
            break;
    
        case CT_PM_PARAM_MIN:
            paramId = PMA_DELAY_ODUKT_F_PARAMETER;
            break;
    
        case CT_PM_PARAM_MAX:
            paramId = PMA_DELAY_ODUKT_C_PARAMETER;
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
 
string& PM_TypeTcmGauge::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}
 
string& PM_TypeTcmGauge::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}

