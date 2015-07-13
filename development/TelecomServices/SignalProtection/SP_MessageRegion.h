//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_MESSAGEREGION_H
#define SP_MESSAGEREGION_H

#include <TelCommon/TEL_BbObjectBase.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Port.h>
//#include <CommonTypes/CT_Telecom.h>

extern const FC_BbKey SP_RX_MSGREGION_KEY;
extern const FC_BbKey SP_TX_MSGREGION_KEY;

//This class hold the contents of a message that can be sent or received
class SP_Message :public TEL_BbObjectBase
{
public:

    //Constructor.
    SP_Message();

    //Virtual destructor.
    virtual ~SP_Message(void);

    void SetMessage(CT_Port& theSrcAddress, CT_Port& theDstAddress, uint8 theMessage);
    void SetMessage(uint8 theMessage, uint8 theMask);
    CT_Port& GetSrcAddress();
    CT_Port& GetDstAddress();
    uint8 GetMessage();
    uint32 GetMessageRxCounter();
    void IncMessageRxCounter();

    //Serialization methods
	virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

	//Initialize data members
	void Reset();

protected:

private:

    uint8 myMessage;
    CT_Port mySrcAddress;
    CT_Port myDstAddress;
    uint32 myMessageRxCounter;
};

class SP_MessageRegion: public TEL_BbRegionBaseImp<SP_Message>
{
public:
	// Default class constructor
    SP_MessageRegion();

    // Class constructor
    SP_MessageRegion(const FC_BbKey theKey, int theSize);
	
    // Virtual class destructor
    virtual ~SP_MessageRegion();
};

#endif /* SP_MESSAGEREGION_H */
