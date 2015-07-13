/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, April 15, 2002.
 DESCRIPTION:   PM base class object.
--------------------------------------------------------------------------*/

#ifndef PM_BBOBJECT_H
#define PM_BBOBJECT_H

#include <TelCommon/TEL_BbObjectBase.h>


// Forward class declaration;
class PM_BbValue;


//This is the performance monitoring base class object.
//##ModelId=3CBC723F0351
class PM_BbObject : public TEL_BbObjectBase
{

public:

    //Class default constructor.
    //##ModelId=3CBC724001C1
    PM_BbObject ();
    
    //Class default destructor.
    //##ModelId=3CBC724001CA
    virtual ~PM_BbObject();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC724001D4
    virtual void Init(restart_type theRestartType);

    //Resets all parameter values.
    //##ModelId=3CBC724001D6
    virtual void Reset() = 0;

};

#endif //PM_BBOBJECT_H

