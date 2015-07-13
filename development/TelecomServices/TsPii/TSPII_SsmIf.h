#ifndef _TSPII_SSMIF_H
#define _TSPII_SSMIF_H
/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_SsmIf.h
* Type:    C++ include
* Description:
*    Provides the platform specific interface for the SSM card methods.
*
*************************************END***************************************
*/
#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"
#include <map>
#include <list>

const uint8  TSPII_SSMIF_NUM_PORTS        = 15;  // Includes the client SFPs, XFP & line XFP, TTP

enum TSPII_SSMIF_PRIORITY_TABLE
{
    TSPII_SSMIF_PRIOR_TBL_LINE = 0,
    TSPII_SSMIF_PRIOR_TBL_PATH,
    TSPII_SSMIF_PRIOR_TBL_ALT_LINE,
    TSPII_SSMIF_PRIOR_TBL_MAX
};

#define TSPII_SSMIF_DISPLAY_PRIORTBL(x) (\
                     (x==TSPII_SSMIF_PRIOR_TBL_LINE) ? "line" :\
                     (x==TSPII_SSMIF_PRIOR_TBL_PATH) ? "path" :\
                     (x==TSPII_SSMIF_PRIOR_TBL_ALT_LINE) ? "alt" : " ?  ")

enum TSPII_SSMIF_PRIORITY_DEFECT
{
    TSPII_SSMIF_PRIOR_DEF_TIMS = 0,
    TSPII_SSMIF_PRIOR_DEF_AISL,
    TSPII_SSMIF_PRIOR_DEF_SFL,
    TSPII_SSMIF_PRIOR_DEF_AISP,
    TSPII_SSMIF_PRIOR_DEF_LOPP,
    TSPII_SSMIF_PRIOR_DEF_UNEQP,
    TSPII_SSMIF_PRIOR_DEF_TIMP,
    TSPII_SSMIF_PRIOR_DEF_PLMP,
    TSPII_SSMIF_PRIOR_DEF_SFP,
    TSPII_SSMIF_PRIOR_DEF_PDI,
    TSPII_SSMIF_PRIOR_DEF_SDP,
    TSPII_SSMIF_PRIOR_DEF_SDL,
    TSPII_SSMIF_PRIOR_DEF_MAX
};

#define TSPII_SSMIF_DISPLAY_PRIORDEF(x) (\
                     (x==TSPII_SSMIF_PRIOR_DEF_TIMS) ? "tims" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_AISL) ? "aisl" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_SFL) ? "sfl" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_AISP) ? "aisp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_LOPP) ? "lopp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_UNEQP) ? "uneqp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_TIMP) ? "timp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_PLMP) ? "plmp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_SFP) ? "sfp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_PDI) ? "pdi" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_SDP) ? "sdp" :\
                     (x==TSPII_SSMIF_PRIOR_DEF_SDL) ? "sdl" : "?")

enum TSPII_SSMIF_PRIORITY
{
    TSPII_SSMIF_PRIOR_NONE = 0,
    TSPII_SSMIF_PRIOR_SD,
    TSPII_SSMIF_PRIOR_SFL,
    TSPII_SSMIF_PRIOR_SFH
};

#define TSPII_SSMIF_DISPLAY_PRIORITY(x) (\
                     (x==TSPII_SSMIF_PRIOR_NONE) ? "none" :\
                     (x==TSPII_SSMIF_PRIOR_SD)   ? "sd" :\
                     (x==TSPII_SSMIF_PRIOR_SFL)  ? "sfl" :\
                     (x==TSPII_SSMIF_PRIOR_SFH)  ? "sfh" : "?")


enum TSPII_SSMIF_LAYER
{
    TSPII_SSMIF_LAYER_L2 = 0,
    TSPII_SSMIF_LAYER_UNKNOWN
};

#define TSPII_SSMIF_DISPLAY_LAYER(x) (\
                     (x==TSPII_SSMIF_LAYER_L2)      ? "l2" :\
                     (x==TSPII_SSMIF_LAYER_UNKNOWN) ? "unknown" : " ?  ")


