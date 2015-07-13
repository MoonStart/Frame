/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   PM Configuration parameters class. Keep the congig of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdEon.h>


//-----------------------------------------------------------------
//##ModelId=3FA1610A0249
PM_BbThresholdEon::PM_BbThresholdEon(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(PM_TypeEon::PM_PARAM_NUM, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610A025A
PM_BbThresholdEon::~PM_BbThresholdEon()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C9255B9029D
void PM_BbThresholdEon::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeEon::PM_ICMPDUR].UnsignedValue     = PM_MAX_THRES_ICMPDUR_15M;
    myThresholdArray[PM_TypeEon::PM_ICMPDUT].UnsignedValue     = PM_MAX_THRES_ICMPDUT_15M;
    myThresholdArray[PM_TypeEon::PM_ICMPER].UnsignedValue      = PM_MAX_THRES_ICMPER_15M;
    myThresholdArray[PM_TypeEon::PM_ICMPTTLER].UnsignedValue   = PM_MAX_THRES_ICMPTTLER_15M;
    myThresholdArray[PM_TypeEon::PM_IPADDER].UnsignedValue     = PM_MAX_THRES_IPADDER_15M;
    myThresholdArray[PM_TypeEon::PM_IPDISCR].UnsignedValue     = PM_MAX_THRES_IPDISCR_15M;
    myThresholdArray[PM_TypeEon::PM_IPDISCT].UnsignedValue     = PM_MAX_THRES_IPDISCT_15M;
    myThresholdArray[PM_TypeEon::PM_IPHDRR].UnsignedValue      = PM_MAX_THRES_IPHDRR_15M;
    myThresholdArray[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue = PM_MAX_THRES_IPNOROUTEST_15M;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3C9255B902A7
ostream& PM_BbThresholdEon::WriteObject( ostream& theStream )
{
    theStream 
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_ICMPDUR ].UnsignedValue    )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_ICMPDUT].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_ICMPER].UnsignedValue      )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_ICMPTTLER].UnsignedValue   )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_IPADDER].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_IPDISCR].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_IPDISCT].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_IPHDRR].UnsignedValue      )
        << FC_InsertVar( myThresholdArray[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue );

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3C9255B902B2
istream& PM_BbThresholdEon::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream 
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_ICMPDUR ].UnsignedValue    )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_ICMPDUT].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_ICMPER].UnsignedValue      )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_ICMPTTLER].UnsignedValue   )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_IPADDER].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_IPDISCR].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_IPDISCT].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_IPHDRR].UnsignedValue      )
        >> FC_ExtractVar( myThresholdArray[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue );

    return theStream;

}



//-----------------------------------------------------------------
//##ModelId=3FA1610A03D1
PM_BbThresholdEon1Day::PM_BbThresholdEon1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdEon( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610A03E1
PM_BbThresholdEon1Day::~PM_BbThresholdEon1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3FA1610A03E3
void PM_BbThresholdEon1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    myThresholdArray[PM_TypeEon::PM_ICMPDUR].UnsignedValue     = PM_MAX_THRES_ICMPDUR_DAY;
    myThresholdArray[PM_TypeEon::PM_ICMPDUT].UnsignedValue     = PM_MAX_THRES_ICMPDUT_DAY;
    myThresholdArray[PM_TypeEon::PM_ICMPER].UnsignedValue      = PM_MAX_THRES_ICMPER_DAY;
    myThresholdArray[PM_TypeEon::PM_ICMPTTLER].UnsignedValue   = PM_MAX_THRES_ICMPTTLER_DAY;
    myThresholdArray[PM_TypeEon::PM_IPADDER].UnsignedValue     = PM_MAX_THRES_IPADDER_DAY;
    myThresholdArray[PM_TypeEon::PM_IPDISCR].UnsignedValue     = PM_MAX_THRES_IPDISCR_DAY;
    myThresholdArray[PM_TypeEon::PM_IPDISCT].UnsignedValue     = PM_MAX_THRES_IPDISCT_DAY;
    myThresholdArray[PM_TypeEon::PM_IPHDRR].UnsignedValue      = PM_MAX_THRES_IPHDRR_DAY;
    myThresholdArray[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue = PM_MAX_THRES_IPNOROUTEST_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
