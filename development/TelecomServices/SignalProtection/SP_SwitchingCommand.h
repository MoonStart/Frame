// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SWITCHINGCOMMAND_38DFC40203C1_INCLUDED
#define _INC_SP_SWITCHINGCOMMAND_38DFC40203C1_INCLUDED

#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_SignalProtection.h>

//This class contains the switch command for its 
//corresponding protection group.
class CT_SP_CommandType;

//This class contains the switch command for its 
//corresponding protection group. This is a blackboard 
//object. There one object for each protection group. These 
//object are contained in region in an order identical to 
//configuration and status.
//##ModelId=38DFC40203C1
class SP_SwitchingCommand 
: public TEL_BbObjectBase
{
public:
	//This method forces the execution of the given switch 
	//command (MS-W,MS-P, FS-W, FS-P, LP, CLR for 1+1, MS-S, 
	//MS-R, FS-S, FS-R, LP-S, EXER-S, EXER-P, CLR for CLSR). 
	//A command counter is returned.
	//##ModelId=38DFC0FF0232
    CT_SP_CommandID SetCommand(CT_SP_Request theCommand, bool incCommandId=true);

	//Class constructor.
	//##ModelId=38DFCFDC03D8
	SP_SwitchingCommand();

	//This method returns the current switch command 
	//(MS-W,MS-P, FS-W, FS-P, LP, CLR for 1+1, MS-S, MS-R, 
	//FS-S, FS-R, LP-S, EXER-S, EXER-P, CLR for CLSR). It 
	//also returns a command ID in reference.
	//##ModelId=38E0AF7D0284
	 CT_SP_Request& GetCommand();
	//Returns the ID of the command.
	//##ModelId=3911AE76001D
	 CT_SP_CommandID& GetCommandID();

	//Class destructor.
	//##ModelId=38E201EC018A
	virtual ~SP_SwitchingCommand();

	//Writes the attributes of the command to a stream.
	//##ModelId=3932D1D40150
    virtual ostream& WriteObject( ostream& theStream );
	//Reads the attributes of the command from a stream.
	//##ModelId=3932D1D400EC
    virtual istream& ReadObject( istream& theStream );
	//Writes the attributes of the command to a binary stream.
	//##ModelId=39ACEFAA0087
	virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
	//Reads the attributes of the command from a binary 
	//stream.
	//##ModelId=39ACEFAA0055
	virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
	//The current command to apply on the group. The command 
	//is a typedef of type CT_SP_Request. Different request 
	//type a define for each protection type.
	//##ModelId=38DFC85C00F2
	CT_SP_Request myCommand;

	//The ID of the command. This ID is derived from a statis 
	//counter and is used for matching command with incoming 
	//result.
	//##ModelId=38DFC86201B9
	CT_SP_CommandID myCommandID;

};

#endif /* _INC_SP_SWITCHINGCOMMAND_38DFC40203C1_INCLUDED */

