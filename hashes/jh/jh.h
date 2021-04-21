#ifndef JH_H
#define JH_H

typedef unsigned long long uint64;

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;
#ifdef __SSE2__
  #include <emmintrin.h>

  typedef __m128i  word128;   /*word128 defines a 128-bit SSE2 word*/
#endif

#define SUCCESS 0
#define FAIL 1
#define BAD_HASHLEN 2

/*define data alignment for different C compilers*/
#if defined(__GNUC__)
      #define DATA_ALIGN16(x) x __attribute__ ((aligned(16)))
#else
      #define DATA_ALIGN16(x) __declspec(align(16)) x
#endif

typedef struct {
	int hashbitlen;	   	              /*the message digest size*/
	unsigned long long databitlen;    /*the message size in bits*/
	unsigned long long datasize_in_buffer;      /*the size of the message remained in buffer; assumed to be multiple of 8bits except for the last partial block at the end of the message*/
	DATA_ALIGN16(uint64 x[8][2]);     /*the 1024-bit state, ( x[i][0] || x[i][1] ) is the ith row of the state in the pseudocode*/

    #ifdef __SSE2__
      word128  x0,x1,x2,x3,x4,x5,x6,x7; /*1024-bit state;*/
    #else
	  DATA_ALIGN16(uint64 x[8][2]);     /*the 1024-bit state, ( x[i][0] || x[i][1] ) is the ith row of the state in the pseudocode*/
    #endif

	unsigned char buffer[64];         /*the 512-bit message block to be hashed;*/
} jh_state_t;

int	jh_init(jh_state_t *state, int hashbitlen);
int	jh_update(jh_state_t *state, const BitSequence *data, DataLength databitlen);
int	jh_final(jh_state_t *state, BitSequence *hashval);
int	jh_hash(int hashbitlen, const BitSequence *data, DataLength databitlen, BitSequence *hashval);

#endif

