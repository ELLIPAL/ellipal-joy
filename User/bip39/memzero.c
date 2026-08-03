#include "memzero.h"

/* A plain memset is not enough: this project builds at -Os, where the
 * compiler may drop the write as a dead store once the buffer goes out
 * of scope. The volatile byte loop (as in libsodium / trezor-crypto)
 * cannot be optimised away. */
void memzero(void *s, size_t n) {
	volatile unsigned char *volatile p = (volatile unsigned char *volatile) s;
	size_t i = 0;

	while (i < n) {
		p[i++] = 0U;
	}
}
