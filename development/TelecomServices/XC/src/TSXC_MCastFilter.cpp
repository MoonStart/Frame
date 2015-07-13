/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_MCastFilter      Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_MCAST_FILTER_C
#define TSXC_MCAST_FILTER_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_MCastFilter.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <XC/TSXC_TestMenu.h>

// *************
// Constructor
// *************
TSXC_MCastFilter::TSXC_MCastFilter()
{
    SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
}

// *************
// Destructor
// *************
TSXC_MCastFilter::~TSXC_MCastFilter()
{
}

// *********************
// Serialization Methods
// *********************

ostream& TSXC_MCastFilter::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myMCastType);
    return theStream;
}

istream& TSXC_MCastFilter::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myMCastType);
    return theStream;
}

/*
FC_Stream& TSXC_MCastFilter::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myMCastType;
    return theStream;
}

FC_Stream& TSXC_MCastFilter::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myMCastType;
    return theStream;
}
*/

bool TSXC_MCastFilter::operator==(const TSXC_MCastFilter& theMCast) const
{
    if (myMCastType       != theMCast.myMCastType)
        return false;
    else
        return true;
}

bool TSXC_MCastFilter::operator!=(const TSXC_MCastFilter& theMCast) const
{
    return (!(*this == theMCast));
}

// *************
// Set Method
// *************
void TSXC_MCastFilter::SetMCastTypeToUse(CT_XC_ConnectMapping theMCastType)
{
    if ((theMCastType != CT_XC_MAPPING_FIXED)
        && (theMCastType != CT_XC_MAPPING_FLEXIBLE))
    {
        char ErrorMsg[50];
        sprintf(ErrorMsg, "TSXC_MCastFilter::SetMCastTypeToUse() CT_XC_ConnectMapping (%d) out of range\n", theMCastType);
        FC_REPORT_ERROR(FC_RuntimeError, ErrorMsg);
    }

    uint8 aType = (uint8)theMCastType;
    myMCastType = aType;
}

// *************
// Get Method
// *************
CT_XC_ConnectMapping TSXC_MCastFilter::GetMCastTypeToUse() const
{
    return static_cast<CT_XC_ConnectMapping>(myMCastType);
}

#endif // TSXC_MCAST_FILTER_C
