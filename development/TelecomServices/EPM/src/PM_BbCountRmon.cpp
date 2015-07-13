/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 20, 2005 Larry Wolfrum.
 DESCRIPTION:   Update and keep the statistics and
				error counts of RMON Ethernet.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_RmonCounters.h>
#include <EPM/PM_BbCountRmon.h>
#include <CommonTypes/CT_PMA_General.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
PM_BbCountRmon::PM_BbCountRmon()
{
    if (( CSPII_CardIF::GetInstance()->GetCardType() == HGTM ) || ( CSPII_CardIF::GetInstance()->GetCardType() == FGTME )
     || ( CSPII_CardIF::GetInstance()->GetCardType() == HGTMS ) //Coriant HGTMS
     || ( CSPII_CardIF::GetInstance()->GetCardType() == OSM2C )|| ( CSPII_CardIF::GetInstance()->GetCardType() == HGTMMS ))
    {
        myDroppedEventsCounter.Set64BitPMSupported(true);
        myPacketCounter.Set64BitPMSupported(true);
        myBroadcastPacketCounter.Set64BitPMSupported(true);
        myMulticastPacketCounter.Set64BitPMSupported(true);
        myCrcAlignErrorCounter.Set64BitPMSupported(true);
        myUndersizePacketCounter.Set64BitPMSupported(true);
        myOversizePacketCounter.Set64BitPMSupported(true);
        myFragmentCounter.Set64BitPMSupported(true);
        myJabberCounter.Set64BitPMSupported(true);
    }
}

//-----------------------------------------------------------------
PM_BbCountRmon::~PM_BbCountRmon()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbCountRmon::Update(MON_RmonCounters& theCounter) 
{
    uint32 count = 0;
    uint32 countHIGH = 0;
    CT_PM_64bit_ull count64bit = 0;

    //------------------------------------------------
    // 64 Bit Register. Treat appropriately!
    //------------------------------------------------

    theCounter.GetErrorCount(CT_TEL_RMON_DROP_EVENTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_DROP_EVENTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myDroppedEventsCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_PKTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_PKTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myPacketCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_BROADCAST_PKTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_BROADCAST_PKTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myBroadcastPacketCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_MULTICAST_PKTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_MULTICAST_PKTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myMulticastPacketCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_CRC_ALIGN_ERRORS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_CRC_ALIGN_ERRORS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myCrcAlignErrorCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_UNDERSIZE_PKTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_UNDERSIZE_PKTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myUndersizePacketCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_OVERSIZE_PKTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_OVERSIZE_PKTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myOversizePacketCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_FRAGMENTS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_FRAGMENTS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myFragmentCounter.Update(count64bit);

	theCounter.GetErrorCount(CT_TEL_RMON_JABBERS, &count);
	theCounter.GetErrorCount(CT_TEL_RMON_HIGH_JABBERS, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myJabberCounter.Update(count64bit);

}

//-----------------------------------------------------------------
ostream& PM_BbCountRmon::WriteObject( ostream& theStream )
{
    return theStream << myDroppedEventsCounter
					 <<	myPacketCounter
					 <<	myBroadcastPacketCounter
					 <<	myMulticastPacketCounter
					 <<	myCrcAlignErrorCounter
					 <<	myUndersizePacketCounter
					 <<	myOversizePacketCounter
					 <<	myFragmentCounter
					 <<	myJabberCounter;

}

//-----------------------------------------------------------------
istream& PM_BbCountRmon::ReadObject( istream& theStream )
{
    return theStream >> myDroppedEventsCounter
					 >>	myPacketCounter
					 >>	myBroadcastPacketCounter
					 >>	myMulticastPacketCounter
					 >>	myCrcAlignErrorCounter
					 >>	myUndersizePacketCounter
					 >>	myOversizePacketCounter
					 >>	myFragmentCounter
					 >>	myJabberCounter;

}

//-----------------------------------------------------------------
void PM_BbCountRmon::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
