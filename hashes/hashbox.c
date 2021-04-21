#include "hashbox.h"

#define CHECK_ALLOC(ptr) \
  if (!ptr) puts("hasbox_new: context allocation failed");

hashbox_t* hashbox_new() {
  hashbox_t* hashbox = malloc(sizeof(hashbox_t));

  if (!hashbox) {
    puts("hasbox_new: hashbox allocation failed");

    return NULL;
  }

  // Contexts

  /* SHA-512 */
  hashbox->sha512 = EVP_MD_CTX_new();
  CHECK_ALLOC(hashbox->sha512);
  EVP_DigestInit_ex(hashbox->sha512, EVP_sha512(), NULL);

  /* BLAKE2b */
  hashbox->blake2b = EVP_MD_CTX_new();
  CHECK_ALLOC(hashbox->blake2b);
  EVP_DigestInit_ex(hashbox->blake2b, EVP_blake2b512(), NULL);

  /* Streebog */
  GOST34112012Init(&hashbox->streebog, 512);

  /* SHA3 */
  hashbox->sha3 = EVP_MD_CTX_new();
  CHECK_ALLOC(hashbox->sha3);
  EVP_DigestInit_ex(hashbox->sha3, EVP_sha3_512(), NULL);

  /* FNV-0 */
  fnv_init(&hashbox->fnv0, FNV_VERSION_0);

  /* FNV-1 */
  fnv_init(&hashbox->fnv1, FNV_VERSION_1);

  /* FNV-1a */
  fnv_init(&hashbox->fnv1a, FNV_VERSION_1a);

  /* Grøstl */
  grostl_init(&hashbox->grostl, 512);

  /* MD6 */
  md6_init(&hashbox->md6, 512);

  /* JH */
  jh_init(&hashbox->jh, 512);

  /* BLAKE-512 */
  blake512_init(&hashbox->blake512);

  /* LSH */
  lsh_init(&hashbox->lsh);

  /* Skein */
  skein_init(&hashbox->skein, 512);

  /* Keccak3 */
  keccak3_init(&hashbox->keccak3, 64);

  /* Cubehash */
  cubehash_init(&hashbox->cubehash, 16, 16, 32, 32, 512); // CubeHash16+16/32+32–512

  /* Whirlpool-0 */
  whirlpool_init(&hashbox->whirlpool0, WHIRLPOOL_0);

  /* Whirlpool-T */
  whirlpool_init(&hashbox->whirlpoolT, WHIRLPOOL_T);

  /* Whirlpool */
  whirlpool_init(&hashbox->whirlpool, WHIRLPOOL);

  return hashbox;
}

void hashbox_update(hashbox_t* hashbox, uint8_t* data, uint32_t length) {
  EVP_DigestUpdate(hashbox->sha512, data, length);
  EVP_DigestUpdate(hashbox->blake2b, data, length);
  GOST34112012Update(&hashbox->streebog, data, length);
  EVP_DigestUpdate(hashbox->sha3, data, length);
  fnv_update(&hashbox->fnv0, data, length);
  fnv_update(&hashbox->fnv1, data, length);
  fnv_update(&hashbox->fnv1a, data, length);
  grostl_update(&hashbox->grostl, data, length * 8);
  md6_update(&hashbox->md6, data, length * 8);
  jh_update(&hashbox->jh, data, length * 8);
  blake512_update(&hashbox->blake512, data, length);
  lsh_update(&hashbox->lsh, data, length * 8);
  skein_update(&hashbox->skein, data, length * 8);
  keccak3_update(&hashbox->keccak3, data, length);
  cubehash_update(&hashbox->cubehash, data, length);
  whirlpool_update(data, length * 8, &hashbox->whirlpool0);
  whirlpool_update(data, length * 8, &hashbox->whirlpoolT);
  whirlpool_update(data, length * 8, &hashbox->whirlpool);
}

#define MATCH_DIGEST(message_digest, hash_function) do { \
    if (/**(uint64_t*)message_digest == LP_SIGNATURE && */memcmp(message_digest, lp_hash, 64) == 0) { \
      result = hash_function; \
      goto cleanup; \
    } \
  } while(0)

/*
// Debug version, prints hashes
#define MATCH_DIGEST(message_digest, hash_function) do { \
    for (unsigned int i = 0; i < 64; i++) \
      printf("%02x", message_digest[i]); \
    printf("\n"); \
     \
    if (*(uint64_t*)message_digest == LP_SIGNATURE && memcmp(message_digest, lp_hash, 64) == 0) { \
      result = hash_function; \
      goto cleanup; \
    } \
  } while(0) */

unsigned int hashbox_final(hashbox_t* hashbox) {
  uint8_t message_digest[64] = {0};
  unsigned int result = HASHBOX_NO_MATCH;

  // Finalize and check hashes
  EVP_DigestFinal_ex(hashbox->sha512, message_digest, NULL);
  MATCH_DIGEST(message_digest, HASHBOX_SHA512);

  EVP_DigestFinal_ex(hashbox->blake2b, message_digest, NULL);
  MATCH_DIGEST(message_digest, HASHBOX_BLAKE2B);

  GOST34112012Final(&hashbox->streebog, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_STREEBOG);

  EVP_DigestFinal_ex(hashbox->sha3, message_digest, NULL);
  MATCH_DIGEST(message_digest, HASHBOX_SHA3);

  fnv_final(&hashbox->fnv0, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_FNV0);

  fnv_final(&hashbox->fnv1, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_FNV1);

  fnv_final(&hashbox->fnv1a, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_FNV1A);

  grostl_final(&hashbox->grostl, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_GROSTL);

  md6_final(&hashbox->md6, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_MD6);

  jh_final(&hashbox->jh, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_JH);

  blake512_final(&hashbox->blake512, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_BLAKE512);

  lsh_final(&hashbox->lsh, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_LSH);

  skein_final(&hashbox->skein, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_SKEIN);

  keccak3_final(message_digest, &hashbox->keccak3);
  MATCH_DIGEST(message_digest, HASHBOX_KECCAK3);

  cubehash_final(&hashbox->cubehash, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_CUBEHASH);

  whirlpool_final(&hashbox->whirlpool0, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_WHIRLPOOL0);

  whirlpool_final(&hashbox->whirlpoolT, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_WHIRLPOOLT);

  whirlpool_final(&hashbox->whirlpool, message_digest);
  MATCH_DIGEST(message_digest, HASHBOX_WHIRLPOOL);

  // Cleanup
cleanup:
  EVP_MD_CTX_free(hashbox->sha512);
  EVP_MD_CTX_free(hashbox->blake2b);
  GOST34112012Cleanup(&hashbox->streebog);
  EVP_MD_CTX_free(hashbox->sha3);
  cubehash_cleanup(&hashbox->cubehash);

  free(hashbox);

  return result;
}

