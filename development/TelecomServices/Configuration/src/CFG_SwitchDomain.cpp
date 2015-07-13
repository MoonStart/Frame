//Copyright(c) Tellabs Transport Group. All rights reserved

#include <string.h>
#include "../CFG_SwitchDomain.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_SwitchDomainMap.h>
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

//These may be temporary; final resolve of SwitchDomainMode may go a different route
#include <T6100/T6100_ShelfIf.h>
#include <T6100/T6100_MainAppIf.h>
#include <T6100/T6100_CssCfgIf.h>
#include <T6100/T6100_CssIf.h>

//-----------------------------------------------------------------------------
CFG_SwitchDomain::CFG_SwitchDomain(uint32 theIndex):
    CFG_Object(theIndex)
{
    //Set all values to default
    Reset();
}
//-----------------------------------------------------------------------------
CFG_SwitchDomain::~CFG_SwitchDomain(void)
{
}
//-----------------------------------------------------------------------------
void CFG_SwitchDomain::Reset(void)
{   
    myShelfId = UNKNOWN_SHELF_ID;
    myShelfType = UNKNOWN_SHELF;
    myFirstUfab = UNKNOWN_SLOT_ID;
    myNumUfabs = UNKNOWN_SLOT_ID;
    myNumCxpsPerUfab = UNKNOWN_SLOT_ID;
    mySwitchDomainMode = CT_SWITCHDOMAINMODE_UNKNOWN;

    for(CT_SlotId aSlotId = 0; aSlotId < NUMBER_OF_UFAB_IN_SWITCH_SHELF; aSlotId++)
    {
        myCardOperState[aSlotId] = false;
        mySwitchMode[aSlotId] = CT_TEL_SwitchMode_None;

        for(CT_SlotId aSubSlotId = 0; aSubSlotId < MAX_NUM_CXP_ON_UFABC; aSubSlotId++)
        {
            myLinkOperState[aSlotId][aSubSlotId] = false;
            myRemoteHwRev[aSlotId][aSubSlotId][0] = '\0';
            myCableLength[aSlotId][aSubSlotId] = CT_CABLELENGTH_UNKNOWN;
        }
    }

    myCxpMap.clear();
}

//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetSwitchDomainMode(CT_SwitchDomainMode theSwitchDomainMode)
{
    mySwitchDomainMode = theSwitchDomainMode;
}
//-------------------------------------------------------------------------------------
CT_SwitchDomainMode CFG_SwitchDomain::GetSwitchDomainMode()
{
    return(mySwitchDomainMode);
}
//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetCardOperState(CT_SlotId theSlotId, bool theOperState)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if(aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF)
    {
        myCardOperState[aUfabSlotIdx] = theOperState;
    }
}
//-------------------------------------------------------------------------------------
bool CFG_SwitchDomain::GetCardOperState(CT_SlotId theSlotId)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if(aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF)
    {
        return myCardOperState[aUfabSlotIdx];
    }
    return(false);
}
//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetSwitchMode(CT_SlotId theSlotId, CT_TEL_SwitchMode theSwitchMode)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if(aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF)
    {
        mySwitchMode[aUfabSlotIdx] = theSwitchMode;
    }
}
//-------------------------------------------------------------------------------------
CT_TEL_SwitchMode CFG_SwitchDomain::GetSwitchMode(CT_SlotId theSlotId)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if(aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF)
    {
        return mySwitchMode[aUfabSlotIdx];
    }

    return(CT_TEL_SwitchMode_None);
}
//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetLinkOperState(CT_SlotId theSlotId, CT_SlotId theSubSlotId,  bool linkState)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        myLinkOperState[aUfabSlotIdx][theSubSlotId-1] = linkState;
    }
}
//-------------------------------------------------------------------------------------
bool CFG_SwitchDomain::GetLinkOperState(CT_SlotId theSlotId, CT_SlotId theSubSlotId)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        return myLinkOperState[aUfabSlotIdx][theSubSlotId-1];
    }
    
    return (false);
}

//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetRemoteHwRev(CT_SlotId theSlotId, CT_SlotId theSubSlotId, string& theRevLevel)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        myRemoteHwRev[aUfabSlotIdx][theSubSlotId - 1] = theRevLevel;
    }
}
//-------------------------------------------------------------------------------------
string CFG_SwitchDomain::GetRemoteHwRev(CT_SlotId theSlotId, CT_SlotId theSubSlotId) const
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        return myRemoteHwRev[aUfabSlotIdx][theSubSlotId - 1];
    }

    return NULL;
}

