//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Tarp.h"
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>
#include <CommonTypes/CT_FacilityIds.h>


CFG_Tarp::CFG_Tarp(uint32 theIndex):
    CFG_Object(theIndex)
{
    Reset();
}

CFG_Tarp::~CFG_Tarp(void)
{
}


// Set TARP Flush Timer
void CFG_Tarp::SetFlushTimer(uint16 theFlushTimer)
{
    myFlushTimer = theFlushTimer;
}

//Get TARP Flush Timer
uint16 CFG_Tarp::GetFlushTimer() const
{
    return myFlushTimer;
}


// Set TARP Entry Timer
void CFG_Tarp::SetEntryTimer(uint8 theEntryTimer)
{
    myEntryTimer = theEntryTimer;
}

//Get TARP Entry Timer
uint8 CFG_Tarp::GetEntryTimer() const
{
    return myEntryTimer;
}


// Set TARP Type1 Timer
void CFG_Tarp::SetType1Timer(uint16 theType1Timer)
{
    myType1Timer = theType1Timer;
}

//Get TARP Type1 Timer
uint16 CFG_Tarp::GetType1Timer() const
{
    return myType1Timer;
}


// Set TARP Type2 Timer
void CFG_Tarp::SetType2Timer(uint16 theType2Timer)
{
    myType2Timer = theType2Timer;
}

//Get TARP Type2 Timer
uint16 CFG_Tarp::GetType2Timer() const
{
    return myType2Timer;
}


// Set TARP Type3 Timer
void CFG_Tarp::SetType3Timer(uint16 theType3Timer)
{
    myType3Timer = theType3Timer;
}

//Get TARP Type3 Timer
uint16 CFG_Tarp::GetType3Timer() const
{
    return myType3Timer;
}


// Set TARP Type4 Timer
void CFG_Tarp::SetType4Timer(uint16 theType4Timer)
{
    myType4Timer = theType4Timer;
}

//Get TARP Type4 Timer
uint16 CFG_Tarp::GetType4Timer() const
{
    return myType4Timer;
}


// Set TARP Protocol Address
void CFG_Tarp::SetProtocolAddr(uint8 theProtocolAddr)
{
    myProtocolAddr = theProtocolAddr;
}

//Get TARP Protocol Address
uint8 CFG_Tarp::GetProtocolAddr() const
{
    return myProtocolAddr;
}


//This method is used to Reset the Sequence Counter
void CFG_Tarp::SetResetSequenceCounter(uint8 theResetSequenceCounter)
{
    myResetSequenceCounter = theResetSequenceCounter;
}

//This method returns the value of Reset the Sequence Counter.
uint8 CFG_Tarp::GetResetSequenceCounter() const
{
    return myResetSequenceCounter;
}


// Set Tarp Lifetime Hops
void CFG_Tarp::SetLifetimeHops(uint16 theLifetimeHops)
{
    myLifetimeHops = theLifetimeHops;
}

//Get Tarp Lifetime Hops
uint16 CFG_Tarp::GetLifetimeHops() const
{
    return myLifetimeHops;
}

//Set TARP Flush Count
void CFG_Tarp::SetFlushCounter( uint32 theFlushCounter )
{
    myFlushCounter = theFlushCounter;
}

//Get TARP Flush Count
uint32 CFG_Tarp::GetFlushCounter(  ) const
{
    return myFlushCounter;
}



//This method is used to Enable the Dcc TARP.
void CFG_Tarp::SetDCCTarpEnabled(bool theDCCTarpEnabled)
{
    myTarpEnabled = theDCCTarpEnabled;

}

//This method returns the state of the Dcc TARP.
bool CFG_Tarp::GetDCCTarpEnabled() const
{
   return  myTarpEnabled;
}

void CFG_Tarp::Reset(void)
{
    myFlushTimer = 0;
    myEntryTimer = 0;
    myType1Timer = 0;
    myType2Timer = 0;
    myType3Timer = 0;
    myType4Timer = 0;
    myProtocolAddr = 0;
    myResetSequenceCounter = 0;
    myLifetimeHops = 0;
    myFlushCounter = 0;
    myTarpEnabled = false;
}

ostream& CFG_Tarp::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myFlushTimer);
    theStream   << FC_InsertVar(myEntryTimer);
    theStream   << FC_InsertVar(myType1Timer);
    theStream   << FC_InsertVar(myType2Timer);
    theStream   << FC_InsertVar(myType3Timer);
    theStream   << FC_InsertVar(myType4Timer);
    theStream   << FC_InsertVar(myProtocolAddr);
    theStream   << FC_InsertVar(myResetSequenceCounter);
    theStream   << FC_InsertVar(myLifetimeHops);
    theStream   << FC_InsertVar(myFlushCounter);

    return theStream;
}

