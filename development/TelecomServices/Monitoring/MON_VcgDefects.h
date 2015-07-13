//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_VCGDEFECTS_H
#define MON_VCGDEFECTS_H

#include "MON_HopDefects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for the 
//virtual concatenation (VCG) layer.
class MON_VcgDefects :public MON_HopDefects
{
public:

    //Constructor.
    MON_VcgDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_VcgDefects(void);

    // All methods inherited from Hop Layer

protected:
    // Serialization methods
    // All methods inherited from Hop Layer

private:
    // Defects at VCG layer
    // All defects inherited from Hop Layer
};

#endif /* MON_VCGDEFECTS_H */
