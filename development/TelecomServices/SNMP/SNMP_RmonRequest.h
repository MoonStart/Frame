/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_RMONREQUEST_H
#define SNMP_RMONREQUEST_H

#include <SNMP/SNMP_Request.h>
#include <CommonTypes/CT_SNMP_Definition.h>

class SNMP_BbRmonRequest : public SNMP_BbRequest
{
public:

    SNMP_BbRmonRequest ();
    virtual ~SNMP_BbRmonRequest();
    inline uint32 SendRequest(CT_SNMP_Integer32 theIndex);
    inline void SendRequest(CT_SNMP_Integer32 theIndex,
                            uint32 theRequestId);
    inline uint32 GetIndex() const;
    virtual void Reset();

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );

    CT_SNMP_Integer32 myIndex;

private:

};

//-----------------------------------------------------------------
inline uint32 SNMP_BbRmonRequest::GetIndex() const
{
    return myIndex;
}

//-----------------------------------------------------------------
inline uint32 SNMP_BbRmonRequest::SendRequest(CT_SNMP_Integer32 theIndex)
{
    myIndex = theIndex;
    return SNMP_BbRequest::SendRequest();
}

//-----------------------------------------------------------------
inline void SNMP_BbRmonRequest::SendRequest(CT_SNMP_Integer32 theIndex,
                                            uint32 theRequestId)
{
    myIndex = theIndex;
    SNMP_BbRequest::SendRequest(theRequestId);
}

class SNMP_BbRmonEtherStatsRequest : public SNMP_BbRmonRequest
{
public:
    SNMP_BbRmonEtherStatsRequest();
    virtual ~SNMP_BbRmonEtherStatsRequest();
};

class SNMP_BbRmonEtherHistRequest : public SNMP_BbRmonRequest
{
public:
    SNMP_BbRmonEtherHistRequest();
    virtual ~SNMP_BbRmonEtherHistRequest();

    inline uint32 SendRequest(CT_SNMP_Integer32 theIndex,
                              CT_SNMP_Integer32 theSampleIndex);
    inline void   SendRequest(CT_SNMP_Integer32 theIndex,
                              CT_SNMP_Integer32 theSampleIndex,
                              uint32 theRequestId,
                              bool theNextSampleRequested = false);
    inline CT_SNMP_Integer32 GetSampleIndex();
    inline bool IsNextSampleRequested();
    virtual void Reset();

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );

private:
    CT_SNMP_Integer32 mySampleIndex;
    bool              myNextSampleRequested;
};

//-----------------------------------------------------------------
inline CT_SNMP_Integer32 SNMP_BbRmonEtherHistRequest::GetSampleIndex()
{
    return mySampleIndex;
}

inline bool SNMP_BbRmonEtherHistRequest::IsNextSampleRequested()
{
    return myNextSampleRequested;
}

inline uint32 SNMP_BbRmonEtherHistRequest::SendRequest(CT_SNMP_Integer32 theIndex,
                              CT_SNMP_Integer32 theSampleIndex)
{
    mySampleIndex = theSampleIndex;
    return SNMP_BbRmonRequest::SendRequest(theIndex);
}

inline void SNMP_BbRmonEtherHistRequest::SendRequest(CT_SNMP_Integer32 theIndex,
                                                       CT_SNMP_Integer32 theSampleIndex,
                                                       uint32 theRequestId,
                                                       bool theNextSampleRequested)
{
    mySampleIndex = theSampleIndex;
    myNextSampleRequested = theNextSampleRequested;
    SNMP_BbRmonRequest::SendRequest(theIndex, theRequestId);
}


#endif //SNMP_RMONREQUEST_H
