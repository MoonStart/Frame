// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_Defects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>


SP_Defects::SP_Defects():
    myOtuLOFState(false), 
    myOtuLOFCount(0),
    myOduSDBerState(false),
    myOduSDBerCount(0),
    myUpperLayerTAState(false),
    myUpperLayerTACount(0),
	myUpperLayerNTAState(false),
    myUpperLayerNTACount(0),
	myIsValidated(false),
	myDefectId(CT_SP_INVALID_COMMAND),
	myPortId(CT_INTF_ID_UNKNOWN)
{
}

SP_Defects::~SP_Defects()
{
}


void SP_Defects::Reset(void)
{
    // Initialize all attributes to default
    myOtuLOFState = false;
    myOtuLOFCount = 0;
    myOduSDBerState = false;   
    myOduSDBerCount = 0;
    myUpperLayerTAState = false;
    myUpperLayerTACount = 0;
	myUpperLayerNTAState = false;
    myUpperLayerNTACount = 0;
	myIsValidated = false;
	myDefectId= CT_SP_INVALID_COMMAND;
	myPortId= CT_INTF_ID_UNKNOWN;
}

void SP_Defects::GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const
{
    switch (theDefect)
    {
    case CT_TEL_OTU_LOF_DEFECT:
        *theState = myOtuLOFState;
        *theCount = myOtuLOFCount;
        break;
    case CT_TEL_ODU_SDBER_DEFECT:
        *theState = myOduSDBerState;
        *theCount = myOduSDBerCount;
        break;
    case CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT:
        *theState = myUpperLayerTAState;
        *theCount = myUpperLayerTACount;
        break;
	case CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT:
        *theState = myUpperLayerNTAState;
        *theCount = myUpperLayerNTACount;
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "SP_Defects: unsupported defect");
    }
}
    
bool SP_Defects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, uint32 theCount)
{
    switch (theDefect)
    {
    case CT_TEL_OTU_LOF_DEFECT:
		if (myOtuLOFState != theState || myOtuLOFCount != theCount)
		{
           myOtuLOFState = theState;
		   myOtuLOFCount = theCount;
		   return true;
		}
		break;
        
    case CT_TEL_ODU_SDBER_DEFECT:
		if (myOduSDBerState != theState || myOduSDBerCount != theCount)
		{
           myOduSDBerState = theState;
		   myOduSDBerCount = theCount;
		   return true;
		}
		break;   

    case CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT:
		if (myUpperLayerTAState != theState || myUpperLayerTACount != theCount)
		{
           myUpperLayerTAState = theState;
		   myUpperLayerTACount = theCount;
		   return true;
		}
		break; 

	case CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT:
		if (myUpperLayerNTAState != theState || myUpperLayerNTACount != theCount)
		{
           myUpperLayerNTAState = theState;
		   myUpperLayerNTACount = theCount;
		   return true;
		}
		break; 

    default:
        FC_THROW_ERROR(FC_NotSupportedError, "SP_Defects: unsupported defect");
        return false;
    }
	return false;
}

void SP_Defects::SetPortId(CT_IntfId thePortId)
{
	myPortId = thePortId;
}

ostream& SP_Defects::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(myOtuLOFState);
    theStream   << FC_InsertVar(myOtuLOFCount); 
    theStream   << FC_InsertVar(myOduSDBerState);
    theStream   << FC_InsertVar(myOduSDBerCount);
    theStream   << FC_InsertVar(myUpperLayerTAState);
    theStream   << FC_InsertVar(myUpperLayerTACount);
	theStream   << FC_InsertVar(myUpperLayerNTAState);
    theStream   << FC_InsertVar(myUpperLayerNTACount);
	theStream   << FC_InsertVar(myIsValidated);
	theStream   << FC_InsertVar(myDefectId);

	uint8 aPortId = (uint8) myPortId;
	theStream   << FC_InsertVar(aPortId);

    return theStream;
}

istream& SP_Defects::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(myOtuLOFState);
    theStream   >> FC_ExtractVar(myOtuLOFCount);    
    theStream   >> FC_ExtractVar(myOduSDBerState);
    theStream   >> FC_ExtractVar(myOduSDBerCount);
    theStream   >> FC_ExtractVar(myUpperLayerTAState);
    theStream   >> FC_ExtractVar(myUpperLayerTACount);
	 theStream   >> FC_ExtractVar(myUpperLayerNTAState);
    theStream   >> FC_ExtractVar(myUpperLayerNTACount);
    theStream   >> FC_ExtractVar(myIsValidated);
	theStream   >> FC_ExtractVar(myDefectId);

	uint8 aPortId = 0;
    theStream   >> FC_ExtractVar(aPortId);
	myPortId = (CT_IntfId) aPortId;

    return theStream;
}

FC_Stream& SP_Defects::WriteObjectBinary( FC_Stream& theStream )
{
    theStream   << myOtuLOFState;
    theStream   << myOtuLOFCount;    
    theStream   << myOduSDBerState;
    theStream   << myOduSDBerCount;
    theStream   << myUpperLayerTAState;
    theStream   << myUpperLayerTACount;
	theStream   << myUpperLayerNTAState;
    theStream   << myUpperLayerNTACount;
	theStream   << myIsValidated;
	theStream   << myDefectId;

	uint8 aPortId = (uint8) myPortId;
	theStream   << aPortId;

    return theStream;

}

FC_Stream& SP_Defects::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream   >> myOtuLOFState;
    theStream   >> myOtuLOFCount;   
    theStream   >> myOduSDBerState;
    theStream   >> myOduSDBerCount;
    theStream   >> myUpperLayerTAState;
    theStream   >> myUpperLayerTACount;
	theStream   >> myUpperLayerNTAState;
    theStream   >> myUpperLayerNTACount;
	theStream   >> myIsValidated;
	theStream   >> myDefectId;

	uint8 aPortId = 0;
    theStream   >> aPortId;
	myPortId = (CT_IntfId) aPortId;

    return theStream;

}
