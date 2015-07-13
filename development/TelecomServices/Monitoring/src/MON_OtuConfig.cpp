// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtuConfig.h"
#include <BaseClass/FC_TextStream.h>

MON_OtuConfig::MON_OtuConfig(uint32 theIndex):
    MON_Config(theIndex),
    myTraceInUse(false),
    myExpectedTracePtr(NULL),
    myTIMMonitoringEnable(false),
    myLayerFailOnTIM(false),
    myTIMCriteraMode(CT_TEL_TIM_UNKNOWN),
    myDefectFailLayerBitMask(MON_FAILLAYER_OTU_DEFAULT_BITMASK)
{
}

MON_OtuConfig::~MON_OtuConfig(void )
{
}

void MON_OtuConfig::Reset()
{
    MON_Config::Reset();
    // Note: DeleteExpectedTrace() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //myExpectedTracePtr   = NULL;
    DeleteExpectedTrace();
    myTIMMonitoringEnable = false;
    myLayerFailOnTIM = false;
    myTIMCriteraMode =  CT_TEL_TIM_UNKNOWN;
    myDefectFailLayerBitMask = MON_FAILLAYER_OTU_DEFAULT_BITMASK;
}

bool MON_OtuConfig::SetExpectedTrace(const CT_G709Trace& theExpTrace)
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

bool MON_OtuConfig::DeleteExpectedTrace()
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

CT_G709Trace & MON_OtuConfig::GetExpectedTrace() const
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


bool MON_OtuConfig::SetTIMMonitoringEnable(bool theTIMMonitoringState)
{
    // This setting has effect only in LTE termination type.

    bool hasChanged = (myTIMMonitoringEnable != theTIMMonitoringState);
    myTIMMonitoringEnable = theTIMMonitoringState;
    return hasChanged;
}

bool MON_OtuConfig::GetTIMMonitoringEnable() const
{
    return myTIMMonitoringEnable;
}

bool MON_OtuConfig::SetTimCriteria(const CT_TEL_TimCriteriaMode& theTimCriteria)
{
    bool hasChanged = (myTIMCriteraMode != theTimCriteria);
    myTIMCriteraMode = theTimCriteria;
    return hasChanged;
}

const CT_TEL_TimCriteriaMode MON_OtuConfig::GetTimCriteria() const
{
    return myTIMCriteraMode;
}

bool MON_OtuConfig::SetLayerFailOnTIM(bool theLayerFailOnTIM)
{
    bool hasChanged = (myLayerFailOnTIM != theLayerFailOnTIM);
    myLayerFailOnTIM = theLayerFailOnTIM;
    return hasChanged;
}

bool MON_OtuConfig::GetLayerFailOnTIM() const
{
    return myLayerFailOnTIM;
}

bool MON_OtuConfig::SetAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_OTUAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_OTUAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OtuConfig::GetAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTUAIS_BITMASK) == 0 ? false : true;
}

bool MON_OtuConfig::SetLofFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLofFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_OTULOF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_OTULOF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OtuConfig::GetLofFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTULOF_BITMASK) == 0 ? false : true;
}

bool MON_OtuConfig::SetLomfFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLomfFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_OTULOMF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_OTULOMF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OtuConfig::GetLomfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTULOMF_BITMASK) == 0 ? false : true;
}

bool MON_OtuConfig::SetFecmFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetFecmFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_OTUFECM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_OTUFECM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OtuConfig::GetFecmFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTUFECM_BITMASK) == 0 ? false : true;
}

bool MON_OtuConfig::SetTimFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetTimFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_OTUTIM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_OTUTIM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OtuConfig::GetTimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_OTUTIM_BITMASK) == 0 ? false : true;
}

uint16 MON_OtuConfig::GetFailLayerBitMask() const
{
    return myDefectFailLayerBitMask;
}

// For Display
ostream& MON_OtuConfig::WriteObject(ostream& theStream)
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

    uint16 tmp= (uint16)myTIMCriteraMode;
    theStream << FC_InsertVar(tmp);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);

    return theStream;
}

// For Display
istream& MON_OtuConfig::ReadObject(istream& theStream)
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

    uint16 tmp;
    theStream >> FC_ExtractVar(tmp);
    myTIMCriteraMode = (CT_TEL_TimCriteriaMode)tmp;
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);
    
    return theStream;
}


