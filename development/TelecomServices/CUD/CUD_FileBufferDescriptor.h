/*----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :  Common Types
TARGET      :  Platform Independent
DATE        :  March 15, 2007
AUTHOR      :  Jim Beck
DESCRIPTION :  CUD File Buffer Descriptor class
-----------------------------------------------------------------------*/

#ifndef CT_CUD_FILEBUFFERDESCRIPTOR_H
#define CT_CUD_FILEBUFFERDESCRIPTOR_H

#include <ss_gdef.h>

const uint32 CUD_FILE_BUFFER_PATH_SIZE_MAX = 11000;

class CUD_FileBufferDescriptor
{

public:

	// Default Constructor
	CUD_FileBufferDescriptor();   

	// Destructor
	~CUD_FileBufferDescriptor();

	// Method to retrieve the buffer pointer.
	char* GetBufferPtr();

	// Method to retrieve the buffer size.
	uint32 GetBufferSize();

	// Method to set the buffer size.
	void SetBufferSize( uint32 theSize );

private:

	// Buffer pointer.
	char* myBufferPtr;

	// Buffer size.
	uint32 myBufferSize;
};


//------------------------------------------------------------------
inline
char* CUD_FileBufferDescriptor::GetBufferPtr()
{
	return myBufferPtr;
}

//------------------------------------------------------------------
inline
uint32 CUD_FileBufferDescriptor::GetBufferSize()
{
	return myBufferSize;
}

//------------------------------------------------------------------
inline
void CUD_FileBufferDescriptor::SetBufferSize( uint32 theSize )
{
	myBufferSize = theSize;
}

#endif //CT_CUD_FILEBUFFERDESCRIPTOR_H

