// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_UnitStatus.h"
#include <BaseClass/FC_TextStream.h>


//##ModelId=38E201F10368
SP_UnitStatus::SP_UnitStatus()
{
}

//##ModelId=3932D1E000FD
SP_UnitStatus::SP_UnitStatus(const SP_UnitStatus& theUnit)
{
}

//##ModelId=39ACEFB7027B
SP_UnitStatus& SP_UnitStatus::operator=(const SP_UnitStatus& theUnit)
{
    return *this;
}

//##ModelId=39ACEFB701DA
bool SP_UnitStatus::operator==(const SP_UnitStatus& theUnit) const
{
    return true;
}


//##ModelId=38E201F103A4
SP_UnitStatus::~SP_UnitStatus()
{
}


//##ModelId=3932D1DF034B
ostream& SP_UnitStatus::WriteObject( ostream& theStream )
{
    return theStream;
}

//##ModelId=3932D1DF01E2
istream& SP_UnitStatus::ReadObject( istream& theStream )
{
    return theStream;
}

//##ModelId=39ACEFB700CC
FC_Stream& SP_UnitStatus::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=39ACEFB70018
FC_Stream& SP_UnitStatus::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=3B8BC9DE0327
void SP_UnitStatus::Init(restart_type theRestartType)
{
}
