/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     November, 2008  Kumar Solai
 DESCRIPTION:   TSXC_RollRxStatus  Class Definition
--------------------------------------------------------------------------*/

#ifndef TSXC_ROLLRXSTATUS_H
#define TSXC_ROLLRXSTATUS_H

#include <TelCommon/TEL_BbObjectBase.h>

class TSXC_RollRxStatus : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_RollRxStatus();

    // Class destructor
    virtual ~TSXC_RollRxStatus();

    //
    // Methods to set object attributes
    //
    void SetRollCommand(INT32 theCommand);
    void SetRollCommandID(INT32 theCommandID);
    void SetRollMsgSent(INT32 theMsgSent);
    void SetRollMsgRcvd(INT32 theMsgRcvd);
    void Reset();
    
    // *********************************
    // Methods to get object attributes
    // *********************************
    INT32   GetRollCommand();
    INT32   GetRollCommandID();
    INT32   GetRollMsgSent();
    INT32   GetRollMsgRcvd();
        
protected:
    // *********************************
    // Serialization methods
    // *********************************
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    INT32                   myRollCommand;
    INT32                   myRollCommandID;
    INT32                   myRollMsgSent;
    INT32                   myRollMsgRcvd;    
};

#endif /* TSXC_ROLLRXSTATUS_H */
