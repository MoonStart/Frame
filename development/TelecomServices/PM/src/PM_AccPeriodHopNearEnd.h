/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM
 AUTHOR   :     16 February 2004  Hemant Thakkar
 DESCRIPTION:   Class to accumulate Near-End SONET/SDH HOP layer parameters 
                for one accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODHOPNEAREND_H
#define PM_ACCUMULATIONPERIODHOPNEAREND_H

#include <PM/src/PM_AccPeriodCounter.h>
#include <PM/src/PM_LayerElem.h>
#include <PM/PM_GenericApplication.h>

// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_BbTcaCondtion;
template <class OBJECT_TYPE> class PM_RegionImp;


//This class updates the Near-End SONET/SDH HOP layer PM parameters. 
//This class computes PM parameters with the data given by 
//the Collector. Then it updates the blackboard regions owned 
//by Processor with the current PM parameter values.
class PM_AccumulationPeriodHopNearEnd : public PM_AccumulationPeriodCounter
{
public:

    //Class default constructor.
    PM_AccumulationPeriodHopNearEnd(PM_GenericApplication &theGenericApplication,
                                   CT_PM_Value*          theMaxValueTable,
                                   PM_Rules&             theRules,
                                   uint32                thePortNumber,
                                   CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodHopNearEnd();

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

	//Adjusts the IDF of all parameters according to the 
    //inhibition status. This method is used at the start of 
    //a new accumulation period.
    virtual void AdjustCurrentIdf();

protected:

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

	// Adjusts the current value data and IDF states
	// based on the STS-1 selection for pointer justification
	// data collection.
	virtual bool AdjustForStst1Selection();

private:

    //Flag that indicates Unavailability state of Near-End Multiplex Section 
    bool myUaDeclaredHopNearEnd;

    //Flag to indicate the potential to be in Unavailability state of 
    //Near-End Multiplex Section.
    bool myPotentialStateChangeHopNearEnd;

    //This class handles the Unavailability state of Near-End Multiplex Section
    PM_LayerElem myLayerElementHopNearEnd;

	// Flag to indicate that the STS-1 pointer justification parameter inhibit
	// IDF flags can be dynamically set according to the update algorithm. This
	// flag is set at the beginning of a control period until the All Inhibit
	// flag is cleared.
	bool myDisableSts1Inhibit;

};

#endif //PM_ACCUMULATIONPERIODHOPNEAREND_H
