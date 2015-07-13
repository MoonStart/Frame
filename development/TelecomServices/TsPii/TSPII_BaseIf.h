/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : Generic
 AUTHOR      : Martin Piotte, 2002/12/19
 DESCRIPTION : Base class for the hardware independent interface.  
--------------------------------------------------------------------------*/

#ifndef TSPII_BASEIF_H
#define TSPII_BASEIF_H

#include "Blackboard/FC_BbObject.h"

#define TSPII_DEFECT(count) (((count) & 1) != 0)

extern const char* gTspiiSlotName[];
extern const char* gTspiiPumpName[];

class TSPII_BaseIf : public FC_BbObject
{
    friend class TSPII_UpdateAction;

public:
    
    TSPII_BaseIf(bool theDefault = false);
    virtual ~TSPII_BaseIf();
    virtual void Reset();

    // -----------------------------------------------------------------------------------
    // Base methods
    // -----------------------------------------------------------------------------------
    bool IsDefault() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   & WriteObject(ostream & theStream);
    virtual istream   & ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    virtual void UpdateValues();

    bool itsDefault;
};

#endif // TSPII_BASEIF_H
