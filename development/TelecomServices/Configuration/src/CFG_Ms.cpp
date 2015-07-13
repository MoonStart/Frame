//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Ms.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Ms::CFG_Ms(uint32 theIndex):
    CFG_Object(theIndex),
    myRefType(CT_TEL_MS_TREF_NONE),  
    mySsmSupported(false),
    myFirstTimeslot(INVALID_START_CHANNEL),
	myDTSourceMode(CT_DT_SOURCE_NONE),
    myIsAutoTimingRedProv(false),
    myIsUserProvLocked(false)
{
}

CFG_Ms::~CFG_Ms(void)
{
}


bool CFG_Ms::SetRefType(CT_TEL_MsTref theRefType)
{
    bool hasChanged = (myRefType != theRefType);
    myRefType = theRefType;
    return hasChanged;
}

CT_TEL_MsTref CFG_Ms::GetRefType() const
{
    return myRefType;
}


bool CFG_Ms::SetSsmSupported(bool theSsmSupported)
{
    bool hasChanged = (mySsmSupported != theSsmSupported);
    mySsmSupported = theSsmSupported;
    return hasChanged;
}

bool CFG_Ms::GetSsmSupported() const
{
    return mySsmSupported;
}

bool CFG_Ms::SetTxSsm(CT_FAC_RxSsm theTxSsm)
{
    bool hasChanged = (myTxSsm!= theTxSsm);
    myTxSsm= theTxSsm;
    return hasChanged;
}

CT_FAC_RxSsm CFG_Ms::GetTxSsm() const
{
    return myTxSsm;
}

bool CFG_Ms::SetTxSsmForce(bool theTxSsmForce)
{
    bool hasChanged = (myTxSsmForce!= theTxSsmForce);
    myTxSsmForce= theTxSsmForce;
    return hasChanged;
}

bool CFG_Ms::GetTxSsmForce() const
{
    return myTxSsmForce;
}

bool CFG_Ms::SetFirstTimeslot(uint16 theFirstTimeslot)
{
    bool hasChanged = (myFirstTimeslot != theFirstTimeslot);
    myFirstTimeslot = theFirstTimeslot;
    return hasChanged;
}

uint16 CFG_Ms::GetFirstTimeslot() const
{
    return myFirstTimeslot;
}


bool CFG_Ms::SetDerivedTimingSourceMode(CT_TEL_DT_Source_Mode theDTMode)
{
    bool hasChanged = (myDTSourceMode != theDTMode);
    myDTSourceMode = theDTMode;
    return hasChanged;
}


CT_TEL_DT_Source_Mode CFG_Ms::GetDerivedTimingSourceMode() const
{
	return myDTSourceMode;
}

bool CFG_Ms::SetIsAutoTimingRedProv(bool isAutoTimingActive)
{
    bool hasChanged = (myIsAutoTimingRedProv != isAutoTimingActive);
    myIsAutoTimingRedProv = isAutoTimingActive;
    return hasChanged;
}


bool CFG_Ms::GetIsAutoTimingRedProv() const
{
	return myIsAutoTimingRedProv;
}
 

bool CFG_Ms::SetIsProvLocked(bool isUserProvLocked)
{
    bool hasChanged = (myIsUserProvLocked != isUserProvLocked);
    myIsUserProvLocked = isUserProvLocked;
    return hasChanged;
}

bool CFG_Ms::GetIsProvLocked() const
{
    return myIsUserProvLocked;
}

void CFG_Ms::Reset(void)
{
    // Initialize all attributes to default values.
    myRefType = CT_TEL_MS_TREF_NONE;  
    mySsmSupported = false;
    myFirstTimeslot = INVALID_START_CHANNEL;
	myDTSourceMode = CT_DT_SOURCE_NONE;
    myIsAutoTimingRedProv = false;
    myIsUserProvLocked = false;
    myTxSsm = CT_RxSsm_DNU;
    myTxSsmForce = false;
}

ostream& CFG_Ms::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);

    uint32 aRefType = (uint32) myRefType;
    theStream   << FC_InsertVar(aRefType);

    theStream   << FC_InsertVar(mySsmSupported);

    uint32 aFirstTimeslot = (uint32) myFirstTimeslot;
    theStream   << FC_InsertVar(aFirstTimeslot);

	uint32 aDTMode = (uint32) myDTSourceMode;
    theStream   << FC_InsertVar(aDTMode);

    theStream   << FC_InsertVar(myIsAutoTimingRedProv);

    theStream   << FC_InsertVar(myIsUserProvLocked);

	uint32 aTxSsm = (uint32) myTxSsm;
    theStream   << FC_InsertVar(aTxSsm);

    theStream   << FC_InsertVar(myTxSsmForce);

    return theStream;
}

