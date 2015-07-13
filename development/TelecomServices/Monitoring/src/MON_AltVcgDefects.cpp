// Copyright(c) Tellabs Transport Group. All rights reserved

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../MON_AltVcgDefects.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include "../MON_Definitions.h"

MON_AltVcgDefects::MON_AltVcgDefects(uint32 theIndex):
    MON_Defects(theIndex),
    myTX_TLCCount(0),
    myTX_PLCCount(0),
    myRX_TLCCount(0),
    myRX_PLCCount(0),
    myLOS_AlignCount(0),
    myLOS_MF_AlignCount(0),
    myTX_FOPCount(0),
    myRX_FOPCount(0),
    mySeqMisMatchCount(0),
    myMbrNotDeSkewCount(0),
    myIsConnectedAsSrcCount(0),
    myIsConnectedAsDstCount(0),
    myTX_TLCState(false),
    myTX_PLCState(false),
    myRX_TLCState(false),
    myRX_PLCState(false),
    myLOS_AlignState(false),
    myLOS_MF_AlignState(false),
    myTX_FOPState(false),
    myRX_FOPState(false),
    mySeqMisMatchState(false),
    myMbrNotDeSkewState(false),
    myIsConnectedAsSrcState(false),
    myIsConnectedAsDstState(false)
{
}

MON_AltVcgDefects::~MON_AltVcgDefects()
{
}

bool MON_AltVcgDefects::IsLayerInDefects() const
{
    bool aIsLayerFail = myTX_TLCState || myTX_PLCState || myRX_TLCState || myRX_PLCState || myLOS_AlignState || myLOS_MF_AlignState
                       || myTX_FOPState || myRX_FOPState || mySeqMisMatchState;
    
    return aIsLayerFail && IsValidated();
}

bool MON_AltVcgDefects::IsConnectedAsSrc() const
{
    return myIsConnectedAsSrcState && IsValidated();
}

bool MON_AltVcgDefects::IsConnectedAsDst() const
{
    return myIsConnectedAsDstState && IsValidated();
}


void MON_AltVcgDefects::Reset(void)
{
    // Initialize all attributes to default values.
    MON_Defects::Reset();
    myTX_TLCCount = 0;
    myTX_PLCCount = 0;
    myRX_TLCCount = 0;
    myRX_PLCCount = 0;
    myLOS_AlignCount = 0;
    myLOS_MF_AlignCount = 0;
    myTX_FOPCount = 0;
    myRX_FOPCount = 0;
    mySeqMisMatchCount = 0;
    myMbrNotDeSkewCount = 0;
    myIsConnectedAsSrcCount = 0;
    myIsConnectedAsDstCount = 0;

    myTX_TLCState = false;
    myTX_PLCState = false;
    myRX_TLCState = false;
    myRX_PLCState = false;
    myLOS_AlignState = false;
    myLOS_MF_AlignState = false;
    myTX_FOPState = false;
    myRX_FOPState = false;
    mySeqMisMatchState = false;
    myMbrNotDeSkewState = false;
    myIsConnectedAsSrcState = false;
    myIsConnectedAsDstState = false;

}

