// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_MacStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_MacStatus::MON_MacStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_MacStatus::~MON_MacStatus(void)
{
    // Nothing to do for now.
}

CT_TEL_MAC_AUTONEGSTATUS MON_MacStatus::GetAutoNegStatus() const 
{
    return myAutoNegStatus;
}

bool MON_MacStatus::SetAutoNegStatus(CT_TEL_MAC_AUTONEGSTATUS theAutoNegStatus) 
{
    bool hasChanged = false;
    if (!(myAutoNegStatus == theAutoNegStatus))
    {
        myAutoNegStatus = theAutoNegStatus;
        hasChanged = true;
    }

    return hasChanged;
}


CT_TEL_DETECTED MON_MacStatus::GetAutoNegRmtSignal() const 
{
    return myAutoNegRmtSignal;
}

bool MON_MacStatus::SetAutoNegRmtSignal(CT_TEL_DETECTED theAutoNegRmtSignal) 
{
    bool hasChanged = false;
    if (!(myAutoNegRmtSignal == theAutoNegRmtSignal))
    {
        myAutoNegRmtSignal = theAutoNegRmtSignal;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_daHz MON_MacStatus::GetOperRate() const 
{
    return myOperRate;
}

bool MON_MacStatus::SetOperRate(CT_TEL_daHz theOperRate) 
{
    bool hasChanged = false;
    if (!(myOperRate == theOperRate))
    {
        myOperRate = theOperRate;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_MAC_DUPLEX_MODE MON_MacStatus::GetOperDuplexMode() const 
{
    return myOperDuplex;
}

bool MON_MacStatus::SetOperDuplexMode(CT_TEL_MAC_DUPLEX_MODE theOperDuplex)
{
    bool hasChanged = false;
    if (!(myOperDuplex == theOperDuplex))
    {
        myOperDuplex = theOperDuplex;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_MAC_FLOWCTRL MON_MacStatus::GetOperFlowCtrl() const 
{
    return myOperFlowCtrl;
}

bool MON_MacStatus::SetOperFlowCtrl(CT_TEL_MAC_FLOWCTRL theOperFlowCtrl)
{
    bool hasChanged = false;
    if (!(myOperFlowCtrl == theOperFlowCtrl))
    {
        myOperFlowCtrl = theOperFlowCtrl;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_MacStatus::GetOperAutoNeg() const 
{
    return myOperAutoNeg;
}

bool MON_MacStatus::SetOperAutoNeg(bool theOperAutoNeg)
{
    bool hasChanged = false;
    if (!(myOperAutoNeg == theOperAutoNeg))
    {
        myOperAutoNeg = theOperAutoNeg;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_MacStatus::GetLinkFailRx() const 
{
    return myLinkFailRx;
}

bool MON_MacStatus::SetLinkFailRx(bool theLinkFailRx)
{
    bool hasChanged = false;
    if (!(myLinkFailRx == theLinkFailRx))
    {
        myLinkFailRx = theLinkFailRx;
        hasChanged = true;
    }

    return hasChanged;
}



CT_TEL_LacpPortState MON_MacStatus::GetPortLacpState() const
{
    return myPortLacpState;
}

bool MON_MacStatus::SetPortLacpState(CT_TEL_LacpPortState theState)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPortLacpState == theState))
    {
        myPortLacpState = theState;
        return true;// field has changed
    }

    return hasChanged;   
}


CT_AGGRE_FIELD MON_MacStatus::GetPortAggregationField() const
{
    return myPortAggregationField;
}

bool MON_MacStatus::SetPortAggregationField(CT_AGGRE_FIELD theField)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPortAggregationField == theField))
    {
        myPortAggregationField = theField;
        return true;// field has changed
    }

    return hasChanged;   
}


uint16 MON_MacStatus::GetPortLacpPriority() const
{
    return myPortLacpPriority;
}

bool MON_MacStatus::SetPortLacpPriority(uint16 thePriority)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPortLacpPriority == thePriority))
    {
        myPortLacpPriority = thePriority;
        return true;// field has changed
    }

    return hasChanged;   
}


bool MON_MacStatus::GetPartnerActiveFlag() const
{
    return myPartnerActiveFlag;
}

bool MON_MacStatus::SetPartnerActiveFlag(bool theFlag)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPartnerActiveFlag == theFlag))
    {
        myPartnerActiveFlag = theFlag;
        return true;// field has changed
    }

    return hasChanged;   
}


