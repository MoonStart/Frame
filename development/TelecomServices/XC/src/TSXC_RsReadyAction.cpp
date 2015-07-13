// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_CardIf.h>
#include <T6100_Dispatcher.h>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>

#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_RsReadyAction.h>
#include <XC/TSXC_RsReadyRegion.h>
#include <XC/TSXC_RsReady.h>

#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_AppIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_RsIf.h>
#include <TsPii/TSPII_Region.h>

//----------------------------------------------------------------------------------------------------------------------
const FC_Milliseconds  TSXC_RsReadyAction::RUN_FREQUENCY = (5 * 1000);    // 5 seconds

//----------------------------------------------------------------------------------------------------------------------
//--- Constructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_RsReadyAction::TSXC_RsReadyAction(T6100_CardIf& theCardContext, TSXC_RsReadyRegion<TSXC_RsReady>* theXCRsReady_Region) :
    myCardContext(theCardContext),
    myBbAction(NULL),
    myPeriodicProcess(NULL),
    myXCRsReady_Region(theXCRsReady_Region)
{
    myBbAction  = new FC_BbAction(this);
    myPeriodicProcess  = new FC_PeriodicProcess(*this, gTimerDispatcher, RUN_FREQUENCY);
    myPeriodicProcess->WakeUp();
}

//----------------------------------------------------------------------------------------------------------------------
//--- Destructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_RsReadyAction::~TSXC_RsReadyAction()
{
    delete myBbAction;
    delete myPeriodicProcess;
}

