//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Lprf.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Lprf::CFG_Lprf(uint32 theIndex):
    CFG_Object(theIndex),
    myTransferMode(CT_LPF_UNKNOWN),
    myRetransmissionCount(0),
    myAckWaitTimer(0),
    myMaxFrameSize(0),
    myFrameCount(0),
    myInactivityTimer(0),
    mySideAssignment(CT_LPF_Unknown),
    mySequenceRange(0)
{
}

CFG_Lprf::~CFG_Lprf(void)
{
}


void CFG_Lprf::SetTransferMode(CT_LPF_TxMode theTransferMode)
{
    myTransferMode = theTransferMode;
}

CT_LPF_TxMode CFG_Lprf::GetTransferMode() const
{
    return myTransferMode;
}


void CFG_Lprf::SetRetransmissionCount(uint8 theRetransmissionCount)
{
    myRetransmissionCount = theRetransmissionCount;
}

uint8 CFG_Lprf::GetRetransmissionCount() const
{
    return myRetransmissionCount;
}

void CFG_Lprf::SetAckWaitTimer(uint16 theAckWaitTimer)
{
    myAckWaitTimer = theAckWaitTimer;
}

uint16 CFG_Lprf::GetAckWaitTimer() const
{
    return myAckWaitTimer;
}

void CFG_Lprf::SetMaxFrameSize(uint16 theMaxFrameSize)
{
    myMaxFrameSize = theMaxFrameSize;
}

uint16 CFG_Lprf::GetMaxFrameSize() const
{
    return myMaxFrameSize;
}

void CFG_Lprf::SetFrameCount(uint8 theFrameCount)
{
    myFrameCount = theFrameCount;
}

uint8 CFG_Lprf::GetFrameCount() const
{
    return myFrameCount;
}

void CFG_Lprf::SetInactivityTimer(uint16 theInactivityTimer)
{
    myInactivityTimer = theInactivityTimer;
}

uint16 CFG_Lprf::GetInactivityTimer() const
{
    return myInactivityTimer;
}


void CFG_Lprf::SetSideAssignment(CT_LPF_Side theSideAssignment)
{
    mySideAssignment = theSideAssignment;
}

CT_LPF_Side CFG_Lprf::GetSideAssignment() const
{
    return mySideAssignment;
}


void CFG_Lprf::SetSequenceRange(uint8 theSequenceRange)
{
    mySequenceRange = theSequenceRange;
}

uint8 CFG_Lprf::GetSequenceRange() const
{
    return mySequenceRange;
}


void CFG_Lprf::Reset(void)
{
    // Initialize all attributes to default values.
    myTransferMode = CT_LPF_UNKNOWN;
    myRetransmissionCount = 0;
    myAckWaitTimer = 0;
    myMaxFrameSize = 0;
    myFrameCount = 0;
    myInactivityTimer = 0;
    mySideAssignment = CT_LPF_Unknown;
    mySequenceRange = 0;
}

// For Display
ostream& CFG_Lprf::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint8 aTransferMode = myTransferMode;
    theStream   << FC_InsertVar(aTransferMode);

    theStream   << FC_InsertVar(myRetransmissionCount);
    theStream   << FC_InsertVar(myAckWaitTimer);
    theStream   << FC_InsertVar(myMaxFrameSize);
    theStream   << FC_InsertVar(myFrameCount);
    theStream   << FC_InsertVar(myInactivityTimer);

    uint8 aSideAssignment = mySideAssignment;
    theStream   << FC_InsertVar(aSideAssignment);

    theStream   << FC_InsertVar(mySequenceRange);

    return theStream;
}