//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetLinkMap(CT_SlotId theSlotId, CT_SlotId theSubSlotId, CT_TL1_SlotAddr theDstCxp)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        myCxpMap[CT_TL1_SlotAddr(myShelfId, theSlotId, theSubSlotId)] = CT_TL1_SlotAddr(theDstCxp);
    }
}
//-------------------------------------------------------------------------------------
const CT_TL1_SlotAddr& CFG_SwitchDomain::GetLinkMap(CT_SlotId theSlotId, CT_SlotId theSubSlotId)
{
    if(myCxpMap.count(CT_TL1_SlotAddr(myShelfId, theSlotId, theSubSlotId)))
    {
        return myCxpMap[CT_TL1_SlotAddr(myShelfId, theSlotId, theSubSlotId)];
    }

    return UNKNOWN_SLOT_ADDR;
}
//-------------------------------------------------------------------------------------
void CFG_SwitchDomain::SetCableLength(CT_SlotId theSlotId, CT_SlotId theSubSlotId, CT_CableLength theCableLength)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        myCableLength[aUfabSlotIdx][theSubSlotId - 1] = theCableLength;
    }
}
//-------------------------------------------------------------------------------------
CT_CableLength CFG_SwitchDomain::GetCableLength(CT_SlotId theSlotId, CT_SlotId theSubSlotId)
{
    uint aUfabSlotIdx = SlotToIndex(theSlotId);
    if((theSubSlotId >= 1 && theSubSlotId <= MAX_NUM_CXP_ON_UFABC) &&
       (aUfabSlotIdx < NUMBER_OF_UFAB_IN_SWITCH_SHELF))
    {
        return myCableLength[aUfabSlotIdx][theSubSlotId - 1];
    }

    return CT_CABLELENGTH_UNKNOWN;
}

//-------------------------------------------------------------------------------------
CT_SwitchDomainMode CFG_SwitchDomain::GetSystemSwitchDomainMode(){

    // Get the switch domain mode from the Config SwitchDomain region.
    T6100_ShelfIf* aCssShelfIfPtr = T6100_MainAppIf::Instance().GetShelfPtr(FIRST_SWITCH_SHELF);
    if ( aCssShelfIfPtr)
    {    
        CFG_SwitchDomainCfgRegion* aCfgSwDomainRegion = 
            static_cast<CFG_SwitchDomainCfgRegion*> (aCssShelfIfPtr->GetSwitchDomainIf().GetCfgShelfApp().GetCfgRegion());

        if(aCfgSwDomainRegion)
        {
            CFG_SwitchDomain& aSwDomainObj = static_cast<CFG_SwitchDomain&> ((*aCfgSwDomainRegion)[0]);
            return(aSwDomainObj.GetSwitchDomainMode());
        }
    }
    //If there is no CSS structure being formed, we can assume that we are an 'ALL' Configuration
    return CT_SWITCHDOMAINMODE_ALL;
}

//-------------------------------------------------------------------------------------
bool CFG_SwitchDomain::SwitchDomainModeSupportsSS() {

    CT_SwitchDomainMode swDomMode = CFG_SwitchDomain::GetSystemSwitchDomainMode();

    switch(swDomMode)
    {
    case CT_SWITCHDOMAINMODE_1SS6UFAB:
    case CT_SWITCHDOMAINMODE_3CSS18UFAB:
    case CT_SWITCHDOMAINMODE_UNKNOWN:
        return true;
    case CT_SWITCHDOMAINMODE_ALL:
    case CT_SWITCHDOMAINMODE_SINGLESHELF:
    default:
        return false;
    }

    return false;
}


