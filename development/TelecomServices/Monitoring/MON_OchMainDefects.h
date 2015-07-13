//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OCHMAINDEFECT_H
#define MON_OCHMAINDEFECT_H

#include "MON_Defects.h"


//This class contains the defects status and transition 
//counts for the Main Och layer.
class MON_OchMainDefects :public MON_Defects
{

public:

	//Constructor.
    MON_OchMainDefects(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OchMainDefects(void);

    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;

    //Returns the status and count of the defect provide as argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //True if signaling that fails och layer is received. 
	bool myChannelFailDefects;

	//Current number of rising transition of the Signaling defect.
	uint32 myChannelFailDefectsCount;
};

#endif /* MON_OCHMAINDEFECT_H */
