//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Tcm.h"
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>

#include <TsPii/TSPII_DwIf.h>
#include <TsPii/TSPII_SubApplication.h>


CFG_Tcm::CFG_Tcm(uint32 theIndex):
    CFG_Object(theIndex),
    mySdInterval(0),
    mySdThreshold(0),
    myTraceInUse(false),
    mySentTracePtr(NULL),
    myPMProfileId(CT_PM_PT_99),
    myTcmMode(CT_TCM_MODE_NONE),
    myProvisionningActive(false),
    myServerID(CT_DEFAULT_ODU_SERVER_ID),
    myTcmId(CT_DEFAULT_ODU_ID),
    myTcmDelayEnabled(false),
    myOduBbIndex(0),
    mySdBerLevel(CT_TEL_INFINITE_BER),
    myChannelIndexInAID(CT_ODU_CHANNEL_INDEX_DEFAULT),
    myTcmOrder(CT_TCM_Order_END),
    myTcmLTCActEnabled(false)
{
}

CFG_Tcm::~CFG_Tcm(void)
{
}

bool CFG_Tcm::SetTcmIdentifier(CT_ODU_Identifier theTcmId)
{
    if (myTcmId != theTcmId)
    {
        myTcmId = theTcmId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_Identifier CFG_Tcm::GetTcmIdentifier() const
{
    return myTcmId;
}

bool CFG_Tcm::SetSentTrace(const CT_G709Trace& theSentTrace)
{
    bool hasChanged = false;
    if (mySentTracePtr == NULL) 
    {
        mySentTracePtr = new CT_G709Trace(CT_TEL_STANDARD_TRACE); 
        hasChanged = true;
    }
    hasChanged = hasChanged || (!(*mySentTracePtr == theSentTrace));
    *mySentTracePtr = theSentTrace;
    myTraceInUse = true;
    return hasChanged;
}

bool CFG_Tcm::DeleteSentTrace()
{
    bool hasChanged = false;
    if (mySentTracePtr != NULL) 
    {
        delete mySentTracePtr;
        mySentTracePtr = NULL;
        hasChanged = true;
    }

    myTraceInUse = false;
    return hasChanged;
}

CT_G709Trace & CFG_Tcm::GetSentTrace() const
{
    if (mySentTracePtr != NULL) 
    {
        return(*mySentTracePtr);
    }
    else
    {
        return(CT_G709StandardDefaultTrace::GetInstance());
    }
}

// Add in Monitoring Configurations also
bool CFG_Tcm::SetBerSdInterval(uint16 theSdInterval)
{
    bool hasChanged = (mySdInterval != theSdInterval);
    mySdInterval  = theSdInterval;    
    return hasChanged;
}

uint16 CFG_Tcm::GetBerSdInterval() const
{
    return mySdInterval;
}

bool CFG_Tcm::SetBerSdThreshold(uint32 theSdThreshold)
{
    bool hasChanged = (mySdThreshold != theSdThreshold);
    mySdThreshold = theSdThreshold;
    return hasChanged;
}

uint32 CFG_Tcm::GetBerSdThreshold() const
{
    return mySdThreshold;
}

bool CFG_Tcm::SetPMProfileId(CT_PMProfileTableId thePMPFId)
{
    bool hasChanged = (myPMProfileId != thePMPFId);
    myPMProfileId = thePMPFId;
    return hasChanged;
}

CT_PMProfileTableId CFG_Tcm::GetPMProfileId() const
{
    return myPMProfileId;
}

bool CFG_Tcm::SetTcmMode(CT_TCM_Mode theTcmMode)
{
    bool hasChanged = (myTcmMode != theTcmMode);
    myTcmMode = theTcmMode;
    return hasChanged;
}

CT_TCM_Mode CFG_Tcm::GetTcmMode() const
{
    return myTcmMode;
}

bool CFG_Tcm::SetOduBbIndex(bbindex_t theOduBbIndex)
{
    bool hasChanged = (myOduBbIndex != theOduBbIndex);
    myOduBbIndex = theOduBbIndex;
    return hasChanged;
}

bbindex_t CFG_Tcm::GetOduBbIndex() const
{
    return myOduBbIndex;
}

bool CFG_Tcm::SetProvisionningActive(bool theProvisionningActive)
{
    if (myProvisionningActive != theProvisionningActive)
    {
        myProvisionningActive = theProvisionningActive;
        return true;
    }
    else
    {
        return false;
    }

}

bool CFG_Tcm::GetProvisionningActive() const
{
    return myProvisionningActive;
}

bool CFG_Tcm::SetServerID(CT_ODU_ServerID theServerId)
{
    if (myServerID != theServerId)
    {
        myServerID = theServerId;
        return true;
    }
    else
    {
        return false;
    }
}

CT_ODU_ServerID CFG_Tcm::GetServerID() const 
{
    return myServerID;
}

bool CFG_Tcm::SetChannelIndexInAID(uint8 theChannelIndexInAID)
{
    bool hasChanged = (theChannelIndexInAID != myChannelIndexInAID);
    myChannelIndexInAID = theChannelIndexInAID;
    return hasChanged;
}

uint8 CFG_Tcm::GetChannelIndexInAID() const
{
    return myChannelIndexInAID;
}

bool CFG_Tcm::SetTcmDelayEnabled(bool theEnabled)
{
    if (myTcmDelayEnabled != theEnabled)
    {
        myTcmDelayEnabled = theEnabled;
        return true;
    }
    else
    {
        return false;
    }

}

bool CFG_Tcm::GetTcmDelayEnabled() const
{
    return myTcmDelayEnabled;
}

bool CFG_Tcm::SetTcmOrder(CT_TCM_Order theTcmOrder)
{
    bool hasChanged = (myTcmOrder != theTcmOrder);
    myTcmOrder = theTcmOrder;
    return hasChanged;
}

CT_TCM_Order CFG_Tcm::GetTcmOrder() const
{
    return myTcmOrder;
}

bool CFG_Tcm::SetTcmLTCActEnabled(bool theEnabled)
{
    if (myTcmLTCActEnabled != theEnabled)
    {
        myTcmLTCActEnabled = theEnabled;
        return true;
    }
    else
    {
        return false;
    }

}

bool CFG_Tcm::GetTcmLTCActEnabled() const
{
    return myTcmLTCActEnabled;
}

void CFG_Tcm::Reset(void)
{   
    myOduBbIndex  = 0;
    mySdBerLevel  = CT_TEL_INFINITE_BER;
    mySdInterval  = 0;
    mySdThreshold = 0;
    // Note: DeleteSentTrace() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //mySentTracePtr   = NULL;
    DeleteSentTrace();
    myPMProfileId = CT_PM_PT_99;
    myTcmMode = CT_TCM_MODE_NONE;
    myProvisionningActive = false;
    myServerID = CT_DEFAULT_ODU_SERVER_ID;
    myTcmId = CT_DEFAULT_ODU_ID;
    myChannelIndexInAID = CT_ODU_CHANNEL_INDEX_DEFAULT;    
    myTcmDelayEnabled = false;
    myTcmOrder = CT_TCM_Order_END;
    myTcmLTCActEnabled = false;
}

// For Display
ostream& CFG_Tcm::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    uint32 tcmId = myTcmId.GetIdValue();
    theStream << FC_InsertVar(tcmId);

    uint8 aTcmMode = (uint8) myTcmMode;
    theStream   << FC_InsertVar(aTcmMode);

    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        theStream    << FC_InsertVar(aTrace);
    }

    theStream   << FC_InsertVar(mySdInterval);
    theStream   << FC_InsertVar(mySdThreshold);

    uint8 aPMProfileId = (uint8) myPMProfileId;
    theStream   << FC_InsertVar(aPMProfileId);

    theStream   << FC_InsertVar(myProvisionningActive);

    uint32 anIdentifier = myServerID.GetIdValue(); 
    theStream   << FC_InsertVar(anIdentifier);

    theStream   << FC_InsertVar(myChannelIndexInAID);

    theStream   << FC_InsertVar(myTcmDelayEnabled);
    theStream   << FC_InsertVar(myOduBbIndex);

    uint8 aTcmOrder = (uint8) myTcmOrder;
    theStream   << FC_InsertVar(aTcmOrder);

    theStream   << FC_InsertVar(myTcmLTCActEnabled);

    return theStream;
}

