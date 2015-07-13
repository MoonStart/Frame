//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_DEFECTS_H
#define SP_DEFECTS_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>


//This class hold the a collection of defects counts & value (LOF TIM, etc)
//that SP collects from other entities
class SP_Defects :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_Defects();

    //Virtual destructor.
    virtual ~SP_Defects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, uint32 theCount);

    //Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

	//Initialize data members
	void Reset();

	void Validate() {myIsValidated = true;};
	bool IsValid() {return myIsValidated == true;};

	CT_SP_CommandID GetDefectId() {return myDefectId;};
	void IncDefectId() {myDefectId++;};

	void SetPortId(CT_IntfId thePortId);
	CT_IntfId GetPortId() {return myPortId;};

protected:

private:

    //True if there is an OTU LOF.
    bool myOtuLOFState;

    //Number of OTU LOF defect rising transition.
    uint32 myOtuLOFCount;

    //True if ODU SD BER is detected.
    bool myOduSDBerState;

    //Number of ODU SD BER defect rising transition.
    uint32 myOduSDBerCount;

    //True if Upper layer TA is detected.
    bool myUpperLayerTAState;

    //Number of Upper layer TA defect rising transition.
    uint32 myUpperLayerTACount;

	//True if Upper layer NTA is detected.
    bool myUpperLayerNTAState;

    //Number of Upper layer NTA defect rising transition.
    uint32 myUpperLayerNTACount;

	bool myIsValidated;

	CT_SP_CommandID myDefectId;

	CT_IntfId myPortId;
};

#endif /* SP_DEFECTS_H */
