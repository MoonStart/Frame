//
//Copyright(c) Tellabs Transport Group. All rights reserved
//
#ifndef MON_OPTPROTCONFIG_H
#define MON_OPTPROTCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>

//This class contains configuration parameters that affects 
//how the monitoring of the optical (OPT) layer is performed.
class MON_OptProtConfig 
: public MON_Config
{
public:

    //Constructor.
    MON_OptProtConfig(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OptProtConfig();

    bool SetProtectionEnable(bool theState);
    bool GetProtectionEnable() const;

    void ClearOppositeSideBitMask();
    void ResetOppositeSidePosition(uint16 thePosition);
    void SetOppositeSidePosition(uint16 thePosition);
    uint16 GetOppositeSideBitMask() const;

    CT_IntfId GetOppositeSideIntfId() const;

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
    bool   myProtectionEnable;

    uint16 myOppositeSideBitMask;
};

#endif /* MON_OPTPROTCONFIG_H */
