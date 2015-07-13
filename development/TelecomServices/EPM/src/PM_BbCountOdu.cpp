/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     22 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Update and keep the error count of ODU layer
 --------------------------------------------------------------------------*/

#include <Monitoring/MON_OduCounters.h>
#include <EPM/PM_BbCountOdu.h>
#include <CommonTypes/CT_PMA_General.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
PM_BbCountOdu::PM_BbCountOdu ()
{
    if ( CSPII_CardIF::GetInstance()->GetCardType() == HGTM  
      || CSPII_CardIF::GetInstance()->GetCardType() == HGTMS //Coriant HGTMS
      || CSPII_CardIF::GetInstance()->GetCardType() == OSM2C) 
    {
        myBIPCounter.Set64BitPMSupported(true);
    }
}

//-----------------------------------------------------------------
PM_BbCountOdu::~PM_BbCountOdu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountOdu::Update(MON_OduCounters& theCounter) 
{
    uint32 count = 0;
    uint32 countHIGH = 0;
    unsigned long long count64bit = 0;

    //------------------------------------------------
    // 64 Bit Register. Treat appropriately!
    //------------------------------------------------

    theCounter.GetErrorCount(CT_TEL_ODU_BIP8, &count);
	theCounter.GetErrorCount(CT_TEL_ODU_HIGH_BIP8, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myBIPCounter.Update(count64bit);
}

//-----------------------------------------------------------------
ostream& PM_BbCountOdu::WriteObject( ostream& theStream )
{
    return (theStream << myBIPCounter);
		

}

//-----------------------------------------------------------------
istream& PM_BbCountOdu::ReadObject( istream& theStream )
{
    return (theStream >> myBIPCounter);

}

//-----------------------------------------------------------------
void PM_BbCountOdu::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
