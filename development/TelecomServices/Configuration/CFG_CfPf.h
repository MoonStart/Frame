/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_CFPFOBJECT_H
#define CFG_CFPFOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Cfpf
: public CFG_Object
{

public:

	//Constructor.
    CFG_Cfpf(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Cfpf(void);

    // Get State of Tunneling of Link Aggregation Control Protocol.
    bool GetLACP() const;
    
    // Set State of Tunneling of Link Aggregation Control Protocol.
    void SetLACP(bool theLACP);

    // Get State of Tunneling of Link Operations, Administration and Maintenance Protocol
    bool GetLinkOAM() const;

    // Set State of Tunneling of Link Operations, Administration and Maintenance Protocol.
    void SetLinkOAM(bool theLinkOAM);

    // Get State of Tunneling of Dot1X authentication.
    bool GetDot1X() const;

    // Set State of Tunneling of Dot1X authentication.
    void SetDot1X(bool theDot1X);

    // Get State of Tunneling of Enhanced Local Management Interface protocol.
    bool GetELMI() const;

    // Set State of Tunneling of Enhanced Local Management Interface protocol.
    void SetELMI(bool theELMI);

    // Get State of Tunneling of Link Layer Discovery Protocol.
    bool GetLLDP() const;

    // Set State of Tunneling of Link Layer Discovery Protocol.
    void SetLLDP(bool theLLDP);

    // Get State of Tunneling of GARP Control Frames
    bool GetGARP() const;

    // Set State of Tunneling of GARP Control Frames.
    void SetGARP(bool theLLDP);

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

    // Enable Tunneling of Link Aggregation Control Protocol.
    bool myLACP;

    // Enable Tunneling of Link Operations, Administration and Maintenance Protocol. 
    bool myLinkOAM;
    
    // Enable Tunneling of Dot1X authentication.
    bool myDot1X;
    
    // Enable Tunneling of Enhanced Local Management Interface protocol.
    bool myELMI;
    
    // Enable Tunneling of Link Layer Discovery Protocol.
    bool myLLDP;

    // Enable Tunneling of GARP Control Frames.
    bool myGARP;
};

#endif /* CFG_CFPFOBJECT_H */

