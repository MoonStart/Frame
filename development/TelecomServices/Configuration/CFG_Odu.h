/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_ODUOBJECT_H
#define CFG_ODUOBJECT_H

//#include <gdef.h>
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <list>

#include "CFG_Object.h"


//This object contains all the generic ODU (Optical Channel 
//Data Unit) configuration for one port.
class CFG_Odu 
: public CFG_Object
{

public:
    //Constructor.
    CFG_Odu(uint32 theIndex);

    //Virtual destructor.
    virtual ~CFG_Odu(void);

    // This methods sets the ODU Identifies for ODU pools
    bool SetOduIdentifier(CT_ODU_Identifier theOduId);

    //This method returns the ODU Identifies for ODU pools
    CT_ODU_Identifier GetOduIdentifier() const; 

    // This methods sets the ODU Object Type for the ODU instance
    bool SetOduObjectType(CT_ODU_Object_Type theOduType);

    //This method returns the ODU Identifies for the ODU instance
    CT_ODU_Object_Type GetOduObjectType() const;

    // This methods sets the ODU Position List for ODU pools
    bool SetOduPositionList(vector<CT_ODU_ServerID>& thePosList);

    //This method returns the ODU Position List for ODU pools
    const vector<CT_ODU_ServerID>& GetOduPositionList();


    // This methods sets the Direction A Processing List for TCM pools
    bool SetOduTcmAProcList(vector<CT_NumberOfOdus>& theProcList);

    //This method returns the Direction A Processing List for TCM pools
    const vector<CT_NumberOfOdus>& GetOduTcmAProcList();


    // This methods sets the Direction B Processing List for TCM pools
    bool SetOduTcmBProcList(vector<CT_NumberOfOdus>& theProcList);

    //This method returns the Direction B Processing List for TCM pools
    const vector<CT_NumberOfOdus>& GetOduTcmBProcList();


    // This methods sets the Server ID for the upper layer
    bool SetServerID(CT_ODU_ServerID theServerId);

    //This method returns the Server ID for the upper layer
    CT_ODU_ServerID GetServerID() const; 


    // This methods sets the Alternate Server ID for the upper layer
    bool SetAltServerID(CT_ODU_ServerID theServerId);

    //This method returns the Alternate Server ID for the upper layer
    CT_ODU_ServerID GetAltServerID() const; 



    //This method sets the Internal Signaling Disabled flag of the facility (YES or NO).
    bool SetInternalSignalingDisabled(bool theDisable);

    //This method returns the Internal Signaling Disabled flag of the facility.
    bool GetInternalSignalingDisabled() const;

    //This method sets the External Signaling Disabled flag of the facility (YES or NO).
    bool SetExternalSignalingDisabled(bool theDisable);

    //This method returns the External Signaling Disabled flag of the facility.
    bool GetExternalSignalingDisabled() const;


    //This method sets the force generation of ODU-LCK maintenance signal (ON or OFF).
    bool SetForceLCK(bool theForceLCK);

    //This method returns the setting (ON or OFF) of the 
    //force generation of ODU-LCK maintenance signal.
    bool GetForceLCK() const;

    //This method sets the force generation of ODU-OCI maintenance signal (ON or OFF).
    bool SetForceOCI(bool theForceOCI);

    //This method returns the setting (ON or OFF) of the force generation of ODU-OCI maintenance signal.
    bool GetForceOCI() const;


    //This method sets the value of the 'sent Trace' in the 
    //TTI byte of the ODU (Optical Channel Data Unit) layer.
    bool SetSentTrace(const CT_G709Trace& theSentTrace);
    bool DeleteSentTrace();

    //This method returns the set value of the 'sent Trace' 
    //in the TTI byte of the ODU (Optical Channel Data Unit) layer.
    CT_G709Trace & GetSentTrace() const;


    //This method sets the Odu Terminating flag of the facility (YES or NO).
    bool SetIsOduTerm(bool theIsOduTerm);

    //This method returns the Odu Terminating flag of the facility.
    bool GetIsOduTerm() const;


    //This method sets the force generation of ODU-AIS maintenance signal (ON or OFF).
    bool SetForceAIS(bool theForceAIS);

    //This method returns the setting (ON or OFF) of the force generation of ODU-AIS maintenance signal.
    bool GetForceAIS() const;


    //Add in Monitoring Configurations 
    //Set Signal Degrade threshold for BER
    bool SetBerSdThreshold(CT_TEL_BERLevels theBerSdThreshold);

    //Set Signal Failure threshold for BER
    bool SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold);

    //Get Signal Degrade threshold for BER
    CT_TEL_BERLevels GetBerSdThreshold() const;

    //Get Signal Failure threshold for BER
    CT_TEL_BERLevels GetBerSfThreshold() const;


    //This method returns the configured PSI (Payload Structure Identifier).
    CT_TEL_PayloadSignalId GetTxPayloadType() const;

    //This method sets the PSI (Payload Structure Identifier).
    bool SetTxPayloadType(CT_TEL_PayloadSignalId theTxPayloadType);


    //This method sets the force generation of ODU-LCK maintenance signal (ON or OFF).
    bool SetForceInternalLCK(bool theForceInternalLCK);

    //This method returns the setting (ON or OFF) of the 
    //force generation of ODU-LCK maintenance signal.
    bool GetForceInternalLCK() const;

    //This method sets the force generation of ODU-OCI maintenance signal (ON or OFF).
    bool SetForceInternalOCI(bool theForceInternalOCI);

     //This method returns the setting (ON or OFF) of the force generation of ODU-OCI maintenance signal.
    bool GetForceInternalOCI() const;

    //This method sets the force generation of ODU-AIS maintenance signal (ON or OFF).
    bool SetForceInternalAIS(bool theForceInternalAIS);

    //This method returns the setting (ON or OFF) of the force generation of ODU-AIS maintenance signal.
    bool GetForceInternalAIS() const;

    //This method sets the Bursty BerSd number of inervals
    bool SetBurstyBerSdIntervals(uint16 theIntervals);

    //This method returns the Bursty BerSd number of inervals
    uint16 GetBurstyBerSdIntervals() const;

    //This method sets the Bursty BerSd threshold of errored blocks
    bool SetBurstyBerSdThreshold(uint32 theThreshold);

    //This method returns the Bursty BerSd threshold of errored blocks
    uint32 GetBurstyBerSdThreshold() const;

    bool SetProvisionningActive(bool theProvisionningActive);
    bool GetProvisionningActive() const;

    bool SetPMProfileId(CT_PMProfileTableId thePMPFId);
    CT_PMProfileTableId GetPMProfileId() const;

    bool SetClockType(CT_TEL_ClkType theClockType);
    CT_TEL_ClkType GetClockType() const;

    //These methods set/get the Terminated ODU Indication to be sent when the layer is failed
    bool SetTerminatedIndication(CT_ODU_IndicationType theTerminatedIndication);
    CT_ODU_IndicationType GetTerminatedIndication() const;

    bool SetTribSize(CT_TEL_TS_SIZE theTsSize);
    CT_TEL_TS_SIZE GetTribSize() const;

    bool SetTribPort(uint8 theTribPort);
    uint8 GetTribPort() const;

    bool SetTribAutoFallBack(bool theTribAutoFallBack);
    bool GetTribAutoFallBack() const;

    bool SetChannelIndexInAID(uint8 theChannelIndexInAID);
    uint8 GetChannelIndexInAID() const;

    //These methods set/get whether the Path Delay measurement is enabled.
    bool SetPathDelayEnabled(bool theEnable);
    bool GetPathDelayEnabled() const;

    // These methods set/get whether the NULL Signnal is enabled.
    bool GetNULLSignalEnable() const;
    bool SetNULLSignalEnable(bool theEnable);

    //This method sets the current state of the PRBS BER Transmit Enable.
    bool SetPrbsTxEnable(bool thePrbsTxEnable);

    //This method returns the current state of the PRBS BER Transmit Enable.
    bool GetPrbsTxEnable() const;

    //This method sets the current state of the PRBS BER Receive Enable.
    bool SetPrbsRxEnable(bool thePrbsRxEnable);

    //This method returns the current state of the PRBS BER Receive Enable.
    bool GetPrbsRxEnable() const;

    //This method sets the PRBS BER Receive Seesion Counter.
    bool SetPrbsRxSessionCounter(uint32 thePrbsRxSessionCounter);

    //This method returns the PRBS BER Receive Seesion Counter.
    uint32 GetPrbsRxSessionCounter() const;

    // This method sets expect rate.
    bool SetExpectedSignalRate(uint32 theExpSigRate);

    //This method returns ExpectRate.
    uint32 GetExpectedSignalRate() const;

    // This method sets gfp ts.
    bool SetGfpTs(uint8 theGfpTs);

    //This method returns gfp ts.
    uint8 GetGfpTs() const;

    // This method sets cross connected ODU's index in the same board.
    bool SetCrossConnectedOduIdx(uint8 theOduIdx);

    //This method returns cross connected ODU's index in the same board.
    uint8 GetCrossConnectedOduIdx() const;


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
    vector<CT_ODU_ServerID> myPositionList;

    
    // TCM Direction A Processing List for ODU pools
    vector<CT_NumberOfOdus> myTcmAProcList;

    // TCM Direction V Processing List for ODU pools
    vector<CT_NumberOfOdus> myTcmBProcList;

    // ODU Server (upper layer) identifier
    CT_ODU_ServerID myServerID;

    // ODU Alternate Server (alternate upper layer) identifier
    CT_ODU_ServerID myAltServerID;


    //Trace message (including SAPI, DAPI and operator 
    //specific text) to transmit in the ODU path overhead (PM).
    CT_G709Trace* mySentTracePtr;
    bool myTraceInUse;

    //Payload Structure Identifier
    CT_TEL_PayloadSignalId myTxPayloadType;


    //Add in Monitoring Configurations 
    //Signal degrade BER threshold
    CT_TEL_BERLevels myBerSdLevel;

    // Signal failure BER threshold
    CT_TEL_BERLevels mySfBerLevel;
	   
    
    // Set Interval and Threshold for bursty BerSd monitoring
    uint16 myBurstyBerSdIntervals;
    uint32 myBurstyBerSdThreshold;

    CT_PMProfileTableId myPMProfileId;

    //Set clock type
    CT_TEL_ClkType myClockType;

    //the Terminated ODU Indication to be sent when the layer is failed
    CT_ODU_IndicationType myTerminatedIndication;

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
    uint8  myChannelIndexInAID;

    //The session number for an Rx PRBS BER collection on a facility.
    uint32 myPrbsRxSessionCounter;

    // ODUflex Expected Signal Rate
    uint32 myExpSigRate;

    // ODUflex GFP TS.
    uint8 myGfpTs;

    // Cross connected ODU index on the same board.
    uint8 myCrossConnectedOduIdx;
};

#endif /* CFG_ODUOBJECT_H */

