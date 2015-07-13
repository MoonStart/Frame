/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     May 21, 2006  Larry M. Wolfrum.
 DESCRIPTION:   Action to populate a PM file image buffer.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <TimeService/FC_TimeService.h>
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_TimerDispatcher.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100/T6100_CardIf.h>
#include <CommonTypes/CT_PMA_General.h>
#include <CommonTypes/CT_PM_BinaryFileHandler.h>
#include <CommonTypes/CT_PM_FileNameHandle.h>
#include <CommonTypes/CT_PM_FileTransferBase.h>
#include <CommonTypes/CT_PM_FileOps.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_PortMap.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Hop.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Odu.h>
#include <Configuration/CFG_Tcm.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_BbValue.h>
#include <PM/PM_Def.h>
#include <PM/PM_FileStorageSubApplication.h>
#include <PM/PM_HopNearEndSubApplication.h>
#include <EPM/PM_FilePopulationAction.h>
#include <PM/PM_TypeHopNearEnd.h>
#include <EPM/PM_BbFileTransfer.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <SignalProtection/SP_ERSBaseApplication.h>
#include <CsPii/CSPII_CardIF.h>

using namespace std;

extern bool gPM_FileTrace;

//-----------------------------------------------------------------
PM_FilePopulationAction::PM_FilePopulationAction(PM_FileStorageSubApplication& theContext,
                                                 CT_PM_Period thePeriod,
                                                 CT_PM_DataType theDataType) :

    myContext(theContext),
    myState(PM_START_BUILDING),
    myPeriod(thePeriod),
    myDelay(PM_FILE_INITIALIZATION_DELAY),
    myFileHandler(NULL),
    myDataType(theDataType),
    myDuplicateFileCount(0)
{
    myBbAction = new FC_BbAction(this);

    myFileNameHandle = new PM_FileNameHandle( myPeriod,
                                              theContext.GetCardContext().GetShelfId(),
                                              theContext.GetCardContext().GetCardId(),
                                              CT_TL1_PORT_UNKNOWN,
                                              CT_PM_FILE_UNCOMPRESSED,
                                              0,
                                              CT_PM_RPT_HISTORICAL,
                                              myDataType );

    // Less than pleasing way of initializing a vector to a particular size.
    PM_BinFileParamData dummyParam;
    myParamVector.reserve( PM_MAX_NUMBER_OF_PARAMETERS );

    for( uint32 param = 0; param < PM_MAX_NUMBER_OF_PARAMETERS; param++ )
    {
        myParamVector.push_back( dummyParam );
    }

}

//-----------------------------------------------------------------
PM_FilePopulationAction::~PM_FilePopulationAction()
{
    delete myFileNameHandle;
    delete myBbAction;
}

//-----------------------------------------------------------------
FC_Object*  PM_FilePopulationAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    bool duplicateFile = false;


    switch(myState)
    {
    case PM_START_BUILDING:

//      fc_cout << "PM_FilePopulationAction: PM_START_BUILDING" << endl;

        mySubAppVecIt = myContext.GetSubApplicationVector().begin();

        myFileNameHandle->SetTime( myContext.GetControlPeriodTimeStamp( myPeriod ) );
        myFileNameHandle->Fungrulate();
        myEntityCount = 0;

        if( gPM_FileTrace )
        {
            FC_Time currentTime;
            currentTime.GetCurrentTime();

            currentTime.DisplayLocal(fc_cout);
            fc_cout << " PM_FilePopulationAction: File name = " << myFileNameHandle->GetFileNameHandleStr() << endl;
        }

        // Check to see if this action was inadvertently rescheduled for the same file.
        duplicateFile = CT_PM_FileTransferBase::Instance()->IsDuplicateFile( *myFileNameHandle );
        if( duplicateFile )
        {
            myDuplicateFileCount++;

            if( gPM_FileTrace )
            {
                fc_cout << "PM_FilePopulationAction: Duplicate file count = " << myDuplicateFileCount << endl;
            }
        }

        // Get buffer pointer.
        if( (!duplicateFile) &&
            ((myBuffer = CT_PM_FileTransferBase::Instance()->AllocateFileBuffer( *myFileNameHandle )) != NULL) &&
            ((myFileHandler = new PM_BinaryFileHandler( *myFileNameHandle, myBuffer, PM_FILE_BUFFER_PATH_SIZE_MAX)) != NULL) )
        {
            // Change the state to PM_BUILDING_FILE and
            // purposely fall through to that state
            // without rescheduling the action.
            myState = PM_BUILDING_FILE;
        }
        else
        {
            // Could not get a buffer and/or a file handler.
            myState = PM_START_BUILDING;
            break;
        }


    case PM_BUILDING_FILE:

//      fc_cout << "PM_FilePopulationAction: PM_BUILDING_FILE" << endl;

        // Start building that file.
        myFacilityCount = 0;

        while( (myFacilityCount < 5) &&
               (mySubAppVecIt != myContext.GetSubApplicationVector().end()) )
        {
            AddDataToFile();
            mySubAppVecIt++;
        }

        if( mySubAppVecIt == myContext.GetSubApplicationVector().end() )
        {
            // Check to see if any data was actually collected.
            if( myEntityCount > 0 )
            {
                // Close out the file handler object
                uint32 fileBufferSize = myFileHandler->Close();
                CT_PM_FileTransferBase::Instance()->SetBufferSize( *myFileNameHandle, fileBufferSize );

#if 0
                CT_PM_FileOps fileOps( *myFileNameHandle, CT_PM_FileOps::PM_FILE_WRITE );
                fileOps.Write( myBuffer, fileBufferSize );
                fileOps.Close();
#endif

                // Send the handle on its merry way to the SPM
                bool sendToSPM = true;
                SP_ERSBaseApplication *sP_ERSaPP = myContext.GetCardContext().GetERSAppIf();
                if( sP_ERSaPP )
                {
                    // File shouldn't be sent in case ESRApp isn't null and card is standby
                    if(sP_ERSaPP->IsStandbySlot(myContext.GetCardContext().GetCardId()))
                    {
                        sendToSPM = false;
                    }
                }
                if( sendToSPM )
                {
                    CT_PM_FileTransferBase::Instance()->FileReady( *myFileNameHandle );
                }
                if( gPM_FileTrace )
                {
                    const char* fileName = myFileNameHandle->GetFileNameHandle().c_str();
                    fc_cout << "PM_FilePopulationAction: File image created for " << fileName << endl;
                }
            }

            myState = PM_START_BUILDING;
            myDelay = PM_FILE_INITIALIZATION_DELAY;

            if( myFileHandler != NULL )
            {
                delete myFileHandler;
            }

            if( gPM_FileTrace )
            {
                fc_cout << "PM_FilePopulationAction: myDataType = " << myDataType << " myPeriod = " << myPeriod << " Finished Subapp vector" << endl;
            }
        }
        else
        {
            // Reschedule this state.
            myDelay = PM_FILE_ITERATION_DELAY;
            myContext.GetTimedProcess(myPeriod)->SetDelay( myDelay );
            myContext.GetTimedProcess(myPeriod)->WakeUp();

            if( gPM_FileTrace )
            {
                fc_cout << "PM_FilePopulationAction: myDataType = " << myDataType << " myPeriod = " << myPeriod << " Reschedule action" << endl;
            }
        }

        break;

    default:

        fc_cout << "PM_FilePopulationAction: Default case" << endl;

        myState = PM_START_BUILDING;
        myDelay = PM_FILE_INITIALIZATION_DELAY;

        if( myFileHandler != NULL )
        {
            delete myFileHandler;
        }

        break;
    }

    return NULL;
}

