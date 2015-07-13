/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     January, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_SourceConnectStatus  Implementation
--------------------------------------------------------------------------*/
#include <XC/TSXC_SourceConnectStatus.h>
#include <XC/TSXC_BaseApplication.h>
//----------------------------------------------------------------------------------------------------------------------
//--- Constructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_SourceConnectStatus::TSXC_SourceConnectStatus(T6100_TelecomIf& theContext):myContext(theContext)
{
    Reset();
}

//----------------------------------------------------------------------------------------------------------------------
//--- Destructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_SourceConnectStatus::~TSXC_SourceConnectStatus()
{
}

//----------------------------------------------------------------------------------------------------------------------
//  The "theChannel" perameter is assumes as zero based 
//  Since this method have to be as fast as possible therefore no range checks are done. 
//  If the inputs parameters are wrong the result will not be correct.  
//----------------------------------------------------------------------------------------------------------------------
bool TSXC_SourceConnectStatus::IsSrcConnectedInternally(CT_IntfId thePort, CT_ChannelId theChannel)
{
    uint8 aConnectCount = 0;
    if (CT_PORT_SIDE_32 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[2].Channels[theChannel];
    }
    else if (CT_LINE_SIDE_0 == thePort)
    {
       aConnectCount =  myPortInfo.Ports_192[1].Channels[theChannel];
    }
    else if (CT_PORT_SIDE_12 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[0].Channels[theChannel];
    }
    else if (CT_PORT_SIDE_11 >= thePort && CT_PORT_SIDE_0 <= thePort && theChannel < XC_MAX_XC_SSM_PORT)
    {
        uint8 anIndex = (uint8) thePort;
        aConnectCount =  myPortInfo.Ports_48[anIndex].Channels[theChannel];
    }     
    return aConnectCount != 0;
}

//----------------------------------------------------------------------------------------------------------------------
int TSXC_SourceConnectStatus::GetConnectionCount(CT_IntfId thePort, CT_ChannelId theChannel)
{
    uint8 aConnectCount = 0;
    if (CT_PORT_SIDE_32 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[2].Channels[theChannel] +
                         myPortInfo.Ports_192[2].ChannelsToImux[theChannel];
    }    
    else if (CT_LINE_SIDE_0 == thePort)
    {
       aConnectCount =  myPortInfo.Ports_192[1].Channels[theChannel] +
                        myPortInfo.Ports_192[1].ChannelsToImux[theChannel];
    }
    else if (CT_PORT_SIDE_12 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[0].Channels[theChannel] +
                         myPortInfo.Ports_192[0].ChannelsToImux[theChannel];;
    }
    else if (CT_PORT_SIDE_11 >= thePort && CT_PORT_SIDE_0 <= thePort && theChannel < XC_MAX_XC_SSM_PORT)
    {
        uint8 anIndex = (uint8) thePort;
        aConnectCount =  myPortInfo.Ports_48[anIndex].Channels[theChannel] +
                         myPortInfo.Ports_48[anIndex].ChannelsToImux[theChannel];
    }     
    return (int) aConnectCount;
}

//----------------------------------------------------------------------------------------------------------------------
bool TSXC_SourceConnectStatus::IsSrcConnectedToImux(CT_IntfId thePort, CT_ChannelId theChannel)
{
    uint8 aConnectCount = 0;
    if (CT_PORT_SIDE_32 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[2].ChannelsToImux[theChannel];
    }
    else if (CT_LINE_SIDE_0 == thePort)
    {
       aConnectCount =  myPortInfo.Ports_192[1].ChannelsToImux[theChannel];
    }
    else if (CT_PORT_SIDE_12 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[0].ChannelsToImux[theChannel];
    }
    else if (CT_PORT_SIDE_11 >= thePort && CT_PORT_SIDE_0 <= thePort && theChannel < XC_MAX_XC_SSM_PORT)
    {
        uint8 anIndex = (uint8) thePort;
        aConnectCount =  myPortInfo.Ports_48[anIndex].ChannelsToImux[theChannel];
    }     
    return aConnectCount != 0;
}

//----------------------------------------------------------------------------------------------------------------------
bool TSXC_SourceConnectStatus::IsSrcConnectedToImuxAlwaysEnabled(CT_IntfId thePort, CT_ChannelId theChannel)
{
    uint8 aConnectCount = 0;
    if (CT_PORT_SIDE_32 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[2].ChannelsToImuxAlwaysEnabled[theChannel];
    }
    else if (CT_LINE_SIDE_0 == thePort)
    {
       aConnectCount =  myPortInfo.Ports_192[1].ChannelsToImuxAlwaysEnabled[theChannel];
    }
    else if (CT_PORT_SIDE_12 == thePort)
    {
        aConnectCount =  myPortInfo.Ports_192[0].ChannelsToImuxAlwaysEnabled[theChannel];
    }
    else if (CT_PORT_SIDE_11 >= thePort && CT_PORT_SIDE_0 <= thePort && theChannel < XC_MAX_XC_SSM_PORT)
    {
        uint8 anIndex = (uint8) thePort;
        aConnectCount =  myPortInfo.Ports_48[anIndex].ChannelsToImuxAlwaysEnabled[theChannel];
    }     
    return aConnectCount != 0;
}