//--------------------------------------------------------------------------
uint CFG_SwitchDomain::SlotToIndex(CT_SlotId theUfabSlot) const
{
    if(myShelfType == PORT_SHELF_HCSS_TYPE) 
    {
        if((theUfabSlot >= FIRST_UFAB_SLOT) &&
           (theUfabSlot <= LAST_UFAB_SLOT))
        {
            return (theUfabSlot - FIRST_UFAB_SLOT);
        }
    }
    else if(myShelfType == OTN_SHELF_CSS_TYPE)
    {
        if((theUfabSlot >= UFAB_C_FIRST) &&
           (theUfabSlot <= UFAB_C_LAST))
        {
            //Temporary resolve to reduce the number of structures - this will need to 
            //be modified in the future to handle right hand UFAB-Cs
            return ((theUfabSlot/2) - 1);
        }
    }
    else if(myShelfType == UNKNOWN_SHELF)
    {
        //Return out 0 - the shelf hasn't been provisioned yet, default values shall suffice
        return 0;
    }

    //FC Error out here - this should only be used on functioning 
    //UFAB slots.
    FC_THROW_ERROR(FC_ArgumentOutOfRangeError, "UFAB SlotID out of range");

    return NUMBER_OF_UFAB_IN_SWITCH_SHELF;
}

//--------------------------------------------------------------------------
CT_SlotId CFG_SwitchDomain::IndexToSlot(uint theIndex)
{
    if(myShelfType == PORT_SHELF_HCSS_TYPE) 
    {
        return(theIndex + FIRST_UFAB_SLOT);
    }
    else if(myShelfType == OTN_SHELF_CSS_TYPE)
    {
        return((theIndex+1)*2);
    }
    else if(myShelfType == UNKNOWN_SHELF)
    {
        //Irrelevant/shelf not configured yet.
        return(UNKNOWN_SLOT_ID);
    }

    //FC Error out here - this should only be used on functioning 
    //UFAB slots.
    FC_THROW_ERROR(FC_InvalidArgumentError, "CFG_SwitchDomain: Shelf type not supported for this command");

    return(UNKNOWN_SLOT_ID);
}


//-----------------------------------------------------------------------------
ostream& CFG_SwitchDomain::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint16 aShelfId = (uint16)myShelfId;
    theStream << FC_InsertVar(aShelfId);
    uint16 aShelfType = (uint16)myShelfType;
    theStream << FC_InsertVar(aShelfType);
    uint16 aFirstUfab = (uint16)myFirstUfab;
    theStream << FC_InsertVar(aFirstUfab);
    uint16 aNumUfabs = (uint16)myNumUfabs;
    theStream << FC_InsertVar(aNumUfabs);
    uint16 aNumCxpsPerUfab = (uint16)myNumCxpsPerUfab;
    theStream << FC_InsertVar(aNumCxpsPerUfab);
    uint8 aSwitchDomainMode = (uint8)mySwitchDomainMode;
    theStream << FC_InsertVar(aSwitchDomainMode);

    char cxpSrcStr[50] = "";
    char cxpDstStr[50] = "";

    //  We are only writing the existing number of UFABs and CXPs
    for(uint i = 0; i < aNumUfabs; i++)
    {
        char statusStr[50] = "";

        //Ufab oper state
        sprintf(statusStr, "myCardOperState[%d]", i+aFirstUfab);
        theStream << FC_InsertLabelAndVar(statusStr, myCardOperState[i]);

        //Switch Mode
        sprintf(statusStr, "mySwitchMode[%d]", i+aFirstUfab);
        theStream << FC_InsertLabelAndVar(statusStr, mySwitchMode[i]);
        
        for(uint j = 0; j < aNumCxpsPerUfab; j++)
        {
            //Write CXP Status
            sprintf(statusStr, "CXP-%d-%d-%d: myLinkOperState", myShelfId, IndexToSlot(i), j+1);
            theStream << FC_InsertLabelAndVar(statusStr, myLinkOperState[i][j]);
            
            //Write the remote HW Revision
            sprintf(statusStr, "CXP-%d-%d-%d: myRemoteHwRev", myShelfId, IndexToSlot(i), j+1);
            theStream << FC_InsertLabelAndVar( statusStr, myRemoteHwRev[i][j]);

            //Write Cable Length
            sprintf(statusStr, "CXP-%d-%d-%d: myCableLength", myShelfId, IndexToSlot(i), j+1);
            theStream << FC_InsertLabelAndVar(statusStr, myCableLength[i][j]);
        }
    }

    for(CT_SwitchDomainCxpMap::const_iterator it = myCxpMap.begin(); it != myCxpMap.end(); it++)
    {
        CT_TL1_SlotAddr aSrcPort = (*it).first;
        CT_TL1_SlotAddr aDstPort = (*it).second;

        //Write the CXP map
        sprintf(cxpSrcStr, "CXP-%d-%d-%d: ->", aSrcPort.GetShelfId(), aSrcPort.GetSlot(), aSrcPort.GetSubSlot());
        sprintf(cxpDstStr, "%d-%d-%d", aDstPort.GetShelfId(), 
                                       aDstPort.GetSlot(),
                                       aDstPort.GetSubSlot());
        theStream << FC_InsertLabelAndVar(cxpSrcStr, cxpDstStr);
    }

    return theStream;
}

