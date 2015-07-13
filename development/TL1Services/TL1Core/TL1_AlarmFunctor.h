/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 15, 2003- Jean-Francois Tremblay
DESCRIPTION:    Alarm Functors Definitions
-----------------------------------------------------------------------------*/ 
#include <iostream>
#include <iomanip>
#include <cstring>

#ifndef __TL1_ALARMFUNCTOR_H__
#define __TL1_ALARMFUNCTOR_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_GENERICFUNCTOR_H__
#include <TL1Core/TL1_GenericFunctor.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_ALARMRSPBLK_H__
#include <Response/TL1_AlarmRspBlk.h>
#endif

#ifndef __TL1_ENVRSPBLK_H__
#include <Response/TL1_EnvRspBlk.h>
#endif

#ifndef _AG7100_SC_GCC_IF_H_
#include <AG7100/AG7100_GccIf.h>
#endif

#ifndef _AG7100_SLOTIF_H_
#include <AG7100/AG7100_SlotIf.h>
#endif

#include <AM/AMA_BbAlarmObject.h>
#include <Facility/Fac_BbOduKTCfg.h>
#include <TL1Facility/T7100_TL1Odu0TEntity.h>
#include <TL1Facility/T7100_TL1Odu1TEntity.h>
#include <TL1Facility/T7100_TL1Odu2TEntity.h>
#include <TL1Facility/T7100_TL1Odu3TEntity.h>
#include <TL1Facility/T7100_TL1Odu4TEntity.h>
#include <TL1Facility/T7100_TL1OdufTEntity.h>

#include <CommonTypes/CT_Time.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <AGIF/AGIF_MainIf.h>
#include <TL1Core/T7100_TL1AgentUtility.h>
#include <AG7100/AG7100_SmartCardIf.h>
#include <AG7100/AG7100_VcgIf.h>
#include <AG7100/AG7100_EvcIf.h>
#include <AG7100/AG7100_OdukPoolsIf.h>
#include <AG7100/AG7100_LinkIf.h>
#include <AgFacility/Fac_OduKPoolsSubApp.h>
#include <AgFacility/Fac_VcgSubApp.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <Layer2Management/EVC_ContextManager.h>
#include <DCC/GCC_SubApplication.h>

#define TL1_ALARM_FUNCTOR_ENTITY_DEFAULT  0
#define TL1_ALARM_FUNCTOR_ENTITY_ENV      1
#define TL1_ALARM_FUNCTOR_ENTITY_RSVPADJ  2
#define TL1_ALARM_FUNCTOR_ENTITY_TL       3

/*-------------------------------------------------------------------------
// Functors declarations
//-----------------------------------------------------------------------*/

/** CLASS AppendAlarmFunctor
    This functor append an alarm response block to a TL1Response
    given an entity, entity address and an alarm object
*/
template < class AddressType >
class AppendAlarmFunctor : public unary_function< AMA_BbAlarmObject, void >
{
public:
    AppendAlarmFunctor( const TL1_Entity& theEntity,
                        const AddressType& theAddress,
                        TL1_Response& theResponse,
                        int theAlarmEntityType = TL1_ALARM_FUNCTOR_ENTITY_DEFAULT) :
        itsEntity( theEntity ),
        itsAddress( theAddress ),
        itsResponse( theResponse ),
        itsAlarmEntityType( theAlarmEntityType ),
        itsAmoState(NULL)
    {}