//-----------------------------------------------------------------
void PM_FilePopulationAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_SWError, "Run method is obsoleted!");

}

//-----------------------------------------------------------------
FC_Time PM_FilePopulationAction::GetAccumulationPeriod(CT_PM_Period thePeriod)
{
    FC_Time currentTime;
    time_t  pstOffset;

    // Get the actual time.
    currentTime.GetCurrentTime();

    if( myPeriod == CT_PM_PERIOD_15_MINUTES )
    {
        pstOffset = 0;
    }
    else
    {
//      pstOffset = GetGenericConfigObject().GetPeriodOffset(CT_PM_PERIOD_1_DAY);
        pstOffset = 0;
    }

    return PM_GetAccumulationPeriod(thePeriod, currentTime, pstOffset);
}

//-----------------------------------------------------------------
FC_BbAction* PM_FilePopulationAction::GetBbAction()
{
    return myBbAction;
}


void PM_FilePopulationAction::AddDataToFile()
{
    PM_GenericApplication* pmApp = (*mySubAppVecIt)->GetSubApp();
    PM_RegionImp<PM_BbValue>* previousValueRegion;
    PM_BbValue* value;
    CT_PM_64BitValue aValue;
    CT_PM_64BitValue aMinValue;
    CT_PM_64BitValue aMaxValue;
    CT_PM_IdfStatus idf;
    PM_BinFileParamData paramData;
    CT_TEL_SignalType signalType = CT_TEL_SIGNAL_END;
    CT_FacilitySubType facilityType = FAC_SUBTYPE_UNKNOWN; 
    CT_CardFamily cardFamily;
    CT_PMA_ParamId pmaParamId;
    CT_PM_Side thePMSide = CT_PM_UNKNOWN_SIDE;
    PM_BinFileEntityInfo entityInfo;

    CFG_Region* cfgRegion = NULL;

    PM_ParamVector::iterator paramIterator;
    uint32 numberParams;

    // Create default entity object based on the data type
    switch( myDataType )
    {
        case CT_PM_DATA_PATH:
            {
                cfgRegion = pmApp->GetCfgApplication().GetCfgRegion();
                signalType = GetFacilitySignalType();
                cardFamily = myContext.GetCardContext().GetCardFamily();
                thePMSide = pmApp->GetSide();

                PM_BinFileEntityInfo tempEntityInfo( myContext.GetCardContext().GetShelfId(),
                                                     myContext.GetCardContext().GetCardId(),
                                                     thePMSide,
                                                     signalType,
                                                     cardFamily );

                entityInfo = tempEntityInfo;
            }
            break;

        case CT_PM_DATA_ODU:
        case CT_PM_DATA_TCM:
            {
                cardFamily = myContext.GetCardContext().GetCardFamily();
                cfgRegion = pmApp->GetCfgApplication().GetCfgRegion();
                CT_ODU_Identifier anOduId;

                PM_BinFileEntityInfo tempEntityInfo( myContext.GetCardContext().GetShelfId(),
                                                     myContext.GetCardContext().GetCardId(),
                                                     anOduId );

                entityInfo = tempEntityInfo;
            }
            break;

        case CT_PM_DATA_FAC_EQUIP:
            {
                thePMSide = pmApp->GetSide();

                PM_BinFileEntityInfo tempEntityInfo( myContext.GetCardContext().GetShelfId(),
                                                     myContext.GetCardContext().GetCardId(),
                                                     thePMSide,
                                                     signalType,
                                                     cardFamily );

                entityInfo = tempEntityInfo;
            }
            break;

        default:
            return;
    }

    // Check to see if the previous region is "ready".
    if( !((*mySubAppVecIt)->IsPreviousRegionReady( myPeriod )) )
    {
        // The previous region is not ready.
        return;
    }

    // Get the previous value region for this PM subapplication.
    previousValueRegion = pmApp->GetPreviousRegionValue(myPeriod);

    // Record the fact that this facility is being processed.
    myFacilityCount++;

    //=========================================================================
    // Loop for every entity in the facility
    //=========================================================================
    for( uint32 entity = 0 ; entity < previousValueRegion->Size(); entity++ )
    {
        // Initialize the per entity control data.
        numberParams = 0;

        value = &((*previousValueRegion)[entity]);
        paramIterator = myParamVector.begin();

        // Check to see if the first parameter is valid. If so, assume that
        // PM for this entire entity is valid.
        if( ((idf = value->GetIdf()->GetIdf(0)) == CT_PM_IDF_PARTIAL) || (idf == CT_PM_IDF_COMPLETE) )
        {
            // PM collection is enabled on this entity

            //=================================================================
            // Loop for every parameter in the entity.
            //=================================================================
            for( uint32 param = 0; param < pmApp->GetMaxParams(); param++ )
            {
                pmaParamId = pmApp->ConvertPmIdToPmaId( param );
                if( pmaParamId != PMA_INVALID_PARAMETER )
                {
                    // Populate the validity and ID elements.
                    idf = value->GetIdf()->GetIdf(param);
                    paramData.SetParamValidity( (CT_PMA_Validity)idf );
                    paramData.SetParamId( pmaParamId );

                    // Populate the actual value.
                    if( pmApp->GetLayerType() == CT_PM_LAYER_COUNTER )
                    {
                        //---------------------------------------------
                        // Call PM_BbValue->GetValue(,,false) to inform
                        // method to NOT combine Low and High 64 Bit
                        // values together. We want to keep the individual
                        // param values separate here and keep 32 Bits!
                        //---------------------------------------------
                        value->GetValue( param, aValue, false );
                        paramData.SetParamValue( (uint32)aValue.UnsignedValue );
                        (*paramIterator) = paramData;
                        paramIterator++;
                        numberParams++;
                    }
                    else
                    {
                        value->GetValues( param, aValue, aMinValue, aMaxValue );

                        paramData.SetParamValue( (uint32)aValue.SignedValue );
                        (*paramIterator) = paramData;
                        paramIterator++;
                        numberParams++;

                        paramData.SetParamId( pmApp->ConvertPmIdToPmaId( param, CT_PM_PARAM_MIN ) );
                        paramData.SetParamValue( (uint32)aMinValue.SignedValue );
                        (*paramIterator) = paramData;
                        paramIterator++;
                        numberParams++;

                        paramData.SetParamId( pmApp->ConvertPmIdToPmaId( param, CT_PM_PARAM_MAX ) );
                        paramData.SetParamValue( (uint32)aMaxValue.SignedValue );
                        (*paramIterator) = paramData;
                        paramIterator++;
                        numberParams++;
                    }
                }
            }
        }

        // If we have added any data to the parameter vector, complete the entity.
        if( numberParams > 0 )
        {
            // Complete the population of the entity info object.
            switch( myDataType )
            {
            case CT_PM_DATA_PATH:
                {
                    PM_HopNearEndSubApplication& hopApp = *(dynamic_cast<PM_HopNearEndSubApplication*>(pmApp));
                    uint8 hopOffset = 1;

                    CT_TEL_HopSpeMapping stsHopMapping = ((CFG_Hop&)((*cfgRegion)[(bbindex_t)(entity + hopApp.GetOffset())])).GetSpeMapping();
                    CT_TEL_HopSpeMapping vcHopMapping = stsHopMapping;
                    GetHopMapTrueSdh( stsHopMapping, vcHopMapping, hopOffset);

                    entityInfo.SetChannelId((CT_ChannelId)((entity + hopApp.GetOffset()) / hopOffset) + 1);
                    if( !(entityInfo.SetSpeMapping( vcHopMapping )) )
                    {
                        // No AID type was found for the entity. Stop processing this entity.
                        continue;
                    }
                }
                break;

            case CT_PM_DATA_ODU:
                {
                    CT_PM_AidType aidType = CT_PM_AIDTYPE_UNKNOWN;
                    CT_TL1_Port portId = CT_TL1_PORT_UNKNOWN;
                    vector<CT_ODU_ServerID> aPositionList;
                    CT_ChannelId channelId = UNKNOWN_CHANNEL_ID;
                    CT_IntfId theIntfId = CT_INTF_ID_UNKNOWN;
                    CT_ODU_ServerID theServerID;
                    CFG_Odu& configRef = dynamic_cast<CFG_Odu&>((*cfgRegion)[(bbindex_t)entity]);

                    //=============================================================================
                    // Do NOT continue if the OduObjectType is not configured! Continue for loop().
                    //=============================================================================
                    if ( configRef.GetOduObjectType() == CT_ODU_POOL_NOT_ASSIGNED ||
                         configRef.GetOduObjectType() == CT_ODU_UNKNOWN_TYPE )
                    {
                        continue; /////////////////////////////////////////////////////////////////
                    }

                    aPositionList = configRef.GetOduPositionList();
                    theServerID = aPositionList[0]; // normally only 1 in PositionList as ODU AID feature.
//                    theIntfId = (CT_IntfId)GetUplayerPhysicalPort(myContext.GetCardContext().GetOduIf(), theServerID);
                    theIntfId = (CT_IntfId)GetUplayerPhysicalPort(theServerID);

                    // Populate the AID type based on the ODU "k" value.
                    switch( configRef.GetOduIdentifier().GetOduKvalue() )
                    {
                    case 0:
                        aidType = CT_PM_AIDTYPE_ODU0;
                        facilityType = FAC_SUBTYPE_ODU0;                     
                        break;

                    case 1:
                        aidType = CT_PM_AIDTYPE_ODU1;
                        facilityType = FAC_SUBTYPE_ODU1;
                        break;

                    case 2:
                        aidType = CT_PM_AIDTYPE_ODU2;
                        facilityType = FAC_SUBTYPE_ODU2;
                        if(configRef.GetClockType() == CT_TEL_CLK_OVRCLKFS)
                        {
                            if((CSPII_CardIF::GetInstance()->GetCardType() == HGTMM) ||
                               (CSPII_CardIF::GetInstance()->GetCardType() == HGTMMS) ||
							   (CSPII_CardIF::GetInstance()->GetCardType() == HDTG2))
                            {
                                aidType = CT_PM_AIDTYPE_ODU2;
                                facilityType = FAC_SUBTYPE_ODU2;
                            }
                            else
                            {
                                aidType = CT_PM_AIDTYPE_ODU2E;
                                facilityType = FAC_SUBTYPE_ODU2E;
                            }
                        }
                        break;


                    case 3:
                        aidType = CT_PM_AIDTYPE_ODU3;
                        facilityType = FAC_SUBTYPE_ODU3;
                        break;

                    case 4:
                        aidType = CT_PM_AIDTYPE_ODU4;
                        facilityType = FAC_SUBTYPE_ODU4;
                        break;

                    case CT_ODU_LayerF:
                        aidType = CT_PM_AIDTYPE_ODUF;
                        facilityType = FAC_SUBTYPE_ODUF;
                        break;

                    default:
                        break;
                    }

                    if( cardFamily == SSM40_FAM )
                    {
                        portId = CT_Map_PortId::GetSsm40TL1PortId(facilityType, theIntfId);
                        channelId = configRef.GetChannelIndexInAID();
                    }
                    else if( cardFamily == OMM_FAM )
                    {
                        portId = CT_Map_PortId::GetOmmxTL1PortId(facilityType, theIntfId);
                        channelId = configRef.GetChannelIndexInAID();
                    }
                    else if( cardFamily == OSM_FAM )
                    {
                        portId = CT_Map_PortId::GetOsmTL1PortId(facilityType, theIntfId);
                        channelId = configRef.GetChannelIndexInAID();
                    }

                    else if( cardFamily == FGSM_FAM  )
                    {
                        portId = CT_Map_PortId::GetFgsmTL1PortId(facilityType, theIntfId);
                        channelId = configRef.GetChannelIndexInAID();
                    }
                    else if( cardFamily == HGTMM_FAM  )
                    {
                        //Coriant HGTMMS start
                        if (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMMS)
                        {
                            portId = CT_Map_PortId::GetHgtmmsTL1PortId(facilityType, theIntfId);
                        }
                        else
                        {
                            portId = CT_Map_PortId::GetHgtmmTL1PortId(facilityType, theIntfId);
                        }
                        //Coriant HGTMMS end

                        channelId = configRef.GetChannelIndexInAID();
                    }
					else if(cardFamily == HDTG2_FAM)
					{
                       portId = CT_Map_PortId::GetHdtg2TL1PortId(facilityType, theIntfId);
                       channelId = configRef.GetChannelIndexInAID();
					}
                    else // other CardFamliy, ESM HDTG etc.
                    {
                        // Get the portId but device chan need to be got from another way
                        CT_Map_PortId::GetOduTl1PortChan( cardFamily,
                                                          configRef,
                                                          portId,
                                                          channelId );
                        if (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMS)
                        {
                            channelId = configRef.GetChannelIndexInAID();
                        }
                    }

                    //----------------------------------------------------------------------------
                    // Determine the myPmDir(CT_PM_Dir) for the HDTG/HGTM ODUK entity.
                    //----------------------------------------------------------------------------
                    CT_CardType       aCardType      = CSPII_CardIF::GetInstance()->GetCardType();                            
                    CFG_RsCfgRegion*  aCfgRegion     = static_cast<CFG_RsCfgRegion*>(myContext.GetCardContext().
                                                       GetRsIf().GetCfgPortSideApp(theIntfId).GetCfgRegion());
                    CT_TEL_SignalType aSignalType    = (*aCfgRegion)[0].GetSignalType();

                    CT_PM_Dir aCurrDirection = CT_PM_DIR_NA;
                    if ( aCardType == OSM20 || aCardType == OMMX || aCardType == OSM40 || aCardType == OSM2C || aCardType == OSM2S || aCardType == OSM1S )
                    {
                        CT_DirectionFlag aOduDirection = PM_GetOduDirectionByOduType(aCardType, configRef.GetOduObjectType());
                        aCurrDirection = (aOduDirection == CT_DIR_TRMT ) ? CT_PM_DIR_TRMT : CT_PM_DIR_RCV;
                    }
                    else // HDTG and HGTM
                    {
                        CT_DirectionFlag aOduDirection = PM_GetOduDirectionBySigType(aCardType, aSignalType);
                        aCurrDirection = (aOduDirection == CT_DIR_TRMT) ? CT_PM_DIR_TRMT : CT_PM_DIR_RCV;
                    }

                    CT_PM_IntermediateOduId theOduId;
                    CT_PM_IntermediateOduType theOduType;
                    GetUplayerIntermediateOdu(configRef.GetOduIdentifier().GetOduKvalueEnum(), theServerID, theOduId, theOduType);

                    entityInfo.SetPmDir( aCurrDirection );
                    entityInfo.SetAidType( aidType );
                    entityInfo.SetPortId( portId );
                    entityInfo.SetIntermediateOduId( theOduId );
                    entityInfo.SetIntermediateOduType( theOduType );
                    entityInfo.SetChannelId( channelId );
                }
                break;

            case CT_PM_DATA_TCM:
                {
                    CT_PM_AidType aidType  = CT_PM_AIDTYPE_UNKNOWN;
                    CT_TL1_Port portId     = CT_TL1_PORT_UNKNOWN;
                    CT_ChannelId channelId = DONTCARE_CHANNEL_ID;
                    CT_IntfId theIntfId    = CT_INTF_ID_UNKNOWN;                    
                    CFG_Tcm & configRef       = dynamic_cast<CFG_Tcm&>((*cfgRegion)[(bbindex_t)entity]);
                    CT_ODU_ServerID aServerID = configRef.GetServerID();
                    CT_ODU_Layer aOduLayer    = configRef.GetTcmIdentifier().GetOduKvalueEnum();
                    CT_PM_IntermediateOduId intermediateODUId = CT_PM_INTERMEDIATEODUID_UNKNOWN;
                    
                    //----------------------------------------------------------------------------
                    // 1) Get Tcm direction, if B-dir, it is needed to do some special process
                    //----------------------------------------------------------------------------
                    CT_ODU_Direction aOduDirection = configRef.GetTcmIdentifier().GetOduDirection();
                    CT_PM_Dir aCurrDirection = (aOduDirection == CT_ODU_Direction_A) ? CT_PM_DIR_RCV : CT_PM_DIR_TRMT;

                    // For B-dir Tcm, the client could be OTN or non-OTN signal,
                    // if non-OTN signal, the serverID of this B-dir Tcm is invalid,
                    // using its ODUk serverID to get physical port#
                    if(CT_ODU_Direction_B == aOduDirection)
                    {
                        vector<CT_ODU_ServerID> aPositionList;
                        T6100_TelecomIf& theOduApp = myContext.GetCardContext().GetOduIf();
                        CFG_AppIf& aCfgApp =  theOduApp.GetCfgPortSideApp((CT_IntfId)(aOduLayer == CT_ODU_LayerF ? CT_PORT_SIDE_30 : CT_PORT_SIDE_30 + int(aOduLayer)));
                        CFG_Odu& aCfgOdu = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[configRef.GetOduBbIndex()]);
                        aPositionList = aCfgOdu.GetOduPositionList();
                        aServerID = aPositionList[0]; // normally only 1 in PositionList as ODU AID feature.
                        
                        if( gPM_FileTrace )
                        {
                            fc_cout << "PM_FilePopulationAction: B-dir's CFG_Odu index = " << configRef.GetOduBbIndex() << endl;
                        }
                    }
                    
                    //----------------------------------------------------------------------------
                    // 2) Get AID-type
                    //----------------------------------------------------------------------------
                    switch( aOduLayer )
                    {
                    case CT_ODU_Layer0:
                        aidType = CT_PM_AIDTYPE_ODU0T;
                        facilityType = FAC_SUBTYPE_ODU0T;
                        intermediateODUId = (CT_PM_IntermediateOduId)GetUplayerIntermediateOduId(configRef.GetTcmIdentifier().GetOduKvalueEnum(),
                                                                                                 aServerID);
                        break;

                    case CT_ODU_Layer1:
                        aidType = CT_PM_AIDTYPE_ODU1T;
                        facilityType = FAC_SUBTYPE_ODU1T;                        
                        break;

                    case CT_ODU_Layer2:
                        aidType = CT_PM_AIDTYPE_ODU2T;
                        facilityType = FAC_SUBTYPE_ODU2T;                        
                        break;

                    case CT_ODU_Layer3:
                        aidType = CT_PM_AIDTYPE_ODU3T;
                        facilityType = FAC_SUBTYPE_ODU3T;                        
                        break;

                    case CT_ODU_Layer4:
                        aidType = CT_PM_AIDTYPE_ODU4T;
                        facilityType = FAC_SUBTYPE_ODU4T;                        
                        break;

                    case CT_ODU_LayerF:
                        aidType = CT_PM_AIDTYPE_ODUFT;
                        facilityType = FAC_SUBTYPE_ODUFT;                        
                        break;
                        
                    default:
                        break;
                    }
                    
                    //----------------------------------------------------------------------------
                    // 3) Get get port# according to TCM's serverID
                    //----------------------------------------------------------------------------
                    theIntfId = (CT_IntfId)GetUplayerPhysicalPort(aServerID);
                    if( cardFamily == SSM40_FAM )
                    {
                        portId = CT_Map_PortId::GetSsm40TL1PortId(facilityType, theIntfId);
                        channelId = configRef.GetChannelIndexInAID();
                    }
                    else if( cardFamily == HGTMM_FAM  )
                    {
                        //Coriant HGTMMS start
                        if (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMMS)
                        {
                            portId = CT_Map_PortId::GetHgtmmsTL1PortId(facilityType, theIntfId);                    
                        }
                        else
                        {
                            portId = CT_Map_PortId::GetHgtmmTL1PortId(facilityType, theIntfId);
                        }
                        //Coriant HGTMMS end

                        channelId = configRef.GetChannelIndexInAID();
                    }
	                else if( cardFamily == HDTG2_FAM  )
                    {
                        portId = CT_Map_PortId::GetHdtg2TL1PortId(facilityType, theIntfId);                    
                        channelId = configRef.GetChannelIndexInAID();
                    }
                    else // other CardFamliy, ESM HDTG etc.
                    {
                        // Get the portId but device chan need to be got from another way
                        CT_Map_PortId::GetOduTl1PortChan( cardFamily,
                                                          configRef,
                                                          portId,
                                                          channelId );   
                        if (CSPII_CardIF::GetInstance()->GetCardType() == CARD_TYPE_HGTMS)
                        {
                            channelId = configRef.GetChannelIndexInAID();
                        }
                    }
                    
                    entityInfo.SetAidType( aidType );
                    entityInfo.SetPortId( portId );
                    entityInfo.SetChannelId( channelId );
                    entityInfo.SetIntermediateOduId( intermediateODUId );

                    entityInfo.SetPmDir( aCurrDirection );
                    entityInfo.SetOduDir( configRef.GetTcmIdentifier().GetOduDirectionUint() );
                    entityInfo.SetTcmLevel( configRef.GetTcmIdentifier().GetTcmLevel() );
                }
                break;

            default:
                // This is a bit of a kludge to force the defensive checks on the
                // entity data to pass.
                entityInfo.SetChannelId( 1 );
                break;
            }

            entityInfo.SetNbParams( (uint8)numberParams );
            if( gPM_FileTrace )
            {


                char shelfbuf[80];
                char slotbuf[80];
                char portbuf[80];
                char chanbuf[80];
                char aidtypebuf[80];
                char pmdirbuf[80];
                char odudirbuf[80];
                char tcmlevelbuf[80];
                char intoduidbuf[80];
                char intodutypebuf[80];
                char nbparamsbuf[80];

                sprintf(shelfbuf,    "%u", entityInfo.GetShelfId());
                sprintf(slotbuf,     "%u", entityInfo.GetSlotId());
                sprintf(portbuf,     "%u", entityInfo.GetPortId());
                sprintf(chanbuf,     "%u", entityInfo.GetChannelId());
                sprintf(aidtypebuf,  "%u", entityInfo.GetAidType());
                sprintf(pmdirbuf,    "%u", entityInfo.GetPmDir());
                sprintf(odudirbuf,   "%u", entityInfo.GetOduDir());
                sprintf(tcmlevelbuf, "%u", entityInfo.GetTcmLevel());                
                sprintf(intoduidbuf, "%u", entityInfo.GetIntermediateOduId());
                sprintf(intodutypebuf, "%u", entityInfo.GetIntermediateOduType());
                sprintf(nbparamsbuf, "%u", entityInfo.GetNbParams());

                fc_cout << " Shelf = "       << shelfbuf
                        << " Slot = "        << slotbuf
                        << " Port = "        << portbuf
                        << " Chan = "        << chanbuf
                        << " aidType = "     << aidtypebuf
                        << " pmDir = "       << pmdirbuf
                        << " oduDir = "      << odudirbuf
                        << " tcmLevel = "    << tcmlevelbuf
                        << " interOduId = "  << intoduidbuf
                        << " interOduType = "  << intodutypebuf
                        << " nbParams = "    << nbparamsbuf << endl;
            }
            // Put the entity data into the file buffer.
            if(myFileHandler->PutNext( entityInfo, myParamVector ))
            {
                myEntityCount++;
            }
            else
            {
                if( gPM_FileTrace )
                {
                    fc_cout << " PM_FilePopulationAction: AddDataToFail() failed!" << endl;
                }
            }
        }
    }

    // Mark region as being "consumed".
    (*mySubAppVecIt)->SetPreviousRegionReady( myPeriod, false );
}


