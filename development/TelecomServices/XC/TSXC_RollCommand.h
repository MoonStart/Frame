/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     July, 2007  Kumar Solai
 DESCRIPTION:   TSXC_RollCommand  Class Definition
--------------------------------------------------------------------------*/
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#ifndef TSXC_ROLLCOMMAND_H
#define TSXC_ROLLCOMMAND_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <XC/TSXC_CrossConnect.h>
#include <CommonTypes/CT_CrossConnect.h>

class TSXC_RollCommand : public TEL_BbObjectBase
{
public:

    // Class constructor
    TSXC_RollCommand();

    // Class destructor
    virtual ~TSXC_RollCommand();

    //
    // Methods to set object attributes
    //
    void    SetRollCommand(INT32 theCommand);
    void    SetRollCommandID(INT32 theCommandID);    
    void    SetRollConnectKeyOne(TSXC_Connection theCkey);
    void    SetRollConnectKeyTwo(TSXC_Connection theCkey);    
    void    SetRollInfo(TSXC_Roll_Info theRollInfo);
        
    // *********************************
    // Methods to get object attributes
    // *********************************
    INT32   GetRollCommand();
    INT32   GetRollCommandID();
    TSXC_Connection GetRollConnectKeyOne();
    TSXC_Connection GetRollConnectKeyTwo();    
    TSXC_Roll_Info  GetRollInfo();
    
protected:
    // *********************************
    // Serialization methods
    // *********************************
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    INT32                   myRollCommand;
    INT32                   myRollCommandID;
    TSXC_Connection         myRollConnectKeyOne;    // a connection to be add/rmv 
    TSXC_Connection         myRollConnectKeyTwo;    // a connection of an other module 
    TSXC_Roll_Info          myRollInfo;
};

#endif /* TSXC_ROLLCOMMAND_H */
