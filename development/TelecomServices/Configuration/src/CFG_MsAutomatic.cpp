//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_MsAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_MsAutomatic::CFG_MsAutomatic(uint32 theIndex):
    CFG_Object(theIndex)
{
    Reset();
}

CFG_MsAutomatic::~CFG_MsAutomatic()
{
}

bool CFG_MsAutomatic::SetIsActiveRef(bool theIsActiveRef)
{
    bool hasChanged = false;
    if(myIsActiveRef != theIsActiveRef)
    {
        myIsActiveRef = theIsActiveRef;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_MsAutomatic::GetIsActiveRef() const
{
    return myIsActiveRef;
}


bool CFG_MsAutomatic::SetSelectedRefSSM(CT_FAC_RxSsm theSelectedRefSSM)
{
    bool hasChanged = false;
    if(mySelectedRefSSM != theSelectedRefSSM)
    {
        mySelectedRefSSM = theSelectedRefSSM;
        hasChanged = true;
    }
    return hasChanged;
}

CT_FAC_RxSsm CFG_MsAutomatic::GetSelectedRefSSM() const
{
    return mySelectedRefSSM;
}


void CFG_MsAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myIsActiveRef    = false;
    mySelectedRefSSM = CT_TEL_SUPPORTED_DEFAULT_SSM;
}

ostream& CFG_MsAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myIsActiveRef);
    uint32 aSsm = (uint32) mySelectedRefSSM;
    theStream << FC_InsertVar(aSsm);
    return theStream;

}

istream& CFG_MsAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myIsActiveRef);
    uint32 aSsm;
    theStream >> FC_ExtractVar(aSsm);
    mySelectedRefSSM = (CT_FAC_RxSsm) aSsm;
    return theStream;

}

FC_Stream& CFG_MsAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myIsActiveRef;
    uint32 aSsm = (uint32) mySelectedRefSSM;
    theStream << aSsm;
    return theStream;

}

FC_Stream& CFG_MsAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myIsActiveRef;
    uint32 aSsm;
    theStream >> aSsm;
    mySelectedRefSSM = (CT_FAC_RxSsm) aSsm;

    return theStream;

}

void CFG_MsAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "MS AUTO  - Is Active Reference                  = " << DISPLAY_BOOL(myIsActiveRef) << endl;
    theStream   << "MS AUTO  - Selected Reference SSM               = " << display_RXSSM(mySelectedRefSSM) << endl;
}

