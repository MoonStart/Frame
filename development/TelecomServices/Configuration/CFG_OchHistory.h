/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OCHHISTORYOBJECT_H
#define CFG_OCHHISTORYOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

#include <time.h>
typedef struct
{
    time_t          myTimeStamp;    //time stamp
    CT_TEL_mBm      cfg;			//eova value to hardware
    CT_TEL_mBm      mon;			//eova value from hardware
    bool            active;         //whether it is being controlled (xc)
    uint8           port;           //the add Port number (CCM P2L pipe)
}tOchHistory;

const int HW_REF_OCH_HISTORY_SIZE = 60;

//This object contains all the generic optical configuration 
//for one port.
class CFG_OchHistory : public CFG_Object
{

public:

    //Constructor.
    CFG_OchHistory(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OchHistory(void);

    //This method resets all attributes to their default 
    //value.
    virtual void Reset(void);

    virtual void Display(FC_Stream& theStream);

    virtual void RecordHistory(CT_TEL_mBm evoaValToHw, CT_TEL_mBm evoaValFromHw);

    virtual void RecordMoreHistory(bool activePath, uint8 portNumber);

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
    unsigned long       myHistIdx;
    unsigned long       myIndex;
	unsigned long		myHistCount;
    tOchHistory         myOchHistory[HW_REF_OCH_HISTORY_SIZE];
};

#endif /* CFG_OCHHISTORYOBJECT_H */

