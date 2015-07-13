//Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OTSOCHOHAUTOMATICACTION_
#define _CFG_OTSOCHOHAUTOMATICACTION_

#include "CFG_Definitions.h"
#include "CFG_HwRefreshAction.h"
#include "Monitoring/MON_Definitions.h"
#include "CSM/CSM_CardStatusRegion.h"
#include "ITS/ITS_Definitions.h"

class MON_AppIf;

//This action handle the refresh of transmitted indication over the OTS
class CFG_OtsOchOHAutomaticAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_OtsOchOHAutomaticAction(CFG_AppIf& aCfgApp,
                                MON_OmsDefectsRegion& theOutputMonOmsDefectsRegion,
                                MON_OchDefectsRegion& theOutputMonOchDefectsRegion,
                                ITS_ConfigRegion& theItsConfigRegion,
                                CFG_OtsOchOHAutomaticCfgRegion& theOtsOchOHAutomaticCfgRegion,
                                vector<CT_Side>& thePossibleSidesVector,
                                uint32 theNumberofPossibleSides = 0);

    virtual ~CFG_OtsOchOHAutomaticAction();

    //Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

	//Virtual destructor of the class.
    void UpdateObject(unsigned theRunReason, uint32 theIndex);
    
	virtual FC_CmdProcessor::STATUS Debug(int argc, char **argv);

private:

    //Input regions
    MON_OmsDefectsRegion&      myOutputMonOmsDefectsRegion;
    MON_OchDefectsRegion&      myOutputMonOchDefectsRegion;
    ITS_ConfigRegion&          myItsConfigRegion;

    MON_RsDefectsRegion*       myPossibleOtherSideMonRsDefectsRegion[CT_NUMBER_OF_SIDES];
    MON_OtsOHDefectsRegion*    myPossibleOtherSideMonOtsOHDefectsRegion[CT_NUMBER_OF_SIDES];
    MON_OtsOchOHDefectsRegion* myPossibleOtherSideMonOtsOchOHDefectsRegion[CT_NUMBER_OF_SIDES];
    MON_OmsDefectsRegion*      myPossibleOtherSideInputMonOmsDefectsRegion[CT_NUMBER_OF_SIDES];

    //Output region
    CFG_OtsOchOHAutomaticCfgRegion& myOtsOchOHAutomaticCfgRegion;

    vector<CT_Side> myPossibleSidesVector;
    uint32          myNumberofPossibleSides;

    bool myOmsPassThru;
	
	//Added for to assist with debugging.
    CT_Side myPTSourceSide[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    int myOtherSideIndex[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myPassThruState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myFDIOState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOscLosState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOtherSideFDIOState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOtherSideOmsFDIO[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myFDIPState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myInputOmsLosState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOtherSideFDIPState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOtherSideOmsFDIP[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOtherSideOtsPMI[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOCIState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOutputOmsLosState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOchLossState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
    bool myOtherSideOCIState[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
};



#endif /* _CFG_OTSOCHOHAUTOMATICACTION_ */
