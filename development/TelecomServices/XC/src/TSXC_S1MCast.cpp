/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_S1MCast       Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/
#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_S1MCast.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_S1MCast::TSXC_S1MCast()
{
    myMCastId = XC_MCASTID_UNKNOWN;
    myMCastImuxLMap = 0;
    myMCastImuxPMap = 0;
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_S1MCast::~TSXC_S1MCast()
{
}

//--------------------------------------------------------------------------------------------------
// Serialization Methods
//--------------------------------------------------------------------------------------------------
ostream& TSXC_S1MCast::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myMCastId);
    theStream<<FC_InsertVar(myMCastImuxLMap);
    theStream<<FC_InsertVar(myMCastImuxPMap);
    return theStream;
}

istream& TSXC_S1MCast::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myMCastId);
    theStream>>FC_ExtractVar(myMCastImuxLMap);
    theStream>>FC_ExtractVar(myMCastImuxPMap);
    return theStream;
}

FC_Stream& TSXC_S1MCast::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myMCastId;
    theStream<<myMCastImuxLMap;
    theStream<<myMCastImuxPMap;
    return theStream;
}

FC_Stream& TSXC_S1MCast::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myMCastId;
    theStream>>myMCastImuxLMap;
    theStream>>myMCastImuxPMap;
    return theStream;
}

//--------------------------------------------------------------------------------------------------
void TSXC_S1MCast::PrintMulticast(int theChan)
{
    uint8 slotIndex;
    FC_FmtFlags previousFlags;
    previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::left);

    fc_cout.Width(8);
    fc_cout << (theChan+1);
    fc_cout.Width(20);
    fc_cout << static_cast<int>(myMCastId);
    
        for (slotIndex = 0; slotIndex < (NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF-1); slotIndex++)
        {
            if ( IsImuxSet(CT_XC_IMUXL, slotIndex, 0, CT_XC_BR_MASK_NONE) )
            {
                fc_cout << "L";
                fc_cout.Width(1);
                fc_cout << static_cast<int>(slotIndex+1);
                fc_cout << " ";
            }
        }
        for (slotIndex = 0; slotIndex < (NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF-1); slotIndex++)
        {
            if ( IsImuxSet(CT_XC_IMUXP, slotIndex, 0, CT_XC_BR_MASK_NONE) )
            {
                fc_cout << "P";
                fc_cout.Width(1);
                fc_cout << static_cast<int>(slotIndex+1);
                fc_cout << " ";
            }
        }

    fc_cout << endl;
    fc_cout.Width(0);
    fc_cout.Flags(previousFlags);
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S1MCast::operator==(const TSXC_S1MCast& theMCast) const
{
    bool retVal = false;

    if ( (myMCastId == theMCast.myMCastId) &&
         (myMCastImuxLMap == theMCast.myMCastImuxLMap) &&
         (myMCastImuxPMap == theMCast.myMCastImuxPMap) )
    {
        retVal = true;
    }

    return retVal;
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S1MCast::operator!=(const TSXC_S1MCast& theMCast) const
{
    return (!(*this == theMCast));
}

//--------------------------------------------------------------------------------------------------
// Validate Methods
//--------------------------------------------------------------------------------------------------
bool TSXC_S1MCast::IsMcastSet() const
{
    bool retVal;

    retVal = false;
    if (myMCastId != XC_MCASTID_UNKNOWN)
    {
        retVal = true;
    }

    return retVal;
}

bool TSXC_S1MCast::IsImuxSet() const
{
    if ((myMCastImuxLMap > 0 ) || (myMCastImuxPMap > 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------------------------------
bool TSXC_S1MCast::IsImuxSet(uint8 theImuxType, uint8 theSlot, uint32 theMask,
                             uint8 theMaskAction) const
{
    uint8 aMask = 0x1;

    uint32 aImuxMapBefore;
    uint32 aImuxMapAfter;

    // theSlot is 0 based
    if (theImuxType == CT_XC_IMUXL)
    {
        aImuxMapAfter = aImuxMapBefore = myMCastImuxLMap;
    }
    else if (theImuxType == CT_XC_IMUXP)
    {
        aImuxMapAfter = aImuxMapBefore = myMCastImuxPMap;
    }
    else
    {
        FC_REPORT_ERROR(FC_NotSupportedError, "TSXC_S1MCast: Invalid Imux Type!");
        return false;
    }

    if (theMaskAction == CT_XC_BR_MASK_AND)
    {
        aImuxMapAfter = (aImuxMapBefore & theMask);
    }
    else if (theMaskAction == CT_XC_BR_MASK_OR)
    {
        aImuxMapAfter = (aImuxMapBefore | theMask);
    }

    return  (false != ((aImuxMapAfter & (aMask << theSlot)) >> theSlot));
}

//--------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------
void TSXC_S1MCast::InitMCast()
{
    myMCastId = XC_MCASTID_UNKNOWN;
    myMCastImuxLMap = 0;
    myMCastImuxPMap = 0;
}

void TSXC_S1MCast::SetMCastId( uint16 theMCastId )
{
    myMCastId = theMCastId;
}


void TSXC_S1MCast::SetMCastImuxLMap( uint16 theMCImuxLMap )
{
    myMCastImuxLMap = theMCImuxLMap; 
}

void TSXC_S1MCast::SetMCastImuxPMap( uint16 theMCImuxPMap )
{
    myMCastImuxPMap = theMCImuxPMap; 
}

//--------------------------------------------------------------------------------------------------
// Get Methods
//--------------------------------------------------------------------------------------------------
uint16 TSXC_S1MCast::GetMCastId()
{
    return myMCastId;
}

uint16 TSXC_S1MCast::GetMCastImuxLMap()
{
    return myMCastImuxLMap;
}

uint16 TSXC_S1MCast::GetMCastImuxPMap()
{
    return myMCastImuxPMap;
}
//--------------------------------------------------------------------------------------------------
