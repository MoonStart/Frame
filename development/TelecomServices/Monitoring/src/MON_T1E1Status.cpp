// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_T1E1Status.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_T1E1Status::MON_T1E1Status(uint32 theIndex):
    MON_Object(theIndex)
{
    MON_Object::Reset();
}

MON_T1E1Status::~MON_T1E1Status(void)
{
    // Nothing to do for now.

}

CT_FAC_RxSsm MON_T1E1Status::GetRxSsm() const 
{
    return myRxSsm;
}

bool MON_T1E1Status::SetRxSsm(CT_FAC_RxSsm theSsm) 
{
    bool hasChanged = false;
    if (!(myRxSsm == theSsm))
    {
        myRxSsm = theSsm;
        hasChanged = true;
    }

    return hasChanged;
}

void MON_T1E1Status::Reset(void)
{ 
    myRxSsm = CT_RxSsm_DUS;
}

ostream& MON_T1E1Status::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);
    uint32 aSsm = (uint32) myRxSsm;
    theStream << FC_InsertVar(aSsm);
    return theStream;

}

istream& MON_T1E1Status::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
    uint32 aSsm;
    theStream >> FC_ExtractVar(aSsm);
    myRxSsm = (CT_FAC_RxSsm) aSsm;
    return theStream;

}

FC_Stream& MON_T1E1Status::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    uint32 aSsm = (uint32) myRxSsm;
    theStream << aSsm;
    return theStream;

}

FC_Stream& MON_T1E1Status::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);  
    uint32 aSsm;
    theStream >> aSsm;
    myRxSsm = (CT_FAC_RxSsm) aSsm;
    return theStream;

}

void MON_T1E1Status::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    FC_FmtFlags previousFlags = fc_cout.Flags();

    fc_cout.Setf(ios::hex, ios::basefield);    
    theStream   << "T1E1    - Received SSM Value            = " << display_RXSSM(myRxSsm) << endl;
    fc_cout.Flags(previousFlags);
}
