/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        CFG_PilotToneAssignment.cpp
 *    DATE:          07/05/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Pilot Tone Assignment
 *    OVERVIEW:      Pilot Tone Assignment for 32/44 channels system
 *                   configuration
 *    FEATURE PACK:  FP3.2
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#include "CommonTypes/CT_CardInventory.h"
#include "Configuration/CFG_PilotToneAssignment.h"
#include "ErrorService/FC_Error.h"
#include "Monitoring/MON_SubNodeParameters.h"
#include <cstring>

CFG_PilotToneAssignment*  CFG_PilotToneAssignment::ourInstance = NULL;


typedef struct
{
    CT_TEL_Hz           freq;
    uint8               ch;
}tFreqToCh;

tFreqToCh* pFreqToChTable = NULL;

tFreqToCh FreqToChTable[]=
{
    /**************
     freq       ch
     **************/
    { 782250,   0  },
    { 782500,   0  },
    { 782750,   0  },
    { 783250,   1  },
    { 783500,   1  },
    { 783750,   1  },
    { 784250,   2  },
    { 784500,   2  },
    { 784750,   2  },
    { 785250,   3  },
    { 785500,   3  },
    { 785750,   3  },
    { 786250,   4  },
    { 786500,   4  },
    { 786750,   4  },
    { 750250,   5  },
    { 750500,   5  },
    { 750750,   5  },
    { 751250,   6  },
    { 751500,   6  },
    { 751750,   6  },
    { 752250,   7  },
    { 752500,   7  },
    { 752750,   7  },
    { 753250,   8  },
    { 753500,   8  },
    { 753750,   8  },
    { 754250,   9  },
    { 754500,   9  },
    { 754750,   9  },
    { 755250,   10 },
    { 755500,   10 },
    { 755750,   10 },
    { 756250,   11 },
    { 756500,   11 },
    { 756750,   11 },
    { 757250,   12 },
    { 757500,   12 },
    { 757750,   12 },
    { 787250,   13 },
    { 787500,   13 },
    { 787750,   13 },
    { 788250,   14 },
    { 788500,   14 },
    { 788750,   14 },
    { 758250,   15 },
    { 758500,   15 },
    { 758750,   15 },
    { 759250,   16 },
    { 759500,   16 },
    { 759750,   16 },
    { 760250,   17 },
    { 760500,   17 },
    { 760750,   17 },
    { 761250,   18 },
    { 761500,   18 },
    { 761750,   18 },
    { 762250,   19 },
    { 762500,   19 },
    { 762750,   19 },
    { 763250,   20 },
    { 763500,   20 },
    { 763750,   20 },
    { 764250,   21 },
    { 764500,   21 },
    { 764750,   21 },
    { 765250,   22 },
    { 765500,   22 },
    { 765750,   22 },
    { 789250,   23 },
    { 789500,   23 },
    { 789750,   23 },
    { 790250,   24 },
    { 790500,   24 },
    { 790750,   24 },
    { 766250,   25 },
    { 766500,   25 },
    { 766750,   25 },
    { 767250,   26 },
    { 767500,   26 },
    { 767750,   26 },
    { 768250,   27 },
    { 768500,   27 },
    { 768750,   27 },
    { 769250,   28 },
    { 769500,   28 },
    { 769750,   28 },
    { 770250,   29 },
    { 770500,   29 },
    { 770750,   29 },
    { 771250,   30 },
    { 771500,   30 },
    { 771750,   30 },
    { 772250,   31 },
    { 772500,   31 },
    { 772750,   31 },
    { 773250,   32 },
    { 773500,   32 },
    { 773750,   32 },
    { 791250,   33 },
    { 791500,   33 },
    { 791750,   33 },
    { 792250,   34 },
    { 792500,   34 },
    { 792750,   34 },
    { 774250,   35 },
    { 774500,   35 },
    { 774750,   35 },
    { 775250,   36 },
    { 775500,   36 },
    { 775750,   36 },
    { 776250,   37 },
    { 776500,   37 },
    { 776750,   37 },
    { 777250,   38 },
    { 777500,   38 },
    { 777750,   38 },
    { 778250,   39 },
    { 778500,   39 },
    { 778750,   39 },
    { 779250,   40 },
    { 779500,   40 },
    { 779750,   40 },
    { 780250,   41 },
    { 780500,   41 },
    { 780750,   41 },
    { 781250,   42 },
    { 781500,   42 },
    { 781750,   42 },
    { 793250,   43 },
    { 793500,   43 },
    { 793750,   43 }
};

