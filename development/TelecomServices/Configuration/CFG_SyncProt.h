//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef CFG_SYNCPROT_H
#define CFG_SYNCPROT_H

#include "gdef.h"
#include "Blackboard/FC_BbObject.h"
#include "BaseClass/FC_TextStream.h"
#include "CFG_Object.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_FacilityIds.h>

//This object contains all the protection configuration for 
//timing reference selection.
class CFG_SyncProt : public CFG_Object
{
public:

	//Constructor.
    CFG_SyncProt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_SyncProt(void);


	//This method sets the current selected timing reference
    void SetTimingReference(CT_TEL_ClkSelRef theTimingReference);

	//This method sets the current selected timing reference
    CT_TEL_ClkSelRef GetTimingReference() const;


	//This method sets the current selected timing reference
    void SetActiveRefId(CT_IntfId theActiveRefId);

	//This method sets the current selected timing reference
    CT_IntfId GetActiveRefId() const;


	//This method sets the current selected timing reference
    void SetSelectedRefSSM(CT_FAC_RxSsm theSelectedRefSSM);

	//This method sets the current selected timing reference
    CT_FAC_RxSsm GetSelectedRefSSM() const;


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

	//The current timing reference
    CT_TEL_ClkSelRef myTimingReference;

    //The current Active Reference Interface ID
    CT_IntfId        myActiveRefId;

    //The current SSM value of the Selected Reference
    CT_FAC_RxSsm     mySelectedRefSSM;

	//The object has valid states 
    bool itsReady;

	//The port number.
    //uint32 itsPortNumber;

};

#endif /* CFG_SYNCPROT_H */

