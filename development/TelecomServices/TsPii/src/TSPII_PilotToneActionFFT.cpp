/*-----------------------------------------------------------------------------
 *Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:         TSPII
AUTHOR:         M. Piotte, 2002/12/11
DESCRIPTION:    Pilot tone collection class
-----------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include "TsPii/TSPII_PilotToneAction.h"

// This following include must come after the above includes because it has an
// evil redefinition for "sin", "cos", and "sqrt". If you place it in front of
// previous header files, it can destroy the definitions of standard versions
// of these math services, and damage classes depending on those. You will get
// errors like : the global scope has no "cos"
#include <OSPortability/mathFPU.h>

//
// I don't know how this ever works, because math.h also defines M_PI to pi.
// I am only changing things for linux now. aer 08/16/06
//
#ifdef LINUX
#undef M_PI
#endif

const float M_PI          = 3.1415926535897932384626433832795f;

///////////////////////////////////////////////////////////////////////////////
// NOTE:    This method was put in a separate file in order to compile
//          with and without floating point unit enabled on CPU
// WARNING: If this file is compiled with FPU enabled on CPU, but
//          linked with other objects that are using S/W FP emulation,
//          this function must not make function calls to other with floating
//          parameters (calling convention is different between S/W and H/W FP).
///////////////////////////////////////////////////////////////////////////////
void TSPII_PilotToneAction::ComputeFFT()
{
    uint32 i;
    uint32 j;

    // Recompute window if needed.
    if (mySampleCount != myWindowLength)
    {
        const float FT_A0 = 0.2810639f;
        const float FT_A1 = 0.5208972f;
        const float FT_A2 = 0.1980399f;

        float rot = 2.0f*M_PI/mySampleCount;
        float dc  = 0.0f;

        // Compute values
        for (i = 0; i < mySampleCount; i++)
        {
            float ip5        = i + 0.5f;
            myWindowData[i] = (float)(FT_A0 - FT_A1*cos(rot*ip5) + FT_A2*cos(rot*2.0*ip5));
            dc               += myWindowData[i];
        }

        // Scale values
        float scale = 1.0f/dc;
        for (i = 0; i < mySampleCount; i++) myWindowData[i] *= scale;

        // Remember current length
        myWindowLength = mySampleCount;
    }

    // Apply the window
    for (i = j = 0; i <mySampleCount; i++, j += 2)
    {
        myFreqData[j    ] = myTimeData[i].q*myWindowData[i];
        myFreqData[j + 1] = myTimeData[i].i*myWindowData[i];
    }

    const    float PT_FORWARD_FFT =  1.0f;
    // const float PT_REVERSE_FFT = -1.0f;

    int32   i2, ip, j2, k, l, le, le2, n2, nm1, m;
    float   ur, ui, wr, wi, temr, temi, piol1;
    float * array_A = myFreqData;
    int32   n       = mySampleCount;

    // Valid that the length is a power of 2
    // m = log2(n);
    for (m = 0, i = 1; i <= TSPII_MAX_PILOT_TONE_SAMPLE; m++, i <<= 1) if (i == n) break;
    FC_THROW_ERROR_IF(i > TSPII_MAX_PILOT_TONE_SAMPLE, FC_ValueOutOfRangeError, "Cannot compute FFT if not power of 2");

    // FFT processing
    n2  = n / 2;
    nm1 = n - 1;
    j   = 1;
    for (i = 1; (int32)i <= nm1; i++)
    {
        if (i < j)
        {
            i2            = (i - 1)*2;
            j2            = (j - 1)*2;
            temr        = array_A[j2];
            temi        = array_A[j2+1];
            array_A[j2]   = array_A[i2];
            array_A[j2+1] = array_A[i2+1];
            array_A[i2]   = temr;
            array_A[i2+1] = temi;
        }
        k = n2;
        while (k < (int32)j)
        {
            j = j - k;
            k = k/2;
        }
        j = j + k;
    }
    for(l = 1; l <= m; l++)
    {
        le    = 1 << l;
        le2   = le/2;
        ur  = 1.;
        ui  = 0.;
        piol1 = PT_FORWARD_FFT*M_PI/le2;
        wr  = cos(piol1);
        wi  = sin(piol1);
        for (j = 1; (int32)j <= le2; j++)
        {
            for (i = j; (int32)i <= n; i = i + le)
            {
                i2              = (i - 1)*2 ;
                ip              = (i - 1 + le2)*2 ;
                temr            = array_A[ip    ]*ur - array_A[ip + 1]*ui; // tem = A*u (R)
                temi            = array_A[ip + 1]*ur + array_A[ip    ]*ui; // tem = A*u (I)
                array_A[ip    ] = array_A[i2    ] - temr;
                array_A[ip + 1] = array_A[i2 + 1] - temi;
                array_A[i2    ] = array_A[i2    ] + temr;
                array_A[i2 + 1] = array_A[i2 + 1] + temi;
            }

            // u *= w
            temr = ur*wr - ui*wi; // tem = u*w (R)
            temi = ui*wr + ur*wi; // tem = u*w (I)
            ur   = temr;
            ui   = temi;
        }
    }

    // Compute squared amplitude
    for (i = j = 0; i < mySampleCount; i++, j += 2)
    {
        myFreqData[i] = myFreqData[j]*myFreqData[j] + myFreqData[j + 1]*myFreqData[j + 1];
    }

    // Replace sample order
    for (i = mySampleCount/2, j = mySampleCount;   i < mySampleCount;   i++, j++) myFreqData[j] = myFreqData[i];
    for (i = 0,               j = mySampleCount/2; j < mySampleCount;   i++, j++) myFreqData[j] = myFreqData[i];
    for (i = mySampleCount,   j = 0;               j < mySampleCount/2; i++, j++) myFreqData[j] = myFreqData[i];
}

