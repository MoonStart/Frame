// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_OduKSncMiscActions.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_ApplicationStatus.h"
#include <ErrorService/FC_Error.h>
#include <T6100_Services.h>
#include <T6100_Dispatcher.h>
//#include <T6100_MainAppIf.h>
//#include <T6100_TelecomIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_SncIf.h>
#include <TsPii/TSPII_FabIf.h>
#include <Blackboard/FC_BbAction.h>
#include <Blackboard/FC_BoolRegion.h>
#include <CsPii/CSPII_CardIF.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Misc.h>

#ifdef __TARGET__
#endif

#define MAX_PROCESS_PER_ITERATION 20

extern int gSP_DebugTraceSnc;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----SP_PQWPollData action-------------------------------------------

SP_PQWPollData::SP_PQWPollData(uint8 thePQWChannel) :
    myPQWChannel(thePQWChannel)
{
    myIsConfigured = false;
    myRxPQW = 0;
    myHWSquelch = false;
    myRxSFHigh = false;
    myRxSFLow = false;
    myRxSD = false;
    myTxSFHigh = false;
    myTxSFLow = false;
    myTxSD = false;
}
SP_PQWPollData::~SP_PQWPollData()
{
}

bool SP_PQWPollData::SetPollData(uint16 theRxPqw, bool theHwSquelch, bool theRxSFHigh, bool theRxSFLow, bool theRxSD, bool theTxSFHigh, bool theTxSFLow, bool theTxSD)
{
    bool hasChanged = false;

    if (theRxPqw != myRxPQW)
    {
        myRxPQW = theRxPqw;
        hasChanged = true;
    }
    if (theHwSquelch != myHWSquelch)
    {
        myHWSquelch = theHwSquelch;
        hasChanged = true;
    }
    if (theRxSFHigh != myRxSFHigh)
    {
        myRxSFHigh = theRxSFHigh;
        hasChanged = true;
    }
    if (theRxSFLow != myRxSFLow)
    {
        myRxSFLow = theRxSFLow;
        hasChanged = true;
    }
    if (theRxSD != myRxSD)
    {
        myRxSD = theRxSD;
        hasChanged = true;
    }
    if (theTxSFHigh != myTxSFHigh)
    {
        myTxSFHigh = theTxSFHigh;
        hasChanged = true;
    }
    if (theTxSFLow != myTxSFLow)
    {
        myTxSFLow = theTxSFLow;
        hasChanged = true;
    }
    if (theTxSD != myTxSD)
    {
        myTxSD = theTxSD;
        hasChanged = true;
    }

    return hasChanged;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----SP_OduKSncPQWPollingAction action-------------------------------------------

SP_OduKSncPQWPollingAction * SP_OduKSncPQWPollingAction::itsInstance = NULL;

SP_OduKSncPQWPollingAction::SP_OduKSncPQWPollingAction(FC_BoolRegion& theIsrMonRegion, int theNumOfPqwChannels):
    myIsrMonRegion(theIsrMonRegion)
{
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, 500);

    int i, j;
    for (i=0; i< theNumOfPqwChannels; i++)
    {
        myDataCollectionSet.push_back(new SP_PQWPollData((uint8)i));
    }

    for (i=0; i < NUMBER_OF_SHELF; i++)
    {
        for (j=0; j<NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; j++)
        {
            myPQWTimeout[i][j] = false;
        }
    }

    for (i=0; i < NUMBER_OF_SHELF; i++)
   {
       for (j=0; j<NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; j++)
       {
            myPQWTimeoutRefCount[i][j] = 0;
       }
   }

    //Set instance pointer
    itsInstance = this;
}

//##ModelId=38EDF51800A6
SP_OduKSncPQWPollingAction::~SP_OduKSncPQWPollingAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
    myProcess = NULL;

    //Free poll data memory
    myDataCollectionSet.clear();
}

SP_OduKSncPQWPollingAction* SP_OduKSncPQWPollingAction::GetInstance()
{
    if(itsInstance == NULL)
    {
        FC_THROW_ERROR(FC_NotSupportedError, "SP_OduKSncPQWPollingAction::GetInstance() Instance not set");
    }
    return itsInstance;
}

