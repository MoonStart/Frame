/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/

#ifndef PWR_APPIF_H
#define PWR_APPIF_H

#include "AppFramework/FC_BbApp.h"

class T6100_CardIf;
//class TEL_BbRegionBase;

class PWR_AppIf : public FC_BbApp
{
public:
    /* Constructor */            PWR_AppIf(T6100_CardIf & theContext);
    virtual                      ~PWR_AppIf();
    T6100_CardIf &               GetContext();

private:
    T6100_CardIf &               myContext;
};

#endif // PWR_APPIF_H