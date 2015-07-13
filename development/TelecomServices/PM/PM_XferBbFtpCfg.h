//-----------------------------------------------------------------------------
//
// Copyright(c) 2012 Tellabs Transport Group. All rights reserved
// 
// Backend FTP server configuration for thePMXfer on SPM 
// 
//-----------------------------------------------------------------------------

#ifndef PM_XferBbFtpCfg_H
#define PM_XferBbFtpCfg_H

#include <CommonTypes/CT_Ftp.h>
#include <PM/PM_BbObject.h>


// FTP server configuration
class PM_XferBbFtpCfg : public PM_BbObject
{

public:

    PM_XferBbFtpCfg();
    virtual ~PM_XferBbFtpCfg();

    PM_XferBbFtpCfg& operator=(const PM_XferBbFtpCfg& rhs)
    {
        if (&rhs != this)  
        {
            myFtpUrl = rhs.myFtpUrl;
            myInUseFlag = rhs.myInUseFlag;
        }
        return *this;
    }

    bool operator==(const PM_XferBbFtpCfg& theObject) const
    {
        return ((myFtpUrl == theObject.myFtpUrl) && (myInUseFlag == theObject.myInUseFlag));
    }

    // Reset all parameter values
    virtual void Reset();

    // Get and Set FTP URL
    CT_FtpUrl GetFtpUrl() const
    {
        return myFtpUrl;
    }
    void SetFtpUrl(CT_FtpUrl theFtpUrl)
    {
        myFtpUrl = theFtpUrl;
        myInUseFlag = true;
    }

    bool IsInUse()
    {
        return myInUseFlag;
    }

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );

private:

    CT_FtpUrl myFtpUrl;
    bool myInUseFlag;
};


#endif //PM_XferBbFtpCfg_H