//-----------------------------------------------------------------------------
istream& CFG_SwitchDomain::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint16 aShelfId;
    theStream >> FC_ExtractVar(aShelfId);
    myShelfId = (CT_ShelfId)aShelfId;

    uint16 aShelfType;
    theStream >> FC_ExtractVar(aShelfType);
    myShelfType = (CT_ShelfType)aShelfType;

    uint16 aFirstUfab;
    theStream >> FC_ExtractVar(aFirstUfab);
    myFirstUfab = (CT_SlotId)aFirstUfab;

    uint16 aNumUfabs;
    theStream >> FC_ExtractVar(aNumUfabs);
    myNumUfabs = (CT_SlotId)aNumUfabs;

    uint16 aNumCxpsPerUfab;
    theStream >> FC_ExtractVar(aNumCxpsPerUfab);
    myNumCxpsPerUfab = (CT_SlotId)aNumCxpsPerUfab;

    uint8 aSwitchDomainMode;
    theStream >> FC_ExtractVar(aSwitchDomainMode);
    mySwitchDomainMode = (CT_SwitchDomainMode)aSwitchDomainMode;

    char cxpDstStr[50] = "";

    //  We are only reading the existing number of UFABs and CXPs
    for(uint i = 0; i < aNumUfabs; i++)
    {
        //Ufab oper state
        theStream >> FC_ExtractVar(myCardOperState[i]);

        //Switch Mode
        uint16 aSwitchMode;
        theStream >> FC_ExtractVar(aSwitchMode);
        mySwitchMode[i] = (CT_TEL_SwitchMode)aSwitchMode;

        for(uint j = 0; j < aNumCxpsPerUfab; j++)
        {

            theStream >> FC_ExtractVar(myLinkOperState[i][j]);

            theStream >> FC_ExtractVar(myRemoteHwRev[i][j]);

            uint16 aCableLength;
            theStream >> FC_ExtractVar(aCableLength);
            myCableLength[i][j] = (CT_CableLength)aCableLength;
            
        }
    }

    for(CT_SwitchDomainCxpMap::const_iterator it = myCxpMap.begin(); it != myCxpMap.end(); it++)
    {
        CT_TL1_SlotAddr aSrcPort = (*it).first;

        // Read out the CXP Map
        char dash;
        theStream >> FC_ExtractVar(cxpDstStr); 
        int aShelfId, aSlotId, aPortId;
        sscanf (cxpDstStr,"%d%c%d%c%d", &aShelfId, &dash,
                                        &aSlotId, &dash,
                                        &aPortId);
        myCxpMap[aSrcPort] = CT_TL1_SlotAddr(aShelfId, aSlotId, aPortId);
    }

    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& CFG_SwitchDomain::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    
    theStream << myShelfId;
    theStream << myShelfType;
    theStream << myFirstUfab;
    theStream << myNumUfabs;
    theStream << myNumCxpsPerUfab;
    theStream << (uint)mySwitchDomainMode;

    //  We are only writing the existing number of UFABs and CXPs
    for(uint i = 0; i < myNumUfabs; i++)
    {
        theStream << myCardOperState[i];
        theStream << mySwitchMode[i];

        for(uint j = 0; j < myNumCxpsPerUfab; j++)
        {

            theStream << myLinkOperState[i][j];
            theStream << myRemoteHwRev[i][j];
            theStream << myCableLength[i][j];
            
        }
    }

    //Write the map out
    theStream << myCxpMap.size();
    for(CT_SwitchDomainCxpMap::const_iterator it = myCxpMap.begin(); it != myCxpMap.end(); it++)
    {
        CT_TL1_SlotAddr aSrcPort = (*it).first;
        CT_TL1_SlotAddr aDstPort = (*it).second;
        theStream << aSrcPort.GetShelfId();
        theStream << aSrcPort.GetSlot();
        theStream << aSrcPort.GetSubSlot();
        theStream << aDstPort.GetShelfId();
        theStream << aDstPort.GetSlot();
        theStream << aDstPort.GetSubSlot();
    }

    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& CFG_SwitchDomain::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream >> myShelfId;
    theStream >> myShelfType;
    theStream >> myFirstUfab;
    theStream >> myNumUfabs;
    theStream >> myNumCxpsPerUfab;
    theStream >> (uint&)mySwitchDomainMode;

    //  We are only writing the existing number of UFABs and CXPs
    for(uint i = 0; i < myNumUfabs; i++)
    {
        theStream >> myCardOperState[i];
        theStream >> mySwitchMode[i];

        for(uint j = 0; j < myNumCxpsPerUfab; j++)
        {

            theStream >> myLinkOperState[i][j];
            theStream >> myRemoteHwRev[i][j];
            theStream >> myCableLength[i][j];
        }
    }

    //Read the map out
    int aSize = 0;
    CT_ShelfId aSrcShelf   = UNKNOWN_SHELF_ID;
    CT_SlotId  aSrcSlot    = UNKNOWN_SLOT_ID;
    CT_SlotId  aSrcSubSlot = UNKNOWN_SLOT_ID;
    CT_ShelfId aDstShelf   = UNKNOWN_SHELF_ID;
    CT_SlotId  aDstSlot    = UNKNOWN_SLOT_ID;
    CT_SlotId  aDstSubSlot = UNKNOWN_SLOT_ID;

    myCxpMap.clear();
    theStream >> aSize;
    for(int i = 0; i < aSize; i++)
    {
        theStream >> aSrcShelf;
        theStream >> aSrcSlot;
        theStream >> aSrcSubSlot;

        theStream >> aDstShelf;
        theStream >> aDstSlot;
        theStream >> aDstSubSlot;

        myCxpMap[CT_TL1_SlotAddr(aSrcShelf, aSrcSlot, aSrcSubSlot)] = CT_TL1_SlotAddr(aDstShelf, aDstSlot, aDstSubSlot); 
    }

    return theStream;
}

