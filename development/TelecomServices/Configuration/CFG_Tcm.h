/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_TCMOBJECT_H
#define CFG_TCMOBJECT_H

//#include <gdef.h>
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <list>

#include "CFG_Object.h"


//This object contains all the generic ODU TCM configuration.
class CFG_Tcm: public CFG_Object
{

public:
    //Constructor.
    CFG_Tcm(uint32 theIndex);

    //Virtual destructor.
    virtual ~CFG_Tcm(void);

    // This methods sets the TCM Identifies
    bool SetTcmIdentifier(CT_ODU_Identifier theTcmId);

    //This method returns the TCM Identifies
    CT_ODU_Identifier GetTcmIdentifier() const; 

    //This method sets the value of the 'sent Trace' in the 
    //TTI byte of the TCM overhead.
    bool SetSentTrace(const CT_G709Trace& theSentTrace);
    bool DeleteSentTrace();

    //This method returns the set value of the 'sent Trace' 
    //in the TTI byte of the TCM overhead.
    CT_G709Trace & GetSentTrace() const;

    //Add in Monitoring Configurations 
    //Set Signal Degrade interval for BER
    bool SetBerSdInterval(uint16 theSdInterval);

    //Get Signal Degrade interval for BER
    uint16 GetBerSdInterval() const;

    //Set Signal Degrade threshold for BER
    bool SetBerSdThreshold(uint32 theSdThreshold);

    //Get Signal Degrade threshold for BER
    uint32 GetBerSdThreshold() const;


    bool SetPMProfileId(CT_PMProfileTableId thePMPFId);
    CT_PMProfileTableId GetPMProfileId() const;

    bool SetTcmMode(CT_TCM_Mode theTcmMode);
    CT_TCM_Mode GetTcmMode() const;

    bool SetOduBbIndex(bbindex_t theOduBbIndex);
    bbindex_t GetOduBbIndex() const;

    bool SetProvisionningActive(bool theProvisionningActive);
    bool GetProvisionningActive() const;

    // This methods sets the Server ID for the upper layer
    bool SetServerID(CT_ODU_ServerID theServerId);

    //This method returns the Server ID for the upper layer
    CT_ODU_ServerID GetServerID() const; 

    //Set the channel index in TCM AID
    bool SetChannelIndexInAID(uint8 theChannelIndexInAID);

    //Get the channel index in TCM AID
    uint8 GetChannelIndexInAID() const;

    //These methods set/get whether the Tcm Delay measurement is enabled.
    bool SetTcmDelayEnabled(bool theEnable);
    bool GetTcmDelayEnabled() const;

    bool SetTcmOrder(CT_TCM_Order theTcmOrder);
    CT_TCM_Order GetTcmOrder() const;

    //These methods set/get whether the Tcm ACT is enabled.
    bool SetTcmLTCActEnabled(bool theEnable);
    bool GetTcmLTCActEnabled() const;


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
    //Trace message (including SAPI, DAPI and operator 
    //specific text) to transmit in the TCM path overhead (PM).
    CT_G709Trace* mySentTracePtr;
    bool myTraceInUse;

    //Add in Monitoring Configurations 
    //Signal degrade BER threshold
    CT_TEL_BERLevels mySdBerLevel;

    uint16 mySdInterval;
    uint32 mySdThreshold;

    CT_PMProfileTableId myPMProfileId;

    CT_TCM_Mode myTcmMode;

    bbindex_t myOduBbIndex;

    bool myProvisionningActive;

    //Server (upper layer) identifier
    CT_ODU_ServerID myServerID;

    CT_ODU_Identifier myTcmId;

    // The field for channel in TCM AID. PM needs this info for pm file operations.
    uint8  myChannelIndexInAID;

    //the Tcm Delay measurement is enabled.
    bool myTcmDelayEnabled;

    CT_TCM_Order myTcmOrder;

    bool myTcmLTCActEnabled;
};

#endif /* CFG_TCMOBJECT_H */

