// md5.cpp: implementation of the md5 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MD5Calc.h"
#include "md5.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define mod %
#define or |
#define xor ^
#define and &
#define not ~

#define leftrotate(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)))

/*  leftrotate function definition
    leftrotate (x, c)
     return (x << c) binary or (x >> (32-c))

https://tls.mbed.org/md5-source-code
https://en.wikipedia.org/wiki/MD5
*/

void InitConstants(int *K)
{
// Use binary integer part of the sines of integers (Radians) as constants:
for (int i=0;i<64;i++)
K[i] = (int)floor(pow(2, 32)*fabs((sin(i + 1))));  // (1<<32) mean 2 at power 23
// (Or just use the following precomputed table)

}

inline unsigned int GET_UINT32_LE(unsigned char*b, int i)
{
    return ( (unsigned int) (b)[(i)    ]       )
         | ( (unsigned int) (b)[(i) + 1] <<  8 )
         | ( (unsigned int) (b)[(i) + 2] << 16 )
         | ( (unsigned int) (b)[(i) + 3] << 24 );
}

// Encodes input (unsigned int) into output (unsigned char). Assumes len is 8.
inline void PUT_UINT64_LE(unsigned char* output, int out_pos, unsigned int* input)
{

    output[out_pos+0+0] = (unsigned char)  (input[0] & 0xff);
    output[out_pos+0+1] = (unsigned char) ((input[0] >> 8) & 0xff);
    output[out_pos+0+2] = (unsigned char) ((input[0] >> 16) & 0xff);
    output[out_pos+0+3] = (unsigned char) ((input[0] >> 24) & 0xff);

    output[out_pos+4+0] = (unsigned char) (input[1] & 0xff);
    output[out_pos+4+1] = (unsigned char) ((input[1] >> 8) & 0xff);
    output[out_pos+4+2] = (unsigned char) ((input[1] >> 16) & 0xff);
    output[out_pos+4+3] = (unsigned char) ((input[1] >> 24) & 0xff);

}

int Padding(unsigned char* bytes, int size)
{
/* Pseudocode of Padding:
//Pre-processing: adding a single 1 bit
append "1" bit to message    
  Notice: the input bytes are considered as bits strings,
  where the first bit is the most significant bit of the byte.

  Pre-processing: padding with zeros
append "0" bit until message length in bits = 448 (mod 512)
append original length in bits to message
*/

unsigned int count[2] = {0, 0};     // number of bits

// Pad out to 56 mod 64: this size is in bytes!
// in bits: append "0" bit until message length in bits = 448 (mod 512)
int index = (unsigned int) (size & 0x3f);
int padLen = (index < 56) ? (56 - index) : (120 - index);

bytes[size+0] = 0x80;  // append 1 to message message
for (int i=1;i<padLen;i++)
bytes[size+i] = 0;  // append 0 to message message

// Place NumberOfBits at the end of buffer:
// append original length in bits to message

// Update number of bits
count[0] = (unsigned int) size << 3;
if (count[0]<((unsigned int) size << 3))
   count[1]++;
// <<3 means that we multiply with 2^8 to get bits from bytes

count[1] += ((unsigned int)size >> 29);

PUT_UINT64_LE(bytes, size+padLen, count);
// bytes = output; siz+padLen = position; count - integer to encode; 8 = number of bytes of count
return padLen+8;

}

int K[64] = // contants
{ 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
  0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
  0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
  0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
  0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
  0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

// s specifies the per-round shift amounts
int s[64] =
{ 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

md5_context md5::CalculateMD5(unsigned char* bytes, int size)
{

md5_context* md5_val = new md5_context();
md5_val->Failed = false;

if (size==0||bytes==NULL)
{
md5_val->Failed = true;
return *md5_val;
}

InitConstants(K);

int pad_len = Padding(bytes, size);

//Initialize variables:
unsigned int a0 = 0x67452301;   // A
unsigned int b0 = 0xefcdab89;   // B
unsigned int c0 = 0x98badcfe;   // C
unsigned int d0 = 0x10325476;   // D

for (int j=0;j<size+pad_len;j+=64)
{

	// break chunk into sixteen 32-bit words M[k], 0 <= k <= 15
	unsigned int M[16];
	for (int k=0;k<16;k++)
	M[k] = GET_UINT32_LE(bytes, k*4+j);

	// Initialize hash value for this chunk:
    unsigned int A = a0;
    unsigned int B = b0;
    unsigned int C = c0;
    unsigned int D = d0;
    // Main loop:
    for (int i=0;i<64;i++)  // 64 passes; 4 rounds: 16 passes per round
	{
        unsigned int F, g;
        if ((0<=i)&&(i<=15))
		{
            F = D xor (B and (C xor D));
			// C++ style: F = D ^ (B & (C ^ D));
            g = i;
		}
        else if ((16<=i)&&(i<=31))
		{
			F = C xor (D and (B xor C));
			// C++ style: F = C ^ (D & (B ^ C));
            g = (5*i + 1) mod 16;
		}
        else if ((32<=i)&&(i<=47))
		{

			F = B xor C xor D;  // C++: xor = ^
            g = (3*i + 5) mod 16;
		}
        else if ((48<=i)&&(i<=63))
		{
			F = C xor (B or (not D));
            // C++ style: F = C ^ (B | ~D);
            g = (7*i) mod 16;
		}
        // Be wary of the below definitions of A, B, C, D
		F = F + A + K[i] + M[g];
        A = D;  // the A value is lost and is only kept in previous F sum
        D = C;
        C = B;  // previous value of B is kept in C
        B = B + leftrotate(F, s[i]);  // we can calculate F
  /*  B is a big sum which includes previous values of A, Formula(B, C, D) and M[g]
	  Reverse of variable switch:
	  A value is lost while B isn't changed here so we can get C and D:
	  C = D;
	  D = A;
	  B = sum(F(B,C,D))+sum(A)+sum(M[g])
		*/

	} // end of current block for
	//Add this chunk's hash to result so far:
    a0 = a0 + A;
    b0 = b0 + B;
    c0 = c0 + C;
    d0 = d0 + D;
	// var char digest[16] = a0 append b0 append c0 append d0 (Output is in little-endian)

}

md5_val->A = a0;
md5_val->B = b0;
md5_val->C = c0;
md5_val->D = d0;
return *md5_val;

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


md5::md5()
{

}

md5::~md5()
{

}
