/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Common.
 TARGET   :     All cards.
 AUTHOR   :     Steve Thiffault, June 18, 2002.
 DESCRIPTION:   Contains the version of the TCS library.
--------------------------------------------------------------------------*/
#ifndef SPM8560_SWVERSION_H
#define SPM8560_SWVERSION_H

#include <Shell/FC_CmdProcessor.h>
#include <BaseClass/FC_TextStream.h>


inline void SPM8560_RegisterSwVersionCmd();
inline static FC_CmdProcessor::STATUS SwVersionCmd (int argc, char** argv);


class SPM8560_SwVersion
{

public: 

    //Class constructor.
    SPM8560_SwVersion ();
    
    //Class destructor.
    ~SPM8560_SwVersion();

    //This class returns a reference to the sw version object.
    static SPM8560_SwVersion& GetInstance();

    //This class prints the application sw version.
    virtual void PrintVersion();

    //Static pointer to the SPM8560 sw version instance.
    static SPM8560_SwVersion* myInstancePtr;

};

//---------------------------------------------------------------------------
// SPM8560_RegisterSwVersionCmd - Function to register all commands
//                            defined in this file
//---------------------------------------------------------------------------

inline void SPM8560_RegisterSwVersionCmd()
{
    static const FC_CmdProcessor::CMD_TABLE_STRUCT cmdTable[] =
    {
        { "swversion",  NULL,  "swversion    - Display application sw version", NULL, SwVersionCmd },
    };


    FC_CmdProcessor& cmdProcessor= *FC_CmdProcessor::GetShellInstance(); // get instance of Shell
    cmdProcessor.FC_RegisterCommand(cmdTable, sizeof(cmdTable)/sizeof(FC_CmdProcessor::CMD_TABLE_STRUCT));

}

//---------------------------------------------------------------------------
inline static FC_CmdProcessor::STATUS SwVersionCmd (int argc, char** argv)
{

    if( argc == 1 )
    {
        SPM8560_SwVersion::GetInstance().PrintVersion();

        return FC_CmdProcessor::E_SUCCESS;
    }


    // Usage.
    fc_cout << "usage: swversion" << endl;

    return FC_CmdProcessor::E_SUCCESS;

}

#endif //SPM8560_SWVERSION_H
