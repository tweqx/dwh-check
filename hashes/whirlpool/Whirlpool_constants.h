#ifndef WHIRLPOOL_CONSTANTS_H
#define WHIRLPOOL_CONSTANTS_H

#include "nessie.h"

/*
 * The number of rounds of the internal dedicated block cipher.
 */
#define R 10

// Whirlpool-0
extern const u64 rc_0[R + 1];

extern const u64 C0_0[256];
extern const u64 C1_0[256];
extern const u64 C2_0[256];
extern const u64 C3_0[256];
extern const u64 C4_0[256];
extern const u64 C5_0[256];
extern const u64 C6_0[256];
extern const u64 C7_0[256];

// Whirlpool-T
extern const u64 rc_T[R + 1];

extern const u64 C0_T[256];
extern const u64 C1_T[256];
extern const u64 C2_T[256];
extern const u64 C3_T[256];
extern const u64 C4_T[256];
extern const u64 C5_T[256];
extern const u64 C6_T[256];
extern const u64 C7_T[256];

// Whirlpool
extern const u64 rc[R + 1];

extern const u64 C0[256];
extern const u64 C1[256];
extern const u64 C2[256];
extern const u64 C3[256];
extern const u64 C4[256];
extern const u64 C5[256];
extern const u64 C6[256];
extern const u64 C7[256];

#endif