//----------------------------------------------------------------------------------------------------------------------
FC_Object* TSXC_RsReadyAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    //--- If Cfg and Tspii don't match, check for match.
    if( (*myXCRsReady_Region)[0].GetReadyFlag() == false)
    {
        CompareCfgToTspii();
    }
    //---- Else check if current configuration is different than previous configuration.
    else
    {
        CompareCurrentAndPrevCfg();
    }

    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RsReadyAction::CompareCfgToTspii()
{
    uint32                  aCfgIntfId;
    uint32                  aLowestPort;
    uint32                  aHighestPort;
    uint32                  aTspiiIntfId;
    uint32                  aFirstTspiiIntfId;
    CFG_RsCfgRegion*        aCfgRegion;
    CT_TEL_SignalType       aCfgSigType;
    uint32                  aCfgSfpRouteDevice;
    uint32                  aCfgSfpCrossoverDevice;
    CT_TEL_SignalType       aTspiiSigType;
    uint32                  aTspiiSfpRouteDevice;
    uint32                  aTspiiSfpCrossoverDevice;
    bool                    matchFound;
    TSPII_RsRegion*         aTspiiRsRegion;
    uint32                  aMaxPort;
    
    //--- Set flag to true, and let it be set to false below, if mismatch is found.
    matchFound = true;
    
    //--- The Max Port count will be set based on Card Familiy
    CT_CardType theCardType = myCardContext.GetXCAppIf().GetXCApp().GetAgCfgRegion()->GetMyCardType();
    switch(myCardContext.GetCardFamily().GetCardFamily())
    {
        case CARD_FAM_SSM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_SSM;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        case CARD_FAM_SMTM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_SMTM;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        case CARD_FAM_FGTMM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_FGTMM;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        case CARD_FAM_OTNM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_OTNM;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        case CARD_FAM_SSM40:
            aMaxPort = CT_PORT_SIDE_15 + 1;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_4;
            break;
        case CARD_FAM_FGSM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_FGSM;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        case CARD_FAM_OMM:
            aMaxPort = CT_PORT_SIDE_7 + 1;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_2;
            break;
        case CARD_FAM_HGTMM:
            aMaxPort = CT_PORT_SIDE_12 + 1;
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        case CARD_FAM_OSM:
            switch(theCardType)
            {
               case CARD_TYPE_OSM2S: 
                    aMaxPort = CT_PORT_SIDE_19 + 1;
                    break;
               case CARD_TYPE_OSM2C:
                    aMaxPort = CT_PORT_SIDE_1 + 1;
                    break;
               case CARD_TYPE_OSM1S:
                    aMaxPort = CT_PORT_SIDE_31 + 1;
                    break;
            }
            aFirstTspiiIntfId = TSPII_PORT_SIDE_0;
            break;
        default:
            aMaxPort = 0;
            break;
    }

    //--- For all port-side CFG RS regions, if the region is valid,
    //--- compare the SignalType and SfpRoute to what is in TSPII. 
    
    for(aCfgIntfId = (uint32)CT_PORT_SIDE_0, aTspiiIntfId = (uint32)aFirstTspiiIntfId; 
        (aCfgIntfId < aMaxPort) && (matchFound == true); 
         aCfgIntfId++, aTspiiIntfId++)
    {
        aCfgRegion  = static_cast<CFG_RsCfgRegion*> (myCardContext.GetRsIf().GetCfgPortSideApp((CT_IntfId)aCfgIntfId).GetCfgRegion());
        CFG_Rs& aCfgRsObj    = (*aCfgRegion)[0];

        //--- Only check for match if CFG RS region is valid.
        if (aCfgRegion->IsValid() == true)
        {
            //--- Retrieve CFG RS Info
            aCfgSigType            = aCfgRsObj.GetSignalType();
            aCfgSfpRouteDevice     = CfgToTspii(aCfgRsObj.GetDeviceInSfpRoute());
            aCfgSfpCrossoverDevice = aCfgRsObj.GetCrossoverInSfpRoute();

            //--- Retrieve TSPII RS Info
            aTspiiRsRegion            = TSPII_SubApplication::GetInstance()->GetRs(aTspiiIntfId);
            TSPII_RsIf&  aTspiiRsObj  = (*aTspiiRsRegion)[0];
            aTspiiRsObj.GetSfpRouteAndSignalType(aTspiiSfpRouteDevice, aTspiiSfpCrossoverDevice, aTspiiSigType);

            //--- If CFG RS Info does not match TSPII RS Info, set flag accordingly
            if ( (aCfgSigType != aTspiiSigType) ||
                 (aCfgSfpRouteDevice != aTspiiSfpRouteDevice) ||
                 (aCfgSfpCrossoverDevice != aTspiiSfpCrossoverDevice) )
            {
                matchFound = false;
            }
        }
        else
        {
            matchFound = false;
        }
    }

    //--- Set low/high port based on Card Family
    switch(myCardContext.GetCardFamily().GetCardFamily())
    {
        case CARD_FAM_SSM40:
            aLowestPort  = (uint32) CT_PORT_SIDE_85;
            aHighestPort = (uint32) CT_PORT_SIDE_88;
            break;
        case CARD_FAM_OMM:
            aLowestPort  = (uint32) CT_PORT_SIDE_87;
            aHighestPort = (uint32) CT_PORT_SIDE_88;
            break;
        case CARD_FAM_HGTMM:
        case CARD_FAM_SSM:
        case CARD_FAM_SMTM:
        case CARD_FAM_FGTMM:
        case CARD_FAM_OTNM:
        case CARD_FAM_FGSM:
        case CARD_FAM_OSM:
        default:
            // This second loop is not needed for these cards so
            // intentionally make LowestPort > HighestPort
            aLowestPort  = (uint32) CT_PORT_SIDE_1;
            aHighestPort = (uint32) CT_PORT_SIDE_0;
            break;
    }

    //--- For all port-side CFG RS regions, if the region is valid,
    //--- compare the SignalType and SfpRoute to what is in TSPII. 
    
    for(aCfgIntfId = aHighestPort, aTspiiIntfId = (uint32)TSPII_PORT_SIDE_0; 
        (aCfgIntfId >= aLowestPort) && (matchFound == true); 
         aCfgIntfId--, aTspiiIntfId++)
    {
        aCfgRegion  = static_cast<CFG_RsCfgRegion*> (myCardContext.GetRsIf().GetCfgPortSideApp((CT_IntfId)aCfgIntfId).GetCfgRegion());
        CFG_Rs& aCfgRsObj    = (*aCfgRegion)[0];

        //--- Only check for match if CFG RS region is valid.
        if (aCfgRegion->IsValid() == true)
        {
            //--- Retrieve CFG RS Info
            aCfgSigType            = aCfgRsObj.GetSignalType();
            aCfgSfpRouteDevice     = CfgToTspii(aCfgRsObj.GetDeviceInSfpRoute());
            aCfgSfpCrossoverDevice = aCfgRsObj.GetCrossoverInSfpRoute();

            //--- Retrieve TSPII RS Info
            aTspiiRsRegion            = TSPII_SubApplication::GetInstance()->GetRs(aTspiiIntfId);
            TSPII_RsIf&  aTspiiRsObj  = (*aTspiiRsRegion)[0];
            aTspiiRsObj.GetSfpRouteAndSignalType(aTspiiSfpRouteDevice, aTspiiSfpCrossoverDevice, aTspiiSigType);

            //--- If CFG RS Info does not match TSPII RS Info, set flag accordingly
            if ( (aCfgSigType != aTspiiSigType) ||
                 (aCfgSfpRouteDevice != aTspiiSfpRouteDevice) ||
                 (aCfgSfpCrossoverDevice != aTspiiSfpCrossoverDevice) )
            {
                matchFound = false;
            }
        }
        else
        {
            matchFound = false;
        }
    }

    //--- If all CFG RS configuration matches TSPII RS configuration, 
    //--- update TSXC_ReadyRegion and suspend this process since it is no longer needed.
	
    if (matchFound == true)
    {
        (*myXCRsReady_Region)[0].SetReadyFlag(true);
        myXCRsReady_Region->IncModificationCounter();
        myXCRsReady_Region->UpdateNotify();

        myPeriodicProcess->Suspend();
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RsReadyAction::CompareCurrentAndPrevCfg()
{
    uint32                  aCfgIntfId;
    CFG_RsCfgRegion*        aCfgRegion;
    CT_TEL_SignalType       aCfgSigType;
    bool                    aCfgChanged;
    uint32                  aMaxPort;
    uint32                  aLowestPort;
    uint32                  aHighestPort;

    //--- No cfg change has been found, yet.
    aCfgChanged = false;
    CT_CardType theCardType = myCardContext.GetXCAppIf().GetXCApp().GetAgCfgRegion()->GetMyCardType();
    switch(myCardContext.GetCardFamily().GetCardFamily())
    {
        case CARD_FAM_SSM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_SSM;
            break;
        case CARD_FAM_SMTM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_SMTM;
            break;
        case CARD_FAM_FGTMM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_FGTMM;
            break;
        case CARD_FAM_OTNM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_OTNM;
            break;
        case CARD_FAM_SSM40:
            aMaxPort = (uint32)CT_PORT_SIDE_15 + 1;
            break;
        case CARD_FAM_FGSM:
            aMaxPort = NUMBER_OF_PORT_FAC_ON_FGSM;
            break;
        case CARD_FAM_OMM:
            aMaxPort = (uint32)CT_PORT_SIDE_7 + 1;			            
            break;
        case CARD_FAM_HGTMM:
            aMaxPort = (uint32)CT_PORT_SIDE_12 + 1;
            break;
        case CARD_FAM_OSM:
           switch(theCardType)
           {
               case CARD_TYPE_OSM2S: 
                    aMaxPort = CT_PORT_SIDE_19 + 1;
                    break;
               case CARD_TYPE_OSM2C:
                    aMaxPort = CT_PORT_SIDE_1 + 1;
                    break;
               case CARD_TYPE_OSM1S:
                    aMaxPort = CT_PORT_SIDE_31 + 1;
                    break;
            }
            break;
        default:
            aMaxPort = 0;
            break;
    }

    //--- For all valid port-side CFG RS regions, check if SignalType has changed.
    for(aCfgIntfId = (uint32)CT_PORT_SIDE_0; (aCfgIntfId < aMaxPort) && (aCfgChanged == false); aCfgIntfId++)
    {
        aCfgRegion  = static_cast<CFG_RsCfgRegion*> (myCardContext.GetRsIf().GetCfgPortSideApp((CT_IntfId)aCfgIntfId).GetCfgRegion());
        CFG_Rs& aCfgRsObj    = (*aCfgRegion)[0];

        //--- Only check for match if CFG RS region is valid.
        if (aCfgRegion->IsValid() == true)
        {
            //--- Retrieve CFG RS Info
            aCfgSigType = aCfgRsObj.GetSignalType();

            //--- If CFG RS has changed, set flag accordingly
            if (aCfgSigType != (*myXCRsReady_Region)[0].GetSignalType((CT_IntfId)aCfgIntfId - CT_PORT_SIDE_0)) 
            {
                aCfgChanged = true;
            }

            //--- Store latest CFG RS Info in TSXC_ReadyRegion
            (*myXCRsReady_Region)[0].SetSignalType(((CT_IntfId)aCfgIntfId - CT_PORT_SIDE_0), aCfgSigType);
        }
    }

    //--- Set low/high port based on Card Familiy
    switch(myCardContext.GetCardFamily().GetCardFamily())
    {
        case CARD_FAM_SSM40:
            aLowestPort  = (uint32) CT_PORT_SIDE_85;
            aHighestPort = (uint32) CT_PORT_SIDE_88;
            break;
        case CARD_FAM_OMM:
            aLowestPort  = (uint32) CT_PORT_SIDE_87;
            aHighestPort = (uint32) CT_PORT_SIDE_88;
            break;
        case CARD_FAM_HGTMM:
        case CARD_FAM_SSM:
        case CARD_FAM_SMTM:
        case CARD_FAM_FGTMM:
        case CARD_FAM_OTNM:
        case CARD_FAM_FGSM:
        case CARD_FAM_OSM:
        default:
            // This second loop is not needed for these cards so
            // intentionally make LowestPort > HighestPort
            aLowestPort  = (uint32) CT_PORT_SIDE_1;
            aHighestPort = (uint32) CT_PORT_SIDE_0;
            break;
    }

    //--- For all valid port-side CFG RS regions, check if SignalType has changed.
    for(aCfgIntfId = aLowestPort; (aCfgIntfId <= aHighestPort) && (aCfgChanged == false); aCfgIntfId++)
    {
        aCfgRegion  = static_cast<CFG_RsCfgRegion*> (myCardContext.GetRsIf().GetCfgPortSideApp((CT_IntfId)aCfgIntfId).GetCfgRegion());
        CFG_Rs& aCfgRsObj    = (*aCfgRegion)[0];

        //--- Only check for match if CFG RS region is valid.
        if (aCfgRegion->IsValid() == true)
        {
            //--- Retrieve CFG RS Info
            aCfgSigType = aCfgRsObj.GetSignalType();

            //--- If CFG RS has changed, set flag accordingly
            if (aCfgSigType != (*myXCRsReady_Region)[0].GetSignalType((CT_IntfId)aCfgIntfId - CT_PORT_SIDE_0)) 
            {
                aCfgChanged = true;
            }

            //--- Store latest CFG RS Info in TSXC_ReadyRegion
            (*myXCRsReady_Region)[0].SetSignalType(((CT_IntfId)aCfgIntfId - CT_PORT_SIDE_0), aCfgSigType);
        }
    }

    //--- If configuration has changed, update TSXC_ReadyRegion
    if (aCfgChanged == true)
    {
        myXCRsReady_Region->IncModificationCounter();
        myXCRsReady_Region->UpdateNotify();
    }
}

//----------------------------------------------------------------------------------------------------------------------
uint32 TSXC_RsReadyAction::CfgToTspii(uint32 theCfgDev)
{
    uint32     aTspiiDev;

    aTspiiDev = theCfgDev;

    // Target tspii code converts CT_TEL_SSM40_*MUX* facilities, so perform same conversion here
#ifdef __TARGET__
    switch(theCfgDev)
    {
        case CT_TEL_SSM40_DEV1_OTU2MUX_0: aTspiiDev = CT_TEL_SSM40_DEV1_OTU2_0; break;
        case CT_TEL_SSM40_DEV2_OTU2MUX_0: aTspiiDev = CT_TEL_SSM40_DEV2_OTU2_0; break;
        case CT_TEL_SSM40_DEV1_OTU2MUX_1: aTspiiDev = CT_TEL_SSM40_DEV1_OTU2_1; break;
        case CT_TEL_SSM40_DEV2_OTU2MUX_1: aTspiiDev = CT_TEL_SSM40_DEV2_OTU2_1; break;
    }
#endif

    return aTspiiDev;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RsReadyAction::AddInputRegion( FC_BbRegion* theInputRegion )
{
    GetBbAction()->AddInputRegion( theInputRegion );
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RsReadyAction::RemoveInputRegion( FC_BbRegion* theInputRegion )
{
    GetBbAction()->RemoveInputRegion( theInputRegion );
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RsReadyAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
//----------------------------------------------------------------------------------------------------------------------
