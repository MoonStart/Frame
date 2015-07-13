// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OptConfig.h"
#include <BaseClass/FC_TextStream.h>

MON_OptConfig::MON_OptConfig(uint32 theIndex):
    MON_Config(theIndex),
    mySdPwrThreshold(TRAFFIC_DEFAULT_POWER),
    myInternalUpperLayerFailed(false),
    myUpperLayerFailed(false),
    myLayerLocked(false),
    myOppositeSideBitMask(0),
    myOppositeSideIsPooled(false),
    myOppositeSideServerID(CT_DEFAULT_ODU_SERVER_ID),
    myIgnoreOppositeSide(false),
    myOtnOppositeSideServerID(CT_DEFAULT_ODU_SERVER_ID),
    myEqptLocked(false),
    myDefectFailLayerBitMask(MON_FAILLAYER_OPT_DEFAULT_BITMASK)
{
}

MON_OptConfig::~MON_OptConfig(void )
{
}

//
bool MON_OptConfig::SetInternalUpperLayerFailed(bool theState)
{
	bool hasChanged = false;
	if (myInternalUpperLayerFailed != theState)
	{
		myInternalUpperLayerFailed = theState;
		hasChanged = true;
	}
	return hasChanged;
}

bool MON_OptConfig::GetInternalUpperLayerFailed() const
{
	return myInternalUpperLayerFailed;
}


