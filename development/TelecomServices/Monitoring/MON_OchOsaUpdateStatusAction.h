/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        MON_OchOsaUpdateStatusAction.h
 *    DATE:          11/07/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     MON/OCH; LIAME/LRAME
 *    OVERVIEW:      MON och action for collecting OSA data from TSPII 
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#ifndef __MON_OCHOSAUPDATESTATUSACTION__
#define __MON_OCHOSAUPDATESTATUSACTION__

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include "MON_OchPower.h"
#include <time.h>

typedef struct 
{
	CT_TEL_mBm prevPwr;
	CT_TEL_mBm curPwr;
    time_t     myTimestamp;
    eMON_Event event;
} tHistEvent;
const int MON_OCH_PWR_HISTORY_SIZE = 30;

typedef struct 
{
    tHistEvent myHistMax;
    tHistEvent myHistMin;
    tHistEvent myHistEvent[MON_OCH_PWR_HISTORY_SIZE];
} tHistory;

//This action handle the refresh of its Optical defect and status object.
class MON_OchOsaUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_OchOsaUpdateStatusAction(MON_AppIf&             theMonIf,
                                 TSPII_OsaRegion*       thePiiOsaRegion,
                                 uint32                 thePiiOsaUnit,
                                 MON_OchStatusRegion*   theOchStatusRegion,
                                 uint32                 theNumberOfWavelengths,
                                 MON_AppIf*             theOmsLayerIf=NULL);  

    //Virtual destructor of the class.
	virtual ~MON_OchOsaUpdateStatusAction();

    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    virtual FC_Object* Suspend(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void UpdateObject(unsigned theRunReason,
                      uint32 theIndex,
                      TSPII_OsaIf& thePiiOsa,
					  bool **hasStatusChanged,
					  bool **hasDefectsChanged);

    bool Set(int argc, char ** argv);

private:
    TSPII_OsaRegion* myPiiOsaRegion;
    MON_OchStatusRegion* myAmpOchStatusRegion;
    MON_AppIf* myOmsLayerIf;
    MON_OchStatusRegion* myOchStatusRegion;
    uint32 myNumberOfWavelengths;

    MON_OchRequest& myRequest;
    MON_OchResult&  myResult;

    uint32 myPiiOsaUnit;

	CT_TEL_mBm myOchPowerDebounceThreshold;
	time_t	 myOchPowerDebouncePeriod;


	tHistory myHistory[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
	unsigned long myHistoryIndex;

    bool myRecordHistoryFlag;
	void ClearHistoryForAllCh();
	void ClearHistoryForCh(uint32 theIndex);
	void RecordHistory(uint32 theIndex, CT_TEL_mBm prevPwr, CT_TEL_mBm curPwr, time_t curSampleTime, eMON_Event event);
	void RecordHysteresis(uint32 theIndex, CT_TEL_mBm prevPwr, CT_TEL_mBm curPwr, time_t curSampleTime);
	void DisplayHistoryForAllCh();
	void DisplayHistoryForCh(uint32 theIndex);
	void DisplayHysteresis();
	void GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len);
};

#endif /* __MON_OCHOSAUPDATESTATUSACTION__ */
