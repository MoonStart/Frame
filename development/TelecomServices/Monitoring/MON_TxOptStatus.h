// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _MON_TXOPTSTATUS_
#define _MON_TXOPTSTATUS_

#include "MON_Status.h"
#include <CommonTypes/CT_Telecom.h>

//This class hold the status value (equipment levels) for the optical layer (transmit side).
class MON_TxOptStatus 
: public MON_Status
{
public:
	//Constructor.
	MON_TxOptStatus(uint32 theIndex);

	//Virtual destructor.
	virtual ~MON_TxOptStatus(void );

  	//Returns the level of the status provide as argument.
	virtual void GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const;

    //Returns true if level has changed.
    virtual bool SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel);

	//Returns or set the optical output power transmitted (mBm).
	CT_TEL_mBm GetOutputPower() const;
	bool SetOutputPower(CT_TEL_mBm thePower);

	//Returns or set the laser bias current (mA).
	CT_TEL_Percent GetLaserBiasCurrent() const;
	bool SetLaserBiasCurrent(CT_TEL_Percent theLBC);

	//Returns or set the temperature of the laser (in 0.1 °C).
	CT_TEL_milliCelcius GetLaserTemp() const;
	bool SetLaserTemp(CT_TEL_milliCelcius theTemp);

	//Returns or set the laser state.
    bool SetLaserState(bool theState);
    bool GetLaserState() const;

    bool GetLowTxPowerDefect() const;
    bool SetLowTxPowerDefect(bool theState);

    // Debug Methods
    void Reset();
    virtual void Display(FC_Stream& theStream);


protected:
    //Serialization methods
    virtual ostream& WriteObject(ostream& theStream);
	virtual istream& ReadObject(istream& theStream);
	virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);
	virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);

private:
    //The current value of the laser bias current (in mA).
	CT_TEL_Percent myLaserBiasCurrent;

	//The current temperature of the laser (in 0.1 °C).
	CT_TEL_milliCelcius myLaserTemp;

	//The transmitted optical power (in mBm).
	CT_TEL_mBm myOutputPower;

    //The actual state of the laser
    bool myLaserState;

    bool myLowTxPowerDefect;
};

#endif /* _MON_TXOPTSTATUS_ */