    void operator()( const AMA_BbAlarmObject& theAlarmObject ) const
    {

      bool flag = true;
      string facType = itsEntity.GetAidName();
      const CT_TL1_FacAddr* facAddr = dynamic_cast< const CT_TL1_FacAddr* >( &itsAddress);

      if( (strcmp(facType.c_str(),"STS1") == 0)    ||
          (strcmp(facType.c_str(),"STS3C") == 0)   ||
          (strcmp(facType.c_str(),"STS12C") == 0)  ||
          (strcmp(facType.c_str(),"STS48C") == 0)  ||
          (strcmp(facType.c_str(),"STS192C") == 0)  )
      {
          CT_AG_PortId aPort = CT_AG_PORT_UNKNOWN;
          if (facAddr)
          {
             const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
             CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();
             aPort = AGIF_MainIf::ConvertTL1PortIdToAgentPortId(cardFam, FAC_SUBTYPE_ALL, facAddr->GetPort(), T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardType());
          }

          if (facAddr->GetChannel().WavelengthIndex() != (uint8)(theAlarmObject.GetStartChannel() - 1) ||
                                                                       aPort != theAlarmObject.GetPortId())
          {
              flag = false;
          }
      }

      //-------------------------------------------------------------------------------------------------
      // ENH_TRN ODU4 facility's -PORT ID- (CT_TL1_PORT_0..CT_TL1_PORT_1) must match AlmStChan.
      //-------------------------------------------------------------------------------------------------
      if (strcmp(facType.c_str(),"ODU4") == 0)
      {
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();
          CT_CardType cardType = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardType();

          if ( cardFam == ENH_TRN_FAM )
          {
              if ( facAddr->GetPort() != ((CT_TL1_Port)(theAlarmObject.GetStartChannel() - 1)) )
              {
                  flag = false;
              }
          }
	  else if(cardType == CARD_TYPE_OSM2C )
	  {
	      if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODU4) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_Layer4).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
              {
                  flag = false;
              }
	  }
      }

      //-------------------------------------------------------------------------------------------------
      // FGSM facility's -Wavelth- (ODU3 1) must match AlmStChan(1).
      //-------------------------------------------------------------------------------------------------
      if (strcmp(facType.c_str(),"ODU3") == 0)
      {
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();
          CT_CardType cardType = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardType();

          if ( cardFam == FGSM_FAM || cardType == CARD_TYPE_OSM2C )
          {
             if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODU3) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_Layer3).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
             {
                 flag = false;
             }
          }
      }

      //-------------------------------------------------------------------------------------------------
      // FGTMM LINE side ODUK facility's WavelengthIndex (0..3) must match the Alarm's StartChannel (1..4).
      // HDTG  PORT side ODU2 facility's -PORT ID- (CT_TL1_PORT_0..CT_TL1_PORT_9) must match AlmStChan.
      // SSM40/ENH_PACKETODUK facility's -Wavelth- (ODU2 1-4) must match AlmStChan(1..4).
      //-------------------------------------------------------------------------------------------------
      if ( strcmp(facType.c_str(),"ODU2") == 0 )
      {
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();

          if ( cardFam == FGTMM_FAM )
          {
              if (facAddr->GetChannel().WavelengthIndex() != (uint8)(theAlarmObject.GetStartChannel() - 1))
              {
                  flag = false;
              }
          }
          else if ( cardFam == HDTG_FAM || cardFam == ENH_PACKET_FAM || cardFam == HDTG2_FAM)
          {
              if ( facAddr->GetPort() != ((CT_TL1_Port)(theAlarmObject.GetStartChannel() - 1)) )
              {
                  flag = false;
              }
          }
          else if ( cardFam == SSM40_FAM || cardFam == FGSM_FAM || cardFam == OMM_FAM || cardFam == HGTMM_FAM || cardFam == OSM_FAM)
          {
             if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODU2) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_Layer2).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
              {
                  flag = false;
              }
          }
      }

      if(strcmp(facType.c_str(),"ODU2E") == 0)
      {
	  const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();
	  if(cardFam == OSM_FAM)
	  {
	      if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODU2E) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_Layer2).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
              {
                  flag = false;
              }
	  }
      }

      //-------------------------------------------------------------------------------------------------
      // SSM40/ENH_PACKETODUK/OMM facility's -Wavelth- (ODU1 1-16) must match AlmStChan(1..16).
      //-------------------------------------------------------------------------------------------------
      if (strcmp(facType.c_str(),"ODU1") == 0)
      {
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();

          if ( cardFam == SSM40_FAM || cardFam == FGSM_FAM || cardFam == OMM_FAM || cardFam == OSM_FAM )
          {
             if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODU1) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_Layer1).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
              {
                  flag = false;
              }
          }
      }

      //-------------------------------------------------------------------------------------------------
      // SSM40/FGSM/OMM facility's -Wavelth- (ODU0 1-32) must match AlmStChan(1..32).
      //-------------------------------------------------------------------------------------------------
      if (strcmp(facType.c_str(),"ODU0") == 0)
      {
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFam = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily().GetCardFamily();

          if ( cardFam == SSM40_FAM || cardFam == FGSM_FAM || cardFam == OMM_FAM || cardFam == OSM_FAM || cardFam == HGTMM_FAM) // t71mr00215184
          {
             if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODU0) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_Layer0).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
             {
                 flag = false;
             }
          }
      }

      //-------------------------------------------------------------------------------------------------
      // OSM20 facility's -Wavelth- (ODUF 1-16) must match AlmStChan(1..16).
      //-------------------------------------------------------------------------------------------------
      if (strcmp(facType.c_str(),"ODUF") == 0)
      {
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardType cardType = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardType();

          if ( cardType == CARD_TYPE_OSM20 || cardType == CARD_TYPE_OMMX || cardType == CARD_TYPE_OSM2S || cardType == CARD_TYPE_OSM2C || cardType == CARD_TYPE_HDTG2 || cardType == CARD_TYPE_HGTMMS) // t71mr00215184
          {
             if (T7100_TL1AgentUtility::ConvertFacAddrToOduMap(*facAddr, FAC_SUBTYPE_ODUF) != 
                 T7100_TL1AgentUtility::GetSmartCardIf(slotAddr).GetOduKIf(CT_ODU_LayerF).GetFacSubApp().GetOduMapByIndex((bbindex_t)(theAlarmObject.GetStartChannel()-1)))
             {
                 flag = false;
             }
          }
      }

      if (strncmp(facType.c_str(),"ODU0T", 5) == 0)
      {
          Fac_BbOduKTCfg& TheOduKT = (dynamic_cast<const T7100_TL1Odu0TEntity&>(itsEntity)).GetOduKTConfigObject(*facAddr);
          if ( TheOduKT.GetEntityIndex() != (int)(theAlarmObject.GetStartChannel() - 1) )
          {
              flag = false;
          }
      }
      else if (strncmp(facType.c_str(),"ODU1T", 5) == 0)
      {
          Fac_BbOduKTCfg& TheOduKT = (dynamic_cast<const T7100_TL1Odu1TEntity&>(itsEntity)).GetOduKTConfigObject(*facAddr);
          if ( TheOduKT.GetEntityIndex() != (int)(theAlarmObject.GetStartChannel() - 1) )
          {
              flag = false;
          }
      }
      else if (strncmp(facType.c_str(),"ODU2T", 5) == 0)
      {
          Fac_BbOduKTCfg& TheOduKT = (dynamic_cast<const T7100_TL1Odu2TEntity&>(itsEntity)).GetOduKTConfigObject(*facAddr);
          if ( TheOduKT.GetEntityIndex() != (int)(theAlarmObject.GetStartChannel() - 1) )
          {
              flag = false;
          }
      }
      else if (strncmp(facType.c_str(),"ODU3T", 5) == 0)
      {
          Fac_BbOduKTCfg& TheOduKT = (dynamic_cast<const T7100_TL1Odu3TEntity&>(itsEntity)).GetOduKTConfigObject(*facAddr);
          if ( TheOduKT.GetEntityIndex() != (int)(theAlarmObject.GetStartChannel() - 1) )
          {
              flag = false;
          }
      }
      else if (strncmp(facType.c_str(),"ODU4T", 5) == 0)
      {
          Fac_BbOduKTCfg& TheOduKT = (dynamic_cast<const T7100_TL1Odu4TEntity&>(itsEntity)).GetOduKTConfigObject(*facAddr);
          if ( TheOduKT.GetEntityIndex() != (int)(theAlarmObject.GetStartChannel() - 1) )
          {
              flag = false;
          }
      }
      else if (strncmp(facType.c_str(),"ODUFT", 5) == 0)
      {
          Fac_BbOduKTCfg& TheOduKT = (dynamic_cast<const T7100_TL1OdufTEntity&>(itsEntity)).GetOduKTConfigObject(*facAddr);
          if ( TheOduKT.GetEntityIndex() != (int)(theAlarmObject.GetStartChannel() - 1) )
          {
              flag = false;
          }
      }

      //-------------------------------------------------------------------------------------------------
      // POOL SFP WavelengthIndex (0..13) must match the Alarm's GetPortId (1..14).
      //-------------------------------------------------------------------------------------------------
      if (strcmp(facType.c_str(),"SFP") == 0 || strcmp(facType.c_str(),"XFP") == 0 
          || strcmp(facType.c_str(),"DCM") == 0 || strcmp(facType.c_str(),"OMD") == 0
          || strcmp(facType.c_str(),"QSFPP") == 0 || strcmp(facType.c_str(),"SFPP") == 0
          || (strcmp(facType.c_str(),"CXP") == 0)|| (strcmp(facType.c_str(),"CFP") == 0)
          || (strcmp(facType.c_str(),"CFP4") == 0))
      {
        const CT_TL1_SlotAddr* subSlotAddr = dynamic_cast< const CT_TL1_SlotAddr* >( &itsAddress);
        if (subSlotAddr)
        {
            CT_DaughterBoardId aPort = 
                T7100_TL1AgentUtility::ConvertAddressToDaughterBoardId(*subSlotAddr, theAlarmObject.GetPortId());
           if (subSlotAddr->GetSubSlot() != (uint8)(aPort))
           {
               flag = false;
           }
        }
      }

      if (strcmp(facType.c_str(),"SLOT") == 0)
      {
        if ((uint8)(theAlarmObject.GetPortId()) != CT_AG_PORT_UNKNOWN)
        {
            const CT_TL1_SlotAddr* subSlotAddr = dynamic_cast< const CT_TL1_SlotAddr* >( &itsAddress);
            if (subSlotAddr)
            {
                if ( CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsHwPicoVer() && 
                     subSlotAddr->GetSlot() == PICO_LIAME_1 )
                {
                    flag = false;
                }
                else
                {
                    CT_DaughterBoardId aPort = 
                        T7100_TL1AgentUtility::ConvertAddressToDaughterBoardId(*subSlotAddr, theAlarmObject.GetPortId());
                    if (subSlotAddr->GetSubSlot() != (uint8)(aPort))
                    {
                        flag = false;
                    }
                }
            }
        }
      }

      if ((strcmp(facType.c_str(),"LAPDL") == 0) || (strcmp(facType.c_str(),"LAPDS") == 0) ||
          (strcmp(facType.c_str(),"PPPL") == 0)  || (strcmp(facType.c_str(),"PPPS") == 0))
      {
          flag = T7100_TL1AgentUtility::DoesDccPortMatch(*facAddr, theAlarmObject.GetStartChannel());
      }

      if (strcmp(facType.c_str(),"GCC") == 0)
      {
          uint32 channelNum = theAlarmObject.GetStartChannel() - 1;
          int index = -1;
          const CT_TL1_SlotBaseAddr& slotAddr = dynamic_cast<const CT_TL1_SlotBaseAddr&>(itsAddress);
          CT_CardFamily cardFamily = T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardFamily();
          //It is agent port id in GCCMAP, need to convert TL1 port to AG port          
          CT_AG_PortId portId = AGIF_MainIf::ConvertTL1PortIdToAgentPortId(cardFamily,FAC_SUBTYPE_ALL, facAddr->GetPort(),T7100_TL1AgentUtility::GetProvisionedCardIf(slotAddr).GetCardType());
          CT_TEL_GccMap  GccMap(portId, facAddr->GetGccType(),
                          facAddr->GetMuxOdu(), facAddr->GetGccOdu());
         
          
          if (cardFamily == SSM40_FAM || cardFamily == OMM_FAM || cardFamily == HGTMM_FAM || cardFamily == OSM_FAM || cardFamily == HDTG2_FAM || cardFamily == ENH_TRN_FAM)
          {
              AG7100_CardIf*      cardIfPtr = T7100_TL1AgentUtility::GetSlotIf(*facAddr).GetCardPtr(cardFamily);
              AG7100_SmartCardIf* smartCardPtr   = NULL;

              if (cardIfPtr)
              {
                  smartCardPtr = dynamic_cast<AG7100_SmartCardIf*>(cardIfPtr);
              }
              
              if (smartCardPtr)
              {
                  index = smartCardPtr->GetGccIf().GetGccSubApp().GetGccIndex(GccMap);
              }
              if (index != (uint8)(channelNum))
              {
                  flag = false;
              }
          }

      }

      if (strcmp(facType.c_str(),"OSIRTR") == 0)
      {
        if ((uint8)(facAddr->GetSlot()-1) != (uint8)theAlarmObject.GetStartChannel())
        {
            flag = false;
        }
      }
      if (strcmp(facType.c_str(),"LAG") == 0)
      {
        if ( ((uint8)(facAddr->GetChannel().WavelengthIndex()) != (uint8)(theAlarmObject.GetStartChannel() -1)) ||
             (facAddr->GetSlot() != (CT_SlotId)(theAlarmObject.GetPortId())))
        {
            flag = false;
        }
      }
      if (strcmp(facType.c_str(),"VCG") == 0)
      {
          int vcgIndex = T7100_TL1AgentUtility::ConvertFacAddrToVcgIndex(*facAddr);
          if (vcgIndex != Fac_VcgSubApp::VCG_NOT_FOUND)
          {
              if ((uint8)(vcgIndex) != (uint8)(theAlarmObject.GetStartChannel() -1))
              {
                  flag = false;
              }
          }
          else
          {
              flag = false;
          }
        
      }
      if (strcmp(facType.c_str(),"EVC") == 0)
      {
          CT_EvcData aEvcData = T7100_TL1AgentUtility::ConvertFacAddrToEvcData(*facAddr);
          EVC_ConfigBbObject* aCfgObj = EVC_CtxMgr::Instance()->GetEvcCfgObject(aEvcData, aEvcData.GetShelf(), aEvcData.GetSlot());
          if ((uint8)(aCfgObj->GetIndex()) != (uint8)(theAlarmObject.GetStartChannel() -1))
          {
              flag = false;
          }
      }

      // Make sure the SwitchDomain(-2,-3, etc.) logical matches the StartChannel(1,2,etc.).
      if (strcmp(facType.c_str(), "SWITCHDOMAIN") == 0)
      {
          const CT_TL1_LogicalAddr& SWDAddr = dynamic_cast<const CT_TL1_LogicalAddr&>(itsAddress);

          //=========================================================================================
          // Goal: Align SwitchDomain Index with Alarm object start channel
          //  - SwitchDomain Index is shelf ID based (start PS2) in paired switchdomains
          //  - SwitchDomain Index is 0 based in Multishelf configurations and there will be only 1
          //==========================================================================================
          CT_TL1_LogicalId aLogicalId = SWDAddr.GetLogical();
          uint32 aLogicalChannel = aLogicalId - (aLogicalId >= FIRST_PORT_SHELF ? FIRST_PORT_SHELF : 0);
          aLogicalChannel++; //Resolve to 'ones based' start channel

          if ( aLogicalChannel != theAlarmObject.GetStartChannel() )
          {
              flag = false;
          }
      }

      bool forceETHMACPORTAid = false;
      //===============================================================================================
      // A SYNCETH facility (ESM) may be provisioned, but this alarm(s) might be for a ETH/MAC/PORT.
      // The only valid alarm for a SYNCETH facility is SYNC_REF_FAIL, otherwise it is ETH/MAC/PORT!
      //===============================================================================================
      if (strcmp(facType.c_str(), "SYNCETH") == 0)
      {
          if ( theAlarmObject.GetConditionType() != CT_SYNC_REF_FAIL_COND_TYPE )
          {
              forceETHMACPORTAid = true; ///////////////////////////////////////
          }
      }

      if ((strcmp(facType.c_str(),"SWITCHDOMAIN") == 0))
      {
          uint8 switchDomainIndex = CT_SWITCH_DOMAIN_UNKNOWN;
          uint8 theSwitchDomainId = CT_SWITCH_DOMAIN_UNKNOWN;

          CT_SubNodeConfiguration aSubNodeCfg = 
              CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();

          const CT_TL1_LogicalAddr* logicalAddr = 
              dynamic_cast< const CT_TL1_LogicalAddr* >( &itsAddress);

          theSwitchDomainId = logicalAddr->GetLogical();

          if (aSubNodeCfg.IsSwitchShelfSupported())
          {
              // valid indexes are 0..8
              if (theSwitchDomainId == CT_SWITCH_DOMAIN_MULTISHELF)
              {
                  switchDomainIndex = CT_SWITCH_DOMAIN_START_INDEX;
              }
              else
              {
                  switchDomainIndex = theSwitchDomainId - FIRST_PORT_SHELF + 1;
              }
          }
          else
          {
              // return the 0 based index
              // valid switch domains are 2..9
              // valid indexes are 0..7
              switchDomainIndex = theSwitchDomainId - FIRST_PORT_SHELF;
          }

          if (switchDomainIndex != (uint8)theAlarmObject.PairedRegionIndex())
          {
              flag = false;
          }
      }

      if (strcmp(facType.c_str(),"MGTETH") == 0)
      {
            if ( facAddr->GetPort() != ((CT_TL1_Port)(theAlarmObject.GetStartChannel() - 1)) )
            {
                flag = false;
            }
      }
      
      if(flag == true)  
      {
          // First determine if this is a raised alarm
          if ( ( theAlarmObject.GetNotificationCode() != CT_CLEAR )
               && ( theAlarmObject.GetNotificationCode() != CT_UNRESOLVED ) )
          {
              // CT_TimeTm temporary object due to bogus interface
              CT_TimeTm tempo;

              switch(itsAlarmEntityType)
              {
                  case TL1_ALARM_FUNCTOR_ENTITY_ENV:
                      {  
                          TL1_EnvRspBlk respBlock(
                                                 *(dynamic_cast<const CT_TL1_LogicalAddr*>(&itsAddress)),
                                                 theAlarmObject.GetNotificationCode(),
                                                 theAlarmObject.GetConditionType(),
                                                 theAlarmObject.GetTimeTag().GetCtTime(tempo),                                       
                                                 theAlarmObject.GetConditionDescription() );
                          itsResponse.AddResponseBlock( respBlock );
                      }
                      break;

                  default:
                      {                
                          string anEntityAid;
                          if (strcmp(facType.c_str(),"GCC") == 0)
                          {
                              switch(facAddr->GetGccType())
                              {
                                   case CT_GCC_0:
                                       anEntityAid = "GCC0";
                                       break;
                                   case CT_GCC_1:
                                       anEntityAid = "GCC1";
                                       break;
                                   case CT_GCC_2:
                                       anEntityAid = "GCC2";
                                       break;
                                   case CT_GCC_1_2:
                                       anEntityAid = "GCC12";
                                       break;
                              }
                          }
                          else
                          {
                              anEntityAid = itsEntity.GetAidName();
                          }

                          if ( forceETHMACPORTAid ) // ESM20/40 ETH fac!
                          {
                              anEntityAid = "ETH";
                          }

                          const CT_TL1_SlotAddr* slotAddr = dynamic_cast< const CT_TL1_SlotAddr* >( &itsAddress);
                          if ( slotAddr && 
                              CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsHwPicoVer() && 
                              strcmp(facType.c_str(),"OMD") == 0 ) 
                          {
                              // Because in PICO, the OMD AID format is OMD-shelfid-subslotid without displaying slotid.
                              // Generate the response according to the rule.
                              CT_TL1_SlotAddr tmpAid(slotAddr->GetShelf(), slotAddr->GetSubSlot()); 
                              TL1_AlarmRspBlk respBlock(
                                                     anEntityAid,
                                                     tmpAid,
                                                     theAlarmObject.GetNotificationCode(),
                                                     theAlarmObject.GetConditionType(),
                                                     theAlarmObject.GetSAFlag(),
                                                     theAlarmObject.GetTimeTag().GetCtTime(tempo),
                                                     theAlarmObject.GetNearEnd(),
                                                     theAlarmObject.GetDirectionDisplay(),
                                                     theAlarmObject.GetConditionDescription() );
                              itsResponse.AddResponseBlock( respBlock );
                              return;
                          }
                          const CT_TL1_FacAddr* facAddr = dynamic_cast< const CT_TL1_FacAddr* >( &itsAddress);
                          if ( facAddr && 
                              CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsHwPicoVer() && 
                              strcmp(facType.c_str(),"MGTETH") == 0 ) 
                           {
                              // Because in PICO, the MGTETH AID format is OMD-shelfid-portid without displaying slotid.
                              // Generate the response according to the rule.																									 
														 CT_TL1_SlotAddr tmpAid(facAddr->GetShelf(), facAddr->GetPort()+1); 
                             TL1_AlarmRspBlk respBlock(
                                                     anEntityAid,
                                                     tmpAid,
                                                     theAlarmObject.GetNotificationCode(),
                                                     theAlarmObject.GetConditionType(),
                                                     theAlarmObject.GetSAFlag(),
                                                     theAlarmObject.GetTimeTag().GetCtTime(tempo),
                                                     theAlarmObject.GetNearEnd(),
                                                     theAlarmObject.GetDirectionDisplay(),
                                                     theAlarmObject.GetConditionDescription() );
                              itsResponse.AddResponseBlock( respBlock );
                              return;														 
                          }
                          TL1_AlarmRspBlk respBlock(
                                                 anEntityAid,
                                                 itsAddress,
                                                 theAlarmObject.GetNotificationCode(),
                                                 theAlarmObject.GetConditionType(),
                                                 theAlarmObject.GetSAFlag(),
                                                 theAlarmObject.GetTimeTag().GetCtTime(tempo),
                                                 theAlarmObject.GetNearEnd(),
                                                 theAlarmObject.GetDirectionDisplay(),
                                                 theAlarmObject.GetConditionDescription() );
                          itsResponse.AddResponseBlock( respBlock );
                      }            
              }
          }
      }
   }

   void SetAmoState(SM_AmoRegion *amoState)
   {
        itsAmoState = amoState;
   }

