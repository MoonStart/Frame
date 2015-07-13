// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_VcgStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_VcgStatus::MON_VcgStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_VcgStatus::~MON_VcgStatus(void)
{
    // Nothing to do for now.
}


void MON_VcgStatus::ClearMemberList(void)
{
    myMbrList.erase(myMbrList.begin(), myMbrList.end());
}


void MON_VcgStatus::AddNewVcgMember(CT_Vcg_Mbr theNewVcgMbr)
{
    myMbrList.push_back(theNewVcgMbr);
}


uint16 MON_VcgStatus::GetNumActiveTxMbrs() const 
{
    return myNumActiveTxMbrs;
}

bool MON_VcgStatus::SetNumActiveTxMbrs(uint16 theNumActiveTxMbrs) 
{
    bool hasChanged = false;
    if (!(myNumActiveTxMbrs == theNumActiveTxMbrs))
    {
        myNumActiveTxMbrs = theNumActiveTxMbrs;
        hasChanged = true;
    }

    return hasChanged;
}


uint16 MON_VcgStatus::GetNumActiveRxMbrs() const 
{
    return myNumActiveRxMbrs;
}

bool MON_VcgStatus::SetNumActiveRxMbrs(uint16 theNumActiveRxMbrs) 
{
    bool hasChanged = false;
    if (!(myNumActiveRxMbrs == theNumActiveRxMbrs))
    {
        myNumActiveRxMbrs = theNumActiveRxMbrs;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_VcgStatus::GetLcasDetected() const 
{
    return myLcasActive;
}

bool MON_VcgStatus::SetLcasDetected(bool theLCASDetected) 
{
    bool hasChanged = false;
    if (!(myLcasActive == theLCASDetected))
    {
        myLcasActive = theLCASDetected;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_VcgStatus::GetActive() const 
{
    return myActive;
}

bool MON_VcgStatus::SetActive(bool theActive) 
{
    bool hasChanged = false;
    if (!(myActive == theActive))
    {
        myActive = theActive;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_VcgStatus::GetForceEvcRefresh() const 
{
    return myForceEvcRefresh;
}

bool MON_VcgStatus::SetForceEvcRefresh(bool theForceEvcRefresh) 
{
    bool hasChanged = false;
    if ((myForceEvcRefresh != theForceEvcRefresh) && (theForceEvcRefresh))
    {
        // Only set the hasChanged flag if myForceEvcRefresh becomes true
        // and increment the count
        hasChanged = true;
        myForceEvcRefrCount++;
    }
    myForceEvcRefresh = theForceEvcRefresh;

    return hasChanged;
}

void MON_VcgStatus::SetMbrList(vector<CT_Vcg_Mbr>& theMbrList)
{
    myMbrList = theMbrList;
}

void MON_VcgStatus::AddNewMbr2List(uint16 theMbrId)
{
    CT_Vcg_Mbr aMbr;
    aMbr.myMbrId = theMbrId;
    myMbrList.push_back(aMbr);
}

void MON_VcgStatus::RemoveMbrFrmList(uint32 theMbrId)
{
    myMbrList.erase( myMbrList.begin() + theMbrId );
}

const vector<CT_Vcg_Mbr>& MON_VcgStatus::GetMbrList()
{
    return myMbrList;
}

uint16 MON_VcgStatus::GetListMbrId(uint16 theMbrId) const
{
    	
    uint16 numberOfMbrs = myMbrList.size();;
    uint16 i;

	for (i = 0; i < numberOfMbrs; i++)
    {
	    if (myMbrList[i].GetMbrId() == theMbrId)
            return i;
    }
    return 255;
}

uint32 MON_VcgStatus::GetTxSeqNbr(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetTxSeqNbr());
    }
    return 0;
}

bool MON_VcgStatus::SetTxSeqNbr(uint32 theTxSeqNbr, uint16 theMbrId, bool theConvertId) 
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetTxSeqNbr() == theTxSeqNbr))
        {
            myMbrList[i].myTxSeqNbr = theTxSeqNbr;
            hasChanged = true;
        }
    }
    return hasChanged;
}

uint32 MON_VcgStatus::GetRxSeqNbr(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetRxSeqNbr());
    }
    return 0;
}

bool MON_VcgStatus::SetRxSeqNbr(uint32 theRxSeqNbr, uint16 theMbrId, bool theConvertId) 
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetRxSeqNbr() == theRxSeqNbr))
        {
            myMbrList[i].myRxSeqNbr = theRxSeqNbr;
            hasChanged = true;
        }
    }
    return hasChanged;
}

uint32 MON_VcgStatus::GetRxDifferentalDelay(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetRxDifferentalDelay());
    }
    return 0;
}

bool MON_VcgStatus::SetRxDifferentalDelay(uint32 theRxDifferentalDelay, uint16 theMbrId, bool theConvertId) 
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetRxDifferentalDelay() == theRxDifferentalDelay))
        {
            myMbrList[i].myRxDifferentalDelay = theRxDifferentalDelay;
            hasChanged = true;
        }
    }
    return hasChanged;
}

