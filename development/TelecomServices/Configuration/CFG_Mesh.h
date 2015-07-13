/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_MESHSOBJECT_H
#define CFG_MESHSOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>

#include "CFG_Object.h"
/*
class CFG_Mesh
: public CFG_Object
{

public:

	//Constructor.
    CFG_Mesh(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Mesh(void);

    // Indicate Link is enabled.
    void SetLinkEnabled(CT_SlotId theSlotId);

    // Indicate Link is disabled.
    void SetLinkDisabled(CT_SlotId theSlotId);

    // Get Link Status for a slot.
    bool GetLinkStatus(CT_SlotId theSlotId) const;

    // Indicate we are in Mesh Mode.
    void SetSwitchMode(CT_TEL_SwitchMode theMode);

    // Get what mode we are in i.e. Mesh or non Mesh.
    CT_TEL_SwitchMode GetSwitchMode() const;

    // Indicate the number of Slots supported.
    void SetNbrOfSlots(uint8 theNbrSlots);

    // Get the number of Slots supported.
    uint8 GetNbrOfSlots() const;

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
                    
     // Link Enabled.
    bool myLinkEnabled[NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF];

    // Switch Mode Enabled.
    CT_TEL_SwitchMode mySwitchMode;

    // Number of Slots Supported.
    uint8 myNbrSlots;

};
*/
#endif /* CFG_MESHOBJECT_H */

