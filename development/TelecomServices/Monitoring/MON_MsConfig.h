//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_MSCONFIG_H
#define MON_MSCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>
#include "MON_MsDefects.h"

//This class contains configuration parameters that affects 
//how the monitoring of the SONET multiplex section layer 
//is performed.
class MON_MsConfig : public MON_Config
{
public:

    //Constructor.
    MON_MsConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_MsConfig();

    //Set Signal Degrade threshold for BER
    bool SetBerSdThreshold(CT_TEL_BERLevels theSdBerThreshold);

    //Set Signal Failure threshold for BER
    bool SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold);

    //Get Signal Degrade threshold for BER
    CT_TEL_BERLevels GetBerSdThreshold() const;

    //Get Signal Failure threshold for BER
    CT_TEL_BERLevels GetBerSfThreshold() const;

    bool SetAisFailLayer(bool theState);

    bool GetAisFailLayer() const;

    bool SetInternalAisFailLayer(bool theState);

    bool GetInternalAisFailLayer() const;

    bool SetPropAisFailLayer(bool theState);

    bool GetPropAisFailLayer() const;    

    uint16 GetFailLayerBitMask() const;

    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //Signal degrade BER threshold
    CT_TEL_BERLevels mySdBerLevel;

    // Signal failure BER threshold
    CT_TEL_BERLevels mySfBerLevel;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;       
};

#endif /* MON_OTUCONFIG_H */
