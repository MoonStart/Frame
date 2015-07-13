//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_GFPCONFIG_H
#define MON_GFPCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>
#include "MON_GfpDefects.h"

//This class contains configuration parameters that affects 
//how the monitoring of the GFP layer 
//is performed.
class MON_GfpConfig : public MON_Config
{
public:

    //Constructor.
    MON_GfpConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_GfpConfig();

    bool SetGfpLfFailLayer(bool theState);
    
    bool GetGfpLfFailLayer() const;
    
    bool SetGfpRfFailLayer(bool theState);
    
    bool GetGfpRfFailLayer() const;
    
    bool SetGfpFefiFailLayer(bool theState);
    
    bool GetGfpFefiFailLayer() const;
    
    bool SetGfpCsfFefiFailLayer(bool theState);
    
    bool GetGfpCsfFefiFailLayer() const;
    
    bool SetGfpLinkFailRxFailLayer(bool theState);
    
    bool GetGfpLinkFailRxFailLayer() const;
    
    bool SetGfpCsfLosFailLayer(bool theState);  
    
    bool GetGfpCsfLosFailLayer() const;
    
    bool SetGfpLofdFailLayer(bool theState);
    
    bool GetGfpLofdFailLayer() const;
    
    bool SetGfpPlmFailLayer(bool theState);
    
    bool GetGfpPlmFailLayer() const;
    
    bool SetGfpCsfLosyncFailLayer(bool theState);
    
    bool GetGfpCsfLosyncFailLayer() const;
    
    bool SetGfpCsfFdiFailLayer(bool theState);
    
    bool GetGfpCsfFdiFailLayer() const;

    bool SetGfpCsfRdiFailLayer(bool theState);
    
    bool GetGfpCsfRdiFailLayer() const;

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
    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;       
};

#endif /* MON_GFPCONFIG_H */

