// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ArrDefectCollectorAction.h"
#include "../SP_Utilities.h"
#include "../SP_ArrRegion.h"
#include "../SP_BitSetDataObject.h"
#include <Blackboard/FC_BbAction.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_OtuDefects.h>
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_OtuConfig.h>
#include <Monitoring/MON_RsConfig.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Odu.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_AppIf.h>
#include <T6100_CardIf.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <CsPii/CSPII_CardIF.h>
#include <AM/AM_DefectProcessor.h>
#include <AM/AM_AppIf.h>
#include <AM/AM_BbDefectRegion.h>
#include <AM/AM_BbAlarmRegion.h>
#include <AM/AM_DefectCollector.h>

const FC_Milliseconds ARR_DEFECT_CLEAR_HOLDOFF_TIMER  = 15 * 1000; //15 secs
const FC_Milliseconds ARR_DEFECT_PHY_HOLDOFF_TIMER  = 5 * 60* 1000; //5 minutes

int gSpArrDebugTrace = 0;

#define SP_ARR_NODEFECT_MASK 0
#define SP_ARR_DEFECT_NO_PHY_MASK 0x1F


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////SP_ArrDefectCollectorAction/////////////////////////////////////////////////////////////////////////////////////
//##ModelId=3BBC9B0F02A0
SP_ArrDefectCollectorAction::SP_ArrDefectCollectorAction(	
    SP_ReRouteConfigRegion& theConfigRegion,
	SP_ReRouteDefectRegion& theDefectRegion,
	T6100_CardIf& theCardContext):
    myConfigRegion(theConfigRegion),
	myDefectsRegion(theDefectRegion),
	myCardContext(theCardContext),
	stopped(false),
    myPendingUpdate(false)
{
    myBbAction = new FC_BbAction(this);
	myBbAction->AddOutputRegion(&myDefectsRegion);

	CT_ShelfId theShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
	CT_SlotId theSlotId   = CSPII_CardIF::GetInstance()->GetSlotId();

    T6100_ShelfIf* theShelf = T6100_MainAppIf::Instance().GetShelfPtr(theShelfId);
	myCsmRegion = &(theShelf->GetSlotPtr(theSlotId)->GetCsmApp().GetCardConfigStatusRegion());

	//////////////////////////////////////////
	////////Populate defect list//////////////
	//////////////////////////////////////////
	//OPT layer
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_OPT, CT_TEL_OPT_LOSS_LIGHT_DEFECT));
	//OTU layer
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_OTU, CT_TEL_OTU_LOF_DEFECT));
    myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_OTU, CT_TEL_OTU_LOMF_DEFECT));
    myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_OTU, CT_TEL_OTU_AIS_DEFECT));
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_OTU, CT_TEL_OTU_BDI_DEFECT));
    myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_OTU, CT_TEL_OTU_TIM_DEFECT));
	//ODU layer
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_ODU, CT_TEL_ODU_AIS_DEFECT));
	//RS layer
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_RS, CT_TEL_RS_LOF_DEFECT));
    myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_RS, CT_TEL_RS_TIM_DEFECT));
	//MS layer
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_MS, CT_TEL_MS_SFBER_DEFECT));
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_MS, CT_TEL_MS_RDI_DEFECT));
	myDefectList.insert(SP_ArrDefectList::value_type(Defect_Layer_MS, CT_TEL_MS_AIS_DEFECT));

    myOdukIdentifierList = new vector<uint32>();
	
}

//##ModelId=38EDF51800A6
SP_ArrDefectCollectorAction::~SP_ArrDefectCollectorAction()
{
    delete myBbAction;
#ifndef PSOSP
    myOdukIdentifierList->clear();
#endif
    delete myOdukIdentifierList;
    myOdukIdentifierList = NULL;
}

//##ModelId=3B8BC9D30390
void SP_ArrDefectCollectorAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_ArrDefectCollectorAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;
	bool hasChangedPort = false;
    bool hasChangedOdu = false;

    hasChangedPort = ProcessPortDefects();
    hasChangedOdu = ProcessOduDefects();
	
	if (hasChangedPort || hasChangedOdu)
		myDefectsRegion.IncModificationCounter();
	
    return NULL;
}

