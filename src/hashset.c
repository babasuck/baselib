#include "baselib.h"

#include <stdint.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 100

typedef struct Bucket Bucket;

typedef struct Bucket {
    List* elements;
} Bucket;


typedef struct HashSet {
    Bucket** buckets;
    uint64_t capacity;
} HashSet;

Bucket* __Bucket_alloc() {
    return (Bucket*)malloc(sizeof(Bucket));
}

void __Bucket_ctor(Bucket* bucket) {
    List* list = List_alloc();
    List_ctr(list);
    bucket->elements = list;
}

void __Bucket_dtor(Bucket* bucket) {
    List_dtor(bucket->elements);
    free(bucket);
}

HashSet* HashSet_alloc() {
    return (HashSet*)malloc(sizeof(HashSet));
}

void HashSet_ctor(HashSet* hashSet) {
    hashSet->capacity = INITIAL_CAPACITY;
    Bucket** buckets = (Bucket**)calloc(hashSet->capacity, sizeof(Bucket*));
    for(int i = 0; i < hashSet->capacity; i++) {
        buckets[i] = __Bucket_alloc();
        __Bucket_ctor(buckets[i]);
    }
    hashSet->buckets = buckets;
}

void HashSet_dtor(HashSet* hashSet) {
    for(int i = 0; i < hashSet->capacity; i++) {
        __Bucket_dtor(hashSet->buckets[i]);
    }
    free(hashSet);
}