//for configurations that support only 32 wavelengths
tFreqToCh FreqToChTable_FP2[]=
{
    /**************
     freq       ch
     **************/
    { 750250,   0  },
    { 750500,   0  },
    { 750750,   0  },
    { 751250,   1  },
    { 751500,   1  },
    { 751750,   1  },
    { 752250,   2  },
    { 752500,   2  },
    { 752750,   2  },
    { 753250,   3  },
    { 753500,   3  },
    { 753750,   3  },
    { 754250,   4  },
    { 754500,   4  },
    { 754750,   4  },
    { 755250,   5  },
    { 755500,   5  },
    { 755750,   5  },
    { 756250,   6  },
    { 756500,   6  },
    { 756750,   6  },
    { 757250,   7  },
    { 757500,   7  },
    { 757750,   7  },
    { 758250,   8  },
    { 758500,   8  },
    { 758750,   8  },
    { 759250,   9  },
    { 759500,   9  },
    { 759750,   9  },
    { 760250,   10 },
    { 760500,   10 },
    { 760750,   10 },
    { 761250,   11 },
    { 761500,   11 },
    { 761750,   11 },
    { 762250,   12 },
    { 762500,   12 },
    { 762750,   12 },
    { 763250,   13 },
    { 763500,   13 },
    { 763750,   13 },
    { 764250,   14 },
    { 764500,   14 },
    { 764750,   14 },
    { 765250,   15 },
    { 765500,   15 },
    { 765750,   15 },
    { 766250,   16 },
    { 766500,   16 },
    { 766750,   16 },
    { 767250,   17 },
    { 767500,   17 },
    { 767750,   17 },
    { 768250,   18 },
    { 768500,   18 },
    { 768750,   18 },
    { 769250,   19 },
    { 769500,   19 },
    { 769750,   19 },
    { 770250,   20 },
    { 770500,   20 },
    { 770750,   20 },
    { 771250,   21 },
    { 771500,   21 },
    { 771750,   21 },
    { 772250,   22 },
    { 772500,   22 },
    { 772750,   22 },
    { 773250,   23 },
    { 773500,   23 },
    { 773750,   23 },
    { 774250,   24 },
    { 774500,   24 },
    { 774750,   24 },
    { 775250,   25 },
    { 775500,   25 },
    { 775750,   25 },
    { 776250,   26 },
    { 776500,   26 },
    { 776750,   26 },
    { 777250,   27 },
    { 777500,   27 },
    { 777750,   27 },
    { 778250,   28 },
    { 778500,   28 },
    { 778750,   28 },
    { 779250,   29 },
    { 779500,   29 },
    { 779750,   29 },
    { 780250,   30 },
    { 780500,   30 },
    { 780750,   30 },
    { 781250,   31 },
    { 781500,   31 },
    { 781750,   31 }
};