void SP_ArrDefectCollectorAction::AddToPortDefectCollector(CT_IntfId thePortId)
{
	MON_Region* theOtuDefectRegion = NULL;
	MON_Region* theOduDefectRegion = NULL;
	MON_Region* theOptDefectRegion = NULL;
    MON_Region* theRsDefectRegion = NULL;
	MON_Region* theMsDefectRegion = NULL;

    MON_Region* theRsConfigRegion = NULL;
	MON_Region* theOtuConfigRegion = NULL;
    
	//Retrieve region pointers and store
	if (thePortId == CT_LINE_SIDE_0)
	{
		theOduDefectRegion = myCardContext.GetOduIf().GetMonLineSideApp(CT_LINE_SIDE_1).GetDefectsRegion();
		theRsDefectRegion = myCardContext.GetRsIf().GetMonLineSideApp(thePortId).GetDefectsRegion();
	    theMsDefectRegion = myCardContext.GetMsIf().GetMonLineSideApp(thePortId).GetDefectsRegion();

        theRsConfigRegion = myCardContext.GetRsIf().GetMonLineSideApp(thePortId).GetConfigRegion();
	}
	else if (thePortId == CT_LINE_SIDE_1)
	{
	    theOtuDefectRegion = myCardContext.GetOtuIf().GetMonLineSideApp(thePortId).GetDefectsRegion();
		theOptDefectRegion = myCardContext.GetOptIf().GetMonLineSideApp(thePortId).GetDefectsRegion();

        theOtuConfigRegion = myCardContext.GetOtuIf().GetMonLineSideApp(thePortId).GetConfigRegion();
	}
	else
	{
		//Some layers may not exist, so add conditionally
		if (myCardContext.GetOduIf().GetMonPortSideAppPtr(thePortId))
		{
		    theOduDefectRegion = myCardContext.GetOduIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
		}

		if (myCardContext.GetOtuIf().GetMonPortSideAppPtr(thePortId))
		{
	        theOtuDefectRegion = myCardContext.GetOtuIf().GetMonPortSideApp(thePortId).GetDefectsRegion();

            theOtuConfigRegion = myCardContext.GetOtuIf().GetMonPortSideApp(thePortId).GetConfigRegion();
		}

		if (myCardContext.GetOptIf().GetMonPortSideAppPtr(thePortId))
		{
			theOptDefectRegion = myCardContext.GetOptIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
		}
		
		if (myCardContext.GetRsIf().GetMonPortSideAppPtr(thePortId))
		{
		    theRsDefectRegion = myCardContext.GetRsIf().GetMonPortSideApp(thePortId).GetDefectsRegion();

            theRsConfigRegion = myCardContext.GetRsIf().GetMonPortSideApp(thePortId).GetConfigRegion();
		}

		if (myCardContext.GetMsIf().GetMonPortSideAppPtr(thePortId))
		{
	        theMsDefectRegion = myCardContext.GetMsIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
		}
	}


	//Add to data collection set
	myPortDataCollectionSet.push_back(new SP_ArrPortDefectCollectorData(thePortId, 0, theOptDefectRegion, theOtuDefectRegion, theOduDefectRegion, theRsDefectRegion, theMsDefectRegion, theRsConfigRegion, theOtuConfigRegion, *myBbAction));
	
}

void SP_ArrDefectCollectorAction::UpdateOduDefectCollector(CT_IntfId thePortId, bool theAdd)
{
    CFG_Region* theCfgOdukRegion = myCardContext.GetOduIf().GetCfgPortSideApp(thePortId).GetCfgRegion();
    if (theCfgOdukRegion)
    {
        if (theAdd)
        {
            myBbAction->AddInputRegion(theCfgOdukRegion);
        }
        else
        {
            myBbAction->RemoveInputRegion(theCfgOdukRegion);
        }
    }
}

void RemoveFromOduDefectCollector(CT_IntfId thePortId);

void SP_ArrDefectCollectorAction::ConfigureBbActionInputs(bool addRegions)
{
    if (addRegions)
	{
	   myBbAction->AddInputRegion(&myConfigRegion); 
	   myBbAction->AddInputRegion(myCsmRegion);
	}
	else
	{
		myBbAction->RemoveInputRegion(&myConfigRegion);
		myBbAction->RemoveInputRegion(myCsmRegion);
	}
}

void SP_ArrDefectCollectorAction::MonitorDefects()
{
	//For each port registered with defect collect action:
	//Check config
    //if config is set
    //If region not previously added
    //Then walk through the defect layers, get the region and add the regions as input, and mark as added
    //If region was previously added, do nothing (refresh)
  
    //If config not set
    //If region was previously added
    //Then walk through the defect layers, get the region and remove input regions, mark as removed

	SP_ArrPortDefectCollectorDataCollection::iterator thePortDefectCollectorIterator;
	for (thePortDefectCollectorIterator = myPortDataCollectionSet.begin();
	     thePortDefectCollectorIterator != myPortDataCollectionSet.end();
		 ++thePortDefectCollectorIterator )
	{
	    //Do processing here
		SP_ArrPortDefectCollectorData* thePortDataCollectorData = (*thePortDefectCollectorIterator);
		bool isConfigured = myConfigRegion.IsConfigSet(thePortDataCollectorData->GetPortId());
		bool isMonitored  = thePortDataCollectorData->IsCurrentlyMonitoringDefects();

		if ( isConfigured == true && isMonitored == false )
		{
            MonitorDefectsOnPort(thePortDataCollectorData, true);
		}
		else if (isConfigured == false && isMonitored == true )
		{
			MonitorDefectsOnPort(thePortDataCollectorData, false);
		}
	}

    MonitorDefectsOnOdu();

}

void SP_ArrDefectCollectorAction::MonitorDefectsOnPort(SP_ArrPortDefectCollectorData* thePortData, bool theMonitor)
{
	int theDefectLayer;
	MON_Region* aMonRegion;
	for (theDefectLayer=(int)Defect_Layer_OPT; theDefectLayer<(int)Defect_Layer_NONE; theDefectLayer++)
	{
		aMonRegion = thePortData->GetDefectRegion((SP_ArrDefectLayer)theDefectLayer);
		if (aMonRegion)
		{
			if (theMonitor)
			{
                myBbAction->AddInputRegion(aMonRegion); 
			}
			else
			{
				myBbAction->RemoveInputRegion(aMonRegion); 
			}
		}
	}

	//Save the current monitoring state
	thePortData->SetDefectMonitoring(theMonitor);
}

