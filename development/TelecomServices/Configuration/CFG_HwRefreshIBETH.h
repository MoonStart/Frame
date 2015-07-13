// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHIBETH_
#define _CFG_HWREFRESHIBETH_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_IBETHIf.h>

#include <CommonTypes/CT_IBETH_Definitions.h>

class CFG_HwRefreshIBETH 
: public CFG_HwRefreshAction
{
public:
	
	CFG_HwRefreshIBETH(CFG_AppIf& theCfgIf,                  
                     TSPII_IBETHRegion& theIBETHPiiRegion,
                     uint8 theNumLinks);

	//Virtual destructor
	virtual ~CFG_HwRefreshIBETH();

	//This method refreshes all hardware related to SONET/SDH 
	//high order path layer. It reads the current value 
	//of each Gcc layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_IBETHRegion& myIBETHPiiRegion;

    uint8 myNumLinks;

};

#endif /* _CFG_HWREFRESHGCC_ */
