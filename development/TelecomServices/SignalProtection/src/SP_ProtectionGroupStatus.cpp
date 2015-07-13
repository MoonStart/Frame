// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ProtectionGroupStatus.h"


//##ModelId=39ACEFA403DC
SP_ProtectionGroupStatus::SP_ProtectionGroupStatus()
{
}

//##ModelId=39ACEFA50008
SP_ProtectionGroupStatus::SP_ProtectionGroupStatus(const SP_ProtectionGroupStatus& theStatus)
{
}

//##ModelId=39ACEFA40382
bool SP_ProtectionGroupStatus::operator==(const SP_ProtectionGroupStatus& theStatus) const
{
    return true;
}

//##ModelId=39ACEFA40332
SP_ProtectionGroupStatus& SP_ProtectionGroupStatus::operator=(const SP_ProtectionGroupStatus& theStatus)
{
    return *this;
}


//##ModelId=38E201EB01A7
SP_ProtectionGroupStatus::~SP_ProtectionGroupStatus()
{
}


//##ModelId=3932D1CD00F6
ostream& SP_ProtectionGroupStatus::WriteObject( ostream& theStream )
{
    return theStream;
}

//##ModelId=3932D1CD0056
istream& SP_ProtectionGroupStatus::ReadObject( istream& theStream )
{
    return theStream;
}

//##ModelId=39ACEFA402CD
FC_Stream& SP_ProtectionGroupStatus::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=39ACEFA40223
FC_Stream& SP_ProtectionGroupStatus::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream;
}
