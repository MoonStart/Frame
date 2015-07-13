// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_Defects_3C1785620164_INCLUDED
#define _INC_MON_Defects_3C1785620164_INCLUDED

#include "MON_Object.h"

//This is the base class for defects monitoring. It is a 
//MON_Object.
//##ModelId=3C1785620164
class MON_Defects 
: public MON_Object
{
public:
	//Returns the status and count of the defect provide as 
	//argument.
	//##ModelId=3C17511B020A
	virtual void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const = 0;
	//##ModelId=3C18E9350380
    // Returns true if defect status has changed.
	//##ModelId=3C18E9350380
    virtual bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition) = 0;

    virtual bool GetDefectForMaintSig(CT_TEL_Defect theDefect) const;
        
	//Constructor.
	//##ModelId=3C1785A90007
	MON_Defects(uint32 theIndex);

	//Virtual destructor.
	//##ModelId=3C1785A90011
	virtual ~MON_Defects();

	//##ModelId=3C7170F70035
    virtual bool IsLayerInDefects() const;

    virtual bool IsLayerForMaintSigInDefects() const;

    virtual bool IsInPropagateNextLayerDefectsTA() const;

    virtual bool IsLayerInDefectsNTA() const;

    virtual bool IsLayerLocked() const;


    virtual uint8 GetLockBitMask() const;

    virtual uint8 GetInternalLockBitMask() const;

    virtual bool IsOtuLayerLocked(uint8 theBitMask) const;

    virtual bool IsAnyTcmLevelLocked(uint8 theBitMask) const;


    // New for 5.1, Intrnal Failure/Lock is propagated
    virtual bool IsLayerInternalInDefects() const;

    virtual bool IsLayerInternalForMaintSigInDefects() const;

    virtual bool IsInternalInPropagateNextLayerDefectsTA() const;

    virtual bool IsLayerForMaintSigInNonPropagateDefectsNTA() const;

    virtual bool IsLayerInternalInDefectsNTA() const;

    virtual bool IsLayerInternalLocked() const;


    virtual bool IsLayerInTermLpbk() const;

    virtual bool IsConnectedAsSrc() const;

    virtual bool IsConnectedAsDst() const;

    virtual bool IsLayerInNonPropagateDefectsNTA() const;
    virtual bool IsIgnoreDirectUpperLayerDefects() const;    

    virtual bool IsAdaptionLayerInDefectsTA() const;
    virtual bool IsBDIForcedForDefects() const;

    virtual bool IsLayerInDegrade() const;

    virtual bool IsMateLayerInDefects() const;

protected:
	//##ModelId=3C7170F7004A
    bool UpdateDefect(bool theNewState,      bool theNewTransition,
                      bool* theCurrentState, uint32* theCurrentCounter);

	//##ModelId=3C1785BB0158
	virtual ostream& WriteObject(ostream& theStream);

	//##ModelId=3C1785BB0162
	virtual istream& ReadObject(istream& theStream);

	//##ModelId=3C1785BB016C
	virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);

	//##ModelId=3C1785BB016E
	virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);

};



#endif /* _INC_MON_Defects_3C1785620164_INCLUDED */
