#ifndef UINT512_H
#define UINT512_H

#include <stdint.h>

#define UINT512(u8, u7, u6, u5, u4, u3, u2, u1) ((uint512_t){ {u1, u2, u3, u4, u5, u6, u7, u8} })

// uint512_t :
//   Blocks of 64 bits :   u8 | u7 | u6 | u5 | u4 | u3 | u2 | u1 
//   Bits (MSB) :         512               256                 0
typedef struct uint512_t {
  uint64_t u[8];
} uint512_t;

void uint512_print_hex(const uint512_t* n);

// Sets n to 0
uint512_t* uint512_zero(uint512_t* n);
// Sets n to a constant
uint512_t* uint512_const(uint512_t* n, uint64_t c);

// Sets n1 to n2
uint512_t* uint512_set(uint512_t* n1, const uint512_t* n2);

// Adds n2 to n1
uint512_t* uint512_add(uint512_t* n1, const uint512_t* n2);
// Substracts n2 from n1 (unsigned arithmetics)
uint512_t* uint512_sub(uint512_t* n1, const uint512_t* n2);
// Multiplies n1 by n2
uint512_t* uint512_mul(uint512_t* n1, const uint512_t* n2);

// XORs the lowest 64 bits of n1 with c
uint512_t* uint512_xor(uint512_t* n1, uint64_t c);


#endif
