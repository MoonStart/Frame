/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     December, 2007  Kumar C Solai
 DESCRIPTION:   TSXC_ConnectService  Class Definition
--------------------------------------------------------------------------*/
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef TSXC_QRSSERVICE_H
#define TSXC_QRSSERVICE_H

class CT_XC_CQMID;

class TSXC_QrsService 
{
public:

    // Get TSXC_QrsService singleton instance
    static TSXC_QrsService* GetInstance();

    bool GetXcInitComplete();
    bool GetXcByPassFlag();
    void RequestResponse(CT_XC_CQMID* theRespId);

private:
        
    static TSXC_QrsService* ItsInstance;
};

#endif // TSXC_QRSSERVICE_H
