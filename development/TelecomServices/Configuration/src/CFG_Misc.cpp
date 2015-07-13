//Copyright(c) Tellabs Transport Group. All rights reserved

#include <string.h>
#include "../CFG_Misc.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

//-----------------------------------------------------------------------------
CFG_Misc::CFG_Misc(uint32 theIndex):
    CFG_Object(theIndex),
    mySwitchDomainMode(CT_SWITCHDOMAINMODE_UNKNOWN),
    mySwitchMode(CT_TEL_SwitchMode_None),
    myNbrSlots(CFG_MISC_MAX_SIZE),
    mySwitchDomain(CT_SWITCH_DOMAIN_UNKNOWN),
    myShelfType(UNKNOWN_SHELF),
    myProtLvl(CT_NONE),
    myNumFabSlice(0)
{
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        myLinkRate[i]            = CT_TEL_LinkRateNone;
        myRemoteLinkRate[i]      = CT_TEL_LinkRateNone;
        myLinkOperState[i]       = false;
        myRemoteLinkOperState[i] = false;
        myCardTypeList[i]        = CARD_TYPE_UNKNOWN;
        myRemoteCardTypeList[i]  = CARD_TYPE_UNKNOWN;
        myCardHwVersion[i]       = "";
        myRemoteCardHwVersion[i] = "";
    }
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        myDomainShelfMbrs[i] = UNKNOWN_SHELF;
    }
        
    // Override no longer needed.  SSM/SPFAB in USS will now use official 5Gbs rate.
    myLinkRateOverride = CT_TEL_LinkRateNone;
}

//-----------------------------------------------------------------------------
CFG_Misc::~CFG_Misc(void)
{
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetLinkRate(CT_SlotId theSlotId, CT_TEL_LinkRate theRate)
{
    // CFG Link Rate array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        // This code is only needed for SWIT/SIT as 3Gbs SSM will be deployed in the field. Only applies to SPFAB (USS Shelf).
        if ((myLinkRateOverride != CT_TEL_LinkRateNone) 
            && ((theRate == CT_TEL_LinkRate5Gbs) || (theRate == CT_TEL_LinkRate3Gbs) || (theRate == CT_TEL_LinkRate6Gbs)))
        {
            myLinkRate[theSlotId] = myLinkRateOverride;
        }
        else
            myLinkRate[theSlotId] = theRate;
    }
}

//-----------------------------------------------------------------------------
CT_TEL_LinkRate CFG_Misc::GetLinkRate(CT_SlotId theSlotId) const
{
    // CFG Link Rate array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
        return myLinkRate[theSlotId];

    return CT_TEL_LinkRateNone;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetRemoteLinkRate(CT_SlotId theSlotId, CT_TEL_LinkRate theRate)
{
    // CFG Link Rate array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        // This code is only needed for SWIT/SIT as 3Gbs SSM will be deployed in the field. Only applies to SPFAB (USS Shelf).
        if ((myLinkRateOverride != CT_TEL_LinkRateNone) 
            && ((theRate == CT_TEL_LinkRate5Gbs) || (theRate == CT_TEL_LinkRate3Gbs) || (theRate == CT_TEL_LinkRate6Gbs)))
        {
            myRemoteLinkRate[theSlotId] = myLinkRateOverride;
        }
        else
            myRemoteLinkRate[theSlotId] = theRate;
    }
}

//-----------------------------------------------------------------------------
CT_TEL_LinkRate CFG_Misc::GetRemoteLinkRate(CT_SlotId theSlotId) const
{
    // CFG Link Rate array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
        return myRemoteLinkRate[theSlotId];

    return CT_TEL_LinkRateNone;
}

//-----------------------------------------------------------------------------
// Set/Get provisioned card type for a slot.
void CFG_Misc::SetCardType(CT_SlotId theSlotId, CT_CardType theCardType)
{
    // CFG local card type is zero based
    if (theSlotId < myNbrSlots)
    {
        myCardTypeList[theSlotId] = theCardType;
    }
}

//-----------------------------------------------------------------------------
CT_CardType CFG_Misc::GetCardType(CT_SlotId theSlotId) const
{
    // CFG remote card type is zero based
    if (theSlotId < myNbrSlots)
    {
        return (myCardTypeList[theSlotId]);
    }
    return CARD_TYPE_UNKNOWN;
}