enum TSPII_SSMIF_DIAG
{
    TSPII_SSMIF_DIAG_RESOURCE_LOW = 0,
    TSPII_SSMIF_DIAG_RESOURCE_UNAVAIL,
    TSPII_SSMIF_DIAG_UNKNOWN,
};

#define TSPII_SSMIF_DISPLAY_DIAG(x) (\
                     (x==TSPII_SSMIF_DIAG_RESOURCE_LOW)       ? "resourceLow" :\
                     (x==TSPII_SSMIF_DIAG_RESOURCE_UNAVAIL)   ? "resourceUnavail" :\
                     (x==TSPII_SSMIF_DIAG_UNKNOWN)            ? "unknown" : "?")


/////////////////////////////////////////////////////////////////////////////////////


// Structure of TohPqwEgrXc Record --> Key + Val
class TSPII_SsmIfTohPqwEgrXcKey
{
public:
    uint16     DstSts;
    inline bool operator < (const TSPII_SsmIfTohPqwEgrXcKey& aDiagKey) const;
};

class TSPII_SsmIfTohPqwEgrXcVal
{
public:
    uint8      SrcShelf;
    uint8      SrcSlot;
    uint8      SrcPort;
    uint8      SrcSts;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_SsmIfTohPqwEgrXcVal& operator = (const TSPII_SsmIfTohPqwEgrXcVal& aVal);
    inline bool operator == (const TSPII_SsmIfTohPqwEgrXcVal& aVal);
};

// Structure of TohPqwIngXc Record --> Key + Val
class TSPII_SsmIfTohPqwIngXcKey
{
public:
    uint16     DstSts;
    inline bool operator < (const TSPII_SsmIfTohPqwIngXcKey& aDiagKey) const;
};

class TSPII_SsmIfTohPqwIngXcVal
{
public:
    uint8      SrcPort;
    uint8      SrcSts;
    CT_TEL_SignalType SrcCat;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_SsmIfTohPqwIngXcVal& operator = (const TSPII_SsmIfTohPqwIngXcVal& aVal);
    inline bool operator == (const TSPII_SsmIfTohPqwIngXcVal& aVal);
};

// Structure of TohFppXc Record --> Key + Val
class TSPII_SsmIfTohFppXcKey
{
public:
    uint16     DstSts;
    inline bool operator < (const TSPII_SsmIfTohFppXcKey& aDiagKey) const;
};

class TSPII_SsmIfTohFppXcVal
{
public:
    uint8      SrcPort;
    uint8      SrcSts;          // indicates which STS1 is controlled by FPP word
    CT_TEL_SignalType SrcCat;
    bool       IsNewOrChanged;   // true if this is a new or changed element
    bool       IsDeleted;        // true if this entry has been deleted
    inline TSPII_SsmIfTohFppXcVal& operator = (const TSPII_SsmIfTohFppXcVal& aVal);
    inline bool operator == (const TSPII_SsmIfTohFppXcVal& aVal);
};

typedef map<TSPII_SsmIfTohPqwEgrXcKey, TSPII_SsmIfTohPqwEgrXcVal, less<TSPII_SsmIfTohPqwEgrXcKey> > TSPII_SsmIfTohPqwEgrXcMap;
typedef map<TSPII_SsmIfTohPqwIngXcKey, TSPII_SsmIfTohPqwIngXcVal, less<TSPII_SsmIfTohPqwIngXcKey> > TSPII_SsmIfTohPqwIngXcMap;
typedef map<TSPII_SsmIfTohFppXcKey, TSPII_SsmIfTohFppXcVal, less<TSPII_SsmIfTohFppXcKey> > TSPII_SsmIfTohFppXcMap;

class TSPII_SsmIf : public TSPII_BaseIf
{
public:

    /*************************************************************************/
    /** Constructor                                                         **/
    /*************************************************************************/
    TSPII_SsmIf(bool theDefault, uint8 theNumShelves, uint8 theNumSlots, uint8 theNumImuxs, bool theForceShelf);