CT_LacpSystemId MON_MacStatus::GetPartnerSystemID() const
{
    return myPartnerSystemID;
}

bool MON_MacStatus::SetPartnerSystemID(CT_LacpSystemId theSystemID)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPartnerSystemID == theSystemID))
    {
        myPartnerSystemID = theSystemID;
        return true;// field has changed
    }

    return hasChanged;   
}


uint16 MON_MacStatus::GetPartnerPortPriority() const
{
    return myPartnerPortPriority;
}

bool MON_MacStatus::SetPartnerPortPriority(uint16 thePriority)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPartnerPortPriority == thePriority))
    {
        myPartnerPortPriority = thePriority;
        return true;// field has changed
    }

    return hasChanged;   
}


uint32 MON_MacStatus::GetPartnerOperationalKey() const
{
    return myPartnerOperationalKey;
}

bool MON_MacStatus::SetPartnerOperationalKey(uint32 theKey)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPartnerOperationalKey == theKey))
    {
        myPartnerOperationalKey = theKey;
        return true;// field has changed
    }

    return hasChanged;   
}


uint8 MON_MacStatus::GetPartnerPortState() const
{
    return myPartnerPortState;
}

bool MON_MacStatus::SetPartnerPortState(uint8 theState)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myPartnerPortState == theState))
    {
        myPartnerPortState = theState;
        return true;// field has changed
    }

    return hasChanged;   
}


CT_LacpSystemId MON_MacStatus::GetLagActorSystemID() const
{
    return myLagActorSystemID;
}

bool MON_MacStatus::SetLagActorSystemID(CT_LacpSystemId theSystemID)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagActorSystemID == theSystemID))
    {
        myLagActorSystemID = theSystemID;
        return true;// field has changed
    }

    return hasChanged;   
}


uint16 MON_MacStatus::GetLagActorSystemPriority() const
{
    return myLagActorSystemPriority;
}

bool MON_MacStatus::SetLagActorSystemPriority(uint16 thePriority)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagActorSystemPriority == thePriority))
    {
        myLagActorSystemPriority = thePriority;
        return true;// field has changed
    }

    return hasChanged;   
}


uint32 MON_MacStatus::GetLagActorOperationalKey() const
{
    return myLagActorOperationalKey;
}

bool MON_MacStatus::SetLagActorOperationalKey(uint32 theKey)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagActorOperationalKey == theKey))
    {
        myLagActorOperationalKey = theKey;
        return true;// field has changed
    }

    return hasChanged;   
}


uint16 MON_MacStatus::GetLagActorAdminKey() const
{
    return myLagActorAdminKey;
}

bool MON_MacStatus::SetLagActorAdminKey(uint16 theKey)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagActorAdminKey == theKey))
    {
        myLagActorAdminKey = theKey;
        return true;// field has changed
    }

    return hasChanged;   
}


CT_LacpSystemId MON_MacStatus::GetLagPartnerSystemID() const
{
    return myLagPartnerSystemID;
}

bool MON_MacStatus::SetLagPartnerSystemID(CT_LacpSystemId theSystemID)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagPartnerSystemID == theSystemID))
    {
        myLagPartnerSystemID = theSystemID;
        return true;// field has changed
    }

    return hasChanged;   
}


uint16 MON_MacStatus::GetLagPartnerSystemPriority() const
{
    return myLagPartnerSystemPriority;
}

bool MON_MacStatus::SetLagPartnerSystemPriority(uint16 thePriority)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagPartnerSystemPriority == thePriority))
    {
        myLagPartnerSystemPriority = thePriority;
        return true;// field has changed
    }

    return hasChanged;   
}


uint32 MON_MacStatus::GetLagPartnerOperationalKey() const
{
    return myLagPartnerOperationalKey;
}

bool MON_MacStatus::SetLagPartnerOperationalKey(uint32 theKey)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagPartnerOperationalKey == theKey))
    {
        myLagPartnerOperationalKey = theKey;
        return true;// field has changed
    }

    return hasChanged;   
}


uint16 MON_MacStatus::GetLagPartnerAdminKey() const
{
    return myLagPartnerAdminKey;
}

bool MON_MacStatus::SetLagPartnerAdminKey(uint16 theKey)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myLagPartnerAdminKey == theKey))
    {
        myLagPartnerAdminKey = theKey;
        return true;// field has changed
    }

    return hasChanged;   
}


