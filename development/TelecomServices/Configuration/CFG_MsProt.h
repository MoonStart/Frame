//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef CFG_MSPROT_H
#define CFG_MSPROT_H

#include "gdef.h"
#include "Blackboard/FC_BbObject.h"
#include "BaseClass/FC_TextStream.h"
#include "CFG_Object.h"
#include <CommonTypes/CT_FacilityIds.h>

//This object contains all the protection configuration for 
//MS layer of one SONET/SDH interface
class CFG_MsProt : public CFG_Object
{
public:

	//Constructor.
    CFG_MsProt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_MsProt(void);

	//This method sets the current egress K1 value.
    void SetEgressK1Value(uint8 theK1Value);

	//This method sets the current egress K2 value.
    void SetEgressK2Value(uint8 theK2Value);

	//This method sets the current egress Csi value.
    void SetEgressCsi(uint8 theCsi);

	//This methid sets the mate facility interface id.
	void SetMateIntfId(CT_IntfId theIntfId);

	//This method retrieves the current egress K1 value.
    uint8 GetEgressK1Value(void);

	//This method retrieves the current egress K2 value.
    uint8 GetEgressK2Value(void);

    //This method retrieves the current egress Csi value.
    uint8 GetEgressCsi(void);

	//This method retrieves the mate facility interface id.
	CT_IntfId GetMateIntfId(void);

	//This method resets all attributes to their default 
	//value.
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization text mode: This function allows writing 
	//object content to the output stream for debugging with 
	//the console.
    virtual ostream& WriteObject( ostream& theStream );

	//Serialization text mode: This function allows reading 
	//object content from the input stream for debugging with 
	//the console.
    virtual istream& ReadObject( istream& theStream );

	//Serialization binary mode: This function allows writing 
	//object content to the output stream for blackboard 
	//transfer.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

	//Serialization binary mode: This function allows reading 
	//object content from the input stream for blackboard 
	//transfer.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

	//This method allows setting the context of the object.
	//##ModelId=3AE0A74F02CC
    //void SetContext(T6700_OpmIf& theContext);

	//The context of the object.
	//##ModelId=3AE83E7103B9
   //T6700_OpmIf* itsContext;

private:
	
	//This method refreshes all hardware registers with 
	//current protection configuration.
	//##ModelId=3AE0A74F02C1
    //void HwRefresh(void);

	//The egress K1 value configured.
    uint8 myEgressK1Value;

	//The egress K2 value configured.
    uint8 myEgressK2Value;

    //The egress Csi value configured.
    uint8 myEgressCsi;

	//The object has valid states 
    bool itsReady;

	//The port number.
    //uint32 itsPortNumber;

	//The mate facility interface id
	CT_IntfId myMateIntfId;

};

#endif /* CFG_MSPROT_H */

