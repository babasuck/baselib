#pragma once

#include <stddef.h>
#include <stdlib.h> 

void* antileak_malloc(size_t n, const char* file, size_t line);
void antileak_free(void* p, const char* file, size_t line);

#ifdef _ANTILEAK
    #define malloc(n) antileak_malloc(n, __FILE__, __LINE__)
    #define free(p) antileak_free(p, __FILE__, __LINE__)
#endif

