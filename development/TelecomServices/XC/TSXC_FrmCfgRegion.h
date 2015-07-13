// Copyright(c) Tellabs Transport Group. All rights reserved

#ifndef _INC_TSXC_FrmCfgRegion_H
#define _INC_TSXC_FrmCfgRegion_H

#include <CommonTypes/CT_QrsTypes.h>

//------------------------------------------------------------------------------------------------------------------------
//--- This region is used to store Framer Cross Connect configuration
//------------------------------------------------------------------------------------------------------------------------
template <class T> class TSXC_FrmCfgRegion: public TSXC_BaseRegion<T>
{
public:

    TSXC_FrmCfgRegion(const FC_BbKey theKey): TSXC_BaseRegion<T>(theKey){}
    virtual ~TSXC_FrmCfgRegion() {}

    // Interfaces
    void Connect(
          uint8 IF, 
          uint8 IFE, 
          uint8 OF, 
          uint8 OFE, 
          CT_XC_ConnectType theConnType,
          CT_XC_CQMID* theRespId = NULL,
          bool theImmediateCommit = true);

    void Disconnect(
          uint8 OF, 
          uint8 OFE,
          CT_XC_CQMID* theRespId = NULL,
          bool theImmediateCommit = true);

    void ResetFrame(
          CT_XC_CQMID* theRespId = NULL,
          bool theImmediateCommit = true);

    // Helper Methods
    bool FrmXc_OsmFrontEndDevToFac(
          CT_TEL_HyphyFlexFrontEndDevice theOsmFrontEndDev, 
          uint8* IF, 
          uint8* IFE);

    bool FrmXc_OsmDevPortToFac(
          uint8 devicePort, 
          uint8 deviceChannel, 
          uint8* OF, 
          uint8* OFE);

    uint8 OduXc_OsmFrontEndDevToFac(
          CT_TEL_HyphyFlexFrontEndDevice firstOdu, 
          CT_TEL_HyphyFlexFrontEndDevice secondOdu, 
          uint8* IF, 
          uint8* OF, 
          bool secondOduIsOduF);

protected:

    virtual void PopulateUnknown();
    virtual void PopulateOSM1S();

private:

    bool FindValidOffset(uint8 IF,uint8 IFE,uint8 OF,uint8 OFE,int* FacilityOffsetPtr);
};

template<class T> void TSXC_FrmCfgRegion<T>::Connect(
  uint8 IF, 
  uint8 IFE, 
  uint8 OF, 
  uint8 OFE, 
  CT_XC_ConnectType theConnType,
  CT_XC_CQMID* theRespId,
  bool theImmediateCommit)
{
    int FacilityOffset = 0;
    bool ValidData;

    ValidData = FindValidOffset(IF, IFE, OF, OFE, &FacilityOffset);

    if(ValidData)
    {
        (*this)[FacilityOffset+OFE-1].SetInputFacility(IF);
        (*this)[FacilityOffset+OFE-1].SetInputFacilityEndpoint(IFE);
        (*this)[FacilityOffset+OFE-1].SetType(theConnType);
        (*this)[FacilityOffset+OFE-1].SetMapping(CT_XC_MAPPING_FIXED);
        (*this)[FacilityOffset+OFE-1].SetState(CT_XC_STATE_CONNECTED);

        this->SetRespIdAndCommit(theRespId, theImmediateCommit);
    }
}

template<class T> void TSXC_FrmCfgRegion<T>::Disconnect(
  uint8 OF, 
  uint8 OFE,
  CT_XC_CQMID* theRespId,
  bool theImmediateCommit)
{
    int FacilityOffset = 0;
    bool ValidData;

    ValidData = FindValidOffset(1, 1, OF, OFE, &FacilityOffset);

    if(ValidData)
    {
        (*this)[FacilityOffset+OFE-1].SetState(CT_XC_STATE_NOTCONNECTED);

        this->SetRespIdAndCommit(theRespId, theImmediateCommit);
    }
}

