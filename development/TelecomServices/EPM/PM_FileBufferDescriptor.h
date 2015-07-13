/*----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :  Common Types
TARGET      :  Platform Independent
AUTHOR      :  May 24, 2006 - Larry M. Wolfrum
DESCRIPTION :  PM File Buffer Descriptor class
-----------------------------------------------------------------------*/

#ifndef CT_PM_FILEBUFFERDESCRIPTOR_H
#define CT_PM_FILEBUFFERDESCRIPTOR_H

#include <ss_gdef.h>

const uint32 PM_FILE_BUFFER_PATH_SIZE_MAX = 24000;

class PM_FileBufferDescriptor
{

public:

	// Default Constructor
	PM_FileBufferDescriptor();   

	// Destructor
	~PM_FileBufferDescriptor();

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
char* PM_FileBufferDescriptor::GetBufferPtr()
{
	return myBufferPtr;
}

//------------------------------------------------------------------
inline
uint32 PM_FileBufferDescriptor::GetBufferSize()
{
	return myBufferSize;
}

//------------------------------------------------------------------
inline
void PM_FileBufferDescriptor::SetBufferSize( uint32 theSize )
{
	myBufferSize = theSize;
}

#endif //CT_PM_FILEBUFFERDESCRIPTOR_H

