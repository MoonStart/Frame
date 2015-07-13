/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_MACOBJECT_H
#define CFG_MACOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>

#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Mac
: public CFG_Object
{

public:

	//Constructor.
    CFG_Mac(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Mac(void);

    // Set Auto-Negotiation.
    bool GetAutoNeg() const;

    // Get Auto-Negotiation
    bool SetAutoNeg(bool theAutoNeg);

    // Get Selected Ethernet Rate.
    CT_TEL_daHz GetEthernetRate() const;

    // Set Selected Ethernet Rate.
    bool SetEthernetRate(CT_TEL_daHz theEthernetRate);

    // Get Selected Ethernet Mode.
    CT_TEL_MAC_DUPLEX_MODE GetDuplexMode() const;

    // Set Selected Ethernet Rate.
    bool SetDuplexMode(CT_TEL_MAC_DUPLEX_MODE theDuplexMode);

    // Get Advertised Flow Control.
    CT_TEL_MAC_ADFLW_CTRL GetAdvrtFlowCtrl() const;

    // Set Advertised Flow Control.
    bool SetAdvrtFlowCtrl(CT_TEL_MAC_ADFLW_CTRL theAdvrtFlowCtrl);

    // Get Flow Control.
    CT_TEL_MAC_FLOWCTRL GetFlowControl() const;

    // Set Flow Control.
    bool SetFlowControl(CT_TEL_MAC_FLOWCTRL theFlowControl);

	//Debug Methods
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
                    
    // Auto Negotiation Enabled/Disabled.
    bool myAutoNeg;

    // Selected Ethernet Rate.
	CT_TEL_daHz myEthernetRate;
	
    // Selected Ethernet Mode (Duplex Status).
    CT_TEL_MAC_DUPLEX_MODE myDuplexMode;

    // Advertised Flow Control used in Auto Negotiation.
    CT_TEL_MAC_ADFLW_CTRL myAdvrtFlowCtrl;

    // Flow Control Manual Configuration.
    CT_TEL_MAC_FLOWCTRL myFlowControl;
};

#endif /* CFG_MACOBJECT_H */

