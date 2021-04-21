// keccak3.h
// Markku-Juhani O. Saarinen <mjos@iki.fi>

#ifndef KECCAK3_H
#define KECCAK3_H

#include <stddef.h>
#include <stdint.h>

#ifndef KECCAKF_ROUNDS
#define KECCAKF_ROUNDS 24
#endif

#ifndef ROTL64
#define ROTL64(x, y) (((x) << (y)) | ((x) >> (64 - (y))))
#endif

// state context
typedef struct {
    union {                                 // state:
        uint8_t b[200];                     // 8-bit bytes
        uint64_t q[25];                     // 64-bit words
    } st;
    int pt, rsiz, mdlen;                    // these don't overflow
} keccak3_ctx_t;

// Compression function.
void keccak3_keccakf(uint64_t st[25]);

// OpenSSL - like interface
int keccak3_init(keccak3_ctx_t *c, int mdlen);    // mdlen = hash output in bytes
int keccak3_update(keccak3_ctx_t *c, const void *data, size_t len);
int keccak3_final(void *md, keccak3_ctx_t *c);    // digest goes to md

// compute a keccak3 hash (md) of given byte length from "in"
void *keccak3_hash(const void *in, size_t inlen, void *md, int mdlen);

#endif

