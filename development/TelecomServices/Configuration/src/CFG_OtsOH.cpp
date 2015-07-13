//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OtsOH.h"
#include "BaseClass/FC_TextStream.h"
#include "ErrorService/FC_Error.h"
#include "CsPii/CSPII_SysCfgParamIF.h"
#include <string.h>

CFG_OtsOH::CFG_OtsOH(uint32 theIndex):
    CFG_Object(theIndex),
    myForceOTS_PMI(false),
    myForceOMS_FDIP(false),
    myForceOCH_OCI(CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY),
    myForceOCH_FDIP(CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY),
    myEnablePMIGen(false)
{
    for(uint16 i=0; i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        myForceOCH_OCI[i] = false;
        myForceOCH_FDIP[i] = false;
    }
}

CFG_OtsOH::~CFG_OtsOH(void)
{
}

void CFG_OtsOH::Reset(void)
{
    myForceOTS_PMI = false;
    myForceOMS_FDIP = false;
    myEnablePMIGen = false;
    for(uint16 i=0; i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        myForceOCH_OCI[i] = false;
        myForceOCH_FDIP[i] = false;
    }
}

bool CFG_OtsOH::GetForceOtsPMI() const
{
    return myForceOTS_PMI;
}

void CFG_OtsOH::SetForceOtsPMI(bool theForceOTS_PMI)
{
    myForceOTS_PMI = theForceOTS_PMI;
}

bool CFG_OtsOH::GetForceOmsFDIP() const
{
    return myForceOMS_FDIP;
}

void CFG_OtsOH::SetForceOmsFDIP(bool theForceOMS_FDIP)
{
    myForceOMS_FDIP = theForceOMS_FDIP;
}

bool CFG_OtsOH::GetForceOchOCI(uint8 theIndex) const
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    uint32 omsWavelengthCapacity = aSubNodeCfg.GetOmsWavelengthCapacity();

    FC_THROW_ERROR_IF(theIndex >= omsWavelengthCapacity,FC_ValueOutOfRangeError,"Invalid Index (0-43)");

    return myForceOCH_OCI[theIndex];
}

void CFG_OtsOH::SetForceOchOCI(bool theForceOCH_OCI,uint8 theIndex)
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    uint32 omsWavelengthCapacity = aSubNodeCfg.GetOmsWavelengthCapacity();

    FC_THROW_ERROR_IF(theIndex >= omsWavelengthCapacity,FC_ValueOutOfRangeError,"Invalid Index (0-43)");
    myForceOCH_OCI[theIndex] = theForceOCH_OCI;
}

bool CFG_OtsOH::GetForceOchFDIP(uint8 theIndex) const
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    uint32 omsWavelengthCapacity = aSubNodeCfg.GetOmsWavelengthCapacity();

    FC_THROW_ERROR_IF(theIndex >= omsWavelengthCapacity,FC_ValueOutOfRangeError,"Invalid Index (0-43)");

    return myForceOCH_FDIP[theIndex];
}

void CFG_OtsOH::SetForceOchFDIP(bool theForceOCH_FDIP,uint8 theIndex)
{
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    uint32 omsWavelengthCapacity = aSubNodeCfg.GetOmsWavelengthCapacity();

    FC_THROW_ERROR_IF(theIndex >= omsWavelengthCapacity,FC_ValueOutOfRangeError,"Invalid Index (0-43)");
    myForceOCH_FDIP[theIndex] = theForceOCH_FDIP;
}

void CFG_OtsOH::SetEnablePMIGeneration(bool theMode)
{
    myEnablePMIGen = theMode;
}

bool CFG_OtsOH::GetPMIGenerationEnabled()
{
    return myEnablePMIGen;
}

ostream& CFG_OtsOH::WriteObject( ostream& theStream )
{
    uint8 i;
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myForceOTS_PMI);
    theStream << FC_InsertVar(myForceOMS_FDIP);
    theStream << FC_InsertVar(myEnablePMIGen);

    //Serialize OCH-OCI list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce = myForceOCH_OCI[i];
        theStream << FC_InsertVar(aForce);
    }

    //Serialize OCH-FDIP list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce = myForceOCH_FDIP[i];
        theStream << FC_InsertVar(aForce);
    }

    return theStream;

}


istream& CFG_OtsOH::ReadObject( istream& theStream )
{
    uint8 i;
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myForceOTS_PMI);
    theStream >> FC_ExtractVar(myForceOMS_FDIP);
    theStream >> FC_ExtractVar(myEnablePMIGen);

    //Deserialize OCH-OCI list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce;
        theStream >> FC_ExtractVar(aForce);
        myForceOCH_OCI[i]=aForce;
    }

    //Deserialize OCH-FDIO list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce;
        theStream >> FC_ExtractVar(aForce);
        myForceOCH_FDIP[i]=aForce;
    }

    return theStream;

}


