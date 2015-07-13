/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - March 2008
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for Ethernet Virtual Connection hardware
 MODIFIED :
--------------------------------------------------------------------------*/

#ifndef TSPII_EVCIF_H
#define TSPII_EVCIF_H

#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_Port.h"
#include "CommonTypes/CT_AgentFacility.h"
#include "TsPii/TSPII_BaseIf.h"

#define DISPLAY_PBIT(x)  ((x == CT_TEL_PbitRegen_Ingress) ? " Ingress " :\
                          (x == CT_TEL_PbitRegen_Egress)  ? " Egress "  :\
                          (x == CT_TEL_PbitRegen_Both)    ? " Both "    :\
                          (x == CT_TEL_PbitRegen_Off)     ? " Off "     :\
                          " Unknown ")

class TSPII_EvcIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_EvcIf(bool theDefault = false);
    virtual                           ~TSPII_EvcIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Monitor Interfaces
    // -----------------------------------------------------------------------------------
    
    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetIsEpl(bool theEnable); 
    virtual bool                      GetIsEpl() const;

    virtual void                      SetAllFrames(bool thAllFrames); 
    virtual bool                      GetAllFrames() const;

    virtual void                      SetPairId(uint32 thePairId); 
    virtual uint32                    GetPairId() const;

    virtual void                      SetDestPort(CT_Port thePort);
    virtual CT_Port                   GetDestPort() const;

    virtual void                      SetSrcPort(CT_Port thePort);
    virtual CT_Port                   GetSrcPort() const;

    // Whether the source port is part of any EVC - used in the deletion of EVCs
    virtual void                      SetSrcIncludedInAnyEVC(bool theIncluded);
    virtual bool                      GetSrcIncludedInAnyEVC() const;

    // Whether the destinaiton port is part of any EVC - used in the deletion of EVCs
    virtual void                      SetDestIncludedInAnyEVC(bool theIncluded);
    virtual bool                      GetDestIncludedInAnyEVC() const;

    virtual void                      SetEvc(CT_Port srcPort, CT_Port dstPort, bool theEnable, uint32 thePairId, 
                                             bool allframes=true, bool srcIncluded=true, bool dstIncluded=true, bool isProtected=false);

    virtual void                      SetSTAG(uint32 theSTAG);
    virtual uint32                    GetSTAG();

    virtual vector<uint16>            GetSVID();
    virtual void                      SetSVID(vector<uint16> theSVID);

    virtual vector<uint16>            GetCVID();
    virtual void                      SetCVID(vector<uint16> theCVID);

    virtual void                      SetCommittedBurstSize(uint32 theSize);
    virtual uint32                    GetCommittedBurstSize() const;

    virtual void                      SetCommittedInfoRate(uint32 theRate); 
    virtual uint32                    GetCommittedInfoRate() const;

    virtual void                      EnablePauseFrameTransparency(bool enable);
    virtual bool                      GetPauseFrameTransparencyEnabled() const;
    
    virtual void                      SetPbitRegen(CT_TEL_PbitRegen thePbitRegen);
    virtual CT_TEL_PbitRegen          GetPbitRegen() const;

    virtual bool                      GetGARPMode() const;
    virtual void                      SetGARPMode(bool theGARPMode);

    // Whether ETH-AIS is enabled 
    virtual void                      SetAisEnabled(bool theAisEnabled);
    virtual bool                      GetAisEnabled() const;

    // Set the AIS transmission interval
    virtual void                      SetAisInterval(uint16 theAisInterval);
    virtual uint16                    GetAisInterval() const;

    // Set the MEG level included in the AIS message
    virtual void                      SetAisMegLevel(uint8 theAisMegLevel);
    virtual uint8                     GetAisMegLevel() const;

    // Set the destination MAC Address Mode (unicast or multicast)
    virtual void                      SetAisDestMacMode(CT_TEL_MacMode theAisDestMacMode);
    virtual CT_TEL_MacMode            GetAisDestMacMode() const;

    // Set destination MAC Address
    virtual void                      SetAisDestMacAddr(const CT_LacpSystemId & theMacAddr);
    virtual const CT_LacpSystemId   & GetAisDestMacAddr() const;

    // Set the Force AIS Indication
    virtual void                      SetForceAis(bool theEnable);
    virtual bool                      GetForceAis() const;

    // Use this after EVC and AIS parameters have been configured.
    virtual void                      SetAis() {}

        //This method allows enabling or disabling the facility 
    //loopback. Traffic is loop backed toward the source of the EVC 
    //(normally the client)
    virtual void                      SetFacilityLoopBackEnable(bool theEnable);
    virtual bool                      GetFacilityLoopBackEnable() const;

    //This method allows enabling or disabling the terminal 
    //loopback. Traffic is loop backed toward the destination 
    //of the EVC (normally back toward the system)
    virtual void                      SetTerminalLoopBackEnable(bool theEnable);
    virtual bool                      GetTerminalLoopBackEnable() const;

    // Warm Restart
    virtual void                      InitWarm();

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv)
                                          { TSPII_BaseIf::Display(theStream, argc, argv); }
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);

protected:

    void                 RefreshGet();
    void                 RefreshSet();
    string               DisplayPort(CT_Port thePort);

    // Monitoring attributes
   bool ReadPortInput(int argc, char ** argv, char* aBuf, int, CT_ShelfId *aShelfId,CT_SlotId* aSlotId, CT_IntfId* aPortId, CT_FacilitySubType* aPortType, CT_ChannelId* aChannelId );
    
    // Configuration attributes
    bool                   itsIsEpl;
    bool                   itsAllFrames;
    bool                   itsSrcIncludedInAnyEVC;
    bool                   itsDestIncludedInAnyEVC;
    CT_Port                itsDestPort;
    CT_Port                itsSrcPort;
    uint32                 itsPairId;
    uint32                 itsStag;
    vector<uint16>         itsCvid;
    vector<uint16>         itsSvid;
    uint32                 itsCommittedInfoRate;
    uint32                 itsCommittedBurstSize;
    bool                   itsPauseFrameTransparencyEnabled;
    CT_TEL_PbitRegen       itsPbitRegen;
    bool                   itsGARPMode;
    bool                   itsAisEnabled;
    uint16                 itsAisInterval;
    uint8                  itsAisMegLevel;
    CT_TEL_MacMode         itsAisDestMacMode;
    CT_LacpSystemId        itsAisDestMacAddr;
    bool                   itsForceAIS;
    bool                   itsFacilityLoopBackEnable;
    bool                   itsTerminalLoopBackEnable;
};

#endif // TSPII_EVCIF_H
