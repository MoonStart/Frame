// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1PROTECTIONGROUPCONFIG_38D77ED80026_INCLUDED
#define _INC_SP_1PLUS1PROTECTIONGROUPCONFIG_38D77ED80026_INCLUDED


#include "SP_ProtectionGroupConfig.h"
#include <CommonTypes/CT_SP_ProtectionPair.h>
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <ErrorService/FC_Error.h>


//The class defines the configuration of a 1+1 protection 
//group. This class is a blackboard object that holds the 
//configuration of a 1+1 protection group. These objects are 
//store in blackboard regions and are usually accessed either 
//by the facade interface on the admin, or by the blackboard 
//context interface on the PCSM.
//##ModelId=38D77ED80026
class SP_1plus1ProtectionGroupConfig 
: public SP_ProtectionGroupConfig
{
public:
    //Returns the type of 1+1 protection: linear or UPSR.
    //##ModelId=3B8BCA070178
    inline CT_SP_1plus1Type Get1plus1Type() const;
    //Returns the subtype of 1+1 protection:
    //##ModelId=3B8BCA070178
    inline CT_SP_1plus1SubType Get1plus1SubType() const;
    //Return the direction mode of the group: bidir or unidir.
    //##ModelId=3B8BCA070132
    inline CT_SP_DirectionMode GetDirectionMode() const;
    //Return true if hold off should be applied.
    //##ModelId=3B8BCA070100
    inline bool GetHoldOffEnabled() const;
    //Return the hold off timer value
    inline uint16 GetHoldOffTimer() const;
    //Return the protect sub type
    inline CT_SP_1plus1Type GetProtSubType() const;
    //Return true is it is bidirectional switching
    inline bool IsBiSwitching() const;
    //get the sources involved in protection
    CT_SP_ProtectionPair<CT_Port> & GetSources();
    //Get the resource id
    SP_ResourceId GetResourceId();
    //Get the resource 2 id
    SP_ResourceId GetResource2Id();
    //Set Channels
    CT_SP_ProtectionPair<CT_ChannelId> & GetChannels();
    //Get the mate cardtype
    CT_CardType GetMateCardType();

    //Sets the 1+1 type: linear or upsr.
    //##ModelId=3B8BCA0700AF
    void Set1plus1Type(CT_SP_1plus1Type the1plus1Type);
    //Sets the 1+1 subtype: (used only for timing)
    void Set1plus1SubType(CT_SP_1plus1SubType the1plus1SubType);
    //This methods set the direction mode: unidir or bidir.
    //##ModelId=3B8BCA070069
    void SetDirectionMode(CT_SP_DirectionMode theDirectionMode);
    //Set the holdoff timer.
    //##ModelId=3B8BCA070023
    void SetHoldOffTimer(uint16 theHoldOffTimer);
    //Sets prot sub type(HDTG2 DPRing):  SNCN or SNCI or SNCS.
    void SetProtSubType(CT_SP_1plus1Type theProtSubType);
    //Set the bidirectional switching
    void SetBiSwitching(bool theBiSwitching);
    //set the sources involved in protection
    void SetSources(CT_SP_ProtectionPair<CT_Port>& theSources);
    //Set the resource id -- id for any resource this protection group is using
    void SetResourceId(SP_ResourceId theResource);
    //Set the resource 2 id - additional resource that this protecton group is using
    void SetResource2Id(SP_ResourceId theResource);
    //Set channels
    void SetChannels(CT_SP_ProtectionPair<CT_ChannelId>& theChannels);
    //Set mate cardtype
    void SetMateCardType(CT_CardType theMateCardType);


    //Default constructor.
    //##ModelId=38D79CF4026E
    SP_1plus1ProtectionGroupConfig();
    //Copy constructor.
    //##ModelId=3B8BCA0600E0
    SP_1plus1ProtectionGroupConfig(const SP_1plus1ProtectionGroupConfig& theConfig);

    //This method resets configuration to default value, 
    //except for the group ID.
    //##ModelId=38DF79C20239
    virtual void Reset();

    //This method checks if the group is configured
    //and provisioned as expected
    bool IsGroupConfigured(CT_SP_1plus1Type the1plus1Type, CT_SP_ProtectionPair<CT_Port>& theSources);

    //Destructor.
    //##ModelId=38E201F50219
    virtual ~SP_1plus1ProtectionGroupConfig();

    //Assignment operator.
    //##ModelId=3937FD510070
    virtual SP_ProtectionGroupConfig& operator=(const SP_ProtectionGroupConfig& theConfig);
    //Comparioson operator.
    //##ModelId=3B8BCA060068
    virtual bool operator==(const SP_ProtectionGroupConfig& theRhs) const ;
    //Returns true is current facilities, connection points 
    //or pass-through connection IDs are different than the 
    //given one.
    //##ModelId=3B8BCA060018
    virtual bool IsGroupDifferent(const SP_ProtectionGroupConfig& theRhs) const;

protected:
    //Writes the attributes of the configuration to a stream.
    //##ModelId=3932D20B0163
    virtual ostream& WriteObject( ostream& theStream );
    //Reads the attributes of the configuration from a stream.
    //##ModelId=3932D20B00CD
    virtual istream& ReadObject( istream& theStream );
    //Writes the attributes of the configuration to a binary 
    //stream.
    //##ModelId=39ACEFD200D5
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    //Reads the attributes of the configuration from a binary 
    //stream.
    //##ModelId=39ACEFD2007B
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:
    //The level at which protection is done: linear,upsr, oaps, timing, dpring, or oduk-laps.
    //##ModelId=3B8BCA0503BA
    CT_SP_1plus1Type my1plus1Type;

    //The 1plus1 subtype (used only with timing).
    //##ModelId=3B8BCA0503BA
    CT_SP_1plus1SubType my1plus1SubType;

    CT_SP_1plus1Type myProtSubType;//Used for HDTG2 DPRing ProtType=SNCN/SNCI/SNCS

    //The directions the the 1+1 should handle: bidir 
    //(bridged and switch), unidir (switch only).
    //##ModelId=3B8BCA0503B0
    CT_SP_DirectionMode myDirectionMode;

    //This is to indicate that the protection group should 
    //apply a hold off period before actually 
    //switching.
    //##ModelId=3B8BCA050361
    uint16 myHoldOffTimer;

    // This is to indicate whether it is bidirectional switching
    bool myBiSwitching;

    //The sources (facilities or paths) being protected
    CT_SP_ProtectionPair<CT_Port> mySources;

    //Any applicable resource ids that signal protect has to keep track of
    SP_ResourceId myResourceId;
    SP_ResourceId myResource2Id;

    //A pair of channel ids
    CT_SP_ProtectionPair<CT_ChannelId> myChannels;

    CT_CardType myMateCardType;
    
};

