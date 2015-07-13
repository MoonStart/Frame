/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     May, 2009           Kumar Solai
 DESCRIPTION:   TSXC Stage Three Multicast Class Implementation
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_S3MCAST_C
#define TSXC_S3MCAST_C

#include <TelCommon/TEL_BbObjectBase.h>
#include <BaseClass/FC_TextStream.h>
#include <XC/TSXC_S3MCast.h>
#include <string.h>

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TSXC_S3MCast::TSXC_S3MCast()
{
    InitMCast();
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TSXC_S3MCast::~TSXC_S3MCast()
{
}

//-------------------------------------------------------------------------
// Validate Methods
//-------------------------------------------------------------------------
bool TSXC_S3MCast::IsMcastIdSet() const
{
    return (myMCastId == XC_MCASTID_UNKNOWN ? false : true);
}

//-------------------------------------------------------------------------
// Set Methods
//-------------------------------------------------------------------------
void TSXC_S3MCast::InitMCast()
{
    myMCastId = XC_MCASTID_UNKNOWN;
    myDestination = 0;

    for(int i=0; i < 10; i++)
    {
        myDst[i] = 0;
    }
}

void TSXC_S3MCast::SetMCastId( uint16 theMCastId )
{
    myMCastId = theMCastId;
}

void TSXC_S3MCast::SetDestination( uint8 theDest )
{
    myDestination = theDest;
}

void TSXC_S3MCast::SetDestination( CT_FAC_StsMap& theDst )
{
    uint8 aDstIndex;
    uint8 aDstBit;
    uint16 aDstChan;

    // Clear myDst and reset dst channel
    memset(myDst, 0, sizeof(myDst));
    aDstChan = 0;

    // Populate myDst based on theDst
    for(aDstIndex = 0; aDstIndex < 10; aDstIndex++)
    {
        for(aDstBit = 0; aDstBit < 16; aDstBit++)
        {
            if (theDst.IsInUse(aDstChan))
            {
                myDst[aDstIndex] |= (1 << aDstBit);
            }

            aDstChan++;
        }
    }
}

//-------------------------------------------------------------------------
// Get Methods
//-------------------------------------------------------------------------

uint16 TSXC_S3MCast::GetMCastId()
{
    return myMCastId;
}

uint8 TSXC_S3MCast::GetDestination()
{
    return myDestination;
}

void TSXC_S3MCast::GetDestinationMap(CT_FAC_StsMap& theDstMap)
{
    uint8 aDstIndex;
    uint8 aDstBit;
    uint16 aDstChan;

    // Reset theDstMap and dst channel
    theDstMap.Reset();
    aDstChan = 0;

    // Populate RetMap based on myDst
    for(aDstIndex = 0; aDstIndex < 10; aDstIndex++)
    {
        for(aDstBit = 0; aDstBit < 16; aDstBit++)
        {
            if (myDst[aDstIndex] & (1 << aDstBit))
            {
                theDstMap.AddSts(aDstChan);
            }

            aDstChan++;
        }
    }
}

//-------------------------------------------------------------------------
// Operators
//-------------------------------------------------------------------------
bool TSXC_S3MCast::operator==(const TSXC_S3MCast& theMCast) const
{
    bool retVal;

    retVal = true;

    if ( (myMCastId     != theMCast.myMCastId) ||
         (myDestination != theMCast.myDestination) ||
         (memcmp(myDst, theMCast.myDst, sizeof(myDst)) != 0)  )
    {
        retVal = false;
    }

    return retVal;
}

bool TSXC_S3MCast::operator!=(const TSXC_S3MCast& theMCast) const
{
    return (!(*this == theMCast));
}


//-------------------------------------------------------------------------
void TSXC_S3MCast::PrintMulticast(int theChan)
{
    FC_FmtFlags previousFlags;

    previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::left);

    fc_cout.Width(8);
    fc_cout << (theChan+1);
    fc_cout.Width(20);
    fc_cout << static_cast<int>(myMCastId);
 
    // TBD   

    fc_cout << endl;
    fc_cout.Width(0);
    fc_cout.Flags(previousFlags);
}

//-------------------------------------------------------------------------
// Serialization Methods
//-------------------------------------------------------------------------

ostream& TSXC_S3MCast::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myMCastId);
    theStream<<FC_InsertVar(myDestination);
    for(int i = 0; i < 10; i++)
    {
        theStream<<FC_InsertVar(myDst[i]);
    }

    return theStream;
}

istream& TSXC_S3MCast::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myMCastId);
    theStream>>FC_ExtractVar(myDestination);
    for(int i = 0; i < 10; i++)
    {
        theStream>>FC_ExtractVar(myDst[i]);
    }

    return theStream;
}

FC_Stream& TSXC_S3MCast::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myMCastId;
    theStream<<myDestination;
    for(int i = 0; i < 10; i++)
    {
        theStream<<myDst[i];
    }

    return theStream;
}

FC_Stream& TSXC_S3MCast::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myMCastId;
    theStream>>myDestination;
    for(int i = 0; i < 10; i++)
    {
        theStream>>myDst[i];
    }

    return theStream;
}

#endif // TSXC_S3MCAST_C
