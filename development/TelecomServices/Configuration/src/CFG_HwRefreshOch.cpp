// //Copyright(c Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include "../CFG_HwRefreshOch.h"
#include "../CFG_Och.h"
#include "../CFG_OchAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_Dispatcher.h>
#include <TsPii/TSPII_PipeIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <ITS/ITS_AppIfMain.h>
#include <ITS/ITS_Region.h>
#include <ITS/ITS_Config.h>
#include <T6100_MainAppIf.h>
#include <CSM/CSM_ConfigStatus.h>
#include <CSM/CSM_AppIf.h>
#include <T6100_OpticalShelfSlotIf.h>
#include <T6100_OpticalShelfIf.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_OchHistory.h>

const CT_TEL_mBm CFG_OCH_MAXIMUM_ATTENUATION        = -2500;
const CT_TEL_mBm CFG_OCH_MAXIMUM_ATTENUATION_RCMM   = -2550;
const FC_Milliseconds CFG_OCH_REFRESH_PERIOD        = (20 * 60 * 1000);// 20 minutes

CFG_HwRefreshOch::CFG_HwRefreshOch(CFG_AppIf& theCfgIf,
                                   TSPII_PipeRegion& thePipePiiRegion,
                                   unsigned int thePipePiiUnit,
                                   CT_Side theSide) :
    CFG_HwRefreshAction(theCfgIf),
    myPipePiiRegion(thePipePiiRegion),
    myItsConfigRegion(NULL),
    myCardContext(NULL),
    myPipePiiUnit(thePipePiiUnit),
    mySide(theSide),
    myHistoryCfgRegion(NULL),
    myOchMaxAtten(CFG_OCH_MAXIMUM_ATTENUATION),
    myRefreshTimer(CFG_OCH_REFRESH_PERIOD),
    myHistorySize(0),
    myIsAutoPowerAdjReady(false),
    myIsAllDataValid(false),
    myEvoaWrittenFlag(false),
    myXcInfoWrittenFlag(false),
    myHasAnyEvoaChanged(false),
    myHasAnyXcInfoChanged(false)
{
    myCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    FC_THROW_ERROR_IF(myCardContext==NULL, FC_RuntimeError, "Cannot get card context");

    myItsConfigRegion = T6100_MainAppIf::Instance().GetITSMainApp(mySide).GetConfigRegionOut();

    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    // false required until autopower adjustment is implemented
    GetBbAction()->AddInputRegion(theCfgIf.GetAutomaticCfgRegion(),false);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    GetBbAction()->AddInputRegion(myItsConfigRegion);  //for cross-connections

    myHistoryCfgRegion = static_cast<CFG_OchHistoryCfgRegion*>(theCfgIf.GetHistoryCfgRegion());
    if(myHistoryCfgRegion)
        GetBbAction()->AddOutputRegion(myHistoryCfgRegion);

    if(myCardContext->GetCardFamily() == RCMM_FAM)
        myOchMaxAtten = CFG_OCH_MAXIMUM_ATTENUATION_RCMM;

    for(int i = 0; i < CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        myPrevGain[i] = TRAFFIC_DEFAULT_POWER;
        myPrevActivePath[i] = false;
        myPrevPortNumber[i] = CT_TEL_INVALID_PORT_NUMBER;
    }

    myRefreshTimer.Start();
}

CFG_HwRefreshOch::~CFG_HwRefreshOch()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    GetBbAction()->RemoveInputRegion(myItsConfigRegion);
    if(myHistoryCfgRegion)
        GetBbAction()->RemoveOutputRegion(myHistoryCfgRegion);
}

