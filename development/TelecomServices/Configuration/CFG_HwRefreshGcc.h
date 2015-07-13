// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHGCC_
#define _CFG_HWREFRESHGCC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_GccIf.h>
#include <TsPii/TSPII_GccMapIf.h>

#include <CommonTypes/CT_DCC_Definitions.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_GcclIf;
class TSPII_GcclMapIf;

class CFG_GccProt;

//This action is invoked periodically in order to update 
//GCC hardware registers with current 'Gcc' configuration.
class CFG_HwRefreshGcc 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshGcc(CFG_AppIf& theCfgIf,
                     CFG_GccAutomaticCfgRegion* theAutomaticCfgRegion,
                     TSPII_GccRegion& theGccPiiRegion,
                     TSPII_GccMapRegion& theGccMapPiiRegion,
                     uint8 theNumLinks,
                     CFG_AppIf* thePprfCfgApp = NULL);

	//Virtual destructor
	virtual ~CFG_HwRefreshGcc();

	//This method refreshes all hardware related to SONET/SDH 
	//high order path layer. It reads the current value 
	//of each Gcc layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_GccRegion& myGccPiiRegion;
    TSPII_GccMapRegion& myGccMapPiiRegion;
    CFG_GccAutomaticCfgRegion* myAutomaticCfgRegion;

    CFG_AppIf* myPprfCfgApp;

    CT_DCC_LinkType myLastSentLinkType;
    bool  myFirstRefreshAction;

    uint8 myNumLinks;

    vector<TSPII_GccMapRecord>  myTspiiGccMapRecords;
};

#endif /* _CFG_HWREFRESHGCC_ */
