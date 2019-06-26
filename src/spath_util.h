#include  <stdlib.h>
#include  <stdio.h>
/* allocate size bytes, returns NULL if size == 0,
 *  * calls er_abort if allocation fails */
#define SPATH_MALLOC(X) spath_malloc(X, __FILE__, __LINE__);
void* spath_malloc(size_t size, const char* file, int line);

