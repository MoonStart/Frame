//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_DRTRCONFIG_H
#define MON_DRTRCONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_Telecom.h>

//This class contains configuration parameters that affects 
//how the monitoring of the DCC Router (DRTR) layer is performed.
class MON_DrtrConfig 
: public MON_Config
{
public:
    //Constructor.
    MON_DrtrConfig(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_DrtrConfig();


    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);

    //This method allows specifying if Drtr is monitored.
    void SetMonitoringEnable(bool theMonitorEnable);

    //This method returns the current state of Drtr enable option.
    bool GetMonitoringEnable() const;


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The Drtr Monitor state configured.
    bool myMonitorEnable;

};

#endif /* MON_DRTRCONFIG_H */