//-----------------------------------------------------------------------------
// Set/Get Remote provisioned card type for a slot.
void CFG_Misc::SetRemoteCardType(CT_SlotId theSlotId, CT_CardType theCardType)
{
    // CFG remote card type is zero based
    if (theSlotId < myNbrSlots)
    {
        myRemoteCardTypeList[theSlotId] = theCardType;
    }
}

//-----------------------------------------------------------------------------
CT_CardType CFG_Misc::GetRemoteCardType(CT_SlotId theSlotId) const
{
    // CFG remote card type is zero based
    if (theSlotId < myNbrSlots)
    {
        return (myRemoteCardTypeList[theSlotId]);
    }
    return CARD_TYPE_UNKNOWN;
}


//-----------------------------------------------------------------------------
bool CFG_Misc::GetLinkStatus(CT_SlotId theSlotId) const
{
    // CFG Link Enabled array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        return ((GetLinkRate(theSlotId) != CT_TEL_LinkRateNone) && 
                (GetLinkOperState(theSlotId) == true));
    }

    return false;
}

//-----------------------------------------------------------------------------
bool CFG_Misc::GetRemoteLinkStatus(CT_SlotId theSlotId) const
{
    // CFG Remote Link Enabled array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        return ((GetRemoteLinkRate(theSlotId) != CT_TEL_LinkRateNone) && 
                (GetRemoteLinkOperState(theSlotId) == true));
    }

    return false;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetLinkOperState(CT_SlotId theSlotId, bool linkState)
{
    uint8 aMask = CFG_LINK_STATE_MASK; // state for if linkState is true

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        if ( linkState )
        {
            myLinkOperState[theSlotId] = (myLinkOperState[theSlotId] | (~aMask));
        }
        else
        {
            myLinkOperState[theSlotId] = (myLinkOperState[theSlotId] & aMask);
        }
    }
}

//-----------------------------------------------------------------------------
bool CFG_Misc::GetLinkOperState(CT_SlotId theSlotId) const
{
    uint8 aState = 0x0;

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        aState = (myLinkOperState[theSlotId]  & (~CFG_LINK_STATE_MASK));
    }

    if ( aState )
        return true;
    else
        return false;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetRemoteLinkOperState(CT_SlotId theSlotId, bool linkState)
{
    uint8 aMask = CFG_LINK_STATE_MASK; // state for if linkState is true

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        if ( linkState )
        {
            myRemoteLinkOperState[theSlotId] = (myRemoteLinkOperState[theSlotId] | (~aMask));
        }
        else
        {
            myRemoteLinkOperState[theSlotId] = (myRemoteLinkOperState[theSlotId] & aMask);
        }
    }
}

//-----------------------------------------------------------------------------
bool CFG_Misc::GetRemoteLinkOperState(CT_SlotId theSlotId) const
{
    uint8 aState = 0x0;

    // CFG Remote Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        aState = (myRemoteLinkOperState[theSlotId]  & (~CFG_LINK_STATE_MASK));
    }

    if ( aState )
        return true;
    else
        return false;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetCardOperState(CT_SlotId theSlotId, bool cardState)
{
    uint8 aMask = CFG_CARD_STATE_MASK; // state for if linkState is true

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        if ( cardState )
        {
            myLinkOperState[theSlotId] = (myLinkOperState[theSlotId] | (~aMask));
        }
        else
        {
            myLinkOperState[theSlotId] = (myLinkOperState[theSlotId] & aMask);
        }
    }
}

//-----------------------------------------------------------------------------
bool CFG_Misc::GetCardOperState(CT_SlotId theSlotId) const
{
    uint8 aState = 0x0;

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        aState = (myLinkOperState[theSlotId]  & (~CFG_CARD_STATE_MASK));
    }

    if ( aState )
        return true;
    else
        return false;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetRemoteCardOperState(CT_SlotId theSlotId, bool cardState)
{
    uint8 aMask = CFG_CARD_STATE_MASK; // state for if linkState is true

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        if ( cardState )
        {
            myRemoteLinkOperState[theSlotId] = (myRemoteLinkOperState[theSlotId] | (~aMask));
        }
        else
        {
            myRemoteLinkOperState[theSlotId] = (myRemoteLinkOperState[theSlotId] & aMask);
        }
    }
}

