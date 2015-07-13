//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Otu.h"
#include <BaseClass/FC_TextStream.h>

CFG_Otu::CFG_Otu(uint32 theIndex):
    CFG_Object(theIndex),
    myEnableFECCorrection(true),
    myForceErrorInsertion(false),
    myEnableSuperFEC(false),
    myForceAIS(false),
    myBurstyBerSdIntervals(0),
    myBurstyBerSdThreshold(0),
    myTraceInUse(false),
    mySentTracePtr(NULL),
    myFECType(CT_TEL_FEC_TYPE_UNKNOWN)
{
}

CFG_Otu::~CFG_Otu(void)
{
}

bool CFG_Otu::SetSentTrace(const CT_G709Trace& theSentTrace)
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

bool CFG_Otu::DeleteSentTrace()
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

CT_G709Trace & CFG_Otu::GetSentTrace() const
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


bool CFG_Otu::SetForceAIS(bool theForceAIS)
{
    bool hasChanged = (myForceAIS != theForceAIS);
    myForceAIS = theForceAIS;
    return hasChanged;
}

bool CFG_Otu::GetForceAIS() const
{
        return myForceAIS;
}

bool CFG_Otu::SetEnableFECCorrection(bool theEnableFECCorrection)
{
    bool hasChanged = (myEnableFECCorrection != theEnableFECCorrection);
    myEnableFECCorrection = theEnableFECCorrection;
    return hasChanged;
}

bool CFG_Otu::GetEnableFECCorrection() const
{
        return myEnableFECCorrection;
}

bool CFG_Otu::SetForceErrorInsertion(bool theForceErrorInsertion)
{
    bool hasChanged = (myForceErrorInsertion != theForceErrorInsertion);
    myForceErrorInsertion = theForceErrorInsertion;
    return hasChanged;
}

bool CFG_Otu::GetForceErrorInsertion() const
{
        return myForceErrorInsertion;
}

bool CFG_Otu::SetEnableSuperFEC(bool theEnableSuperFEC)
{
    bool hasChanged = (myEnableSuperFEC != theEnableSuperFEC);
    myEnableSuperFEC = theEnableSuperFEC;
    return hasChanged;
}

bool CFG_Otu::GetEnableSuperFEC() const
{
        return myEnableSuperFEC;
}

bool CFG_Otu::SetBurstyBerSdIntervals(uint16 theIntervals)
{
    bool hasChanged = (myBurstyBerSdIntervals != theIntervals);
    myBurstyBerSdIntervals = theIntervals;
    return hasChanged;
}

uint16 CFG_Otu::GetBurstyBerSdIntervals() const
{
    return myBurstyBerSdIntervals;
}

bool CFG_Otu::SetBurstyBerSdThreshold(uint32 theThreshold)
{
    bool hasChanged = (myBurstyBerSdThreshold != theThreshold);
    myBurstyBerSdThreshold = theThreshold;
    return hasChanged;
}

uint32 CFG_Otu::GetBurstyBerSdThreshold() const
{
    return myBurstyBerSdThreshold;
}

bool CFG_Otu::SetFECType(CT_TEL_FecType theFECType)
{
    bool hasChanged = (myFECType != theFECType);
    myFECType = theFECType;
    return hasChanged;
}

CT_TEL_FecType CFG_Otu::GetFECType() const
{
    return myFECType;
}


void CFG_Otu::Reset(void)
{
    myEnableFECCorrection = true;
    myForceAIS = false;
    myForceErrorInsertion = false;
    // Note: DeleteSentTrace() will accomplish the two commented out lines
    // and delete the memory if needed.
    //myTraceInUse  = false;
    //mySentTracePtr   = NULL;
    DeleteSentTrace();
    myEnableSuperFEC = false;
    myBurstyBerSdIntervals = 0;
    myBurstyBerSdThreshold = 0;
    myFECType = CT_TEL_FEC_TYPE_SUPER;
}


// For Display
ostream& CFG_Otu::WriteObject( ostream& theStream )
{
    int aFECType = myFECType;

    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myEnableFECCorrection);
    theStream   << FC_InsertVar(myForceAIS);
    theStream   << FC_InsertVar(myForceErrorInsertion);
    theStream   << FC_InsertVar(myEnableSuperFEC);
    theStream   << FC_InsertVar(myBurstyBerSdIntervals);
    theStream   << FC_InsertVar(myBurstyBerSdThreshold);

    theStream   << FC_InsertVar(myTraceInUse);
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        theStream    << FC_InsertVar(aTrace);
    }

    theStream   << FC_InsertVar(aFECType);
    return theStream;

}

// For Display
istream& CFG_Otu::ReadObject( istream& theStream )
{
    int aFECType;

    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myEnableFECCorrection);
    theStream   >> FC_ExtractVar(myForceAIS);
    theStream   >> FC_ExtractVar(myForceErrorInsertion);
    theStream   >> FC_ExtractVar(myEnableSuperFEC);
    theStream   >> FC_ExtractVar(myBurstyBerSdIntervals);
    theStream   >> FC_ExtractVar(myBurstyBerSdThreshold);

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

    theStream   >> FC_ExtractVar(aFECType);
    myFECType = (CT_TEL_FecType)aFECType;

    return theStream;

}


