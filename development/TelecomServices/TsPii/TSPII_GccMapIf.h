#ifndef _TSPII_GCCMAPIF_H
#define _TSPII_GCCMAPIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Jessica Chen - April 2011
 DESCRIPTION:Base class for the hardware independent interface. 
             Provides the interface for Gcc Map.
 MODIFIED :  
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"
#include "CommonTypes/CT_Telecom.h"
#include "CommonTypes/CT_OduDefinitions.h"
#include "CommonTypes/CT_DCC_Definitions.h"


// Macro to convert input string into Gcc Map Type
// PLEASE KEEP THIS IN SYNCH WITH THE DISPLAY MACRO ABOVE
#define TSPII_GCC_TYPE_GET(type) \
    ((strcmp(type, "gcc0") == 0)  ? CT_GCC_0 : \
    (strcmp(type, "gcc1") == 0)   ? CT_GCC_1 : \
    (strcmp(type, "gcc2") == 0)   ? CT_GCC_2 : \
    (strcmp(type, "gcc1+2") == 0) ? CT_GCC_1_2 : CT_GCC_UNKNOWN)
// This class describes one gcc map

const uint16  TSPII_GCCMAP_NOT_IN_USE = 0xFFFF;

class TSPII_GccMapRecord
{
public:   
    uint16        GccIndex;     // Gcc Index - "0" based
    CT_GCC_Type   GccType;      // Gcc Type
    uint16        OduIndex;     // Odu Index - "0" based
    uint16        OduKLevel;    // OduK Level - "0" based
    

    TSPII_GccMapRecord()
    {
       GccIndex=0; GccType=CT_GCC_UNKNOWN;  OduIndex=0; OduKLevel=0; 
    }

    void Clear()
    {
       GccIndex=0; GccType=CT_GCC_UNKNOWN;  OduIndex=0; OduKLevel=0; 
    }

    void operator=(const TSPII_GccMapRecord &right)
    {
        this->GccIndex = right.GccIndex;
        this->GccType  = right.GccType;        
        this->OduIndex = right.OduIndex;
        this->OduKLevel= right.OduKLevel;        
    }

    bool operator==( const TSPII_GccMapRecord &right) const
    {
        if((this->GccIndex    == right.GccIndex) &&
           (this->GccType     == right.GccType)  &&           
           (this->OduIndex    == right.OduIndex) &&
           (this->OduKLevel   == right.OduKLevel))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class TSPII_GccMapIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */                 TSPII_GccMapIf(bool theDefault = false, 
                                                     uint16 theNumGccs = 0);
    virtual                           ~TSPII_GccMapIf();
    virtual void                      Reset();
    virtual void                      UpdateValues();
   

    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
                                      // Add a single gcc map
    virtual void                      AddGccMap(const TSPII_GccMapRecord & theMap);

                                      // Delete a single gcc map
    virtual void                      DeleteGccMap(const TSPII_GccMapRecord & theMap);

                                      // Delete all the gcc maps
    virtual void                      DeleteAllGccMaps();
                                     
                                      // Get the Gcc Map given the Gcc Index
    virtual bool                      GetGccMapFromGccIndex(uint16 theGccIndex,TSPII_GccMapRecord & theMap);

                                      // Get the list of Gcc Maps given Gcc Type
    virtual bool                      GetGccMapsFromGccType(CT_GCC_Type theGccType,vector<TSPII_GccMapRecord> & theMaps);
   
    virtual void                      SetGCCProcessEnabled(bool theEnable);
    virtual bool                      GetGCCProcessEnabled() const;

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                      Set(int argc, char ** argv);
   
protected:

    void                              RefreshGet();
    void                              RefreshSet();

   
    
    // Configuration attributes 
    uint16                            itsNumGccs; // the maximum of GCC Channel in this smart card
    bool                              itsGCCProcessEnable;
    vector<TSPII_GccMapRecord> &      itsCommitted;      // Reference to the HW committed list
    vector<TSPII_GccMapRecord>        itsDummyBuf;

    
};

#endif // TSPII_GCCMAPIF_H
