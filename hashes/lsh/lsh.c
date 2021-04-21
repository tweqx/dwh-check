/*
 * Copyright (c) 2016 NSR (National Security Research Institute)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

#include "lsh.h"
#include "lsh_local.h"

#if LSH_COMPILE_AVX2
 #include "avx2/lsh512_avx2.h"

 #define lsh_impl_init lsh512_avx2_init
 #define lsh_impl_update lsh512_avx2_update
 #define lsh_impl_final lsh512_avx2_final
 #define lsh_impl_digest lsh512_avx2_digest
#elif LSH_COMPILE_XOP
 #include "xop/lsh512_xop.h"

 #define lsh_impl_init lsh512_xop_init
 #define lsh_impl_update lsh512_xop_update
 #define lsh_impl_final lsh512_xop_final
 #define lsh_impl_digest lsh512_xop_digest
#elif LSH_COMPILE_SSSE3
 #include "ssse3/lsh512_ssse3.h"

 #define lsh_impl_init lsh512_ssse3_init
 #define lsh_impl_update lsh512_ssse3_update
 #define lsh_impl_final lsh512_ssse3_final
 #define lsh_impl_digest lsh512_ssse3_digest
#elif LSH_COMPILE_SSE2
 #include "sse2/lsh512_sse2.h"

 #define lsh_impl_init lsh512_sse2_init
 #define lsh_impl_update lsh512_sse2_update
 #define lsh_impl_final lsh512_sse2_final
 #define lsh_impl_digest lsh512_sse2_digest
#else
 #include "no_arch/lsh512.h"

 #define lsh_impl_init lsh512_noarch_init
 #define lsh_impl_update lsh512_noarch_update
 #define lsh_impl_final lsh512_noarch_final
 #define lsh_impl_digest lsh512_noarch_digest
#endif

lsh_err lsh_init(struct LSH512_Context * state){
	if (state == NULL)
		return LSH_ERR_NULL_PTR;

	return lsh_impl_init(state, LSH_TYPE_512);
}
lsh_err lsh_update(struct LSH512_Context * state, const lsh_u8 * data, size_t databitlen){
	if (state == NULL)
		return LSH_ERR_NULL_PTR;

	return lsh_impl_update(state, data, databitlen);
}
lsh_err lsh_final(struct LSH512_Context * state, lsh_u8 * hashval){
	if (state == NULL)
		return LSH_ERR_NULL_PTR;

	return lsh_impl_final(state, hashval);
}

lsh_err lsh_digest(const lsh_u8 * data, size_t databitlen, lsh_u8 * hashval) {
	return lsh_impl_digest(LSH_TYPE_512, data, databitlen, hashval);
}

