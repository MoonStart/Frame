//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTSSTATUS_H
#define MON_OTSSTATUS_H

#include "MON_Object.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>


//This class hold the status value (trace message, levels) 
//for the OTS layer.
class MON_OtsStatus 
: public MON_Object
{
public:

    //Constructor.
    MON_OtsStatus(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OtsStatus(void);

 	//Returns the receive OTS (PM) trace message.
	const CT_G709Trace GetTraceMessage() const;

	//Sets the receive OTS (PM) trace message.
	bool SetTraceMessage(const CT_G709Trace theTrace);

    virtual void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The receive OTS (PM) trace message.
	CT_G709Trace myTraceMessage;

    //The Catps state (enable or disable)
    bool myCatpsEnable;
};

#endif /* MON_OTSSTATUS_H */
