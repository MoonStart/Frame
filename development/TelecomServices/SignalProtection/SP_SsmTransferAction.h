// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SSMRANSFERACTION_38E35B0900D0_INCLUDED
#define _INC_SP_SSMTRANSFERACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_SignalProtection.h>
//#include <vector>
#include "SP_Definitions.h"
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include <CommonTypes/CT_SystemIds.h>
#include "SP_1plus1ProtectionGroupConfig.h"

class FC_BbAction;
class SP_ProtectionGroupConfigRegion;
class MON_Region;
class SP_SsmRegion;
class SP_SystemTimingManager;
class SP_ProtectionGroupStatusRegion;
class CFG_Region;


//This class transfers SSM from one module to another
//##ModelId=38E35B0900D0
class SP_SsmTransferAction 
: public FC_Action
{
public:
	//Constructor. Requires configuration region.
    //##ModelId=3BBC9B0F02A0
    SP_SsmTransferAction(SP_ProtectionGroupConfigRegion* theConfigRegion, SP_SsmRegion* theSsmRegion, SP_SystemTimingManager* theTimingManager);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_SsmTransferAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles transfer of defects from one card to another
	//based on configuration
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	bool AddInputs(CT_SP_ProtectionPair<CT_Port> & theSources); //returns false if unable to add input regions
	void RemoveInputs();

	void AddStatusInputs(CT_SP_ProtectionPair<CT_Port> & theSources);
	void RemoveStatusInputs();

	//This method checks if the protection group this action
	//is managing is different from the specified group
	//A group is considered different if the sources are different
	//the protection type is different or the usage status is different
	bool IsProtectionGroupDifferent(SP_1plus1ProtectionGroupConfig& theConfig);

	//Copies the configuration data passed in to local copy
    void CopyConfiguration(SP_1plus1ProtectionGroupConfig& theConfig);


	//Forces the defect processing to start if it was 
	//stopped(debug).
    //##ModelId=39ACEFB00072
    inline void Start();
	//Forces the defect processing to stop (debug).
    //##ModelId=39ACEFB0005E
    inline void Stop();

    FC_BbAction* GetBbAction() { return myBbAction; }

    CT_Side GetSideFromPort(CT_ShelfId theShelf, CT_IntfId thePort);
	
protected:
	
	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

private:
    FC_BbAction* myBbAction;

	CT_SP_ProtectionPair<MON_Region*> myMonRegion;

    CT_SP_ProtectionPair<CFG_Region*> myCfgRegion;

	SP_ProtectionGroupConfigRegion* myConfigRegion;

	SP_1plus1ProtectionGroupConfig myProtCfgCopy;

	SP_SsmRegion* mySsmRegion;

	SP_SystemTimingManager* myTimingManager;

	CT_SP_ProtectionPair<SP_ProtectionGroupStatusRegion*> myStatusRegion;
};

//##ModelId=39ACEFB00072
inline void SP_SsmTransferAction::Start() { stopped = false; }
//##ModelId=39ACEFB0005E
inline void SP_SsmTransferAction::Stop() { stopped = true; }

#endif /* _INC_SP_SSMTRANSFERACTION_38E35B0900D0_INCLUDED */
