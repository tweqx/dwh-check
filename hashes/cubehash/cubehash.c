#include "cubehash.h"

#include <stdlib.h>
#include <string.h>

void cubehash_round(cubehash_t* state) {
  uint32_t* x = state->state;

  /* 1. Add x[0jklm] into x[1jklm] modulo 2^32, for each (j,k,l,m) */
  for (unsigned int a = 0; a <= 0b01111; a++)
    x[0b10000 | a] += x[a];

  /* 2. Rotate x[0jklm] upwards by 7 bits, for each (j,k,l,m) */
  for (unsigned int a = 0; a <= 0b01111; a++)
    x[a] = x[a] << 7 | x[a] >> 25;

  /* 3. Swap x[00klm] with x[01klm], for each (k,l,m) */
  for (unsigned int a = 0; a <= 0b00111; a++) {
    uint32_t v = x[a];
    x[a] = x[0b01000 | a];
    x[0b01000 | a] = v;
  }

  /* 4. Xor x[1jklm] into x[0jklm], for each (j,k,l,m). */
  for (unsigned int a = 0; a <= 0b01111; a++)
    x[a] ^= x[0b10000 | a];

  /* 5. Swap x[1jk0m] with x[1jk1m], for each (j,k,m). */
  for (unsigned int a = 0b100; a <= 0b111; a++) {
    for (unsigned int b = 0; b <= 1; b++) {
      uint8_t n = a << 2 | b;

      uint32_t v = x[n];
      x[n] = x[0b00010 | n];
      x[0b00010 | n] = v;
    }
  }

  /* 6. Add x[0jklm] into x[1jklm] modulo 2^32, for each (j,k,l,m) */
  for (unsigned int a = 0; a <= 0b01111; a++)
    x[0b10000 | a] += x[a];

  /* 7. Rotate x[0jklm] upwards by 11 bits, for each (j,k,l,m) */
  for (unsigned int a = 0; a <= 0b01111; a++)
    x[a] = x[a] << 11 | x[a] >> 21;

  /* 8. Swap x[0j0lm] with x[0j1lm], for each (j,l,m) */
  for (unsigned int a = 0b00; a <= 0b11; a++) {
    for (unsigned int b = 0; b <= 1; b++) {
      uint8_t n = b << 3 | a;

      uint32_t v = x[n];
      x[n] = x[0b00100 | n];
      x[0b00100 | n] = v;
    }
  }

  /* 9. Xor x[1jklm] into x[0jklm], for each (j,k,l,m) */
  for (unsigned int a = 0; a <= 0b01111; a++)
    x[a] ^= x[0b10000 | a];

  /* 10. Swap x[1jkl0] with x[1jkl1], for each (j,k,l) */
  for (unsigned int a = 0b1000; a <= 0b1111; a++) {
    uint8_t n = a << 1;

    uint32_t v = x[n];
    x[n] = x[0b00001 | n];
    x[0b00001 | n] = v;
  }
}

void cubehash_init(cubehash_t* state, unsigned int i, unsigned int r, unsigned int b, unsigned int f, unsigned int h) {
  // Are parameters valid ?
  if (i == 0 || r == 0 || b == 0 || b > 128 || f == 0 || h < 7 || h > 512 || h % 8 != 0)
    return;

  // Parameters
  state->i = i;
  state->r = r;
  state->b = b;
  state->f = f;
  state->h = h;

  // Incomplete block
  state->remainder = malloc(b * sizeof(uint8_t));
  state->remainder_length = 0;

  if (state->remainder == NULL) {
    free(state->remainder);

    return;
  }

  // Internal state
  /* Set the first three state words x[00000], x[00001], x[00010] to the integers h/8, b, r respectively. */
  state->state[0b00000] = h/8;
  state->state[0b00001] = b;
  state->state[0b00010] = r;

  /* Set the remaining state words to 0 */
  for (unsigned int i = 0b00011; i <= 0b11111; i++)
    state->state[i] = 0;

  /* Then transform the state invertibly through i rounds */
  for (unsigned int i = 0; i < state->i; i++)
    cubehash_round(state);
}

// Processes a block
void cubehash_process(cubehash_t* state, const uint8_t* block) {
  /* Xors the first b-byte input block into the first b bytes of the state */
  int i = 0;
  for (; i < (signed)(state->b) - 3; i += 4)
    state->state[i / 4] ^= ((uint32_t*)block)[i / 4];

  for (; i < state->b; i++)
    ((uint8_t*)state->state)[i] ^= block[i];

  /* Transforms the state invertibly through r identical rounds */
  for (unsigned int rounds = 0; rounds < state->r; rounds++)
    cubehash_round(state);
}

void cubehash_update(cubehash_t* state, const unsigned char *data, size_t len) {
  // Attempts to process the incomplete block
  if (state->remainder_length + len >= state->b) {
    memcpy(&state->remainder[state->remainder_length], data, state->b - state->remainder_length);

    cubehash_process(state, state->remainder);

    len -= state->b - state->remainder_length;
    data += state->b - state->remainder_length;

    state->remainder_length = 0;
  }

  while (len >= state->b) {
    cubehash_process(state, data);

    len -= state->b;
    data += state->b;
  }

  // Save remaining bytes
  if (len > 0) {
    memcpy(&state->remainder[state->remainder_length], data, len);

    state->remainder_length += len;
  }
}

void cubehash_final(cubehash_t* state, unsigned char* digest) {
  /* Padding works as follows: append a 1 bit;
      then append the minimum possible number of 0 bits to reach a multiple of 8b bits.
     (The bits in a byte are first 128, then 64, then 32, then 16, then 8, then 4, then 2, then 1.)
     Implementations restricted to byte-aligned messages can simply append a 128 byte
      and then the minimum possible number of 0 bytes to reach a multiple of b bytes. */
  state->remainder[state->remainder_length] = 128;
  memset(&state->remainder[state->remainder_length + 1], 0, state->b - state->remainder_length - 1);

  cubehash_process(state, state->remainder);

  /* Xor the integer 1 into the last state word x[11111] */
  state->state[0b11111] ^= 1;

  /* Transform the state invertibly through f rounds */
  for (unsigned int i = 0; i < state->f; i++)
    cubehash_round(state);

  /* Finally, output the first h/8 bytes of the state. */
  unsigned int i = 0;

  for (; i < state->h / 8 - 3; i += 4)
    ((uint32_t*)digest)[i / 4] = state->state[i / 4];

  unsigned int shift = 24;
  while (i < state->h / 8) {
    digest[i] = (state->state[i / 4] >> shift) & 0xff;

    shift -= 8;
    i++;
  }
}

void cubehash_cleanup(cubehash_t* state) {
  free(state->remainder);
}

