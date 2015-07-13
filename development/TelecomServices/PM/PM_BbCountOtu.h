/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 24, 2002 Sebastien Cossette.
 DESCRIPTION:   Update and keep the counts of Optical
                Transport Unit or FEC.
--------------------------------------------------------------------------*/

#ifndef PM_BBCOUNTOTU_H
#define PM_BBCOUNTOTU_H

#include <TelCommon/TEL_BbObjectBase.h>
#include "src/PM_Counter.h"


// Forward declaration of classes.
class MON_OtuCounters;

using namespace std;

//Keeps various OTU counters up to date for the current second.
//##ModelId=3C20AB6E0341
class PM_BbCountOtu: public TEL_BbObjectBase
{
public:

    //Class default constructor.
    //##ModelId=3C20AB6F018B
    PM_BbCountOtu();

    //Class default destructor.
    //##ModelId=3C20AB6F0194
    virtual ~PM_BbCountOtu();

    //Initializes BB object according to the restart type.
    //##ModelId=3CBC8F110127
    virtual void Init(restart_type theRestart);

    //Returns the BE corrected count.
    //##ModelId=3C20AB6F01B2
    inline CT_PM_64bit_ull GetBE() const;

    //Returns the BE Byte count.
    inline CT_PM_64bit_ull GetBEByte() const;

    //Returns the BE un-corrected count.
	//##ModelId=3E6E4D21017C
    inline uint32 GetUBE() const;

	//Returns the BIP count.
    inline CT_PM_64bit_ull GetBIP() const;

    //Updates PM counts for the OTU.
    //##ModelId=3C20AB6F01BC
    void Update(MON_OtuCounters& theCounter);

protected:

    //Stores the counter to the stream.
    //##ModelId=3C20AB6F01C6
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the counter from the stream.
    //##ModelId=3C20AB6F01D1
    virtual istream& ReadObject( istream& theStream );

private:

    //The PM Counter to memorize the number of Block Errors 
    //corrected for this second.
    //##ModelId=3C20AB6F01EF
    PM_Counter myBECounter;

    //The PM Counter to memorize the number of Block Errors 
    //uncorrectable for this second.
	//##ModelId=3E6E4D21039A
    PM_Counter myUBECounter;

	//The PM Counter to memorize the number of BIP8 Errors 
    //for this second.
    PM_Counter myBIPCounter;

    //This counter is used by all modules except for OMMX and OSM20
    PM_Counter myBEByteCounter;

};

//-----------------------------------------------------------------
//##ModelId=3C20AB6F01B2
inline CT_PM_64bit_ull PM_BbCountOtu::GetBE() const
{
    return myBECounter.GetCount();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D21017C
inline uint32 PM_BbCountOtu::GetUBE() const
{
    return myUBECounter.GetCount();

}

//-----------------------------------------------------------------
inline CT_PM_64bit_ull PM_BbCountOtu::GetBIP() const
{
    return myBIPCounter.GetCount();

}

//-----------------------------------------------------------------
inline CT_PM_64bit_ull PM_BbCountOtu::GetBEByte() const
{
    return myBEByteCounter.GetCount();

}
#endif //PM_BBCOUNTOTU_H
