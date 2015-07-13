//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_TcmAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_TcmAutomatic::CFG_TcmAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
    myForceBDI(false),
    myForceBIAE(false),
    mySuppressBackwardInd(false)
{
}

CFG_TcmAutomatic::~CFG_TcmAutomatic()
{
}

bool CFG_TcmAutomatic::SetForceBDI(bool theForceBDI)
{
    bool hasChanged = false;

    if(myForceBDI != theForceBDI)
    {
        myForceBDI = theForceBDI;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_TcmAutomatic::GetForceBDI() const
{
    return myForceBDI;
}

bool CFG_TcmAutomatic::SetForceBIAE(bool theForceBIAE)
{
    bool hasChanged = false;

    if(myForceBIAE != theForceBIAE)
    {
        myForceBIAE = theForceBIAE;
        hasChanged = true;
    }

    return hasChanged;
}


bool CFG_TcmAutomatic::GetForceBIAE() const
{
    return myForceBIAE;
}


bool CFG_TcmAutomatic::SetSuppressBackwardInd(bool theSuppressBackwardInd)
{
    bool hasChanged = false;
    if(mySuppressBackwardInd != theSuppressBackwardInd)
    {
        mySuppressBackwardInd = theSuppressBackwardInd;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_TcmAutomatic::GetSuppressBackwardInd() const
{
    return mySuppressBackwardInd;
}


void CFG_TcmAutomatic::Reset()
{
    //Initialize all attributes to default values.
    myForceBDI  = false;
    myForceBIAE = false;
    mySuppressBackwardInd  = false;
}

ostream& CFG_TcmAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myForceBDI);
    theStream   << FC_InsertVar(myForceBIAE);
    theStream   << FC_InsertVar(mySuppressBackwardInd);
    return theStream;

}

istream& CFG_TcmAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myForceBDI);
    theStream   >> FC_ExtractVar(myForceBIAE);
    theStream   >> FC_ExtractVar(mySuppressBackwardInd);
    return theStream;

}

FC_Stream& CFG_TcmAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << myForceBDI;
    theStream   << myForceBIAE;
    theStream   << mySuppressBackwardInd;
    return theStream;

}

FC_Stream& CFG_TcmAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myForceBDI;
    theStream   >> myForceBIAE;
    theStream   >> mySuppressBackwardInd;
    return theStream;

}

void CFG_TcmAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "TCM AUTO - Force BDI                        = " << DISPLAY_BOOL(myForceBDI) << endl;
    theStream   << "TCM AUTO - Force BIAE                       = " << DISPLAY_BOOL(myForceBIAE) << endl;
    theStream   << "TCM AUTO - Suppress Backward Indicators     = " << DISPLAY_BOOL(mySuppressBackwardInd) << endl;
}
