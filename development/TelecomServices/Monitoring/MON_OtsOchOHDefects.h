//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTSOCHOHDEFECT_H
#define MON_OTSOCHOHDEFECT_H

#include "MON_Defects.h"


class MON_OtsOchOHDefects :public MON_Defects
{
public:

	//Constructor.
    MON_OtsOchOHDefects(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OtsOchOHDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization method
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //True if FDI-P (Forward defect indication - Payload) is detected.
    bool myOCH_FDIPState;

    //Number of FDI-P defect rising transition.
    uint32 myOCH_FDIPCount;

    //True if FDI-O (Forward defect indication - Overhead) is detected.
    bool myOCH_FDIOState;

    //Number of FDI-O defect rising transition.
    uint32 myOCH_FDIOCount;

    //True if OCH OCI is detected.
    bool myOCH_OCIState;

    //Number of OCH OCI defect rising transition.
    uint32 myOCH_OCICount;

};

#endif /* MON_OTSOCHOHDEFECT_H */