//---------------------------------------------------------------------------------------
template<class T> void TSXC_FrmCfgRegion<T>::ResetFrame(
  CT_XC_CQMID* theRespId,
  bool theImmediateCommit)
{
    int maxRegionSize = (int)this->Size();
    for(int i = 0; i < maxRegionSize; i++)
    {
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);
}

template<class T> bool TSXC_FrmCfgRegion<T>::FindValidOffset(uint8 IF, uint8 IFE, uint8 OF, uint8 OFE, int* FacilityOffsetPtr)
{
    bool Valid = FALSE;

    if(IF != 0 && OF != 0 && IFE != 0 && OFE != 0)
    {
        Valid = TRUE;
        if(this->myCardType == CARD_TYPE_OSM1S)
        {
            switch(IF)
            {
                // Frame XC
                // odu
                case XC_OSM1S_FRMXC_FRM_ODUK_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_FRMXC_FRM_ODUK_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_FRMXC_FRM_ODUK);
                    break;

                case XC_OSM1S_FRMXC_FRM_ODU1_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_FRMXC_FRM_ODU1_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_FRMXC_FRM_ODU1);
                    break;

                // cbr
                case XC_OSM1S_FRMXC_FRM_CBR_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_FRMXC_FRM_CBR_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_FRMXC_FRM_CBR);
                    break;

                case XC_OSM1S_FRMXC_FRM_GE_HYPHYFLEX0_FACILITY_ID:
                case XC_OSM1S_FRMXC_FRM_GE_HYPHYFLEX1_FACILITY_ID:
                    Valid = !(IFE > XC_MAX_OSM1S_FRMXC_FRM_GE);
                    break;

                default:
                    Valid = FALSE;
                    break;
            }

            if(Valid)
            {
                switch(OF)
                {
                    // Frame XC
                    // odu
                    case XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_ODUK);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_START;
                        break;
                        
                    case XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_ODU1);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_ODUK);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_START;
                        break;
                        
                    case XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_ODU1);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_START;
                        break;

                    // cbr
                    case XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_START;
                        break;

                    case XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_FACILITY_ID:
                        Valid = !(OFE > XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1);
                        *FacilityOffsetPtr = XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_START;
                        break;

                    default:
                        Valid = FALSE;
                        break;
                }
            }
        }
        else
        {
            Valid = FALSE;
        }
    }

    if(!Valid)
    {
        char errMsg[200];
        sprintf(errMsg, "TSXC_FrmCfgRegion<T>::FindValidOffset(IF= %d, IFE= %d, OF= %d, OFE= %d) returning FALSE for cardType = %d", IF, IFE, OF, OFE, this->myCardType);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return Valid;
}

