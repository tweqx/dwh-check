#ifndef LP_HASH_H
#define LP_HASH_H

#include <stdint.h>
#include <endian.h>

// 36367763ab73783c7af284446c59466b4cd653239a311cb7116d4618dee09a8425893dc7500b464fdaf1672d7bef5e891c6e2274568926a49fb4f45132c2a8b4
extern const char* lp_hexdigest;

// 'lp_hexdigest' converted from hex to binary
extern uint8_t lp_hash[64];

// First 64 bits of 'lp_hash', for fast comparaisons
#if __BYTE_ORDER == __LITTLE_ENDIAN
  #define LP_SIGNATURE 0x3c7873ab63773636
#else /* __BYTE_ORDER == __BIG_ENDIAN */
  #define LP_SIGNATURE 0x36367763ab73783c
#endif

#endif
