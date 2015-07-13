/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_ODUCRITICALOBJECT_H
#define CFG_ODUCRITICALOBJECT_H

#include <gdef.h>
//#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_OduDefinitions.h>
//#include <CommonTypes/CT_PM_Definition.h>
#include <list>

#include "CFG_Object.h"


//This object contains all the critical ODU (Optical Channel 
//Data Unit) configuration, which is a subset of the normal ODU region.
class CFG_OduCritical
: public CFG_Object
{

public:
    //Constructor.
    CFG_OduCritical(uint32 theIndex);
    CFG_OduCritical(const CFG_OduCritical& theCfg);

    //Virtual destructor.
    virtual ~CFG_OduCritical(void);

    // This methods sets the ODU Identifies for ODU pools
    bool SetOduIdentifier(CT_ODU_Identifier theOduId);

    //This method returns the ODU Identifies for ODU pools
    CT_ODU_Identifier GetOduIdentifier() const; 

    // This methods sets the ODU Object Type for the ODU instance
    bool SetOduObjectType(CT_ODU_Object_Type theOduType);

    //This method returns the ODU Identifies for the ODU instance
    CT_ODU_Object_Type GetOduObjectType() const;


    //This method sets the Odu Terminating flag of the facility (YES or NO).
    bool SetIsOduTerm(bool theIsOduTerm);

    //This method returns the Odu Terminating flag of the facility.
    bool GetIsOduTerm() const;


    //This method returns the configured PSI (Payload Structure Identifier).
    CT_TEL_PayloadSignalId GetTxPayloadType() const;

    //This method sets the PSI (Payload Structure Identifier).
    bool SetTxPayloadType(CT_TEL_PayloadSignalId theTxPayloadType);


    //bool SetProvisionningActive(bool theProvisionningActive);
    //bool GetProvisionningActive() const;


    bool SetClockType(CT_TEL_ClkType theClockType);
    CT_TEL_ClkType GetClockType() const;


    bool SetTribSize(CT_TEL_TS_SIZE theTsSize);
    CT_TEL_TS_SIZE GetTribSize() const;

    bool SetTribPort(uint8 theTribPort);
    uint8 GetTribPort() const;


    // This method sets expect rate.
    bool SetExpectedSignalRate(uint32 theExpSigRate);

    //This method returns ExpectRate.
    uint32 GetExpectedSignalRate() const;

    // This method sets gfp ts.
    bool SetGfpTs(uint8 theGfpTs);

    //This method returns gfp ts.
    uint8 GetGfpTs() const;

    // Operators
    bool operator==(const CFG_OduCritical& theCfg) const;
    bool operator!=(const CFG_OduCritical& theCfg) const;
    CFG_OduCritical& operator=(const CFG_OduCritical& theCfg);

    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

    //Serialization methods 
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:

    // ODU Identifier for ODU pools
    CT_ODU_Identifier myOduIdentifier; 

    // ODU Identifies for the ODU instance
    CT_ODU_Object_Type myInstanceObjectType;

    // ODU Position for ODU pools
    //vector<CT_ODU_ServerID> myPositionList;

    
    // TCM Direction A Processing List for ODU pools
    //vector<CT_NumberOfOdus> myTcmAProcList;

    // TCM Direction V Processing List for ODU pools
    //vector<CT_NumberOfOdus> myTcmBProcList;

    // ODU Server (upper layer) identifier
    //CT_ODU_ServerID myServerID;

    // ODU Alternate Server (alternate upper layer) identifier
    //CT_ODU_ServerID myAltServerID;


    //Trace message (including SAPI, DAPI and operator 
    //specific text) to transmit in the ODU path overhead (PM).
    //CT_G709Trace* mySentTracePtr;
    //bool myTraceInUse;

    //Payload Structure Identifier
    CT_TEL_PayloadSignalId myTxPayloadType;


    //Add in Monitoring Configurations 
    //Signal degrade BER threshold
    //CT_TEL_BERLevels myBerSdLevel;

    // Signal failure BER threshold
    //CT_TEL_BERLevels mySfBerLevel;
	   
    
    // Set Interval and Threshold for bursty BerSd monitoring
    //uint16 myBurstyBerSdIntervals;
    //uint32 myBurstyBerSdThreshold;

    //CT_PMProfileTableId myPMProfileId;

    //Set clock type
    CT_TEL_ClkType myClockType;

    //the Terminated ODU Indication to be sent when the layer is failed
    //CT_ODU_IndicationType myTerminatedIndication;

    //Set trib slot size
    CT_TEL_TS_SIZE myTribSize;

    //Set trib port
    uint8 myTribPort;

    

    // Generic Provisioning Parameter.  The bits can be used for whatever porpose.
    // Combine all the bools into one uint parameter to reduce space used.
    // bool myProvisionningActive;
    // bool myIsOduTerm;
    // bool myInternalSignalingDisabled;
    // bool myExternalSignalingDisabled;
    // bool myForceAIS;
    // bool myForceLCK;
    // bool myForceOCI;
    // bool myForceInternalAIS;
    // bool myForceInternalLCK;
    // bool myForceInternalOCI;
    // bool myTribAutoFallBack;
    // bool myPathDelayEnabled;
    // bool myNullSignalEnabled;
    // bool myPrbsTxEnabled;
    // bool myPrbsRxEnabled;
    uint16 myGenericProvisioning;

    // The field for channel in ODU AID. PM needs this info for pm file operations.
    //uint8  myChannelIndexInAID;

    //The session number for an Rx PRBS BER collection on a facility.
    //uint32 myPrbsRxSessionCounter;

    // ODUflex Expected Signal Rate
    uint32 myExpSigRate;

    // ODUflex GFP TS.
    uint8 myGfpTs;

    // Cross connected ODU index on the same board.
    //uint8 myCrossConnectedOduIdx;
};

#endif /* CFG_ODUCRITICALOBJECT_H */

