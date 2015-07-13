/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SPM.
 AUTHOR   :     May 4, 2006  Larry Wolfrum
 DESCRIPTION:   Class defining the state of PM data collection
				files.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbFilePeriodStatus.h>


//-----------------------------------------------------------------
PM_BbFilePeriodStatus::PM_BbFilePeriodStatus(uint32 dummy, uint32 dummy1) :
	myTimestamp(0)
{
	Reset();
}

//-----------------------------------------------------------------
PM_BbFilePeriodStatus::~PM_BbFilePeriodStatus()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbFilePeriodStatus::Reset()
{
	myTimestamp = 0;
}

//-----------------------------------------------------------------
ostream& PM_BbFilePeriodStatus::WriteObject( ostream& theStream )
{
	theStream 
        << FC_InsertVar( myTimestamp );

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbFilePeriodStatus::ReadObject( istream& theStream )
{
	theStream 
			>> FC_ExtractVar( myTimestamp );

    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& PM_BbFilePeriodStatus::WriteObjectBinary( FC_Stream& theStream )
{
    theStream   << myTimestamp;

    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& PM_BbFilePeriodStatus::ReadObjectBinary( FC_Stream& theStream )
{
    theStream   >> myTimestamp;

    return theStream;
}

//-----------------------------------------------------------------
FC_Time& PM_BbFilePeriodStatus::GetTimestamp()
{
	return myTimestamp;
}

//-----------------------------------------------------------------
void PM_BbFilePeriodStatus::SetTimestamp( FC_Time& theTimestamp )
{
	myTimestamp = theTimestamp;
}