// For persitance and region transfer
FC_Stream& MON_OtuConfig::WriteObjectBinary(FC_Stream& theStream)
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

    uint16 tmp= (uint16)myTIMCriteraMode;
    theStream << tmp;
    theStream << myDefectFailLayerBitMask;
    
    return theStream;
}

// For persitance and region transfer
FC_Stream& MON_OtuConfig::ReadObjectBinary(FC_Stream& theStream)
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

    uint16 tmp;
    theStream >> tmp;
    myTIMCriteraMode = (CT_TEL_TimCriteriaMode)tmp;
    theStream >> myDefectFailLayerBitMask;
    
    return theStream;
}

void MON_OtuConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "OTU     - TIM Monitoring        [tim]       = " << DISPLAY_BOOL(myTIMMonitoringEnable) << endl;
    theStream   << "OTU     - Layer Fail On TIM     [timfail]   = " << DISPLAY_BOOL(myLayerFailOnTIM) << endl;
    theStream   << "OTU     - TIM Criteria Mode     [timmode]    = " << DISPLAY_TIMCRITERIAMODE(myTIMCriteraMode)<<endl;
    theStream   << "OTU     - Trace In Use                      = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "OTU     - Expected Trace        [trace]     = " ;
    if (myExpectedTracePtr != NULL) 
    {
        CT_G709Trace &aTrace = GetExpectedTrace();
        aTrace.Display(theStream);
    }
    else
    {
        theStream   << endl;
    }
    theStream   << "OTU      - AIS Fail Layer                    = " << DISPLAY_BOOL(GetAisFailLayer()) << endl;  
    theStream   << "OTU      - LOF Fail Layer                    = " << DISPLAY_BOOL(GetLofFailLayer()) << endl;  
    theStream   << "OTU      - LOMF Fail Layer                   = " << DISPLAY_BOOL(GetLomfFailLayer()) << endl;  
    theStream   << "OTU      - FECM Fail Layer                   = " << DISPLAY_BOOL(GetFecmFailLayer()) << endl;  
    theStream   << "OTU      - TIM Fail Layer                    = " << DISPLAY_BOOL(GetTimFailLayer()) << endl;  
}

FC_CmdProcessor::STATUS MON_OtuConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto OTUERROR;

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
            goto OTUERROR;        
    }
    else if (!strcmp(argv[0],"trace"))
    {
        if (argc != 5) goto OTUERROR;
        string aMessage(argv[1]);
        string aSapi(argv[2]);
        string aDapi(argv[3]);
        string aTraceId(argv[4]);

        CT_G709Trace aTrace(aSapi,aDapi,aMessage, atoi(aTraceId.c_str()));
        SetExpectedTrace(aTrace);
    }
    else if (!strncmp(argv[0],"rmtr",4))
    {
        if(argv[1][0]=='e')
        {
            DeleteExpectedTrace();
        }
    }
    else if (!strcmp(argv[0],"aisfaillayer"))
    {
        SetAisFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"loffaillayer"))
    {
        SetLofFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"lomffaillayer"))
    {
        SetLomfFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"fecmfaillayer"))
    {
        SetFecmFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timfaillayer"))
    {
        SetTimFailLayer(argv[1][0]=='e');
    }
    else
        goto OTUERROR;

    return FC_CmdProcessor::E_SUCCESS;

OTUERROR:
    {
        fc_cout << "otu <tim> <e-nable|d-isable> " << endl;
        fc_cout << "otu <timfail> <e-nable|d-isable> " << endl;
        fc_cout << "otu <timotu> <sapi|dapi|oper|sd|so|do|sdo|unknown> " << endl;
        fc_cout << "otu <rmtr-ace> <e-nable|d-isable> " << endl;
        fc_cout << "otu <trace> <32-byte message> <15-byte sapi> <15-byte dapi> <trace ID>" << endl;
        fc_cout << "otu aisfaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "otu loffaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "otu lomffaillayer            <e-nable|d-isable> " << endl;
        fc_cout << "otu fecmfaillayer            <e-nable|d-isable> " << endl;
        fc_cout << "otu timfaillayer             <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}
