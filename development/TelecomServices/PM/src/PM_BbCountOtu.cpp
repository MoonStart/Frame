/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 24, 2002 Sebastien Cossette.
 DESCRIPTION:   Update and keep the counts of Optical
                Transport Unit or FEC.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OtuCounters.h>
#include <PM_BbCountOtu.h>
#include <CommonTypes/CT_PMA_General.h>
#include <CsPii/CSPII_CardIF.h>

//-----------------------------------------------------------------
//##ModelId=3C20AB6F018B
PM_BbCountOtu::PM_BbCountOtu ()
{
    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
    
    if ( aCardType == HGTM || aCardType == HGTMS || aCardType == HGTMM || aCardType == HGTMMS || aCardType == OSM2C )
    {
        myBIPCounter.Set64BitPMSupported(true);
        myBECounter.Set64BitPMSupported(true);
        myBEByteCounter.Set64BitPMSupported(true);
    }
}

//-----------------------------------------------------------------
//##ModelId=3C20AB6F0194
PM_BbCountOtu::~PM_BbCountOtu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6F01BC
void PM_BbCountOtu::Update(MON_OtuCounters& theCounter) 
{
    uint32 count = 0, count0 = 0;
    uint32 countHIGH = 0, count1HIGH = 0, count0HIGH = 0;
    CT_PM_64bit_ull count64bit = 0;

    theCounter.GetErrorCount(CT_TEL_OTU_BIT_ERROR_ON_ONES, &count);
	theCounter.GetErrorCount(CT_TEL_OTU_BIT_ERROR_ON_ZEROS, &count0);
    //myBECounter.Update(count + count0);
    theCounter.GetErrorCount(CT_TEL_OTU_HIGH_BIT_ERROR_ON_ONES, &count1HIGH);
	theCounter.GetErrorCount(CT_TEL_OTU_HIGH_BIT_ERROR_ON_ZEROS, &count0HIGH);
    count64bit = ( (count0HIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER  + count0) + (count1HIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER  + count) );
    myBECounter.Update(count64bit);

    theCounter.GetErrorCount(CT_TEL_OTU_BYTE_CORRECTIONS, &count);
    theCounter.GetErrorCount(CT_TEL_OTU_HIGH_BYTE_CORRECTIONS, &countHIGH);
    count64bit = countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER  + count;
    myBEByteCounter.Update(count64bit);

    theCounter.GetErrorCount(CT_TEL_OTU_UNCORRECTABLE_RSFRAMES, &count);
    myUBECounter.Update(count);

    //------------------------------------------------
    // 64 Bit Register. Treat appropriately!
    //------------------------------------------------
	theCounter.GetErrorCount(CT_TEL_OTU_BIP8, &count);
	theCounter.GetErrorCount(CT_TEL_OTU_HIGH_BIP8, &countHIGH);
    count64bit = ( countHIGH * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER ) + count;
    myBIPCounter.Update(count64bit);
}

//-----------------------------------------------------------------
//##ModelId=3C20AB6F01C6
ostream& PM_BbCountOtu::WriteObject( ostream& theStream )
{
    return theStream << myBECounter
                     << myUBECounter
					 << myBIPCounter
                     << myBEByteCounter;

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6F01D1
istream& PM_BbCountOtu::ReadObject( istream& theStream )
{
    return theStream >> myBECounter
                     >> myUBECounter
					 >> myBIPCounter
                     >> myBEByteCounter;

}

//-----------------------------------------------------------------
//##ModelId=3CBC8F110127
void PM_BbCountOtu::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
