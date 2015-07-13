//Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef CFG_DCCLPROT_H
#define CFG_DCCLPROT_H

#include "gdef.h"
#include "Blackboard/FC_BbObject.h"
#include "BaseClass/FC_TextStream.h"
#include "CFG_Object.h"
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_DCC_Definitions.h>

//This object contains all the protection configuration for 
//DCCL layer.
class CFG_DcclProt : public CFG_Object
{
public:

	//Constructor.
    CFG_DcclProt(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_DcclProt(void);

    bool                      SetBroadcastMode(CT_DCC_BroadcastMode theBroadcastMode);
    bool                      SetSelectionMode(CT_DCC_SelectionMode theSelectionMode);
    bool                      SetRemotePort(uint8 theRemotePort);
    bool                      SetRxSelected(bool theSelected);

    CT_DCC_BroadcastMode      GetBroadcastMode() const;
    CT_DCC_SelectionMode      GetSelectionMode() const;
    uint8                     GetRemotePort() const;
    bool                      GetRxSelected() const;

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

private:

	//Currently laps broadcast and selection mode
    CT_DCC_BroadcastMode myBroadcastMode;
    CT_DCC_SelectionMode mySelectionMode;
    bool myIsRxSelected;

    //Remote port information
    uint8 myRemotePort;

};

#endif /* CFG_DCCLPROT_H */