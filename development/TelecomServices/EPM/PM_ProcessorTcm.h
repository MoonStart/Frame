/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     8 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Process that computes the PM Parameters TCM layer.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORTCM_H
#define PM_PROCESSORTCM_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//ODU layer. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor ODU 
//is woken up by the Collector every second.
class PM_ProcessorTcm:    public PM_Processor
{
public:

    //The constructor of Processor ODU.
    PM_ProcessorTcm(PM_GenericApplication& theGenericApplication, 
                    uint16                 theNumberOfPort);
    
    //The default destructor of Processor ODU.
    virtual ~PM_ProcessorTcm();

    //Creates actions and instances used by the Processor ODU.
    virtual void CreateActionsInstances();

    //This method is responsible for detecting a system time 
    //change and prints an error message if "warning" is on. 
    //It is also responsible of the change of period and 
    //adjusts the current/previous regions via the 
    //ControlPeriod object for all accumulation period 
    //supported. Note that, this method must be called at the 
    //end of the Run of the derived Processor class.
    //##ModelId=3C1F9DEF0239
    virtual void Run(FC_Object* theObject = NULL);

    // Resets the statically allocated objects associated with
    // the indicated index.
    //virtual void Reset( bbindex_t theIndex );

    //Initializes the Processor.
    virtual void Init();
  
    //Initializes the Processor for a particular "port" number.
    virtual void Init( uint16 thePortNumber );

    // Method to retieve flag indicating that at least one dynamically
    // allocated object was encountered by the processor.
    bool AreObjectsAllocated();

private:

    bool myObjectsAllocated;
};

inline
bool PM_ProcessorTcm::AreObjectsAllocated()
{
    return myObjectsAllocated;
}

#endif //PM_PROCESSORTCM_H
