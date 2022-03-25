gcc main.c \
    dwh-hashkit/hashbox.c dwh-hashkit/lp_hash.c \
    dwh-hashkit/streebog/gost3411-2012-core.c dwh-hashkit/grostl/grostl.c \
    dwh-hashkit/md6/md6_compress.c dwh-hashkit/md6/md6_mode.c dwh-hashkit/jh/jh.c \
    dwh-hashkit/blake512/blake512.c \
    dwh-hashkit/lsh/ssse3/lsh512_ssse3.c dwh-hashkit/lsh/xop/lsh512_xop.c dwh-hashkit/lsh/sse2/lsh512_sse2.c \
    dwh-hashkit/lsh/lsh.c dwh-hashkit/lsh/no_arch/lsh512.c dwh-hashkit/lsh/avx2/lsh512_avx2.c \
    dwh-hashkit/skein/SHA3api_ref.c dwh-hashkit/skein/skein.c dwh-hashkit/skein/skein_block.c \
    dwh-hashkit/keccak3/keccak3.c dwh-hashkit/cubehash/cubehash.c \
    dwh-hashkit/whirlpool/Whirlpool.c dwh-hashkit/whirlpool/Whirlpool_constants_0.c dwh-hashkit/whirlpool/Whirlpool_constants.c dwh-hashkit/whirlpool/Whirlpool_constants_T.c \
    dwh-hashkit/fnv512/fnv512.c dwh-hashkit/fnv512/uint512.c \
     -o dwh-check -lssl -lcrypto