uint16 PM_FilePopulationAction::GetUplayerPhysicalPort(CT_ODU_ServerID theServerID)
{
    uint16 port = 0;

    // OSM20 typical case: 
    // 1) OTU2<--ODU2<--ODU1<--ODU0
    //    OTU2--(ODU2T)--ODU2--(ODU1T)--ODU1--(ODU0T)--ODU0
    //
    // 2) OTU1<--ODU1<--ODU0
    //    OTU1--(ODU1T)--ODU1--(ODU0T)--ODU0
    //
    // 3) OTU1<--ODU1
    //    OTU1--(ODU1T)--ODU1
    //
    // 4) ODUk<--client signal
    //    only B-direction TCM is supported in case of non-OTN client signal
    //
    switch(theServerID.GetIdTelecomLayer())
    {
        case CT_ServerPool_Layer_Otu:
            // For non-OTN client signal, 
            // the server-layer of ODUk in which the non-OTN client signal is mapped
            // is CT_ServerPool_Layer_Otu also
            port = theServerID.GetPoolInstance();
            break;
            
        case CT_ServerPool_Layer_Odu:
            {
                T6100_TelecomIf& theOduApp = myContext.GetCardContext().GetOduIf();
                CFG_AppIf& aCfgApp =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(theServerID.GetOduKvalue())));
                CFG_Odu& aCfgOdu = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[theServerID.GetPoolInstance()]);
                
                // the server-layer of this odu could be TCM, or high order ODU
                port = GetUplayerPhysicalPort(aCfgOdu.GetServerID());
            }
            break;
            
        case CT_ServerPool_Layer_Tcm:
            {
                // TCM nest case            
                T6100_TelecomIf& theOdukTApp = myContext.GetCardContext().GetTcmIf();
                CFG_AppIf& aCfgApp =  theOdukTApp.GetCfgPortSideApp((CT_IntfId)CT_PORT_SIDE_40);
                CFG_Tcm& aCfgTcm = dynamic_cast<CFG_Tcm&>((*(aCfgApp.GetCfgRegion()))[theServerID.GetPoolInstance()]);
                port = GetUplayerPhysicalPort(aCfgTcm.GetServerID());
            }
            break;
            
        default:
            break;
    }
    return port;
}


