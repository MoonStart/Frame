/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/
#ifndef SNMP_BBINTFDATA_H
#define SNMP_BBINTFDATA_H


#include <gdef.h>
#include <iostream>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <Blackboard/FC_BbObject.h>
#include <SNMP/SNMP_Data.h>

class SNMP_BbIntfStatsData : public SNMP_BbData
{
public:
    SNMP_BbIntfStatsData();
    virtual ~SNMP_BbIntfStatsData();

    CT_SNMP_Integer32 GetMtu()                  { return myMtu; }
    CT_SNMP_Guage32   GetSpeed()                { return mySpeed; }
    CT_SNMP_String&   GetPhysAddress()          { return myPhysAddress; }
    CT_SNMP_Counter32 GetInOctets()             { return myInOctets; }
    CT_SNMP_Counter32 GetInUCastPkts()          { return myInUCastPkts;  }
    CT_SNMP_Counter32 GetInDiscards()           { return myInDiscards;  }
    CT_SNMP_Counter32 GetInErrors()             { return myInErrors;   }
    CT_SNMP_Counter32 GetInUnknownProtos()      { return myInUnknownProtos; }
    CT_SNMP_Counter32 GetOutOctets()            { return myOutOctets;  }
    CT_SNMP_Counter32 GetOutUCastPkts()         { return myOutUCastPkts; }
    CT_SNMP_Counter32 GetOutDiscards()          { return myOutDiscards; }
    CT_SNMP_Counter32 GetOutErrors()            { return myOutErrors;  }
    CT_SNMP_Counter32 GetInMulticastPkts()      { return myInMulticastPkts;  }
    CT_SNMP_Counter32 GetInBroadcastPkts()      { return myInBroadcastPkts;  }
    CT_SNMP_Counter32 GetOutMulticastPkts()     { return myOutMulticastPkts;  }
    CT_SNMP_Counter32 GetOutBroadcastPkts()     { return myOutBroadcastPkts; }
    CT_SNMP_Counter64& GetHCInOctets()           { return myHCInOctets; }
    CT_SNMP_Counter64& GetHCInUCastPkts()        { return myHCInUCastPkts; }
    CT_SNMP_Counter64& GetHCInMulticastPkts()    { return myHCInMulticastPkts;  }
    CT_SNMP_Counter64& GetHCInBroadcastPkts()    { return myHCInBroadcastPkts;     }
    CT_SNMP_Counter64& GetHCOutOctets()          { return myHCOutOctets; }
    CT_SNMP_Counter64& GetHCOutUCastPkts()       { return myHCOutUCastPkts; }
    CT_SNMP_Counter64& GetHCOutMulticastPkts()   { return myHCOutMulticastPkts; }
    CT_SNMP_Counter64& GetHCOutBroadcastPkts()   { return myHCOutBroadcastPkts; }
    CT_SNMP_Guage32   GetHighSpeed()            { return myHighSpeed; }
    CT_SNMP_TruthValue GetConnectorPresent()    { return CT_SNMP_TruthValue_true; }
    CT_SNMP_TimeStamp GetDiscontinuityTime()    { return myDiscontinuityTime; }
    CT_SNMP_TruthValue GetPromiscuousMode()     { return CT_SNMP_TruthValue_false; }
    CT_SNMP_AdminStatus GetAdminStatus()        { return myAdminStatus; }
    CT_SNMP_OperStatus  GetOperStatus()         { return myOperStatus; }
    CT_SNMP_TimeTicks GetLastChange()           { return myLastChangeTime; }
    bool IsFirstSample()                        { return myFirstSample; }

