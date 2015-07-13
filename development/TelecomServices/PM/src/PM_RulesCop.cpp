/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, February 26, 2003.
 DESCRIPTION:   The class to update Optical parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CsPii/CSPII_CardIF.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM_GenericApplication.h>
#include <PM/PM_TypeCop.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbStatusCop.h>
#include <PM/PM_BbDefectCop.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_RulesCop.h>


//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3E6E4CD7037F
PM_RulesCop::PM_RulesCop (PM_GenericApplication&    theGenericApplication, 
                          uint16                    theIndex,
                          CT_CardFamily             theCardFamily,
                          CT_PM_Side                theSide):
    PM_Rules(theGenericApplication, theIndex, PM_TypeCop::PM_PARAM_NUM),
    myStatusCop ((*myGenericApplication.GetRegionStatusCop())[theIndex]),
    myDefectCop ((*myGenericApplication.GetRegionDefectCop())[theIndex]),
    myCardFamily(theCardFamily),
    mySide(theSide)
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3E6E4CD70393
PM_RulesCop::~PM_RulesCop ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610D02B6
void PM_RulesCop::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

	// Force the initial value of the power reading to a sane value.
	myCurrentValueParam[PM_TypeCop::PM_COP].SignedValue = -6000;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CD7039D
void PM_RulesCop::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStateSecondStage)
{
    // Computed state for first stage filtering (2.5 seconds failures).
    bool            filteringStateFirstStage[PM_TypeCop::PM_PARAM_NUM];
    // Computed state for second stage filtering (90 seconds failures).
    bool            filteringStateSecondStage[PM_TypeCop::PM_PARAM_NUM];
    // Iteraror of Accumulation Period.
    vector<PM_AccumulationPeriod*>::iterator    i;
    // Alarm reference.

    //
    // Determine validity state:
    //

    // Verify monitoring state validity change or at first iteration.
    if (myValidityState[PM_TypeCop::PM_COP] != myStatusCop.StatusIsValid(PM_TypeCop::PM_COP) || myFirstTime)
    {
        // Update my validity.
        myValidityState[PM_TypeCop::PM_COP] = myStatusCop.StatusIsValid(PM_TypeCop::PM_COP);

        // Update first time flag.
        myFirstTime = false;

        // Set availability for all Accumulation period.
        // IDF is available if monitoring status is valid, otherwise it is not available.
        for (i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++)
        {
            (*i)->SetAvailability(PM_TypeCop::PM_COP, myValidityState[PM_TypeCop::PM_COP]);
        }
    }


    //
    // Determine TCA filtering state:
    //

    // On OLIM and Amplifiers only.
    if (myCardFamily == CARD_FAM_OLIM || myCardFamily == CARD_FAM_IAM ||
        myCardFamily == CARD_FAM_OAM)
    {
        ALM_FailureBase &almOmsRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOmsApplication().GetFilteredRegionPtr()))[0];
        ALM_FailureBase &almRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmApplication().GetFilteredRegionPtr()))[myIndex];

        // Verify side of instance.
        if (mySide == CT_PM_LINE_SIDE)
        {
           // Line to Port side.

            ALM_FailureBase &almOtsRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOtsApplication().GetFilteredRegionPtr()))[0];
            ALM_FailureBase &almOtsOhRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmOtsOhApplication().GetFilteredRegionPtr()))[0];

            // FP2.0 hardware only. (OSC8250 is slotted)
            if (!CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsCfgFP1_3())
            {
				ALM_FailureRegionImp<ALM_FailureBase>* almFilteredRegionPtr = myGenericApplication.GetAlmOscOchApplication().GetFilteredRegionPtr();
				if (myIndex < almFilteredRegionPtr->Size())
				{
                    ALM_FailureBase &almOscOchRef = (ALM_FailureBase &)(*(almFilteredRegionPtr))[myIndex];


                    // Filter channel optical power received TCA if LOS-OTS, PMI-OTS, TIM-OTS, LOS-OMS, FDIP-OMS, 
                    // PMI-OMS, LOS-OCH, FDI-P-OCH or OCI-OCH failure or LOP defect is present or if monitoring 
                    // status is invalid.
                    filteringStateFirstStage[PM_TypeCop::PM_COP] = (almOtsRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OTS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_PMI_OTS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_OTS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_FDIP_OMS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_PMI_OMS) ||
                                                                almOmsRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OMS) ||
                                                                almOscOchRef.GetStatus(CT_TelAlarmCondition::ALM_FDIP_OCH) || 
                                                                almOscOchRef.GetStatus(CT_TelAlarmCondition::ALM_OCI_OCH) || 
                                                                myDefectCop.EverPresentLOP() ||
                                                                !myValidityState[PM_TypeCop::PM_COP]);
                    filteringStateSecondStage[PM_TypeCop::PM_COP] = almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OCH);
				}
				else
				{
					//OSC och alarm regions could be transferred from the OSC. There are situations during
					//module swaps where the OSC is running with the incorrect subnode configuration. In these
					//situations the region transferred from the OSC may have less objects than we expect (32 instead of 44)
					//To avoid over-indexing into the alarm region (and causing a crash), 
					//simply return if this is the case. This mismatch is rectified automatically once the correct configuration is
					//received on the OSC from the APM.
					return;
				}
            }
            else
            {
                // Filter channel optical power received TCA if LOS-OTS, PMI-OTS, TIM-OTS, LOS-OMS, FDIP-OMS, 
                // PMI-OMS, LOS-OCH failure or LOP defect is present or if monitoring 
                // status is invalid.
                // Note that there is no signaling on OSC of FP1.3.
                filteringStateFirstStage[PM_TypeCop::PM_COP] = (almOtsRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OTS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_PMI_OTS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_TIM_OTS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_FDIP_OMS) || 
                                                                almOtsOhRef.GetStatus(CT_TelAlarmCondition::ALM_PMI_OMS) ||
                                                                almOmsRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OMS) ||
                                                                myDefectCop.EverPresentLOP() ||
                                                                !myValidityState[PM_TypeCop::PM_COP]);
                filteringStateSecondStage[PM_TypeCop::PM_COP] = almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OCH);
            }
        }
        else 
        {
            // Port to Line side.

            ALM_FailureBase &almRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmApplication().GetFilteredRegionPtr()))[myIndex];

            // Filter channel optical power received TCA if LOS-OMS, LOS-OCH failure or 
            // LOP defect is present or if monitoring status is invalid.
            filteringStateFirstStage[PM_TypeCop::PM_COP] = (almOmsRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OMS) ||
                                                            myDefectCop.EverPresentLOP() ||
                                                            !myValidityState[PM_TypeCop::PM_COP]);
            filteringStateSecondStage[PM_TypeCop::PM_COP] = almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OCH);
        }
    }
    // Multiplexers.
    else 
    {
        // Filter channel optical power received TCA if LOS-OCH failure or 
        // LOP defect is present or if monitoring status is invalid.
        ALM_FailureBase &almRef = (ALM_FailureBase &)(*(myGenericApplication.GetAlmApplication().GetFilteredRegionPtr()))[myIndex];
        filteringStateFirstStage[PM_TypeCop::PM_COP] = (myDefectCop.EverPresentLOP() ||
                                                        !myValidityState[PM_TypeCop::PM_COP]);
        filteringStateSecondStage[PM_TypeCop::PM_COP] = almRef.GetStatus(CT_TelAlarmCondition::ALM_LOS_OCH);
    }

    //
    // Apply rules:
    //

    // Accumulate new value of COP only if monitoring is valid.
    if (myValidityState[PM_TypeCop::PM_COP])
    {
		CT_PM_Value newCopValue;

		// Check to see MON has sent up the default value.
		if( (newCopValue.SignedValue = myStatusCop.GetCop()) != TRAFFIC_DEFAULT_POWER )
		{
			myCurrentValueParam[PM_TypeCop::PM_COP].SignedValue = newCopValue.SignedValue;
		}
	}

    // Call the method of the base class.
    PM_Rules::UpdateRules(filteringStateFirstStage, filteringStateSecondStage);

}
