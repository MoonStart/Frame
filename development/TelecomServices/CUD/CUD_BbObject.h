/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Configuration File Upload/Download
 TARGET   :     All.
 AUTHOR   :     April, 2007  Jim Beck
 DESCRIPTION:   CUD base class object.
--------------------------------------------------------------------------*/

#ifndef CUD_BBOBJECT_H
#define CUD_BBOBJECT_H

#include <TelCommon/TEL_BbObjectBase.h>


// Forward class declaration;
// class CUD_BbValue;


// This is the Configuration Upload/Download base class object.
class CUD_BbObject : public TEL_BbObjectBase
{

public:

    // Class default constructor.
    CUD_BbObject ();
    
    //Class default destructor.
    virtual ~CUD_BbObject();

    //Initializes BB object according to the restart type.
    virtual void Init(restart_type theRestartType);

    //Resets all parameter values.
    virtual void Reset() = 0;

};

#endif //CUD_BBOBJECT_H

