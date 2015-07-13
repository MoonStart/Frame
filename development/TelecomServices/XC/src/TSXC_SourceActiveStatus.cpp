/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2004  Jai Harpalani
 DESCRIPTION:   XC_ActiveSource  Class Implementation
--------------------------------------------------------------------------*/

#ifndef XC_SOURCEACTIVESTATUS_C
#define XC_SOURCEACTIVESTATUS_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_SourceActiveStatus.h>
#include <XC/TSXC_TestMenu.h>
#include <XC/TSXC_CrossConnect.h>

// *************
// Constructor
// *************
TSXC_SourceActiveStatus::TSXC_SourceActiveStatus():
    myActiveFacility(XC_INVALID_FAC),
    myActiveFacilityEndpoint(XC_INVALID_FAC_ENDPT),
    mySourceFacility(0),
    mySourceFacilityEndpoint(0)
{
}

// *************
// Destructor
// *************
TSXC_SourceActiveStatus::~TSXC_SourceActiveStatus()
{
}

// *************
// Set Methods
// *************

void TSXC_SourceActiveStatus::SetSourceFacility( uint8 Facility )
{
    mySourceFacility = Facility;
}

void TSXC_SourceActiveStatus::SetSourceFacilityEndpoint( uint8 Endpoint )
{
    mySourceFacilityEndpoint = Endpoint;
}

void TSXC_SourceActiveStatus::SetActiveFacility( uint8 Facility )
{
    myActiveFacility = Facility;
}

void TSXC_SourceActiveStatus::SetActiveFacilityEndpoint( uint8 Endpoint )
{
    myActiveFacilityEndpoint = Endpoint;
}

void TSXC_SourceActiveStatus::ResetActiveFacility()
{
    myActiveFacility = XC_INVALID_FAC;
}

void TSXC_SourceActiveStatus::ResetActiveFacilityEndpoint()
{
    myActiveFacilityEndpoint = XC_INVALID_FAC_ENDPT;
}

// *************
// Get Methods
// *************
uint8 TSXC_SourceActiveStatus::GetSourceFacility()
{
    return mySourceFacility;
}

uint8 TSXC_SourceActiveStatus::GetSourceFacilityEndpoint()
{
    return mySourceFacilityEndpoint;
}

uint8 TSXC_SourceActiveStatus::GetActiveFacility()
{
    return myActiveFacility;
}

uint8 TSXC_SourceActiveStatus::GetActiveFacilityEndpoint()
{
    return myActiveFacilityEndpoint;
}

bool TSXC_SourceActiveStatus::IsActiveFacilitySet()
{
    return (myActiveFacility == XC_INVALID_FAC) ? false : true;
}

bool TSXC_SourceActiveStatus::IsActiveFacilityEndpointSet()
{
    return (myActiveFacilityEndpoint == XC_INVALID_FAC_ENDPT) ? false : true;
}


// *********************
// Serialization Methods
// *********************

ostream& TSXC_SourceActiveStatus::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myActiveFacility);
    theStream<<FC_InsertVar(myActiveFacilityEndpoint);
    theStream<<FC_InsertVar(mySourceFacility);
    theStream<<FC_InsertVar(mySourceFacilityEndpoint);

    return theStream;
}

istream& TSXC_SourceActiveStatus::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myActiveFacility);
    theStream>>FC_ExtractVar(myActiveFacilityEndpoint);
    theStream>>FC_ExtractVar(mySourceFacility);
    theStream>>FC_ExtractVar(mySourceFacilityEndpoint);

    return theStream;
}

FC_Stream& TSXC_SourceActiveStatus::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myActiveFacility;
    theStream<<myActiveFacilityEndpoint;
    theStream<<mySourceFacility;
    theStream<<mySourceFacilityEndpoint;

    return theStream;
}

FC_Stream& TSXC_SourceActiveStatus::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myActiveFacility;
    theStream>>myActiveFacilityEndpoint;
    theStream>>mySourceFacility;
    theStream>>mySourceFacilityEndpoint;

    return theStream;
}


bool TSXC_SourceActiveStatus::PrintSource(uint8 requestedFacID, bool filter)
{
    bool printedStatus = false;
    FC_FmtFlags previousFlags;

    previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::left);
    if ((requestedFacID == 0) || (requestedFacID == mySourceFacility) || (requestedFacID == myActiveFacility))
      if ((myActiveFacility != mySourceFacility) || (mySourceFacilityEndpoint != myActiveFacilityEndpoint) || (filter != true))
        { 
            fc_cout.Width(5);
            fc_cout << TSXC_TestMenu::ConnectFacToText(mySourceFacility,true);
            fc_cout.Width(4);
            fc_cout << static_cast<int>(mySourceFacilityEndpoint);
            fc_cout.Width(5);
            fc_cout << TSXC_TestMenu::ConnectFacToText(myActiveFacility,true);
            fc_cout.Width(4);
            fc_cout << static_cast<int>(myActiveFacilityEndpoint);
            fc_cout << "|";
            printedStatus = true;
        }
    fc_cout.Width(0);
    fc_cout.Flags(previousFlags);
    return printedStatus;
}

bool TSXC_SourceActiveStatus::operator==(const TSXC_SourceActiveStatus& theSourceActiveStatus) const
{
    bool retVal;

    retVal = false;

    if ( (mySourceFacility         == theSourceActiveStatus.mySourceFacility) &&
         (mySourceFacilityEndpoint == theSourceActiveStatus.mySourceFacilityEndpoint) &&
         (myActiveFacility         == theSourceActiveStatus.myActiveFacility) &&
         (myActiveFacilityEndpoint == theSourceActiveStatus.myActiveFacilityEndpoint) )
    {
        retVal = true;
    }

    return retVal;
}

bool TSXC_SourceActiveStatus::operator!=(const TSXC_SourceActiveStatus& theSourceActiveStatus) const
{
    return (!(*this == theSourceActiveStatus));
}

#endif // XC_SOURCEACTIVESTATUS_C

