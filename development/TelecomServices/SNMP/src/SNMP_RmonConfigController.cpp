/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#include <SNMP/SNMP_RmonConfigController.h>
#include <SNMP/SNMP_SystemData.h>
#include <Configuration/CFG_Region.h>
#include <CommonTypes/CT_SNMP_Utilization.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Rs.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_MacStatus.h>

SNMP_RmonEtherStatsCfgCtrl::SNMP_RmonEtherStatsCfgCtrl(SNMP_RmonEtherStatsCfgRegion*  theStatsCfgRegion,
                               SNMP_RmonEtherStatsDataRegion* theStatsDataRegion,
                               SNMP_SysUpTimeRegion*  theSysUpTimeRegion) :
SNMP_RmonConfigController<SNMP_RmonEtherStatsDataRegion, 
                          SNMP_RmonEtherStatsCfgRegion>(theStatsDataRegion, theStatsCfgRegion),
mySysUpTimeRegion(theSysUpTimeRegion)
{

}

SNMP_RmonEtherStatsCfgCtrl::~SNMP_RmonEtherStatsCfgCtrl()
{

}

void SNMP_RmonEtherStatsCfgCtrl::UpdateEtherStatsConfig()
{
    SNMP_RmonConfigController<SNMP_RmonEtherStatsDataRegion, 
                              SNMP_RmonEtherStatsCfgRegion>::UpdateConfig();

    vector<int>::const_iterator indexIter;
    for (indexIter = myUpdateIndices.begin(); indexIter != myUpdateIndices.end(); ++indexIter) 
    {
        try
        {
            SNMP_BbRmonEtherStatsCfg& cfgObj = (*myCfgRegion)[*indexIter];
            SNMP_BbRmonEtherStatsData& dataObj = myDataRegion->GetEntry(cfgObj.GetIndex());
            SNMP_BbSystemUpTime& sysUpTime = (*mySysUpTimeRegion)[0];
            dataObj.SetCreateTime(sysUpTime.GetSysUpTime());         
        }
        catch (FC_RuntimeError theError)
        {
            theError.ReportError();
        }
    }
}

SNMP_RmonEtherHistCfgCtrl::SNMP_RmonEtherHistCfgCtrl(SNMP_RmonEtherHistCfgRegion*  theHistCfgRegion,
                               SNMP_RmonEtherHistStorageRegion* theHistStorageRegion,
                               SNMP_RmonEtherHistDataRegion* theDataFwdRegion,
                               SNMP_SysUpTimeRegion*  theSysUpTimeRegion,
                               CFG_Region* theOptCfgRegion,
							   MON_AppIf& theMonApp,
							   CFG_AppIf& theCfgRsApp,
                               MON_AppIf* theMacMonApp) :
SNMP_RmonConfigController<SNMP_RmonEtherHistStorageRegion, 
                          SNMP_RmonEtherHistCfgRegion, SNMP_RmonEtherHistDataRegion>(theHistStorageRegion, 
                                                                                     theHistCfgRegion,
                                                                                     theDataFwdRegion),
mySysUpTimeRegion(theSysUpTimeRegion),
myOptCfgRegion(theOptCfgRegion),
myMonApp(theMonApp),
myCfgRsApp(theCfgRsApp),
myMacMonApp(theMacMonApp),
myUtilBitRate(0)
{
    
}

SNMP_RmonEtherHistCfgCtrl::~SNMP_RmonEtherHistCfgCtrl()
{

}