//---------------------------------------------------------------------------------------
template<class T> bool TSXC_FrmCfgRegion<T>::FrmXc_OsmFrontEndDevToFac(CT_TEL_HyphyFlexFrontEndDevice theOsmFrontEndDev, uint8* IF, uint8* IFE)
{
    bool retVal = true;
    char errMsg[100];

    if(this->myCardType == CARD_TYPE_OSM1S)
    {
        switch(theOsmFrontEndDev)
        {
            // HyPhyflex 0

            case CT_TEL_HYPHYFLEX_CBR_DEV1:
            case CT_TEL_HYPHYFLEX_CBR_DEV2:
            case CT_TEL_HYPHYFLEX_CBR_DEV3:
            case CT_TEL_HYPHYFLEX_CBR_DEV4:
            case CT_TEL_HYPHYFLEX_CBR_DEV5:
            case CT_TEL_HYPHYFLEX_CBR_DEV6:
            case CT_TEL_HYPHYFLEX_CBR_DEV7:
            case CT_TEL_HYPHYFLEX_CBR_DEV8:
            case CT_TEL_HYPHYFLEX_CBR_DEV9:
            case CT_TEL_HYPHYFLEX_CBR_DEV10:
            case CT_TEL_HYPHYFLEX_CBR_DEV11:
            case CT_TEL_HYPHYFLEX_CBR_DEV12:
            case CT_TEL_HYPHYFLEX_CBR_DEV13:
            case CT_TEL_HYPHYFLEX_CBR_DEV14:
            case CT_TEL_HYPHYFLEX_CBR_DEV15:
            case CT_TEL_HYPHYFLEX_CBR_DEV16:
                *IF = XC_OSM1S_FRMXC_FRM_CBR_HYPHYFLEX0_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_CBR_DEV1) + 1;
                break;

            case CT_TEL_HYPHYFLEX_GE_DEV1:
            case CT_TEL_HYPHYFLEX_GE_DEV2:
            case CT_TEL_HYPHYFLEX_GE_DEV3:
            case CT_TEL_HYPHYFLEX_GE_DEV4:
            case CT_TEL_HYPHYFLEX_GE_DEV5:
            case CT_TEL_HYPHYFLEX_GE_DEV6:
            case CT_TEL_HYPHYFLEX_GE_DEV7:
            case CT_TEL_HYPHYFLEX_GE_DEV8:
            case CT_TEL_HYPHYFLEX_GE_DEV9:
            case CT_TEL_HYPHYFLEX_GE_DEV10:
            case CT_TEL_HYPHYFLEX_GE_DEV11:
            case CT_TEL_HYPHYFLEX_GE_DEV12:
            case CT_TEL_HYPHYFLEX_GE_DEV13:
            case CT_TEL_HYPHYFLEX_GE_DEV14:
            case CT_TEL_HYPHYFLEX_GE_DEV15:
            case CT_TEL_HYPHYFLEX_GE_DEV16:
                *IF = XC_OSM1S_FRMXC_FRM_GE_HYPHYFLEX0_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_GE_DEV1) + 1;
                break;

            case CT_TEL_HYPHYFLEX_ODUK_DEV1:
            case CT_TEL_HYPHYFLEX_ODUK_DEV2:
            case CT_TEL_HYPHYFLEX_ODUK_DEV3:
            case CT_TEL_HYPHYFLEX_ODUK_DEV4:
            case CT_TEL_HYPHYFLEX_ODUK_DEV5:
            case CT_TEL_HYPHYFLEX_ODUK_DEV6:
            case CT_TEL_HYPHYFLEX_ODUK_DEV7:
            case CT_TEL_HYPHYFLEX_ODUK_DEV8:
            case CT_TEL_HYPHYFLEX_ODUK_DEV9:
            case CT_TEL_HYPHYFLEX_ODUK_DEV10:
            case CT_TEL_HYPHYFLEX_ODUK_DEV11:
            case CT_TEL_HYPHYFLEX_ODUK_DEV12:
            case CT_TEL_HYPHYFLEX_ODUK_DEV13:
            case CT_TEL_HYPHYFLEX_ODUK_DEV14:
            case CT_TEL_HYPHYFLEX_ODUK_DEV15:
            case CT_TEL_HYPHYFLEX_ODUK_DEV16:
                *IF = XC_OSM1S_FRMXC_FRM_ODUK_HYPHYFLEX0_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_ODUK_DEV1) + 1;
                break;

            case CT_TEL_HYPHYFLEX_OTU1_DEV1:
            case CT_TEL_HYPHYFLEX_OTU1_DEV2:
            case CT_TEL_HYPHYFLEX_OTU1_DEV3:
            case CT_TEL_HYPHYFLEX_OTU1_DEV4:
            case CT_TEL_HYPHYFLEX_OTU1_DEV5:
            case CT_TEL_HYPHYFLEX_OTU1_DEV6:
            case CT_TEL_HYPHYFLEX_OTU1_DEV7:
            case CT_TEL_HYPHYFLEX_OTU1_DEV8:
                *IF = XC_OSM1S_FRMXC_FRM_ODU1_HYPHYFLEX0_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_OTU1_DEV1) + 1;
                break;


            // HyPhyflex 1

            case CT_TEL_HYPHYFLEX_1_CBR_DEV1:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV2:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV3:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV4:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV5:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV6:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV7:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV8:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV9:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV10:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV11:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV12:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV13:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV14:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV15:
            case CT_TEL_HYPHYFLEX_1_CBR_DEV16:
                *IF = XC_OSM1S_FRMXC_FRM_CBR_HYPHYFLEX1_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_1_CBR_DEV1) + 1;
                break;

            case CT_TEL_HYPHYFLEX_1_GE_DEV1:
            case CT_TEL_HYPHYFLEX_1_GE_DEV2:
            case CT_TEL_HYPHYFLEX_1_GE_DEV3:
            case CT_TEL_HYPHYFLEX_1_GE_DEV4:
            case CT_TEL_HYPHYFLEX_1_GE_DEV5:
            case CT_TEL_HYPHYFLEX_1_GE_DEV6:
            case CT_TEL_HYPHYFLEX_1_GE_DEV7:
            case CT_TEL_HYPHYFLEX_1_GE_DEV8:
            case CT_TEL_HYPHYFLEX_1_GE_DEV9:
            case CT_TEL_HYPHYFLEX_1_GE_DEV10:
            case CT_TEL_HYPHYFLEX_1_GE_DEV11:
            case CT_TEL_HYPHYFLEX_1_GE_DEV12:
            case CT_TEL_HYPHYFLEX_1_GE_DEV13:
            case CT_TEL_HYPHYFLEX_1_GE_DEV14:
            case CT_TEL_HYPHYFLEX_1_GE_DEV15:
            case CT_TEL_HYPHYFLEX_1_GE_DEV16:
                *IF = XC_OSM1S_FRMXC_FRM_GE_HYPHYFLEX1_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_1_GE_DEV1) + 1;
                break;

            case CT_TEL_HYPHYFLEX_1_ODUK_DEV1:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV2:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV3:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV4:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV5:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV6:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV7:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV8:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV9:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV10:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV11:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV12:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV13:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV14:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV15:
            case CT_TEL_HYPHYFLEX_1_ODUK_DEV16:
                *IF = XC_OSM1S_FRMXC_FRM_ODUK_HYPHYFLEX1_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_1_ODUK_DEV1) + 1;
                break;

            case CT_TEL_HYPHYFLEX_1_OTU1_DEV1:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV2:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV3:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV4:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV5:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV6:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV7:
            case CT_TEL_HYPHYFLEX_1_OTU1_DEV8:
                *IF = XC_OSM1S_FRMXC_FRM_ODU1_HYPHYFLEX1_FACILITY_ID;
                *IFE = (theOsmFrontEndDev - CT_TEL_HYPHYFLEX_1_OTU1_DEV1) + 1;
                break;

            default:
                retVal = false;
                sprintf(errMsg, "TSXC_FrmCfgRegion<T>::FrmXc_OsmFrontEndDevToFac(): Invalid theOsmFrontEndDev = %d", theOsmFrontEndDev);
                FC_REPORT_ERROR(FC_LogicError, errMsg);
        }
    }
    else
    {
        retVal = false;
        sprintf(errMsg, "TSXC_FrmCfgRegion<T>::FrmXc_OsmFrontEndDevToFac(): Invalid cardType = %d", this->myCardType);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> bool TSXC_FrmCfgRegion<T>::FrmXc_OsmDevPortToFac(uint8 devicePort, uint8 deviceChannel, uint8* OF, uint8* OFE)
{
    bool retVal = true;
    char errMsg[100];

    if(this->myCardType == CARD_TYPE_OSM1S)
    {
        switch(devicePort)
        {
            // HyPhyflex 0

            case OSM1S_OTN_ODUK_PORT0_HYPHYFLEX0:
            case OSM1S_OTN_ODUK_PORT1_HYPHYFLEX0:
                *OF = XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_FACILITY_ID;
                *OFE = (devicePort - OSM1S_OTN_ODUK_PORT0_HYPHYFLEX0) * 8 + deviceChannel + 1;
                break;

            case OSM1S_OTN_ODU1_PORT_HYPHYFLEX0:
                *OF = XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_FACILITY_ID;
                *OFE = deviceChannel + 1;
                break;

            case OSM1S_ODUKPP_ODUK_PORT0_HYPHYFLEX0:
                *OF = XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_FACILITY_ID;
                *OFE = deviceChannel + 1;
                break;

            case OSM1S_ODUKPP_ODUK_PORT1_HYPHYFLEX0:
                *OF = XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_FACILITY_ID;
                *OFE = deviceChannel + 1;
                break;

            case OSM1S_ODUKPP_ODU1_PORT_HYPHYFLEX0:
                if(deviceChannel < XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1)
                {
                    *OF = XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_FACILITY_ID;
                    *OFE = deviceChannel + 1;
                }
                else
                {
                    *OF = XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_FACILITY_ID;
                    *OFE = deviceChannel - XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1 + 1;
                }
                break;


            // HyPhyflex 1

            case OSM1S_OTN_ODUK_PORT0_HYPHYFLEX1:
            case OSM1S_OTN_ODUK_PORT1_HYPHYFLEX1:
                *OF = XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_FACILITY_ID;
                *OFE = (devicePort - OSM1S_OTN_ODUK_PORT0_HYPHYFLEX1) * 8 + deviceChannel + 1;
                break;

            case OSM1S_OTN_ODU1_PORT_HYPHYFLEX1:
                *OF = XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_FACILITY_ID;
                *OFE = deviceChannel + 1;
                break;

            case OSM1S_ODUKPP_ODUK_PORT0_HYPHYFLEX1:
                *OF = XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_FACILITY_ID;
                *OFE = deviceChannel + 1;
                break;

            case OSM1S_ODUKPP_ODUK_PORT1_HYPHYFLEX1:
                *OF = XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_FACILITY_ID;
                *OFE = deviceChannel + 1;
                break;

            case OSM1S_ODUKPP_ODU1_PORT_HYPHYFLEX1:
                if(deviceChannel < XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1)
                {
                    *OF = XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_FACILITY_ID;
                    *OFE = deviceChannel + 1;
                }
                else
                {
                    *OF = XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_FACILITY_ID;
                    *OFE = deviceChannel - XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1 + 1;
                }
                break;

            default:
                retVal = false;
                sprintf(errMsg, "TSXC_FrmCfgRegion<T>::FrmXc_OsmDevPortToFac(): Invalid DevicePort = %d", devicePort);
                FC_REPORT_ERROR(FC_LogicError, errMsg);
        }
    }
    else
    {
        retVal = false;
        sprintf(errMsg, "TSXC_ConfigRegion<T>::FrmXc_Osm2DevPortToFac(): Invalid cardType = %d", this->myCardType);
        FC_REPORT_ERROR(FC_LogicError, errMsg);
    }

    return retVal;
}

//---------------------------------------------------------------------------------------
template<class T> uint8 TSXC_FrmCfgRegion<T>::OduXc_OsmFrontEndDevToFac(CT_TEL_HyphyFlexFrontEndDevice firstOdu, CT_TEL_HyphyFlexFrontEndDevice secondOdu, uint8* IF, uint8* OF, bool secondOduIsOduF)
{
    return 0;
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_FrmCfgRegion<T>::PopulateUnknown()
{
    this->Resize(0);
}

//----------------------------------------------------------------------------------------------------------
template<class T> void TSXC_FrmCfgRegion<T>::PopulateOSM1S()
{
    this->Resize(XC_OSM1S_FRMXC_MAX_SIZE);

    // HyPhyflex chip 0

    int channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_START; i <= XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU0);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_START; i <= XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU1);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_START; i <= XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU0);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_START; i <= XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU1);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_START; i <= XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU0);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_START; i <= XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU1);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }


    // HyPhyflex chip 1

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_START; i <= XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU0);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_START; i <= XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU1);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_START; i <= XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU0);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_START; i <= XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU1);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_START; i <= XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU0);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }

    channel = 1;
    for(int i = XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_START; i <= XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_END; i++)
    {
        (*this)[i].SetOutputFacility(XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_FACILITY_ID);
        (*this)[i].SetOutputFacilityEndpoint(channel++);
        (*this)[i].SetType(CT_XC_TYPE_ODU1);
        (*this)[i].SetMapping(CT_XC_MAPPING_UNSPECIFIED);
        (*this)[i].SetState(CT_XC_STATE_NOTCONNECTED);
    }
}

#endif //--- _INC_TSXC_FrmCfgRegion_H
