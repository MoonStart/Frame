/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM Configuration parameters class. Keep the congig of PM.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>

#include <PM/PM_Def.h>
#include <PM/PM_BbGeneralCfg.h>


//-----------------------------------------------------------------
//##ModelId=3C1F6F6F0083
PM_BbGeneralCfg::PM_BbGeneralCfg(uint32 dummy )
{
    myPeriodOffset = 0;

    myXvalueOc3 = 0;
    myXvalueOc12 = 0;
    myXvalueE1 = 0;
    myXvalueOc48 = 0;
    myXvalueOc192 = 0;
    myXvalueOc768 = 0;
    myXvalueOc3Ms = 0;
    myXvalueOc12Ms = 0;
    myXvalueOc48Ms = 0;
    myXvalueOc192Ms = 0;
    myXvalueOc768Ms = 0;
    myXvalueSts1 = 0;
    myXvalueSts3c = 0;
    myXvalueSts12c = 0;
    myXvalueSts48c = 0;
    myXvalueSts192c = 0;
    myYvalueStm1 = 0;
    myYvalueStm4 = 0;
    myYvalueStm16 = 0;
    myYvalueStm64 = 0;
    myYvalueStm256 = 0;
    myYvalueStm1Ms = 0;
    myYvalueStm4Ms = 0;
    myYvalueStm16Ms = 0;
    myYvalueStm64Ms = 0;
    myYvalueStm256Ms = 0;
    myYvalueVc3 = 0;
    myYvalueVc4 = 0;
    myYvalueVc4_4c = 0;
    myYvalueVc4_16c = 0;
    myYvalueVc4_64c = 0;
    myXvalueOtuOduLayer0 = 0;
    myXvalueOtuOduLayer1 = 0;
    myXvalueOtuOduLayer2 = 0;
    myXvalueOtuOduLayer2e = 0;
    myXvalueOtuOduLayer3 = 0;
    myXvalueOtuOduLayer3e2 = 0;
    myXvalueOtuOduLayer4 = 0;
    myXvalueOtuOduLayerF = 0;
    myXvalueOtuOduLayer0T = 0;
    myXvalueOtuOduLayer1T = 0;
    myXvalueOtuOduLayer2T = 0;
    myXvalueOtuOduLayer3T = 0;
    myXvalueOtuOduLayer4T = 0;
    myYvalueOtu1 = 0;
    myYvalueOtu2 = 0;
    myYvalueOtu3 = 0;
    myYvalueOtu4 = 0;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6F008E
PM_BbGeneralCfg::~PM_BbGeneralCfg()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6F00DE
FC_Stream& PM_BbGeneralCfg::WriteObjectBinary( FC_Stream& theStream )
{
    unsigned long myDbPeriodOffset = (unsigned long)myPeriodOffset;
    theStream << myXvalueOc3
              << myXvalueOc12
              << myXvalueE1
              << myXvalueOc48
              << myXvalueOc192
              << myXvalueOc768
              << myXvalueOc3Ms
              << myXvalueOc12Ms
              << myXvalueOc48Ms
              << myXvalueOc192Ms
              << myXvalueOc768Ms
              << myXvalueSts1
              << myXvalueSts3c
              << myXvalueSts12c
              << myXvalueSts48c
              << myXvalueSts192c
              << myYvalueStm1
              << myYvalueStm4
              << myYvalueStm16
              << myYvalueStm64
              << myYvalueStm256
              << myYvalueStm1Ms
              << myYvalueStm4Ms
              << myYvalueStm16Ms
              << myYvalueStm64Ms
              << myYvalueStm256Ms
              << myYvalueVc3
              << myYvalueVc4
              << myYvalueVc4_4c
              << myYvalueVc4_16c
              << myYvalueVc4_64c
              << myXvalueOtuOduLayer0
              << myXvalueOtuOduLayer1
              << myXvalueOtuOduLayer2
              << myXvalueOtuOduLayer2e
              << myXvalueOtuOduLayer3
              << myXvalueOtuOduLayer3e2
              << myXvalueOtuOduLayer4
              << myXvalueOtuOduLayerF
              << myXvalueOtuOduLayer0T
              << myXvalueOtuOduLayer1T
              << myXvalueOtuOduLayer2T
              << myXvalueOtuOduLayer3T
              << myXvalueOtuOduLayer4T
              << myYvalueOtu1
              << myYvalueOtu2
              << myYvalueOtu3
              << myYvalueOtu4
              << myDbPeriodOffset;

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6F00F1
FC_Stream& PM_BbGeneralCfg::ReadObjectBinary( FC_Stream& theStream )
{
    unsigned long myDbPeriodOffset = 0;

    theStream >> myXvalueOc3
              >> myXvalueOc12
              >> myXvalueE1
              >> myXvalueOc48
              >> myXvalueOc192
              >> myXvalueOc768
              >> myXvalueOc3Ms
              >> myXvalueOc12Ms
              >> myXvalueOc48Ms
              >> myXvalueOc192Ms
              >> myXvalueOc768Ms
              >> myXvalueSts1
              >> myXvalueSts3c
              >> myXvalueSts12c
              >> myXvalueSts48c
              >> myXvalueSts192c
              >> myYvalueStm1
              >> myYvalueStm4
              >> myYvalueStm16
              >> myYvalueStm64
              >> myYvalueStm256
              >> myYvalueStm1Ms
              >> myYvalueStm4Ms
              >> myYvalueStm16Ms
              >> myYvalueStm64Ms
              >> myYvalueStm256Ms
              >> myYvalueVc3
              >> myYvalueVc4
              >> myYvalueVc4_4c
              >> myYvalueVc4_16c
              >> myYvalueVc4_64c
              >> myXvalueOtuOduLayer0
              >> myXvalueOtuOduLayer1
              >> myXvalueOtuOduLayer2
              >> myXvalueOtuOduLayer2e
              >> myXvalueOtuOduLayer3
              >> myXvalueOtuOduLayer3e2
              >> myXvalueOtuOduLayer4
              >> myXvalueOtuOduLayerF
              >> myXvalueOtuOduLayer0T
              >> myXvalueOtuOduLayer1T
              >> myXvalueOtuOduLayer2T
              >> myXvalueOtuOduLayer3T
              >> myXvalueOtuOduLayer4T
              >> myYvalueOtu1
              >> myYvalueOtu2
              >> myYvalueOtu3
              >> myYvalueOtu4
              >> myDbPeriodOffset;

    myPeriodOffset = (time_t)myDbPeriodOffset;

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6F0105
ostream& PM_BbGeneralCfg::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myXvalueOc3)
              << FC_InsertVar(myXvalueOc12)
              << FC_InsertVar(myXvalueE1)
              << FC_InsertVar(myXvalueOc48)
              << FC_InsertVar(myXvalueOc192)
              << FC_InsertVar(myXvalueOc768)
              << FC_InsertVar(myXvalueOc3Ms)
              << FC_InsertVar(myXvalueOc12Ms)
              << FC_InsertVar(myXvalueOc48Ms)
              << FC_InsertVar(myXvalueOc192Ms)
              << FC_InsertVar(myXvalueOc768Ms)
              << FC_InsertVar(myXvalueSts1)
              << FC_InsertVar(myXvalueSts3c)
              << FC_InsertVar(myXvalueSts12c)
              << FC_InsertVar(myXvalueSts48c)
              << FC_InsertVar(myXvalueSts192c)
              << FC_InsertVar(myYvalueStm1)
              << FC_InsertVar(myYvalueStm4)
              << FC_InsertVar(myYvalueStm16)
              << FC_InsertVar(myYvalueStm64)
              << FC_InsertVar(myYvalueStm256)
              << FC_InsertVar(myYvalueStm1Ms)
              << FC_InsertVar(myYvalueStm4Ms)
              << FC_InsertVar(myYvalueStm16Ms)
              << FC_InsertVar(myYvalueStm64Ms)
              << FC_InsertVar(myYvalueStm256Ms)
              << FC_InsertVar(myYvalueVc3)
              << FC_InsertVar(myYvalueVc4)
              << FC_InsertVar(myYvalueVc4_4c)
              << FC_InsertVar(myYvalueVc4_16c)
              << FC_InsertVar(myYvalueVc4_64c)
              << FC_InsertVar(myXvalueOtuOduLayer0)
              << FC_InsertVar(myXvalueOtuOduLayer1)
              << FC_InsertVar(myXvalueOtuOduLayer2)
              << FC_InsertVar(myXvalueOtuOduLayer2e)
              << FC_InsertVar(myXvalueOtuOduLayer3)
              << FC_InsertVar(myXvalueOtuOduLayer3e2)
              << FC_InsertVar(myXvalueOtuOduLayer4)
              << FC_InsertVar(myXvalueOtuOduLayerF)
              << FC_InsertVar(myXvalueOtuOduLayer0T)
              << FC_InsertVar(myXvalueOtuOduLayer1T)
              << FC_InsertVar(myXvalueOtuOduLayer2T)
              << FC_InsertVar(myXvalueOtuOduLayer3T)
              << FC_InsertVar(myXvalueOtuOduLayer4T)
              << FC_InsertVar(myYvalueOtu1)
              << FC_InsertVar(myYvalueOtu2)
              << FC_InsertVar(myYvalueOtu3)
              << FC_InsertVar(myYvalueOtu4)
              << FC_InsertVar(myPeriodOffset);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6F0119
istream& PM_BbGeneralCfg::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myXvalueOc3)
              >> FC_ExtractVar(myXvalueOc12)
              >> FC_ExtractVar(myXvalueE1)
              >> FC_ExtractVar(myXvalueOc48)
              >> FC_ExtractVar(myXvalueOc192)
              >> FC_ExtractVar(myXvalueOc768)
              >> FC_ExtractVar(myXvalueOc3Ms)
              >> FC_ExtractVar(myXvalueOc12Ms)
              >> FC_ExtractVar(myXvalueOc48Ms)
              >> FC_ExtractVar(myXvalueOc192Ms)
              >> FC_ExtractVar(myXvalueOc768Ms)
              >> FC_ExtractVar(myXvalueSts1)
              >> FC_ExtractVar(myXvalueSts3c)
              >> FC_ExtractVar(myXvalueSts12c)
              >> FC_ExtractVar(myXvalueSts48c)
              >> FC_ExtractVar(myXvalueSts192c)
              >> FC_ExtractVar(myYvalueStm1)
              >> FC_ExtractVar(myYvalueStm4)
              >> FC_ExtractVar(myYvalueStm16)
              >> FC_ExtractVar(myYvalueStm64)
              >> FC_ExtractVar(myYvalueStm256)
              >> FC_ExtractVar(myYvalueStm1Ms)
              >> FC_ExtractVar(myYvalueStm4Ms)
              >> FC_ExtractVar(myYvalueStm16Ms)
              >> FC_ExtractVar(myYvalueStm64Ms)
              >> FC_ExtractVar(myYvalueStm256Ms)
              >> FC_ExtractVar(myYvalueVc3)
              >> FC_ExtractVar(myYvalueVc4)
              >> FC_ExtractVar(myYvalueVc4_4c)
              >> FC_ExtractVar(myYvalueVc4_16c)
              >> FC_ExtractVar(myYvalueVc4_64c)
              >> FC_ExtractVar(myXvalueOtuOduLayer0)
              >> FC_ExtractVar(myXvalueOtuOduLayer1)
              >> FC_ExtractVar(myXvalueOtuOduLayer2)
              >> FC_ExtractVar(myXvalueOtuOduLayer2e)
              >> FC_ExtractVar(myXvalueOtuOduLayer3)
              >> FC_ExtractVar(myXvalueOtuOduLayer3e2)
              >> FC_ExtractVar(myXvalueOtuOduLayer4)
              >> FC_ExtractVar(myXvalueOtuOduLayerF)
              >> FC_ExtractVar(myXvalueOtuOduLayer0T)
              >> FC_ExtractVar(myXvalueOtuOduLayer1T)
              >> FC_ExtractVar(myXvalueOtuOduLayer2T)
              >> FC_ExtractVar(myXvalueOtuOduLayer3T)
              >> FC_ExtractVar(myXvalueOtuOduLayer4T)
              >> FC_ExtractVar(myYvalueOtu1)
              >> FC_ExtractVar(myYvalueOtu2)
              >> FC_ExtractVar(myYvalueOtu3)
              >> FC_ExtractVar(myYvalueOtu4)
              >> FC_ExtractVar(myPeriodOffset);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F6F0097
void PM_BbGeneralCfg::Reset()
{
    myXvalueOc3 = PM_XVAL_SES_RS_OC3;
    myXvalueOc12 = PM_XVAL_SES_RS_OC12;
    myXvalueE1 = PM_XVAL_SES_RS_E1;
    myXvalueOc48 = PM_XVAL_SES_RS_OC48;
    myXvalueOc192 = PM_XVAL_SES_RS_OC192;
    myXvalueOc768 = PM_XVAL_SES_RS_OC768;

    myXvalueOc3Ms = PM_XVAL_SES_MS_OC3;
    myXvalueOc12Ms = PM_XVAL_SES_MS_OC12;
    myXvalueOc48Ms = PM_XVAL_SES_MS_OC48;
    myXvalueOc192Ms = PM_XVAL_SES_MS_OC192;
    myXvalueOc768Ms = PM_XVAL_SES_MS_OC768;

    myXvalueSts1 = PM_XVAL_SES_HOP_STS1;
    myXvalueSts3c = PM_XVAL_SES_HOP_STS3C;
    myXvalueSts12c = PM_XVAL_SES_HOP_STS12C;
    myXvalueSts48c = PM_XVAL_SES_HOP_STS48C;
    myXvalueSts192c = PM_XVAL_SES_HOP_STS192C;
    
    myYvalueStm1 = PM_YVAL_SES_RS_STM1;
    myYvalueStm4 = PM_YVAL_SES_RS_STM4;
    myYvalueStm16 = PM_YVAL_SES_RS_STM16;
    myYvalueStm64 = PM_YVAL_SES_RS_STM64;
    myYvalueStm256 = PM_YVAL_SES_RS_STM256;

    myYvalueStm1Ms = PM_YVAL_SES_MS_STM1;
    myYvalueStm4Ms = PM_YVAL_SES_MS_STM4;
    myYvalueStm16Ms = PM_YVAL_SES_MS_STM16;
    myYvalueStm64Ms = PM_YVAL_SES_MS_STM64;
    myYvalueStm256Ms = PM_YVAL_SES_MS_STM256;

    myYvalueVc3 = PM_YVAL_SES_HOP_VC3;
    myYvalueVc4 = PM_YVAL_SES_HOP_VC4;
    myYvalueVc4_4c = PM_YVAL_SES_HOP_VC4_4C;
    myYvalueVc4_16c = PM_YVAL_SES_HOP_VC4_16C;
    myYvalueVc4_64c = PM_YVAL_SES_HOP_VC4_64C;

    myXvalueOtuOduLayer0 = PM_XVAL_SES_OTU_ODU_0;
    myXvalueOtuOduLayer1 = PM_XVAL_SES_OTU_ODU_1;
    myXvalueOtuOduLayer2 = PM_XVAL_SES_OTU_ODU_2;
    myXvalueOtuOduLayer2e = PM_XVAL_SES_OTU_ODU_2e;
    myXvalueOtuOduLayer3 = PM_XVAL_SES_OTU_ODU_3;
    myXvalueOtuOduLayer3e2 = PM_XVAL_SES_OTU_ODU_3e2;
    myXvalueOtuOduLayer4 = PM_XVAL_SES_OTU_ODU_4;	
    myXvalueOtuOduLayerF = PM_XVAL_SES_OTU_ODU_F;

    myXvalueOtuOduLayer0T = PM_XVAL_SES_OTU_ODU_0T;
    myXvalueOtuOduLayer1T = PM_XVAL_SES_OTU_ODU_1T;
    myXvalueOtuOduLayer2T = PM_XVAL_SES_OTU_ODU_2T;
    myXvalueOtuOduLayer3T = PM_XVAL_SES_OTU_ODU_3T;
    myXvalueOtuOduLayer4T = PM_XVAL_SES_OTU_ODU_4T;

    myYvalueOtu1 = PM_YVAL_SES_OTU_OTU1;
    myYvalueOtu2 = PM_YVAL_SES_OTU_OTU2;
    myYvalueOtu3 = PM_YVAL_SES_OTU_OTU3;
    myYvalueOtu4 = PM_YVAL_SES_OTU_OTU4;

    myPeriodOffset = 0;

}
