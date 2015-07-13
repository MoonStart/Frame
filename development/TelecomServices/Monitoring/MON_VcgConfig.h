//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_VCGCONFIG_H
#define MON_VCGCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <ExecutionSupport/FC_BaseTimer.h>


//This class contains configuration parameters that affects 
//how the monitoring of the VCG (virtual concatenation group) layer 
//is performed.
class MON_VcgConfig : public MON_Config
{
public:

    //Constructor.
    MON_VcgConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_VcgConfig();

 
    // Set list of ids of HOPs to support the VCG
    void SetHopIdList(CT_FAC_StsMap& theHopIdList);

    // Get list of ids of HOPs used to support the VCG
    CT_FAC_StsMap& GetHopIdList();

    //Set whether the Group of Hops in the VCG is enabled or disabled
    void SetGroupOfHopsEnable(bool theGroupEnable);

    //Get whether the Group of Hops in the VCG is enabled or disabled
    bool GetGroupOfHopsEnable() const;


    //Added to debug how long Automatic Action is taking.
    void SetDebugFlagSet(bool theDebugEnable);
    bool IsDebugFlagSet() const;
    void SetProcessTime(const FC_Milliseconds& theTime);

  
    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // List of ids of HOPs representing my VCG
    CT_FAC_StsMap myHopIdList;

    //The Group of Hops in the VCG state configured.
    bool myGroupEnable;

    //Added to debug how long Automatic Action is taking.
    bool myDebugFlag;
    FC_Milliseconds myLastTime;
    FC_Milliseconds myShortestTime;  
    FC_Milliseconds myLongestTime;
};

#endif /* VCGCONFIG_H */
