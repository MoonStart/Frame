// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SWITCHINGCOMMANDRESULT_38DFCA5102D3_INCLUDED
#define _INC_SP_SWITCHINGCOMMANDRESULT_38DFCA5102D3_INCLUDED

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_Definitions.h"

//This class contains the result of the last command sent. It 
//contains a command IDs that is use to match with original 
//command. This is a blackboard object. There one object for 
//each protection group. These object are contained in region 
//in an order identical to command region.
//##ModelId=38DFCA5102D3
class SP_SwitchingCommandResult 
: public TEL_BbObjectBase
{
public:
	//This method returns the result of the switching command 
	//and the command ID to which it applies.
	//##ModelId=38DFCBD90074
	CT_SP_CommandID GetCommandStatus(CT_SP_CommandResultCode& theResult);

	//Class constructor.
	//##ModelId=38DFD00F011F
	SP_SwitchingCommandResult();
	//Copy constructor.
	//##ModelId=39ACEFBA0365
	SP_SwitchingCommandResult(const SP_SwitchingCommandResult& theComandResult);
	//Comparison operator.
	//##ModelId=39ACEFBA0301
    bool operator==(const SP_SwitchingCommandResult& theComandResult) const;
	//Assignment operator.
	//##ModelId=39ACEFBA02CF
    SP_SwitchingCommandResult& operator=(const SP_SwitchingCommandResult& theComandResult);

	//Class destructor.
	//##ModelId=38E201F20066
	virtual ~SP_SwitchingCommandResult();

	//This method sets the result of the switching command 
	//and the command ID to which it applies.
	//##ModelId=38EDEA6D0329
	void SetCommandStatus(CT_SP_CommandResultCode theResult, CT_SP_CommandID theCommandID);

	//Writes the attributes of the result to a stream.
	//##ModelId=3932D1E10394
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the results from a stream.
	//##ModelId=3932D1E10325
    virtual istream& ReadObject( istream& theStream );
	//Writes the attributes of the result to a binary stream.
	//##ModelId=39ACEFBA026B
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the attributes of the results from a binary 
	//stream.
	//##ModelId=39ACEFBA021B
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//The result of the command (COMPLETED, FAIL, DENIED, 
	//TIMEOUT).
	//##ModelId=38E0A7D20231
	CT_SP_CommandResultCode myResult;

	//The ID of the command that was processed.
	//##ModelId=38E0A8C0036A
	CT_SP_CommandID myCommandID;

};

#endif /* _INC_SP_SWITCHINGCOMMANDRESULT_38DFCA5102D3_INCLUDED */

