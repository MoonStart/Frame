/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Class to accumulate Data parameters for one accumulation
                period.
--------------------------------------------------------------------------*/

#include <PM/PM_BbCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_TypeData.h>
#include <PM/src/PM_RulesData.h>
#include <PM/src/PM_AccPeriodData.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3C9255BB0390
PM_AccumulationPeriodData::PM_AccumulationPeriodData( PM_GenericApplication &theGenericApplication,
                                                      CT_PM_64BitValue*     theMaxValueTable,
                                                      PM_Rules&             theRules,
                                                      uint32                thePortNumber,
                                                      CT_PM_Period          thePeriod):

    PM_AccumulationPeriodCounter( theGenericApplication,
                                  theMaxValueTable,
                                  theRules,
                                  PM_TypeData::GetMaxNbParamsNoHighOrder64Bits(),
                                  thePortNumber,
                                  thePeriod),
    // Regenerator Section stuff.
    myUaDeclaredRs(false),
    myPotentialStateChangeRs(false),
    myDisableAutoRateInhibit(true)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3C9255BB03A5
PM_AccumulationPeriodData::~PM_AccumulationPeriodData()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB03D8
void PM_AccumulationPeriodData::RegAdjReset()
{
    // This will reset the soaking SES count for the change of UA state.
    myLayerElementRs.ResetSoakCountforUa();

    ResetAllAdjustRegister();

}

//-----------------------------------------------------------------
//##ModelId=3C9255BB03AE
bool PM_AccumulationPeriodData::UpdatePeriod(bool* theValidityState,
                                             bool* theFilteringStateFirstStage,
                                             bool* theFilteringStateSecondStage)
{
    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Regenerator section rules.
    PM_RulesData& dataRules = (PM_RulesData&) myRules;

    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    myUaDeclaredRs = myLayerElementRs.UpdateUA(dataRules.GetValueParam(PM_TypeData::PM_SES).UnsignedValue==1);
    myPotentialStateChangeRs = myLayerElementRs.IsPotential2ChgState();

    // Apply Auto-Rate Lock adjustments to current value data.
    SetSomeTcaChangedState( AdjustForAutoRateLock() );

    // Check if All parameters accumulation is enabled.
    if (!GetCurrentAllInhibit())
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, theValidityState,
                                                  theFilteringStateFirstStage,
                                                  theFilteringStateSecondStage,
                                                  false) );
    }

    return GetSomeTcaChangedState();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CE20135
bool PM_AccumulationPeriodData::UpdateEndPeriod()
{
    bool    validityState[PM_MAX_NUMBER_OF_PARAMETERS];             // Computed validity state.
    bool    filteringStateFirstStage[PM_MAX_NUMBER_OF_PARAMETERS];  // Computed filtering state first stage.
    bool    filteringStateSecondStage[PM_MAX_NUMBER_OF_PARAMETERS]; // Computed filtering state second stage.
    uint32  param;                                                  // Parameter index.


    // Get the reference to the value Operation BB object associated to this port.
    PM_BbValue& value = (*GetCurrentValueRegion())[myIndex];

    // Get the reference to the control configuration BB object associated to this port.
    PM_BbCfg& config = (*GetConfigRegion())[myIndex];

    // Set validity state to valid and filtering state to no filtering.
    for (param = 0; param < myNumberOfParam; param++)
    {
        filteringStateFirstStage[param] = false;
        filteringStateSecondStage[param] = false;
        validityState[param] = true;
    }

    // In normal accumulation (it is not the end of period) it can have an accumulation
    // in the adjustement registers. These registers are used to accumulate counters when
    // in potential to be in UA state (see SRS behavioral for more detail on that).
    // At the end of the period, an other pass must be done in that function to add
    // the counters accumulated to the adjustement registers in the normal register.
    // In that case, theEndOfPeriod flag is set to true. also, it is possible that a
    // threshold is crossed, so, a TCA must be sent to the ADMIN.

    // Check if All parameters accumulation is enabled.
    if (!GetCurrentAllInhibit())
    {
        SetSomeTcaChangedState( UpdatePeriodOfAll(value, config, validityState,
                                                  filteringStateFirstStage,
                                                  filteringStateSecondStage,
                                                  true) );
    }

    return GetSomeTcaChangedState();

}