//-----------------------------------------------------------------------------
FC_CmdProcessor::STATUS CFG_SwitchDomain::Set(int argc, char **argv)
{
    char aParam[32];
    strcpy(aParam, argv[0]);

    //We need 2 arguments
    if (argc < 3)
    {       
        if(!strncmp(aParam,"swdmode", 7))
        {
            SetSwitchDomainMode(CT_SwitchDomainMode(atoi(argv[1])));
        }
        else if (!strncmp(aParam,"cardis", 6))
        {
            SetCardOperState(uint8(atoi(argv[1])), true);
        }
        else if (!strncmp(aParam,"cardoos", 6))
        {
            SetCardOperState(uint8(atoi(argv[1])), false);
        }
        else
        {
            goto MSERROR;
        }
    }
    else if (argc < 4)
    {
        if(!strncmp(aParam, "lnkis", 5))
        {
            SetLinkOperState(uint8(atoi(argv[1])), uint8(atoi(argv[2])), true);
        }
        else if(!strncmp(aParam, "lnkoos", 6))
        {
            SetLinkOperState(uint8(atoi(argv[1])), uint8(atoi(argv[2])), false);
        }
        else if (!strncmp(aParam,"swmode", 7))
        {
            SetSwitchMode(uint8(atoi(argv[1])), uint8(atoi(argv[2])));
        }
        else
        {
            goto MSERROR;
        }
    }
    else if (argc < 5)
    {
        if (!strncmp(aParam,"cbllen",7))
        {
            SetCableLength(uint8(atoi(argv[1])), uint8(atoi(argv[2])), uint8(atoi(argv[3])));
        }
        else if(!strncmp(aParam, "remhwrev", 9))
        {
            string hwRev = (const char*)(argv[3]);
            SetRemoteHwRev(uint8(atoi(argv[1])), uint8(atoi(argv[2])), hwRev);
        }
        else
        {
            goto MSERROR;
        }
    }
    else if(argc < 7)
    {
        if (!strncmp(aParam,"lnkmap",7))
        {
            CT_TL1_SlotAddr aSlotAddr(GET_INTERNAL_SHELF_ID(uint8(atoi(argv[3]))),
                                      uint8(atoi(argv[4])),
                                      uint8(atoi(argv[5])));
            SetLinkMap(uint8(atoi(argv[1])), uint8(atoi(argv[2])), aSlotAddr);
        }
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "SWDOM <swdmode>  <SwDomainMode: 0 (unknown), 1 (1SS6UFAB)> " <<endl;
        fc_cout << "SWDOM <lnkmap>   <SlotId 9-11;2-12> <CXP 1-8(16)> <ShelfId> <SlotId> <PortId>" << endl;
        fc_cout << "SWDOM <cbllen>   <SlotId 9-11;2-12> <CXP 1-8(16)> <CableLength:10|20|80>" << endl;
        fc_cout << "SWDOM <remhwrev> <SlotId 9-11;2-12> <CXP 1-8(16)> <Remote Hw Rev (4 char)>" << endl;
        fc_cout << "SWDOM <lnkis>    <SlotId 9-11;2-12> <CXP 1-8;1-16> " << endl;
        fc_cout << "SWDOM <lnkoos>   <SlotId 9-11;2-12> <CXP 1-8;1-16> " << endl;
        fc_cout << "SWDOM <cardis>   <SlotId 9-11;2-12> " << endl;
        fc_cout << "SWDOM <cardoos>  <SlotId 9-11;2-12> " << endl;
        fc_cout << "SWDOM <swmode>   <SlotId 9-11;2-12> <SwitchMode: 1 - Center; 2 - Repeater; 3 - End>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

//-----------------------------------------------------------------------------
void CFG_SwitchDomain::Display( FC_Stream& theStream )
{

    theStream   << "SWITCHDOMAIN - SWITCHDOMAIN MODE: " << mySwitchDomainMode << endl;

    theStream   << "SWITCHDOMAIN - CARD OPER STATE (Slot): " << endl;
    for(int i = 0; i < myNumUfabs; i++)
    {
        theStream   << "(" << uint32(IndexToSlot(i)) << ") = ";
        theStream   << DISPLAY_BOOL(GetCardOperState(IndexToSlot(i))) << endl;
    }

    theStream   << "SWITCHDOMAIN - SWITCHMODE (Slot): " << endl;
    for(int i = 0; i < myNumUfabs; i++)
    {
        theStream   << "(" << uint32(IndexToSlot(i)) << ") = ";
        theStream   << DISPLAY_SWITCH_MODE(GetSwitchMode(IndexToSlot(i))) << endl;
    }

    theStream   << "SWITCHDOMAIN - LINK OPER STATE UFABs (Slot) (SubSlot): " << endl;
    for(int i = 0; i < myNumUfabs; i++)
    {
        for(int j = 0; j < myNumCxpsPerUfab; j++)
        {
            theStream   << "(" << uint32(IndexToSlot(i)) << ") (" << j+1 << ") = ";
            theStream   << DISPLAY_BOOL(GetLinkOperState(IndexToSlot(i), j)) << endl;
        }
    }

    theStream << "SWITCHDOMAIN - REMOTE HW REV (Slot) (SubSlot): " << endl;;
    for(int i = 0; i < myNumUfabs; i++)
    {
        for(int j = 0; j < myNumCxpsPerUfab; j++)
        {
            theStream   << "(" << uint32(IndexToSlot(i)) << ") (" << j+1 << ") = ";
            theStream   << GetRemoteHwRev(IndexToSlot(i), j+1) << endl;
        }
    }

    theStream   << "SWITCHDOMAIN - LINK MAP: (Slot) (Port): <CXP>" << endl;
    for(int i = 0; i < myNumUfabs; i++)
    {
        for(int j = 0; j < myNumCxpsPerUfab; j++)
        {
            theStream   << "(" << uint32(IndexToSlot(i)) << ") (" << j+1 << ") = ";
            theStream   << uint32(GET_EXTERNAL_SHELF_ID(GetLinkMap(IndexToSlot(i), j+1).GetShelfId())) << "-";
            theStream   << uint32(GetLinkMap(IndexToSlot(i), j+1).GetSlot()) << "-";
            theStream   << uint32(GetLinkMap(IndexToSlot(i), j+1).GetSubSlot()) << endl;
        }
    }

    theStream   << "SWITCHDOMAIN - CableLength: (Slot) (Port): <Cable Length>" << endl;
    for(int i = 0; i < myNumUfabs; i++)
    {
        for(int j = 0; j < myNumCxpsPerUfab; j++)
        {
            theStream   << "(" << uint32(IndexToSlot(i)) << ") (" << j+1 << ") = ";
            theStream   << uint32(GetCableLength(IndexToSlot(i), j+1)) << endl;
        }
    }

    theStream   << endl;
}

