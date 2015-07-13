//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_EvcAutomatic.h"
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_FacilityIds.h>

CFG_EvcAutomatic::CFG_EvcAutomatic(uint32 theIndex):
    CFG_Object(theIndex)
{
    for (int i = 0; i < CT_TEL_NBR_OF_EVCS; i++) 
    {
        myForceAIS[i] = false;
    }

    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        myGfpIdx[i] = CT_TEL_INVALID_VCG_IDX;
    }

    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        myPortIdx[i] = CT_INTF_ID_UNKNOWN;
    }   
}

CFG_EvcAutomatic::~CFG_EvcAutomatic()
{
}

bool CFG_EvcAutomatic::SetForceAIS(bool theForceAIS, unsigned int theEvcIdx)
{
    bool hasChanged = false;
    if(myForceAIS[theEvcIdx] != theForceAIS)
    {
        myForceAIS[theEvcIdx] = theForceAIS;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_EvcAutomatic::GetForceAIS(unsigned int theEvcIdx) const
{
    return myForceAIS[theEvcIdx];
}

bool CFG_EvcAutomatic::SetGfpIdx(uint8 theGfpIdx, uint8 thePortIdx)
{
    bool hasChanged = false;
    if(myGfpIdx[thePortIdx] != theGfpIdx)
    {
        myGfpIdx[thePortIdx] = theGfpIdx;
        hasChanged = true;
    }
    return hasChanged;
}

uint8 CFG_EvcAutomatic::GetGfpIdx(uint8 thePortIdx) const
{
    return myGfpIdx[thePortIdx];
}

bool CFG_EvcAutomatic::SetPortIdx(uint8 thePortIdx, uint8 theGfpIdx)
{
    bool hasChanged = false;
    if(myPortIdx[theGfpIdx] != thePortIdx)
    {
        myPortIdx[theGfpIdx] = thePortIdx;
        hasChanged = true;
    }
    return hasChanged;
}

uint8 CFG_EvcAutomatic::GetPortIdx(uint8 theGfpIdx) const
{
    return myPortIdx[theGfpIdx];
}

void CFG_EvcAutomatic::Reset()
{
    // Initialize all attributes to default values.
    for (int i = 0; i < CT_TEL_NBR_OF_EVCS; i++) 
    {
        myForceAIS[i] = false;
    }

    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        myGfpIdx[i] = CT_TEL_INVALID_VCG_IDX;
    } 

    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        myPortIdx[i] = CT_INTF_ID_UNKNOWN;
    }
}

// For Display
ostream& CFG_EvcAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    for (int i = 0; i < CT_TEL_NBR_OF_EVCS; i++) 
    {
        theStream   << FC_InsertVar(myForceAIS[i]);
    }

    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        theStream   << FC_InsertVar(myGfpIdx[i]);
    } 

    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        theStream   << FC_InsertVar(myPortIdx[i]);
    } 
    return theStream;

}

istream& CFG_EvcAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    for (int i = 0; i < CT_TEL_NBR_OF_EVCS; i++) 
    {
        theStream   >> FC_ExtractVar(myForceAIS[i]);
    }

    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        theStream   >> FC_ExtractVar(myGfpIdx[i]);
    }

    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        theStream   >> FC_ExtractVar(myPortIdx[i]);
    }
    return theStream;

}

// For persitance and region transfer
FC_Stream& CFG_EvcAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    for (int i = 0; i < CT_TEL_NBR_OF_EVCS; i++) 
    {
        theStream   << myForceAIS[i];
    }

    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        theStream   << myGfpIdx[i];
    }

    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        theStream   << myPortIdx[i];
    }
    return theStream;

}

FC_Stream& CFG_EvcAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    for (int i = 0; i < CT_TEL_NBR_OF_EVCS; i++) 
    {
        theStream   >> myForceAIS[i];
    }

    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        theStream   >> myGfpIdx[i];
    }

    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        theStream   >> myPortIdx[i];
    }
    return theStream;

}

void CFG_EvcAutomatic::Display( FC_Stream& theStream )
{
    char outBuf[32];

    theStream   << "EVC AUTO - Gfp Idx  = ";
    for (int i = 0; i < CT_TEL_NBR_OF_ETH_PORTS; i++) 
    {
        theStream   << " " << (int)myGfpIdx[i];
    } 
    theStream   << endl;

    theStream   << "EVC AUTO - Port Index  = ";
    theStream   << endl;
    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        theStream   << " " << (int)myPortIdx[i];
        if (i == 15 || i == 31 || i == 47)
        {
            theStream   << endl;

        }
    }  
    theStream   << endl;

    theStream   << "EVC AUTO - Force AIS  = ";
    theStream   << endl;
    for (int i = 0; i < CT_TEL_NBR_OF_GFPS; i++) 
    {
        sprintf(outBuf, "%3d-%3s /", i, DISPLAY_BOOL(myForceAIS[i])); 
        theStream   << outBuf;
        if ((i+1) % 8 == 0)
        {
            theStream   << endl;

        }
    }  
    theStream   << endl;

    theStream   << endl;
}
