// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef __SP_YCABLEMISCACTIONS_H__
#define __SP_YCABLEMISCACTIONS_H__

#include <CommonTypes/CT_AgentFacility.h>
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_OpticalIf.h>
#include "SignalProtection/SP_ProtectionGroupConfigRegion.h"
#include <TelCommon/TEL_BbRegionBaseImp.h>

class FC_PeriodicProcess;
class FC_Action;
class FC_BbAction;
class FC_TimedProcess;
class FC_BoolRegion;
class SP_1plus1SubApplication;
class T6100_SfpIf;
class SP_Defects;

class SP_YCablePollData
{
public:
    SP_YCablePollData(uint32 tspiiIntf, TSPII_OpticalRegion* theRxOpticalRegion);
    virtual ~SP_YCablePollData();

	//All these functions are defined inline for performance reasons as they are used during protection switching
    bool SetPollData(uint8 theRxMsg);
	inline TSPII_OpticalRegion* GetOpticalRegion();
	inline bool IsConfigured();
	inline void SetIsConfigured(bool theConfigure);
    inline uint32 GetPort();

private:
    uint32 myPort;
    TSPII_OpticalRegion* myRxOpticalRegion;
	bool myIsConfigured;
	uint8 myRxMsg;

};

inline TSPII_OpticalRegion* SP_YCablePollData::GetOpticalRegion() { return myRxOpticalRegion; }
inline bool SP_YCablePollData::IsConfigured()                     { return myIsConfigured; }
void SP_YCablePollData::SetIsConfigured(bool theConfigure)        { myIsConfigured = theConfigure; }
uint32 SP_YCablePollData::GetPort()                               { return myPort; }

/////////////////////////////////////////////////////////
class SP_YCableEqptData
{
public:
    SP_YCableEqptData(T6100_SfpIf* theSfpIf, uint8 idx);
    virtual ~SP_YCableEqptData();

    bool SetCardData(bool theCardFault);
	bool SetSfpData(bool theSfpFault);
	inline T6100_SfpIf* GetSfpIntf();
    inline uint8 GetDefectIdx();

private:
    T6100_SfpIf* mySfpIf;
    bool myCardFault;
	bool mySfpFault;
    uint8 myDefectIdx;
};

inline T6100_SfpIf* SP_YCableEqptData::GetSfpIntf()   { return mySfpIf; }
inline uint8 SP_YCableEqptData::GetDefectIdx() { return myDefectIdx; }

/////////////////////////////////////////////////////////////////////////
//This action is responsible for polling for y-cable rx message and backplane LOS
class SP_YCableMsgPollingAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_YCableMsgPollingAction (FC_BoolRegion& theIsrMonRegion, TSPII_OpticalRegion* mateOpticalRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_YCableMsgPollingAction();

	static SP_YCableMsgPollingAction* GetInstance();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//Run method
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    FC_PeriodicProcess* GetProcessPtr();

    void InitializePollData(uint32 tspiiIntf, TSPII_OpticalRegion* theRxOpticalRegion);
    void SetConfiguration(bool isConfigured, uint32 tspiiIntf);

protected:
	
private:

	//
    FC_PeriodicProcess* myProcess;
    FC_BoolRegion& myIsrMonRegion;
	static SP_YCableMsgPollingAction       *itsInstance;    // Instance pointers

    typedef vector<SP_YCablePollData*> SP_YCablePollDataCollection;
	SP_YCablePollDataCollection myDataCollectionSet;

    TSPII_OpticalRegion* myMateOpticalRegion;
    bool myMateLos;
};

/////////////////////////////////////////////////////////////////////////
//This action is responsible for detecting supporting equipment presence/diagnostic faults
class SP_EqptFltDetectionAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_EqptFltDetectionAction (FC_BoolRegion& theIsrMonRegion, TEL_BbRegionBaseImp<SP_Defects>& theDefectsRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_EqptFltDetectionAction();

	//static SP_EqptFltDetectionAction* GetInstance();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//Run method
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);


    void InitializeEqptData(T6100_SfpIf* theEqptIf, uint8 theDefectIdx);

protected:
	
private:

    FC_BbAction* myBbAction;
	//
    FC_BoolRegion& myIsrMonRegion;
	//static SP_EqptFltDetectionAction       *itsInstance;    // Instance pointers

    typedef vector<SP_YCableEqptData*> SP_YCableEqptDataCollection;
	SP_YCableEqptDataCollection myDataCollectionSet;

    TEL_BbRegionBaseImp<SP_Defects>& myDefectsRegion;
};


#endif /* __SP_YCABLEMISCACTIONS_H__ */