void SP_ArrDefectCollectorAction::MonitorDefectsOnOdu()
{
    myOdukIdentifierList->clear();
    myConfigRegion.GetOduConfigList(myOdukIdentifierList);


    //Clear invalid entries
    SP_ArrOduDefectCollectorDataCollection::iterator iter = myOduDataCollectionSet.begin();

    while(iter != myOduDataCollectionSet.end())
    {
        CT_ODU_Identifier theOduId ( (*iter).first);
        SP_ArrOduDefectCollectorData* theOduData = (*iter).second;
        bool configSet = myConfigRegion.IsConfigSet(theOduId);

        if (!configSet)
        {
            ManageOduInputRegions((*iter).first, false, true);
            myDefectsRegion.ClearDefects(theOduId);
            myOduDataCollectionSet.erase(iter++);
            delete theOduData; //free the object
            myPendingUpdate = true;
        }
        else
        {
            ++iter;
        }
    }
    
    //Loop through the config list to find configured odu and add to list if new entry
    vector<uint32>::iterator theConfigIterator;
	for (theConfigIterator = myOdukIdentifierList->begin();
	     theConfigIterator != myOdukIdentifierList->end();
		 ++theConfigIterator )
	{
        uint32 oduId = (*theConfigIterator);
        SP_ArrOduDefectCollectorDataCollection::iterator aIter = myOduDataCollectionSet.find(oduId);
        if(aIter == myOduDataCollectionSet.end())
        {
            MON_Region* theMonRegion = NULL;
            int theObjIndex = -1;
            bool found = false;
            theMonRegion = FindOduk(oduId, &theObjIndex);
            if (theMonRegion)
            {
                ManageOduInputRegions(oduId, true, false);
                SP_ArrOduDefectCollectorData* newOduData = new SP_ArrOduDefectCollectorData(CT_ODU_Identifier(oduId), theObjIndex, theMonRegion, *myBbAction);
                myOduDataCollectionSet[oduId] = newOduData;

            }
        }
    }

}

