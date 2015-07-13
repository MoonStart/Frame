/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     February 8, 1999 Marc-Andre Ledoux.
 DESCRIPTION:   Update and keep the error count of Data (RS,
                FICON, ESCON, GbE, GOPT).
--------------------------------------------------------------------------*/

#include <Monitoring/MON_RsCounters.h>
#include <PM_BbCountData.h>
#include <CommonTypes/CT_PMA_General.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
//##ModelId=3C9255C7009F
PM_BbCountData::PM_BbCountData ()
{
    if (( CSPII_CardIF::GetInstance()->GetCardType() == HGTM ) || ( CSPII_CardIF::GetInstance()->GetCardType() == FGTME )
                                                               || ( CSPII_CardIF::GetInstance()->GetCardType() == HGTMS ) //Coriant HGTMS
                                                               || ( CSPII_CardIF::GetInstance()->GetCardType() == OSM2C ) )
    {
        myBIPCounter.Set64BitPMSupported(true);
    }
}

//-----------------------------------------------------------------
//##ModelId=3C9255C700A0
PM_BbCountData::~PM_BbCountData ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255C700C7
void PM_BbCountData::Update(MON_RsCounters& theCounter) 
{
    uint32 count = 0;
    uint32 countHIGH = 0;

	CT_PM_64bit_ull count64bit = 0;

    //------------------------------------------------
    // 64 Bit Register. Treat appropriately!
    //------------------------------------------------

    theCounter.GetErrorCount(CT_TEL_RS_B1, &count);

    //================================================
    theCounter.GetErrorCount(CT_TEL_RS_HIGH_B1, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myBIPCounter.Update(count64bit);
    //================================================
}

//-----------------------------------------------------------------
//##ModelId=3C9255C700D2
ostream& PM_BbCountData::WriteObject( ostream& theStream )
{
    return theStream << myBIPCounter;
}

//-----------------------------------------------------------------
//##ModelId=3C9255C700DD
istream& PM_BbCountData::ReadObject( istream& theStream )
{
    return theStream >> myBIPCounter;
}

//-----------------------------------------------------------------
//##ModelId=3C9255C700AA
void PM_BbCountData::Init(restart_type theRestart)
{
    // Nothing to do for now.
 
}
