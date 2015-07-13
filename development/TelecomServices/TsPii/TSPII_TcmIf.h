#ifndef _TSPII_TCMIF_H
#define _TSPII_TCMIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Jessica Chen - July 2010
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/
#include "CommonTypes/CT_G709Trace.h"
#include "CommonTypes/CT_OduDefinitions.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_DwIf.h"


#define MAX_NUM_TCMPOOL_PER_SHELF 136
// Macro to convert input string into Tcm Map Type
// PLEASE KEEP THIS IN SYNCH WITH THE DISPLAY MACRO ABOVE
#define TSPII_TCM_DIRECTION_GET(type) \
    ((strcmp(type, "a") == 0)  ? CT_ODU_Direction_A : \
    (strcmp(type, "b") == 0)   ? CT_ODU_Direction_B : CT_ODU_Direction_A)

class TSPII_TcmMapRecord
{
public:   
    uint16           TcmChannel;   // Tcm Channel - "0" based    
    CT_TCM_Level     TcmLevel;     // TCM Level Type
    CT_ODU_Direction TcmDirection; // TCM A or B
    uint16           OduIndex;     // Odu Index - "0" based
    CT_ODU_Layer     OduKLevel;    // OduK Level - "0" based
    

    TSPII_TcmMapRecord()
    {
       TcmChannel=0; TcmLevel=CT_TCM_Level_UNKNOWN; TcmDirection= CT_ODU_Direction_A; OduIndex=0; OduKLevel=CT_ODU_LayerEnd; 
    }

    void Clear()
    {
       TcmChannel=0; TcmLevel=CT_TCM_Level_UNKNOWN; TcmDirection= CT_ODU_Direction_A;  OduIndex=0; OduKLevel=CT_ODU_LayerEnd; 
    }

    bool operator<(class TSPII_TcmMapRecord const &right) const
    {
        if (this->TcmChannel < right.TcmChannel)
            return true;
        else if (this->TcmChannel == right.TcmChannel)
        {
            if (this->TcmLevel < right.TcmLevel)
                return true;
            else if (this->TcmLevel == right.TcmLevel)
            {
                if (this->TcmDirection < right.TcmDirection)
                    return true;
                else if (this->TcmDirection == right.TcmDirection)
                {
                    if (this->OduIndex < right.OduIndex)
                        return true;
                    else if (this->OduIndex == right.OduIndex)
                    {
                        if (this->OduKLevel < right.OduKLevel)
                            return true;
                        else
                            return false;
                    }
                    else 
                        return false;
                }
                else 
                    return false;
            }
            else 
                return false;
        }
        else 
            return false;
    }

    void operator=(const TSPII_TcmMapRecord &right)
    {
        this->TcmChannel    = right.TcmChannel;
        this->TcmLevel      = right.TcmLevel;  
        this->TcmDirection  = right.TcmDirection;            
        this->OduIndex      = right.OduIndex;
        this->OduKLevel     = right.OduKLevel;        
    }

    bool operator==( const TSPII_TcmMapRecord &right) const
    {
        if((this->TcmChannel    == right.TcmChannel) &&
           (this->TcmLevel     == right.TcmLevel)  && 
           (this->TcmDirection == right.TcmDirection) &&           
           (this->OduIndex    == right.OduIndex) &&
           (this->OduKLevel   == right.OduKLevel))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class TSPII_TcmIf : public TSPII_DwIf
{
public:
    
    /* Constructor */               TSPII_TcmIf(bool theDefault = false);
    virtual                         ~TSPII_TcmIf();
    virtual void                    Reset();

    virtual void                    SetTcmMap(const TSPII_TcmMapRecord & theMap);
    virtual TSPII_TcmMapRecord*     GetTcmMap();

    // Indicate that TCM updates are complete
    virtual void                    CommitTcm();

    // -----------------------------------------------------------------------------------
    // Digital Wrapper Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32                  GetLTC();
    virtual uint32                  GetIAE();    
    virtual uint32                  GetBIAE();
    virtual int32                   GetTcmDelay();
    
    // -----------------------------------------------------------------------------------
    // Digital Wrapper Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                    ForceTCMIndication(CT_TCM_IndicationType theIndication);
    virtual void                    ForceBIAE(bool theEnable);
    virtual void                    SetTCMMode(CT_TCM_Mode theMode);
    virtual void                    SetAutoTCMIndication(CT_TCM_IndicationType theIndication,bool theEnable);
    virtual void                    SetTcmSsf(bool ssfActive);
    virtual void                    SetTcmDelayEnabled(bool theEnable);
    virtual void                    SetTcmOrder(CT_TCM_Order theTcmOrder);
    virtual void                    SetTcmLTCActEnabled(bool theEnable);
   
    virtual CT_TCM_IndicationType   GetForcedTCMIndication() const;
    virtual bool                    GetForcedBIAE() const;
    virtual CT_TCM_Mode             GetTCMMode();
    virtual bool                    GetAutoTCMIndication(CT_TCM_IndicationType theIndication);
    virtual bool                    GetTcmSsf() const;
    virtual bool                    GetTcmDelayEnabled() const;
    virtual CT_TCM_Order            GetTcmOrder();
    virtual bool                    GetTcmLTCActEnabled();
    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &             WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &             ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   &             WriteObject(ostream & theStream);
    virtual istream   &             ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                    Display(FC_Stream & theStream);
    virtual void                    Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                    Set(int argc, char ** argv);
    virtual bool                    Simul(int argc, char ** argv);


    void                    RefreshGet();
    void                    RefreshSet();

protected:

    TSPII_TcmMapRecord      itsTcmMapRecord;

    // Monitoring attributes
    uint32                  itsLTC;
    uint32                  itsIAE;    
    uint32                  itsBIAE;
    int32                   itsTcmDelay;
   
    // Configuration attributes
    CT_TCM_IndicationType   itsForcedTCMIndication;
    bool                    itsForcedBIAE;
    CT_TCM_Mode             itsTCMMode; 
    bool                    itsSsfActive;
    bool                    itsTcmDelayEnabled;
    bool                    itsTcmLTCActEnabled;
    CT_TCM_Order            itsTcmOrder;

    // for autoIndication
    bool                    itsAutoLTC;
    bool                    itsAutoIAE;
    bool                    itsAutoLCK;
    bool                    itsAutoOCI;
    bool                    itsAutoAIS;
    bool                    itsAutoBIAE;    
};	

#endif // _TSPII_TCMIF_H
