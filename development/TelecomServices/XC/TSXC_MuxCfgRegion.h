/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_MUXCFGREGION_H
#define _INC_TSXC_MUXCFGREGION_H

#include <XC/TSXC_BaseRegion.h>

#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <CommonTypes/CT_QrsTypes.h>


template <class T>  class TSXC_MuxCfgRegion : public TSXC_BaseRegion<T>
{
public:

    // Constructor 
    TSXC_MuxCfgRegion(const FC_BbKey theKey) : TSXC_BaseRegion<T>(theKey) {}

	// Destructor
    virtual ~TSXC_MuxCfgRegion() {}

    // Interfaces
    void Connect(
          uint16 theIndex, 
          uint16 theHighOdu, 
          uint16 theLowOdu, 
          uint16* theTribSlot,
          CT_XC_CQMID* theRespId = NULL,
          bool theImmediateCommit = true);

    void ResetMux(
          CT_XC_CQMID* theRespId = NULL,
          bool theImmediateCommit = true);

    // Helper Methods
    uint16 OsmOduToFac(
      uint8 theOduPort,
      uint8 theOduChannel,
      CT_XC_ConnectType theConnType);

private:
    virtual void PopulateUnknown();
    virtual void PopulateOSM();
    virtual void PopulateOSM1S();
};

