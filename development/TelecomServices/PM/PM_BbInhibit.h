/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM inhibition class. Keeps the inhibition state of PM.
--------------------------------------------------------------------------*/
#ifndef PM_BBINHIBIT_H
#define PM_BBINHIBIT_H

#include <CommonTypes/CT_PM_Definition.h>
#include <ctime>
#include <PM/PM_Def.h>
#include <PM/PM_BbObject.h>


using namespace std;


//This class keeps the PM Signal Control, which corresponds 
//to accumulation and TCA inhibition of entity layer.
//##ModelId=3C1F6F7502F8
class PM_BbInhibit : public PM_BbObject
{

public:

    //Class default constructor.
    //##ModelId=3C1F6F760141
    PM_BbInhibit (uint32 dummy1, uint32 dummy2);

    //Class default destructor.
    //##ModelId=3C1F6F76015F
    virtual ~PM_BbInhibit();

    //Reset all PM values to zero.
    //##ModelId=3C1F6F760161
    virtual void Reset();

    //Gets inhibition control. TCA and accumulation.
    //##ModelId=3C1F6F76016A
    bool GetInhibit(CT_PM_BbControlWord theControlWord) const;

    //Not supported by the base class.
    //##ModelId=3C9255C2000B
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;

    //Not supported by the base class.
    //##ModelId=3E6E4CAB0259
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //Sets inhibition control. TCA and accumulation.
    //##ModelId=3C1F6F760175
    void SetInhibit(CT_PM_BbControlWord theControlWord, bool theBoolVal);

    //Not supported by the base class.
    //##ModelId=3C9255C20033
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Not supported by the base class.
    //##ModelId=3E6E4CAB02B3
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Stores the values to the binary stream.
    //##ModelId=3C1F6F7601BA
    FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F7601CD
    FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3C1F6F7601E1
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F7601F5
    virtual istream& ReadObject( istream& theStream );

    bool SetControlWord(CT_PM_BbControlWord theWord);

    inline CT_PM_BbControlWord GetControlWord() { return myControlWord; }

protected:

    //Bit map to control the inhibition of registers 
    //accumulation of any signal. Here is the definition of 
    //all bits:
    //##ModelId=3FA161040386
    CT_PM_BbControlWord    myControlWord;

private:

    //This method is used to change the state of any control 
    //bit.
    //##ModelId=3C1F6F76024F
    inline void ChangeControlBit(bool theBoolVal, CT_PM_BbControlWord theMask);

    //This method is used to Get the value of any control 
    //bit. It returns true if the bit is set and false is the 
    //bit is clear.
    //##ModelId=3C1F6F76026E
    inline bool GetControlBit(CT_PM_BbControlWord theMask) const;

    //This method is used to set (to true) the state of any 
    //control bit.
    //##ModelId=3C1F6F760282
    inline void SetControlBit(CT_PM_BbControlWord theMask);

    //This method is used to reset (set to false) the state 
    //of any control bit.
    //##ModelId=3C1F6F760295
    inline void UnSetControlBit(CT_PM_BbControlWord theMask);

};

//-----------------------------------------------------------------
//##ModelId=3C1F6F760282
inline void PM_BbInhibit::SetControlBit(CT_PM_BbControlWord theMask)
{
    myControlWord |= theMask;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F760295
inline void PM_BbInhibit::UnSetControlBit(CT_PM_BbControlWord theMask)
{
    myControlWord &= ~theMask;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F76024F
inline void PM_BbInhibit::ChangeControlBit(bool theBoolVal, CT_PM_BbControlWord theMask)
{
    // !! If bit is unset, it is inhibited. The default value is "inhibited" so that PM
    // will NOT accumulate when no configuration is set by ADMIN. Check the constructor.
    (theBoolVal) ? UnSetControlBit(theMask) : SetControlBit(theMask);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F76026E
inline bool PM_BbInhibit::GetControlBit(CT_PM_BbControlWord theMask) const
{
    return ( myControlWord & theMask ) ? true : false;

}

#endif //PM_BBINHIBIT_H

