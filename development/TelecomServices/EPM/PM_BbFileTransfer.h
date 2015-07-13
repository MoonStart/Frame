/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     May 12, 2006 Larry Wolfrum.
 DESCRIPTION:   PM data file transfer class.
--------------------------------------------------------------------------*/

#ifndef PM_BBFILETRANSFER_H
#define PM_BBFILETRANSFER_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_PM_FileNameHandle.h>

// 
class PM_BbFileTransfer : public TEL_BbObjectBase
{

public:

	// Class default constructor.
    PM_BbFileTransfer();

    //Class default destructor.
    virtual ~PM_BbFileTransfer();

	// Method to retrieve the file name handle object.
	PM_FileNameHandle *GetFileNameHandle();

	// Method to set the file name handle.
	void SetFileNameHandle( PM_FileNameHandle *theFileNameHandle );

	//Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

	PM_FileNameHandle *myFileNameHandle;

};

#endif // PM_BBFILETRANSFER_H
