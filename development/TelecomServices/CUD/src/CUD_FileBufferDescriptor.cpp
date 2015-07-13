/*----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

SUBSYSTEM   :  Common Types
TARGET      :  Platform Independent
DATE        :  March 15, 2007
AUTHOR      :  Jim Beck
DESCRIPTION :  Configuration file Upload/Download File Buffer Descriptor class
-----------------------------------------------------------------------*/

#include <CUD/CUD_FileBufferDescriptor.h>

//-----------------------------------------------------------------
CUD_FileBufferDescriptor::CUD_FileBufferDescriptor()
{
	myBufferPtr = new char[CUD_FILE_BUFFER_PATH_SIZE_MAX];
}

//-----------------------------------------------------------------
CUD_FileBufferDescriptor::~CUD_FileBufferDescriptor()
{
	delete myBufferPtr;
}

