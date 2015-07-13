/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        MON_OchOsaPrimeUpdateStatusAction.h
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
#ifndef __MON_OCHOSAPRIMEUPDATESTATUSACTION__
#define __MON_OCHOSAPRIMEUPDATESTATUSACTION__

#include "MON_UpdateStatusAction.h"
#include "MON_Definitions.h"
#include "Monitoring/MON_OchOsaUpdateStatusAction.h"
#include <TsPii/TSPII_Region.h>
#include "MON_OchPower.h"
#include <time.h>


//This action handle the refresh of its Optical defect and status object.
class MON_OchOsaPrimeUpdateStatusAction : public MON_UpdateStatusAction
{
public:
	//Constructor for .
	MON_OchOsaPrimeUpdateStatusAction(MON_AppIf&             theMonIf,
                                      TSPII_OsaRegion*       thePiiOsaRegion, 
                                      uint32                 thePiiOsaUnit,
                                      MON_OchStatusRegion*   theOchStatusRegion,
                                      MON_OchAltStatusRegion*  theAltOchRegion,
                                      uint32                 theNumberOfWavelengths,
                                      TSPII_PipeRegion*      theTspiiPipeRegion = NULL);  

    //Virtual destructor of the class.
	virtual ~MON_OchOsaPrimeUpdateStatusAction();

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
    TSPII_PipeRegion* myTspiiPipeRegion;
    MON_OchStatusRegion* myOchStatusRegion;
    MON_OchAltStatusRegion*  myAltOchRegion;
    uint32 myNumberOfWavelengths;

    MON_OchRequest& myRequest;
    MON_OchResult&  myResult;

    uint32 myPiiOsaUnit;

	CT_TEL_mBm myOchPowerDebounceThreshold;
	time_t	 myOchPowerDebouncePeriod;

	tHistory myHistory[CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY];
	unsigned long myHistoryIndex;

	void ClearHistoryForAllCh();
	void ClearHistoryForCh(uint32 theIndex);
	void RecordHistory(uint32 theIndex, CT_TEL_mBm prevPwr, CT_TEL_mBm curPwr, time_t curSampleTime, eMON_Event event);
	void RecordHysteresis(uint32 theIndex, CT_TEL_mBm prevPwr, CT_TEL_mBm curPwr, time_t curSampleTime);
	void DisplayHistoryForAllCh();
	void DisplayHistoryForCh(uint32 theIndex);
	void DisplayHysteresis();
	void GetDateTimeStampStr(time_t theTime, char **pBuf, uint32 len);

    //Local counts of defects read on PII
    vector<uint32> myPiiLOSCount;
};

#endif /* __MON_OCHOSAPRIMEUPDATESTATUSACTION__ */