private:
    const TL1_Entity& itsEntity;
    const AddressType& itsAddress;
    TL1_Response& itsResponse;
    int itsAlarmEntityType;

    SM_AmoRegion *itsAmoState;
};


class TL1_AlarmCondFilter : public unary_function< AMA_BbAlarmObject, bool >
{
public:
    TL1_AlarmCondFilter( const TL1_SmartParameter< CT_NotificationCode >& theNotifCode,
                         const TL1_SmartParameter< CT_ConditionType >& theCondType,
                         const TL1_SmartParameter< CT_SAFlag >& theServAffectingFlag,
                         const TL1_SmartParameter< CT_NEFlag >& theLocation,
                         const TL1_SmartParameter< CT_DirectionFlag >& theDirection ) :
        itsNotifCode(theNotifCode),
        itsCondType(theCondType),
        itsServAffectingFlag(theServAffectingFlag),
        itsLocation(theLocation),
        itsDirection(theDirection)
    {}

    bool operator()( const AMA_BbAlarmObject& theAlarmObject ) const
    {
        bool result = true;

        if ( itsNotifCode.IsPresent() &&
             (itsNotifCode.GetValue() != theAlarmObject.GetNotificationCode()) )
        {
            result = false;
        }

        if ( itsCondType.IsPresent() &&
             (itsCondType.GetValue() != theAlarmObject.GetConditionType()) )
        {
            result = false;
        }

        if ( itsServAffectingFlag.IsPresent() &&
             (itsServAffectingFlag.GetValue() != theAlarmObject.GetSAFlag()) )
        {
            result = false;
        }

        if ( itsLocation.IsPresent() &&
             (itsLocation.GetValue() != theAlarmObject.GetNearEnd()) )
        {
            result = false;
        }

        if ( itsDirection.IsPresent() && 
            ( itsDirection.GetValue() != theAlarmObject.GetSimpleDirection()) )
        {
            // In case we have both directions, NA direction shall not be sent.
            if ( ( itsDirection.GetValue() != CT_BOTH ) ||
                 ( itsDirection.GetValue() == CT_BOTH && theAlarmObject.GetSimpleDirection() == CT_DIR_DONT_CARE ) )
            {
                result = false;
            }
        }

        return result;
    }

private:
    const TL1_SmartParameter< CT_NotificationCode > itsNotifCode;
    const TL1_SmartParameter< CT_ConditionType > itsCondType;
    const TL1_SmartParameter< CT_SAFlag > itsServAffectingFlag;
    const TL1_SmartParameter< CT_NEFlag > itsLocation;
    const TL1_SmartParameter< CT_DirectionFlag > itsDirection;
};


