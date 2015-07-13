/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 17, 2007 - Tong Wu
DESCRIPTION:    Implementation file for Static Route TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_STATRTEPARAMETERS_H__
#include <TL1Core/TL1_StatRteParameters.h>
#endif


TL1_StatRteParameters::TL1_StatRteParameters():
        myDestination(""),
        myPrefixLen(0),
        myNexthop(""),
        myTLAid(),
        myIfName(INVALID_IFNB),
        myAdvertise(false),
        myAddrType(IP_V4_ADDR),
        myBitSet( INDEX_END, false)
{

}

TL1_StatRteParameters::TL1_StatRteParameters(const TL1_StatRteParameters& theInst )
{
    myDestination   =   theInst.myDestination;
    myPrefixLen     =   theInst.myPrefixLen;
    myNexthop       =   theInst.myNexthop;
    myTLAid         =   theInst.myTLAid;
    myIfName        =   theInst.myIfName;
    myAdvertise     =   theInst.myAdvertise;
    myAddrType      =   theInst.myAddrType;
}

TL1_StatRteParameters::~TL1_StatRteParameters()
{
}

TL1_StatRteParameters& 
TL1_StatRteParameters::operator=( const TL1_StatRteParameters& theInst )
{
    myDestination   =   theInst.myDestination;
    myPrefixLen     =   theInst.myPrefixLen;
    myNexthop       =   theInst.myNexthop;
    myTLAid         =   theInst.myTLAid;
    myIfName        =   theInst.myIfName;
    myAdvertise     =   theInst.myAdvertise;
    myAddrType      =   theInst.myAddrType;

    return *this;
}

bool 
TL1_StatRteParameters::operator==( const TL1_StatRteParameters& theInst ) const
{
    if ( myDestination != theInst.myDestination)
        return false;

    if( myPrefixLen != theInst.myPrefixLen)
    {
        return false;
    }

    if ( myNexthop != theInst.myNexthop )
        return false;

    if ( myTLAid != theInst.myTLAid)
        return false;

    if ( myAdvertise != theInst.myAdvertise )
         return false;

    if ( myIfName != theInst.myIfName )
        return false;

    if(myAddrType != theInst.myAddrType)
    {
        return false;
    }

    return true;
}


string TL1_StatRteParameters::RemoveQuotesFromParameter(const char *vpIpAddr)
{
    string tempStr(vpIpAddr);

    if ( vpIpAddr[0] == '"' )
    {
        if ( vpIpAddr[strlen(vpIpAddr)-1] != '"' )
        {
            throw CT_TL1_IIFMError(CT_TL1_IIFMError::ER_IIFM_STRING);
        }

        return tempStr.substr(1,tempStr.length()-2);
    }
    else
    {
        return tempStr;
    }
}


//--------------------------------------------------------------------------------

string TL1_StatRteParameters::GetIpv6Destination( ) const
{
    return myDestination;

}

uint32 TL1_StatRteParameters::GetDestination( ) const
{
    int32  ipAddr = 0;
    int32  ipAddrTmp[4] = {0};

    if(myAddrType == IP_V4_ADDR)
    {
        sscanf(myDestination.c_str(),"%d.%d.%d.%d",&ipAddrTmp[0],&ipAddrTmp[1],&ipAddrTmp[2],&ipAddrTmp[3]); 
        ipAddr = ipAddrTmp[0]<<24 | ipAddrTmp[1]<<16 | ipAddrTmp[2]<<8 | ipAddrTmp[3];
    }

    return ipAddr;
}

void                       
TL1_StatRteParameters::SetDestination( string &theDestination)
{
    if(theDestination.find(':') != string::npos)
    {
        myAddrType = IP_V6_ADDR;
    }
    else
    {
        myAddrType = IP_V4_ADDR;
    }
    
    myDestination = theDestination;
    myBitSet[INDEX_DESTINATION] = true;

}

//--------------------------------------------------------------------------------

uint32 TL1_StatRteParameters::GetPrefixLen() const
{
    return myPrefixLen;
}

void TL1_StatRteParameters::SetPrefixLen(uint32 thePrefixLen)
{
    myPrefixLen = thePrefixLen;
    myBitSet[INDEX_PREFIXLEN] = true;
}

uint32 TL1_StatRteParameters::GetNetmask( ) const
{
    if(32 == myPrefixLen)               /* bits shifted on a 32-bit data should less than 32 */
    {
        return (uint32)0xffffffff;
    }    
    else
    {
        return ~(0xffffffff>>myPrefixLen);
    }
}

//--------------------------------------------------------------------------------
CT_TL1_LinkAddr         
TL1_StatRteParameters::GetTLAid( ) const
{
    return myTLAid;
}

void                       
TL1_StatRteParameters::SetTLAid( CT_TL1_LinkAddr &theTLAid )
{
    myTLAid = theTLAid;
    myBitSet[INDEX_TLAID] = true;
}

//--------------------------------------------------------------------------------
CT_IfNumber         
TL1_StatRteParameters::GetIfName( ) const
{
    return myIfName;
}

void                       
TL1_StatRteParameters::SetIfName( CT_IfNumber theIfName )
{
    myIfName = theIfName;
    myBitSet[INDEX_IFNAME] = true;
}

//--------------------------------------------------------------------------------
string TL1_StatRteParameters::GetIpv6Nexthop( ) const
{
    return myNexthop;
}


uint32 TL1_StatRteParameters::GetNexthop( ) const
{
    int32  ipAddr = 0;
    int32  ipAddrTmp[4] = {0};

    if(myAddrType == IP_V4_ADDR)
    {
        sscanf(myNexthop.c_str(),"%d.%d.%d.%d",&ipAddrTmp[0],&ipAddrTmp[1],&ipAddrTmp[2],&ipAddrTmp[3]); 
        ipAddr = ipAddrTmp[0]<<24 | ipAddrTmp[1]<<16 | ipAddrTmp[2]<<8 | ipAddrTmp[3];
    }

    return ipAddr;
}

void TL1_StatRteParameters::SetNexthop(const string &theNexthop )
{
    myNexthop = theNexthop;
    myBitSet[INDEX_NEXTHOP] = true;
}


//--------------------------------------------------------------------------------
bool
TL1_StatRteParameters::GetAdvertise( ) const
{
    return myAdvertise;
}

void 
TL1_StatRteParameters::SetAdvertise(bool theAdvertise)
{
    myAdvertise = theAdvertise;
    myBitSet[INDEX_ADVERTISE] = true;
}

IpAddrType TL1_StatRteParameters::GetAdrdrType( ) const
{
    return myAddrType;
}


void TL1_StatRteParameters::SetAddrType(IpAddrType theType)
{
    myAddrType = theType;
}


bool  TL1_StatRteParameters::GetParamValid(TL1_StatRteParameters::PARAM theParam)
{
    if(theParam >= INDEX_END)
    {
        return false;
    }

    return myBitSet[theParam];
}




