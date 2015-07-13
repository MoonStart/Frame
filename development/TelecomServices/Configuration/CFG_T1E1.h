/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_T1E1OBJECT_H
#define CFG_T1E1OBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SystemIds.h>
#include <vector>

#include "CFG_Object.h"


//This object contains all the T1E1 configuration.
class CFG_T1E1
: public CFG_Object
{

public:

    //Constructor.
    CFG_T1E1(uint32 theIndex);

    //Virtual destructor.
    virtual ~CFG_T1E1(void);

    //This method is used to indicate that the T1E1 facility is configured (for LED).
    void SetT1E1Enable(bool theT1E1Enable);

    //This method returns the state of the T1E1 facility.
    bool GetT1E1Enable() const;


    // Set T1E1 Line Code
    void SetT1E1LineCoding(CT_FAC_LineCode theT1E1LineCode);

    //Get T1E1 Line Code
    CT_FAC_LineCode GetT1E1LineCoding() const;


    // Set T1E1 Framing  type
    void SetT1E1FramingType(CT_FAC_FrameFormat theT1E1FramingType);

    //Get T1E1 Framing type
    CT_FAC_FrameFormat GetT1E1FramingType() const;


    // Set one item of the list of clock output enables that support the T1E1 facility
    void SetClkOutEnable(uint32 theSlotNum, bool theClkOutEnable);

    // Get one item of the list of clock output enables that support the T1E1 facility
    bool GetClkOutEnable(uint32 theSlotNum);


    // Set list of clock output enables that support the T1E1 facility
    void SetClkOutEnableList(vector<bool>& theClkOutEnableList);

    // Get list of clock output enables that support the T1E1 facility
    const vector<bool>& GetClkOutEnableList();


    // Add item to list of clock output enables that support the T1E1 facility
    void AddToClkOutEnableList(bool theInitialValue);

    //Set timing source shelf
    void SetTimingSourceShelf(CT_ShelfId sourceShelf);

    //Get timing source shelf
    CT_ShelfId GetTimingSourceShelf() const;

    //Set timing source slot
    void SetTimingSourceSlot(CT_SlotId sourceSlot);

    //Get timing source slot
    CT_SlotId GetTimingSourceSlot() const;

    //Set SA BIT
    void SetSABIT(CT_FAC_SaBit theSABIT);

    //Get configured SA BIT
    CT_FAC_SaBit GetSABIT() const;

    //Set QL override value
    void SetQualityLevelOverride(CT_FAC_QualityLevelOverride theQLOverride);

    //Get configured QL override value
    CT_FAC_QualityLevelOverride GetQualityLevelOverride();


    //Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);


protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );


private:
    // Set to true if the T1E1 facility is enabled
    bool myT1E1Enable;

    //The T1E1 Line Code configured
    CT_FAC_LineCode    myT1E1LineCode;

    //The T1E1 Framing Type configured
    CT_FAC_FrameFormat myT1E1FramingType;

    // List of clock output enables that support the T1E1 facility
    vector<bool> myClkOutEnableList;

    //Shelf Id for the reference source
    CT_ShelfId myTimingSourceShelf;

    //Slot Id for the reference source
    CT_SlotId myTimingSourceSlot;

    //SSM bits
    CT_FAC_SaBit mySABIT;

    //QL override
    CT_FAC_QualityLevelOverride myQLOverride;

};

#endif /* CFG_T1E1OBJECT_H */