uint32 MON_VcgStatus::GetTxState(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetTxState());
    }
    return 0;
}

bool MON_VcgStatus::SetTxState(CT_TEL_VCG_STATE theTxState, uint16 theMbrId, bool theConvertId)
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetTxState() == theTxState))
        {
            myMbrList[i].myTxState = theTxState;
            hasChanged = true;
        }
    }
    return hasChanged;
}

uint32 MON_VcgStatus::GetRxState(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetRxState());
    }
    return 0;
}

bool MON_VcgStatus::SetRxState(CT_TEL_VCG_STATE theRxState, uint16 theMbrId, bool theConvertId)
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetRxState() == theRxState))
        {
            myMbrList[i].myRxState = theRxState;
            hasChanged = true;
        }
    }
    return hasChanged;
}
bool MON_VcgStatus::GetSeqMisMatchActive(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
      bool aSeqMisMatchActive = false;  
      if(myMbrList[i].GetSeqMisMatchCount()%2 != 0)
      {
          aSeqMisMatchActive = true;        
      }
      return aSeqMisMatchActive;
    }
    return false;
}

uint32 MON_VcgStatus::GetSeqMisMatchCount(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetSeqMisMatchCount());
    }
    return 0;
}

bool MON_VcgStatus::SetSeqMisMatchCount(uint32 theSeqMisMatchCount, uint16 theMbrId, bool theConvertId)
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetSeqMisMatchCount() == theSeqMisMatchCount))
        {
            myMbrList[i].mySeqMisMatchCount = theSeqMisMatchCount;
            hasChanged = true;
        }
    }
    return hasChanged;
}

bool MON_VcgStatus::GetLOS_MF_AlignActive(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
      bool aLOS_MF_AlignActive = false;  
      if(myMbrList[i].GetLOS_MF_AlignCount()%2 != 0)
      {
          aLOS_MF_AlignActive = true;        
      }
      return aLOS_MF_AlignActive;
    }
    return false;
}

uint32 MON_VcgStatus::GetLOS_MF_AlignCount(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetLOS_MF_AlignCount());
    }
    return 0;
}

bool MON_VcgStatus::SetLOS_MF_AlignCount(uint32 theLOS_MF_AlignCount, uint16 theMbrId, bool theConvertId)
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetLOS_MF_AlignCount() == theLOS_MF_AlignCount))
        {
            myMbrList[i].myLOS_MF_AlignCount = theLOS_MF_AlignCount;
            hasChanged = true;
        }
    }
    return hasChanged;
}

bool MON_VcgStatus::GetMNDActive(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
      bool aMNDActive = false;  
      if(myMbrList[i].GetMNDCount()%2 != 0)
      {
          aMNDActive = true;        
      }
      return aMNDActive;
    }
    return false;
}

uint32 MON_VcgStatus::GetMNDCount(uint16 theMbrId) const
{
    uint16 i;
    i = GetListMbrId(theMbrId);

    if (i != 255)
    {
        return(myMbrList[i].GetMNDCount());
    }
    return 0;
}

bool MON_VcgStatus::SetMNDCount(uint32 theMNDCount, uint16 theMbrId, bool theConvertId)
{
    bool hasChanged = false;
    uint16 i;

    if(theConvertId)
    {
        i = GetListMbrId(theMbrId);
    }
    else
        i = theMbrId;

    if (i != 255)
    {
        if (!(myMbrList[i].GetMNDCount() == theMNDCount))
        {
            myMbrList[i].myMNDCount = theMNDCount;
            hasChanged = true;
        }
    }
    return hasChanged;
}

void MON_VcgStatus::Reset(void)
{
    MON_Object::Reset();
    myNumActiveTxMbrs = 0;
	myNumActiveRxMbrs = 0;
    myLcasActive = false;
    myActive = false;
    myForceEvcRefresh = false;
    myForceEvcRefrCount = 0;
    myMbrList.erase(myMbrList.begin(), myMbrList.end());
}

// For Display
ostream& MON_VcgStatus::WriteObject( ostream& theStream )
{
    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myNumActiveTxMbrs);
    theStream << FC_InsertVar(myNumActiveRxMbrs);
    theStream << FC_InsertVar(myLcasActive);
    theStream << FC_InsertVar(myActive);
    theStream << FC_InsertVar(myForceEvcRefresh);
    theStream << FC_InsertVar(myForceEvcRefrCount);

  	uint32	numberOfMbrs = myMbrList.size();
    theStream << FC_InsertVar(numberOfMbrs);
	vector<CT_Vcg_Mbr>::iterator i;
	for (i = myMbrList.begin(); i != myMbrList.end(); i++)
    {
        CT_Vcg_Mbr aMbr;
        aMbr = CT_Vcg_Mbr(*i);
		theStream << FC_InsertVar(aMbr);
    }
    return theStream;

}

