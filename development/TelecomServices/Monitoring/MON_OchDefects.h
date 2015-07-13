//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OCHDEFECT_H
#define MON_OCHDEFECT_H

#include "MON_Defects.h"


//This class contains the defects status and transition 
//counts for the Och layer. It can apply to the line side.
class MON_OchDefects :public MON_Defects
{

public:

	//Constructor.
    MON_OchDefects(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_OchDefects(void);

    bool IsLayerInDefects() const;

    //Returns the status and count of the defect provide as argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool SetDetectedId(MON_RelativeTraceId theRelTraceId);
    MON_RelativeTraceId GetDetectedId() const;

    //This method is used to force the Loss Of Ptone to OFF.
    void DisableLos(bool theDisableLos);
    
    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //True if debug trace is detected.
	bool myDebugTraceDetected;

	//Current number of rising transition of the debug trace detected defect.
	uint32 myDebugTraceDetectedCount;

    //True if there is no pilot tone detected
	bool myLossOfPilotTone;

	//Current number of rising transition of the Loss of pilot tone power defect.
	uint32 myLossOfPilotToneCount;

    MON_RelativeTraceId myDetectedTraceId;

    //Debug attributes
    bool myDisableLos; // True if Loss Of Ptone is forced to off

};

#endif /* MON_OCHDEFECT_H */
