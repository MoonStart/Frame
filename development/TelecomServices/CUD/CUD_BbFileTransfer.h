/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     April 11, 2007 Jim Beck.
 DESCRIPTION:   CUD data file transfer class.
--------------------------------------------------------------------------*/

#ifndef CUD_BBFILETRANSFER_H
#define CUD_BBFILETRANSFER_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_CUD_FileNameHandle.h>

// 
class CUD_BbFileTransfer : public TEL_BbObjectBase
{

public:

    // Class default constructor.
    CUD_BbFileTransfer();

    //Class default destructor.
    virtual ~CUD_BbFileTransfer();

    // Method to retrieve the file name handle object.
    CUD_FileNameHandle *GetFileNameHandle();

    // Method to set the file name handle.
    void SetFileNameHandle( CUD_FileNameHandle *theFileNameHandle );

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    CUD_FileNameHandle *myFileNameHandle;

};

#endif // CUD_BBFILETRANSFER_H
