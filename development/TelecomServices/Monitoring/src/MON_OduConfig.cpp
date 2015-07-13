//Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OduConfig.h"
#include <BaseClass/FC_TextStream.h>

MON_OduConfig::MON_OduConfig(uint32 theIndex):
    MON_Config(theIndex),
    myTraceInUse(false),
    myExpectedTracePtr(NULL),
    myTIMMonitoringEnable(false),
    myLayerFailOnTIM(false),
    myLayerLocked(false),
    myIsMonOduTerm(false),
    myIsConnectedAsSrc(false),
    myIsConnectedAsDst(false),
    myTIMCriteriaMode(CT_TEL_TIM_UNKNOWN),
    myDefectFailLayerBitMask(MON_FAILLAYER_ODU_DEFAULT_BITMASK)
{
}

MON_OduConfig::~MON_OduConfig()
{
}

void MON_OduConfig::Reset(void)
{
    MON_Config::Reset();
    // Note: DeleteExpectedTrace() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //myExpectedTracePtr   = NULL;
    DeleteExpectedTrace();
    myTIMMonitoringEnable = false;
    myLayerFailOnTIM = false;
    myLayerLocked = false;
    myIsMonOduTerm = false;
    myIsConnectedAsSrc = false;
    myIsConnectedAsDst = false;
    myTIMCriteriaMode =  CT_TEL_TIM_UNKNOWN;
    myDefectFailLayerBitMask = MON_FAILLAYER_ODU_DEFAULT_BITMASK;
}

bool MON_OduConfig::SetExpectedTrace(const CT_G709Trace& theExpTrace)
{

    bool hasChanged = false;
    if (myExpectedTracePtr == NULL) 
    {
        myExpectedTracePtr = new CT_G709Trace(CT_TEL_STANDARD_TRACE); 
        hasChanged = true;
    }
    hasChanged = hasChanged || (!(*myExpectedTracePtr == theExpTrace));
    *myExpectedTracePtr = theExpTrace;
    myTraceInUse = true;
    return hasChanged;
}

bool MON_OduConfig::DeleteExpectedTrace()
{
    bool hasChanged = false;
    if (myExpectedTracePtr != NULL) 
    {
        delete myExpectedTracePtr;
        myExpectedTracePtr = NULL;
        hasChanged = true;
    }

    myTraceInUse = false;
    return hasChanged;
}

CT_G709Trace & MON_OduConfig::GetExpectedTrace() const
{
    if (myExpectedTracePtr != NULL) 
    {
        return(*myExpectedTracePtr);
    }
    else
    {
        return(CT_G709StandardDefaultTrace::GetInstance());
    }
}


bool MON_OduConfig::SetTIMMonitoringEnable(bool theTIMMonitoringState)
{
    bool hasChanged = (theTIMMonitoringState != myTIMMonitoringEnable);
    // This setting has effect only in LTE termination type.
    myTIMMonitoringEnable = theTIMMonitoringState;
    return hasChanged;
}

bool MON_OduConfig::GetTIMMonitoringEnable() const
{
    return myTIMMonitoringEnable;
}

bool MON_OduConfig::SetTimCriteria(const CT_TEL_TimCriteriaMode& theTimCriteria)
{
    bool hasChanged = (theTimCriteria != myTIMCriteriaMode);
    // This setting has effect only in LTE termination type.
    myTIMCriteriaMode = theTimCriteria;
    return hasChanged;
}

const CT_TEL_TimCriteriaMode MON_OduConfig::GetTimCriteria() const
{
    return myTIMCriteriaMode;
}

bool MON_OduConfig::SetLayerFailOnTIM(bool theLayerFailOnTIM)
{
    bool hasChanged = (theLayerFailOnTIM != myLayerFailOnTIM);
    myLayerFailOnTIM = theLayerFailOnTIM;
    return hasChanged;
}

bool MON_OduConfig::GetLayerFailOnTIM() const
{
    return myLayerFailOnTIM;
}

