/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TelecomServices Performance Monitoring

TARGET:         ActiveController, SMTMU, SSM

AUTHOR:         Michael Sharkey
-----------------------------------------------------------------------------*/

#include "PM_ProfileTable.h"
#include <PM/PM_TypeHopNearEnd.h>
#include <EPM/PM_TypeOdu.h>
#include <EPM/PM_TypeTcm.h>
#include <BaseClass/FC_TextStream.h>

PM_ProfileTable::PM_ProfileTable()
:myEntityType(CT_UNKNOWN_ENTITY_TYPE)
{
    myPMProfileTable_DIR1_15M = NULL; 
    myPMProfileTable_DIR2_15M = NULL; 
    myPMProfileTable_DIR1_1DAY = NULL; 
    myPMProfileTable_DIR2_1DAY = NULL;
}

PM_ProfileTable::~PM_ProfileTable()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            delete myPMProfileTable_DIR1_15M;
            delete myPMProfileTable_DIR2_15M;
            delete myPMProfileTable_DIR1_1DAY;
            delete myPMProfileTable_DIR2_1DAY;
            break;
        }

        default:
            break;
    }
}

void PM_ProfileTable::SetEntityType(CT_EntityType theEntityType)
{
    myEntityType = theEntityType;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myPMProfileTable_DIR1_15M = new PM_ProfileTableElem( theEntityType );
            myPMProfileTable_DIR2_15M = new PM_ProfileTableElem( theEntityType );
            myPMProfileTable_DIR1_1DAY = new PM_ProfileTableElem( theEntityType );
            myPMProfileTable_DIR2_1DAY = new PM_ProfileTableElem( theEntityType );
            break;
        }

        default:
            break;
    }
}

ostream& PM_ProfileTable::WriteObject(ostream& theStream)
{
    CT_EntityType aTableEntityType = myEntityType;
    theStream << FC_InsertVar(aTableEntityType);
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:     
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            fc_cout << "DIR1(LINE/TRMT) 15 min" << endl;
                    myPMProfileTable_DIR1_15M->WriteObject(theStream);
            fc_cout << "DIR1(LINE/TRMT) 24 hour" << endl;
                    myPMProfileTable_DIR1_1DAY->WriteObject(theStream);
            fc_cout << "DIR2(PORT/RCV ) 15 min" << endl;
                    myPMProfileTable_DIR2_15M->WriteObject(theStream);
            fc_cout << "DIR2(PORT/RCV) 24 hour" << endl;
                    myPMProfileTable_DIR2_1DAY->WriteObject(theStream);
            break;
        }

        default:
            break;
    }

    return theStream;
}

istream& PM_ProfileTable::ReadObject(istream& theStream)
{
    CT_EntityType aTableEntityType;
    theStream >> FC_ExtractVar(aTableEntityType);
    myEntityType = aTableEntityType;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myPMProfileTable_DIR1_15M->ReadObject(theStream);
            myPMProfileTable_DIR1_1DAY->ReadObject(theStream);
            myPMProfileTable_DIR2_15M->ReadObject(theStream);
            myPMProfileTable_DIR2_1DAY->ReadObject(theStream);
            break;
        }

        default:
            break;
    }

    return theStream;
}

FC_Stream& PM_ProfileTable::WriteObjectBinary(FC_Stream& theStream)
{
    theStream << myEntityType;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myPMProfileTable_DIR1_15M->WriteObjectBinary(theStream);
            myPMProfileTable_DIR1_1DAY->WriteObjectBinary(theStream);
            myPMProfileTable_DIR2_15M->WriteObjectBinary(theStream);
            myPMProfileTable_DIR2_1DAY->WriteObjectBinary(theStream);
            break;
        }
        default:
            break;
    }

    return theStream;
}

FC_Stream& PM_ProfileTable::ReadObjectBinary(FC_Stream& theStream)
{
    theStream >> myEntityType;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myPMProfileTable_DIR1_15M->ReadObjectBinary(theStream);
            myPMProfileTable_DIR1_1DAY->ReadObjectBinary(theStream);
            myPMProfileTable_DIR2_15M->ReadObjectBinary(theStream);
            myPMProfileTable_DIR2_1DAY->ReadObjectBinary(theStream);

            break;
        }
        default:
            break;
    }

    return theStream;
}