void MON_AltVcgDefects::GetDefectStatus(CT_TEL_Defect theDefect, 
                                    uint32* theCount, 
                                    bool* theState) const
{
    // Return all current counts and states filtered.

    switch (theDefect)
    {
    case CT_TEL_VCG_TX_TLC:
        *theCount = myTX_TLCCount;
        *theState = myTX_TLCState;
        break;
    case CT_TEL_VCG_TX_PLC:
        *theCount = myTX_PLCCount;
        *theState = myTX_PLCState;
        break;
    case CT_TEL_VCG_RX_TLC:
        *theCount = myRX_TLCCount;
        *theState = myRX_TLCState;
        break;
    case CT_TEL_VCG_RX_PLC:
        *theCount = myRX_PLCCount;
        *theState = myRX_PLCState;
        break;
    case CT_TEL_VCG_LOS_ALIGN:
        *theCount = myLOS_AlignCount;
        *theState = myLOS_AlignState;
        break;
    case CT_TEL_VCG_LOS_MF_ALIGN:
        *theCount = myLOS_MF_AlignCount;
        *theState = myLOS_MF_AlignState;
        break;
    case CT_TEL_VCG_TX_FOP:
        *theCount = myTX_FOPCount;
        *theState = myTX_FOPState;
        break;
    case CT_TEL_VCG_RX_FOP:
        *theCount = myRX_FOPCount;
        *theState = myRX_FOPState;
        break;
    case CT_TEL_VCG_SEQMISMATCH:
        *theCount = mySeqMisMatchCount;
        *theState = mySeqMisMatchState;
        break;
    case CT_TEL_VCG_MBR_NOT_DESKEWABLE:
        *theCount = myMbrNotDeSkewCount;
        *theState = myMbrNotDeSkewState;
        break;
    case CT_TEL_VCG_IS_SRC:
        *theState = myIsConnectedAsSrcState;
        *theCount = myIsConnectedAsSrcCount;
        break;
    case CT_TEL_VCG_IS_DST:
        *theState = myIsConnectedAsDstState;
        *theCount = myIsConnectedAsDstCount;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "MON_AltVcgDefects: defect not supported");
        break;
    }

}

bool MON_AltVcgDefects::SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition)
{
    switch (theDefect)
    {
    case CT_TEL_VCG_TX_TLC:
        return UpdateDefect(theState, theTransition, &myTX_TLCState, &myTX_TLCCount);
    case CT_TEL_VCG_TX_PLC:
        return UpdateDefect(theState, theTransition, &myTX_PLCState, &myTX_PLCCount);
    case CT_TEL_VCG_RX_TLC:
        return UpdateDefect(theState, theTransition, &myRX_TLCState, &myRX_TLCCount);
    case CT_TEL_VCG_RX_PLC:
        return UpdateDefect(theState, theTransition, &myRX_PLCState, &myRX_PLCCount);
    case CT_TEL_VCG_LOS_ALIGN:
       return UpdateDefect(theState, theTransition, &myLOS_AlignState, &myLOS_AlignCount); 
    case CT_TEL_VCG_LOS_MF_ALIGN:
       return UpdateDefect(theState, theTransition, &myLOS_MF_AlignState, &myLOS_MF_AlignCount); 
    case CT_TEL_VCG_TX_FOP:
       return UpdateDefect(theState, theTransition, &myTX_FOPState, &myTX_FOPCount); 
    case CT_TEL_VCG_RX_FOP:
       return UpdateDefect(theState, theTransition, &myRX_FOPState, &myRX_FOPCount); 
    case CT_TEL_VCG_SEQMISMATCH:
       return UpdateDefect(theState, theTransition, &mySeqMisMatchState, &mySeqMisMatchCount); 
    case CT_TEL_VCG_MBR_NOT_DESKEWABLE:
       return UpdateDefect(theState, theTransition, &myMbrNotDeSkewState, &myMbrNotDeSkewCount); 
    case CT_TEL_VCG_IS_SRC:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsSrcState, &myIsConnectedAsSrcCount);
    case CT_TEL_VCG_IS_DST:
        return UpdateDefect(theState, theTransition, &myIsConnectedAsDstState, &myIsConnectedAsDstCount);
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_AltVcgDefects: unsupported defect");
        return false;
    }
}