// For Display
istream& CFG_Tcm::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    uint32 tcmId;
    theStream >> FC_ExtractVar(tcmId);
    myTcmId.SetValue(tcmId);

    uint8 aTcmMode;
    theStream   >> FC_ExtractVar(aTcmMode);
    myTcmMode = (CT_TCM_Mode) aTcmMode;

    theStream   >> FC_ExtractVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream   >> FC_ExtractVar(aTrace);
        SetSentTrace(aTrace);
    }
    else
    {
        DeleteSentTrace();
    }

    theStream   >> FC_ExtractVar(mySdInterval);
    theStream   >> FC_ExtractVar(mySdThreshold);

    uint8 aPMProfileId = 0;
    theStream   >> FC_ExtractVar(aPMProfileId);
    myPMProfileId = (CT_PMProfileTableId) aPMProfileId;
    
    theStream   >> FC_ExtractVar(myProvisionningActive);

    uint32 anIdentifier;
    theStream   >> FC_ExtractVar(anIdentifier);
    myServerID = (CT_ODU_ServerID) anIdentifier;

    theStream   >> FC_ExtractVar(myChannelIndexInAID);

    theStream   >> FC_ExtractVar(myTcmDelayEnabled);
    theStream   >> FC_ExtractVar(myOduBbIndex);

    uint8 aTcmOrder;
    theStream   >> FC_ExtractVar(aTcmOrder);
    myTcmOrder = (CT_TCM_Order) aTcmOrder;

    theStream   >> FC_ExtractVar(myTcmLTCActEnabled);
    
    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Tcm::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    uint32 tcmId = myTcmId.GetIdValue();
    theStream << tcmId;

    uint8 aTcmMode = (uint8) myTcmMode;
    theStream   << aTcmMode;

    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        theStream    << aTrace;
    }

    theStream   << mySdInterval;
    theStream   << mySdThreshold;

    uint8 aPMProfileId = (uint8) myPMProfileId;
    theStream   << aPMProfileId;

    theStream   << myProvisionningActive;

    uint32 anIdentifier = myServerID.GetIdValue(); 
    theStream   << anIdentifier;

    theStream   << myChannelIndexInAID;

    theStream   << myTcmDelayEnabled;
    theStream   << myOduBbIndex;

    uint8 aTcmOrder = (uint8) myTcmOrder;
    theStream   << aTcmOrder;

    theStream   << myTcmLTCActEnabled;

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Tcm::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    uint32 tcmId;
    theStream >> tcmId;
    myTcmId.SetValue(tcmId);

    uint8 aTcmMode;
    theStream   >> aTcmMode;
    myTcmMode = (CT_TCM_Mode) aTcmMode;

    theStream   >> myTraceInUse;
    if (myTraceInUse) 
    {
        // CT_G709Trace aTrace();
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream    >> aTrace;
        SetSentTrace(aTrace);
    }
    else
    {
        DeleteSentTrace();
    }
    
    theStream >> mySdInterval;
    theStream >> mySdThreshold;

    uint8 aPMProfileId = 0;
    theStream   >> aPMProfileId;
    myPMProfileId = (CT_PMProfileTableId)aPMProfileId;

    theStream   >> myProvisionningActive;

    uint32 anIdentifier;
    theStream   >> anIdentifier;
    myServerID = (CT_ODU_ServerID) anIdentifier;

    theStream   >> myChannelIndexInAID;

    theStream   >> myTcmDelayEnabled;
    theStream   >> myOduBbIndex;

    uint8 aTcmOrder;
    theStream   >> aTcmOrder;
    myTcmOrder = (CT_TCM_Order) aTcmOrder;

    theStream   >> myTcmLTCActEnabled;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Tcm::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto TCMERROR;
    
    if (strlen(argv[0])>32) 
        goto TCMERROR;

    //Copy arguments
    strcpy(aParam, argv[0]); 

    if(!strcmp(aParam,"tcmid"))
    {
        myTcmId.SetValue((atol(argv[1])));
    }
    else if(!strncmp(aParam,"hextcm",6))
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: odu id must be a hex number" << endl;
            goto TCMERROR;
        }
        uint32 numlong = uint32(strtoul(argv[1], NULL, 0));
        SetTcmIdentifier(CT_ODU_Identifier(numlong));
    }
    else if(!strncmp(aParam,"serv",4))
    {  
        if (!isdigit(argv[1][0]))
        {
            fc_cout << "Error: server id must be a numeric number" << endl;
            goto TCMERROR;
        }
        SetServerID(CT_ODU_ServerID(atol(argv[1])));
    }
    else if(!strncmp(aParam,"hexser",6))
    {
        if (!isxdigit(argv[1][0]))
        {
            fc_cout << "Error: server id must be a hex number" << endl;
            goto TCMERROR;
        }
        SetServerID(CT_ODU_ServerID(strtoul(argv[1], NULL, 0)));
    }
    else if (!strcmp(aParam,"mode"))
    {
        SetTcmMode(CFG_STRING_TO_TCM_MODE(argv[1]));        
    }
    else if (!strcmp(aParam,"trace"))
    {
        if (argc != 4) goto TCMERROR;
        string aSapi(argv[1]);
        string aDapi(argv[2]);
        string aMessage(argv[3]);

        CT_G709Trace aTrace(aSapi,aDapi,aMessage);
        SetSentTrace(aTrace);
    }
    else if (!strncmp(aParam,"rmtr",4))
    {
        if(argv[1][0]=='e')
        {
            DeleteSentTrace();
        }
    }
    else if (!strcmp(argv[0],"BerSdInterval"))
    {
        SetBerSdInterval(CFG_STRING_TO_BER(argv[1]));
    }
    else if (!strcmp(argv[0],"BerSdThreshold"))
    {
        SetBerSdThreshold(CFG_STRING_TO_BER(argv[1]));
    }
    else if (!strncmp(aParam,"prov",4))
    {
        SetProvisionningActive(argv[1][0]=='e');
    }
    else if(!strncmp(aParam,"chan", 4))
    {
        SetChannelIndexInAID(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"del",3))
    {
        SetTcmDelayEnabled(argv[1][0]=='e');
    }
    else if (!strcmp(aParam,"order"))
    {
        SetTcmOrder(CT_TCM_Order(atoi(argv[1])));        
    }
    else if (!strncmp(aParam,"ltcact",6))
    {
        SetTcmLTCActEnabled(argv[1][0]=='e');
    }
    else
    {
        goto TCMERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

TCMERROR:
    {
        fc_cout << "tcm <tcmid>         <uint32 Tcm ID definition> " << endl;
        fc_cout << "tcm <hextcm>        <hex 0x Tcm ID definition> " << endl;
        fc_cout << "tcm <serv-erid>     <uint16 Server ID definition> " << endl;
        fc_cout << "tcm <hexserv>       <hex 0x Server ID definition> " << endl;
        fc_cout << "tcm <mode>  <src|snk|src_snk|src_snk_nim|snk_nim|unknown> " << endl;
        fc_cout << "tcm <prov-ision>    <e-nable|d-isable> " << endl;        
        fc_cout << "tcm <del-ay source> <e-nable|d-isable> " << endl;        
        fc_cout << "tcm <sdber> <SdInterval> <SdThreshold> " << endl;
        fc_cout << "tcm <BerSdInterval>  <Numeric value range 2 .. 10 inclusive | 0 for NO_BER> " << endl;
        fc_cout << "tcm <BerSdThreshold> <Numeric value range 1 .. 329492 inclusive> " << endl;
        fc_cout << "tcm <rmtr-ace> <e-nable|d-isable> " << endl;
        fc_cout << "tcm <chan-idx> < Value between 0 and 32 > " << endl;
        fc_cout << "tcm trace <15-byte sapi> <15-byte dapi> <28-byte message> " << endl;
        fc_cout << "tcm <order>           <uint8 order> " << endl;
        fc_cout << "tcm <ltcact>          <e-nable|d-isable> " << endl;

        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Tcm::Display( FC_Stream& theStream )
{
    theStream   << "TCM      - Tcm ID               [tcmid]     = 0x " << hex << myTcmId.GetIdValue() << myTcmId.DisplayOduIdentifier() << dec << endl;
    if (myTcmId != CT_DEFAULT_ODU_ID) 
    {  
        // Note: add one because TSPII is one based
        uint16 aTspiiDwInstance = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(myTcmId.GetIdValue()) + 1;
        theStream   << "    -----> Odu tspii instance (test menu)   = " << dec << aTspiiDwInstance << endl;
    }
    theStream   << "TCM      - Server ID            [serv]      = 0x " << hex << myServerID.GetIdValue() << myServerID.DisplayServerID() << dec << endl;

    theStream   << "TCM      - TCM Mode             [mode]      = " << DISPLAY_TCM_MODE(myTcmMode) << endl;
    theStream   << "TCM      - TCM Delay Source     [delay]     = " << DISPLAY_BOOL(myTcmDelayEnabled) << endl;
    theStream   << "TCM      - TCM Order            [order]     = " << dec << (uint32)myTcmOrder << endl;
    theStream   << "TCM      - SD BER Threshold     [interval]  = " << mySdInterval << endl;
    theStream   << "TCM      - SD BER Threshold     [threshold] = " << mySdThreshold << endl;
    theStream   << "TCM      - Channel Index        [chanidx]   = " << dec << (uint32)myChannelIndexInAID << dec << endl;
    theStream   << "TCM      - Trace In Use                     = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "TCM      - LTC act                          = " << DISPLAY_BOOL(myTcmLTCActEnabled) << endl;
    theStream   << "TCM      - Transmitted Trace    [trace]     = " ;
    if (mySentTracePtr != NULL) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        aTrace.Display(theStream);
    }
    else
    {
        theStream   << endl;
    }
}