bool MON_OduConfig::SetLayerLocked(bool theState)
{
    bool hasChanged = false;
    if (myLayerLocked != theState)
    {
        myLayerLocked = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OduConfig::GetLayerLocked() const
{
    return myLayerLocked;
}

bool MON_OduConfig::SetIsMonOduTerm(bool theIsMonOduTerm)
{
    bool hasChanged = (myIsMonOduTerm != theIsMonOduTerm);
    myIsMonOduTerm = theIsMonOduTerm;
    return hasChanged;
}

bool MON_OduConfig::GetIsMonOduTerm() const
{
    return myIsMonOduTerm;
}

bool MON_OduConfig::SetIsConnectedAsSrc(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsSrc != theState)
    {
        myIsConnectedAsSrc = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OduConfig::GetIsConnectedAsSrc() const
{
    return myIsConnectedAsSrc;
}

bool MON_OduConfig::SetIsConnectedAsDst(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsDst != theState)
    {
        myIsConnectedAsDst = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OduConfig::GetIsConnectedAsDst() const
{
    return myIsConnectedAsDst;
}

bool MON_OduConfig::SetAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OduConfig::GetAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUAIS_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetLckFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLckFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODULCK_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODULCK_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OduConfig::GetLckFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODULCK_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetOciFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetOciFailLayer() != theState)
    {    
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUOCI_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUOCI_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;        
}

bool MON_OduConfig::GetOciFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUOCI_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetPlmFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetPlmFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUPLM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUPLM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;    
}

bool MON_OduConfig::GetPlmFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUPLM_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetGenAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGenAisFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUGENAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUGENAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;  
}

bool MON_OduConfig::GetGenAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUGENAIS_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetMfiFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetMfiFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODULOOMFI_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODULOOMFI_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;  
}

bool MON_OduConfig::GetMfiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODULOOMFI_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetTimFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetTimFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUTIM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUTIM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;  
}

bool MON_OduConfig::GetTimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUTIM_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetInternalAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetInternalAisFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUINTERNALAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUINTERNALAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;  
}

bool MON_OduConfig::GetInternalAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUINTERNALAIS_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetMsimFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetMsimFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODUMSIM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODUMSIM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;  
}

bool MON_OduConfig::GetMsimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODUMSIM_BITMASK) == 0 ? false : true;
}

bool MON_OduConfig::SetLoflomFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLoflomFailLayer() != theState)
    {  
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_ODULOFLOM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_ODULOFLOM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;  
}

bool MON_OduConfig::GetLoflomFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_ODULOFLOM_BITMASK) == 0 ? false : true;
}

uint16 MON_OduConfig::GetFailLayerBitMask() const
{
    return myDefectFailLayerBitMask;
}

// For Display
ostream& MON_OduConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);

    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetExpectedTrace();
        theStream    << FC_InsertVar(aTrace);
    }

    theStream << FC_InsertVar(myTIMMonitoringEnable);
    theStream << FC_InsertVar(myLayerFailOnTIM);
    theStream << FC_InsertVar(myLayerLocked);
    theStream << FC_InsertVar(myIsMonOduTerm);
    theStream << FC_InsertVar(myIsConnectedAsSrc);
    theStream << FC_InsertVar(myIsConnectedAsDst);

    uint16 tmp= (uint16)myTIMCriteriaMode;
    theStream << FC_InsertVar(tmp);

    theStream << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

// For Display
istream& MON_OduConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream   >> FC_ExtractVar(aTrace);
        SetExpectedTrace(aTrace);
    }
    else
    {
        DeleteExpectedTrace();
    }

    theStream >> FC_ExtractVar(myTIMMonitoringEnable);
    theStream >> FC_ExtractVar(myLayerFailOnTIM);
    theStream >> FC_ExtractVar(myLayerLocked);
    theStream >> FC_ExtractVar(myIsMonOduTerm);
    theStream >> FC_ExtractVar(myIsConnectedAsSrc);
    theStream >> FC_ExtractVar(myIsConnectedAsDst);

    uint16 tmp;
    theStream >> FC_ExtractVar(tmp);
    myTIMCriteriaMode = (CT_TEL_TimCriteriaMode)tmp;

    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);

    return theStream;
}