//-----------------------------------------------------------------------------
bool CFG_Misc::GetRemoteCardOperState(CT_SlotId theSlotId) const
{
    uint8 aState = 0x0;

    // CFG Link Operational State array is zero based i.e. 0 thru 5.
    if (theSlotId < myNbrSlots)
    {
        aState = (myRemoteLinkOperState[theSlotId]  & (~CFG_CARD_STATE_MASK));
    }

    if ( aState )
        return true;
    else
        return false;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetSwitchMode(CT_TEL_SwitchMode theMode)
{
    mySwitchMode = theMode;
}

//-----------------------------------------------------------------------------
CT_TEL_SwitchMode CFG_Misc::GetSwitchMode() const
{
    return mySwitchMode;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetSwitchDomainMode(CT_SwitchDomainMode theSwDomMode)
{
    mySwitchDomainMode = theSwDomMode;
}

//-----------------------------------------------------------------------------
CT_SwitchDomainMode CFG_Misc::GetSwitchDomainMode() const
{
    return mySwitchDomainMode;
}

//-----------------------------------------------------------------------------
bool CFG_Misc::IsSwitchMode() const
{
    bool retVal;

    retVal = false;
    if ( (mySwitchMode == CT_TEL_SwitchMode_Cntr_Switch) ||
         (mySwitchMode == CT_TEL_SwitchMode_Repeater) ||
         (mySwitchMode == CT_TEL_SwitchMode_End_Switch) )
    {
        retVal = true;
    }

    return retVal;
}

//-----------------------------------------------------------------------------
bool CFG_Misc::IsMeshMode() const
{
    bool retVal;

    retVal = false;
    if (mySwitchMode == CT_TEL_SwitchMode_Mesh)
    {
        retVal = true;
    }

    return retVal;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetNbrOfSlots(uint8 theNbrSlots)
{
    if (theNbrSlots > CFG_MISC_MAX_SIZE)
        FC_THROW_ERROR (FC_LogicError, "!!! Attempting to configure beyond array maximum !!!");

    myNbrSlots = theNbrSlots; 
}

//-----------------------------------------------------------------------------
uint8 CFG_Misc::GetNbrOfSlots() const
{
    return myNbrSlots;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetSwitchDomain(CT_SwitchDomain theSwitchDomain)
{
    mySwitchDomain = theSwitchDomain;
}

//-----------------------------------------------------------------------------
CT_SwitchDomain CFG_Misc::GetSwitchDomain() const
{
    return mySwitchDomain;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetShelfType(CT_ShelfType theShelfType)
{
    myShelfType = theShelfType;
}

//-----------------------------------------------------------------------------
CT_ShelfType CFG_Misc::GetShelfType() const
{
    return myShelfType;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetProtLvl(CT_ProtLevel theProtLvl)
{
    myProtLvl = theProtLvl;
}

//-----------------------------------------------------------------------------
CT_ProtLevel CFG_Misc::GetProtLvl() const
{
    return myProtLvl;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetNumFabSlice(uint8 numFabSlice)
{
    myNumFabSlice = numFabSlice;
}

//-----------------------------------------------------------------------------
uint8 CFG_Misc::GetNumFabSlice() const
{
    return myNumFabSlice;
}

//-----------------------------------------------------------------------------
void CFG_Misc::SetDomainMbrShelfId(CT_ShelfId theMbrShelfId, uint8 theDomainArrayIndex)
{
    myDomainShelfMbrs[theDomainArrayIndex] = theMbrShelfId;
}

//-----------------------------------------------------------------------------
CT_ShelfId CFG_Misc::GetDomainMbrShelfId( uint8 theDomainArrayIndex )
{
    return myDomainShelfMbrs[theDomainArrayIndex];
}

//-----------------------------------------------------------------------------
void CFG_Misc::Reset(void)
{
    // Initialize all attributes to default values.
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        myLinkRate[i]            = CT_TEL_LinkRateNone;
        myRemoteLinkRate[i]      = CT_TEL_LinkRateNone;
        myLinkOperState[i]       = 0;
        myRemoteLinkOperState[i] = 0;
        myCardTypeList[i]        = CARD_TYPE_UNKNOWN;
        myRemoteCardTypeList[i]  = CARD_TYPE_UNKNOWN;
        myCardHwVersion[i]       = "";
        myRemoteCardHwVersion[i] = "";
    }
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        myDomainShelfMbrs[i] = UNKNOWN_SHELF;
    }
    mySwitchMode = CT_TEL_SwitchMode_None;
    myNbrSlots = CFG_MISC_MAX_SIZE;
    mySwitchDomain = CT_SWITCH_DOMAIN_UNKNOWN;
    mySwitchDomainMode = CT_SWITCHDOMAINMODE_UNKNOWN;
    myShelfType = UNKNOWN_SHELF;
    myLinkRateOverride = CT_TEL_LinkRateNone;
}

//-----------------------------------------------------------------------------
ostream& CFG_Misc::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint8 aSwitchDomainMode = (uint8)mySwitchDomainMode;

    theStream   << FC_InsertVar(mySwitchMode);
    theStream   << FC_InsertVar(myNbrSlots);
    theStream   << FC_InsertVar(mySwitchDomain);
    theStream   << FC_InsertVar(aSwitchDomainMode);
    theStream   << FC_InsertVar(myShelfType);
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myLinkRate[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myRemoteLinkRate[i]);
    }
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream   << FC_InsertVar(myDomainShelfMbrs[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myLinkOperState[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myRemoteLinkOperState[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myCardTypeList[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myRemoteCardTypeList[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myCardHwVersion[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << FC_InsertVar(myRemoteCardHwVersion[i]);
    }
    
    theStream   << FC_InsertVar(myLinkRateOverride);
    theStream   << FC_InsertVar(myProtLvl);
    theStream   << FC_InsertVar(myNumFabSlice);

    return theStream;
}

//-----------------------------------------------------------------------------
istream& CFG_Misc::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(mySwitchMode);
    theStream   >> FC_ExtractVar(myNbrSlots);
    theStream   >> FC_ExtractVar(mySwitchDomain);

    uint8 aSwitchDomainMode;
    theStream   >> FC_ExtractVar(aSwitchDomainMode);
    mySwitchDomainMode = (CT_SwitchDomainMode)aSwitchDomainMode;

    theStream   >> FC_ExtractVar(myShelfType);
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myLinkRate[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myRemoteLinkRate[i]);
    }
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream   >> FC_ExtractVar(myDomainShelfMbrs[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myLinkOperState[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myRemoteLinkOperState[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myCardTypeList[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myRemoteCardTypeList[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myCardHwVersion[i]);
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> FC_ExtractVar(myRemoteCardHwVersion[i]);
    }

    theStream   >> FC_ExtractVar(myLinkRateOverride);
    theStream   >> FC_ExtractVar(myProtLvl);
    theStream   >> FC_ExtractVar(myNumFabSlice);

    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& CFG_Misc::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    uint8 aSwitchDomainMode = (uint8)mySwitchDomainMode;

    theStream   << mySwitchMode;
    theStream   << myNbrSlots;
    theStream   << mySwitchDomain;
    theStream   << aSwitchDomainMode;
    theStream   << myShelfType;

    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myLinkRate[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myRemoteLinkRate[i];
    }
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream   << myDomainShelfMbrs[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myLinkOperState[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myRemoteLinkOperState[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myCardTypeList[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myRemoteCardTypeList[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myCardHwVersion[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   << myRemoteCardHwVersion[i];
    }
    
    theStream   << myLinkRateOverride;
    theStream   << myProtLvl;
    theStream   << myNumFabSlice;

    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& CFG_Misc::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint8 aSwitchDomainMode = (uint8)CT_SWITCHDOMAINMODE_UNKNOWN;

    theStream   >> mySwitchMode;
    theStream   >> myNbrSlots;
    theStream   >> mySwitchDomain;
    theStream   >> aSwitchDomainMode;
    theStream   >> myShelfType;
    
    mySwitchDomainMode = (CT_SwitchDomainMode)aSwitchDomainMode;

    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myLinkRate[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myRemoteLinkRate[i];
    }
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream   >> myDomainShelfMbrs[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myLinkOperState[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myRemoteLinkOperState[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myCardTypeList[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myRemoteCardTypeList[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myCardHwVersion[i];
    }
    for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
    {
        theStream   >> myRemoteCardHwVersion[i];
    }
    
    theStream   >> myLinkRateOverride;
    theStream   >> myProtLvl;
    theStream   >> myNumFabSlice;

    return theStream;
}

//-----------------------------------------------------------------------------
FC_CmdProcessor::STATUS CFG_Misc::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
    {       
        // This code is only needed for SWIT/SIT as 3Gbs SSM will be deployed in the field. Only applies to SPFAB (USS Shelf).
        //Copy arguments
        strcpy(aParam, argv[0]);
        if (!strncmp(aParam,"link3gbs",8))
        {
            myLinkRateOverride = CT_TEL_LinkRate3Gbs;
            for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
            {   
                if ((myLinkRate[i] == CT_TEL_LinkRate5Gbs) || (myLinkRate[i] == CT_TEL_LinkRate6Gbs))
                    myLinkRate[i] = CT_TEL_LinkRate3Gbs;
            }
            for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
            {
                if ((myRemoteLinkRate[i] == CT_TEL_LinkRate5Gbs) || (myRemoteLinkRate[i] == CT_TEL_LinkRate6Gbs))
                    myRemoteLinkRate[i] = CT_TEL_LinkRate3Gbs;
            }
            return FC_CmdProcessor::E_SUCCESS;
        }
        else if (!strncmp(aParam,"link5gbs",8))
        {   
            myLinkRateOverride = CT_TEL_LinkRate5Gbs;
            for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
            {   
                if ((myLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myLinkRate[i] == CT_TEL_LinkRate6Gbs))
                    myLinkRate[i] = CT_TEL_LinkRate5Gbs;
            }
            for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
            {
                if ((myRemoteLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myRemoteLinkRate[i] == CT_TEL_LinkRate6Gbs))
                    myRemoteLinkRate[i] = CT_TEL_LinkRate5Gbs;
            }
            return FC_CmdProcessor::E_SUCCESS;
        }
        else if (!strncmp(aParam,"link6gbs",8))
        {   
            myLinkRateOverride = CT_TEL_LinkRate6Gbs;
            for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
            {   
                if ((myLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myLinkRate[i] == CT_TEL_LinkRate5Gbs))
                    myLinkRate[i] = CT_TEL_LinkRate6Gbs;
            }
            for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
            {
                if ((myRemoteLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myRemoteLinkRate[i] == CT_TEL_LinkRate5Gbs))
                    myRemoteLinkRate[i] = CT_TEL_LinkRate6Gbs;
            }
            return FC_CmdProcessor::E_SUCCESS;
        }
        else if (!strncmp(aParam,"linknone",8))
        {
            myLinkRateOverride = CT_TEL_LinkRateNone;

            if ( myShelfType == PORT_SHELF_HCSS_TYPE)
            {
                for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
                {   
                    if ((myLinkRate[i] == CT_TEL_LinkRate5Gbs) || (myLinkRate[i] == CT_TEL_LinkRate6Gbs))
                        myLinkRate[i] = CT_TEL_LinkRate3Gbs;
                }
                for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
                {
                    if ((myRemoteLinkRate[i] == CT_TEL_LinkRate5Gbs) || (myRemoteLinkRate[i] == CT_TEL_LinkRate6Gbs))
                        myRemoteLinkRate[i] = CT_TEL_LinkRate3Gbs;
                }
            }
            else if ( myShelfType == PORT_SHELF_FP3_TYPE)
            {
                for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
                {   
                    if ((myLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myLinkRate[i] == CT_TEL_LinkRate6Gbs))
                        myLinkRate[i] = CT_TEL_LinkRate5Gbs;
                }
                for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
                {
                    if ((myRemoteLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myRemoteLinkRate[i] == CT_TEL_LinkRate6Gbs))
                        myRemoteLinkRate[i] = CT_TEL_LinkRate5Gbs;
                }
            }
            else if ( myShelfType == PORT_SHELF_NANO_TYPE)
            {
                for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
                {   
                    if ((myLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myLinkRate[i] == CT_TEL_LinkRate5Gbs))
                        myLinkRate[i] = CT_TEL_LinkRate6Gbs;
                }
                for (int i = 0; i < CFG_MISC_MAX_SIZE; i++)
                {
                    if ((myRemoteLinkRate[i] == CT_TEL_LinkRate3Gbs) || (myRemoteLinkRate[i] == CT_TEL_LinkRate5Gbs))
                        myRemoteLinkRate[i] = CT_TEL_LinkRate6Gbs;
                }
            }
            return FC_CmdProcessor::E_SUCCESS;
        }
        else 
            goto MSERROR;
    }

    //Copy arguments
    strcpy(aParam, argv[0]);


    if (!strncmp(aParam,"mode",4))
    {
        CT_TEL_SwitchMode aMode;
        if (argv[1][0]=='m')
        {
            aMode = CT_TEL_SwitchMode_Mesh;
            SetSwitchMode(aMode);
        }
        else if (argv[1][0]=='c')
        {
            aMode = CT_TEL_SwitchMode_Cntr_Switch;
            SetSwitchMode(aMode);
        }
        else if (argv[1][0]=='r')
        {
            aMode = CT_TEL_SwitchMode_Repeater;
            SetSwitchMode(aMode);
        }
        else if (argv[1][0]=='e')
        {
            aMode = CT_TEL_SwitchMode_End_Switch;
            SetSwitchMode(aMode);
        }
        else
        {
            aMode = CT_TEL_SwitchMode_None;
            SetSwitchMode(aMode);
        }
    }
    else if (!strncmp(aParam,"swdommode", 9))
    {
        CT_SwitchDomainMode aSwDomMode;
        if (argv[1][0]=='a')
        {
            aSwDomMode = CT_SWITCHDOMAINMODE_ALL;
            SetSwitchDomainMode(aSwDomMode);
        }
        else if (argv[1][0]=='1')
        {
            aSwDomMode = CT_SWITCHDOMAINMODE_1SS6UFAB;
            SetSwitchDomainMode(aSwDomMode);
        }
        else if (argv[1][0]=='s')
        {
            aSwDomMode = CT_SWITCHDOMAINMODE_SINGLESHELF;
            SetSwitchDomainMode(aSwDomMode);
        }
        else
        {
            aSwDomMode = CT_SWITCHDOMAINMODE_UNKNOWN;
            SetSwitchDomainMode(aSwDomMode);
        }

    }
    else if (!strncmp(aParam,"nbr",3))
    {
        SetNbrOfSlots(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"lnkrate",7))
    {
        SetLinkRate(uint8(atoi(argv[1])),CFG_STRING_TO_LNKRATE(argv[2]));
    }
    else if (!strncmp(aParam,"rmlnkrate",9))
    {
        SetRemoteLinkRate(uint8(atoi(argv[1])),CFG_STRING_TO_LNKRATE(argv[2]));
    }
    else if (!strncmp(aParam,"lnkis",5))
    {
        SetLinkOperState(uint8(atoi(argv[1])), true);
    }
    else if (!strncmp(aParam,"lnkoos",6))
    {
        SetLinkOperState(uint8(atoi(argv[1])), false);
    }
        else if (!strncmp(aParam,"cardis",6))
    {
        SetCardOperState(uint8(atoi(argv[1])), true);
    }
    else if (!strncmp(aParam,"cardoos",7))
    {
        SetCardOperState(uint8(atoi(argv[1])), false);
    }
    else if (!strncmp(aParam,"cardtype",8))
    {
        SetCardType(uint8(atoi(argv[1])), uint8(atoi(argv[2])));
    }
    else if (!strncmp(aParam,"rmlnkis",7))
    {
        SetRemoteLinkOperState(uint8(atoi(argv[1])), true);
    }
    else if (!strncmp(aParam,"rmlnkoos",8))
    {
        SetRemoteLinkOperState(uint8(atoi(argv[1])), false);
    }
    else if (!strncmp(aParam,"rmcardis",8))
    {
        SetRemoteCardOperState(uint8(atoi(argv[1])), true);
    }
    else if (!strncmp(aParam,"rmcardoos",9))
    {
        SetRemoteCardOperState(uint8(atoi(argv[1])), false);
    }
    else if (!strncmp(aParam,"rmcardtype",10))
    {
        SetRemoteCardType(uint8(atoi(argv[1])), uint8(atoi(argv[2])));
    }
    else if (!strncmp(aParam,"domain",6))
    {
        SetSwitchDomain(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"protlvl",7))
    {
        SetProtLvl(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"numfabslice",11))
    {
        SetNumFabSlice(atoi(argv[1]));
    }
    else if ((!strncmp(aParam,"dmmbr",5)) && (argc == 3))
    {
        SetDomainMbrShelfId(atoi(argv[1]),atoi(argv[2]));
    }
    else if (!strncmp(aParam,"shelf",5))
    {
        CT_ShelfType aMode;
        char aShelf[32];
        strcpy(aShelf, argv[1]);
        if (!strncmp(aShelf,"hcss",4))
        {
            aMode = PORT_SHELF_HCSS_TYPE;
        }
        else if (!strncmp(aShelf,"psnano",6))
        {
            aMode = PORT_SHELF_NANO_TYPE;
        }
        else if (!strncmp(aShelf,"msnano",6))
        {
            aMode = OPTICAL_SHELF_NANO_TYPE;
        }
        else if (!strncmp(aShelf,"uss",3))
        {
            aMode = PORT_SHELF_FP3_TYPE;
        }
        else if (!strncmp(aShelf,"os",2))
        {
            aMode = OPTICAL_SHELF_FP3_TYPE;
        }
        else
        {
            aMode = UNKNOWN_SHELF;
        }
        SetShelfType(aMode);
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "MISC <mode>         <m-esh|d-isable|r-peater|c-ntrswitch|e-ndswitch> " << endl;
        fc_cout << "MISC <swdommode>    <u-nknown|a-ll|1-ss6ufab|s-ingleshelf> " << endl;
        fc_cout << "MISC <nbr>          <1 to 19> " << endl;
        fc_cout << "MISC <lnkrate>      <SlotId 0-18> <Rate 6gbs|5gbs|3gbs|sonet|pkt|none>" << endl;
        fc_cout << "MISC <rmlnkrate>    <SlotId 0-18> <Rate 6gbs|5gbs|3gbs|sonet|pkt|none>" << endl;;
        fc_cout << "MISC <lnkis>        <SlotId 0-18> " << endl;
        fc_cout << "MISC <lnkoos>       <SlotId 0-18> " << endl;
        fc_cout << "MISC <cardis>       <SlotId 0-18> " << endl;
        fc_cout << "MISC <cardoos>      <SlotId 0-18> " << endl;
        fc_cout << "MISC <rmlnkis>      <SlotId 0-18> " << endl;
        fc_cout << "MISC <rmlnkoos>     <SlotId 0-18> " << endl;
        fc_cout << "MISC <rmcardis>     <SlotId 0-18> " << endl;
        fc_cout << "MISC <rmcardoos>    <SlotId 0-18> " << endl;
        fc_cout << "MISC <cardtype>     <SlotId 0-18> <Card type #>" << endl;
        fc_cout << "MISC <rmcardtype>   <SlotId 0-18> <Card type #>" << endl;
        fc_cout << "MISC <domain>       <uint8>" << endl;
        fc_cout << "MISC <protlvl>      <uint8>" << endl;
        fc_cout << "MISC <numfabslice>  <uint8>" << endl;
        fc_cout << "MISC <shelf>        <hcss uss msnano psnano os unknown> " << endl;
        fc_cout << "MISC <dmmbr>        <domainshelfid idx 0-1> " << endl;
        fc_cout << "MISC <link3gbs>     " << endl;
        fc_cout << "MISC <link5gbs>     " << endl;
        fc_cout << "MISC <link6gbs>     " << endl;
        fc_cout << "MISC <linknone>     " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

//-----------------------------------------------------------------------------
void CFG_Misc::Display( FC_Stream& theStream )
{
    if ( mySwitchMode == CT_TEL_SwitchMode_Mesh)
        theStream   << "MISC - Mode             [mode]   = MESH " << endl;
    else if ( mySwitchMode == CT_TEL_SwitchMode_Cntr_Switch)
        theStream   << "MISC - Mode             [mode]   = UFAB CNTR SWITCHED " << endl;
    else if ( mySwitchMode == CT_TEL_SwitchMode_End_Switch)
        theStream   << "MISC - Mode             [mode]   = UFAB END SWITCHED " << endl;
    else if ( mySwitchMode == CT_TEL_SwitchMode_Repeater)
        theStream   << "MISC - Mode             [mode]   = UFAB REPEATER " << endl;
    else
        theStream   << "MISC - Mode             [mode]   = None " << endl;

    if ( mySwitchDomainMode == CT_SWITCHDOMAINMODE_SINGLESHELF)
        theStream   << "MISC - SwDomMode        [swdommode]   = SINGLESHELF " << endl;
    else if ( mySwitchDomainMode == CT_SWITCHDOMAINMODE_1SS6UFAB)
        theStream   << "MISC - SwDomMode        [swdommode]   = 1SS6UFAB " << endl;
    else if ( mySwitchDomainMode == CT_SWITCHDOMAINMODE_ALL)
        theStream   << "MISC - SwDomMode        [swdommode]   = ALL " << endl;
    else
        theStream   << "MISC - SwDomMode        [swdommode]   = UNKNOWN " << endl;

    if ( myShelfType == PORT_SHELF_HCSS_TYPE)
        theStream   << "MISC - Shelf Type       [shelf]  = HCSS " << endl;
    else if ( myShelfType == PORT_SHELF_FP3_TYPE)
        theStream   << "MISC - Shelf Type       [shelf]  = USS " << endl;
    else if ( myShelfType == PORT_SHELF_NANO_TYPE)
        theStream   << "MISC - Shelf Type       [shelf]  = PS NANO " << endl;
    else if ( myShelfType == OPTICAL_SHELF_NANO_TYPE)
        theStream   << "MISC - Shelf Type       [shelf]  = MS NANO " << endl;
    else if ( myShelfType == OPTICAL_SHELF_FP3_TYPE)
        theStream   << "MISC - Shelf Type       [shelf]  = OS " << endl;
    else
        theStream   << "MISC - Shelf Type       [shelf]  = UNKNOWN " << endl;

    theStream   << "MISC - Switch Domain    [domain] = " << uint32(mySwitchDomain) << endl;

    theStream   << "MISC - Domain Shelf Mbrs[dmmbr]  =";
    for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
    {
        theStream   << " " << uint32(myDomainShelfMbrs[i]);

    }
    
    if ( myLinkRateOverride == CT_TEL_LinkRate3Gbs)
        theStream  << endl << "MISC - LinkRate Overide [link3gbs]   = 3GBS " << endl;
    else if ( myLinkRateOverride == CT_TEL_LinkRate5Gbs)
        theStream  << endl << "MISC - LinkRate Overide [link5gbs]   = 5GBS " << endl;
    else if ( myLinkRateOverride == CT_TEL_LinkRate6Gbs)
        theStream  << endl << "MISC - LinkRate Overide [link6gbs]   = 6GBS " << endl;
    else
        theStream  << endl << "MISC - LinKRate Overide [linknone]   = DISABLED " << endl;

    theStream   << "MISC - Number of Slots  [nbr]    = " << uint32(myNbrSlots) << endl << endl;

    theStream   << "MISC - LINK RATE =                ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_LINK_RATE(myLinkRate[i]);
        if ((i == 4) || (i == 9) || (i == 14))
            theStream << endl << "                                  ";
    }
    theStream  << endl << endl << "MISC - REMOTE LINK RATE =         ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_LINK_RATE(myRemoteLinkRate[i]);
        if ((i == 4) || (i == 9) || (i == 14))
            theStream << endl << "                                  ";
    }

    theStream   << endl << endl << "MISC - LINK OPER STATE =          ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_BOOL(GetLinkOperState(i));
        if (i == 9)
            theStream << endl << "                                  ";
    }
    theStream  << endl << endl << "MISC - REMOTE LINK OPERSTATE =    ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_BOOL(GetRemoteLinkOperState(i));
        if (i == 9)
            theStream << endl << "                                  ";
    }

    theStream   << endl << endl << "MISC - CARD LINK OPER STATE =          ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_BOOL(GetCardOperState(i));
        if (i == 9)
            theStream << endl << "                                  ";
    }
    theStream  << endl << endl << "MISC - REMOTE CARD LINK OPERSTATE =    ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << DISPLAY_BOOL(GetRemoteCardOperState(i));
        if (i == 9)
            theStream << endl << "                                  ";
    }
    theStream  << endl << endl << "MISC - CARD TYPES =               ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << ((uint32)GetCardType(i));
        if (i == 9)
            theStream << endl << "                                  ";
    }
    theStream  << endl << endl << "MISC - REMOTE CARD TYPES =        ";
    for (int i = 0; i < myNbrSlots; i++)
    {
        theStream   << " " << ((uint32)GetRemoteCardType(i));
        if (i == 9)
            theStream << endl << "                                  ";
    }

    theStream   << endl;
}

