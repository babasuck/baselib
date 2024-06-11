#include "baselib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 5

typedef struct Bucket Bucket;

typedef struct Bucket {
    Object object;
    List* elements;
} Bucket;

// Virtual Functions

char* __Bucket_ToString(Object* object) {
    Bucket* bucket = (Bucket*)object;
    char* buf = Object_toString((Object*)bucket->elements);
    int size = strlen(buf) * sizeof(*buf);
    char* str = (char*)malloc(size + 225);
    strcpy(str, "Bucket ");
    strncat(str, buf, size);
    free(buf);
    return str;
}

typedef struct HashSet {
    Object object;
    Bucket** buckets;
    uint64_t size;
    uint64_t capacity;
} HashSet;

Bucket* __Bucket_alloc() {
    return (Bucket*)malloc(sizeof(Bucket));
}

void __Bucket_ctor(Bucket* bucket) {
    Object_ctr((Object*)bucket, "Bucket");
    List* list = List_alloc();
    List_ctr(list);
    bucket->elements = list;

    // Setting V-Table
    bucket->object.toString = __Bucket_ToString;
}

void __Bucket_dtor(Bucket* bucket) {
    Object_dtor((Object*)bucket);
    List_dtor(bucket->elements);
    free(bucket);
}

HashSet* HashSet_alloc() {
    return (HashSet*)malloc(sizeof(HashSet));
}

void HashSet_ctor(HashSet* hashSet) {
    Object_ctr((Object*)hashSet, "HashSet");
    hashSet->capacity = INITIAL_CAPACITY;
    hashSet->size = 0;
    Bucket** buckets = (Bucket**)calloc(hashSet->capacity, sizeof(Bucket*));
    for(int i = 0; i < hashSet->capacity; i++) {
        buckets[i] = __Bucket_alloc();
        __Bucket_ctor(buckets[i]);
    }
    hashSet->buckets = buckets;
}

void HashSet_dtor(HashSet* hashSet) {
    Object_dtor((Object*)hashSet);
    for(int i = 0; i < hashSet->capacity; i++) {
        __Bucket_dtor(hashSet->buckets[i]);
    }
    free(hashSet->buckets);
    free(hashSet);
}

int HashSet_add(HashSet* hashSet, Object* el) {
    if (HashSet_contains(hashSet, el)) {
        return -1;
    }
    if (hashSet->size >= hashSet->capacity) {
        size_t new_capacity = hashSet->capacity * 2;
        //size_t a = List_getSize(hashSet->buckets[0]->elements);
        Bucket** newBuckets = (Bucket**)calloc(new_capacity, sizeof(Bucket*));
        for(int i = 0; i < new_capacity; i++) {
            newBuckets[i] = __Bucket_alloc();
            __Bucket_ctor(newBuckets[i]);
        }
        for (int i = 0; i <  hashSet->capacity; i++) {
            if(List_getSize(hashSet->buckets[i]->elements) > 0) {
                // Rehash
                for(int j = 0; j < List_getSize(hashSet->buckets[i]->elements); j++) {
                    Object* el = List_at(hashSet->buckets[i]->elements, j);
                    int newBucketNum = Object_hashCode(el) % new_capacity;
                    List_add(newBuckets[newBucketNum]->elements, el);
                }
            }
            __Bucket_dtor(hashSet->buckets[i]);
        }
        free(hashSet->buckets);
        hashSet->buckets = newBuckets;
        hashSet->capacity = new_capacity;
    }
    size_t bucketNum = Object_hashCode(el) % hashSet->capacity;
    List_add(hashSet->buckets[bucketNum]->elements, el);
    hashSet->size++;
    return 0;
}

void HashSet_print(HashSet* hashSet) {
    for (int i = 0; i < hashSet->capacity; i++) {
        char* buffer = Object_toString((Object*)(hashSet->buckets[i]));
        printf("%s\n", buffer);
        free(buffer);
    }
}

bool HashSet_contains(HashSet* hashSet, Object* object) {
    int num = Object_hashCode(object) % hashSet->capacity;
    for(int i = 0; i < List_getSize(hashSet->buckets[num]->elements); i++) {
        if(List_at(hashSet->buckets[num]->elements, i) == object) {
            return true;
        }
    }
    return false;
}