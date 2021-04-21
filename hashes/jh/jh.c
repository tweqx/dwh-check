#include "jh.h"

#ifdef __SSE2__
  #include "jh_sse2_opt64.h"
#else
  #include "jh_ansi_opt64.h"
#endif

/* hash a message,
   three inputs: message digest size in bits (hashbitlen); message (data); message length in bits (databitlen)
   one output:   message digest (hashval)
*/
int jh_hash(int hashbitlen, const BitSequence *data, DataLength databitlen, BitSequence *hashval)
{
      jh_state_t state;

      if ( hashbitlen == 224 || hashbitlen == 256 || hashbitlen == 384 || hashbitlen == 512 )
      {
          jh_init(&state, hashbitlen);
          jh_update(&state, data, databitlen);
          jh_final(&state, hashval);
          return SUCCESS;
      }
      else
          return(BAD_HASHLEN);
}
