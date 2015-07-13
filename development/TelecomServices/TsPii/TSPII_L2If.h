/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds - March 2008
 DESCRIPTION:Base class for the hardware independent interface.
             Provides the interface for Level2 switching hardware
 MODIFIED :
--------------------------------------------------------------------------*/

#ifndef TSPII_L2IF_H
#define TSPII_L2IF_H

#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"

const uint32 TSPII_PVID_UNDEFINED = 0xffffffff;
const uint32 TSPII_TPID_UNDEFINED = 0xffffffff;
const uint32 TSPII_PVID_DEFAULT   = 0x00000001;

namespace TSPII_L2
{
    enum Enum
    {
        UNTAGGED = 0,
        TAGGED,
        UNKNOWN
    };
}

class TSPII_L2If : public TSPII_BaseIf
{
public:

    /* Constructor */                 TSPII_L2If(bool theDefault = false);
    virtual                           ~TSPII_L2If();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Monitor Interfaces
    // -----------------------------------------------------------------------------------

    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetCommittedInfoRate(uint32 theRate);
    virtual uint32                    GetCommittedInfoRate() const;

    virtual void                      SetCommittedBurstSize(uint32 theSize);
    virtual uint32                    GetCommittedBurstSize() const;

    virtual void                      SetExcessBurstSize(uint32 theSize);
    virtual uint32                    GetExcessBurstSize() const;

    virtual void                      SetExcessInfoRate(uint32 theRate);
    virtual uint32                    GetExcessInfoRate() const;

    virtual void                      SetColorMode(CT_TEL_BW_CM theMode);
    virtual CT_TEL_BW_CM              GetColorMode() const;

    virtual void                      SetMeterType(CT_TEL_BW_METERTYPE theMode);
    virtual CT_TEL_BW_METERTYPE       GetMeterType() const;

    virtual uint32                    GetPVID() const;
    virtual void                      SetPVID(uint32 thePVID);

    virtual bool                      GetTagmode() const;
    virtual void                      SetTagmode(bool theTagmode);

    virtual uint32                    GetTPID() const;
    virtual void                      SetTPID(uint32 theTPID);

    virtual uint8                     GetPortMode() const;
    virtual void                      SetPortMode(uint8 thePortMode);

    virtual bool                      GetLACPMode() const;
    virtual void                      SetLACPMode(bool theLACPMode);

    virtual bool                      GetLinkOAMMode() const;
    virtual void                      SetLinkOAMMode(bool theLinkOAMMode);

    virtual bool                      GetDot1XMode() const;
    virtual void                      SetDot1XMode(bool theDot1XMode);

    virtual bool                      GetELMIMode() const;
    virtual void                      SetELMIMode(bool theELMIMode);

    virtual bool                      GetLLDPMode() const;
    virtual void                      SetLLDPMode(bool theLLDPMode);

    //virtual bool                      GetGARPMode() const;
    //virtual void                      SetGARPMode(bool theLLDPMode);

    virtual uint16                    GetPortLacpPriority() const;
    virtual void                      SetPortLacpPriority(uint16 theLacpPriority);

    virtual CT_TEL_LacpPartiMode      GetPortLacpPartiMode() const;
    virtual void                      SetPortLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode);

    virtual uint16                    GetMateLacpPriority() const;
    virtual void                      SetMateLacpPriority(uint16 theLacpPriority);

    virtual CT_TEL_LacpPartiMode      GetMateLacpPartiMode() const;
    virtual void                      SetMateLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode);

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

    void                  RefreshGet();
    void                  RefreshSet();

    // Monitoring attributes

    // Configuration attributes
    uint32                itsCommittedInfoRate;
    uint32                itsCommittedBurstSize;
    uint32                itsExcessBurstSize;
    uint32                itsExcessInfoRate;
    CT_TEL_BW_CM          itsColorMode;
    CT_TEL_BW_METERTYPE   itsMeterType;
    uint32                itsPVID;
    uint32                itsTPID;
    uint8                 itsPortMode;
    TSPII_L2::Enum        itsTagMode;
    bool                  itsLACPMode;
    bool                  itsLinkOAMMode;
    bool                  itsDot1XMode;
    bool                  itsELMIMode;
    bool                  itsLLDPMode;
    uint16                itsPortLacpPriority;
    CT_TEL_LacpPartiMode  itsPortLacpPartiMode;
    uint16                itsMateLacpPriority;
    CT_TEL_LacpPartiMode  itsMateLacpPartiMode;

};
#define DISPLAY_TAGMODE(x) ((x == TSPII_L2::TAGGED  ) ? "Tagged" : \
                           (x == TSPII_L2::UNTAGGED) ? "Untagged" : "Unknown")

#endif // TSPII_L2IF_H