    /*************************************************************************/
    /** Destructor                                                          **/
    /*************************************************************************/
    virtual ~TSPII_SsmIf();

    /**************************************************************************/
    /** Utility functions                                                   **/
    /*************************************************************************/
    virtual void Reset();

    virtual void SetTohPriorityTable(TSPII_SSMIF_PRIORITY_TABLE theTable, TSPII_SSMIF_PRIORITY_DEFECT theDefect, TSPII_SSMIF_PRIORITY thePriority);
    virtual TSPII_SSMIF_PRIORITY GetTohPriorityTable(TSPII_SSMIF_PRIORITY_TABLE theTable, TSPII_SSMIF_PRIORITY_DEFECT theDefect);

    virtual void SetTohPriorityAssignment(uint8 thePort, TSPII_SSMIF_PRIORITY_TABLE theTable);
    virtual TSPII_SSMIF_PRIORITY_TABLE GetTohPriorityAssignment(uint8 thePort);

    virtual void AddTohPqwEgressXconn(uint8 theSrcShelf, uint8 theSrcSlot, uint8 theSrcPort, uint8 theSrcSts, uint16 theDstSts);
    virtual void DeleteTohPqwEgressXconn(uint16 theDstSts);
    virtual void DeleteAllTohPqwEgressXconns();
    virtual void CommitTohPqwEgressXconns();
    virtual TSPII_SsmIfTohPqwEgrXcMap& GetTohPqwEgressXconns();

    virtual void AddTohPqwIngressXconn(uint8 theSrcPort, uint8 theSrcSts, uint16 theDstSts,CT_TEL_SignalType SrcCat=CT_TEL_SIGNAL_UNKNOWN);
    virtual void DeleteTohPqwIngressXconn(uint16 theDstSts);
    virtual void DeleteAllTohPqwIngressXconns();
    virtual void CommitTohPqwIngressXconns();
    virtual TSPII_SsmIfTohPqwIngXcMap& GetTohPqwIngressXconns();

    virtual uint32 GetPqwTimeout(uint8 theShelf, uint8 theSlot);

    virtual void AddTohFppXconn( uint8 theSrcPort, uint8 theSrcSts, uint16 theDstSts,CT_TEL_SignalType SrcCat=CT_TEL_SIGNAL_UNKNOWN );
    virtual void DeleteTohFppXconn(uint16 theDstSts);
    virtual void DeleteAllTohFppXconn();
    virtual void CommitTohFppXconn();
    virtual TSPII_SsmIfTohFppXcMap& GetTohFppXconns();

    virtual void HwInit() {};



    // Equipment Stats and Diags (generic, but created for Layer 2)
    virtual bool StartEqptStatsCollection(TSPII_SSMIF_LAYER theLayer);  
    virtual bool GetEqptStats(TSPII_SSMIF_LAYER theLayer, list<string> *theList);
    virtual void DumpEqptStats(TSPII_SSMIF_LAYER theLayer);

    virtual bool GetDiagState(TSPII_SSMIF_LAYER theLayer, TSPII_SSMIF_DIAG theDiag);
    virtual void DumpDiags(TSPII_SSMIF_LAYER theLayer);



    /*************************************************************************/
    /** Blackboard serialization                                            **/
    /*************************************************************************/
    virtual FC_Stream & WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream & ReadObjectBinary(FC_Stream & theStream);
    virtual ostream & WriteObject(ostream & theStream);
    virtual istream & ReadObject(istream & theStream);

    /*************************************************************************/
    /** Test Menus                                                          **/
    /*************************************************************************/
    virtual void Display(FC_Stream & theStream);
    virtual void Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool Set(int argc, char ** argv);
    virtual bool Simul(int argc, char ** argv);

protected:
    virtual void RefreshGet();
    virtual void RefreshSet();
    virtual string DisplayPriorityTable();
    virtual string DisplayPriorityAssign();
    virtual string DisplayPqwTimeout();
    virtual string DisplayTohPqwEgressXc(bool printDetail);
    virtual string DisplayTohPqwIngressXc(bool printDetail);
    virtual string DisplayTohFppXc(bool printDetail);

