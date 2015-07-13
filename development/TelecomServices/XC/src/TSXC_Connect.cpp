/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     March, 2004  Jai Harpalani
    DESCRIPTION:   TSXC_Connect  Class Implementation
    LAST REVISION:
    Date    Description
    ----    -----------
    09-03-08  t71mr00073743:Allocate 7 bits for myInputFacility and myOutput-
            Facility and pack them into bits16 along with myConnectState.  
            Update ReadObjectBinary(), WriteObjectBinary(), ReadObject()
            and WriteObject() to handle these new bit-field allocations.
--------------------------------------------------------------------------*/

#ifndef TSXC_CONNECT_C
#define TSXC_CONNECT_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_Connect.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <XC/TSXC_TestMenu.h>

// *************
// Constructor
// *************
TSXC_Connect::TSXC_Connect()
{
    myInputFacilityEndpoint = 0;
    myOutputFacilityEndpoint = 0;
    myOutputFacility = 0;
    myInputFacility = 0;
    myConnectState = static_cast<uint8>(CT_XC_STATE_NOTCONNECTED);
    myConnectType = static_cast<uint8>(CT_XC_TYPE_UNSPECIFIED);
    myConnectMapping = static_cast<uint8>(CT_XC_MAPPING_UNSPECIFIED);
}

// *************
// Destructor
// *************
TSXC_Connect::~TSXC_Connect()
{
}


// *********************
// Serialization Methods
// *********************

ostream& TSXC_Connect::WriteObject( ostream& theStream )
{
    uint8 tmpInputFacility  = GetInputFacility();
    uint8 tmpOutputFacility = GetOutputFacility();
    uint8 tmpConnState      = GetState();
    uint8 tmpConnType       = GetType();
    uint8 tmpConnMapping    = GetMapping();

    theStream<<FC_InsertVar(tmpInputFacility);
    theStream<<FC_InsertVar(myInputFacilityEndpoint);
    theStream<<FC_InsertVar(tmpOutputFacility);
    theStream<<FC_InsertVar(myOutputFacilityEndpoint);
    theStream<<FC_InsertVar(tmpConnType);
    theStream<<FC_InsertVar(tmpConnMapping);
    theStream<<FC_InsertVar(tmpConnState);

    return theStream;
}

istream& TSXC_Connect::ReadObject( istream& theStream )
{
    uint8  tmpInputFacility;
    uint8  tmpOutputFacility;
    uint8  tmpConnType;
    uint8  tmpConnMapping;
    uint8  tmpConnState;

    theStream>>FC_ExtractVar(tmpInputFacility);
    theStream>>FC_ExtractVar(myInputFacilityEndpoint);
    theStream>>FC_ExtractVar(tmpOutputFacility);
    theStream>>FC_ExtractVar(myOutputFacilityEndpoint);
    theStream>>FC_ExtractVar(tmpConnType);
    theStream>>FC_ExtractVar(tmpConnMapping);
    theStream>>FC_ExtractVar(tmpConnState);

    SetInputFacility(tmpInputFacility);
    SetOutputFacility(tmpOutputFacility);
    SetType(static_cast<CT_XC_ConnectType>(tmpConnType));
    SetMapping(static_cast<CT_XC_ConnectMapping>(tmpConnMapping));
    SetState(static_cast<CT_XC_ConnectState>(tmpConnState));

    return theStream;
}

FC_Stream& TSXC_Connect::WriteObjectBinary( FC_Stream& theStream )
{

    bits8   ConnectStatePlusConnectTypePlusConnectMapping;

    ConnectStatePlusConnectTypePlusConnectMapping = (myConnectState << XC_BIT_POS_CONNECTSTATE  ) |
                                             (myConnectMapping << XC_BIT_POS_MAP  ) |
                                              myConnectType;

    theStream<<myInputFacilityEndpoint;
    theStream<<myOutputFacilityEndpoint;
    theStream<<myInputFacility;
    theStream<<myOutputFacility;
    theStream<<ConnectStatePlusConnectTypePlusConnectMapping;

    return theStream;
}

