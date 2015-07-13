//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_T1E1CONFIG_H
#define MON_T1E1CONFIG_H

#include "MON_Config.h"
#include <CommonTypes/CT_G709Trace.h>
#include <CommonTypes/CT_Telecom.h>

// This class contains configuration parameters that affects 
// how the monitoring of the T1E1 layer is performed.
class MON_T1E1Config 
: public MON_Config
{
public:

    //Constructor.
    MON_T1E1Config(uint32 theIndex);

	//Virtual destructor.
    virtual ~MON_T1E1Config();

    bool SetLayerLocked(bool theState);
    bool GetLayerLocked() const;

    //Debug methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char** argv);


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    bool myLayerLocked;
};

#endif /* MON_T1E1CONFIG_H */
