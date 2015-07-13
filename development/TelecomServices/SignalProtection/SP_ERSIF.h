//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_ERSIF_H
#define SP_ERSIF_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <SignalProtection/SP_Definitions.h>

class SP_TimingRSConfigRegion;


//This class defines an abstract interface
//for equipment redundancy related operations
//Any module that supports equipment redundancy is
//expected to provide a concrete implementation of this
//interface
class SP_ERSIF
{
public:
    virtual void AcquireMastership() =0;
	virtual void ReleaseMastership() =0;
	virtual bool IsMaster() = 0;
	virtual bool IsMateMaster() = 0;
	virtual bool IsMatePresent() = 0;
    virtual bool IsMateReady() = 0;
    virtual void SendERSMessage(CT_ControllerMode theMode) = 0;
    virtual uint32 GetRxMessageCounter() = 0;
    virtual bool IsModuleOOS() = 0;
	virtual bool InitOnOOSAllowed() = 0;
    virtual void SetHeartBeatState(bool theState) = 0;
    virtual bool GetHeartBeatState() = 0;
    virtual void SetTxERSMessage(uint32 theMessage) = 0;
    virtual uint32 GetTxERSMessage() = 0;
    virtual uint32 GetRxERSMessage() = 0;
	virtual void ControlActiveLED(bool isActive) = 0;
};


//This class provides a base implementation for the above
//SP_ERSIF interface
class SP_ERSDefaultImp: public SP_ERSIF
{
public:
	// Default class constructor
    SP_ERSDefaultImp();
	
    // Virtual class destructor
    virtual ~SP_ERSDefaultImp();

    virtual void AcquireMastership();
	virtual void ReleaseMastership();
	virtual bool IsMaster();
	virtual bool IsMateMaster();
	virtual bool IsMatePresent();
    virtual bool IsMateReady();
    virtual void SendERSMessage(CT_ControllerMode theMode);
    virtual uint32 GetRxMessageCounter();
    virtual bool IsModuleOOS();
	virtual bool InitOnOOSAllowed();
    virtual void SetHeartBeatState(bool theState); 
    virtual bool GetHeartBeatState();
    virtual void SetTxERSMessage(uint32 theMessage);
    virtual uint32 GetTxERSMessage();
    virtual uint32 GetRxERSMessage();
	virtual void ControlActiveLED(bool isActive);

private:

};

#endif /* SP_ERSIF_H */
