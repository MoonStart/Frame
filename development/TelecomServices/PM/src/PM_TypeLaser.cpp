/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Transponders.
 AUTHOR   :     December 13, 2001 Sebastien Cossette
 DESCRIPTION:   Base for PM parameters definition of the Laser.
--------------------------------------------------------------------------*/

#include <PM_TypeLaser.h>


//##ModelId=3FA164BF03C9
CT_PM_Value PM_TypeLaser::myMaxValueTableLaser15M[PM_PARAM_NUM];
//##ModelId=3FA164BF03D9
CT_PM_Value PM_TypeLaser::myMaxValueTableLaserDay[PM_PARAM_NUM];

string PM_TypeLaser::PM_ParamNameTable[] =
{
    "lt",
    "lbc"
};

string PM_TypeLaser::PM_ParamUnitTable[] =
{
    "milliCelsius",
    "%"
};

//-------------------------------------------------------------
//##ModelId=3E6E4CD00216
PM_TypeLaser::PM_TypeLaser()
{
    static bool done = false;

    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableLaser15M[PM_LT].SignedValue      = 20000;
    myMaxValueTableLaser15M[PM_LBC].SignedValue     = 255;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableLaserDay[PM_LT].SignedValue      = 20000;
    myMaxValueTableLaserDay[PM_LBC].SignedValue     = 255;

    done = true;

}

//-------------------------------------------------------------
//##ModelId=3E6E4CD00217
PM_TypeLaser::~PM_TypeLaser()
{
    // Nothing to do for now.

}

CT_PMA_ParamId
PM_TypeLaser::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_LT:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_LT_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_LT_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_LT_C_PARAMETER;
			break;

		default:
			paramId = PMA_INVALID_PARAMETER;
			break;
		}

		break;

	case PM_LBC:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_LBC_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_LBC_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_LBC_C_PARAMETER;
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

string& PM_TypeLaser::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeLaser::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}
