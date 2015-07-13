//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OtuAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_OtuAutomatic::CFG_OtuAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
    myForceBDI(false),
    mySendDefectToMate(false),
    mySuppressBackwardInd(false)
{
}

CFG_OtuAutomatic::~CFG_OtuAutomatic()
{
}

bool CFG_OtuAutomatic::SetForceBDI(bool theForceBDI)
{
    bool hasChanged = false;
    if(myForceBDI != theForceBDI)
    {
        myForceBDI = theForceBDI;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OtuAutomatic::GetForceBDI() const
{
    return myForceBDI;
}


bool CFG_OtuAutomatic::SetSuppressBackwardInd(bool theSuppressBackwardInd)
{
    bool hasChanged = false;
    if(mySuppressBackwardInd != theSuppressBackwardInd)
    {
        mySuppressBackwardInd = theSuppressBackwardInd;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OtuAutomatic::GetSuppressBackwardInd() const
{
    return mySuppressBackwardInd;
}

bool CFG_OtuAutomatic::SetSendDefectToMate(bool theSendDefectToMate)
{
    bool hasChanged = false;
    if(mySendDefectToMate != theSendDefectToMate)
    {
        mySendDefectToMate = theSendDefectToMate;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OtuAutomatic::GetSendDefectToMate() const
{
    return mySendDefectToMate;
}



void CFG_OtuAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myForceBDI = false;
    mySuppressBackwardInd = false;
    mySendDefectToMate = false;
}

ostream& CFG_OtuAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceBDI);
    theStream   << FC_InsertVar(mySuppressBackwardInd);
    theStream   << FC_InsertVar(mySendDefectToMate);
    return theStream;

}

istream& CFG_OtuAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceBDI);
    theStream   >> FC_ExtractVar(mySuppressBackwardInd);
    theStream   >> FC_ExtractVar(mySendDefectToMate);
    return theStream;

}

FC_Stream& CFG_OtuAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceBDI;
    theStream   << mySuppressBackwardInd;
    theStream   << mySendDefectToMate;
    return theStream;

}

FC_Stream& CFG_OtuAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForceBDI;
    theStream   >> mySuppressBackwardInd;
    theStream   >> mySendDefectToMate;
    return theStream;

}

void CFG_OtuAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "OTU AUTO - Force BDI                        = " << DISPLAY_BOOL(myForceBDI) << endl;
    theStream   << "OTU AUTO - Suppress Backward Indicators     = " << DISPLAY_BOOL(mySuppressBackwardInd) << endl;
    theStream   << "OTU AUTO - Send Defect To Mate              = " << DISPLAY_BOOL(mySendDefectToMate) << endl;
}
