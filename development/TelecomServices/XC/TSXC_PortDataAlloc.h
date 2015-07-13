/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     May, 2012     Jai Harpalani
    DESCRIPTION:   TSXC Port Data Allocation Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_PORTDATAALLOC_H
#define TSXC_PORTDATAALLOC_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "CommonTypes/CT_AgentFacility.h"


//--------------------------------------------------------------------------------------------------
// This class contains information to support port-side data allocation
//--------------------------------------------------------------------------------------------------

class TSXC_PortDataAlloc : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_PortDataAlloc();

    // Class destructor
    virtual ~TSXC_PortDataAlloc();

    //
    // Methods to set object attributes
    //
    void SetIngressMap (CT_FAC_StsMap*  theIngressMap);
    void SetEgressMap  (CT_FAC_StsMap*  theEgressMap);
            
    //
    // Methods to get object attributes
    //
    const CT_FAC_StsMap&  GetIngressMap ();
    const CT_FAC_StsMap&  GetEgressMap  ();

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
 
    CT_FAC_StsMap  myIngressMap;       
    CT_FAC_StsMap  myEgressMap;       
};

#endif // TSXC_PORTDATAALLOC_H