////////////////////////////////////////////////////////////////////////////////
CFG_PilotToneAssignment & CFG_PilotToneAssignment::GetInstance()
{
    if (ourInstance == NULL)
        ourInstance = new CFG_PilotToneAssignment();

    return *ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
void CFG_PilotToneAssignment::DeleteInstance()
{
    delete ourInstance;
    ourInstance = NULL;
}

////////////////////////////////////////////////////////////////////////////////
CFG_PilotToneAssignment::CFG_PilotToneAssignment() :
    myNumOfWaveLengths(0),
    myFreqToChTableSize(0)
{
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    // For 5.1.1 f2 and beyond, we want the wavelength capacity to be 44 channels.
    // If a new table is constructed for 88 channel or 32 channel is needed again,
    // then we suspect the subnode parameters must be ready before looking up the
    // wavelength capacity
    //if (!(MON_SubNodeParameters::GetInstance().IsSubNodeParametersReady()))
    //{
    //    fc_cout << endl << "**** CFG_PilotToneAssignment: SubNodeParameters NOT READY, cap =  " << omsWavelengthCapacity << endl;
    //}

    if (omsWavelengthCapacity != CT_TEL_FP3_OMS_WAVELENGTH_CAPACITY) 
    {
        fc_cout << endl << "**** CFG_PilotToneAssignment: Changing wavelength capacity to 44 from " << omsWavelengthCapacity << endl;
        omsWavelengthCapacity = CT_TEL_FP3_OMS_WAVELENGTH_CAPACITY;
    }

    if(omsWavelengthCapacity == CT_TEL_FP2_OMS_WAVELENGTH_CAPACITY)
    {
        pFreqToChTable = &FreqToChTable_FP2[0];
        //fc_cout << "**** CFG_PilotToneAssignment: Using FreqToChTable_FP2, cap =  " << omsWavelengthCapacity << endl;
    }
    else
    {
        pFreqToChTable = &FreqToChTable[0];
        //fc_cout << "**** CFG_PilotToneAssignment: Using FreqToChTable, cap =  " << omsWavelengthCapacity << endl;
    }

    myNumOfWaveLengths  = omsWavelengthCapacity;
    myFreqToChTableSize = omsWavelengthCapacity * 3;
}

////////////////////////////////////////////////////////////////////////////////
CFG_PilotToneAssignment::~CFG_PilotToneAssignment()
{
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_PilotToneID CFG_PilotToneAssignment::PT_FREQ_TO_OTID(CT_TEL_Hz freq)
{
    uint32 rVal = 0xff;
    for(uint32 i = 0; i < myFreqToChTableSize; i++)
    {
        if((pFreqToChTable + i)->freq == freq)
        {
            //OTID is 1-based
            rVal = i + 1;
            break;
        }
    }

    return(rVal);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_Hz CFG_PilotToneAssignment::OTID_TO_PT_FREQ(CT_TEL_PilotToneID otid)
{
    return((pFreqToChTable + otid-1)->freq);
}

////////////////////////////////////////////////////////////////////////////////
uint8 CFG_PilotToneAssignment::OTID_TO_CH_ID(CT_TEL_PilotToneID otid)
{
    return((pFreqToChTable + otid-1)->ch);
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_PilotToneID CFG_PilotToneAssignment::CH_ID_TO_OTID(uint8 chid, MON_RelativeTraceId theRelativeId)
{
    uint32 rVal = 0xff;
    for(uint32 i = 0; i < myFreqToChTableSize; i++)
    {
        if((pFreqToChTable + i)->ch == chid)
        {
            //OTID is 1-based
            if(theRelativeId == MON_ID_FIRST)
                rVal = i + 1;
            else if(theRelativeId == MON_ID_SECOND)
                rVal = i + 2;
            else
                rVal = i + 3;
            break;
        }
    }

    return(CT_TEL_PilotToneID(rVal));
}

////////////////////////////////////////////////////////////////////////////////
CT_TEL_Hz CFG_PilotToneAssignment::CH_ID_TO_CENTER_FREQ(uint8 chid)
{
    const float  MON_PT_BAND_LOWER_FREQ      = 750500.0;
    CT_TEL_Hz rVal = (CT_TEL_Hz)MON_PT_BAND_LOWER_FREQ;
    for(uint32 i = 0; i < myFreqToChTableSize; i++)
    {
        if((pFreqToChTable + i)->ch == chid)
        {
            //get the next frequnecy
            rVal = (pFreqToChTable + i + 1)->freq;
            break;
        }
    }

    return(rVal);
}

////////////////////////////////////////////////////////////////////////////////
void CFG_PilotToneAssignment::SetFreq(uint8 ch, CT_TEL_Hz freq)
{
    //find the index of the ch in the table
    for(uint32 i = 0; i < myFreqToChTableSize; i++)
    {
        if((pFreqToChTable + i)->ch == ch)
        {
            (pFreqToChTable + i + 0)->freq = freq;
            (pFreqToChTable + i + 1)->freq = (pFreqToChTable + i)->freq+250;
            (pFreqToChTable + i + 2)->freq = (pFreqToChTable + i)->freq+500;

            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void CFG_PilotToneAssignment::Display()
{
    char line[80];
    CT_TEL_PilotToneID firstOtid;

    fc_cout << "\r\nPilot Tone Frequency Assignment: Num of Wavelengths = "<<myNumOfWaveLengths<< endl << endl;
    fc_cout << "\r Ch Otid1 Freq1  Otid2 Freq2  Otid3 Freq3 "<<endl;
    fc_cout << "\r------------------------------------------"<<endl;
    for(uint32 i = 0; i < myNumOfWaveLengths; i++)
    {
        firstOtid = CH_ID_TO_OTID((uint8)i, MON_ID_FIRST);

        sprintf(line, "\r %2d %3d   %6d %3d   %6d %3d   %6d",
                i,
                firstOtid,   OTID_TO_PT_FREQ(firstOtid),
                firstOtid+1, OTID_TO_PT_FREQ(firstOtid+1),
                firstOtid+2, OTID_TO_PT_FREQ(firstOtid+2));
        fc_cout << line << endl;
    }
    fc_cout <<endl;
}

////////////////////////////////////////////////////////////////////////////////
void CFG_PilotToneAssignment::Menu(int argc, char ** argv)
{
    if(argc == 1 && argv[0][0] == 'd')
    {
        Display();
    }

    else if(argc == 2 && (strncmp(argv[0], "freqtootid", 10) == 0))
    {
        uint32 freq = strtoul(argv[1], NULL, 0);
        fc_cout << "\rOTID = " << PT_FREQ_TO_OTID((CT_TEL_Hz)freq) << endl;
    }

    else if(argc == 2 && (strncmp(argv[0], "otidtofreq", 10) == 0))
    {
        uint32 otid = strtoul(argv[1], NULL, 0);
        fc_cout << "\rPT Freq = " << OTID_TO_PT_FREQ((CT_TEL_PilotToneID)otid) << endl;
    }

    else if(argc == 2 && (strncmp(argv[0], "otidtochid", 10) == 0))
    {
        uint32 otid = strtoul(argv[1], NULL, 0);
        fc_cout << "\rChannel ID = " << (uint32)(OTID_TO_CH_ID((CT_TEL_PilotToneID)otid)) << endl;
    }

    else if(argc == 3 && (strncmp(argv[0], "chidtootid", 10) == 0))
    {
        uint32 chid = strtoul(argv[1], NULL, 0);
        uint32 tone = strtoul(argv[2], NULL, 0);

        fc_cout << "\rOTID = " << CH_ID_TO_OTID((uint8)chid, MON_RelativeTraceId(tone-1)) << endl;
    }

    else if(argc == 2 && (strncmp(argv[0], "chidtocenterfreq", 16) == 0))
    {
        uint32 chid = strtoul(argv[1], NULL, 0);
        fc_cout << "\rPT Center Freq = " << CH_ID_TO_CENTER_FREQ((uint8)chid) << endl;
    }

    else if(argc == 3 && (strncmp(argv[0], "setfreq", 7) == 0))
    {
        uint32 ch   = strtoul(argv[1], NULL, 0);
        uint32 freq = strtoul(argv[2], NULL, 0);
        SetFreq((uint8)ch, (CT_TEL_Hz)freq);
    }

    else
    {
        fc_cout << "d(isplay)"                                          << endl;
        fc_cout << "freqtootid <freq in Hz>"                            << endl;
        fc_cout << "otidtofreq <otid (1-based)>"                        << endl;
        fc_cout << "otidtochid <otid (1-based)>"                        << endl;
        fc_cout << "chidtootid <chid (0-bases)> <tone (1|2|3)>"         << endl;
        fc_cout << "chidtocenterfreq <chid (0-based)>"                  << endl;
        fc_cout << "setfreq <ch (0-based)> <freq (Hz)>"                 << endl << endl;
    }
}
