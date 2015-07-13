//Copyright(c) Tellabs Transport Group. All rights reserved


#include "TEL_TraceUtilities.h"
#include <ErrorService/FC_Error.h>
#include <cstring>

using namespace std;



//##ModelId=3C20B0B000D0
void TEL_TraceUtilities::Build16BytesMsg(const char* theSrcMsg, char* theDestMsg)
{
    int len;
    int i;

    // Get source msg length.
    len = strlen(theSrcMsg);

    // Skip one char for CRC and frame marker.
    char* tmpPtr = theDestMsg+1;

    // Copy source message skipping first char.
    for (i=0; i < TEL_MAX_USER_CHARS_16BYTES; i++)
        *tmpPtr++ = *theSrcMsg++;
    *tmpPtr = NULL;

    // Add frame marker.
    *theDestMsg = (char)TEL_TRACE_16BYTES_FRAME_MARKER;

    // Pad message with ASCII space if nescessary
    for (i=len; i < TEL_MAX_USER_CHARS_16BYTES; i++)
        theDestMsg[i+1] = ' ';

    // Calculate CRC-7 for source message and store CRC-7.
    *theDestMsg |= ComputeCrc7(theDestMsg, TEL_MAX_CHARS_16BYTES);

}

//##ModelId=3C20B0B000DC
void TEL_TraceUtilities::Build64BytesMsg(const char* theSrcMsg, char* theDestMsg)
{
    int i;
    // Get source msg length.
    int len = strlen(theSrcMsg);


    // Copy source message.
    strncpy(theDestMsg, theSrcMsg, TEL_MAX_USER_CHARS_64BYTES);

    // Pad message with ASCII NULL if nescessary.
    for (i=len; i < TEL_MAX_USER_CHARS_64BYTES; i++)
        theDestMsg[i] = '\0';

    // Add <CR> and <LF>
    theDestMsg[TEL_MAX_USER_CHARS_64BYTES] = TEL_TRACE_MSG_CR;
    theDestMsg[TEL_MAX_USER_CHARS_64BYTES+1] = TEL_TRACE_MSG_LF;
    theDestMsg[TEL_MAX_USER_CHARS_64BYTES+2] = NULL;

}

//##ModelId=3C20B0B000EE
bool TEL_TraceUtilities::Validate16BytesMsg(const char* theMsg)
{
    if ( theMsg == NULL )
    {
        FC_THROW_ERROR( FC_InvalidArgumentError, "Buffer is invalid");
        return false;
    }

    // Verify all 15 characters for good ASCII value.
    int  noChar =0;
    while ( *theMsg != '\0' )
    {
        if ( (*theMsg < TEL_GOOD_ASCII_LOWER_VALUE) ||
             (*theMsg > TEL_GOOD_ASCII_UPPER_VALUE) )
             return false; // Bad message.

        noChar++;  // Cumulate number of chars.
        theMsg++;  // Next available chars.
    }

    // Verify that no more than 15 characters are available.
    if ( noChar > TEL_MAX_USER_CHARS_16BYTES)
        return false;   // Bad message.

    // Message is valid.
    return true;

}

//##ModelId=3C20B0B000F8
bool TEL_TraceUtilities::Validate64BytesMsg(const char* theMsg)
{
    if ( theMsg == NULL )
    {
        FC_THROW_ERROR( FC_InvalidArgumentError, "Buffer is invalid");
        return false;
    }

    // Verify all characters for good ASCII value.
    int  noChar =0;
    while ( *theMsg != '\0' )
    {
        if ( (*theMsg < TEL_GOOD_ASCII_LOWER_VALUE) ||
             (*theMsg > TEL_GOOD_ASCII_UPPER_VALUE) )
             return false; // Bad message.

        noChar++;  // Cumulate number of chars.
        theMsg++;  // Next available chars.
    }

    // Verify that message is not too long.
    if ( noChar > TEL_MAX_USER_CHARS_64BYTES)
        return false;   // Bad message.

    // Message is valid.
    return true;
}

/*
    CRC-7 algorithm
    ---------------

    Using poly X^7 + x^3 + 1  (10001001 ( W = 7  : width ).
    Using message with the following convention:  (TTI = xxxxxxx...)
                                                         1234567...
        byte 1, bit 7 is the MSB

    Let's define a shift register and poly of the form:

                        16 bits value
                  -----------------------------
                  Byte #1           Byte #0
             6  5  4  3  2  1  0   Bits
  Pop! <--  [ ][ ][ ][ ][ ][ ][ ]     <--- msg
          1  0  0  0  1  0  0  1   Poly

    The alogorithm is as follow:

        Load register with zero bits
        While (more message bits)
        {
            Shift register left by one bit, reading the next bit of the msg
                (MSB enter register first)
            If (a 1 bit popped out of the register)
                Register = Register XOR Poly
            End
        }
        The Register contains the remainder (CRC7)
*/
//##ModelId=3C20B0B00103
uint8 TEL_TraceUtilities::ComputeCrc7(const char* theBuffer, uint32 theBufSize)
{
    const uint16 POLY = 0x8900;
    const uint16 POPPED = 0x8000;

    volatile uint16 crc = 0;
    uint16 tmpByte;
    uint32 i;
    int j;


    // Verify parameters.
    FC_THROW_ERROR_IF( (theBuffer == NULL),
        FC_InvalidArgumentError, "Buffer length is zero");

    FC_THROW_ERROR_IF( (theBufSize == 0),
        FC_InvalidArgumentError, "Buffer size is invalid");

    for (i=0; i<theBufSize; i++)
    {
        // Parse entire byte.
        tmpByte = ( (uint16)theBuffer[i] & 0xFF);

        // Put byte in crc registers LSB.
        crc = crc | tmpByte;

        for (j=1; j<=8; j++)  // 8 bits.
        {
            // Shift crc by 1 bit.
            crc = crc << 1;

            if ( crc & POPPED)
                crc = crc ^ POLY;
        }
    }

    for (j=1; j<=7; j++)  // Augmented message remaining bits (7).
    {
        // Shift crc by 1 bit.
        crc = crc << 1;

        if ( crc & POPPED)
            crc = crc ^ POLY;
    }

    // Align CRC.
    crc >>=8;

    return (crc & 0x7F);

}

