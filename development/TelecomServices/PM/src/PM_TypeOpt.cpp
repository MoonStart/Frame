/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Transponders.
 AUTHOR   :     December 13, 2001 Sebastien Cossette
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <PM_TypeOpt.h>
#include <CsPii/CSPII_CardIF.h>


//##ModelId=3FA164BF00AC
CT_PM_Value PM_TypeOpt::myMaxValueTableOpt15M[PM_PARAM_NUM];
//##ModelId=3FA164BF00BE
CT_PM_Value PM_TypeOpt::myMaxValueTableOptDay[PM_PARAM_NUM];

string PM_TypeOpt::PM_ParamNameTable[] =
{
    "opr",
    "opt",
    "dgd",
    "cd",
    "osnr"
};

string PM_TypeOpt::PM_ParamUnitTable[] =
{
    "x100 dBm",
    "x100 dBm",
    "ps",
    "ps/(nm*km)",
    "x100 dBm"
};

//-------------------------------------------------------------
//##ModelId=3E6E4CC40241
PM_TypeOpt::PM_TypeOpt()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOpt15M[PM_OPR].SignedValue       = 6000;
    myMaxValueTableOpt15M[PM_OPT].SignedValue       = 6000;
    if(CSPII_CardIF::GetInstance()->GetCardType() == HGTMS ||
       CSPII_CardIF::GetInstance()->GetCardType() == HGTMMS )
    {
        myMaxValueTableOpt15M[PM_DGD].SignedValue   = 70;
        myMaxValueTableOpt15M[PM_CD].SignedValue    = 40000;
    }
    else
    {
        myMaxValueTableOpt15M[PM_DGD].SignedValue   = 100;
        myMaxValueTableOpt15M[PM_CD].SignedValue    = 70000;
    }
    myMaxValueTableOpt15M[PM_OSNR].SignedValue      = 2100;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableOptDay[PM_OPR].SignedValue       = 6000;
    myMaxValueTableOptDay[PM_OPT].SignedValue       = 6000;
    myMaxValueTableOptDay[PM_CD].SignedValue        = 70000;
    if(CSPII_CardIF::GetInstance()->GetCardType() == HGTMS ||
       CSPII_CardIF::GetInstance()->GetCardType() == HGTMMS )
    {
        myMaxValueTableOptDay[PM_DGD].SignedValue   = 70;
        myMaxValueTableOptDay[PM_CD].SignedValue    = 40000;
    }
    else
    {
        myMaxValueTableOptDay[PM_DGD].SignedValue   = 100;
        myMaxValueTableOptDay[PM_CD].SignedValue    = 70000;
    }
    myMaxValueTableOptDay[PM_OSNR].SignedValue      = 2100;

    done = true;
}

//-------------------------------------------------------------
//##ModelId=3E6E4CC40242
PM_TypeOpt::~PM_TypeOpt()
{
    // Nothing to do for now.

}

CT_PMA_ParamId
PM_TypeOpt::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_OPR:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_OPR_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_OPR_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_OPR_C_PARAMETER;
			break;

		default:
			paramId = PMA_INVALID_PARAMETER;
			break;
		}

		break;

	case PM_OPT:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_OPT_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_OPT_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_OPT_C_PARAMETER;
			break;

		default:
			paramId = PMA_INVALID_PARAMETER;
			break;
		}

		break;

    case PM_DGD:
 
        switch( theParamType )
        {
        case CT_PM_PARAM_CURRENT:
            paramId = PMA_DGD_PARAMETER;
            break;
   
        case CT_PM_PARAM_MIN:
            paramId = PMA_DGD_F_PARAMETER;
            break;
   
        case CT_PM_PARAM_MAX:
            paramId = PMA_DGD_C_PARAMETER;
            break;
 
        default:
            paramId = PMA_INVALID_PARAMETER;
            break;
        }
 
        break;

    case PM_CD:
 
        switch( theParamType )
        {
        case CT_PM_PARAM_CURRENT:
            paramId = PMA_CD_PARAMETER;
            break;
   
        case CT_PM_PARAM_MIN:
            paramId = PMA_CD_F_PARAMETER;
            break;
   
        case CT_PM_PARAM_MAX:
            paramId = PMA_CD_C_PARAMETER;
            break;
 
        default:
            paramId = PMA_INVALID_PARAMETER;
            break;
        }
 
        break;

    case PM_OSNR:
 
        switch( theParamType )
        {
        case CT_PM_PARAM_CURRENT:
            paramId = PMA_OSNR_PARAMETER;
            break;
   
        case CT_PM_PARAM_MIN:
            paramId = PMA_OSNR_F_PARAMETER;
            break;
   
        case CT_PM_PARAM_MAX:
            paramId = PMA_OSNR_C_PARAMETER;
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

string& PM_TypeOpt::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOpt::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}


CT_PM_Value PM_TypeOptCounter::myMaxValueTableOpt15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeOptCounter::myMaxValueTableOptDay[PM_PARAM_NUM];

string PM_TypeOptCounter::PM_ParamNameTable[] =
{
    "psc",
    "psd"
};

string PM_TypeOptCounter::PM_ParamUnitTable[] =
{
    "prot sw cnt",
    "s"
};

//-------------------------------------------------------------
PM_TypeOptCounter::PM_TypeOptCounter()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableOpt15M[PM_PSC].SignedValue       = 900;
    myMaxValueTableOpt15M[PM_PSD].SignedValue       = 900;
    // Max value table.
    myMaxValueTableOptDay[PM_PSC].SignedValue       = 86400;
    myMaxValueTableOptDay[PM_PSD].SignedValue       = 86400;

    done = true;
}

//-------------------------------------------------------------
PM_TypeOptCounter::~PM_TypeOptCounter()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeOptCounter::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
    case PM_PSC:
        paramId = PMA_PSC_OPT_PARAMETER;
        break;
    
    case PM_PSD:
        paramId = PMA_PSD_OPT_PARAMETER;
        break;
 
	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeOptCounter::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeOptCounter::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}