bool SP_ArrDefectCollectorAction::ProcessPortDefects()
{
    MON_Region* aMonDefectRegion = NULL;
	MON_Defects* aMonitoringDefectObject = NULL;
    MON_Region* aMonConfigRegion = NULL;
    MON_OtuConfig* aMonOtuConfigObject = NULL;
    MON_RsConfig* aMonRsConfigObject = NULL;
	bool hasChanged = false;
	uint32 aCount=0;
    bool aState=false;
	int aIdx = 0;
	bool updateRegion = false;
	int theTelLayer;
    uint8 theAggState = SP_ARR_NODEFECT_MASK;
    bool thePhyDefect = false;
    bool thePhyDefectChanged = false;

	CSM_PersistentConfigStatus* aPersConfigPtr = &((*myCsmRegion)[0]);
	CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();

	SP_ArrPortDefectCollectorDataCollection::iterator thePortDefectCollectorIterator;
	for (thePortDefectCollectorIterator = myPortDataCollectionSet.begin();
	     thePortDefectCollectorIterator != myPortDataCollectionSet.end();
		 ++thePortDefectCollectorIterator )
	{
		theAggState = SP_ARR_NODEFECT_MASK;
        thePhyDefect = false;
        thePhyDefectChanged = false;
		updateRegion = true;

	    //Do processing here
		SP_ArrPortDefectCollectorData* theDataCollectorData = (*thePortDefectCollectorIterator);
		SP_ArrTimerState theTimerState = theDataCollectorData->GetClearSoakTimerState();
        SP_ArrTimerState thePhyTimerState = theDataCollectorData->GetPhySoakTimerState();
        uint8 prevDefectList = myDefectsRegion.GetDefectList(theDataCollectorData->GetPortId());

		if (myConfigRegion.IsConfigSet(theDataCollectorData->GetPortId()))
		{
            theAggState = SP_ARR_NODEFECT_MASK;

			for (theTelLayer=(int)Defect_Layer_OPT; theTelLayer<(int)Defect_Layer_NONE; theTelLayer++)
			{
				SP_ArrDefectList::iterator it;
                pair<SP_ArrDefectList::iterator,SP_ArrDefectList::iterator> ret;

				aMonDefectRegion = theDataCollectorData->GetDefectRegion((SP_ArrDefectLayer)theTelLayer);
				aIdx =  theDataCollectorData->GetDefectObjIndex((SP_ArrDefectLayer)theTelLayer);
                
                CT_SP_DefectLayer arrLayer = GetRerouteLayerMask((SP_ArrDefectLayer)theTelLayer);

				if (aMonDefectRegion != NULL)
				{
					//Current defect layer is monitored for this port
					SP_ArrDefectList::iterator it;
                    pair<SP_ArrDefectList::iterator,SP_ArrDefectList::iterator> ret;
				    ret = myDefectList.equal_range((SP_ArrDefectLayer)theTelLayer);
					//Look for all the defects at this layer
				    for (it=ret.first; it!=ret.second; ++it)
					{
						aMonitoringDefectObject = static_cast<MON_Defects*>(&((*aMonDefectRegion)[aIdx]));
						aMonitoringDefectObject->GetDefectStatus((*it).second, &aCount, &aState);
						if (aState)
						{
                            //For TIM defects, only consider it defect if layer fail is enabled
                            if (theTelLayer == Defect_Layer_RS && (*it).second == CT_TEL_RS_TIM_DEFECT)
                            {
                                aMonConfigRegion = theDataCollectorData->GetConfigRegion((SP_ArrDefectLayer)theTelLayer);
                                if (aMonConfigRegion)
                                {
                                    aMonRsConfigObject = static_cast<MON_RsConfig*>(&((*aMonConfigRegion)[aIdx]));
                                    if (aMonRsConfigObject->GetLayerFailOnTIM())
                                    {
                                        theAggState |= arrLayer;
                                    }
                                }
                            }
                            else if (theTelLayer == Defect_Layer_OTU && (*it).second == CT_TEL_OTU_TIM_DEFECT)
                            {
                                aMonConfigRegion = theDataCollectorData->GetConfigRegion((SP_ArrDefectLayer)theTelLayer);
                                if (aMonConfigRegion)
                                {
                                    aMonOtuConfigObject = static_cast<MON_OtuConfig*>(&((*aMonConfigRegion)[aIdx]));
                                    if (aMonOtuConfigObject->GetLayerFailOnTIM())
                                    {
                                        theAggState |= arrLayer;
                                    }
                                }
                            }
                            else
                            {
							    theAggState |= arrLayer;
                            }

                            
                            if ( (theTelLayer == Defect_Layer_OPT && (*it).second == CT_TEL_OPT_LOSS_LIGHT_DEFECT) ||
                                 (theTelLayer == Defect_Layer_OTU && (*it).second == CT_TEL_OTU_BDI_DEFECT) )
                            {
                                if (myConfigRegion.IsPhyLayerMonitorEnabled(theDataCollectorData->GetPortId()))
                                {
                                    thePhyDefect = true;
                                }
                            }
						}
					}
				}
			}


			//If the module is locked, then force clear all the defects
			if (theCardAdminState == CARD_LOCK)
	        {
                theAggState = SP_ARR_NODEFECT_MASK;
                thePhyDefect = false;
			}

			if (theAggState != SP_ARR_NODEFECT_MASK)
			{
				//If the timer was previously running, stop it since the defect is present again
                if (theTimerState == TIMER_STARTED_RUNNING ||
					theTimerState == TIMER_STARTED_EXPIRED)
				{
					theDataCollectorData->StopClearSoakTimer();
					//Notify immediately
				}

				//DEBUG
				if (gSpArrDebugTrace != 0)
				{
                    fc_cout << "Defect set on port " << DISPLAY_CT_IntfId(theDataCollectorData->GetPortId()) << " : Mask is " << (uint32)theAggState << endl;
				}
				//END DEBUG
			}
			else
			{
				//Timer wasnt previously started, start timer if there is a toggle in the defect state from set to clear
				if (theTimerState == TIMER_NOT_STARTED)
				{
					if (myDefectsRegion.IsDefectSet(theDataCollectorData->GetPortId()))
					{
						theDataCollectorData->StartClearSoakTimer();
						//No change
						updateRegion = false;
					}
				}
				else if (theTimerState == TIMER_STARTED_RUNNING)
				{
					//Clear timer running
					//No change
					updateRegion = false;
				}
				else if (theTimerState == TIMER_STARTED_EXPIRED)
				{
					//Stop the timer
					theDataCollectorData->StopClearSoakTimer();
					//Notify immediately

					//DEBUG
					if (gSpArrDebugTrace != 0)
					{
						fc_cout << "Clear timer expired, sending notification for port " << DISPLAY_CT_IntfId(theDataCollectorData->GetPortId()) << endl;
					}
					//END DEBUG
				}
			}

            if (updateRegion == false)
            {
                theAggState = (prevDefectList & SP_ARR_DEFECT_NO_PHY_MASK);
                //DEBUG
		        if (gSpArrDebugTrace != 0)
		        {
			        fc_cout << "Previous non phy defect state on port is " << (uint32)theAggState << endl;
		        }
		        //END DEBUG
            }

            //PHY layer processing. Add the physical layer defect indication to the aggregate defect state as needed
            thePhyDefectChanged = theDataCollectorData->SetPhyDefectActive(thePhyDefect);

            //Process physical layer defect.
            if (thePhyDefect)
            {
                if (thePhyDefectChanged)
                {
                    //Timer wasnt previously started, start timer if there is a toggle in the defect state from clear to set
				    if (thePhyTimerState == TIMER_NOT_STARTED)
				    {
					    theDataCollectorData->StartPhySoakTimer();
                        //Save off internal system defect state
                        bool internalSystemDefect = InternalSystemDefectPresent(theDataCollectorData);
                        theDataCollectorData->SetInternalSystemDefect(internalSystemDefect);

                        //No change (use current aggregate defect state)
				    }
                }
                else
                {
                    bool intSysDefectChg = false;
                    bool internalSystemDefect = InternalSystemDefectPresent(theDataCollectorData);
                    
                    intSysDefectChg = theDataCollectorData->SetInternalSystemDefect(internalSystemDefect);

                    if (intSysDefectChg)
                    {
                        if (gSpArrDebugTrace != 0)
			            {
                            fc_cout << "Internal system defect toggle detected for " << DISPLAY_CT_IntfId(theDataCollectorData->GetPortId()) << ": " << DISPLAY_BOOL(internalSystemDefect) << endl;
			            }
                        theDataCollectorData->StopPhySoakTimer();
                        theDataCollectorData->StartPhySoakTimer();

                        //Keep what we currently have
                        theAggState |= (prevDefectList & CT_SP_LAYER_PHY);
				        
                    }
                    else
                    {

				        if (thePhyTimerState == TIMER_STARTED_EXPIRED)
				        {
					        //Stop the timer
					        theDataCollectorData->StopPhySoakTimer();
					        //Notify immediately if a valid alarm. A valid phy layer alarm is one that is caused by an internal system issue (missing module/cable etc).
                            if (internalSystemDefect)
                            {

					            //DEBUG
					            if (gSpArrDebugTrace != 0)
					            {
						            fc_cout << "Phy timer expired, sending notification for port " << DISPLAY_CT_IntfId(theDataCollectorData->GetPortId()) << endl;
					            }
					            //END DEBUG

                                //mark the physical layer as failed
                                theAggState |= CT_SP_LAYER_PHY;
                            }
                            else
                            {
                                //Immediate clear since it is an external system defect
                                 //DEBUG
					            if (gSpArrDebugTrace != 0)
					            {
						            fc_cout << "Phy timer expired, suppressing notification due to external defect for port " << DISPLAY_CT_IntfId(theDataCollectorData->GetPortId()) << endl;
					            }
					            //END DEBUG
                    
                            }
				        }
                        else if (thePhyTimerState == TIMER_STARTED_RUNNING)
				        {
                            //Keep what we currently have
                            theAggState |= (prevDefectList & CT_SP_LAYER_PHY);
                        }
                        else
                        {
                            if (internalSystemDefect)
                            {
                                //mark the physical layer as failed
                                theAggState |= CT_SP_LAYER_PHY;
                            }
                            else
                            {
                                if (gSpArrDebugTrace != 0)
					            {
						            fc_cout << "External defect detected, clearing existing phy layer defect for port " << DISPLAY_CT_IntfId(theDataCollectorData->GetPortId()) << endl;
					            }
                            }
                        }
                    }
                }
            }
            else
            {
                //Immediate clear
                theDataCollectorData->SetInternalSystemDefect(false);
                //Stop the timer
			    theDataCollectorData->StopPhySoakTimer();
            }

	        if (theAggState == SP_ARR_NODEFECT_MASK)
            {
                hasChanged |= myDefectsRegion.ClearDefects(theDataCollectorData->GetPortId());
            }
            else
            {
                //Setup new defect list
		        hasChanged |= myDefectsRegion.SetDefects(theDataCollectorData->GetPortId(), theAggState);
            }
			
		}
		else //Configuration not set
		{
			//If any timers were previously running, stop it since the port is deprovisioned
            theDataCollectorData->StopClearSoakTimer();
            theDataCollectorData->StopPhySoakTimer();
			//Not provisioned. Clear the state
			hasChanged |= myDefectsRegion.ClearDefects(theDataCollectorData->GetPortId());
		}
	}

    return hasChanged;
}

