/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        CFG_CmmOosAutomatic.h
 *    DATE:          11/16/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Configuration
 *    OVERVIEW:      CMM Out-of-service object
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#ifndef __CFG_CMMOOSAUTOMATIC_H__
#define __CFG_CMMOOSAUTOMATIC_H__

#include "CFG_Object.h"
#include <CommonTypes/CT_Telecom.h>

class CFG_CmmOosAutomatic : public CFG_Object
{
public:
    /* Constructor */   CFG_CmmOosAutomatic(uint32 theIndex);
    virtual             ~CFG_CmmOosAutomatic();

    // -----------------------------------------------------------------------------------
    // Access methods
    // -----------------------------------------------------------------------------------
    bool                GetAmplifierShutdown() const;

    // -----------------------------------------------------------------------------------
    // Control methods
    // -----------------------------------------------------------------------------------
    bool                SetAmplifierShutdown(bool theState);

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   & WriteObject(ostream & theStream);
    virtual istream   & ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Menus
    // -----------------------------------------------------------------------------------
    virtual void        Menu(int argc, char ** argv);
    virtual void        Display(FC_Stream& theStream);

private:
    bool                myAmplifierShutdown;
};

#endif /* __CFG_CMMOOSAUTOMATIC_H__ */
