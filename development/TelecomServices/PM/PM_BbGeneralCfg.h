/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM Configuration of X values for RS, OTU/ODU signals.
--------------------------------------------------------------------------*/

#ifndef PM_BBGENERALCFG
#define PM_BBGENERALCFG

#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_BbObject.h>
#include <ErrorService/FC_Error.h>


//Keeps some global configuration parameters for the whole 
//network element. Parameters are the X values (used in the 
//accumulation of some parameters) and the offset value for 1 
//day accumulation period.
//##ModelId=3C1F6F6E023A
class PM_BbGeneralCfg : public PM_BbObject
{

public:

    //Class constructor.
    //##ModelId=3C1F6F6F0083
    PM_BbGeneralCfg(uint32 dummy = 0 );

    //Class default destructor.
    //##ModelId=3C1F6F6F008E
    virtual ~PM_BbGeneralCfg();

    //Resets the X values to their default value.
    //##ModelId=3C1F6F6F0097
    virtual void Reset();

    //Returns the X value for RS layer OC3 signal.
    //##ModelId=3C9255A503CB
    inline uint32 GetXvalueOc3() const;

    //Returns the X value for RS layer OC12 signal.
    //##ModelId=3C9255A503DF
    inline uint32 GetXvalueOc12() const;

    //Returns the X value for E1 signal.
    //##ModelId=3E6E4C9102F2
    inline uint32 GetXvalueE1() const;

    //Returns the X value for RS layer OC48 signal.
    //##ModelId=3C9255A60015
    inline uint32 GetXvalueOc48() const;

    //Returns the X value for RS layer OC192 signal.
    //##ModelId=3C9255A6001F
    inline uint32 GetXvalueOc192() const;

    //Returns the X value for RS layer OC768 signal.
    inline uint32 GetXvalueOc768() const;

    //Sets the X value for RS layer OC3 signal.
    //##ModelId=3C9255A60033
    inline void SetXvalueOc3(uint32 theXvalue );

    //Sets the X value for RS layer OC12 signal.
    //##ModelId=3C9255A6005B
    inline void SetXvalueOc12(uint32 theXvalue );

    //Sets the X value for E1 signal.
    //##ModelId=3E6E4C910310
    inline void SetXvalueE1(uint32 theXvalue );

    //Sets the X value for RS layer OC48 signal.
    //##ModelId=3C9255A6006F
    inline void SetXvalueOc48(uint32 theXvalue );

    //Sets the X value for RS layer OC192 signal.
    //##ModelId=3C9255A6008D
    inline void SetXvalueOc192(uint32 theXvalue );

    //Sets the X value for RS layer OC768 signal.
    inline void SetXvalueOc768(uint32 theXvalue );

    //Returns the X value for MS layer (near-end and far-end) OC3 signal.
    inline uint32 GetXvalueOc3Ms() const;

    //Returns the X value for MS layer (near-end and far-end) OC12 signal.
    inline uint32 GetXvalueOc12Ms() const;

    //Returns the X value for MS layer (near-end and far-end) OC48 signal.
    inline uint32 GetXvalueOc48Ms() const;

    //Returns the X value for MS layer (near-end and far-end) OC192 signal.
    inline uint32 GetXvalueOc192Ms() const;

    //Returns the X value for MS layer (near-end and far-end) OC768 signal.
    inline uint32 GetXvalueOc768Ms() const;

    //Sets the X value for MS layer (near-end and far-end) OC3 signal.
    inline void SetXvalueOc3Ms(uint32 theXvalue );

    //Sets the X value for MS layer (near-end and far-end) OC12 signal.
    inline void SetXvalueOc12Ms(uint32 theXvalue );

    //Sets the X value for MS layer (near-end and far-end) OC48 signal.
    inline void SetXvalueOc48Ms(uint32 theXvalue );

    //Sets the X value for MS layer (near-end and far-end) OC192 signal.
    inline void SetXvalueOc192Ms(uint32 theXvalue );

    //Sets the X value for MS layer (near-end and far-end) OC768 signal.
    inline void SetXvalueOc768Ms(uint32 theXvalue );
    
    //Returns the X value for HOP layer (near-end and far-end) OC3 signal.
    inline uint32 GetXvalueSts1() const;

    //Returns the X value for HOP layer (near-end and far-end) OC12 signal.
    inline uint32 GetXvalueSts3c() const;

