/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2004  Jai Harpalani
 DESCRIPTION:   XC configuration region interface
 LAST REVISION:
    Date    Description
    ----    -----------
  01-28-10  t71mr00117025:Add TRSPSAN and TRSPSAN2G SigTypes (for OTNM-
            supported GOPT facilities).
--------------------------------------------------------------------------*/

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_ConfigRegion_H
#define _INC_TSXC_ConfigRegion_H

#include <T6100_MainAppIf.h>
#include <T6100_ShelfIf.h>
#include <T6100_SlotIf.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <CommonTypes/CT_XcTypes.h>
#include <CommonTypes/CT_Protection.h>
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <XC/TSXC_CrossConnect.h>
#include <XC/TSXC_Connect.h>
#include <Blackboard/FC_BbRegionVectImp.h>
#include <XC/TSXC_BaseRegion.h>
#include <QRS/QRS_RequestTypes.h>


//------------------------------------------------------------------------------------------------------------------------
//--- This region is used to store CrossConnect configuration
//
//--- Note:  This region is always created without any objects since the number of objects it contains is based
//---        on the type of card which is sometimes unknown at time of region creation.  
//---        Objects are subsequently created within the SetMyCardType() method.
//------------------------------------------------------------------------------------------------------------------------
template <class T> class TSXC_ConfigRegion: public TSXC_BaseRegion<T>
{

public:

    //Constructor of Cross Connects region base.
    TSXC_ConfigRegion(const FC_BbKey theKey): TSXC_BaseRegion<T>(theKey)
    {
    }

    //--- Region destructor.
    //##ModelId=3C20B0B1030D
    virtual ~TSXC_ConfigRegion()
    {
    }

    //------------------------------------------------------------------------------------------------------------------------
    //----------------------------- Basic Connect/Disconnect API(s) -------------------------------
    //--- Create unidirectional connection from (IF,IFE) to (OF,OFE) for a contiguous set of channels.
    //------------------------------------------------------------------------------------------------------------------------
    void Connect(
                 uint8 IF,                   //--- Input Facility (1-based)
                 uint8 IFE,                  //--- Input Facility Endpoint (1-based)
                 uint8 OF,                   //--- Output Facility (1-based)
                 uint8 OFE,                  //--- Output Facility Endpoint (1-based)
                 CT_XC_ConnectType          ConnType,
                 CT_XC_ConnectMapping       ConnMapping); 

    //--- Delete unidirectional connection from to (OF,OFE) for a contiguous set of channels.
    void Disconnect(
                    uint8 OF,               //--- Output Facility
                    uint8 OFE,              //--- Output Facility Endpoint
                    CT_XC_ConnectType ConnType);

    //------------------------------------------------------------------------------------------------------------------------    
    //------ Connect/Disconnect API(s) used as helper methods and the signal protect of the smart cards --------
    //--- Create unidirectional connection from (IF,IFE) to (OF,OFE) for a contiguous or non-contiguous set of channels.
    //------------------------------------------------------------------------------------------------------------------------
    void Connect(       
                        uint8                       IF,
                        const CT_FAC_StsMap&        IFE,
                        uint8                        OF,
                        const CT_FAC_StsMap&        OFE,
                        const CT_XC_ConnectType&    ConnType,
                        const CT_XC_ConnectMapping& ConnMapping);

    //--- Delete unidirectional connection to (OF,OFE) for a contiguous or non-contiguous set of channels.
    void Disconnect(
                        uint8                       OF,                        
                        const CT_FAC_StsMap&        OFE,
                        const CT_XC_ConnectType&    ConnType);
    //------------------------------------------------------------------------------------------------------------------------
    //----- Connect/Disconnect API(s) used by APM/SPM Modules Agent Crossconnect request for Non SmartCards(RCMM)--------
    //--- Create a unidirectional connection from Input to Output for a contiguous set of channels.
    //------------------------------------------------------------------------------------------------------------------------
    void Connect(             
                        CT_XcFacData            Input,          //--- Source of connection
                        CT_XcFacData            Output,         //--- Destination of connection
                        CT_XC_ConnectType       ConnType,       //--- Connection Type
                        CT_XC_ConnectMapping    ConnMapping);   //--- Connection mapping
    
    //--- Delete a unidirectional connection from Input to Output for a contiguous set of channels.
    void Disconnect(                 
                        CT_XcFacData            Input,          //--- Source of connection (unused for disconnect)
                        CT_XcFacData            Output,         //--- Destination of connection
                        CT_XC_ConnectType       ConnType);      //--- Connection Type
    
    //------------------------------------------------------------------------------------------------------------------------   
    //--------------------- Connect/Disconnect API(s) used by the agent for the SD/UD modules --------------------------   
    //--- Create a bidirectional connection between Port and Line for a contiguous or non-contiguous set of channels.
    //------------------------------------------------------------------------------------------------------------------------   
    void Connect(       
                        uint8                   Port,           //--- Port facility number (0-9)
                        CT_TEL_SignalType       SignalType,     //--- Port facility signal type
                        CT_FAC_StsMap           StsMap,         //--- Map of which line-side STSs are being connected to
                        CT_TEL_TermSize         TermSize);      //--- for the data connection size as STS1 or STS3C
    
    //--- Delete a bidirectional connection between Port and Line for a contiguous or non-contiguous set of channels.
    void Disconnect(
                        uint8                   Port,           //--- Port facility number (0-9)
                        CT_TEL_SignalType       SignalType,     //--- Port facility signal type
                        CT_FAC_StsMap           StsMap,         //--- Map of which line-side STSs are being connected to
                        CT_TEL_TermSize         TermSize);      //--- Data Connection size as STS1 or STS3C

    //------------------------------------------------------------------------------------------------------------------------   
    bool IsConnectActive(
                         uint8 IF, uint8 IFE, 
                         CT_XC_ConnectType ConnType);

    //--------------------- Atomic Operations used by the agent CQM for SSM  --------------------------   
    //------------------------------------------------------------------------------------------------------------------------   

    //--- Create a unidirectional connection from Imux to Destination for a contiguous or non-contiguous set of channels.
    void ConnectImuxToDst(       
                        QRS_ConnectXcTerm&      Dst,            //--- Destination (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            theRespId = NULL,
                        bool                    theImmediateCommit = true);
    
    //--- Create a unidirectional connection from Source to Imux for a contiguous or non-contiguous set of channels.
    void ConnectSrcToImux(       
                        QRS_ConnectXcTerm&      Src,            //--- Source (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            theRespId = NULL,
                        bool                    theImmediateCommit = true);

    //--- Delete a unidirectional connection from Imux to Destination for a contiguous or non-contiguous set of channels.
    void DisconnectImuxToDst(
                        QRS_ConnectXcTerm&      Dst,            //--- Destination (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            theRespId = NULL,
                        bool                    theImmediateCommit = true);

    //--- Delete a unidirectional connection from Source to Imux for a contiguous or non-contiguous set of channels.
    void DisconnectSrcToImux(       
                        QRS_ConnectXcTerm&      Src,            //--- Source (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            theRespId = NULL,
                        bool                    theImmediateCommit = true);

    //------------------------------------------------------------------------------------------------------------------------   
            
    //--------------------------------------------- Helper functions ---------------------------------------------------------   
    void GetFacilityIdFromIntfId(uint8 * theFacility, CT_IntfId theIntfId); 
    void GetFacilityIdFromAGPortId(uint8 * theFacility, CT_AG_PortId theAGPortId); 
    void GetFacilityIdFromPortNum(uint8 * theFacility, uint8 thePortNum);
    CT_IntfId ConvertAGPort2IntfId(CT_AG_PortId theAGPortId);
    void GetConnTypeFromSigType(CT_XC_ConnectType* theConnType, CT_TEL_SignalType theSignalType, CT_TEL_TermSize theTermSize);

    uint8 FrmXc_Ssm40FrontEndDevToFac(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev);
    uint8 FrmXc_Ssm40FrontEndDevToFacEndpt(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev);
    uint8 OduXc_Ssm40FrontEndDevToFac(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev);
    uint8 OduXc_Ssm40FrontEndDevToFacEndpt(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev, uint8 theChan);

    void ResetFgsmMux();
    uint8 OduXc_FgsmFrontEndDevToFac(CT_TEL_FgsmOduDevice firstOdu, CT_TEL_FgsmOduDevice secondOdu, uint8* IF, uint8* OF);

    void ResetOsm20FrameAndMux();
    bool FrmXc_Osm20FrontEndDevToFac(CT_TEL_HyphyFlexFrontEndDevice theOsm20FrontEndDev, uint8* IF, uint8* IFE);
    bool FrmXc_Osm20DevPortToFac(uint8 devicePort, uint8 deviceChannel, uint8* IF, uint8* IFE);
    uint8 OduXc_Osm20FrontEndDevToFac(CT_TEL_HyphyFlexFrontEndDevice firstOdu, CT_TEL_HyphyFlexFrontEndDevice secondOdu, 
                                      uint8* IF, uint8* OF, bool secondOduIsOduF);

    void ResetHgtmmFrameAndMux();

    void ResetHdtg2FrameAndMux();

    void ResetOmmxFrameAndMux();
    bool FrmXc_OmmxFrontEndDevToFac(CT_TEL_HyphyAxsFrontEndDevice theOmmxFrontEndDev, uint8* IF, uint8* IFE);
    bool FrmXc_OmmxDevPortToFac(uint8 devicePort, uint8 deviceChannel, uint8* IF, uint8* IFE);
    uint8 OduXc_OmmxFrontEndDevToFac(CT_TEL_HyphyAxsFrontEndDevice firstOdu, CT_TEL_HyphyAxsFrontEndDevice secondOdu, 
                                     uint8* IF, uint8* OF, bool secondOduIsOduF);

    uint8 OduIdToFac(CT_ODU_Identifier& theOduId);
    uint8 OduIdToFacEndpt(CT_ODU_Identifier& theOduId);
    uint8 GetInputFacilityFromDst(CT_XcTerm& theDstTerm);
    TSXC_Connect* GetConnection(uint8 OF, uint8 OFE);
    bool IsConnectedAsOutput(uint8 OF, uint8 OFE);

protected:
    virtual void          PopulateUnknown();
    virtual void          PopulateFGTMM();
    virtual void          PopulateSSM();
    virtual void          PopulateSPFAB();
    virtual void          PopulateSMTMU();
    virtual void          PopulateSMTMUDSD();
    virtual void          PopulateOTNM();
    virtual void          PopulateRCMM();
    virtual void          PopulateDCMM();
    virtual void          PopulateNANOCCM();
    virtual void          PopulateCADM();
    virtual void          PopulateSSM40();
    virtual void          PopulateOSM40();
    virtual void          PopulateHDTG();
    virtual void          PopulateHDTG2();
    virtual void          PopulateFGSM();
    virtual void          PopulateOSM20();
    virtual void          PopulateOMMX();
    virtual void      	  PopulateHGTMM();
    virtual void      	  PopulateOSM();
    virtual void      	  PopulateOSM1S();

private:
    //--- Sets following facilities based on type
    void SetConcatanated(int FacilityOffset, CT_XC_ConnectState ClearState);
    bool FindValidOffset(uint8 IF,uint8 IFE,uint8 OF,uint8 OFE,int* FacilityOffsetPtr);
    void AddConnection(TSXC_Connect& Connection);
    void DeleteConnection(TSXC_Connect& Connection);
    
};

//------------------------------------------------------------------------------------------------------------------------
//--- This method connects Input Facility to Output Facility. It currently does minimal validation.
//--- Examples: Connect(9,1,1,1,CT_XC_TYPE_STS12C,CT_XC_MAPPING_FLEXIBLE)
//--- This will be a connection from DWDM Lineside to Port 1 on chanel 1.
//--- This interface method is one based. Zero is considered invalid.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Connect(
                                            uint8 IF, uint8 IFE, uint8 OF, uint8 OFE,
                                            CT_XC_ConnectType           ConnType,
                                            CT_XC_ConnectMapping        ConnMapping)
{
    int FacilityOffset = 0;
    bool ValidData;

    //--- Get the Starting facility offset into the region.
    ValidData = FindValidOffset(IF, IFE, OF, OFE, &FacilityOffset);
    
    //--- If a valid Facility then go ahead and set the connection.
    if(ValidData)
    {
        (*this)[FacilityOffset+OFE-1].SetInputFacility(IF);
        (*this)[FacilityOffset+OFE-1].SetInputFacilityEndpoint(IFE);
        (*this)[FacilityOffset+OFE-1].SetType(ConnType);
        (*this)[FacilityOffset+OFE-1].SetMapping(ConnMapping);
        (*this)[FacilityOffset+OFE-1].SetState(CT_XC_STATE_CONNECTED);
    
        //Now fill in the CT_XC_STATE_CONCATANATED ones
        SetConcatanated(FacilityOffset+OFE-1, CT_XC_STATE_CONNECTED);

        (*this).IncModificationCounter();
    }
}

//------------------------------------------------------------------------------------------------------------------------
//--- This method disconnects an Output Facility by changing the state. It currently performs minimal validation.
//--- This interface method is one based. Zero is considered invalid.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Disconnect(
                                                uint8 OF, uint8 OFE, 
                                                CT_XC_ConnectType ConnType)
{
    int FacilityOffset = 0;
    bool ValidData;

    //--- Any valid number for IF / IFE will work for disconnect since
    //--- we do not care about inputs on a disconnect.
    ValidData = FindValidOffset(1, 1, OF, OFE, &FacilityOffset);
     
    //--- If a valid Facility then go ahead and set the connection.
    if(ValidData)
    {
        (*this)[FacilityOffset+OFE-1].SetState(CT_XC_STATE_NOTCONNECTED);
        
        //--- Now find all the CT_XC_STATE_CONCATANATED and disconnect them.
        SetConcatanated(FacilityOffset+OFE-1, CT_XC_STATE_NOTCONNECTED);

        (*this).IncModificationCounter();
    }
}

//--------- Connect/Disconnect used as helper methods and the signal protect of the smart cards --------------
//------------------------------------------------------------------------------------------------------------------------
//--- Create unidirectional connection from (IF,IFE) to (OF,OFE) for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Connect(   
                                    uint8                       IF,
                                    const CT_FAC_StsMap&        IFE,
                                    uint8                       OF,
                                    const CT_FAC_StsMap&        OFE,
                                    const CT_XC_ConnectType&    ConnType,
                                    const CT_XC_ConnectMapping& ConnMapping)
{
    int     anInputChannel;
    int     anOutputChannel;
    int8    aNumInputChannels;
    int8    aNumOutputChannels;
    CT_XC_ConnectType conCatType;

    //--- Count number of Input and Output Channels
    aNumInputChannels  = IFE.CountSts();
    aNumOutputChannels = OFE.CountSts();
 
    //--- If no Input Channels exist or no Output Channels exist, or
    //--- the number of Input Channels is not equal to the number
    //--- of Output Channels, then agent is in the process of setting a connection
    if ( (aNumInputChannels  == 0) ||
         (aNumOutputChannels == 0) ||
         (aNumInputChannels != aNumOutputChannels) )
    {
        //No error is reported because agent may be in processing a connection. 
    }
    //--- Else parameters are good so continue processing.
    else
    {
        //--- Find the first input and output channel.
        anInputChannel  = IFE.FindLowestInUseSts();
        anOutputChannel = OFE.FindLowestInUseSts();

        //--- Connect the first input to output channel using specified ConnType.
        Connect(IF, anInputChannel + 1, OF, anOutputChannel + 1, ConnType, ConnMapping);

        switch(ConnType)
        {
            case CT_XC_TYPE_OPTD1M:
            case CT_XC_TYPE_STS1D:
            case CT_XC_TYPE_STS1C22V:
                conCatType = CT_XC_TYPE_STS1D;
                while (--aNumInputChannels > 0)
                {
                    //--- Find the next Input and Output Channels.
                    anInputChannel  = IFE.FindLowestInUseSts(anInputChannel + 1);
                    anOutputChannel = OFE.FindLowestInUseSts(anOutputChannel + 1);
                    Connect(IF, anInputChannel + 1, OF, anOutputChannel + 1, conCatType, ConnMapping);
                }                
                break;
            case CT_XC_TYPE_OPTD3M:
            case CT_XC_TYPE_STS3CD:
                conCatType = CT_XC_TYPE_STS3CD;
                while (--aNumInputChannels > 0)
                {
                    //--- Find the next Input and Output Channels.
                    anInputChannel  = IFE.FindLowestInUseSts(anInputChannel + 3);
                    anOutputChannel = OFE.FindLowestInUseSts(anOutputChannel + 3);
                    Connect(IF, anInputChannel + 1, OF, anOutputChannel + 1, conCatType, ConnMapping);
                }                
                break;
             default:
                //--- for all other conection types the subsequent channels are set as CT_XC_TYPE_CONCATANATED
                //--- by the very first connect function above. The number of channels is based on the connType.
                break;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------
//--- Delete unidirectional connection to (OF,OFE) for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Disconnect(
                                     uint8                       OF,  
                                     const CT_FAC_StsMap&        OFE, 
                                     const CT_XC_ConnectType&    ConnType)
{
    int8   aNumOutputChannels;
    uint8  anOutputChannel;
    
    //--- Count number of Input and Output Channels
    aNumOutputChannels = OFE.CountSts();
 
    //--- If no Output Channels exist, something is wrong.
    if (aNumOutputChannels  == 0)
    {
        //--- Error
    }
    //--- Else parameters are good so continue processing.
    else
    {
        //--- Find the first output channel.
        anOutputChannel = OFE.FindLowestInUseSts();

        //--- Disconnect the first output channel using specified ConnType.
        Disconnect(OF, anOutputChannel + 1, ConnType);

        //--- While there are still channels to disonnect,
        while (--aNumOutputChannels > 0)
        {
            //--- Find the next Output Channel.
            anOutputChannel = OFE.FindLowestInUseSts(anOutputChannel + 1);

            //--- Disconnect this output channel using Concatenated as the type.
            //--- All channels after the first are concatenated.
            Disconnect(OF, anOutputChannel + 1, CT_XC_TYPE_CONCATANATED);
        }
    }
}
    
//------------------------------------------------------------------------------------------------------------------------
//--- This method sets the following facilities based on type. Only set the objects state for the following connection.
//--- So it is 1 less what you might expect.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::SetConcatanated(int FacilityOffset, CT_XC_ConnectState SetState)
{
    int i;
    int Concatanated = 0;
    uint8 InitialFacility = 0;
    uint8 InitialFacilityEndpoint = 0;
    CT_XC_ConnectMapping InitialMapping = CT_XC_MAPPING_UNSPECIFIED;
    int maxXc;
    CT_XC_ConnectType connType;
    
    connType = (*this)[FacilityOffset].GetType();
    
    //--- Try and decide how many Facility Endpoints need filling in.
    switch(connType)
    {
        case CT_XC_TYPE_STS1:
        case CT_XC_TYPE_LAMBDA:
        case CT_XC_TYPE_STS1D:
        case CT_XC_TYPE_OPTD1M:
        case CT_XC_TYPE_STS1C22V:
        case CT_XC_TYPE_ODUF:
        case CT_XC_TYPE_ODU0:
        case CT_XC_TYPE_ODU1:
        case CT_XC_TYPE_ODU2:
        case CT_XC_TYPE_ODU2E:
        case CT_XC_TYPE_ODU3:
        case CT_XC_TYPE_ODU4:
            //--- Do nothing
            Concatanated = 0;
            break;
        case CT_XC_TYPE_STS3C:
        case CT_XC_TYPE_OC3M:
        case CT_XC_TYPE_STS3T:
        case CT_XC_TYPE_STS3CD:
        case CT_XC_TYPE_OPTD3M:
            //--- Set 2
            Concatanated = 2;     
            break;
        case CT_XC_TYPE_STS12C:
        case CT_XC_TYPE_OC12M:
        case CT_XC_TYPE_STS12T:
            //--- Set 11
            Concatanated = 11; 
            break;
        case CT_XC_TYPE_STS48C:
        case CT_XC_TYPE_OC48M:
        case CT_XC_TYPE_STS48T:
            //--- Set 47
            Concatanated = 47;
            break;
        case CT_XC_TYPE_STS192C:
        case CT_XC_TYPE_OC192M:
        case CT_XC_TYPE_OCHM:
            //--- Set 191
            Concatanated = 191;
            break;
        default:
            break;
    }

    InitialFacility = (*this)[FacilityOffset].GetInputFacility();
    InitialFacilityEndpoint = (*this)[FacilityOffset].GetInputFacilityEndpoint();
    InitialMapping = (*this)[FacilityOffset].GetMapping();

    switch(this->myCardType)
    {
        case CARD_TYPE_SMTMU:
            maxXc = XC_MAX_XC_SMTMU;
            break;
        case CARD_TYPE_SMTMUD:
        case CARD_TYPE_SMTMSD:
            maxXc = XC_MAX_XC_SMTMUDSD;
            break;
        case CARD_TYPE_OTNMX:
        case CARD_TYPE_OTNMD:
            maxXc = XC_MAX_XC_OTNM;
            break;
        case CARD_TYPE_SSMX:
        case CARD_TYPE_SSMD:
            maxXc = XC_MAX_XC_SSM;
            break;            
        case CARD_TYPE_SPFAB:
            maxXc = XC_MAX_XC_SPFAB;
            break;
        case CARD_TYPE_OSM40:
        case CARD_TYPE_SSM40:
            maxXc = XC_MAX_XC_SSM40;
            break;
        case CARD_TYPE_FGSM:
            maxXc = XC_MAX_XC_FGSM;
            break;
        case CARD_TYPE_OSM20:
            maxXc = XC_MAX_XC_OSM20;
            break;
        case CARD_TYPE_OMMX:
            maxXc = XC_MAX_XC_OMMX;
            break;
        default:
            maxXc = 0;
    }

    //--- This additional check prevents us from writing beyond the region space.
    for (i = 1; (i <= Concatanated) && ((FacilityOffset+i) < maxXc); i++)
    {
        //--- Set the passed in state Connected or disconnected.
        (*this)[FacilityOffset+i].SetState(SetState);
        
        //--- Everything is concatenated.
        (*this)[FacilityOffset+i].SetType(CT_XC_TYPE_CONCATANATED);

        //--- This stuff is duplicated from the initial object.

        (*this)[FacilityOffset+i].SetInputFacility(InitialFacility);
        (*this)[FacilityOffset+i].SetMapping(InitialMapping);

        //--- Add i to the initial facility Endpoint, while the Facility stays the same.
        (*this)[FacilityOffset+i].SetInputFacilityEndpoint(InitialFacilityEndpoint+i);
    }
}

//------------------------------------------------------------------------------------------------------------------------
//--- This method connects Input to Output. Agent Crossconnect request for Non SmartCards(RCMM).
//--- Create a unidirectional connection from Input to Output for a contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Connect( 
                        CT_XcFacData            Input,          //--- Source of connection
                        CT_XcFacData            Output,         //--- Destination of connection
                        CT_XC_ConnectType       ConnType,       //--- Connection Type
                        CT_XC_ConnectMapping    ConnMapping)    //--- Connection mapping
{   
    uint8         IF;
    uint8         IFE;
    uint8         OF;
    uint8         OFE;
    int           FacilityOffset;
    bool          ValidData;
    TSXC_Connect  connection;

    //--- Convert from CommonTypes
    GetFacilityIdFromIntfId(&IF, Input.GetIntfId());
    GetFacilityIdFromIntfId(&OF, Output.GetIntfId());
    IFE = Input.GetWavelength().WavelengthIndex();
    OFE = Output.GetWavelength().WavelengthIndex();

    //--- Increment to make 1-based
    IFE++;
    OFE++;

    //--- Get the Starting facility offset into the region.
    ValidData = FindValidOffset(IF, IFE, OF, OFE, &FacilityOffset);

    if (ValidData == true)
    {
        connection.SetInputFacility(IF);
        connection.SetInputFacilityEndpoint(IFE);
        connection.SetOutputFacility(OF);
        connection.SetOutputFacilityEndpoint(OFE);
        connection.SetType(ConnType);
        connection.SetMapping(ConnMapping);
        connection.SetState(CT_XC_STATE_CONNECTED);

        AddConnection(connection);
    
        (*this).IncModificationCounter();
    }
}

//------------------------------------------------------------------------------------------------------------------------
//--- Delete a unidirectional connection from Input to Output for a contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Disconnect(
                        CT_XcFacData            Input,          //--- Source of connection (unused for disconnect)
                        CT_XcFacData            Output,         //--- Destination of connection
                        CT_XC_ConnectType       ConnType)       //--- Connection Type
{
    uint8         OF;
    uint8         OFE;
    int           FacilityOffset = 0;
    bool          ValidData;
    TSXC_Connect  connection;

    //--- Convert from CommonTypes
    GetFacilityIdFromIntfId(&OF, Output.GetIntfId());
    OFE = Output.GetWavelength().WavelengthIndex();

    //--- Increment to make 1-based
    OFE++;

    //--- Any valid number for IF / IFE will work for disconnect since
    //--- we do not care about inputs on a disconnect.
    ValidData = FindValidOffset(1, 1, OF, OFE, &FacilityOffset);
     
    //--- If a valid Facility then go ahead and set the connection.
    if(ValidData)
    {
        connection.SetOutputFacility(OF);
        connection.SetOutputFacilityEndpoint(OFE);
    
        DeleteConnection(connection);

        (*this).IncModificationCounter();
    }
}

