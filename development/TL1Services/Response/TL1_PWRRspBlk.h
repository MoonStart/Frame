/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Optical Power Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Optical Power Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_PWR_RESPONSE_BLOCK_H_
#define __TL1_PWR_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_PWRRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_PWRRspBlk();
    
    // Construcotr for General Facility
    TL1_PWRRspBlk(const string *, 
                  const CT_TL1_FacAddr *,
                  const bool *Apao, 
                  const CT_TEL_mBm *Output,
                  const bool *Apai, 
                  const CT_TEL_mBm *Input);

    TL1_PWRRspBlk(const TL1_PWRRspBlk& pwrBlk);

    virtual ~TL1_PWRRspBlk();

    TL1_PWRRspBlk& operator=( const TL1_PWRRspBlk& theBlock );

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetApao(bool & ) const;

    bool GetOutput(CT_TEL_mBm &) const;

    bool GetApai(bool & ) const;

    bool GetInput(CT_TEL_mBm &) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_Apao,
        INDEX_Output,
        INDEX_Apai,
        INDEX_Input,
        INDEX_END
    };

    vector<bool>    myBitSet;

    string          myEntityName;
    CT_TL1_FacAddr  myFacAddr;
    bool            myApao;
    CT_TEL_mBm      myOutput;
    bool            myApai;
    CT_TEL_mBm      myInput;

};

typedef TL1_Rtv_Response< TL1_PWRRspBlk > TL1_PWRResponse;
#endif  // #ifndef __TL1_PWR_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
