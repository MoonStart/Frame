/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OTSOHOBJECT_H
#define CFG_OTSOHOBJECT_H

#include "CFG_Object.h"
#include "CommonTypes/CT_Telecom.h"
#include <vector>
using namespace std;

//This object contains all the generic OTS Overhead configuration for OTS line interface.
class CFG_OtsOH 
: public CFG_Object
{

public:
    //Constructor.
    CFG_OtsOH(uint32 theIndex);

    //Virtual destructor.
    virtual ~CFG_OtsOH(void);

    bool GetForceOtsPMI() const;
    void SetForceOtsPMI(bool theForceOTS_PMI);

    bool GetForceOmsFDIP() const;
    void SetForceOmsFDIP(bool theForceOMS_FDIP);

    bool GetForceOchOCI(uint8 theIndex) const;
    void SetForceOchOCI(bool theForceOCH_OCI, uint8 theIndex);

    bool GetForceOchFDIP(uint8 theIndex) const;
    void SetForceOchFDIP(bool theForceOCH_FDIP, uint8 theIndex);

	void SetEnablePMIGeneration(bool theMode);
	bool GetPMIGenerationEnabled();

    //Debug methods
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

    bool myForceOTS_PMI;
    bool myForceOMS_FDIP;
	bool myEnablePMIGen;
    vector<bool> myForceOCH_OCI;
    vector<bool> myForceOCH_FDIP;
};

#endif /* CFG_OTSOHOBJECT_H */

