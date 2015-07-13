/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008  Teresa Chen
 DESCRIPTION:   TSXC_S2MCast       Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/
#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>

#include <XC/TSXC_S2MCast.h>
#include <XC/TSXC_CrossConnect.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_S2MCast::TSXC_S2MCast()
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        myDest[i].Init();
    }
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_S2MCast::~TSXC_S2MCast()
{
}

//--------------------------------------------------------------------------------------------------
// Validate Methods
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------
void TSXC_S2MCast::InitMCast()
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        myDest[i].Init();
    }
}

void TSXC_S2MCast::InitMCastPrev()
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        myDest[i].InitPrev();
    }
}

void TSXC_S2MCast::SetShelfSlots(const TSXC_DESTINATION theDest[])
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        myDest[i] = theDest[i];                
    }
}
    
//--------------------------------------------------------------------------------------------------
// Get Methods
//--------------------------------------------------------------------------------------------------

void TSXC_S2MCast::GetShelfSlots(TSXC_DESTINATION theDest[])
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        theDest[i] = myDest[i];
    }
}

bool TSXC_S2MCast::IsEmpty()
{
    bool retVal;
    int  i;

    for (i = 0, retVal = true; 
         (i < TSXC_MAX_SHELF_PER_MCAST) && (retVal == true); 
         i++)
    {
        retVal = myDest[i].IsEmpty();
    }
    
    return retVal;
}

//--------------------------------------------------------------------------------------------------
// Operators
//--------------------------------------------------------------------------------------------------

bool TSXC_S2MCast::operator==(const TSXC_S2MCast& theMCast) const
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        if ( (myDest[i].Shelf  != theMCast.myDest[i].Shelf ) ||
             (myDest[i].ImuxSlotMap != theMCast.myDest[i].ImuxSlotMap ))
        {
            return false;
        }
    }
    return true;
}

bool TSXC_S2MCast::operator!=(const TSXC_S2MCast& theMCast) const
{
    return (!(*this == theMCast));
}

void TSXC_S2MCast::operator=(const TSXC_S2MCast& theMCast)
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        myDest[i].Shelf  = theMCast.myDest[i].Shelf;
        myDest[i].ImuxSlotMap = theMCast.myDest[i].ImuxSlotMap;
    }
}

//--------------------------------------------------------------------------------------------------
// Serialization Methods
//--------------------------------------------------------------------------------------------------

ostream& TSXC_S2MCast::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myDest[0].Shelf);
    theStream<<FC_InsertVar(myDest[0].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[1].Shelf);
    theStream<<FC_InsertVar(myDest[1].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[2].Shelf);
    theStream<<FC_InsertVar(myDest[2].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[3].Shelf);
    theStream<<FC_InsertVar(myDest[3].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[4].Shelf);
    theStream<<FC_InsertVar(myDest[4].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[5].Shelf);
    theStream<<FC_InsertVar(myDest[5].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[6].Shelf);
    theStream<<FC_InsertVar(myDest[6].ImuxSlotMap);
    theStream<<FC_InsertVar(myDest[7].Shelf);
    theStream<<FC_InsertVar(myDest[7].ImuxSlotMap);
    return theStream;
}

istream& TSXC_S2MCast::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myDest[0].Shelf);
    theStream>>FC_ExtractVar(myDest[0].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[1].Shelf);
    theStream>>FC_ExtractVar(myDest[1].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[2].Shelf);
    theStream>>FC_ExtractVar(myDest[2].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[3].Shelf);
    theStream>>FC_ExtractVar(myDest[3].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[4].Shelf);
    theStream>>FC_ExtractVar(myDest[4].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[5].Shelf);
    theStream>>FC_ExtractVar(myDest[5].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[6].Shelf);
    theStream>>FC_ExtractVar(myDest[6].ImuxSlotMap);
    theStream>>FC_ExtractVar(myDest[7].Shelf);
    theStream>>FC_ExtractVar(myDest[7].ImuxSlotMap);
    return theStream;
}

FC_Stream& TSXC_S2MCast::WriteObjectBinary( FC_Stream& theStream )
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        theStream<<myDest[i].Shelf;
        theStream<<myDest[i].ImuxSlotMap;
    }
    return theStream;
}

FC_Stream& TSXC_S2MCast::ReadObjectBinary( FC_Stream& theStream )
{
    for (int i = 0; i < TSXC_MAX_SHELF_PER_MCAST; i++)
    {
        theStream>>myDest[i].Shelf;
        theStream>>myDest[i].ImuxSlotMap;
    }
    return theStream;
}