CT_ETH_SFP_XFP_TYPE MON_MacStatus::GetEthSfpXfpType() const
{
    return myEthSfpXfpType;
}

bool MON_MacStatus::SetEthSfpXfpType(CT_ETH_SFP_XFP_TYPE theType)
{
    // keep track of any changes
    bool hasChanged = false;
    if (!(myEthSfpXfpType == theType))
    {
        myEthSfpXfpType = theType;
        return true;// field has changed
    }

    return hasChanged;   
}


bool MON_MacStatus::GetIsSoftwareAutoNegEnabled() const
{
    return myIsSoftwareAutoNegEnabled;
}

void MON_MacStatus::SetIsSoftwareAutoNegEnabled(CT_ETH_SFP_XFP_TYPE theType)
{
    myIsSoftwareAutoNegEnabled = ((theType == CT_ETH_10G_XFP)           || 
                                  (theType == CT_ETH_1G_ELECTRICAL_SFP) ||
                                  (theType == CT_ETH_1G_OPTICAL_SFP)    );
}



void MON_MacStatus::Reset(void)
{
    MON_Object::Reset();
    myAutoNegStatus    = CT_TEL_MAC_AUTONEG_UNKNOWN;
    myAutoNegRmtSignal = CT_TEL_DETECTED_UNKNOWN;
    myOperRate         = 0;
    myOperDuplex       = CT_TEL_MAC_DUPLEX_UNKNOWN;
    myOperFlowCtrl     = CT_TEL_MAC_FLW_UNKNOWN;
    myOperAutoNeg      = false;
    myLinkFailRx       = false;
    myIsSoftwareAutoNegEnabled       = false;
    myEthSfpXfpType    = CT_ETH_UNKNOWN_TYPE;
    myPortLacpState         = CT_TEL_LacpPortState_UNKNOWN;
    myPortAggregationField  = 0;
    myPortLacpPriority      = 0;;
    myPartnerActiveFlag     = false;
    myPartnerSystemID       = CT_LacpSystemId();
    myPartnerPortPriority   = 0;
    myPartnerOperationalKey = 0;
    myPartnerPortState      = 0;
    myLagActorSystemID         = CT_LacpSystemId();
    myLagActorSystemPriority   = 0;
    myLagActorOperationalKey   = 0;
    myLagActorAdminKey         = 0;
    myLagPartnerSystemID       = CT_LacpSystemId();
    myLagPartnerSystemPriority = 0;
    myLagPartnerOperationalKey = 0;
    myLagPartnerAdminKey       = 0;
}

// For Display
ostream& MON_MacStatus::WriteObject( ostream& theStream )
{
    uint32 aTemp;
 
    MON_Object::WriteObject(theStream);
    aTemp = myAutoNegStatus;
    theStream << FC_InsertVar(aTemp);
    aTemp = myAutoNegRmtSignal;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(myOperRate);
    aTemp = myOperDuplex;
    theStream << FC_InsertVar(aTemp);
    aTemp = myOperFlowCtrl;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(myOperAutoNeg);
    theStream << FC_InsertVar(myLinkFailRx);
    theStream << FC_InsertVar(myIsSoftwareAutoNegEnabled);

    aTemp = myPortLacpState;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(myPortAggregationField);
    theStream << FC_InsertVar(myPortLacpPriority);
    theStream << FC_InsertVar(myPartnerActiveFlag);
    theStream << FC_InsertVar(myPartnerSystemID);
    theStream << FC_InsertVar(myPartnerPortPriority);
    theStream << FC_InsertVar(myPartnerOperationalKey);
    theStream << FC_InsertVar(myPartnerPortState);
    theStream << FC_InsertVar(myLagActorSystemID);
    theStream << FC_InsertVar(myLagActorSystemPriority);
    theStream << FC_InsertVar(myLagActorOperationalKey);
    theStream << FC_InsertVar(myLagActorAdminKey);
    theStream << FC_InsertVar(myLagPartnerSystemID);
    theStream << FC_InsertVar(myLagPartnerSystemPriority);
    theStream << FC_InsertVar(myLagPartnerOperationalKey);
    theStream << FC_InsertVar(myLagPartnerAdminKey);

    aTemp = myEthSfpXfpType;
    theStream << FC_InsertVar(aTemp);

    return theStream;

}