bool MON_OptConfig::SetUpperLayerFailed(bool theState)
{
    bool hasChanged = false;
    if (myUpperLayerFailed != theState)
    {
        myUpperLayerFailed = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OptConfig::GetUpperLayerFailed() const
{
    return myUpperLayerFailed;
}


bool MON_OptConfig::SetLayerLocked(bool theState)
{
    bool hasChanged = false;
    if (myLayerLocked != theState)
    {
        myLayerLocked = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OptConfig::GetLayerLocked() const
{
    return myLayerLocked;
}

bool MON_OptConfig::SetEqptLocked(bool theState)
{
    bool hasChanged = false;
    if (myEqptLocked != theState)
    {
        myEqptLocked = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OptConfig::GetEqptLocked() const
{
    return myEqptLocked;
}

void MON_OptConfig::ClearOppositeSideBitMask()
{
    myOppositeSideBitMask = 0;
    return;
}

void MON_OptConfig::SetOppositeSidePosition(uint16 thePosition)
{
    uint16 aSetMask = 1;
    aSetMask = aSetMask << thePosition;
    myOppositeSideBitMask |= aSetMask;
    return;
}

uint16 MON_OptConfig::GetOppositeSideBitMask() const
{
    return(myOppositeSideBitMask);
}

void MON_OptConfig::ResetOppositeSidePosition(uint16 thePosition)
{
    uint16 aSetMask = 1;
    aSetMask = aSetMask << thePosition;
    myOppositeSideBitMask &= ~aSetMask;
    return;
}

bool MON_OptConfig::IsOppositeSidePositionSet(uint16 theBitMask, uint16 thePosition) const
{
    uint16 aSetMask = 1;
    aSetMask = aSetMask << thePosition;
    return((theBitMask & aSetMask) == aSetMask);
}


bool MON_OptConfig::SetOppositeSideIsPooled(bool theState)
{
    bool hasChanged = false;
    if (myOppositeSideIsPooled != theState)
    {
        myOppositeSideIsPooled = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OptConfig::GetOppositeSideIsPooled() const
{
    return myOppositeSideIsPooled;
}


bool MON_OptConfig::SetOppositeSideServerID(CT_ODU_ServerID theServerID)
{
    bool hasChanged = false;
    if (myOppositeSideServerID != theServerID)
    {
        myOppositeSideServerID = theServerID;
        hasChanged = true;
    }
    return hasChanged;
}

CT_ODU_ServerID MON_OptConfig::GetOppositeSideServerID() const
{
    return myOppositeSideServerID;
}

bool MON_OptConfig::SetOtnOppositeSideServerID(CT_ODU_ServerID theOtnServerID)
{
    bool hasChanged = false;
    if (myOtnOppositeSideServerID != theOtnServerID)
    {
        myOtnOppositeSideServerID = theOtnServerID;
        hasChanged = true;
    }
    return hasChanged;
}

CT_ODU_ServerID MON_OptConfig::GetOtnOppositeSideServerID() const
{
    return myOtnOppositeSideServerID;
}

bool MON_OptConfig::SetIgnoreOppositeSide(bool theState)
{
    bool hasChanged = false;
    if (myIgnoreOppositeSide != theState)
    {
        myIgnoreOppositeSide = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OptConfig::GetIgnoreOppositeSide() const
{
    return myIgnoreOppositeSide;
}

bool MON_OptConfig::SetLosFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLosFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_OPTLOS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_OPTLOS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OptConfig::GetLosFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OPTLOS_BITMASK) == 0 ? false : true;
}

uint16 MON_OptConfig::GetFailLayerBitMask() const
{
    return myDefectFailLayerBitMask;
}

bool MON_OptConfig::SetSdPwrThreshold(CT_TEL_mBm theSdPwrThreshold)
{
    mySdPwrThreshold = theSdPwrThreshold;

    return true;
}

CT_TEL_mBm MON_OptConfig::GetSdPwrThreshold() const
{
    return mySdPwrThreshold;
}


void MON_OptConfig::Reset()
{
    mySdPwrThreshold = TRAFFIC_DEFAULT_POWER,
    myInternalUpperLayerFailed = false;
    myUpperLayerFailed = false;
    myLayerLocked = false;
    myOppositeSideBitMask = 0;
    myOppositeSideIsPooled = false;
    myOppositeSideServerID = CT_DEFAULT_ODU_SERVER_ID;
    myIgnoreOppositeSide = false;
    myOtnOppositeSideServerID = CT_DEFAULT_ODU_SERVER_ID;
    myEqptLocked = false;
    myDefectFailLayerBitMask = MON_FAILLAYER_OPT_DEFAULT_BITMASK;
    MON_Config::Reset();
}

ostream& MON_OptConfig::WriteObject(ostream& theStream)
{
    uint32 anIdentifier;

    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myIgnoreOppositeSide);
    theStream << FC_InsertVar(mySdPwrThreshold);
    theStream << FC_InsertVar(myInternalUpperLayerFailed);
    theStream << FC_InsertVar(myUpperLayerFailed);
    theStream << FC_InsertVar(myLayerLocked);
    theStream << FC_InsertVar(myOppositeSideBitMask);
    theStream << FC_InsertVar(myOppositeSideIsPooled);
    anIdentifier =  myOppositeSideServerID.GetIdValue(); 
    theStream << FC_InsertVar(anIdentifier);
    anIdentifier =  myOtnOppositeSideServerID.GetIdValue(); 
    theStream << FC_InsertVar(anIdentifier);
    theStream << FC_InsertVar(myEqptLocked);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);
	
    return theStream;
}

istream& MON_OptConfig::ReadObject(istream& theStream)
{
    uint32 anIdentifier;

    MON_Config::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myIgnoreOppositeSide);
    theStream   >> FC_ExtractVar(mySdPwrThreshold);
    theStream   >> FC_ExtractVar(myInternalUpperLayerFailed);
    theStream   >> FC_ExtractVar(myUpperLayerFailed);
    theStream   >> FC_ExtractVar(myLayerLocked);
    theStream   >> FC_ExtractVar(myOppositeSideBitMask);
    theStream   >> FC_ExtractVar(myOppositeSideIsPooled);
    theStream   >> FC_ExtractVar(anIdentifier);
    myOppositeSideServerID  =  (CT_ODU_ServerID) anIdentifier;
    theStream   >> FC_ExtractVar(anIdentifier);
    myOtnOppositeSideServerID  =  (CT_ODU_ServerID) anIdentifier;
    theStream   >> FC_ExtractVar(myEqptLocked);
    theStream   >> FC_ExtractVar(myDefectFailLayerBitMask);
	
    return theStream;
}

FC_Stream& MON_OptConfig::WriteObjectBinary(FC_Stream& theStream)
{
    uint32 anIdentifier;

    MON_Config::WriteObjectBinary(theStream);
    theStream   << myIgnoreOppositeSide;
    theStream   << mySdPwrThreshold;
    theStream   << myInternalUpperLayerFailed;
    theStream   << myUpperLayerFailed;
    theStream   << myLayerLocked;
    theStream   << myOppositeSideBitMask;
    theStream   << myOppositeSideIsPooled;
    anIdentifier = myOppositeSideServerID.GetIdValue(); 
    theStream   << anIdentifier;
    anIdentifier = myOtnOppositeSideServerID.GetIdValue(); 
    theStream   << anIdentifier;
    theStream   << myEqptLocked;
    theStream   << myDefectFailLayerBitMask;
	
    return theStream;
}

FC_Stream& MON_OptConfig::ReadObjectBinary(FC_Stream& theStream)
{
    uint32 anIdentifier;

    MON_Config::ReadObjectBinary(theStream);
    theStream   >> myIgnoreOppositeSide;
    theStream   >> mySdPwrThreshold;
    theStream   >> myInternalUpperLayerFailed;
    theStream   >> myUpperLayerFailed;
    theStream   >> myLayerLocked;
    theStream   >> myOppositeSideBitMask;
    theStream   >> myOppositeSideIsPooled;
    theStream   >> anIdentifier;
    myOppositeSideServerID  =  (CT_ODU_ServerID) anIdentifier;
    theStream   >> anIdentifier;
    myOtnOppositeSideServerID  =  (CT_ODU_ServerID) anIdentifier;
    theStream   >> myEqptLocked;
    theStream   >> myDefectFailLayerBitMask;

    return theStream;
}

void MON_OptConfig::Display( FC_Stream& theStream )
{
    uint32 anIdentifier=0;

    MON_Config::Display(theStream);
    theStream   << "OPT     - SDPWR Threshold (mBm)       [sdpwr]     = " << mySdPwrThreshold << endl;
    theStream   << "OPT     - Opposite Side Bit Mask      [setPos]    = 0x " << hex << myOppositeSideBitMask << dec << endl;
    theStream   << "OPT     - Opposite Side Is Pooled     [isPooled]  = " << DISPLAY_BOOL(myOppositeSideIsPooled) << endl;
    anIdentifier = myOppositeSideServerID.GetIdValue();
    theStream   << "OPT     - Opposite Side Server ID     [servID]    = 0x " << hex << anIdentifier << dec << myOppositeSideServerID.DisplayServerID() << endl;
    anIdentifier = myOtnOppositeSideServerID.GetIdValue();
    theStream   << "OPT     - OTN Opposite Side Server ID [servID]    = 0x " << hex << anIdentifier << dec << myOtnOppositeSideServerID.DisplayServerID() << endl;
    theStream   << "OPT     - Ignore Opposite Side        [ignoreOpp] = " << DISPLAY_BOOL(myIgnoreOppositeSide) << endl;
    theStream   << "OPT     - Forced Internal Layer Fail  [interfail] = " << DISPLAY_BOOL(myInternalUpperLayerFailed) << endl;
    theStream   << "OPT     - Forced Layer Fail           [layerfail] = " << DISPLAY_BOOL(myUpperLayerFailed) << endl;
    theStream   << "OPT     - Forced Layer Lock           [layerlock] = " << DISPLAY_BOOL(myLayerLocked) << endl;
    theStream   << "OPT     - Forced Eqpt Lock            [eqptlock]  = " << DISPLAY_BOOL(myEqptLocked) << endl;
    theStream   << "OPT     - LOS Fail Layer          [losfaillayer]  = " << DISPLAY_BOOL(GetLosFailLayer()) << endl;  
}

FC_CmdProcessor::STATUS MON_OptConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto OPTERROR;

    if (!strncmp(argv[0],"ign",3))
    {
        SetIgnoreOppositeSide(argv[1][0]=='e');
    }
    else if (!strncmp(argv[0],"sdp",3))
    {
        SetSdPwrThreshold(atoi(argv[1]));
    }
    else if (!strncmp(argv[0],"inter",5))
    {
        SetInternalUpperLayerFailed(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"layerfail"))
    {
        SetUpperLayerFailed(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"layerlock"))
    {
        SetLayerLocked(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"eqptlock"))
    {
        SetEqptLocked(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"losfaillayer"))
    {
        SetLosFailLayer(argv[1][0]=='e');
    }
    else if (!strncmp(argv[0],"set",3))
        {
        SetOppositeSidePosition(atoi(argv[1]));
    }
    else if (!strncmp(argv[0],"res",3))
        {
        ResetOppositeSidePosition(atoi(argv[1]));
    }
    else if (!strncmp(argv[0],"bit",3))
        {
        ClearOppositeSideBitMask();
    }
    else if (!strncmp(argv[0],"isP",3))
        {
        SetOppositeSideIsPooled(argv[1][0]=='e');
    }
    else if (!strncmp(argv[0],"serv",4))
    {
        SetOppositeSideServerID(CT_ODU_ServerID(atoi(argv[1])));
    }
    else if (!strncmp(argv[0],"otnserv",4))
    {
        SetOtnOppositeSideServerID(CT_ODU_ServerID(atoi(argv[1])));
    }
    else
        goto OPTERROR;

    return FC_CmdProcessor::E_SUCCESS;

OPTERROR:
    {
        fc_cout << "sdpwr <Signal Degrade Power (SDPWR) threshold in mBm> " << endl;
        fc_cout << "<setPos | resetPos> <Numeric value for bit position, range 0 .. 15 inclusive> " << endl;
        fc_cout << "<setPos | resetPos> <Numeric value for bit position, range 0 .. 15 inclusive> " << endl;
        fc_cout << "isP-ooled <e-nable|d-isable> " << endl;
        fc_cout << "serv-ID   <uint16 Server ID definition> " << endl;
        fc_cout << "otnserv-ID   <uint16 OTN Server ID definition> " << endl;
        fc_cout << "ign-oreOpp <e-nable|d-isable> " << endl;
        fc_cout << "bitsclear <e-nable|d-isable> " << endl;
        fc_cout << "inter-nallayerfail <e-nable|d-isable> " << endl;
        fc_cout << "layerfail <e-nable|d-isable> " << endl;
        fc_cout << "layerlock <e-nable|d-isable> " << endl;
        fc_cout << "eqptlock <e-nable|d-isable> " << endl;
        fc_cout << "losfaillayer <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

