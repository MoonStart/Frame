#ifndef _TSPII_1NSELIF_H
#define _TSPII_1NSELIF_H
/************************************BEGIN*************************************
*                         CONFIDENTIAL AND PROPRIETARY
*              Copyright (C) 2004 Tellabs, All Rights Reserved
*******************************************************************************
*
* File:    TSPII_1NSelIf.h 
* Type:    C++ include
* Description:
*    Provides the platform independant interface for the 1NSel 
*    selector methods.
*
*************************************END***************************************
*/
#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"
 

class TSPII_1NSelIf : public TSPII_BaseIf
{
public:

    /*************************************************************************/
    /** Constructor                                                         **/
    /*************************************************************************/	
	TSPII_1NSelIf(bool theDefault = false, bool interpretAsWorkProtect = true);
    
    /*************************************************************************/
	/** Destructor                                                          **/
    /*************************************************************************/
	virtual ~TSPII_1NSelIf();

    /**************************************************************************/
	/** Utility functions                                                   **/
    /*************************************************************************/
    virtual void Reset();

    /*************************************************************************/
	/** 1NSel Entity configuration method                                   **/
    /*************************************************************************/
	virtual void SetSelector(uint16 itsInput);

    /*************************************************************************/
    /** 1NSel Entity monitor method                                         **/
    /*************************************************************************/
    virtual uint16 GetSelector(void);

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

    /*************************************************************************/
	/** Selector  attribute                                                 **/
    /*************************************************************************/
    uint16 itsSelected;            // the selector  
    bool   itsInterpretAsWorkProtect;
};

#endif // _TSPII_1NSelIF_H
