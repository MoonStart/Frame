// TestProg.cpp : Defines the entry point for the console application.
//

#include "gdef.h"
#include "stdio.h"
#ifdef WIN32
    #include <iostream>                  // Input/output stream
    using namespace std;
#else 
    #include <iostream.h>
#endif    

int main(int argc, char* argv[])
{
    uint32 count=0;
//    uint8 bufP[5]={0x5c, 0x8f, 0x2, 0x3e, 0};
/*    uint8 bufP[121]= {0x8d, 0x97,  0x2e,   0x3e, // Li Curve
                      0x6f, 0x12,  0x83,   0x3c,     
                      0x78, 0x7a,  0x25,   0x3d,     
                      0x56, 0x9f,  0x6b,   0x3e,     
                      0x8d, 0x28,  0x8d,   0x3e,     
                      0x97, 0x90,  0x4f,   0x3f,     
                      0x6a, 0x4d,  0x93,   0x3e,     
                      0x81, 0x4 ,  0x5 ,   0x3f,     
                      0x71, 0x3d,  0xca,   0x3f,     
                      0x20, 0xd2,  0xaf,   0x3e,     
                      0xbc, 0x5 ,  0x42,   0x3f,     
                      0xb4, 0xc8,  0x16,   0x40,     
                      0x68, 0x22,  0xcc,   0x3e,     
                      0x9f, 0x3c,  0x7c,   0x3f,     
                      0x64, 0x3b,  0x47,   0x40,     
                      0x30, 0x2a,  0xe9,   0x3e,     
                      0xc5, 0xfe,  0x9a,   0x3f,     
                      0xe9, 0x26,  0x79,   0x40,     
                      0x93, 0xa9,  0x2 ,   0x3f,     
                      0x90, 0x31,  0xb7,   0x3f,     
                      0x56, 0xe ,  0x95,   0x40,     
                      0x93, 0x3a,  0x11,   0x3f,     
                      0xb1, 0x50,  0xd3,   0x3f,     
                      0xf2, 0xd2,  0xad,   0x40,     
                      0xae, 0xd8,  0x1f,   0x3f,     
                      0x2b, 0x87,  0xee,   0x3f,     
                      0x4 , 0x56,  0xc6,   0x40,     
                      0x40, 0xa4,  0x2f,   0x3f,     
                      0x88, 0x63,  0x5 ,   0x40,     
                      0x6d, 0xe7,  0xdf,   0x40, 0};*/
/*    uint8 bufP[9]= {0xd9, 0xbd, 0x13, 0x42,  C0 and C1 Therm resistance
                    0xfb, 0x4b, 0xca, 0x41,0};*/
    uint8 bufP[5]= {0xc9, 0x71, 0x27, 0x3c, 0};  // 

    float *floatP;
    float displayFloat;
    char  aChar;

    // Converts 4 bytes to a float value
    floatP = (float *)bufP;
/*    for (int i=0; i<30; i+=3)
    {
        cout << " Li Curve element #" << (i/3) << endl;
        for (int j=0; j<3; j++)
        {
            displayFloat = *floatP;
            cout << "Parameter " << j << " float value: " << displayFloat << endl;
            floatP++;
        }
    }*/
    displayFloat = *floatP;
    cout << "Bias.Cf.k " << displayFloat << endl;
/*    cout << "C0 " << displayFloat << endl;
    floatP++;
    displayFloat = *floatP;
    cout << "C1 " << displayFloat << endl;*/
    cout << "press enter to quit" << endl;
    aChar = getchar();
    return 0;
}