//------------------------------------------------------------------------------------------------------------------------
//--- Create a bidirectional connection between Port and Line for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
//--- This method connects an SMTM-M/UD/SD Port Facility to DWDM Facility connection.
//--- It is provided for Agent Facility to set up cross-connects on the SMTM-M/UD/SD which
//--- views connections as facility mappings instead of STS-level connections.
//--- Note: this method is also shared with the OTNM for setting up the Bachelor 192x192 cross connect
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Connect(       
                        uint8                   Port,           //--- Port facility number (0-9)
                        CT_TEL_SignalType       SignalType,     //--- Port facility signal type
                        CT_FAC_StsMap           StsMap,         //--- Map of which line-side STSs are being connected to
                        CT_TEL_TermSize         TermSize)       //--- for the data connection size as STS1 or STS3C
{

    uint8 DWDM_Facility;
    uint8 DWDM_FacilityEndpoint;
    uint8 Port_Facility;
    uint8 Port_FacilityEndpoint;
    CT_XC_ConnectType  ConnType;
    CT_CardType  aCardType;
    bool  found;
    uint16 maxDWDMConns;
    
    GetConnTypeFromSigType(&ConnType, SignalType, TermSize);
    GetFacilityIdFromPortNum(&Port_Facility, Port);
    aCardType = this->GetMyCardType();
    
    //--- Determine values for SMTMU (or OTNM) transparent type specific parameters
    if ((aCardType == CARD_TYPE_SMTMUD) || (aCardType == CARD_TYPE_SMTMSD))
    {
        DWDM_Facility = XC_SMTMUDSD_DWDM_FACILITY_ID;
        maxDWDMConns  = XC_MAX_XC_SMTMUDSD_DWDM;
    }
    else if ((aCardType == CARD_TYPE_OTNMX) || (aCardType == CARD_TYPE_OTNMD))
    {
        DWDM_Facility = XC_OTNM_OC192_FACILITY_ID;
        maxDWDMConns  = XC_MAX_XC_OTNM_OC192;
    }
    else
    {
        char aErrMsg[100];
        sprintf(aErrMsg, "Invalid aCardType = %d", aCardType);
        FC_REPORT_ERROR(FC_LogicError, aErrMsg);
        return;
    }

    //--- Always start at channel 1 of port-side facility
    Port_FacilityEndpoint = 1;

    //--- If this is a Data Connection, special processing is
    //--- necessary since a variable number of channels can make up a Data Connection.
    
    if ((ConnType == CT_XC_TYPE_STS1C22V) || (ConnType == CT_XC_TYPE_STS1D)) 
    {
        for (DWDM_FacilityEndpoint = 0; (DWDM_FacilityEndpoint < maxDWDMConns); DWDM_FacilityEndpoint++)
        {
            //--- If StsMap indicates that this DWDM endpoint is connected, set up a bidirectional
            //--- connection between the port-side and DWDM for this endpoint.
            //
            //--- Note that one STS1 connection will be created for each connected channel in StsMap.
            //
            
            if (StsMap.IsInUse(DWDM_FacilityEndpoint) == true)
            {
                Connect(Port_Facility, Port_FacilityEndpoint,       //--- Source is port-side
                        DWDM_Facility, DWDM_FacilityEndpoint + 1,   //--- Dest is DWDM-side
                        CT_XC_TYPE_STS1D, CT_XC_MAPPING_FIXED);     //--- FIXED Mapping (no protection on SMTM-M/UD/SD)

                Connect(DWDM_Facility, DWDM_FacilityEndpoint + 1,   //--- Source is DWDM-side
                        Port_Facility, Port_FacilityEndpoint,       //--- Dest is port-side
                        CT_XC_TYPE_STS1D, CT_XC_MAPPING_FIXED);     //--- FIXED Mapping (no protection on SMTM-M/UD/SD)

                //--- Increment port facility endpoint only when connection is made.
                Port_FacilityEndpoint++;
            }
        }
    }
    else if (ConnType == CT_XC_TYPE_STS3CD)     //--- Data connection with STS3C type 
    {
        for (DWDM_FacilityEndpoint = 0; (DWDM_FacilityEndpoint < maxDWDMConns); DWDM_FacilityEndpoint+=3)
        {
            //--- If StsMap indicates that this DWDM endpoint is connected, set up a bidirectional
            //--- connection between the port-side and DWDM for this endpoint.
            //
            //--- Note that one STS3C connection will be created for each connected channel in StsMap.
            
            if (StsMap.IsInUse(DWDM_FacilityEndpoint) == true)
            {
                Connect(Port_Facility, Port_FacilityEndpoint,       //--- Source is port-side
                        DWDM_Facility, DWDM_FacilityEndpoint + 1,   //--- Dest is DWDM-side
                        CT_XC_TYPE_STS3CD, CT_XC_MAPPING_FIXED);    //--- FIXED Mapping (no protection on SMTM-M/UD/SD)

                Connect(DWDM_Facility, DWDM_FacilityEndpoint + 1,   //--- Source is DWDM-side
                        Port_Facility, Port_FacilityEndpoint,       //--- Dest is port-side
                        CT_XC_TYPE_STS3CD, CT_XC_MAPPING_FIXED);    //--- FIXED Mapping (no protection on SMTM-M/UD/SD)
                //--- the above connect function will also set the next two consecutive channels as concatenation. 
                //--- Increment port facility endpoint only when connection is made.
                Port_FacilityEndpoint +=3;
            }
        }        
    }
    //--- SONET Connections contain a fixed number of contiguous channels
    //--- Note: If the ConnType is not specified then do nothing.
    
    else if (CT_XC_TYPE_UNSPECIFIED != ConnType)
    {
        for (DWDM_FacilityEndpoint = 0, found = false; 
            (DWDM_FacilityEndpoint < maxDWDMConns) && (found == false); 
             DWDM_FacilityEndpoint++)
        {
            //--- If StsMap indicates that this DWDM endpoint is connected, set up a bidirectional 
            //--- connection between the port-side and DWDM for this endpoint.
            //
            //--- Assumption is made that channels are consecutive on both DWDM and port-side.
            
            if (StsMap.IsInUse(DWDM_FacilityEndpoint) == true)
            {
                Connect(Port_Facility, Port_FacilityEndpoint,       //--- Source is port-side
                        DWDM_Facility, DWDM_FacilityEndpoint + 1,   //--- Dest is DWDM-side
                        ConnType,      CT_XC_MAPPING_FIXED);        //--- FIXED Mapping (no protection on SMTM-M/UD/SD)

                Connect(DWDM_Facility, DWDM_FacilityEndpoint + 1,   //--- Source is DWDM-side
                        Port_Facility, Port_FacilityEndpoint,       //--- Dest is port-side
                        ConnType,      CT_XC_MAPPING_FIXED);        //--- FIXED Mapping (no protection on SMTM-M/UD/SD)

                found = true;
            }
        }
    }   
}

//------------------------------------------------------------------------------------------------------------------------  
//--- Delete a bidirectional connection between Port and Line for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::Disconnect(
                        uint8                   Port,           //--- Port facility number (0-9)
                        CT_TEL_SignalType       SignalType,     //--- Port facility signal type
                        CT_FAC_StsMap           StsMap,         //--- Map of which line-side STSs are being connected to
                        CT_TEL_TermSize         TermSize)       //--- Data Connection size as STS1 or STS3C
{
//////////////////////////////////////////////////////////////////
//--- This method disconnects an SMTM-M/UD/SD Port Facility to DWDM Facility connection.
//--- It is provided for Agent Facility to delete cross-connects on the SMTM-M/UD/SD which
//--- views connections as facility mappings instead of STS-level connections.
//--- Note: this method is also shared with the OTNM for setting up the Bachelor 192x192 cross connect
//////////////////////////////////////////////////////////////////
    uint8 DWDM_Facility;
    uint8 DWDM_FacilityEndpoint;
    uint8 Port_Facility;
    uint8 Port_FacilityEndpoint;
    CT_XC_ConnectType  ConnType;
    CT_CardType  aCardType;
    bool  found;
    uint16 maxDWDMConns;
    
    //--- Determine connection parameters
    GetConnTypeFromSigType(&ConnType, SignalType, TermSize);
    GetFacilityIdFromPortNum(&Port_Facility, Port);
    aCardType = this->GetMyCardType();
    
    //--- Determine values for SMTMU (or OTNM) transparent -type specific parameters
    if ((aCardType == CARD_TYPE_SMTMUD) || (aCardType == CARD_TYPE_SMTMSD))
    {
        DWDM_Facility = XC_SMTMUDSD_DWDM_FACILITY_ID;
        maxDWDMConns  = XC_MAX_XC_SMTMUDSD_DWDM;
    }
    else if ((aCardType == CARD_TYPE_OTNMX) || (aCardType == CARD_TYPE_OTNMD))
    {
        DWDM_Facility = XC_OTNM_OC192_FACILITY_ID;
        maxDWDMConns  = XC_MAX_XC_OTNM_OC192;
    }
    else
    {
        char aErrMsg[100];
        sprintf(aErrMsg, "Invalid aCardType = %d", aCardType);
        FC_REPORT_ERROR(FC_LogicError, aErrMsg);
        return;
    }


    //--- Always start at channel 1 of port-side facility
    Port_FacilityEndpoint = 1;

    //--- If this is a GBE Connection, special processing is
    //--- necessary since a variable number of channels can  make up the GBE Connection.    
    
    if ((ConnType == CT_XC_TYPE_STS1C22V) || (ConnType == CT_XC_TYPE_STS1D) ) 
    {
        for (DWDM_FacilityEndpoint = 0; (DWDM_FacilityEndpoint < maxDWDMConns); DWDM_FacilityEndpoint++)
        {
            //--- If StsMap indicates that this DWDM endpoint is connected, delete bidirectional 
            //--- connection between the port-side and DWDM for this endpoint.
            
            if (StsMap.IsInUse(DWDM_FacilityEndpoint) == true)
            {
                Disconnect(DWDM_Facility,               //--- Dest is DWDM-side
                           DWDM_FacilityEndpoint + 1,  
                           CT_XC_TYPE_STS1D);      

                Disconnect(Port_Facility,               //--- Dest is port-side
                           Port_FacilityEndpoint, 
                           CT_XC_TYPE_STS1D);      

                //--- Increment port facility endpoint only when connection is made.
                Port_FacilityEndpoint++;
            }
        }
    }
    else if (ConnType == CT_XC_TYPE_STS3CD)  //--- Data conection with STS3C type
    {
        for (DWDM_FacilityEndpoint = 0; (DWDM_FacilityEndpoint < maxDWDMConns); DWDM_FacilityEndpoint+=3)
        {
            //--- If StsMap indicates that this DWDM endpoint is
            //--- connected, delete bidirectional connection between
            //--- the port-side and DWDM for this endpoint.
            if (StsMap.IsInUse(DWDM_FacilityEndpoint) == true)
            {
                Disconnect(DWDM_Facility,               //--- Dest is DWDM-side
                           DWDM_FacilityEndpoint + 1,  
                           CT_XC_TYPE_STS3CD);      

                Disconnect(Port_Facility,               //--- Dest is port-side
                           Port_FacilityEndpoint, 
                           CT_XC_TYPE_STS3CD);      

                //--- Increment port facility endpoint only when connection is made.
                Port_FacilityEndpoint+=3;
            }
        }        
    }
    //--- SONET Connections contain a fixed number of contiguous channels
    //--- Note: If the ConnType is not specified then do nothing.
    else if (CT_XC_TYPE_UNSPECIFIED != ConnType)
    {
        for (DWDM_FacilityEndpoint = 0, found = false; 
            (DWDM_FacilityEndpoint < maxDWDMConns) && (found == false); 
             DWDM_FacilityEndpoint++)
        {
            //--- If StsMap indicates that this DWDM endpoint is connected, delete bidirectional 
            //--- connection between the port-side and DWDM for this endpoint.
            //
            //--- Assumption is made that channels are consecutive on both DWDM and port-side.
            
            if (StsMap.IsInUse(DWDM_FacilityEndpoint) == true)
            {
                Disconnect(DWDM_Facility,               //--- Dest is DWDM-side
                           DWDM_FacilityEndpoint + 1,  
                           ConnType);        

                Disconnect(Port_Facility,               //--- Dest is DWDM-side
                           Port_FacilityEndpoint,     
                           ConnType);       

                found = true;
            }
        }
    }
}

// IsConnectActive
template<class T> bool TSXC_ConfigRegion<T>::IsConnectActive(
                                                uint8 IF, uint8 IFE, 
                                                CT_XC_ConnectType ConnType)
{
    bbindex_t         index;

    for(index = 0; index < (int) (*this).Size(); index++)
    {
        if ( ((*this)[index].GetState() == CT_XC_STATE_CONNECTED) &&
             ((*this)[index].GetType() == ConnType) &&
             ((*this)[index].GetInputFacility() == IF) &&
             ((*this)[index].GetInputFacilityEndpoint() == IFE ))
        {
            return true;
        }
    }

    return false;
    
}

//------------------------------------------------------------------------------------------------------------------------  
//--- Create a unidirectional connection from Imux to Destination for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ConnectImuxToDst(
                        QRS_ConnectXcTerm&      Dst,            //--- Destination (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            RespId,
                        bool                    ImmediateCommit)
{
    uint8           srcFac;
    CT_FAC_StsMap   srcFacStsMap;
    uint8           dstFac;
    CT_FAC_StsMap   dstFacStsMap;

    // Set Source Info
    if (Dst.TermMappedToImuxl == true)
    {
        //srcFacStsMap = Dst.ImuxLineMapIngress;
        srcFacStsMap = Dst.ImuxLineMapEgress;
        GetFacilityIdFromIntfId(&srcFac, CT_LINE_SIDE_3);
    }
    else if (Dst.TermMappedToImuxp == true)
    {
        //srcFacStsMap = Dst.ImuxPortMapIngress;
        srcFacStsMap = Dst.ImuxPortMapEgress;
        GetFacilityIdFromIntfId(&srcFac, CT_LINE_SIDE_4);
    }
    else 
    {
        FC_THROW_ERROR(FC_NotSupportedError, "Dst must be mapped to either Imuxl/Imuxp");
        return;
    }

    // Set Destination Info
    GetFacilityIdFromAGPortId(&dstFac, Dst.FacData.GetPortId()); 
    dstFacStsMap = Dst.FacStsMap;

    // Create connection from Source to Destination
    Connect(srcFac, srcFacStsMap, dstFac, dstFacStsMap, ConnType, CT_XC_MAPPING_FIXED);   

    this->SetRespIdAndCommit(RespId, ImmediateCommit);
}

//------------------------------------------------------------------------------------------------------------------------  
//--- Create a unidirectional connection from Source to Imux for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ConnectSrcToImux(
                        QRS_ConnectXcTerm&      Src,            //--- Destination (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            RespId,
                        bool                    ImmediateCommit)
{
    uint8                 srcFac;
    CT_FAC_StsMap         srcFacStsMap;
    uint8                 dstFac;
    CT_FAC_StsMap         dstFacStsMap;
    CT_XC_ConnectMapping  connMapping;

    // Set Source Info
    GetFacilityIdFromAGPortId(&srcFac, Src.FacData.GetPortId()); 
    srcFacStsMap = Src.FacStsMap;

    // Set Destination Info
    if (Src.TermMappedToImuxl == true)
    {
        dstFacStsMap = Src.ImuxLineMapIngress;        
        GetFacilityIdFromIntfId(&dstFac, CT_LINE_SIDE_3);
    }
    else if (Src.TermMappedToImuxp == true)
    {
        dstFacStsMap = Src.ImuxPortMapIngress;
        GetFacilityIdFromIntfId(&dstFac, CT_LINE_SIDE_4);
    }
    else 
    {
        FC_THROW_ERROR(FC_NotSupportedError, "Src must be mapped to either Imuxl/Imuxp");
        return;
    }

    // On SSM/OSM40/FGSM/OSM20, the connection mapping to the Imux is stored in the src term
    connMapping = CT_XC_MAPPING_FIXED;
    if ( (this->myCardType == CARD_TYPE_SSMX)  || 
         (this->myCardType == CARD_TYPE_SSMD)  ||
         (this->myCardType == CARD_TYPE_OSM40) ||
         (this->myCardType == CARD_TYPE_SSM40) ||
         (this->myCardType == CARD_TYPE_FGSM)  ||
         (this->myCardType == CARD_TYPE_OSM20) ||
         this->myCardType == CARD_TYPE_OSM2S   ||
         this->myCardType == CARD_TYPE_OSM2C   ||
         this->myCardType == CARD_TYPE_OSM1S )
    {
        connMapping = Src.TermToImuxConnMapping;
    }

    // Create connection from Source to Destination
    Connect(srcFac, srcFacStsMap, dstFac, dstFacStsMap, ConnType, connMapping);   

    this->SetRespIdAndCommit(RespId, ImmediateCommit);
}

//------------------------------------------------------------------------------------------------------------------------  
//--- Delete a unidirectional connection from Imux to Destination for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::DisconnectImuxToDst(
                        QRS_ConnectXcTerm&      Dst,            //--- Destination (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            RespId,
                        bool                    ImmediateCommit)
{
    uint8           dstFac;
    CT_FAC_StsMap   dstFacStsMap;

    // Set Destination Info
    GetFacilityIdFromAGPortId(&dstFac, Dst.FacData.GetPortId()); 
    dstFacStsMap = Dst.FacStsMap;

    // Delete connection to Destination
    Disconnect(dstFac, dstFacStsMap, ConnType);   

    this->SetRespIdAndCommit(RespId, ImmediateCommit);
}

//------------------------------------------------------------------------------------------------------------------------  
//--- Delete a unidirectional connection from Source to Imux for a contiguous or non-contiguous set of channels.
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::DisconnectSrcToImux(
                        QRS_ConnectXcTerm&      Src,            //--- Destination (also contains IMUX info)
                        CT_XC_ConnectType&      ConnType,       //--- Connection Type
                        CT_XC_CQMID*            RespId,
                        bool                    ImmediateCommit)
{
    uint8           dstFac;
    CT_FAC_StsMap   dstFacStsMap;

    // Set Destination Info
    if (Src.TermMappedToImuxl == true)
    {
        //dstFacStsMap = Src.ImuxLineMapEgress;
        dstFacStsMap = Src.ImuxLineMapIngress;
        GetFacilityIdFromIntfId(&dstFac, CT_LINE_SIDE_3);
    }
    else if (Src.TermMappedToImuxp == true)
    {
        //dstFacStsMap = Src.ImuxPortMapEgress;
        dstFacStsMap = Src.ImuxPortMapIngress;
        GetFacilityIdFromIntfId(&dstFac, CT_LINE_SIDE_4);
    }
    else 
    {
        FC_THROW_ERROR(FC_NotSupportedError, "Src must be mapped to either Imuxl/Imuxp");
        return;
    }

    // Delete connection to Destination
    Disconnect(dstFac, dstFacStsMap, ConnType);   

    this->SetRespIdAndCommit(RespId, ImmediateCommit);
}

//------------------------------------------------------------------------------------------------------------------------
//--- The GetConnTypeFromSigType is used only for SMTM-M/UD/SD/FGTM-M/OTNM
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::GetConnTypeFromSigType(CT_XC_ConnectType* theConnType, 
                                                CT_TEL_SignalType theSignalType, 
                                                CT_TEL_TermSize theTermSize)
{
    switch (theSignalType)
    {
        case CT_TEL_SIGNAL_OC3:
        case CT_TEL_SIGNAL_STM1:
            *theConnType = CT_XC_TYPE_STS3T;
            break;
        case CT_TEL_SIGNAL_OC12:
        case CT_TEL_SIGNAL_STM4:
            *theConnType = CT_XC_TYPE_STS12T;
            break;
        case CT_TEL_SIGNAL_OC48:
        case CT_TEL_SIGNAL_STM16:
            *theConnType = CT_XC_TYPE_STS48T;
            break;
        case CT_TEL_SIGNAL_GOPT:
        case CT_TEL_SIGNAL_GBEP:
        case CT_TEL_SIGNAL_TGBEP:
        case CT_TEL_SIGNAL_100BFX:
        case CT_TEL_SIGNAL_FC:
        case CT_TEL_SIGNAL_ESCON:
        case CT_TEL_SIGNAL_DVBASI:
        case CT_TEL_SIGNAL_FICON:
        case CT_TEL_SIGNAL_ISC:
        case CT_TEL_SIGNAL_FC1G:
        case CT_TEL_SIGNAL_FC266M:
        case CT_TEL_SIGNAL_FC531M:
        case CT_TEL_SIGNAL_TGLAN:
        case CT_TEL_SIGNAL_FC133M:
        case CT_TEL_SIGNAL_D1VIDEO:
        case CT_TEL_SIGNAL_FC2G:
        case CT_TEL_SIGNAL_FICON2G:
        case CT_TEL_SIGNAL_ISC2G:
        case CT_TEL_SIGNAL_FC4G:
        case CT_TEL_SIGNAL_DV6000:
        case CT_TEL_SIGNAL_SDI:
        case CT_TEL_SIGNAL_HDSDI:
        case CT_TEL_SIGNAL_3GSDI:
        case CT_TEL_SIGNAL_VS411:
        case CT_TEL_SIGNAL_VS811:
        case CT_TEL_SIGNAL_TRSPSAN:
        case CT_TEL_SIGNAL_TRSPSAN2G:
        case CT_TEL_SIGNAL_OPTDM:
        case CT_TEL_SIGNAL_TGFC:
            if (theTermSize == CT_TEL_TERMSIZE_STS3C)
                *theConnType = CT_XC_TYPE_STS3CD;
            else
                *theConnType = CT_XC_TYPE_STS1D;
            break;
        case CT_TEL_SIGNAL_ODU0:
            *theConnType = CT_XC_TYPE_ODU0;
            break;
        case CT_TEL_SIGNAL_ODU1:
            *theConnType = CT_XC_TYPE_ODU1;
            break;
        case CT_TEL_SIGNAL_ODU2:
            *theConnType = CT_XC_TYPE_ODU2;
            break;
        case CT_TEL_SIGNAL_ODUF:
            *theConnType = CT_XC_TYPE_ODUF;
            break;
        case CT_TEL_SIGNAL_UNKNOWN:
            *theConnType = CT_XC_TYPE_UNSPECIFIED;
            break;
        default:
            FC_THROW_ERROR(FC_NotSupportedError, "Unknown signal type");
    }
}

