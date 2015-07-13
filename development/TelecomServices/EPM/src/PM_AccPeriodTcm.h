/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     8 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Class to accumulate TCM layer parameters 
                for one accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODTCM_H
#define PM_ACCUMULATIONPERIODTCM_H

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
class PM_AccumulationPeriodTcm : public PM_AccumulationPeriodCounter
{
public:

    //Class default constructor.
    PM_AccumulationPeriodTcm(PM_GenericApplication &theGenericApplication,
                             CT_PM_64BitValue*     theMaxValueTable,
                             PM_Rules&             theRules,
                             uint32                thePortNumber,
                             CT_PM_Period          thePeriod);

    //Class default destructor.
    virtual ~PM_AccumulationPeriodTcm();

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

    //Sets all modification actions on region changing and 
    //setup the attributes according to the actual 
    //configuration of the control region.
    virtual void Init(uint16 thePortNumber);

    //Resets all PM values to zero, TCA statues are reset,
    //IDF are set to invalid.
    virtual void ResetAll();

    //Adjusts the IDF of all parameters according to the 
    //inhibition status. This method is used at the start of 
    //a new accumulation period.
    virtual void AdjustCurrentIdf();

    //Set the availability when monitoring 
    //status is invalid or valid of specifier parameter.
    virtual void SetAvailability(CT_PM_Parameter theParameter, bool theAvailability);

protected:

    //Verifies if there is a pending threshold configuration.
    virtual bool VerifyConfigChange();

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig);

    virtual CT_PM_64BitValue GetMaxValueTable64Bit(CT_PM_Parameter theParameter);
    virtual CT_EntityType GetEntityTypeFor64BitPM();

private:

    //Flag that indicates Unavailability state of Near-End Multiplex Section 
    bool myUaDeclaredTcm;

    //Flag to indicate the potential to be in Unavailability state of 
    //Near-End Multiplex Section.
    bool myPotentialStateChangeTcm;

    //This class handles the Unavailability state of Near-End Multiplex Section
    PM_LayerElem myLayerElementTcm;

    // Index to associated dynamically allocated object.
    uint16 myDynamicIndex;
};

#endif //PM_ACCUMULATIONPERIODTCM_H
