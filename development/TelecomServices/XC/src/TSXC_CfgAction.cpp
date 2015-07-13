// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <XC/TSXC_CfgAction.h>
#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_ConfigRegion.h>
#include <XC/TSXC_SourceActiveStatusRegion.h>
#include <XC/TSXC_SourceActiveStatus.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_Connect.h>
#include <XC/TSXC_PortDataAllocRegion.h>

#include <TsPii/TSPII_XcIf.h>
#include <TsPii/TSPII_HopIf.h>
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_SubApplication.h>
#include <SignalProtection/SP_ApplicationStatus.h>
               
bool TSXC_CfgAction::myDisplayConnDelete = false;
bool TSXC_CfgAction::myDisplayConnAdd = false;

//------------------------------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------------------------------
TSXC_CfgAction::TSXC_CfgAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myXCAgentConfig_Region(NULL),
    myXCSigProtectConfig_Region(NULL),
    mySPSourceActive_Region(NULL),
    mySPReady_Regions(NULL),
    myRollStatus_Region(NULL),
    myPortDataAlloc_Region(NULL)
{
}

//------------------------------------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------------------------------------
TSXC_CfgAction::~TSXC_CfgAction()
{

}

//------------------------------------------------------------------------------------------------------------
// Get Methods
//

//------------------------------------------------------------------------------------------------------------
// Set Methods
//
void TSXC_CfgAction::SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion)
{
    myXCAgentConfig_Region = theAGCfgRegion;
}

void TSXC_CfgAction::SetSPCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theSPCfgRegion)
{
    myXCSigProtectConfig_Region = theSPCfgRegion;
}

void TSXC_CfgAction::SetSPSrcActRegion(TSXC_SourceActiveStatusRegion<TSXC_SourceActiveStatus>* theSPSrcActRegion)
{
    mySPSourceActive_Region = theSPSrcActRegion;
}

void TSXC_CfgAction::SetDisplayConnDelete(bool theValue)
{
    myDisplayConnDelete = theValue;
}

void TSXC_CfgAction::SetDisplayConnAdd(bool theValue)
{
    myDisplayConnAdd = theValue;
}

void TSXC_CfgAction::SetSPReady_Regions(vector<TEL_BbRegionBaseImp<SP_ApplicationStatus>*> * theSPReady_Regions)
{
    mySPReady_Regions = theSPReady_Regions;
}

void TSXC_CfgAction::SetRollStatus_Region(TEL_BbRegionBaseImp <TSXC_RollStatus> * theRollStatus_Region)
{
    myRollStatus_Region = theRollStatus_Region;
}

void TSXC_CfgAction::SetPortDataAllocRegion(TSXC_PortDataAllocRegion<TSXC_PortDataAlloc>* thePortDataAllocRegion)
{
    myPortDataAlloc_Region = thePortDataAllocRegion;
}