FC_Object* CFG_HwRefreshOch::Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    // New booleans to handle the complexity of the HwRefresh action.
    // For example, the case when the Automatic Power Region is not ready
    // or any case in the future when the data should not be written to hardware.
    // These are defined to help TSPII determine what should be written to HW.
    // First two, ssume true until proven otherwise.
    myIsAutoPowerAdjReady = true;
    myIsAllDataValid = true;

    myEvoaWrittenFlag = false;
    myXcInfoWrittenFlag = false;
    myHasAnyEvoaChanged = false;
    myHasAnyXcInfoChanged = false;

    // Local variables
    bool incModCounter  = false;
    // For now, hasChanged is for any data changed (and written to TSPII)
    bool hasChanged = false;

    uint32 aIndex=0;
    TSPII_PipeIf& aPipePii = myPipePiiRegion[0];

    //Update status of each object in region
    uint32 aSize  = GetCfgIf().GetCfgRegion()->Size();
    myHistorySize = GetCfgIf().GetHistoryCfgRegion()->Size();

    // Since there can be two different sized regions and also the myPrev arrays (based on CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY), 
    // set the size to be the lowest value
    //if (myHistorySize < aSize) 
    //{
    //    aSize = myHistorySize;
    //}
    //if (CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY < aSize) 
    //{
    //    aSize = CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY;
    //}

    if (myCardContext->GetCardFamily() == QUAD_FAM)
    {
        //On QUAD cards, only the 1st object is used to configure because there is only one
        //attenuator.
        aSize = 1;
    }

    //If refresh is required at this time, read current gain values
    //from hardware.  Doing so insures that any configured values
    //that differ from hardware will be applied to hardware.
    if(myRefreshTimer.IsExpired())
    {

        while(aIndex<aSize)
        {
            myPrevGain[aIndex]       = aPipePii.GetEvoa(aIndex);
            myPrevActivePath[aIndex] = aPipePii.GetActivePath(aIndex);
            myPrevPortNumber[aIndex] = aPipePii.GetPortNumber(aIndex);
            aIndex++;
        }

        // Restart refresh timer
        myRefreshTimer.Start();
    }
    // if TSPII requested a refresh, it has probably just detected a card inserted
    // and the entire pipe need to be configured. start at the initial conditions
    if ( aPipePii.IsRefreshNeeded() )
    {
        for (aIndex = 0; aIndex<aSize; aIndex++ )
        {
            myPrevGain[aIndex] = TRAFFIC_DEFAULT_POWER;
            myPrevActivePath[aIndex] = false;
            myPrevPortNumber[aIndex] = CT_TEL_INVALID_PORT_NUMBER;
        }

        // clear the force refresh request
        aPipePii.SetRefreshNeeded(false);
    }

    aIndex=0;
    while (aIndex<aSize)
    {
        hasChanged = UpdateObject(theRunReason, aIndex);

        //if for any of the objects in the region the gain
        //has changed then we will increment the modification
        //counter
        if(hasChanged)
        {
            incModCounter = true;
        }
        aIndex++;
    }

    // if any changes were encountered
    if(incModCounter )
    {
        // Record the change (from anything)
        GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();
    }

    // Let TSPII know (via Commit) that Evoa data has been written
    // Later, this may be a Commit written everytime with multiple flags for TSPII,
    // including: myDataWrittenFlag, myIsAutoPowerAdjReady, myIsAllDataValid,
    // myHasAnyEvoaChanged, myHasAnyXconChanged.
    if (myEvoaWrittenFlag)
    {
        // For RCMM, commit any time the Evoa is written
        if (myCardContext->GetCardFamily() == RCMM_FAM)
        {
            aPipePii.CommitEvoas();
        }
        // If not RCMM, Commit only if all Power Adjustment Is Ready
        // Note: New CCM and OADM will work as CCM here
        else if (myIsAutoPowerAdjReady && myIsAllDataValid)
        {
            aPipePii.CommitEvoas();
        }
    }

    return NULL;
}

