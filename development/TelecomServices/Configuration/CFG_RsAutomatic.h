/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_RSAUTOMATICOBJECT_H
#define CFG_RSAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_RsAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_RsAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_RsAutomatic(void);

    //This method sets the current state of AIS-L force.
    bool SetForceAIS(bool theForceAIS);

    //This method returns the current state of AIS-L force.
    bool GetForceAIS() const;

    // This method sets the current state of internal AIS-L force
    bool SetForceAISInternal(bool theForceAISInternal);

    //This method returns the current state of internal AIS-L force.
    bool GetForceAISInternal() const;

    // This method sets the current state of RDI-L force
    bool SetForceRDI(bool theForceRDI);

    //This method returns the current state of RDI-L force.
    bool GetForceRDI() const;

    // This method sets the current state of Internal CSF OPU force
    bool SetForceCSFOPUInternal(bool theForceCSFOPUInternal);

    //This method returns the current state of Internal CSF OPU force.
    bool GetForceCSFOPUInternal() const;

	//This method allows enabling or disabling the Line Side 
    //Protection. This is set to true (on the line side facility only)
    //when the line side facility is involed in protection. This 
    //will be used to disable generation of AIS-L (internal and external)
    //in the line to port direction
    bool SetLineSideProtExists(bool theLineSideProtExists);

    //This method allows retrieving the state of the Line Side 
    //Protection: enabled or disabled.
    bool GetLineSideProtExists() const;

    //This method will set the Suppress Backward Indicator attribute
    bool SetSuppressBackwardInd(bool theSuppressBackwardInd);

    //This method will return the value Suppress Backward Indicator attribute
    bool GetSuppressBackwardInd() const;

    //This method will set the 1 Way Drop XC attribute
    bool SetDrop(bool theDrop);

    //This method will return the value 1 Way Drop XC attribute
    bool GetDrop() const;

    //This method will set the 1 Way Add XC attribute
    bool SetAdd(bool theDrop);

    //This method will return the value 1 Way Add XC attribute
    bool GetAdd() const;

    //This method sets the indication type for the maintenance signal.
    void SetAutoIndicationType(CT_RS_IndicationType theIndicationType);

    //This method retrieves  the indication type for the maintenance signal.
    CT_RS_IndicationType GetAutoIndicationType() const;

    //This method sets the internal indication type for the maintenance signal.
    void SetAutoInternalIndType(CT_RS_IndicationType theIndicationType);

    //This method retrieves the internal indication type for the maintenance signal.
    CT_RS_IndicationType GetAutoInternalIndType() const;

    //This method resets all attributes to their default value.
    virtual void Reset(void);

    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // Set to true to enable AIS
    bool myForceAIS;
    // Set to true to enable AIS internal
    bool myForceAISInternal;
    // Set to true to enable RDI 
    bool myForceRDI;
    // Set to true to enable Internal CSF OPU 
    bool myForceCSFOPUInternal;
	// The Line Side Protection Exists.
    bool myLineSideProtExists;
    // The Suppress Backward Indicators Exists
    bool mySuppressBackwardInd;
    // 1 Way Drop XC
    bool myAdd;
    // 1 Way Add XC
    bool myDrop;
    //The indication type for the maintenance signal configured
    CT_RS_IndicationType myAutoIndicationType;
    //The internal indication type for the maintenance signal configured
    CT_RS_IndicationType myAutoInternalIndType;

};

#endif /* CFG_RSAUTOMATICOBJECT_H */

