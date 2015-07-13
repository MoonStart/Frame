// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_ODUUPDATESTATUSACTION_
#define _MON_ODUUPDATESTATUSACTION_

#include <CommonTypes/CT_OduDefinitions.h>
#include "Configuration/CFG_Definitions.h"
#include "Configuration/CFG_Odu.h"
#include "MON_UpdateStatusAction.h"
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
class TSPII_DwIf;

//This class is an action that reads the current state of the 
//ODU layer in the hardware and updates the ODU regions accordingly.
class MON_OduUpdateStatusAction 
: public MON_UpdateStatusAction
{
public:
	//Constructor.
	MON_OduUpdateStatusAction(MON_AppIf&        theMonIf, 
                              TSPII_DwRegion&   theDwPiiRegion,
                              MON_AppIf*        theUpstreamLayerIf,
                              MON_AppIf*        theIMUXLayerIf,
                              CT_NumberOfOdus   theOdusOnCard,
                              bool              theUpperLayerRemoteFlag = false,
                              bool              theUpperLayerPoolFlag = false,
                              CFG_OduCfgRegion* theOduConfigRegion = NULL);

 	//Virtual destructor of the class.
	virtual ~MON_OduUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason);


    MON_AppIf* GetPoolApp(CT_ODU_ServerID theServerID,
                          T6100_CardIf*   theCardContext);

private:

    TSPII_DwRegion&   myDwPiiRegion;

    MON_AppIf*        myIMUXLayerIf;

    CFG_OduCfgRegion* myOduConfigRegion;

    CT_NumberOfOdus   myOdusOnCard;
    /*For OSM20, update only part ODU in each UpdateObject so that it will not have big latency for protection
    each period(100ms) update 2 ODU0F; total 16 ODU0F; 
    each period(200ms) update 2 ODU1 ; total  8 ODU1;
    each period(400ms) update 1 ODU2 ; total  2 ODU2; */
    uint8             myNextOdu;
    uint8             myNbrOdu2Check;
    bool              myFirstPassFlag;

    bool myUpperLayerRemoteFlag; 
    bool myUpperLayerPoolFlag;

    uint32         myNumConsecTraceComp;

    vector<uint32> myGoodTraceMessageCounter;
	vector<uint32> myBadTraceMessageCounter;

    // First time read of ODU-Trace from TSPII
    vector<bool> myFirstRcvdOduTrace;

    //Local counts of defects read on PII
    vector<uint32> myPiiAISCount;
    vector<uint32> myPiiLCKCount;
    vector<uint32> myPiiOCICount;
    vector<uint32> myPiiBDICount;
    vector<uint32> myPiiInternalAISCount;
    vector<uint32> myPiiInternalLCKCount;
    vector<uint32> myPiiInternalOCICount;
    vector<uint32> myPiiSdBerCount;
    vector<uint32> myPiiSfBerCount;
    vector<uint32> myPiiPLMCount;
    vector<uint32> myPiiMSIMCount;
    vector<uint32> myPiiGenAISCount;
    vector<uint32> myPiiLOFLOMCount;
    vector<uint32> myPiiLOOMFICount;

    //Local Tspii instance for pools.   
    vector<uint16> myPiiTspiiDwInstance;

    // Local Prbs RX session Counter
    vector<uint32> myLocalPRBSRXSessionCounter;

    vector<uint32> myPiiSSFforSGEOCount;

    bool           myTimCheckByMon;
};


#endif /* _MON_ODUUPDATESTATUSACTION_ */
