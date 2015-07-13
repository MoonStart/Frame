// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#include "../MON_PilotToneProcessingController.h"
#include <ErrorService/FC_Error.h>
#include <PII_Interrupt.h>
#include "../MON_OchResult.h"
#include <Monitoring/MON_PilotToneProcessorRequest.h>
#include <BaseClass/FC_Stream.h>
#include <PII_TickTimer.h>
#include <T6100_Dispatcher.h>
#include "../MON_OchConfig.h"
#include "../MON_SubNodeParameters.h"
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <Blackboard/FC_BbRegionId.h>
#include <Monitoring/MON_OchConfig.h>
#include <T6100_MainAppIf.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CsPii/CSPII_CardIF.h>

#ifdef __TARGET__
#include <Monitoring/MON_PilotToneTaskProcessor.h>
#endif

//##ModelId=3C7170DD0226
MON_PilotToneProcessingController* MON_PilotToneProcessingController::myInstance = NULL;
uint32 MON_PilotToneProcessingController::myMaxSimultenousRequest = 0;


//##ModelId=3C7170DC03D0
MON_PilotToneProcessingController& MON_PilotToneProcessingController::GetInstance()
{
    if (myInstance==NULL)
        myInstance = new MON_PilotToneProcessingController();

    return *myInstance;
}

//Constructor.
//##ModelId=3C7170DD00F6
MON_PilotToneProcessingController::MON_PilotToneProcessingController():
    myChannelId(0)
{
    FC_THROW_ERROR_IF(myMaxSimultenousRequest==NULL, FC_RuntimeError, "Max Simultenous Request was not set");

    // get a pointer to beginning of list
    myNextRequest = myRequestList.begin();

    // resize free pilot tone action pool to maximum size
    uint32 i=0;
    while (i < myMaxSimultenousRequest)
    {
        myFreePilotToneActionList.push_back(new MON_PilotToneAction());
        i++;
    }
}

void MON_PilotToneProcessingController::SetMaxSimultenousRequest(uint32 theMax)
{
    FC_THROW_ERROR_IF(myInstance!=NULL, FC_RuntimeError, "Cannot change max simul request after creation");
    myMaxSimultenousRequest = theMax;
}

//Override of Run method from FC_Action.
//##ModelId=3C7170DC03DA
void MON_PilotToneProcessingController::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_RuntimeError, "Run not supported");
}

