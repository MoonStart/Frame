/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved
--------------------------------------------------------------------------*/

#include <XC/TSXC_MuxCfg.h>
#include <XC/TSXC_TestMenu.h>

//--------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------
TSXC_MuxCfg::TSXC_MuxCfg()
{
    InitMux();
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------
TSXC_MuxCfg::~TSXC_MuxCfg()
{
}

//--------------------------------------------------------------------------------------------------
ostream& TSXC_MuxCfg::WriteObject( ostream& theStream )
{
    theStream<<FC_InsertVar(myHighOdu);
    theStream<<FC_InsertVar(myLowOdu);
    for(int i=0; i < TSXC_MUX_BITMAP_LENGTH; i++)
    {
        theStream<<FC_InsertVar(myTribSlotBitmap[i]);
    }

    return theStream;
}

//--------------------------------------------------------------------------------------------------
istream& TSXC_MuxCfg::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myHighOdu);
    theStream>>FC_ExtractVar(myLowOdu);
    for(int i=0; i < TSXC_MUX_BITMAP_LENGTH; i++)
    {
        theStream>>FC_ExtractVar(myTribSlotBitmap[i]);
    }

    return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_MuxCfg::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myHighOdu;
    theStream<<myLowOdu;
    for(int i=0; i < TSXC_MUX_BITMAP_LENGTH; i++)
    {
        theStream<<myTribSlotBitmap[i];;
    }

    return theStream;
}

//--------------------------------------------------------------------------------------------------
FC_Stream& TSXC_MuxCfg::ReadObjectBinary( FC_Stream& theStream )
{
    theStream>>myHighOdu;
    theStream>>myLowOdu;
    for(int i=0; i < TSXC_MUX_BITMAP_LENGTH; i++)
    {
        theStream>>myTribSlotBitmap[i];;
    }

    return theStream;
}

//--------------------------------------------------------------------------------------------------
bool TSXC_MuxCfg::operator==(const TSXC_MuxCfg& theMuxCfg) const
{
    for(int i = 0; i < TSXC_MUX_BITMAP_LENGTH; i++)
    {
        if(myTribSlotBitmap[i] != theMuxCfg.myTribSlotBitmap[i])
            return false;
    }

    return  ( myHighOdu == theMuxCfg.myHighOdu && 
              myLowOdu  == theMuxCfg.myLowOdu );
}

//--------------------------------------------------------------------------------------------------
bool TSXC_MuxCfg::operator!=(const TSXC_MuxCfg& theMuxCfg) const
{
    return (!(*this == theMuxCfg));
}

//--------------------------------------------------------------------------------------------------
void TSXC_MuxCfg::InitMux()
{
    myHighOdu = 0;
    myLowOdu  = 0;
    memset(myTribSlotBitmap, 0, sizeof(uint16)*TSXC_MUX_BITMAP_LENGTH);
}

//--------------------------------------------------------------------------------------------------
void TSXC_MuxCfg::SetTribSlot(uint16* theTribSlot)
{
    memcpy(myTribSlotBitmap, theTribSlot, sizeof(uint16)*TSXC_MUX_BITMAP_LENGTH);
}

//--------------------------------------------------------------------------------------------------
void TSXC_MuxCfg::GetTribSlot(uint16* theTribSlot)
{
    memcpy(theTribSlot, myTribSlotBitmap, sizeof(uint16)*TSXC_MUX_BITMAP_LENGTH);
}

//--------------------------------------------------------------------------------------------------
void TSXC_MuxCfg::PrintMux()
{
    FC_FmtFlags previousFlags;

    if ( (myHighOdu != 0) && (myLowOdu != 0) )
    {
        previousFlags = fc_cout.Flags();
        fc_cout.Setf(ios::left);

        //fc_cout.Width(13);
        TSXC_TestMenu::ConnectFacToText(myHighOdu,false);
        //fc_cout.Width(13);
        TSXC_TestMenu::ConnectFacToText(myLowOdu,false);
        fc_cout.Width(24);
        char tribSlotBuf[50] = {0};
        sprintf(tribSlotBuf, "%04x %04x %04x %04x %04x",
                        myTribSlotBitmap[4],
                        myTribSlotBitmap[3],
                        myTribSlotBitmap[2],
                        myTribSlotBitmap[1],
                        myTribSlotBitmap[0]);
        fc_cout << tribSlotBuf;
        fc_cout << endl;
    
        fc_cout.Width(0);
        fc_cout.Flags(previousFlags);
    }
}


