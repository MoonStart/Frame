/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     April 11, 2007 Jim Beck.
 DESCRIPTION:   CUD data file transfer class.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <CUD/CUD_BbFileTransfer.h>


//-----------------------------------------------------------------
CUD_BbFileTransfer::CUD_BbFileTransfer()
{
    myFileNameHandle = new CUD_FileNameHandle;
}

//-----------------------------------------------------------------
CUD_BbFileTransfer::~CUD_BbFileTransfer()
{
}

//-----------------------------------------------------------------
CUD_FileNameHandle* CUD_BbFileTransfer::GetFileNameHandle()
{
    return myFileNameHandle;
}

//-----------------------------------------------------------------
void CUD_BbFileTransfer::SetFileNameHandle( CUD_FileNameHandle *theFileNameHandle )
{
   *myFileNameHandle = *theFileNameHandle;
}

//-----------------------------------------------------------------
FC_Stream& CUD_BbFileTransfer::WriteObjectBinary( FC_Stream& theStream )
{
    // Write the file name handle data.
    (*myFileNameHandle).WriteObjectBinary( theStream );

    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& CUD_BbFileTransfer::ReadObjectBinary( FC_Stream& theStream )
{
    // Read the file name handle data.
    (*myFileNameHandle).ReadObjectBinary( theStream );

    return theStream;
}

//-----------------------------------------------------------------
ostream& CUD_BbFileTransfer::WriteObject( ostream& theStream )
{
    // Write the file name handle data.
    (*myFileNameHandle).WriteObject( theStream );

    return theStream;
}

//-----------------------------------------------------------------
istream& CUD_BbFileTransfer::ReadObject( istream& theStream )
{
    // Read the file name handle data.
    (*myFileNameHandle).ReadObject( theStream );

    return theStream;
}