//------------------------------------------------------------------
//##ModelId=3E7793BF015B
bool PM_AccumulationPeriodData::CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue)
{
    bool isRegionChanged = false;
    uint16 param=0;     //This is my parameter loop index.

    // Verify accumulation inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL) != GetCurrentAllInhibit() )
    {
        SetCurrentAllInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_INHIBIT_ALL));

        // Get pointer to Auto-Rate Lock inhibit profile
        PM_RulesData& rulesRef = dynamic_cast<PM_RulesData&>(GetRules());
        bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

        // Validate pointer to see if this facility is configured for
        // Auto-Rate Lock
        if( aAutoRateInhibitProfile == NULL )
        {
            // This is a fixed rate facility.
            for (param = 0; param < myNumberOfParam; param++)
            {
                theValue.GetIdf()->SetInhibit(param, GetCurrentAllInhibit());

                ResetAdjustRegister(param);
            }
        }
        else
        {
            // This is an Auto-Rate Lock facility

            // Within a period, any change in inhibition sets the
            // invalid flag.
            theValue.GetIdf()->ForcedSetAllIdf( true );

            if( myDisableAutoRateInhibit && !(GetCurrentAllInhibit()) )
            {
                // This is the first time PM collection has been enabled
                // during this period.
                 myDisableAutoRateInhibit = false;
            }

            if( !myDisableAutoRateInhibit )
            {
                for (param = 0; param < myNumberOfParam; param++)
                {

                    theValue.GetIdf()->ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                    aAutoRateInhibitProfile++;

                    ResetAdjustRegister(param);
                }
            }
        }
        myLayerElementRs.ResetSoakCountforUa();
        isRegionChanged = true;
    }

    // Verify TCA inhibition of all parameters.
    if ( theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ALL) != GetCurrentAllTcaInhibit() )
    {
        SetCurrentAllTcaInhibit(theConfig.GetInhibit(CT_PM_SIGNAL_CTL_BITMASK_TCA_INHIBIT_ALL));
        isRegionChanged = true;
    }

    return isRegionChanged;

}

bool PM_AccumulationPeriodData::AdjustForAutoRateLock()
{
    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesData& rulesRef = dynamic_cast<PM_RulesData&>(GetRules());
    bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();
    bool retVal = false;

    // Validate pointer to see if this facility is configured for
    // Auto-Rate Lock
    if( (aAutoRateInhibitProfile != NULL) && (!myDisableAutoRateInhibit) )
    {
        // Determine if an Auto-Rate Lock update has occured.
        if( rulesRef.IsAutoRateStateRefreshed() )
        {
            // An Auto-Rate update has occured.
            // Reset all of the current data.
            ResetAll();

            // Reset the adjustment register.
            RegAdjReset();

            // Get a reference to the IDF object.
            PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

            // Adjust the IDF inhibit states per the Auto-Rate
            // inhibit profile.
            for (uint32 param=0; param<myNumberOfParam; param++)
            {
                idf.ForcedSetInhibit( param, *aAutoRateInhibitProfile );
                aAutoRateInhibitProfile++;
            }

            retVal = true;
        }
    }
    return retVal;
}

//------------------------------------------------------------------
void PM_AccumulationPeriodData::AdjustCurrentIdf()
{
    uint32 param;

    // Get pointer to Auto-Rate Lock inhibit profile
    PM_RulesData& rulesRef = dynamic_cast<PM_RulesData&>(GetRules());
    bool* aAutoRateInhibitProfile = rulesRef.GetAutoRateInhibitProfile();

    // Get a reference to the IDF object.
    PM_BbIdf& idf = *((*GetCurrentValueRegion())[myIndex].GetIdf());

    // In new period, IDF should be reset.
    idf.ForcedSetAllIdf(false);

    // Validate pointer to see if this facility is configured for
    // Auto-Rate Lock
    if( aAutoRateInhibitProfile != NULL )
    {
        // Set initial rules for applying Auto-Rate Lock inhibit.
        myDisableAutoRateInhibit =  GetCurrentAllInhibit();

        // Adjust the IDF inhibit states per the Auto-Rate
        // inhibit profile combined with the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, (*aAutoRateInhibitProfile | myDisableAutoRateInhibit) );
            aAutoRateInhibitProfile++;
        }
    }
    else
    {
        // Set the IDF inhibit states based on the configuration inhibit.
        for (param=0; param<myNumberOfParam; param++)
        {
            idf.ForcedSetInhibit( param, GetCurrentAllInhibit() );
        }
    }
}

//-----------------------------------------------------------------
CT_PM_64BitValue PM_AccumulationPeriodData::GetMaxValueTable64Bit(CT_PM_Parameter theParameter)
{
    if ( ((CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTM) ||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_FGTME)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_OSM2C) ||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMS) ) &&
         ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_0) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_1)) )
    {
        switch ( theParameter )
        {
            case PM_TypeData::PM_SE:  return myMaxValueTable64Bit[PM_TypeData::PM_SE_HIGH];
        }
    }
 
    return myMaxValueTable64Bit[theParameter];
}
 
//-----------------------------------------------------------------
CT_EntityType PM_AccumulationPeriodData::GetEntityTypeFor64BitPM()
{
    CT_EntityType a64BitEntityType = CT_UNKNOWN_ENTITY_TYPE;
 
    if ( ((CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTM)||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_OSM2C) ||
          (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMS)) &&
         ((myGenericApplication.GetSide() == CT_PM_PORT_SIDE_0) ||
          (myGenericApplication.GetSide() == CT_PM_PORT_SIDE_1)) )
    {
        a64BitEntityType = CT_ETH; // must distinguish between Data(ETH) and Rmon(HGE)
    }
 
    return a64BitEntityType;
}

