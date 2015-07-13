//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_ODUSTATUS_H
#define MON_ODUSTATUS_H

#include "MON_Status.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>


//This class hold the status value (trace message, levels) 
//for the ODU layer.
class MON_OduStatus 
: public MON_Status
{
public:
	
    //Constructor.
    MON_OduStatus(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OduStatus(void);

    //Returns the level of the status provide as argument.
    virtual void GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const;

    //Returns true if level has changed.
    virtual bool SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel);


    //Sets the receive ODU (PM) trace message.
    bool SetTraceMessage(const CT_G709Trace theTrace);
    void DeleteTraceMessage();

    //Returns the receive ODU (PM) trace message.
    CT_G709Trace & GetTraceMessage() const;


    const uint8 GetRxPayloadType() const;
    bool SetRxPayloadType(const uint8 theRxPayloadType);

    const CT_TEL_TS_SIZE GetActTribSize() const;
    bool SetActTribSize(const CT_TEL_TS_SIZE theActTribSize);

    const bool GetServerSignalFail() const;
    bool SetServerSignalFail(const bool theServerSignalFail);

    const bool GetServerSignalDegrade() const;
    bool SetServerSignalDegrade(const bool theServerSignalDegrade);

    const bool GetAutoFallbackStatus() const;
    bool SetAutoFallbackStatus(const bool theAutoFallbackStatus);

    bool SetPathDelay(const int32 theTcmDelay);
    int32 GetPathDelay() const;

    //Sets the Most Significant Digits of the PRBS Rx Error Counter
    bool SetPrbsRxMostSignifCount(uint32 thePrbsRxMostSignifCount) ;

    //Gets the Most Significant Digits of the PRBS Rx Error Counter
     uint32 GetPrbsRxMostSignifCount() const ;

    //Sets the Least Significant Digits of the PRBS Rx Error Counter
    bool SetPrbsRxLeastSignifCount(uint32 thePrbsRxLeastSignifCount) ;

    //Gets the Least Significant Digits of the PRBS Rx Error Counter
    uint32 GetPrbsRxLeastSignifCount() const ;

    //Sets the Time associated with the PRBS Rx Error Counter
    bool SetPrbsRxTimeInterval(uint32 thePrbsRxTimeInterval) ;

    //Gets the Time associated with the PRBS Rx Error Counter
    uint32 GetPrbsRxTimeInterval() const ;

    //Sets the PRBS Rx Losync
    bool SetPrbsRxLosync(CT_TEL_PrbsSyncStatus thePrbsRxLosync) ;

    //Gets the PRBS Rx Losync
    CT_TEL_PrbsSyncStatus GetPrbsRxLosync() const ;

    // Sets the PRBS Rx Losync Count
    bool SetPrbsRxFirstSyncLosyncCount(uint32 thePrbsRxLosyncCount);

    // Gets the PRBS Rx Losync Count
    uint32 GetPrbsRxFirstSyncLosyncCount() const;

    // Sets the PRBS Rx First Sync flag
    bool SetPrbsRxFirstSync(bool thePrbsRxFirstSync);

    // Gets the PRBS Rx First Sync flag
    bool GetPrbsRxFirstSync() const;

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	
    //The receive ODU (PM) trace message.
    CT_G709Trace* myTraceMessagePtr;
    bool myTraceInUse;

    uint8        myRxPayloadType;

    //The actual trib size: 1.25G, 2.5G
    CT_TEL_TS_SIZE myActTribSize;

    //Indicates if Server Signal Fail
    bool         myServerSignalFail;

    //Indicates if Server Signal Degrade
    bool         myServerSignalDegrade;

    //Indicates if Auto fallback happens
    bool         myAutoFallbackStatus;

    // The Oduk Path Delay measurement
    int32        myPathDelay;

    //The Most Significant Digits of the PRBS Rx Error Counter
    uint32 myPrbsRxMostSignifCount;
    //The Least Significant Digits of the PRBS Rx Error Counter
    uint32 myPrbsRxLeastSignifCount;
    //The Time associated with the PRBS Rx Error Counter
    uint32 myPrbsRxTimeInterval;
    //The PRBS Rx Losync
    CT_TEL_PrbsSyncStatus myPrbsRxLosync;
    //The PRBS Rx LosyncCount
    uint32 myPrbsRxFirstSyncLosyncCount;
    //Flag indicating when Prbs first goes in Sync
    bool myPrbsRxFirstSync;
};

#endif /* MON_ODUSTATUS_H */
