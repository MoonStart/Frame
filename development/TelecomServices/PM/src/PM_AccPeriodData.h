/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Class to accumulate Data parameters for one accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODDATA_H
#define PM_ACCUMULATIONPERIODDATA_H

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
//##ModelId=3C9255BB012E
class PM_AccumulationPeriodData : public PM_AccumulationPeriodCounter
{
public:

    //Class default constructor.
    //##ModelId=3C9255BB0390
    PM_AccumulationPeriodData(PM_GenericApplication &theGenericApplication,
                              CT_PM_64BitValue*     theMaxValueTable,
                              PM_Rules&             theRules,
                              uint32                thePortNumber,
                              CT_PM_Period          thePeriod);

    //Class default destructor.
    //##ModelId=3C9255BB03A5
    virtual ~PM_AccumulationPeriodData();

    //This method verifies if each entity inhibition is 
    //enable or not. If not it calls update period of each entity.
    //##ModelId=3C9255BB03AE
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period at the end of period.
    //##ModelId=3E6E4CE20135
    virtual bool UpdateEndPeriod();

    //Resets the soaking SES count for the change of UA 
    //state. 
    //This method is called when there is a period change.
    //##ModelId=3C9255BB03D8
    virtual void RegAdjReset();

    //Adjusts the IDF of all parameters according to the 
    //inhibition status. This method is used at the start of 
    //a new accumulation period.
    virtual void AdjustCurrentIdf();


protected:

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    //##ModelId=3E7793BF015B
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

	// Adjusts the current value data and IDF states
	// based on Auto-Rate Lock state.
	virtual bool AdjustForAutoRateLock();

	// Flag to indicate that Auto-Rate Lock inhibit profiles should
	// be applied if this is an Auto-Rate Lock facility.
	bool myDisableAutoRateInhibit;

    virtual CT_PM_64BitValue GetMaxValueTable64Bit(CT_PM_Parameter theParameter);
    virtual CT_EntityType GetEntityTypeFor64BitPM();

private:

    //Flag that indicates Unavailability state of Regenerator 
    //Section.
    //##ModelId=3C9255BC00C3
    bool myUaDeclaredRs;

    //Flag to indicate the potential to be in Unavailability state of Regenerator Section.
    //##ModelId=3C9255BC00D5
    bool myPotentialStateChangeRs;

    //This class handles the Unavailability state of 
    //Regenerator Section.
    //##ModelId=3C926092011B
    PM_LayerElem myLayerElementRs;

};

#endif //PM_ACCUMULATIONPERIODDATA_H
