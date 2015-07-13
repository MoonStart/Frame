//-----------------------------------------------------------------------------
//
// Copyright(c) 2012 Tellabs Transport Group. All rights reserved
// 
// Backend FTP server configuration for the PMXfer on SPM 
// 
//-----------------------------------------------------------------------------

#include <BaseClass/FC_TextStream.h>

#include <PM/PM_Def.h>
#include <PM/PM_XferBbFtpCfg.h>


PM_XferBbFtpCfg::PM_XferBbFtpCfg()
{
    Reset();
}

//--------------------------------------------------------------------------
PM_XferBbFtpCfg::~PM_XferBbFtpCfg()
{
}

//-----------------------------------------------------------------
void PM_XferBbFtpCfg::Reset()
{
    CT_FtpUrl defaultUrl("","","","","",22);

    myFtpUrl = defaultUrl;
    myInUseFlag = false;
}

//--------------------------------------------------------------------------
FC_Stream& PM_XferBbFtpCfg::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myFtpUrl;
    theStream << myInUseFlag;
    return theStream;
}

//--------------------------------------------------------------------------
FC_Stream& PM_XferBbFtpCfg::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myFtpUrl;
    theStream >> myInUseFlag;
    return theStream;
}

//--------------------------------------------------------------------------
ostream& PM_XferBbFtpCfg::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myFtpUrl);
    theStream << FC_InsertVar(myInUseFlag);
    return theStream;
}

//--------------------------------------------------------------------------
istream& PM_XferBbFtpCfg::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myFtpUrl);
    theStream >> FC_ExtractVar(myInUseFlag);
    return theStream;
}
