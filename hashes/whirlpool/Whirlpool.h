#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

#include "nessie.h"

// Parameters
#define WHIRLPOOL_0 0
#define WHIRLPOOL_T 1
#define WHIRLPOOL 2 /* Latest version */

void whirlpool_init(struct whirlpool_state_t * const structpointer, unsigned int version);
void whirlpool_update(const unsigned char * const source,
               unsigned long sourceBits,
               struct whirlpool_state_t * const structpointer);
void whirlpool_final(struct whirlpool_state_t * const structpointer,
                    unsigned char * const result);

#endif
