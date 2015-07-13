/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_MISCSOBJECT_H
#define CFG_MISCSOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_SwitchDomainMap.h>

#include "CFG_Object.h"

/// This value used to be just the number of physical slots in port shelf, but needed to grow.
const uint8 CFG_MISC_MAX_SIZE = NUMBER_OF_TRN_IN_MTERA_SHELF + NUMBER_OF_MFAB_IN_MTERA_SHELF;

const uint8 CFG_LINK_STATE_MASK = 0xfe;
const uint8 CFG_CARD_STATE_MASK = 0xfd;

class CFG_Misc
: public CFG_Object
{

public:

	//Constructor.
    CFG_Misc(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Misc(void);

    // Set/Get Link Rate for a slot.
    void SetLinkRate(CT_SlotId theSlotId, CT_TEL_LinkRate theRate);
    CT_TEL_LinkRate GetLinkRate(CT_SlotId theSlotId) const;
    
    // Set/Get Remote Rate for a slot.
    void SetRemoteLinkRate(CT_SlotId theSlotId, CT_TEL_LinkRate theRate);
    CT_TEL_LinkRate GetRemoteLinkRate(CT_SlotId theSlotId) const;

    // Get Provisioned state of Link and Remote Link for a slot.
    bool GetLinkStatus(CT_SlotId theSlotId) const;
    bool GetRemoteLinkStatus(CT_SlotId theSlotId) const;

    // Set/Get Link state for a slot.
    void SetLinkOperState(CT_SlotId theSlotId, bool linkState);
    bool GetLinkOperState(CT_SlotId theSlotId) const;
    
    // Set/Get Remote Link State for a slot.
    void SetRemoteLinkOperState(CT_SlotId theSlotId, bool linkState);
    bool GetRemoteLinkOperState(CT_SlotId theSlotId) const;
    
    // Set/Get Card state for a slot.
    void SetCardOperState(CT_SlotId theSlotId, bool linkState);
    bool GetCardOperState(CT_SlotId theSlotId) const;
    
    // Set/Get Remote Card State for a slot.
    void SetRemoteCardOperState(CT_SlotId theSlotId, bool linkState);
    bool GetRemoteCardOperState(CT_SlotId theSlotId) const;

    // Set/Get provisioned card type for a slot.
    void SetCardType(CT_SlotId theSlotId, CT_CardType theCardType);
    CT_CardType GetCardType(CT_SlotId theSlotId) const;

    // Set/Get Remote provisioned card type for a slot.
    void SetRemoteCardType(CT_SlotId theSlotId, CT_CardType theCardType);
    CT_CardType GetRemoteCardType(CT_SlotId theSlotId) const;
    
    // Set/Get card revision number
    void SetCardHwVersion(CT_SlotId theSlotId, string theHwVersion){ myCardHwVersion[theSlotId-1] = theHwVersion; }
    string GetCardHwVersion(CT_SlotId theSlotId){ return myCardHwVersion[theSlotId-1]; }

    // Set/Get remote card revision number
    void SetRemoteCardHwVersion(CT_SlotId theSlotId, string theHwVersion){ myRemoteCardHwVersion[theSlotId-1] = theHwVersion; }
    string GetRemoteCardHwVersion(CT_SlotId theSlotId){ return myRemoteCardHwVersion[theSlotId-1]; }
    
    // Set/Get Switch Mode for shelf
    void SetSwitchMode(CT_TEL_SwitchMode theMode);
    CT_TEL_SwitchMode GetSwitchMode() const;

    // Set/Get Switch Domain Mode for shelf
    void SetSwitchDomainMode(CT_SwitchDomainMode theSwDomMode);
    CT_SwitchDomainMode GetSwitchDomainMode() const;

    // Indicate if we are in switched mode.
    bool IsSwitchMode() const;

    // Indicate if we are in mesh mode.
    bool IsMeshMode() const;

    // Indicate the number of Slots supported.
    void SetNbrOfSlots(uint8 theNbrSlots);

    // Set/Get the number of Slots supported.
    uint8 GetNbrOfSlots() const;
    void SetSwitchDomain(CT_SwitchDomain theMode);

    // Get what Switch Domain we are in..
    CT_SwitchDomain GetSwitchDomain() const;
    
    // Set/Get Shelf Type.
    void SetShelfType(CT_ShelfType theMode);
    CT_ShelfType GetShelfType() const;

    // Set/Get Protection Level
    void SetProtLvl(CT_ProtLevel theProtLvl);
    CT_ProtLevel GetProtLvl() const;
    
    // Set/Get the number of Fabric Slice provisioned.
    void SetNumFabSlice(uint8 numFabSlice);
    uint8 GetNumFabSlice() const;
    
    // Indicate Shelf Member of Switch Domain. 
    // 1st Para - Shelf Id
    // 2nd Para - Index into myDomainShelfMbrs array.
    // Set/Get Shelf Members of Switch Domain. Para - Index into myDomainShelfMbrs array.
    void SetDomainMbrShelfId(CT_ShelfId theMbrShelfId, uint8 theDomainArrayIndex);
    CT_ShelfId GetDomainMbrShelfId( uint8 theDomainArrayIndex );

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

     // Link Rate. THIS WILL REPLACE myLinkEnabled.
    CT_TEL_LinkRate myLinkRate[CFG_MISC_MAX_SIZE];
    
    // Remote Rate. THIS WILL REPLACE myRemoteLinkEnabled.
    CT_TEL_LinkRate myRemoteLinkRate[CFG_MISC_MAX_SIZE];                  

     // Link State.
    uint8 myLinkOperState[CFG_MISC_MAX_SIZE];
    
    // Remote Shelf Link Enabled.
    uint8 myRemoteLinkOperState[CFG_MISC_MAX_SIZE];

    //Local shelf populated card types
    CT_CardType myCardTypeList[CFG_MISC_MAX_SIZE];

    //remote shelf populated card types
    CT_CardType myRemoteCardTypeList[CFG_MISC_MAX_SIZE];

    //Local shelf populated card revision numbers
    string myCardHwVersion[CFG_MISC_MAX_SIZE];

    //Remote shelf populated card revision numbers
    string myRemoteCardHwVersion[CFG_MISC_MAX_SIZE];

    // Switch Mode.
    CT_TEL_SwitchMode mySwitchMode;

    // Switch Domain Mode
    CT_SwitchDomainMode mySwitchDomainMode;

    // Number of Slots Supported.
    uint8 myNbrSlots;

    // Switch Domain Id
    CT_SwitchDomain mySwitchDomain;

    // Domain Shelf Members.
    CT_ShelfId myDomainShelfMbrs[MAX_HCSS_SWFAB_SHELF];

    // Shelf Type.
    CT_ShelfType myShelfType;

    // Protection Level
    CT_ProtLevel myProtLvl;

    // Number of Fabric Slices
    uint8 myNumFabSlice;

    //Link Rate Override - This is only used for SIT/SWIT testing.
    CT_TEL_LinkRate myLinkRateOverride;
};

#endif /* CFG_MISCOBJECT_H */

