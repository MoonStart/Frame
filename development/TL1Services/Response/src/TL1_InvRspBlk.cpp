/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 INV Response 
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Retrive INV Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_InvRspBlk.h>


TL1_InvRspBlk::TL1_InvRspBlk(const TL1_SmartParameter<string>&          theEntityName,
                             const TL1_SmartParameter<CT_TL1_SlotAddr>& theAddr,
                             const TL1_SmartParameter<CT_PartNumber>&   thePartNumber,
                             const TL1_SmartParameter<string>&          theType,
                             const TL1_SmartParameter<string>&          theSerialNumber,
                             const TL1_SmartParameter<string>&          theHWRevLevel,
                             const TL1_SmartParameter<string>&          theCLEICode,
                             const TL1_SmartParameter<CT_LaserReach>&   theLaserReach,
                             const TL1_SmartParameter<string>&          theSfpType,
                             const TL1_SmartParameter<string>&          theSfpVendor,
                             const TL1_SmartParameter<string>&          theSfpVendorPN,
                             const TL1_SmartParameter<string>&          theXfpVendor,
                             const TL1_SmartParameter<string>&          theXfpVendorPN,
                             const TL1_SmartParameter<CT_FirmwareStatus>& theFirmwareStatus,
                                const TL1_SmartParameter<CT_SoftwareStatus>& theSoftwareStatus) :
    itsEntityName(theEntityName),
    itsAddr(theAddr),
    itsPartNumber(thePartNumber),
    itsType(theType),
    itsSerialNumber(theSerialNumber),
    itsHWRevLevel(theHWRevLevel),
    itsCLEICode(theCLEICode),
    itsLaserReach(theLaserReach),
    itsSfpType(theSfpType),
    itsSfpVendor(theSfpVendor),
    itsSfpVendorPN(theSfpVendorPN),
    itsXfpVendor(theXfpVendor),
    itsXfpVendorPN(theXfpVendorPN),
    itsFirmwareStatus(theFirmwareStatus),
    itsSoftwareStatus(theSoftwareStatus)
{
}

TL1_InvRspBlk::~TL1_InvRspBlk()
{
}
  
TL1_InvRspBlk::TL1_InvRspBlk(const TL1_InvRspBlk& theBlock) :
    itsEntityName(theBlock.itsEntityName),
    itsAddr(theBlock.itsAddr),
    itsPartNumber(theBlock.itsPartNumber),
    itsType(theBlock.itsType),
    itsSerialNumber(theBlock.itsSerialNumber),
    itsHWRevLevel(theBlock.itsHWRevLevel),
    itsCLEICode(theBlock.itsCLEICode),
    itsLaserReach(theBlock.itsLaserReach),
    itsSfpType(theBlock.itsSfpType),
    itsSfpVendor(theBlock.itsSfpVendor),
    itsSfpVendorPN(theBlock.itsSfpVendorPN),
    itsXfpVendor(theBlock.itsXfpVendor),
    itsXfpVendorPN(theBlock.itsXfpVendorPN),
    itsFirmwareStatus(theBlock.itsFirmwareStatus),
    itsSoftwareStatus(theBlock.itsSoftwareStatus)
{
}

TL1_InvRspBlk& TL1_InvRspBlk::operator=( const TL1_InvRspBlk& theBlock )
{
    itsEntityName=   theBlock.itsEntityName;
    itsAddr=         theBlock.itsAddr;
    itsPartNumber=   theBlock.itsPartNumber;
    itsType=         theBlock.itsType;
    itsSerialNumber= theBlock.itsSerialNumber;
    itsHWRevLevel=   theBlock.itsHWRevLevel;
    itsCLEICode=     theBlock.itsCLEICode;
    itsLaserReach=   theBlock.itsLaserReach;
    itsSfpType=      theBlock.itsSfpType;
    itsSfpVendor=    theBlock.itsSfpVendor;
    itsSfpVendorPN=  theBlock.itsSfpVendorPN;
    itsXfpVendor=    theBlock.itsXfpVendor;
    itsXfpVendorPN=  theBlock.itsXfpVendorPN;
    itsFirmwareStatus= theBlock.itsFirmwareStatus;
    itsSoftwareStatus= theBlock.itsSoftwareStatus;
    
    return *this;
}

bool TL1_InvRspBlk::operator==( const TL1_InvRspBlk& theBlock ) const
{
    return ( itsEntityName==   theBlock.itsEntityName &&
             itsAddr==         theBlock.itsAddr &&
             itsPartNumber==   theBlock.itsPartNumber &&
             itsType==         theBlock.itsType &&
             itsSerialNumber== theBlock.itsSerialNumber &&
             itsHWRevLevel==   theBlock.itsHWRevLevel &&
             itsCLEICode==     theBlock.itsCLEICode &&
             itsLaserReach==   theBlock.itsLaserReach &&
             itsSfpType==      theBlock.itsSfpType &&
             itsSfpVendor==    theBlock.itsSfpVendor &&
             itsSfpVendorPN==  theBlock.itsSfpVendorPN &&
             itsXfpVendor==    theBlock.itsXfpVendor &&
             itsXfpVendorPN==  theBlock.itsXfpVendorPN &&
             itsFirmwareStatus== theBlock.itsFirmwareStatus &&
             itsSoftwareStatus== theBlock.itsSoftwareStatus);
}