//##ModelId=3C7170DD0006
FC_Object* MON_PilotToneProcessingController::DoRunWithReason(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

    // check if this is a callback. This is done regardless of whethere pilottome is enabled or not since
    // the pilottone could have been disabled during processing
    if (theParam != NULL)
    {
        // If caller is a pilot tone action, put it back in the free pool
        MON_PilotToneAction* anAction = dynamic_cast<MON_PilotToneAction*>(theParam);
        if (anAction)
            myFreePilotToneActionList.push_back(anAction);

    }

    if(!MON_SubNodeParameters::GetInstance().IsSubNodeParametersReady() ||
       (MON_SubNodeParameters::GetInstance().IsSubNodeParametersReady() && !MON_SubNodeParameters::GetInstance().IsPilotToneSupported()))
    {
        return NULL;
    }
    else
    {
#ifdef __TARGET__
        if(!MON_PilotToneTaskProcessor::GetInstance().IsPilotToneTaskInitilized())
            MON_PilotToneTaskProcessor::GetInstance().InitilizePilotToneTask();
#endif
    }

    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    // Determine if this action is running on a controller or a Transponder

    bool AllOtiDisabled = true;

    // Retrieve the card type
    CT_CardFamily aCardFam = CSPII_CardIF::GetInstance()->GetCardFamily();
    if(aCardFam == APM_FAM || aCardFam == OSC_FAM)
    {

        /****************************************************************************
        Important!!!!
        During Basic Commissioning it was discovered that this Process
        was consuming a large percent of the CPU
        It turns out that if MON_OTID is disabled for all chhannels that
        this Process cycles 6000 times per instance per sec!! looking for a request
        to process

        In order to not waste time this while loop checks for at least one MON_OTID
        channel to be enabled, if one is discovered then allow this process to run!!
        ***************************************************************************/
        int aSide = CT_SIDE_A;
        CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
        int maxSides = aSubNodeCfg.GetNumberOfSides();

        MON_Region* aSideOchConfigRegion;
        MON_OchConfigRegion* aOchConfigRegion;

        while((aSide < maxSides) && (AllOtiDisabled == true) )
        {
             aSideOchConfigRegion = T6100_MainAppIf::Instance().GetOchIf().
                  GetMonLineApp(static_cast<CT_Side>(aSide)).GetConfigRegion();
             if (aSideOchConfigRegion != NULL)
             {
                 aOchConfigRegion = static_cast<MON_OchConfigRegion*>(aSideOchConfigRegion);

                 // *** Added this check for region validity since we can skip
                 // the loop entirely if region is invalid.  ***
                 if (aOchConfigRegion->IsValid() == true)
                 {
                     uint32 j =0;
                     while  (AllOtiDisabled && j<omsWavelengthCapacity )
                     {
                         MON_OchConfig& aConfig = (*aOchConfigRegion)[(bbindex_t)j];
                         if (aConfig.GetExpectedChannelId() !=UNKNOWN_WAVELENGHT)
                             AllOtiDisabled = false;
                         j++;
                     }
                 }
             }//aOchConfigRegion !=NULL

             ++aSide;
        }//end while

    }
    else
    {  //if this is a Transponder then set defaults
        AllOtiDisabled = false;
    }

    // If At least one OTID is enabled  the process requests
    if (!AllOtiDisabled)
    {
        uint32 aChannelChange = 0;
        // fill the request list until full or until we scanned two complete channel
        // ********************************************************************************
        //Checking <=  omsWavelengthCapacity because Smart Transponders can't access
        // aSubNodeCfg.GetOmsWavelengthCapacity(), on Smart Transponders this call returns
        // a zero (0)!!!!!
        // ********************************************************************************
        while (!myFreePilotToneActionList.empty() && (aChannelChange<=omsWavelengthCapacity))
        {
            if (myNextRequest!=myRequestList.end())
            {
                // check if this wavelenght is expected by this request
                MON_OchConfigRegion* aConfigRegion = (*myNextRequest)->GetConfigRegion();

                // scan all the band specified in the request starting from 1st wavelenght
                uint32 i = 0;
                int aChannel = (*myNextRequest)->GetFirstWavelength();
                while(aConfigRegion->IsValid() && (i < (*myNextRequest)->GetBandwidth()))
                {
                    MON_OchConfig& aConfig = (*aConfigRegion)[aChannel];
                    if ( aConfig.GetExpectedChannelId() == myChannelId)
                    {
                        // start a pilot tone collection for this request
                        static MON_RequestID asRequestId = 0;
                        MON_PilotToneProcessorRequest  aRequest(myChannelId,
                                                                ++asRequestId,
                                                                MON_PT_EXACTMODE_NUM_SAMPLE,
                                                                TSPII_PT_LOW_PRIORITY);

                        // get a free pilot tone action from the pool
                        MON_PilotToneAction* anAction = *(myFreePilotToneActionList.begin());
                        myFreePilotToneActionList.pop_front();

                        // start a pilot tone collection
                        anAction->Collect(aRequest,
                                          (*myNextRequest)->GetStatusRegion(),
                                          i,
                                          (*myNextRequest)->GetTspiiRegion(),
                                          this);
                        break;
                    }
                    ++i;
                    ++aChannel;
                }
                ++myNextRequest;
            }
            // we have reached the end of the list
            else
            {
                // let's proceed to the next channel
                myChannelId = CT_Wavelength((uint8)((myChannelId.WavelengthIndex()+1)%omsWavelengthCapacity));
                aChannelChange++;
                myNextRequest = myRequestList.begin();
            }
        }
  }//AllOtiDisabled
    return NULL;
}

//Virtual destructor.
//##ModelId=3C7170DD0042
MON_PilotToneProcessingController::~MON_PilotToneProcessingController()
{
}

void MON_PilotToneProcessingController::Register(MON_PilotToneControllerRequest* theRequest)
{
    // make sure it is not already in list, then add it
    myRequestList.remove(theRequest);
    myRequestList.push_back(theRequest);
    // myNextRequest = myRequestList.begin();
}

void MON_PilotToneProcessingController::Unregister(MON_PilotToneControllerRequest* theRequest)
{
    bool needNewPointer = false;


    if (myRequestList.empty())
    {
        needNewPointer = true;
    }
    else
    {
        if (theRequest == (*myNextRequest))
            needNewPointer = true;

        myRequestList.remove(theRequest);
    }

    // change next request since if it has changed
    if (needNewPointer)
        myNextRequest = myRequestList.begin();
}



void MON_PilotToneProcessingController::Display( FC_Stream& theStream )
{
    theStream.GetOutputStream() << "Maximum simultaneous request: " << myMaxSimultenousRequest << endl;
    theStream.GetOutputStream() << "Free Pilot tone actions:      " << myFreePilotToneActionList.size() << endl;
    theStream.GetOutputStream() << "Number of monitoring point:   " << myRequestList.size() << endl;
    theStream.GetOutputStream() << "Current channel ID:           " << (uint32)myChannelId.WavelengthIndex() << endl;
    FC_BbRegionId aRegionId;
    if (myNextRequest != myRequestList.end())
    {
        aRegionId = *(*myNextRequest)->GetStatusRegion();
        theStream.GetOutputStream() << "Next Region to be processed:       " << aRegionId << endl;
    }
    else
    {
        theStream.GetOutputStream() << "About to change to next channel" << endl;
    }
}

void MON_PilotToneProcessingController::ResetStats()
{
}
