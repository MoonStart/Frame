// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ERSIF.h"


SP_ERSDefaultImp::SP_ERSDefaultImp()
{
}

SP_ERSDefaultImp::~SP_ERSDefaultImp()
{
}

void SP_ERSDefaultImp::AcquireMastership()
{
    //No implementation
}
void SP_ERSDefaultImp::ReleaseMastership()
{
    //No implementation
}
bool SP_ERSDefaultImp::IsMaster()
{
    return false;
}
bool SP_ERSDefaultImp::IsMateMaster()
{
    return false;
}
bool SP_ERSDefaultImp::IsMatePresent()
{
    return false;
}
bool SP_ERSDefaultImp::IsMateReady()
{
    return true;
}
void SP_ERSDefaultImp::SendERSMessage(CT_ControllerMode theMode)
{
}
uint32 SP_ERSDefaultImp::GetRxMessageCounter()
{
    return 0;
}
bool SP_ERSDefaultImp::IsModuleOOS()
{
    return false;
}
bool SP_ERSDefaultImp::InitOnOOSAllowed()
{
    return true;
}
void SP_ERSDefaultImp::SetHeartBeatState(bool theState)
{
    //No implementation
}

bool SP_ERSDefaultImp::GetHeartBeatState()
{
    return true;
}

void SP_ERSDefaultImp::SetTxERSMessage(uint32 theMessage)
{
}
uint32 SP_ERSDefaultImp::GetTxERSMessage()
{
    return 0;
}
uint32 SP_ERSDefaultImp::GetRxERSMessage()
{
    return 0;
}
void SP_ERSDefaultImp::ControlActiveLED(bool isActive)
{
}