istream& MON_MacStatus::ReadObject( istream& theStream )
{
    uint32 aTemp = 0;

    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(aTemp);
    myAutoNegStatus = (CT_TEL_MAC_AUTONEGSTATUS)aTemp;
    theStream >> FC_ExtractVar(aTemp);
    myAutoNegRmtSignal = (CT_TEL_DETECTED)aTemp;
    theStream >> FC_ExtractVar(myOperRate);
    theStream >> FC_ExtractVar(aTemp);
    myOperDuplex = (CT_TEL_MAC_DUPLEX_MODE)aTemp;
    theStream >> FC_ExtractVar(aTemp);
    myOperFlowCtrl = (CT_TEL_MAC_FLOWCTRL)aTemp;
    theStream   >> FC_ExtractVar(myOperAutoNeg);
    theStream   >> FC_ExtractVar(myLinkFailRx);
    theStream   >> FC_ExtractVar(myIsSoftwareAutoNegEnabled);

    theStream >> FC_ExtractVar(aTemp);
    myPortLacpState = (CT_TEL_LacpPortState) aTemp;
    theStream >> FC_ExtractVar(myPortAggregationField);
    theStream >> FC_ExtractVar(myPortLacpPriority);
    theStream >> FC_ExtractVar(myPartnerActiveFlag);
    theStream >> FC_ExtractVar(myPartnerSystemID);
    theStream >> FC_ExtractVar(myPartnerPortPriority);
    theStream >> FC_ExtractVar(myPartnerOperationalKey);
    theStream >> FC_ExtractVar(myPartnerPortState);
    theStream >> FC_ExtractVar(myLagActorSystemID);
    theStream >> FC_ExtractVar(myLagActorSystemPriority);
    theStream >> FC_ExtractVar(myLagActorOperationalKey);
    theStream >> FC_ExtractVar(myLagActorAdminKey);
    theStream >> FC_ExtractVar(myLagPartnerSystemID);
    theStream >> FC_ExtractVar(myLagPartnerSystemPriority);
    theStream >> FC_ExtractVar(myLagPartnerOperationalKey);
    theStream >> FC_ExtractVar(myLagPartnerAdminKey);

    theStream >> FC_ExtractVar(aTemp);
    myEthSfpXfpType = (CT_ETH_SFP_XFP_TYPE) aTemp;

    return theStream;

}

// For persitance and region transfer
FC_Stream& MON_MacStatus::WriteObjectBinary( FC_Stream& theStream )
{
    uint32 aTemp;

    MON_Object::WriteObjectBinary(theStream);

    aTemp = myAutoNegStatus;
    theStream << aTemp;
    aTemp = myAutoNegRmtSignal;
    theStream << aTemp;
    theStream << myOperRate;
    aTemp = myOperDuplex;
    theStream << aTemp;
    aTemp = myOperFlowCtrl;
    theStream << aTemp;
    theStream << myOperAutoNeg;
    theStream << myLinkFailRx;
    //theStream << myIsSoftwareAutoNegEnabled;

    aTemp = myPortLacpState;
    theStream << aTemp;
    theStream << myPortAggregationField;
    theStream << myPortLacpPriority;
    theStream << myPartnerActiveFlag;
    theStream << myPartnerSystemID;
    theStream << myPartnerPortPriority;
    theStream << myPartnerOperationalKey;
    theStream << myPartnerPortState;
    theStream << myLagActorSystemID;
    theStream << myLagActorSystemPriority;
    theStream << myLagActorOperationalKey;
    theStream << myLagActorAdminKey;
    theStream << myLagPartnerSystemID;
    theStream << myLagPartnerSystemPriority;
    theStream << myLagPartnerOperationalKey;
    theStream << myLagPartnerAdminKey;

    //aTemp = myEthSfpXfpType;
    //theStream << aTemp;

    return theStream;

}

