
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef TSXC_ROLLRESPONSE_H
#define TSXC_ROLLRESPONSE_H

#include <TelCommon/TEL_BbObjectBase.h>


class TSXC_RollResponse : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_RollResponse();

    // Class destructor
    virtual ~TSXC_RollResponse();

    //
    // Methods to set object attributes
    //
    void    SetRollResponse(INT32 theResponse);
    void    SetRollCommandID(INT32 theCommand);
         
    // *********************************
    // Methods to get object attributes
    // *********************************
    INT32   GetRollResponse();
    INT32   GetRollCommandID();
        
protected:
    // *********************************
    // Serialization methods
    // *********************************
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    INT32                   myRollResponse;
    INT32                   myRollCommandID;
};

#endif /* TSXC_ROLLRESPONSE_H */
