/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_PortDataAlloc      Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_PORTDATAALLOC_C
#define TSXC_PORTDATAALLOC_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>
#include <XC/TSXC_PortDataAlloc.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_PortDataAlloc::TSXC_PortDataAlloc()
{
    myIngressMap.Reset();
    myEgressMap.Reset();
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_PortDataAlloc::~TSXC_PortDataAlloc()
{
}

//--------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------
void TSXC_PortDataAlloc::SetIngressMap(CT_FAC_StsMap*  theIngressMap)
{
    myIngressMap = *theIngressMap;
}

void TSXC_PortDataAlloc::SetEgressMap(CT_FAC_StsMap*  theEgressMap)
{
    myEgressMap = *theEgressMap;
}

//--------------------------------------------------------------------------------------------------
// Get Methods
//--------------------------------------------------------------------------------------------------
const CT_FAC_StsMap& TSXC_PortDataAlloc::GetIngressMap()
{
    return myIngressMap;
}

const CT_FAC_StsMap& TSXC_PortDataAlloc::GetEgressMap()
{
    return myEgressMap;
}

//--------------------------------------------------------------------------------------------------
// Serialization Methods
//--------------------------------------------------------------------------------------------------

ostream& TSXC_PortDataAlloc::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myIngressMap);
    theStream << FC_InsertVar(myEgressMap);

    return theStream;
}

istream& TSXC_PortDataAlloc::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myIngressMap);
    theStream >> FC_ExtractVar(myEgressMap);

    return theStream;
}

FC_Stream& TSXC_PortDataAlloc::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myIngressMap;
    theStream << myEgressMap;

    return theStream;
}

FC_Stream& TSXC_PortDataAlloc::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myIngressMap;
    theStream >> myEgressMap;

    return theStream;
}

#endif // TSXC_PORTDATAALLOC_C
