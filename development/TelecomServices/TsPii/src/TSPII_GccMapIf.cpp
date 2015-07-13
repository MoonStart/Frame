/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Jessica Chen - April 2011
 DESCRIPTION:Definition of the class TSPII_GccMapIf -  
             Provides the interface for Gcc Map.
 MODIFIED : 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_GccMapIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"


bool gTspiiGccMapAddDeleteDebug = false;    // log Add Delete events.
///////////////////////////////////////////////////////////////////////////////
TSPII_GccMapIf::TSPII_GccMapIf(bool theDefault,
                               uint16 theNumGccs) :
    TSPII_BaseIf(theDefault),
    itsNumGccs(theNumGccs),   
    itsCommitted(itsDummyBuf)     // initially force a pointer to a dummy something
{
    itsCommitted.erase(itsCommitted.begin(), itsCommitted.end());   // Erase the vector
    itsGCCProcessEnable = false;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_GccMapIf::~TSPII_GccMapIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::RefreshGet()
{   
    // Configuration attributes 
    itsGCCProcessEnable = GetGCCProcessEnabled();  
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::RefreshSet()
{   
    // Configuration attributes
    SetGCCProcessEnabled(itsGCCProcessEnable); 
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::UpdateValues()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::Reset()
{
    // Configuration attributes
    itsGCCProcessEnable =false;       
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::AddGccMap(const TSPII_GccMapRecord & theMap)
{
    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::DeleteGccMap(const TSPII_GccMapRecord & theMap)
{
    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::DeleteAllGccMaps()
{
    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::SetGCCProcessEnabled(bool theEnable)
{
    itsGCCProcessEnable = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccMapIf::GetGCCProcessEnabled() const
{
    return itsGCCProcessEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool   TSPII_GccMapIf::GetGccMapFromGccIndex(uint16 theGccIndex,TSPII_GccMapRecord & theMap)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool  TSPII_GccMapIf::GetGccMapsFromGccType(CT_GCC_Type theGccType,vector<TSPII_GccMapRecord> & theMaps)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_GccMapIf::WriteObjectBinary(FC_Stream & theStream)
{
    int      aMapCount;
    char     aMapStr[256];
    vector<TSPII_GccMapRecord>::iterator aIter;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // write out the size of the list of committed Gcc Maps
    aMapCount = itsCommitted.size();
    theStream << aMapCount;                // Committed

    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        // Write out each Map record as a comma seperated string
        sprintf(aMapStr, "%08d,%8s,%08d,%08d",aIter->GccIndex, 
                                                  DISPLAY_CT_GCC_Type(aIter->GccType),
                                                  aIter->OduIndex,
                                                  aIter->OduKLevel);
        theStream << aMapStr;
    }
    
    // Configuration
    theStream << itsGCCProcessEnable;
    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_GccMapIf::ReadObjectBinary(FC_Stream & theStream)
{
    int            aMapCount;
    char           aMapStr[256];
    TSPII_GccMapRecord aMap;

    // Delete all the current crossconnects
    DeleteAllGccMaps();

    // read in the list size
    theStream >> aMapCount;

    // The timeslot list must be converted from a char string to a vector
    while (aMapCount > 0)
    {
        // Read each Map record as a comma seperated string - write to driver. 
        theStream >> aMapStr;
        aMap.GccIndex   = (uint16) atoi(strtok(aMapStr, ","));
        aMap.GccType     = TSPII_GCC_TYPE_GET(strtok(NULL, ","));
        aMap.OduIndex  = (uint16) atoi(strtok(NULL, ","));
        aMap.OduKLevel  = (uint16) atoi(strtok(NULL, ","));
      
        AddGccMap(aMap);
        aMapCount--;
    }

    // Configuration
    theStream >> itsGCCProcessEnable;
    // Update H/W
    RefreshSet();
    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_GccMapIf::WriteObject(ostream & theStream)
{
    int      aMapCount;
    char     aMapStr[256];
    vector<TSPII_GccMapRecord>::iterator aIter;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // write out the sizes of each of the three lists
    aMapCount = itsCommitted.size();
    theStream << FC_InsertVar(aMapCount);

    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        // Write out each Map record as a comma seperated string
        sprintf(aMapStr, "%08d,%8s,%08d,%08d", aIter->GccIndex,  
                                                   DISPLAY_CT_GCC_Type(aIter->GccType),
                                                   aIter->OduIndex,
                                                   aIter->OduKLevel);
        theStream << FC_InsertVar(aMapStr);
    }
     // Configuration
    theStream <<FC_InsertVar(itsGCCProcessEnable);
    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_GccMapIf::ReadObject(istream & theStream)
{
    int            aMapCount;
    char           aMapStr[256];    // big to avoid overflow
    TSPII_GccMapRecord aMap;

    // Delete all the current crossconnects
    DeleteAllGccMaps();

    // read in the list size
    theStream >> FC_ExtractVar(aMapCount);
    
    // The timeslot list must be converted from a char string to a vector
    while (aMapCount > 0)
    {
        // Read each Map record as a comma seperated string - write to driver. 
        theStream >> FC_ExtractVar(aMapStr);
        aMap.GccIndex   = (uint16) atoi(strtok(aMapStr, ","));
        aMap.GccType     = TSPII_GCC_TYPE_GET(strtok(NULL, ","));
        aMap.OduIndex  = (uint16) atoi(strtok(NULL, ","));
        aMap.OduKLevel  = (uint16) atoi(strtok(NULL, ","));      
        
        AddGccMap(aMap);
        aMapCount--;
    }

    // Configuration
    theStream >>FC_ExtractVar(itsGCCProcessEnable);
    // Update H/W
    RefreshSet();
    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::Display(FC_Stream & theStream)
{   
    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapIf::Display(FC_Stream & theStream, int argc, char ** argv)
{
    int      aMapCount;
    char     aOutBuf[256];
    int      aIndex;
    
    uint16   aGccIndex = TSPII_GCCMAP_NOT_IN_USE;
    CT_GCC_Type   aGccType = CT_GCC_UNKNOWN;
    bool     aGccTypeall = false;
    bool     aGccIndexall = false;
    
    bool     aDisplayUsage = true;
    bool     aMatch;
    TSPII_GccMapRecord   aaMap;

    // Update H/W
    UpdateValues();
    RefreshGet();

    if((argc>=1)&&(strcmp(argv[0],"all")==0))
    {//no need to check GccType
        aGccTypeall = true;
        aDisplayUsage = false;
    }
   
    if(argc==1)
    {//"tspii display gccmap gcc0" is for only show "gcc0" related items, no need to check GccIndex   

        if((argv[0][0]=='a')||(argv[0][0] =='A'))
        {// "tspii display gccmap all"
            aGccTypeall = true;
        }
        else
        { //"tspii display gccmap gcc0"           
            aGccType = TSPII_GCC_TYPE_GET(argv[0]);
        }
        
        //no need to check GccIndex
        aGccIndexall = true;
        aDisplayUsage = false;
    }    
    else if (argc >=2)
    {//"tspii display gccmap gcc0 1" for only show "gcc0" and "gccindex=1" related item
     //"tspii display gccmap all 1" for only show "gccindex=1" related items
        aGccType = TSPII_GCC_TYPE_GET(argv[0]);
        aGccIndex   = static_cast<unsigned int>(strtoul(argv[1], NULL, 0));
        if ((aGccIndex < itsNumGccs) )
        {
            aDisplayUsage = false;
        }
    }


    if (aDisplayUsage)
    {
        fc_cout << "Usage: tspii display gccmap                           - a command list\n"
                   "       tspii display gccmap <type>                    - type <gcc0|gcc1|gcc2|gcc1+2|unknown|all>\n"
                   "       tspii display gccmap <type> <gccindex>         - [0 Based] gccindex = the GCC Channel[0~" << itsNumGccs-1 << "]  \n\n"                 
                << endl;
        return;
    }

    theStream << "  GCC Map Configuration/Status" << endl;

    aMapCount = itsCommitted.size();
    theStream << "       itsNumGccs  : " << itsNumGccs << endl;    
    theStream << "       itsCommitted: " << aMapCount << endl;    
    theStream << "                 GCCIndex, GCCType, OduIndex,OduKLevel " << endl;
    theStream << "----------------------------------------------------------" << endl;
    
    aIndex = 0;


    for (aIndex = 0; aIndex < itsNumGccs; aIndex++)
    {
        if(GetGccMapFromGccIndex(aIndex,aaMap))
        {
             aMatch = true;

             if ((!aGccIndexall)&&(aGccIndex != TSPII_GCCMAP_NOT_IN_USE)&&(aGccIndex != aaMap.GccIndex ))
             {//if aGccIndexall==true, no need to check GccIndex
                aMatch = false;
             }
             if ((!aGccTypeall)&&(aGccType != aaMap.GccType ))
             {// if aGccTypeall==true, no need to check GccType
                aMatch = false;
             }   
                 

             if(aMatch == true)
             {
                // If this Gcc Map matches the filter -
                // write out each Map record as a comma seperated string
                // all values are "0" based
                sprintf(aOutBuf, "%8d,%8s,%8d,%8d ", aaMap.GccIndex,  
                DISPLAY_CT_GCC_Type(aaMap.GccType), aaMap.OduIndex, aaMap.OduKLevel);
                theStream << "                 " << aOutBuf << endl;
             }                    
            
        }
    }
    theStream << "----------------------------------------------------------" << endl; 
    theStream << "      GCC Process Enabled  = " << TEXT_ON_OFF(itsGCCProcessEnable)       << "\n";
  
   // TSPII_BaseIf::Display(theStream);
} 

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccMapIf::Set(int argc, char ** argv)
{    TSPII_GccMapRecord   aMap;
    char             aOutBuf[256];
    bool             aDisplayUsage = true;    


    if (((argc == 2) && (strcmp(argv[0], "add") == 0)) ||
        ((argc == 3) && (strcmp(argv[0], "add") == 0)))
    {
        // Read the Map record as a comma seperated string. 
        if (strlen(argv[1]) < 256)
        {
            strcpy(aOutBuf, argv[1]);
            strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
            aMap.GccIndex   = (uint16) atoi(strtok(aOutBuf, ","));
            aMap.OduIndex  = (uint16) atoi(strtok(NULL, ","));
            aMap.OduKLevel  = (uint16) atoi(strtok(NULL, ","));
            
            aMap.GccType = CT_GCC_UNKNOWN;   // default type
            if(gTspiiGccMapAddDeleteDebug == true)
            {
                fc_cout << "Set---input: GccIndex = " << aMap.GccIndex << ",GccType = " << DISPLAY_CT_GCC_Type(aMap.GccType) << ", OduIndex = " << aMap.OduIndex << ",OduKLevel = " << aMap.OduKLevel << ". " << endl;
            }
            if((aMap.GccIndex >= 0) && (aMap.GccIndex <itsNumGccs) )
            {
                // don't need to Convert it, because it is "0" based numbering 
                
                if(argc == 3)
                {
                    // If a third argument it is the type
                    aMap.GccType = TSPII_GCC_TYPE_GET(argv[2]);
                }
                if(gTspiiGccMapAddDeleteDebug == true)
                {
                  fc_cout << "Set---input---: GccIndex = " << aMap.GccIndex << ",GccType = " << DISPLAY_CT_GCC_Type(aMap.GccType) << ", OduIndex = " << aMap.OduIndex << ",OduKLevel = " << aMap.OduKLevel << ". " << endl;
                }
                AddGccMap(aMap);
                aDisplayUsage =  false;
           }
       } 
    }
    else if (((argc == 2) && (strcmp(argv[0], "delete") == 0)) ||
             ((argc == 3) && (strcmp(argv[0], "delete") == 0)))
    {
        if (strlen(argv[1]) < 256)
        {
            // Read the Map record as a comma seperated string. 
            strcpy(aOutBuf, argv[1]);
            strcat(aOutBuf, ",0,0,0,");    // force some tokens in the string.
            aMap.GccIndex   = (uint16) atoi(strtok(aOutBuf, ","));
            aMap.OduIndex  = (uint16) atoi(strtok(NULL, ","));
            aMap.OduKLevel  = (uint16) atoi(strtok(NULL, ","));
           
            aMap.GccType = CT_GCC_UNKNOWN;   // default type
            if(aMap.OduKLevel >= 0)
            {
                // don't need to Convert it, because it is "0" based numbering 
                
                if(argc == 3)
                {
                    // If a third argument it is the type
                    aMap.GccType = TSPII_GCC_TYPE_GET(argv[2]);
                }
                DeleteGccMap(aMap);
                aDisplayUsage =  false;
           }
       } 
    } 
    else if((argc == 2) && (strcmp(argv[0], "getfromindex") == 0))
    {   
        uint16 aGccIndex=static_cast<unsigned int>(strtoul(argv[1], NULL, 0));
        
        if(aGccIndex < itsNumGccs)
        {
            if(GetGccMapFromGccIndex(aGccIndex,aMap))
            {
                fc_cout << "                 GCCIndex, GCCType, OduIndex,OduKLevel " << endl;
                fc_cout << "----------------------------------------------------------" << endl;
                // We have a match
                // Write out each Map record as a comma seperated string
                // all values are "0" based
                sprintf(aOutBuf, "%8d,%8s,%8d,%8d ", aMap.GccIndex,  
                    DISPLAY_CT_GCC_Type(aMap.GccType), aMap.OduIndex, aMap.OduKLevel);
               fc_cout  << "                 " << aOutBuf << endl;                       
            
            }
            else
            {
                fc_cout << "No match found" << endl;
            }
            aDisplayUsage =  false;
        }        
    }
    else if((argc == 2) && (strcmp(argv[0], "getfromtype") == 0))
    {
        CT_GCC_Type aGccType = TSPII_GCC_TYPE_GET(argv[1]);
        vector<TSPII_GccMapRecord> aMaps;

        vector<TSPII_GccMapRecord>::const_iterator aIter;
        if(GetGccMapsFromGccType(aGccType,aMaps)== true)
        {
            if(aMaps.size() >= 1)
            {
                fc_cout << "                 GCCIndex, GCCType, OduIndex,OduKLevel " << endl;
                fc_cout << "----------------------------------------------------------" << endl;
                
                for(aIter=aMaps.begin(); aIter != aMaps.end(); ++aIter)
                {
                    // We have a match
                    // Write out each Map record as a comma seperated string
                    // all values are "0" based
                    sprintf(aOutBuf, "%8d,%8s,%8d,%8d ",aIter->GccIndex,  
                      DISPLAY_CT_GCC_Type(aIter->GccType), aIter->OduIndex, aIter->OduKLevel);
                    fc_cout<< "                 " << aOutBuf << endl;                     
                   
                } 
            }
            aDisplayUsage =  false;
        }
    }
    else if ((argc == 1) && (strcmp(argv[0], "deleteall") == 0))
    {
        DeleteAllGccMaps();
        aDisplayUsage =  false;
    }
     
    else if ((argc == 2) && strcmp(argv[0], "setgccprocessenable") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetGCCProcessEnabled(true);
            aDisplayUsage =  false;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetGCCProcessEnabled(false);
            aDisplayUsage =  false;
        }       
    }
 
    else
    {
        aDisplayUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (aDisplayUsage)
    {
        fc_cout << "Usage: tspii setgccmap add <gccindex,oduindex,oduklevel>[0 Based] <type>\n"
                   "                           - gccindex = the GCC Channel[0~31] for GCC Channel 1~32.  \n"
                   "                           - oduindex = the odu pool Index: 0~31 for ODU1 32 instances,\n"
                   "                                                            0~7  for ODU2 8 instances,\n "
                   "                                                            0~63 for ODU0 64 instances.\n"
                   "                           - oduklevel = the oduklevel [0~2]  for ODU0,ODU1,ODU2 \n"
                   "                           - type      = <gcc0|gcc1|gcc2|gcc1+2|unknown>\n"   
                   "                       delete <gccindex,oduindex,oduklevel>[0 Based] <type=optional>\n"
                   "                       deleteall\n"                  
                   "                       getfromindex         <gccindex>   -[0~31] for GCC Channel 1~32.\n"
                   "                       getfromtype          <type>       -<gcc0|gcc1|gcc2|gcc1+2|unknown>\n"
                   "                       setgccprocessenable  <on|off>\n"
                   << endl;

      
    }   

    return (!aDisplayUsage);
}
    


