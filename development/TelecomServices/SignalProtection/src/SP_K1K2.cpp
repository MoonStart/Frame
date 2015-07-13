// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_K1K2.h"
#include <BaseClass/FC_TextStream.h>


//##ModelId=390583F901AF
SP_K1K2::SP_K1K2():
    destination(0),
    source(0),
    path(0),
    request(0),
    status(0)
{
}

//##ModelId=390583F901B0
SP_K1K2::~SP_K1K2()
{
}

//##ModelId=3B8BC9D80206
SP_K1K2::SP_K1K2(const SP_K1K2 &theK1K2) : 
    destination (theK1K2.destination),
    path (theK1K2.path),
    request (theK1K2.request),
    source (theK1K2.source),
    status (theK1K2.status)
{
}

//##ModelId=39ACEFB201DD
bool SP_K1K2::operator==(const SP_K1K2 &rhs) const
{
    return ( (destination == rhs.destination) &&
             (path == rhs.path) &&
             (request == rhs.request) &&
             (source == rhs.source) &&
             (status == rhs.status) );
}

//##ModelId=3B8BC9D80256
bool SP_K1K2::operator!=(const SP_K1K2 &rhs) const
{
    return ( !(*this == rhs) );
}

//##ModelId=3B8BC9D8022E
SP_K1K2& SP_K1K2::operator=(const SP_K1K2 &rhs)
{
    destination = rhs.destination;
    path = rhs.path;
    request = rhs.request;
    source = rhs.source;
    status = rhs.status;

    return *this;
}


//##ModelId=3B8BC9D80198
ostream& SP_K1K2::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(request);
    theStream<<FC_InsertVar(destination);
    theStream<<FC_InsertVar(source);
    theStream<<FC_InsertVar(path);
    theStream<<FC_InsertVar(status);

    return theStream;
}

//##ModelId=3B8BC9D80166
istream& SP_K1K2::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(request);
    theStream>>FC_ExtractVar(destination);
    theStream>>FC_ExtractVar(source);
    theStream>>FC_ExtractVar(path);
    theStream>>FC_ExtractVar(status);

    return theStream;
}

//##ModelId=3B8BC9D8012A
FC_Stream& SP_K1K2::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<request;
    theStream<<destination;
    theStream<<source;
    theStream<<path;
    theStream<<status;

    return theStream;
}

//##ModelId=3B8BC9D800F8
FC_Stream& SP_K1K2::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>request;
    theStream>>destination;
    theStream>>source;
    theStream>>path;
    theStream>>status;

    return theStream;
}

//##ModelId=3B8BC9D801D4
FC_Stream& SP_K1K2::SnapshotWrite(FC_Stream& theStream)
{
	theStream << "      request     = " << DISPLAY_SP_K1Request_CLSR(request) << " / " << DISPLAY_SP_K1Request_1PLUS1(request) << endl;
	theStream << "      destination = " << DISPLAY_CT_SP_NodeID(destination)  << endl;
	theStream << "      source      = " << DISPLAY_CT_SP_NodeID(source)       << endl;
	theStream << "      path        = " << DISPLAY_SP_ClsrPath(path)          << endl;
	theStream << "      status      = " << DISPLAY_SP_Status_CLSR(status)     << " / " << DISPLAY_SP_Status_1PLUS1(status) << endl;
	return theStream;
}

//##ModelId=3BBC9B080368
uint8 SP_K1K2::GetK1() const
{
    return ((request & 0x0F) << 4) | (destination & 0x0F);
}

//##ModelId=3BBC9B080386
uint8 SP_K1K2::GetK2() const
{
    return ((source  & 0x0F) << 4) | (path ? 0x08 : 0x00) | (status & 0x07);
}

