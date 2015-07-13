// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_OpticalIf.h>
#include <ErrorService/FC_Error.h>
#include "../MON_TxOptUpdateStatusAction.h"
#include "../MON_TxOptStatus.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"


// A low power transponder should drive at least -6dBm
const CT_TEL_mBm MON_TRN_OUTPUT_POWER_DEFECT = -1000; //-10dBm
const CT_TEL_mBm MON_TRN_OUTPUT_POWER_CLEAR = -900; //-9dBm

MON_TxOptUpdateStatusAction::MON_TxOptUpdateStatusAction(MON_AppIf& theMonIf,
                                                         TSPII_OpticalRegion& theOptPiiRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myOptPiiRegion(theOptPiiRegion),
    myPassesPerFiveSecs(25),
    myCount(0)
{
    GetBbAction()->AddInputRegion(&myOptPiiRegion);
    GetBbAction()->AddOutputRegion(GetMonIf().GetStatusRegion(), false);

    // Compute PassesPerSecond for throttling with different Tspii update periods.
    uint32 aTspiiUpdatePeriod = uint32(myOptPiiRegion[0].GetUpdatePeriod());
    if (aTspiiUpdatePeriod != 0) 
    {
        float aPassesPerSecond = float(1000) / aTspiiUpdatePeriod;
        // To get five seconds, multiply by five and round up.
        myPassesPerFiveSecs =  uint32((aPassesPerSecond * 5) + .49);
    }
}

MON_TxOptUpdateStatusAction::~MON_TxOptUpdateStatusAction()
{
    GetBbAction()->RemoveInputRegion(&myOptPiiRegion);
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetStatusRegion());
}

FC_Object* MON_TxOptUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    GetMonIf().GetStatusRegion()->Reset();
    return NULL;
}

FC_Object* MON_TxOptUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    //Update status of each object in region
    myCount++;
    UpdateObject(theRunReason, myOptPiiRegion[0]);
    return NULL;
}

void MON_TxOptUpdateStatusAction::UpdateObject(unsigned theRunReason, TSPII_OpticalIf& theOptPII)
{
    CT_TEL_mBm thePrevOutputPower, theCurrOutputPower, aDiffPower;
    MON_TxOptStatus& aStatus = static_cast<MON_TxOptStatus&>((*GetMonIf().GetStatusRegion())[0]);
    bool aSignifPowerChange = false;

    bool hasChanged = false;
    //--------------------------------------------------------------
    // STATUS
    try
    {
        // update current laser state
        hasChanged |= aStatus.SetLaserState(theOptPII.GetLaserState());

        // need to relax request
        switch (myCount%3)
        {
        case 0:
            aStatus.SetLaserBiasCurrent(theOptPII.GetLaserBiasCurrent());
            break;
        case 1:
            aStatus.SetLaserTemp(theOptPII.GetLaserTemperature());
            break;
        case 2:
            thePrevOutputPower = aStatus.GetOutputPower();
            //hasChanged |= aStatus.SetOutputPower(theOptPII.GetOpticalPowerTransmitted());
            aStatus.SetOutputPower(theOptPII.GetOpticalPowerTransmitted());
            theCurrOutputPower = aStatus.GetOutputPower();

            if (thePrevOutputPower != theCurrOutputPower)
            {
                // Check if there is a significant change in power 
                // If there is, then the hasChanged will be updated below.
                aDiffPower = abs(theCurrOutputPower - thePrevOutputPower);
                aSignifPowerChange = (aDiffPower >= ((CT_TEL_mBm) CT_TEL_POWER_FACTOR));
            }

            // update low TX power defect
            bool aLowTxPowerDefect = aStatus.GetLowTxPowerDefect();

            // if got default power, we assume it is not available
            if ((theCurrOutputPower == TRAFFIC_DEFAULT_POWER) ||
                 !aStatus.IsValidated() )
            {
                // do not rise any defect for something not available
                aLowTxPowerDefect = false;
            }
            else if (theCurrOutputPower < MON_TRN_OUTPUT_POWER_DEFECT)
            {
                // this can be set when laser is disabled
                aLowTxPowerDefect = true;
            }
            else if (theCurrOutputPower > MON_TRN_OUTPUT_POWER_CLEAR)
            {
                aLowTxPowerDefect = false;
            }
            hasChanged |= aStatus.SetLowTxPowerDefect(aLowTxPowerDefect);
            break;
        }

        // Always update the has changed flag after a certain time (36 x 5 sec = 3 minute)
        if (((myCount % (myPassesPerFiveSecs*36)) == 0) || aSignifPowerChange)
        {
            hasChanged = true;
        }

        // validate object
        aStatus.Validate();
    }
    catch (FC_HWError&)
    {
        // invalidate object
        aStatus.Invalidate();
    }

    if (hasChanged)
        GetMonIf().GetStatusRegion()->IncModificationCounter();
}