    //Returns the X value for HOP layer (near-end and far-end) OC48 signal.
    inline uint32 GetXvalueSts12c() const;

    //Returns the X value for HOP layer (near-end and far-end) OC192 signal.
    inline uint32 GetXvalueSts48c() const;

    inline uint32 GetXvalueSts192c() const;

    //Sets the X value for HOP layer (near-end and far-end) OC3 signal.
    inline void SetXvalueSts1(uint32 theXvalue );

    //Sets the X value for HOP layer (near-end and far-end) OC12 signal.
    inline void SetXvalueSts3c(uint32 theXvalue );

    //Sets the X value for HOP layer (near-end and far-end) OC48 signal.
    inline void SetXvalueSts12c(uint32 theXvalue );

    //Sets the X value for HOP layer (near-end and far-end) OC192 signal.
    inline void SetXvalueSts48c(uint32 theXvalue );

    inline void SetXvalueSts192c(uint32 theXvalue );


    //Gets the X value for OTU/ODU layer 0.
    //##ModelId=3C9255A600AB
    inline uint32 GetXvalueOtuOduLayer0() const;

    //Gets the X value for OTU/ODU layer 1.
    //##ModelId=3C9255A600AB
    inline uint32 GetXvalueOtuOduLayer1() const;

    //Gets the X value for OTU/ODU layer 2.
    //##ModelId=3C9255A600B5
    inline uint32 GetXvalueOtuOduLayer2() const;

    //Gets the X value for OTU/ODU layer 2e.
    //##ModelId=3C9255A600B5
    inline uint32 GetXvalueOtuOduLayer2e() const;

    //Gets the X value for OTU/ODU layer 3.
    //##ModelId=3C9255A600B5
    inline uint32 GetXvalueOtuOduLayer3() const;

    //Gets the X value for OTU/ODU layer 3e2.
    //##ModelId=3C9255A600B5
    inline uint32 GetXvalueOtuOduLayer3e2() const;

    inline uint32 GetXvalueOtuOduLayer4() const;

    ////Gets the X value for OTU/ODU Flex
    inline uint32 GetXvalueOtuOduLayerF() const;

    //Sets the X value for OTU/ODU layer 0.
    //##ModelId=3C9255A600D3
    inline void SetXvalueOtuOduLayer0(uint32 theXvalue );

    //Sets the X value for OTU/ODU layer 1.
    //##ModelId=3C9255A600D3
    inline void SetXvalueOtuOduLayer1(uint32 theXvalue );

    //Sets the X value for OTU/ODU layer 2.
    //##ModelId=3C9255A600F1
    inline void SetXvalueOtuOduLayer2(uint32 theXvalue );

    //Sets the X value for OTU/ODU layer 2e.
    //##ModelId=3C9255A600F1
    inline void SetXvalueOtuOduLayer2e(uint32 theXvalue );

    //Sets the X value for OTU/ODU layer 3.
    //##ModelId=3C9255A600F1
    inline void SetXvalueOtuOduLayer3(uint32 theXvalue );

    //Sets the X value for OTU/ODU layer 3e2.
    //##ModelId=3C9255A600F1
    inline void SetXvalueOtuOduLayer3e2(uint32 theXvalue );

    inline void SetXvalueOtuOduLayer4(uint32 theXvalue );

    inline void SetXvalueOtuOduLayerF(uint32 theXvalue );

    //Gets the X value for OTU/ODUT layer 0.
    //##ModelId=3C9255A600AB
    inline uint32 GetXvalueOtuOduLayer0T() const;

    //Gets the X value for OTU/ODUT layer 1.
    //##ModelId=3C9255A600AB
    inline uint32 GetXvalueOtuOduLayer1T() const;

    //Gets the X value for OTU/ODUT layer 2.
    //##ModelId=3C9255A600B5
    inline uint32 GetXvalueOtuOduLayer2T() const;

    //Gets the X value for OTU/ODUT layer 3.
    //##ModelId=3C9255A600B5
    inline uint32 GetXvalueOtuOduLayer3T() const;

    inline uint32 GetXvalueOtuOduLayer4T() const;

    //Sets the X value for OTU/ODUT layer 0.
    //##ModelId=3C9255A600D3
    inline void SetXvalueOtuOduLayer0T(uint32 theXvalue );