istream& CFG_Tarp::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myFlushTimer);
    theStream   >> FC_ExtractVar(myEntryTimer);
    theStream   >> FC_ExtractVar(myType1Timer);
    theStream   >> FC_ExtractVar(myType2Timer);
    theStream   >> FC_ExtractVar(myType3Timer);
    theStream   >> FC_ExtractVar(myType4Timer);
    theStream   >> FC_ExtractVar(myProtocolAddr);
    theStream   >> FC_ExtractVar(myResetSequenceCounter);
    theStream   >> FC_ExtractVar(myLifetimeHops);
    theStream   >> FC_ExtractVar(myFlushCounter);

    return theStream;
}

FC_Stream& CFG_Tarp::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    theStream   << myFlushTimer;
    theStream   << myEntryTimer;
    theStream   << myType1Timer;
    theStream   << myType2Timer;
    theStream   << myType3Timer;
    theStream   << myType4Timer;
    theStream   << myProtocolAddr;
    theStream   << myResetSequenceCounter;
    theStream   << myLifetimeHops;
    theStream   << myFlushCounter;

    return theStream;
}

FC_Stream& CFG_Tarp::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myFlushTimer;
    theStream   >> myEntryTimer;
    theStream   >> myType1Timer;
    theStream   >> myType2Timer;
    theStream   >> myType3Timer;
    theStream   >> myType4Timer;
    theStream   >> myProtocolAddr;
    theStream   >> myResetSequenceCounter;
    theStream   >> myLifetimeHops;
    theStream   >> myFlushCounter;

    return theStream;
}




FC_CmdProcessor::STATUS CFG_Tarp::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto TarpERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);


    if (!strncmp(aParam,"flusht",6))
    {
        SetFlushTimer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"entry",5))
    {
        SetEntryTimer(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"type1",5))
    {
        SetType1Timer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"type2",5))
    {
        SetType2Timer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"type3",5))
    {
        SetType3Timer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"type4",5))
    {
        SetType4Timer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"proto",5))
    {
        SetProtocolAddr(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"reset",5))
    {
        SetResetSequenceCounter(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"life",4))
    {
        SetLifetimeHops(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"flushc",6))
    {
        SetFlushCounter(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else
    {
        goto TarpERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

TarpERROR:
    {
        fc_cout << "tarp <flushtimer>    <1-10> (min) " << endl;
        fc_cout << "tarp <entrytimer>    <0-3600> (ms) " << endl;
        fc_cout << "tarp <type1timer>    <0-3600> (ms) " << endl;
        fc_cout << "tarp <type2timer>    <0-3600> (ms) " << endl;
        fc_cout << "tarp <type3timer>    <0-3600> (ms) " << endl;
        fc_cout << "tarp <type4timer>    <0-3600> (ms) " << endl;
        fc_cout << "tarp <protocoladdr>  <0-255> " << endl;
        fc_cout << "tarp <resetseqcntr>  <0-255> " << endl;
        fc_cout << "tarp <lifetime>      <0-65535> " << endl;
        fc_cout << "tarp <flushcache>    <0-65535> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Tarp::Display( FC_Stream& theStream )
{
    theStream   << "TARP       - Flush Timer (min)     [flush]            = " << uint32(myFlushTimer) << endl;
    theStream   << "TARP       - Entry Timer (min)     [entry]            = " << uint32(myEntryTimer) << endl;
    theStream   << "TARP       - Type 1 Timer (min)    [type1]            = " << uint32(myType1Timer) << endl;
    theStream   << "TARP       - Type 2 Timer (min)    [type2]            = " << uint32(myType2Timer) << endl;
    theStream   << "TARP       - Type 3 Timer (min)    [type3]            = " << uint32(myType3Timer) << endl;
    theStream   << "TARP       - Type 4 Timer (min)    [type4]            = " << uint32(myType4Timer) << endl;
    theStream   << "TARP       - TARP Protocol Addr    [protocoladdr]     = " << uint32(myProtocolAddr) << endl;
    theStream   << "TARP       - Reset Sequence Cntr   [resetseq]         = " << uint32(myResetSequenceCounter) << endl;
    theStream   << "TARP       - Lifetime Hops         [lifetime]         = " << uint32(myLifetimeHops) << endl;
    theStream   << "TARP       - Flush Cache Cntr      [flushcache]       = " << uint32(myFlushCounter) << endl;
    theStream << endl;
}

