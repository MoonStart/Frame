/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:         
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 

#ifndef SNMP_BBCONFIG_H
#define SNMP_BBCONFIG_H

#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>

class SNMP_BbCfg : public FC_BbObject
{
public:
    SNMP_BbCfg();
    virtual ~SNMP_BbCfg();

    inline bool IsCollectionEnabled();
    inline bool EnableCollection();
    inline bool DisableCollection();

    virtual void Init(restart_type theRestart);
    virtual void ResetAll() = 0;

protected:
    virtual FC_Stream& ReadObjectBinary (FC_Stream& theStream);
    virtual FC_Stream& WriteObjectBinary (FC_Stream& theStream);
    virtual istream& ReadObject (istream& theStream);
    virtual ostream& WriteObject (ostream& theStream);

private:
    const int SNMP_COLL_ENABLED;
    const int SNMP_COLL_DISABLED;

    int myCollMode;

};

inline bool SNMP_BbCfg::IsCollectionEnabled()
{
    return (myCollMode == SNMP_COLL_ENABLED);
}

inline bool SNMP_BbCfg::EnableCollection()
{
    bool hasChanged = (myCollMode != SNMP_COLL_ENABLED);
    myCollMode = SNMP_COLL_ENABLED;
    return hasChanged;
}

inline bool SNMP_BbCfg::DisableCollection()
{
    bool hasChanged = (myCollMode != SNMP_COLL_DISABLED);
    myCollMode = SNMP_COLL_DISABLED;
    return hasChanged;
}

#endif //SNMP_RMONETHERCFG_H

