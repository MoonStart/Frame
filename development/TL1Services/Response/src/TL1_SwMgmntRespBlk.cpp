/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         June 11 2003- Mathieu Lavoie
DESCRIPTION:    Implementation file for TL1 Sw Mgmnt response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_SwMgmntRespBlk.h>


TL1_RtvUpgStateRspBlk::TL1_RtvUpgStateRspBlk( const TL1_SmartParameter< CT_SMAA_SubState >& theState):
	itsState(theState)
{
}

TL1_RtvUpgStateRspBlk::~TL1_RtvUpgStateRspBlk()
{
}

TL1_RtvUpgStateRspBlk::TL1_RtvUpgStateRspBlk( const TL1_RtvUpgStateRspBlk& theBlock )
{
	*this = theBlock;
}

TL1_RtvUpgStateRspBlk& TL1_RtvUpgStateRspBlk::operator=( const TL1_RtvUpgStateRspBlk& theBlock )
{
	itsState = theBlock.itsState;
    return *this;
}



TL1_RtvFileRspBlk::TL1_RtvFileRspBlk(const TL1_SmartParameter<uint32>& theStorageSize,
                                     const TL1_SmartParameter<uint32>& theStorageUsed,
                                     const TL1_SmartParameter<uint32>& theStorageFree,
                                     const TL1_SmartParameter<string>& theFileName,
                                     const TL1_SmartParameter<uint32>& theFileSize,
                                     const TL1_SmartParameter<CT_TimeTm>& theFileDate ) :
        itsStorageSize(theStorageSize),
        itsStorageUsed(theStorageUsed),
        itsStorageFree(theStorageFree),
        itsFileName(theFileName),
        itsFileSize(theFileSize),
        itsFileDate(theFileDate)
{

}

TL1_RtvFileRspBlk::~TL1_RtvFileRspBlk()
{
}

TL1_RtvFileRspBlk::TL1_RtvFileRspBlk( const TL1_RtvFileRspBlk& theBlock )
{
	*this = theBlock;
}

TL1_RtvFileRspBlk& TL1_RtvFileRspBlk::operator=( const TL1_RtvFileRspBlk& theBlock )
{
    itsStorageSize = theBlock.itsStorageSize;
    itsStorageUsed = theBlock.itsStorageUsed;
    itsStorageFree = theBlock.itsStorageFree;
    itsFileName = theBlock.itsFileName;
    itsFileSize = theBlock.itsFileSize;
    itsFileDate= theBlock.itsFileDate;
    return *this;
}



TL1_RtvSwStateRspBlk::TL1_RtvSwStateRspBlk(const TL1_SmartParameter< CT_SM_PST >& thePST,
    			                          const	TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                          const	TL1_SmartParameter< CT_SM_SST >& theSST) :
        itsPST(thePST),
        itsPSTQ(thePSTQ),
        itsSST(theSST)
{

}

TL1_RtvSwStateRspBlk::~TL1_RtvSwStateRspBlk()
{
}

TL1_RtvSwStateRspBlk::TL1_RtvSwStateRspBlk( const TL1_RtvSwStateRspBlk& theBlock )
{
	*this = theBlock;
}

TL1_RtvSwStateRspBlk& TL1_RtvSwStateRspBlk::operator=( const TL1_RtvSwStateRspBlk& theBlock )
{
    itsPST = theBlock.itsPST;
    itsPSTQ = theBlock.itsPSTQ;
    itsSST = theBlock.itsSST;
    return *this;
}



TL1_ReportFxFrRspBlk::TL1_ReportFxFrRspBlk( const TL1_SmartParameter< CT_FileTransferType >& theFileTransferType,
                            const TL1_SmartParameter< string >& theFileName,
				            const TL1_SmartParameter< CT_FxFrStatus >& theStatus,
				            const TL1_SmartParameter< CT_FxFrResult >& theResult,
                            const TL1_SmartParameter< int >& thePercentage,
                            const TL1_SmartParameter< int >& theBytesTransfered):
        itsFileTransferType(theFileTransferType),
        itsFileName(theFileName),
        itsStatus(theStatus),
        itsResult(theResult),
        itsPercentage(thePercentage),
        itsBytesTransfered(theBytesTransfered)
{

}

TL1_ReportFxFrRspBlk::~TL1_ReportFxFrRspBlk()
{
}

TL1_ReportFxFrRspBlk::TL1_ReportFxFrRspBlk( const TL1_ReportFxFrRspBlk& theBlock )
{
	*this = theBlock;
}

TL1_ReportFxFrRspBlk& TL1_ReportFxFrRspBlk::operator=( const TL1_ReportFxFrRspBlk& theBlock )
{
    itsFileTransferType = theBlock.itsFileTransferType;
    itsFileName = theBlock.itsFileName;
    itsStatus = theBlock.itsStatus;
    itsResult = theBlock.itsResult;
    itsPercentage = theBlock.itsPercentage;
    itsBytesTransfered = theBlock.itsBytesTransfered;
    return *this;
}

TL1_RtvCefRspBlk::TL1_RtvCefRspBlk(const string& theVersion, CT_CEFType theCefType):
itsVersion(theVersion),
itsCefType(theCefType)
{
}

TL1_RtvCefRspBlk::TL1_RtvCefRspBlk(const TL1_RtvCefRspBlk& theBlock)
{
    *this = theBlock;
}

TL1_RtvCefRspBlk::~TL1_RtvCefRspBlk()
{
}

TL1_RtvCefRspBlk& TL1_RtvCefRspBlk::operator=( const TL1_RtvCefRspBlk& theBlock)
{
    itsVersion = theBlock.itsVersion;
    itsCefType = theBlock.itsCefType;
    return *this;
}