PM_ProfileTableElem* PM_ProfileTable::GetPMProfileTableElem(CT_DirectionFlag theDir,
                                                            CT_PM_Period thePeriod)
{
    if ( (theDir == CT_LINE_SIDE || theDir == CT_DIR_TRMT) && (thePeriod == CT_PM_PERIOD_15_MINUTES) )
    {
        return myPMProfileTable_DIR1_15M;
    }
    if ( (theDir == CT_LINE_SIDE || theDir == CT_DIR_TRMT) && (thePeriod == CT_PM_PERIOD_1_DAY) )
    {
        return myPMProfileTable_DIR1_1DAY;
    }
    if ( (theDir == CT_PORT_SIDE || theDir == CT_DIR_RCV) && (thePeriod == CT_PM_PERIOD_15_MINUTES) )
    {
        return myPMProfileTable_DIR2_15M;
    }
    if ( (theDir == CT_PORT_SIDE || theDir == CT_DIR_RCV) && (thePeriod == CT_PM_PERIOD_1_DAY) )
    {
        return myPMProfileTable_DIR2_1DAY;
    }
    return NULL;
}

//============================================================================
//============================================================================
//============================================================================

PM_ProfileTableElem::PM_ProfileTableElem(CT_EntityType theEntityType)
:myEntityType(theEntityType)
,myNbParams(0)
{
    myInUseState = false;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myNbParams = PM_TypeHopNearEnd::PM_PARAM_NUM;
            myThresholdList.reserve(PM_TypeHopNearEnd::PM_PARAM_NUM);
            for(int i = 0; i < myNbParams; i++)
            {
                myThresholdList.push_back(0);
            }
            break;
        }

        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            //---------------------------------------------------------------------------------------------------
            // The COUNTER and GAUGE params are needed for ODUK entity. GAUGE is multiplied by 2 for FLOOR/CEILING.
            //---------------------------------------------------------------------------------------------------
            myNbParams = (uint8)PM_TypeOdu::GetMaxNbParams( myEntityType ) + (PM_TypeOduGauge::PM_PARAM_NUM * 2);
            myThresholdList.reserve( myNbParams );
            for(int i = 0; i < myNbParams; i++)
            {
                myThresholdList.push_back(0);
            }
            break;
        }

        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            //---------------------------------------------------------------------------------------------------
            // The COUNTER and GAUGE params are needed for ODUK entity. GAUGE is multiplied by 2 for FLOOR/CEILING.
            //---------------------------------------------------------------------------------------------------
            myNbParams = (uint8)PM_TypeTcm::GetMaxNbParams( myEntityType ) + (PM_TypeTcmGauge::PM_PARAM_NUM * 2);
            myThresholdList.reserve( myNbParams );
            for(int i = 0; i < myNbParams; i++)
            {
                myThresholdList.push_back(0);
            }
            break;
        }

        default:
            break;
    }
}

PM_ProfileTableElem::~PM_ProfileTableElem()
{
}

ostream& PM_ProfileTableElem::WriteObject(ostream& theStream)
{
    theStream << FC_InsertVar(myInUseState);
    CT_EntityType anElemEntityType = myEntityType;
    theStream << FC_InsertVar(anElemEntityType);
    theStream << FC_InsertVar(myNbParams);
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            for(int i = 0; i < myNbParams; i++)
            {
                theStream << FC_InsertVar( myThresholdList[i] );
            }
            break;
        }
        default:
            break;
    }

    return theStream;
}

istream& PM_ProfileTableElem::ReadObject(istream& theStream)
{
    theStream >> FC_ExtractVar(myInUseState);
    CT_EntityType anElemEntityType;
    theStream >> FC_ExtractVar(anElemEntityType);
    myEntityType = anElemEntityType;
    theStream >> FC_ExtractVar(myNbParams);
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            for(int i = 0; i < myNbParams; i++)
            {
                theStream >> FC_ExtractVar( myThresholdList[i] );
            }
            break;
        }
        default:
            break;
    }

    return theStream;
}

FC_Stream& PM_ProfileTableElem::WriteObjectBinary(FC_Stream& theStream)
{
    theStream << myInUseState;
    theStream << myEntityType;
    theStream << myNbParams;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            for(int i = 0; i < myNbParams; i++)
            {
                theStream <<  myThresholdList[i];
            }
            break;
        }
        default:
            break;
    }

    return theStream;
}

FC_Stream& PM_ProfileTableElem::ReadObjectBinary(FC_Stream& theStream)
{
    theStream >> myInUseState;
    theStream >> myEntityType;
    theStream >> myNbParams;
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
            
        {
            for(int i = 0; i < myNbParams; i++)
            {
                theStream >> myThresholdList[i];
            }
            break;
        }
        default:
            break;
    }

    return theStream;
}

bool PM_ProfileTableElem::GetInUseState()
{
    return myInUseState;
}

