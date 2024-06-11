#include "baselib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 100

typedef struct Bucket Bucket;

typedef struct Bucket {
    Object object;
    List* elements;
} Bucket;

// Virtual Functions

char* __Bucket_ToString(Object* object) {
    Bucket* bucket = (Bucket*)bucket;
    return Object_ToString((Object*)bucket->elements);
}

typedef struct HashSet {
    Object object;
    Bucket** buckets;
    uint64_t capacity;
} HashSet;

Bucket* __Bucket_alloc() {
    return (Bucket*)malloc(sizeof(Bucket));
}

void __Bucket_ctor(Bucket* bucket) {
    Object_ctr(&bucket->object, "Bucket");
    List* list = List_alloc();
    List_ctr(list);
    bucket->elements = list;

    // Setting V-Table
    bucket->object.toString = __Bucket_ToString;
}

void __Bucket_dtor(Bucket* bucket) {
    List_dtor(bucket->elements);
    Object_dtor((Object*)bucket);
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
    Object_dtor((Object*)hashSet);
}

int HashSet_add(HashSet* hashSet, Object* el) {
    if (el == NULL) {
        return -1;
    }
    size_t bucketNum = Object_HashCode(el) % hashSet->capacity;
    List_add(hashSet->buckets[bucketNum]->elements, el);
}

void HashSet_print(HashSet* hashSet) {
    for (int i = 0; i < hashSet->capacity; i++) {
        char* buffer = Object_ToString((Object*)hashSet->buckets[i]);
        printf("%s\n", buffer);
        free(buffer);
    }
}