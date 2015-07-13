/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  WIN32 - GCC MAP
 AUTHOR   :  Jessica Chen - April 2011
 DESCRIPTION:Specialized implementation class of the Gcc Map entity for
             use in win32 simulation environment.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_GccMapSimIf.h"


///////////////////////////////////////////////////////////////////////////////
TSPII_GccMapSimIf::TSPII_GccMapSimIf(uint16 theNumGccs) :
    TSPII_GccMapIf(false, theNumGccs)
{
    
    // Dynamically allocate the memory for the Gcc Map Lookup table
    itsLuTbl = (TSPII_GccMapLuTblRecord *) malloc(sizeof(TSPII_GccMapLuTblRecord ) * itsNumGccs);
    

    itsCommitted.erase(itsCommitted.begin(), itsCommitted.end());  // initial clear
    Reset();        // this initializes the rest.
}

///////////////////////////////////////////////////////////////////////////////
TSPII_GccMapSimIf::~TSPII_GccMapSimIf()
{
    
    free(itsLuTbl);                 // release top level pointer table
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapSimIf::Reset()
{
    vector<TSPII_GccMapRecord>::iterator aIter;

    TSPII_BaseIf::Reset();      // Call base class

    DeleteAllGccMaps();          // Clears out the Look Up Table
    RefreshGet();               // Get the current Gcc Map list

    // Rebuild the itsLuTbl from the hardware view of crossconnects.
    for(aIter=itsCommitted.begin(); aIter != itsCommitted.end(); ++aIter)
    {
        itsLuTbl[aIter->GccIndex].GccType = aIter->GccType;
        itsLuTbl[aIter->GccIndex].OduIndex = aIter->OduIndex;
        itsLuTbl[aIter->GccIndex].OduKLevel = aIter->OduKLevel;
    }
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapSimIf::AddGccMap(const TSPII_GccMapRecord & theMap)
{

    if(theMap.GccIndex >= itsNumGccs)
    {
        // Out of range parameters - ignore
        return;
    }
    TSPII_GccMapRecord aMap;

    // Write the new Gcc Map in to the look up table. Replaces any previous
    // Gcc Map with the same destination port/timeslot. This is like an
    // automatic delete.
    itsLuTbl[theMap.GccIndex].GccType = theMap.GccType;
    itsLuTbl[theMap.GccIndex].OduIndex = theMap.OduIndex;
    itsLuTbl[theMap.GccIndex].OduKLevel = theMap.OduKLevel;     

    // Create a vector version of the internal lookup table.
    if (itsLuTbl[theMap.GccIndex].OduIndex != TSPII_GCCMAP_NOT_IN_USE)
    {
            aMap.GccType = itsLuTbl[theMap.GccIndex].GccType;
            aMap.OduIndex = itsLuTbl[theMap.GccIndex].OduIndex;
            aMap.OduKLevel = itsLuTbl[theMap.GccIndex].OduKLevel;
            aMap.GccIndex = theMap.GccIndex;                
            itsCommitted.push_back(aMap);
    }    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapSimIf::DeleteGccMap(const TSPII_GccMapRecord & theMap)
{

    if(theMap.GccIndex >= itsNumGccs) 
    {
        // Out of range parameters - ignore
        return;
    }

    uint16         OutGcc;
    TSPII_GccMapRecord aMap;

   if(GetGccMapFromGccIndex(theMap.GccIndex,aMap)&& (theMap.OduIndex == aMap.OduIndex) && (theMap.OduKLevel == aMap.OduKLevel))
   {
       // if found a match, then delete it.
       // Set the referenced Gcc Map to the look up table to NOT_IN_USE
       itsLuTbl[theMap.GccIndex].GccType = CT_GCC_UNKNOWN;
       itsLuTbl[theMap.GccIndex].OduIndex = TSPII_GCCMAP_NOT_IN_USE;
       itsLuTbl[theMap.GccIndex].OduKLevel = TSPII_GCCMAP_NOT_IN_USE;
   

       itsCommitted.erase(itsCommitted.begin(), itsCommitted.end());   // Erase the vector

       // Create a vector version of the internal lookup table.
       for (OutGcc = 0; OutGcc < itsNumGccs; OutGcc++)
       {
           if (itsLuTbl[OutGcc].OduIndex != TSPII_GCCMAP_NOT_IN_USE)
           {
               aMap.GccType = itsLuTbl[OutGcc].GccType;
               aMap.OduIndex = itsLuTbl[OutGcc].OduIndex;
               aMap.OduKLevel = itsLuTbl[OutGcc].OduKLevel;
               aMap.GccIndex = OutGcc;                
               itsCommitted.push_back(aMap);
           }
       }
   }    
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_GccMapSimIf::DeleteAllGccMaps()
{
    uint16 OutGcc; 

    // Clears out the Look Up Table
    for (OutGcc = 0; OutGcc < itsNumGccs; OutGcc++)
    {      
            // Set this crossconnect entry in the look up table to NOT_IN_USE
            itsLuTbl[OutGcc].GccType = CT_GCC_UNKNOWN;
            itsLuTbl[OutGcc].OduIndex = TSPII_GCCMAP_NOT_IN_USE;
            itsLuTbl[OutGcc].OduKLevel = TSPII_GCCMAP_NOT_IN_USE;  
    }    
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccMapSimIf::GetGccMapsFromGccType(CT_GCC_Type theGccType,
                                       vector<TSPII_GccMapRecord> & theMaps)
{
    uint16             OutGcc;    
    TSPII_GccMapRecord aMap;
    uint16             Count = 0;

    // Create a vector list of connections that match.
    for (OutGcc = 0; OutGcc < itsNumGccs; OutGcc++)
    {
       
            if (itsLuTbl[OutGcc].GccType == theGccType)
            {
                aMap.GccType = itsLuTbl[OutGcc].GccType;
                aMap.OduIndex = itsLuTbl[OutGcc].OduIndex;
                aMap.OduKLevel = itsLuTbl[OutGcc].OduKLevel;
                aMap.GccIndex = OutGcc;
               
                theMaps.push_back(aMap);
                Count++;
            }        
    }

    if(Count != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccMapSimIf::GetGccMapFromGccIndex(uint16 theGccIndex,
                                       TSPII_GccMapRecord & theMap)
{
    if(theGccIndex >= itsNumGccs) 
    {
        // Out of range parameters - ignore
        return false;
    }

    // check if this Input is mapped to an output
    if(itsLuTbl[theGccIndex].OduIndex != TSPII_GCCMAP_NOT_IN_USE)
    {
        theMap.GccType = itsLuTbl[theGccIndex].GccType;
        theMap.OduIndex = itsLuTbl[theGccIndex].OduIndex;
        theMap.OduKLevel = itsLuTbl[theGccIndex].OduKLevel;
        theMap.GccIndex = theGccIndex;
      
        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_GccMapSimIf::Simul(int argc, char ** argv)
{
    TSPII_GccMapRecord   aMap;
    char             aOutBuf[256];
    bool             aDisplayUsage = true;    

   
    if (((argc == 2) && (strcmp(argv[0], "add") == 0)) ||
        ((argc == 3) && (strcmp(argv[0], "add") == 0)))
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
            if((aMap.GccIndex >= 0) && (aMap.GccIndex <itsNumGccs) )
            {
                // don't need to Convert it, because it is "0" based numbering 
                
                if(argc == 3)
                {
                    // If a third argument it is the type
                    aMap.GccType = TSPII_GCC_TYPE_GET(argv[2]);
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
        TSPII_GccMapRecord   aaMap;
        if(aGccIndex < itsNumGccs)
        {
            if(GetGccMapFromGccIndex(aGccIndex,aaMap))
            {
                fc_cout << "                 GCCIndex, GCCType, OduIndex,OduKLevel " << endl;
                fc_cout << "----------------------------------------------------------" << endl;
                // We have a match
                // Write out each Map record as a comma seperated string
                // all values are "0" based
                sprintf(aOutBuf, "%8d,%8s,%8d,%8d ", aaMap.GccIndex,  
                    DISPLAY_CT_GCC_Type(aaMap.GccType), aaMap.OduIndex, aaMap.OduKLevel);
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
                    sprintf(aOutBuf, "%8d,%8s,%8d,%8d ", aIter->GccIndex,  
                      DISPLAY_CT_GCC_Type(aIter->GccType), aIter->OduIndex, aIter->OduKLevel);
                    fc_cout<< "                 " << aOutBuf << endl;
                     
                    
                } 
            }            
        }
        else
        {
                fc_cout << "No match found" << endl;
        }
        aDisplayUsage =  false;
    }
    else if ((argc == 1) && (strcmp(argv[0], "deleteall") == 0))
    {
        DeleteAllGccMaps();
        aDisplayUsage =  false;
    }       
    else
    {
        aDisplayUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (aDisplayUsage)
    {
        fc_cout << "Usage: tspii simgccmap add <gccindex,oduindex,oduklevel>[0 Based] <type>\n"
                   "                           - gccindex = the GCC Channel[0~31] for GCC Channel 1~32.  \n"
                   "                           - oduindex = the odu Index : 0~31 for ODU1 32 instances,\n"
                   "                                                        0~7  for ODU2 8 instances,\n "
                   "                                                        0~63 for ODU0 64 instances.\n"
                   "                           - oduklevel = the oduklevel [0~2]  for ODU0,ODU1,ODU2 \n"
                   "                           - type      = <gcc0|gcc1|gcc2|gcc1+2|unknown>\n"   
                   "                       delete <gccindex,oduindex,oduklevel>[0 Based] <type=optional>\n"
                   "                       deleteall\n"               
                   "                       getfromindex      <gccindex>   -[0~31] for GCC Channel 1~32.\n"
                   "                       getfromtype       <type>       -<gcc0|gcc1|gcc2|gcc1+2|unknown>\n"
                   << endl;
      
    }   
    return (!aDisplayUsage);
}
