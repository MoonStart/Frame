//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_GfpAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_GfpAutomatic::CFG_GfpAutomatic(uint32 theIndex):
    myForce10BError(false),
    myForceGenericLayerFail(false),
    myClientMgmtFrameType(CT_TEL_GFP_CMGMT_NONE),
	myForceIdle(false),
    myForceLinkFailTx(false),
    myForceRemoteFault(CT_GBE_REMOTE_OK),
    myOneWayGbe(false),
    myMacAutoNegEnabled(false),
    myPortIndex(CFG_GFP_DEFAULT_PORT_INDEX),
    CFG_Object(theIndex)    
{
}

CFG_GfpAutomatic::~CFG_GfpAutomatic()
{
}


bool CFG_GfpAutomatic::SetForce10BError(bool theForce10BError)
{
    bool hasChanged = false;
    if(myForce10BError != theForce10BError)
    {
        myForce10BError = theForce10BError;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_GfpAutomatic::GetForce10BError() const
{
    return myForce10BError;
}

bool CFG_GfpAutomatic::SetForceGenericLayerFail(bool theForceGenericLayerFail)
{
    bool hasChanged = false;
    if(myForceGenericLayerFail != theForceGenericLayerFail)
    {
        myForceGenericLayerFail = theForceGenericLayerFail;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_GfpAutomatic::GetForceGenericLayerFail() const
{
    return myForceGenericLayerFail;
}

void CFG_GfpAutomatic::SetForceClientMgmtFrame(CT_TEL_GfpClientMgmt theClientMgmtFrameType)
{
    myClientMgmtFrameType = theClientMgmtFrameType;
}

CT_TEL_GfpClientMgmt CFG_GfpAutomatic::GetForceClientMgmtFrame() const
{
    return myClientMgmtFrameType;
}

////////////////////////////////////////////////////////////////////////////////
bool CFG_GfpAutomatic::SetForceIdle(bool theForceMode)
{
    bool hasChanged = false;
    if (myForceIdle != theForceMode)
    {
        myForceIdle = theForceMode;
        hasChanged = true;
    }
    return hasChanged;
}

////////////////////////////////////////////////////////////////////////////////
bool CFG_GfpAutomatic::GetForceIdle() const
{
    return(myForceIdle);
}

bool CFG_GfpAutomatic::SetForceLinkFailTx(bool theForceLinkFailTx)
{
    bool hasChanged = false;
    if (myForceLinkFailTx != theForceLinkFailTx)
    {
        myForceLinkFailTx = theForceLinkFailTx;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_GfpAutomatic::GetForceLinkFailTx() const
{
    return(myForceLinkFailTx);
}

bool CFG_GfpAutomatic::SetForceRemoteFault(CT_GBE_REMOTE_FAULT theForceRemoteFault)
{
    bool hasChanged = false;
    if (myForceRemoteFault != theForceRemoteFault)
    {
        myForceRemoteFault = theForceRemoteFault;
        hasChanged = true;
    }
    return hasChanged;
}

CT_GBE_REMOTE_FAULT CFG_GfpAutomatic::GetForceRemoteFault() const
{
    return(myForceRemoteFault);
}

bool CFG_GfpAutomatic::SetOneWayGbe(bool theOneWayGbe)
{
    bool hasChanged = false;
    if (myOneWayGbe != theOneWayGbe)
    {
        myOneWayGbe = theOneWayGbe;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_GfpAutomatic::GetOneWayGbe() const
{
    return(myOneWayGbe);
}


bool CFG_GfpAutomatic::SetMacAutoNegEnabled(bool theMacAutoNegEnabled)
{
    bool hasChanged = false;
    if (myMacAutoNegEnabled != theMacAutoNegEnabled)
    {
        myMacAutoNegEnabled = theMacAutoNegEnabled;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_GfpAutomatic::GetMacAutoNegEnabled() const
{
    return(myMacAutoNegEnabled);
}


bool  CFG_GfpAutomatic::SetPortIndex(uint8 theIndex)
{
    bool hasChanged = false;
    if (myPortIndex != theIndex)
    {
        myPortIndex = theIndex;
        hasChanged = true;
    }
    return hasChanged;
}

uint8 CFG_GfpAutomatic::GetPortIndex() const
{
    return(myPortIndex);
}



void CFG_GfpAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myForce10BError = false;
    myForceGenericLayerFail = false;
    myClientMgmtFrameType = CT_TEL_GFP_CMGMT_NONE;
	myForceIdle = false;
    myForceLinkFailTx = false;
    myForceRemoteFault = CT_GBE_REMOTE_OK;
    myOneWayGbe = false;
    myMacAutoNegEnabled = false;
    myPortIndex = CFG_GFP_DEFAULT_PORT_INDEX;
}

ostream& CFG_GfpAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForce10BError);
    theStream   << FC_InsertVar(myForceGenericLayerFail);
    uint32 aClientMgmtFrameType = (uint32) myClientMgmtFrameType;
    theStream   << FC_InsertVar(aClientMgmtFrameType);
	theStream   << FC_InsertVar(myForceIdle);
    theStream   << FC_InsertVar(myForceLinkFailTx);
    uint32 aForceRemoteFault = (uint32) myForceRemoteFault;    
    theStream   << FC_InsertVar(aForceRemoteFault);
    theStream   << FC_InsertVar(myOneWayGbe);   
    theStream   << FC_InsertVar(myMacAutoNegEnabled);   
    theStream   << FC_InsertVar(myPortIndex);   
    return theStream;
}

istream& CFG_GfpAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForce10BError);
    theStream   >> FC_ExtractVar(myForceGenericLayerFail);
    uint32 aClientMgmtFrameType = 0;
    theStream   >> FC_ExtractVar(aClientMgmtFrameType);
    myClientMgmtFrameType = (CT_TEL_GfpClientMgmt) aClientMgmtFrameType;
	theStream   >> FC_ExtractVar(myForceIdle);
    theStream   >> FC_ExtractVar(myForceLinkFailTx);
    uint32 aForceRemoteFault = 0;
    theStream   >> FC_ExtractVar(aForceRemoteFault);
    myForceRemoteFault = (CT_GBE_REMOTE_FAULT) aForceRemoteFault; 
    theStream   >> FC_ExtractVar(myOneWayGbe);
    theStream   >> FC_ExtractVar(myMacAutoNegEnabled);
    theStream   >> FC_ExtractVar(myPortIndex);
    return theStream;

}

FC_Stream& CFG_GfpAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForce10BError;
    theStream   << myForceGenericLayerFail;
    theStream   << (uint32) myClientMgmtFrameType;
	theStream   << myForceIdle;
    theStream   << myForceLinkFailTx;
    theStream   << (uint32) myForceRemoteFault;
    theStream   << myOneWayGbe;
    theStream   << myMacAutoNegEnabled;
    theStream   << myPortIndex;
    return theStream;
}

FC_Stream& CFG_GfpAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForce10BError;
    theStream   >> myForceGenericLayerFail;
    uint32 aClientMgmtFrameType = 0;
    theStream   >> aClientMgmtFrameType;
    myClientMgmtFrameType = (CT_TEL_GfpClientMgmt) aClientMgmtFrameType;
	theStream   >> myForceIdle;
    theStream   >> myForceLinkFailTx;
    uint32 aForceRemoteFault = 0;
    theStream   >> aForceRemoteFault;  
    myForceRemoteFault = (CT_GBE_REMOTE_FAULT) aForceRemoteFault; 
    theStream   >> myOneWayGbe;
    theStream   >> myMacAutoNegEnabled;
    theStream   >> myPortIndex;
    return theStream;
}

void CFG_GfpAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "GFP AUTO  - Force Ill 8B/10B Codes              = " << DISPLAY_BOOL(myForce10BError) << endl;
    theStream   << "GFP AUTO  - Force Generic Layer Fail            = " << DISPLAY_BOOL(myForceGenericLayerFail) << endl;
    theStream   << "GFP AUTO  - Client Mgmt Frame Type              = ";
    theStream   << DISPLAY_GFP_CMGMT(myClientMgmtFrameType) << endl;
	theStream   << "GFP AUTO  - Force Idle Codes                    = " << DISPLAY_BOOL(myForceIdle) << endl;
    theStream   << "GFP AUTO  - Force Remote Fault                  = ";
    theStream   << DISPLAY_GBE_REMOTE_FAULT(myForceRemoteFault) << endl;
    theStream   << "GFP AUTO  - Force Link Fail Tx                  = " << DISPLAY_BOOL(myForceLinkFailTx) << endl; 
    theStream   << "GFP AUTO  - One Way Gbe                         = " << DISPLAY_BOOL(myOneWayGbe) << endl; 
    theStream   << "GFP AUTO  - Sotware Auto Neg (based on Xfp/Sfp) = " << DISPLAY_BOOL(myMacAutoNegEnabled) << endl; 
    theStream   << "GFP AUTO  - Port Index (for pooled Gfp)         = " << uint16(myPortIndex) << endl; 
}
