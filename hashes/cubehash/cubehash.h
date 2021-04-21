#ifndef CUBEHASH_H
#define CUBEHASH_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
  // Parameters
  unsigned int i, r, b, f, h;

  // Internal state
  uint32_t state[32];

  // Incomplete block
  uint8_t* remainder;
  uint8_t remainder_length;
} cubehash_t;

void cubehash_init(cubehash_t* state, unsigned int i, unsigned int r, unsigned int b, unsigned int f, unsigned int h);
void cubehash_update(cubehash_t* state, const unsigned char *data, size_t len);
void cubehash_final(cubehash_t* state, unsigned char* digest);
void cubehash_cleanup(cubehash_t* state);

#endif
