/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     January 6, 2006 Larry Wolfrum.
 DESCRIPTION:   Class for RMON gauge parameters for an accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODRMONGAUGE_H
#define PM_ACCUMULATIONPERIODRMONGAUGE_H

#include <PM/src/PM_AccPeriodGauge.h>

class PM_AccumulationPeriodRmonGauge : public PM_AccumulationPeriodGauge
{
public:

    //Class default constructor.
    PM_AccumulationPeriodRmonGauge(PM_GenericApplication &theGenericApplication,
                              CT_PM_Value*          theMaxValueTable,
                              PM_Rules&             theRules,
                              uint32                thePortNumber,
                              CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodRmonGauge();

    //This method verifies if each entity inhibition is 
    //enabled or not. If not it calls update period of each entity.
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

protected:

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

	// Adjusts the current value data and IDF states
	// based on Auto-Rate Lock state.
	virtual bool AdjustForAutoRateLock();

	// Over-ridden version of method to adjust IDF flags at end of period
	// for Auto Rate lock.
	virtual void AdjustCurrentIdf();

    //Verifies if threshold and values has to be reset due to 
    //a reset request.
    virtual bool CheckResetReqChange(PM_BbCfg    &theConfig,
                                     PM_BbValue& theCurrentValue);

	// Flag to indicate that Auto-Rate Lock inhibit profiles should
	// be applied if this is an Auto-Rate Lock facility.
	bool myDisableAutoRateInhibit;

};

#endif //PM_ACCUMULATIONPERIODRMONGAUGE_H