ostream& MON_AltVcgDefects::WriteObject( ostream& theStream )
{
    MON_Defects::WriteObject(theStream);
    theStream << FC_InsertVar(myTX_TLCState);
    theStream << FC_InsertVar(myTX_TLCCount);
    theStream << FC_InsertVar(myTX_PLCState);
    theStream << FC_InsertVar(myTX_PLCCount);
    theStream << FC_InsertVar(myRX_TLCState);
    theStream << FC_InsertVar(myRX_TLCCount);
    theStream << FC_InsertVar(myRX_PLCState);
    theStream << FC_InsertVar(myRX_PLCCount);
    theStream << FC_InsertVar(myLOS_AlignState);
    theStream << FC_InsertVar(myLOS_AlignCount);
    theStream << FC_InsertVar(myLOS_MF_AlignState);
    theStream << FC_InsertVar(myLOS_MF_AlignCount);
    theStream << FC_InsertVar(myTX_FOPState);
    theStream << FC_InsertVar(myTX_FOPCount);
    theStream << FC_InsertVar(myRX_FOPState);
    theStream << FC_InsertVar(myRX_FOPCount);
    theStream << FC_InsertVar(mySeqMisMatchState);
    theStream << FC_InsertVar(mySeqMisMatchCount);
    theStream << FC_InsertVar(myMbrNotDeSkewState);
    theStream << FC_InsertVar(myMbrNotDeSkewCount);
    theStream << FC_InsertVar(myIsConnectedAsSrcState);
    theStream << FC_InsertVar(myIsConnectedAsSrcCount);
    theStream << FC_InsertVar(myIsConnectedAsDstState);
    theStream << FC_InsertVar(myIsConnectedAsDstCount);

    return theStream;
}

istream& MON_AltVcgDefects::ReadObject( istream& theStream )
{
    MON_Defects::ReadObject(theStream);
    theStream >> FC_ExtractVar(myTX_TLCState);
    theStream >> FC_ExtractVar(myTX_TLCCount);
    theStream >> FC_ExtractVar(myTX_PLCState);
    theStream >> FC_ExtractVar(myTX_PLCCount);
    theStream >> FC_ExtractVar(myRX_TLCState);
    theStream >> FC_ExtractVar(myRX_TLCCount);
    theStream >> FC_ExtractVar(myRX_PLCState);
    theStream >> FC_ExtractVar(myRX_PLCCount);
    theStream >> FC_ExtractVar(myLOS_AlignState);
    theStream >> FC_ExtractVar(myLOS_AlignCount);
    theStream >> FC_ExtractVar(myLOS_MF_AlignState);
    theStream >> FC_ExtractVar(myLOS_MF_AlignCount);
    theStream >> FC_ExtractVar(myTX_FOPState);
    theStream >> FC_ExtractVar(myTX_FOPCount);
    theStream >> FC_ExtractVar(myRX_FOPState);
    theStream >> FC_ExtractVar(myRX_FOPCount);
    theStream >> FC_ExtractVar(mySeqMisMatchState);
    theStream >> FC_ExtractVar(mySeqMisMatchCount);
    theStream >> FC_ExtractVar(myMbrNotDeSkewState);
    theStream >> FC_ExtractVar(myMbrNotDeSkewCount);
    theStream >> FC_ExtractVar(myIsConnectedAsSrcState);
    theStream >> FC_ExtractVar(myIsConnectedAsSrcCount);
    theStream >> FC_ExtractVar(myIsConnectedAsDstState);
    theStream >> FC_ExtractVar(myIsConnectedAsDstCount);

    return theStream;
}

FC_Stream& MON_AltVcgDefects::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Defects::WriteObjectBinary(theStream);
    theStream << myTX_TLCState;
    theStream << myTX_TLCCount;
    theStream << myTX_PLCState;
    theStream << myTX_PLCCount;
    theStream << myRX_TLCState;
    theStream << myRX_TLCCount;
    theStream << myRX_PLCState;
    theStream << myRX_PLCCount;
    theStream << myLOS_AlignState;
    theStream << myLOS_AlignCount;
    theStream << myLOS_MF_AlignState;
    theStream << myLOS_MF_AlignCount;
    theStream << myTX_FOPState;
    theStream << myTX_FOPCount;
    theStream << myRX_FOPState;
    theStream << myRX_FOPCount;
    theStream << mySeqMisMatchState;
    theStream << mySeqMisMatchCount;
    theStream << myMbrNotDeSkewState;
    theStream << myMbrNotDeSkewCount;
    theStream << myIsConnectedAsSrcState;
    theStream << myIsConnectedAsSrcCount;
    theStream << myIsConnectedAsDstState;
    theStream << myIsConnectedAsDstCount;

    return theStream;
}

