/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Update and keep the error count of TCM layer
 --------------------------------------------------------------------------*/

#include <Monitoring/MON_TcmCounters.h>
#include <EPM/PM_BbCountTcm.h>
#include <CommonTypes/CT_PMA_General.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
PM_BbCountTcm::PM_BbCountTcm ()
{
    if ( CSPII_CardIF::GetInstance()->GetCardType() == HGTM 
      || CSPII_CardIF::GetInstance()->GetCardType() == HGTMS ) //Coriant HGTMS
    {
        myBIPCounter.Set64BitPMSupported(true);
    }
}

//-----------------------------------------------------------------
PM_BbCountTcm::~PM_BbCountTcm ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountTcm::Update(MON_TcmCounters& theCounter) 
{
    uint32 count = 0;
    uint32 countHIGH = 0;
    unsigned long long count64bit = 0;

    //------------------------------------------------
    // 64 Bit Register. Treat appropriately!
    //------------------------------------------------

    theCounter.GetErrorCount(CT_TEL_TCM_BIP8, &count);
	theCounter.GetErrorCount(CT_TEL_TCM_HIGH_BIP8, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myBIPCounter.Update(count64bit);
}

//-----------------------------------------------------------------
ostream& PM_BbCountTcm::WriteObject( ostream& theStream )
{
    return (theStream << myBIPCounter);
		

}

//-----------------------------------------------------------------
istream& PM_BbCountTcm::ReadObject( istream& theStream )
{
    return (theStream >> myBIPCounter);

}

//-----------------------------------------------------------------
void PM_BbCountTcm::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