istream& CFG_Lprf::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint8 aTransferMode = 0;
    theStream   >> FC_ExtractVar(aTransferMode);
    myTransferMode = (CT_LPF_TxMode) aTransferMode;

    theStream   >> FC_ExtractVar(myRetransmissionCount);
    theStream   >> FC_ExtractVar(myAckWaitTimer);
    theStream   >> FC_ExtractVar(myMaxFrameSize);
    theStream   >> FC_ExtractVar(myFrameCount);
    theStream   >> FC_ExtractVar(myInactivityTimer);

    uint8 aSideAssignment = 0;
    theStream   >> FC_ExtractVar(aSideAssignment);
    mySideAssignment = (CT_LPF_Side) aSideAssignment;

    theStream   >> FC_ExtractVar(mySequenceRange);

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Lprf::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << (uint8) myTransferMode;

    theStream   << myRetransmissionCount;
    theStream   << myAckWaitTimer;
    theStream   << myMaxFrameSize;
    theStream   << myFrameCount;
    theStream   << myInactivityTimer;

    theStream   << (uint8) mySideAssignment;

    theStream   << mySequenceRange;

    return theStream;
}

FC_Stream& CFG_Lprf::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint8 aTransferMode = 0;
    theStream   >> aTransferMode;
    myTransferMode = (CT_LPF_TxMode) aTransferMode;

    theStream   >> myRetransmissionCount;
    theStream   >> myAckWaitTimer;
    theStream   >> myMaxFrameSize;
    theStream   >> myFrameCount;
    theStream   >> myInactivityTimer;

    uint8 aSideAssignment = 0;
    theStream   >> aSideAssignment;
    mySideAssignment = (CT_LPF_Side) aSideAssignment;

    theStream   >> mySequenceRange;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Lprf::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto LPRFERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"tran",4))
    {
        SetTransferMode(CFG_STRING_TO_TRANSFER_MODE(argv[1]));
    }
    else if (!strncmp(aParam,"retra",5))
    {
        SetRetransmissionCount(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"ackwa",5))
    {
        SetAckWaitTimer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"maxfr",5))
    {
        SetMaxFrameSize(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"frame",5))
    {
        SetFrameCount(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"inact",5))
    {
        SetInactivityTimer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"side",4))
    {
        SetSideAssignment(CFG_STRING_TO_SIDE_ASSIGNMENT(argv[1]));
    }
    else if (!strncmp(aParam,"sequ",4))
    {
        SetSequenceRange(uint8(atoi(argv[1])));
    }
    else
    {
        goto LPRFERROR;
    }


    return FC_CmdProcessor::E_SUCCESS;

LPRFERROR:
    {
        fc_cout << "lprf transfer      <uits|aits|qos> " << endl;
        fc_cout << "lprf retranscount  <2-16> " << endl;
        fc_cout << "lprf ackwaittimer  <200-20000> (ms)" << endl;
        fc_cout << "lprf maxframesize  <512-1500>" << endl;
        fc_cout << "lprf framecount    <1-127>" << endl;
        fc_cout << "lprf inactivitytim <4-300> (sec)" << endl;
        fc_cout << "lprf sideassign    <user|network|auto> " << endl;
        fc_cout << "lprf sequencerange <4-300> (sec)" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Lprf::Display( FC_Stream& theStream )
{
    theStream   << "LPRF     - Transfer Mode       [transfer]      = " << DISPLAY_LPF_TRANSFER_MODE(myTransferMode) << endl;
    theStream   << "LPRF     - Retransmission Cnt  [retranscount]  = " << uint32(myRetransmissionCount) << endl;
    theStream   << "LPRF     - Ack Wait Timer (ms) [ackwaittimer]  = " << uint32(myAckWaitTimer) << endl;
    theStream   << "LPRF     - Max Frame Size      [maxframesize]  = " << uint32(myMaxFrameSize) << endl;
    theStream   << "LPRF     - Frame Count         [framecount]    = " << uint32(myFrameCount) << endl;
    theStream   << "LPRF     - Inactivity Timer(s) [inactivitytim] = " << uint32(myInactivityTimer) << endl;
    theStream   << "LPRF     - Side Assignment     [sideassign]    = " << DISPLAY_LPF_SIDE(mySideAssignment) << endl;
    theStream   << "LPRF     - Sequence Range      [sequencerange] = " << uint32(mySequenceRange) << endl;
}

