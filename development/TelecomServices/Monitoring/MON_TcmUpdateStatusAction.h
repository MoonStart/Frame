// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_TCMUPDATESTATUSACTION_
#define _MON_TCMUPDATESTATUSACTION_

#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_FacilityIds.h>
#include "Configuration/CFG_Definitions.h"
#include "Configuration/CFG_Tcm.h"
#include "Configuration/CFG_Odu.h"
#include "MON_UpdateStatusAction.h"
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class TSPII_TcmIf;

//This class is an action that reads the current state of the 
//TCM layer in the hardware and updates the TCM regions accordingly.
class MON_TcmUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_TcmUpdateStatusAction(MON_AppIf&        theMonIf,
                              CT_IntfId         theIntfId,
                              TSPII_TcmRegion&  theTcmPiiRegion,
                              CT_NumberOfOdus   theTcmsInRegion = 0,                              
                              CFG_TcmCfgRegion* theTcmConfigRegion = NULL );

 	//Virtual destructor of the class.
	virtual ~MON_TcmUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason);

    void ResetInstance(uint16 theIndex);

    MON_AppIf* GetPoolApp(CT_ODU_ServerID theServerID,
                          T6100_CardIf*   theCardContext);

private:
    CT_IntfId          myIntfId;

    TSPII_TcmRegion&   myTcmPiiRegion;

    CT_NumberOfOdus    myTcmsInRegion;
    CFG_TcmCfgRegion*  myTcmConfigRegion;

    uint32         myNumConsecTraceComp;

    /*All TCM instances now are handled in one action. In order to decrease running time,
      below 4 member variables are added to divide the processing of all TCM instances to 
      several rounds.
     
       1. The action is broken up by Odu Layer Offset, one round for all instances of one certion ODU layer.
     
       2. The division will affect TSPII update time in in the TSPII sub application.  For
       example, if we are splitting the instances in half, then we probably want the Tspiiupdate
       time for TCM to be 400ms (so we can get through all the reads in under 1 second. less than 1 second.
    */
    uint16         myRoundCount;
    uint16         myInitialLayer;
    uint16         myLastLayer;
    bool           myFirstPassFlag;         


    vector<uint32> myGoodTraceMessageCounter;
	vector<uint32> myBadTraceMessageCounter;

    //First time read of TCM-Trace from TSPII
    vector<bool> myFirstRcvdTcmTrace;

    //Local counts of defects read on PII
    vector<uint32> myPiiLTCCount;
    vector<uint32> myPiiAISCount;
    vector<uint32> myPiiLCKCount;
    vector<uint32> myPiiOCICount;
    vector<uint32> myPiiBDICount;
    vector<uint32> myPiiSdBerCount;
    vector<uint32> myPiiIAECount;
    vector<uint32> myPiiBIAECount;

    //Record if the instance is used
    vector<CT_ODU_Identifier> myOldTcmId;
    vector<CT_ODU_Identifier> myNewTcmId;   
};


#endif /* _MON_TCMUPDATESTATUSACTION_ */
