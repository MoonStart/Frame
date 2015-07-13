/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     9 March, 1999 Erik Gobeil.
 DESCRIPTION:   IDF class. Keep and set the PM IDF states.
--------------------------------------------------------------------------*/

#ifndef PM_BBIDF_H
#define PM_BBIDF_H

#include <CommonTypes/CT_PM_Definition.h>
#include "PM_BbObject.h"


//Keeps and sets the PM IDF states. This contains an array of 
//bytes, where each combination of bits keeps IDF states.
//##ModelId=3C1F6F7303BE
class PM_BbIdf : public PM_BbObject
{

public:

    //This class constructor allocates the necessary memory 
    //to put an array that contained theNumberOfParam IDF.
    //##ModelId=3C1F6F7401FD
    PM_BbIdf (uint32 theNumberOfParam);

    //Class default destructor.
    //##ModelId=3C1F6F74021B
    virtual ~PM_BbIdf();

    //Resets to OFF all IDF states.
    //##ModelId=3C1F6F740225
    virtual void Reset();

    //Gets the IDF state of a PM parameter.
    //##ModelId=3C1F6F74022E
    CT_PM_IdfStatus GetIdf(CT_PM_Parameter theParameter) const;

    //Sets the invalid bit status of the parameter passed.
    //##ModelId=3C1F6F740239
    void SetIdf(CT_PM_Parameter theParameter);

    //Sets the IDF to the specified status of the parameter 
    //passed 
    //##ModelId=3E6E4CAC0305
    void SetIdf(CT_PM_Parameter theParameter, CT_PM_IdfStatus theStatus);

    //Sets to inhibit state the parameter passed. This method 
    //doesn't allow to set back on if the inhibition was 
    //previously set to off.
    //##ModelId=3C1F6F740243
    void SetInhibit(CT_PM_Parameter theParameter, bool theState);

    //Sets to inhibit the parameter passed. This method 
    //allows setting back if the inhibition was previously reset. 
    //It is used during a change of period.
    //##ModelId=3C1F6F740258
    void ForcedSetInhibit(CT_PM_Parameter theParameter, bool theState);

    //Sets to inhibit all parameters. This method allows 
    //setting back if the inhibition was previously reset. It 
    //is used during a change of period.
    //##ModelId=3C1F6F74026C
    void ForcedSetAllInhibit(bool theState);

    //Sets the availability bit status of the parameter passed. 
    //This method allows resetting back if the availability bit 
    //was previously set.
	//##ModelId=3FA161050068
    void ForcedSetAvailability(CT_PM_Parameter theParameter, bool theState);

    //Sets the availability bit status of all parameters. This 
    //method allows to set back to available if the availability bit 
    //was previously set to not available.
	//##ModelId=3FA161050087
    void ForcedSetAllAvailability(bool theState);

    //Sets the invalid bit status of the parameter passed. 
    //This method allows resetting back if the invalid bit 
    //was previously set.
    //##ModelId=3C1F6F740276
    void ForcedSetIdf(CT_PM_Parameter theParameter, bool theState);

    //Sets the invalid bit status of all parameters. This 
    //method allows to set back to valid if the invalid bit 
    //was previously set to invalid.
    //##ModelId=3C1F6F740289
    void ForcedSetAllIdf(bool theState);

    //Operator that returns true if IDF statuses are equal.
    //##ModelId=3C1F6F740293
    bool operator==(const PM_BbIdf& theOtherIdf) const;

    //Operator that copies the IDF statuses.
    //##ModelId=3C1F6F74029E
    PM_BbIdf& operator=(const PM_BbIdf& theOtherIdf);

protected:

    //Stores the IDF states to the stream.
    //##ModelId=3C1F6F7402A8
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the IDF states from the stream.
    //##ModelId=3C1F6F7402BB
    virtual istream& ReadObject( istream& theStream );

    //Writes the IDF states to the binary stream.
    //##ModelId=3C1F6F7402CF
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the IDF states from a binary stream.
    //##ModelId=3C1F6F7402DA
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //The number of parameter handled by this class.
    //##ModelId=3C1F6F7402ED
    uint32  myNumberOfParam;

    //Array that contains all the IDF states for a signal of this layer.
    //##ModelId=3C1F6F740316
    uint8* myIdf;

};

#endif //PM_BBIDF_H