// For persitance and region transfer
FC_Stream& CFG_Otu::WriteObjectBinary( FC_Stream& theStream )
{
    int aFECType = myFECType;

    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myEnableFECCorrection;
    theStream   << myForceAIS;
    theStream   << myForceErrorInsertion;
    theStream   << myEnableSuperFEC;
    theStream   << myBurstyBerSdIntervals;
    theStream   << myBurstyBerSdThreshold;

    theStream   << myTraceInUse;
    if (myTraceInUse) 
    {
        CT_G709Trace &aTrace = GetSentTrace();
        theStream    << aTrace;
    }

    theStream   << aFECType;
    return theStream;

}

// For persitance and region transfer
FC_Stream& CFG_Otu::ReadObjectBinary( FC_Stream& theStream )
{
    int aFECType;

    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myEnableFECCorrection;
    theStream   >> myForceAIS;
    theStream   >> myForceErrorInsertion;
    theStream   >> myEnableSuperFEC;
    theStream   >> myBurstyBerSdIntervals;
    theStream   >> myBurstyBerSdThreshold;

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

    theStream   >> aFECType;
    myFECType = (CT_TEL_FecType)aFECType;

    return theStream;

}

FC_CmdProcessor::STATUS CFG_Otu::Set(int argc, char **argv)
{
    char aParam[32];
    char aParamState[16];

    //We need 2 arguments
    if (argc < 2)
        goto OTUERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);
    strcpy(aParamState, argv[1]);

    if (!strcmp(aParam,"aisgen"))
    {
        SetForceAIS(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"fec"))
    {
        SetEnableFECCorrection(aParamState[0]=='e');
    }
    else if (!strcmp(aParam,"fecgen"))
    {
        SetForceErrorInsertion(aParamState[0]=='e');
    }
    else if (!strncmp(aParam,"sup",3))
    {
        SetEnableSuperFEC(aParamState[0]=='e');
    }
    else if(!strncmp(aParam,"inter",5))
    {
        SetBurstyBerSdIntervals(uint16(atoi(argv[1])));
    }
    else if(!strncmp(aParam,"thres",5))
    {
        SetBurstyBerSdThreshold(uint32(atoi(argv[1])));
    }
    else if(!strncmp(aParam,"fect",4))
    {
        bool printUsage = true;
        for (int i = 0; i <= CT_TEL_FEC_TYPE_LAST; i++) if (strcmp(argv[1], DISPLAY_FEC_TYPE(i)) == 0)
        {
            SetFECType((CT_TEL_FecType)i);
            printUsage = false;
            break;
        }
        if (printUsage) 
        {
            goto OTUERROR;
        }
    }
    else if (!strcmp(aParam,"trace"))
    {
        if (argc != 4) { goto OTUERROR; }
        string aSapi(argv[1]);
        string aDapi(argv[2]);
        string aMessage(argv[3]);

        CT_G709Trace aTrace(aSapi,aDapi,aMessage);
        SetSentTrace(aTrace);
    }
    else if (!strncmp(aParam,"rmtr",4))
    {
        if(aParamState[0]=='e')
        {
            DeleteSentTrace();
        }
    }
    else
    {
        goto OTUERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OTUERROR:
    {
        fc_cout << "otu <aisgen|fec|fecgen|sup-erfec> <e-nable|d-isable> " << endl;
        fc_cout << "otu <inter-vals> < int number of intervas for SD calculation > " << endl;
        fc_cout << "otu <thres-hold> < int thresold of block errors > " << endl;
        fc_cout << "otu <fectype> <Regular | Super | SuperI7 | SuperI9 | SoftDecision | None | Unknown)> " << endl;
        fc_cout << "otu <rmtr-ace> <e-nable|d-isable> " << endl;
        fc_cout << "otu trace <15-byte sapi> <15-byte dapi> <28-byte operator specific>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Otu::Display( FC_Stream& theStream )
{
    theStream   << "OTU      - AIS Forced           []          = " << DISPLAY_BOOL(myForceAIS) << endl;
    theStream   << "OTU      - Force Error Insertion[fecgen]    = " << DISPLAY_BOOL(myForceErrorInsertion) << endl;
    theStream   << "OTU      - FEC Type             [fectype]   = " << DISPLAY_FEC_TYPE(myFECType) << endl;
    theStream   << "OTU      - FEC correction       [fec]       = " << DISPLAY_BOOL(myEnableFECCorrection) << endl;
    theStream   << "OTU      - Super FEC            [superfec]  = " << DISPLAY_BOOL(myEnableSuperFEC) << endl;
    theStream   << "OTU      - Bursty SD Intervals  [intervals] = " << dec << myBurstyBerSdIntervals << dec << endl;
    theStream   << "OTU      - Bursty SD Threshold  [threshold] = " << dec << myBurstyBerSdThreshold << dec << endl;
    theStream   << "OTU      - Trace In Use                     = " << DISPLAY_BOOL(myTraceInUse) << endl;
    theStream   << "OTU      - Transmitted Trace    [trace]     = " ;
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