// For persitance and region transfer
FC_Stream& MON_OduConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);

    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetExpectedTrace();
        theStream    << aTrace;
    }

    theStream << myTIMMonitoringEnable;
    theStream << myLayerFailOnTIM;
    theStream << myLayerLocked;
    theStream << myIsMonOduTerm;
    theStream << myIsConnectedAsSrc;
    theStream << myIsConnectedAsDst;

    uint16 tmp= (uint16)myTIMCriteriaMode;
    theStream << tmp;

    theStream << myDefectFailLayerBitMask;
    
    return theStream;
}

// For persitance and region transfer
FC_Stream& MON_OduConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);

    theStream   >> myTraceInUse;
    if (myTraceInUse) 
    {
        // CT_G709Trace aTrace();
        CT_G709Trace aTrace = CT_G709DefaultTrace::GetInstance();
        theStream    >> aTrace;
        SetExpectedTrace(aTrace);
    }
    else
    {
        DeleteExpectedTrace();
    }

    theStream >> myTIMMonitoringEnable;
    theStream >> myLayerFailOnTIM;
    theStream >> myLayerLocked;
	theStream >> myIsMonOduTerm;
    theStream >> myIsConnectedAsSrc;
    theStream >> myIsConnectedAsDst;

    uint16 tmp;
    theStream >> tmp;
    myTIMCriteriaMode = (CT_TEL_TimCriteriaMode)tmp;

    theStream >> myDefectFailLayerBitMask;

    return theStream;
}



void MON_OduConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "ODU     - Forced Layer lock     [layerlock] = " << DISPLAY_BOOL(myLayerLocked) << endl;
    theStream   << "ODU     - Terminate Mon         [monterm]   = " << DISPLAY_BOOL(myIsMonOduTerm) << endl;
    theStream   << "ODU     - Is Connected As Src   [src]       = " << DISPLAY_BOOL(myIsConnectedAsSrc) << endl;
    theStream   << "ODU     - Is Connected As Dst   [dst]       = " << DISPLAY_BOOL(myIsConnectedAsDst) << endl;
    theStream   << "ODU     - TIM Monitoring        [tim]       = " << DISPLAY_BOOL(myTIMMonitoringEnable) << endl;
    theStream   << "ODU     - TIM Criteria Mode     [timmode]   = " << DISPLAY_TIMCRITERIAMODE(myTIMCriteriaMode)<<endl;
    theStream   << "ODU     - Layer Fail On TIM     [timfail]   = " << DISPLAY_BOOL(myLayerFailOnTIM) << endl;
    theStream   << "TCM     - Trace In Use                      = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "TCM     - Expected Trace        [trace]     = " ;
    if (myExpectedTracePtr != NULL) 
    {
        CT_G709Trace &aTrace = GetExpectedTrace();
        aTrace.Display(theStream);
    }
    else
    {
        theStream   << endl;
    }

    theStream   << "ODU     - AIS Fail Layer                    = " << DISPLAY_BOOL(GetAisFailLayer()) << endl;  
    theStream   << "ODU     - LCK Fail Layer                    = " << DISPLAY_BOOL(GetLckFailLayer()) << endl;  
    theStream   << "ODU     - OCI Fail Layer                    = " << DISPLAY_BOOL(GetOciFailLayer()) << endl;  
    theStream   << "ODU     - PLM Fail Layer                    = " << DISPLAY_BOOL(GetPlmFailLayer()) << endl;  
    theStream   << "ODU     - GENAIS Fail Layer                 = " << DISPLAY_BOOL(GetGenAisFailLayer()) << endl;  
    theStream   << "ODU     - MFI Fail Layer                    = " << DISPLAY_BOOL(GetMfiFailLayer()) << endl;  
    theStream   << "ODU     - TIM Fail Layer                    = " << DISPLAY_BOOL(GetTimFailLayer()) << endl;  
    theStream   << "ODU     - INTERNALAIS Fail Layer            = " << DISPLAY_BOOL(GetInternalAisFailLayer()) << endl;  
    theStream   << "ODU     - MSIM Fail Layer                   = " << DISPLAY_BOOL(GetTimFailLayer()) << endl;  
    theStream   << "ODU     - LOFLOM Fail Layer                 = " << DISPLAY_BOOL(GetInternalAisFailLayer()) << endl;
}

