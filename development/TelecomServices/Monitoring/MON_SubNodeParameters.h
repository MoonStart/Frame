/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        MON_SubNodeParameters.h
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
#ifndef __MON_SUBNODEPARAMETERS_H__
#define __MON_SUBNODEPARAMETERS_H__

#include <CommonTypes/CT_Telecom.h>
#include <TelCommon/TEL_BbObjectBase.h>
#include <Configuration/CFG_Definitions.h>

class MON_SubNodeParameters 
{
public:
    virtual                             ~MON_SubNodeParameters();
    static MON_SubNodeParameters &		GetInstance();
    static void                         DeleteInstance();
	void								SetLossOfInputPowerThreshold(CT_TEL_mBm theLossOfInputPowerThreshold);
	void								SetMinimumSNRatio(CT_TEL_mBm theMinimumSNRatio);
	void								SetOmsWavelengthCapacity(uint32 theOmsWavelengthCapacity);
	CT_TEL_mBm							GetLossOfInputPowerThreshold() const;
	CT_TEL_mBm							GetMinimumSNRatio() const;
	uint32								GetOmsWavelengthCapacity() const;
	bool								IsSubNodeParametersReady();
	bool								IsPilotToneSupported();
    void								Display(FC_Stream& theStream);

private:
    /* Constructor */                   MON_SubNodeParameters();
	void								SetSubNodeParameters();

    static MON_SubNodeParameters *		ourInstance;

	CT_TEL_mBm							myLossOfInputPowerThreshold;
	CT_TEL_mBm							myMinimumSNRatio;
	uint32								myOmsWavelengthCapacity;
	CFG_OptCfgRegion *					myOptCfgRegion;
	bool								mySubNodeParametersFilled;
	bool                                myIsPilotToneSupported;

};

#endif /* __MON_SUBNODEPARAMETERS_H__ */
