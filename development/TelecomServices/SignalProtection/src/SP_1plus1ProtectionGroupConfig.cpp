// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_1plus1ProtectionGroupConfig.h"
#include <BaseClass/FC_TextStream.h>

//##ModelId=38D79CF4026E
SP_1plus1ProtectionGroupConfig::SP_1plus1ProtectionGroupConfig():
    SP_ProtectionGroupConfig(),
    my1plus1Type(CT_SP_UNKNOWN),
    my1plus1SubType(CT_SP_SUBTYPE_UNKNOWN),
    myDirectionMode(CT_SP_BIDIRECTIONAL),
    myHoldOffTimer(0),
    myProtSubType(CT_SP_UNKNOWN),
    myBiSwitching(false),
    myResourceId(SP_RESOURCE_ID_DEFAULT),
    myResource2Id(SP_RESOURCE_ID_DEFAULT),
    myMateCardType(CARD_TYPE_UNKNOWN)
{
    mySources.working = CT_Port();
    mySources.protection = CT_Port();
    myChannels.working = UNKNOWN_CHANNEL_ID;
    myChannels.protection = UNKNOWN_CHANNEL_ID;
}

//##ModelId=3B8BCA0600E0
SP_1plus1ProtectionGroupConfig::SP_1plus1ProtectionGroupConfig(const SP_1plus1ProtectionGroupConfig& theConfig):
    SP_ProtectionGroupConfig(theConfig),
    my1plus1Type(theConfig.my1plus1Type),
    my1plus1SubType(theConfig.my1plus1SubType),
    myDirectionMode(theConfig.myDirectionMode),
    myHoldOffTimer(theConfig.myHoldOffTimer),
    myProtSubType(theConfig.myProtSubType),
    myBiSwitching(theConfig.myBiSwitching),
    mySources(theConfig.mySources),
    myResourceId(theConfig.myResourceId),
    myResource2Id(theConfig.myResource2Id),
    myChannels(theConfig.myChannels),
    myMateCardType(theConfig.myMateCardType)
{}

//##ModelId=38DF79C20239
void SP_1plus1ProtectionGroupConfig::Reset()
{
    *this = SP_1plus1ProtectionGroupConfig();
}

//##ModelId=38E201F50219
SP_1plus1ProtectionGroupConfig::~SP_1plus1ProtectionGroupConfig()
{
}

//##ModelId=3B8BCA0700AF
void SP_1plus1ProtectionGroupConfig::Set1plus1Type(CT_SP_1plus1Type the1plus1Type)
{
    my1plus1Type = the1plus1Type;
}

//##ModelId=3B8BCA0700AF
void SP_1plus1ProtectionGroupConfig::Set1plus1SubType(CT_SP_1plus1SubType the1plus1SubType)
{
    my1plus1SubType = the1plus1SubType;
}

//##ModelId=3B8BCA070069
void SP_1plus1ProtectionGroupConfig::SetDirectionMode(CT_SP_DirectionMode theDirectionMode)
{
    myDirectionMode = theDirectionMode;
}

//##ModelId=3B8BCA070023
void SP_1plus1ProtectionGroupConfig::SetHoldOffTimer(uint16 theHoldOffTimer)
{
    myHoldOffTimer = theHoldOffTimer;
}

void SP_1plus1ProtectionGroupConfig::SetProtSubType(CT_SP_1plus1Type theProtSubType)
{
    myProtSubType = theProtSubType;
}

void SP_1plus1ProtectionGroupConfig::SetBiSwitching(bool theBiSwitching)
{
    myBiSwitching = theBiSwitching;
}

//set the sources to be protected
void SP_1plus1ProtectionGroupConfig::SetSources(CT_SP_ProtectionPair<CT_Port>& theSources)
{
    mySources.working = theSources.working;
    mySources.protection = theSources.protection;
}

//set the sources to be protected
void SP_1plus1ProtectionGroupConfig::SetChannels(CT_SP_ProtectionPair<CT_ChannelId>& theChannels)
{
    myChannels.working = theChannels.working;
    myChannels.protection = theChannels.protection;
}

