/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/



#include "PowerManagement/PWR_OchHistory.h"
#include <stdio.h>
#include "BaseClass/FC_Stream.h"

////////////////////////////////////////////////////////////////////////////////
PWR_OchHistory::PWR_OchHistory() :
    myEvent(0)
{
}

////////////////////////////////////////////////////////////////////////////////
PWR_OchHistory::~PWR_OchHistory()
{
}

////////////////////////////////////////////////////////////////////////////////
void PWR_OchHistory::DisplayHeader(FC_Stream & theStream)
{
    theStream << "                 E(vent)     : C(ontrol), F(ilter) or M(odify)" << endl;
    theStream << "                   S(tate)   : O(bservable), C(ontrollable) or N(one)" << endl;
    theStream << "                     R(eady) : Y(es) or N(no)" << endl;
    theStream << "#       time     E S R Power MinPwr Target Error Command" << endl;
}

////////////////////////////////////////////////////////////////////////////////
FC_Stream & operator<<(FC_Stream & theStream, const PWR_OchHistory & theHistory)
{
    char line[80];
    int  hour    = (int)(theHistory.myTimestamp/3600)%24;
    int  minute  = (int)(theHistory.myTimestamp/60)%60;
    int  second  = (int)theHistory.myTimestamp%60;
    char state   = !theHistory.myObservable ? 'N' : !theHistory.myControllable ? 'O' : 'C';
    char rdy     = theHistory.myOchReady ? 'Y' : 'N';
    sprintf(line, "%2d:%02d:%02d %c %c %c %5d %6d %6d %5d %5d", hour, minute, second, theHistory.myEvent, state, rdy, theHistory.myOchPower, theHistory.myOchMinPwr, theHistory.myOchTarget, theHistory.myError, theHistory.myOchCommand);
    return theStream << line;
}