//##ModelId=3B8BCA070178
inline CT_SP_1plus1Type SP_1plus1ProtectionGroupConfig::Get1plus1Type() const
{
    return my1plus1Type;
}

//##ModelId=3B8BCA070178
inline CT_SP_1plus1SubType SP_1plus1ProtectionGroupConfig::Get1plus1SubType() const
{
    return my1plus1SubType;
}

//##ModelId=3B8BCA070132
inline CT_SP_DirectionMode SP_1plus1ProtectionGroupConfig::GetDirectionMode() const
{
    return myDirectionMode;
}

//##ModelId=3B8BCA070100
inline bool SP_1plus1ProtectionGroupConfig::GetHoldOffEnabled() const
{
    return (myHoldOffTimer !=0);
}

//##ModelId=3B8BCA070100
inline uint16 SP_1plus1ProtectionGroupConfig::GetHoldOffTimer() const
{
    return myHoldOffTimer;
}

inline CT_SP_1plus1Type SP_1plus1ProtectionGroupConfig::GetProtSubType() const
{
    return myProtSubType;
}

inline bool SP_1plus1ProtectionGroupConfig::IsBiSwitching() const
{
    return myBiSwitching;
}


#endif /* _INC_SP_1PLUS1PROTECTIONGROUPCONFIG_38D77ED80026_INCLUDED */

