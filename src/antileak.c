#include "antileak.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

int malloc_sum = 0, free_sum = 0;

typedef struct MemoryBlock {
    size_t size;
    char data[];  
} MemoryBlock;

void* antileak_malloc(size_t n, const char* file, size_t line) {
    MemoryBlock* block = (MemoryBlock*)malloc(sizeof(*block) + n);
    block->size = n;
    malloc_sum += n;
    printf("Malloc in %s:%zu, all alloc - %d b\n", file, line, malloc_sum);
    return block->data;
}

void* realloc_free(void* p, size_t n, const char* file, size_t line) {
    MemoryBlock* block = (MemoryBlock*)((char*)p - offsetof(MemoryBlock, data));
    malloc_sum += (n - block->size);
    MemoryBlock* newBlock = (MemoryBlock*)realloc(block, sizeof(*newBlock) + n);
    newBlock->size = n;
    printf("Realloc in %s:%zu, all alloc - %d b\n", file, line, malloc_sum);
    return newBlock->data;
}

void antileak_free(void* ptr, const char* file, size_t line) {
    if (!ptr) {
        fprintf(stderr, "Try to free null ptr in %s:%zu\n", file, line);
        return;
    }
    MemoryBlock* block = (MemoryBlock*)((char*)ptr - offsetof(MemoryBlock, data));
    free_sum += block->size;
    printf("Free in %s:%zu, all freed - %d b\n", file, line, free_sum);
    free(block);
}