bool CFG_HwRefreshOch::UpdateObject(unsigned theRunReason, uint32 theIndex)
{
    bool isEvoaValid = true;
    bool hasEvoaChanged = false;
    bool hasXcInfoChanged = false;
    // New flag to always write Evoa values to TSPII for certain cards
    // Note: the normal behavior is to only write the Evoa values when there is a change.
    bool writeNow = false;

    // Refresh the hardware related to facility config object according
    // to current configuration within this object.
    CFG_Och& aCfgObject = static_cast<CFG_Och&>((*GetCfgIf().GetCfgRegion())[(bbindex_t)theIndex]);
    TSPII_PipeIf& aPipePii = myPipePiiRegion[0];

    // if automatic control is enabled, use value in automatic object
    CT_TEL_mBm aGain = 0;
    //facility port number connected to the wavelength (CCM only, for now)
    uint8 aPortNumber = CT_TEL_INVALID_PORT_NUMBER;

    // Check whether the path is active (CCM only, for now)
    // All other cards (at this time) should be true (set in else)
    // Note: CADM Family is set up to work like an RCMM in regard to the EVOAs.
    bool  anActivePath = false;
    if (myCardContext->GetCardFamily() == CCM_FAM)
    {
        // For CCM, Tspii want the Evoas written for each pass (not just when they change)
        writeNow = true;

        ITS_Config& aItsConfig = (*myItsConfigRegion)[(bbindex_t)theIndex];
        if (myPipePiiUnit == TSPII_P2L)
        {
            // If P2L on CCM, then check if this is an add port
            aPortNumber =  aItsConfig.GetPhyPortMapping();
            anActivePath = (aItsConfig.GetInfo(ITS_XC) && (aPortNumber != CT_TEL_INVALID_PORT_NUMBER));
            // ITS can not guarantee the information will be updated together, but CFG definition requires that a path must
            // active to have a valid port number and vice-versa.  Therefore, if either are default values,
            // make sure (set) both to default values
            if ((anActivePath == false) || (aPortNumber == CT_TEL_INVALID_PORT_NUMBER))
            {
                aPortNumber = CT_TEL_INVALID_PORT_NUMBER;
                anActivePath = false;
            }
        }
        else if (myPipePiiUnit == TSPII_L2P)
        {
            // If L2P on CCM, then check if this is a source to another (CCM) card,
            // which is supplied using the ITS new service PT_LtoP (which is pass through
            // in the Line to Port direction)
            anActivePath = (aItsConfig.GetInfo(ITS_XC) && aItsConfig.GetInfo(ITS_PT_LtoP));
        }

        // check if activePath or port number has changed
        if ((anActivePath != myPrevActivePath[theIndex]) ||
            (aPortNumber  != myPrevPortNumber[theIndex]))
        {
            hasXcInfoChanged = true;
        }
    }
    else
    {
        // For other cards, active path should be always true
        // This is needed for the Manual Control
        anActivePath = true;
    }

    if(aCfgObject.GetAutoPowerAdjEnable())
    {
        //get wavelenght configuration for this EVOA
        bool  aCrossConnected = false;

        if (myCardContext->GetCardFamily() == QUAD_FAM)
        {
            //for QUAD, cross-connect shold be true if at least one EVOA is in use
            FC_THROW_ERROR_IF(theIndex!=0, FC_RuntimeError, "Expecting only one object in region for QUAD");
            int i=0;
            for (i=0;i<4;i++)
            {
                ITS_Config& aItsConfig = (*myItsConfigRegion)[(bbindex_t)(GetWavelengthFromEvoa(i))];
                aCrossConnected |= aItsConfig.GetInfo(ITS_XC);
            }
        }
        //Since RCMM supports all 32/44 wavelengths we don't need to find
        //the band based on the hardware part#, the EVOA that we want
        //to control is the wavelength we are looking at
        else if (myCardContext->GetCardFamily() == RCMM_FAM || myCardContext->GetCardFamily() == CADM_FAM)
        {
            // For RCMM and CADMs we want to always send the attenuation value
            // in FP6.1, TSPII for the RCMM handle the command queue better so CFG
            // doesn't need to throw away an attenuation setting if it appears the
            // channel is already configured to the same value.
            // CADMs are like CCM and should always get all attenuation values.
            writeNow = true;

            ITS_Config& aItsConfig = (*myItsConfigRegion)[(bbindex_t)theIndex];
            aCrossConnected = (aItsConfig.GetInfo(ITS_XC) && aItsConfig.GetInfo(ITS_PtoL)) ||
                               aItsConfig.GetDirDxSideXconExists();
        }
        //Since the CCM is a different beast, then more special code.
        else if (myCardContext->GetCardFamily() == CCM_FAM)
        {
            // Set the cross connect based on the Active Path (determined above)
            aCrossConnected = anActivePath;
        }
        else
        {
            ITS_Config& aItsConfig = (*myItsConfigRegion)[(bbindex_t)(GetWavelengthFromEvoa(theIndex))];
            aCrossConnected = aItsConfig.GetInfo(ITS_XC);
        }

        // put attenuation to maximum if not cross-connected
        if (aCrossConnected)
        {
            if (GetCfgIf().GetAutomaticCfgRegion()->IsValid())
            {
                CFG_OchAutomatic& aAutomaticCfgObject = static_cast<CFG_OchAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[(bbindex_t)theIndex]);
                aGain = aAutomaticCfgObject.GetGain();
            }
            else
            {
                // Set a flag that Auto Power Adj is not ready and instaed of returning as before,
                // set the Evoa to Default value (so it won't be written to TSPII.
                myIsAutoPowerAdjReady = false;
                aGain = TRAFFIC_DEFAULT_POWER;
                // fc_cout<<"Cfg HwRefresh Och Wavelength # "<<theIndex<<" GetAutomaticCfgRegion()->IsValid() returned false "<<endl;
            }
        }
        else // no cross-connected
        {
                aGain = myOchMaxAtten;
        }
    }

    // Here, Agent is controlling the Evoa (Gain)
    // Add code for CCM case because Agent will write to both pipes
    // and only the active path (determined above) should be applied.
    else
    {
        aGain = aCfgObject.GetGain();

        // If not an active path, then set Gain to max attenuation.
        // Note: for all non-CCM cards, activePath should be true.
        if (! anActivePath )
        {
            aGain = myOchMaxAtten;
        }
    }

    // Set gain in HW

    // make sure that we are not writing garbage data to the EVOA
    // by never letting the hasEvoaChangedFlag be true when gain is TRAFFIC_DEFAULT_POWER
    if (aGain != TRAFFIC_DEFAULT_POWER)
    {
        hasEvoaChanged = ((abs(aGain) != abs(myPrevGain[theIndex])));
    }
    else
    {
        // Set the Evoa Flag (so the Evoa isn't written to TSPII later)
        isEvoaValid = false;
        // Record the fact that an invalid data exists.
        myIsAllDataValid = false;
        // fc_cout<<"Cfg HwRefresh Och Wavelength # "<<theIndex<<" aGain is equal to TRAFFIC_DEFAULT_POWER "<<endl;
    }


    if(hasXcInfoChanged || hasEvoaChanged)
    {
        //record this set evoa in the history
        if ((myHistoryCfgRegion) && (theIndex < myHistorySize)) 
        {
            CFG_OchHistory& aOchHist = (*myHistoryCfgRegion)[(bbindex_t)theIndex];
            aOchHist.RecordHistory(aGain, myPrevGain[theIndex]);
            aOchHist.RecordMoreHistory(anActivePath, aPortNumber);
        }
        writeNow = true;

        if (hasXcInfoChanged)
        {
            myHasAnyXcInfoChanged = true;
        }
        if (hasEvoaChanged)
        {
            myHasAnyEvoaChanged = true;
        }
    }


    if (writeNow)
    {
        myXcInfoWrittenFlag = true;

        aPipePii.SetPortNumber(aPortNumber, theIndex);
        aPipePii.SetActivePath(theIndex, anActivePath);

        // Save off values written to TSPII
        myPrevActivePath[theIndex] = anActivePath;
        myPrevPortNumber[theIndex] = aPortNumber;

        // Only Write Valid Evoas to TSPII
        if (isEvoaValid)
        {
            myEvoaWrittenFlag = true;
            aPipePii.SetEvoa(aGain, theIndex);
            // Save off values written to TSPII
            myPrevGain[theIndex] = aGain;
        }
    }

    // Keep one return (any change in data)
    return(hasXcInfoChanged || hasEvoaChanged);
}

uint32 CFG_HwRefreshOch::GetWavelengthFromEvoa(uint32 theEvoa) const
{
    // get CSM region of that mux card
    T6100_SlotIf* aSlotIf = dynamic_cast<T6100_SlotIf*>(myCardContext->GetParent());

    if( NULL != aSlotIf) 
    {
        CSM_CardStatusRegion* aCsmRegion = &aSlotIf->GetCsmApp().GetCardStatusRegion();
        CSM_CardStatus& aCsm          = (*aCsmRegion)[0];

        // get base wavelenght of the mux card and return absolute wavelenght for this evoa
        return aCsm.GetCardWavelenght().WavelengthIndex()+theEvoa;
    }

    return 0;
}