//##ModelId=3B8BC9D30390
void SP_OduKSncPQWPollingAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_OduKSncPQWPollingAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    bool hasChanged = false;
    uint16 rxPQM;
    uint32 PII_count;
    uint8 thePQWChannel;
    bool rxSfHigh(false),rxSfLow(false),rxSd(false),hwSquelch(false), txSfHigh(false), txSfLow(false), txSd(false), txpqwTimeout(false);
    int i,j;

    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    for (i=0; (uint32)i<myDataCollectionSet.size(); i++)
    {
        SP_PQWPollData* thePollData = myDataCollectionSet[i];
        if (thePollData->IsConfigured() == true)
        {
            thePQWChannel = thePollData->GetPQWChannel();
            rxSfHigh = rxSfLow = rxSd = txSfHigh = txSfLow = txSd = false;

            rxPQM       = theSncIf.GetRxPQM(thePQWChannel);
            hwSquelch   = theSncIf.GetRxHwPQWSquelch(thePQWChannel);
            PII_count   = theSncIf.GetRxSFHigh(thePQWChannel);
            if(PII_count%2 != 0)
            {
                rxSfHigh = true;
            }
            PII_count   = theSncIf.GetRxSFLow(thePQWChannel);
            if(PII_count%2 != 0)
            {
                rxSfLow = true;
            }
            PII_count   = theSncIf.GetRxSD(thePQWChannel);
            if(PII_count%2 != 0)
            {
                rxSd = true;
            }
            PII_count   = theSncIf.GetTxSFHigh(thePQWChannel);
            if(PII_count%2 != 0)
            {
                txSfHigh = true;
            }
            PII_count   = theSncIf.GetTxSFLow(thePQWChannel);
            if(PII_count%2 != 0)
            {
                txSfLow = true;
            }
            PII_count   = theSncIf.GetTxSD(thePQWChannel);
            if(PII_count%2 != 0)
            {
                txSd = true;
            }

            hasChanged |= thePollData->SetPollData(rxPQM, hwSquelch, rxSfHigh, rxSfLow, rxSd, txSfHigh, txSfLow, txSd);
        }

    }

    bool pqwTimeout = false;
    for (i=0; i < NUMBER_OF_SHELF; i++)
    {
        for (j=0; j<NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; j++)
        {
            if (myPQWTimeoutRefCount[i][j] > 0)
            {
                pqwTimeout = false;
                //PII_count = theSsmIf.GetPqwTimeout(theShelfId-1, (uint8)j /*TSPII expects 0-based*/);
                PII_count = theSncIf.GetPqwTimeout(i, (uint8)j /*TSPII expects 0-based*/);
                if(PII_count%2 != 0)
                {
                   pqwTimeout = true;
                }

                if (pqwTimeout != myPQWTimeout[i][j])
                {
                   hasChanged = true;
                }

                myPQWTimeout[i][j] = pqwTimeout;
            }
        }

    }

    if (hasChanged)
    {
        myIsrMonRegion.IncModificationCounter();
        myIsrMonRegion.UpdateNotify();
    }
    return NULL;
}

FC_PeriodicProcess* SP_OduKSncPQWPollingAction::GetProcessPtr()
{
    return myProcess;
}