//--------------------------------------- end of the SD/UD/FGTM-M/OTNM  --------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
//--- This method returns a true or false if the entered data is valid FacilityOffset is also updated.
//------------------------------------------------------------------------------------------------------------------------ 
template<class T> bool TSXC_ConfigRegion<T>::FindValidOffset(uint8 IF, uint8 IFE, uint8 OF, uint8 OFE, int* FacilityOffsetPtr)
{
    bool Valid = FALSE;

    if((IF != 0) &&
       (OF != 0) &&
       (IFE != 0) &&
       (OFE != 0))
    {
        Valid = TRUE;
        if (this->myCardType == CARD_TYPE_SPFAB)
        {
            //--- Validate the Input and Output facility
            Valid = ((IF >= XC_SPFAB_LINE0_FACILITY_ID) && 
                     (IF <= XC_SPFAB_LINE27_FACILITY_ID) &&
                     (!(IFE > XC_MAX_XC_SPFAB_LINE)));
            //--- if the Input facility is valid then validate the Output facility
            if (Valid)
            { 
                Valid = ((OF >= XC_SPFAB_LINE0_FACILITY_ID) && 
                         (OF <= XC_SPFAB_LINE27_FACILITY_ID) &&
                         (!(OFE > XC_MAX_XC_SPFAB_LINE)));
            }
            if (Valid)
            {
                *FacilityOffsetPtr = SPFABConfigMap[OF];
            } 
        }
        //--- Validation check for the FGTMM module.
        else if (this->myCardType == CARD_TYPE_FGTMM)
        {
            if ((IF >= XC_FGTMM_ODU2_PORT0_FACILITY_ID) && (IF <= XC_FGTMM_ODU2_PORT3_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_FGTMM_ODU2_PORT);
            }
            else if ( IF == XC_FGTMM_DWDM_FACILITY_ID )
            {
                Valid = !(IFE > XC_MAX_XC_FGTMM_ODU2_DWDM);
            }
            else
                Valid = FALSE;

            if (Valid)
            {
                if ((OF >= XC_FGTMM_ODU2_PORT0_FACILITY_ID) && (OF <= XC_FGTMM_ODU2_PORT3_FACILITY_ID))
                {
                    Valid = !(OFE > XC_MAX_XC_FGTMM_ODU2_PORT);
                }
                else if ( OF == XC_FGTMM_DWDM_FACILITY_ID )
                {
                    Valid = !(OFE > XC_MAX_XC_FGTMM_ODU2_DWDM);
                }
                else
                    Valid = FALSE;               
            }
            if(Valid)
            {
                *FacilityOffsetPtr = FGTMMConfigMap[OF];
            } 
        }
        //--- Validation check for the SSM module.
        else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
        {
            if ((IF >= XC_SSM_PORT0_FACILITY_ID) && (IF <= XC_SSM_PORT11_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_SSM_PORT);
            }
            else if ((IF >= XC_SSM_PORT12_FACILITY_ID) && (IF <= XC_SSM_TTP_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_SSM_DWDM);
            }
            else
                Valid = FALSE;
            
            if (Valid)
            {
                if ((OF >= XC_SSM_PORT0_FACILITY_ID) && (OF <= XC_SSM_PORT11_FACILITY_ID))
                {
                    Valid = !(OFE > XC_MAX_XC_SSM_PORT);
                }
                else if ((OF >= XC_SSM_PORT12_FACILITY_ID) && (OF <= XC_SSM_TTP_FACILITY_ID))
                {
                    Valid = !(OFE > XC_MAX_XC_SSM_DWDM);
                }
                else
                    Valid = FALSE;               
            }
            if(Valid)
            {
                *FacilityOffsetPtr = SSMConfigMap[OF];
            }            
        }

        else if ( (this->myCardType == CARD_TYPE_OSM40) || (this->myCardType == CARD_TYPE_SSM40) )
        {
            switch (IF) 
            {
                case XC_SSM40_ODUXC_ODU_OTNOTU0_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_OTNOTU0_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODUXC_OTN0);
                    break;

                case XC_SSM40_ODUXC_ODU_OTNOTU1_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_OTNOTU1_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODUXC_OTN1);
                    break;

                case XC_SSM40_ODUXC_ODU_OTNOTU2_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_OTNOTU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODUXC_OTN2);
                    break;

                case XC_SSM40_ODUXC_ODU_VCAT0A_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_VCAT0B_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_VCAT0A_1_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_VCAT0B_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODUXC_VCAT0);
                    break;

                case XC_SSM40_ODUXC_ODU_VCATA_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_VCATB_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_VCATA_1_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_VCATB_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODUXC_VCAT);
                    break;

                case XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID:
                case XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODUXC_IMUX);
                    break;

                case XC_SSM40_FRMODUXC_FRM_OTU0_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_OTU0_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU0);
                    break;

                case XC_SSM40_FRMODUXC_FRM_OTU1_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_OTU1_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU1);
                    break;

                case XC_SSM40_FRMODUXC_FRM_OTU2_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_OTU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU2);
                    break;

                case XC_SSM40_FRMODUXC_FRM_CBR_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_CBR_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR);
                    break;

                case XC_SSM40_FRMODUXC_FRM_CBR10G_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_CBR10G_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR10G);
                    break;

                case XC_SSM40_FRMODUXC_FRM_GE_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_GE_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_GE);
                    break;

                case XC_SSM40_FRMODUXC_FRM_GE10G_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_FRM_GE10G_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_GE10G);
                    break;

                case XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU0);
                    break;

                case XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU1);
                    break;

                case XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU2);
                    break;

                case XC_SSM40_FRMODUXC_ODU_VCATA_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_ODU_VCATB_0_FACILITY_ID:
                case XC_SSM40_FRMODUXC_ODU_VCATA_1_FACILITY_ID:
                case XC_SSM40_FRMODUXC_ODU_VCATB_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT);
                    break;

                case XC_SSM40_ODU21XC_ODU2_0_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU2_1_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU2_0_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU2_1_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODU21XC_ODU2);
                    break;

                case XC_SSM40_ODU21XC_ODU1_0_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_1_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_2_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_3_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_4_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_5_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_6_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_7_0_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_0_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_1_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_2_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_3_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_4_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_5_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_6_1_FACILITY_ID:
                case XC_SSM40_ODU21XC_ODU1_7_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_SSM40_ODU21XC_ODU1);
                    break;

                default:
                    Valid = FALSE;
                    break;
            }


            if (Valid)
            {
                switch (OF) 
                {
                    case XC_SSM40_ODUXC_ODU_OTNOTU0_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_OTNOTU0_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODUXC_OTN0);
                        break;

                    case XC_SSM40_ODUXC_ODU_OTNOTU1_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_OTNOTU1_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODUXC_OTN1);
                        break;

                    case XC_SSM40_ODUXC_ODU_OTNOTU2_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_OTNOTU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODUXC_OTN2);
                        break;

                    case XC_SSM40_ODUXC_ODU_VCAT0A_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_VCAT0B_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_VCAT0A_1_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_VCAT0B_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODUXC_VCAT0);
                        break;

                    case XC_SSM40_ODUXC_ODU_VCATA_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_VCATB_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_VCATA_1_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_VCATB_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODUXC_VCAT);
                        break;

                    case XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID:
                    case XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODUXC_IMUX);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_OTU0_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_OTU0_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU0);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_OTU1_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_OTU1_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU1);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_OTU2_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_OTU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU2);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_CBR_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_CBR_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_CBR10G_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_CBR10G_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR10G);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_GE_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_GE_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_GE);
                        break;

                    case XC_SSM40_FRMODUXC_FRM_GE10G_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_FRM_GE10G_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_FRM_GE10G);
                        break;

                    case XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU0);
                        break;

                    case XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU1);
                        break;

                    case XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU2);
                        break;

                    case XC_SSM40_FRMODUXC_ODU_VCATA_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_ODU_VCATB_0_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_ODU_VCATA_1_FACILITY_ID:
                    case XC_SSM40_FRMODUXC_ODU_VCATB_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT);
                        break;

                    case XC_SSM40_ODU21XC_ODU2_0_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU2_1_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU2_0_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU2_1_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODU21XC_ODU2);
                        break;

                    case XC_SSM40_ODU21XC_ODU1_0_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_1_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_2_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_3_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_4_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_5_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_6_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_7_0_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_0_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_1_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_2_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_3_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_4_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_5_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_6_1_FACILITY_ID:
                    case XC_SSM40_ODU21XC_ODU1_7_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_SSM40_ODU21XC_ODU1);
                        break;

                    default:
                        Valid = FALSE;
                        break;
                }
            }

            if(Valid)
            {
                *FacilityOffsetPtr = SSM40ConfigMap[OF];
            }
        }

        //--- Validation check for the FGSM module.
        else if(this->myCardType == CARD_TYPE_FGSM)
        {
            switch (IF) 
            {
                case XC_FGSM_ODUXC_ODU_OTNOTU0_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODUXC_OTN0);
                    break;

                case XC_FGSM_ODUXC_ODU_OTNOTU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODUXC_OTN1);
                    break;

                case XC_FGSM_ODUXC_ODU_OTNOTU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODUXC_OTN2);
                    break;

                case XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODUXC_IMUX);
                    break;

                case XC_FGSM_ODU32XC_ODU3_0_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU32XC_ODU3);
                    break;

                case XC_FGSM_ODU32XC_ODU2_0_FACILITY_ID:
                case XC_FGSM_ODU32XC_ODU2_1_FACILITY_ID:
                case XC_FGSM_ODU32XC_ODU2_2_FACILITY_ID:
                case XC_FGSM_ODU32XC_ODU2_3_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU32XC_ODU2);
                    break;

                case XC_FGSM_ODU31XC_ODU3_0_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU31XC_ODU3);
                    break;

                case XC_FGSM_ODU31XC_ODU1_0_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_1_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_2_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_3_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_4_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_5_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_6_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_7_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_8_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_9_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_10_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_11_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_12_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_13_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_14_FACILITY_ID:
                case XC_FGSM_ODU31XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU31XC_ODU1);
                    break;

                case XC_FGSM_ODU30XC_ODU3_0_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU30XC_ODU3);
                    break;

                case XC_FGSM_ODU30XC_ODU0_0_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_1_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_2_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_3_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_4_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_5_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_6_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_7_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_8_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_9_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_10_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_11_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_12_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_13_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_14_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_15_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_16_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_17_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_18_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_19_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_20_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_21_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_22_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_23_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_24_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_25_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_26_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_27_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_28_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_29_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_30_FACILITY_ID:
                case XC_FGSM_ODU30XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU30XC_ODU0);
                    break;

                case XC_FGSM_ODU21XC_ODU2_0_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU2_1_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU2_2_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU2_3_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU21XC_ODU2);
                    break;

                case XC_FGSM_ODU21XC_ODU1_0_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_1_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_2_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_3_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_4_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_5_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_6_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_7_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_8_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_9_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_10_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_11_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_12_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_13_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_14_FACILITY_ID:
                case XC_FGSM_ODU21XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU21XC_ODU1);
                    break;

                case XC_FGSM_ODU20XC_ODU2_0_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU2_1_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU2_2_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU2_3_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU20XC_ODU2);
                    break;

                case XC_FGSM_ODU20XC_ODU0_0_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_1_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_2_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_3_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_4_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_5_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_6_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_7_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_8_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_9_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_10_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_11_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_12_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_13_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_14_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_15_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_16_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_17_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_18_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_19_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_20_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_21_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_22_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_23_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_24_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_25_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_26_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_27_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_28_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_29_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_30_FACILITY_ID:
                case XC_FGSM_ODU20XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU20XC_ODU0);
                    break;

                case XC_FGSM_ODU10XC_ODU1_0_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_1_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_2_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_3_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_4_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_5_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_6_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_7_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_8_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_9_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_10_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_11_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_12_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_13_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_14_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU10XC_ODU1);
                    break;

                case XC_FGSM_ODU10XC_ODU0_0_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_1_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_2_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_3_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_4_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_5_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_6_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_7_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_8_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_9_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_10_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_11_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_12_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_13_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_14_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_15_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_16_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_17_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_18_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_19_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_20_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_21_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_22_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_23_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_24_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_25_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_26_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_27_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_28_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_29_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_30_FACILITY_ID:
                case XC_FGSM_ODU10XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_FGSM_ODU10XC_ODU0);
                    break;

                default:
                    Valid = FALSE;
                    break;
            }


            if (Valid)
            {
                switch (OF) 
                {
                    case XC_FGSM_ODUXC_ODU_OTNOTU0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODUXC_OTN0);
                        break;
    
                    case XC_FGSM_ODUXC_ODU_OTNOTU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODUXC_OTN1);
                        break;
    
                    case XC_FGSM_ODUXC_ODU_OTNOTU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODUXC_OTN2);
                        break;
    
                    case XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODUXC_IMUX);
                        break;
    
                    case XC_FGSM_ODU32XC_ODU3_0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU32XC_ODU3);
                        break;
    
                    case XC_FGSM_ODU32XC_ODU2_0_FACILITY_ID:
                    case XC_FGSM_ODU32XC_ODU2_1_FACILITY_ID:
                    case XC_FGSM_ODU32XC_ODU2_2_FACILITY_ID:
                    case XC_FGSM_ODU32XC_ODU2_3_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU32XC_ODU2);
                        break;
    
                    case XC_FGSM_ODU31XC_ODU3_0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU31XC_ODU3);
                        break;
    
                    case XC_FGSM_ODU31XC_ODU1_0_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_1_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_2_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_3_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_4_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_5_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_6_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_7_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_8_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_9_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_10_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_11_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_12_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_13_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_14_FACILITY_ID:
                    case XC_FGSM_ODU31XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU31XC_ODU1);
                        break;
    
                    case XC_FGSM_ODU30XC_ODU3_0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU30XC_ODU3);
                        break;
    
                    case XC_FGSM_ODU30XC_ODU0_0_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_1_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_2_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_3_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_4_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_5_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_6_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_7_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_8_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_9_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_10_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_11_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_12_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_13_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_14_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_15_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_16_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_17_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_18_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_19_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_20_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_21_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_22_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_23_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_24_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_25_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_26_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_27_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_28_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_29_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_30_FACILITY_ID:
                    case XC_FGSM_ODU30XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU30XC_ODU0);
                        break;
    
                    case XC_FGSM_ODU21XC_ODU2_0_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU2_1_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU2_2_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU2_3_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU21XC_ODU2);
                        break;
    
                    case XC_FGSM_ODU21XC_ODU1_0_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_1_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_2_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_3_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_4_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_5_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_6_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_7_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_8_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_9_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_10_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_11_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_12_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_13_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_14_FACILITY_ID:
                    case XC_FGSM_ODU21XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU21XC_ODU1);
                        break;
    
                    case XC_FGSM_ODU20XC_ODU2_0_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU2_1_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU2_2_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU2_3_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU20XC_ODU2);
                        break;
    
                    case XC_FGSM_ODU20XC_ODU0_0_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_1_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_2_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_3_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_4_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_5_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_6_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_7_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_8_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_9_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_10_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_11_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_12_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_13_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_14_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_15_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_16_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_17_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_18_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_19_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_20_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_21_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_22_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_23_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_24_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_25_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_26_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_27_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_28_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_29_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_30_FACILITY_ID:
                    case XC_FGSM_ODU20XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU20XC_ODU0);
                        break;
    
                    case XC_FGSM_ODU10XC_ODU1_0_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_1_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_2_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_3_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_4_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_5_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_6_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_7_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_8_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_9_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_10_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_11_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_12_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_13_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_14_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU10XC_ODU1);
                        break;
    
                    case XC_FGSM_ODU10XC_ODU0_0_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_1_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_2_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_3_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_4_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_5_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_6_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_7_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_8_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_9_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_10_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_11_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_12_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_13_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_14_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_15_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_16_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_17_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_18_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_19_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_20_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_21_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_22_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_23_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_24_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_25_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_26_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_27_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_28_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_29_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_30_FACILITY_ID:
                    case XC_FGSM_ODU10XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_FGSM_ODU10XC_ODU0);
                        break;

                    default:
                        Valid = FALSE;
                        break;
                }
            }

            if(Valid)
            {
                *FacilityOffsetPtr = FGSMConfigMap[OF];
            }
        }

        //--- Validation check for the OSM20 module.
        else if(this->myCardType == CARD_TYPE_OSM20)
        {
            switch (IF) 
            {
                //ODU XC
                case XC_OSM20_ODUXC_ODUK_0_FACILITY_ID:
                case XC_OSM20_ODUXC_ODUK_1_FACILITY_ID:
                case XC_OSM20_ODUXC_ODUK_2_FACILITY_ID:
                case XC_OSM20_ODUXC_ODUK_3_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_OTNK);
                    break;

                case XC_OSM20_ODUXC_ODU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_OTN1);
                    break;

                case XC_OSM20_ODUXC_ODU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_OTN2);
                    break;

                case XC_OSM20_ODUXC_ODUKPP_ODUK0_FACILITY_ID:
                case XC_OSM20_ODUXC_ODUKPP_ODUK1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODUK);
                    break;
                case XC_OSM20_ODUXC_ODUKPP_ODU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU1);
                    break;
                case XC_OSM20_ODUXC_ODUKPP_ODU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU2);
                    break;

                case XC_OSM20_ODUXC_IMUX_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODUXC_IMUX);
                    break;

                //Frame XC
                case XC_OSM20_FRMODUXC_FRM_OTUK_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_OTUK);
                    break;

                case XC_OSM20_FRMODUXC_FRM_OTU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU1);
                    break;

                case XC_OSM20_FRMODUXC_FRM_OTU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU2);
                    break;
    
                case XC_OSM20_FRMODUXC_FRM_CBR_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR);
                    break;
    
                case XC_OSM20_FRMODUXC_FRM_CBR10G_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR10G);
                    break;

                case XC_OSM20_FRMODUXC_FRM_GE_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_GE);
                    break;

                case XC_OSM20_FRMODUXC_FRM_GE10G_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_GE10G);
                    break;


                case XC_OSM20_FRMODUXC_ODU_OTUK_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_OTUK);
                    break;

                case XC_OSM20_FRMODUXC_ODU_OTU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU1);
                    break;
    
                case XC_OSM20_FRMODUXC_ODU_OTU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU2);
                    break;

                case XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID:
                case XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU2);
                    break;

                case XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID:
                case XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU1);
                    break;

                case XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID:
                case XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODUK);
                    break;

                //ODU21 MUX
                case XC_OSM20_ODU21XC_ODU2_0_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU21XC_ODU2);
                    break;

                case XC_OSM20_ODU21XC_ODU1_0_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_1_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_2_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_3_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_4_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_5_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_6_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_7_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_8_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_9_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_10_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_11_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_12_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_13_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_14_FACILITY_ID:
                case XC_OSM20_ODU21XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU21XC_ODU1);
                    break;

                //ODU20 MUX
                case XC_OSM20_ODU20XC_ODU2_0_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU20XC_ODU2);
                    break;

                case XC_OSM20_ODU20XC_ODU0_0_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_1_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_2_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_3_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_4_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_5_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_6_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_7_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_8_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_9_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_10_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_11_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_12_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_13_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_14_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_15_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_16_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_17_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_18_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_19_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_20_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_21_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_22_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_23_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_24_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_25_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_26_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_27_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_28_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_29_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_30_FACILITY_ID:
                case XC_OSM20_ODU20XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU20XC_ODU0);
                    break;

                //ODU2F MUX
                case XC_OSM20_ODU2FXC_ODU2_0_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU2FXC_ODU2);
                    break;

                case XC_OSM20_ODU2FXC_ODUF_0_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_1_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_2_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_3_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_4_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_5_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_6_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_7_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_8_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_9_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_10_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_11_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_12_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_13_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_14_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_15_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_16_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_17_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_18_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_19_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_20_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_21_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_22_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_23_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_24_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_25_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_26_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_27_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_28_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_29_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_30_FACILITY_ID:
                case XC_OSM20_ODU2FXC_ODUF_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU2FXC_ODUF);
                    break;

                //ODU10 MUX
                case XC_OSM20_ODU10XC_ODU1_0_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_1_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_2_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_3_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_4_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_5_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_6_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_7_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_8_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_9_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_10_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_11_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_12_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_13_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_14_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU10XC_ODU1);
                    break;

                case XC_OSM20_ODU10XC_ODU0_0_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_1_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_2_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_3_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_4_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_5_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_6_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_7_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_8_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_9_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_10_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_11_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_12_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_13_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_14_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_15_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_16_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_17_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_18_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_19_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_20_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_21_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_22_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_23_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_24_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_25_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_26_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_27_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_28_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_29_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_30_FACILITY_ID:
                case XC_OSM20_ODU10XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM20_ODU10XC_ODU0);
                    break;

                default:
                    Valid = FALSE;
                    break;
            }

            if (Valid)
            {
                switch (OF) 
                {
                    //ODU XC
                    case XC_OSM20_ODUXC_ODUK_0_FACILITY_ID:
                    case XC_OSM20_ODUXC_ODUK_1_FACILITY_ID:
                    case XC_OSM20_ODUXC_ODUK_2_FACILITY_ID:
                    case XC_OSM20_ODUXC_ODUK_3_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_OTNK);
                        break;
    
                    case XC_OSM20_ODUXC_ODU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_OTN1);
                        break;
    
                    case XC_OSM20_ODUXC_ODU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_OTN2);
                        break;
    
                    case XC_OSM20_ODUXC_ODUKPP_ODUK0_FACILITY_ID:
                    case XC_OSM20_ODUXC_ODUKPP_ODUK1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODUK);
                        break;
                    case XC_OSM20_ODUXC_ODUKPP_ODU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU1);
                        break;
                    case XC_OSM20_ODUXC_ODUKPP_ODU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU2);
                        break;

                    case XC_OSM20_ODUXC_IMUX_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODUXC_IMUX);
                        break;
    
                    //Frame XC
                    case XC_OSM20_FRMODUXC_FRM_OTUK_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_OTUK);
                        break;
    
                    case XC_OSM20_FRMODUXC_FRM_OTU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU1);
                        break;
    
                    case XC_OSM20_FRMODUXC_FRM_OTU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU2);
                        break;
        
                    case XC_OSM20_FRMODUXC_FRM_CBR_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR);
                        break;
        
                    case XC_OSM20_FRMODUXC_FRM_CBR10G_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR10G);
                        break;
    
                    case XC_OSM20_FRMODUXC_FRM_GE_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_GE);
                        break;
    
                    case XC_OSM20_FRMODUXC_FRM_GE10G_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_FRM_GE10G);
                        break;
    
    
                    case XC_OSM20_FRMODUXC_ODU_OTUK_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_OTUK);
                        break;
    
                    case XC_OSM20_FRMODUXC_ODU_OTU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU1);
                        break;
        
                    case XC_OSM20_FRMODUXC_ODU_OTU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU2);
                        break;

                    case XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID:
                    case XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU2);
                        break;

                    case XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID:
                    case XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU1);
                        break;

                    case XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID:
                    case XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODUK);
                        break;

                    //ODU21 MUX
                    case XC_OSM20_ODU21XC_ODU2_0_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU21XC_ODU2);
                        break;
    
                    case XC_OSM20_ODU21XC_ODU1_0_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_1_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_2_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_3_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_4_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_5_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_6_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_7_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_8_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_9_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_10_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_11_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_12_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_13_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_14_FACILITY_ID:
                    case XC_OSM20_ODU21XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU21XC_ODU1);
                        break;
    
                    //ODU20 MUX
                    case XC_OSM20_ODU20XC_ODU2_0_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU20XC_ODU2);
                        break;
    
                    case XC_OSM20_ODU20XC_ODU0_0_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_1_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_2_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_3_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_4_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_5_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_6_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_7_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_8_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_9_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_10_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_11_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_12_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_13_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_14_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_15_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_16_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_17_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_18_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_19_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_20_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_21_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_22_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_23_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_24_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_25_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_26_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_27_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_28_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_29_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_30_FACILITY_ID:
                    case XC_OSM20_ODU20XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU20XC_ODU0);
                        break;
    
                    //ODU2F MUX
                    case XC_OSM20_ODU2FXC_ODU2_0_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU2FXC_ODU2);
                        break;
    
                    case XC_OSM20_ODU2FXC_ODUF_0_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_1_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_2_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_3_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_4_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_5_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_6_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_7_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_8_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_9_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_10_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_11_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_12_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_13_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_14_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_15_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_16_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_17_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_18_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_19_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_20_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_21_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_22_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_23_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_24_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_25_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_26_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_27_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_28_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_29_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_30_FACILITY_ID:
                    case XC_OSM20_ODU2FXC_ODUF_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU2FXC_ODUF);
                        break;
    
                    //ODU10 MUX
                    case XC_OSM20_ODU10XC_ODU1_0_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_1_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_2_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_3_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_4_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_5_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_6_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_7_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_8_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_9_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_10_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_11_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_12_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_13_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_14_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU10XC_ODU1);
                        break;
    
                    case XC_OSM20_ODU10XC_ODU0_0_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_1_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_2_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_3_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_4_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_5_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_6_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_7_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_8_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_9_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_10_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_11_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_12_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_13_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_14_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_15_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_16_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_17_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_18_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_19_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_20_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_21_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_22_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_23_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_24_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_25_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_26_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_27_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_28_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_29_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_30_FACILITY_ID:
                    case XC_OSM20_ODU10XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM20_ODU10XC_ODU0);
                        break;

                    default:
                        Valid = FALSE;
                        break;
                }
            }

            if(Valid)
            {
                *FacilityOffsetPtr = OSM20ConfigMap[OF];
            }
        }

        else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS
        {
            Valid = FALSE;

            if ( (OF == HGTMM_XC_ODU3_CLIENT_1_FACILITY_ID)   ||
                 (OF == HGTMM_XC_ODU3_CLIENT_2_FACILITY_ID)   ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_3_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_4_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_5_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_6_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_7_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_8_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_9_FACILITY_ID)  ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_10_FACILITY_ID) ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_11_FACILITY_ID) ||
                 (OF == HGTMM_XC_ODU2F_CLIENT_12_FACILITY_ID) ||
                 (OF == HGTMM_XC_ODU4_LINE_FACILITY_ID) )
            {
                if ( IF <= HGTMM_XC_ODU4_LINE_FACILITY_ID )
                {
                    Valid = TRUE;
                }
            }
            else if ( IF == HGTMM_XC_ODU4_DEMUX_ODU2_FACILITY_ID ||
                      IF == HGTMM_XC_ODU4_DEMUX_ODUF_FACILITY_ID || 
                      IF == HGTMM_XC_ODU4_DEMUX_ODU3_FACILITY_ID )
            {
                if ( OF == HGTMM_XC_ODU4_MUX_FACILITY_ID )
                {
                    Valid = TRUE;
                }
            }

            if(Valid)
            {
                *FacilityOffsetPtr = HGTMMConfigMap[OF];
            }
		}

        //--- Validation check for the SMTMU module
        //--- Get the Starting facility offset into the region.
        else if (this->myCardType == CARD_TYPE_SMTMU) //--- SMTMU Checks
        {
            //--- Check to see if this is a port facility 
            if((IF == XC_SMTMU_PORT0_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT1_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT2_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT3_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT4_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT5_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT6_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT7_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT8_FACILITY_ID) ||
               (IF == XC_SMTMU_PORT9_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_SMTMU_PORT)
                {
                    Valid = FALSE;
                }
            }
            //--- Is it a Line Facility?
            else if((IF == XC_SMTMU_DWDM_FACILITY_ID) ||
                    (IF == XC_SMTMU_IM_LINE_FACILITY_ID) ||
                    (IF == XC_SMTMU_IM_PORT_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_SMTMU_DWDM)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }

            //--- Check to see if this is a port facility 
            if((OF == XC_SMTMU_PORT0_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT1_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT2_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT3_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT4_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT5_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT6_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT7_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT8_FACILITY_ID) ||
               (OF == XC_SMTMU_PORT9_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_SMTMU_PORT)
                {
                    Valid = FALSE;
                }
            }
            //--- Is it a Line Facility?
            else if((OF == XC_SMTMU_DWDM_FACILITY_ID) ||
                    (OF == XC_SMTMU_IM_LINE_FACILITY_ID) ||
                    (OF == XC_SMTMU_IM_PORT_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_SMTMU_DWDM)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }

            if(Valid)
            {
                *FacilityOffsetPtr = SMTMUConfigMap[OF];
            }
        }
        else if ( (this->myCardType == CARD_TYPE_SMTMUD) ||   //--- SMTMUDSD Checks
                  (this->myCardType == CARD_TYPE_SMTMSD) )    
        {
            //--- Check to see if this is a port facility 
            if((IF == XC_SMTMUDSD_PORT0_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT1_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT2_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT3_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT4_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT5_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT6_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT7_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT8_FACILITY_ID) ||
               (IF == XC_SMTMUDSD_PORT9_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_SMTMUDSD_PORT)
                {
                    Valid = FALSE;
                }
            }
            //--- Is it a Line Facility?
            else if(IF == XC_SMTMUDSD_DWDM_FACILITY_ID)
            {
                if(IFE > XC_MAX_XC_SMTMUDSD_DWDM)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }

            //--- Check to see if this is a port facility 
            if((OF == XC_SMTMUDSD_PORT0_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT1_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT2_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT3_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT4_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT5_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT6_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT7_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT8_FACILITY_ID) ||
               (OF == XC_SMTMUDSD_PORT9_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_SMTMUDSD_PORT)
                {
                    Valid = FALSE;
                }
            }
            //--- Is it a Line Facility?
            else if(OF == XC_SMTMUDSD_DWDM_FACILITY_ID)
            {
                if(OFE > XC_MAX_XC_SMTMUDSD_DWDM)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }

            if(Valid)
            {
                *FacilityOffsetPtr = SMTMUDSDConfigMap[OF];
            }
        }

        //--- Validation check for the OTNM module.
        else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
        {
            //--- Check to see if this is a port facility 
            if((IF == XC_OTNM_PORT1_FACILITY_ID) ||
               (IF == XC_OTNM_PORT2_FACILITY_ID) ||
               (IF == XC_OTNM_PORT3_FACILITY_ID) ||
               (IF == XC_OTNM_PORT4_FACILITY_ID) ||
               (IF == XC_OTNM_PORT5_FACILITY_ID) ||
               (IF == XC_OTNM_PORT6_FACILITY_ID) ||
               (IF == XC_OTNM_PORT7_FACILITY_ID) ||
               (IF == XC_OTNM_PORT8_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_OTNM_PORT)
                {
                    Valid = FALSE;
                }
            }
            //--- Is it a OC192 (Coming from Bachelor)?
            else if(IF == XC_OTNM_OC192_FACILITY_ID)
            {
                if(IFE > XC_MAX_XC_OTNM_OC192)
                {
                    Valid = FALSE;
                }
            }

            //--- Is it a mid line ODU1?
            else if ((IF >= XC_OTNM_ODU1_MIDLINE1_FACILITY_ID) && (IF <= XC_OTNM_ODU1_IMUX4_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_OTNM_ODU1);
            }
            //--- Is it a mid line ODU2?  Note: Not in 5.1
            else if ((IF >= XC_OTNM_ODU2_HIGHSPEED_FACILITY_ID) && (IF <= XC_OTNM_ODU2_IMUX_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_OTNM_ODU2);
            }
            
            //--- Unknown
            else
            {
                Valid = FALSE;
            }


            //--- Check to see if this is a port facility 
            if((OF == XC_OTNM_PORT1_FACILITY_ID) ||
               (OF == XC_OTNM_PORT2_FACILITY_ID) ||
               (OF == XC_OTNM_PORT3_FACILITY_ID) ||
               (OF == XC_OTNM_PORT4_FACILITY_ID) ||
               (OF == XC_OTNM_PORT5_FACILITY_ID) ||
               (OF == XC_OTNM_PORT6_FACILITY_ID) ||
               (OF == XC_OTNM_PORT7_FACILITY_ID) ||
               (OF == XC_OTNM_PORT8_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_OTNM_PORT)
                {
                    Valid = FALSE;
                }
            }
            //--- Is it a Line Facility?
            else if(OF == XC_OTNM_OC192_FACILITY_ID)
            {
                if(OFE > XC_MAX_XC_OTNM_OC192)
                {
                    Valid = FALSE;
                }
            }

            //--- Is it a mid line ODU1?
            else if ((OF >= XC_OTNM_ODU1_MIDLINE1_FACILITY_ID) && (IF <= XC_OTNM_ODU1_IMUX4_FACILITY_ID))
            {
                Valid = !(OFE > XC_MAX_XC_OTNM_ODU1);
            }
            //--- Is it a mid line ODU2?  Note: Not in 5.1
            else if ((OF >= XC_OTNM_ODU2_HIGHSPEED_FACILITY_ID) && (IF <= XC_OTNM_ODU2_IMUX_FACILITY_ID))
            {
                Valid = !(OFE > XC_MAX_XC_OTNM_ODU2);
            }

            //--- Unknown
            else
            {
                Valid = FALSE;
            }

            if(Valid)
            {
                *FacilityOffsetPtr = OTNMConfigMap[OF];
            }
        }
        //--- Validation check for the HDTG module.
        else if (this->myCardType == CARD_TYPE_HDTG)
        {
            if ((IF >= XC_HDTG_ODU2_PORT0_FACILITY_ID) && (IF <= XC_HDTG_ODU2_PORT14_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_HDTG_ODU2_PORT);
            }
            else
                Valid = FALSE;

            if (Valid)
            {
                if ((OF >= XC_HDTG_ODU2_PORT0_FACILITY_ID) && (OF <= XC_HDTG_ODU2_PORT14_FACILITY_ID))
                {
                    Valid = !(OFE > XC_MAX_XC_HDTG_ODU2_PORT);
                }
                else
                    Valid = FALSE;               
            }
            if(Valid)
            {
                *FacilityOffsetPtr = HDTGConfigMap[OF];
            } 
        }
        //--- Validation check for the HDTG module.
        else if (this->myCardType == CARD_TYPE_HDTG2)
        {
            if ((IF >= XC_HDTG2_ODU2F_PORT0_FACILITY_ID) && (IF <= XC_HDTG2_ODU2F_PORT15_FACILITY_ID))
            {
                Valid = !(IFE > XC_MAX_XC_HDTG2_ODU2F_PORT);
                if (Valid)
                {
                    if ((OF >= XC_HDTG2_ODU2F_PORT0_FACILITY_ID) && (OF <= XC_HDTG2_ODU2F_PORT15_FACILITY_ID))
                    {
                        Valid = !(OFE > XC_MAX_XC_HDTG2_ODU2F_PORT);
                    }
                    else
                        Valid = FALSE;               
                }
            }
            else if (IF == XC_HDTG2_ODU2_DEMUX_ODUF_FACILITY_ID)
            {
                Valid = !(IFE > XC_MAX_HDTG2_ODU2_TRIBPORT_ID);
                if (Valid)
                {
                    if ((OF >= XC_HDTG2_ODUF_MUX0_START) && (OF <= XC_HDTG2_ODUF_MUX7_END))
                    {
                        Valid = !(OFE > XC_MAX_HDTG2_ODU2_TRIBSLOTS);
                    }
                    else
                        Valid = FALSE;               
                }
            }
            else
                Valid = FALSE;

            if(Valid)
            {
                *FacilityOffsetPtr = HDTG2ConfigMap[OF];
            } 
        }
        else if(this->myCardType == CARD_TYPE_DCMM)//--- DCMM Checks
        {

            //--- Check to see if this is a valid DCMM facility 
            if((IF == XC_DCMM_PORT0_FACILITY_ID) ||
               (IF == XC_DCMM_PORT1_FACILITY_ID) ||
               (IF == XC_DCMM_PORT2_FACILITY_ID) ||
               (IF == XC_DCMM_PORT3_FACILITY_ID) ||
               (IF == XC_DCMM_PORT4_FACILITY_ID) ||
               (IF == XC_DCMM_PORT5_FACILITY_ID) ||
               (IF == XC_DCMM_PORT6_FACILITY_ID) ||
               (IF == XC_DCMM_PORT7_FACILITY_ID) ||
               (IF == XC_DCMM_LINE_FACILITY_ID)  ||
               (IF == XC_DCMM_EXPRESS_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_DCMM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_DCMM_PORT0_FACILITY_ID) ||
               (OF == XC_DCMM_PORT1_FACILITY_ID) ||
               (OF == XC_DCMM_PORT2_FACILITY_ID) ||
               (OF == XC_DCMM_PORT3_FACILITY_ID) ||
               (OF == XC_DCMM_PORT4_FACILITY_ID) ||
               (OF == XC_DCMM_PORT5_FACILITY_ID) ||
               (OF == XC_DCMM_PORT6_FACILITY_ID) ||
               (OF == XC_DCMM_PORT7_FACILITY_ID) ||
               (OF == XC_DCMM_LINE_FACILITY_ID)  ||
               (OF == XC_DCMM_EXPRESS_FACILITY_ID))               
            {
                if(OFE > XC_MAX_XC_DCMM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = DCMMConfigMap[OF];
            }          
        }
        else if(this->myCardType == CARD_TYPE_RCMM)//--- RCMM Checks
        {

            //--- Check to see if this is a valid RCMM facility 
            if((IF == XC_RCMM_PORT0_FACILITY_ID) ||
               (IF == XC_RCMM_PORT1_FACILITY_ID) ||
               (IF == XC_RCMM_PORT2_FACILITY_ID) ||
               (IF == XC_RCMM_PORT3_FACILITY_ID) ||
               (IF == XC_RCMM_PORT4_FACILITY_ID) ||
               (IF == XC_RCMM_PORT5_FACILITY_ID) ||
               (IF == XC_RCMM_PORT6_FACILITY_ID) ||
               (IF == XC_RCMM_PORT7_FACILITY_ID) ||
               (IF == XC_RCMM_PORT8_FACILITY_ID) ||
               (IF == XC_RCMM_PORT9_FACILITY_ID) ||
               (IF == XC_RCMM_PORT10_FACILITY_ID) ||
               (IF == XC_RCMM_PORT11_FACILITY_ID) ||
               (IF == XC_RCMM_PORT12_FACILITY_ID) ||
               (IF == XC_RCMM_PORT13_FACILITY_ID) ||
               (IF == XC_RCMM_PORT14_FACILITY_ID) ||
               (IF == XC_RCMM_PORT15_FACILITY_ID) ||
               (IF == XC_RCMM_PORT16_FACILITY_ID) ||
               (IF == XC_RCMM_PORT17_FACILITY_ID) ||
               (IF == XC_RCMM_PORT18_FACILITY_ID) ||
               (IF == XC_RCMM_PORT19_FACILITY_ID) ||
               (IF == XC_RCMM_PORT20_FACILITY_ID) ||
               (IF == XC_RCMM_PORT21_FACILITY_ID) ||
               (IF == XC_RCMM_PORT22_FACILITY_ID) ||
               (IF == XC_RCMM_PORT23_FACILITY_ID) ||
               (IF == XC_RCMM_PORT24_FACILITY_ID) ||
               (IF == XC_RCMM_PORT25_FACILITY_ID) ||
               (IF == XC_RCMM_PORT26_FACILITY_ID) ||
               (IF == XC_RCMM_PORT27_FACILITY_ID) ||
               (IF == XC_RCMM_PORT28_FACILITY_ID) ||
               (IF == XC_RCMM_PORT29_FACILITY_ID) ||
               (IF == XC_RCMM_PORT30_FACILITY_ID) ||
               (IF == XC_RCMM_PORT31_FACILITY_ID) ||
               (IF == XC_RCMM_PORT32_FACILITY_ID) ||
               (IF == XC_RCMM_PORT33_FACILITY_ID) ||
               (IF == XC_RCMM_PORT34_FACILITY_ID) ||
               (IF == XC_RCMM_PORT35_FACILITY_ID) ||
               (IF == XC_RCMM_PORT36_FACILITY_ID) ||
               (IF == XC_RCMM_PORT37_FACILITY_ID) ||
               (IF == XC_RCMM_PORT38_FACILITY_ID) ||
               (IF == XC_RCMM_PORT39_FACILITY_ID) ||
               (IF == XC_RCMM_PORT40_FACILITY_ID) ||
               (IF == XC_RCMM_PORT41_FACILITY_ID) ||
               (IF == XC_RCMM_PORT42_FACILITY_ID) ||
               (IF == XC_RCMM_PORT43_FACILITY_ID) ||
               (IF == XC_RCMM_PORT44_FACILITY_ID) ||
               (IF == XC_RCMM_PORT45_FACILITY_ID) ||
               (IF == XC_RCMM_PORT46_FACILITY_ID) ||
               (IF == XC_RCMM_PORT47_FACILITY_ID) ||
               (IF == XC_RCMM_PORT48_FACILITY_ID) ||
               (IF == XC_RCMM_PORT49_FACILITY_ID) ||
               (IF == XC_RCMM_PORT50_FACILITY_ID) ||
               (IF == XC_RCMM_PORT51_FACILITY_ID) ||
               (IF == XC_RCMM_PORT52_FACILITY_ID) ||
               (IF == XC_RCMM_PORT53_FACILITY_ID) ||
               (IF == XC_RCMM_PORT54_FACILITY_ID) ||
               (IF == XC_RCMM_PORT55_FACILITY_ID) ||
               (IF == XC_RCMM_PORT56_FACILITY_ID) ||
               (IF == XC_RCMM_PORT57_FACILITY_ID) ||
               (IF == XC_RCMM_PORT58_FACILITY_ID) ||
               (IF == XC_RCMM_PORT59_FACILITY_ID) ||
               (IF == XC_RCMM_PORT60_FACILITY_ID) ||
               (IF == XC_RCMM_PORT61_FACILITY_ID) ||
               (IF == XC_RCMM_PORT62_FACILITY_ID) ||
               (IF == XC_RCMM_PORT63_FACILITY_ID) ||
               (IF == XC_RCMM_PORT64_FACILITY_ID) ||
               (IF == XC_RCMM_PORT65_FACILITY_ID) ||
               (IF == XC_RCMM_PORT66_FACILITY_ID) ||
               (IF == XC_RCMM_PORT67_FACILITY_ID) ||
               (IF == XC_RCMM_PORT68_FACILITY_ID) ||
               (IF == XC_RCMM_PORT69_FACILITY_ID) ||
               (IF == XC_RCMM_PORT70_FACILITY_ID) ||
               (IF == XC_RCMM_PORT71_FACILITY_ID) ||
               (IF == XC_RCMM_PORT72_FACILITY_ID) ||
               (IF == XC_RCMM_PORT73_FACILITY_ID) ||
               (IF == XC_RCMM_PORT74_FACILITY_ID) ||
               (IF == XC_RCMM_PORT75_FACILITY_ID) ||
               (IF == XC_RCMM_PORT76_FACILITY_ID) ||
               (IF == XC_RCMM_PORT77_FACILITY_ID) ||
               (IF == XC_RCMM_PORT78_FACILITY_ID) ||
               (IF == XC_RCMM_PORT79_FACILITY_ID) ||
               (IF == XC_RCMM_PORT80_FACILITY_ID) ||
               (IF == XC_RCMM_PORT81_FACILITY_ID) ||
               (IF == XC_RCMM_PORT82_FACILITY_ID) ||
               (IF == XC_RCMM_PORT83_FACILITY_ID) ||
               (IF == XC_RCMM_PORT84_FACILITY_ID) ||
               (IF == XC_RCMM_PORT85_FACILITY_ID) ||
               (IF == XC_RCMM_PORT86_FACILITY_ID) ||
               (IF == XC_RCMM_PORT87_FACILITY_ID) ||
               (IF == XC_RCMM_LINE_FACILITY_ID)  ||
               (IF == XC_RCMM_EXPRESS_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS0_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS1_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS2_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS3_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS4_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS5_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS6_FACILITY_ID) ||
               (IF == XC_RCMM_EXPRESS7_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_RCMM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_RCMM_PORT0_FACILITY_ID) ||
               (OF == XC_RCMM_PORT1_FACILITY_ID) ||
               (OF == XC_RCMM_PORT2_FACILITY_ID) ||
               (OF == XC_RCMM_PORT3_FACILITY_ID) ||
               (OF == XC_RCMM_PORT4_FACILITY_ID) ||
               (OF == XC_RCMM_PORT5_FACILITY_ID) ||
               (OF == XC_RCMM_PORT6_FACILITY_ID) ||
               (OF == XC_RCMM_PORT7_FACILITY_ID) ||
               (OF == XC_RCMM_PORT8_FACILITY_ID) ||
               (OF == XC_RCMM_PORT9_FACILITY_ID) ||
               (OF == XC_RCMM_PORT10_FACILITY_ID) ||
               (OF == XC_RCMM_PORT11_FACILITY_ID) ||
               (OF == XC_RCMM_PORT12_FACILITY_ID) ||
               (OF == XC_RCMM_PORT13_FACILITY_ID) ||
               (OF == XC_RCMM_PORT14_FACILITY_ID) ||
               (OF == XC_RCMM_PORT15_FACILITY_ID) ||
               (OF == XC_RCMM_PORT16_FACILITY_ID) ||
               (OF == XC_RCMM_PORT17_FACILITY_ID) ||
               (OF == XC_RCMM_PORT18_FACILITY_ID) ||
               (OF == XC_RCMM_PORT19_FACILITY_ID) ||
               (OF == XC_RCMM_PORT20_FACILITY_ID) ||
               (OF == XC_RCMM_PORT21_FACILITY_ID) ||
               (OF == XC_RCMM_PORT22_FACILITY_ID) ||
               (OF == XC_RCMM_PORT23_FACILITY_ID) ||
               (OF == XC_RCMM_PORT24_FACILITY_ID) ||
               (OF == XC_RCMM_PORT25_FACILITY_ID) ||
               (OF == XC_RCMM_PORT26_FACILITY_ID) ||
               (OF == XC_RCMM_PORT27_FACILITY_ID) ||
               (OF == XC_RCMM_PORT28_FACILITY_ID) ||
               (OF == XC_RCMM_PORT29_FACILITY_ID) ||
               (OF == XC_RCMM_PORT30_FACILITY_ID) ||
               (OF == XC_RCMM_PORT31_FACILITY_ID) ||
               (OF == XC_RCMM_PORT32_FACILITY_ID) ||
               (OF == XC_RCMM_PORT33_FACILITY_ID) ||
               (OF == XC_RCMM_PORT34_FACILITY_ID) ||
               (OF == XC_RCMM_PORT35_FACILITY_ID) ||
               (OF == XC_RCMM_PORT36_FACILITY_ID) ||
               (OF == XC_RCMM_PORT37_FACILITY_ID) ||
               (OF == XC_RCMM_PORT38_FACILITY_ID) ||
               (OF == XC_RCMM_PORT39_FACILITY_ID) ||
               (OF == XC_RCMM_PORT40_FACILITY_ID) ||
               (OF == XC_RCMM_PORT41_FACILITY_ID) ||
               (OF == XC_RCMM_PORT42_FACILITY_ID) ||
               (OF == XC_RCMM_PORT43_FACILITY_ID) ||
               (OF == XC_RCMM_PORT44_FACILITY_ID) ||
               (OF == XC_RCMM_PORT45_FACILITY_ID) ||
               (OF == XC_RCMM_PORT46_FACILITY_ID) ||
               (OF == XC_RCMM_PORT47_FACILITY_ID) ||
               (OF == XC_RCMM_PORT48_FACILITY_ID) ||
               (OF == XC_RCMM_PORT49_FACILITY_ID) ||
               (OF == XC_RCMM_PORT50_FACILITY_ID) ||
               (OF == XC_RCMM_PORT51_FACILITY_ID) ||
               (OF == XC_RCMM_PORT52_FACILITY_ID) ||
               (OF == XC_RCMM_PORT53_FACILITY_ID) ||
               (OF == XC_RCMM_PORT54_FACILITY_ID) ||
               (OF == XC_RCMM_PORT55_FACILITY_ID) ||
               (OF == XC_RCMM_PORT56_FACILITY_ID) ||
               (OF == XC_RCMM_PORT57_FACILITY_ID) ||
               (OF == XC_RCMM_PORT58_FACILITY_ID) ||
               (OF == XC_RCMM_PORT59_FACILITY_ID) ||
               (OF == XC_RCMM_PORT60_FACILITY_ID) ||
               (OF == XC_RCMM_PORT61_FACILITY_ID) ||
               (OF == XC_RCMM_PORT62_FACILITY_ID) ||
               (OF == XC_RCMM_PORT63_FACILITY_ID) ||
               (OF == XC_RCMM_PORT64_FACILITY_ID) ||
               (OF == XC_RCMM_PORT65_FACILITY_ID) ||
               (OF == XC_RCMM_PORT66_FACILITY_ID) ||
               (OF == XC_RCMM_PORT67_FACILITY_ID) ||
               (OF == XC_RCMM_PORT68_FACILITY_ID) ||
               (OF == XC_RCMM_PORT69_FACILITY_ID) ||
               (OF == XC_RCMM_PORT70_FACILITY_ID) ||
               (OF == XC_RCMM_PORT71_FACILITY_ID) ||
               (OF == XC_RCMM_PORT72_FACILITY_ID) ||
               (OF == XC_RCMM_PORT73_FACILITY_ID) ||
               (OF == XC_RCMM_PORT74_FACILITY_ID) ||
               (OF == XC_RCMM_PORT75_FACILITY_ID) ||
               (OF == XC_RCMM_PORT76_FACILITY_ID) ||
               (OF == XC_RCMM_PORT77_FACILITY_ID) ||
               (OF == XC_RCMM_PORT78_FACILITY_ID) ||
               (OF == XC_RCMM_PORT79_FACILITY_ID) ||
               (OF == XC_RCMM_PORT80_FACILITY_ID) ||
               (OF == XC_RCMM_PORT81_FACILITY_ID) ||
               (OF == XC_RCMM_PORT82_FACILITY_ID) ||
               (OF == XC_RCMM_PORT83_FACILITY_ID) ||
               (OF == XC_RCMM_PORT84_FACILITY_ID) ||
               (OF == XC_RCMM_PORT85_FACILITY_ID) ||
               (OF == XC_RCMM_PORT86_FACILITY_ID) ||
               (OF == XC_RCMM_PORT87_FACILITY_ID) ||
               (OF == XC_RCMM_LINE_FACILITY_ID)  ||
               (OF == XC_RCMM_EXPRESS_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS0_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS1_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS2_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS3_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS4_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS5_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS6_FACILITY_ID) ||
               (OF == XC_RCMM_EXPRESS7_FACILITY_ID))              
            {
                if(OFE > XC_MAX_XC_RCMM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = RCMMConfigMap[OF];
            }          
        }
        else if((this->myCardType == CARD_TYPE_CCMIR) ||
                (this->myCardType == CARD_TYPE_CCMLR) ||
                (this->myCardType == CARD_TYPE_CCMER))//--- Nano Core Checks
        {

            //--- Check to see if this is a valid RCMM facility 
            if((IF == XC_NANO_CCM_PORT0_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT1_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT2_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT3_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT4_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT5_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT6_FACILITY_ID) ||
               (IF == XC_NANO_CCM_PORT7_FACILITY_ID) ||
               (IF == XC_NANO_CCM_LINE_FACILITY_ID)  ||
               (IF == XC_NANO_CCM_EXPRESS_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_NANO_CCM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_NANO_CCM_PORT0_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT1_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT2_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT3_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT4_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT5_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT6_FACILITY_ID) ||
               (OF == XC_NANO_CCM_PORT7_FACILITY_ID) ||
               (OF == XC_NANO_CCM_LINE_FACILITY_ID)  ||
               (OF == XC_NANO_CCM_EXPRESS_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_NANO_CCM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = NANO_CCMConfigMap[OF];
            }          
        }
        else if (this->myCardType == CARD_TYPE_OTSM)//--- CADM Optical Transport Section Module Checks
        {
            //--- Check to see if this is a valid OTSM facility 
            if((IF == XC_CADM_LINE_FACILITY_ID)       ||
               (IF == XC_CADM_AUXILIARY0_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_CADM_LINE_FACILITY_ID)       ||
               (OF == XC_CADM_AUXILIARY0_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = CADMConfigMap[OF];
            }          
        }
        else if((this->myCardType == CARD_TYPE_OADM88IR) ||
                (this->myCardType == CARD_TYPE_OADM88LR) ||
                (this->myCardType == CARD_TYPE_OADM88ER) ||
                (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                (this->myCardType == CARD_TYPE_OADM8DSIR) ||
                (this->myCardType == CARD_TYPE_OADM8DSLR) ||
                (this->myCardType == CARD_TYPE_OADM8DSER))//--- CADM Optical Add/Drop Module Checks
        {
            //--- Check to see if this is a valid OADM facility 
            if((IF == XC_CADM_LINE_FACILITY_ID)       ||
               (IF == XC_CADM_EXPRESS0_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS1_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS2_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS3_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS4_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS5_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS6_FACILITY_ID)   ||
               (IF == XC_CADM_AUXILIARY0_FACILITY_ID) ||
               (IF == XC_CADM_AUXILIARY1_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_CADM_LINE_FACILITY_ID)       ||
               (OF == XC_CADM_EXPRESS0_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS1_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS2_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS3_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS4_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS5_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS6_FACILITY_ID)   ||
               (OF == XC_CADM_AUXILIARY0_FACILITY_ID) ||
               (OF == XC_CADM_AUXILIARY1_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = CADMConfigMap[OF];
            }          
        }
        else if (this->myCardType == CARD_TYPE_DXOADM)
        {
            //--- Check to see if this is a valid facility 
            if((IF == XC_CADM_EXPRESS0_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS1_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS2_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS3_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS4_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS5_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS6_FACILITY_ID)   ||
               (IF == XC_CADM_LINE_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_CADM_EXPRESS0_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS1_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS2_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS3_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS4_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS5_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS6_FACILITY_ID)   ||
               (OF == XC_CADM_LINE_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = CADMConfigMap[OF];
            }          
        }
        else if((this->myCardType == CARD_TYPE_CCM88IR) ||
                (this->myCardType == CARD_TYPE_CCM88LR) ||
                (this->myCardType == CARD_TYPE_CCM88ER))//--- CADM Colorless Core Module Checks
        {
            //--- Check to see if this is a valid CCM facility 
            if((IF == XC_CADM_LINE_FACILITY_ID)       ||
               (IF == XC_CADM_PORT0_FACILITY_ID)      ||
               (IF == XC_CADM_PORT1_FACILITY_ID)      ||
               (IF == XC_CADM_PORT2_FACILITY_ID)      ||
               (IF == XC_CADM_PORT3_FACILITY_ID)      ||
               (IF == XC_CADM_PORT4_FACILITY_ID)      ||
               (IF == XC_CADM_PORT5_FACILITY_ID)      ||
               (IF == XC_CADM_PORT6_FACILITY_ID)      ||
               (IF == XC_CADM_PORT7_FACILITY_ID)      ||
               (IF == XC_CADM_EXPRESS0_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS1_FACILITY_ID)   ||
               (IF == XC_CADM_EXPRESS2_FACILITY_ID)   ||
               (IF == XC_CADM_AUXILIARY0_FACILITY_ID) ||
               (IF == XC_CADM_AUXILIARY1_FACILITY_ID))
            {
                if(IFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
       
            //--- Check to see if this is a valid facility 
            if((OF == XC_CADM_LINE_FACILITY_ID)       ||
               (OF == XC_CADM_PORT0_FACILITY_ID)      ||
               (OF == XC_CADM_PORT1_FACILITY_ID)      ||
               (OF == XC_CADM_PORT2_FACILITY_ID)      ||
               (OF == XC_CADM_PORT3_FACILITY_ID)      ||
               (OF == XC_CADM_PORT4_FACILITY_ID)      ||
               (OF == XC_CADM_PORT5_FACILITY_ID)      ||
               (OF == XC_CADM_PORT6_FACILITY_ID)      ||
               (OF == XC_CADM_PORT7_FACILITY_ID)      ||
               (OF == XC_CADM_EXPRESS0_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS1_FACILITY_ID)   ||
               (OF == XC_CADM_EXPRESS2_FACILITY_ID)   ||
               (OF == XC_CADM_AUXILIARY0_FACILITY_ID) ||
               (OF == XC_CADM_AUXILIARY1_FACILITY_ID))
            {
                if(OFE > XC_MAX_XC_CADM_LINE)
                {
                    Valid = FALSE;
                }
            }
            //--- Unknown
            else
            {
                Valid = FALSE;
            }
            
            if(Valid)
            {
                *FacilityOffsetPtr = CADMConfigMap[OF];
            }          
        }

        //--- Validation check for the OMMX module.
        else if(this->myCardType == CARD_TYPE_OMMX)
        {
            switch (IF) 
            {
                //ODU XC
                case XC_OMMX_ODUXC_ODUK_0_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_0_VIRTUAL_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_1_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_1_VIRTUAL_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_2_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_2_VIRTUAL_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_3_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUK_3_VIRTUAL_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODUXC_OTNK);
                    break;

                case XC_OMMX_ODUXC_ODU1_FACILITY_ID:
                case XC_OMMX_ODUXC_ODU1_VIRTUAL_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODUXC_OTN1);
                    break;

                case XC_OMMX_ODUXC_ODU2_FACILITY_ID:
                case XC_OMMX_ODUXC_ODU2_VIRTUAL_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODUXC_OTN2);
                    break;

                case XC_OMMX_ODUXC_ODUKPP_ODUK0_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUKPP_ODUK1_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK);
                    break;
                case XC_OMMX_ODUXC_ODUKPP_ODU1_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1);
                    break;
                case XC_OMMX_ODUXC_ODUKPP_ODU2_FACILITY_ID:
                case XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2);
                    break;

                //Frame XC
                case XC_OMMX_FRMODUXC_FRM_OTUK_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_OTUK);
                    break;

                case XC_OMMX_FRMODUXC_FRM_OTU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU1);
                    break;

                case XC_OMMX_FRMODUXC_FRM_OTU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU2);
                    break;
    
                case XC_OMMX_FRMODUXC_FRM_CBR_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR);
                    break;
    
                case XC_OMMX_FRMODUXC_FRM_CBR10G_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR10G);
                    break;

                case XC_OMMX_FRMODUXC_FRM_GE_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_GE);
                    break;

                case XC_OMMX_FRMODUXC_FRM_GE10G_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_GE10G);
                    break;


                case XC_OMMX_FRMODUXC_ODU_OTUK_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_OTUK);
                    break;

                case XC_OMMX_FRMODUXC_ODU_OTU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU1);
                    break;
    
                case XC_OMMX_FRMODUXC_ODU_OTU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU2);
                    break;

                case XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID:
                case XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU2);
                    break;

                case XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID:
                case XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU1);
                    break;

                case XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID:
                case XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODUK);
                    break;

                //ODU21 MUX
                case XC_OMMX_ODU21XC_ODU2_0_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU21XC_ODU2);
                    break;

                case XC_OMMX_ODU21XC_ODU1_0_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_1_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_2_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_3_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_4_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_5_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_6_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_7_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_8_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_9_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_10_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_11_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_12_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_13_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_14_FACILITY_ID:
                case XC_OMMX_ODU21XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU21XC_ODU1);
                    break;

                //ODU20 MUX
                case XC_OMMX_ODU20XC_ODU2_0_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU20XC_ODU2);
                    break;

                case XC_OMMX_ODU20XC_ODU0_0_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_1_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_2_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_3_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_4_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_5_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_6_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_7_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_8_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_9_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_10_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_11_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_12_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_13_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_14_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_15_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_16_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_17_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_18_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_19_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_20_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_21_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_22_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_23_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_24_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_25_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_26_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_27_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_28_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_29_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_30_FACILITY_ID:
                case XC_OMMX_ODU20XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU20XC_ODU0);
                    break;

                //ODU2F MUX
                case XC_OMMX_ODU2FXC_ODU2_0_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODU2_1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU2FXC_ODU2);
                    break;

                case XC_OMMX_ODU2FXC_ODUF_0_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_1_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_2_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_3_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_4_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_5_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_6_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_7_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_8_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_9_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_10_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_11_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_12_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_13_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_14_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_15_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_16_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_17_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_18_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_19_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_20_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_21_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_22_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_23_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_24_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_25_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_26_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_27_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_28_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_29_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_30_FACILITY_ID:
                case XC_OMMX_ODU2FXC_ODUF_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU2FXC_ODUF);
                    break;

                //ODU10 MUX
                case XC_OMMX_ODU10XC_ODU1_0_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_1_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_2_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_3_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_4_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_5_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_6_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_7_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_8_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_9_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_10_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_11_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_12_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_13_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_14_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU1_15_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU10XC_ODU1);
                    break;

                case XC_OMMX_ODU10XC_ODU0_0_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_1_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_2_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_3_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_4_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_5_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_6_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_7_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_8_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_9_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_10_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_11_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_12_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_13_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_14_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_15_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_16_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_17_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_18_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_19_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_20_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_21_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_22_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_23_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_24_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_25_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_26_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_27_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_28_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_29_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_30_FACILITY_ID:
                case XC_OMMX_ODU10XC_ODU0_31_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OMMX_ODU10XC_ODU0);
                    break;

                default:
                    Valid = FALSE;
                    break;
            }

            if (Valid)
            {
                switch (OF) 
                {
                    //ODU XC
                    case XC_OMMX_ODUXC_ODUK_0_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_0_VIRTUAL_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_1_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_1_VIRTUAL_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_2_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_2_VIRTUAL_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_3_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUK_3_VIRTUAL_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODUXC_OTNK);
                        break;
    
                    case XC_OMMX_ODUXC_ODU1_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODU1_VIRTUAL_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODUXC_OTN1);
                        break;
    
                    case XC_OMMX_ODUXC_ODU2_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODU2_VIRTUAL_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODUXC_OTN2);
                        break;
    
                    case XC_OMMX_ODUXC_ODUKPP_ODUK0_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUKPP_ODUK1_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK);
                        break;
                    case XC_OMMX_ODUXC_ODUKPP_ODU1_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1);
                        break;
                    case XC_OMMX_ODUXC_ODUKPP_ODU2_FACILITY_ID:
                    case XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2);
                        break;
    
                    //Frame XC
                    case XC_OMMX_FRMODUXC_FRM_OTUK_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_OTUK);
                        break;
    
                    case XC_OMMX_FRMODUXC_FRM_OTU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU1);
                        break;
    
                    case XC_OMMX_FRMODUXC_FRM_OTU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU2);
                        break;
        
                    case XC_OMMX_FRMODUXC_FRM_CBR_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR);
                        break;
        
                    case XC_OMMX_FRMODUXC_FRM_CBR10G_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR10G);
                        break;
    
                    case XC_OMMX_FRMODUXC_FRM_GE_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_GE);
                        break;
    
                    case XC_OMMX_FRMODUXC_FRM_GE10G_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_FRM_GE10G);
                        break;
    
    
                    case XC_OMMX_FRMODUXC_ODU_OTUK_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_OTUK);
                        break;
    
                    case XC_OMMX_FRMODUXC_ODU_OTU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU1);
                        break;
        
                    case XC_OMMX_FRMODUXC_ODU_OTU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU2);
                        break;

                    case XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID:
                    case XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU2);
                        break;

                    case XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID:
                    case XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU1);
                        break;

                    case XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID:
                    case XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODUK);
                        break;

                    //ODU21 MUX
                    case XC_OMMX_ODU21XC_ODU2_0_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU21XC_ODU2);
                        break;
    
                    case XC_OMMX_ODU21XC_ODU1_0_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_1_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_2_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_3_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_4_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_5_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_6_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_7_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_8_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_9_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_10_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_11_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_12_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_13_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_14_FACILITY_ID:
                    case XC_OMMX_ODU21XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU21XC_ODU1);
                        break;
    
                    //ODU20 MUX
                    case XC_OMMX_ODU20XC_ODU2_0_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU20XC_ODU2);
                        break;
    
                    case XC_OMMX_ODU20XC_ODU0_0_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_1_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_2_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_3_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_4_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_5_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_6_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_7_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_8_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_9_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_10_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_11_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_12_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_13_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_14_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_15_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_16_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_17_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_18_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_19_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_20_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_21_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_22_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_23_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_24_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_25_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_26_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_27_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_28_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_29_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_30_FACILITY_ID:
                    case XC_OMMX_ODU20XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU20XC_ODU0);
                        break;
    
                    //ODU2F MUX
                    case XC_OMMX_ODU2FXC_ODU2_0_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODU2_1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU2FXC_ODU2);
                        break;
    
                    case XC_OMMX_ODU2FXC_ODUF_0_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_1_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_2_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_3_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_4_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_5_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_6_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_7_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_8_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_9_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_10_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_11_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_12_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_13_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_14_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_15_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_16_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_17_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_18_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_19_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_20_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_21_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_22_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_23_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_24_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_25_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_26_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_27_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_28_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_29_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_30_FACILITY_ID:
                    case XC_OMMX_ODU2FXC_ODUF_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU2FXC_ODUF);
                        break;
    
                    //ODU10 MUX
                    case XC_OMMX_ODU10XC_ODU1_0_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_1_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_2_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_3_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_4_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_5_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_6_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_7_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_8_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_9_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_10_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_11_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_12_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_13_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_14_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU1_15_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU10XC_ODU1);
                        break;
    
                    case XC_OMMX_ODU10XC_ODU0_0_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_1_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_2_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_3_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_4_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_5_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_6_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_7_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_8_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_9_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_10_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_11_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_12_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_13_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_14_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_15_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_16_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_17_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_18_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_19_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_20_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_21_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_22_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_23_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_24_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_25_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_26_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_27_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_28_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_29_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_30_FACILITY_ID:
                    case XC_OMMX_ODU10XC_ODU0_31_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OMMX_ODU10XC_ODU0);
                        break;

                    default:
                        Valid = FALSE;
                        break;
                }
            }

            if(Valid)
            {
                *FacilityOffsetPtr = OMMXConfigMap[OF];
            }
        }

        //--- Validation check for the OSM2C/S
        else if ( (this->myCardType == CARD_TYPE_OSM2C) || (this->myCardType == CARD_TYPE_OSM2S) )
        {
            switch (IF) 
            {
                case XC_OSM_ODUXC_ODUK_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_ODUK_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_ODUK);
                    break;

                case XC_OSM_ODUXC_ODU1_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_ODU1_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_ODU1);
                    break;

                case XC_OSM_ODUXC_ODU2_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_ODU2_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_ODU2);
                    break;

                case XC_OSM_ODUXC_ODU3_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_ODU3_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_ODU3);
                    break;

                case XC_OSM_ODUXC_ODU4_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_ODU4_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_ODU4);
                    break;

                case XC_OSM_ODUXC_CLIENT_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_CLIENT_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_CLIENT);
                    break;

                case XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID:
                case XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_XC_OSM_ODUXC_IMUX);
                    break;

                default:
                    Valid = false;
                    break;
            }

            if (Valid)
            {
                switch (OF) 
                {
                    case XC_OSM_ODUXC_ODUK_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_ODUK_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_ODUK);
                        break;

                    case XC_OSM_ODUXC_ODU1_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_ODU1_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_ODU1);
                        break;

                    case XC_OSM_ODUXC_ODU2_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_ODU2_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_ODU2);
                        break;

                    case XC_OSM_ODUXC_ODU3_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_ODU3_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_ODU3);
                        break;

                    case XC_OSM_ODUXC_ODU4_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_ODU4_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_ODU4);
                        break;

                    case XC_OSM_ODUXC_CLIENT_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_CLIENT_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_CLIENT);
                        break;

                    case XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID:
                    case XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_XC_OSM_ODUXC_IMUX);
                        break;

                    default:
                        Valid = false;
                        break;
                }     
            }

            if(Valid)
            {
                *FacilityOffsetPtr = OSMOduXcConfigMap[OF];
            }
        }

        //--- Validation check for the OSM1S
        else if ( this->myCardType == CARD_TYPE_OSM1S )
        {
            switch (IF) 
            {
                case XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_ODUXC_ODUK);
                    break;

                case XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_ODUXC_ODU1);
                    break;

                case XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK);
                    break;

                case XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1);
                    break;

                case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_ODUXC_IMUX);
                    break;

                default:
                    Valid = false;
                    break;
            }

            if (Valid)
            {
                switch (OF) 
                {
                    case XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_ODUXC_ODUK);
                        break;

                    case XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_ODUXC_ODU1);
                        break;

                    case XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK);
                        break;

                    case XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1);
                        break;

                    case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID:
                    case XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_ODUXC_IMUX);
                        break;

                    default:
                        Valid = false;
                        break;
                }     
            }

            if(Valid)
            {
                *FacilityOffsetPtr = OSM1SOduXcConfigMap[OF];
            }
        }

        else
        {
            Valid = FALSE;
        }
    }

    if (!Valid)
    {
        char errMsg[200];
        sprintf(errMsg, "TSXC_ConfigRegion<T>::FindValidOffset(IF= %d, IFE= %d, OF= %d, OFE= %d) returning FALSE for cardType = %d", 
                        IF, IFE, OF, OFE, this->myCardType);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return Valid;
}


