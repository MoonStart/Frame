#ifndef _TSPII_IPCOUNTERSIF_H
#define _TSPII_IPCOUNTERSIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  GENERIC
 AUTHOR   :  Simon Cadieux, 2003/06/12
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_BaseIf.h"

class TSPII_IPCountersIf : public TSPII_BaseIf
{
public:
    
    /* Constructor */  TSPII_IPCountersIf(bool theDefault = false);
    virtual            ~TSPII_IPCountersIf();
    virtual void       Reset();
    void               UpdateCounters();

    int GetICMP_DestUnreachableReceived();
    int GetICMP_DestUnreachableTransmitted();
    int GetICMP_ErrorsReceived();
    int GetICMP_TTLExceededReceived();
    int GetIP_AddressErrorsReceived();
    int GetIP_DiscardsReceived();
    int GetIP_DiscardsTransmitted();
    int GetIP_HeaderErrorsReceived();
    int GetIP_NoRoutesTransmitted();    

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream   & WriteObject(ostream & theStream);
    virtual istream   & ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:

    virtual void UpdateValues();

    bool mySimulationFlag;
    int myICMP_DestUnreachableReceived;
    int myICMP_DestUnreachableTransmitted;
    int myICMP_ErrorsReceived;
    int myICMP_TTLExceededReceived;
    int myIP_AddressErrorsReceived;
    int myIP_DiscardsReceived;
    int myIP_DiscardsTransmitted;
    int myIP_HeaderErrorsReceived;
    int myIP_NoRoutesTransmitted;
};

#endif // _TSPII_IPCOUNTERSIF_H
