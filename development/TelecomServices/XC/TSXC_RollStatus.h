/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     November, 2008  Kumar Solai
 DESCRIPTION:   TSXC_RollStatus  Class Definition
--------------------------------------------------------------------------*/

#ifndef TSXC_ROLLSTATUS_H
#define TSXC_ROLLSTATUS_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>

class TSXC_RollStatus : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_RollStatus();

    // Class destructor
    virtual ~TSXC_RollStatus();

    //
    // Methods to set object attributes
    //
    void SetRollCommand(INT32 theCommand);
    void SetRollCommandID(INT32 theCommandID);
    void SetRollCmdState(TSXC_RollCmdFsmState theRollCmdState);
    void SetRollConnectAddKey(TSXC_Connection theConnkey);
    void SetRollConnectRmvKey(TSXC_Connection theConnKey);
    void SetRollInfo(TSXC_Roll_Info theRollInfo);
    void Reset();
    void ApplyRollFilterForActivation(uint8 theSrc, uint8 theSrcEndPt, uint8 theDst, uint8 theDstEndPt, bool* theActiveFlag);
    
    // *********************************
    // Methods to get object attributes
    // *********************************
    INT32 GetRollCommand();
    TSXC_Connection GetRollConnectAddKey();
    TSXC_Connection GetRollConnectRmvKey();
    TSXC_Roll_Info  GetRollInfo();
    TSXC_RollCmdFsmState GetRollCmdState();
            
protected:
    // *********************************
    // Serialization methods
    // *********************************
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    INT32                               myRollCommand;
    TSXC_Connection                     myRollConnectAddKey;
    TSXC_Connection                     myRollConnectRmvKey;
    TSXC_Roll_Info                      myRollInfo;
    TSXC_RollCmdFsmState                myRollCmdState;             
};

#endif /* TSXC_ROLLSTATUS_H */
