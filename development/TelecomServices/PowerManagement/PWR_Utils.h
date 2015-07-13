/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/
#ifndef PWR_UTILS_H__
#define PWR_UTILS_H__

#include <time.h>
#include "PowerManagement/PWR_Region.h"

class PWR_Utils
{
public:
    virtual                     ~PWR_Utils();
    static PWR_Utils &			GetInstance();
    static void                 DeleteInstance();

	void 						GetDateStampStr(time_t theTime, char **pBuf, uint32 len);
	void 						GetTimeStampStr(time_t theTime, char **pBuf, uint32 len);
	void 						GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len);

private:
    /* Constructor */           PWR_Utils();

    static PWR_Utils *	ourInstance;
};

#endif //PWR_UTILS_H__