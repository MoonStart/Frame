/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     24 August, 1998 Jean-Francois Birtz.
 DESCRIPTION:   TCA State class. Keep and set the TCA PM states.
--------------------------------------------------------------------------*/

#include "BaseClass/FC_TextStream.h"
#include "TimeService/FC_TimeService.h"
#include "PM_BbTca.h"
#include <PM/PM_TypeOtu.h>
#include <PM/PM_TypeData.h>
#include <EPM/PM_TypeOdu.h>
#include <EPM/PM_TypeTcm.h>
#include <EPM/PM_TypeRmon.h>
#include <cstring>   // for strcpy

const uint8 PM_BBTCA_DATA_PRESENT     = 1;
const uint8 PM_BBTCA_DATA_NOT_PRESENT = 0;

//-----------------------------------------------------------------
//##ModelId=3C1F6F720290
PM_BbTca::PM_BbTca(uint32 theNumberOfParam):
    myCounters(0),
    myStates(0),
    myStatesUnFiltered(0),
    myOccurTime(NULL),
    myCrossedValue(NULL),
    myNumberOfParam(theNumberOfParam)
{
    // Nothing else to do for now.
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F72029A
PM_BbTca::~PM_BbTca ()
{
    if( myCrossedValue )
    {
        delete [] myCrossedValue;
    }
    myCrossedValue = NULL;

    if( myOccurTime )
    {
        delete [] myOccurTime;
    }
    myOccurTime = NULL;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F72029C
void PM_BbTca::Reset()
{
    ResetAllTca();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7202A5
bool PM_BbTca::GetTcaState(CT_PM_Parameter theParameter) const
{
    return (myStates & (0x01 << theParameter)) != 0;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA8006A
bool PM_BbTca::GetTcaUnFilteredState(CT_PM_Parameter theParameter) const
{
    return (myStatesUnFiltered & (0x01 << theParameter)) != 0;

}

//-----------------------------------------------------------------
bool PM_BbTca::GetAnyTcaDeclared() const
{
    return  (myStates != 0) ? true : false;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA800EC
uint8 PM_BbTca::GetTcaCounter(CT_PM_Parameter theParameter) const
{
    return (uint8)((myCounters & (0x03 << (theParameter*2))) >> (theParameter*2));

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7202B9
void PM_BbTca::SetBbTca(CT_PM_Parameter theParameter,
                        FC_Time         theOccurTime,
                        CT_PM_64BitValue theCrossedValue,
                        CT_EntityType theEntityType)
{
    uint8 count;

    // Set TCA state.
    myStates |= (0x01 << theParameter);

    // Increment TCA counter.
    // Note that 2 bits counters are kept for each parameter (maximum of 16 parameters).
    count = GetTcaCounter(theParameter) + 1;
    // Clear counter.
    myCounters &= ~(0x03 << (theParameter*2));
    // Set counter.
    myCounters |= ((count & 0x03) << (theParameter*2));

    // Set occur time.
    SetOccurTime(theParameter, theOccurTime);

    // Set crossed value.
    SetCrossedValue(theParameter, theCrossedValue, theEntityType);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA80150
void PM_BbTca::SetTcaUnFiltered(CT_PM_Parameter theParameter)
{
    // Set TCA state.
    myStatesUnFiltered |= (0x01 << theParameter);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7202FE
void PM_BbTca::ResetTca(CT_PM_Parameter theParameter)
{
    // Reset filtered and unfiltered TCA states.
    myStates &= ~(0x01 << theParameter);
    ResetTcaUnFiltered(theParameter);

    // Do not reset TCA counters.

}

//-----------------------------------------------------------------
//##ModelId=3FA16104024C
void PM_BbTca::ResetTcaUnFiltered(CT_PM_Parameter theParameter)
{
    // Reset unfiltered TCA states.
    myStatesUnFiltered &= ~(0x01 << theParameter);

    // Do not reset TCA counters.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F720331
ostream& PM_BbTca::WriteObject(ostream& theStream )
{
    time_t  occurTime;
    char    tmpBuff[30];
    struct  tm tmpTm;
    char    occurTimeString[30];

    theStream << FC_InsertVar(myStates);
    theStream << FC_InsertVar(myStatesUnFiltered);
    theStream << FC_InsertVar(myCounters);
    theStream << FC_InsertVar(myNumberOfParam);

    if( (myOccurTime != NULL) && (myCrossedValue != NULL) )
    {
        for (uint32 i=0; i<myNumberOfParam; i++)
        {
            occurTime = myOccurTime[i].GetUTCTime();
            if ( strlen(FC_TimeService::Asctime(FC_TimeService::Gmtime(&occurTime,&tmpTm),tmpBuff)) <= 30 )
            {
                strcpy(occurTimeString, FC_TimeService::Asctime(FC_TimeService::Gmtime(&occurTime,&tmpTm),tmpBuff));
            }
            theStream << FC_InsertVar(occurTime);
            theStream << FC_InsertVar(occurTimeString);
            theStream << FC_InsertVar(myCrossedValue[i].SignedValue);
            theStream << FC_InsertVar(myCrossedValue[i].UnsignedValue);
        }
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F72034E
istream& PM_BbTca::ReadObject(istream& theStream )
{
    time_t occurTime;

    theStream >> FC_ExtractVar(myStates);
    theStream >> FC_ExtractVar(myStatesUnFiltered);
    theStream >> FC_ExtractVar(myCounters);
    theStream >> FC_ExtractVar(occurTime);

    if( (myOccurTime != NULL) && (myCrossedValue != NULL) )
    {
        theStream >> FC_ExtractVar(myCrossedValue[0].SignedValue);
        theStream >> FC_ExtractVar(myCrossedValue[0].UnsignedValue);

        myOccurTime[0].SetUTCTime(occurTime);
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F720359
FC_Stream& PM_BbTca::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myStates;
    theStream << myStatesUnFiltered;
    theStream << myCounters;

    if( (myOccurTime != NULL) && (myCrossedValue != NULL) )
    {
        theStream << PM_BBTCA_DATA_PRESENT;

        for (uint32 i=0; i<myNumberOfParam; i++)
        {
            myOccurTime[i].WriteObjectBinary(theStream);
        }

        theStream.write_array((int32*)myCrossedValue, myNumberOfParam);
    }
    else
    {
        theStream << PM_BBTCA_DATA_NOT_PRESENT;
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F72036C
FC_Stream& PM_BbTca::ReadObjectBinary( FC_Stream& theStream )
{
    uint8 tcaPresent;

    theStream >> myStates;
    theStream >> myStatesUnFiltered;
    theStream >> myCounters;
    theStream >> tcaPresent;

    if( (tcaPresent == PM_BBTCA_DATA_PRESENT) )
    {
        if( (myOccurTime == NULL) || (myCrossedValue == NULL) )
        {
            AllocateEventData();
        }

        for (uint32 i=0; i<myNumberOfParam; i++)
        {
            myOccurTime[i].ReadObjectBinary(theStream);
        }

        theStream.read_array((int32*)myCrossedValue, myNumberOfParam);
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F72031C
bool PM_BbTca::operator==(const PM_BbTca& theOtherTCA) const
{
    bool retVal = true;

    if( (myStates != theOtherTCA.myStates) ||
        (myStatesUnFiltered != theOtherTCA.myStatesUnFiltered) ||
        (myCounters != theOtherTCA.myCounters) )
    {
        retVal = false;
    }

    if( retVal                              &&
        (myOccurTime != NULL)               &&
        (theOtherTCA.myOccurTime != NULL )  &&
        (myCrossedValue != NULL)            &&
        (theOtherTCA.myCrossedValue != NULL) )
    {
        for (uint32 i=0; i<myNumberOfParam; i++)
        {
            if( (myOccurTime[i] != theOtherTCA.myOccurTime[i]) ||
                (myCrossedValue[i].SignedValue != theOtherTCA.myCrossedValue[i].SignedValue) ||
                (myCrossedValue[i].UnsignedValue != theOtherTCA.myCrossedValue[i].UnsignedValue) )
            {
                retVal = false;
                break;
            }
        }
    }

    return retVal;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F720328
PM_BbTca& PM_BbTca::operator=(const PM_BbTca& theOtherTCA)
{
    myStates = theOtherTCA.myStates;
    myStatesUnFiltered = theOtherTCA.myStatesUnFiltered;
    myCounters = theOtherTCA.myCounters;

    if( (myOccurTime != NULL)               &&
        (theOtherTCA.myOccurTime != NULL )  &&
        (myCrossedValue != NULL)            &&
        (theOtherTCA.myCrossedValue != NULL) )
    {
        for (uint32 i=0; i<myNumberOfParam; i++)
        {
            myOccurTime[i] = theOtherTCA.myOccurTime[i];
            myCrossedValue[i] = theOtherTCA.myCrossedValue[i];
        }
    }

    return *this;

}

//-----------------------------------------------------------------
void PM_BbTca::ResetAllTca()
{
    myStates = 0;
    myStatesUnFiltered = 0;

    if( (myOccurTime != NULL) && (myCrossedValue != NULL) )
    {
        for (uint32 i=0; i<myNumberOfParam; i++)
        {
            myCrossedValue[i].UnsignedValue = 0;
            myOccurTime[i].SetUTCTime(0);;
        }
    }
}

//-----------------------------------------------------------------
FC_Time PM_BbTca::GetOccurTime(CT_PM_Parameter theParameter) const
{
    if( myOccurTime != NULL )
    {
        return myOccurTime[theParameter];
    }
    else
    {
        FC_Time occurTime;

        occurTime.SetUTCTime(0);
        return occurTime;
    }

}

//-----------------------------------------------------------------
void PM_BbTca::SetOccurTime(CT_PM_Parameter theParameter, FC_Time theOccuringTime)
{
    if( myOccurTime != NULL )
    {
        myOccurTime[theParameter] = theOccuringTime;
    }
}

//-----------------------------------------------------------------
CT_PM_64BitValue PM_BbTca::GetCrossedValue(CT_PM_Parameter theParameter, CT_EntityType theEntityType, bool isGaugeValue) const
{
    if ( myCrossedValue != NULL )
    {
        CT_PM_64BitValue a64BitValue;

        if ( theEntityType == CT_ODU4 )
        {
            if ( (theParameter == PM_TypeOdu::PM_CV) && (myNumberOfParam > PM_TypeOdu::PM_CV_HIGH) )
            {
                uint32 aHighValue = myCrossedValue[PM_TypeOdu::PM_CV_HIGH].UnsignedValue; 
                uint32 aLowValue  = myCrossedValue[PM_TypeOdu::PM_CV].UnsignedValue;
                a64BitValue.UnsignedValue = (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue;
                return a64BitValue;
            }
        }
        else if ( theEntityType == CT_ODU4T )
        {
            if ( (theParameter == PM_TypeTcm::PM_CV) && (myNumberOfParam > PM_TypeTcm::PM_CV_HIGH) )
            {
                uint32 aHighValue = myCrossedValue[PM_TypeTcm::PM_CV_HIGH].UnsignedValue;
                uint32 aLowValue  = myCrossedValue[PM_TypeTcm::PM_CV].UnsignedValue;
                a64BitValue.UnsignedValue = (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue;
                return a64BitValue;
            }
        }
        else if ( theEntityType == CT_OTU4 )
        {
            if ( (theParameter == PM_TypeOtu::PM_CV) && (myNumberOfParam > PM_TypeOtu::PM_CV_HIGH) )
            {
                uint32 aHighValue = myCrossedValue[PM_TypeOtu::PM_CV_HIGH].UnsignedValue;
                uint32 aLowValue  = myCrossedValue[PM_TypeOtu::PM_CV].UnsignedValue;
                a64BitValue.UnsignedValue = (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue;
                return a64BitValue;
            }
            else if ( (theParameter == PM_TypeOtu::PM_BE) && (myNumberOfParam > PM_TypeOtu::PM_BE_HIGH) )
            {
                uint32 aHighValue = myCrossedValue[PM_TypeOtu::PM_BE_HIGH].UnsignedValue;
                uint32 aLowValue  = myCrossedValue[PM_TypeOtu::PM_BE].UnsignedValue;
                a64BitValue.UnsignedValue = (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue;
                return a64BitValue;
            }
        }
        else if ( theEntityType == CT_ETH ) // symbolize HGE && Data
        {
            if ( (theParameter == PM_TypeData::PM_SE) && (myNumberOfParam > PM_TypeData::PM_SE_HIGH) )
            {
                uint32 aHighValue = myCrossedValue[PM_TypeData::PM_SE_HIGH].UnsignedValue;
                uint32 aLowValue  = myCrossedValue[PM_TypeData::PM_SE].UnsignedValue;
                a64BitValue.UnsignedValue = (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue;
                return a64BitValue;
            }
        }
        else if ( theEntityType == CT_HGE || theEntityType == CT_FGE) // symbolize HGE && Rmon
        {
            PM_TypeRmonCounter::PM_Param aLowParam  = PM_TypeRmonCounter::PM_PARAM_NUM;
            PM_TypeRmonCounter::PM_Param aHighParam = PM_TypeRmonCounter::PM_PARAM_NUM;

            switch ( theParameter )
            {
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_DROP: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_DROP_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_DROP;
                        aHighParam = PM_TypeRmonCounter::PM_DROP_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_PKT: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_PKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_PKT;
                        aHighParam = PM_TypeRmonCounter::PM_PKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_BCPKT: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_BCPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_BCPKT;
                        aHighParam = PM_TypeRmonCounter::PM_BCPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_MCPKT: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_MCPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_MCPKT;
                        aHighParam = PM_TypeRmonCounter::PM_MCPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_CRCAE: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_CRCAE_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_CRCAE;
                        aHighParam = PM_TypeRmonCounter::PM_CRCAE_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_USPKT: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_USPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_USPKT;
                        aHighParam = PM_TypeRmonCounter::PM_USPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_OSPKT: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_OSPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_OSPKT;
                        aHighParam = PM_TypeRmonCounter::PM_OSPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_FRAG: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_FRAG_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_FRAG;
                        aHighParam = PM_TypeRmonCounter::PM_FRAG_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_JABR: 
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_JABR_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_JABR;
                        aHighParam = PM_TypeRmonCounter::PM_JABR_HIGH;
                    }
                    break;
                default:
                    break;
            }

            if ( aLowParam != aHighParam ) // both defaulted to PM_PARAM_NUM
            {
                uint32 aHighValue = myCrossedValue[aHighParam].UnsignedValue;
                uint32 aLowValue  = myCrossedValue[aLowParam ].UnsignedValue;
                a64BitValue.UnsignedValue = (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue;
                return a64BitValue;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        CT_PM_64BitValue crossedValue;

        if ( isGaugeValue )
        {
            crossedValue.SignedValue   = myCrossedValue[theParameter].SignedValue;
        }
        else // Counter (Unsigned)
        {
            crossedValue.UnsignedValue = myCrossedValue[theParameter].UnsignedValue;
        }

        return crossedValue;
    }
    else
    {
        CT_PM_64BitValue crossedValue;
        crossedValue.UnsignedValue = 0;
        return crossedValue;
    }
}

//-----------------------------------------------------------------
void PM_BbTca::SetCrossedValue(CT_PM_Parameter theParameter, CT_PM_64BitValue theCrossedValue, CT_EntityType theEntityType)
{
    if( myCrossedValue != NULL )
    {
        // Set the crossed value with the current value.

        if ( theEntityType == CT_ODU4 )
        {
            if ( (theParameter == PM_TypeOdu::PM_CV) && (myNumberOfParam > PM_TypeOdu::PM_CV_HIGH) )
            {
                myCrossedValue[PM_TypeOdu::PM_CV_HIGH].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER); 
                myCrossedValue[PM_TypeOdu::PM_CV].UnsignedValue      = (uint32)(theCrossedValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);

                return;///////////////////////////////////////////////
            }
        }
        else if ( theEntityType == CT_ODU4T )
        {
            if ( (theParameter == PM_TypeTcm::PM_CV) && (myNumberOfParam > PM_TypeTcm::PM_CV_HIGH) )
            {
                myCrossedValue[PM_TypeTcm::PM_CV_HIGH].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER); 
                myCrossedValue[PM_TypeTcm::PM_CV].UnsignedValue      = (uint32)(theCrossedValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);

                return;///////////////////////////////////////////////
            }
        }
        else if ( theEntityType == CT_OTU4 )
        {
            if ( (theParameter == PM_TypeOtu::PM_CV) && (myNumberOfParam > PM_TypeOtu::PM_CV_HIGH) )
            {
                myCrossedValue[PM_TypeOtu::PM_CV_HIGH].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
                myCrossedValue[PM_TypeOtu::PM_CV].UnsignedValue      = (uint32)(theCrossedValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
 
                return;///////////////////////////////////////////////
            }
            else if ( (theParameter == PM_TypeOtu::PM_BE) && (myNumberOfParam > PM_TypeOtu::PM_BE_HIGH) )
            {
                myCrossedValue[PM_TypeOtu::PM_BE_HIGH].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
                myCrossedValue[PM_TypeOtu::PM_BE].UnsignedValue      = (uint32)(theCrossedValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
 
                return;///////////////////////////////////////////////
            }
        }
        else if ( theEntityType == CT_ETH ) // symbolize HGE && Data
        {
            if ( (theParameter == PM_TypeData::PM_SE) && (myNumberOfParam > PM_TypeData::PM_SE_HIGH) )
            {
                myCrossedValue[PM_TypeData::PM_SE_HIGH].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
                myCrossedValue[PM_TypeData::PM_SE].UnsignedValue      = (uint32)(theCrossedValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
 
                return;///////////////////////////////////////////////
            }
        }
        else if ( theEntityType == CT_HGE || theEntityType == CT_FGE) // symbolize HGE && Rmon
        {
            PM_TypeRmonCounter::PM_Param aLowParam  = PM_TypeRmonCounter::PM_PARAM_NUM;
            PM_TypeRmonCounter::PM_Param aHighParam = PM_TypeRmonCounter::PM_PARAM_NUM;
 
            switch ( theParameter )
            {
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_DROP:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_DROP_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_DROP;
                        aHighParam = PM_TypeRmonCounter::PM_DROP_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_PKT:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_PKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_PKT;
                        aHighParam = PM_TypeRmonCounter::PM_PKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_BCPKT:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_BCPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_BCPKT;
                        aHighParam = PM_TypeRmonCounter::PM_BCPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_MCPKT:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_MCPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_MCPKT;
                        aHighParam = PM_TypeRmonCounter::PM_MCPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_CRCAE:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_CRCAE_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_CRCAE;
                        aHighParam = PM_TypeRmonCounter::PM_CRCAE_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_USPKT:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_USPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_USPKT;
                        aHighParam = PM_TypeRmonCounter::PM_USPKT_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_OSPKT:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_OSPKT_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_OSPKT;
                        aHighParam = PM_TypeRmonCounter::PM_OSPKT_HIGH;
                    }
                    break;
                 case (CT_PM_Parameter) PM_TypeRmonCounter::PM_FRAG:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_FRAG_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_FRAG;
                        aHighParam = PM_TypeRmonCounter::PM_FRAG_HIGH;
                    }
                    break;
                case (CT_PM_Parameter) PM_TypeRmonCounter::PM_JABR:
                    if ( myNumberOfParam > PM_TypeRmonCounter::PM_JABR_HIGH )
                    {
                        aLowParam  = PM_TypeRmonCounter::PM_JABR;
                        aHighParam = PM_TypeRmonCounter::PM_JABR_HIGH;
                    }
                    break;
                default:
                    break;
            }

            if ( aLowParam != aHighParam ) // both defaulted to PM_PARAM_NUM
            {
                myCrossedValue[aHighParam].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
                myCrossedValue[aLowParam ].UnsignedValue = (uint32)(theCrossedValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);

            }
        }

        myCrossedValue[theParameter].UnsignedValue = (uint32)theCrossedValue.UnsignedValue;
    }
}

//-----------------------------------------------------------------
void PM_BbTca::AllocateEventData()
{
    if( myCrossedValue )
    {
        delete [] myCrossedValue;
    }
    myCrossedValue = new CT_PM_Value[myNumberOfParam];

    if( myOccurTime )
    {
        delete [] myOccurTime;
    }
    myOccurTime = new FC_Time[myNumberOfParam];

    for (uint32 i=0; i<myNumberOfParam; i++)
    {
        myCrossedValue[i].UnsignedValue = 0;
        myOccurTime[i].SetUTCTime(0);
    }
}
