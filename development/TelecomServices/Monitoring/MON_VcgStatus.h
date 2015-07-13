//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_VCGSTATUS_H
#define MON_VCGSTATUS_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Vcg_Member.h>
#include "MON_Object.h"
#include <vector>

//This class hold the status values for the Vcg layer.
class MON_VcgStatus 
: public MON_Object
{
public:

	//Constructor.
    MON_VcgStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_VcgStatus();

    void ClearMemberList();
    // This method adds a new Mbr to the Mbr Status List.
    void AddNewVcgMember(CT_Vcg_Mbr theNewVcgMbr);

    // These methods are modifiers and accessors for 
    // the current number of active Tx members.
    uint16 GetNumActiveTxMbrs() const;
    bool SetNumActiveTxMbrs(uint16 theNumActiveTxMbrs);

    // These methods are modifiers and accessors for 
    // the current current number of active Rx members.
    uint16 GetNumActiveRxMbrs() const;
    bool SetNumActiveRxMbrs(uint16 theNumActiveRxMbrs);

    // These methods are modifiers and accessors for 
    // the current Lcas protocol active.
    bool GetLcasDetected() const; 
    bool SetLcasDetected(bool theLCASDetected);

    // These methods are modifiers and accessors for 
    // the active VCG (protected VCG).
    bool GetActive() const; 
    bool SetActive(bool theActive);

    // These methods are modifiers and accessors for 
    // whether to Force an Evc Refresh.
    bool GetForceEvcRefresh() const; 
    bool SetForceEvcRefresh(bool theForceEvcRefresh);

    // Set List of Mbr Status for this VCG.
    void SetMbrList(vector<CT_Vcg_Mbr>& theMbrList);

    // Get List of Mbr Status for this VCG.
    const vector<CT_Vcg_Mbr>& GetMbrList();

    // This method returns the index to the MbrList for a given TTP id.
    uint16 GetListMbrId(uint16 theMbrId) const;

    // This method adds a new Mbr to the Mbr Status List.
    void AddNewMbr2List(uint16 theMbrId);
    
    // This method removes a Mbr from the Status List.
    void RemoveMbrFrmList(uint32 theMbrId);

    // This method Gets the TX Sequence number.
    uint32 GetTxSeqNbr(uint16 theMbrId) const;

    // This method Sets the TX Sequence number. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetTxSeqNbr(uint32 theTxSeqNbr, uint16 theMbrId, bool theConvertId = true);

    // This method Gets the RX Sequence number.
    uint32 GetRxSeqNbr(uint16 theMbrId) const;

    // This method Sets the RX Sequence number. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetRxSeqNbr(uint32 theRxSeqNbr, uint16 theMbrId, bool theConvertId = true);

    // This method Gets the Rx Differental Delay.
    uint32 GetRxDifferentalDelay(uint16 theMbrId) const;

    // This method Sets the Rx Differental Delay. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetRxDifferentalDelay(uint32 theRxDifferentalDelay, uint16 theMbrId, bool theConvertId = true);

    // This method Gets the Tx State.
    uint32 GetTxState(uint16 theMbrId) const;

    // This method Sets the Tx State. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetTxState(CT_TEL_VCG_STATE theTxState, uint16 theMbrId, bool theConvertId = true);

    // This method Gets the Rx State.
    uint32 GetRxState(uint16 theMbrId) const;

    // This method Sets the Rx State. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetRxState(CT_TEL_VCG_STATE theRxState, uint16 theMbrId, bool theConvertId = true);
        
    // This method Gets the status of the Sequence MisMatch condition.
    bool GetSeqMisMatchActive(uint16 theMbrId) const;
    
    // This method Gets the status of the Sequence MisMatch counter.
    uint32 GetSeqMisMatchCount(uint16 theMbrId) const;

    // This method Sets the Sequence MisMatch. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetSeqMisMatchCount(uint32 theSeqMisMatchCount, uint16 theMbrId, bool theConvertId = true);

    // This method Gets the status Loss Of Multi-Frame Alignment condition.
    bool GetLOS_MF_AlignActive(uint16 theMbrId) const;
    
    // This method Gets the status Loss Of Multi-Frame Alignment counter.
    uint32 GetLOS_MF_AlignCount(uint16 theMbrId) const;

    // This method Sets the Loss Of Multi-Frame Alignment. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetLOS_MF_AlignCount(uint32 theLOS_MF_AlignCount, uint16 theMbrId, bool theConvertId = true);

    // This method Gets the Member Not De-Skewable condition.
    bool GetMNDActive(uint16 theMbrId) const;
    
    // This method Gets the Member Not De-Skewable counter.
    uint32 GetMNDCount(uint16 theMbrId) const;

    // This method Sets the Member Not De-Skewable. Note: Parameter theConvertId is
    // used to indicate if theMbrId is actual TTP id, then theConvertId should
    // be true otherwise theConvertId should be false and theMbrId should be
    // the result of GetListMbr being called.
    bool SetMNDCount(uint32 theMNDCount, uint16 theMbrId, bool theConvertId = true);

    //Debug Methods
    void Reset();
	virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // The current number of active Tx members.
    uint16 myNumActiveTxMbrs;
	
    // The current number of active Rx members.
    uint16 myNumActiveRxMbrs;
	
    // Lcas protocol active on this VCG.
    bool myLcasActive;
    
    // Thie VCG is active (protected VCG).
    bool myActive;

    // Thie indicates if the Evc layer needs to be refreshed, 
    // plus a counter of the number of times it is changed to true.
    bool   myForceEvcRefresh; 
    uint32 myForceEvcRefrCount;

    // Members that make up this VCG.
    vector<CT_Vcg_Mbr> myMbrList;

};

#endif /* MON_VCGSTATUS_H */