FC_Stream& TSXC_Connect::ReadObjectBinary( FC_Stream& theStream )
{
    bits8   ConnectStatePlusConnectTypePlusConnectMapping;

    theStream>>myInputFacilityEndpoint;
    theStream>>myOutputFacilityEndpoint;
    theStream>>myInputFacility;
    theStream>>myOutputFacility;
    theStream>>ConnectStatePlusConnectTypePlusConnectMapping;

    SetType(static_cast<CT_XC_ConnectType>(ConnectStatePlusConnectTypePlusConnectMapping & XC_BITS_TYPE));
    SetMapping(static_cast<CT_XC_ConnectMapping>((ConnectStatePlusConnectTypePlusConnectMapping  & XC_BITS_MAP) >> XC_BIT_POS_MAP));
    SetState(static_cast<CT_XC_ConnectState>((ConnectStatePlusConnectTypePlusConnectMapping & XC_BITS_CONNECTSTATE) >> XC_BIT_POS_CONNECTSTATE));

    return theStream;
}


void TSXC_Connect::PrintConnect()
{
    FC_FmtFlags previousFlags;

    previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::left);

    fc_cout.Width(13);
    fc_cout << TSXC_TestMenu::ConnectFacToText(GetInputFacility(),false);
    fc_cout.Width(4);
    fc_cout << static_cast<int>(GetInputFacilityEndpoint());
    fc_cout.Width(13);
    fc_cout << TSXC_TestMenu::ConnectFacToText(GetOutputFacility(),false);
    fc_cout.Width(4);
    fc_cout << static_cast<int>(GetOutputFacilityEndpoint());
    fc_cout.Width(14);
    fc_cout << TSXC_TestMenu::ConnectTypeToText(GetType());
    fc_cout.Width(11);
    fc_cout << TSXC_TestMenu::ConnectMappingToText(GetMapping());
    fc_cout.Width(13);
    fc_cout << TSXC_TestMenu::ConnectStateToText(GetState());
    //fc_cout.Width(13);
    //fc_cout << TSXC_TestMenu::ConnectActDeactToText(GetActDeact());
    fc_cout << endl;

    fc_cout.Width(0);
    fc_cout.Flags(previousFlags);
}

void TSXC_Connect::PrintConnectActive(UINT8 theInput, UINT8 theInputEndpt)
{
    FC_FmtFlags previousFlags;

    previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::left);

    fc_cout.Width(13);
    fc_cout << TSXC_TestMenu::ConnectFacToText(theInput,false);
    fc_cout.Width(4);
    fc_cout << static_cast<int>(theInputEndpt);
    fc_cout.Width(13);
    fc_cout << TSXC_TestMenu::ConnectFacToText(GetOutputFacility(),false);
    fc_cout.Width(4);
    fc_cout << static_cast<int>(GetOutputFacilityEndpoint());
    fc_cout.Width(14);
    fc_cout << TSXC_TestMenu::ConnectTypeToText(GetType());
    fc_cout.Width(11);
    fc_cout << TSXC_TestMenu::ConnectMappingToText(GetMapping());
    fc_cout.Width(13);
    fc_cout << TSXC_TestMenu::ConnectStateToText(GetState());
    //fc_cout.Width(13);
    //fc_cout << TSXC_TestMenu::ConnectActDeactToText(GetActDeact());
    fc_cout << endl;

    fc_cout.Width(0);
    fc_cout.Flags(previousFlags);
}

bool TSXC_Connect::operator==(const TSXC_Connect& theConnect) const
{
    bool retVal;

    retVal = false;

    if ( (myInputFacilityEndpoint  == theConnect.myInputFacilityEndpoint) &&
         (myOutputFacilityEndpoint == theConnect.myOutputFacilityEndpoint) &&
         (myOutputFacility         == theConnect.myOutputFacility) &&
         (myInputFacility          == theConnect.myInputFacility) &&
         (myConnectState           == theConnect.myConnectState) &&
         (myConnectType            == theConnect.myConnectType) &&
         (myConnectMapping         == theConnect.myConnectMapping) )
    {
        retVal = true;
    }

    return retVal;
}

bool TSXC_Connect::operator!=(const TSXC_Connect& theConnect) const
{
    return (!(*this == theConnect));
}

TSXC_Connect& TSXC_Connect::operator=(const TSXC_Connect& theConnect)
{
    myInputFacilityEndpoint  = theConnect.myInputFacilityEndpoint;
    myOutputFacilityEndpoint = theConnect.myOutputFacilityEndpoint;
    myOutputFacility         = theConnect.myOutputFacility;
    myInputFacility          = theConnect.myInputFacility;
    myConnectState           = theConnect.myConnectState;
    myConnectType            = theConnect.myConnectType;
    myConnectMapping         = theConnect.myConnectMapping;

    return *this;
}


#endif // TSXC_CONNECT_C
