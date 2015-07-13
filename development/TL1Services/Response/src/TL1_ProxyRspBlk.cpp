/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 Mtera Response 
TARGET:
AUTHOR:        2013.11.8- Gang zhu
DESCRIPTION:    Source file for TL1 Retrive mtera Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_ProxyRspBlk.h>


TL1_ProxyRspBlk::TL1_ProxyRspBlk(const TL1_SmartParameter<CT_ProxyMode>& theProxyMode) : 
    myProxyMode(theProxyMode)
{
}
  
TL1_ProxyRspBlk::TL1_ProxyRspBlk(const TL1_ProxyRspBlk& theBlock) :
    myProxyMode(theBlock.myProxyMode)      
{
}

TL1_ProxyRspBlk::~TL1_ProxyRspBlk()
{
}

TL1_ProxyRspBlk& TL1_ProxyRspBlk::operator=( const TL1_ProxyRspBlk& theBlock )
{
    myProxyMode = theBlock.myProxyMode;
   
    return *this;
}


const TL1_SmartParameter<CT_ProxyMode>& TL1_ProxyRspBlk::GetProxyMode() const
{
    return myProxyMode;
}
