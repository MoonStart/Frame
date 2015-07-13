//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RMONCONFIG_H
#define MON_RMONCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>

//This class contains configuration parameters that affects 
//how the monitoring of the RMON layer is performed.
class MON_RmonConfig : public MON_Config
{
public:

    //Constructor.
    MON_RmonConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_RmonConfig();


    //This method allows specifying if Rmon is monitored.
    bool SetRmonEnable(bool theRmonState);

    //This method returns the current state of Rmon enable option.
    bool GetRmonEnable() const;


    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The Rmon state configured.
    bool myRmonEnable;
};

#endif /* RMONCONFIG_H */