uint32 PM_ProfileTableElem::GetCVPThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_CV];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetESPThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_ES];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetSESPThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_SES];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetUASPThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_UAS];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetFCPThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_FC];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetPJCDiffPThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_PJCDIFF];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetPJCSPGenThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_PJCSGEN];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetPJCSPDetThreshold()
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            return myThresholdList[PM_TypeHopNearEnd::PM_PJCSDET];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetCVODUThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            return myThresholdList[PM_TypeOdu::PM_CV];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetESODUThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            return myThresholdList[PM_TypeOdu::PM_ES];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetSESODUThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            return myThresholdList[PM_TypeOdu::PM_SES];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetUASODUThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            return myThresholdList[PM_TypeOdu::PM_UAS];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetCVTcmThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            return myThresholdList[PM_TypeTcm::PM_CV];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetESTcmThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            return myThresholdList[PM_TypeTcm::PM_ES];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetSESTcmThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            return myThresholdList[PM_TypeTcm::PM_SES];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetUASTcmThreshold()
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            return myThresholdList[PM_TypeTcm::PM_UAS];
            break;
        }
        default:
            break;
    }
    return 0;
}

uint32 PM_ProfileTableElem::GetThreshold( CT_PM_Parameter theId )
{
    if ( (CT_PM_Parameter)myNbParams > theId )
    {
        return myThresholdList[theId];
    }
    return 0;
}

void PM_ProfileTableElem::SetInUseState( bool theInUseState )
{
    myInUseState = theInUseState;
}

void PM_ProfileTableElem::SetCVPThreshold( uint32 theCVPThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_CV] = theCVPThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetESPThreshold( uint32 theESPThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_ES] = theESPThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetSESPThreshold( uint32 theSESPThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_SES] = theSESPThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetUASPThreshold( uint32 theUASPThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_UAS] = theUASPThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetFCPThreshold( uint32 theFCPThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_FC] = theFCPThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetPJCDiffPThreshold( uint32 thePJCDiffPThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_PJCDIFF] = thePJCDiffPThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetPJCSPGenThreshold( uint32 thePJCSPGenThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_PJCSGEN] = thePJCSPGenThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetPJCSPDetThreshold( uint32 thePJCSPDetThreshold )
{
    switch (myEntityType)
    {
        case CT_STS1:
        case CT_STS3C:
        case CT_STS12C:
        case CT_STS48C:
        case CT_STS192C:
        {
            myThresholdList[PM_TypeHopNearEnd::PM_PJCSDET] = thePJCSPDetThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetCVODUThreshold( uint32 theCVODUThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            myThresholdList[PM_TypeOdu::PM_CV] = theCVODUThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetESODUThreshold( uint32 theESODUThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            myThresholdList[PM_TypeOdu::PM_ES] = theESODUThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetSESODUThreshold( uint32 theSESODUThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            myThresholdList[PM_TypeOdu::PM_SES] = theSESODUThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetUASODUThreshold( uint32 theUASODUThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0:
        case CT_ODU1:
        case CT_ODU2:
        case CT_ODU2E:
        case CT_ODU3:
        case CT_ODU4:
        case CT_ODUF:
        {
            myThresholdList[PM_TypeOdu::PM_UAS] = theUASODUThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetCVTcmThreshold( uint32 theCVTcmThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myThresholdList[PM_TypeTcm::PM_CV] = theCVTcmThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetESTcmThreshold( uint32 theESTcmThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myThresholdList[PM_TypeTcm::PM_ES] = theESTcmThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetSESTcmThreshold( uint32 theSESTcmThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myThresholdList[PM_TypeTcm::PM_SES] = theSESTcmThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetUASTcmThreshold( uint32 theUASTcmThreshold )
{
    switch (myEntityType)
    {
        case CT_ODU0TA:
        case CT_ODU0TB:
        case CT_ODU1TA:
        case CT_ODU1TB:
        case CT_ODU2TA:
        case CT_ODU2TB:
        case CT_ODU3TA:
        case CT_ODU3TB:
        case CT_ODU4TA:
        case CT_ODU4TB:
        case CT_ODUFTA:
        case CT_ODUFTB:
        case CT_ODU2ETA:
        case CT_ODU2ETB:
        {
            myThresholdList[PM_TypeTcm::PM_UAS] = theUASTcmThreshold;
            break;
        }
        default:
            break;
    }
}

void PM_ProfileTableElem::SetThreshold( CT_PM_Parameter theId, uint32 theThreshold )
{
    if ( (CT_PM_Parameter)myNbParams > theId )
    {
        myThresholdList[theId] = theThreshold;
    }
}