istream& CFG_Ms::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
   
    uint32 aRefType = 0;
    theStream   >> FC_ExtractVar(aRefType);
    myRefType = (CT_TEL_MsTref) aRefType;

    theStream   >> FC_ExtractVar(mySsmSupported);

    uint32 aFirstTimeslot = 0;
    theStream   >> FC_ExtractVar(aFirstTimeslot);
    myFirstTimeslot = (uint16) aFirstTimeslot;

	uint32 aDTMode = 0;
    theStream   >> FC_ExtractVar(aDTMode);
    myDTSourceMode = (CT_TEL_DT_Source_Mode) aDTMode;

    theStream   >> FC_ExtractVar(myIsAutoTimingRedProv);

    theStream   >> FC_ExtractVar(myIsUserProvLocked);

    uint32 aTxSsm = 0;
    theStream   >> FC_ExtractVar(aTxSsm);
    myTxSsm = (CT_FAC_RxSsm) aTxSsm;

    theStream   >> FC_ExtractVar(myTxSsmForce);

    return theStream;
}

FC_Stream& CFG_Ms::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << (uint32)myRefType;
    theStream   << mySsmSupported;
    theStream   << (uint32)myFirstTimeslot;
	theStream   << (uint32)myDTSourceMode;
    theStream   << myIsAutoTimingRedProv;
    theStream   << myIsUserProvLocked;
    theStream   << (uint32)myTxSsm;
    theStream   << myTxSsmForce;

    return theStream;
}

FC_Stream& CFG_Ms::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
      
    uint32 aRefType = 0;
    theStream   >> aRefType;
    myRefType = (CT_TEL_MsTref)aRefType;

    theStream   >> mySsmSupported;

    uint32 aFirstTimeslot = 0;
    theStream   >> aFirstTimeslot;
    myFirstTimeslot = (uint16)aFirstTimeslot;

	uint32 aDTMode = 0;
    theStream   >> aDTMode;
    myDTSourceMode = (CT_TEL_DT_Source_Mode)aDTMode;

    theStream   >> myIsAutoTimingRedProv;
    theStream   >> myIsUserProvLocked;

	uint32 aTxSsm = 0;
    theStream   >> aTxSsm;
    myTxSsm = (CT_FAC_RxSsm)aTxSsm;

    theStream   >> myTxSsmForce;

    return theStream;    
}

FC_CmdProcessor::STATUS CFG_Ms::Set(int argc, char **argv)
{ 
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;
 
    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"ref",3)) 
    {
        SetRefType(CFG_STRING_TO_REF_TYPE(argv[1]));
    }
    else if (!strncmp(aParam,"ssm",3))
    {
        SetSsmSupported(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"fir",3)) 
    {
        SetFirstTimeslot(uint16(atoi(argv[1])));
    }
	else if (!strncmp(aParam,"dts",3))
    {
        SetDerivedTimingSourceMode(CFG_STRING_TO_DT_MODE(argv[1]));
    }
    else if (!strncmp(aParam,"aut",3))
    {
        SetIsAutoTimingRedProv(argv[1][0]=='t');
    }
    else if (!strncmp(aParam,"lock",3))
    {
        SetIsProvLocked(argv[1][0]=='t');
    }
    else if (!strncmp(aParam,"txs",3))
    {
        SetTxSsm(CFG_STRING_TO_RXSSM(argv[1]));
    }
    else if (!strncmp(aParam,"for",3))
    {
        SetTxSsmForce(argv[1][0]=='t');
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "MS <reftype>        <none|pri|sec> " << endl;
        fc_cout << "MS <ssmsupport>     <e-nable|d-isable> " << endl;
        fc_cout << "MS <firsttimeslot>  <0-191 | 65535> " << endl;
		fc_cout << "MS <dtsourcemode>   <none|srca|srcb|ab> " << endl;
        fc_cout << "MS <autotiming>     <t-rue|f-alse> " << endl;
        fc_cout << "MS <locked>         <t-rue|f-alse> " << endl;
        fc_cout << "MS <txssm>          <dnu|prc|sec|ssua|ssub|stu> " << endl;
        fc_cout << "MS <forcetxssm>     <t-rue|f-alse> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Ms::Display( FC_Stream& theStream )
{
    theStream   << "MS       - Reference Type     [reftype]         = " << DISPLAY_MS_TREF(myRefType) << endl;
    theStream   << "MS       - Ssm Support        [ssmsupport]      = " << DISPLAY_BOOL(mySsmSupported) << endl;
    theStream   << "MS       - Tx Ssm             [txssm]           = " << display_RXSSM(myTxSsm) << endl;
    theStream   << "MS       - Tx Ssm Forcing     [forcetxssm]      = " << DISPLAY_BOOL(myTxSsmForce) << endl;
    theStream   << "MS       - First Timeslot     [firsttimeslot]   = " << (uint32)myFirstTimeslot << endl;
	theStream   << "MS       - DT Source Mode     [derivedsource]   = " << DISPLAY_DT_SOURCE_MODE(myDTSourceMode) << endl;
    theStream   << "MS       - Auto Timing        [autotiming]      = " << DISPLAY_BOOL(myIsAutoTimingRedProv) << endl;
    theStream   << "MS       - Provisioning Locked [locked]         = " << DISPLAY_BOOL(myIsUserProvLocked) << endl;
}

