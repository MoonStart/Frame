/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     January, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_SourceConnectStatus  Class Definition
--------------------------------------------------------------------------*/

#ifndef TSXC_SourceConnectStatus_H
#define TSXC_SourceConnectStatus_H
#include <XC/TSXC_CrossConnect.h>
//----------------------------------------------------------------------------------------------------------------------
//--- The purpose this module is to provide a connection status to signal protect and it has to be fast lookup too.
//--- When the config action runs the PortInfo gets updated based on internal connections(between ports/line). 
//--- The signal protect checks the status by indexing to the right place by passing the port and channel number. 
//--- The GetConnectionCount() method is used for the test menu only.
//----------------------------------------------------------------------------------------------------------------------
class ChanInfo_48 
{
public:
    uint8   Channels[XC_MAX_XC_SSM_PORT];
    uint8   ChannelsToImux[XC_MAX_XC_SSM_PORT];
    uint8   ChannelsToImuxAlwaysEnabled[XC_MAX_XC_SSM_PORT];
};
class ChanInfo_192 
{
public:
    uint8   Channels[XC_MAX_XC_SSM_DWDM];
    uint8   ChannelsToImux[XC_MAX_XC_SSM_DWDM];
    uint8   ChannelsToImuxAlwaysEnabled[XC_MAX_XC_SSM_DWDM];
};
class PortInfo
{
public:
    ChanInfo_48    Ports_48  [XC_MAX_SSM_PORTN_INTF];
    ChanInfo_192   Ports_192 [XC_MAX_SSM_PORTX_INTF   + XC_MAX_SSM_DWDM_INTF   + XC_MAX_SSM_TTP_INTF];
};

//----------------------------------------------------------------------------------------------------------------------
class TSXC_SourceConnectStatus 
{
public:
	//--- Constructor 
	TSXC_SourceConnectStatus(T6100_TelecomIf& theContext); 

	//--- Destructor
	~TSXC_SourceConnectStatus();
    
    bool    IsSrcConnectedInternally(CT_IntfId thePort, CT_ChannelId theChannel);
    int     GetConnectionCount(CT_IntfId thePort, CT_ChannelId theChannel);    
    bool    IsSrcConnectedToImux(CT_IntfId thePort, CT_ChannelId theChannel);
    bool    IsSrcConnectedToImuxAlwaysEnabled(CT_IntfId thePort, CT_ChannelId theChannel);
    bool    IsSrcUniConnectedToMate(uint16 theImuxChannel, CT_ShelfId theMateShelf, CT_SlotId theMateSlot);
    void    Reset();
    void    SetConnectStatus();
    void    InitConnectStatus();
    
private:
    T6100_TelecomIf&                myContext;
    PortInfo                        myPortInfo;
    bool                            myConnStatusInitialized;

};

#endif /* TSXC_SourceConnectStatus_H */