FC_Stream& MON_MacStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    uint32 aTemp = 0;

    MON_Object::ReadObjectBinary(theStream);

    theStream >> aTemp;
    myAutoNegStatus = (CT_TEL_MAC_AUTONEGSTATUS)aTemp;
    theStream >> aTemp;
    myAutoNegRmtSignal = (CT_TEL_DETECTED)aTemp;
    theStream >> myOperRate;
    theStream >> aTemp;
    myOperDuplex = (CT_TEL_MAC_DUPLEX_MODE)aTemp;
    theStream >> aTemp;
    myOperFlowCtrl = (CT_TEL_MAC_FLOWCTRL)aTemp;
    theStream >> myOperAutoNeg;
    theStream >> myLinkFailRx;
    //theStream >> myIsSoftwareAutoNegEnabled;

    theStream >> aTemp;
    myPortLacpState = (CT_TEL_LacpPortState) aTemp;
    theStream >> myPortAggregationField;
    theStream >> myPortLacpPriority;
    theStream >> myPartnerActiveFlag;
    theStream >> myPartnerSystemID;
    theStream >> myPartnerPortPriority;
    theStream >> myPartnerOperationalKey;
    theStream >> myPartnerPortState;
    theStream >> myLagActorSystemID;
    theStream >> myLagActorSystemPriority;
    theStream >> myLagActorOperationalKey;
    theStream >> myLagActorAdminKey;
    theStream >> myLagPartnerSystemID;
    theStream >> myLagPartnerSystemPriority;
    theStream >> myLagPartnerOperationalKey;
    theStream >> myLagPartnerAdminKey;

    //theStream >> aTemp;
    //myEthSfpXfpType = (CT_ETH_SFP_XFP_TYPE) aTemp;

    return theStream;

}

void MON_MacStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "MAC    - Auto Neg Status                  = " << DISPLAY_MAC_AUTONEGSTATUS(myAutoNegStatus) << endl;
    theStream   << "MAC    - Auto Neg Remote Signal Detected  = " << DISPLAY_DETECTED(myAutoNegRmtSignal) << endl;
    theStream   << "MAC    - Operational Ethernet Rate (daHz) = " << myOperRate << endl;
    theStream   << "MAC    - Operational Duplex Mode          = " << DISPLAY_MAC_DUPLEX_MODE(myOperDuplex) << endl;
    theStream   << "MAC    - Operational Flow Control Mode    = " << DISPLAY_MAC_FLOWCTRL(myOperFlowCtrl) << endl;
    theStream   << "MAC    - Operational Auto-Neg Mode        = " << DISPLAY_BOOL(myOperAutoNeg) << endl;
    theStream   << "MAC    - Link Fail Rx                     = " << DISPLAY_BOOL(myLinkFailRx) << endl;
    theStream   << "MAC    - Ethernet Sfp Xfp Type            = " << DISPLAY_ETH_SFP_XFP_TYPE(myEthSfpXfpType)          << "\n";
    theStream   << "MAC    - Is Software Auto Neg Enabled     = " << DISPLAY_BOOL(myIsSoftwareAutoNegEnabled) << endl;
    theStream   << "MAC    - LACP Port State                  = " << DISPLAY_LACP_PORT_STATE(myPortLacpState)          << "\n";
    theStream   << "MAC    - LACP Aggregation                 = " << DisplayAggreField(myPortAggregationField)          << "\n";
    theStream   << "MAC    - LACP Port Priority               = " << dec << (int)myPortLacpPriority                 << "\n";
    theStream   << "MAC    - Partner Active Flag              = " << DISPLAY_BOOL(myPartnerActiveFlag)                 << "\n";
    theStream   << "MAC    - Partner System ID                = " << myPartnerSystemID.DisplayAddr()      << "\n";
    theStream   << "MAC    - Partner Port Priority            = " << dec << (int)myPartnerPortPriority        << "\n";
    theStream   << "MAC    - Partner Operational Key          = " << myPartnerOperationalKey        << "\n";
    theStream   << "MAC    - Partner Port State               = 0x" << hex << static_cast<uint32>(myPartnerPortState) << dec   << "\n";
    theStream   << "MAC    - Lag Actor System ID              = " << myLagActorSystemID.DisplayAddr()      << "\n";
    theStream   << "MAC    - Lag Actor System Priority        = " << dec << (int)myLagActorSystemPriority        << "\n";
    theStream   << "MAC    - Lag Actor Operational Key        = " << myLagActorOperationalKey        << "\n";
    theStream   << "MAC    - Lag Actor Admin Key              = " << dec << (int)myLagActorAdminKey        << "\n";
    theStream   << "MAC    - Lag Partner System ID            = " << myLagPartnerSystemID.DisplayAddr()      << "\n";
    theStream   << "MAC    - Lag Partner System Priority      = " << dec << (int)myLagPartnerSystemPriority        << "\n";
    theStream   << "MAC    - Lag Partner Operational Key      = " << myLagPartnerOperationalKey        << "\n";
    theStream   << "MAC    - Lag Partner Admin Key            = " << dec << (int)myLagPartnerAdminKey        << "\n";
}