// theOduLayer -- For Tcm, it is the oduk in which the Tcm entity is resided
//                For Odu, it is the 'k' value of this Odu
// theServerID -- For B-dir tcm, it is the positionList of the oduk in which 
//                               the Tcm entity is resided
//                For A-dir tcm, it is serverID of CFG_Tcm
//                For Odu, it is positionList of the Oduk
void PM_FilePopulationAction::GetUplayerIntermediateOdu(CT_ODU_Layer theOduLayer, CT_ODU_ServerID theServerID, CT_PM_IntermediateOduId &theOduId, CT_PM_IntermediateOduType &theOduType)
{   
    uint16 aTemp = CT_PM_INTERMEDIATEODUID_UNKNOWN;
    uint16 aTempType = CT_PM_INTERMEDIATEODUTYPE_UNKNOWN;
    bool hasOdu0 = false, hasOdu1 = false, hasOdu2 = false, hasOdu3 = false, hasOdu4 = false, hasOduf = false;
    theOduId = CT_PM_INTERMEDIATEODUID_UNKNOWN;
    theOduType = CT_PM_INTERMEDIATEODUTYPE_UNKNOWN;
    // OSM20 typical case: 
    // 1) OTU2<--ODU2<--ODU1<--ODU0
    //    OTU2--(ODU2T)--ODU2--(ODU1T)--ODU1--(ODU0T)--ODU0
    //
    // 2) OTU1<--ODU1<--ODU0
    //    OTU1--(ODU1T)--ODU1--(ODU0T)--ODU0
    //
    // 3) OTU1<--ODU1
    //    OTU1--(ODU1T)--ODU1
    //
    // 4) ODUk<--client signal
    //    B-dir Tcm is supported in case of non-OTN client signal
    //

    /*OSM2C typical cases:
    ODU0 -> ODU2 -> ODU4

    ODU0 -> ODU3 -> ODU4

    ODUf -> ODU2 -> ODU4

    ODUf -> ODU3 -> ODU4

    ODU1 -> ODU2 (1.25G tributary slots) -> ODU4

    ODU1 -> ODU3 (1.25G tributary slots) -> ODU4

    ODU2 -> ODU3 (1.25G tributary slots) -> ODU4*/


    switch(theOduLayer)
    {
        case CT_ODU_Layer0:
            hasOdu0 = true;
            break;
        case CT_ODU_Layer1:
            hasOdu1 = true;
            break;
        case CT_ODU_Layer2:
            hasOdu2 = true;
            break;
        case CT_ODU_LayerF:
            hasOduf = true;
            break;
        case CT_ODU_Layer3:
            hasOdu3 = true;
            break;
        case CT_ODU_Layer4:
            hasOdu4 = true;
            break;
        default:
            break;
    }

    CT_ODU_ServerID & aServerID = theServerID;

    bool aDone = false;
    while(!aDone)
    {
        if(aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu)
        {                    
            T6100_TelecomIf& theOduApp = myContext.GetCardContext().GetOduIf();
            CFG_AppIf& aCfgApp =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(aServerID.GetOduKvalue())));
            CFG_Odu& aCfgOdu = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[aServerID.GetPoolInstance()]);
            if(aCfgOdu.GetOduIdentifier().GetOduKvalueEnum() == CT_ODU_Layer1)
            {
                hasOdu1 = true;
                aTemp = aCfgOdu.GetChannelIndexInAID();
                aTempType = CT_PM_INTERMEDIATEODUTYPE_A;
            }
            
            if(aCfgOdu.GetOduIdentifier().GetOduKvalueEnum() == CT_ODU_Layer2)
            {
                hasOdu2 = true;
                /*MR217778
                For card OSM20, ODU2 is the highest layer for 2 stage mux ODU.
                We should not get aTemp and aTempType again here.
                Any card whose highest mux layer is not ODU4 should be added here
                to aviod get the wrong ChannelIndex and IntermediateType.*/
                if(CSPII_CardIF::GetInstance()->GetCardType() != OSM20)
                {
                    aTemp = aCfgOdu.GetChannelIndexInAID();
                    aTempType = CT_PM_INTERMEDIATEODUTYPE_B;
                }
            }

            if(aCfgOdu.GetOduIdentifier().GetOduKvalueEnum() == CT_ODU_Layer3)
            {
                hasOdu3 = true;
                aTemp = aCfgOdu.GetChannelIndexInAID();
                aTempType = CT_PM_INTERMEDIATEODUTYPE_C;
            }

            if(aCfgOdu.GetOduIdentifier().GetOduKvalueEnum() == CT_ODU_Layer4)
            {
                hasOdu4 = true;
            }

            // the server-layer of the odu could be tcm or high-order odu
            aServerID = aCfgOdu.GetServerID();
            aDone = false;
        }

        if(aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)
        {
            T6100_TelecomIf& theOdukTApp = myContext.GetCardContext().GetTcmIf();                    
            CFG_AppIf& aCfgApp =  theOdukTApp.GetCfgPortSideApp((CT_IntfId)CT_PORT_SIDE_40);
            CFG_Tcm& aCfgTcm = dynamic_cast<CFG_Tcm&>((*(aCfgApp.GetCfgRegion()))[aServerID.GetPoolInstance()]);
            aServerID = aCfgTcm.GetServerID();
            aDone = false;
        }
        else if(aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu)
        {
            // high-order odu, for example, Odu0 --> Odu1 --> Odu2 case
            aDone = false;
        }
        else//CT_ServerPool_Layer_Otu or invalid
        {
            aDone = true;
        }
    }

    if((hasOdu0 && hasOdu1 && hasOdu2)||
       (hasOdu0 && hasOdu2 && hasOdu4)||
       (hasOdu0 && hasOdu3 && hasOdu4)||
       (hasOdu1 && hasOdu2 && hasOdu4)||
       (hasOdu1 && hasOdu3 && hasOdu4)||
       (hasOduf && hasOdu2 && hasOdu4)||
       (hasOduf && hasOdu3 && hasOdu4)||
       (hasOdu2 && hasOdu3 && hasOdu4))
    {   
        theOduId = aTemp;     
        theOduType = aTempType;
    }
}
uint16 PM_FilePopulationAction::GetUplayerIntermediateOduId(CT_ODU_Layer theOduLayer, CT_ODU_ServerID theServerID)
{   
    uint16 intermediateODUIdA = 0xff, aTemp = 0xff;
    bool intermediateODUIdValid = false;
    bool hasOdu0 = false, hasOdu1 = false, hasOdu2 = false;
    

    // OSM20 typical case: 
    // 1) OTU2<--ODU2<--ODU1<--ODU0
    //    OTU2--(ODU2T)--ODU2--(ODU1T)--ODU1--(ODU0T)--ODU0
    //
    // 2) OTU1<--ODU1<--ODU0
    //    OTU1--(ODU1T)--ODU1--(ODU0T)--ODU0
    //
    // 3) OTU1<--ODU1
    //    OTU1--(ODU1T)--ODU1
    //
    // 4) ODUk<--client signal
    //    B-dir Tcm is supported in case of non-OTN client signal

    switch(theOduLayer)
    {
        case CT_ODU_Layer0:
            {
                // currently, only support ODU0 --> ODU1 --> ODU2 case
                bool aDone = false;
                hasOdu0 = true;
                CT_ODU_ServerID & aServerID = theServerID;
                while(!aDone)
                {
                    if(aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu)
                    {                    
                        T6100_TelecomIf& theOduApp = myContext.GetCardContext().GetOduIf();
                        CFG_AppIf& aCfgApp =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(aServerID.GetOduKvalue())));
                        CFG_Odu& aCfgOdu = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[aServerID.GetPoolInstance()]);
                        if(aCfgOdu.GetOduIdentifier().GetOduKvalueEnum() == CT_ODU_Layer1)
                        {
                            hasOdu1 = true;
                            aTemp = aCfgOdu.GetChannelIndexInAID();
                        }
                        
                        if(aCfgOdu.GetOduIdentifier().GetOduKvalueEnum() == CT_ODU_Layer2)
                        {
                            hasOdu2 = true;
                        }

                        // the server-layer of the odu could be tcm or high-order odu
                        aServerID = aCfgOdu.GetServerID();
                        aDone = false;
                    }

                    if(aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)
                    {
                        T6100_TelecomIf& theOdukTApp = myContext.GetCardContext().GetTcmIf();                    
                        CFG_AppIf& aCfgApp =  theOdukTApp.GetCfgPortSideApp((CT_IntfId)CT_PORT_SIDE_40);
                        CFG_Tcm& aCfgTcm = dynamic_cast<CFG_Tcm&>((*(aCfgApp.GetCfgRegion()))[aServerID.GetPoolInstance()]);
                        aServerID = aCfgTcm.GetServerID();
                        aDone = false;
                    }
                    else if(aServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu)
                    {
                        // high-order odu, for example, Odu0 --> Odu1 --> Odu2 case
                        aDone = false;
                    }
                    else//CT_ServerPool_Layer_Otu or invalid
                    {
                        aDone = true;
                    }
                }
            }
            break;
            
        default:
            break;
    }

    if(hasOdu0 && hasOdu1 && hasOdu2)
    {        
        intermediateODUIdA = aTemp;
    }
    
    return intermediateODUIdA;
}