    void SetMtu(CT_SNMP_Integer32 theData)                  {  myMtu = theData; }
    void SetSpeed(CT_SNMP_Guage32 theData)                  {  mySpeed = theData; }
    void SetPhysAddress(CT_SNMP_String& theData)            {  myPhysAddress = theData; }
    void SetInOctets(CT_SNMP_Counter32 theData)             {  myInOctets = theData; }
    void SetInUCastPkts(CT_SNMP_Counter32 theData)          {  myInUCastPkts = theData;  }
    void SetInDiscards(CT_SNMP_Counter32 theData)           {  myInDiscards = theData;  }
    void SetInErrors(CT_SNMP_Counter32 theData)             {  myInErrors = theData;   }
    void SetInUnknownProtos(CT_SNMP_Counter32 theData)      {  myInUnknownProtos = theData; }
    void SetOutOctets(CT_SNMP_Counter32 theData)            {  myOutOctets = theData;  }
    void SetOutUCastPkts(CT_SNMP_Counter32 theData)         {  myOutUCastPkts = theData; }
    void SetOutDiscards(CT_SNMP_Counter32 theData)          {  myOutDiscards = theData; }
    void SetOutErrors(CT_SNMP_Counter32 theData)            {  myOutErrors = theData;  }
    void SetInMulticastPkts(CT_SNMP_Counter32 theData)      {  myInMulticastPkts = theData;  }
    void SetInBroadcastPkts(CT_SNMP_Counter32 theData)      {  myInBroadcastPkts = theData;  }
    void SetOutMulticastPkts(CT_SNMP_Counter32 theData)     {  myOutMulticastPkts = theData;  }
    void SetOutBroadcastPkts(CT_SNMP_Counter32 theData)     {  myOutBroadcastPkts = theData; }
    void SetHCInOctets(CT_SNMP_Counter64& theData)          {  myHCInOctets = theData; }
    void SetHCInUCastPkts(CT_SNMP_Counter64& theData)       {  myHCInUCastPkts = theData; }
    void SetHCInMulticastPkts(CT_SNMP_Counter64& theData)   {  myHCInMulticastPkts = theData;  }
    void SetHCInBroadcastPkts(CT_SNMP_Counter64& theData)   {  myHCInBroadcastPkts = theData;     }
    void SetHCOutOctets(CT_SNMP_Counter64& theData)         {  myHCOutOctets = theData; }
    void SetHCOutUCastPkts(CT_SNMP_Counter64& theData)      {  myHCOutUCastPkts = theData; }
    void SetHCOutMulticastPkts(CT_SNMP_Counter64& theData)  {  myHCOutMulticastPkts = theData; }
    void SetHCOutBroadcastPkts(CT_SNMP_Counter64& theData)  {  myHCOutBroadcastPkts = theData; }
    void SetHCInOctets(CT_SNMP_Counter32 theData)           {  myHCInOctets = theData; }
    void SetHCInUCastPkts(CT_SNMP_Counter32 theData)        {  myHCInUCastPkts = theData; }
    void SetHCInMulticastPkts(CT_SNMP_Counter32 theData)    {  myHCInMulticastPkts = theData;  }
    void SetHCInBroadcastPkts(CT_SNMP_Counter32 theData)    {  myHCInBroadcastPkts = theData;     }
    void SetHCOutOctets(CT_SNMP_Counter32 theData)          {  myHCOutOctets = theData; }
    void SetHCOutUCastPkts(CT_SNMP_Counter32 theData)       {  myHCOutUCastPkts = theData; }
    void SetHCOutMulticastPkts(CT_SNMP_Counter32 theData)   {  myHCOutMulticastPkts = theData; }
    void SetHCOutBroadcastPkts(CT_SNMP_Counter32 theData)   {  myHCOutBroadcastPkts = theData; }
    void SetHighSpeed(CT_SNMP_Guage32 theData)              {  myHighSpeed = theData; }
    void SetDiscontinuityTime(CT_SNMP_TimeStamp theData)    {  myDiscontinuityTime = theData; }
    void SetAdminStatus(CT_SNMP_AdminStatus theData)        {  myAdminStatus = theData; }
    void SetOperStatus(CT_SNMP_OperStatus theData)          {  myOperStatus = theData;  }
    void SetLastChange(CT_SNMP_TimeTicks theData)           {  myLastChangeTime = theData; }

    void ResetMtu()                 {  myMtu = 0; }
    void ResetSpeed()               {  mySpeed = 0; }
    void ResetInOctets()            {  myInOctets = 0; }
    void ResetInUCastPkts()         {  myInUCastPkts = 0;  }
    void ResetInDiscards()          {  myInDiscards = 0;  }
    void ResetInErrors()            {  myInErrors = 0;   }
    void ResetInUnknownProtos()     {  myInUnknownProtos = 0; }
    void ResetOutOctets()           {  myOutOctets = 0;  }
    void ResetOutUCastPkts()        {  myOutUCastPkts = 0; }
    void ResetOutDiscards()         {  myOutDiscards = 0; }
    void ResetOutErrors()           {  myOutErrors = 0;  }
    void ResetInMulticastPkts()     {  myInMulticastPkts = 0;  }
    void ResetInBroadcastPkts()     {  myInBroadcastPkts = 0;  }
    void ResetOutMulticastPkts()    {  myOutMulticastPkts = 0;  }
    void ResetOutBroadcastPkts()    {  myOutBroadcastPkts = 0; }
    void ResetHCInOctets()          {  myHCInOctets = 0; }
    void ResetHCInUCastPkts()       {  myHCInUCastPkts = 0; }
    void ResetHCInMulticastPkts()   {  myHCInMulticastPkts = 0;  }
    void ResetHCInBroadcastPkts()   {  myHCInBroadcastPkts = 0;     }
    void ResetHCOutOctets()         {  myHCOutOctets = 0; }
    void ResetHCOutUCastPkts()      {  myHCOutUCastPkts = 0; }
    void ResetHCOutMulticastPkts()  {  myHCOutMulticastPkts = 0; }
    void ResetHCOutBroadcastPkts()  {  myHCOutBroadcastPkts = 0; }
    void ResetHighSpeed()           {  myHighSpeed = 0; }
    void ResetConnectorPresent()    {  myConnectorPresent = CT_SNMP_TruthValue_true; }
    void ResetDiscontinuityTime()   {  myDiscontinuityTime = 0; }
    void ResetAdminStatus()         {  myAdminStatus = CT_SNMP_AdminStatusUnk; }
    void ResetOperStatus()          {  myOperStatus = CT_SNMP_OperStatusNotPresent; }
    void ResetLastChange()          {  myLastChangeTime = 0; }
    void DisableFirstSampleFlag()   {  myFirstSample = false;   }                       