//------------------------------------------------------------------------------
template<class T> void TSXC_MuxCfgRegion<T>::Connect(
  uint16 theIndex, 
  uint16 theHighOdu, 
  uint16 theLowOdu, 
  uint16* theTribSlot,
  CT_XC_CQMID* theRespId,
  bool theImmediateCommit)
{
    if(theIndex < this->Size())
    {
        (*this)[theIndex].SetHighOdu(theHighOdu);
        (*this)[theIndex].SetLowOdu(theLowOdu);
        (*this)[theIndex].SetTribSlot(theTribSlot);

        this->SetRespIdAndCommit(theRespId, theImmediateCommit);
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_MuxCfgRegion<T>::ResetMux(
  CT_XC_CQMID* theRespId,
  bool theImmediateCommit)
{
    int maxRegionSize = (int)this->Size();
    for(int i = 0; i < maxRegionSize; i++)
    {
        (*this)[i].InitMux();
    }

    this->SetRespIdAndCommit(theRespId, theImmediateCommit);
}

//------------------------------------------------------------------------------
template<class T> uint16 TSXC_MuxCfgRegion<T>::OsmOduToFac(
  uint8 theOduPort,
  uint8 theOduChannel,
  CT_XC_ConnectType theConnType)
{
    uint16 aBaseXcFac = 0;
    uint16 aXcFac = 0xFFFF;
    char aErrMsg[90];

    // Prepare error message
    sprintf(aErrMsg, "theOduPort = %d, theOduChannel = %d, theConnType = %d", theOduPort, theOduChannel, theConnType);

    switch(theOduPort)
    {
        // * * * * * * OSM2S/C * * * * * * 
        /************ DIGI0 ***********/
        case OSM2_OTN_ODUK_PORT_DIGI0:
            switch (theConnType)
            {
                case CT_XC_TYPE_ODU0:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU0_0_FACILITY_ID;
                    break;
                case CT_XC_TYPE_ODUF:
                    aBaseXcFac = XC_OSM_ODUMUX_ODUF_0_FACILITY_ID;
                    break;
                default:
                    FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
                    break;
            }
            break;

        case OSM2_OTN_ODU1_PORT_DIGI0:
            aBaseXcFac = XC_OSM_ODUMUX_ODU1_0_FACILITY_ID;
            break;

        case OSM2_OTN_ODU2_PORT_DIGI0:
            switch (theConnType)
            {
                // ODU2 -> ODUx (x > 2)
                case CT_XC_TYPE_ODU2:  
                    aBaseXcFac = XC_OSM_ODUMUX_ODU2_0_FACILITY_ID;
                    break;
                // ODU2E -> ODUx (x > 2)
                case CT_XC_TYPE_ODU2E:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU2E_0_FACILITY_ID;
                    break;
                // ODU1 -> ODU2
                case CT_XC_TYPE_ODU1:
                // ODU0 -> ODU2
                case CT_XC_TYPE_ODU0:
                // ODUF -> ODU2
                case CT_XC_TYPE_ODUF:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU2_0_FACILITY_ID;
                    break;
                default:
                    FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
                    break;
            }
            break;

        case OSM2_OTN_ODU3_PORT_DIGI0:
            aBaseXcFac = XC_OSM_ODUMUX_ODU3_0_FACILITY_ID;
            break;

        case OSM2_OTN_ODU4_PORT_DIGI0:
            aBaseXcFac = XC_OSM_ODUMUX_ODU4_0_FACILITY_ID;
            break;

        case OSM2_CLIENT_ODU_PORT_DIGI0:
            // Invalid mux
            FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
            break;

        /************ DIGI1 ***********/
        case OSM2_OTN_ODUK_PORT_DIGI1:
            switch (theConnType)
            {
                case CT_XC_TYPE_ODU0:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU0_80_FACILITY_ID;
                    break;
                case CT_XC_TYPE_ODUF:
                    aBaseXcFac = XC_OSM_ODUMUX_ODUF_80_FACILITY_ID;
                    break;
                default:
                    FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
                    break;
            }
            break;

        case OSM2_OTN_ODU1_PORT_DIGI1:
            aBaseXcFac = XC_OSM_ODUMUX_ODU1_40_FACILITY_ID;
            break;

        case OSM2_OTN_ODU2_PORT_DIGI1:
            switch (theConnType)
            {
                // ODU2 -> ODUx (x > 2)
                case CT_XC_TYPE_ODU2:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU2_10_FACILITY_ID;
                    break;
                // ODU2E -> ODUx (x > 2)
                case CT_XC_TYPE_ODU2E:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU2E_10_FACILITY_ID;
                    break;
                // ODU1 -> ODU2
                case CT_XC_TYPE_ODU1:
                // ODU0 -> ODU2
                case CT_XC_TYPE_ODU0:
                // ODUF -> ODU2
                case CT_XC_TYPE_ODUF:
                    aBaseXcFac = XC_OSM_ODUMUX_ODU2_10_FACILITY_ID;
                    break;
                default:
                    FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
                    break;
            }
            break;

        case OSM2_OTN_ODU3_PORT_DIGI1:
            aBaseXcFac = XC_OSM_ODUMUX_ODU3_2_FACILITY_ID;
            break;

        case OSM2_OTN_ODU4_PORT_DIGI1:
            aBaseXcFac = XC_OSM_ODUMUX_ODU4_1_FACILITY_ID;
            break;

        case OSM2_CLIENT_ODU_PORT_DIGI1:
            // Invalid mux
            FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
            break;

        // * * * * * * OSM1S * * * * * * 
        // HyphyFlex0
        case OSM1S_OTN_ODUK_PORT0_HYPHYFLEX0:
            aBaseXcFac = XC_OSM1S_ODUMUX_ODUK_0_FACILITY_ID;
            break;

        case OSM1S_OTN_ODUK_PORT1_HYPHYFLEX0:
            aBaseXcFac = XC_OSM1S_ODUMUX_ODUK_8_FACILITY_ID;
            break;

        case OSM1S_OTN_ODU1_PORT_HYPHYFLEX0:
            aBaseXcFac = XC_OSM1S_ODUMUX_ODU1_0_FACILITY_ID;
            break;

        // HyphyFlex1
        case OSM1S_OTN_ODUK_PORT0_HYPHYFLEX1:
            aBaseXcFac = XC_OSM1S_ODUMUX_ODUK_16_FACILITY_ID;
            break;

        case OSM1S_OTN_ODUK_PORT1_HYPHYFLEX1:
            aBaseXcFac = XC_OSM1S_ODUMUX_ODUK_24_FACILITY_ID;
            break;

        case OSM1S_OTN_ODU1_PORT_HYPHYFLEX1:
            aBaseXcFac = XC_OSM1S_ODUMUX_ODU1_8_FACILITY_ID;
            break;


        default:
            FC_REPORT_ERROR(FC_RuntimeError, aErrMsg);
            break;
    }

    aXcFac = aBaseXcFac + theOduChannel;
    return aXcFac;
}

//------------------------------------------------------------------------------
template<class T> void TSXC_MuxCfgRegion<T>::PopulateUnknown()
{
    this->Resize(0);
}

//------------------------------------------------------------------------------
template<class T> void TSXC_MuxCfgRegion<T>::PopulateOSM()
{
    this->Resize(XC_OSM_MUX_MAX_SIZE);
    for(int i = 0; i < XC_OSM_MUX_MAX_SIZE; i++)
    {
        (*this)[i].InitMux();
    }
}

//------------------------------------------------------------------------------
template<class T> void TSXC_MuxCfgRegion<T>::PopulateOSM1S()
{
    this->Resize(XC_OSM1S_MUX_MAX_SIZE);
    for(int i = 0; i < XC_OSM1S_MUX_MAX_SIZE; i++)
    {
        (*this)[i].InitMux();
    }
}

#endif // _INC_TSXC_MUXCFGREGION_H
