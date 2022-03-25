#include <string.h>
#include <stdbool.h>

#include "dwh-hashkit/hashbox.h"

int main(int argc, char** argv) {
  // Command line arguments - for now, only -h/--help
  if (argc > 1) {
    if (strcmp(argv[1], "-h") != 0 || strcmp(argv[1], "--help") != 0)
      printf("dwh-check : unrecognized option '%s'\n", argv[1]);

    puts("Usage : dwh-check [--help]\n"
         "Hash stdin and compare it against the deep web hash\n\n"

         "Return 0 if the deep web hash was found, 1 else\n\n"

         "Examples :\n"
         "  cat file | dwh-checker\n"
         "  find -type f -exec sh -c \"cat {} | dwh-check\" \\;\n");

    return 1;
  }

  // Hashing process
  hashbox_t* hashbox = hashbox_new();

  if (hashbox == NULL) {
    puts("fatal error : hashbox allocation failed");

    return 1;
  }

  // Read stdin and feed the hashbox
  char stdin_buffer[1024] = {0};
  int read;

  while (read = fread(stdin_buffer, sizeof(char), 1024, stdin))
    hashbox_update(hashbox, stdin_buffer, read * sizeof(char));

  if (ferror(stdin))
    puts("fatal error : reading from stdin failed");

  // Check results
  unsigned int results = hashbox_final(hashbox);

  if (results == HASHBOX_NO_MATCH)
    return 1;

  printf("Found the DWH, with ");
  switch (results) {
    case HASHBOX_SHA512:     puts("SHA-512"); break;
    case HASHBOX_BLAKE2B:    puts("BLAKE2b"); break;
    case HASHBOX_STREEBOG:   puts("Streebog"); break;
    case HASHBOX_SHA3:	     puts("SHA-3"); break;
    case HASHBOX_FNV0:       puts("FNV-0"); break;
    case HASHBOX_FNV1:       puts("FNV-1"); break;
    case HASHBOX_FNV1A:      puts("FNV-1a"); break;
    case HASHBOX_GROSTL:     puts("Grøstl"); break;
    case HASHBOX_MD6:        puts("MD6"); break;
    case HASHBOX_JH:         puts("JH"); break;
    case HASHBOX_BLAKE512:   puts("BLAKE-512"); break;
    case HASHBOX_LSH:        puts("LSH"); break;
    case HASHBOX_SKEIN:      puts("Skein"); break;
    case HASHBOX_KECCAK3:    puts("KECCAK-3"); break;
    case HASHBOX_CUBEHASH:   puts("CubeHash"); break;
    case HASHBOX_WHIRLPOOL0: puts("Whirlpool-0"); break;
    case HASHBOX_WHIRLPOOLT: puts("Whirlpool-T"); break;
    case HASHBOX_WHIRLPOOL:  puts("Whirlpool"); break;

    default:
      puts("MissingNo. (?!)");
  }

  return 0;
}
