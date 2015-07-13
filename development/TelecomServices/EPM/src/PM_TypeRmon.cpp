/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     December 2005, Teresa Chen
 DESCRIPTION:   Base for PM parameters definition.
--------------------------------------------------------------------------*/

#include <EPM/PM_TypeRmon.h>

//--------------------------
// Class PM_TypeRmonCounter
//--------------------------

CT_PM_64BitValue PM_TypeRmonCounter::myMaxValueTableRmon15M[PM_PARAM_NUM];
CT_PM_64BitValue PM_TypeRmonCounter::myMaxValueTableRmonDay[PM_PARAM_NUM];

string PM_TypeRmonCounter::PM_ParamNameTable[] =
{
    "drop",
    "packet",
    "bcast",
    "mcast",
    "crc align",
    "undersize",
    "oversize",
    "frag",
    "jabber",
    "droph",
    "packeth",
    "bcasth",
    "mcasth",
    "crc alignh",
    "undersizeh",
    "oversizeh",
    "fragh",
    "jabberh"
};

string PM_TypeRmonCounter::PM_ParamUnitTable[] =
{
    "pkt",
    "cnt",
    "pkt",
    "pkt",
    "error",
    "pkt",
    "pkt",
    "pkt",
    "pkt",
    "pkt",
    "cnt",
    "pkt",
    "pkt",
    "error",
    "pkt",
    "pkt",
    "pkt",
    "pkt"
};

//-------------------------------------------------------------
PM_TypeRmonCounter::PM_TypeRmonCounter()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableRmon15M[PM_DROP].UnsignedValue       = 0x7fffffff;
    myMaxValueTableRmon15M[PM_PKT].UnsignedValue        = 0x7fffffff;
    myMaxValueTableRmon15M[PM_BCPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmon15M[PM_MCPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmon15M[PM_CRCAE].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmon15M[PM_USPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmon15M[PM_OSPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmon15M[PM_FRAG].UnsignedValue       = 0x7fffffff;
    myMaxValueTableRmon15M[PM_JABR].UnsignedValue       = 0x7fffffff;
    myMaxValueTableRmon15M[PM_DROP_HIGH].UnsignedValue  = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_PKT_HIGH].UnsignedValue   = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_BCPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_MCPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_CRCAE_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_USPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_OSPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_FRAG_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmon15M[PM_JABR_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableRmonDay[PM_DROP].UnsignedValue       = 0x7fffffff;
    myMaxValueTableRmonDay[PM_PKT].UnsignedValue        = 0x7fffffff;
    myMaxValueTableRmonDay[PM_BCPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmonDay[PM_MCPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmonDay[PM_CRCAE].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmonDay[PM_USPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmonDay[PM_OSPKT].UnsignedValue      = 0x7fffffff;
    myMaxValueTableRmonDay[PM_FRAG].UnsignedValue       = 0x7fffffff;
    myMaxValueTableRmonDay[PM_JABR].UnsignedValue       = 0x7fffffff;
    myMaxValueTableRmonDay[PM_DROP_HIGH].UnsignedValue  = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_PKT_HIGH].UnsignedValue   = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_BCPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_MCPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_CRCAE_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_USPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_OSPKT_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_FRAG_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    myMaxValueTableRmonDay[PM_JABR_HIGH].UnsignedValue = 0xffffffffffffffffULL;
    done = true;
}

//-------------------------------------------------------------
PM_TypeRmonCounter::~PM_TypeRmonCounter()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeRmonCounter::ConvertPmIdToPmaId( uint32 theParamId )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_DROP:
		paramId = PMA_DROP_PARAMETER;
		break;

	case PM_PKT:
		paramId = PMA_PKT_PARAMETER;
		break;

	case PM_BCPKT:
		paramId = PMA_BCPKT_PARAMETER;
		break;

	case PM_MCPKT:
		paramId = PMA_MCPKT_PARAMETER;
		break;

	case PM_CRCAE:
		paramId = PMA_CRCAE_PARAMETER;
		break;

	case PM_USPKT:
		paramId = PMA_USPKT_PARAMETER;
		break;

	case PM_OSPKT:
		paramId = PMA_OSPKT_PARAMETER;
		break;

	case PM_FRAG:
		paramId = PMA_FRAG_PARAMETER;
		break;

	case PM_JABR:
		paramId = PMA_JABR_PARAMETER;
		break;

    case PM_DROP_HIGH:
        paramId = PMA_DROP_HIGH_PARAMETER;
        break;
 
    case PM_PKT_HIGH:
        paramId = PMA_PKT_HIGH_PARAMETER;
        break;
 
    case PM_BCPKT_HIGH:
        paramId = PMA_BCPKT_HIGH_PARAMETER;
        break;
 
    case PM_MCPKT_HIGH:
        paramId = PMA_MCPKT_HIGH_PARAMETER;
        break;
 
    case PM_CRCAE_HIGH:
        paramId = PMA_CRCAE_HIGH_PARAMETER;
        break;
 
    case PM_USPKT_HIGH:
        paramId = PMA_USPKT_HIGH_PARAMETER;
        break;
 
    case PM_OSPKT_HIGH:
        paramId = PMA_OSPKT_HIGH_PARAMETER;
        break;
 
	case PM_FRAG_HIGH:
        paramId = PMA_FRAG_HIGH_PARAMETER;
        break;

    case PM_JABR_HIGH:
        paramId = PMA_JABR_HIGH_PARAMETER;
        break;
 
	default:
		paramId = PMA_INVALID_PARAMETER;
		break;
	}

	return paramId;
}

string& PM_TypeRmonCounter::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeRmonCounter::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}


//--------------------------
// Class PM_TypeRmonGauge
//--------------------------

CT_PM_Value PM_TypeRmonGauge::myMaxValueTableRmon15M[PM_PARAM_NUM];
CT_PM_Value PM_TypeRmonGauge::myMaxValueTableRmonDay[PM_PARAM_NUM];

string PM_TypeRmonGauge::PM_ParamNameTable[] =
{
    "util"
};

string PM_TypeRmonGauge::PM_ParamUnitTable[] =
{
    "%"
};


//-------------------------------------------------------------
PM_TypeRmonGauge::PM_TypeRmonGauge()
{
    static bool done = false;
    if (done) return;

    // **************15 MINUTE STUFF*************
    // Max value table.
    myMaxValueTableRmon15M[PM_UTIL].SignedValue       = 100;

    // **************1 DAY STUFF*************
    // Max value table.
    myMaxValueTableRmonDay[PM_UTIL].SignedValue       = 100;

    done = true;
}

//-------------------------------------------------------------
PM_TypeRmonGauge::~PM_TypeRmonGauge()
{
    // Nothing to do for now.
}

CT_PMA_ParamId
PM_TypeRmonGauge::ConvertPmIdToPmaId( uint32 theParamId, CT_PM_ParamType theParamType )
{
	CT_PMA_ParamId paramId;

	switch( theParamId )
	{
	case PM_UTIL:

		switch( theParamType )
		{
		case CT_PM_PARAM_CURRENT:
			paramId = PMA_UTIL_PARAMETER;
			break;
	
		case CT_PM_PARAM_MIN:
			paramId = PMA_UTIL_F_PARAMETER;
			break;
	
		case CT_PM_PARAM_MAX:
			paramId = PMA_UTIL_C_PARAMETER;
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

string& PM_TypeRmonGauge::GetParamName( CT_PM_Parameter theParameter )
{
    return PM_ParamNameTable[theParameter];
}

string& PM_TypeRmonGauge::GetParamUnit( CT_PM_Parameter theParameter )
{
    return PM_ParamUnitTable[theParameter];
}
