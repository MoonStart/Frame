// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_HWREFRESHOTU_3C176F500382_INCLUDED
#define _INC_CFG_HWREFRESHOTU_3C176F500382_INCLUDED

#include "CFG_HwRefreshAction.h"
#include <TsPii/TSPII_Region.h>
#include "Monitoring/MON_Definitions.h"
#include "CFG_Definitions.h"

// Forward declaration of class.
//class CFG_Region;
class TSPII_FecIf;


class CFG_Otu;

//This action is invoked periodically in order to update 
//'OTU (Optical Channel Transport Unit) layer' hardware 
//registers with current 'OTU' configuration.
//##ModelId=3C176F500382
class CFG_HwRefreshOtu 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	//##ModelId=3C17AE7200C4
	CFG_HwRefreshOtu(CFG_AppIf& theCfgIf, 
                     TSPII_FecRegion& theFecPiiRegion);

	//Virtual destructor
	//##ModelId=3C17AE7102EA
	virtual ~CFG_HwRefreshOtu();

	//This method refreshes all hardware related to OTU 
	//(Optical Channel Transport Unit) layer. It reads the 
	//current value of each OTU layer parameter an invokes 
	//the corresponding PII interface. This action is 
	//normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

	//##ModelId=3C3B463A0315
    TSPII_FecRegion& myFecPiiRegion;
    CFG_TxOchAutomaticCfgRegion* myTxOchAutomaticConfigRegion;
    MON_OtuConfigRegion* myOtuMonConfigRegion;
    
};

#endif /* _INC_CFG_HWREFRESHOTU_3C176F500382_INCLUDED */
