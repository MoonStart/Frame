//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTSDEFECTS_H
#define MON_OTSDEFECTS_H

#include "MON_Defects.h"


class MON_OtsDefects :public MON_Defects
{
public:

	//Constructor.
    MON_OtsDefects(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OtsDefects(void);

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

    //True if OTS_LOS is detected.
    bool myOTS_LOSState;

    //Number of OTS_LOS defect rising transition.
    uint32 myOTS_LOSCount;
};

#endif /* MON_OTSOHDEFECT_H */