    //Sets the X value for OTU/ODUT layer 1.
    //##ModelId=3C9255A600D3
    inline void SetXvalueOtuOduLayer1T(uint32 theXvalue );

    //Sets the X value for OTU/ODUT layer 2.
    //##ModelId=3C9255A600F1
    inline void SetXvalueOtuOduLayer2T(uint32 theXvalue );
    inline void SetXvalueOtuOduLayer2eT(uint32 theXvalue );

    //Sets the X value for OTU/ODUT layer 3.
    //##ModelId=3C9255A600F1
    inline void SetXvalueOtuOduLayer3T(uint32 theXvalue );

    inline void SetXvalueOtuOduLayer4T(uint32 theXvalue );

    //Returns the Y value for RS layer STM-1 signal.
    inline uint32 GetYvalueStm1() const;

    //Returns the Y value for RS layer STM-4 signal.
    inline uint32 GetYvalueStm4() const;

    //Returns the Y value for RS layer STM-16 signal.
    inline uint32 GetYvalueStm16() const;

    //Returns the Y value for RS layer STM-64 signal.
    inline uint32 GetYvalueStm64() const;

    //Returns the Y value for RS layer STM-256 signal.
    inline uint32 GetYvalueStm256() const;

    //Sets the Y value for RS layer STM-1 signal.
    inline void SetYvalueStm1( uint32 theYvalue );

    //Sets the Y value for RS layer STM-4 signal.
    inline void SetYvalueStm4( uint32 theYvalue );

    //Sets the Y value for RS layer STM-16 signal.
    inline void SetYvalueStm16( uint32 theYvalue );

    //Sets the Y value for RS layer STM-64 signal.
    inline void SetYvalueStm64( uint32 theYvalue );

    //Sets the Y value for RS layer STM-256 signal.
    inline void SetYvalueStm256( uint32 theYvalue );

    //Returns the Y value for MS layer (near-end and far-end) STM-1 signal.
    inline uint32 GetYvalueStm1Ms() const;

    //Returns the Y value for MS layer (near-end and far-end) STM-4 signal.
    inline uint32 GetYvalueStm4Ms() const;

    //Returns the Y value for MS layer (near-end and far-end) STM-16 signal.
    inline uint32 GetYvalueStm16Ms() const;

    //Returns the Y value for MS layer (near-end and far-end) STM-64 signal.
    inline uint32 GetYvalueStm64Ms() const;

    //Returns the Y value for MS layer (near-end and far-end) STM-256 signal.
    inline uint32 GetYvalueStm256Ms() const;

    //Sets the Y value for MS layer (near-end and far-end) STM-1 signal.
    inline void SetYvalueStm1Ms( uint32 theYvalue );

    //Sets the Y value for MS layer (near-end and far-end) STM-4 signal.
    inline void SetYvalueStm4Ms( uint32 theYvalue );

    //Sets the Y value for MS layer (near-end and far-end) STM-16 signal.
    inline void SetYvalueStm16Ms( uint32 theYvalue );

    //Sets the Y value for MS layer (near-end and far-end) STM-64 signal.
    inline void SetYvalueStm64Ms( uint32 theYvalue );

    //Sets the Y value for MS layer (near-end and far-end) STM-256 signal.
    inline void SetYvalueStm256Ms( uint32 theYvalue );
    
    //Returns the Y value for HOP layer (near-end and far-end) VC-3 signal.
    inline uint32 GetYvalueVc3() const;

    //Returns the Y value for HOP layer (near-end and far-end) VC-4 signal.
    inline uint32 GetYvalueVc4() const;

    //Returns the Y value for HOP layer (near-end and far-end) VC-4-4c signal.
    inline uint32 GetYvalueVc4_4c() const;

    //Returns the Y value for HOP layer (near-end and far-end) VC-4-16c signal.
    inline uint32 GetYvalueVc4_16c() const;

    //Returns the Y value for HOP layer (near-end and far-end) VC-4-64c signal.
    inline uint32 GetYvalueVc4_64c() const;

    //Sets the Y value for HOP layer (near-end and far-end) VC-3 signal.
    inline void SetYvalueVc3( uint32 theYvalue );

    //Sets the Y value for HOP layer (near-end and far-end) VC-4 signal.
    inline void SetYvalueVc4( uint32 theYvalue );

