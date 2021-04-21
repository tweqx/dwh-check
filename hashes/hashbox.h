#ifndef HASHBOX_H
#define HASHBOX_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <openssl/evp.h>
#include "streebog/gost3411-2012-core.h"
#include "grostl/grostl.h"
#include "md6/md6.h"
#include "jh/jh.h"
#include "blake512/blake512.h"
#include "lsh/lsh.h"
#include "skein/SHA3api_ref.h"
#include "keccak3/keccak3.h"
#include "cubehash/cubehash.h"
#include "whirlpool/Whirlpool.h"
#include "fnv512/fnv512.h"

#include "lp_hash.h"

// Return values for 'hashbox_final()'
#define HASHBOX_NO_MATCH 0
#define HASHBOX_SHA512 1
#define HASHBOX_BLAKE2B 2
#define HASHBOX_STREEBOG 3
#define HASHBOX_SHA3 4
#define HASHBOX_FNV0 5
#define HASHBOX_FNV1 6
#define HASHBOX_FNV1A 7
#define HASHBOX_GROSTL 8
#define HASHBOX_MD6 9
#define HASHBOX_JH 10
#define HASHBOX_BLAKE512 11
#define HASHBOX_LSH 12
#define HASHBOX_SKEIN 13
#define HASHBOX_KECCAK3 14
#define HASHBOX_CUBEHASH 15
#define HASHBOX_WHIRLPOOL0 16
#define HASHBOX_WHIRLPOOLT 17
#define HASHBOX_WHIRLPOOL 18

typedef struct {
  EVP_MD_CTX* sha512;
  EVP_MD_CTX* blake2b;
  GOST34112012Context streebog;
  EVP_MD_CTX* sha3;
  fnv512_state_t fnv0;
  fnv512_state_t fnv1;
  fnv512_state_t fnv1a;
  grostl_state_t grostl;
  md6_state md6;
  jh_state_t jh;
  blake512_state_t blake512;
  struct LSH512_Context lsh;
  skein_state_t skein;
  keccak3_ctx_t keccak3;
  cubehash_t cubehash;
  whirlpool_state_t whirlpool0;
  whirlpool_state_t whirlpoolT;
  whirlpool_state_t whirlpool;
} hashbox_t;

// Creates a new hashbox. This hashbox should be freed with 'hashbox_final'
hashbox_t* hashbox_new();
// Updates all hashes with 'data', of length 'length' bytes
void hashbox_update(hashbox_t* hashbox, uint8_t* data, uint32_t length);
// Computes the digest of each hash, returns HASHBOX_NO_MATCH if none are matching to the DWH,
//  or else the relevant HASHBOX_* constant
unsigned int hashbox_final(hashbox_t* hashbox);

#endif