void SP_OduKSncPQWPollingAction::SetConfiguration(bool isConfigured, uint8 thePQWChannel, CT_ShelfId theShelf, CT_SlotId theSlot /*0-based*/)
{
    if (gSP_DebugTraceSnc != 0)
    {
        if (isConfigured)
            fc_cout << "SP_OduKSncPQWPollingAction: Adding PQW channel " << (uint32)thePQWChannel << " to polling list" << endl;
        else
            fc_cout << "SP_OduKSncPQWPollingAction: Removing PQW channel " << (uint32)thePQWChannel << " from polling list" << endl;
    }

    for (int i=0; (uint32)i<myDataCollectionSet.size(); i++)
    {
        SP_PQWPollData* thePollData = myDataCollectionSet[i];
        if (thePollData->GetPQWChannel() == thePQWChannel)
        {
            thePollData->SetIsConfigured((isConfigured == true) ? true : false);
            break;
        }
    }

    if (isConfigured)
    {
        myPQWTimeoutRefCount[theShelf][theSlot]++;
    }
    else
    {
        myPQWTimeoutRefCount[theShelf][theSlot]--;
    }

    if (myPQWTimeoutRefCount[theShelf][theSlot] <= 0)
    {
        myPQWTimeoutRefCount[theShelf][theSlot] =0;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class implements enables/disables of PQW timeout interrupts for remote
//slots
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_OduKSncPQWTimeoutIntrCtrl * SP_OduKSncPQWTimeoutIntrCtrl::itsInstance = NULL;

SP_OduKSncPQWTimeoutIntrCtrl::SP_OduKSncPQWTimeoutIntrCtrl()
{
    int i,j;
    for (i=0; i < NUMBER_OF_SHELF; i++)
    {
       for (j=0; j<NUMBER_OF_PHYSICAL_SLOT_IN_PORT_SHELF; j++)
       {
            myPQWIntRefCount[i][j] = 0;
       }
    }
}

//##ModelId=38EDF51800A6
SP_OduKSncPQWTimeoutIntrCtrl::~SP_OduKSncPQWTimeoutIntrCtrl()
{
}

SP_OduKSncPQWTimeoutIntrCtrl & SP_OduKSncPQWTimeoutIntrCtrl::GetInstance()
{
    if(itsInstance == NULL)
    {
        itsInstance = new SP_OduKSncPQWTimeoutIntrCtrl();
    }
    return *itsInstance;
}

void SP_OduKSncPQWTimeoutIntrCtrl::SetConfiguration(bool interruptEnable, CT_ShelfId theShelf /*0-based*/, CT_SlotId theSlot /* 0-based */)
{
    //If the reference count <=0
    //Then disable the interrupt.
    //If the reference count == 1 then enable the interrupt
    //else simply update reference count
    if (interruptEnable)
    {
        myPQWIntRefCount[theShelf][theSlot]++;
    }
    else
    {
        myPQWIntRefCount[theShelf][theSlot]--;
    }

    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    if (myPQWIntRefCount[theShelf][theSlot] <= 0)
    {
        myPQWIntRefCount[theShelf][theSlot] =0;
        theSncIf.SetPqwTimeoutInterruptEnable(false, theShelf, theSlot);
    }
    else if (myPQWIntRefCount[theShelf][theSlot] == 1)
    {
        theSncIf.SetPqwTimeoutInterruptEnable(true, theShelf, theSlot);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class configures the defect priority table for SNC.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_OduKSncPriorityTable * SP_OduKSncPriorityTable::itsInstance = NULL;

SP_OduKSncPriorityTable::SP_OduKSncPriorityTable()
{
    myIsConfigured = false;
}

//##ModelId=38EDF51800A6
SP_OduKSncPriorityTable::~SP_OduKSncPriorityTable()
{
}

SP_OduKSncPriorityTable & SP_OduKSncPriorityTable::GetInstance()
{
    if(itsInstance == NULL)
    {
        itsInstance = new SP_OduKSncPriorityTable();
    }
    return *itsInstance;
}

void SP_OduKSncPriorityTable::Configure()
{
    //If previously configured, then return;
    if (myIsConfigured == true)
        return;

    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);


    //Build table
    //---------------
    //For ODU0 SNC/N
    //----------------
    /* Defect Group     Defect Type      Framer      Defect Index     Defect Priority   Priority Table
       OTU_SF           Client           ODU0        0                SF                0
       ODU_SF           Client           ODU0        1                SF                0
       ODU_SD           Client           ODU0        2                SD                0
       ODU_SF           Server           ODU1        3                SF                0
       ODU_SD           Server           ODU1        4                SC                0
       OTU_SF           Server           ODU1        5                SF                0
       OTU_SD           Server           ODU1        6                SC                0
    */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU0, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU0, 1, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU0, 2, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 3, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 4, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 5, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 6, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
    //---------------
    //For ODU1 SNC/N
    //----------------
    /*
       OTU_SF           Client           ODU1        0                SF                0
       OTU_SD           Client           ODU1        1                SC                0
       ODU_SF           Client           ODU1        2                SF                0
       ODU_SD           Client           ODU1        3                SD                0
       ODU_SF           Server           ODU2        4                SF                0
       ODU_SD           Server           ODU2        5                SC                0
       OTU_SF           Server           ODU2        6                SF                0
       OTU_SD           Server           ODU2        7                SC                0
     */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 2, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 3, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 5, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);

    //---------------
    //For ODU2 SNC/N
    //----------------
       /*
       OTU_SF           Client           ODU2        0                SF                0
       OTU_SD           Client           ODU2        1                SC                0
       ODU_SF           Client           ODU2        2                SF                0
       ODU_SD           Client           ODU2        3                SD                0
       ODU_SF           Server           ODU3        4                SF                0
       ODU_SD           Server           ODU3        5                SC                0
       OTU_SF           Server           ODU3        6                SF                0
       OTU_SD           Server           ODU3        7                SC                0
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 2, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 3, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 5, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);

    //---------------
    //For ODU3 SNC/N
    //----------------
       /*
       OTU_SF           Client           ODU3        0                SF                0
       OTU_SD           Client           ODU3        1                SC                0
       ODU_SF           Client           ODU3        2                SF                0
       ODU_SD           Client           ODU3        3                SD                0
       ODU_SF           Server           ODU4        4                SF                0
       ODU_SD           Server           ODU4        5                SC                0
       OTU_SF           Server           ODU4        6                SF                0
       OTU_SD           Server           ODU4        7                SC                0
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 2, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 3, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 5, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);

    //---------------
    //For ODU4 SNC/N
    //----------------
       /*
       OTU_SF           Client           ODU4        0                SF                0
       OTU_SD           Client           ODU4        1                SC                0
       ODU_SF           Client           ODU4        2                SF                0
       ODU_SD           Client           ODU4        3                SD                0
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 2, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 3, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_0);

    //---------------
    //For ODUF SNC/N
    //----------------
    /*
       OTU_SF           Client           ODUF        0                SF                0
       OTU_SD           Client           ODUF        1                SC                0
       ODU_SF           Client           ODUF        2                SF                0
       ODU_SD           Client           ODUF        3                SD                0
       ODU_SF           Server           ODU2        4                SF                0
       ODU_SD           Server           ODU2        5                SC                0
       OTU_SF           Server           ODU2        6                SF                0
       OTU_SD           Server           ODU2        7                SC                0
     */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 2, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 3, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 5, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_0);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_0);

    //---------------
    //For ODU0 SNC/I
    //----------------
       /*
       OTU_SF           Client           ODU0        0                SC                1
       ODU_SF           Client           ODU0        1                SC                1
       ODU_SD           Client           ODU0        2                SC                1
       ODU_SF           Server           ODU1        3                SF                1
       OTU_SF           Server           ODU1        4                SF                1
       ODU_SD           Server           ODU1        5                SD                1
       OTU_SD           Server           ODU1        6                SC                1
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU0, 0, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU0, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU0, 2, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 3, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 5, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU1, 6, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);

    //---------------
    //For ODU1 SNC/I
    //----------------
       /*
       OTU_SF           Client           ODU1        0                SF                1
       OTU_SD           Client           ODU1        1                SD                1
       ODU_SF           Client           ODU1        2                SC                1
       ODU_SD           Client           ODU1        3                SC                1
       ODU_SF           Server           ODU2        4                SF                1
       ODU_SD           Server           ODU2        5                SD                1
       OTU_SF           Server           ODU2        6                SF                1
       OTU_SD           Server           ODU2        7                SC                1
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 2, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU1, 3, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 5, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);

    //---------------
    //For ODU2 SNC/I
    //----------------
       /*
       OTU_SF           Client           ODU2        0                SF                1
       OTU_SD           Client           ODU2        1                SD                1
       ODU_SF           Client           ODU2        2                SC                1
       ODU_SD           Client           ODU2        3                SC                1
       ODU_SF           Server           ODU3        4                SF                1
       ODU_SD           Server           ODU3        5                SD                1
       OTU_SF           Server           ODU3        6                SF                1
       OTU_SD           Server           ODU3        7                SC                1
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 2, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU2, 3, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 5, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU3, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);

    //---------------
    //For ODU3 SNC/I
    //----------------
       /*
       OTU_SF           Client           ODU3        0                SF                1
       OTU_SD           Client           ODU3        1                SD                1
       ODU_SF           Client           ODU3        2                SC                1
       ODU_SD           Client           ODU3        3                SC                1
       ODU_SF           Server           ODU4        4                SF                1
       ODU_SD           Server           ODU4        5                SD                1
       OTU_SF           Server           ODU4        6                SF                1
       OTU_SD           Server           ODU4        7                SC                1
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 2, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU3, 3, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 5, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU4, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);

    //---------------
    //For ODU4 SNC/I
    //----------------
       /*
       OTU_SF           Client           ODU4        0                SF                1
       OTU_SD           Client           ODU4        1                SD                1
       ODU_SF           Client           ODU4        2                SC                1
       ODU_SD           Client           ODU4        3                SC                1
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 2, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODU4, 3, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);

    //---------------
    //For ODUF SNC/I
    //----------------
       /*
       OTU_SF           Client           ODUF        0                SF                1
       OTU_SD           Client           ODUF        1                SC                1
       ODU_SF           Client           ODUF        2                SC                1
       ODU_SD           Client           ODUF        3                SC                1
       ODU_SF           Server           ODU2        4                SF                1
       ODU_SD           Server           ODU2        5                SD                1
       OTU_SF           Server           ODU2        6                SF                1
       OTU_SD           Server           ODU2        7                SC                1
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 1, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 2, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_CLIENT, TSPII_SNCIF_ODUF, 3, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 4, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_ODU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 5, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SF, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 6, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_1);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_OTU_SD, TSPII_SNCIF_SERVER, TSPII_SNCIF_ODU2, 7, TSPII_SNCIF_PRIOR_NONE, TSPII_SNCIF_PRIOR_TBL_1);

    //---------------
    //For ODU0 SNC/S
    //----------------
       /*
       TCM_SF           Client           ODU0        0                SF                2
       TCM_SD           Client           ODU0        1                SD                2
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SF, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU0, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_2);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SD, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU0, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_2);

    //---------------
    //For ODU1 SNC/S
    //----------------
       /*
       TCM_SF           Client           ODU1        0                SF                2
       TCM_SD           Client           ODU1        1                SD                2
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SF, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU1, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_2);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SD, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU1, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_2);

    //---------------
    //For ODU2 SNC/S
    //----------------
       /*
       TCM_SF           Client           ODU2        0                SF                2
       TCM_SD           Client           ODU2        1                SD                2
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SF, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU2, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_2);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SD, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU2, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_2);

    //---------------
    //For ODU3 SNC/S
    //----------------
       /*
       TCM_SF           Client           ODU3        0                SF                2
       TCM_SD           Client           ODU3        1                SD                2
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SF, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU3, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_2);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SD, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU3, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_2);

    //---------------
    //For ODU4 SNC/S
    //----------------
       /*
       TCM_SF           Client           ODU4        0                SF                2
       TCM_SD           Client           ODU4        1                SD                2
       */

       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SF, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU4, 0, TSPII_SNCIF_PRIOR_SFH, TSPII_SNCIF_PRIOR_TBL_2);
       theSncIf.SetTohPriorityTable(TSPII_SNCIF_TCM_SD, TSPII_SNCIF_TCM, TSPII_SNCIF_ODU4, 1, TSPII_SNCIF_PRIOR_SD, TSPII_SNCIF_PRIOR_TBL_2);

       myIsConfigured = true;//Fully configured
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class determines general switch fab configuration parameters like logical shelf id etc...
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_OduKSncSwitchFabConfig * SP_OduKSncSwitchFabConfig::itsInstance = NULL;

