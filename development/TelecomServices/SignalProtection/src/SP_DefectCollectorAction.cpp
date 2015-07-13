// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_Defects.h"
#include "../SP_DefectCollectorAction.h"
#include "../SP_Utilities.h"
#include <Blackboard/FC_BbAction.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_OtuDefects.h>
#include <Monitoring/MON_OptDefects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_Defects.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Odu.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_AppIf.h>
#include <T6100_CardIf.h>

//##ModelId=3BBC9B0F02A0
SP_DefectCollectorAction::SP_DefectCollectorAction(	
    TEL_BbRegionBaseImp<SP_Defects>& theDefectsRegion,
	T6100_CardIf& theCardContext):
	myDefectsRegion(theDefectsRegion),
	myCardContext(theCardContext),
	stopped(false),
	myCfgPoolOduRegion(NULL),
	myNumPooledOdu(0),
	myConfigAction(NULL)
{
    myBbAction = new FC_BbAction(this);
	myBbAction->AddOutputRegion(&myDefectsRegion);
	
}

//##ModelId=38EDF51800A6
SP_DefectCollectorAction::~SP_DefectCollectorAction()
{
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_DefectCollectorAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_DefectCollectorAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

	MON_Region* aMonRegion = NULL;
	MON_Defects* aMonitoringObject = NULL;
	SP_Defects* aDefects = NULL;
	bool hasChanged = false;
	uint32 aCount=0;
    bool aState=false;
	uint8 defectIdx = 0;
	int oduIdx = 0;

	SP_DefectCollectorDataCollection::iterator theDefectCollectorIterator;
	for (theDefectCollectorIterator = myDataCollectionSet.begin();
	     theDefectCollectorIterator != myDataCollectionSet.end();
		 ++theDefectCollectorIterator )
	{
	
	    //Do processing here
		SP_DefectCollectorData* theDataCollectorData = (*theDefectCollectorIterator);
		defectIdx = theDataCollectorData->GetDefectObjIndex();
	
		aDefects = static_cast<SP_Defects*>(&(myDefectsRegion[defectIdx]));

		//ODU could be either pooled or not
		aCount = 0;aState=false;aMonRegion = NULL;aMonitoringObject=NULL;

		if (theDataCollectorData->GetOduPoolIndex() != SP_INVALID_ODU_POOL_IDX)
		{
            oduIdx = theDataCollectorData->GetOduPoolIndex();
			aMonRegion = theDataCollectorData->GetOduPoolRegion();
		}
		else
		{
			oduIdx = 0;
			aMonRegion = theDataCollectorData->GetOduRegion();
		}
		
		//Has an odu mon region been found?
		if (aMonRegion != NULL)
		{
			aMonitoringObject = static_cast<MON_Defects*>(&((*aMonRegion)[oduIdx]));
			aMonitoringObject->GetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, &aCount, &aState);
			hasChanged |= aDefects->SetDefectStatus(CT_TEL_ODU_SDBER_DEFECT, aState, aCount);
		}

		aCount = 0;aState=false;aMonRegion = NULL;aMonitoringObject=NULL;
		aMonRegion = theDataCollectorData->GetOtuRegion();
		aMonitoringObject = static_cast<MON_Defects*>(&((*aMonRegion)[0]));
		aMonitoringObject->GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &aCount, &aState);
		hasChanged |= aDefects->SetDefectStatus(CT_TEL_OTU_LOF_DEFECT, aState, aCount);

		aDefects->Validate();

		aCount = 0;aState=false;aMonRegion = NULL;aMonitoringObject=NULL;
		aMonRegion = theDataCollectorData->GetOptRegion();
		aMonitoringObject = static_cast<MON_Defects*>(&((*aMonRegion)[0]));
		aMonitoringObject->GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &aCount, &aState);
		if (theDataCollectorData->GetOptLosCount() != aCount)
		{
			//Optical los has toggled since last run.
			//Force a region transfer
			aDefects->IncDefectId();
			hasChanged = true;
			theDataCollectorData->SetOptLosCount(aCount);
		}
	}

	if (hasChanged)
		myDefectsRegion.IncModificationCounter();
	
    return NULL;
}

void SP_DefectCollectorAction::AddToDefectCollector(CT_IntfId thePortId, bool oduIsPooled)
{
	MON_Region* theOduRegion = NULL;
	MON_Region* theOtuRegion = NULL;
	MON_Region* theOptRegion = NULL;
    /* Add MON Opt and Otu regions as input regions */
	/* Also add MON Odu region as input if not a pooled region */
	if (thePortId == CT_LINE_SIDE_0)
	{
		if (!oduIsPooled)
		{
	        theOduRegion = myCardContext.GetOduIf().GetMonLineApp().GetDefectsRegion();
		}
	    theOtuRegion = myCardContext.GetOtuIf().GetMonLineApp().GetDefectsRegion();
		theOptRegion = myCardContext.GetOptIf().GetMonLineApp().GetDefectsRegion();
	}
	else if (thePortId == CT_LINE_SIDE_1)
	{
		if (!oduIsPooled)
		{
		    theOduRegion = myCardContext.GetOduIf().GetMonLineSideApp(thePortId).GetDefectsRegion();
		}
	    theOtuRegion = myCardContext.GetOtuIf().GetMonLineSideApp(thePortId).GetDefectsRegion();
		theOptRegion = myCardContext.GetOptIf().GetMonLineSideApp(thePortId).GetDefectsRegion();
	}
	else if (IsPortFacility(thePortId))
	{
		if (!oduIsPooled)
		{
		    theOduRegion = myCardContext.GetOduIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
		}
	    theOtuRegion = myCardContext.GetOtuIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
		theOptRegion = myCardContext.GetOptIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
	}

	uint8 theDefectObjIdx = GetOPDefectObjIndex(thePortId);
	if (theDefectObjIdx < SP_MAX_NUM_LSP)
	{
		if (theOduRegion)
		{
	        myBbAction->AddInputRegion(theOduRegion,true, true, true, FC_BbRegObsPriority::HIGH);
		}
		if (theOtuRegion)
		{
            myBbAction->AddInputRegion(theOtuRegion,true, true, true, FC_BbRegObsPriority::HIGH);
		}
		if (theOptRegion)
		{
	        myBbAction->AddInputRegion(theOptRegion);
		}

		//Add to data collection set
		myDataCollectionSet.push_back(new SP_DefectCollectorData(thePortId, theDefectObjIdx, theOptRegion, theOtuRegion, theOduRegion));
		//Set the port id in the defects region
		SP_Defects* aDefects = static_cast<SP_Defects*>(&(myDefectsRegion[theDefectObjIdx]));
		aDefects->SetPortId(thePortId);
	}
}