bool SP_ArrDefectCollectorAction::ProcessOduDefects()
{
    
    MON_Region* aMonDefectRegion = NULL;
	MON_Defects* aMonitoringDefectObject = NULL;
	bool hasChanged = false;
	uint32 aCount=0;
    bool aState=false;
	int aIdx = 0;
	bool updateRegion = false;
    bool theAggState = false;

	CSM_PersistentConfigStatus* aPersConfigPtr = &((*myCsmRegion)[0]);
	CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();

	SP_ArrOduDefectCollectorDataCollection::iterator theOduDefectCollectorIterator;
	for (theOduDefectCollectorIterator = myOduDataCollectionSet.begin();
	     theOduDefectCollectorIterator != myOduDataCollectionSet.end();
		 ++theOduDefectCollectorIterator )
	{
		theAggState = false;
		updateRegion = true;

	    //Do processing here
		SP_ArrOduDefectCollectorData* theDataCollectorData = (*theOduDefectCollectorIterator).second;
		SP_ArrTimerState theTimerState = theDataCollectorData->GetClearSoakTimerState();
        bool prevDefectState = myDefectsRegion.IsDefectSet(theDataCollectorData->GetOduId());

		if (myConfigRegion.IsConfigSet(theDataCollectorData->GetOduId()))
		{
            theAggState = false;

            aMonDefectRegion = theDataCollectorData->GetDefectRegion();
            aIdx =  theDataCollectorData->GetDefectObjIndex();
            if (aMonDefectRegion != NULL)
			{
                aMonitoringDefectObject = static_cast<MON_Defects*>(&((*aMonDefectRegion)[aIdx]));
				aMonitoringDefectObject->GetDefectStatus(CT_TEL_ODU_BDI_DEFECT, &aCount, &aState);
                if (aState || aMonitoringDefectObject->IsLayerInDefects() || aMonitoringDefectObject->IsLayerLocked())
                {
                    theAggState = true;
                }
            }

			//If the module is locked, then force clear all the defects
			if (theCardAdminState == CARD_LOCK)
	        {
                theAggState = false;
			}

			if (theAggState != false)
			{
				//If the timer was previously running, stop it since the defect is present again
                if (theTimerState == TIMER_STARTED_RUNNING ||
					theTimerState == TIMER_STARTED_EXPIRED)
				{
					theDataCollectorData->StopClearSoakTimer();
					//Notify immediately
				}

				//DEBUG
				if (gSpArrDebugTrace != 0)
				{
                    fc_cout << "Defect set on odu " << (uint32)theDataCollectorData->GetOduId().GetIdValue() << " : Mask is " << DISPLAY_BOOL(theAggState) << endl;
				}
				//END DEBUG
			}
			else
			{
				//Timer wasnt previously started, start timer if there is a toggle in the defect state from set to clear
				if (theTimerState == TIMER_NOT_STARTED)
				{
					if (myDefectsRegion.IsDefectSet(theDataCollectorData->GetOduId()))
					{
						theDataCollectorData->StartClearSoakTimer();
						//No change
						updateRegion = false;
					}
				}
				else if (theTimerState == TIMER_STARTED_RUNNING)
				{
					//Clear timer running
					//No change
					updateRegion = false;
				}
				else if (theTimerState == TIMER_STARTED_EXPIRED)
				{
					//Stop the timer
					theDataCollectorData->StopClearSoakTimer();
					//Notify immediately

					//DEBUG
					if (gSpArrDebugTrace != 0)
					{
						fc_cout << "Clear timer expired, sending notification for odu " << (uint32)theDataCollectorData->GetOduId().GetIdValue() << endl;
					}
					//END DEBUG
				}
			}

            if (updateRegion == false)
            {
                theAggState = prevDefectState;
                //DEBUG
		        if (gSpArrDebugTrace != 0)
		        {
			        fc_cout << "Previous defect state on odu is " << DISPLAY_BOOL(theAggState) << endl;
		        }
		        //END DEBUG
            }

            

	        if (theAggState == false)
            {
                hasChanged |= myDefectsRegion.ClearDefects(theDataCollectorData->GetOduId());
            }
            else
            {
                //Setup new defect list
		        hasChanged |= myDefectsRegion.SetDefects(theDataCollectorData->GetOduId());
            }
			
		}
		else //Configuration not set
		{
			//If any timers were previously running, stop it since the port is deprovisioned
            theDataCollectorData->StopClearSoakTimer();
			//Not provisioned. Clear the state
			hasChanged |= myDefectsRegion.ClearDefects(theDataCollectorData->GetOduId());
		}
	}

    //Go through and nuke any that are not configured.
    if (myPendingUpdate)
    {
        hasChanged = true;
        myPendingUpdate = false;
    }
    
    return hasChanged;
}

