//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OduAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_OduAutomatic::CFG_OduAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
    myForceBDI(false),
    myForceOCI(false),
    myForceLCK(false),
    myForceAIS(false),
    myForceInternalOCI(false),
    myForceInternalLCK(false),
    myForceInternalAIS(false),
    mySuppressBackwardInd(false),
    myAdd(false),
    myDrop(false),
    myTxPayloadType(CT_TEL_PSI_UNAVAILABLE),
    myTribSize(CT_TEL_TS_UNKNOWN)
{
}

CFG_OduAutomatic::~CFG_OduAutomatic()
{
}

bool CFG_OduAutomatic::SetForceBDI(bool theForceBDI)
{
    bool hasChanged = false;

    if(myForceBDI != theForceBDI)
    {
        myForceBDI = theForceBDI;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceBDI() const
{
    return myForceBDI;
}

bool CFG_OduAutomatic::SetForceOCI(bool theForceOCI)
{
    bool hasChanged = false;

    if(myForceOCI != theForceOCI)
    {
        myForceOCI = theForceOCI;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceOCI() const
{
    return myForceOCI;
}

bool CFG_OduAutomatic::SetForceLCK(bool theForceLCK)
{
    bool hasChanged = false;

    if(myForceLCK != theForceLCK)
    {
        myForceLCK = theForceLCK;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceLCK() const
{
    return myForceLCK;
}


bool CFG_OduAutomatic::SetForceAIS(bool theForceAIS)
{
    bool hasChanged = false;

    if(myForceAIS != theForceAIS)
    {
        myForceAIS = theForceAIS;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceAIS() const
{
    return myForceAIS;
}


bool CFG_OduAutomatic::SetForceInternalOCI(bool theForceInternalOCI)
{
    bool hasChanged = false;

    if(myForceInternalOCI != theForceInternalOCI)
    {
        myForceInternalOCI = theForceInternalOCI;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceInternalOCI() const
{
    return myForceInternalOCI;
}

bool CFG_OduAutomatic::SetForceInternalLCK(bool theForceInternalLCK)
{
    bool hasChanged = false;

    if(myForceInternalLCK != theForceInternalLCK)
    {
        myForceInternalLCK = theForceInternalLCK;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceInternalLCK() const
{
    return myForceInternalLCK;
}

bool CFG_OduAutomatic::SetForceInternalAIS(bool theForceInternalAIS)
{
    bool hasChanged = false;

    if(myForceInternalAIS != theForceInternalAIS)
    {
        myForceInternalAIS = theForceInternalAIS;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_OduAutomatic::GetForceInternalAIS() const
{
    return myForceInternalAIS;
}


bool CFG_OduAutomatic::SetSuppressBackwardInd(bool theSuppressBackwardInd)
{
    bool hasChanged = false;
    if(mySuppressBackwardInd != theSuppressBackwardInd)
    {
        mySuppressBackwardInd = theSuppressBackwardInd;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OduAutomatic::GetSuppressBackwardInd() const
{
    return mySuppressBackwardInd;
}

bool CFG_OduAutomatic::SetAdd(bool theAdd)
{
    bool hasChanged = false;
    if(myAdd != theAdd)
    {
        myAdd = theAdd;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OduAutomatic::GetAdd() const
{
    return myAdd;
}

bool CFG_OduAutomatic::SetDrop(bool theDrop)
{
    bool hasChanged = false;
    if(myDrop != theDrop)
    {
        myDrop = theDrop;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OduAutomatic::GetDrop() const
{
    return myDrop;
}

bool CFG_OduAutomatic::SetTxPayloadType(CT_TEL_PayloadSignalId theTxPayloadType)
{
    bool hasChanged = false;
    if(myTxPayloadType != theTxPayloadType)
    {
        myTxPayloadType = theTxPayloadType;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_PayloadSignalId CFG_OduAutomatic::GetTxPayloadType() const
{
    return myTxPayloadType;
}

bool CFG_OduAutomatic::SetTribSize(CT_TEL_TS_SIZE theTribSize)
{
    bool hasChanged = false;
    if(myTribSize != theTribSize)
    {
        myTribSize = theTribSize;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_TS_SIZE CFG_OduAutomatic::GetTribSize() const
{
    return (CT_TEL_TS_SIZE)myTribSize;
}

void CFG_OduAutomatic::Reset()
{
    //Initialize all attributes to default values.
    myForceBDI = false;
    myForceOCI = false;
    myForceLCK = false;
    myForceAIS = false;
    myForceInternalOCI = false;
    myForceInternalLCK = false;
    myForceInternalAIS = false;
    mySuppressBackwardInd  = false;
    myAdd                  = false;
    myDrop                 = false;
    myTxPayloadType = CT_TEL_PSI_UNAVAILABLE;
    myTribSize = CT_TEL_TS_UNKNOWN;
}

ostream& CFG_OduAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceBDI);
    theStream   << FC_InsertVar(myForceOCI);
    theStream   << FC_InsertVar(myForceLCK);
    theStream   << FC_InsertVar(myForceAIS);
    theStream   << FC_InsertVar(myForceInternalOCI);
    theStream   << FC_InsertVar(myForceInternalLCK);
    theStream   << FC_InsertVar(myForceInternalAIS);
    theStream   << FC_InsertVar(mySuppressBackwardInd);
    theStream   << FC_InsertVar(myAdd);
    theStream   << FC_InsertVar(myDrop);
    theStream   << FC_InsertVar(myTxPayloadType);

    uint8 aTribSize = (uint8)myTribSize;
    theStream   << FC_InsertVar(aTribSize);

    return theStream;

}

istream& CFG_OduAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceBDI);
    theStream   >> FC_ExtractVar(myForceOCI);
    theStream   >> FC_ExtractVar(myForceLCK);
    theStream   >> FC_ExtractVar(myForceAIS);
    theStream   >> FC_ExtractVar(myForceInternalOCI);
    theStream   >> FC_ExtractVar(myForceInternalLCK);
    theStream   >> FC_ExtractVar(myForceInternalAIS);
    theStream   >> FC_ExtractVar(mySuppressBackwardInd);
    theStream   >> FC_ExtractVar(myAdd);
    theStream   >> FC_ExtractVar(myDrop);
    theStream   >> FC_ExtractVar(myTxPayloadType);

    uint8 aTribSize;
    theStream   >> FC_ExtractVar(aTribSize);
    myTribSize = (CT_TEL_TS_SIZE)aTribSize;

    return theStream;

}

FC_Stream& CFG_OduAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceBDI;
    theStream   << myForceOCI;
    theStream   << myForceLCK;
    theStream   << myForceAIS;
    theStream   << myForceInternalOCI;
    theStream   << myForceInternalLCK;
    theStream   << myForceInternalAIS;
    theStream   << mySuppressBackwardInd;
    theStream   << myAdd;
    theStream   << myDrop;
    theStream   << myTxPayloadType;

    uint8 aTribSize = (uint8) myTribSize;
    theStream   << aTribSize;

    return theStream;

}

FC_Stream& CFG_OduAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForceBDI;
    theStream   >> myForceOCI;
    theStream   >> myForceLCK;
    theStream   >> myForceAIS;
    theStream   >> myForceInternalOCI;
    theStream   >> myForceInternalLCK;
    theStream   >> myForceInternalAIS;
    theStream   >> mySuppressBackwardInd;
    theStream   >> myAdd;
    theStream   >> myDrop;
    theStream   >> myTxPayloadType;

    uint8 aTribSize;
    theStream   >> aTribSize;
    myTribSize = (CT_TEL_TS_SIZE) aTribSize;

    return theStream;

}

void CFG_OduAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "ODU AUTO - Force BDI                        = " << DISPLAY_BOOL(myForceBDI) << endl;
    theStream   << "ODU AUTO - Force OCI                        = " << DISPLAY_BOOL(myForceOCI) << endl;
    theStream   << "ODU AUTO - Force LCK                        = " << DISPLAY_BOOL(myForceLCK) << endl;
    theStream   << "ODU AUTO - Force AIS                        = " << DISPLAY_BOOL(myForceAIS) << endl;
    theStream   << "ODU AUTO - Force Internal OCI               = " << DISPLAY_BOOL(myForceInternalOCI) << endl;
    theStream   << "ODU AUTO - Force Internal LCK               = " << DISPLAY_BOOL(myForceInternalLCK) << endl;
    theStream   << "ODU AUTO - Force Internal AIS               = " << DISPLAY_BOOL(myForceInternalAIS) << endl;
    theStream   << "ODU AUTO - Suppress Backward Indicators     = " << DISPLAY_BOOL(mySuppressBackwardInd) << endl;
    theStream   << "ODU AUTO - 1 Way Add XC                     = " << DISPLAY_BOOL(myAdd) << endl;
    theStream   << "ODU AUTO - 1 Way Drop XC                    = " << DISPLAY_BOOL(myDrop) << endl;
}