FC_Stream& MON_AltVcgDefects::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Defects::ReadObjectBinary(theStream);
    theStream >> myTX_TLCState;
    theStream >> myTX_TLCCount;
    theStream >> myTX_PLCState;
    theStream >> myTX_PLCCount;
    theStream >> myRX_TLCState;
    theStream >> myRX_TLCCount;
    theStream >> myRX_PLCState;
    theStream >> myRX_PLCCount;
    theStream >> myLOS_AlignState;
    theStream >> myLOS_AlignCount;
    theStream >> myLOS_MF_AlignState;
    theStream >> myLOS_MF_AlignCount;
    theStream >> myTX_FOPState;
    theStream >> myTX_FOPCount;
    theStream >> myRX_FOPState;
    theStream >> myRX_FOPCount;
    theStream >> mySeqMisMatchState;
    theStream >> mySeqMisMatchCount;
    theStream >> myMbrNotDeSkewState;
    theStream >> myMbrNotDeSkewCount;
    theStream >> myIsConnectedAsSrcState;
    theStream >> myIsConnectedAsSrcCount;
    theStream >> myIsConnectedAsDstState;
    theStream >> myIsConnectedAsDstCount;

    return theStream;
}

void MON_AltVcgDefects::Display(FC_Stream& theStream)
{
    MON_Defects::Display(theStream);
    theStream   << "VCG - TX TLC               = " << DISPLAY_BOOL(myTX_TLCState) << " (" << myTX_TLCCount << ")"<< endl;
    theStream   << "VCG - TX PLC               = " << DISPLAY_BOOL(myTX_PLCState) << " (" << myTX_PLCCount << ")"<< endl;
    theStream   << "VCG - RX TLC               = " << DISPLAY_BOOL(myRX_TLCState) << " (" << myRX_TLCCount << ")"<< endl;
    theStream   << "VCG - RX PLC               = " << DISPLAY_BOOL(myRX_PLCState) << " (" << myRX_PLCCount << ")"<< endl;
    theStream   << "VCG - LOS ALIGN            = " << DISPLAY_BOOL(myLOS_AlignState) << " (" << myLOS_AlignCount << ")"<< endl;
    theStream   << "VCG - LOS MF ALIGN         = " << DISPLAY_BOOL(myLOS_MF_AlignState) << " (" << myLOS_MF_AlignCount << ")"<< endl;
    theStream   << "VCG - TX FOP               = " << DISPLAY_BOOL(myTX_FOPState) << " (" << myTX_FOPCount << ")"<< endl;
    theStream   << "VCG - RX FOP               = " << DISPLAY_BOOL(myRX_FOPState) << " (" << myRX_FOPCount << ")"<< endl;
    theStream   << "VCG - SEQ MISMATCH         = " << DISPLAY_BOOL(mySeqMisMatchState) << " (" << mySeqMisMatchCount << ")"<< endl;
    theStream   << "VCG - MBR NOT DE-SKEWABLE  = " << DISPLAY_BOOL(myMbrNotDeSkewState) << " (" << myMbrNotDeSkewCount << ")"<< endl;
    theStream   << "VCG - IS CONNECTED AS SRC  = " << DISPLAY_BOOL(myIsConnectedAsSrcState) << " (" << myIsConnectedAsSrcCount << ")" << endl;
    theStream   << "VCG - IS CONNECTED AS DEST = " << DISPLAY_BOOL(myIsConnectedAsDstState) << " (" << myIsConnectedAsDstCount << ")" << endl;

}