#if 0
uint16 PM_FilePopulationAction::GetUplayerPhysicalPort(T6100_TelecomIf& theOduApp, CT_ODU_ServerID theServerID)
{
    uint16 port;
    if (theServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)
    {
        port = theServerID.GetPoolInstance();
    }
    else
    {
        CFG_AppIf& aCfgApp =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(theServerID.GetOduKvalue())));
        CFG_Odu& aCfgOdu = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[theServerID.GetPoolInstance()]);
        port = GetUplayerPhysicalPort(theOduApp, aCfgOdu.GetServerID());
    }
    return port;
}

uint16 PM_FilePopulationAction::GetUplayerIntermediateOduId(T6100_TelecomIf& theOduApp, CT_ODU_ServerID theServerID)
{
    uint16 intermediateODUIdA = 0xff;
    bool intermediateODUIdValid = false;

    // Currently, we only have intermediateODU 'A'. We will handle 'B' and 'C' in the future. 
    // We also will add A/B/C to pm file handler at that time.
    if(theServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Odu) // should be ODU1 layer
    {
        CFG_AppIf& aCfgOdu1App =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(theServerID.GetOduKvalue())));
        CFG_Odu& aCfgOdu1 = dynamic_cast<CFG_Odu&>((*(aCfgOdu1App.GetCfgRegion()))[theServerID.GetPoolInstance()]);
        CT_ODU_ServerID theOdu1ServerID = aCfgOdu1.GetServerID(); 
        if(theOdu1ServerID.GetOduKvalue() == CT_ODU_Layer2)
        {
            CFG_AppIf& aCfgOdu2App =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(theOdu1ServerID.GetOduKvalue())));
            CFG_Odu& aCfgOdu2 = dynamic_cast<CFG_Odu&>((*(aCfgOdu2App.GetCfgRegion()))[theOdu1ServerID.GetPoolInstance()]);
            CT_ODU_ServerID theOdu2ServerID = aCfgOdu2.GetServerID(); 
            if(theOdu2ServerID.GetIdTelecomLayer() == CT_ServerPool_Layer_Otu)
            {
                intermediateODUIdValid = true;
            }
        }
        if( intermediateODUIdValid )
        {
            if(theServerID.GetOduKvalue() == CT_ODU_Layer1)
            {
                intermediateODUIdA = aCfgOdu1.GetChannelIndexInAID();
            }
        }
    }

    return intermediateODUIdA;
}
#endif

