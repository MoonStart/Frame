#ifndef TSPII_GCCMAPIMIF_H
#define TSPII_GCCMAPIMIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  WIN32 - Gcc Map
 AUTHOR   :  Jessica Chen - April 2011
 DESCRIPTION:Specialized class for the Gcc Map implementation
             in the win32 simulation environment.
 MODIFIED :
--------------------------------------------------------------------------*/



#include "TsPii/TSPII_GccMapIf.h"

class TSPII_GccMapLuTblRecord
{
public:
//  uint16        GccIndex;     //Gcc Index - "0" based,used as the index of the table 
    CT_GCC_Type   GccType;      // Gcc Type
    uint16        OduIndex;     // Odu Index - "0" based
    uint16        OduKLevel;    // OduK Level - "0" based

    TSPII_GccMapLuTblRecord()
    {
        GccType=CT_GCC_UNKNOWN;  OduIndex=0; OduKLevel=0;
    }
};

class TSPII_GccMapSimIf : public TSPII_GccMapIf
{
public:

    /* Constructor */           TSPII_GccMapSimIf(uint16 theNumGccs);
    virtual                     ~TSPII_GccMapSimIf();

    virtual void                Reset();

                                // Add a single Gcc Map
    virtual void                AddGccMap(const TSPII_GccMapRecord & theMap);

                                // Delete a single Gcc Map
    virtual void                DeleteGccMap(const TSPII_GccMapRecord & theMap);

                                // Delete all the Gcc Maps
    virtual void                DeleteAllGccMaps();
                               
                                // Get the Gcc Map given the Gcc Index
    virtual bool                GetGccMapFromGccIndex(uint16 theGccIndex,TSPII_GccMapRecord & theMap);

                                // Get the list of Gcc Maps given Gcc Type
    virtual bool                GetGccMapsFromGccType(CT_GCC_Type theGccType,vector<TSPII_GccMapRecord> & theMaps);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual bool                Simul(int argc, char ** argv);
private:

    TSPII_GccMapLuTblRecord     *itsLuTbl;         // Simulation Gcc Map lookup table
    
};

#endif // TSPII_GCCMAPIMIF_H
