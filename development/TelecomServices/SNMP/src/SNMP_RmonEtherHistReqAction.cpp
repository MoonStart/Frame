/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <PII_TickTimer.h>
#include <SNMP/SNMP_RmonEtherHistReqAction.h>
#include <SNMP/SNMP_RmonEtherHistData.h>
#include <SNMP/SNMP_RmonRequest.h>
#include <SNMP/SNMP_ScRmonSubApplication.h>
#include <CommonTypes/CT_SNMP_RmonEtherFileBuffers.h>

PMD_SnmpEtherHistBuffer  PmdEtherHistBuffer[96];

//-----------------------------------------------------------------
// Class constructor.
SNMP_ScRmonEtherHistReqAction::SNMP_ScRmonEtherHistReqAction (SNMP_RmonEtherHistDataRegion*  theDataRegion,
                                 SNMP_RmonEtherHistStorageRegion* theStorageRegion,
                                 SNMP_RmonEtherHistReqRegion*  theReqRegion,
                                 SNMP_ScRmonSubApplication* theScSubApp) :
//SNMP_ScRmonEtherHistReqAction::SNMP_ScRmonEtherHistReqAction (SNMP_RmonEtherHistStorageRegion* theStorageRegion,
//                                 SNMP_ScRmonSubApplication* theScSubApp) :
myStorageRegion(theStorageRegion),
myReqRegion(theReqRegion),
myDataRegion(theDataRegion),
myScSubApp(theScSubApp)
{
}

//-----------------------------------------------------------------
SNMP_ScRmonEtherHistReqAction::~SNMP_ScRmonEtherHistReqAction ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScRmonEtherHistReqAction::Run (FC_Object* theObject) 
{
    int activeSamples;
    int activeStorageIndex =0;
    // Get my PMD file buffer
    SNMP_EtherFileBuffer * myPMDFileBuffer = myScSubApp->GetFileBufferPtr();

    SNMP_BbRmonEtherHistStorage* storageObj = NULL;

    fc_cout <<" Ether Hist Request Entered "<<endl;

    //Get all the active hist samples for this port
    for (int i = 0; i <CT_SNMP_MAX_RMON_HIST_INDEX; i++)
    {
        try
        {
             storageObj = reinterpret_cast<SNMP_BbRmonEtherHistStorage*>(&(*myStorageRegion)[i]);
        }
        catch (FC_RuntimeError theError)
        {
            // Something major is wrong here.
            // Basically the Agent and back-end are out-of-sync.
          //  cout << "Agent & TS-RMON Hist out-of-sync" << endl;
            storageObj = NULL;
            fc_cout <<" Ether Hist Storaage object failed --- index "<<i<<endl;
        }
        if(storageObj)
        {

            if (storageObj->GetIndex()>0 && 
                storageObj->GetBucketsGranted() >0 &&
                storageObj->IsCollectionEnabled())
            {
                int * mylocalbuffer = reinterpret_cast< int *>(&PmdEtherHistBuffer[0].Index);
                fc_cout <<" Ether Hist Request index "<<i<<endl;
                
                activeSamples = 0;
                activeStorageIndex++;      //increement the Active Storage count
                for (int j=0;j<96;j++)
                {   
                    SNMP_RmonEtherHistSample& histSample = storageObj->GetSampleBuffer(j);
                    PmdEtherHistBuffer[j].SampleIndex = histSample.GetSampleIndex();
                    if (PmdEtherHistBuffer[j].SampleIndex)
                    {
                        PmdEtherHistBuffer[j].Index = storageObj->GetIndex();
                        PmdEtherHistBuffer[j].IntervalStart = histSample.GetIntervalStart() ;
                        PmdEtherHistBuffer[j].DropEvents = histSample.GetDropEvents() ;
                        PmdEtherHistBuffer[j].Octets = histSample.GetOctets() ;
                        PmdEtherHistBuffer[j].Pkts =  histSample.GetPkts() ;
                        PmdEtherHistBuffer[j].BroadcastPkts =  histSample.GetBroadcastPkts() ;
                        PmdEtherHistBuffer[j].MulticastPkts =  histSample.GetMulticastPkts() ; 
                        PmdEtherHistBuffer[j].CRCAlignErrors =  histSample.GetCRCAlignErrors() ;
                        PmdEtherHistBuffer[j].UndersizePkts =  histSample.GetUndersizePkts() ;
                        PmdEtherHistBuffer[j].OversizePkts =  histSample.GetOversizePkts() ;
                        PmdEtherHistBuffer[j].Fragments =    histSample.GetFragments() ;
                        PmdEtherHistBuffer[j].Jabbers =     histSample.GetJabbers() ;
                        PmdEtherHistBuffer[j].Collisions =  histSample.GetCollisions() ;
                        PmdEtherHistBuffer[j].Utilization = histSample.GetUtilization() ;
                        activeSamples++;

                    }
                }
                myPMDFileBuffer->CopyHistData(mylocalbuffer, 15*sizeof(int)*activeSamples ,i);
        
            }
        }
    }
    myPMDFileBuffer->WriteHistIndex(activeStorageIndex);
}