//----------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::GetFacilityIdFromIntfId(uint8 * theFacility, CT_IntfId theIntfId )
{     
    switch (theIntfId)
    {
        case CT_LINE_SIDE_0:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_DWDM_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_DWDM_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_DWDM_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_LINE_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_LINE_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_LINE_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OTSM) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_LINE_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_1:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_DWDM_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_DWDM_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_DWDM_FACILITY_ID;
            }             
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU2_OCHP_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_EXPRESS0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_EXPRESS_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_EXPRESS_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_2:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_LINE_FACILITY_ID;
            }
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_LINE_FACILITY_ID;
            }              
            else if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS1_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_3:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_LINE_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_LINE_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS2_FACILITY_ID;
            }
            // CT_LINE_SIDE_3 is common way of addressing IMUXL
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGSM)
            {
                *theFacility = XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_IMUX_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_4:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            } 
            else if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS3_FACILITY_ID;
            }
            // CT_LINE_SIDE_4 is common way of addressing IMUXP
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_5:
            if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS4_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_6:
            if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS5_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_7:
            if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS6_FACILITY_ID;
            }
            break;
            
        case CT_LINE_SIDE_8:
            if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_EXPRESS7_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_DWDM_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_9:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_DWDM_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_10:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_DWDM_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_11:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE4_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_DWDM_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_12:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE5_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_13:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE6_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_14:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE7_FACILITY_ID;
            }
            break;

        case CT_LINE_SIDE_15:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE8_FACILITY_ID;
            }
            break;

            //---------------------- Start of the port side translation             
        case CT_PORT_SIDE_0:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT0_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT0_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_ODU2_PORT0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT0_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) ||
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT0_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS
            {
                *theFacility = HGTMM_XC_ODU3_CLIENT_1_FACILITY_ID;
            }			
            break;
            
        case CT_PORT_SIDE_1:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT1_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT1_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_ODU2_PORT1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT1_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT1_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT1_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS
            {
                *theFacility = HGTMM_XC_ODU3_CLIENT_2_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_2:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT2_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT2_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_ODU2_PORT2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT2_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT2_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT2_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_3_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_3:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT3_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT3_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT3_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_ODU2_PORT3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT3_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT3_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT3_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_4_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_4:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT4_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT4_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT4_FACILITY_ID;
            } 
            else if (this->myCardType == CARD_TYPE_FGTMM)
            {
                *theFacility = XC_FGTMM_DWDM_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT4_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT4_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT4_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT4_FACILITY_ID;
            }
            if ((this->myCardType == CARD_TYPE_CCMIR) || 
                (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT4_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT4_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT4_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_5_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_5:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT5_FACILITY_ID;
            }
            if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT5_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT5_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT5_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT5_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT5_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT5_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT5_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT5_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT5_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_6_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_6:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT6_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT6_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT6_FACILITY_ID;
            } 
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT6_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT6_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT6_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT6_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT6_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT6_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT6_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_7_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_7:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT7_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT7_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT7_FACILITY_ID;
            } 
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT7_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT7_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT7_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT7_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCMIR) || 
                    (this->myCardType == CARD_TYPE_CCMLR) ||(this->myCardType == CARD_TYPE_CCMER)) 
            {
                *theFacility = XC_NANO_CCM_PORT7_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR) ||
                     (this->myCardType == CARD_TYPE_CCM88LR) ||
                     (this->myCardType == CARD_TYPE_CCM88ER)) 
            {
                *theFacility = XC_CADM_PORT7_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_DCMM) 
            {
                *theFacility = XC_DCMM_PORT7_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_8_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_8: 
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT8_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT8_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT8_FACILITY_ID;
            } 
            else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_PORT8_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT8_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT8_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT8_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_9_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_9:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_PORT9_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SMTMUD) || (this->myCardType == CARD_TYPE_SMTMSD))
            {
                *theFacility = XC_SMTMUDSD_PORT9_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT9_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT9_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT9_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT9_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_10_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_10:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT10_FACILITY_ID;
            }        
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT10_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT10_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT10_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_11_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_11:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT11_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT11_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT11_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT11_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER))
            {
                *theFacility = XC_CADM_AUXILIARY1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU2F_CLIENT_12_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_12:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_PORT12_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT12_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT12_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT12_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OTSM) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER))
            {
                *theFacility = XC_CADM_AUXILIARY0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HGTMM || this->myCardType == CARD_TYPE_HGTMMS) // Coriant HGTMMS 
            {
                *theFacility = HGTMM_XC_ODU4_LINE_FACILITY_ID;
            }						
            break;
            
        case CT_PORT_SIDE_13:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT13_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT13_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT13_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OTSM) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS3_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_14:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG)
            {
                *theFacility = XC_HDTG_ODU2_PORT14_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT14_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT14_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OTSM) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D) ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS4_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_15:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT15_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_HDTG2)
            {
                *theFacility = XC_HDTG2_ODU2F_PORT15_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OTSM) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS5_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_16:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT16_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_CCM88IR)   ||
                     (this->myCardType == CARD_TYPE_CCM88LR)   ||
                     (this->myCardType == CARD_TYPE_CCM88ER)   ||
                     (this->myCardType == CARD_TYPE_OADM88IR)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER)  ||
                     (this->myCardType == CARD_TYPE_OTSM) ||
                     (this->myCardType == CARD_TYPE_OADM88IR8D)  ||
                     (this->myCardType == CARD_TYPE_OADM88LR8D)  ||
                     (this->myCardType == CARD_TYPE_OADM88ER8D) ||
                     (this->myCardType == CARD_TYPE_OADM8DSIR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSLR)  ||
                     (this->myCardType == CARD_TYPE_OADM8DSER)  ||
                     (this->myCardType == CARD_TYPE_DXOADM))
            {
                *theFacility = XC_CADM_EXPRESS6_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_17:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT17_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            break;
            
        case CT_PORT_SIDE_18:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT18_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_19:
            if (this->myCardType == CARD_TYPE_SMTMU)
            {
                *theFacility = XC_SMTMU_IM_PORT_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }              
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT19_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_20:
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT20_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_21:
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_PORT21_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_22:
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT22_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_23:
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_PORT23_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_24:
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }             
            else if (this->myCardType == CARD_TYPE_RCMM)
            {
                *theFacility = XC_RCMM_PORT24_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_25:
            if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_IM_PORT_FACILITY_ID;
            }              
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT25_FACILITY_ID;
            }
            break;
            
        case CT_PORT_SIDE_26:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU2_HIGHSPEED_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT26_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_27:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU2_ODU12MUX_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT27_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_28:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_OC192_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT28_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_29:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE9_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT29_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_30:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE10_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT30_FACILITY_ID;
            }
            break;

    case CT_PORT_SIDE_31:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE11_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT31_FACILITY_ID;
            }
            break;

        case CT_PORT_SIDE_32:
            if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD))
            {
                *theFacility = XC_OTNM_ODU1_MIDLINE12_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSMX) || (this->myCardType == CARD_TYPE_SSMD))
            {
                *theFacility = XC_SSM_TTP_FACILITY_ID;
            }              
            else if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT32_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_33:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT33_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_34:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT34_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_35:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT35_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_36:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT36_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_37:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT37_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_38:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT38_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_39:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT39_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_40:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT40_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_OTNOTU1_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGSM)
            {
                *theFacility = XC_FGSM_ODUXC_ODU_OTNOTU0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUK_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUK_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODUK_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_41:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT41_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_OTNOTU2_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGSM)
            {
                *theFacility = XC_FGSM_ODUXC_ODU_OTNOTU1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUK_1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUK_1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU1_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_42:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT42_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCATA_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_FGSM)
            {
                *theFacility = XC_FGSM_ODUXC_ODU_OTNOTU2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUK_2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUK_2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU2_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_43:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT43_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCATB_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUK_3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUK_3_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU3_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_44:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT44_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_OTNOTU1_1_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUKPP_ODUK0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUKPP_ODUK0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU4_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_45:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT45_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_OTNOTU2_1_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUKPP_ODUK1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUKPP_ODUK1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_CLIENT_DIGI0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_46:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT46_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCATA_1_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODU1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODU1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODUK_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_47:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT47_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCATB_1_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUKPP_ODU1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUKPP_ODU1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU1_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_48:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT48_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_OTNOTU0_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODU2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODU2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU2_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_49:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT49_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCAT0A_0_FACILITY_ID;
            }            
            else if (this->myCardType == CARD_TYPE_OSM20)
            {
                *theFacility = XC_OSM20_ODUXC_ODUKPP_ODU2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OMMX)
            {
                *theFacility = XC_OMMX_ODUXC_ODUKPP_ODU2_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU3_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_50:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT50_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCAT0B_0_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_ODU4_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_51:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT51_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_OTNOTU0_1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM2S || this->myCardType == CARD_TYPE_OSM2C)
            {
                *theFacility = XC_OSM_ODUXC_CLIENT_DIGI1_FACILITY_ID;
            }
            else if (this->myCardType == CARD_TYPE_OSM1S)
            {
                *theFacility = XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_52:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT52_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCAT0A_1_FACILITY_ID;
            }            
            break;
        case CT_PORT_SIDE_53:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT53_FACILITY_ID;
            }
            else if ((this->myCardType == CARD_TYPE_SSM40) || (this->myCardType == CARD_TYPE_OSM40))
            {
                *theFacility = XC_SSM40_ODUXC_ODU_VCAT0B_1_FACILITY_ID;
            }            
            break;
        case CT_PORT_SIDE_54:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT54_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_55:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT55_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_56:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT56_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_57:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT57_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_58:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT58_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_59:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT59_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_60:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT60_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_61:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT61_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_62:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT62_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_63:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT63_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_64:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT64_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_65:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT65_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_66:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT66_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_67:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT67_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_68:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT68_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_69:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT69_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_70:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT70_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_71:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT71_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_72:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT72_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_73:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT73_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_74:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT74_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_75:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT75_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_76:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT76_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_77:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT77_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_78:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT78_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_79:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT79_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_80:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT80_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_81:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT81_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_82:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT82_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_83:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT83_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_84:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT84_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_85:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT85_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_86:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT86_FACILITY_ID;
            }
            break;
        case CT_PORT_SIDE_87:
            if (this->myCardType == CARD_TYPE_RCMM) 
            {
                *theFacility = XC_RCMM_PORT87_FACILITY_ID;
            }
            break;
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::GetFacilityIdFromAGPortId(uint8 * theFacility, CT_AG_PortId theAGPortId)
{
    GetFacilityIdFromIntfId( theFacility, ConvertAGPort2IntfId(theAGPortId) );
}
     