    uint8                      itsNumShelves;
    uint8                      itsNumSlots;
    uint8                      itsNumImuxs;
    bool                       itsForceShelf;
    TSPII_SSMIF_PRIORITY       itsTohPriorTbl[TSPII_SSMIF_PRIOR_TBL_MAX][TSPII_SSMIF_PRIOR_DEF_MAX];  // Line and Path table storage
    TSPII_SSMIF_PRIORITY_TABLE itsTohPriorAssign[TSPII_SSMIF_NUM_PORTS];
    uint32                     **itsPqwTimeout;
    TSPII_SsmIfTohPqwEgrXcMap  itsTohPqwEgressXconnsMap;
    TSPII_SsmIfTohPqwIngXcMap  itsTohPqwIngressXconnsMap;
    TSPII_SsmIfTohFppXcMap     itsTohFppXconnMap;

    // Stat attributes
    list<string>               itsL2List;
    bool                       itsL2ResourcesLow;
    bool                       itsL2ResourcesUnavailable;
};

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SsmIfTohPqwEgrXcKey::operator < (const TSPII_SsmIfTohPqwEgrXcKey& aKey) const
{
    return (DstSts < aKey.DstSts) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SsmIfTohPqwIngXcKey::operator < (const TSPII_SsmIfTohPqwIngXcKey& aKey) const
{
    return (DstSts < aKey.DstSts) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_SsmIfTohPqwEgrXcVal& TSPII_SsmIfTohPqwEgrXcVal::operator = (const TSPII_SsmIfTohPqwEgrXcVal& aVal)
{
    SrcShelf = aVal.SrcShelf;
    SrcSlot = aVal.SrcSlot;
    SrcPort = aVal.SrcPort;
    SrcSts = aVal.SrcSts;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_SsmIfTohPqwIngXcVal& TSPII_SsmIfTohPqwIngXcVal::operator = (const TSPII_SsmIfTohPqwIngXcVal& aVal)
{
    SrcPort = aVal.SrcPort;
    SrcSts = aVal.SrcSts;
    SrcCat = aVal.SrcCat;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SsmIfTohPqwEgrXcVal::operator == (const TSPII_SsmIfTohPqwEgrXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if ( (SrcShelf == aVal.SrcShelf) &&
         (SrcSlot  == aVal.SrcSlot)  &&
         (SrcPort  == aVal.SrcPort)  &&
         (SrcSts   == aVal.SrcSts) )
    {
        retVal = true;
    }

    return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SsmIfTohPqwIngXcVal::operator == (const TSPII_SsmIfTohPqwIngXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if ( (SrcPort == aVal.SrcPort) &&
         (SrcSts  == aVal.SrcSts) &&
         (SrcCat  == aVal.SrcCat) )
    {
        retVal = true;
    }

    return retVal;
}


//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SsmIfTohFppXcVal::operator == (const TSPII_SsmIfTohFppXcVal& aVal)
{
    bool retVal;

    retVal = false;
    if ( (SrcPort == aVal.SrcPort) &&
         (SrcSts  == aVal.SrcSts) &&
         (SrcCat  == aVal.SrcCat) )
    {
        retVal = true;
    }

    return retVal;
}
//////////////////////////////////////////////////////////////////////////////////////
inline TSPII_SsmIfTohFppXcVal& TSPII_SsmIfTohFppXcVal::operator = (const TSPII_SsmIfTohFppXcVal& aVal)
{
    SrcPort = aVal.SrcPort;
    SrcSts = aVal.SrcSts;
    SrcCat = aVal.SrcCat;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
inline bool TSPII_SsmIfTohFppXcKey::operator < (const TSPII_SsmIfTohFppXcKey& aKey) const
{
    return (DstSts < aKey.DstSts) ? true : false;
}



#endif // _TSPII_SSMIF_H