void SP_DefectCollectorAction::AddOduPoolToDefectCollector(CT_IntfId thePortId, uint8 numOfPooledOdu)
{
	myNumPooledOdu = numOfPooledOdu;
	myCfgPoolOduRegion = myCardContext.GetOduIf().GetCfgPortSideApp(thePortId).GetCfgRegion();

	//Add the pool region pointer to the data collector data set
	MON_Region* theMONOduRegion = myCardContext.GetOduIf().GetMonPortSideApp(thePortId).GetDefectsRegion();
	SP_DefectCollectorDataCollection::iterator theDefectCollectorIterator;
	for (theDefectCollectorIterator = myDataCollectionSet.begin();
	     theDefectCollectorIterator != myDataCollectionSet.end();
		 ++theDefectCollectorIterator )
	{
	    SP_DefectCollectorData* theDataCollectorData = (*theDefectCollectorIterator);
		theDataCollectorData->SetOduPoolRegion(theMONOduRegion);
	}

	if (myConfigAction)
	{
	    myConfigAction->ConfigureBbActionInputs(true, myCfgPoolOduRegion);
	}

	myBbAction->AddInputRegion(theMONOduRegion,true, true, true, FC_BbRegObsPriority::HIGH);
	myBbAction->AddInputRegion(myCfgPoolOduRegion);
	
}

void SP_DefectCollectorAction::ConfigureOduPoolData()
{
	//Pooled Oduk
	if (myCfgPoolOduRegion != NULL)
	{
		vector<CT_ODU_ServerID> aPositionList;
		SP_DefectCollectorDataCollection::iterator theDefectCollectorIterator;
		for (theDefectCollectorIterator = myDataCollectionSet.begin();
			 theDefectCollectorIterator != myDataCollectionSet.end();
			 ++theDefectCollectorIterator )
		{
			SP_DefectCollectorData* theDataCollectorData = (*theDefectCollectorIterator);
			CT_IntfId aPort = theDataCollectorData->GetPortId();
			//Clear the odu pool index
			theDataCollectorData->SetOduPoolIndex(SP_INVALID_ODU_POOL_IDX);
			for (uint8 i=0; i<myNumPooledOdu; i++)
			{
				aPositionList.clear();
				CFG_Odu* aCfgOduObject = static_cast<CFG_Odu*>(&((*myCfgPoolOduRegion)[i]));
				if (aCfgOduObject->GetProvisionningActive() == true)
				{
					aPositionList = aCfgOduObject->GetOduPositionList();
                    // ?? if ((aPositionList.size() > 0) && (aCfgOduObject->GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT))
					if (aPositionList.size() > 0) 
					{
						//Assume there should always be just one postion in the list.
						if (CT_IntfId(aPositionList[0].GetPoolInstance()) == aPort)
						{
							theDataCollectorData->SetOduPoolIndex((int)i);
							break;
						}
					}  // if (aPositionList.size() > 0)
				} //provisioning active
			} // for (i=0
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_DefectCollectorData::SP_DefectCollectorData(	
	CT_IntfId thePortId,
    uint8 theDefectObjIndex,
	MON_Region* theMonOptRegion,
	MON_Region* theMonOtuRegion,
	MON_Region* theMonOduRegion):
    myPortId(thePortId),
	myDefectObjIndex(theDefectObjIndex),
	myMonOptRegion(theMonOptRegion),
    myMonOtuRegion(theMonOtuRegion),
    myMonOduRegion(theMonOduRegion),
	myOduPoolIndex(SP_INVALID_ODU_POOL_IDX),
	myMonOduPoolRegion(NULL),
	myOptLosCount(0)
{	
}

//##ModelId=38EDF51800A6
SP_DefectCollectorData::~SP_DefectCollectorData()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_DefectCollectorConfigAction::SP_DefectCollectorConfigAction( 
	SP_DefectCollectorAction* theDefectCollector):
    myDefectCollector(theDefectCollector)
{
	myBbAction = new FC_BbAction(this);
}

//##ModelId=38EDF51800A6
SP_DefectCollectorConfigAction::~SP_DefectCollectorConfigAction()
{
	delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_DefectCollectorConfigAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_DefectCollectorConfigAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
	myDefectCollector->ConfigureOduPoolData();
	return NULL;
}

void SP_DefectCollectorConfigAction::ConfigureBbActionInputs(bool addRegions, CFG_Region* theCfgPoolOduRegion)
{
	if (addRegions)
	{
	    myBbAction->AddInputRegion(theCfgPoolOduRegion);
	}
	else
	{
	    myBbAction->RemoveInputRegion(theCfgPoolOduRegion);
	}
}