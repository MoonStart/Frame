/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     September, 2008    Teresa Chen
 DESCRIPTION:   TSXC_MCastFilter   Class Definition
 LAST REVISION:
--------------------------------------------------------------------------*/

#ifndef TSXC_MCAST_FILTER_H
#define TSXC_MCAST_FILTER_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>

//
// This class contains information to support destination IMUX mapping
//

class TSXC_MCastFilter : public TEL_BbObjectBase
{
public:
    // Class constructor
    TSXC_MCastFilter();

    // Class destructor
    virtual ~TSXC_MCastFilter();

    //
    // Set/Get Methods
    //
    void SetMCastTypeToUse(CT_XC_ConnectMapping theType);
    CT_XC_ConnectMapping GetMCastTypeToUse() const;

    //
    // Operators
    //
    bool operator==(const TSXC_MCastFilter& theFilter) const;
    bool operator!=(const TSXC_MCastFilter& theFilter) const;

protected:

    //
    // Serialization methods
    //
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    // virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    // virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    uint8    myMCastType;             // MCast type for ingress IMUXL/IMUXP Channel
};

#endif // TSXC_MCAST_FILTER_H