FC_Stream& CFG_OtsOH::WriteObjectBinary( FC_Stream& theStream )
{
    uint8 i;
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myForceOTS_PMI;
    theStream << myForceOMS_FDIP;
    theStream << myEnablePMIGen;

    //Serialize OCH-OCI list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce = myForceOCH_OCI[i];
        theStream << aForce;
    }

    //Serialize OCH-FDIP list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce = myForceOCH_FDIP[i];
        theStream << aForce;
    }
    return theStream;

}


FC_Stream& CFG_OtsOH::ReadObjectBinary( FC_Stream& theStream )
{
    uint8 i;

    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myForceOTS_PMI;
    theStream >> myForceOMS_FDIP;
    theStream >> myEnablePMIGen;

    //Deserialize OCH-OCI list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce;
        theStream >> aForce;
        myForceOCH_OCI[i]=aForce;
    }

    //Deserialize OCH-FDIO list
    for (i=0;i<CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        bool aForce;
        theStream >> aForce;
        myForceOCH_FDIP[i]=aForce;
    }
    return theStream;

}

FC_CmdProcessor::STATUS CFG_OtsOH::Set(int argc, char **argv)
{
    //We need 2 arguments
    if (argc < 2)
        goto OTSERROR;

    if(!strcmp(argv[0],"forceotspmi"))
    {
        SetForceOtsPMI(argv[1][0]=='e');
    }
    else if(!strcmp(argv[0],"forceomsfdip"))
    {
        SetForceOmsFDIP(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"enablepmigen"))
    {
        SetEnablePMIGeneration(argv[1][0]=='y');
    }
    else if(!strcmp(argv[0],"forceochoci"))
    {
        if (argc < 3) goto OTSERROR;
        uint8 aIndex = atoi(argv[2]);
        bool aForce = argv[1][0] == 'e';
        SetForceOchOCI(aForce,aIndex-1);
    }
    else if(!strcmp(argv[0],"forceochfdip"))
    {
        if (argc < 3) goto OTSERROR;
        uint8 aIndex = atoi(argv[2]);
        bool aForce = argv[1][0] == 'e';
        SetForceOchFDIP(aForce,aIndex-1);
    }

    else
        goto OTSERROR;

    return FC_CmdProcessor::E_SUCCESS;

OTSERROR:
    {
        fc_cout << "ots <forceotspmi>  <e-nable|d-isable>" << endl;
        fc_cout << "ots <forceomsfdip> <e-nable|d-isable>" << endl;
        fc_cout << "ots <enablepmigen> <y-es   |n-o     >" << endl;
        fc_cout << "ots <forceochoci>  <e-nable|d-isable> <index(0-43)>" << endl;
        fc_cout << "ots <forceochfdip> <e-nable|d-isable> <index(0-43)>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_FAILURE;
}

void CFG_OtsOH::Display( FC_Stream& theStream )
{
    uint8 i,j;
    uint32 columns = 10;
    uint32 rows = (CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY / columns) + 1;
    theStream   << "OTS      - Force OTS-PMI    [forceotspmi]   = " << DISPLAY_BOOL(myForceOTS_PMI) << endl;
    theStream   << "OTS      - Force OMS-FDIP   [forceomsfdip]  = " << DISPLAY_BOOL(myForceOMS_FDIP) << endl;
    theStream   << "OTS      - Force OCH-OCI    [forceochoci]   = " << "1 2 3 4 5 6 7 8 9 10" << endl;

    for(j = 0; j < rows; j++)
    {
        theStream   << "                                              ";
        for(i = 0; i < columns; i++)
        {
            uint32 index = (j * columns) + i;
            if (index >= CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY) 
            {
                break;
            }

            if(myForceOCH_OCI[index] == true)
                theStream << "X ";
            else
                theStream << "- ";
        }
        theStream << endl;
    }
    theStream   << "OTS      - Force OCH-FDIP   [forceochfdip]  = " << "1 2 3 4 5 6 7 8 9 10" << endl;

    for(j = 0; j < rows; j++)
    {
        theStream   << "                                              ";
        for(i = 0; i < columns; i++)
        {
            uint32 index = (j * columns) + i;
            if (index >= CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY) 
            {
                break;
            }

            if(myForceOCH_FDIP[index] == true)
                theStream << "X ";
            else
                theStream << "- ";
        }
        theStream << endl;
    }

}
