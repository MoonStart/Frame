//Copyright(c) Tellabs Transport Group. All rights reserved


#ifndef TEL_TRACEUTILITIES
#define TEL_TRACEUTILITIES

#include "CommonTypes/CT_Telecom.h"
#include "gdef.h"


//##ModelId=3C20B0AF0009
enum TEL_TraceMsgMode
{
    //##ModelId=3C20B0AF027D
     TEL_TRACE_NOT_PROV = 0,          // Not provisionned
    //##ModelId=3C20B0AF02B9
     TEL_TRACE_LEN16    = 1,          // 16 bytes string
    //##ModelId=3C20B0AF02C3
     TEL_TRACE_LEN64    = 2,          // 64 bytes string
    //##ModelId=3C20B0AF02CD
     TEL_G709_LEN64     = 3           // 64 bytes string (G.709 format)
};

// ASCII characters range defines.
const uint8 TEL_GOOD_ASCII_LOWER_VALUE = 0x20;
const uint8 TEL_GOOD_ASCII_UPPER_VALUE = 0x7E;

// Number of user-suplied characters.
const uint8 TEL_MAX_USER_CHARS_16BYTES = 15;
const uint8 TEL_MAX_USER_CHARS_64BYTES = 62;

// Number of characters for trace messages.
const uint8 TEL_MAX_CHARS_16BYTES = 16;
const uint8 TEL_MAX_CHARS_64BYTES = 64;
const uint8 TEL_TRACE_MAX_MSG_LENGTH = 65; // Last char always = '\0'

// Frame marker in 16 bytes message.
const uint8 TEL_TRACE_16BYTES_FRAME_MARKER = 0x80;

// <CR> and <LF>
const char TEL_TRACE_MSG_CR = 0x0D;
const char TEL_TRACE_MSG_LF = 0x0A;


//This object provides all the functionnality required to
//encode, decode and validate a trace message.
//##ModelId=3C20B0AF0309
class TEL_TraceUtilities
{
public:

    //-----------------------------------------------------------------
    // Build16BytesMsg()

    //Process a valid message to generate a formatted trace
    //message. The string is generated as follow: <blockquote>
    //        - A valid message is received<br>
    //        - A CRC-7 is added in the first byte (7
    //bits)<br>
    //        - The string is padded to 16 characters using
    //ASCII NULL characters,<br>
    //        - A frame marker is added in the first byte
    //(marker = 0x80)<br><br>
    //##ModelId=3C20B0B000D0
    static void Build16BytesMsg(const char* theSrcMsg, char* theDestMsg);

    //-----------------------------------------------------------------
    // Build64BytesMsg()

    //Process a valid message to generate a formatted trace
    //message. The string is generated as follow:
    //<blockquote>
    //        - A valid message is received<br>
    //        - The string is padded to 62 characters using
    //ASCII NULL characters,<br>
    //        - <CR> and <LF> characters are appended to
    //message<br><br>
    //##ModelId=3C20B0B000DC
    static void Build64BytesMsg(const char* theSrcMsg, char* theDestMsg);

    //-----------------------------------------------------------------
    // Validate16BytesMsg()

    //Validate a 16 bytes trace message.  If properly
    //validated, this method return a 'true', if not, it
    //returns false. <blockquote>The string is validated as
    //follow:<br>
    //        - The user enters a string of up to 15
    //characters;<br>
    //        - Characters shall be ASCII printable
    //characters (i.e, ?0?through ?E?hex));<br>
    //        - The string is padded to 15 characters; the
    //user must enter up to 15 characters.<br><br>
    //##ModelId=3C20B0B000EE
    static bool Validate16BytesMsg(const char* theMsg);

    //-----------------------------------------------------------------
    // Validate64BytesMsg()

    //Validate a 64 bytes trace message.  If properly
    //validated, this method return a 'true', if not, it
    //returns false. <blockquote>
    //        The string is validated as follow:<br>
    //        - The user enters a string of up to 62
    //characters;<br>
    //        - Characters shall be ASCII printable
    //characters (i.e, ?0? through ?E?hex));<br> <br>
    //##ModelId=3C20B0B000F8
    static bool Validate64BytesMsg(const char* theMsg);

    //-----------------------------------------------------------------
    // ComputeCrc7()

    //Calculate CRC-7 on a given buffer.
    //##ModelId=3C20B0B00103
    static uint8 ComputeCrc7(const char* theBuffer, uint32 theBufSize);

    //------------------------------------------------------------------
    // SetMsg()

    //Configure expected or 'to transmit' trace message.
    //Message passed in parameter is first validated.  If
    //invalid, message is discarded, no internal attributes
    //are changed, and a false is returned.  If valid,
    //internal ttributes are configured.
    //##ModelId=3C20B0B0010E
    static bool SetMsg(TEL_TraceMsgMode theTraceMsgMode,
                const char* theSrcMsg, char* theDestMsg);

    //------------------------------------------------------------------
    // GetReceivedMsg()

    //Retrieve FILTERED received trace message.  The message
    //is validated againt the current trace setting (16 or 64
    //bytes mode). If any invalid character is found, CRC-7
    //is incorrect a NULL string is returned.
    //##ModelId=3C20B0B00121
    static bool GetReceivedMsg(TEL_TraceMsgMode theMode,const char* theSrcMsg, char* theDestMsg);


    //Pad the 16 bytes message with white spaces.
    //##ModelId=3C20B0B00134
    static void Pad16BytesMsg(const char* theSrcMsg, char* theDestMsg);

    //Pad the 64 bytes message with white spaces.
    //##ModelId=3C20B0B0013F
    static void Pad64BytesMsg(const char* theSrcMsg, char* theDestMsg);

};

#endif /* TEL_TRACEUTILITIES */

