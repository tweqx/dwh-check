gcc main.c \
    hashes/hashbox.c hashes/lp_hash.c \
    hashes/streebog/gost3411-2012-core.c hashes/grostl/grostl.c \
    hashes/md6/md6_compress.c hashes/md6/md6_mode.c hashes/jh/jh.c \
    hashes/blake512/blake512.c \
    hashes/lsh/ssse3/lsh512_ssse3.c hashes/lsh/xop/lsh512_xop.c hashes/lsh/sse2/lsh512_sse2.c \
    hashes/lsh/lsh.c hashes/lsh/no_arch/lsh512.c hashes/lsh/avx2/lsh512_avx2.c \
    hashes/skein/SHA3api_ref.c hashes/skein/skein.c hashes/skein/skein_block.c \
    hashes/keccak3/keccak3.c hashes/cubehash/cubehash.c \
    hashes/whirlpool/Whirlpool.c hashes/whirlpool/Whirlpool_constants_0.c hashes/whirlpool/Whirlpool_constants.c hashes/whirlpool/Whirlpool_constants_T.c \
    hashes/fnv512/fnv512.c hashes/fnv512/uint512.c \
     -o dwh-check -lssl -lcrypto