FC_CmdProcessor::STATUS MON_OduConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto ODUERROR;

    if (!strcmp(argv[0],"tim"))
    {
        SetTIMMonitoringEnable(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timfail"))
    {
        SetLayerFailOnTIM(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timmode"))
    {
        if (!strcmp(argv[1],"sapi"))
            SetTimCriteria(CT_TEL_TIM_SAPI);
        else if(!strcmp(argv[1],"dapi"))
            SetTimCriteria(CT_TEL_TIM_DAPI);
        else if(!strcmp(argv[1],"sd"))
            SetTimCriteria(CT_TEL_TIM_SAPI_DAPI);
        else if(!strcmp(argv[1],"oper"))
            SetTimCriteria(CT_TEL_TIM_OPER);
        else if(!strcmp(argv[1],"so"))
            SetTimCriteria(CT_TEL_TIM_SAPI_OPER);
        else if(!strcmp(argv[1],"do"))
            SetTimCriteria(CT_TEL_TIM_DAPI_OPER);
        else if(!strcmp(argv[1],"sdo"))
            SetTimCriteria(CT_TEL_TIM_SAPI_DAPI_OPER);
        else if(!strcmp(argv[1],"unknown"))
            SetTimCriteria(CT_TEL_TIM_UNKNOWN);
        else
            goto ODUERROR;        
    }
    else if (!strcmp(argv[0],"trace"))
    {
        if (argc != 4) goto ODUERROR;
        string aMessage(argv[1]);
        string aSapi(argv[2]);
        string aDapi(argv[3]);

        CT_G709Trace aTrace(aSapi,aDapi,aMessage);

        SetExpectedTrace(aTrace);
    }
    else if (!strncmp(argv[0],"rmtr",4))
    {
        if(argv[1][0]=='e')
        {
            DeleteExpectedTrace();
        }
    }
    else if (!strcmp(argv[0],"layerlock"))
    {
        SetLayerLocked(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"monterm"))
    {
        SetIsMonOduTerm(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"src"))
    {
        SetIsConnectedAsSrc(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"dst"))
    {
        SetIsConnectedAsDst(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"aisfaillayer"))
    {
        SetAisFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"lckfaillayer"))
    {
        SetLckFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"ocifaillayer"))
    {
        SetOciFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"plmfaillayer"))
    {
        SetPlmFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"genaisfaillayer"))
    {
        SetGenAisFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"mfifaillayer"))
    {
        SetMfiFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timfaillayer"))
    {
        SetTimFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"internalaisfaillayer"))
    {
        SetInternalAisFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"msimfaillayer"))
    {
        SetMsimFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"loflomfaillayer"))
    {
        SetLoflomFailLayer(argv[1][0]=='e');
    }    
    else
        goto ODUERROR;

    return FC_CmdProcessor::E_SUCCESS;

ODUERROR:
    {
        fc_cout << "odu layerlock     <e-nable|d-isable> " << endl;
        fc_cout << "odu monterm       <e-nable|d-isable> " << endl;
        fc_cout << "odu <src|dst>     <e-nable|d-isable> " << endl;
        fc_cout << "odu <tim|timfail> <e-nable|d-isable> " << endl;
        fc_cout << "odu <timmode>     <sapi|dapi|oper|sd|so|do|sdo|unknown> " << endl;
        fc_cout << "odu <rmtr-ace>    <e-nable|d-isable> " << endl;
        fc_cout << "odu <trace>       <32-byte message> <15-byte sapi> <15-byte dapi>" << endl;
        fc_cout << "odu aisfaillayer  <e-nable|d-isable> " << endl;
        fc_cout << "odu lckfaillayer  <e-nable|d-isable> " << endl;
        fc_cout << "odu ocifaillayer  <e-nable|d-isable> " << endl;
        fc_cout << "odu plmfaillayer  <e-nable|d-isable> " << endl;
        fc_cout << "odu genaisfaillayer <e-nable|d-isable> " << endl;
        fc_cout << "odu mfifaillayer  <e-nable|d-isable> " << endl;
        fc_cout << "odu timfaillayer  <e-nable|d-isable> " << endl;
        fc_cout << "odu internalaisfaillayer <e-nable|d-isable> " << endl;
        fc_cout << "odu msimfaillayer <e-nable|d-isable> " << endl;
        fc_cout << "odu loflomfaillayer <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;

}
