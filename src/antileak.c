#include "antileak.h"
#include <stdio.h>
#include <stddef.h>

int malloc_sum = 0, free_sum = 0;

typedef struct MemoryBlock {
    size_t size;
    char data[];  // Гибкий массив для данных
} MemoryBlock;

void* antileak_malloc(size_t n, const char* file, size_t line) {
    MemoryBlock* block = (MemoryBlock*)malloc(sizeof(*block) + n);
    if (!block) {
        fprintf(stderr, "Ошибка выделения памяти в %s:%zu\n", file, line);
        return NULL;
    }
    block->size = n;
    malloc_sum += n;
    printf("Malloc в %s:%zu, всего выделено - %d байт\n", file, line, malloc_sum);
    return block->data;
}

void antileak_free(void* ptr, const char* file, size_t line) {
    if (!ptr) return;

    MemoryBlock* block = (MemoryBlock*)((char*)ptr - offsetof(MemoryBlock, data));
    free_sum += block->size;
    printf("Free в %s:%zu, всего освобождено - %d байт\n", file, line, free_sum);
    free(block);
}
