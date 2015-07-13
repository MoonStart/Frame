// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_DefectTransferAction.h"
#include "../SP_Defects.h"
#include "../SP_Utilities.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ITS/ITS_UpstreamRegion.h>
#include <ITS/ITS_Upstream.h>
#include <ITS/ITS_ConfigOnTrn.h>
#include <ITS/ITS_SubApplicationUpstream.h>
#include <T6100_MainAppIf.h>
#include <T6100_ShelfIf.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <T6100_Dispatcher.h>
#include <SignalProtection/SP_DefectSubApplicationOnAdmin.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegion.h>
#include <SignalProtection/SP_1plus1ProtectionGroupConfig.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>

int gSP_OSPMProtDebugTrace = 0;


//##ModelId=3BBC9B0F02A0
SP_DefectTransferAction::SP_DefectTransferAction(TEL_BbRegionBaseImp<SP_Defects>& theDefectsRegion, T6100_CardIf& theCardContext):
myDefectsRegion(theDefectsRegion),
myContext(theCardContext),
stopped(false)
{
    myBbAction = new FC_BbAction(this);
	myTimedProcess = new FC_TimedProcess(*this,gTimerDispatcher,500); //500 msecs
	for (uint32 i =0; i <SP_MAX_NUM_LSP; i++)
	{
        myPrevDefectId[i] = CT_SP_INVALID_COMMAND;
	}
}

//##ModelId=38EDF51800A6
SP_DefectTransferAction::~SP_DefectTransferAction()
{
	delete myTimedProcess;
    delete myBbAction;
}