/**
 CLASS TL1_IsAlarmedPredicate
 
 This is a predicate (a functor returning a bool) that returns true
 if the AMA_BbAlarmObject is an alarm.
*/
struct TL1_IsAlarmedPredicate : public unary_function< AMA_BbAlarmObject, bool >
{
    TL1_IsAlarmedPredicate( bool includeNR = false ) : itsIncludeNRflag( includeNR ) {}

    bool operator()( const AMA_BbAlarmObject& theAlarm ) const
    {
        return ( ( (theAlarm.GetNotificationCode() == CT_CRITICAL) ||
                   (theAlarm.GetNotificationCode() == CT_MAJOR)    ||
                   (theAlarm.GetNotificationCode() == CT_MINOR)    ||
                   (itsIncludeNRflag && (theAlarm.GetNotificationCode() == CT_NOT_REPORTED) ) ) &&
                 !theAlarm.IsTransientCondition() );
    }
private:
    bool itsIncludeNRflag;
};

/**
 CLASS TL1_IsConditionPredicate
 
 This is a predicate (a functor returning a bool) that returns true
 if the AMA_BbAlarmObject is a condition.
*/
struct TL1_IsConditionPredicate : public unary_function< AMA_BbAlarmObject, bool >
{
    TL1_IsConditionPredicate( bool includeNR = false ) : itsIncludeNRflag( includeNR ) {}

    bool operator()( const AMA_BbAlarmObject& theAlarm ) const
    {
        return ( ( (theAlarm.GetNotificationCode() == CT_CRITICAL)     ||
                   (theAlarm.GetNotificationCode() == CT_MAJOR)        ||
                   (theAlarm.GetNotificationCode() == CT_MINOR)        ||
                   (theAlarm.GetNotificationCode() == CT_NOT_ALARMED ) ||
                   (itsIncludeNRflag && (theAlarm.GetNotificationCode() == CT_NOT_REPORTED) ) ) &&
                 !theAlarm.IsTransientCondition() );
    }
private:
    bool itsIncludeNRflag;
};


#endif
