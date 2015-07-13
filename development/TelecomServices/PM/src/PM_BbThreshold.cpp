/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM threshold class. Keeps the threshold of PM.
--------------------------------------------------------------------------*/


#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM/PM_BbThreshold.h>


//-----------------------------------------------------------------
//##ModelId=3C1F6F710311
PM_BbThreshold::PM_BbThreshold(uint32 theNumberOfParam, uint32 dummy):
    myNumberOfParam(theNumberOfParam)
{
    myThreshold = new CT_PM_Value [myNumberOfParam];
    myThresholdChanged = new bool [myNumberOfParam];
    Reset();

    myMemoryAllocated = true;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F710325
PM_BbThreshold::PM_BbThreshold(uint32       theNumberOfParam,
                               CT_PM_Value* theThresholdPtr,
                               bool*        theThresholdChangedPtr):
    myNumberOfParam(theNumberOfParam),
    myMemoryAllocated(false)
{
    myThreshold = theThresholdPtr;
    myThresholdChanged = theThresholdChangedPtr;
    Reset();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F710331
PM_BbThreshold::~PM_BbThreshold()
{
    if(myMemoryAllocated)
    {
        delete[] myThreshold;
        delete[] myThresholdChanged;
        myMemoryAllocated = false;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F71033A
void PM_BbThreshold::Reset()
{
    uint32 i = 0;


    for ( i=0; i<myNumberOfParam; i++)
    {
        myThreshold[i].SignedValue = 0;
        myThreshold[i].UnsignedValue = 0;
        myThresholdChanged[i] = true;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F71038B
FC_Stream& PM_BbThreshold::WriteObjectBinary( FC_Stream& theStream )
{
    theStream.write_array((int32*)myThreshold, myNumberOfParam );

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F71039D
FC_Stream& PM_BbThreshold::ReadObjectBinary( FC_Stream& theStream )
{
    // Throw an error: Binary serialization must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "PM_BbThreshold: Textual serialization not implemented" );
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7103B1
ostream& PM_BbThreshold::WriteObject( ostream& theStream )
{
    // Throw an error: Textual serialization must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "PM_BbThreshold: Textual serialization not implemented" );
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7103C5
istream& PM_BbThreshold::ReadObject( istream& theStream )
{
    // Throw an error: Textual serialization must be implemented into derived class
    FC_THROW_ERROR( FC_NotSupportedError, "PM_BbThreshold: Textual serialization not implemented" );

    return theStream;

}
