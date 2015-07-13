/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_LAYER2OBJECT_H
#define CFG_LAYER2OBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>

#include "CFG_Object.h"


//This object contains all the generic SONET/SDH Regenerator 
//section configuration for one port.
class CFG_Layer2
: public CFG_Object
{

public:

	//Constructor.
    CFG_Layer2(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Layer2(void);

    // Get BandWidth Profile.
    int GetBWPF() const;

    // Set BandWidth Profile.
    void SetBWPF(int theBWPF);

    // Get Control Frame Profile.
    int GetCFPF() const;

    // Set Control Frame Profile.
    void SetCFPF(int theCFPF);

    // Get Port VLAN Id.
    uint32 GetPVID() const;

    // Set Port VLAN Id.
    void SetPVID(uint32 thePVID);

    // Get Tagmode of PVID.
    bool GetTagmode() const;

    // Set Tagmode of PVID.
    void SetTagmode(bool theTagmode);

    // Get Tag Protocol Id.
    uint32 GetTPID() const;

    // Set Tag Protocol Id.
    void SetTPID(uint32 theTPID);

    // Get Port Mode.
    uint8 GetPortMode() const;

    // Set Port Mode.
    void SetPortMode(uint8 thePortMode);


    // Get Port Lacp Priority.
    uint16 GetPortLacpPriority() const;

    // Set Port Lacp Priority.
    void SetPortLacpPriority(uint16 theLacpPriority);

    // Get Port Lacp Participation Mode.
    CT_TEL_LacpPartiMode GetPortLacpPartiMode() const;

    // Set Port Lacp Participation Mode.
    void SetPortLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode);

    // Get Mate Lacp Priority.
    uint16 GetMateLacpPriority() const;

    // Set Mate Lacp Priority.
    void SetMateLacpPriority(uint16 theLacpPriority);

    // Get Mate Lacp Participation Mode.
    CT_TEL_LacpPartiMode GetMateLacpPartiMode() const;

    // Set Mate Lacp Participation Mode.
    void SetMateLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode);


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
                    
    // BandWidth Profile for this port.
    int myBWPF;

    // Control Frame Profile for this port.
    int myCFPF;

    // Port VLAN Id.
    uint32 myPVID;

    // Indicates PVID should remain (Tagged) or remove (Untagged).
    bool myTagmode;

    // Tag Protocol Id.
    uint32 myTPID;

    // Port Mode.
    uint8 myPortMode;

    // the Port Lacp Priority.
    uint16 myPortLacpPriority;

    // the Port Lacp Participation Mode.
    CT_TEL_LacpPartiMode myPortLacpPartiMode;

    // the Mate Lacp Priority.
    uint16 myMateLacpPriority;

    // the Mate Lacp Participation Mode.
    CT_TEL_LacpPartiMode myMateLacpPartiMode;

};

#endif /* CFG_LAYER2OBJECT_H */

