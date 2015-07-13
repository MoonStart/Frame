/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     22 April 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the error count of GFP layer
 --------------------------------------------------------------------------*/

#include <Monitoring/MON_GfpCounters.h>
#include <PM_BbCountGfp.h>


//-----------------------------------------------------------------
PM_BbCountGfp::PM_BbCountGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbCountGfp::~PM_BbCountGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountGfp::Update(MON_GfpCounters& theCounter) 
{
    uint32 count = 0;

    theCounter.GetErrorCount(CT_TEL_GFP_10BERROR, &count);
    my10BErrCounter.Update(count);
}

//-----------------------------------------------------------------
ostream& PM_BbCountGfp::WriteObject( ostream& theStream )
{
    return theStream << my10BErrCounter;

}

//-----------------------------------------------------------------
istream& PM_BbCountGfp::ReadObject( istream& theStream )
{
    return theStream >> my10BErrCounter;

}

//-----------------------------------------------------------------
void PM_BbCountGfp::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
