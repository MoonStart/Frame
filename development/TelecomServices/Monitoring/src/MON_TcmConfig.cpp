//Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TcmConfig.h"
#include <BaseClass/FC_TextStream.h>

MON_TcmConfig::MON_TcmConfig(uint32 theIndex):
    MON_Config(theIndex),
    myTraceInUse(false),
    myExpectedTracePtr(NULL),
    myTIMMonitoringEnable(false),
    myLayerFailOnTIM(false),
    myLayerFailOnLTC(false),
    myLayerLocked(false),
    myTIMCriteriaMode(CT_TEL_TIM_UNKNOWN)
{
}

MON_TcmConfig::~MON_TcmConfig()
{
}

void MON_TcmConfig::Reset(void)
{
    MON_Config::Reset();   

    // Note: DeleteExpectedTrace() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //myExpectedTracePtr   = NULL;
    DeleteExpectedTrace();
    myTIMMonitoringEnable = false;
    myLayerFailOnTIM = false;
    myLayerFailOnLTC = false;
    myLayerLocked = false;
    myTIMCriteriaMode =  CT_TEL_TIM_UNKNOWN;
}

bool MON_TcmConfig::SetExpectedTrace(const CT_G709Trace& theExpTrace)
{
    bool hasChanged = false;
    if (myExpectedTracePtr == NULL) 
    {
        myExpectedTracePtr = new CT_G709Trace(); 
        hasChanged = true;
    }
    hasChanged = hasChanged || (!(*myExpectedTracePtr == theExpTrace));
    *myExpectedTracePtr = theExpTrace;
    myTraceInUse = true;
    return hasChanged;
}

bool MON_TcmConfig::DeleteExpectedTrace()
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

CT_G709Trace & MON_TcmConfig::GetExpectedTrace() const
{
    if (myExpectedTracePtr != NULL) 
    {
        return(*myExpectedTracePtr);
    }
    else
    {
        return(CT_G709DefaultTrace::GetInstance());
    }
}


bool MON_TcmConfig::SetTIMMonitoringEnable(bool theTIMMonitoringState)
{
    bool hasChanged = (myTIMMonitoringEnable != theTIMMonitoringState);
    // This setting has effect only in LTE termination type.
    myTIMMonitoringEnable = theTIMMonitoringState;
    return hasChanged;
}

bool MON_TcmConfig::GetTIMMonitoringEnable() const
{
    return myTIMMonitoringEnable;
}

bool MON_TcmConfig::SetTimCriteria(const CT_TEL_TimCriteriaMode& theTimCriteria)
{
    bool hasChanged = (myTIMCriteriaMode != theTimCriteria);
    myTIMCriteriaMode = theTimCriteria;
    return hasChanged;
}

CT_TEL_TimCriteriaMode MON_TcmConfig::GetTimCriteria() const
{
    return myTIMCriteriaMode;
}

bool MON_TcmConfig::SetLayerFailOnTIM(bool theLayerFailOnTIM)
{
    bool hasChanged = (myLayerFailOnTIM != theLayerFailOnTIM);
    myLayerFailOnTIM = theLayerFailOnTIM;
    return hasChanged;
}

bool MON_TcmConfig::GetLayerFailOnTIM() const
{
    return myLayerFailOnTIM;
}

bool MON_TcmConfig::SetLayerFailOnLTC(bool theLayerFailOnLTC)
{
    bool hasChanged = (myLayerFailOnLTC != theLayerFailOnLTC);
    myLayerFailOnLTC = theLayerFailOnLTC;
    return hasChanged;
}

bool MON_TcmConfig::GetLayerFailOnLTC() const
{
    return myLayerFailOnLTC;
}

bool MON_TcmConfig::SetLayerLocked(bool theState)
{
    bool hasChanged = false;
    if (myLayerLocked != theState)
    {
        myLayerLocked = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_TcmConfig::GetLayerLocked() const
{
    return myLayerLocked;
}

// For Display
ostream& MON_TcmConfig::WriteObject(ostream& theStream)
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
    theStream << FC_InsertVar(myLayerFailOnLTC);
    theStream << FC_InsertVar(myLayerLocked);

    uint16 tmp= (uint16)myTIMCriteriaMode;
    theStream << FC_InsertVar(tmp);

    return theStream;
}

// For Display
istream& MON_TcmConfig::ReadObject(istream& theStream)
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
    theStream >> FC_ExtractVar(myLayerFailOnLTC);
    theStream >> FC_ExtractVar(myLayerLocked);

    uint16 tmp;
    theStream >> FC_ExtractVar(tmp);
    myTIMCriteriaMode = (CT_TEL_TimCriteriaMode)tmp;

    return theStream;
}

// For persitance and region transfer
FC_Stream& MON_TcmConfig::WriteObjectBinary(FC_Stream& theStream)
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
    theStream << myLayerFailOnLTC;
    theStream << myLayerLocked;

    uint16 tmp= (uint16)myTIMCriteriaMode;
    theStream << tmp;

    return theStream;
}

// For persitance and region transfer
FC_Stream& MON_TcmConfig::ReadObjectBinary(FC_Stream& theStream)
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
    theStream >> myLayerFailOnLTC;
    theStream >> myLayerLocked;

    uint16 tmp;
    theStream >> tmp;
    myTIMCriteriaMode = (CT_TEL_TimCriteriaMode)tmp;

    return theStream;
}

void MON_TcmConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "TCM     - Forced Layer lock     [layerlock] = " << DISPLAY_BOOL(myLayerLocked) << endl;
    theStream   << "TCM     - TIM Monitoring        [tim]       = " << DISPLAY_BOOL(myTIMMonitoringEnable) << endl;
    theStream   << "TCM     - TIM Criteria Mode     [timmode]   = " << DISPLAY_TIMCRITERIAMODE(myTIMCriteriaMode)<<endl;
    theStream   << "TCM     - Layer Fail On TIM     [timfail]   = " << DISPLAY_BOOL(myLayerFailOnTIM) << endl;    
    theStream   << "TCM     - Layer Fail On LTC     [timfail]   = " << DISPLAY_BOOL(myLayerFailOnLTC) << endl;    
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
}

FC_CmdProcessor::STATUS MON_TcmConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto TCMERROR;

    if (!strcmp(argv[0],"tim"))
    {
        SetTIMMonitoringEnable(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timfail"))
    {
        SetLayerFailOnTIM(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"ltcfail"))
    {
        SetLayerFailOnLTC(argv[1][0]=='e');
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
            goto TCMERROR;        
    }
    else if (!strcmp(argv[0],"trace"))
    {
        if (argc != 4) goto TCMERROR;
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
    else
        goto TCMERROR;

    return FC_CmdProcessor::E_SUCCESS;

TCMERROR:
    {
        fc_cout << "tcm layerlock     <e-nable|d-isable> " << endl;
        fc_cout << "tcm <tim|timfail> <e-nable|d-isable> " << endl;
        fc_cout << "tcm <timmode> <sapi|dapi|oper|sd|so|do|sdo|unknown> " << endl;
        fc_cout << "tcm <rmtr-ace> <e-nable|d-isable> " << endl;
        fc_cout << "tcm <trace> <32-byte message> <15-byte sapi> <15-byte dapi>" << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;

}