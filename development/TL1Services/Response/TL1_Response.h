/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response Base Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Response base class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_RESPONSE_H_
#define __TL1_RESPONSE_H_

#include <list>
#include <string>
using namespace std;

#include <Response/TL1_GeneralRspBlk.h>
#include <CommonTypes/CT_TL1_ErrorIndex.h>
#include <CommonTypes/CT_TL1_Error.h>
#include <LumosTypes/LT_System.h>

class TL1_Response
{
public:
    TL1_Response();
    virtual ~TL1_Response() {};

    void SetError( const CT_TL1_ErrorIndex::EC_Index&, const CT_TL1_ErrorIndex::ER_Index&);
    bool IsSuccess() const;
    CT_TL1_ErrorIndex::EC_Index GetErrorCode() const;
    CT_TL1_ErrorIndex::ER_Index GetErrorReason() const;
    typedef size_t size_type;

    // Add Function for AddResponse
    virtual void AddResponseBlock( const TL1_GeneralRspBlk &);
    virtual size_type size() const { return 0; }
    virtual int GetNumberOfErrorResponse() const { return myNbOfErrorRsp; }
    virtual void IncrementNumberOfErrorResponse() { ++myNbOfErrorRsp; }

    virtual const TL1_GeneralRspBlk& GetRspBlkAt( unsigned int ) const
    {
        // This method is not defined for this base class, see TL1_Rtv_Response
        throw CT_TL1_SROFError(CT_TL1_SROFError::ER_SROF_CMD_NC);
    }

    void SetIgnoreStatus(bool theIgnoreStatus) { myIgnoreStatus = theIgnoreStatus; }
    bool GetIgnoreStatus() const { return myIgnoreStatus; }

    void SetHandle(LT_Handle theHandle){myHandle = theHandle;}
    void SetCtag(LT_Ctag theCtag);

    LT_Handle GetHandle(){return myHandle;}
    LT_Ctag   GetCtag()  {return myCtag;}


private:
    CT_TL1_ErrorIndex::EC_Index myEC;
    CT_TL1_ErrorIndex::ER_Index myER;
    int myNbOfErrorRsp;
    bool myIgnoreStatus;
    LT_Handle myHandle;
    char myCtag[20];
};

template< class T >
class TL1_Rtv_Response : public TL1_Response
{
public:
    TL1_Rtv_Response();
    virtual ~TL1_Rtv_Response();

    void AddResponseBlock(const TL1_GeneralRspBlk &);

#if defined(LINUX) || defined(WIN32)
    typedef typename list< T >::const_iterator iterator;
#else
    typedef list< T >::const_iterator iterator;
#endif

    virtual const TL1_GeneralRspBlk& GetRspBlkAt( unsigned int pos ) const
    {
        if( pos >= myRsp.size() )
        {
            // Index out of range
            throw CT_TL1_SROFError(CT_TL1_SROFError::ER_SROF_CMD_NC);
        }

        iterator it;
        for( it = myRsp.begin(); pos > 0; --pos, ++it) { };

        return *it;
    }

    iterator begin() { return myRsp.begin(); }
    iterator end() { return myRsp.end(); }
    virtual size_type size() const { return myRsp.size(); }
    list< T >& GetRtvRsp() { return myRsp; }
private:
    list< T > myRsp;
};

template< class T>
TL1_Rtv_Response<T>::TL1_Rtv_Response()
{
}

template< class T>
TL1_Rtv_Response<T>::~TL1_Rtv_Response()
{
}

template< class T>
void TL1_Rtv_Response<T>::AddResponseBlock( const TL1_GeneralRspBlk &theBlk)
{
    const T *pBlk = dynamic_cast< const T *>( &theBlk);
    if( pBlk )
    {
        myRsp.push_back( *pBlk );
        if (theBlk.IsSuccess() == false)
        {
            IncrementNumberOfErrorResponse();
        }
    }
    else
    {
        // Throw !!!!
        throw string("Wrong Response Block");
    }
}


inline CT_TL1_ErrorIndex::EC_Index TL1_Response::GetErrorCode() const { return myEC; }
inline CT_TL1_ErrorIndex::ER_Index TL1_Response::GetErrorReason() const { return myER; }
inline bool TL1_Response::IsSuccess() const { return (myEC == CT_TL1_ErrorIndex::EC_NO_ERROR); }

#endif  // #ifndef __TL1_RESPONSE_H_  

#endif // #ifdef __cplusplus
