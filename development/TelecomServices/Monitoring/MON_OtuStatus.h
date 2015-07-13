//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTUSTATUS_H
#define MON_OTUSTATUS_H

#include "MON_Status.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Float32.h>
#include <CommonTypes/CT_Telecom.h>


//This class hold the status value (trace message, levels) 
//for the OTU layer.
class MON_OtuStatus 
: public MON_Status
{
public:
    //Constructor.
    MON_OtuStatus(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OtuStatus(void);

    //Returns the level of the status provide as argument.
    virtual void GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const;

    //Returns true if level has changed.
    virtual bool SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel);


    //Sets the receive OTU (SM) trace message.
    bool SetTraceMessage(const CT_G709Trace& theTrace);
    void DeleteTraceMessage();

    //Returns the receive OTU (SM) trace message.
    CT_G709Trace & GetTraceMessage() const;

	
    //Returns the BER value.
    const CT_Float32 GetBER() const;

    // Sets the BER value in MON
    bool SetBER(const CT_Float32& theBER);


    // Returns the Dispersion Compensation State in MON
    CT_TEL_DispCompState GetDispCompState() const; 

    // Sets the Dispersion Compensation State in MON
    bool SetDispCompState(CT_TEL_DispCompState theDispCompState);


    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //The receive OTU (SM) trace message.
    CT_G709Trace* myTraceMessagePtr;
    bool myTraceInUse;

    //The BER value
    CT_Float32 myBER;

    // The Dispersion Compensation State
    CT_TEL_DispCompState myDispCompState;
};

#endif /* MON_OTUSTATUS_H */
