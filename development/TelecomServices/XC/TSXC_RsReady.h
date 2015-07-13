/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     July, 2006  Jai Harpalani
 DESCRIPTION:   TSXC_RsReady  Class Definition
--------------------------------------------------------------------------*/

#ifndef TSXC_RSREADY_H
#define TSXC_RSREADY_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_Telecom.h>

//
// This class stores the readiness state of the information in the RS Region.
// The RS Region is considered ready when it has been applied to TSPII.
//
class TSXC_RsReady : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_RsReady();

    // Class destructor
    virtual ~TSXC_RsReady();

    //
    // Methods to set object attributes
    //
    void SetReadyFlag(bool theFlagValue);
    void SetSignalType(uint8 thePort, CT_TEL_SignalType theSigType);

    //
    // Methods to get object attributes
    //
    bool                GetReadyFlag();
    CT_TEL_SignalType   GetSignalType(uint8 thePort);   

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    bool                myReadyFlag;
    CT_TEL_SignalType   myCfgSigType[XC_MAX_PORT_INTF];
};

#endif // TSXC_RSREADY_H

