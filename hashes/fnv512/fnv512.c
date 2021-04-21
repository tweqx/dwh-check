#include "fnv512.h"

#include <endian.h>
#include <byteswap.h>

#include <stdio.h>

static uint512_t fnv_prime = UINT512(
  0x0000000000000000, 0x0000000000000000, 0x0000000001000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000157
);

static uint512_t hash0_v1 = UINT512(
  0xb86db0b1171f4416, 0xdca1e50f309990ac, 0xac87d059c9000000, 0x0000000000000d21, 0xe948f68a34c192f6, 0x2ea79bc942dbe7ce, 0x182036415f56e34b, 0xac982aac4afe9fd9
);

void fnv_init(fnv512_state_t* state, unsigned char version) {
  if (version != FNV_VERSION_0 && version != FNV_VERSION_1 && version != FNV_VERSION_1a)
    version = FNV_VERSION_1a;

  state->version = version;

  // Loads the offset basis
  if (version == FNV_VERSION_0)
    uint512_zero(&state->hash);
  else if (version == FNV_VERSION_1)
    uint512_set(&state->hash, &hash0_v1);
  else
    uint512_set(&state->hash, &hash0_v1);
}
void fnv_update(fnv512_state_t* state, const unsigned char* data, uint64_t length) {
  if (state->version == FNV_VERSION_0 || state->version == FNV_VERSION_1) {
    // FNV-0/FNV-1a : XOR after the multiplication
    for (uint64_t i = 0; i < length; i++) {
      uint512_mul(&state->hash, &fnv_prime);

      uint512_xor(&state->hash, data[i]);
    }
  }

  else {
    // FNV-1a : XOR followed by the multiplication
    for (uint64_t i = 0; i < length; i++) {
      uint512_xor(&state->hash, data[i]);

      uint512_mul(&state->hash, &fnv_prime);
    }
  }
}
void fnv_final(fnv512_state_t* state, unsigned char* digest) {
  for (int i = 0; i < 8; i++) {
    uint64_t u = state->hash.u[i];

#if __BYTE_ORDER == __BIG_ENDIAN
    ((uint64_t*)digest)[7 - i] = u;
#else /* __BYTE_ORDER == __LITTLE_ENDIAN */
    ((uint64_t*)digest)[7 - i] = __bswap_64(u);
#endif
  }
}

