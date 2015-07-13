// //Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../MON_Defects.h"
#include "../MON_Definitions.h"
#include <ErrorService/FC_Error.h>



//##ModelId=3C1785A90007
MON_Defects::MON_Defects(uint32 theIndex):
    MON_Object(theIndex)
{
}

//##ModelId=3C1785A90011
MON_Defects::~MON_Defects()
{
}

//##ModelId=3C7170F7004A
bool MON_Defects::UpdateDefect(bool theNewState,      bool theNewTransition,
                               bool* theCurrentState, uint32* theCurrentCounter)
{
    FC_THROW_ERROR_IF(theCurrentState==NULL || theCurrentCounter==NULL,
                      FC_RuntimeError,
                      "Cannot update defects");

    // keep track of any changes
    bool hasChanged = false;

    // incrment transition counter if rising edge detected
    if HAS_CHANGED (*theCurrentState, theNewState, theNewTransition) 
    {
        (*theCurrentCounter)++;
        hasChanged = true;
    }

    // update state of defect
    if (*theCurrentState != theNewState)
    {
        *theCurrentState = theNewState;
        hasChanged = true;
    }

    return hasChanged;
}


//##ModelId=3C7170F70035
bool MON_Defects::IsLayerInDefects() const
{
    return false;
}

bool MON_Defects::IsLayerForMaintSigInDefects() const
{
    return false;
}

bool MON_Defects::GetDefectForMaintSig(CT_TEL_Defect theDefect) const
{
    return theDefect;
}

bool MON_Defects::IsInPropagateNextLayerDefectsTA() const
{
    return false;
}

bool MON_Defects::IsLayerForMaintSigInNonPropagateDefectsNTA() const
{
    return false;
}

bool MON_Defects::IsLayerInDefectsNTA() const
{
    return false;
}

bool MON_Defects::IsLayerLocked() const
{
    return false;
}


uint8 MON_Defects::GetLockBitMask() const
{
    return 0;
}

uint8 MON_Defects::GetInternalLockBitMask() const
{
    return 0;
}

bool MON_Defects::IsOtuLayerLocked(uint8 theBitMask) const
{
    return false;
}

bool MON_Defects::IsAnyTcmLevelLocked(uint8 theBitMask) const
{
    return false;
}


bool MON_Defects::IsLayerInternalInDefects() const
{
    return false;
}

bool MON_Defects::IsLayerInternalForMaintSigInDefects() const
{
    return false;
}

bool MON_Defects::IsInternalInPropagateNextLayerDefectsTA() const
{
    return false;
}

bool MON_Defects::IsLayerInternalInDefectsNTA() const
{
    return false;
}

bool MON_Defects::IsLayerInternalLocked() const
{
    return false;
}


bool MON_Defects::IsLayerInTermLpbk() const
{
    return false;
}

bool MON_Defects::IsConnectedAsSrc() const
{
    return false;
}

bool MON_Defects::IsConnectedAsDst() const
{
    return false;
}



bool MON_Defects::IsLayerInNonPropagateDefectsNTA() const
{
    return false;
}

bool MON_Defects::IsIgnoreDirectUpperLayerDefects() const
{
    return false;
}

bool MON_Defects::IsAdaptionLayerInDefectsTA() const
{
    return false;
}

bool MON_Defects::IsBDIForcedForDefects() const
{
    return false;
}

bool MON_Defects::IsLayerInDegrade() const
{
    return false;
}

bool MON_Defects::IsMateLayerInDefects() const
{
    return false;
}

//##ModelId=3C1785BB0158
ostream& MON_Defects::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    return theStream;
}

//##ModelId=3C1785BB0162
istream& MON_Defects::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    return theStream;
}

//##ModelId=3C1785BB016C
FC_Stream& MON_Defects::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    return theStream;
}

//##ModelId=3C1785BB016E
FC_Stream& MON_Defects::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    return theStream;
}