MON_Region* SP_ArrDefectCollectorAction::FindOduk(uint32 theOduIdentifier, int* theLayerIdx)
{
	//Client defaults
    CT_IntfId theLayerPort = CT_INTF_ID_UNKNOWN;
    (*theLayerIdx) = -1;
    MON_Region* theMonRegion = NULL;
	
	
	theLayerPort = GetOduKPort(theOduIdentifier);
    
	CFG_Region* theCfgOdukRegion = myCardContext.GetOduIf().GetCfgPortSideApp(theLayerPort).GetCfgRegion();
    for (int i=0; i<(int)theCfgOdukRegion->Size(); i++)
    {
        CFG_Odu* aCfgOdukObject = static_cast<CFG_Odu*>(&((*theCfgOdukRegion)[i]));
		if (aCfgOdukObject->GetOduIdentifier().GetIdValue() == theOduIdentifier)
        {
			(*theLayerIdx) = i;
            break;
        }
    }

    if ( (*theLayerIdx) != -1)
    {
        theMonRegion = myCardContext.GetOduIf().GetMonPortSideApp(theLayerPort).GetDefectsRegion();
    }

    return theMonRegion;
}

CT_IntfId SP_ArrDefectCollectorAction::GetOduKPort(uint32 theOduIdentifier)
{
	CT_IntfId thePort = CT_INTF_ID_UNKNOWN;
    CT_ODU_Identifier aOduIdentifier (theOduIdentifier);
    uint8 kVal = aOduIdentifier.GetOduKvalue();

	if (kVal == CT_ODU_Layer0 || kVal == CT_ODU_LayerF)
	{
		thePort = CT_PORT_SIDE_30;
	}
	else if (kVal == CT_ODU_Layer1)
	{
		thePort = CT_PORT_SIDE_31;
	}
	else if (kVal == CT_ODU_Layer2)
	{
		thePort = CT_PORT_SIDE_32;
	}
    else if (kVal == CT_ODU_Layer3)
	{
		thePort = CT_PORT_SIDE_33;
	}
    else if (kVal == CT_ODU_Layer4)
    {
        thePort = CT_PORT_SIDE_34;
    }

	return thePort;
}

void SP_ArrDefectCollectorAction::ManageOduInputRegions(uint32 theOduIdentifier, bool addInput, bool removeInput)
{
    bool result = false;
    CT_ODU_Identifier aOduIdentifier(theOduIdentifier);
	uint32 aRefCount =0;
	bool processUpdate = false;
    CT_IntfId theLayerPort = CT_INTF_ID_UNKNOWN;

    theLayerPort = GetOduKPort(theOduIdentifier);

	SP_ArrRegionObserveMap::iterator regionIt;
	regionIt = myRegionObserveMap.find((unsigned int)theLayerPort);
	if (regionIt != myRegionObserveMap.end())
	{
		aRefCount = (*regionIt).second;
		if (addInput)
		{
			aRefCount++;
            (*regionIt).second = aRefCount;
		}
		else if (removeInput)
		{
            aRefCount--;
			if (aRefCount == 0)
			{
				myRegionObserveMap.erase(regionIt);
				processUpdate = true;
			}
			else
			{
                (*regionIt).second = aRefCount;
			}
		}
	}
	else
	{
		//Not in the map
		//If adding input regions, then add to the map so that future adds do not do the same thing
		if (addInput)
		{
		    processUpdate = true;
			myRegionObserveMap.insert(SP_ArrRegionObserveMap::value_type((unsigned int)theLayerPort, 1));
		}
	}

    if (processUpdate)
    {
        if (addInput)
		{
            myBbAction->AddInputRegion(myCardContext.GetOduIf().GetMonPortSideApp(theLayerPort).GetDefectsRegion());
		}
		else if (removeInput)
		{
            myBbAction->RemoveInputRegion(myCardContext.GetOduIf().GetMonPortSideApp(theLayerPort).GetDefectsRegion());
		}
    }
}

