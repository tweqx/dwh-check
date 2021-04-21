#include "uint512.h"

#include <stdio.h>
#include <stdbool.h>

void uint512_print_hex(const uint512_t* n) {
  printf("0x");
  for (int i = 7; i >= 0; i--)
    printf("%016lx", n->u[i]);
}

uint512_t* uint512_zero(uint512_t* n) {
  for (unsigned int i = 0; i < 8; i++)
    n->u[i] = 0;

  return n;
}
uint512_t* uint512_const(uint512_t* n, uint64_t c) {
  n->u[0] = c;
  for (unsigned int i = 1; i < 8; i++)
    n->u[i] = 0;

  return n;
}

uint512_t* uint512_set(uint512_t* n1, const uint512_t* n2) {
  for (unsigned int i = 0; i < 8; i++)
    n1->u[i] = n2->u[i];

  return n1;
}

uint512_t* uint512_add(uint512_t* n1, const uint512_t* n2) {
  uint64_t carry = 0;

  for (unsigned int i = 0; i < 8; i++) {
    bool overflowed = __builtin_add_overflow(n1->u[i], n2->u[i], &n1->u[i]);

    int next_carry = 0;
    if (overflowed)
      next_carry += 1;

    overflowed = __builtin_add_overflow(n1->u[i], carry, &n1->u[i]);
    if (overflowed)
      next_carry += 1;

    carry = next_carry;
  }

  return n1;
}

uint512_t* uint512_sub(uint512_t* n1, const uint512_t* n2) {
  uint64_t carry = 0;

  for (unsigned int i = 0; i < 8; i++) {
    uint8_t overflowed = __builtin_sub_overflow(n1->u[i], n2->u[i], &n1->u[i]);
    overflowed += __builtin_sub_overflow(n1->u[i], carry, &n1->u[i]);

    carry = overflowed;
  }

  return n1;
}

// Adds value * (2^64)^shift to n1
static void uint512_shifted_sum(uint512_t* n1, uint64_t value, unsigned int shift) {
  uint64_t carry = __builtin_add_overflow(n1->u[shift], value, &n1->u[shift]);

  for (unsigned int i = shift + 1; i < 8; i++) {
    if (carry == 0)
      break;

    carry = __builtin_add_overflow(n1->u[i], carry, &n1->u[i]);
  }
}

uint512_t* uint512_mul(uint512_t* n1, const uint512_t* n2) {
  uint512_t c;
  uint512_zero(&c);

  for (unsigned int k = 0; k < 8; k++) {
    // Cauchy Product
    for (unsigned int l = 0; l <= k; l++) {
      // c->u[k] += n1->u[l] * n2->u[k - l]
      __uint128_t term = n1->u[l] * (__uint128_t)n2->u[k - l];

      uint512_shifted_sum(&c, term & 0xffffffffffffffff, k);
      if (k + 1 < 8)
        uint512_shifted_sum(&c, term >> 64, k + 1);
    }
  }

  uint512_set(n1, &c);

  return n1;
}

uint512_t* uint512_xor(uint512_t* n1, uint64_t c) {
  n1->u[0] ^= c;

  return n1;
}

