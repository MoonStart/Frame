/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OPTAUTOMATICOBJECT_H
#define CFG_OPTAUTOMATICOBJECT_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"

//This object contains all the generic optical configuration for one port.
class CFG_OptAutomatic 
: public CFG_Object
{

public:

    //Constructor.
    CFG_OptAutomatic(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OptAutomatic(void);


    //This method sets the current state of laser.
    bool SetAutomaticLaserShutdown(bool theLaserShutdown);

    //This method returns the current state of laser.
    bool GetAutomaticLaserShutdown() const;


    //This method sets the current state of laser.
    bool SetNearEndAutomaticLaserShutdown(bool theNearEndLaserShutdown);

    //This method returns the current state of laser.
    bool GetNearEndAutomaticLaserShutdown() const;


    //This method allows enabling or disabling the Line Side 
    //Protection. This is set to true (on the line side facility only)
    //when the line side facility is involed in protection. This 
    //will be used to disable generation of AIS-L (internal and external)
    //in the line to port direction
    bool SetLineSideProtExists(bool theLineSideProtExists);

    //This method allows retrieving the state of the Line Side 
    //Protection: enabled or disabled.
    bool GetLineSideProtExists() const;

    // This method set/clear the Fefi mode
    bool SetForceFefi(bool theForceFefi);

    //This method retrieves the FEFI mode
    bool GetForceFefi() const;


    //Debug methods
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //Set to true to disbale laser.
    bool myLaserShutdown;

    //Set to true to disbale near end laser.
    bool myNearEndLaserShutdown;

    //The Line Side Protection Exists.
    bool myLineSideProtExists;

    // set to indicate Force FEFI
    bool myForceFefi;
};

#endif /* CFG_OPTAUTOMATICOBJECT_H */

