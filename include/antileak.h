#pragma once

#include <stddef.h>
#include <stdlib.h> 

void* antileak_malloc(size_t n, const char* file, size_t line);
void antileak_free(void* p, const char* file, size_t line);
void* realloc_free(void* p, size_t n, const char* file, size_t line);
char* antileak_strdup(const char* s, const char* file, size_t line);

#ifdef _ANTILEAK
    //#pragma message "Compiling with _ANTILEAK defined"
    #define malloc(n) antileak_malloc(n, __FILE__, __LINE__)
    #define realloc(p, n) realloc_free(p, n, __FILE__, __LINE__)
    #define free(p) antileak_free(p, __FILE__, __LINE__)
    #define strdup(str) antileak_strdup(str, __FILE__, __LINE__)
#endif

