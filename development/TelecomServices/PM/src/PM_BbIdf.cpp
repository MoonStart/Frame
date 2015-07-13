/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     9 March, 1999 Erik Gobeil.
 DESCRIPTION:   Idf class. Keep and set the PM IDF states.
--------------------------------------------------------------------------*/

#include "BaseClass/FC_TextStream.h"
#include "ErrorService/FC_Error.h"
#include "../PM_BbIdf.h"
#include <cstring>


static const uint8 sAvailabilityMask = 0x04;
static const uint8 sInhibitMask      = 0x02;
static const uint8 sInvalidMask      = 0x01;

//-----------------------------------------------------------------
//##ModelId=3C1F6F7401FD
PM_BbIdf::PM_BbIdf(uint32 theNumberOfParam):
    myNumberOfParam(theNumberOfParam)
{
    if(myNumberOfParam == 0)
        myIdf = NULL;
    else
        myIdf = new uint8[myNumberOfParam];

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F74021B
PM_BbIdf::~PM_BbIdf()
{
    delete [] myIdf;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740225
void PM_BbIdf::Reset()
{
    if(myIdf)
        memset(myIdf, 0, myNumberOfParam);

    // Default, all not available.
    ForcedSetAllAvailability(false);
    // Default, all disabled.
    ForcedSetAllInhibit(true);
    // Default, all invalid.
    ForcedSetAllIdf(true);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F74022E
CT_PM_IdfStatus PM_BbIdf::GetIdf(CT_PM_Parameter theParameter) const
{
    if(myIdf)
    {
        // If inhibition is set.
        if (myIdf[theParameter] & sInhibitMask)
        {
            return CT_PM_IDF_OFF;
        }
        else
        {
           // If availability is set.
            if (myIdf[theParameter] & sAvailabilityMask)
            {
                return (myIdf[theParameter] & sInvalidMask ? CT_PM_IDF_PARTIAL : CT_PM_IDF_COMPLETE);
            }
            // If not available.
            else
            {
                return CT_PM_IDF_NA;
            }
        }
    }

    return CT_PM_IDF_OFF;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740239
void PM_BbIdf::SetIdf(CT_PM_Parameter theParameter)
{
    if(myIdf)
        myIdf[theParameter] |= sInvalidMask;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAC0305
void PM_BbIdf::SetIdf(CT_PM_Parameter theParameter, CT_PM_IdfStatus theStatus)
{
    if(myIdf)
    {
        switch (theStatus)
        {
        case CT_PM_IDF_OFF:
            // PM accumulation is inhibited.
            ForcedSetInhibit(theParameter, true);
            break;
        case CT_PM_IDF_NA:
            // PM is not available.
            ForcedSetAvailability(theParameter, false);
            // PM accumulation is enabled.
            ForcedSetInhibit(theParameter, false);
            break;
        case CT_PM_IDF_PARTIAL:
            // PM is available.
            ForcedSetAvailability(theParameter, true);
            // PM accumulation is enabled.
            ForcedSetInhibit(theParameter, false);
            // PM accumulation period is invalid.
            ForcedSetIdf(theParameter, true);
            break;
        case CT_PM_IDF_COMPLETE:
            // PM is available.
            ForcedSetAvailability(theParameter, true);
            // PM accumulation is enabled.
            ForcedSetInhibit(theParameter, false);
            // PM accumulation period is valid.
            ForcedSetIdf(theParameter, false);
            break;
        default:
            FC_THROW_ERROR( FC_NotSupportedError, "PM: This IDF status is not supported" );
            break;
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740243
void PM_BbIdf::SetInhibit(CT_PM_Parameter theParameter, bool theState)
{
    if(myIdf)
    {
        // Since this interface is only used within a period boundary,
        // any change of inhibition sets the invalid flag.
        SetIdf(theParameter);

        // if the inhibition status is off, it is not allowed to change back to on
        // for the rest of the period. During a change of period, the
        // interface ForcedSetInhbit shall be used.

        if (myIdf[theParameter] & sInhibitMask)
        {
            // inhibition is on, a change is possible

            // process the request if an off is requested.
            if (!theState)
            {
                myIdf[theParameter] &= ~sInhibitMask;
            }
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740258
void PM_BbIdf::ForcedSetInhibit(CT_PM_Parameter theParameter, bool theState)
{
    if(myIdf)
        theState ? (myIdf[theParameter] |= sInhibitMask) : (myIdf[theParameter] &= ~sInhibitMask);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F74026C
void PM_BbIdf::ForcedSetAllInhibit(bool theState)
{
    uint16 i;


    if(myIdf)
    {
        if (theState)
        {
            for (i = 0; i < myNumberOfParam; i++)
            {
                myIdf[i] |= sInhibitMask;
            }
        }
        else
        {
            for (i = 0; i < myNumberOfParam; i++)
            {
                myIdf[i] &= ~sInhibitMask;
            }
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3FA161050068
void PM_BbIdf::ForcedSetAvailability(CT_PM_Parameter theParameter, bool theState)
{
    if(myIdf)
        theState ? (myIdf[theParameter] |= sAvailabilityMask) : (myIdf[theParameter] &= ~sAvailabilityMask);

}

//-----------------------------------------------------------------
//##ModelId=3FA161050087
void PM_BbIdf::ForcedSetAllAvailability(bool theState)
{
    uint16 i;


    if(myIdf)
    {
        if (theState)
        {
            for (i = 0; i < myNumberOfParam; i++)
            {
                myIdf[i] |= sAvailabilityMask;
            }
        }

        else
        {
            for (i = 0; i < myNumberOfParam; i++)
            {
                myIdf[i] &= ~sAvailabilityMask;
            }
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740276
void PM_BbIdf::ForcedSetIdf(CT_PM_Parameter theParameter, bool theState)
{
    if(myIdf)
        theState ? (myIdf[theParameter] |= sInvalidMask) : (myIdf[theParameter] &= ~sInvalidMask);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740289
void PM_BbIdf::ForcedSetAllIdf(bool theState)
{
    uint16 i;


    if(myIdf)
    {
        if (theState)
        {
            for (i = 0; i < myNumberOfParam; i++)
            {
                myIdf[i] |= sInvalidMask;
            }
        }

        else
        {
            for (i = 0; i < myNumberOfParam; i++)
            {
                myIdf[i] &= ~sInvalidMask;
            }
        }
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7402A8
ostream& PM_BbIdf::WriteObject( ostream& theStream )
{
    uint32 i;


    if(myIdf)
    {
        for (i=0; i<myNumberOfParam; i++)
        {
            theStream << FC_InsertLabelAndVar ("Param IDF ",myIdf[i]);
        }
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7402BB
istream& PM_BbIdf::ReadObject( istream& theStream )
{
    uint32 i;


    if(myIdf)
    {
        for (i=0; i<myNumberOfParam; i++)
        {
            theStream >> FC_ExtractVar(myIdf[i]);
        }
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7402CF
FC_Stream& PM_BbIdf::WriteObjectBinary( FC_Stream& theStream )
{
    if(myIdf)
        theStream.write_array(myIdf, myNumberOfParam);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7402DA
FC_Stream& PM_BbIdf::ReadObjectBinary( FC_Stream& theStream )
{
    if(myIdf)
        theStream.read_array(myIdf, myNumberOfParam);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F740293
bool PM_BbIdf::operator==(const PM_BbIdf& theOtherIdf) const
{
    uint32 i;
    bool returnFlag = true;


    if(myNumberOfParam != theOtherIdf.myNumberOfParam)
    {
        returnFlag = false;
    }
    else
    {
        for (i=0; i<myNumberOfParam; i++)
        {
            if (myIdf[i] != theOtherIdf.myIdf[i])
            {
                returnFlag = false;
                break;
            }
        }
    }

    return returnFlag;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F74029E
PM_BbIdf& PM_BbIdf::operator=(const PM_BbIdf& theOtherIdf)
{
    uint32 i;


    if(myNumberOfParam != theOtherIdf.myNumberOfParam)
    {
        delete [] myIdf;
        myIdf = new uint8[theOtherIdf.myNumberOfParam];
        myNumberOfParam = theOtherIdf.myNumberOfParam;
    }

    for (i=0; i<myNumberOfParam; i++)
    {
        myIdf[i] = theOtherIdf.myIdf[i];
    }

    return *this;

}
