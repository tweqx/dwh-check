#ifndef __hash_h
#define __hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* some sizes (number of bytes) */
#define ROWS 8
#define LENGTHFIELDLEN ROWS
#define COLS512 8
#define COLS1024 16
#define SIZE512 (ROWS*COLS512)
#define SIZE1024 (ROWS*COLS1024)

#define ROUNDS512 10
#define ROUNDS1024 14

#define ROTL64(a,n) ((((a)<<(n))|((a)>>(64-(n))))&(0xffffffffffffffffULL))
#define EXT_BYTE(var,n) ((uint8_t)((uint64_t)(var) >> (8*n)))
#define U64BIG(a) \
  ((ROTL64(a, 8) & (0x000000FF000000FFULL)) | \
   (ROTL64(a,24) & (0x0000FF000000FF00ULL)) | \
   (ROTL64(a,40) & (0x00FF000000FF0000ULL)) | \
   (ROTL64(a,56) & (0xFF000000FF000000ULL)))

enum { LONG = SIZE1024, SHORT = SIZE512 };

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;

#define SUCCESS 0
#define FAIL 1
#define BAD_HASHLEN 2

typedef struct {
  uint64_t *chaining __attribute__((aligned(16)));            /* actual state */
  BitSequence *buffer;      /* data buffer */
  uint64_t block_counter;        /* message block counter */
  int buf_ptr;              /* data buffer pointer */
  int bits_in_last_byte;    /* no. of message bits in last byte of
			       data buffer */
  int hashbitlen;           /* output length in bits */
  int size;                 /* LONG or SHORT */
} grostl_state_t;

int grostl_init(grostl_state_t*, int);
int grostl_update(grostl_state_t*, const BitSequence*, DataLength);
int grostl_final(grostl_state_t*, BitSequence*);
int grostl_hash(int, const BitSequence*, DataLength, BitSequence*);

#endif /* __hash_h */

