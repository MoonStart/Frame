//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_IBETHCONFIG_H
#define MON_IBETHCONFIG_H

#include "MON_Config.h"


class MON_IBETHConfig : public MON_Config
{
public:

    //Constructor.
    MON_IBETHConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_IBETHConfig();

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////

    //Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);

    //This method allows specifying if Gcc is monitored.
    void SetMonitoringEnable(bool theMonitoringEnable);

    //This method returns the current state of Gcc enable option.
    bool GetMonitoringEnable() const;


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    
    bool myMonitoringEnable;
};

#endif 
