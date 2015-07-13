/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_SWITCHDOMAINOBJECT_H
#define CFG_SWITCHDOMAINOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_SwitchDomainMap.h>
#include <CommonTypes/CT_AM_Definitions.h>

#include "CFG_Object.h"

class CFG_SwitchDomain: public CFG_Object
{
public:

	//Constructor.
    CFG_SwitchDomain(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_SwitchDomain(void);

    // Set/Get Shelf ID
    inline void SetShelfId(CT_ShelfId theShelfId){myShelfId = theShelfId;}
    inline CT_ShelfId GetShelfId() {return myShelfId;}

    // Set/Get Shelf Type
    inline void SetShelfType(CT_ShelfType theShelfType){myShelfType = theShelfType;}
    inline CT_ShelfType GetShelfType() {return myShelfType;}

    // Set/Get First UFAB
    inline void SetFirstUfab(CT_SlotId theFirstUfab){myFirstUfab = theFirstUfab;}
    inline CT_SlotId GetFirstUfab() {return myFirstUfab;}

    // Set/Get Number of UFABS
    inline void SetNumUfabs(CT_SlotId theNumUfabs){myNumUfabs = theNumUfabs;}
    inline CT_SlotId GetNumUfabs() {return myNumUfabs;}

    // Set/Get Number of CXPs per UFAB
    inline void SetNumCxpsPerUfab(CT_SlotId theNumCxpsPerUfab){myNumCxpsPerUfab = theNumCxpsPerUfab;}
    inline CT_SlotId GetNumCxpsPerUfab() {return myNumCxpsPerUfab;}

    // Set/Get Switch Domain Mode
    void SetSwitchDomainMode(CT_SwitchDomainMode theSwitchDomainMode);
    CT_SwitchDomainMode GetSwitchDomainMode();

    // Set/Get Card state for a slot.
    void SetCardOperState(CT_SlotId theSlotId, bool linkState);
    bool GetCardOperState(CT_SlotId theSlotId);

    // Set/Get the SwitchMode
    void SetSwitchMode(CT_SlotId theSlotId, CT_TEL_SwitchMode theSwitchMode);
    CT_TEL_SwitchMode GetSwitchMode(CT_SlotId theSlotId);

    // Set/Get Link state for a slot.
    void SetLinkOperState(CT_SlotId theSlotId, CT_SlotId theSubSlotId,  bool linkState);
    bool GetLinkOperState(CT_SlotId theSlotId, CT_SlotId theSubSlotId);
    
    // Set/Get Remote Link HW Revision Level.
    void SetRemoteHwRev(CT_SlotId theSlotId, CT_SlotId theSubSlotId, string& theRevLevel);
    string GetRemoteHwRev(CT_SlotId theSlotId, CT_SlotId theSubSlotId) const;

    // Set/Get Link (Port) mapping
    void SetLinkMap(CT_SlotId theSlotId, CT_SlotId theSubSlotId, CT_TL1_SlotAddr theDstCxp);
    const CT_TL1_SlotAddr& GetLinkMap(CT_SlotId theSlotId, CT_SlotId theSubSlotId);

    // Set/Get Cable Length 
    void SetCableLength(CT_SlotId theSlotId, CT_SlotId theSubSlotId, CT_CableLength theCableLength);
    CT_CableLength GetCableLength(CT_SlotId theSlotId, CT_SlotId theSubSlotId);

    //Get the switch domain mode from SS90; TEMPORARY
    static CT_SwitchDomainMode GetSystemSwitchDomainMode();
    static bool SwitchDomainModeSupportsSS();

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

    //Shelf ID
    CT_ShelfId myShelfId;

    //Shelf Type
    CT_ShelfType myShelfType;

    //First UFAB - this will vary based on shelf type
    CT_SlotId myFirstUfab;

    //Number of UFABS - dictated by the shelf type
    CT_SlotId myNumUfabs;

    //Number of CXPs per UFAB - dictated by the shelf type
    CT_SlotId myNumCxpsPerUfab;

    // Switch Domain Mode - This will dictate our expected mapping for a multiswitch configuration
    CT_SwitchDomainMode mySwitchDomainMode;

    // Card Oper State
    bool myCardOperState[NUMBER_OF_UFAB_IN_SWITCH_SHELF];

    // Switch Mode (Note the difference between this and SwitchDomainMode) -- this should be the 
    // same for every UFAB across a Port Shelf, but conceptually UFAB-C's can be repeater or
    // center in a future expansion.
    CT_TEL_SwitchMode mySwitchMode[NUMBER_OF_UFAB_IN_SWITCH_SHELF];

    // Link (Port) Oper State 
    bool myLinkOperState[NUMBER_OF_UFAB_IN_SWITCH_SHELF][MAX_NUM_CXP_ON_UFABC];

    //Remote IDPROM Hw Rev Level (Important for cable link information)
    string myRemoteHwRev[NUMBER_OF_UFAB_IN_SWITCH_SHELF][MAX_NUM_CXP_ON_UFABC];

    // CXP Mapping
    CT_SwitchDomainCxpMap myCxpMap;

    // Cable Length (associated by port, as UFAB-C can have multiple cable lengths coming in)
    CT_CableLength myCableLength[NUMBER_OF_UFAB_IN_SWITCH_SHELF][MAX_NUM_CXP_ON_UFABC];

    //Convert the UFAB slot ID to a usable index
    uint SlotToIndex(CT_SlotId theSlotId) const;
    CT_SlotId IndexToSlot(uint index);

};


#endif /* CFG_SWITCHDOMAINOBJECT_H */


