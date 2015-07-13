//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_GCCCONFIG_H
#define MON_GCCCONFIG_H

#include "MON_Config.h"

//This class contains configuration parameters that affects 
//how the monitoring of the GCC (GCC Link) layer is performed.
class MON_GccConfig : public MON_Config
{
public:

    //Constructor.
    MON_GccConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_GccConfig();

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

    //The Gcc Monitor state configured.
    bool myMonitoringEnable;
};

#endif /* GCCCONFIG_H */