//------------------------------------------------------------------------------------------------------------------------
//--- Used only for SMTM-M/UD/SD and OTNM
//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::GetFacilityIdFromPortNum(uint8 * theFacility, uint8 thePortNum)
{
    *theFacility = 0;

    if ((this->myCardType == CARD_TYPE_SMTMUD || this->myCardType == CARD_TYPE_SMTMSD) && thePortNum < XC_MAX_SMTMUDSD_PORT_INTF)
    {
        *theFacility = XC_SMTMUDSD_PORT0_FACILITY_ID + thePortNum;
    }
    else if ((this->myCardType == CARD_TYPE_OTNMX) || (this->myCardType == CARD_TYPE_OTNMD) && (thePortNum <= XC_MAX_OTNM_PORT_INTF))
    {
        *theFacility = XC_OTNM_PORT1_FACILITY_ID + (thePortNum - 1);        
    }
    FC_THROW_ERROR_IF(*theFacility == 0, FC_LogicError, "Matching facility not found.");
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> CT_IntfId TSXC_ConfigRegion<T>::ConvertAGPort2IntfId(CT_AG_PortId theAGPortId)
{
    CT_IntfId aIntfId = CT_INTF_ID_UNKNOWN;

    if ((theAGPortId >= CT_AG_PORT_0) && (theAGPortId <= CT_AG_PORT_88))
        aIntfId = (CT_IntfId) theAGPortId;
   
    else if ((theAGPortId >= CT_AG_LINE_0) && (theAGPortId <= CT_AG_LINE_11))
        aIntfId = (CT_IntfId) (theAGPortId - CT_AG_LINE_0 + CT_LINE_SIDE_0);
   
    return  aIntfId;
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::FrmXc_Ssm40FrontEndDevToFac(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev)
{
    uint8  retVal;
    char   errMsg[100];

    switch(theSsm40FrontEndDev)
    {
        /*** HyPhy 0 ***/
        case CT_TEL_SSM40_DEV1_SONET48_0:
        case CT_TEL_SSM40_DEV2_SONET48_0:
        case CT_TEL_SSM40_DEV3_SONET48_0:
        case CT_TEL_SSM40_DEV4_SONET48_0:
        case CT_TEL_SSM40_DEV5_SONET48_0:
        case CT_TEL_SSM40_DEV6_SONET48_0:
        case CT_TEL_SSM40_DEV7_SONET48_0:
        case CT_TEL_SSM40_DEV8_SONET48_0:
        case CT_TEL_SSM40_DEV9_SONET48_0:
        case CT_TEL_SSM40_DEV10_SONET48_0:
        case CT_TEL_SSM40_DEV11_SONET48_0:
        case CT_TEL_SSM40_DEV12_SONET48_0:
        case CT_TEL_SSM40_DEV13_SONET48_0:
        case CT_TEL_SSM40_DEV14_SONET48_0:
        case CT_TEL_SSM40_DEV15_SONET48_0:
        case CT_TEL_SSM40_DEV16_SONET48_0:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_SONET192_0:
        case CT_TEL_SSM40_DEV2_SONET192_0:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR10G_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_OTU0_0:
        case CT_TEL_SSM40_DEV2_OTU0_0:
        case CT_TEL_SSM40_DEV3_OTU0_0:
        case CT_TEL_SSM40_DEV4_OTU0_0:
        case CT_TEL_SSM40_DEV5_OTU0_0:
        case CT_TEL_SSM40_DEV6_OTU0_0:
        case CT_TEL_SSM40_DEV7_OTU0_0:
        case CT_TEL_SSM40_DEV8_OTU0_0:
        case CT_TEL_SSM40_DEV9_OTU0_0:
        case CT_TEL_SSM40_DEV10_OTU0_0:
        case CT_TEL_SSM40_DEV11_OTU0_0:
        case CT_TEL_SSM40_DEV12_OTU0_0:
        case CT_TEL_SSM40_DEV13_OTU0_0:
        case CT_TEL_SSM40_DEV14_OTU0_0:
        case CT_TEL_SSM40_DEV15_OTU0_0:
        case CT_TEL_SSM40_DEV16_OTU0_0:
            retVal = XC_SSM40_FRMODUXC_FRM_OTU0_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_OTU1_0:
        case CT_TEL_SSM40_DEV2_OTU1_0:
        case CT_TEL_SSM40_DEV3_OTU1_0:
        case CT_TEL_SSM40_DEV4_OTU1_0:
        case CT_TEL_SSM40_DEV5_OTU1_0:
        case CT_TEL_SSM40_DEV6_OTU1_0:
        case CT_TEL_SSM40_DEV7_OTU1_0:
        case CT_TEL_SSM40_DEV8_OTU1_0:
            retVal = XC_SSM40_FRMODUXC_FRM_OTU1_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_OTU2_0:
        case CT_TEL_SSM40_DEV2_OTU2_0:
            retVal = XC_SSM40_FRMODUXC_FRM_OTU2_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_CBR_0:
        case CT_TEL_SSM40_DEV2_CBR_0:
        case CT_TEL_SSM40_DEV3_CBR_0:
        case CT_TEL_SSM40_DEV4_CBR_0:
        case CT_TEL_SSM40_DEV5_CBR_0:
        case CT_TEL_SSM40_DEV6_CBR_0:
        case CT_TEL_SSM40_DEV7_CBR_0:
        case CT_TEL_SSM40_DEV8_CBR_0:
        case CT_TEL_SSM40_DEV9_CBR_0:
        case CT_TEL_SSM40_DEV10_CBR_0:
        case CT_TEL_SSM40_DEV11_CBR_0:
        case CT_TEL_SSM40_DEV12_CBR_0:
        case CT_TEL_SSM40_DEV13_CBR_0:
        case CT_TEL_SSM40_DEV14_CBR_0:
        case CT_TEL_SSM40_DEV15_CBR_0:
        case CT_TEL_SSM40_DEV16_CBR_0:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_CBR10G_0:
        case CT_TEL_SSM40_DEV2_CBR10G_0:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR10G_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_GE_0:
        case CT_TEL_SSM40_DEV2_GE_0:
        case CT_TEL_SSM40_DEV3_GE_0:
        case CT_TEL_SSM40_DEV4_GE_0:
        case CT_TEL_SSM40_DEV5_GE_0:
        case CT_TEL_SSM40_DEV6_GE_0:
        case CT_TEL_SSM40_DEV7_GE_0:
        case CT_TEL_SSM40_DEV8_GE_0:
        case CT_TEL_SSM40_DEV9_GE_0:
        case CT_TEL_SSM40_DEV10_GE_0:
        case CT_TEL_SSM40_DEV11_GE_0:
        case CT_TEL_SSM40_DEV12_GE_0:
        case CT_TEL_SSM40_DEV13_GE_0:
        case CT_TEL_SSM40_DEV14_GE_0:
        case CT_TEL_SSM40_DEV15_GE_0:
        case CT_TEL_SSM40_DEV16_GE_0:
            retVal = XC_SSM40_FRMODUXC_FRM_GE_0_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_GE10G_0:
        case CT_TEL_SSM40_DEV2_GE10G_0:
            retVal = XC_SSM40_FRMODUXC_FRM_GE10G_0_FACILITY_ID;
            break;

        /*** HyPhy 1 ***/
        case CT_TEL_SSM40_DEV1_SONET48_1:
        case CT_TEL_SSM40_DEV2_SONET48_1:
        case CT_TEL_SSM40_DEV3_SONET48_1:
        case CT_TEL_SSM40_DEV4_SONET48_1:
        case CT_TEL_SSM40_DEV5_SONET48_1:
        case CT_TEL_SSM40_DEV6_SONET48_1:
        case CT_TEL_SSM40_DEV7_SONET48_1:
        case CT_TEL_SSM40_DEV8_SONET48_1:
        case CT_TEL_SSM40_DEV9_SONET48_1:
        case CT_TEL_SSM40_DEV10_SONET48_1:
        case CT_TEL_SSM40_DEV11_SONET48_1:
        case CT_TEL_SSM40_DEV12_SONET48_1:
        case CT_TEL_SSM40_DEV13_SONET48_1:
        case CT_TEL_SSM40_DEV14_SONET48_1:
        case CT_TEL_SSM40_DEV15_SONET48_1:
        case CT_TEL_SSM40_DEV16_SONET48_1:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_SONET192_1:
        case CT_TEL_SSM40_DEV2_SONET192_1:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR10G_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_OTU0_1:
        case CT_TEL_SSM40_DEV2_OTU0_1:
        case CT_TEL_SSM40_DEV3_OTU0_1:
        case CT_TEL_SSM40_DEV4_OTU0_1:
        case CT_TEL_SSM40_DEV5_OTU0_1:
        case CT_TEL_SSM40_DEV6_OTU0_1:
        case CT_TEL_SSM40_DEV7_OTU0_1:
        case CT_TEL_SSM40_DEV8_OTU0_1:
        case CT_TEL_SSM40_DEV9_OTU0_1:
        case CT_TEL_SSM40_DEV10_OTU0_1:
        case CT_TEL_SSM40_DEV11_OTU0_1:
        case CT_TEL_SSM40_DEV12_OTU0_1:
        case CT_TEL_SSM40_DEV13_OTU0_1:
        case CT_TEL_SSM40_DEV14_OTU0_1:
        case CT_TEL_SSM40_DEV15_OTU0_1:
        case CT_TEL_SSM40_DEV16_OTU0_1:
            retVal = XC_SSM40_FRMODUXC_FRM_OTU0_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_OTU1_1:
        case CT_TEL_SSM40_DEV2_OTU1_1:
        case CT_TEL_SSM40_DEV3_OTU1_1:
        case CT_TEL_SSM40_DEV4_OTU1_1:
        case CT_TEL_SSM40_DEV5_OTU1_1:
        case CT_TEL_SSM40_DEV6_OTU1_1:
        case CT_TEL_SSM40_DEV7_OTU1_1:
        case CT_TEL_SSM40_DEV8_OTU1_1:
            retVal = XC_SSM40_FRMODUXC_FRM_OTU1_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_OTU2_1:
        case CT_TEL_SSM40_DEV2_OTU2_1:
            retVal = XC_SSM40_FRMODUXC_FRM_OTU2_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_CBR_1:
        case CT_TEL_SSM40_DEV2_CBR_1:
        case CT_TEL_SSM40_DEV3_CBR_1:
        case CT_TEL_SSM40_DEV4_CBR_1:
        case CT_TEL_SSM40_DEV5_CBR_1:
        case CT_TEL_SSM40_DEV6_CBR_1:
        case CT_TEL_SSM40_DEV7_CBR_1:
        case CT_TEL_SSM40_DEV8_CBR_1:
        case CT_TEL_SSM40_DEV9_CBR_1:
        case CT_TEL_SSM40_DEV10_CBR_1:
        case CT_TEL_SSM40_DEV11_CBR_1:
        case CT_TEL_SSM40_DEV12_CBR_1:
        case CT_TEL_SSM40_DEV13_CBR_1:
        case CT_TEL_SSM40_DEV14_CBR_1:
        case CT_TEL_SSM40_DEV15_CBR_1:
        case CT_TEL_SSM40_DEV16_CBR_1:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_CBR10G_1:
        case CT_TEL_SSM40_DEV2_CBR10G_1:
            retVal = XC_SSM40_FRMODUXC_FRM_CBR10G_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_GE_1:
        case CT_TEL_SSM40_DEV2_GE_1:
        case CT_TEL_SSM40_DEV3_GE_1:
        case CT_TEL_SSM40_DEV4_GE_1:
        case CT_TEL_SSM40_DEV5_GE_1:
        case CT_TEL_SSM40_DEV6_GE_1:
        case CT_TEL_SSM40_DEV7_GE_1:
        case CT_TEL_SSM40_DEV8_GE_1:
        case CT_TEL_SSM40_DEV9_GE_1:
        case CT_TEL_SSM40_DEV10_GE_1:
        case CT_TEL_SSM40_DEV11_GE_1:
        case CT_TEL_SSM40_DEV12_GE_1:
        case CT_TEL_SSM40_DEV13_GE_1:
        case CT_TEL_SSM40_DEV14_GE_1:
        case CT_TEL_SSM40_DEV15_GE_1:
        case CT_TEL_SSM40_DEV16_GE_1:
            retVal = XC_SSM40_FRMODUXC_FRM_GE_1_FACILITY_ID;
            break;

        case CT_TEL_SSM40_DEV1_GE10G_1:
        case CT_TEL_SSM40_DEV2_GE10G_1:
            retVal = XC_SSM40_FRMODUXC_FRM_GE10G_1_FACILITY_ID;
            break;

        default:
            retVal = 0;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::FrmXc_Ssm40FrontEndDevToFac(): Invalid FrontEndDev = %d", theSsm40FrontEndDev);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
            break;
    }

    return retVal;
}


//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::FrmXc_Ssm40FrontEndDevToFacEndpt(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev)
{
    uint8   retVal;
    char    errMsg[100];

    switch(theSsm40FrontEndDev)
    {
        /*** HyPhy 0 ***/
        case CT_TEL_SSM40_DEV1_SONET48_0:   retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_SONET48_0:   retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_SONET48_0:   retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_SONET48_0:   retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_SONET48_0:   retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_SONET48_0:   retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_SONET48_0:   retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_SONET48_0:   retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_SONET48_0:   retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_SONET48_0:  retVal = 10; break;
        case CT_TEL_SSM40_DEV11_SONET48_0:  retVal = 11; break;
        case CT_TEL_SSM40_DEV12_SONET48_0:  retVal = 12; break;
        case CT_TEL_SSM40_DEV13_SONET48_0:  retVal = 13; break;
        case CT_TEL_SSM40_DEV14_SONET48_0:  retVal = 14; break;
        case CT_TEL_SSM40_DEV15_SONET48_0:  retVal = 15; break;
        case CT_TEL_SSM40_DEV16_SONET48_0:  retVal = 16; break;

        case CT_TEL_SSM40_DEV1_SONET192_0:  retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_SONET192_0:  retVal = 2;  break;

        case CT_TEL_SSM40_DEV1_OTU0_0:      retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_OTU0_0:      retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_OTU0_0:      retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_OTU0_0:      retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_OTU0_0:      retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_OTU0_0:      retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_OTU0_0:      retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_OTU0_0:      retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_OTU0_0:      retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_OTU0_0:     retVal = 10; break;
        case CT_TEL_SSM40_DEV11_OTU0_0:     retVal = 11; break;
        case CT_TEL_SSM40_DEV12_OTU0_0:     retVal = 12; break;
        case CT_TEL_SSM40_DEV13_OTU0_0:     retVal = 13; break;
        case CT_TEL_SSM40_DEV14_OTU0_0:     retVal = 14; break;
        case CT_TEL_SSM40_DEV15_OTU0_0:     retVal = 15; break;
        case CT_TEL_SSM40_DEV16_OTU0_0:     retVal = 16; break;

        case CT_TEL_SSM40_DEV1_OTU1_0:      retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_OTU1_0:      retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_OTU1_0:      retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_OTU1_0:      retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_OTU1_0:      retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_OTU1_0:      retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_OTU1_0:      retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_OTU1_0:      retVal = 8;  break;

        case CT_TEL_SSM40_DEV1_OTU2_0:      retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_OTU2_0:      retVal = 2;  break;

        case CT_TEL_SSM40_DEV1_CBR_0:       retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_CBR_0:       retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_CBR_0:       retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_CBR_0:       retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_CBR_0:       retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_CBR_0:       retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_CBR_0:       retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_CBR_0:       retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_CBR_0:       retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_CBR_0:      retVal = 10; break;
        case CT_TEL_SSM40_DEV11_CBR_0:      retVal = 11; break;
        case CT_TEL_SSM40_DEV12_CBR_0:      retVal = 12; break;
        case CT_TEL_SSM40_DEV13_CBR_0:      retVal = 13; break;
        case CT_TEL_SSM40_DEV14_CBR_0:      retVal = 14; break;
        case CT_TEL_SSM40_DEV15_CBR_0:      retVal = 15; break;
        case CT_TEL_SSM40_DEV16_CBR_0:      retVal = 16; break;

        case CT_TEL_SSM40_DEV1_CBR10G_0:    retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_CBR10G_0:    retVal = 2;  break;

        case CT_TEL_SSM40_DEV1_GE_0:        retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_GE_0:        retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_GE_0:        retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_GE_0:        retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_GE_0:        retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_GE_0:        retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_GE_0:        retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_GE_0:        retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_GE_0:        retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_GE_0:       retVal = 10; break;
        case CT_TEL_SSM40_DEV11_GE_0:       retVal = 11; break;
        case CT_TEL_SSM40_DEV12_GE_0:       retVal = 12; break;
        case CT_TEL_SSM40_DEV13_GE_0:       retVal = 13; break;
        case CT_TEL_SSM40_DEV14_GE_0:       retVal = 14; break;
        case CT_TEL_SSM40_DEV15_GE_0:       retVal = 15; break;
        case CT_TEL_SSM40_DEV16_GE_0:       retVal = 16; break;

        case CT_TEL_SSM40_DEV1_GE10G_0:     retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_GE10G_0:     retVal = 2;  break;

        /*** HyPhy 1 ***/
        case CT_TEL_SSM40_DEV1_SONET48_1:   retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_SONET48_1:   retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_SONET48_1:   retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_SONET48_1:   retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_SONET48_1:   retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_SONET48_1:   retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_SONET48_1:   retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_SONET48_1:   retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_SONET48_1:   retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_SONET48_1:  retVal = 10; break;
        case CT_TEL_SSM40_DEV11_SONET48_1:  retVal = 11; break;
        case CT_TEL_SSM40_DEV12_SONET48_1:  retVal = 12; break;
        case CT_TEL_SSM40_DEV13_SONET48_1:  retVal = 13; break;
        case CT_TEL_SSM40_DEV14_SONET48_1:  retVal = 14; break;
        case CT_TEL_SSM40_DEV15_SONET48_1:  retVal = 15; break;
        case CT_TEL_SSM40_DEV16_SONET48_1:  retVal = 16; break;

        case CT_TEL_SSM40_DEV1_SONET192_1:  retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_SONET192_1:  retVal = 2;  break;

        case CT_TEL_SSM40_DEV1_OTU0_1:      retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_OTU0_1:      retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_OTU0_1:      retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_OTU0_1:      retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_OTU0_1:      retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_OTU0_1:      retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_OTU0_1:      retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_OTU0_1:      retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_OTU0_1:      retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_OTU0_1:     retVal = 10; break;
        case CT_TEL_SSM40_DEV11_OTU0_1:     retVal = 11; break;
        case CT_TEL_SSM40_DEV12_OTU0_1:     retVal = 12; break;
        case CT_TEL_SSM40_DEV13_OTU0_1:     retVal = 13; break;
        case CT_TEL_SSM40_DEV14_OTU0_1:     retVal = 14; break;
        case CT_TEL_SSM40_DEV15_OTU0_1:     retVal = 15; break;
        case CT_TEL_SSM40_DEV16_OTU0_1:     retVal = 16; break;

        case CT_TEL_SSM40_DEV1_OTU1_1:      retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_OTU1_1:      retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_OTU1_1:      retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_OTU1_1:      retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_OTU1_1:      retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_OTU1_1:      retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_OTU1_1:      retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_OTU1_1:      retVal = 8;  break;

        case CT_TEL_SSM40_DEV1_OTU2_1:      retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_OTU2_1:      retVal = 2;  break;

        case CT_TEL_SSM40_DEV1_CBR_1:       retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_CBR_1:       retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_CBR_1:       retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_CBR_1:       retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_CBR_1:       retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_CBR_1:       retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_CBR_1:       retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_CBR_1:       retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_CBR_1:       retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_CBR_1:      retVal = 10; break;
        case CT_TEL_SSM40_DEV11_CBR_1:      retVal = 11; break;
        case CT_TEL_SSM40_DEV12_CBR_1:      retVal = 12; break;
        case CT_TEL_SSM40_DEV13_CBR_1:      retVal = 13; break;
        case CT_TEL_SSM40_DEV14_CBR_1:      retVal = 14; break;
        case CT_TEL_SSM40_DEV15_CBR_1:      retVal = 15; break;
        case CT_TEL_SSM40_DEV16_CBR_1:      retVal = 16; break;

        case CT_TEL_SSM40_DEV1_CBR10G_1:    retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_CBR10G_1:    retVal = 2;  break;

        case CT_TEL_SSM40_DEV1_GE_1:        retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_GE_1:        retVal = 2;  break;
        case CT_TEL_SSM40_DEV3_GE_1:        retVal = 3;  break;
        case CT_TEL_SSM40_DEV4_GE_1:        retVal = 4;  break;
        case CT_TEL_SSM40_DEV5_GE_1:        retVal = 5;  break;
        case CT_TEL_SSM40_DEV6_GE_1:        retVal = 6;  break;
        case CT_TEL_SSM40_DEV7_GE_1:        retVal = 7;  break;
        case CT_TEL_SSM40_DEV8_GE_1:        retVal = 8;  break;
        case CT_TEL_SSM40_DEV9_GE_1:        retVal = 9;  break;
        case CT_TEL_SSM40_DEV10_GE_1:       retVal = 10; break;
        case CT_TEL_SSM40_DEV11_GE_1:       retVal = 11; break;
        case CT_TEL_SSM40_DEV12_GE_1:       retVal = 12; break;
        case CT_TEL_SSM40_DEV13_GE_1:       retVal = 13; break;
        case CT_TEL_SSM40_DEV14_GE_1:       retVal = 14; break;
        case CT_TEL_SSM40_DEV15_GE_1:       retVal = 15; break;
        case CT_TEL_SSM40_DEV16_GE_1:       retVal = 16; break;

        case CT_TEL_SSM40_DEV1_GE10G_1:     retVal = 1;  break;
        case CT_TEL_SSM40_DEV2_GE10G_1:     retVal = 2;  break;

        default:
            retVal = 0;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::FrmXc_Ssm40FrontEndDevToFac(): Invalid FrontEndDev = %d", theSsm40FrontEndDev);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduXc_Ssm40FrontEndDevToFac(CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev)
{
    uint8  retVal;
    char   errMsg[100];

    switch(theSsm40FrontEndDev)
    {
        /*** HyPhy 0 ***/
        case CT_TEL_SSM40_DEV1_OTU2MUX_0: retVal = XC_SSM40_ODU21XC_ODU2_0_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV2_OTU2MUX_0: retVal = XC_SSM40_ODU21XC_ODU2_1_0_FACILITY_ID; break;

        case CT_TEL_SSM40_DEV1_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_0_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV2_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_1_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV3_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_2_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV4_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_3_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV5_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_4_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV6_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_5_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV7_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_6_0_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV8_OTU1_0:    retVal = XC_SSM40_ODU21XC_ODU1_7_0_FACILITY_ID; break;

        /*** HyPhy 1 ***/
        case CT_TEL_SSM40_DEV1_OTU2MUX_1: retVal = XC_SSM40_ODU21XC_ODU2_0_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV2_OTU2MUX_1: retVal = XC_SSM40_ODU21XC_ODU2_1_1_FACILITY_ID; break;

        case CT_TEL_SSM40_DEV1_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_0_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV2_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_1_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV3_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_2_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV4_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_3_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV5_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_4_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV6_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_5_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV7_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_6_1_FACILITY_ID; break;
        case CT_TEL_SSM40_DEV8_OTU1_1:    retVal = XC_SSM40_ODU21XC_ODU1_7_1_FACILITY_ID; break;

        default:
            retVal = 0;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::OduXc_Ssm40FrontEndDevToFac(): Invalid FrontEndDev = %d", theSsm40FrontEndDev);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
            break;
    }
  
    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduXc_Ssm40FrontEndDevToFacEndpt(
    CT_TEL_Ssm40FrontEndDevice  theSsm40FrontEndDev,
    uint8                       theChan)
{
    uint8  retVal;
    char   errMsg[100];

    switch(theSsm40FrontEndDev)
    {
        /*** HyPhy 0 ***/
        case CT_TEL_SSM40_DEV1_OTU2MUX_0: 
        case CT_TEL_SSM40_DEV2_OTU2MUX_0:
            retVal = theChan + 1;
            break;

        case CT_TEL_SSM40_DEV1_OTU1_0:
        case CT_TEL_SSM40_DEV2_OTU1_0:
        case CT_TEL_SSM40_DEV3_OTU1_0:
        case CT_TEL_SSM40_DEV4_OTU1_0:
        case CT_TEL_SSM40_DEV5_OTU1_0:
        case CT_TEL_SSM40_DEV6_OTU1_0:
        case CT_TEL_SSM40_DEV7_OTU1_0:
        case CT_TEL_SSM40_DEV8_OTU1_0:
            retVal = 1;
            break;

        /*** HyPhy 1 ***/
        case CT_TEL_SSM40_DEV1_OTU2MUX_1:
        case CT_TEL_SSM40_DEV2_OTU2MUX_1:
            retVal = theChan + 1;
            break;

        case CT_TEL_SSM40_DEV1_OTU1_1:
        case CT_TEL_SSM40_DEV2_OTU1_1:
        case CT_TEL_SSM40_DEV3_OTU1_1:
        case CT_TEL_SSM40_DEV4_OTU1_1:
        case CT_TEL_SSM40_DEV5_OTU1_1:
        case CT_TEL_SSM40_DEV6_OTU1_1:
        case CT_TEL_SSM40_DEV7_OTU1_1:
        case CT_TEL_SSM40_DEV8_OTU1_1:
            retVal = 1;
            break;

        default:
            retVal = 0;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::OduXc_Ssm40FrontEndDevToFacEndpt(): Invalid FrontEndDev = %d", theSsm40FrontEndDev);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
            break;
    }
  
    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduXc_FgsmFrontEndDevToFac(CT_TEL_FgsmOduDevice firstOdu, CT_TEL_FgsmOduDevice secondOdu, uint8* IF, uint8* OF)
{
    uint8  retVal = 0;
    char   errMsg[100];
    
    if((firstOdu == CT_TEL_FGSM_DEV0_ODU3) && 
       (secondOdu >= CT_TEL_FGSM_DEV0_ODU2 && secondOdu <= CT_TEL_FGSM_DEV3_ODU2))
    {
        *IF = XC_FGSM_ODU32XC_ODU3_0_FACILITY_ID;
        *OF = XC_FGSM_ODU32XC_ODU2_0_FACILITY_ID + secondOdu - CT_TEL_FGSM_DEV0_ODU2;
    }
    else if((firstOdu == CT_TEL_FGSM_DEV0_ODU3) && 
       (secondOdu >= CT_TEL_FGSM_DEV0_ODU1 && secondOdu <= CT_TEL_FGSM_DEV15_ODU1))
    {
        *IF = XC_FGSM_ODU31XC_ODU3_0_FACILITY_ID;
        *OF = XC_FGSM_ODU31XC_ODU1_0_FACILITY_ID + secondOdu - CT_TEL_FGSM_DEV0_ODU1;
    }
    else if((firstOdu == CT_TEL_FGSM_DEV0_ODU3) && 
       (secondOdu >= CT_TEL_FGSM_DEV0_ODU0 && secondOdu <= CT_TEL_FGSM_DEV31_ODU0))
    {
        *IF = XC_FGSM_ODU30XC_ODU3_0_FACILITY_ID;
        *OF = XC_FGSM_ODU30XC_ODU0_0_FACILITY_ID + secondOdu - CT_TEL_FGSM_DEV0_ODU0;
    }
    else if((firstOdu >= CT_TEL_FGSM_DEV0_ODU2 && firstOdu <= CT_TEL_FGSM_DEV3_ODU2) && 
       (secondOdu >= CT_TEL_FGSM_DEV0_ODU1 && secondOdu <= CT_TEL_FGSM_DEV15_ODU1))
    {
        *IF = XC_FGSM_ODU21XC_ODU2_0_FACILITY_ID + firstOdu - CT_TEL_FGSM_DEV0_ODU2;
        *OF = XC_FGSM_ODU21XC_ODU1_0_FACILITY_ID + secondOdu - CT_TEL_FGSM_DEV0_ODU1;
    }
    else if((firstOdu >= CT_TEL_FGSM_DEV0_ODU2 && firstOdu <= CT_TEL_FGSM_DEV3_ODU2) &&
       (secondOdu >= CT_TEL_FGSM_DEV0_ODU0 && secondOdu <= CT_TEL_FGSM_DEV31_ODU0))
    {
        *IF = XC_FGSM_ODU20XC_ODU2_0_FACILITY_ID + firstOdu - CT_TEL_FGSM_DEV0_ODU2;
        *OF = XC_FGSM_ODU20XC_ODU0_0_FACILITY_ID + secondOdu - CT_TEL_FGSM_DEV0_ODU0;
    }
    else if((firstOdu >= CT_TEL_FGSM_DEV0_ODU1 && firstOdu <= CT_TEL_FGSM_DEV15_ODU1) &&
       (secondOdu >= CT_TEL_FGSM_DEV0_ODU0 && secondOdu <= CT_TEL_FGSM_DEV31_ODU0))
    {
        *IF = XC_FGSM_ODU10XC_ODU1_0_FACILITY_ID + firstOdu - CT_TEL_FGSM_DEV0_ODU1;
        *OF = XC_FGSM_ODU10XC_ODU0_0_FACILITY_ID + secondOdu - CT_TEL_FGSM_DEV0_ODU0;
    }
    else
    {
        retVal = 1;
        sprintf(errMsg, "TSXC_ConfigRegion<T>::OduXc_FgsmFrontEndDevToFac: Invalid firstOdu = %d, secondOdu = %d", firstOdu, secondOdu);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> bool TSXC_ConfigRegion<T>::FrmXc_Osm20FrontEndDevToFac(CT_TEL_HyphyFlexFrontEndDevice theOsm20FrontEndDev, uint8* IF, uint8* IFE)
{
    bool retVal = true;
    char errMsg[100];

    switch(theOsm20FrontEndDev)
    {
        case CT_TEL_HYPHYFLEX_SONET48_DEV1:
        case CT_TEL_HYPHYFLEX_SONET48_DEV2:
        case CT_TEL_HYPHYFLEX_SONET48_DEV3:
        case CT_TEL_HYPHYFLEX_SONET48_DEV4:
        case CT_TEL_HYPHYFLEX_SONET48_DEV5:
        case CT_TEL_HYPHYFLEX_SONET48_DEV6:
        case CT_TEL_HYPHYFLEX_SONET48_DEV7:
        case CT_TEL_HYPHYFLEX_SONET48_DEV8:
        case CT_TEL_HYPHYFLEX_SONET48_DEV9:
        case CT_TEL_HYPHYFLEX_SONET48_DEV10:
        case CT_TEL_HYPHYFLEX_SONET48_DEV11:
        case CT_TEL_HYPHYFLEX_SONET48_DEV12:
        case CT_TEL_HYPHYFLEX_SONET48_DEV13:
        case CT_TEL_HYPHYFLEX_SONET48_DEV14:
        case CT_TEL_HYPHYFLEX_SONET48_DEV15:
        case CT_TEL_HYPHYFLEX_SONET48_DEV16:
            *IF = XC_OSM20_FRMODUXC_FRM_CBR_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_SONET48_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_SONET192_DEV1:
        case CT_TEL_HYPHYFLEX_SONET192_DEV2:
            *IF = XC_OSM20_FRMODUXC_FRM_CBR10G_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_SONET192_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_OTU1_DEV1:
        case CT_TEL_HYPHYFLEX_OTU1_DEV2:
        case CT_TEL_HYPHYFLEX_OTU1_DEV3:
        case CT_TEL_HYPHYFLEX_OTU1_DEV4:
        case CT_TEL_HYPHYFLEX_OTU1_DEV5:
        case CT_TEL_HYPHYFLEX_OTU1_DEV6:
        case CT_TEL_HYPHYFLEX_OTU1_DEV7:
        case CT_TEL_HYPHYFLEX_OTU1_DEV8:
        case CT_TEL_HYPHYFLEX_OTU1_DEV9:
        case CT_TEL_HYPHYFLEX_OTU1_DEV10:
        case CT_TEL_HYPHYFLEX_OTU1_DEV11:
        case CT_TEL_HYPHYFLEX_OTU1_DEV12:
        case CT_TEL_HYPHYFLEX_OTU1_DEV13:
        case CT_TEL_HYPHYFLEX_OTU1_DEV14:
        case CT_TEL_HYPHYFLEX_OTU1_DEV15:
        case CT_TEL_HYPHYFLEX_OTU1_DEV16:
            *IF = XC_OSM20_FRMODUXC_FRM_OTU1_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_OTU1_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_OTU2_DEV1:
        case CT_TEL_HYPHYFLEX_OTU2_DEV2:
            *IF = XC_OSM20_FRMODUXC_FRM_OTU2_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_OTU2_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_CBR_DEV1:
        case CT_TEL_HYPHYFLEX_CBR_DEV2:
        case CT_TEL_HYPHYFLEX_CBR_DEV3:
        case CT_TEL_HYPHYFLEX_CBR_DEV4:
        case CT_TEL_HYPHYFLEX_CBR_DEV5:
        case CT_TEL_HYPHYFLEX_CBR_DEV6:
        case CT_TEL_HYPHYFLEX_CBR_DEV7:
        case CT_TEL_HYPHYFLEX_CBR_DEV8:
        case CT_TEL_HYPHYFLEX_CBR_DEV9:
        case CT_TEL_HYPHYFLEX_CBR_DEV10:
        case CT_TEL_HYPHYFLEX_CBR_DEV11:
        case CT_TEL_HYPHYFLEX_CBR_DEV12:
        case CT_TEL_HYPHYFLEX_CBR_DEV13:
        case CT_TEL_HYPHYFLEX_CBR_DEV14:
        case CT_TEL_HYPHYFLEX_CBR_DEV15:
        case CT_TEL_HYPHYFLEX_CBR_DEV16:
            *IF = XC_OSM20_FRMODUXC_FRM_CBR_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_CBR_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_CBR10G_DEV1:
        case CT_TEL_HYPHYFLEX_CBR10G_DEV2:
            *IF = XC_OSM20_FRMODUXC_FRM_CBR10G_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_CBR10G_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_GE_DEV1:
        case CT_TEL_HYPHYFLEX_GE_DEV2:
        case CT_TEL_HYPHYFLEX_GE_DEV3:
        case CT_TEL_HYPHYFLEX_GE_DEV4:
        case CT_TEL_HYPHYFLEX_GE_DEV5:
        case CT_TEL_HYPHYFLEX_GE_DEV6:
        case CT_TEL_HYPHYFLEX_GE_DEV7:
        case CT_TEL_HYPHYFLEX_GE_DEV8:
        case CT_TEL_HYPHYFLEX_GE_DEV9:
        case CT_TEL_HYPHYFLEX_GE_DEV10:
        case CT_TEL_HYPHYFLEX_GE_DEV11:
        case CT_TEL_HYPHYFLEX_GE_DEV12:
        case CT_TEL_HYPHYFLEX_GE_DEV13:
        case CT_TEL_HYPHYFLEX_GE_DEV14:
        case CT_TEL_HYPHYFLEX_GE_DEV15:
        case CT_TEL_HYPHYFLEX_GE_DEV16:
            *IF = XC_OSM20_FRMODUXC_FRM_GE_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_GE_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_GE10G_DEV1:
        case CT_TEL_HYPHYFLEX_GE10G_DEV2:
            *IF = XC_OSM20_FRMODUXC_FRM_GE10G_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_GE10G_DEV1 + 1;
            break;

        case CT_TEL_HYPHYFLEX_ODUK_DEV1:
        case CT_TEL_HYPHYFLEX_ODUK_DEV2:
        case CT_TEL_HYPHYFLEX_ODUK_DEV3:
        case CT_TEL_HYPHYFLEX_ODUK_DEV4:
        case CT_TEL_HYPHYFLEX_ODUK_DEV5:
        case CT_TEL_HYPHYFLEX_ODUK_DEV6:
        case CT_TEL_HYPHYFLEX_ODUK_DEV7:
        case CT_TEL_HYPHYFLEX_ODUK_DEV8:
        case CT_TEL_HYPHYFLEX_ODUK_DEV9:
        case CT_TEL_HYPHYFLEX_ODUK_DEV10:
        case CT_TEL_HYPHYFLEX_ODUK_DEV11:
        case CT_TEL_HYPHYFLEX_ODUK_DEV12:
        case CT_TEL_HYPHYFLEX_ODUK_DEV13:
        case CT_TEL_HYPHYFLEX_ODUK_DEV14:
        case CT_TEL_HYPHYFLEX_ODUK_DEV15:
        case CT_TEL_HYPHYFLEX_ODUK_DEV16:
        case CT_TEL_HYPHYFLEX_ODUK_DEV17:
        case CT_TEL_HYPHYFLEX_ODUK_DEV18:
        case CT_TEL_HYPHYFLEX_ODUK_DEV19:
        case CT_TEL_HYPHYFLEX_ODUK_DEV20:
        case CT_TEL_HYPHYFLEX_ODUK_DEV21:
        case CT_TEL_HYPHYFLEX_ODUK_DEV22:
        case CT_TEL_HYPHYFLEX_ODUK_DEV23:
        case CT_TEL_HYPHYFLEX_ODUK_DEV24:
        case CT_TEL_HYPHYFLEX_ODUK_DEV25:
        case CT_TEL_HYPHYFLEX_ODUK_DEV26:
        case CT_TEL_HYPHYFLEX_ODUK_DEV27:
        case CT_TEL_HYPHYFLEX_ODUK_DEV28:
        case CT_TEL_HYPHYFLEX_ODUK_DEV29:
        case CT_TEL_HYPHYFLEX_ODUK_DEV30:
        case CT_TEL_HYPHYFLEX_ODUK_DEV31:
        case CT_TEL_HYPHYFLEX_ODUK_DEV32:
            *IF = XC_OSM20_FRMODUXC_FRM_OTUK_FACILITY_ID;
            *IFE = theOsm20FrontEndDev - CT_TEL_HYPHYFLEX_ODUK_DEV1 + 1;
            break;

        default:
            retVal = false;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::FrmXc_Osm20FrontEndDevToFac(): Invalid FrontEndDev = %d", theOsm20FrontEndDev);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
            break;
    }

    return retVal;
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> bool TSXC_ConfigRegion<T>::FrmXc_OmmxFrontEndDevToFac(CT_TEL_HyphyAxsFrontEndDevice theOmmxFrontEndDev, uint8* IF, uint8* IFE)
{
    bool retVal = true;
    char errMsg[100];

    switch(theOmmxFrontEndDev)
    {
        case CT_TEL_HYPHYAXS_OTU1_DEV1:
        case CT_TEL_HYPHYAXS_OTU1_DEV2:
        case CT_TEL_HYPHYAXS_OTU1_DEV3:
        case CT_TEL_HYPHYAXS_OTU1_DEV4:
        case CT_TEL_HYPHYAXS_OTU1_DEV5:
        case CT_TEL_HYPHYAXS_OTU1_DEV6:
        case CT_TEL_HYPHYAXS_OTU1_DEV7:
        case CT_TEL_HYPHYAXS_OTU1_DEV8:
        case CT_TEL_HYPHYAXS_OTU1_DEV9:
        case CT_TEL_HYPHYAXS_OTU1_DEV10:
        case CT_TEL_HYPHYAXS_OTU1_DEV11:
        case CT_TEL_HYPHYAXS_OTU1_DEV12:
        case CT_TEL_HYPHYAXS_OTU1_DEV13:
        case CT_TEL_HYPHYAXS_OTU1_DEV14:
        case CT_TEL_HYPHYAXS_OTU1_DEV15:
        case CT_TEL_HYPHYAXS_OTU1_DEV16:
            *IF = XC_OMMX_FRMODUXC_FRM_OTU1_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_OTU1_DEV1 + 1;
            break;

        case CT_TEL_HYPHYAXS_OTU2_DEV1:
        case CT_TEL_HYPHYAXS_OTU2_DEV2:
            *IF = XC_OMMX_FRMODUXC_FRM_OTU2_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_OTU2_DEV1 + 1;
            break;

        case CT_TEL_HYPHYAXS_CBR_DEV1:
        case CT_TEL_HYPHYAXS_CBR_DEV2:
        case CT_TEL_HYPHYAXS_CBR_DEV3:
        case CT_TEL_HYPHYAXS_CBR_DEV4:
        case CT_TEL_HYPHYAXS_CBR_DEV5:
        case CT_TEL_HYPHYAXS_CBR_DEV6:
        case CT_TEL_HYPHYAXS_CBR_DEV7:
        case CT_TEL_HYPHYAXS_CBR_DEV8:
            *IF = XC_OMMX_FRMODUXC_FRM_CBR_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_CBR_DEV1 + 1;
            break;

        case CT_TEL_HYPHYAXS_CBR10G_DEV1:
        case CT_TEL_HYPHYAXS_CBR10G_DEV2:
            *IF = XC_OMMX_FRMODUXC_FRM_CBR10G_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_CBR10G_DEV1 + 1;
            break;

        case CT_TEL_HYPHYAXS_GE_DEV1:
        case CT_TEL_HYPHYAXS_GE_DEV2:
        case CT_TEL_HYPHYAXS_GE_DEV3:
        case CT_TEL_HYPHYAXS_GE_DEV4:
        case CT_TEL_HYPHYAXS_GE_DEV5:
        case CT_TEL_HYPHYAXS_GE_DEV6:
        case CT_TEL_HYPHYAXS_GE_DEV7:
        case CT_TEL_HYPHYAXS_GE_DEV8:
            *IF = XC_OMMX_FRMODUXC_FRM_GE_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_GE_DEV1 + 1;
            break;

        case CT_TEL_HYPHYAXS_GE10G_DEV1:
        case CT_TEL_HYPHYAXS_GE10G_DEV2:
            *IF = XC_OMMX_FRMODUXC_FRM_GE10G_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_GE10G_DEV1 + 1;
            break;

        case CT_TEL_HYPHYAXS_ODUK_DEV1:
        case CT_TEL_HYPHYAXS_ODUK_DEV2:
        case CT_TEL_HYPHYAXS_ODUK_DEV3:
        case CT_TEL_HYPHYAXS_ODUK_DEV4:
        case CT_TEL_HYPHYAXS_ODUK_DEV5:
        case CT_TEL_HYPHYAXS_ODUK_DEV6:
        case CT_TEL_HYPHYAXS_ODUK_DEV7:
        case CT_TEL_HYPHYAXS_ODUK_DEV8:
        case CT_TEL_HYPHYAXS_ODUK_DEV9:
        case CT_TEL_HYPHYAXS_ODUK_DEV10:
        case CT_TEL_HYPHYAXS_ODUK_DEV11:
        case CT_TEL_HYPHYAXS_ODUK_DEV12:
        case CT_TEL_HYPHYAXS_ODUK_DEV13:
        case CT_TEL_HYPHYAXS_ODUK_DEV14:
        case CT_TEL_HYPHYAXS_ODUK_DEV15:
        case CT_TEL_HYPHYAXS_ODUK_DEV16:
        case CT_TEL_HYPHYAXS_ODUK_DEV17:
        case CT_TEL_HYPHYAXS_ODUK_DEV18:
        case CT_TEL_HYPHYAXS_ODUK_DEV19:
        case CT_TEL_HYPHYAXS_ODUK_DEV20:
        case CT_TEL_HYPHYAXS_ODUK_DEV21:
        case CT_TEL_HYPHYAXS_ODUK_DEV22:
        case CT_TEL_HYPHYAXS_ODUK_DEV23:
        case CT_TEL_HYPHYAXS_ODUK_DEV24:
        case CT_TEL_HYPHYAXS_ODUK_DEV25:
        case CT_TEL_HYPHYAXS_ODUK_DEV26:
        case CT_TEL_HYPHYAXS_ODUK_DEV27:
        case CT_TEL_HYPHYAXS_ODUK_DEV28:
        case CT_TEL_HYPHYAXS_ODUK_DEV29:
        case CT_TEL_HYPHYAXS_ODUK_DEV30:
        case CT_TEL_HYPHYAXS_ODUK_DEV31:
        case CT_TEL_HYPHYAXS_ODUK_DEV32:
            *IF = XC_OMMX_FRMODUXC_FRM_OTUK_FACILITY_ID;
            *IFE = theOmmxFrontEndDev - CT_TEL_HYPHYAXS_ODUK_DEV1 + 1;
            break;

        default:
            retVal = false;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::FrmXc_OmmxFrontEndDevToFac(): Invalid FrontEndDev = %d", theOmmxFrontEndDev);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
            break;
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> bool TSXC_ConfigRegion<T>::FrmXc_Osm20DevPortToFac(uint8 devicePort, uint8 deviceChannel, uint8* IF, uint8* IFE)
{
    bool retVal = true;
    char errMsg[100];

    switch(devicePort)
    {
        case OSM20_OTN_ODUK_PORT0:
        case OSM20_OTN_ODUK_PORT1:
        case OSM20_OTN_ODUK_PORT2:
        case OSM20_OTN_ODUK_PORT3:
            *IF = XC_OSM20_FRMODUXC_ODU_OTUK_FACILITY_ID;
            *IFE = (devicePort - OSM20_OTN_ODUK_PORT0) * 8 + deviceChannel + 1;
            break;

        case OSM20_ODUKPP_ODUK_PORT0:
            *IF = XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OSM20_ODUKPP_ODUK_PORT1:
            *IF = XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OSM20_OTN_ODU1_PORT:
            *IF = XC_OSM20_FRMODUXC_ODU_OTU1_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OSM20_ODUKPP_ODU1_PORT:
            if(deviceChannel < OSM20_ODUKPP_ODU1_CHANS/2)
            {
                *IF = XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID;
                *IFE = deviceChannel + 1;
            }
            else
            {
                *IF = XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID;
                *IFE = deviceChannel - OSM20_ODUKPP_ODU1_CHANS/2 + 1;
            }
            break;

        case OSM20_OTN_ODU2_PORT:
            *IF = XC_OSM20_FRMODUXC_ODU_OTU2_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OSM20_ODUKPP_ODU2_PORT:
            if(deviceChannel < OSM20_ODUKPP_ODU2_CHANS/2)
            {
                *IF = XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID;
                *IFE = deviceChannel + 1;
            }
            else
            {
                *IF = XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID;
                *IFE = deviceChannel - OSM20_ODUKPP_ODU2_CHANS/2 + 1;
            }
            break;

        default:
            retVal = false;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::TSXC_ConfigRegion<T>::FrmXc_Osm20DevPortToFac(): Invalid DevicePort = %d", devicePort);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> bool TSXC_ConfigRegion<T>::FrmXc_OmmxDevPortToFac(uint8 devicePort, uint8 deviceChannel, uint8* IF, uint8* IFE)
{
    bool retVal = true;
    char errMsg[100];

    switch(devicePort)
    {
        case OMMX_OTN_ODUK_PORT0:
        case OMMX_OTN_ODUK_PORT1:
        case OMMX_OTN_ODUK_PORT2:
        case OMMX_OTN_ODUK_PORT3:
            *IF = XC_OMMX_FRMODUXC_ODU_OTUK_FACILITY_ID;
            *IFE = (devicePort - OMMX_OTN_ODUK_PORT0) * 8 + deviceChannel + 1;
            break;

        case OMMX_ODUKPP_ODUK_PORT0:
            *IF = XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OMMX_ODUKPP_ODUK_PORT1:
            *IF = XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OMMX_OTN_ODU1_PORT:
            *IF = XC_OMMX_FRMODUXC_ODU_OTU1_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OMMX_ODUKPP_ODU1_PORT:
            if(deviceChannel < OMMX_ODUKPP_ODU1_CHANS/2)
            {
                *IF = XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID;
                *IFE = deviceChannel + 1;
            }
            else
            {
                *IF = XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID;
                *IFE = deviceChannel - OMMX_ODUKPP_ODU1_CHANS/2 + 1;
            }
            break;

        case OMMX_OTN_ODU2_PORT:
            *IF = XC_OMMX_FRMODUXC_ODU_OTU2_FACILITY_ID;
            *IFE = deviceChannel + 1;
            break;

        case OMMX_ODUKPP_ODU2_PORT:
            if(deviceChannel < OMMX_ODUKPP_ODU2_CHANS/2)
            {
                *IF = XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID;
                *IFE = deviceChannel + 1;
            }
            else
            {
                *IF = XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID;
                *IFE = deviceChannel - OMMX_ODUKPP_ODU2_CHANS/2 + 1;
            }
            break;

        default:
            retVal = false;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::TSXC_ConfigRegion<T>::FrmXc_OmmxDevPortToFac(): Invalid DevicePort = %d", devicePort);
            FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduXc_Osm20FrontEndDevToFac(CT_TEL_HyphyFlexFrontEndDevice firstOdu, CT_TEL_HyphyFlexFrontEndDevice secondOdu, uint8* IF, uint8* OF, bool secondOduIsOduF)
{
    uint8  retVal = 0;
    char   errMsg[100];

    if(firstOdu >= CT_TEL_HYPHYFLEX_OTU2_DEV1 && firstOdu <= CT_TEL_HYPHYFLEX_OTU2_DEV2
       && secondOdu >= CT_TEL_HYPHYFLEX_OTU1_DEV1 && secondOdu <= CT_TEL_HYPHYFLEX_OTU1_DEV16)
    {
        // ODU21 MUX
        *IF = (firstOdu - CT_TEL_HYPHYFLEX_OTU2_DEV1) + XC_OSM20_ODU21XC_ODU2_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYFLEX_OTU1_DEV1) + XC_OSM20_ODU21XC_ODU1_0_FACILITY_ID;
    }
    else if(firstOdu >= CT_TEL_HYPHYFLEX_OTU2_DEV1 && firstOdu <= CT_TEL_HYPHYFLEX_OTU2_DEV2
            && secondOdu >= CT_TEL_HYPHYFLEX_ODUK_DEV1 && secondOdu <= CT_TEL_HYPHYFLEX_ODUK_DEV32
            && secondOduIsOduF == false)
    {
        // ODU20 MUX
        *IF = (firstOdu - CT_TEL_HYPHYFLEX_OTU2_DEV1) + XC_OSM20_ODU20XC_ODU2_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYFLEX_ODUK_DEV1) + XC_OSM20_ODU20XC_ODU0_0_FACILITY_ID;
    }
    else if(firstOdu >= CT_TEL_HYPHYFLEX_OTU2_DEV1 && firstOdu <= CT_TEL_HYPHYFLEX_OTU2_DEV2
            && secondOdu >= CT_TEL_HYPHYFLEX_ODUK_DEV1 && secondOdu <= CT_TEL_HYPHYFLEX_ODUK_DEV32
            && secondOduIsOduF == true)
    {
        // ODU2F MUX
        *IF = (firstOdu - CT_TEL_HYPHYFLEX_OTU2_DEV1) + XC_OSM20_ODU2FXC_ODU2_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYFLEX_ODUK_DEV1) + XC_OSM20_ODU2FXC_ODUF_0_FACILITY_ID;
    }
    else if(firstOdu >= CT_TEL_HYPHYFLEX_OTU1_DEV1 && firstOdu <= CT_TEL_HYPHYFLEX_OTU1_DEV16
        && secondOdu >= CT_TEL_HYPHYFLEX_ODUK_DEV1 && secondOdu <= CT_TEL_HYPHYFLEX_ODUK_DEV32)
    {
        // ODU10 MUX
        *IF = (firstOdu - CT_TEL_HYPHYFLEX_OTU1_DEV1) + XC_OSM20_ODU10XC_ODU1_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYFLEX_ODUK_DEV1) + XC_OSM20_ODU10XC_ODU0_0_FACILITY_ID;
    }
    else
    {
        retVal = 1;
        sprintf(errMsg, "TSXC_ConfigRegion<T>::OduXc_Osm20FrontEndDevToFac: Invalid firstOdu = %d, secondOdu = %d", firstOdu, secondOdu);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduXc_OmmxFrontEndDevToFac(CT_TEL_HyphyAxsFrontEndDevice firstOdu, CT_TEL_HyphyAxsFrontEndDevice secondOdu, uint8* IF, uint8* OF, bool secondOduIsOduF)
{
    uint8  retVal = 0;
    char   errMsg[100];

    if(firstOdu >= CT_TEL_HYPHYAXS_OTU2_DEV1 && firstOdu <= CT_TEL_HYPHYAXS_OTU2_DEV2
       && secondOdu >= CT_TEL_HYPHYAXS_OTU1_DEV1 && secondOdu <= CT_TEL_HYPHYAXS_OTU1_DEV16)
    {
        // ODU21 MUX
        *IF = (firstOdu - CT_TEL_HYPHYAXS_OTU2_DEV1) + XC_OMMX_ODU21XC_ODU2_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYAXS_OTU1_DEV1) + XC_OMMX_ODU21XC_ODU1_0_FACILITY_ID;
    }
    else if(firstOdu >= CT_TEL_HYPHYAXS_OTU2_DEV1 && firstOdu <= CT_TEL_HYPHYAXS_OTU2_DEV2
            && secondOdu >= CT_TEL_HYPHYAXS_ODUK_DEV1 && secondOdu <= CT_TEL_HYPHYAXS_ODUK_DEV32
            && secondOduIsOduF == false)
    {
        // ODU20 MUX
        *IF = (firstOdu - CT_TEL_HYPHYAXS_OTU2_DEV1) + XC_OMMX_ODU20XC_ODU2_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYAXS_ODUK_DEV1) + XC_OMMX_ODU20XC_ODU0_0_FACILITY_ID;
    }
    else if(firstOdu >= CT_TEL_HYPHYAXS_OTU2_DEV1 && firstOdu <= CT_TEL_HYPHYAXS_OTU2_DEV2
            && secondOdu >= CT_TEL_HYPHYAXS_ODUK_DEV1 && secondOdu <= CT_TEL_HYPHYAXS_ODUK_DEV32
            && secondOduIsOduF == true)
    {
        // ODU2F MUX
        *IF = (firstOdu - CT_TEL_HYPHYAXS_OTU2_DEV1) + XC_OMMX_ODU2FXC_ODU2_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYAXS_ODUK_DEV1) + XC_OMMX_ODU2FXC_ODUF_0_FACILITY_ID;
    }
    else if(firstOdu >= CT_TEL_HYPHYAXS_OTU1_DEV1 && firstOdu <= CT_TEL_HYPHYAXS_OTU1_DEV16
        && secondOdu >= CT_TEL_HYPHYAXS_ODUK_DEV1 && secondOdu <= CT_TEL_HYPHYAXS_ODUK_DEV32)
    {
        // ODU10 MUX
        *IF = (firstOdu - CT_TEL_HYPHYAXS_OTU1_DEV1) + XC_OMMX_ODU10XC_ODU1_0_FACILITY_ID;
        *OF = (secondOdu - CT_TEL_HYPHYAXS_ODUK_DEV1) + XC_OMMX_ODU10XC_ODU0_0_FACILITY_ID;
    }
    else
    {
        retVal = 1;
        sprintf(errMsg, "TSXC_ConfigRegion<T>::OduXc_OmmxFrontEndDevToFac: Invalid firstOdu = %d, secondOdu = %d", firstOdu, secondOdu);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduIdToFac(CT_ODU_Identifier&  theOduId)
{
    uint8   retVal;
    char    errMsg[100];

    switch(theOduId.GetDevicePort())
    {
        /*** HyPhy 0 ***/
        case SSM40_ODU0_PORT_0:       retVal = XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_FACILITY_ID;  break;
        case SSM40_OTU1_ODU1_PORT_0:  retVal = XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_FACILITY_ID;  break;
        case SSM40_OTU2_ODU2_PORT_0:  retVal = XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_FACILITY_ID;  break;
        case SSM40_VCAT0_ODU0_PORT_0: retVal = XC_SSM40_FRMODUXC_ODU_VCATA_0_FACILITY_ID;    break;
        case SSM40_VCAT1_ODU0_PORT_0: retVal = XC_SSM40_FRMODUXC_ODU_VCATB_0_FACILITY_ID;    break;
        case SSM40_VCAT0_ODU1_PORT_0: retVal = XC_SSM40_FRMODUXC_ODU_VCATA_0_FACILITY_ID;    break;
        case SSM40_VCAT1_ODU1_PORT_0: retVal = XC_SSM40_FRMODUXC_ODU_VCATB_0_FACILITY_ID;    break;

        /*** HyPhy 1 ***/
        case SSM40_ODU0_PORT_1:       retVal = XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_FACILITY_ID;  break;
        case SSM40_OTU1_ODU1_PORT_1:  retVal = XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_FACILITY_ID;  break;
        case SSM40_OTU2_ODU2_PORT_1:  retVal = XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_FACILITY_ID;  break;
        case SSM40_VCAT0_ODU0_PORT_1: retVal = XC_SSM40_FRMODUXC_ODU_VCATA_1_FACILITY_ID;    break;
        case SSM40_VCAT1_ODU0_PORT_1: retVal = XC_SSM40_FRMODUXC_ODU_VCATB_1_FACILITY_ID;    break;
        case SSM40_VCAT0_ODU1_PORT_1: retVal = XC_SSM40_FRMODUXC_ODU_VCATA_1_FACILITY_ID;    break;
        case SSM40_VCAT1_ODU1_PORT_1: retVal = XC_SSM40_FRMODUXC_ODU_VCATB_1_FACILITY_ID;    break;

        default:
            retVal = 0;
            sprintf(errMsg, "TSXC_ConfigRegion<T>::OduIdToFac(): Invalid DevicePort = %d", theOduId.GetDevicePort());
            FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::OduIdToFacEndpt(CT_ODU_Identifier&  theOduId)
{
    uint8   retVal;

    retVal = theOduId.GetDeviceChannel() + 1;

    return retVal;
}

//----------------------------------------------------------------------------------------------
template<class T> uint8 TSXC_ConfigRegion<T>::GetInputFacilityFromDst(CT_XcTerm& theDstTerm)
{
    uint8             IF;
    uint8             OF;
    uint8             OFE;
    int               FacilityOffset;
    char              errMsg[80];

    // Calculate OF/OFE
    GetFacilityIdFromAGPortId(&OF, theDstTerm.FacData->GetPortId());
    OFE = theDstTerm.FacData->GetChannel();

    // Find offset into region for OF/OFE
    if (FindValidOffset(1, 1, OF, OFE+1, &FacilityOffset) == true)
    {
        // Find input facility connected to OF/OFE
        IF = (*this)[FacilityOffset+OFE].GetInputFacility();
    }
    else
    {
        sprintf(errMsg, "TSXC_ConfigRegion<T>::GetInputFacilityFromDst(): FindValidOffset returned false");
        FC_REPORT_ERROR(FC_LogicError, errMsg);
        IF = 0xFF;
    }

    return IF;
}

//---------------------------------------------------------------------------------------
template<class T> TSXC_Connect* TSXC_ConfigRegion<T>::GetConnection(uint8 OF, uint8 OFE)
{
    int FacilityOffset = 0;
    bool ValidData;
    TSXC_Connect* retVal = NULL;

    //--- Get the Starting facility offset into the region.
    ValidData = FindValidOffset(1, 1, OF, OFE, &FacilityOffset);
    
    //--- If a valid Facility then go ahead and get the connection.
    if(ValidData)
    {
        retVal = &((*this)[FacilityOffset+OFE-1]);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> bool TSXC_ConfigRegion<T>::IsConnectedAsOutput(uint8 OF, uint8 OFE)
{
    bool            aRetVal = false;
    TSXC_Connect*   aConnPtr;

    if ( (aConnPtr = GetConnection(OF, OFE)) != NULL )
    {
        if (aConnPtr->GetState() == CT_XC_STATE_CONNECTED)
        {
            aRetVal = true;
        }
    }

    return aRetVal;
}

//---------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ResetFgsmMux()
{
    //do not reset ODU<->ODU XC

    //reset ODUk<->ODUk MUX only
    int regionIndex;
    for (regionIndex = XC_FGSM_ODU32XC_ODU3_0_START; regionIndex <= XC_FGSM_ODU10XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//---------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ResetOsm20FrameAndMux()
{
    //do not reset ODU<->ODU XC, reset ODUk<->ODUk FRM CRS / MUX CRS only
    int regionIndex;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_OTUK_START; regionIndex <= XC_OSM20_ODU10XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//---------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ResetOmmxFrameAndMux()
{
    //do not reset ODU<->ODU XC, reset ODUk<->ODUk FRM CRS / MUX CRS only
    int regionIndex;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_OTUK_START; regionIndex <= XC_OMMX_ODU10XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//---------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ResetHgtmmFrameAndMux()
{
    int regionIndex;
    for (regionIndex = HGTMM_XC_ODU4_MUX_TRIBSLOT_START; regionIndex <= HGTMM_XC_ODU4_MUX_TRIBSLOT_END; ++regionIndex)
    {
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//---------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::ResetHdtg2FrameAndMux()
{
    int regionIndex;
    for (regionIndex = XC_HDTG2_ODUF_MUX0_START; regionIndex <= XC_HDTG2_ODUF_MUX7_END; ++regionIndex)
    {
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateUnknown()
{
    this->Resize(0);
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateSPFAB()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_SPFAB_LINE0_FACILITY_ID;
    
    this->Resize(XC_MAX_XC_SPFAB);
        
    for (regionIndex = XC_SPFAB_CFG_LINE0_START; regionIndex <= XC_SPFAB_CFG_LINE27_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SPFAB_LINE)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateFGTMM()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_FGTMM_ODU2_PORT0_FACILITY_ID;
    
    this->Resize(XC_MAX_XC_FGTMM);
        
    for (regionIndex = XC_FGTMM_CFG_ODU2_PORT0_START; regionIndex <= XC_FGTMM_CFG_ODU2_PORT3_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_FGTMM_ODU2_PORT)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
    channel         = 1;
    facilityId      = XC_FGTMM_DWDM_FACILITY_ID;
    for (regionIndex = XC_FGTMM_CFG_ODU2_DWDM_START; regionIndex <= XC_FGTMM_CFG_ODU2_DWDM_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_FGTMM_ODU2_DWDM)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateSSM40()
{
#if 0
// Future
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_SSM40_PORT0_FACILITY_ID;

    this->Resize(XC_MAX_XC_SSM40);

    for (regionIndex = XC_SSM40_CFG_PORT0_START; regionIndex <= XC_SSM40_CFG_PORT15_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SSM40_PORT)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility i.e port 1..16
        }
    }
    channel         = 1;
    facilityId      = XC_SSM40_PORT16_FACILITY_ID;
    for (regionIndex = XC_SSM40_CFG_PORT16_START; regionIndex <= XC_SSM40_CFG_IM_SONET_B_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if (channel > XC_MAX_XC_SSM40_PORTX)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility, i.e. port 17..20, IM_SONET_A and IM_SONET_B
        }
    }
    channel         = 1;
    facilityId      = XC_SSM40_IM_ODU_A_FACILITY_ID;
    for (regionIndex = XC_SSM40_CFG_IM_ODU_A_START; regionIndex <= XC_SSM40_CFG_IM_ODU_B_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if (channel > XC_MAX_XC_SSM40_IM_ODU)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility, i.e.IM_ODU_A and IM_ODU_B
        }
    }
    channel         = 1;
    facilityId      = XC_SSM40_ODU_A_PORT0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODU_A_PORT0_START; regionIndex <= XC_SSM40_ODU_B_PORT5_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if (channel > XC_MAX_XC_SSM40_ODU)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility, i.e.IM_ODU_A and IM_ODU_B
        }
    }
#endif
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateOSM40()
{
    int regionIndex;
    int channel;
    int facilityId;

    this->Resize(XC_MAX_XC_SSM40);

    /////////////////////////////////////////////////////////////////// 
    // ODU <-> ODU  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_OTNOTU0_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_OTNOTU0_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_OTNOTU0_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_OTNOTU1_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_OTNOTU1_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_OTNOTU1_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_OTNOTU2_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_OTNOTU2_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_OTNOTU2_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCAT0A_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCAT0A_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCAT0A_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCAT0B_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCAT0B_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCAT0B_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCATA_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCATA_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCATA_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCATB_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCATB_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCATB_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_IMUX_0_START; regionIndex <= XC_SSM40_ODUXC_ODU_IMUX_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_OTNOTU0_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_OTNOTU0_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_OTNOTU0_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_OTNOTU1_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_OTNOTU1_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_OTNOTU1_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_OTNOTU2_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_OTNOTU2_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_OTNOTU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCATA_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCATA_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCATA_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCATB_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCATB_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCATB_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCAT0A_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCAT0A_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCAT0A_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_VCAT0B_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_VCAT0B_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_VCAT0B_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODUXC_ODU_IMUX_1_START; regionIndex <= XC_SSM40_ODUXC_ODU_IMUX_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    /////////////////////////////////////////////////////////////////// 
    // FRM <-> ODU  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_OTU0_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_OTU0_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_OTU0_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_OTU1_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_OTU1_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_OTU1_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_OTU2_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_OTU2_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_OTU2_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_CBR_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_CBR_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_CBR_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_CBR10G_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_CBR10G_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_CBR10G_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_GE_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_GE_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_GE_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_GE10G_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_GE10G_0_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_GE10G_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_OTU0_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_OTU0_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_OTU0_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_OTU1_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_OTU1_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_OTU1_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_OTU2_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_OTU2_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_OTU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_CBR_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_CBR_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_CBR_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_CBR10G_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_CBR10G_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_CBR10G_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_GE_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_GE_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_GE_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_FRM_GE10G_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_FRM_GE10G_1_START; regionIndex <= XC_SSM40_FRMODUXC_FRM_GE10G_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_VCATA_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_VCATA_0_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_VCATA_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_VCATB_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_VCATB_0_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_VCATB_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_VCATA_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_VCATA_1_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_VCATA_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_SSM40_FRMODUXC_ODU_VCATB_1_FACILITY_ID;
    for (regionIndex = XC_SSM40_FRMODUXC_ODU_VCATB_1_START; regionIndex <= XC_SSM40_FRMODUXC_ODU_VCATB_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU2 <-> ODU1  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_SSM40_ODU21XC_ODU2_0_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODU21XC_ODU2_0_0_START; regionIndex <= XC_SSM40_ODU21XC_ODU2_1_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if (channel > XC_MAX_XC_SSM40_ODU21XC_ODU2)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }

    channel         = 1;
    facilityId      = XC_SSM40_ODU21XC_ODU1_0_0_FACILITY_ID;
    for (regionIndex = XC_SSM40_ODU21XC_ODU1_0_0_START; regionIndex <= XC_SSM40_ODU21XC_ODU1_7_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if (channel > XC_MAX_XC_SSM40_ODU21XC_ODU1)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateFGSM()
{
    int regionIndex;
    int channel;
    int facilityId;

    this->Resize(XC_MAX_XC_FGSM);

    /////////////////////////////////////////////////////////////////// 
    // ODU <-> ODU  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_FGSM_ODUXC_ODU_OTNOTU0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODUXC_ODU_OTNOTU0_START; regionIndex <= XC_FGSM_ODUXC_ODU_OTNOTU0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_FGSM_ODUXC_ODU_OTNOTU1_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODUXC_ODU_OTNOTU1_START; regionIndex <= XC_FGSM_ODUXC_ODU_OTNOTU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_FGSM_ODUXC_ODU_OTNOTU2_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODUXC_ODU_OTNOTU2_START; regionIndex <= XC_FGSM_ODUXC_ODU_OTNOTU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODUXC_ODU_IMUX_START; regionIndex <= XC_FGSM_ODUXC_ODU_IMUX_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
    }


    /////////////////////////////////////////////////////////////////// 
    // ODU3 <-> ODU2  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_FGSM_ODU32XC_ODU3_0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODU32XC_ODU3_0_START; regionIndex <= XC_FGSM_ODU32XC_ODU3_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }




    regionIndex = XC_FGSM_ODU32XC_ODU2_0_START;
    for(facilityId = XC_FGSM_ODU32XC_ODU2_0_FACILITY_ID; facilityId <= XC_FGSM_ODU32XC_ODU2_3_FACILITY_ID; facilityId++)
    {
        channel = 1;
        for(; channel <= XC_MAX_XC_FGSM_ODU32XC_ODU2; regionIndex++)
        {
            (*this)[regionIndex].SetOutputFacility(facilityId);
            (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
            (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
            (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
            (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        }

    }


    /////////////////////////////////////////////////////////////////// 
    // ODU3 <-> ODU1  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_FGSM_ODU31XC_ODU3_0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODU31XC_ODU3_0_START; regionIndex <= XC_FGSM_ODU31XC_ODU3_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }



    regionIndex = XC_FGSM_ODU31XC_ODU1_0_START;
    for(facilityId = XC_FGSM_ODU31XC_ODU1_0_FACILITY_ID; facilityId <= XC_FGSM_ODU31XC_ODU1_15_FACILITY_ID; facilityId++)
    {
        channel = 1;
        for(; channel <= XC_MAX_XC_FGSM_ODU31XC_ODU1; regionIndex++)
        {
            (*this)[regionIndex].SetOutputFacility(facilityId);
            (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
            (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
            (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
            (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        }

    }


    /////////////////////////////////////////////////////////////////// 
    // ODU3 <-> ODU0  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_FGSM_ODU30XC_ODU3_0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODU30XC_ODU3_0_START; regionIndex <= XC_FGSM_ODU30XC_ODU3_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_FGSM_ODU30XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODU30XC_ODU0_0_START; regionIndex <= XC_FGSM_ODU30XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId++);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }


    /////////////////////////////////////////////////////////////////// 
    // ODU2 <-> ODU1  XC
    ///////////////////////////////////////////////////////////////////

    regionIndex = XC_FGSM_ODU21XC_ODU2_0_START;
    for(facilityId = XC_FGSM_ODU21XC_ODU2_0_FACILITY_ID; facilityId <= XC_FGSM_ODU21XC_ODU2_3_FACILITY_ID; facilityId++)
    {
        channel = 1;
        for(; channel <= XC_MAX_XC_FGSM_ODU21XC_ODU2; regionIndex++)
        {
            (*this)[regionIndex].SetOutputFacility(facilityId);
            (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
            (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
            (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
            (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        }

    }

    regionIndex = XC_FGSM_ODU21XC_ODU1_0_START;
    for(facilityId = XC_FGSM_ODU21XC_ODU1_0_FACILITY_ID; facilityId <= XC_FGSM_ODU21XC_ODU1_15_FACILITY_ID; facilityId++)
    {
        channel = 1;
        for(; channel <= XC_MAX_XC_FGSM_ODU21XC_ODU1; regionIndex++)
        {
            (*this)[regionIndex].SetOutputFacility(facilityId);
            (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
            (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
            (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
            (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        }

    }


    /////////////////////////////////////////////////////////////////// 
    // ODU2 <-> ODU0  XC
    ///////////////////////////////////////////////////////////////////

    regionIndex = XC_FGSM_ODU20XC_ODU2_0_START;
    for(facilityId = XC_FGSM_ODU20XC_ODU2_0_FACILITY_ID; facilityId <= XC_FGSM_ODU20XC_ODU2_3_FACILITY_ID; facilityId++)
    {
        channel = 1;
        for(; channel <= XC_MAX_XC_FGSM_ODU20XC_ODU2; regionIndex++)
        {
            (*this)[regionIndex].SetOutputFacility(facilityId);
            (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
            (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
            (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
            (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        }

    }

    channel         = 1;
    facilityId      = XC_FGSM_ODU20XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODU20XC_ODU0_0_START; regionIndex <= XC_FGSM_ODU20XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId++);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }


    /////////////////////////////////////////////////////////////////// 
    // ODU1 <-> ODU0  XC
    ///////////////////////////////////////////////////////////////////

    regionIndex = XC_FGSM_ODU10XC_ODU1_0_START;
    for(facilityId = XC_FGSM_ODU10XC_ODU1_0_FACILITY_ID; facilityId <= XC_FGSM_ODU10XC_ODU1_15_FACILITY_ID; facilityId++)
    {
        channel = 1;
        for(; channel <= XC_MAX_XC_FGSM_ODU10XC_ODU1; regionIndex++)
        {
            (*this)[regionIndex].SetOutputFacility(facilityId);
            (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
            (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
            (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
            (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        }

    }

    channel         = 1;
    facilityId      = XC_FGSM_ODU10XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_FGSM_ODU10XC_ODU0_0_START; regionIndex <= XC_FGSM_ODU10XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId++);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}


//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateHGTMM()
{
    int regionIndex;
    int channel;
    int facilityId;

    this->Resize(XC_MAX_XC_HGTMM);

    // line -> client XC
    channel         = 1;
    facilityId      = HGTMM_XC_ODU3_CLIENT_1_FACILITY_ID;
    for (regionIndex = XC_HGTMM_ODU3_CLIENT_1_START; regionIndex <= XC_HGTMM_ODU2F_CLIENT_12_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId++);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    // client -> line XC
    channel         = 1;
    facilityId      = HGTMM_XC_ODU4_LINE_FACILITY_ID;
    for (regionIndex = XC_HGTMM_ODU4_LINE_TRIB_PORT_START; regionIndex <= XC_HGTMM_ODU4_LINE_TRIB_PORT_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    // line ODU4 MUX
    channel         = 1;
    facilityId      = HGTMM_XC_ODU4_MUX_FACILITY_ID;
    for (regionIndex = HGTMM_XC_ODU4_MUX_TRIBSLOT_START; regionIndex <= HGTMM_XC_ODU4_MUX_TRIBSLOT_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateOSM20()
{
    int regionIndex;
    int channel;
    int facilityId;

    this->Resize(XC_MAX_XC_OSM20);
	
    /////////////////////////////////////////////////////////////////// 
    // ODU <-> ODU  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUK_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUK_0_START; regionIndex <= XC_OSM20_ODUXC_ODUK_0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUK_1_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUK_1_START; regionIndex <= XC_OSM20_ODUXC_ODUK_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUK_2_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUK_2_START; regionIndex <= XC_OSM20_ODUXC_ODUK_2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUK_3_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUK_3_START; regionIndex <= XC_OSM20_ODUXC_ODUK_3_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODU1_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODU1_START; regionIndex <= XC_OSM20_ODUXC_ODU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODU2_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODU2_START; regionIndex <= XC_OSM20_ODUXC_ODU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUKPP_ODUK0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUKPP_ODUK0_START; regionIndex <= XC_OSM20_ODUXC_ODUKPP_ODUK0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUKPP_ODUK1_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUKPP_ODUK1_START; regionIndex <= XC_OSM20_ODUXC_ODUKPP_ODUK1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUKPP_ODU1_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUKPP_ODU1_START; regionIndex <= XC_OSM20_ODUXC_ODUKPP_ODU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_ODUKPP_ODU2_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_ODUKPP_ODU2_START; regionIndex <= XC_OSM20_ODUXC_ODUKPP_ODU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODUXC_IMUX_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODUXC_IMUX_START; regionIndex <= XC_OSM20_ODUXC_IMUX_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    /////////////////////////////////////////////////////////////////// 
    // FRM <-> ODU  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_OTUK_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_OTUK_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_OTUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_OTU1_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_OTU1_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_OTU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_OTU2_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_OTU2_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_OTU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_CBR_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_CBR_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_CBR_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_CBR10G_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_CBR10G_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_CBR10G_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_GE_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_GE_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_GE_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_FRM_GE10G_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_FRM_GE10G_START; regionIndex <= XC_OSM20_FRMODUXC_FRM_GE10G_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_OTUK_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_OTUK_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_OTUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_OTU1_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_OTU1_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_OTU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_OTU2_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_OTU2_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_OTU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID;
    for (regionIndex = XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_START; regionIndex <= XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU21 MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OSM20_ODU21XC_ODU2_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU21XC_ODU2_0_START; regionIndex <= XC_OSM20_ODU21XC_ODU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU21XC_ODU2)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODU21XC_ODU1_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU21XC_ODU1_0_START; regionIndex <= XC_OSM20_ODU21XC_ODU1_15_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU21XC_ODU1)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU20 MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OSM20_ODU20XC_ODU2_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU20XC_ODU2_0_START; regionIndex <= XC_OSM20_ODU20XC_ODU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU20XC_ODU2)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODU20XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU20XC_ODU0_0_START; regionIndex <= XC_OSM20_ODU20XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU20XC_ODU0)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU2F MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OSM20_ODU2FXC_ODU2_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU2FXC_ODU2_0_START; regionIndex <= XC_OSM20_ODU2FXC_ODU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODUF);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU2FXC_ODU2)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODU2FXC_ODUF_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU2FXC_ODUF_0_START; regionIndex <= XC_OSM20_ODU2FXC_ODUF_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODUF);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU2FXC_ODUF)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU10 MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OSM20_ODU10XC_ODU1_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU10XC_ODU1_0_START; regionIndex <= XC_OSM20_ODU10XC_ODU1_15_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU10XC_ODU1)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OSM20_ODU10XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_OSM20_ODU10XC_ODU0_0_START; regionIndex <= XC_OSM20_ODU10XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OSM20_ODU10XC_ODU0)
        {
            facilityId += 1;
            channel = 1;
        }
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateOSM()
{
    this->Resize(XC_MAX_ODUXC_OSM);

    // ODU XC only

    // digi120 chip 0
    int regionIndex;
    int channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODUK_DIGI0_START; regionIndex <= XC_OSM_ODUXC_ODUK_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODUK_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU1_DIGI0_START; regionIndex <= XC_OSM_ODUXC_ODU1_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU1_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU2_DIGI0_START; regionIndex <= XC_OSM_ODUXC_ODU2_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU2_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU3_DIGI0_START; regionIndex <= XC_OSM_ODUXC_ODU3_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU3_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU3);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU4_DIGI0_START; regionIndex <= XC_OSM_ODUXC_ODU4_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU4_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU4);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_CLIENT_DIGI0_START; regionIndex <= XC_OSM_ODUXC_CLIENT_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_CLIENT_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_IMUX_DIGI0_START; regionIndex <= XC_OSM_ODUXC_IMUX_DIGI0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    // digi120 chip 1
    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODUK_DIGI1_START; regionIndex <= XC_OSM_ODUXC_ODUK_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODUK_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU1_DIGI1_START; regionIndex <= XC_OSM_ODUXC_ODU1_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU1_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU2_DIGI1_START; regionIndex <= XC_OSM_ODUXC_ODU2_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU2_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU3_DIGI1_START; regionIndex <= XC_OSM_ODUXC_ODU3_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU3_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU3);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_ODU4_DIGI1_START; regionIndex <= XC_OSM_ODUXC_ODU4_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_ODU4_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU4);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_CLIENT_DIGI1_START; regionIndex <= XC_OSM_ODUXC_CLIENT_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_CLIENT_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM_ODUXC_IMUX_DIGI1_START; regionIndex <= XC_OSM_ODUXC_IMUX_DIGI1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateOSM1S()
{
    this->Resize(XC_MAX_ODUXC_OSM1S);

    // ODU XC only

    // HyPhyflex chip 0
    int regionIndex;
    int channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_START; regionIndex <= XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    // HyPhyflex chip 1
    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(regionIndex = XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_START; regionIndex <= XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateOMMX()
{
    int regionIndex;
    int channel;
    int facilityId;

    this->Resize(XC_MAX_XC_OMMX);

    /////////////////////////////////////////////////////////////////// 
    // ODU <-> ODU  XC
    ///////////////////////////////////////////////////////////////////
    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_0_START; regionIndex <= XC_OMMX_ODUXC_ODUK_0_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_0_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUK_0_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_0_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_1_START; regionIndex <= XC_OMMX_ODUXC_ODUK_1_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_1_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUK_1_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_1_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_2_START; regionIndex <= XC_OMMX_ODUXC_ODUK_2_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_2_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_2_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUK_2_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_2_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_3_START; regionIndex <= XC_OMMX_ODUXC_ODUK_3_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_3_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUK_3_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUK_3_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUK_3_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODU1_START; regionIndex <= XC_OMMX_ODUXC_ODU1_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODU1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODU1_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODU1_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODU1_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODU2_START; regionIndex <= XC_OMMX_ODUXC_ODU2_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODU2_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODU2_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODU2_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODU2_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODUK0_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODUK0_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODUK0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODUK1_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODUK1_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODUK1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODU1_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODU1_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODU1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODU2_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODU2_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODU2_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for (regionIndex = XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_START; regionIndex <= XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_END; regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    /////////////////////////////////////////////////////////////////// 
    // FRM <-> ODU  XC
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_OTUK_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_OTUK_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_OTUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_OTU1_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_OTU1_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_OTU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_OTU2_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_OTU2_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_OTU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_CBR_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_CBR_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_CBR_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_CBR10G_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_CBR10G_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_CBR10G_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_GE_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_GE_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_GE_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_FRM_GE10G_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_FRM_GE10G_START; regionIndex <= XC_OMMX_FRMODUXC_FRM_GE10G_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_OTUK_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_OTUK_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_OTUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_OTU1_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_OTU1_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_OTU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_OTU2_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_OTU2_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_OTU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel         = 1;
    facilityId      = XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID;
    for (regionIndex = XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_START; regionIndex <= XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU21 MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OMMX_ODU21XC_ODU2_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU21XC_ODU2_0_START; regionIndex <= XC_OMMX_ODU21XC_ODU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU21XC_ODU2)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OMMX_ODU21XC_ODU1_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU21XC_ODU1_0_START; regionIndex <= XC_OMMX_ODU21XC_ODU1_15_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU21XC_ODU1)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU20 MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OMMX_ODU20XC_ODU2_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU20XC_ODU2_0_START; regionIndex <= XC_OMMX_ODU20XC_ODU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU20XC_ODU2)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OMMX_ODU20XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU20XC_ODU0_0_START; regionIndex <= XC_OMMX_ODU20XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU20XC_ODU0)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU2F MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OMMX_ODU2FXC_ODU2_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU2FXC_ODU2_0_START; regionIndex <= XC_OMMX_ODU2FXC_ODU2_1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODUF);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU2FXC_ODU2)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OMMX_ODU2FXC_ODUF_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU2FXC_ODUF_0_START; regionIndex <= XC_OMMX_ODU2FXC_ODUF_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODUF);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU2FXC_ODUF)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    /////////////////////////////////////////////////////////////////// 
    // ODU10 MUX
    ///////////////////////////////////////////////////////////////////

    channel         = 1;
    facilityId      = XC_OMMX_ODU10XC_ODU1_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU10XC_ODU1_0_START; regionIndex <= XC_OMMX_ODU10XC_ODU1_15_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU10XC_ODU1)
        {
            facilityId += 1;
            channel = 1;
        }
    }

    channel         = 1;
    facilityId      = XC_OMMX_ODU10XC_ODU0_0_FACILITY_ID;
    for (regionIndex = XC_OMMX_ODU10XC_ODU0_0_START; regionIndex <= XC_OMMX_ODU10XC_ODU0_31_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU0);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);

        if(channel > XC_MAX_XC_OMMX_ODU10XC_ODU0)
        {
            facilityId += 1;
            channel = 1;
        }
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateSSM()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_SSM_PORT0_FACILITY_ID;
    
    this->Resize(XC_MAX_XC_SSM);
        
    for (regionIndex = XC_SSM_CFG_PORT0_START; regionIndex <= XC_SSM_CFG_PORT11_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SSM_PORT)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
    channel         = 1;
    facilityId      = XC_SSM_PORT12_FACILITY_ID;
    for (regionIndex = XC_SSM_CFG_PORT12_START; regionIndex <= XC_SSM_CFG_TTP_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SSM_DWDM)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility, i.e. port 12, DWDM, IM_LINE and IM_PORT
        }
    }        
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateSMTMU()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_SMTMU_PORT0_FACILITY_ID;
    
    //
    //--- Resize the region to accomodate the maximum number of SMTMU connections.
    //
    this->Resize(XC_MAX_XC_SMTMU);

    //
    //--- The region is subdivided into sections.  Each section holds TSXC_Connect
    //--- instances for a specific interface on the SMTM.  Since each TSXC_Connect
    //--- instance represents a potential connection for a specific output, the
    //--- output attributes of each TSXC_Connect instance must be set.
    //
    for (regionIndex = XC_SMTMU_CFG_PORT0_START; regionIndex <= XC_SMTMU_CFG_PORT9_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SMTMU_PORT)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
    
    channel         = 1;
    facilityId      = XC_SMTMU_DWDM_FACILITY_ID;
    for (regionIndex = XC_SMTMU_CFG_DWDM_START; regionIndex <= XC_SMTMU_CFG_IM_PORT_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SMTMU_DWDM)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility, i.e. DWDM, IM_LINE and IM_PORT
        }
    }    
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateSMTMUDSD()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_SMTMUDSD_PORT0_FACILITY_ID;
    
    //
    //--- Resize the region to accomodate the maximum number of SMTMUD/SD connections.
    //
    this->Resize(XC_MAX_XC_SMTMUDSD);

    //
    //--- The region is subdivided into sections.  Each section holds TSXC_Connect
    //--- instances for a specific interface on the SMTMUDSD.  Since each TSXC_Connect
    //--- instance represents a potential connection for a specific output, the
    //--- output attributes of each TSXC_Connect instance must be set.
    //
    for (regionIndex = XC_SMTMUDSD_CFG_PORT0_START; regionIndex <= XC_SMTMUDSD_CFG_PORT9_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_SMTMUDSD_PORT)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
    
    channel = 1;
    for (regionIndex = XC_SMTMUDSD_CFG_DWDM_START; regionIndex <= XC_SMTMUDSD_CFG_DWDM_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_SMTMUDSD_DWDM_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateOTNM()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_OTNM_PORT1_FACILITY_ID;
    
    //
    //--- Resize the region to accomodate the maximum number of OTNM connections.
    //
    this->Resize(XC_MAX_XC_OTNM);

    //
    //--- The region is subdivided into sections.  Each section holds TSXC_Connect
    //--- instances for a specific interface on the OTNM.  Since each TSXC_Connect
    //--- instance represents a potential connection for a specific output, the
    //--- output attributes of each TSXC_Connect instance must be set.
    //
    for (regionIndex = XC_OTNM_CFG_PORT1_START; regionIndex <= XC_OTNM_CFG_PORT8_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_OTNM_PORT)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }
    
    channel = 1;
    for (regionIndex = XC_OTNM_CFG_OC192_START; regionIndex <= XC_OTNM_CFG_OC192_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_OTNM_OC192_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    //--- For midline ODU1s
    channel         = 1;
    facilityId      = XC_OTNM_ODU1_MIDLINE1_FACILITY_ID;
    for (regionIndex = XC_OTNM_CFG_ODU1_MIDLINE1_START; regionIndex <= XC_OTNM_CFG_ODU1_IMUX4_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_OTNM_ODU1)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility
        }
    }

    //--- For midline ODU2s
    channel         = 1;
    facilityId      = XC_OTNM_ODU2_HIGHSPEED_FACILITY_ID;
    for (regionIndex = XC_OTNM_CFG_ODU2_HIGHSPEED_START; regionIndex <= XC_OTNM_CFG_ODU2_IMUX_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
        
        if (channel > XC_MAX_XC_OTNM_ODU2)
        {
            channel = 1;  //--- restart at channel 1
            facilityId++; //--- do the next facility, i.e. port 12, DWDM, IM_LINE and IM_PORT
        }
    }

}


//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateRCMM()
{
    //
    //--- Resize the region.  The standard usage of TSXC_ConfigRegion is
    //    inefficient for the RCMM.  So, for the RCMM, only outputs that
    //    are connected have objects within this region.
    //
    this->Resize(0);
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateDCMM()
{
    int regionIndex;
    int channel;

    //
    //--- Resize the region to accomodate the maximum number of DCMM connections.
    //
    this->Resize(XC_MAX_XC_DCMM);

    //
    //--- The region is subdivided into sections.  Each section holds TSXC_Connect
    //--- instances for a specific interface on the DCMM.  Since each TSXC_Connect
    //--- instance represents a potential connection for a specific output, the
    //--- output attributes of each TSXC_Connect instance must be set.  Also, by
    //--- default, each TSXC_Connect instance represents an Unconnected Lambda.
    //
    for (regionIndex = XC_DCMM_CFG_LINE_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_LINE_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_LINE_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    for (regionIndex = XC_DCMM_CFG_EXPRESS_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_EXPRESS_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_EXPRESS_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    for (regionIndex = XC_DCMM_CFG_PORT0_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT0_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT0_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT1_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT1_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT1_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT2_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT2_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT2_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT3_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT3_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT3_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT4_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT4_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT4_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT5_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT5_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT5_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT6_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT6_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT6_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_STS1);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_FIXED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
        
    for (regionIndex = XC_DCMM_CFG_PORT7_START, channel = 1; 
        regionIndex <= XC_DCMM_CFG_PORT7_END;
        regionIndex++, channel++)
    {
        (*this)[regionIndex].SetOutputFacility(XC_DCMM_PORT7_FACILITY_ID);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_LAMBDA);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateNANOCCM()
{
    //
    //--- Resize the region.  The standard usage of TSXC_ConfigRegion is
    //    inefficient for the CCM.  So, for the CCM, only outputs that
    //    are connected have objects within this region.
    //
    this->Resize(0);
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateCADM()
{
    //
    //--- Resize the region.  The standard usage of TSXC_ConfigRegion is
    //    inefficient for the CADM.  So, for the CADM, only outputs that
    //    are connected have objects within this region.
    //
    this->Resize(0);
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateHDTG()
{
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_HDTG_ODU2_PORT0_FACILITY_ID;
    
    this->Resize(XC_MAX_XC_HDTG);
        
    for (regionIndex = XC_HDTG_CFG_ODU2_PORT0_START; regionIndex <= XC_HDTG_CFG_ODU2_PORT14_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId++);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_ODU2);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::PopulateHDTG2()
{
    // jhu1
    int regionIndex;
    int channel         = 1;
    int facilityId      = XC_HDTG2_ODU2F_PORT0_FACILITY_ID;
    
    this->Resize(XC_MAX_XC_HDTG2);
    
    // XC
    for (regionIndex = XC_HDTG2_ODU2F_PORT0_START; regionIndex <= XC_HDTG2_ODU2F_PORT15_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId++);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    // MUX
    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX0_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX0_START; regionIndex <= XC_HDTG2_ODUF_MUX0_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX1_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX1_START; regionIndex <= XC_HDTG2_ODUF_MUX1_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX2_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX2_START; regionIndex <= XC_HDTG2_ODUF_MUX2_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX3_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX3_START; regionIndex <= XC_HDTG2_ODUF_MUX3_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX4_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX4_START; regionIndex <= XC_HDTG2_ODUF_MUX4_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX5_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX5_START; regionIndex <= XC_HDTG2_ODUF_MUX5_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX6_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX6_START; regionIndex <= XC_HDTG2_ODUF_MUX6_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel    = 1;
    facilityId = XC_HDTG2_ODU2F_MUX7_FACILITY_ID;
    for (regionIndex = XC_HDTG2_ODUF_MUX7_START; regionIndex <= XC_HDTG2_ODUF_MUX7_END; regionIndex++)
    {
        (*this)[regionIndex].SetOutputFacility(facilityId);
        (*this)[regionIndex].SetOutputFacilityEndpoint(channel++);
        (*this)[regionIndex].SetType(CT_XC_TYPE_UNSPECIFIED);
        (*this)[regionIndex].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[regionIndex].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::AddConnection(TSXC_Connect& Connection)
{
    uint32         index;
    bool           found;
    TSXC_Connect*  newConnPtr;

    // Search for Connection in region
    for(index = 0, found = false; index < (*this).Size() && found == false; index++)
    {
        // If Connection is found, update its attributes
        if ( ((*this)[index].GetOutputFacility()         == Connection.GetOutputFacility()) &&
             ((*this)[index].GetOutputFacilityEndpoint() == Connection.GetOutputFacilityEndpoint()) )
        {
            found = true;

            (*this)[index].SetInputFacility(Connection.GetInputFacility());
            (*this)[index].SetInputFacilityEndpoint(Connection.GetInputFacilityEndpoint());
            (*this)[index].SetType(Connection.GetType());
            (*this)[index].SetMapping(Connection.GetMapping());
            (*this)[index].SetState(CT_XC_STATE_CONNECTED);
        }
    }

    // If Connection was not found, create it and add it to region
    if (found == false)
    {
        newConnPtr = dynamic_cast <TSXC_Connect*> ((*this).Allocate(index));

        if (newConnPtr != NULL)
        {
            newConnPtr->SetOutputFacility(Connection.GetOutputFacility());
            newConnPtr->SetOutputFacilityEndpoint(Connection.GetOutputFacilityEndpoint());
            newConnPtr->SetInputFacility(Connection.GetInputFacility());
            newConnPtr->SetInputFacilityEndpoint(Connection.GetInputFacilityEndpoint());
            newConnPtr->SetType(Connection.GetType());
            newConnPtr->SetMapping(Connection.GetMapping());
            newConnPtr->SetState(CT_XC_STATE_CONNECTED);

            (*this).AddAt(index, newConnPtr);
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------
template<class T> void TSXC_ConfigRegion<T>::DeleteConnection(TSXC_Connect& Connection)
{
    uint32         index;
    bool           found;
    TSXC_Connect*  connPtr;

    // Search for Connection in region
    for(index = 0, found = false; index < (*this).Size(); index++)
    {
        if ( ((*this)[index].GetOutputFacility()         == Connection.GetOutputFacility()) &&
             ((*this)[index].GetOutputFacilityEndpoint() == Connection.GetOutputFacilityEndpoint()) )
        {
            found = true;
            break;
        }
    }

    // If Connection was found, remove it from region
    if (found == true)
    {
        connPtr = &((*this)[index]);
        (*this).RemoveAt(index);
        (*this).Deallocate(dynamic_cast <TSXC_Connect*> (connPtr));
    }
}

//------------------------------------------------------------------------------------------------------------------------
#endif //--- _INC_TSXC_ConfigRegion_H
