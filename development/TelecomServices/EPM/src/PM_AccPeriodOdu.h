/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Class to accumulate ODU layer parameters 
                for one accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODODU_H
#define PM_ACCUMULATIONPERIODODU_H

#include <PM/src/PM_AccPeriodCounter.h>
#include <PM/src/PM_LayerElem.h>
#include <PM/PM_GenericApplication.h>

// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_BbTcaCondtion;
template <class OBJECT_TYPE> class PM_RegionImp;


//This class updates the ODU layer PM parameters. 
//This class computes PM parameters with the data given by 
//the Collector. Then it updates the blackboard regions owned 
//by Processor with the current PM parameter values.
class PM_AccumulationPeriodOdu : public PM_AccumulationPeriodCounter
{
public:

    //Class default constructor.
    PM_AccumulationPeriodOdu(PM_GenericApplication &theGenericApplication,
                             CT_PM_64BitValue*     theMaxValueTable,
                             PM_Rules&             theRules,
                             uint32                thePortNumber,
                             CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodOdu();

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
	// based on protection scheme state.
	virtual bool AdjustForProtectionScheme( PM_BbValue& theValue );

	// Over-ridden version of method to adjust IDF flags at end of period
	// for Auto Rate lock.
	virtual void AdjustCurrentIdf();

	// Flag to indicate that PM accumulation has previously been enabled
	// in this control period.
	bool myProtectionSchemeInhibit;

    virtual CT_PM_64BitValue GetMaxValueTable64Bit(CT_PM_Parameter theParameter);
    virtual CT_EntityType GetEntityTypeFor64BitPM();

private:

    //Flag that indicates Unavailability state of Near-End Multiplex Section 
    bool myUaDeclaredOdu;

    //Flag to indicate the potential to be in Unavailability state of 
    //Near-End Multiplex Section.
    bool myPotentialStateChangeOdu;

    //This class handles the Unavailability state of Near-End Multiplex Section
    PM_LayerElem myLayerElementOdu;

};

#endif //PM_ACCUMULATIONPERIODODU_H