//-----------------------------------------------------------------------------------------------------------------
// NOTE: we can have an EXTERNAL (DWDM, PMI, e.g.) problem -and- an INTERNAL (RCMM missing, e.g.) problem at the
//       same time. If so, the INTERNAL issue should still cause a switch (higher priority)!
//-----------------------------------------------------------------------------------------------------------------
bool SP_ArrDefectCollectorAction::InternalSystemDefectPresent(SP_ArrPortDefectCollectorData* theDataCollectorData)
{
    CT_CardFamily SCCardFam = CSPII_CardIF::GetInstance()->GetCardFamily();
    bool internalSystemDefect = true;
    AM_DefectVector::iterator i;
    const AM_DefectDescriptor* aDesc = NULL;
    AM_DefectProcessor* aDefectProcessor = AM_DefectCollector::GetInstance()->GetDefectProcessor();

    AM_PortType  aDirection = CT_DIR_WAVE_PORT;
    CT_IntfId aPortId = theDataCollectorData->GetPortId();
    if (aPortId == CT_LINE_SIDE_1 ||
        aPortId == CT_LINE_SIDE_0)
    {
        aDirection = CT_DIR_WAVE_LINE;
    }

    //Need to change intfid for AM access
    if (  (SCCardFam == TRN_FAM || SCCardFam == FGTMM_FAM) && (aPortId ==  CT_LINE_SIDE_1)  )
    {
        aPortId = CT_LINE_SIDE_0;
    }

    CT_IntfId aDefectIntfId = (aDirection==CT_DIR_WAVE_LINE) ? (CT_IntfId)(aPortId - CT_LINE_SIDE_0) : aPortId;

    bool aINH_EXTERNALexists = false;
    i = aDefectProcessor->GetActiveDefect(AM_AM_CABLLOS_INH_EXTERNAL_UID, AM_LOCAL, aDefectIntfId, aDirection, 0, AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, aDesc);
    if ( (i != aDefectProcessor->GetActiveDefects().end()) && ((*i).GetState() != AM_Defect::AM_NOT_DETECTED) )
    {
        aINH_EXTERNALexists = true;
    }

    bool aINH_INTERNALexists = false;
    i = aDefectProcessor->GetActiveDefect(AM_AM_CABLLOS_INH_ON_AC_UID, AM_LOCAL, aDefectIntfId, aDirection, 0, AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, aDesc);
    if ( (i != aDefectProcessor->GetActiveDefects().end()) && ((*i).GetState() != AM_Defect::AM_NOT_DETECTED) )
    {
        aINH_INTERNALexists = true;
    }

    if ( aINH_EXTERNALexists && !aINH_INTERNALexists )
    {
        internalSystemDefect = false;
    }

    return internalSystemDefect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////SP_ArrPortDefectCollectorData/////////////////////////////////////////////////////////////////////////////////////
SP_ArrPortDefectCollectorData::SP_ArrPortDefectCollectorData(	
	CT_IntfId thePortId,
    uint8 theDefectObjIndex, 
    MON_Region* theMonOptDefectRegion, 
    MON_Region* theMonOtuDefectRegion, 
    MON_Region* theMonOduDefectRegion,
    MON_Region* theMonRsDefectRegion,
    MON_Region* theMonMsDefectRegion,
    MON_Region* theMonRsConfigRegion,
    MON_Region* theMonOtuConfigRegion,
	FC_Action&  theCallbackAction):
    myPortId(thePortId),
	myDefectObjIndex(theDefectObjIndex),
	myMonOptDefectRegion(theMonOptDefectRegion),
    myMonOtuDefectRegion(theMonOtuDefectRegion),
    myMonOduDefectRegion(theMonOduDefectRegion),
    myMonRsDefectRegion(theMonRsDefectRegion),
	myMonMsDefectRegion(theMonMsDefectRegion),
    myMonRsConfigRegion(theMonRsConfigRegion),
    myMonOtuConfigRegion(theMonOtuConfigRegion),
	myIsDefectsMonitored(false),
	myClearHoldoffTimer(theCallbackAction),
    myPhyHoldoffTimer(theCallbackAction),
    myPhyDefectActive(false),
    myInternalSystemDefect(false)
{	
}

//##ModelId=38EDF51800A6
SP_ArrPortDefectCollectorData::~SP_ArrPortDefectCollectorData()
{
}

MON_Region* SP_ArrPortDefectCollectorData::GetDefectRegion(SP_ArrDefectLayer theDefectLayer)
{
	switch (theDefectLayer)
	{
	case Defect_Layer_OPT:
		return myMonOptDefectRegion;
		break;
	case Defect_Layer_OTU:
		return myMonOtuDefectRegion;
		break;
	case Defect_Layer_ODU:
		return myMonOduDefectRegion;
		break;
	case Defect_Layer_RS:
		return myMonRsDefectRegion;
		break;
	case Defect_Layer_MS:
		return myMonMsDefectRegion;
		break;
	default:
		fc_cout << "SP_ArrPortDefectCollectorData::GetDefectRegion Invalid defect layer" << endl;
		break;
	}

	return NULL;
}

MON_Region* SP_ArrPortDefectCollectorData::GetConfigRegion(SP_ArrDefectLayer theDefectLayer)
{
	switch (theDefectLayer)
	{
	case Defect_Layer_OTU:
		return myMonOtuConfigRegion;
		break;
	case Defect_Layer_RS:
		return myMonRsConfigRegion;
		break;
	default:
		fc_cout << "SP_ArrPortDefectCollectorData::GetConfigRegion Invalid defect layer" << endl;
		break;
	}

	return NULL;
}

SP_ArrTimerState SP_ArrPortDefectCollectorData::GetClearSoakTimerState()
{
	//Timer Started
    if (myClearHoldoffTimer.IsStarted())
	{
	    if (myClearHoldoffTimer.IsExpired())
		{
			return TIMER_STARTED_EXPIRED;
		}
		else
		{
			return TIMER_STARTED_RUNNING;
		}
	}
	else //Timer not started
	{
		return TIMER_NOT_STARTED;
	}
}

void SP_ArrPortDefectCollectorData::StartClearSoakTimer()
{
	StopClearSoakTimer();
	myClearHoldoffTimer.Start(ARR_DEFECT_CLEAR_HOLDOFF_TIMER);

	//DEBUG
	if (gSpArrDebugTrace != 0)
	{
		fc_cout << "Starting clear timer for port " << DISPLAY_CT_IntfId(GetPortId()) << endl;
	}
	//END DEBUG
}

void SP_ArrPortDefectCollectorData::StopClearSoakTimer()
{
	SP_ArrTimerState timerState = GetClearSoakTimerState();
	if (timerState == TIMER_STARTED_EXPIRED ||
		timerState == TIMER_STARTED_RUNNING)
	{
	    myClearHoldoffTimer.Stop();

		//DEBUG
		if (gSpArrDebugTrace != 0)
		{
			fc_cout << "Stopping clear timer for port " << DISPLAY_CT_IntfId(GetPortId()) << endl;
		}
		//END DEBUG
	}
}

SP_ArrTimerState SP_ArrPortDefectCollectorData::GetPhySoakTimerState()
{
	//Timer Started
    if (myPhyHoldoffTimer.IsStarted())
	{
	    if (myPhyHoldoffTimer.IsExpired())
		{
			return TIMER_STARTED_EXPIRED;
		}
		else
		{
			return TIMER_STARTED_RUNNING;
		}
	}
	else //Timer not started
	{
		return TIMER_NOT_STARTED;
	}
}

void SP_ArrPortDefectCollectorData::StartPhySoakTimer()
{
	StopPhySoakTimer();
	myPhyHoldoffTimer.Start(ARR_DEFECT_PHY_HOLDOFF_TIMER);

	//DEBUG
	if (gSpArrDebugTrace != 0)
	{
		fc_cout << "Starting phy timer for port " << DISPLAY_CT_IntfId(GetPortId()) << endl;
	}
	//END DEBUG
}

void SP_ArrPortDefectCollectorData::StopPhySoakTimer()
{
	SP_ArrTimerState timerState = GetPhySoakTimerState();
	if (timerState == TIMER_STARTED_EXPIRED ||
		timerState == TIMER_STARTED_RUNNING)
	{
	    myPhyHoldoffTimer.Stop();

		//DEBUG
		if (gSpArrDebugTrace != 0)
		{
			fc_cout << "Stopping phy timer for port " << DISPLAY_CT_IntfId(GetPortId()) << endl;
		}
		//END DEBUG
	}
}

bool SP_ArrPortDefectCollectorData::SetPhyDefectActive(bool isActive)
{
    bool hasChanged = false;
    if (isActive != myPhyDefectActive)
    {
        myPhyDefectActive = isActive;
        hasChanged =true;
    }

    return hasChanged;
}

bool SP_ArrPortDefectCollectorData::SetInternalSystemDefect(bool theIntSysDefect)
{
    bool hasChanged = false;
    if (theIntSysDefect != myInternalSystemDefect)
    {
        myInternalSystemDefect = theIntSysDefect;
        hasChanged =true;
    }

    return hasChanged;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////SP_ArrOduDefectCollectorData///////////////////////////////////////////////////////////////////////////////////////////////////
SP_ArrOduDefectCollectorData::SP_ArrOduDefectCollectorData(	
	CT_ODU_Identifier theOduId,
    uint8 theDefectObjIndex,
    MON_Region* theMonOduDefectRegion,
	FC_Action&  theCallbackAction):
    myOduId(theOduId),
	myDefectObjIndex(theDefectObjIndex),
    myMonOduDefectRegion(theMonOduDefectRegion),
	myIsDefectsMonitored(false),
	myClearHoldoffTimer(theCallbackAction)
{	
}

SP_ArrOduDefectCollectorData::~SP_ArrOduDefectCollectorData()
{
}

SP_ArrTimerState SP_ArrOduDefectCollectorData::GetClearSoakTimerState()
{
	//Timer Started
    if (myClearHoldoffTimer.IsStarted())
	{
	    if (myClearHoldoffTimer.IsExpired())
		{
			return TIMER_STARTED_EXPIRED;
		}
		else
		{
			return TIMER_STARTED_RUNNING;
		}
	}
	else //Timer not started
	{
		return TIMER_NOT_STARTED;
	}
}

void SP_ArrOduDefectCollectorData::StartClearSoakTimer()
{
	StopClearSoakTimer();
	myClearHoldoffTimer.Start(ARR_DEFECT_CLEAR_HOLDOFF_TIMER);

	//DEBUG
	if (gSpArrDebugTrace != 0)
	{
		fc_cout << "Starting clear timer for odu " << (uint32)GetOduId().GetIdValue() << endl;
	}
	//END DEBUG
}

void SP_ArrOduDefectCollectorData::StopClearSoakTimer()
{
	SP_ArrTimerState timerState = GetClearSoakTimerState();
	if (timerState == TIMER_STARTED_EXPIRED ||
		timerState == TIMER_STARTED_RUNNING)
	{
	    myClearHoldoffTimer.Stop();

		//DEBUG
		if (gSpArrDebugTrace != 0)
		{
			fc_cout << "Stopping clear timer for odu " << (uint32)GetOduId().GetIdValue() << endl;
		}
		//END DEBUG
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////SP_ArrDefectCollectorConfigAction///////////////////////////////////////////////////////////////////
SP_ArrDefectCollectorConfigAction::SP_ArrDefectCollectorConfigAction( 
	SP_ArrDefectCollectorAction* theDefectCollector,
	SP_ReRouteConfigRegion& theConfigRegion):
    myDefectCollector(theDefectCollector),
	myConfigRegion(theConfigRegion)
{
	myBbAction = new FC_BbAction(this);
	myBbAction->AddInputRegion(&myConfigRegion); 
}

//##ModelId=38EDF51800A6
SP_ArrDefectCollectorConfigAction::~SP_ArrDefectCollectorConfigAction()
{
	delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_ArrDefectCollectorConfigAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_ArrDefectCollectorConfigAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	//Ask defect collector to monitor any new defect regions if needed
	myDefectCollector->MonitorDefects();

	return NULL;
}