//-----------------------------------------------------------------
CT_TEL_SignalType PM_FilePopulationAction::GetFacilitySignalType(bbindex_t channel)
{
    CT_TEL_SignalType theSigType = CT_TEL_SIGNAL_UNKNOWN;
    if( myDataType == CT_PM_DATA_PATH )
    {
        PM_HopNearEndSubApplication* pmApp = dynamic_cast<PM_HopNearEndSubApplication*>((*mySubAppVecIt)->GetSubApp());
        CFG_Rs &configRef = (CFG_Rs &)(*(pmApp->GetParentPmSubApp().GetCfgApplication().GetCfgRegion()))[0];
        theSigType = configRef.GetSignalType();
    }

    return theSigType;
}

//void SetSpeMapping(const CT_TEL_HopSpeMapping& theSpeType);

//-----------------------------------------------------------------
void PM_FilePopulationAction::GetHopMapTrueSdh(CT_TEL_HopSpeMapping &stsHopMapping, CT_TEL_HopSpeMapping &vcHopMapping, uint8 &hopOffset) const
{
    PM_HopNearEndSubApplication* pmApp = dynamic_cast<PM_HopNearEndSubApplication*>((*mySubAppVecIt)->GetSubApp());
    CFG_Rs &configRef = (CFG_Rs &)(*(pmApp->GetParentPmSubApp().GetCfgApplication().GetCfgRegion()))[0];

    hopOffset = 1;
    vcHopMapping = stsHopMapping;

    if( configRef.GetSDHTrueMode() )
    {
        switch(stsHopMapping)
        {
            case CT_TEL_HOP_MAPPING_STS1:
                vcHopMapping = CT_TEL_HOP_MAPPING_VC3;
                break;

            case CT_TEL_HOP_MAPPING_STS3C:
                vcHopMapping = CT_TEL_HOP_MAPPING_VC4;
                hopOffset = 3;
                break;

            case CT_TEL_HOP_MAPPING_STS12C:
                vcHopMapping = CT_TEL_HOP_MAPPING_VC4_4;
                hopOffset = 3;
                break;

            case CT_TEL_HOP_MAPPING_STS48C:
                vcHopMapping = CT_TEL_HOP_MAPPING_VC4_16;
                hopOffset = 3;
                break;

            case CT_TEL_HOP_MAPPING_STS192C:
                vcHopMapping = CT_TEL_HOP_MAPPING_VC4_64;
                hopOffset = 3;
                break;
        }
    }
}


