/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTUOBJECT_H
#define CFG_OTUOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"
#include <CommonTypes/CT_G709Trace.h>

//This object contains all the generic OTU (Optical Channel 
//Transport Unit) configuration for one port.
class CFG_Otu 
: public CFG_Object
{

public:
	//Constructor.
    CFG_Otu(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Otu(void);

	//This method sets the value of the 'sent Trace' in the 
	//TTI byte of the OTU (Optical Channel Transport Unit) layer.
	bool SetSentTrace(const CT_G709Trace& theSentTrace);
    bool DeleteSentTrace();

	//This method returns the set value of the 'sent Trace' 
	//in the TTI byte of the OTU (Optical Channel Transport Unit) layer.
    CT_G709Trace & GetSentTrace() const;

	//This method enables or not the FEC (Forward Error 
	//Correction) correction.
    bool SetEnableFECCorrection(bool theEnableFECCorrection);

    //This method returns the current state (enabled or 
	//disabled) of the FEC (Forward Error Correction) correction.
    bool GetEnableFECCorrection() const;

	//This method force the insertion of errors
    bool SetForceErrorInsertion(bool theForceErrorInsertion);

    //This method returns the current state (enabled or 
	//disabled) of Force Error Insertion.
    bool GetForceErrorInsertion() const;

	//This method enables or not the Super FEC capability
    bool SetEnableSuperFEC(bool theEnableSuperFEC);

    //This method returns the current state (enabled or 
	//disabled) of the Super FEC capability.
    bool GetEnableSuperFEC() const;


    //This method sets the force generation of OTU-AIS 
	//maintenance signal (ON or OFF).
    //(DEBUG PURPOSE ONLY)
	bool SetForceAIS(bool theForceAIS);

	//This method returns the setting (ON or OFF) of the 
	//force generation of OTU-AIS maintenance signal.
    //(DEBUG PURPOSE ONLY)
	bool GetForceAIS() const;


    //This method sets the Bursty BerSd number of inervals
    bool SetBurstyBerSdIntervals(uint16 theIntervals);

    //This method returns the Bursty BerSd number of inervals
    uint16 GetBurstyBerSdIntervals() const;

    //This method sets the Bursty BerSd threshold of errored blocks
    bool SetBurstyBerSdThreshold(uint32 theThreshold);

    //This method returns the Bursty BerSd threshold of errored blocks
    uint32 GetBurstyBerSdThreshold() const;

    // This method sets the specific  FEC type    
    // In 7.1, changed the name of method from SetSuperFecType so that it would
    // be more generic.  OSM40 still expects only Super of SuperI7.
    // Other cards can now use SetFecType for all enums and eliminate the
    // need to use SetEnableFECCorrection and SetEnableSuperFEC.
    bool SetFECType(CT_TEL_FecType theFECType);

    //This method returns the specific FEC type    
    CT_TEL_FecType GetFECType() const;


    // Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//Trace message (including SAPI, DAPI and operator 
	//specific text) to transmit in the OTU overhead byte SM.
    CT_G709Trace* mySentTracePtr;
    bool myTraceInUse;

	//Set to true to force generation of OTU-AIS maintenance signal.
	bool myForceAIS;

	//Set to true to enable FEC (Forward Error Correction) correction.
    bool myEnableFECCorrection;

    //Set to true to enable error insertion
    bool myForceErrorInsertion;

    //Set to true to enable Super FEC capability
    bool myEnableSuperFEC;

    // Set Interval and Threshold for bursty BerSd monitoring
    uint16 myBurstyBerSdIntervals;
    uint32 myBurstyBerSdThreshold;

    // FEC type
    CT_TEL_FecType myFECType;

};

#endif /* CFG_OTUOBJECT_H */