void SP_1plus1ProtectionGroupConfig::SetResourceId(SP_ResourceId theResource)
{
    myResourceId = theResource;
}

void SP_1plus1ProtectionGroupConfig::SetResource2Id(SP_ResourceId theResource)
{
    myResource2Id = theResource;
}

void SP_1plus1ProtectionGroupConfig::SetMateCardType(CT_CardType theMateCardType)
{
    myMateCardType = theMateCardType;
}

//get the sources being protected
CT_SP_ProtectionPair<CT_Port> & SP_1plus1ProtectionGroupConfig::GetSources()
{
    return mySources;
}

//get the sources being protected
CT_SP_ProtectionPair<CT_ChannelId> & SP_1plus1ProtectionGroupConfig::GetChannels()
{
    return myChannels;
}


bool SP_1plus1ProtectionGroupConfig::IsGroupConfigured(CT_SP_1plus1Type the1plus1Type, CT_SP_ProtectionPair<CT_Port>& theSources)
{
    if (InUse() &&
        my1plus1Type == the1plus1Type &&
        mySources == theSources)
        return true;
    else
        return false;
}

SP_ResourceId SP_1plus1ProtectionGroupConfig::GetResourceId()
{
    return myResourceId;
}

SP_ResourceId SP_1plus1ProtectionGroupConfig::GetResource2Id()
{
    return myResource2Id;
}

CT_CardType SP_1plus1ProtectionGroupConfig::GetMateCardType()
{
    return myMateCardType;
}

//##ModelId=3932D20B0163
ostream& SP_1plus1ProtectionGroupConfig::WriteObject( ostream& theStream )
{
    SP_ProtectionGroupConfig::WriteObject(theStream);
    theStream<<FC_InsertVar(my1plus1Type);
    theStream<<FC_InsertVar(myDirectionMode);
    theStream<<FC_InsertVar(myHoldOffTimer);
    theStream<<FC_InsertVar(myBiSwitching);
    theStream<<FC_InsertVar(mySources.working);
    theStream<<FC_InsertVar(mySources.protection);
    theStream<<FC_InsertVar(my1plus1SubType);
    theStream<<FC_InsertVar(myResourceId);
    theStream<<FC_InsertVar(myResource2Id);
    theStream<<FC_InsertVar(myChannels.working);
    theStream<<FC_InsertVar(myChannels.protection);
    theStream<<FC_InsertVar(myMateCardType);
    theStream<<FC_InsertVar(myProtSubType);


    return theStream;
}

//##ModelId=3932D20B00CD
istream& SP_1plus1ProtectionGroupConfig::ReadObject( istream& theStream )
{
    SP_ProtectionGroupConfig::ReadObject(theStream);
    theStream>>FC_ExtractVar(my1plus1Type);
    theStream>>FC_ExtractVar(myDirectionMode);
    theStream>>FC_ExtractVar(myHoldOffTimer);
    theStream>>FC_ExtractVar(myBiSwitching);
    theStream>>FC_ExtractVar(mySources.working);
    theStream>>FC_ExtractVar(mySources.protection);
    theStream>>FC_ExtractVar(my1plus1SubType);
    theStream>>FC_ExtractVar(myResourceId);
    theStream>>FC_ExtractVar(myResource2Id);
    theStream>>FC_ExtractVar(myChannels.working);
    theStream>>FC_ExtractVar(myChannels.protection);
    theStream>>FC_ExtractVar(myMateCardType);
    theStream>>FC_ExtractVar(myProtSubType);

    return theStream;
}

//##ModelId=39ACEFD200D5
FC_Stream& SP_1plus1ProtectionGroupConfig::WriteObjectBinary( FC_Stream& theStream )
{
    SP_ProtectionGroupConfig::WriteObjectBinary(theStream);
    theStream<<my1plus1Type;
    theStream<<myDirectionMode;
    theStream<<myHoldOffTimer;
    theStream<<myBiSwitching;
    theStream<<mySources.working;
    theStream<<mySources.protection;
    theStream<<my1plus1SubType;
    theStream<<myResourceId;
    theStream<<myResource2Id;
    theStream<<myChannels.working;
    theStream<<myChannels.protection;
    theStream<<myMateCardType;
    theStream<<myProtSubType;

    return theStream;
}

