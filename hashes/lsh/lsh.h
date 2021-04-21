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

#ifndef _SIMD_LSH_H_
#define _SIMD_LSH_H_

#include "lsh_def.h"

/**
 * LSH512 내부 상태를 저장하기 위한 구조체
 */
struct LSH_ALIGNED_(32) LSH512_Context {
	LSH_ALIGNED_(16) lsh_type algtype;
	LSH_ALIGNED_(16) lsh_uint remain_databitlen;
	LSH_ALIGNED_(32) lsh_u64 cv_l[8];
	LSH_ALIGNED_(32) lsh_u64 cv_r[8];
	LSH_ALIGNED_(32) lsh_u8 last_block[LSH512_MSG_BLK_BYTE_LEN];
};

lsh_err lsh_init(struct LSH512_Context * ctx);
lsh_err lsh_update(struct LSH512_Context * ctx, const lsh_u8 * data, size_t databitlen);
lsh_err lsh_final(struct LSH512_Context * ctx, lsh_u8 * hashval);
lsh_err lsh_digest(const lsh_u8 * data, size_t databitlen, lsh_u8 * hashval);

#endif