//-----------------------------------------------------------------
PM_PreviousRegionAction::PM_PreviousRegionAction(PM_FileStorageSubApplication& theContext, CT_PM_Period thePeriod, CT_PM_DataType theDataType) :

    myContext(theContext),
    myPeriod(thePeriod),
    myDataType(theDataType)
{
    myBbAction = new FC_BbAction(this);
}

//-----------------------------------------------------------------
PM_PreviousRegionAction::~PM_PreviousRegionAction()
{
    delete myBbAction;
}

//-----------------------------------------------------------------
FC_Object*  PM_PreviousRegionAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    bool allRegionsReady = true;
    PM_GenericApplication* pmApp;
    uint32 readyBitMap = 0;
    uint32 index = 0;

    vector<PM_SubApplicationRegistration*>::iterator subAppIterator;

    for (subAppIterator = myContext.GetSubApplicationVector().begin(); subAppIterator != myContext.GetSubApplicationVector().end(); subAppIterator++, index++)
    {
        pmApp = (*subAppIterator)->GetSubApp();

        // Look for eligible previous value regions that are not ready.
        if( !((*subAppIterator)->IsPreviousRegionReady( myPeriod )) )
        {
            if( pmApp->IsProcessorActionRunning() )
            {
                // Found a PM subapp that we need to wait on yet.
                allRegionsReady = false;
                break;
            }
        }
        else
        {
            // This is a little messy in that we are reaffirming the start time value a number of
            // times after it is set initially.
            myContext.SetControlPeriodTimeStamp( myPeriod, pmApp->GetControlPeriodTimeStamp( myPeriod ) );

            readyBitMap |= 1 << index;
        }
    }

    if( gPM_FileTrace )
    {
        fc_cout << "PM_PreviousRegionAction: myDataType = " << myDataType << " myPeriod = " << myPeriod << " readyBitMap = " << readyBitMap << endl;
    }

    if( allRegionsReady )
    {
        // Trigger the file population action.
        myContext.GetTimedProcess(myPeriod)->WakeUp();

        if( gPM_FileTrace )
        {
            fc_cout << "PM_PreviousRegionAction: myDataType = " << myDataType << " myPeriod = " << myPeriod << " Triggering  File Pop. Action" << endl;
        }
    }

    return NULL;
}

//-----------------------------------------------------------------
void PM_PreviousRegionAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_SWError, "Run method is obsoleted!");

}

//-----------------------------------------------------------------
FC_BbAction* PM_PreviousRegionAction::GetBbAction()
{
    return myBbAction;
}




