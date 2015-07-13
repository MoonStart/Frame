//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OMSDEFECT_H
#define MON_OMSDEFECT_H

#include "MON_Defects.h"


//This class hold the defect values for the OMS layers (amplifiers).
class MON_OmsDefects :public MON_Defects
{
public:

    //Constructor.
    MON_OmsDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OmsDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //True if OMS_LOS is detected.
    bool myLOSState;

    //Number of OMS_LOS defect rising transition.
    uint32 myLOSCount;

    //True if Aplifier Power Reduce is detected.
	bool myAprState;

	//Number of OMS_APR defect rising transition.
	uint32 myAprCount;

    //True if Port to Line OSC_LOS is detected.
    bool myAltLOSState;

    //Number of Port to Line OSC_LOS defect rising transition.
    uint32 myAltLOSCount;
   
    //True if Alternate 2 LOS is detected.
    bool myAltTwoLOSState;

    //Number Alternate 2 LOS defect rising transition.
    uint32 myAltTwoLOSCount;

    //True if Alternate 3 LOS is detected.
    bool myAltThreeLOSState;

    //Number of Alternate 3 LOS defect rising transition.
    uint32 myAltThreeLOSCount;

    //True if there is a OMS-LOS or both pump are closed.
    bool myLOSAfterAmpliState;

    //Number LOS After Ampli defect rising transition.
    uint32 myLOSAfterAmpliCount;

    bool myOutputPowerLimitedState;
    uint32 myOutputPowerLimitedCount;
    
    //Optical power overload defect state and count
    bool myOpovldState;
    uint32 myOpovldCount;

    //Aggregate output power exceeded
    bool myAopeState;
    uint32 myAopeCount;

};

#endif /* MON_OMSDEFECT_H */
