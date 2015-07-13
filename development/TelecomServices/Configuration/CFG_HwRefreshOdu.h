// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CFG_HWREFRESHODU_3C17A8F002C6_INCLUDED
#define _INC_CFG_HWREFRESHODU_3C17A8F002C6_INCLUDED

#include "CFG_HwRefreshAction.h"
#include <CommonTypes/CT_OduDefinitions.h>
#include "Configuration/CFG_Definitions.h"
#include "Monitoring/MON_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_DwIf;

class CFG_Odu;

//This action is invoked periodically in order to update 
//'ODU (Optical Data Transport Unit) layer' hardware 
//registers with current 'ODU' configuration.
//##ModelId=3C17A8F002C6
class CFG_HwRefreshOdu 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	//##ModelId=3C17AD810212
	CFG_HwRefreshOdu(CFG_AppIf&        theCfgIf, 
                     TSPII_DwRegion&   theDwPiiRegion,
                     CT_NumberOfOdus   theOdusOnCard,
                     CFG_OduCfgCriticalRegion* theOduCfgCriticalRegion = NULL);

	//Virtual destructor
	//##ModelId=3C17AD810050
	virtual ~CFG_HwRefreshOdu();

	//This method refreshes all hardware related to ODU 
	//(Optical Channel Data Unit) layer.  It reads the 
	//current value of each ODU layer parameter an invokes 
	//the corresponding PII interface. This action is 
	//normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

	//##ModelId=3C3B463A03AC
    TSPII_DwRegion&   myDwPiiRegion;
    CFG_OduCfgCriticalRegion* myOduCfgCriticalRegion;

    CT_NumberOfOdus   myOdusOnCard;

    uint16            myNumTspiiInstancesInPool;
    vector<bool>      myCurrentPassInstanceUsed;
    vector<bool>      myPreviousPassInstanceUsed;
    bool              myFirstPass;
    vector<uint32>    myLocalPrbsRxSessionCounter;
    MON_OduConfigRegion* myOduMonConfigRegion;
};

#endif /* _INC_CFG_HWREFRESHODU_3C17A8F002C6_INCLUDED */
