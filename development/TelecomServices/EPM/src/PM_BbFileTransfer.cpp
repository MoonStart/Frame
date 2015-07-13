/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     May 12, 2006 Larry Wolfrum.
 DESCRIPTION:   PM data file transfer class.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <EPM/PM_BbFileTransfer.h>


//-----------------------------------------------------------------
PM_BbFileTransfer::PM_BbFileTransfer()
{
	myFileNameHandle = new PM_FileNameHandle;
}

//-----------------------------------------------------------------
PM_BbFileTransfer::~PM_BbFileTransfer()
{
}

//-----------------------------------------------------------------
PM_FileNameHandle* PM_BbFileTransfer::GetFileNameHandle()
{
	return myFileNameHandle;
}

//-----------------------------------------------------------------
void PM_BbFileTransfer::SetFileNameHandle( PM_FileNameHandle *theFileNameHandle )
{
   *myFileNameHandle = *theFileNameHandle;
}

//-----------------------------------------------------------------
FC_Stream& PM_BbFileTransfer::WriteObjectBinary( FC_Stream& theStream )
{
	// Write the file name handle data.
	(*myFileNameHandle).WriteObjectBinary( theStream );

    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& PM_BbFileTransfer::ReadObjectBinary( FC_Stream& theStream )
{
	// Read the file name handle data.
	(*myFileNameHandle).ReadObjectBinary( theStream );

    return theStream;
}

//-----------------------------------------------------------------
ostream& PM_BbFileTransfer::WriteObject( ostream& theStream )
{
		// Write the file name handle data.
	(*myFileNameHandle).WriteObject( theStream );

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbFileTransfer::ReadObject( istream& theStream )
{
	// Read the file name handle data.
	(*myFileNameHandle).ReadObject( theStream );

    return theStream;

}


