//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_RsAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_RsAutomatic::CFG_RsAutomatic(uint32 theIndex):
    myForceAIS(false),
	myForceRDI(false),
	myForceCSFOPUInternal(false),
    myForceAISInternal(false),
    myLineSideProtExists(false),
    mySuppressBackwardInd(false),
    myAdd(false),
    myDrop(false),
    myAutoIndicationType(CT_RS_INDICATION_UNKNOWN),
    myAutoInternalIndType(CT_RS_INDICATION_UNKNOWN),
    CFG_Object(theIndex)
{
}

CFG_RsAutomatic::~CFG_RsAutomatic()
{
}

bool CFG_RsAutomatic::SetForceAIS(bool theForceAIS)
{
    bool hasChanged = false;
    if(myForceAIS != theForceAIS)
    {
        myForceAIS = theForceAIS;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_RsAutomatic::GetForceAIS() const
{
    return myForceAIS;
}

bool CFG_RsAutomatic::SetForceAISInternal(bool theForceAISInternal)
{
    bool hasChanged = false;
    if(myForceAISInternal != theForceAISInternal)
    {
        myForceAISInternal = theForceAISInternal;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_RsAutomatic::GetForceAISInternal() const
{
    return myForceAISInternal;
}

bool CFG_RsAutomatic::SetForceRDI(bool theForceRDI)
{
    bool hasChanged = false;
    if(myForceRDI != theForceRDI)
    {
        myForceRDI = theForceRDI;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_RsAutomatic::GetForceRDI() const
{ 
    return myForceRDI;
}

bool CFG_RsAutomatic::SetForceCSFOPUInternal(bool theForceCSFOPUInternal)
{
    bool hasChanged = false;
    if(myForceCSFOPUInternal != theForceCSFOPUInternal)
    {
        myForceCSFOPUInternal = theForceCSFOPUInternal;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_RsAutomatic::GetForceCSFOPUInternal() const
{ 
    return myForceCSFOPUInternal;
}

bool CFG_RsAutomatic::SetLineSideProtExists(bool theLineSideProtExists)
{
    bool hasChanged = false;
    if(myLineSideProtExists != theLineSideProtExists)
    {
        myLineSideProtExists = theLineSideProtExists;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_RsAutomatic::GetLineSideProtExists() const
{
    return myLineSideProtExists;
}

bool CFG_RsAutomatic::SetSuppressBackwardInd(bool theSuppressBackwardInd)
{
    bool hasChanged = false;
    if(mySuppressBackwardInd != theSuppressBackwardInd)
    {
        mySuppressBackwardInd = theSuppressBackwardInd;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_RsAutomatic::GetSuppressBackwardInd() const
{
    return mySuppressBackwardInd;
}

bool CFG_RsAutomatic::SetAdd(bool theAdd)
{
    bool hasChanged = false;
    if(myAdd != theAdd)
    {
        myAdd = theAdd;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_RsAutomatic::GetAdd() const
{
    return myAdd;
}

bool CFG_RsAutomatic::SetDrop(bool theDrop)
{
    bool hasChanged = false;
    if(myDrop != theDrop)
    {
        myDrop = theDrop;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_RsAutomatic::GetDrop() const
{
    return myDrop;
}

void CFG_RsAutomatic::SetAutoIndicationType(CT_RS_IndicationType theIndicationType)
{
    myAutoIndicationType = theIndicationType;
}

CT_RS_IndicationType CFG_RsAutomatic::GetAutoIndicationType() const
{
    return myAutoIndicationType;

}

void CFG_RsAutomatic::SetAutoInternalIndType(CT_RS_IndicationType theIndicationType)
{
    myAutoInternalIndType = theIndicationType;
}

CT_RS_IndicationType CFG_RsAutomatic::GetAutoInternalIndType() const
{
    return myAutoInternalIndType;

}


void CFG_RsAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myForceAIS             = false;
    myForceRDI             = false;
    myForceCSFOPUInternal  = false;
    myForceAISInternal     = false;
	myLineSideProtExists   = false;
    mySuppressBackwardInd  = false;
    myAdd                  = false;
    myDrop                 = false;
    myAutoIndicationType   = CT_RS_INDICATION_UNKNOWN;
    myAutoInternalIndType  = CT_RS_INDICATION_UNKNOWN;
}

ostream& CFG_RsAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceAIS);
    theStream   << FC_InsertVar(myForceRDI);
    theStream   << FC_InsertVar(myForceCSFOPUInternal);
    theStream   << FC_InsertVar(myForceAISInternal);
	theStream   << FC_InsertVar(myLineSideProtExists);
    theStream   << FC_InsertVar(mySuppressBackwardInd);
    theStream   << FC_InsertVar(myAdd);
    theStream   << FC_InsertVar(myDrop);

    uint8 aIndicationType = (uint8) myAutoIndicationType;
    theStream   << FC_InsertVar(aIndicationType);
    uint8 aInternalIndType = (uint8) myAutoInternalIndType;
    theStream   << FC_InsertVar(aInternalIndType);

    return theStream;

}

istream& CFG_RsAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceAIS);
    theStream   >> FC_ExtractVar(myForceRDI);
    theStream   >> FC_ExtractVar(myForceCSFOPUInternal);
    theStream   >> FC_ExtractVar(myForceAISInternal);
	theStream   >> FC_ExtractVar(myLineSideProtExists);
    theStream   >> FC_ExtractVar(mySuppressBackwardInd);
    theStream   >> FC_ExtractVar(myAdd);
    theStream   >> FC_ExtractVar(myDrop);

    uint8 aIndicationType = 0;
    theStream   >> FC_ExtractVar(aIndicationType);
    myAutoIndicationType = (CT_RS_IndicationType) aIndicationType;
    uint8 aInternalIndType = 0;
    theStream   >> FC_ExtractVar(aInternalIndType);
    myAutoInternalIndType = (CT_RS_IndicationType) aInternalIndType;

    return theStream;

}

FC_Stream& CFG_RsAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceAIS;
    theStream   << myForceRDI;
    theStream   << myForceCSFOPUInternal;
    theStream   << myForceAISInternal;
	theStream   << myLineSideProtExists;
    theStream   << mySuppressBackwardInd;
    theStream   << myAdd;
    theStream   << myDrop;

    theStream   << (uint8) myAutoIndicationType;
    theStream   << (uint8) myAutoInternalIndType;

    return theStream;

}

FC_Stream& CFG_RsAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForceAIS;
    theStream   >> myForceRDI;
    theStream   >> myForceCSFOPUInternal;
    theStream   >> myForceAISInternal;
	theStream   >> myLineSideProtExists;
    theStream   >> mySuppressBackwardInd;
    theStream   >> myAdd;
    theStream   >> myDrop;

    uint8 aIndicationType = 0;
    theStream   >> aIndicationType;
    myAutoIndicationType = (CT_RS_IndicationType) aIndicationType;
    uint8 aInternalIndType = 0;
    theStream   >> aInternalIndType;
    myAutoInternalIndType = (CT_RS_IndicationType) aInternalIndType;

    return theStream;

}

void CFG_RsAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "RS AUTO  - Force AIS                          = " << DISPLAY_BOOL(myForceAIS) << endl;
    theStream   << "RS AUTO  - Force RDI                          = " << DISPLAY_BOOL(myForceRDI) << endl;
    theStream   << "RS AUTO  - Force AIS Internal                 = " << DISPLAY_BOOL(myForceAISInternal) << endl;
    theStream   << "RS AUTO  - Indication Type                    = " << DISPLAY_RS_INDICATION(myAutoIndicationType) << endl;
    theStream   << "RS AUTO  - Internal Indication Type           = " << DISPLAY_RS_INDICATION(myAutoInternalIndType) << endl;
    theStream   << "RS AUTO  - Force CSF-OPU                      = " << DISPLAY_BOOL(myForceCSFOPUInternal) << endl;
	theStream   << "RS AUTO  - Line Side Protection Exists        = " << DISPLAY_BOOL(myLineSideProtExists) << endl;
    theStream   << "RS AUTO  - Suppress Backward Indicators       = " << DISPLAY_BOOL(mySuppressBackwardInd) << endl;
    theStream   << "RS AUTO  - 1 Way Add XC                       = " << DISPLAY_BOOL(myAdd) << endl;
    theStream   << "RS AUTO  - 1 Way Drop XC                      = " << DISPLAY_BOOL(myDrop) << endl;


}
