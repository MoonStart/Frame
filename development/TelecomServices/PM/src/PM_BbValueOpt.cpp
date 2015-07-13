/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Optical layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueOpt.h>
#include <CommonTypes/CT_PM_Definition.h>

//-----------------------------------------------------------------
PM_BbValueOpt::PM_BbValueOpt(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeOpt::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbValueOpt::~PM_BbValueOpt()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbValueOpt::ResetAll(void)
{
    myCurValues[PM_TypeOpt::PM_OPR].SignedValue = 0;
    myMinValues[PM_TypeOpt::PM_OPR].SignedValue = CT_PM_DEFAULT_MIN_POWER;
    myMaxValues[PM_TypeOpt::PM_OPR].SignedValue = CT_PM_DEFAULT_MAX_POWER;

    myCurValues[PM_TypeOpt::PM_OPT].SignedValue = 0;
    myMinValues[PM_TypeOpt::PM_OPT].SignedValue = CT_PM_DEFAULT_MIN_POWER;
    myMaxValues[PM_TypeOpt::PM_OPT].SignedValue = CT_PM_DEFAULT_MAX_POWER;

    myCurValues[PM_TypeOpt::PM_DGD].SignedValue = 0;
    myMinValues[PM_TypeOpt::PM_DGD].SignedValue = CT_PM_DEFAULT_MIN_DGD;
    myMaxValues[PM_TypeOpt::PM_DGD].SignedValue = CT_PM_DEFAULT_MAX_DGD;

    myCurValues[PM_TypeOpt::PM_CD].SignedValue = 0;
    myMinValues[PM_TypeOpt::PM_CD].SignedValue = CT_PM_DEFAULT_MIN_CD;
    myMaxValues[PM_TypeOpt::PM_CD].SignedValue = CT_PM_DEFAULT_MAX_CD;

    myCurValues[PM_TypeOpt::PM_OSNR].SignedValue = 0;
    myMinValues[PM_TypeOpt::PM_OSNR].SignedValue = CT_PM_DEFAULT_MIN_OSNR;
    myMaxValues[PM_TypeOpt::PM_OSNR].SignedValue = CT_PM_DEFAULT_MAX_OSNR;
}

//-----------------------------------------------------------------
void PM_BbValueOpt::ResetMinParam(CT_PM_Parameter theParameter)
{
    if (myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        if /**/ ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_OPR )
        {
            myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_POWER;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_OPT )
        {
            myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_POWER;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_DGD )
        {
            myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_DGD;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_CD )
        {
            myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_CD;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_OSNR )
        {
            myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_OSNR;
        }
        else
        {
            FC_THROW_ERROR(FC_SWError, "PM_BbValueOpt::ResetMinParam()" );
        }

        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOpt::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
void PM_BbValueOpt::ResetMaxParam(CT_PM_Parameter theParameter)
{
    if (myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset maximum value.
        if /**/ ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_OPR )
        {
            myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_POWER;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_OPT )
        {
            myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_POWER;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_DGD )
        {
            myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_DGD;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_CD )
        {
            myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_CD;
        }
        else if ( theParameter == (CT_PM_Parameter)PM_TypeOpt::PM_OSNR )
        {
            myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_OSNR;
        }
        else
        {
            FC_THROW_ERROR(FC_SWError, "PM_BbValueOpt::ResetMaxParam()" );
        }

        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOpt::ResetMaxParam()" );
    }

}

//-----------------------------------------------------------------
ostream& PM_BbValueOpt::WriteObject( ostream& theStream )
{

    char m_OPR_Curbuf[80];
    char m_OPR_Minbuf[80];
    char m_OPR_Maxbuf[80];
    char m_OPT_Curbuf[80];
    char m_OPT_Minbuf[80];
    char m_OPT_Maxbuf[80];
    char m_DGD_Curbuf[80];
    char m_DGD_Minbuf[80];
    char m_DGD_Maxbuf[80];
    char m_CD_Curbuf[80];
    char m_CD_Minbuf[80];
    char m_CD_Maxbuf[80];
    char m_OSNR_Curbuf[80];
    char m_OSNR_Minbuf[80];
    char m_OSNR_Maxbuf[80];

    sprintf(m_OPR_Curbuf, "%d", myCurValues[PM_TypeOpt::PM_OPR].SignedValue);
    sprintf(m_OPR_Minbuf, "%d", myMinValues[PM_TypeOpt::PM_OPR].SignedValue);
    sprintf(m_OPR_Maxbuf, "%d", myMaxValues[PM_TypeOpt::PM_OPR].SignedValue);
    sprintf(m_OPT_Curbuf, "%d", myCurValues[PM_TypeOpt::PM_OPT].SignedValue);
    sprintf(m_OPT_Minbuf, "%d", myMinValues[PM_TypeOpt::PM_OPT].SignedValue);
    sprintf(m_OPT_Maxbuf, "%d", myMaxValues[PM_TypeOpt::PM_OPT].SignedValue);
    sprintf(m_DGD_Curbuf, "%d", myCurValues[PM_TypeOpt::PM_DGD].SignedValue);
    sprintf(m_DGD_Minbuf, "%d", myMinValues[PM_TypeOpt::PM_DGD].SignedValue);
    sprintf(m_DGD_Maxbuf, "%d", myMaxValues[PM_TypeOpt::PM_DGD].SignedValue);
    sprintf(m_CD_Curbuf,  "%d", myCurValues[PM_TypeOpt::PM_CD].SignedValue);
    sprintf(m_CD_Minbuf,  "%d", myMinValues[PM_TypeOpt::PM_CD].SignedValue);
    sprintf(m_CD_Maxbuf,  "%d", myMaxValues[PM_TypeOpt::PM_CD].SignedValue);
    sprintf(m_OSNR_Curbuf,"%d", myCurValues[PM_TypeOpt::PM_OSNR].SignedValue);
    sprintf(m_OSNR_Minbuf,"%d", myMinValues[PM_TypeOpt::PM_OSNR].SignedValue);
    sprintf(m_OSNR_Maxbuf,"%d", myMaxValues[PM_TypeOpt::PM_OSNR].SignedValue);

    fc_cout << "" << endl;
    fc_cout << "--------------------------------------------------------------" << endl;
    fc_cout << " OPR Current = " << m_OPR_Curbuf << endl;
    fc_cout << " OPR Minimum = " << m_OPR_Minbuf << endl;
    fc_cout << " OPR Maximum = " << m_OPR_Maxbuf << endl;
    fc_cout << " OPT Current = " << m_OPT_Curbuf << endl;
    fc_cout << " OPT Minimum = " << m_OPT_Minbuf << endl;
    fc_cout << " OPT Maximum = " << m_OPT_Maxbuf << endl;
    fc_cout << " DGD Current = " << m_DGD_Curbuf << endl;
    fc_cout << " DGD Minimum = " << m_DGD_Minbuf << endl;
    fc_cout << " DGD Maximum = " << m_DGD_Maxbuf << endl;
    fc_cout << " CD Current = "  << m_CD_Curbuf  << endl;
    fc_cout << " CD Minimum = "  << m_CD_Minbuf  << endl;
    fc_cout << " CD Maximum = "  << m_CD_Maxbuf  << endl;
    fc_cout << " OSNR Current = "<< m_OSNR_Curbuf<< endl;
    fc_cout << " OSNR Minimum = "<< m_OSNR_Minbuf<< endl;
    fc_cout << " OSNR Maximum = "<< m_OSNR_Maxbuf<< endl;
    fc_cout << "--------------------------------------------------------------" << endl;
    fc_cout << "" << endl;

    //------------------------------------------------------------------------

    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   << FC_InsertVar( myCurValues[PM_TypeOpt::PM_OPR].SignedValue )
                    << FC_InsertVar( myCurValues[PM_TypeOpt::PM_OPT].SignedValue )
                    << FC_InsertVar( myCurValues[PM_TypeOpt::PM_DGD].SignedValue )
                    << FC_InsertVar( myCurValues[PM_TypeOpt::PM_CD].SignedValue )
                    << FC_InsertVar( myCurValues[PM_TypeOpt::PM_OSNR].SignedValue );

        theStream   << FC_InsertVar( myMinValues[PM_TypeOpt::PM_OPR].SignedValue )
                    << FC_InsertVar( myMinValues[PM_TypeOpt::PM_OPT].SignedValue )
                    << FC_InsertVar( myMinValues[PM_TypeOpt::PM_DGD].SignedValue )
                    << FC_InsertVar( myMinValues[PM_TypeOpt::PM_CD].SignedValue )
                    << FC_InsertVar( myMinValues[PM_TypeOpt::PM_OSNR].SignedValue );

        theStream   << FC_InsertVar( myMaxValues[PM_TypeOpt::PM_OPR].SignedValue )
                    << FC_InsertVar( myMaxValues[PM_TypeOpt::PM_OPT].SignedValue )
                    << FC_InsertVar( myMaxValues[PM_TypeOpt::PM_DGD].SignedValue )
                    << FC_InsertVar( myMaxValues[PM_TypeOpt::PM_CD].SignedValue )
                    << FC_InsertVar( myMaxValues[PM_TypeOpt::PM_OSNR].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOpt::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueOpt::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   >> FC_ExtractVar( myCurValues[PM_TypeOpt::PM_OPR].SignedValue )
                    >> FC_ExtractVar( myCurValues[PM_TypeOpt::PM_OPT].SignedValue )
                    >> FC_ExtractVar( myCurValues[PM_TypeOpt::PM_DGD].SignedValue )
                    >> FC_ExtractVar( myCurValues[PM_TypeOpt::PM_CD].SignedValue )
                    >> FC_ExtractVar( myCurValues[PM_TypeOpt::PM_OSNR].SignedValue );

        theStream   >> FC_ExtractVar( myMinValues[PM_TypeOpt::PM_OPR].SignedValue )
                    >> FC_ExtractVar( myMinValues[PM_TypeOpt::PM_OPT].SignedValue )
                    >> FC_ExtractVar( myMinValues[PM_TypeOpt::PM_DGD].SignedValue )
                    >> FC_ExtractVar( myMinValues[PM_TypeOpt::PM_CD].SignedValue )
                    >> FC_ExtractVar( myMinValues[PM_TypeOpt::PM_OSNR].SignedValue );

        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeOpt::PM_OPR].SignedValue )
                    >> FC_ExtractVar( myMaxValues[PM_TypeOpt::PM_OPT].SignedValue )
                    >> FC_ExtractVar( myMaxValues[PM_TypeOpt::PM_DGD].SignedValue )
                    >> FC_ExtractVar( myMaxValues[PM_TypeOpt::PM_CD].SignedValue )
                    >> FC_ExtractVar( myMaxValues[PM_TypeOpt::PM_OSNR].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOpt::ReadObject()" );
    }

    return theStream;

}

PM_BbValueOptCounter::PM_BbValueOptCounter(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue(PM_TypeOptCounter::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbValueOptCounter::~PM_BbValueOptCounter()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueOptCounter::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeOptCounter::PM_PSC].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeOptCounter::PM_PSD].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOptCounter::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueOptCounter::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeOptCounter::PM_PSC].UnsignedValue  )
            >> FC_ExtractVar( myCurValues[PM_TypeOptCounter::PM_PSD].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOptCounter::ReadObject()" );
    }

    return theStream;

}
