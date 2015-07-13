/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     January 4, 2006, Larry Wolfrum.
 DESCRIPTION:   Class to accumulate RMON counter parameters for one accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODRMONCOUNTER_H
#define PM_ACCUMULATIONPERIODRMONCOUNTER_H

#include <PM/src/PM_AccPeriodCounter.h>
#include <PM/src/PM_LayerElem.h>
#include <PM/PM_GenericApplication.h>

// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_BbTcaCondtion;
template <class OBJECT_TYPE> class PM_RegionImp;


//This class updates the Data (RS, FICON, ESCON...) PM parameters. 
//This class computes PM parameters with the data given by 
//the Collector. Then it updates the blackboard regions owned 
//by Processor with the current PM parameter values.
class PM_AccumulationPeriodRmonCounter : public PM_AccumulationPeriodCounter
{
public:

    //Class default constructor.
    PM_AccumulationPeriodRmonCounter(PM_GenericApplication &theGenericApplication,
                              CT_PM_64BitValue*     theMaxValueTable,
                              PM_Rules&             theRules,
                              uint32                thePortNumber,
                              CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodRmonCounter();

    //This method verifies if each entity inhibition is 
    //enabled or not. If not it calls update period of each entity.
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period at the end of period.
    virtual bool UpdateEndPeriod();

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

	// Flag to indicate that Auto-Rate Lock inhibit profiles should
	// be applied if this is an Auto-Rate Lock facility.
	bool myDisableAutoRateInhibit;

    virtual CT_PM_64BitValue GetMaxValueTable64Bit(CT_PM_Parameter theParameter);
    virtual CT_EntityType GetEntityTypeFor64BitPM();
};

#endif //PM_ACCUMULATIONPERIODRMONCOUNTER_H
