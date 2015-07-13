/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     15 June, 1998 Jean-Francois Birtz.
 DESCRIPTION:   The layer element is all that is commun to each layer for
                updating the PM parameters.
--------------------------------------------------------------------------*/

#ifndef PM_LAYERELEM_H
#define PM_LAYERELEM_H

#include <gdef.h>


#define PM_NB_SES_FOR_UA  10 //Number of SES needed for switch UA state


//This class has everything that each layer element has in 
//common. For now, this class has to keep and update the 
//unavailability status.
//##ModelId=3C1F6F6B039E
class PM_LayerElem
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F6C01E7
    PM_LayerElem ();

    //Class default destructor.
    //##ModelId=3C1F6F6C01F1
    ~PM_LayerElem();

    //Updates the unavailable state with the current SES 
    //status.
    //##ModelId=3C1F6F6C01F2
    bool UpdateUA(bool theSES);

    //Reports if there is a potential for the UA to change 
    //state. This is used for register adjustment.
    //##ModelId=3C1F6F6C01FC
    inline bool IsPotential2ChgState() const;

    //Gets the current unavailable state.
    //##ModelId=3C1F6F6C0206
    inline bool GetUAstate() const;

    //Resets the soaking counter at 0 for the next time there 
    //is a potential to change state.
    //##ModelId=3C1F6F6C0210
    inline void ResetSoakCountforUa();


private:

    //Number of consecutive SES in the other state then the 
    //current one for any direction (available to unavailabe or 
    //the opposite). After 10 consecutive SES in the other state, 
    //it switches the current Unavailable state.
    //##ModelId=3C1F6F6C022E
    uint8 mySecInOstate;

    //The current unavailable state for any direction.
    //##ModelId=3C1F6F6C0241
    bool myUAstate;

};

//-----------------------------------------------------------------
//##ModelId=3C1F6F6C01FC
inline bool PM_LayerElem::IsPotential2ChgState() const
{
    return mySecInOstate ? true : false;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6C0206
inline bool PM_LayerElem::GetUAstate() const
{
    return myUAstate;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6C0210
inline void PM_LayerElem::ResetSoakCountforUa()
{
    mySecInOstate = 0;

}

#endif //PM_LAYERELEM_H