    //Sets the Y value for HOP layer (near-end and far-end) VC-4-4c signal.
    inline void SetYvalueVc4_4c( uint32 theYvalue );

    //Sets the Y value for HOP layer (near-end and far-end) VC-4-16c signal.
    inline void SetYvalueVc4_16c( uint32 theYvalue );

    //Sets the Y value for HOP layer (near-end and far-end) VC-4-64c signal.
    inline void SetYvalueVc4_64c( uint32 theYvalue );

    //Returns the Y value for OTU layer OTU-1 signal.
    inline uint32 GetYvalueOtu1() const;

    //Returns the Y value for OTU layer OTU-2 signal.
    inline uint32 GetYvalueOtu2() const;

    //Returns the Y value for OTU layer OTU-3 signal.
    inline uint32 GetYvalueOtu3() const;
    
    inline uint32 GetYvalueOtu4() const;

    //Sets the Y value for OTU layer OTU-1 signal.
    inline void SetYvalueOtu1( uint32 theYvalue );

    //Sets the Y value for OTU layer OTU-2 signal.
    inline void SetYvalueOtu2( uint32 theYvalue );

    //Sets the Y value for OTU layer OTU-3 signal.
    inline void SetYvalueOtu3( uint32 theYvalue );
    
    inline void SetYvalueOtu4( uint32 theYvalue );

    //Gets the period offset.
    //##ModelId=3C9255A60105
    inline time_t GetPeriodOffset(CT_PM_Period thePeriod) const;

    //Sets the period offset.
    //##ModelId=3C9255A6012D
    inline void SetPeriodOffset(CT_PM_Period thePeriod, time_t theOffset);

protected:

    //Writes the states to the binary stream.
    //##ModelId=3C1F6F6F00DE
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
   
    //Reads the states from a binary stream.
    //##ModelId=3C1F6F6F00F1
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3C1F6F6F0105
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F6F0119
    virtual istream& ReadObject( istream& theStream );

    //The offset to adjust for the period start time.
    //##ModelId=3C9255A6015F
    time_t myPeriodOffset;

private:

    //The X value for the RS layer OC3 signal.
    //##ModelId=3C9255A60193
    uint32  myXvalueOc3;

    //The X value for the RS layer OC12 signal.
    //##ModelId=3C9255A601C4
    uint32  myXvalueOc12;

    //The X value for the  E1 signal.
    //##ModelId=3E6E4C910389
    uint32  myXvalueE1;

    //The X value for the RS layer OC48 signal.
    //##ModelId=3C9255A601E3
    uint32  myXvalueOc48;

    //The X value for the RS layer OC192 signal.
    //##ModelId=3C9255A6020B
    uint32  myXvalueOc192;

	//The X value for the RS layer OC768 signal.
    uint32  myXvalueOc768;

    //The X value for the MS layer (near-end and far-end) OC3 signal.
    uint32  myXvalueOc3Ms;

    //The X value for the MS layer (near-end and far-end) OC12 signal.
    uint32  myXvalueOc12Ms;

    //The X value for the MS layer (near-end and far-end) OC48 signal.
    uint32  myXvalueOc48Ms;

    //The X value for the MS layer (near-end and far-end) OC192 signal.
    uint32  myXvalueOc192Ms;

    //The X value for the MS layer (near-end and far-end) OC768 signal.
    uint32  myXvalueOc768Ms;

     //The X value for the HOP layer (near-end and far-end) STS-1 termination size.
    uint32  myXvalueSts1;

    //The X value for the HOP layer (near-end and far-end) STS-3c terminztion size.
    uint32  myXvalueSts3c;

    //The X value for the HOP layer (near-end and far-end) STS-12c termination size.
    uint32  myXvalueSts12c;

    //The X value for the HOP layer (near-end and far-end) STS-48c termination size.
    uint32  myXvalueSts48c;

    uint32  myXvalueSts192c;


    //The X value for the OTU/ODU layer 0.
    uint32  myXvalueOtuOduLayer0;

    //The X value for the OTU/ODU layer 1.
    //##ModelId=3C9255A60233
    uint32  myXvalueOtuOduLayer1;

    //The X value for the OTU/ODU layer 2.
    //##ModelId=3C9255A6025A
    uint32  myXvalueOtuOduLayer2;

    //The X value for the OTU/ODU layer 2e.
    //##ModelId=3C9255A6025A
    uint32  myXvalueOtuOduLayer2e;