//##ModelId=3C20B0B0010E
bool TEL_TraceUtilities::SetMsg(TEL_TraceMsgMode theTraceMsgMode,
                                const char* theSrcMsg,
                                char* theDestMsg)
{
    // Verify trace message mode or length.
    switch (theTraceMsgMode)
    {
    case TEL_TRACE_LEN16 :
        // Validate trace message.
        if ( !Validate16BytesMsg(theSrcMsg) )
            return false;  // Msg invalid.

        // Generate full trace message.
        Build16BytesMsg(theSrcMsg, theDestMsg);
        break;

    case TEL_TRACE_LEN64 :

        // Validate trace message.
        if ( !Validate64BytesMsg(theSrcMsg) )
            return false;  // Msg invalid.

        // Generate full trace message.
        Build64BytesMsg(theSrcMsg, theDestMsg);
        break;

    case TEL_G709_LEN64 :
    default :
        FC_THROW_ERROR( FC_LogicError, "Trace msg mode invalid");
    }

    // Operation succesfull.
    return true;

}

//##ModelId=3C20B0B00121
bool TEL_TraceUtilities::GetReceivedMsg(TEL_TraceMsgMode theMode,
                                        const char* theSrcMsg,
                                        char* theDestMsg)
{
    char tmpMsg[TEL_MAX_USER_CHARS_16BYTES + 2];  // 1 char for the crc and 1 for the null.

    switch (theMode)
    {
    case TEL_TRACE_LEN16:
        // According to the trace mode or length.
        if(theSrcMsg[0] & TEL_TRACE_16BYTES_FRAME_MARKER)
        {
            // 16 bytes mode.
            // Copy trace and force 17th byte to 0,
            // the first character is the CRC7.
            tmpMsg[0] = (char)TEL_TRACE_16BYTES_FRAME_MARKER;
            memcpy(&tmpMsg[1], &theSrcMsg[1], TEL_MAX_USER_CHARS_16BYTES);
            tmpMsg[TEL_MAX_USER_CHARS_16BYTES+1] = 0;

            // Verify the string character validity and the CRC7.
            if(Validate16BytesMsg(&tmpMsg[1]) &&
               (ComputeCrc7(tmpMsg, TEL_MAX_CHARS_16BYTES) ==
                 ( ((uint8)theSrcMsg[0]) & ~TEL_TRACE_16BYTES_FRAME_MARKER) ) )
            {
                strncpy(theDestMsg, &tmpMsg[1], TEL_MAX_USER_CHARS_16BYTES+1);

                return true;
            }
        }
        break;
    case TEL_TRACE_LEN64:
        // If the 63th and 64th bytes are the cariage return and
        // the line feed, copy the string and force the 63th byte
        // to 0.
        if( (theSrcMsg[TEL_MAX_USER_CHARS_64BYTES] == TEL_TRACE_MSG_CR) &&
            (theSrcMsg[TEL_MAX_USER_CHARS_64BYTES+1] == TEL_TRACE_MSG_LF) )
        {
            strncpy(theDestMsg, theSrcMsg, TEL_MAX_USER_CHARS_64BYTES );
            theDestMsg[TEL_MAX_USER_CHARS_64BYTES] = 0;

            // Verify if the string is valide.
            if(Validate64BytesMsg(theDestMsg))
                return true;
        }
        break;
    case TEL_G709_LEN64:
        FC_REPORT_ERROR(FC_NotSupportedError, "G.709 trace not implemented yet");
        break;

    case TEL_TRACE_NOT_PROV:
        // String not valid, copy empty string and return false.
        theDestMsg[0] = 0;
        break;
    default:
        FC_REPORT_ERROR(FC_NotSupportedError, "Undefined trace mode");
        break;
    }

    return false;

}

//##ModelId=3C20B0B00134
void TEL_TraceUtilities::Pad16BytesMsg(const char* theSrcMsg, char* theDestMsg)
{
    uint32 length;
    uint32 i;

    // Get source msg length.
    length = strlen(theSrcMsg);

    // Copy source message.
    strncpy(theDestMsg, theSrcMsg, TEL_MAX_USER_CHARS_16BYTES);

     // Pad message with white spaces.
    for (i=length; i < (TEL_MAX_USER_CHARS_16BYTES); i++)
        theDestMsg[i] = ' ';

    theDestMsg[TEL_MAX_USER_CHARS_16BYTES] = '\0';

}

//##ModelId=3C20B0B0013F
void TEL_TraceUtilities::Pad64BytesMsg(const char* theSrcMsg, char* theDestMsg)
{
    uint32 length;
    uint32 i;

    // Get source msg length.
    length = strlen(theSrcMsg);

    // Copy source message.
    strncpy(theDestMsg, theSrcMsg, TEL_MAX_USER_CHARS_64BYTES);

     // Pad message with white spaces.
    for (i=length; i < (TEL_MAX_USER_CHARS_64BYTES); i++)
        theDestMsg[i] = ' ';

    theDestMsg[TEL_MAX_USER_CHARS_64BYTES] = '\0';

}