SP_OduKSncSwitchFabConfig::SP_OduKSncSwitchFabConfig()
{
}

//##ModelId=38EDF51800A6
SP_OduKSncSwitchFabConfig::~SP_OduKSncSwitchFabConfig()
{
}

SP_OduKSncSwitchFabConfig & SP_OduKSncSwitchFabConfig::GetInstance()
{
    if(itsInstance == NULL)
    {
        itsInstance = new SP_OduKSncSwitchFabConfig();
    }
    return *itsInstance;
}

void SP_OduKSncSwitchFabConfig::GetLogicalShelfId(CFG_Misc& theMiscCfgObject, CT_ShelfId phyShelfId1, CT_ShelfId phyShelfId2, CT_ShelfId* theShelfId1, CT_ShelfId* theShelfId2)
{
    CT_TEL_SwitchMode aSwitchMode = theMiscCfgObject.GetSwitchMode();
    if (aSwitchMode == CT_TEL_SwitchMode_Repeater)
    {
        (*theShelfId1) = 2;
        (*theShelfId2) =1;
    }
    else if (aSwitchMode == CT_TEL_SwitchMode_End_Switch || aSwitchMode == CT_TEL_SwitchMode_Mesh)
    {
        CT_ShelfId aCurrentShelf = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();
        if (aCurrentShelf == phyShelfId1)
        {
            (*theShelfId1) = phyShelfId1;
            (*theShelfId2) = phyShelfId2;
        }
        else if (aCurrentShelf == phyShelfId2)
        {
            (*theShelfId1) = phyShelfId2;
            (*theShelfId2) = phyShelfId1;
        }
        else
        {
            (*theShelfId1) = UNKNOWN_SHELF_ID;
            (*theShelfId2) = UNKNOWN_SHELF_ID;
        }
    }
    else //Switching shelf
    {
        (*theShelfId1) = 1;
        (*theShelfId2) =2;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class implements an action that control the tranmission of pqw from a module
//during initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SP_OduKSncPQWTxControlAction::SP_OduKSncPQWTxControlAction(
    TEL_BbRegionBaseImp<SP_ApplicationStatus>* theAppStatus,
    FC_BoolRegion* theControlRegion):
    myAppStatus(theAppStatus),
    myControlRegion(theControlRegion)
{
    myBbAction = new FC_BbAction(this);
    myBbAction->AddInputRegion(myControlRegion);
    myBbAction->AddInputRegion(myAppStatus);
}

//##ModelId=38EDF51800A6
SP_OduKSncPQWTxControlAction::~SP_OduKSncPQWTxControlAction()
{
    myBbAction->RemoveInputRegion(myControlRegion);
    myBbAction->RemoveInputRegion(myAppStatus);
    delete myBbAction;
    myBbAction = NULL;
}

//##ModelId=3B8BC9D30390
void SP_OduKSncPQWTxControlAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_OduKSncPQWTxControlAction::DoRunWithReason(unsigned theRunReason,
                                                           FC_Object* theInvokerObj,
                                                           FC_Object* theParam)
{

    if ( ( (*myAppStatus)[0].IsReady() ) )
    {
        TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
        TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
        if (theSncIf.GetPqwTransmitEnable() == false)
        {
            fc_cout << "Enabling Global PQW transmit" << endl;
            theSncIf.EnablePqwTransmit(true);
        }
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////
//This class implements an action that sets up global snc configuration
//prior to protection schemes being configured.
//In then updates the control region so that protection scheme configuration may occur
//////////////////////////////////////////////////////////////////////////////////////
SP_OduKSncGlobalControlConfigAction::SP_OduKSncGlobalControlConfigAction(
    CFG_MiscCfgRegion* theCfgMiscRegion,
    FC_BoolRegion* theControlRegion):
    myCfgSwitchModeRegion(theCfgMiscRegion),
    myPrevSwitchMode(CT_TEL_SwitchMode_None),
    myControlRegion(theControlRegion),
    myLogicalShelfId(UNKNOWN_SHELF_ID),
    myGeneralControlInitComplete(false),
    myOverride(false)
{
    myPhyShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();
    mySlotId = (CT_SlotId)CSPII_CardIF::GetInstance()->GetSlotId();

    myBbAction = new FC_BbAction(this);

    if (myCfgSwitchModeRegion)
    {
        myBbAction->AddInputRegion(myCfgSwitchModeRegion);
    }

    myProcess = new FC_TimedProcess(*myBbAction, gTimerDispatcher, 5 /*5 secs poll rate*/);

    myHoldoffTimer = new SP_CallbackTimer(*myBbAction);
}

//##ModelId=38EDF51800A6
SP_OduKSncGlobalControlConfigAction::~SP_OduKSncGlobalControlConfigAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
    myProcess = NULL;

    myHoldoffTimer->Stop();
    delete myHoldoffTimer;
    myHoldoffTimer = NULL;

    if (myCfgSwitchModeRegion)
    {
        myBbAction->RemoveInputRegion(myCfgSwitchModeRegion);
    }

    delete myBbAction;
    myBbAction = NULL;
}

//##ModelId=3B8BC9D30390
void SP_OduKSncGlobalControlConfigAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_OduKSncGlobalControlConfigAction::DoRunWithReason(unsigned theRunReason,
                                                           FC_Object* theInvokerObj,
                                                           FC_Object* theParam)
{

    //If an override is specified, bypass normal initialization sequence 
    //and follow an abbreviated sequence.
    if (myOverride)
    {
        if (myGeneralControlInitComplete == false)
        {
            //Configure global SNC priority tables
            SP_OduKSncPriorityTable::GetInstance().Configure();

            TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
            TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
            theSncIf.SetGeneralSncControlParams(0, mySlotId-1);

            fc_cout << "Activating SNC control region" << endl;
            myControlRegion->IncModificationCounter();
            myControlRegion->UpdateNotify();
            myGeneralControlInitComplete = true;
        }
        
    }
    else
    {
        //If timer was previously started and now has expired, then validate the control region
        //before doing any more processing
        if (myHoldoffTimer->IsStarted())
        {
            if (myHoldoffTimer->IsExpired())
            {
                fc_cout << "Activating SNC control region" << endl;
                myControlRegion->IncModificationCounter();
                myControlRegion->UpdateNotify();
                myHoldoffTimer->Stop();
            }
        }

        bool hasChanged = false;
        CFG_Misc& aMiscCfgObject = static_cast<CFG_Misc&> ((*myCfgSwitchModeRegion)[0]);

        bool aIsSwitchMode = (aMiscCfgObject.GetLinkRate(mySlotId-1) != CT_TEL_LinkRateNone);
        CT_TEL_SwitchMode curSwitchMode = aMiscCfgObject.GetSwitchMode();
        if (aIsSwitchMode == true)
        {
            TSPII_FabRegion * theFabRegion = TSPII_SubApplication::GetInstance()->GetFab();
            TSPII_FabIf& theFabIf = static_cast<TSPII_FabIf&> ((*theFabRegion)[0]);
            if (theFabIf.GetSlotSpeed(mySlotId-1, false)  !=  CT_TEL_LinkRateNone)
            {

                if (myPrevSwitchMode != curSwitchMode)
                {
                    CT_ShelfId aShelfId1, aShelfId2;
                    SP_OduKSncSwitchFabConfig::GetInstance().GetLogicalShelfId(aMiscCfgObject, myPhyShelfId, UNKNOWN_SHELF_ID, &aShelfId1, &aShelfId2);
                    //calculate new shelf id
                    hasChanged = true;
                    myPrevSwitchMode = curSwitchMode;
                    myLogicalShelfId = aShelfId1;
                }

                //Configure global control init complete
                if (myGeneralControlInitComplete == false || hasChanged)
                {
                    fc_cout << "Configuring Global Snc Control data" << endl;

                    //Configure global SNC priority tables
                    SP_OduKSncPriorityTable::GetInstance().Configure();

                    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
                    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
                    theSncIf.SetGeneralSncControlParams(myLogicalShelfId-1, mySlotId-1);
                    myGeneralControlInitComplete = true;
                    myHoldoffTimer->Stop();
                    myHoldoffTimer->Start(5*1000);
                }
            }
            else
            {
                if (gSP_DebugTraceSnc != 0)
                {
                    fc_cout << "**********SP_OduKSncGlobalControlConfigAction::DEBUG********* TSPII not in switched mode...waiting...." << endl;
                }
                myProcess->WakeUp();
            }
        }
    }
    return NULL;
}

void SP_OduKSncGlobalControlConfigAction::SetOverride(bool theOverride)
{
    myOverride = theOverride;
}

FC_TimedProcess* SP_OduKSncGlobalControlConfigAction::GetProcessPtr()
{
    return myProcess;
}