//##ModelId=39ACEFD2007B
FC_Stream& SP_1plus1ProtectionGroupConfig::ReadObjectBinary( FC_Stream& theStream )
{
    SP_ProtectionGroupConfig::ReadObjectBinary(theStream);
    theStream>>my1plus1Type;
    theStream>>myDirectionMode;
    theStream>>myHoldOffTimer;
    theStream>>myBiSwitching;
    theStream>>mySources.working;
    theStream>>mySources.protection;
    theStream>>my1plus1SubType;
    theStream>>myResourceId;
    theStream>>myResource2Id;
    theStream>>myChannels.working;
    theStream>>myChannels.protection;
    theStream>>myMateCardType;
    theStream>>myProtSubType;

    return theStream;
}

//##ModelId=3937FD510070
SP_ProtectionGroupConfig& SP_1plus1ProtectionGroupConfig::operator=(const SP_ProtectionGroupConfig& theConfig)
{
    SP_ProtectionGroupConfig::operator=(theConfig);

    const SP_1plus1ProtectionGroupConfig& aConfig = static_cast<const SP_1plus1ProtectionGroupConfig&>(theConfig);

    my1plus1Type                = aConfig.my1plus1Type;
    myDirectionMode             = aConfig.myDirectionMode;
    myHoldOffTimer              = aConfig.myHoldOffTimer;
    myBiSwitching               = aConfig.myBiSwitching;
    mySources                   = aConfig.mySources;
    my1plus1SubType             = aConfig.my1plus1SubType;
    myResourceId                = aConfig.myResourceId;
    myResource2Id               = aConfig.myResource2Id;
    myChannels                  = aConfig.myChannels;
    myMateCardType              = aConfig.myMateCardType;
    myProtSubType               = aConfig.myProtSubType;

    return (*this);
}

//##ModelId=3B8BCA060068
bool SP_1plus1ProtectionGroupConfig::operator==(const SP_ProtectionGroupConfig& theRhs) const 
{
    const SP_1plus1ProtectionGroupConfig& aRhs = static_cast<const SP_1plus1ProtectionGroupConfig&>(theRhs);

    return (SP_ProtectionGroupConfig::operator==(theRhs)   &&
            my1plus1Type                == aRhs.my1plus1Type &&
            myDirectionMode             == aRhs.myDirectionMode &&
            myHoldOffTimer              == aRhs.myHoldOffTimer &&
            myBiSwitching               == aRhs.myBiSwitching &&
            mySources                   == aRhs.mySources &&
            my1plus1SubType             == aRhs.my1plus1SubType &&
            myResourceId                == aRhs.myResourceId &&
            myResource2Id               == aRhs.myResource2Id &&
            myChannels                  == aRhs.myChannels &&
            myProtSubType               == aRhs.myProtSubType &&
            myMateCardType              == aRhs.myMateCardType);

}

//##ModelId=3B8BCA060018
bool SP_1plus1ProtectionGroupConfig::IsGroupDifferent(const SP_ProtectionGroupConfig& theRhs) const 
{
    const SP_1plus1ProtectionGroupConfig& aRhs = static_cast<const SP_1plus1ProtectionGroupConfig&>(theRhs);

    return (SP_ProtectionGroupConfig::IsGroupDifferent(theRhs)   ||
            !(my1plus1Type            == aRhs.my1plus1Type &&
              my1plus1SubType         == aRhs.my1plus1SubType &&
              myDirectionMode         == aRhs.myDirectionMode &&
              myHoldOffTimer          == aRhs.myHoldOffTimer &&
              myBiSwitching           == aRhs.myBiSwitching &&
              mySources               == aRhs.mySources &&
              myResourceId            == aRhs.myResourceId &&
              myResource2Id           == aRhs.myResource2Id &&
              myChannels              == aRhs.myChannels &&
              myProtSubType           == aRhs.myProtSubType &&
              myMateCardType          == aRhs.myMateCardType));

}
