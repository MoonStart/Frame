/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     12 December, 2001 Sebastien Cossette.
 DESCRIPTION:   Update and keep the PM status of Optical parameters.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_TxOptStatus.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbStatusOpt.h>


//-----------------------------------------------------------------
//##ModelId=3C20AB6D016A
PM_BbStatusOpt::PM_BbStatusOpt ()
:PM_BbStatus(PM_TypeOpt::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6D0173
PM_BbStatusOpt::~PM_BbStatusOpt ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6D01B9
void PM_BbStatusOpt::Update(MON_OptStatus& theOptMonitor, MON_TxOptStatus& theTxOptMonitor) 
{
    myParam[PM_TypeOpt::PM_OPR].UnsignedValue = theOptMonitor.GetTotalInputPower();
    myParam[PM_TypeOpt::PM_OPT].UnsignedValue = theTxOptMonitor.GetOutputPower();
    myParam[PM_TypeOpt::PM_DGD].UnsignedValue = theOptMonitor.GetDifferentialGroupDelay();
    myParam[PM_TypeOpt::PM_CD].UnsignedValue  = theOptMonitor.GetChromaticDispersion();
    myParam[PM_TypeOpt::PM_OSNR].UnsignedValue= (uint16)theOptMonitor.GetSignalNoiseRatio();

    myValidity[PM_TypeOpt::PM_OPR] = theOptMonitor.IsValidated();
    myValidity[PM_TypeOpt::PM_OPT] = theTxOptMonitor.IsValidated();
    myValidity[PM_TypeOpt::PM_DGD] = theOptMonitor.IsValidated();
    myValidity[PM_TypeOpt::PM_CD]  = theOptMonitor.IsValidated();
    myValidity[PM_TypeOpt::PM_OSNR]= theOptMonitor.IsValidated();

}

//-----------------------------------------------------------------
void PM_BbStatusOpt::Update(MON_OptStatus& theOptMonitor) 
{
    myParam[PM_TypeOpt::PM_OPR].UnsignedValue = theOptMonitor.GetTotalInputPower();
    myValidity[PM_TypeOpt::PM_OPR] = theOptMonitor.IsValidated();
    myParam[PM_TypeOpt::PM_DGD].UnsignedValue = theOptMonitor.GetDifferentialGroupDelay();
    myValidity[PM_TypeOpt::PM_DGD] = theOptMonitor.IsValidated();
    myParam[PM_TypeOpt::PM_CD].UnsignedValue  = theOptMonitor.GetChromaticDispersion();
    myValidity[PM_TypeOpt::PM_CD]  = theOptMonitor.IsValidated();
    myParam[PM_TypeOpt::PM_OSNR].UnsignedValue= (uint16)theOptMonitor.GetSignalNoiseRatio();
    myValidity[PM_TypeOpt::PM_OSNR]= theOptMonitor.IsValidated();
}

//-----------------------------------------------------------------
//##ModelId=3C20AB6D01C4
ostream& PM_BbStatusOpt::WriteObject( ostream& theStream )
{
    char m_OPR_buf[80];
    char m_OPT_buf[80];
    char m_DGD_buf[80];
    char m_CD_buf[80];
    char m_OSNR_buf[80];

    sprintf(m_OPR_buf, "%d", myParam[PM_TypeOpt::PM_OPR].SignedValue);
    sprintf(m_OPT_buf, "%d", myParam[PM_TypeOpt::PM_OPT].SignedValue);
    sprintf(m_DGD_buf, "%d", myParam[PM_TypeOpt::PM_DGD].SignedValue);
    sprintf(m_CD_buf,  "%d", myParam[PM_TypeOpt::PM_CD].SignedValue);
    sprintf(m_OSNR_buf,"%d", myParam[PM_TypeOpt::PM_OSNR].SignedValue);

    fc_cout << "" << endl;
    fc_cout << "--------------------------------------------------------------" << endl;
    fc_cout << " OPR (signed) = " << m_OPR_buf << endl;
    fc_cout << " OPT (signed) = " << m_OPT_buf << endl;
    fc_cout << " DGD (signed) = " << m_DGD_buf << endl;
    fc_cout << " CD  (signed) = " << m_CD_buf  << endl;
    fc_cout << " OSNR(signed) = " << m_OSNR_buf<< endl;
    fc_cout << "--------------------------------------------------------------" << endl;
    fc_cout << "" << endl;

    //------------------------------------------------------------------------

    return theStream << FC_InsertVar(myParam[PM_TypeOpt::PM_OPR].UnsignedValue)
                     << FC_InsertVar(myParam[PM_TypeOpt::PM_OPT].UnsignedValue)
                     << FC_InsertVar(myParam[PM_TypeOpt::PM_DGD].UnsignedValue)
                     << FC_InsertVar(myParam[PM_TypeOpt::PM_CD].UnsignedValue)
                     << FC_InsertVar(myParam[PM_TypeOpt::PM_OSNR].UnsignedValue)
                     << FC_InsertVar(myValidity[PM_TypeOpt::PM_OPR])
                     << FC_InsertVar(myValidity[PM_TypeOpt::PM_OPT])
                     << FC_InsertVar(myValidity[PM_TypeOpt::PM_DGD])
                     << FC_InsertVar(myValidity[PM_TypeOpt::PM_CD])
                     << FC_InsertVar(myValidity[PM_TypeOpt::PM_OSNR]);

}

//-----------------------------------------------------------------
//##ModelId=3C20AB6D01D7
istream& PM_BbStatusOpt::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myParam[PM_TypeOpt::PM_OPR].UnsignedValue)
                     >> FC_ExtractVar(myParam[PM_TypeOpt::PM_OPT].UnsignedValue)
                     >> FC_ExtractVar(myParam[PM_TypeOpt::PM_DGD].UnsignedValue)
                     >> FC_ExtractVar(myParam[PM_TypeOpt::PM_CD].UnsignedValue)
                     >> FC_ExtractVar(myParam[PM_TypeOpt::PM_OSNR].UnsignedValue)
                     >> FC_ExtractVar(myValidity[PM_TypeOpt::PM_OPR])
                     >> FC_ExtractVar(myValidity[PM_TypeOpt::PM_OPT])
                     >> FC_ExtractVar(myValidity[PM_TypeOpt::PM_DGD])
                     >> FC_ExtractVar(myValidity[PM_TypeOpt::PM_CD])
                     >> FC_ExtractVar(myValidity[PM_TypeOpt::PM_OSNR]);

}

//-----------------------------------------------------------------
//##ModelId=3CBC8F1001C6
void PM_BbStatusOpt::Init(restart_type theRestart)
{
    PM_BbStatus::Init(theRestart);

}
