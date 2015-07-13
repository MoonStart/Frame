/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        MON_SubNodeParameters.cpp
 *    DATE:          12/28/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Sub Node Specific Data
 *    OVERVIEW:      Sub Node Specific Data
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#include "../MON_SubNodeParameters.h"
#include "../MON_Definitions.h"
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_Telecom.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <Configuration/CFG_Opt.h>
#include <ErrorService/FC_Error.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Opt.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_MainAppIf.h>
#include <T6100_PortShelfIf.h>
#include <T6100_PortShelfSlotIf.h>
#include <T6100_OpticalShelfIf.h>
#include <T6100_OpticalShelfSlotIf.h>

MON_SubNodeParameters*  MON_SubNodeParameters::ourInstance = NULL;

////////////////////////////////////////////////////////////////////////////////
MON_SubNodeParameters & MON_SubNodeParameters::GetInstance()
{
        if (ourInstance == NULL)
        ourInstance = new MON_SubNodeParameters();

        return *ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
void MON_SubNodeParameters::DeleteInstance()
{
    delete ourInstance;
    ourInstance = NULL;
}

////////////////////////////////////////////////////////////////////////////////
MON_SubNodeParameters::MON_SubNodeParameters() :
        myLossOfInputPowerThreshold(TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD),
        myMinimumSNRatio(TEL_DEFAULT_MINIMUM_SN_RATIO),
        myOmsWavelengthCapacity(CT_TEL_FP2_OMS_WAVELENGTH_CAPACITY),
        myOptCfgRegion(NULL),
        mySubNodeParametersFilled(false),
        myIsPilotToneSupported(true)
{
        CFG_AppIf* theCfgOptAppIf = NULL;
        CT_CardFamily aCardFam = CSPII_CardIF::GetInstance()->GetCardFamily();

        if(aCardFam == TRN_FAM || aCardFam == SMTM_FAM || aCardFam == PACKET_FAM || aCardFam == OTNM_FAM || aCardFam == SSM_FAM||
           aCardFam == FGTMM_FAM)
        {
                uint32 aSlotId = CSPII_CardIF::GetInstance()->GetSlotId();
                CT_ShelfId aShelfId = CSPII_CardIF::GetInstance()->GetShelfId();

            theCfgOptAppIf = T6100_MainAppIf::Instance().GetShelfPtr(aShelfId)->GetSlotPtr((CT_SlotId)aSlotId)->GetCardPtr(aCardFam)->GetOptIf().GetCfgLineSideAppPtr(CT_LINE_SIDE_1);

                FC_THROW_ERROR_IF(theCfgOptAppIf==NULL, FC_RuntimeError, "Unable to get cfg application");

                myOptCfgRegion = static_cast<CFG_OptCfgRegion*>(theCfgOptAppIf->GetCfgRegion());

                if(myOptCfgRegion && myOptCfgRegion->IsValid())
                {
                        CFG_Opt& aCfgObject = (*myOptCfgRegion)[0];
                        CT_TEL_FreqencyPlan aFreqPlan = aCfgObject.GetFreqPlan();

                        if(aFreqPlan != CT_TEL_UNKNOWN_PLAN)
                        {
                                if(aFreqPlan == CT_TEL_44CHAN_PLAN)
                                {
                                        myOmsWavelengthCapacity         = CT_TEL_FP3_OMS_WAVELENGTH_CAPACITY;
                                        myLossOfInputPowerThreshold = TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD_OSA;
                                        myMinimumSNRatio                        = TEL_DEFAULT_MINIMUM_SN_RATIO_OSA;
                                        if(CT_TEL_OTID_DISABLED == aCfgObject.GetOTIDStatus())
                                        {
                                                myIsPilotToneSupported = false;
                                        }
                                }
                                else if (aFreqPlan == CT_TEL_44BST_CHAN_PLAN)
                                {
                                        myOmsWavelengthCapacity             = CT_TEL_FP3_OMS_WAVELENGTH_CAPACITY;
                                }
                                else if ( (aFreqPlan == CT_TEL_88CHAN_PLAN) || (aFreqPlan == CT_TEL_80_OEM_CHAN_PLAN) )
                                {
                                        myOmsWavelengthCapacity             = CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY;
                                        myLossOfInputPowerThreshold = TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD_OSA;
                                        myMinimumSNRatio                        = TEL_DEFAULT_MINIMUM_SN_RATIO_OSA;
                                        if(CT_TEL_OTID_DISABLED == aCfgObject.GetOTIDStatus())
                                        {
                                                myIsPilotToneSupported = false;
                                        }
                                }

                                mySubNodeParametersFilled = true;
                        }
                }
        }
        else if(aCardFam == APM_FAM || aCardFam == OSC_FAM)
        {
                CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();

                if(!aSubNodeCfg.IsPilotToneSupported())
                {
                        myLossOfInputPowerThreshold = TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD_OSA;
                        myMinimumSNRatio                        = TEL_DEFAULT_MINIMUM_SN_RATIO_OSA;
                        myIsPilotToneSupported      = false;
                }

                myOmsWavelengthCapacity = aSubNodeCfg.GetOmsWavelengthCapacity();

                mySubNodeParametersFilled = true;
        }
}

////////////////////////////////////////////////////////////////////////////////
MON_SubNodeParameters::~MON_SubNodeParameters()
{
}

////////////////////////////////////////////////////////////////////////////////
void MON_SubNodeParameters::SetSubNodeParameters()
{
        if(myOptCfgRegion && myOptCfgRegion->IsValid())
        {
                CFG_Opt& aCfgObject = (*myOptCfgRegion)[0];
                CT_TEL_FreqencyPlan aFreqPlan = aCfgObject.GetFreqPlan();

                if(aFreqPlan != CT_TEL_UNKNOWN_PLAN)
                {
                        if(aFreqPlan == CT_TEL_44CHAN_PLAN)
                        {
                                myOmsWavelengthCapacity         = CT_TEL_FP3_OMS_WAVELENGTH_CAPACITY;
                                myLossOfInputPowerThreshold = TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD_OSA;
                                myMinimumSNRatio                        = TEL_DEFAULT_MINIMUM_SN_RATIO_OSA;

                                if(CT_TEL_OTID_DISABLED == aCfgObject.GetOTIDStatus())
                                {
                                        myIsPilotToneSupported = false;
                                }
                                else
                                        myIsPilotToneSupported      = true;
                        }
                        else if (aFreqPlan == CT_TEL_44BST_CHAN_PLAN)
                        {
                                myOmsWavelengthCapacity         = CT_TEL_FP3_OMS_WAVELENGTH_CAPACITY;
                        }
                        else if (aFreqPlan == CT_TEL_88CHAN_PLAN)
                        {
                myOmsWavelengthCapacity         = CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY;
                                myLossOfInputPowerThreshold = TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD_OSA;
                                myMinimumSNRatio                        = TEL_DEFAULT_MINIMUM_SN_RATIO_OSA;
                                if(CT_TEL_OTID_DISABLED == aCfgObject.GetOTIDStatus())
                                {
                                        myIsPilotToneSupported = false;
                                }
                                else
                                        myIsPilotToneSupported      = true;
                        }

                        mySubNodeParametersFilled = true;
                }
                else
                {
                        mySubNodeParametersFilled = false;
                }
        }
}

////////////////////////////////////////////////////////////////////////////////
void MON_SubNodeParameters::SetLossOfInputPowerThreshold(CT_TEL_mBm theLossOfInputPowerThreshold)
{
        myLossOfInputPowerThreshold = theLossOfInputPowerThreshold;
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm MON_SubNodeParameters::GetLossOfInputPowerThreshold() const
{
        return(myLossOfInputPowerThreshold);
}

////////////////////////////////////////////////////////////////////////////////
void MON_SubNodeParameters::SetMinimumSNRatio(CT_TEL_mBm theMinimumSNRatio)
{
        myMinimumSNRatio = theMinimumSNRatio;
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_mBm MON_SubNodeParameters::GetMinimumSNRatio() const
{
        return(myMinimumSNRatio);
}

////////////////////////////////////////////////////////////////////////////////
void MON_SubNodeParameters::SetOmsWavelengthCapacity(uint32 theOmsWavelengthCapacity)
{
        myOmsWavelengthCapacity = theOmsWavelengthCapacity;
}

////////////////////////////////////////////////////////////////////////////////
uint32 MON_SubNodeParameters::GetOmsWavelengthCapacity() const
{
        return(myOmsWavelengthCapacity);
}

////////////////////////////////////////////////////////////////////////////////
bool MON_SubNodeParameters::IsSubNodeParametersReady()
{
        bool otidStatusChanged = false;
        bool newOTIDStatus =false;
        if(myOptCfgRegion && myOptCfgRegion->IsValid())
        {
                CFG_Opt& aCfgObject = (*myOptCfgRegion)[0];
                if(CT_TEL_OTID_DISABLED == aCfgObject.GetOTIDStatus())
                {
                    newOTIDStatus = false;
                }
                else
                    newOTIDStatus = true;
                if( IsPilotToneSupported() != newOTIDStatus)
                {
                    otidStatusChanged = true;
                }
        }

        if(!mySubNodeParametersFilled ||otidStatusChanged )
                SetSubNodeParameters();

        return(mySubNodeParametersFilled);
}

////////////////////////////////////////////////////////////////////////////////
// This method should only be called after IsSubNodeParametersReady is true
////////////////////////////////////////////////////////////////////////////////
bool MON_SubNodeParameters::IsPilotToneSupported()
{
        return(myIsPilotToneSupported);
}

////////////////////////////////////////////////////////////////////////////////
void MON_SubNodeParameters::Display(FC_Stream& theStream)
{
        theStream.GetOutputStream() << "\tmySubNodeParametersFilled   = " << DISPLAY_BOOL(mySubNodeParametersFilled)    << endl;
        theStream.GetOutputStream() << "\tmyOmsWavelengthCapacity     = " << myOmsWavelengthCapacity                                    << endl;
        theStream.GetOutputStream() << "\tmyLossOfInputPowerThreshold = " << myLossOfInputPowerThreshold                                << endl;
        theStream.GetOutputStream() << "\tmyMinimumSNRatio            = " << myMinimumSNRatio                                                   << endl;
        theStream.GetOutputStream() << "\tIsPilotToneSupported        = " << DISPLAY_BOOL(IsPilotToneSupported())               << endl<<endl;
}
