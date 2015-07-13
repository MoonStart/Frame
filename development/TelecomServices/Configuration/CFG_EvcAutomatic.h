/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_EVCAUTOMATICOBJECT_H
#define CFG_EVCAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration 
//for one port.
class CFG_EvcAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_EvcAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_EvcAutomatic(void);


    //This method sets the current state of AIS-L force.
    bool SetForceAIS(bool theForceAIS, unsigned int theEvcIdx);

    //This method returns the current state of AIS-L force.
    bool GetForceAIS(unsigned int theEvcIdx) const;


    //This method will set the Index of the GFP for a given Port
    bool SetGfpIdx(uint8 theGfpIdx, uint8 thePortIdx);

    //This method will return the value of the GFP for a given Port
    uint8 GetGfpIdx(uint8 thePortIdx) const;

    //This method will set the Index of the Port for a given Gfp
    bool SetPortIdx(uint8 thePortIdx, uint8 theGfpIdx);

    //This method will return the value of the Port for a given Gfp
    uint8 GetPortIdx(uint8 theGfpIdx) const;


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
    bool myForceAIS[CT_TEL_NBR_OF_EVCS];

    // Port to GFP array
    uint8 myGfpIdx[CT_TEL_NBR_OF_ETH_PORTS];

     // GFP to Port array
    uint8 myPortIdx[CT_TEL_NBR_OF_GFPS];

};

#endif /* CFG_EVCAUTOMATICOBJECT_H */

