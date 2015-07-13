/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : TSPII
 TARGET      : 
 DESCRIPTION : Pure Virtual OSC Controller Class API
--------------------------------------------------------------------------*/
#include "TsPii/TSPII_OscMapperCtrlIf.h" 

TSPII_OscMapperCtrlIf::TSPII_OscMapperCtrlIf(TSPII_OscChannel theOsc) :
    myOscChannel(theOsc)
{
    unsigned int i;
    for ( i=0; i<TSPII_MAX_OCH; i++ )
    {
        myOchOCI[i] = 0;
        myOchFDIP[i] = 0;
        myOchFDIO[i] = 0;
    }
    myOmsPMI = 0;;
    myOmsBDIP = 0;;
    myOmsBDIO = 0;;
    myOmsFDIP = 0;;
    myOmsFDIO = 0;;
    myOtsPMI = 0;;
    myOtsBDIP = 0;;
    myOtsBDIO = 0;;
    myRsLOF = 0;;
    myRsOOF = 0;;
    myOptLOS = 0;;
    myOptLossOfClock = 0;
    myCVCount = 0;
    myLastCV = 0;
    CT_G709Trace                  myOtsRxTTI;
    CT_G709Trace                  myOtsTxTTI;
    CT_SDH16ByteTrace             myRsTxTrace;
    CT_SDH16ByteTrace             myRsRxTrace;
}

// vim:cindent:sw=4:expandtab

