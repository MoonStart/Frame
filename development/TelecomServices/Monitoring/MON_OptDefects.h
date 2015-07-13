//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OPTDEFECT_H
#define MON_OPTDEFECT_H

#include "MON_Defects.h"

enum MON_FAILLAYER_OPT_BITMASK
{
    MON_FAILLAYER_OPTLOS_BITMASK         = 0x01,
    MON_FAILLAYER_OPT_DEFAULT_BITMASK    = 0xffff
};

//This class contains the defects status and transition 
//counts for the Optical layer. It can apply to either the 
//line or port side.
class MON_OptDefects :public MON_Defects
{
public:

	//Constructor.
    MON_OptDefects(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OptDefects(void);

    //Returns the status and count of the defect provide as argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerForMaintSigInDefects() const;
    bool IsLayerLocked() const;

    bool IsLayerInternalInDefects() const;
    bool IsLayerInternalForMaintSigInDefects() const;
    bool IsLayerInternalLocked() const;
    bool IsInternalInPropagateNextLayerDefectsTA() const;
    bool IsLayerInTermLpbk() const;

    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    bool LosFailLayer() const;
    void SetFailLayerBitMask(uint16 theBitMask);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // True if upper layer is in failure (Traffic Affecting)
    bool myUpperLayerFailTAState;
    uint32 myUpperLayerFailTACount;

    // True if upper layer is in failure (Non Traffic Affecting)
    bool myUpperLayerFailNTAState;
    uint32 myUpperLayerFailNTACount;

    // True if layer is locked (propagated from upper layer)
    bool myLockState;
    uint32 myLockCount;

	//True if no clock can be derived from the incoming optical signal.
	bool myLossOfClock;

	//Current number of rising transition of the Loss of clock defect.
	uint32 myLossOfClockCount;

	//True if the auto rate lock down feature, lost his lock.
	bool myLossOfLock;

	//Current number of rising transition of the Loss of Lock defect.
	uint32 myLossOfLockCount;

	//True if total aggregated optical power from the 
	//incoming signal is below expected power threshold.
	bool myLossOfLight;

	//Current number of rising transition of the Loss of light defect.
	uint32 myLossOfLightCount;

    //Pii LossOfLight value, never overwritten by MON.
    bool myPiiLossOfLight;

    //Pii number of rising transition of the Loss of light defect.
    uint32 myPiiLossOfLightCount;

	//True if received optical power from the incoming signal
	//(from the Status Region) is below Signal Degrade Power threshold.
    //Note: CRM calls the Signal Degrade Power threshold switch_threshold.  
	bool mySdPwrState;

	//Current number of rising transition of the Signal Degrade Power defect.
	uint32 mySdPwrCount;

    //True if detected rate is above the max clock rate configured.
	bool myMFAState;

	//Current number of rising transition of the Mismatch of Facility defect.
	uint32 myMFACount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer for maintenance signal Internal is in failure 
    bool myUpperLayerForMSInternalFailTAState;
    uint32 myUpperLayerForMSInternalFailTACount;

    // True if upper layer for maintenance signal is in failure 
    bool myUpperLayerForMSFailTAState;
    uint32 myUpperLayerForMSFailTACount;

    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockLockCount;

    // True if upper layer Internal Prop Next Layer is in failure 
    bool myUpperLayerInternalFailPNLTAState;
    uint32 myUpperLayerInternalFailPNLTACount;

    // True if layer terminal loopbacked (propagated from upper layer)
    bool myTermLpbkState;
    uint32 myTermLpbkCount;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask; 
};

#endif /* MON_OPTDEFECT_H */
