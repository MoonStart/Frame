// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../TSXC_CQMResponse.h"
#include <BaseClass/FC_TextStream.h>

// -----------------------------------------------------------------------------------------------------
//  Constructor
// -----------------------------------------------------------------------------------------------------
TSXC_CQMResponse::TSXC_CQMResponse()
{
    myCQMResponse.type  = 0;
    myCQMResponse.reqid = 0;
    myCQMResponse.shelf = 0;
    myCQMResponse.slot  = 0;
    myCQMResponse.port  = 0; 
    myCQMResponse.step  = 0;
    myCQMResponse.qmgrIdx  = 0;
}

// -----------------------------------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------------------------------
TSXC_CQMResponse::~TSXC_CQMResponse()
{
}

// -----------------------------------------------------------------------------------------------------
// Methods to set object attributes
// -----------------------------------------------------------------------------------------------------
void TSXC_CQMResponse::SetCQMResponse(CT_XC_CQMID theResponse)
{
	myCQMResponse = theResponse;
}

// -----------------------------------------------------------------------------------------------------
// Methods to get object attributes
// -----------------------------------------------------------------------------------------------------
CT_XC_CQMID TSXC_CQMResponse::GetCQMResponse()
{
	return myCQMResponse;
}

// -----------------------------------------------------------------------------------------------------
ostream& TSXC_CQMResponse::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myCQMResponse.type);
    theStream<<FC_InsertVar(myCQMResponse.reqid);
    theStream<<FC_InsertVar(myCQMResponse.qmgrIdx);
    theStream<<FC_InsertVar(myCQMResponse.step);
	return theStream;
}

istream& TSXC_CQMResponse::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myCQMResponse.type);
    theStream>>FC_ExtractVar(myCQMResponse.reqid);
    theStream>>FC_ExtractVar(myCQMResponse.qmgrIdx);
    theStream>>FC_ExtractVar(myCQMResponse.step);
    return theStream;
}

// -----------------------------------------------------------------------------------------------------
FC_Stream& TSXC_CQMResponse::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myCQMResponse.type;
    theStream<<myCQMResponse.reqid;
    theStream<<myCQMResponse.qmgrIdx;
    theStream<<myCQMResponse.step;
	return theStream;
}

FC_Stream& TSXC_CQMResponse::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myCQMResponse.type;
    theStream>>myCQMResponse.reqid;
    theStream>>myCQMResponse.qmgrIdx;
    theStream>>myCQMResponse.step;
    return theStream;
}
// -----------------------------------------------------------------------------------------------------