istream& MON_VcgStatus::ReadObject( istream& theStream )
{
    uint32 numberOfMbrs;
	uint32 i = 0;

    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myNumActiveTxMbrs);
    theStream >> FC_ExtractVar(myNumActiveRxMbrs);
    theStream >> FC_ExtractVar(myLcasActive);
    theStream >> FC_ExtractVar(myActive);
    theStream >> FC_ExtractVar(myForceEvcRefresh);
    theStream >> FC_ExtractVar(myForceEvcRefrCount);

    theStream >> FC_ExtractVar(numberOfMbrs);

    vector<CT_Vcg_Mbr> aMbrList;
    aMbrList.erase(aMbrList.begin(), aMbrList.end());

    for (i = 0; i < numberOfMbrs; i++)
	{
    	CT_Vcg_Mbr aMbr;
        theStream >> FC_ExtractVar(aMbr);
        aMbrList.push_back(aMbr);
	}

    SetMbrList(aMbrList);
    return theStream;

}

// For persistence and region transfer
FC_Stream& MON_VcgStatus::WriteObjectBinary( FC_Stream& theStream )
{

    MON_Object::WriteObjectBinary(theStream);
    theStream << myNumActiveTxMbrs;
    theStream << myNumActiveRxMbrs;
    theStream << myLcasActive;
    theStream << myActive;
    // -- Used only locally --theStream << myForceEvcRefresh;
    // -- Used only locally --theStream << myForceEvcRefrCount;

    uint32	numberOfMbrs = myMbrList.size();
    theStream << numberOfMbrs;
	vector<CT_Vcg_Mbr>::iterator i;
	for (i = myMbrList.begin(); i != myMbrList.end(); i++)
		theStream << (*i);
    return theStream;

}

FC_Stream& MON_VcgStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    uint32	numberOfMbrs;
	uint32 i = 0;

    MON_Object::ReadObjectBinary(theStream);
    theStream >> myNumActiveTxMbrs;
    theStream >> myNumActiveRxMbrs;
    theStream >> myLcasActive;
    theStream >> myActive;
    // -- Used only locally --theStream >> myForceEvcRefresh;
    // -- Used only locally --theStream >> myForceEvcRefrCount;

    myMbrList.erase(myMbrList.begin(), myMbrList.end());
    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
	{
		CT_Vcg_Mbr aMbr;
		theStream >> aMbr;
		myMbrList.push_back(aMbr);

	}
    return theStream;

}

void MON_VcgStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "VCG   - Number Active Tx Mbrs             = " << uint32(myNumActiveTxMbrs) << endl;
    theStream   << "VCG   - Number Active Rx Mbrs             = " << uint32(myNumActiveRxMbrs) << endl;
    theStream   << "VCG   - LCAS Protocol Active              = " << DISPLAY_BOOL(myLcasActive) << endl;
    theStream   << "VCG   - Active                            = " << DISPLAY_BOOL(myActive) << endl;
    theStream   << "VCG   - Force Evc Refresh                 = " << DISPLAY_BOOL(myForceEvcRefresh) << endl;
    theStream   << "VCG   - Force Evc Refresh Count           = " << myForceEvcRefrCount << endl;
    theStream   << "--------------=== VCG MBR STATUS ===--------------" << endl << endl;
	vector<CT_Vcg_Mbr>::iterator i;
	for (i = myMbrList.begin(); i != myMbrList.end(); i++)
    {
        CT_Vcg_Mbr aMbr;
        aMbr = CT_Vcg_Mbr(*i);
        theStream   << "VCG MBR - Mbr Id              = " << (uint16)aMbr.GetMbrId() << endl;
        theStream   << "VCG MBR - TxSeq               = " << (uint32)aMbr.GetTxSeqNbr() << endl;
        theStream   << "VCG MBR - RxSeq               = " << (uint32)aMbr.GetRxSeqNbr() << endl;
        theStream   << "VCG MBR - DD                  = " << (uint32)aMbr.GetRxDifferentalDelay() << endl;
        theStream   << "VCG MBR - TxState             = " << DISPLAY_VCG_STATE(aMbr.GetTxState()) << endl;
        theStream   << "VCG MBR - RxState             = " << DISPLAY_VCG_STATE(aMbr.GetRxState()) << endl;
        theStream   << "VCG MBR - LossMFAln           = " << DISPLAY_BOOL(GetLOS_MF_AlignActive(aMbr.GetMbrId())) << " (" << (uint32)aMbr.GetLOS_MF_AlignCount() << ")" << endl;
        theStream   << "VCG MBR - SeqMisMtch          = " << DISPLAY_BOOL(GetSeqMisMatchActive(aMbr.GetMbrId())) << " (" << (uint32)aMbr.GetSeqMisMatchCount() << ")" << endl;
        theStream   << "VCG MBR - MbrNotDeSkw         = " << DISPLAY_BOOL(GetMNDActive(aMbr.GetMbrId())) << " (" << (uint32)aMbr.GetMNDCount() << ")" << endl << endl;
    }
}
