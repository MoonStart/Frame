/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved
--------------------------------------------------------------------------*/
#ifndef TSXC_MUXCFG_H
#define TSXC_MUXCFG_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>

//--------------------------------------------------------------------------------------------------
// This class contains information to support MUX Cfg configuration
//--------------------------------------------------------------------------------------------------

class TSXC_MuxCfg : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_MuxCfg();

    // Class destructor
    virtual ~TSXC_MuxCfg();

    void InitMux();
            
    void SetHighOdu(uint16 theHighOdu) { myHighOdu = theHighOdu; }
    void SetLowOdu(uint16  theLowOdu) { myLowOdu = theLowOdu; }
    void SetTribSlot(uint16*  theTribSlot);
            
    uint16 GetHighOdu() { return myHighOdu; }
    uint16 GetLowOdu () { return myLowOdu;  }
    void GetTribSlot(uint16*  theTribSlot);
    void PrintMux();

    //
    // Operators
    //
    bool operator==(const TSXC_MuxCfg& theMuxCfg) const;
    bool operator!=(const TSXC_MuxCfg& theMuxCfg) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    uint16    myHighOdu;
    uint16    myLowOdu;
    uint16    myTribSlotBitmap[TSXC_MUX_BITMAP_LENGTH];
};

#endif // TSXC_MUXCFG_H
