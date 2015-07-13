/*----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :  Common Types
TARGET      :  Platform Independent
AUTHOR      :  May 24, 2006 - Larry M. Wolfrum
DESCRIPTION :  PM File Buffer Descriptor class
-----------------------------------------------------------------------*/

#include <EPM/PM_FileBufferDescriptor.h>

//-----------------------------------------------------------------
PM_FileBufferDescriptor::PM_FileBufferDescriptor()
{
	myBufferPtr = new char[PM_FILE_BUFFER_PATH_SIZE_MAX];
}

//-----------------------------------------------------------------
PM_FileBufferDescriptor::~PM_FileBufferDescriptor()
{
	delete myBufferPtr;
}