//----------------------------------------------------------------------------------------------------------------------
bool TSXC_SourceConnectStatus::IsSrcUniConnectedToMate(uint16 theImuxChannel, CT_ShelfId theMateShelf, CT_SlotId theMateSlot)
{
    TSXC_S1RtRegion<TSXC_S1Route>*      aS1Rt_Region = myContext.GetXCApp().GetS1RtCfgRegion();
    TSXC_S1Route*                       aS1RtObjectPtr;
    bool                                retVal;

    retVal = false;

    //
    // Check if unicast connection exists from Src to mate
    //
    aS1RtObjectPtr = &((*aS1Rt_Region)[theImuxChannel]);
    if (aS1RtObjectPtr->GetMCastId(CT_XC_MAPPING_FIXED) == XC_MCASTID_UNKNOWN)
    {
        if ( (aS1RtObjectPtr->GetDstShelf() == theMateShelf) &&
             (aS1RtObjectPtr->GetDstSlot()  == theMateSlot) )
        {
            retVal = true;
        }
    }

    return retVal;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_SourceConnectStatus::Reset()
{
    memset(&myPortInfo, 0, sizeof(PortInfo));
    myConnStatusInitialized = false;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_SourceConnectStatus::SetConnectStatus()
{
    TSXC_ConfigRegion<TSXC_Connect>*    aXCAgentConfig_Region = myContext.GetXCApp().GetAgCfgRegion();
    TSXC_Connect*                       AG_CfgObjectPtr;
    int                                 regionIndex;
    UINT8                               srcFac;
    UINT8                               srcFacEndpt;
    CT_XC_ConnectMapping                connMapping;
    bool                                connToImux;
        
    for(regionIndex = 0; regionIndex < (int) aXCAgentConfig_Region->Size();  regionIndex++)
    {
        //--- Point to the right object on the agent config region 
        AG_CfgObjectPtr = &((*aXCAgentConfig_Region)[regionIndex]);

        if ( AG_CfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED)
        {
            // Retrieve source info
            srcFac      = AG_CfgObjectPtr->GetInputFacility();
            srcFacEndpt = AG_CfgObjectPtr->GetInputFacilityEndpoint()-1;
            connMapping = AG_CfgObjectPtr->GetMapping();

            // If dst is IMUX, set connToImux = true
            connToImux = ((regionIndex >= XC_SSM_CFG_IM_LINE_START) && (regionIndex <= XC_SSM_CFG_IM_PORT_END)) ? true : false;

            if (XC_SSM_TTP_FACILITY_ID == srcFac && srcFacEndpt < XC_MAX_XC_SSM_DWDM)
            {
                if (connToImux)
                {
                    myPortInfo.Ports_192[2].ChannelsToImux[srcFacEndpt]++;
                    if (connMapping == CT_XC_MAPPING_FIXED)
                    {
                        myPortInfo.Ports_192[2].ChannelsToImuxAlwaysEnabled[srcFacEndpt]++;
                    }
                }
                else
                {
                    myPortInfo.Ports_192[2].Channels[srcFacEndpt]++;
                }
            }
            else if (XC_SSM_DWDM_FACILITY_ID == srcFac && srcFacEndpt < XC_MAX_XC_SSM_DWDM)
            {
                if (connToImux)
                {
                    myPortInfo.Ports_192[1].ChannelsToImux[srcFacEndpt]++;
                    if (connMapping == CT_XC_MAPPING_FIXED)
                    {
                        myPortInfo.Ports_192[1].ChannelsToImuxAlwaysEnabled[srcFacEndpt]++;
                    }
                }
                else
                {
                    myPortInfo.Ports_192[1].Channels[srcFacEndpt]++;
                }
            }
            else if (XC_SSM_PORT12_FACILITY_ID == srcFac && srcFacEndpt < XC_MAX_XC_SSM_DWDM)
            {
                if (connToImux)
                {
                    myPortInfo.Ports_192[0].ChannelsToImux[srcFacEndpt]++;
                    if (connMapping == CT_XC_MAPPING_FIXED)
                    {
                        myPortInfo.Ports_192[0].ChannelsToImuxAlwaysEnabled[srcFacEndpt]++;
                    }
                }
                else
                {
                    myPortInfo.Ports_192[0].Channels[srcFacEndpt]++;
                }
            }
            else if (XC_SSM_PORT11_FACILITY_ID >= srcFac && XC_SSM_PORT0_FACILITY_ID <= srcFac && srcFacEndpt < XC_MAX_XC_SSM_PORT)
            {
                if (connToImux)
                {
                    myPortInfo.Ports_48[srcFac-1].ChannelsToImux[srcFacEndpt]++;
                    if (connMapping == CT_XC_MAPPING_FIXED)
                    {
                        myPortInfo.Ports_48[srcFac-1].ChannelsToImuxAlwaysEnabled[srcFacEndpt]++;
                    }
                }
                else
                {
                    myPortInfo.Ports_48[srcFac-1].Channels[srcFacEndpt]++;
                }
            }               
        }
    }    

    myConnStatusInitialized = true;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_SourceConnectStatus::InitConnectStatus()
{
    if (myConnStatusInitialized == false)
    {
        Reset();
        SetConnectStatus();
    }
}

