//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OchHistory.h"
#include <BaseClass/FC_TextStream.h>
#include "CsPii/CSPII_CardIF.h"

CFG_OchHistory::CFG_OchHistory(uint32 theIndex):
    CFG_Object(theIndex),
        myHistCount(0),
    myIndex(theIndex)
{
    Reset();
}

CFG_OchHistory::~CFG_OchHistory()
{
}


void CFG_OchHistory::Reset()
{
    for(int i = 0; i < HW_REF_OCH_HISTORY_SIZE; i++)
        myOchHistory[i].myTimeStamp = 0;
}

ostream& CFG_OchHistory::WriteObject( ostream& theStream )
{
        CFG_Object::WriteObject(theStream);
    return theStream;

}

istream& CFG_OchHistory::ReadObject( istream& theStream )
{
        CFG_Object::ReadObject(theStream);
    return theStream;

}

FC_Stream& CFG_OchHistory::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    return theStream;

}

FC_Stream& CFG_OchHistory::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    return theStream;

}

///////////////////////////////////////////////////////////////////////////////
// Record the power change history
///////////////////////////////////////////////////////////////////////////////
void CFG_OchHistory::RecordHistory(CT_TEL_mBm evoaValToHw, CT_TEL_mBm evoaValFromHw)
{
    if (++myHistIdx >= HW_REF_OCH_HISTORY_SIZE) myHistIdx = 0;
    myOchHistory[myHistIdx].myTimeStamp    = CSPII_CardIF::GetInstance()->GetUTCTime();
    myOchHistory[myHistIdx].cfg                    = evoaValToHw;
    myOchHistory[myHistIdx].mon                    = evoaValFromHw;
        myHistCount++;
}


///////////////////////////////////////////////////////////////////////////////
// Record the power change history
///////////////////////////////////////////////////////////////////////////////
void CFG_OchHistory::RecordMoreHistory(bool activePath, uint8 portNumber)
{
    myOchHistory[myHistIdx].active         = activePath;
    myOchHistory[myHistIdx].port                   = portNumber;
}


///////////////////////////////////////////////////////////////////////////////
// Display Eova Change history
///////////////////////////////////////////////////////////////////////////////
void CFG_OchHistory::Display( FC_Stream& theStream )
{
        if(myHistCount)
        {
                char line[80];

                time_t currentTime = CSPII_CardIF::GetInstance()->GetUTCTime();
                int  hour    = int((currentTime/3600)%24);
                int  minute  = int((currentTime/60)%60);
                int  second  = int(currentTime%60);

                fc_cout << "\r\nEvoa History-"<<myIndex<<": "<<hour<<":"<<minute<<":"<<second<< endl;
                fc_cout << "\r              MON   CFG     act   port" << endl;
                fc_cout << "\r Time     Num Evoa  Evoa    path  num " << endl;
                fc_cout << "\r--------------------------------------" << endl;
                for (int i = 0; i < HW_REF_OCH_HISTORY_SIZE; i++)
                {
                        if(myOchHistory[i].myTimeStamp != 0)
                        {
                                hour    = int((myOchHistory[i].myTimeStamp/3600)%24);
                                minute  = int((myOchHistory[i].myTimeStamp/60)%60);
                                second  = int(myOchHistory[i].myTimeStamp%60);

                                sprintf(line, "\r %2d:%02d:%02d %3d %5d %5d     %1d    %2d",
                                                hour, minute, second,
                                                i,
                                                myOchHistory[i].mon,
                                                myOchHistory[i].cfg,
                        myOchHistory[i].active,
                        myOchHistory[i].port);
                                fc_cout << line << endl;
                        }
                }
                fc_cout << endl << endl;
        }
}
