# dwh-check

Command line utility to check whether some data hashes to the deep web hash

Usage : `command | dwh-check`

Return 0 and prints a message when the deep web hash is found, returns 1 otherwise.

## Examples

`cat file | dwh-check`

`find -type f -exec sh -c "cat {} | dwh-check" \;`

`wget -o /dev/null -O - example.com | dwh-check`

`echo -n sheogmiof | dwh-check > /dev/null && echo O_o`

## Hashes supported
 * SHA-512
 * BLAKE2b
 * Streebog
 * SHA-3
 * FNV-0/FNV-1/FNV-1a
 * Grøstl
 * MD6
 * JH
 * BLAKE-512
 * LSH
 * Skein
 * Keccak3
 * CubeHash
 * Whirlpool-0/Whirlpool-T/Whirlpool

## License
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)
