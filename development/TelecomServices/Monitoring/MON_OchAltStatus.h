//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OCHALTSTATUS_H
#define MON_OCHALTSTATUS_H

#include "MON_Object.h"
#include <CommonTypes/CT_Telecom.h>


class MON_OchAltStatus
: public MON_Object
{

public:

	//Constructor.
    MON_OchAltStatus(uint32 theIndex);
    MON_OchAltStatus(const MON_OchAltStatus& theOchAltStatus);

	//Virtual destructor.
    virtual ~MON_OchAltStatus(void);

    bool operator==(const MON_OchAltStatus& theOchAltStatus) const;
    void operator=(const MON_OchAltStatus& theOchAltStatus);

    bool SetActualGain(CT_TEL_mBm theGain);
    CT_TEL_mBm GetActualGain() const;

    bool SetConfiguredGain(CT_TEL_mBm theGain);
    CT_TEL_mBm GetConfiguredGain() const;

    bool GetActivePath() const;
    bool SetActivePath(bool theActivePath);
 
    // Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:

    CT_TEL_mBm      myActualGain;
    CT_TEL_mBm      myConfiguredGain;
    bool myActivePath;
};

#endif /* MON_OCHALTSTATUS_H */