    //The X value for the OTU/ODU layer 3.
    uint32  myXvalueOtuOduLayer3;

    //The X value for the OTU/ODU layer 3e2.
    uint32  myXvalueOtuOduLayer3e2;

    uint32  myXvalueOtuOduLayer4;

    //The X value for the OTU/ODU layer ODU Flex.
    uint32  myXvalueOtuOduLayerF;

    //The X value for the OTU/ODUT layer 0.
    uint32  myXvalueOtuOduLayer0T;

    //The X value for the OTU/ODUT layer 1.
    //##ModelId=3C9255A60233
    uint32  myXvalueOtuOduLayer1T;

    //The X value for the OTU/ODUT layer 2.
    //##ModelId=3C9255A6025A
    uint32  myXvalueOtuOduLayer2T;

    //The X value for the OTU/ODUT layer 2eT.
    uint32  myXvalueOtuOduLayer2eT;
    
    //The X value for the OTU/ODUT layer 3.
    uint32  myXvalueOtuOduLayer3T;

    uint32  myXvalueOtuOduLayer4T;

    //The Y value for the RS layer STM-1 signal.
    uint32  myYvalueStm1;

    //The Y value for the RS layer STM-4 signal.
    uint32  myYvalueStm4;

    //The Y value for the RS layer STM-16 signal.
    uint32  myYvalueStm16;

    //The Y value for the RS layer STM-64 signal.
    uint32  myYvalueStm64;

    //The Y value for the RS layer STM-256 signal.
    uint32  myYvalueStm256;

    //The Y value for the MS layer (near-end and far-end) STM-1 signal.
    uint32  myYvalueStm1Ms;

    //The Y value for the MS layer (near-end and far-end) STM-4 signal.
    uint32  myYvalueStm4Ms;

    //The Y value for the MS layer (near-end and far-end) STM-16 signal.
    uint32  myYvalueStm16Ms;

    //The Y value for the MS layer (near-end and far-end) STM-64 signal.
    uint32  myYvalueStm64Ms;

    //The Y value for the MS layer (near-end and far-end) STM-256 signal.
    uint32  myYvalueStm256Ms;

    //The Y value for the HOP layer (near-end and far-end) VC-3 termination size.
    uint32  myYvalueVc3;

    //The Y value for the HOP layer (near-end and far-end) VC-4 termination size.
    uint32  myYvalueVc4;

    //The Y value for the HOP layer (near-end and far-end) VC-4-4c termination size.
    uint32  myYvalueVc4_4c;

    //The Y value for the HOP layer (near-end and far-end) VC-4-16c termination size.
    uint32  myYvalueVc4_16c;

    //The Y value for the HOP layer (near-end and far-end) VC-4-64c te
    uint32  myYvalueVc4_64c;

    //The Y value for the OTU layer OTU-1 signal.
    uint32  myYvalueOtu1;

    //The Y value for the OTU layer OTU-2 signal.
    uint32  myYvalueOtu2;

    //The Y value for the OTU layer OTU-3 signal.
    uint32  myYvalueOtu3;

    uint32  myYvalueOtu4;

};

//-----------------------------------------------------------------
//##ModelId=3C9255A503CB
inline uint32 PM_BbGeneralCfg::GetXvalueOc3() const { return myXvalueOc3; }

//-----------------------------------------------------------------
//##ModelId=3C9255A503DF
inline uint32 PM_BbGeneralCfg::GetXvalueOc12() const { return myXvalueOc12; }

//-----------------------------------------------------------------
//##ModelId=3E6E4C9102F2
inline uint32 PM_BbGeneralCfg::GetXvalueE1() const { return myXvalueE1; }


//-----------------------------------------------------------------
//##ModelId=3C9255A60015
inline uint32 PM_BbGeneralCfg::GetXvalueOc48() const { return myXvalueOc48; }