//------------------------------------------------------------------------------------------------------------
// Do the work
//
FC_Object* TSXC_CfgAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    TSXC_Connect*               AG_CfgObjectPtr;
    TSXC_Connect*               SP_CfgObjectPtr;
    TSXC_SourceActiveStatus*    SP_ActObjectPtr;
    uint32                      regionIndex;
    uint32                      MaxRegionIndex;
    int                         facOffset;
    UINT32                       srcFac;
    UINT32                       srcFacEndpt;
    UINT32                       dstFac;
    UINT32                       dstFacEndpt;
    CT_XC_ConnectType           connType;
    XC_ConnAction               connAction;
    CT_XC_ConnectState          AG_ConnState;
    CT_XC_ConnectState          SP_ConnState;
    bool                        SPReady;
    bool                        ValidCardProvisioned;
    TSPII_XcRegion*             tspiiXcRegion;
    char                        ErrorMsg[100];
    TSPII_XcRecord              tspiiConn;
    CT_CardType                 aCardType;
    const int*                  aConfigMapPtr = NULL;

    // Log the starting of the action
    FC_EventRecord(EVENT_XC_CFG_ACTION_START, NULL);

    // Get and store card type
    aCardType = myXCAgentConfig_Region->GetMyCardType();
    
    //
    // Check if Signal Protect is ready.  If not, XC Config Action
    // cannot run since source activation information and signal protect
    // configuration information is not yet available.
    //
    SPReady = true;
    if (NULL != mySPReady_Regions)
    {
        for (int i = 0; i < int((*mySPReady_Regions).size()); i++)
        {
            if (!((*(*mySPReady_Regions)[i])[0].IsReady()))
                SPReady = false;
        }
    }

    //
    // Get handle to TSPII CrossConnect Region based on card type.
    //
    if (aCardType == CARD_TYPE_SMTMM  ||
        aCardType == CARD_TYPE_SMTMA  ||
        aCardType == CARD_TYPE_SMTMU  ||
        aCardType == CARD_TYPE_SMTMUD ||
        aCardType == CARD_TYPE_SMTMSD ||
        aCardType == CARD_TYPE_SSMX   ||
        aCardType == CARD_TYPE_SSMD   ||
        aCardType == CARD_TYPE_FGTMM  ||
        aCardType == CARD_TYPE_OTNMX  ||
        aCardType == CARD_TYPE_OTNMD  ||
        aCardType == CARD_TYPE_SPFAB  ||
        aCardType == CARD_TYPE_OSM40  ||
        aCardType == CARD_TYPE_SSM40  ||
        aCardType == CARD_TYPE_OSM20  ||
        aCardType == CARD_TYPE_FGSM   ||
        aCardType == CARD_TYPE_HDTG   ||
        aCardType == CARD_TYPE_HDTG2  ||
        aCardType == CARD_TYPE_OMMX   ||
        aCardType == CARD_TYPE_HGTMM  ||
        aCardType == CARD_TYPE_OSM2S  ||
        aCardType == CARD_TYPE_OSM2C  ||
        aCardType == CARD_TYPE_OSM1S  ||
        aCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS
    {
        tspiiXcRegion       = TSPII_SubApplication::GetInstance()->GetXc();
        ValidCardProvisioned = true;
    }
    else if((aCardType == CARD_TYPE_RCMM)     ||
            (aCardType == CARD_TYPE_CCMIR)    ||
            (aCardType == CARD_TYPE_CCMER)    ||
            (aCardType == CARD_TYPE_CCMLR)    ||
            (aCardType == CARD_TYPE_CCM88IR)  ||
            (aCardType == CARD_TYPE_CCM88LR)  ||
            (aCardType == CARD_TYPE_CCM88ER)  ||
            (aCardType == CARD_TYPE_OADM88IR) ||
            (aCardType == CARD_TYPE_OADM88LR) ||
            (aCardType == CARD_TYPE_OADM88ER) ||
            (aCardType == CARD_TYPE_OTSM) ||
            (aCardType == CARD_TYPE_OADM88IR8D) ||
            (aCardType == CARD_TYPE_OADM88LR8D) ||
            (aCardType == CARD_TYPE_OADM88ER8D) ||
            (aCardType == CARD_TYPE_OADM8DSIR)  ||
            (aCardType == CARD_TYPE_OADM8DSLR)  ||
            (aCardType == CARD_TYPE_OADM8DSER)  ||
            (aCardType == CARD_TYPE_DXOADM))
    {
        //
        // Since there are multiple XC regions on the APM give the slot
        //
        tspiiXcRegion = TSPII_SubApplication::GetInstance()->GetXc(TSPII_DONT_CARE, myCardContext.GetCardId());
        ValidCardProvisioned = true;
    }
    else
    {
        ValidCardProvisioned = false;

        //
        // Only generate error message if Config Region contains objects.  If no objects
        // exist in Config Region, this action is running for a non-provisioned card
        // which is okay and does not warrant an error message.
        //
        if ((*myXCAgentConfig_Region).Size() > 0)
        {
            sprintf(ErrorMsg, "TSXC_CfgAction(shelf %d, slot %d) : Unsupported card type of %d",
                myCardContext.GetShelfId(),
                myCardContext.GetCardId(),
                aCardType);
            FC_THROW_ERROR(FC_RuntimeError, ErrorMsg);
        }
    }
    
    //
    // Iterate through regions only if Signal Protect is ready and card is provisioned
    // and connections have changed.
    //
    if ( (SPReady               == true) && 
         (ValidCardProvisioned  == true) )
    {
        // set start time  if debug level was set.
        START_TIME(TSXC_DEBUG_LEVEL01);

        //
        // On the RCMM/CCM, TSXC_ConfigRegion only contains information for 
        // connected outputs.  So, individual delete requests are never issued.
        //
        if ( (aCardType == CARD_TYPE_RCMM)     ||
             (aCardType == CARD_TYPE_CCMIR)    ||
             (aCardType == CARD_TYPE_CCMER)    ||
             (aCardType == CARD_TYPE_CCMLR)    ||
             (aCardType == CARD_TYPE_CCM88IR)  ||
             (aCardType == CARD_TYPE_CCM88LR)  ||
             (aCardType == CARD_TYPE_CCM88ER)  ||
             (aCardType == CARD_TYPE_OADM88IR) ||
             (aCardType == CARD_TYPE_OADM88LR) ||
             (aCardType == CARD_TYPE_OADM88ER) ||
             (aCardType == CARD_TYPE_OTSM)     ||
             (aCardType == CARD_TYPE_HDTG)     ||
             (aCardType == CARD_TYPE_HDTG2)    ||
             (aCardType == CARD_TYPE_OADM88IR8D) ||
             (aCardType == CARD_TYPE_OADM88LR8D) ||
             (aCardType == CARD_TYPE_OADM88ER8D) ||
             (aCardType == CARD_TYPE_OADM8DSIR)  ||
             (aCardType == CARD_TYPE_OADM8DSLR)  ||
             (aCardType == CARD_TYPE_OADM8DSER)  ||
             (aCardType == CARD_TYPE_DXOADM))
        {
            (*tspiiXcRegion)[0].DeleteAllXconns();
        }

        //
        // Due to the large number of connections on the SPFAB, invoke
        // DeleteAllXconns() once rather than many invocations of DeleteXconn().
        // 
        if (aCardType == CARD_TYPE_SPFAB)
        {
            (*tspiiXcRegion)[0].DeleteAllXconns();
        }

        //
        // Only go through the size of the region. This can change depending on
        // the card type.
        //
        MaxRegionIndex = (*myXCAgentConfig_Region).Size();

        //
        // Point to config map region based on card type.
        //
        if (aCardType == CARD_TYPE_SMTMU)
        {
            aConfigMapPtr = SMTMUConfigMap;
        }
        else if (aCardType == CARD_TYPE_SPFAB)
        {
            aConfigMapPtr = SPFABConfigMap;
        }
        else if ((aCardType == CARD_TYPE_SSMX) || (aCardType == CARD_TYPE_SSMD))
        {
            aConfigMapPtr = SSMConfigMap;
        }
        else if (aCardType == CARD_TYPE_FGTMM)
        {
            aConfigMapPtr = FGTMMConfigMap;
        }
        else if ((aCardType == CARD_TYPE_OTNMX) || (aCardType == CARD_TYPE_OTNMD))
        {
            aConfigMapPtr = OTNMConfigMap;
        }
        else if ( (aCardType == CARD_TYPE_OSM40) || (aCardType == CARD_TYPE_SSM40) )
        {
            aConfigMapPtr = SSM40ConfigMap;
        }
        else if ( aCardType == CARD_TYPE_OSM20 )
        {
            aConfigMapPtr = OSM20ConfigMap;
        }
        else if ( aCardType == CARD_TYPE_FGSM )
        {
            aConfigMapPtr = FGSMConfigMap;
        }
        else if (aCardType == CARD_TYPE_HDTG)
        {
            aConfigMapPtr = HDTGConfigMap;
        }
        else if (aCardType == CARD_TYPE_HDTG2)
        {
            aConfigMapPtr = HDTG2ConfigMap;
        }
        else if ( aCardType == CARD_TYPE_OMMX )
        {
            aConfigMapPtr = OMMXConfigMap;
        }
        else if (aCardType == CARD_TYPE_HGTMM || aCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS
        {
            aConfigMapPtr = HGTMMConfigMap;
        }
        else if ( aCardType == CARD_TYPE_OSM2S || aCardType == CARD_TYPE_OSM2C )
        {
            aConfigMapPtr = OSMOduXcConfigMap;
        }
        else if ( aCardType == CARD_TYPE_OSM1S )
        {
            aConfigMapPtr = OSM1SOduXcConfigMap;
        }

        for(regionIndex = 0; regionIndex < MaxRegionIndex; regionIndex++)
        {
            //
            // Initialize variables for the object corresponding to this
            // regionIndex in all regions, if they exist.  
            //
            // Note: Agent Config region always exists, Signal Protect 
            // regions may or may not exist.
            // 
            AG_CfgObjectPtr = &((*myXCAgentConfig_Region)[(bbindex_t)regionIndex]);
            SP_CfgObjectPtr = NULL;

            AG_ConnState    = AG_CfgObjectPtr->GetState();
            SP_ConnState    = CT_XC_STATE_NOTCONNECTED;

            connAction      = XC_NOACTION;
            //connActDeact    = AG_CfgObjectPtr->GetActDeact();

            srcFac = 0;
            dstFac = 0;

            if (myXCSigProtectConfig_Region != NULL)
            {
                if (regionIndex < myXCSigProtectConfig_Region->Size())
                {
                    SP_CfgObjectPtr = &((*myXCSigProtectConfig_Region)[(bbindex_t)regionIndex]);
                    SP_ConnState    = SP_CfgObjectPtr->GetState();
                }
            }

            // *********************************************************
            // The logic to determine action to take is as follows:
            //
            // Rule     Agent Cfg Object    SP Cfg Object      Action
            // ----     ----------------    -------------      ------
            // R1       NOT_CONNECTED       NOT_CONNECTED      Disconnect
            // R2       NOT_CONNECTED       CONNECTED          Connect
            // R3       CONNECTED           NOT_CONNECTED      Connect
            // R4       CONNECTED           CONNECTED          Invalid
            // *********************************************************

            //
            // An object in Agent Cfg and its corresponding object in SP Cfg cannot
            // both be set to CONNECT since Agent and SP contain non-intersecting
            // sets of connections.  Covers rule R4.
            //
            if ( (AG_ConnState == CT_XC_STATE_CONNECTED) &&
                 (SP_ConnState == CT_XC_STATE_CONNECTED) ) 
            {
                FC_THROW_ERROR(FC_RuntimeError,"TSXC_CfgAction::Invalid State");
            }

            //
            // If a connection exists in Agent Cfg, this is a connection 
            // request from Agent.  Covers rule R3.
            //
            else if ( AG_ConnState == CT_XC_STATE_CONNECTED )
            {
                //
                // Set up variables for tspii invocation.
                //
                srcFac      = AG_CfgObjectPtr->GetInputFacility();
                srcFacEndpt = AG_CfgObjectPtr->GetInputFacilityEndpoint();
                dstFac      = AG_CfgObjectPtr->GetOutputFacility();
                dstFacEndpt = AG_CfgObjectPtr->GetOutputFacilityEndpoint();
                connType    = AG_CfgObjectPtr->GetType();
                connAction  = XC_CONNECT;

                //
                // If this is a flexible connection, retrieve active source status
                // information from SP Source Active Region.
                //
                if ( (AG_CfgObjectPtr->GetMapping() == CT_XC_MAPPING_FLEXIBLE) &&
                     (mySPSourceActive_Region != NULL) &&
                     (aConfigMapPtr != NULL) )
                {
                    facOffset = *(aConfigMapPtr + srcFac);

                    SP_ActObjectPtr = &((*mySPSourceActive_Region)[facOffset + srcFacEndpt - 1]);

                    // Re-assign source value based on the active source.
                    srcFac      = SP_ActObjectPtr->GetActiveFacility();
                    srcFacEndpt = SP_ActObjectPtr->GetActiveFacilityEndpoint();

                    // If source information is invalid, leave this destination alone.
                    if ( (srcFac      == XC_INVALID_FAC) && 
                         (srcFacEndpt == XC_INVALID_FAC_ENDPT) )
                    {
                        connAction = XC_NOACTION;
                    }
                }
            }
      
            //
            // If a connection exists in SP Cfg, this is a connection request 
            // from Signal Protect.  Covers rule R2.
            //
            else if ( SP_ConnState == CT_XC_STATE_CONNECTED )
            {
                //
                // Set up variables for tspii invocation.
                //
                srcFac      = SP_CfgObjectPtr->GetInputFacility();
                srcFacEndpt = SP_CfgObjectPtr->GetInputFacilityEndpoint();
                dstFac      = SP_CfgObjectPtr->GetOutputFacility();
                dstFacEndpt = SP_CfgObjectPtr->GetOutputFacilityEndpoint();
                connType    = SP_CfgObjectPtr->GetType();
                connAction  = XC_CONNECT;

                //
                // SP will never contain flexible connections
                //
            }

            //
            // If a connection does not exist in both the Agent Cfg and SP Cfg object,
            // this is a disconnect request.  Covers rule R1.
            //
            else if ( (AG_ConnState == CT_XC_STATE_NOTCONNECTED) &&
                      (SP_ConnState == CT_XC_STATE_NOTCONNECTED) )
            {
                //
                // Set up variables for tspii invocation.
                //
                dstFac      = AG_CfgObjectPtr->GetOutputFacility();
                dstFacEndpt = AG_CfgObjectPtr->GetOutputFacilityEndpoint();
                connType    = AG_CfgObjectPtr->GetType();
                connAction  = XC_DISCONNECT;
            }

            // If necessary, apply this connection to TSPII.
            if (connAction == XC_CONNECT)
            {
                // Populate connection information
                tspiiConn.Type     = ConnectTypeToTspii(connType, dstFac, srcFac);
                tspiiConn.InPort   = (*tspiiXcRegion)[0].TsPortToTspiiPort(srcFac);
                tspiiConn.InTslot  = srcFacEndpt - 1;
                tspiiConn.OutPort  = (*tspiiXcRegion)[0].TsPortToTspiiPort(dstFac);
                tspiiConn.OutTslot = dstFacEndpt - 1;

                (*tspiiXcRegion)[0].AddXconn(tspiiConn);

                if (myDisplayConnAdd == true)
                {
                    fc_cout << "TSXC_CfgAction::Invoking tspii\n" \
                            << "AddXconn(srcFac      = " << tspiiConn.InPort << "\n" \
                            << "         srcFacEndpt = " << tspiiConn.InTslot << "\n" \
                            << "         dstFac      = " << tspiiConn.OutPort << "\n" \
                            << "         dstFacEndpt = " << tspiiConn.OutTslot << "\n" \
                            << "         connType    = " << TSPII_XC_TYPE_DISPLAY(tspiiConn.Type) << ")\n" << endl;
                }
            }

            // If necessary, delete this connection from TSPII.
            // Don't invoke DeleteXconn() for SPFAB since DeleteAllXconns() has already been called.
            else if ( (connAction == XC_DISCONNECT) && (aCardType != CARD_TYPE_SPFAB) )
            {
                // Populate connection information
                tspiiConn.Type     = ConnectTypeToTspii(connType, dstFac);
                tspiiConn.OutPort  = (*tspiiXcRegion)[0].TsPortToTspiiPort(dstFac);
                tspiiConn.OutTslot = dstFacEndpt - 1;

                // Invoke TSPII to delete this connection
                (*tspiiXcRegion)[0].DeleteXconn(tspiiConn);

                if (myDisplayConnDelete == true)
                {
                    fc_cout << "TSXC_CfgAction::Invoking tspii\n" \
                            << "DeleteXconn(dstFac      = " << tspiiConn.OutPort << "\n" \
                            << "            dstFacEndpt = " << tspiiConn.OutTslot << "\n" \
                            << "            connType    = " << TSPII_XC_TYPE_DISPLAY(tspiiConn.Type) << ")\n" << endl;

                }
            }
        } // for regionIndex


        // set end time if debug level was set.
        END_TIME(TSXC_DEBUG_LEVEL01);
        // print debug info if debug level was set
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: TSXC_to_TSPII Add Connect time : ");
        
        //
        // Commit all AddXconn/DeleteXConn invocations.
        //
        START_TIME(TSXC_DEBUG_LEVEL01);
        (*tspiiXcRegion)[0].CommitXconns();
        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: TSPII_XC Commit time : ");

        //
        // For SMTMU, port-side allocation information must be queried and stored.
        //
        if ( (aCardType == CARD_TYPE_SMTMU) && (myPortDataAlloc_Region != NULL) )
        {
            // Query PointC allocation information from TSPII, and store allocation information in TSXC region.
            CT_FAC_StsMap  aIngressMap = (*tspiiXcRegion)[0].GetPointCIngressAlloc();
            CT_FAC_StsMap  aEgressMap = (*tspiiXcRegion)[0].GetPointCEgressAlloc();
            myPortDataAlloc_Region->SetIngressBwUsage(&aIngressMap);
            myPortDataAlloc_Region->SetEgressBwUsage(&aEgressMap);

            // Transfer region to controller.
            myPortDataAlloc_Region->IncModificationCounter();
            myPortDataAlloc_Region->UpdateNotify();
        }

    } // if SP Ready && ValidCardProvisioned

    // Log the end of the action
    FC_EventRecord(EVENT_XC_CFG_ACTION_END, NULL);

    Respond(myXCAgentConfig_Region->GetCQMRequest());

    return NULL;
}

//------------------------------------------------------------------------------------------------------------
// Connections to TSPII are configured at a channel to reduce the 
// complexity of the XC Config Action.
//
// Non-transparent STS connections may occupy several channels.
// The Connection Type of the first channel is set to CT_XC_TYPE_STSx, 
// while the Connection Type of the remaining channels is set to 
// CT_XC_TYPE_CONCATANATED.  For all these channels, the type 
// sent to TSPII is TSPII_XC_TYPE_STS1.
//
// Transparent connections will occupy several channels. 
// The Connection Type of the first channel is set to CT_XC_TYPE_STSxT 
// or CT_XC_TYPE_OCxM, while the Connection Type for the remaining 
// channels is set to CT_XC_TYPE_CONCATANATED.  For the first channel,
// the type sent to TSPII is TSPII_XC_TYPE_STSxT or CT_XC_TYPE_OCxM.
// For the remaining channels, the type sent to TSPII is 
// TSPII_XC_TYPE_STS1.
//------------------------------------------------------------------------------------------------------------
TSPII_XcType TSXC_CfgAction::ConnectTypeToTspii(CT_XC_ConnectType connType, uint8 srcFac, uint8 dstFac)
{
    TSPII_XcType    retVal;
    CT_CardType     aCardType;

    switch(connType)
    {
        case CT_XC_TYPE_UNSPECIFIED:    retVal = TSPII_XC_TYPE_UNKNOWN; break;
        case CT_XC_TYPE_LAMBDA:         retVal = TSPII_XC_TYPE_LAMBDA;  break;
        case CT_XC_TYPE_STS1: 
        case CT_XC_TYPE_STS48C: 
        case CT_XC_TYPE_STS192C: 
        case CT_XC_TYPE_STS1C22V: 
        case CT_XC_TYPE_STS1D: 
        case CT_XC_TYPE_CONCATANATED:   
                                        retVal = TSPII_XC_TYPE_STS1;   break;
        case CT_XC_TYPE_STS3CD:         retVal = TSPII_XC_TYPE_STS3C;  break;
        case CT_XC_TYPE_STS3T:          retVal = TSPII_XC_TYPE_STS3T;  break;
        case CT_XC_TYPE_STS12T:         retVal = TSPII_XC_TYPE_STS12T; break;
        case CT_XC_TYPE_STS48T:         retVal = TSPII_XC_TYPE_STS48T; break;
        case CT_XC_TYPE_OC3M:           retVal = TSPII_XC_TYPE_OC3M;   break;
        case CT_XC_TYPE_OC12M:          retVal = TSPII_XC_TYPE_OC12M;  break;
        case CT_XC_TYPE_OC48M:          retVal = TSPII_XC_TYPE_OC48M;  break;
        case CT_XC_TYPE_OCHM:           retVal = TSPII_XC_TYPE_OCHM;   break;
        case CT_XC_TYPE_OPTD1M:         retVal = TSPII_XC_TYPE_OPTD1M; break;
        case CT_XC_TYPE_OPTD3M:         retVal = TSPII_XC_TYPE_OPTD3M; break;
        case CT_XC_TYPE_OC192M:         retVal = TSPII_XC_TYPE_OC192M; break;
        case CT_XC_TYPE_ODU0:           retVal = TSPII_XC_TYPE_ODU0;   break;
        case CT_XC_TYPE_ODU1:           retVal = TSPII_XC_TYPE_ODU1;   break;
        case CT_XC_TYPE_ODU2:           retVal = TSPII_XC_TYPE_ODU2;   break;
        case CT_XC_TYPE_ODU2E:          retVal = TSPII_XC_TYPE_ODU2E;  break;
        case CT_XC_TYPE_ODU3:           retVal = TSPII_XC_TYPE_ODU3;   break;
        case CT_XC_TYPE_ODU4:           retVal = TSPII_XC_TYPE_ODU4;   break;
        case CT_XC_TYPE_ODUF:           retVal = TSPII_XC_TYPE_ODUF;   break;
        case CT_XC_TYPE_STS3C: 
        case CT_XC_TYPE_STS12C: 
            // On SSMs, a 3C/12C connection where the src or dst is a TTP facility
            // needs to be treated as a TSPII STS3C/STS12C XC.  All other 3C/12C 
            // connections continue to be treated as TSPII STS1 XC.
            retVal = TSPII_XC_TYPE_STS1;
            
            aCardType = myXCAgentConfig_Region->GetMyCardType();
            if ( (aCardType == CARD_TYPE_SSMX) || (aCardType == CARD_TYPE_SSMD) )
            {
                if ( (srcFac == XC_SSM_TTP_FACILITY_ID) || (dstFac == XC_SSM_TTP_FACILITY_ID) )
                {
                    retVal = TSPII_XC_TYPE_STS3C;
                    if (connType == CT_XC_TYPE_STS12C)
                    {
                        retVal = TSPII_XC_TYPE_STS12C;
                    }
                }
            }
            break;

        default:                        retVal =  TSPII_XC_TYPE_UNKNOWN;  break;
    }

    return retVal;
}
