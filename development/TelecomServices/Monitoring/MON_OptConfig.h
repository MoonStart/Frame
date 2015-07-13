//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OPTCONFIG_H
#define MON_OPTCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include "MON_OptDefects.h"

//This class contains configuration parameters that affects 
//how the monitoring of the optical (OPT) layer is performed.
class MON_OptConfig 
: public MON_Config
{
public:

    //Constructor.
    MON_OptConfig(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OptConfig();

    //Set Signal Degrade Power threshold for Optical Power
    //Note: CRM calls the Signal Degrade Power threshold switch_threshold.
    bool SetSdPwrThreshold(CT_TEL_mBm theSdPwrThreshold);

    //Get Signal Degrade Power threshold for Optical Power
    CT_TEL_mBm GetSdPwrThreshold() const;


    bool SetUpperLayerFailed(bool theState);
    bool GetUpperLayerFailed() const;

    bool SetInternalUpperLayerFailed(bool theState);
    bool GetInternalUpperLayerFailed() const;

    bool SetLayerLocked(bool theState);
    bool GetLayerLocked() const;

    bool SetEqptLocked(bool theState);
    bool GetEqptLocked() const;	

    void ClearOppositeSideBitMask();
    void ResetOppositeSidePosition(uint16 thePosition);
    void SetOppositeSidePosition(uint16 thePosition);
    uint16 GetOppositeSideBitMask() const;
    bool IsOppositeSidePositionSet(uint16 theBitMask, uint16 thePosition) const;

    bool SetOppositeSideIsPooled(bool theState);
    bool GetOppositeSideIsPooled() const;

    bool SetOppositeSideServerID(CT_ODU_ServerID theServerID);
    CT_ODU_ServerID GetOppositeSideServerID() const;

    bool SetOtnOppositeSideServerID(CT_ODU_ServerID theOtnServerID);
    CT_ODU_ServerID GetOtnOppositeSideServerID() const;

    bool SetIgnoreOppositeSide(bool theState);
    bool GetIgnoreOppositeSide() const;

    bool SetLosFailLayer(bool theState);
    bool GetLosFailLayer() const;
    uint16 GetFailLayerBitMask() const;

    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    CT_TEL_mBm  mySdPwrThreshold;

    bool myUpperLayerFailed;
    bool myInternalUpperLayerFailed;
    bool myLayerLocked;
    uint16 myOppositeSideBitMask;
    bool myOppositeSideIsPooled;
    CT_ODU_ServerID myOppositeSideServerID;
    bool myIgnoreOppositeSide;
    CT_ODU_ServerID myOtnOppositeSideServerID;  //Only be a place holder for Protection
    bool myEqptLocked;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;
};

#endif /* MON_OPTCONFIG_H */
