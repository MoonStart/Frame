/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/

#include "PowerManagement/PWR_Utils.h"
#include <cstring>

PWR_Utils* PWR_Utils::ourInstance = NULL;

////////////////////////////////////////////////////////////////////////////////
PWR_Utils & PWR_Utils::GetInstance()
{
	if (ourInstance == NULL)
        ourInstance = new PWR_Utils();

	return *ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
void PWR_Utils::DeleteInstance()
{
    delete ourInstance;
    ourInstance = NULL;
}

////////////////////////////////////////////////////////////////////////////////
PWR_Utils::PWR_Utils()
{
}

////////////////////////////////////////////////////////////////////////////////
PWR_Utils::~PWR_Utils()
{
}

///////////////////////////////////////////////////////////////////////////////
void PWR_Utils::GetDateStampStr(time_t theTime, char **pBuf, uint32 len)
{
	if(*pBuf == NULL)
		return;

	memset(*pBuf, 0x00, len);

	struct tm *stamp = NULL;

	if( (stamp = localtime(&theTime)) != NULL)
	{
		sprintf(*pBuf, "%2.2d/%2.2d/%4.4d",
				stamp->tm_mon+1, stamp->tm_mday, stamp->tm_year+1900);
	}
}

///////////////////////////////////////////////////////////////////////////////
void PWR_Utils::GetTimeStampStr(time_t theTime, char **pBuf, uint32 len)
{
	if(*pBuf == NULL)
		return;

	memset(*pBuf, 0x00, len);

	struct tm *stamp = NULL;

	if( (stamp = localtime(&theTime)) != NULL)
	{
		sprintf(*pBuf, "%2.2d:%2.2d:%2.2d",
				stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
	}
}
///////////////////////////////////////////////////////////////////////////////
void PWR_Utils::GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len)
{
	if(*pBuf == NULL)
		return;

	memset(*pBuf, 0x00, len);

	struct tm *stamp = NULL;

	if( (stamp = localtime(&theTime)) != NULL)
	{
		sprintf(*pBuf, "%2.2d/%2.2d/%4.4d-%2.2d:%2.2d:%2.2d",
				stamp->tm_mon+1, stamp->tm_mday, stamp->tm_year+1900,
				stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
	}
}
