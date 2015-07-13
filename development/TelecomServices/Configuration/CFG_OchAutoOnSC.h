/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OCHAUTOCONSC_H
#define CFG_OCHAUTOCONSC_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_OchAutoOnSC
: public CFG_Object
{

public:

    //Constructor.
    CFG_OchAutoOnSC(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OchAutoOnSC(void);

    //This method resets all attributes to their default 
    //value.
    virtual void Reset(void);

    virtual void Display(FC_Stream& theStream);

    bool SetGain(CT_TEL_mBm theGain);
    CT_TEL_mBm GetGain() const;
    bool SetActivePath(bool theActivePath);
    bool GetActivePath() const;
    bool SetPortNumber(uint8 thePortNumber);
    uint8 GetPortNumber() const;
    
    FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

    //Serialization text mode: This function allows writing 
    //object content to the output stream for debugging with 
    //the console.
    //##ModelId=3C0FE62F02E5
    virtual ostream& WriteObject( ostream& theStream );

    //Serialization text mode: This function allows reading 
    //object content from the input stream for debugging with 
    //the console.
    //##ModelId=3C0FE62F02EF
    virtual istream& ReadObject( istream& theStream );

    //Serialization binary mode: This function allows writing 
    //object content to the output stream for blackboard 
    //transfer.
    //##ModelId=3C0FE62F02F9
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Serialization binary mode: This function allows reading 
    //object content from the input stream for blackboard 
    //transfer.
    //##ModelId=3C0FE62F0304
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    CT_TEL_mBm myGain;
    bool myActivePath;
    uint8 myPortNumber;
};

#endif /* CFG_OCHAUTOCONSC_H */
