//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTSOHDEFECT_H
#define MON_OTSOHDEFECT_H

#include "MON_Defects.h"


class MON_OtsOHDefects :public MON_Defects
{
public:

	//Constructor.
    MON_OtsOHDefects(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OtsOHDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    virtual bool IsLayerInDefects() const;

protected:

    //Serialization method
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //True if BDI (backward defect indication) is detected.
    bool myOTS_BDIPState;

    //Number of BDI defect rising transition.
    uint32 myOTS_BDIPCount;

    //True if BDI (backward defect indication) is detected.
    bool myOTS_BDIOState;

    //Number of BDI defect rising transition.
    uint32 myOTS_BDIOCount;

    //True if BDI (backward defect indication) is detected.
    bool myOTS_BDIState;

    //Number of BDI defect rising transition.
    uint32 myOTS_BDICount;

    //True if ODU_AIS is detected.
    bool myOTS_PMIState;

    //Number of ODU_AIS defect rising transition.
    uint32 myOTS_PMICount;

    //True if the received SM trace differs from the expected.
    bool myOTS_TIMState;

    //Number of TIM defect rising transition.
    uint32 myOTS_TIMCount;

    //True if BDI (backward defect indication) is detected.
    bool myOMS_FDIPState;

    //Number of BDI defect rising transition.
    uint32 myOMS_FDIPCount;

    //True if BDI (backward defect indication) is detected.
    bool myOMS_FDIOState;

    //Number of BDI defect rising transition.
    uint32 myOMS_FDIOCount;

    //True if ODU_AIS is detected.
    bool myOMS_PMIState;

    //Number of AIS defect rising transition.
    uint32 myOMS_PMICount;

};

#endif /* MON_OTSOHDEFECT_H */
