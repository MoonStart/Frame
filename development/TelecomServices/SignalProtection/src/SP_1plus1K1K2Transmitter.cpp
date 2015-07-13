// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <ErrorService/FC_Error.h>
#include <Monitoring/MON_MsStatus.h>
#include <Monitoring/MON_Region.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_MsProt.h>
#include "../SP_1plus1K1K2Transmitter.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_DefectProcessorAction.h"

//##ModelId=390584020003
SP_1plus1K1K2Transmitter::SP_1plus1K1K2Transmitter(SP_1plus1ProtectionAction& theProtectionAction):
    myProtectionAction(theProtectionAction)
{
}

//##ModelId=39058402002B
SP_1plus1K1K2Transmitter::~SP_1plus1K1K2Transmitter()
{
}


//##ModelId=3B8BCA030190
void SP_1plus1K1K2Transmitter::Reset()
{
    {
        // get pointer to CFG
        CFG_MsProt& aCfgObject = static_cast<CFG_MsProt&>((*myProtectionAction.myCfgMsRegion.working)[0]);

        // write new K1K2 values on protection facility
        bool changed = false;
        if (aCfgObject.GetEgressK1Value() != 0)
        {
            aCfgObject.SetEgressK1Value(0);
            changed = true;
        }
        if (aCfgObject.GetEgressK2Value() != 0)
        {
            aCfgObject.SetEgressK2Value(0);
            changed = true;
        }
        if (changed)
        {
            myProtectionAction.myCfgMsRegion.working->IncModificationCounter();
            myProtectionAction.myCfgMsRegion.working->UpdateNotify();
        }
    }
    {
        // get pointer to CFG
        CFG_MsProt& aCfgObject = static_cast<CFG_MsProt&>((*myProtectionAction.myCfgMsRegion.protection)[0]);

        // write new K1K2 values on protection facility
        bool changed = false;
        if (aCfgObject.GetEgressK1Value() != 0)
        {
            aCfgObject.SetEgressK1Value(0);
            changed = true;
        }
        if (aCfgObject.GetEgressK2Value() != 0)
        {
            aCfgObject.SetEgressK2Value(0);
            changed = true;
        }
        if (changed)
        {
            myProtectionAction.myCfgMsRegion.protection->IncModificationCounter();
            myProtectionAction.myCfgMsRegion.protection->UpdateNotify();
        }
    }
}

//##ModelId=39059FDE01F5
void SP_1plus1K1K2Transmitter::SetRequest(SP_K1Request theRequest)
{
    switch (theRequest)
    {
    case SP_1PLUS1_K1_SF_H:
    case SP_1PLUS1_K1_SD_H:

        // If we are in SONET, put the low priority code
        if (myProtectionAction.GetConfig().GetFacilityStandard() == CT_TEL_SONET)
            theRequest = (theRequest == SP_1PLUS1_K1_SF_H) ? SP_1PLUS1_K1_SF_L : SP_1PLUS1_K1_SD_L;
        // no break!
    default:
        myK1K2bytes.request = theRequest;
        break;
    }
}



//##ModelId=39170C490169
FC_Object*  SP_1plus1K1K2Transmitter::DoRunWithReason(unsigned theRunReason,
                                                      FC_Object* theInvokerObj,
                                                      FC_Object* theParam)
{

    myK1K2bytes.path   = false;   // 1+1 architecture
    myK1K2bytes.status = SP_1PLUS1_UNIDIR;

    // read b5-b8 of protection K1 byte
    uint8 aRxK1=0;

    MON_MsStatus& aMonObject = static_cast<MON_MsStatus&>((*myProtectionAction.myMonStatusRegion.protection)[myProtectionAction.myMONObjectIndex.protection]);
    // use K1K2 only if valid
    if (aMonObject.IsValid())
    {
        aRxK1 = aMonObject.GetK1RxByte();
        //aRxK2 = aMonObject.GetK2RxByte();

        // if rx selected is null, transmit null
        if ( (aRxK1 & 0x0F) == 0)
            myK1K2bytes.source = 0;
        else // otherwise send working
            myK1K2bytes.source = 1;  // working #1 is protected
    }
    else
    {
        myK1K2bytes.source = 1;
    }

    // convert into bits
    uint8 aK1 = myK1K2bytes.GetK1();
    uint8 aK2 = myK1K2bytes.GetK2();

    // get pointer to CFG
    CFG_MsProt& aCfgObject = static_cast<CFG_MsProt&>((*myProtectionAction.myCfgMsRegion.protection)[0]);

    // write new K1K2 values on protection facility
    bool changed = false;
    if (aCfgObject.GetEgressK1Value() != aK1)
    {
        aCfgObject.SetEgressK1Value(aK1);
        changed = true;
    }
    if (aCfgObject.GetEgressK2Value() != aK2)
    {
        aCfgObject.SetEgressK2Value(aK2);
        changed = true;
    }
    if (changed)
    {
        myProtectionAction.myCfgMsRegion.protection->IncModificationCounter();
        myProtectionAction.myCfgMsRegion.protection->UpdateNotify();
    }

    return NULL;
}

//##ModelId=3905A66900F9
void SP_1plus1K1K2Transmitter::SetAPSChannel(CT_SP_Protection theChannel)
{
    switch (theChannel)
    {
    case CT_SP_PROTECTION_SIDE:
    case CT_SP_WORKING_SIDE:
        break;
    default: FC_THROW_ERROR(FC_InvalidArgumentError, "Invalid APS channel side");
    }

    myK1K2bytes.destination = theChannel; // use destination field for selected APS channel

}

//##ModelId=3B8BCA03017C
ostream& SP_1plus1K1K2Transmitter::WriteObject( ostream& theStream )
{
    SP_K1K2Transmitter::WriteObject(theStream);
    return theStream;
}

//##ModelId=3B8BCA03015E
istream& SP_1plus1K1K2Transmitter::ReadObject( istream& theStream )
{
    SP_K1K2Transmitter::ReadObject(theStream);
    return theStream;
}

//##ModelId=3B8BCA03014A
FC_Stream& SP_1plus1K1K2Transmitter::WriteObjectBinary( FC_Stream& theStream )
{
    SP_K1K2Transmitter::WriteObjectBinary(theStream);
    return theStream;
}

//##ModelId=3B8BCA03012C
FC_Stream& SP_1plus1K1K2Transmitter::ReadObjectBinary( FC_Stream& theStream )
{

    SP_K1K2Transmitter::ReadObjectBinary(theStream);
    return theStream;
}


//##ModelId=3B8BCA030191
bool SP_1plus1K1K2Transmitter::HasChangedSinceLastCheck()
{
    return SP_K1K2Transmitter::HasChangedSinceLastCheck();
}