//##ModelId=3B8BC9D30390
void SP_DefectTransferAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_DefectTransferAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

	bool pendingTransfer = false;
    uint8 defectObjIndex = 0;
	bool isLsp= false;
	bool isXC=false;
	SP_Defects* aDefects = NULL;

	//Do processing here
	//Scan ITS regions for connected info
	//If it exists, find corresponding OSPM line protection config region
	//Check its configuration, if configured run the alt defect update action to set the defects
	SP_ITSConfigRegionCollection::iterator theITSConfigRegIterator;
	SP_ITSUpstreamRegionCollection::iterator theITSUpstreamRegIterator;
	for (theITSConfigRegIterator = myITSConfigRegions.begin(), theITSUpstreamRegIterator = myITSUpstreamRegions.begin();
	     theITSConfigRegIterator != myITSConfigRegions.end();
		 ++theITSConfigRegIterator, ++ theITSUpstreamRegIterator)
	{
	    ITS_ConfigOnTrn* theITSConfigObject = static_cast<ITS_ConfigOnTrn*>(&((*(*theITSConfigRegIterator))[0]));
		if (theITSConfigObject)
		{
			isLsp = theITSConfigObject->GetInfo(ITS_LSP);
			isXC = theITSConfigObject->GetInfo(ITS_XC);
			if (isLsp)
			{
				ITS_Upstream* theITSUpstreamObject = static_cast<ITS_Upstream*>(&((*(*theITSUpstreamRegIterator))[0]));
				if (theITSUpstreamObject)
				{
					//Check if card family is OPSM
					if (theITSUpstreamObject->GetCardFamily() == OPSM_FAM)
					{
						//Get defect object
						if (theITSUpstreamObject->GetThisCardFamily() == HDTG_FAM ||
							theITSUpstreamObject->GetThisCardFamily() == ENH_PACKET_FAM ||
                            theITSUpstreamObject->GetThisCardFamily() == ENH_TRN_FAM ||
                            theITSUpstreamObject->GetThisCardFamily() == SSM40_FAM)
						{
						    defectObjIndex = GetOPDefectObjIndex((*theITSUpstreamRegIterator)->GetITSApp()->GetBaseAppIntfId());
						}
                        else if (theITSUpstreamObject->GetThisCardFamily() == HDTG2_FAM)
                        {
						    defectObjIndex = GetOPDefectObjIndex((*theITSUpstreamRegIterator)->GetITSApp()->GetBaseAppIntfId());
                            defectObjIndex = defectObjIndex/2;
                        }
						else
						{
                            defectObjIndex =0;
						}
						if (defectObjIndex >=SP_MAX_NUM_LSP)
						{
							FC_THROW_ERROR(FC_RuntimeError,"SP_DefectTransferAction: Invalid index into defect region");
						}
							
						aDefects = static_cast<SP_Defects*>(&(myDefectsRegion[defectObjIndex]));
						
						//Get line protection region
						CT_IntfId connIntfId = theITSUpstreamObject->GetIntfId();
						int anIndex = GetIndexFromPort(connIntfId);
						T6100_CardIf* theCard = T6100_MainAppIf::Instance().GetShelfPtr(theITSUpstreamObject->GetShelf())->GetSlotPtr(theITSUpstreamObject->GetSlot())->GetCardPtr(OPSM_FAM);
						if (theCard)
						{
							SP_ProtectionGroupConfigRegion& theConfigRegion = theCard->GetLineSideProtectionIf().GetLineSideProtectionApp().GetConfigRegion();
							//Get the interface
							SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(theConfigRegion[anIndex]);
							if (aConfig.InUse())
							{
								if (aConfig.Get1plus1Type() == CT_SP_DPRING)
								{
									//Call the AltDefectUpdateAction to run
									SP_DefectSubApplicationOnAdmin* theDefectApp = static_cast<SP_DefectSubApplicationOnAdmin*>(theCard->GetSPDefectAppIfPtr());
									theDefectApp->GetDefectUpdateAction()->UpdateDefects(aDefects, anIndex, CT_INTF_ID_UNKNOWN,aConfig.Get1plus1Type(), myPrevDefectId[defectObjIndex] != aDefects->GetDefectId());
									//Save the defect id for future comparisons
									myPrevDefectId[defectObjIndex] = aDefects->GetDefectId();
								}
								else
								{
									if (gSP_OSPMProtDebugTrace != 0)
										fc_cout << "SP_DefectTransferAction: Incompatible protection type" << endl;
								}
							}
							else
							{
								//Should have protection info -- have to reschedule ourselves to run again since we do not know
								//when the configuration will be there
								if (gSP_OSPMProtDebugTrace != 0)
								{
							        fc_cout << "SP_DefectTransferAction: lsp pending transfer...rescheduling" << endl;
								}
								pendingTransfer = true;
							}
						}
					}
				}

			}
			else //not lsp
			{
				if (isXC)
				{
					T6100_CardIf* theConnCard = theITSConfigObject->GetDwnStrmCardIf();
					CT_IntfId theConnPortId = theITSConfigObject->GetDwnStrmIntfId();
					if (theConnCard && theConnCard->GetCardFamily() == OPSM_FAM)
					{
						//Get defect object
						aDefects = static_cast<SP_Defects*>(&(myDefectsRegion[0]));
						//Get line protection region
						int anIndex = GetIndexFromPort(theConnPortId);
						SP_ProtectionGroupConfigRegion& theConfigRegion = theConnCard->GetLineSideProtectionIf().GetLineSideProtectionApp().GetConfigRegion();
						//Get the interface
						SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(theConfigRegion[anIndex]);
						if (aConfig.InUse())
						{
							if (aConfig.Get1plus1Type() == CT_SP_OAPS)
							{
								//Call the AltDefectUpdateAction to run
								SP_DefectSubApplicationOnAdmin* theDefectApp = static_cast<SP_DefectSubApplicationOnAdmin*>(theConnCard->GetSPDefectAppIfPtr());
								theDefectApp->GetDefectUpdateAction()->UpdateDefects(aDefects, anIndex, theConnPortId,aConfig.Get1plus1Type(), myPrevDefectId[defectObjIndex] != aDefects->GetDefectId());
								//Save the defect id for future comparisons
								myPrevDefectId[defectObjIndex] = aDefects->GetDefectId();
							}
							else
							{
								if (gSP_OSPMProtDebugTrace != 0)
									fc_cout << "SP_DefectTransferAction: Incompatible protection type" << endl;
							}
						}
						else
						{
							//Should have protection info -- have to reschedule ourselves to run again since we do not know
							//when the configuration will be there
							if (gSP_OSPMProtDebugTrace != 0)
							{
							    fc_cout << "SP_DefectTransferAction: psp pending transfer...rescheduling" << endl;
							}
							pendingTransfer = true;
						}
					}
				}
			}
		}
	}

	if (pendingTransfer)
		myTimedProcess->WakeUp();
    

    return NULL;
}

void SP_DefectTransferAction::AddtoITSConfigRegions(ITS_ConfigRegionOnTrn* theRegion)
{
	myITSConfigRegions.push_back(theRegion);
}
void SP_DefectTransferAction::AddtoITSUpstreamRegions(ITS_UpstreamRegion* theRegion)
{
	myITSUpstreamRegions.push_back(theRegion);
}

int SP_DefectTransferAction::GetIndexFromPort(CT_IntfId port)
{
	int result(-1);
    switch (port) {
	    case CT_LINE_SIDE_0:
		case CT_LINE_SIDE_1:
		case CT_PORT_SIDE_0:
		    result = 0;
		    break;
	    case CT_LINE_SIDE_2:
		case CT_LINE_SIDE_3:
		case CT_PORT_SIDE_1:
		    result = 1;
		    break;
		case CT_LINE_SIDE_4:
		case CT_LINE_SIDE_5:
		case CT_PORT_SIDE_2:
		    result = 2;
		    break;
	    case CT_LINE_SIDE_6:
		case CT_LINE_SIDE_7:
		case CT_PORT_SIDE_3:
		    result = 3;
		    break;
	    default: //unknown protection scheme
			FC_THROW_ERROR(FC_RuntimeError,
                      "SP_DefectTransferAction: Invalid interface");
		    break;
	}
	return result;
}
