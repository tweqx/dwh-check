#ifndef SKEIN_AHS_API_H_
#define SKEIN_AHS_API_H_

/***********************************************************************
**
** Interface declarations of the AHS API using the Skein hash function.
**
** Source code author: Doug Whiting, 2008.
**
** This algorithm and source code is released to the public domain.
** 
************************************************************************/

#include "skein.h"

typedef struct
    {
    uint_t  statebits;                      /* 256, 512, or 1024 */
    union
        {
        Skein_Ctxt_Hdr_t h;                 /* common header "overlay" */
        Skein_256_Ctxt_t ctx_256;
        Skein_512_Ctxt_t ctx_512;
        Skein1024_Ctxt_t ctx1024;
        } u;
    }
    skein_state_t;

/* "incremental" hashing API */
int skein_init(skein_state_t *state, int hashbitlen);
int skein_update(skein_state_t *state, const u08b_t *data, size_t databitlen);
int skein_final(skein_state_t *state,       u08b_t *hashval);

/* "all-in-one" call */
int skein_hash(int hashbitlen,   const u08b_t *data, 
                  size_t databitlen,  u08b_t *hashval);

/*
** Re-define the compile-time constants below to change the selection
** of the Skein state size in the Init() function in SHA3api_ref.c.
**
** That is, the NIST API does not allow for explicit selection of the
** Skein block size, so it must be done implicitly in the Init() function.
** The selection is controlled by these constants.
*/
#ifndef SKEIN_256_NIST_MAX_HASHBITS
#define SKEIN_256_NIST_MAX_HASHBITS (0)
#endif

#ifndef SKEIN_512_NIST_MAX_HASHBITS
#define SKEIN_512_NIST_MAX_HASHBITS (512)
#endif

#endif  /* ifdef SKEIN_AHS_API_H_ */
