/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004  Hemant Thakkar
 DESCRIPTION:   Class to accumulate Near-End SONET/SDH MS layer parameters 
                for one accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODMSNEAREND_H
#define PM_ACCUMULATIONPERIODMSNEAREND_H

#include <PM/src/PM_AccPeriodCounter.h>
#include <PM/src/PM_LayerElem.h>
#include <PM/PM_GenericApplication.h>

// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_BbTcaCondtion;
template <class OBJECT_TYPE> class PM_RegionImp;


//This class updates the Near-End SONET/SDH MS layer PM parameters. 
//This class computes PM parameters with the data given by 
//the Collector. Then it updates the blackboard regions owned 
//by Processor with the current PM parameter values.
class PM_AccumulationPeriodMsNearEnd : public PM_AccumulationPeriodCounter
{
public:

    //Class default constructor.
    PM_AccumulationPeriodMsNearEnd(PM_GenericApplication &theGenericApplication,
                                   CT_PM_Value*          theMaxValueTable,
                                   PM_Rules&             theRules,
                                   uint32                thePortNumber,
                                   CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodMsNearEnd();

    //This method verifies if each entity inhibition is 
    //enable or not. If not it calls update period of each entity.
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period at the end of period.
    virtual bool UpdateEndPeriod();

    //Resets the soaking SES count for the change of UA 
    //state. 
    //This method is called when there is a period change.
    virtual void RegAdjReset();

protected:

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

	// Adjusts the current value data and IDF states
	// based on Auto-Rate Lock state.
	virtual bool AdjustForAutoRateLock( PM_BbValue& theValue );

 	// Adjusts the current value data and IDF states
	// based on protection scheme state.
	virtual bool AdjustForProtectionScheme( PM_BbValue& theValue );

	// Over-ridden version of method to adjust IDF flags at end of period
	// for Auto Rate lock.
	virtual void AdjustCurrentIdf();

	// Flag to indicate that Auto-Rate Lock inhibit profiles should
	// be applied if this is an Auto-Rate Lock facility.
	bool myDisableAutoRateInhibit;

	// Flag to indicate that PM accumulation has previously been enabled
	// in this control period.
	bool myProtectionSchemeInhibit;

private:

    //Flag that indicates Unavailability state of Near-End Multiplex Section 
    bool myUaDeclaredMsNearEnd;

    //Flag to indicate the potential to be in Unavailability state of 
    //Near-End Multiplex Section.
    bool myPotentialStateChangeMsNearEnd;

    //This class handles the Unavailability state of Near-End Multiplex Section
    PM_LayerElem myLayerElementMsNearEnd;

};

#endif //PM_ACCUMULATIONPERIODMSNEAREND_H