    void IncInOctets(CT_SNMP_Counter32 theInc)             {  myInOctets += theInc; }
    void IncInUCastPkts(CT_SNMP_Counter32 theInc)          {  myInUCastPkts += theInc;  }
    void IncInDiscards(CT_SNMP_Counter32 theInc)           {  myInDiscards += theInc;  }
    void IncInErrors(CT_SNMP_Counter32 theInc)             {  myInErrors += theInc;   }
    void IncInUnknownProtos(CT_SNMP_Counter32 theInc)      {  myInUnknownProtos += theInc; }
    void IncOutOctets(CT_SNMP_Counter32 theInc)            {  myOutOctets += theInc;  }
    void IncOutUCastPkts(CT_SNMP_Counter32 theInc)         {  myOutUCastPkts += theInc; }
    void IncOutDiscards(CT_SNMP_Counter32 theInc)          {  myOutDiscards += theInc; }
    void IncOutErrors(CT_SNMP_Counter32 theInc)            {  myOutErrors += theInc;  }
    void IncInMulticastPkts(CT_SNMP_Counter32 theInc)      {  myInMulticastPkts += theInc;  }
    void IncInBroadcastPkts(CT_SNMP_Counter32 theInc)      {  myInBroadcastPkts += theInc;  }
    void IncOutMulticastPkts(CT_SNMP_Counter32 theInc)     {  myOutMulticastPkts += theInc;  }
    void IncOutBroadcastPkts(CT_SNMP_Counter32 theInc)     {  myOutBroadcastPkts += theInc; }
    void IncHCInOctets(CT_SNMP_Counter32 theInc)           {  myHCInOctets += theInc; }
    void IncHCInUCastPkts(CT_SNMP_Counter32 theInc)        {  myHCInUCastPkts += theInc; }
    void IncHCInMulticastPkts(CT_SNMP_Counter32 theInc)    {  myHCInMulticastPkts += theInc;  }
    void IncHCInBroadcastPkts(CT_SNMP_Counter32 theInc)    {  myHCInBroadcastPkts += theInc;     }
    void IncHCOutOctets(CT_SNMP_Counter32 theInc)          {  myHCOutOctets += theInc; }
    void IncHCOutUCastPkts(CT_SNMP_Counter32 theInc)       {  myHCOutUCastPkts += theInc; }
    void IncHCOutMulticastPkts(CT_SNMP_Counter32 theInc)   {  myHCOutMulticastPkts += theInc; }
    void IncHCOutBroadcastPkts(CT_SNMP_Counter32 theInc)   {  myHCOutBroadcastPkts += theInc; }

    virtual void ResetAll();
    virtual void Init(restart_type theRestart);

protected:

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );  

private:

    CT_SNMP_Integer32 myMtu;
    CT_SNMP_Guage32   mySpeed;
    CT_SNMP_String    myPhysAddress;
    CT_SNMP_Counter32 myInOctets;
    CT_SNMP_Counter32 myInUCastPkts;
    CT_SNMP_Counter32 myInDiscards;
    CT_SNMP_Counter32 myInErrors;
    CT_SNMP_Counter32 myInUnknownProtos;
    CT_SNMP_Counter32 myOutOctets;
    CT_SNMP_Counter32 myOutUCastPkts;
    CT_SNMP_Counter32 myOutDiscards;
    CT_SNMP_Counter32 myOutErrors;
    CT_SNMP_Counter32 myInMulticastPkts;
    CT_SNMP_Counter32 myInBroadcastPkts;
    CT_SNMP_Counter32 myOutMulticastPkts;
    CT_SNMP_Counter32 myOutBroadcastPkts;
    CT_SNMP_Counter64 myHCInOctets;
    CT_SNMP_Counter64 myHCInUCastPkts;
    CT_SNMP_Counter64 myHCInMulticastPkts;
    CT_SNMP_Counter64 myHCInBroadcastPkts;
    CT_SNMP_Counter64 myHCOutOctets;
    CT_SNMP_Counter64 myHCOutUCastPkts;
    CT_SNMP_Counter64 myHCOutMulticastPkts;
    CT_SNMP_Counter64 myHCOutBroadcastPkts;
    CT_SNMP_Guage32   myHighSpeed;
    CT_SNMP_TruthValue myConnectorPresent;
    CT_SNMP_TimeStamp  myDiscontinuityTime;
    CT_SNMP_AdminStatus myAdminStatus;
    CT_SNMP_OperStatus  myOperStatus;
    CT_SNMP_TimeTicks myLastChangeTime;
    bool              myFirstSample;

};

#endif // SNMP_BBINTFDATA_H