void SNMP_RmonEtherHistCfgCtrl::UpdateEtherHistConfig(vector<CT_SNMP_Utilization>& theUtilizationMonitors)
{
    SNMP_RmonConfigController<SNMP_RmonEtherHistStorageRegion, 
                              SNMP_RmonEtherHistCfgRegion, SNMP_RmonEtherHistDataRegion>::UpdateConfig();

    // Obtain current sysUpTime
    SNMP_BbSystemUpTime& sysUpTimeObj = (*mySysUpTimeRegion)[0];
    CT_SNMP_TimeTicks currSysUpTime = sysUpTimeObj.GetSysUpTime();
	CFG_Opt& aOptCfgObject = static_cast<CFG_Opt&>((*myOptCfgRegion)[0]);

    vector<int>::const_iterator indexIter;
    for (indexIter = myUpdateIndices.begin(); indexIter != myUpdateIndices.end(); ++indexIter) 
    {
        // Set the bit rate of the current facility, and
		CT_TEL_daHz bitrate = GetBitRate(&aOptCfgObject);
        uint32 multiplier = GetRateMultiplier(&aOptCfgObject);
        theUtilizationMonitors[*indexIter].SetBitRate(bitrate);
        theUtilizationMonitors[*indexIter].SetRateMultiplier(multiplier);
        // Store Bit Rate used for Utilization so it can be used to check if bitrate has changed (ETH).
        SetUtilBitRate(bitrate);
        // Start the utilization averaging process as each updates are called into
        // the utilization object.
        theUtilizationMonitors[*indexIter].EndOfPeriod();
        try
        {
            SNMP_BbRmonEtherHistCfg&  cfgObj  = (*myCfgRegion)[*indexIter];
            SNMP_BbRmonEtherHistStorage& dataObj = myDataRegion->GetEntry(cfgObj.GetIndex());
            dataObj.SetBucketsRequested(cfgObj.GetBucketsRequested());
            dataObj.SetInterval(cfgObj.GetInterval());
            SNMP_RmonEtherHistSample& firstHistSample = dataObj.GetFirstSampleToFill();
            firstHistSample.SetIntervalStart(currSysUpTime);

            // Let's store the Buckets granted in the data fwd region also
            SNMP_BbRmonEtherHistData& dataFwdObj = static_cast<SNMP_BbRmonEtherHistData &> (myDataFwdRegion->GetEntry(cfgObj.GetIndex()));
            dataFwdObj.SetBucketsGranted(cfgObj.GetBucketsRequested());
        }
        catch (FC_RuntimeError theError)
        {
            theError.ReportError();
        }
    }
}
CT_TEL_daHz SNMP_RmonEtherHistCfgCtrl::GetBitRate(CFG_Opt* aOptCfgObject)
{

	MON_OptStatus* aMonOptStatus = NULL;
	CFG_Rs* aCfgRs = NULL;
	CT_TEL_SignalType signalType;
	CT_TEL_daHz bitRate = 0;

    if (myMacMonApp)
    {
	    MON_MacStatus&  aMonMacStatus = static_cast<MON_MacStatus&> ((*myMacMonApp->GetStatusRegion())[0]);
        return aMonMacStatus.GetOperRate();
    }
    else
    {
	    aCfgRs = (CFG_Rs *) &((*(myCfgRsApp.GetCfgRegion()))[0]);
	    aMonOptStatus = (MON_OptStatus *) &((*(myMonApp.GetStatusRegion()))[0]);
    
	    // Test for GOPT facility
        if((aCfgRs != NULL) && ((signalType = aCfgRs->GetSignalType()) != CT_TEL_SIGNAL_GOPT ))
	    {
            // This is not a GOPT facility. Just map the signal type to payload bit rate.
            bitRate = SignalTypeToBitRate( signalType );
	    }
        else
	    {
           if (aOptCfgObject != NULL)
	       {
               // This is a GOPT facility. Determine if it is fixed or auto rate.
               if (aOptCfgObject->GetAutoRateLockDown() != NULL)
		       {
                   // This is an Auto-Rate Lock facility. Get the bit rate.
                   if(aMonOptStatus != NULL)
			       {
                        aMonOptStatus->GetLevel( CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS, &bitRate );
                        MapToPayloadBitRate( bitRate );
			       }
		       }
               else
		       {
                   // This is a fixed rate facility. Get the bit rate.
                   bitRate = aOptCfgObject->GetSignalRate();
                   MapToPayloadBitRate( bitRate );
		       }
	       }
	    }
	    if ((aOptCfgObject != NULL) && (bitRate == 0))
	    {
		    bitRate = aOptCfgObject->GetSignalRate();
		    MapToPayloadBitRate( bitRate );
	    }
    }
	return bitRate;
}

uint32 SNMP_RmonEtherHistCfgCtrl::GetRateMultiplier(CFG_Opt* aOptCfgObject)
{

	MON_OptStatus* aMonOptStatus = NULL;
	CFG_Rs* aCfgRs = NULL;
	CT_TEL_SignalType signalType;
	uint32 multiplier = 0;

    if (myMacMonApp)
    {
        return CT_SNMP_Utilization::DAHZ_MULTIPLIER;
    }
    else
    {
	    aCfgRs = (CFG_Rs *) &((*(myCfgRsApp.GetCfgRegion()))[0]);
    
	    // Test for GOPT facility
        if((aCfgRs != NULL) && ( (signalType = aCfgRs->GetSignalType()) == CT_TEL_SIGNAL_HGE || 
                                 (signalType = aCfgRs->GetSignalType()) == CT_TEL_SIGNAL_HGE_GFP  ) )
	    {
            //  HGE facility bit rate is reported in KHz.
            return CT_SNMP_Utilization::KHZ_MULTIPLIER;
	    }
        else
	    {
            return CT_SNMP_Utilization::DAHZ_MULTIPLIER;
        }
    }
}
void SNMP_RmonEtherHistCfgCtrl::SetUtilBitRate(CT_TEL_daHz theBitRate)
{
    myUtilBitRate = theBitRate;
}

CT_TEL_daHz SNMP_RmonEtherHistCfgCtrl::GetUtilBitRate()
{
    return myUtilBitRate;
}

CT_TEL_daHz SNMP_RmonEtherHistCfgCtrl::SignalTypeToBitRate( CT_TEL_SignalType theSignalType )
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

	case CT_TEL_SIGNAL_TGLAN:
    case CT_TEL_SIGNAL_TGBEP:
    case CT_TEL_SIGNAL_TGLAN_FRAME:
    case CT_TEL_SIGNAL_TGLAN_PREAMBLE:
    case CT_TEL_SIGNAL_TGLAN_FRAME_STD:
    case CT_TEL_SIGNAL_TGLAN_WFS:
    		bitRate = BIT_RATE_ETH10G_NOMINAL;
		break;

    case CT_TEL_SIGNAL_FGE:
        bitRate = BIT_RATE_FGE;
        break;

    case CT_TEL_SIGNAL_HGE:
    case CT_TEL_SIGNAL_HGE_GFP:        
        bitRate = BIT_RATE_HGE;
        break;

	default:

		// This is not an ethernet bit rate. 
		// Force to 0.
		bitRate = 0;
		break;
	}

	return bitRate;

}

void SNMP_RmonEtherHistCfgCtrl::MapToPayloadBitRate( CT_TEL_daHz& theBitRate )
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

