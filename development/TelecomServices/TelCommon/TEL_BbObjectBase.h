/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Telecom Services
 TARGET   :     ALL
 AUTHOR   :     M. Vendette - April 05th ,2000
 DESCRIPTION:   Base class BbObject used by Telecom Services
--------------------------------------------------------------------------*/

#ifndef TEL_BBOBJECTBASE_H
#define TEL_BBOBJECTBASE_H

#include <gdef.h>
#include <Blackboard/FC_BbObject.h>


/*
This class is the Blackboard base class used by Telecom Services. It defines
the common methods related to the initialization part of the system.
*/
//##ModelId=3C20B0B201A5
class TEL_BbObjectBase : public FC_BbObject
{

public:

    // Class default constructor.
	//##ModelId=3C20B0B203D7
    TEL_BbObjectBase ();
    
    // Class default destructor.
	//##ModelId=3C20B0B203E0
    virtual ~TEL_BbObjectBase(void);

};

#endif //TEL_BBOBJECTBASE_H
