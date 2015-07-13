/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_BBDATA_H
#define SNMP_BBDATA_H


#include <gdef.h>
#include <iostream>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <TimeService/FC_Time.h>
#include <Blackboard/FC_BbObject.h>

class SNMP_BbData : public FC_BbObject
{
public:
    SNMP_BbData();
    virtual ~SNMP_BbData();
    uint32 GetRequestId() const               {return myRequestId; }
    void   SetRequestId(uint32 theRequestId)  { myRequestId = theRequestId; }
    FC_Time& GetLastUpdateTime()              { return myLastUpdateTime; }

    inline bool IsCollectionEnabled();
    inline void EnableCollection();
    inline void DisableCollection();

    virtual void ResetAll();
    virtual void Init(restart_type theRestart);

    void SetLastErrorStatus(CT_SNMP_DataErrorStatus theError)   { myLastError = theError; }
    CT_SNMP_DataErrorStatus GetLastErrorStatus()                { return myLastError; }
    
protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );  

private:
    const int SNMP_COLL_ENABLED;
    const int SNMP_COLL_DISABLED;

    int                     myCollMode;
    uint32                  myRequestId;
    CT_SNMP_DataErrorStatus myLastError;
    FC_Time                 myLastUpdateTime;
};


inline bool SNMP_BbData::IsCollectionEnabled()
{
    return (myCollMode == SNMP_COLL_ENABLED);
}

inline void SNMP_BbData::EnableCollection()
{
    myCollMode = SNMP_COLL_ENABLED;
}

inline void SNMP_BbData::DisableCollection()
{
    myCollMode = SNMP_COLL_DISABLED;
}

#endif //SNMP_BBDATA_H
