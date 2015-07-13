// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef CFG_HWREFRESHTCM_H
#define CFG_HWREFRESHTCM_H

#include "CFG_HwRefreshAction.h"
#include <CommonTypes/CT_OduDefinitions.h>
#include <TsPii/TSPII_Region.h>

#include "Configuration/CFG_Definitions.h"


// Forward declaration of class.
class TSPII_TcmIf;

class CFG_Tcm;

//This action is invoked periodically in order to update 
//'TCM (Optical Data Transport Unit) layer' hardware 
//registers with current 'TCM' configuration.
//##ModelId=3C17A8F002C6
class CFG_HwRefreshTcm 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	//##ModelId=3C17AD810212
	CFG_HwRefreshTcm(CFG_AppIf& theCfgIf, TSPII_TcmRegion&  theTcmPiiRegion,CT_NumberOfOdus  theTcmsOnCard, CT_NumberOfOdus theInstancesPerRound);

	//Virtual destructor
	//##ModelId=3C17AD810050
	virtual ~CFG_HwRefreshTcm();

	//This method refreshes all hardware related to TCM 
	//(Optical Channel Data Unit) layer.  It reads the 
	//current value of each TCM layer parameter an invokes 
	//the corresponding PII interface. This action is 
	//normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:
    TSPII_TcmRegion& myTcmPiiRegion;
    CT_NumberOfOdus myTcmsOnCard;

    //All tcm instances now are handled in one action. In order to decrease running time,
    //TCM refresh action runs twice for one full iteration. One is for first half instances,
    //one for the second half instances. Below variable are for this purpose.
    CT_NumberOfOdus myInstancesPerRound;

    uint16 myRoundCount;

    //Local Tspii instance for pools.   
    vector<uint16> myPiiTspiiTcmInstance;
    vector<uint16> myNewPiiTspiiTcmInstance;
};

#endif /* CFG_HWREFRESHTCM_H */
