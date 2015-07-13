//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_TCMSTATUS_H
#define MON_TCMSTATUS_H

#include "MON_Status.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_OduDefinitions.h>


//This class hold the status value (trace message) 
//for the TCM layer.
class MON_TcmStatus: public MON_Status
{
public:
	
    //Constructor.
    MON_TcmStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_TcmStatus(void);

    //Returns the level of the status provide as argument.
	virtual void GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const;

    //Returns true if level has changed.
    virtual bool SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel);

	//Sets the receive TCM (PM) trace message.
	bool SetTraceMessage(const CT_G709Trace theTrace);
    void DeleteTraceMessage();

    //Returns the receive TCM (PM) trace message.
    CT_G709Trace & GetTraceMessage() const;

    bool GetServerSignalFail() const { return myServerSignalFail; }
    bool SetServerSignalFail(const bool theServerSignalFail);

    bool GetServerSignalDegrade() const { return myServerSignalDegrade; }
    bool SetServerSignalDegrade(const bool theServerSignalFail);

    bool SetTcmDelay(const int32 theTcmDelay);
    int32 GetTcmDelay() const;

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	
    //The receive TCM (PM) trace message.
	CT_G709Trace* myTraceMessagePtr;
    bool  myTraceInUse;

    bool  myServerSignalFail;
    bool  myServerSignalDegrade;
    int32 myTcmDelay;
};

#endif /* MON_TCMSTATUS_H */
