#ifndef FNV512_H
#define FNV512_H

#include "uint512.h"

#define FNV_VERSION_0 0
#define FNV_VERSION_1 1
#define FNV_VERSION_1a 2

typedef struct {
  unsigned char version;
  uint512_t hash;
} fnv512_state_t;

void fnv_init(fnv512_state_t* state, unsigned char version);
void fnv_update(fnv512_state_t* state, const unsigned char* data, uint64_t length);
void fnv_final(fnv512_state_t* state, unsigned char* digest);

#endif
