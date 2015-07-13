/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 19, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Rmon Counter.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_RmonCounters.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_MacStatus.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_AppIf.h>

#include <EPM/PM_BbStatusRmon.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_Processor.h>
#include <PM/PM_RmonGaugeSubApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorRmonGauge.h>
#include <EPM/src/PM_AutoRateLock.h>

//------------------------
// Class PM_CollectorRmonGauge
//------------------------

//-----------------------------------------------------------------
PM_CollectorRmonGauge::PM_CollectorRmonGauge( PM_GenericApplication&    theGenericApplication,
											  FC_OneShotProcess&     theProcessorProcess,
											  uint32					theNumberOfPort ) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_RMON_STRING, theNumberOfPort),
    myStatusRmon(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorRmonGauge::~PM_CollectorRmonGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorRmonGauge::Init()
{
    // Initialize pointers to optical status and defect regions.
    myStatusRmon = &(*myGenericApplication.GetRegionStatusRmon());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorRmonGauge::ProcessData() 
{
	MON_RmonCounters &countersObject = (MON_RmonCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[0];
	CT_TEL_daHz bitRate = GetBitRate();
	
	// Update RMON gauges statuses.
	(*myStatusRmon)[CT_PM_PERIOD_15_MINUTES].Update( countersObject, bitRate );
	(*myStatusRmon)[CT_PM_PERIOD_1_DAY].Update( countersObject, bitRate );

	// Call base class method.
	PM_Collector::ProcessData();
}

CFG_Rs* PM_CollectorRmonGauge::GetCfgRsRegion( T6100_CardIf& theCardContext, CT_PM_Side theSide )
{
	CFG_Rs* aCfgRs = NULL;
	CFG_AppIf* aCfgApp = NULL;

	if( ((theSide >= CT_PM_PORT_SIDE_0) && (theSide <= CT_PM_PORT_SIDE_31)) || 
        ((theSide >= CT_PM_PORT_SIDE_85) && (theSide <= CT_PM_PORT_SIDE_88)) )
	{
		CT_IntfId aSide = (CT_IntfId)(theSide - CT_PM_PORT_SIDE_0 + CT_PORT_SIDE_0);
		aCfgApp = theCardContext.GetRsIf().GetCfgPortSideAppPtr(aSide);
	}

	if( aCfgApp != NULL )
	{
		aCfgRs = (CFG_Rs *) &((*(aCfgApp->GetCfgRegion()))[0]);
	}

	return  aCfgRs;
}

CT_TEL_daHz PM_CollectorRmonGauge::GetBitRate()
{
	MON_OptStatus* aMonOptStatus;
	MON_MacStatus* aMonMacStatus;
	CFG_Rs*	aCfgRs;
	CFG_Opt* aCfgOpt;
	CT_TEL_SignalType signalType;

	CT_TEL_daHz bitRate = 0;

	PM_RmonGaugeSubApplication& rmonApp = dynamic_cast<PM_RmonGaugeSubApplication&>(myGenericApplication);

	// Validate the region pointers as we go along. Return a bit rate of 0 if any
	// information is missing for the calculation.

	if( (aCfgRs = GetCfgRsRegion( rmonApp.GetCardContext(), rmonApp.GetSide() )) != NULL )
	{
		if( (signalType = aCfgRs->GetSignalType()) == CT_TEL_SIGNAL_GOPT )
		{
			// Determine if it is fixed or auto rate.
			if( (aCfgOpt = PM_AutoRateLock::GetCfgOptRegion( rmonApp.GetCardContext(), rmonApp.GetSide() )) != NULL )
			{
				if( aCfgOpt->GetAutoRateLockDown() != NULL )
				{ 		
					// This is an Auto-Rate Lock facility. Get the bit rate.
					if( (aMonOptStatus = PM_AutoRateLock::GetMonOptStatusRegion( rmonApp.GetCardContext() )) != NULL )
					{
						aMonOptStatus->GetLevel( CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS, &bitRate );
						MapToPayloadBitRate( bitRate );
					}
				}
				else
				{
					// This is a fixed rate facility. Get the bit rate.
					bitRate = aCfgOpt->GetSignalRate();
					MapToPayloadBitRate( bitRate );
				}
			}
			else
			{
				FC_REPORT_ERROR( FC_RuntimeError, "GetBitRate(): No CfgOpt region" );
			}
		}
        else if( (signalType = aCfgRs->GetSignalType()) == CT_TEL_SIGNAL_ETH )
		{
            // This is an Auto-Rate Lock facility. Get the bit rate.
            if( (aMonMacStatus = PM_AutoRateLock::GetMonMacStatusRegion( rmonApp.GetCardContext(), rmonApp.GetSide() )) != NULL )
            {
                bitRate = aMonMacStatus->GetOperRate(); // returns PAYLOAD rate!
            }
			else
			{
				FC_REPORT_ERROR( FC_RuntimeError, "GetBitRate(): No MonMacStatus region" );
			}
		}
		else
		{
			// Just map the signal type to payload bit rate.
			bitRate = SignalTypeToBitRate( signalType );
		}
	}

	return bitRate;
}

CT_TEL_daHz PM_CollectorRmonGauge::SignalTypeToBitRate( CT_TEL_SignalType theSignalType )
{
	CT_TEL_daHz bitRate;

	switch( theSignalType )
	{
	case CT_TEL_SIGNAL_100BFX:
		bitRate = BIT_RATE_ETH100M_NOMINAL;
		break;

	case CT_TEL_SIGNAL_GBEP:
		bitRate = BIT_RATE_ETH1000M_NOMINAL;
		break;

	case CT_TEL_SIGNAL_HGE:
    case CT_TEL_SIGNAL_HGE_GFP:        
		bitRate = BIT_RATE_HGE;
		break;

	case CT_TEL_SIGNAL_FGE:
		bitRate = BIT_RATE_FGE;
		break;

	case CT_TEL_SIGNAL_TGLAN:
	case CT_TEL_SIGNAL_TGLAN_FRAME:
	case CT_TEL_SIGNAL_TGLAN_PREAMBLE:
	case CT_TEL_SIGNAL_TGLAN_WFS:
	case CT_TEL_SIGNAL_TGLAN_FRAME_STD:     

		bitRate = BIT_RATE_ETH10G_NOMINAL;
		break;

	default:

		// This is not an ethernet bit rate. 
		// Force to 0.
		bitRate = 0;
		break;
	}

	return bitRate;
}

void PM_CollectorRmonGauge::MapToPayloadBitRate( CT_TEL_daHz& theBitRate )
{
	switch( theBitRate )
	{
	case BIT_RATE_100BFX:
		theBitRate = BIT_RATE_ETH100M_NOMINAL;
		break;

	case BIT_RATE_GBE:
		theBitRate = BIT_RATE_ETH1000M_NOMINAL;
		break;

	case BIT_RATE_TGLAN:
		theBitRate = BIT_RATE_ETH10G_NOMINAL;
		break;

	default:

		// This is not an ethernet bit rate. 
		// Force to 0.
		theBitRate = 0;
		break;
	}
}

