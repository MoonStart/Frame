/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     May, 2009         Kumar Solai
    DESCRIPTION:   TSXC CQM Response Class Definition
    LAST REVISION:
--------------------------------------------------------------------------*/
#ifndef TSXC_CQMRESPONSE_H
#define TSXC_CQMRESPONSE_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_QrsTypes.h>

class TSXC_CQMResponse : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_CQMResponse();

    // Class destructor
    virtual ~TSXC_CQMResponse();

    //
    // Methods to set object attributes
    //
    void SetCQMResponse(CT_XC_CQMID theResponse);
        
    // *********************************
    // Methods to get object attributes
    // *********************************
    CT_XC_CQMID         GetCQMResponse();
        
protected:
    // *********************************
    // Serialization methods
    // *********************************
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    CT_XC_CQMID                     myCQMResponse;
};

#endif /* TSXC_CQMRESPONSE_H */