//-----------------------------------------------------------------
//##ModelId=3C9255A6001F
inline uint32 PM_BbGeneralCfg::GetXvalueOc192() const { return myXvalueOc192; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOc768() const { return myXvalueOc768; }

//-----------------------------------------------------------------
//##ModelId=3C9255A60033
inline void PM_BbGeneralCfg::SetXvalueOc3(uint32 theXvalue ) { myXvalueOc3 = theXvalue; }

//-----------------------------------------------------------------
//##ModelId=3E6E4C910310
inline void PM_BbGeneralCfg::SetXvalueE1(uint32 theXvalue ) { myXvalueE1 = theXvalue; }

//-----------------------------------------------------------------
//##ModelId=3C9255A6005B
inline void PM_BbGeneralCfg::SetXvalueOc12(uint32 theXvalue ) { myXvalueOc12 = theXvalue; }

//-----------------------------------------------------------------
//##ModelId=3C9255A6006F
inline void PM_BbGeneralCfg::SetXvalueOc48(uint32 theXvalue ) { myXvalueOc48 = theXvalue; }

//-----------------------------------------------------------------
//##ModelId=3C9255A6008D
inline void PM_BbGeneralCfg::SetXvalueOc192(uint32 theXvalue ) { myXvalueOc192 = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOc768(uint32 theXvalue ) { myXvalueOc768 = theXvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOc3Ms() const { return myXvalueOc3Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOc12Ms() const { return myXvalueOc12Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOc48Ms() const { return myXvalueOc48Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOc192Ms() const { return myXvalueOc192Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOc768Ms() const { return myXvalueOc768Ms; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOc3Ms(uint32 theXvalue ) { myXvalueOc3Ms = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOc12Ms(uint32 theXvalue ) { myXvalueOc12Ms = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOc48Ms(uint32 theXvalue ) { myXvalueOc48Ms = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOc192Ms(uint32 theXvalue ) { myXvalueOc192Ms = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOc768Ms(uint32 theXvalue ) { myXvalueOc768Ms = theXvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueSts1() const { return myXvalueSts1; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueSts3c() const { return myXvalueSts3c; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueSts12c() const { return myXvalueSts12c; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueSts48c() const { return myXvalueSts48c; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueSts192c() const { return myXvalueSts192c; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueSts1(uint32 theXvalue ) { myXvalueSts1 = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueSts3c(uint32 theXvalue ) { myXvalueSts3c = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueSts12c(uint32 theXvalue ) { myXvalueSts12c = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueSts48c(uint32 theXvalue ) { myXvalueSts48c = theXvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueSts192c(uint32 theXvalue ) { myXvalueSts192c = theXvalue; }


//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer0() const { return myXvalueOtuOduLayer0; }

//##ModelId=3C9255A600AB
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer1() const { return myXvalueOtuOduLayer1; }

//-----------------------------------------------------------------
//##ModelId=3C9255A600B5
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer2() const { return myXvalueOtuOduLayer2; }

inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer2e() const { return myXvalueOtuOduLayer2e; }

//##ModelId=3C9255A600AB
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer3() const { return myXvalueOtuOduLayer3; }

inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer3e2() const { return myXvalueOtuOduLayer3e2; }

inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer4() const { return myXvalueOtuOduLayer4; }

inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayerF() const { return myXvalueOtuOduLayerF; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer0(uint32 theXvalue ) { myXvalueOtuOduLayer0 = theXvalue; }

//##ModelId=3C9255A600D3
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer1(uint32 theXvalue ) { myXvalueOtuOduLayer1 = theXvalue; }

//-----------------------------------------------------------------
//##ModelId=3C9255A600F1
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer2(uint32 theXvalue ) { myXvalueOtuOduLayer2 = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer2e(uint32 theXvalue ) { myXvalueOtuOduLayer2e = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer3(uint32 theXvalue ) { myXvalueOtuOduLayer3 = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer3e2(uint32 theXvalue ) { myXvalueOtuOduLayer3e2 = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer4(uint32 theXvalue ) { myXvalueOtuOduLayer4 = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayerF(uint32 theXvalue ) { myXvalueOtuOduLayerF = theXvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer0T() const { return myXvalueOtuOduLayer0T; }

//##ModelId=3C9255A600AB
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer1T() const { return myXvalueOtuOduLayer1T; }

//-----------------------------------------------------------------
//##ModelId=3C9255A600B5
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer2T() const { return myXvalueOtuOduLayer2T; }

//##ModelId=3C9255A600AB
inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer3T() const { return myXvalueOtuOduLayer3T; }

inline uint32 PM_BbGeneralCfg::GetXvalueOtuOduLayer4T() const { return myXvalueOtuOduLayer4T; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer0T(uint32 theXvalue ) { myXvalueOtuOduLayer0T = theXvalue; }

//##ModelId=3C9255A600D3
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer1T(uint32 theXvalue ) { myXvalueOtuOduLayer1T = theXvalue; }

//-----------------------------------------------------------------
//##ModelId=3C9255A600F1
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer2T(uint32 theXvalue ) { myXvalueOtuOduLayer2T = theXvalue; }
inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer2eT(uint32 theXvalue ) { myXvalueOtuOduLayer2eT = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer3T(uint32 theXvalue ) { myXvalueOtuOduLayer3T = theXvalue; }

inline void PM_BbGeneralCfg::SetXvalueOtuOduLayer4T(uint32 theXvalue ) { myXvalueOtuOduLayer4T = theXvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm1() const { return myYvalueStm1; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm4() const { return myYvalueStm4; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm16() const { return myYvalueStm16; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm64() const { return myYvalueStm64; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm256() const { return myYvalueStm256; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm1(uint32 theYvalue ) { myYvalueStm1 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm4(uint32 theYvalue ) { myYvalueStm4 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm16(uint32 theYvalue ) { myYvalueStm16 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm64(uint32 theYvalue ) { myYvalueStm64 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm256(uint32 theYvalue ) { myYvalueStm256 = theYvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm1Ms() const { return myYvalueStm1Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm4Ms() const { return myYvalueStm4Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm16Ms() const { return myYvalueStm16Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm64Ms() const { return myYvalueStm64Ms; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueStm256Ms() const { return myYvalueStm256Ms; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm1Ms(uint32 theYvalue ) { myYvalueStm1Ms = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm4Ms(uint32 theYvalue ) { myYvalueStm4Ms = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm16Ms(uint32 theYvalue ) { myYvalueStm16Ms = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm64Ms(uint32 theYvalue ) { myYvalueStm64Ms = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueStm256Ms(uint32 theYvalue ) { myYvalueStm256Ms = theYvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueVc3() const { return myYvalueVc3; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueVc4() const { return myYvalueVc4; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueVc4_4c() const { return myYvalueVc4_4c; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueVc4_16c() const { return myYvalueVc4_16c; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueVc4_64c() const { return myYvalueVc4_64c; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueVc3(uint32 theYvalue ) { myYvalueVc3 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueVc4(uint32 theYvalue ) { myYvalueVc4 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueVc4_4c(uint32 theYvalue ) { myYvalueVc4_4c = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueVc4_16c(uint32 theYvalue ) { myYvalueVc4_16c = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueVc4_64c(uint32 theYvalue ) { myYvalueVc4_64c = theYvalue; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueOtu1() const { return myYvalueOtu1; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueOtu2() const { return myYvalueOtu2; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueOtu3() const { return myYvalueOtu3; }

//-----------------------------------------------------------------
inline uint32 PM_BbGeneralCfg::GetYvalueOtu4() const { return myYvalueOtu4; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueOtu1(uint32 theYvalue ) { myYvalueOtu1 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueOtu2(uint32 theYvalue ) { myYvalueOtu2 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueOtu3(uint32 theYvalue ) { myYvalueOtu3 = theYvalue; }

//-----------------------------------------------------------------
inline void PM_BbGeneralCfg::SetYvalueOtu4(uint32 theYvalue ) { myYvalueOtu4 = theYvalue; }

//-----------------------------------------------------------------
//##ModelId=3C9255A60105
inline time_t PM_BbGeneralCfg::GetPeriodOffset(CT_PM_Period thePeriod) const
{
    time_t thePeriodOffset = 0;
    switch(thePeriod)
    {
    case CT_PM_PERIOD_15_MINUTES:
        thePeriodOffset = 0;
        break;
    case CT_PM_PERIOD_1_DAY:
        thePeriodOffset = myPeriodOffset;
        break;
    default:
        FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
        break;
    }
    return thePeriodOffset;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A6012D
inline void PM_BbGeneralCfg::SetPeriodOffset(CT_PM_Period thePeriod, time_t theOffset )
{
    switch(thePeriod)
    {
    case CT_PM_PERIOD_1_DAY:
        myPeriodOffset = theOffset;
        break;
    case CT_PM_PERIOD_15_MINUTES:
    default:
        FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
        break;
    }

}

#endif //PM_BBGENERALCFG
