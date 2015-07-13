/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_BBRMONDATA_H
#define SNMP_BBRMONDATA_H


#include <gdef.h>
#include <iostream>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>
#include <SNMP/SNMP_Data.h>

class SNMP_BbRmonData : public SNMP_BbData
{
public:
    SNMP_BbRmonData();
    virtual ~SNMP_BbRmonData();

    CT_SNMP_Integer32 GetIndex()                  {return myIndex; }
    void SetIndex(CT_SNMP_Integer32 theData)      { myIndex = theData; }
    void ResetIndex()                             { myIndex = CT_SNMP_DEFAULT_RMON_INDEX; }
    virtual void ResetAll();
    virtual void Init(restart_type theRestart);

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );  

private:

    CT_SNMP_Integer32        myIndex;
};

#endif // SNMP_BBRMONDATA_H
