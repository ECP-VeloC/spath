#include "spath_util.h"
void* spath_malloc(size_t size, const char* file, int line)
{
  void* ptr = NULL;
  if (size > 0) {
    ptr = malloc(size);
    if (ptr == NULL) {
      fprintf(stderr, "Failed to allocate %llu bytes @ %s:%d", (unsigned long long) size, file, line);
    }
  }
  return ptr;
}
